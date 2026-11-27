#include "Audio/PluginHost.h"

#include "Data/AppSettings.h"

namespace cursomusica
{

namespace
{
    constexpr const char* pluginListXmlKey = "knownVst3Plugins";
    constexpr const char* pluginSearchPathsKey = "vst3SearchPaths";

    // The VST3 format from the manager, or nullptr when it is not registered.
    juce::AudioPluginFormat* findVst3Format (juce::AudioPluginFormatManager& manager)
    {
        for (auto* format : manager.getFormats())
            if (format != nullptr && format->getName().equalsIgnoreCase ("VST3"))
                return format;

        return nullptr;
    }

    // Default VST3 locations, used only when the user configured no folder.
    juce::FileSearchPath defaultSearchPaths (juce::AudioPluginFormatManager& manager)
    {
        juce::FileSearchPath result;

        if (auto* format = findVst3Format (manager))
        {
            const auto defaults = format->getDefaultLocationsToSearch();
            for (int i = 0; i < defaults.getNumPaths(); ++i)
                result.addIfNotAlreadyThere (defaults[i]);
        }

        return result;
    }

    // The folders the scan must search. The client asked the scan to stay inside
    // the selected folders instead of walking the whole computer, so the user's
    // folders replace the defaults as soon as one exists (see
    // PluginSearchPaths::resolveScanFolders).
    juce::FileSearchPath buildSearchPath (juce::AudioPluginFormatManager& manager,
                                          const PluginSearchPaths& userPaths)
    {
        return userPaths.resolveScanFolders (defaultSearchPaths (manager));
    }
}

// Runs a full scan of every format's search locations on a background thread.
class PluginHost::ScanJob final : public juce::Thread
{
public:
    ScanJob (juce::AudioPluginFormatManager& managerToUse,
             juce::KnownPluginList& listToFill,
             juce::FileSearchPath locationsToSearch,
             std::function<void (float, const juce::String&)> progressCallback,
             std::function<void()> finishedCallback)
        : juce::Thread ("CursoMusica plugin scan"),
          manager (managerToUse),
          list (listToFill),
          locations (std::move (locationsToSearch)),
          onProgress (std::move (progressCallback)),
          onFinished (std::move (finishedCallback))
    {
    }

    void run() override
    {
        const juce::File deadMansPedal = juce::File::getSpecialLocation (juce::File::tempDirectory)
                                             .getChildFile ("CursoMusicaPluginScan.txt");

        const auto formats = manager.getFormats();

        // Total work is the sum of the files across every format's search paths.
        int total = 0;
        for (auto* format : formats)
            if (format != nullptr)
                total += format->searchPathsForPlugins (locations, true, false).size();

        if (total == 0)
        {
            notifyFinished();
            return;
        }

        int done = 0;
        for (auto* format : formats)
        {
            if (format == nullptr || threadShouldExit())
                continue;

            juce::PluginDirectoryScanner scanner (list, *format, locations,
                                                  true, deadMansPedal, true);

            juce::String current;
            while (! threadShouldExit() && scanner.scanNextFile (true, current))
            {
                ++done;
                if (onProgress)
                    onProgress (juce::jlimit (0.0f, 1.0f, (float) done / (float) total), current);
            }
        }

        list.scanFinished();
        notifyFinished();
    }

private:
    void notifyFinished()
    {
        if (onFinished)
            juce::MessageManager::callAsync (onFinished);
    }

    juce::AudioPluginFormatManager& manager;
    juce::KnownPluginList& list;
    juce::FileSearchPath locations;
    std::function<void (float, const juce::String&)> onProgress;
    std::function<void()> onFinished;
};

PluginHost::PluginHost()
    : properties (data::AppSettings::get())
{
    formatManager.addDefaultFormats();
}

PluginHost::~PluginHost()
{
    if (scanJob != nullptr)
    {
        scanJob->stopThread (2000);
        scanJob.reset();
    }

    saveKnownPlugins();
}

void PluginHost::loadKnownPlugins()
{
    searchPaths = PluginSearchPaths::deserialise (properties.getValue (pluginSearchPathsKey));

    const auto xmlText = properties.getValue (pluginListXmlKey);
    if (xmlText.isEmpty())
        return;

    if (auto xml = juce::parseXML (xmlText))
        knownList.recreateFromXml (*xml);
}

void PluginHost::saveKnownPlugins()
{
    auto xml = knownList.createXml();
    if (xml == nullptr)
        return;

    const auto text = xml->toString();
    const auto stored = properties.getValue (pluginListXmlKey);

    // The list only goes to disk when it differs from what is stored, or when an
    // existing list has to be emptied: the shutdown save used to rewrite the
    // settings file on every exit, even for a session that only read the cache.
    if (text == stored || (stored.isEmpty() && knownList.getNumTypes() == 0))
        return;

    properties.setValue (pluginListXmlKey, text);

    // Flush now: the shared instance is not torn down at exit, so a scan that
    // finishes just before the app closes must not wait for the properties timer.
    properties.saveIfNeeded();
}

void PluginHost::saveSearchPaths()
{
    properties.setValue (pluginSearchPathsKey, searchPaths.serialise());
    // Flush now: the window writes through on every edit, and the app may be
    // closed before the properties timer fires.
    properties.saveIfNeeded();
    prunePluginsOutsideSearchPaths();
    saveKnownPlugins();   // the prune dropped types: persist the shorter list now
}

void PluginHost::prunePluginsOutsideSearchPaths()
{
    // The cache must match what the next scan will find, so the same rule that
    // builds the search path decides what to drop: once the user configured a
    // folder, a plugin living outside it (including the format's own default
    // locations) is no longer reachable and leaves the list.
    const auto scanFolders = buildSearchPath (formatManager, searchPaths);

    auto isInside = [] (const juce::File& file, const juce::FileSearchPath& folders)
    {
        for (int i = 0; i < folders.getNumPaths(); ++i)
            if (file.isAChildOf (folders[i]) || file == folders[i])
                return true;

        return false;
    };

    for (const auto& type : knownList.getTypes())
    {
        const juce::File file (type.fileOrIdentifier);
        if (! file.exists())
            continue; // non-file formats (e.g. AudioUnit ids) are left alone

        if (! isInside (file, scanFolders))
            knownList.removeType (type);
    }
}

void PluginHost::scanForPlugins (std::function<void (float, const juce::String&)> onProgress,
                                 std::function<void()> onFinished)
{
    if (scanning.exchange (true))
        return;

    if (scanJob != nullptr)
    {
        scanJob->stopThread (2000);
        scanJob.reset();
    }

    scanJob = std::make_unique<ScanJob> (formatManager, knownList,
                                         buildSearchPath (formatManager, searchPaths),
                                         std::move (onProgress),
                                         [this, finished = std::move (onFinished)]
                                         {
                                             scanning.store (false);
                                             saveKnownPlugins();
                                             if (finished)
                                                 finished();
                                         });

    scanJob->startThread (juce::Thread::Priority::normal);
}

std::unique_ptr<juce::AudioPluginInstance> PluginHost::createInstance (const juce::PluginDescription& description,
                                                                       double sampleRate,
                                                                       int blockSize,
                                                                       juce::String& errorMessage)
{
    auto instance = formatManager.createPluginInstance (description, sampleRate, blockSize, errorMessage);

    if (instance == nullptr)
        return {};

    // Plugins are used as an input insert: one input bus, one output bus,
    // both stereo unless the plugin insists otherwise.
    juce::AudioProcessor::BusesLayout layout;
    layout.inputBuses.add (juce::AudioChannelSet::stereo());
    layout.outputBuses.add (juce::AudioChannelSet::stereo());

    if (instance->checkBusesLayoutSupported (layout))
        instance->setBusesLayout (layout);
    else
        instance->setBusesLayoutWithoutEnabling (layout);

    return instance;
}

void PluginHost::addPluginsFromXml (const juce::XmlElement& xml)
{
    knownList.recreateFromXml (xml);
}

} // namespace cursomusica
