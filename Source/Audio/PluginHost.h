#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

#include <functional>
#include <memory>

#include "Audio/PluginSearchPaths.h"

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

    // User-configured VST3 folders (client request). Message thread only.
    PluginSearchPaths& getSearchPaths() noexcept { return searchPaths; }
    const PluginSearchPaths& getSearchPaths() const noexcept { return searchPaths; }
    // Persists the current folder list and drops the cached plugin types that
    // came from folders no longer configured.
    void saveSearchPaths();
    // The folder list changed: forget the plugins that lived in removed folders
    // so a rescan does not keep offering them.
    void prunePluginsOutsideSearchPaths();

    // Scans the configured VST3 locations (default locations plus the user's
    // folders). Runs on a background thread; the callback is invoked on the
    // message thread as the scan progresses.
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

    PluginSearchPaths searchPaths;

    std::unique_ptr<juce::PropertiesFile> properties;
    std::unique_ptr<ScanJob> scanJob;
    std::atomic<bool> scanning { false };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginHost)
};

} // namespace cursomusica
