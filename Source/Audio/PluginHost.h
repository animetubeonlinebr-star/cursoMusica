#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

#include <functional>
#include <memory>

namespace cursomusica
{

// Owns the plugin format manager and the list of known VST3 plugins, and knows
// how to scan for new ones and instantiate them.
//
// All methods are message-thread only: plugin scanning and instantiation both
// touch the filesystem and allocate, so they must never run on the audio thread.
class PluginHost
{
public:
    PluginHost();
    ~PluginHost();

    juce::AudioPluginFormatManager& getFormatManager() noexcept { return formatManager; }
    juce::KnownPluginList& getKnownPluginList() noexcept { return knownList; }

    // Loads the cached plugin list from the properties file.
    void loadKnownPlugins();
    // Saves the current plugin list so the next launch does not rescan.
    void saveKnownPlugins();

    // Scans the default VST3 locations. Runs on a background thread; the
    // callback is invoked on the message thread as the scan progresses.
    void scanForPlugins (std::function<void (float progress, const juce::String& current)> onProgress,
                         std::function<void()> onFinished);

    // Instantiates a plugin. Returns nullptr and fills errorMessage on failure.
    std::unique_ptr<juce::AudioPluginInstance> createInstance (const juce::PluginDescription& description,
                                                               double sampleRate,
                                                               int blockSize,
                                                               juce::String& errorMessage);

    bool isScanning() const noexcept { return scanning.load(); }

private:
    class ScanJob;
    void addPluginsFromXml (const juce::XmlElement& xml);

    juce::AudioPluginFormatManager formatManager;
    juce::KnownPluginList knownList;

    std::unique_ptr<juce::PropertiesFile> properties;
    std::unique_ptr<ScanJob> scanJob;
    std::atomic<bool> scanning { false };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginHost)
};

} // namespace cursomusica
