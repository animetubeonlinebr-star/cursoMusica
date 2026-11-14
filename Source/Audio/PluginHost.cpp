#include "Audio/PluginHost.h"

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

    // Default VST3 locations plus the user's folders, de-duplicated by path.
    juce::FileSearchPath buildSearchPath (juce::AudioPluginFormatManager& manager,
                                          const juce::FileSearchPath& userFolders)
    {
        juce::FileSearchPath result;

        if (auto* format = findVst3Format (manager))
        {
            const auto defaults = format->getDefaultLocationsToSearch();
            for (int i = 0; i < defaults.getNumPaths(); ++i)
                result.addIfNotAlreadyThere (defaults[i]);
        }

        for (int i = 0; i < userFolders.getNumPaths(); ++i)
            result.addIfNotAlreadyThere (userFolders[i]);

        return result;
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
{
    formatManager.addDefaultFormats();

    juce::PropertiesFile::Options options;
    options.applicationName = "CursoMusica";
    options.filenameSuffix = ".settings";
    options.folderName = "CursoMusica";
    options.osxLibrarySubFolder = "Application Support";
    options.storageFormat = juce::PropertiesFile::storeAsXML;

    properties = std::make_unique<juce::PropertiesFile> (options);
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
    if (properties == nullptr)
        return;

    searchPaths = PluginSearchPaths::deserialise (properties->getValue (pluginSearchPathsKey));

    const auto xmlText = properties->getValue (pluginListXmlKey);
    if (xmlText.isEmpty())
        return;

    if (auto xml = juce::parseXML (xmlText))
        knownList.recreateFromXml (*xml);
}

void PluginHost::saveKnownPlugins()
{
    if (properties == nullptr)
        return;

    if (auto xml = knownList.createXml())
        properties->setValue (pluginListXmlKey, xml->toString());
}

void PluginHost::saveSearchPaths()
{
    if (properties == nullptr)
        return;

    properties->setValue (pluginSearchPathsKey, searchPaths.serialise());
    // Flush now: the window writes through on every edit, and the app may be
    // closed before the properties timer fires.
    properties->saveIfNeeded();
    prunePluginsOutsideSearchPaths();
}

void PluginHost::prunePluginsOutsideSearchPaths()
{
    // Default locations are always searched, so only the user's folders can make
    // a previously known plugin unreachable.
    auto* format = findVst3Format (formatManager);
    if (format == nullptr)
        return;

    const auto defaults = format->getDefaultLocationsToSearch();
    const auto userFolders = searchPaths.resolveExisting();

    auto isInside = [] (const juce::File& file, const juce::FileSearchPath& folders)
    {
        for (int i = 0; i < folders.getNumPaths(); ++i)
            if (file.isAChildOf (folders[i]))
                return true;

        return false;
    };

    for (const auto& type : knownList.getTypes())
    {
        const juce::File file (type.fileOrIdentifier);
        if (! file.exists())
            continue; // non-file formats (e.g. AudioUnit ids) are left alone

        if (! isInside (file, defaults) && ! isInside (file, userFolders))
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
                                         buildSearchPath (formatManager, searchPaths.resolveExisting()),
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
