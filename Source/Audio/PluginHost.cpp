#include "Audio/PluginHost.h"

namespace cursomusica
{

namespace
{
    constexpr const char* pluginListXmlKey = "knownVst3Plugins";
}

// Runs a full scan of every format's default locations on a background thread.
class PluginHost::ScanJob final : public juce::Thread
{
public:
    ScanJob (juce::AudioPluginFormatManager& managerToUse,
             juce::KnownPluginList& listToFill,
             std::function<void (float, const juce::String&)> progressCallback,
             std::function<void()> finishedCallback)
        : juce::Thread ("CursoMusica plugin scan"),
          manager (managerToUse),
          list (listToFill),
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
                total += format->searchPathsForPlugins (format->getDefaultLocationsToSearch(), true, false).size();

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

            auto files = format->searchPathsForPlugins (format->getDefaultLocationsToSearch(), true, false);

            juce::PluginDirectoryScanner scanner (list, *format, format->getDefaultLocationsToSearch(),
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
