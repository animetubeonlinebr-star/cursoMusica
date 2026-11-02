#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

#include <array>
#include <atomic>
#include <memory>
#include <vector>

namespace cursomusica
{

// Ordered chain of VST3 plugins inserted on the input path.
//
// Threading contract
// ------------------
// The audio thread only reads a raw pointer array published through an atomic
// index, so it never locks and never allocates. Ownership lives in `owned`,
// touched only by the message thread.
//
// Every structural change follows the same protocol:
//   1. apply the change to `owned`, moving any removed instance to `pendingDelete`,
//   2. publish a new raw pointer array by flipping the active index,
//   3. wait until the audio thread reports it processed the new index,
//   4. free `pendingDelete`.
//
// Step 3 makes removal safe. The audio thread publishes the index it used at
// the end of each callback, and it runs on a single thread, so once it reports
// the new index, no callback can still be holding a pointer from the old array.
// If the device is stopped, no callback will ever arrive, so the wait times out
// and deletion proceeds — safe, because nothing is reading the array.
class PluginChain
{
public:
    static constexpr int maxPlugins = 8;

    PluginChain();
    ~PluginChain();

    // Message thread. Takes ownership of the instance.
    void addPlugin (std::unique_ptr<juce::AudioPluginInstance> instance);
    // Message thread. Removes the plugin at index.
    void removePlugin (int index);
    // Message thread. Removes everything.
    void clear();

    // Message thread, called when the device opens. Re-prepares all plugins.
    void prepare (double sampleRate, int maximumBlockSize);

    // Message thread. Tells the chain whether the audio device is currently
    // running, so it can skip waiting for a callback that will never arrive.
    void setDeviceRunning (bool isRunning) noexcept { deviceRunning.store (isRunning); }

    // Audio thread. Processes the buffer in place through every active plugin.
    void process (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi) noexcept;

    // Message thread.
    int getNumPlugins() const;
    juce::AudioPluginInstance* getPlugin (int index) const;

private:
    struct SlotArray
    {
        std::array<juce::AudioPluginInstance*, maxPlugins> plugins {};
        int count = 0;
    };

    void publish (const SlotArray& next);
    void waitForAudioThread (int publishedIndex);

    // Authoritative ownership. Message thread only.
    std::vector<std::unique_ptr<juce::AudioPluginInstance>> owned;
    std::vector<std::unique_ptr<juce::AudioPluginInstance>> pendingDelete;

    // Raw pointer snapshots published to the audio thread.
    std::array<SlotArray, 2> slots;
    std::atomic<int> activeIndex { 0 };
    std::atomic<int> lastProcessedIndex { -1 };
    std::atomic<bool> deviceRunning { false };

    double currentSampleRate = 44100.0;
    int currentBlockSize = 512;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginChain)
};

} // namespace cursomusica
