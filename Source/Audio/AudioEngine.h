#pragma once

#include <juce_audio_utils/juce_audio_utils.h>

#include <array>
#include <atomic>

#include "Audio/PitchDetector.h"
#include "Audio/PluginChain.h"

namespace cursomusica
{

// Handles device I/O and the real-time audio path.
//
// Real-time rules enforced by the callback in this class:
//   - no heap allocation, no locks, no I/O on the audio thread;
//   - UI <-> audio communication uses atomics and a lock-free FIFO only.
//
// Pitch detection is deliberately kept off the audio thread: the callback
// pushes samples into a lock-free FIFO and a dedicated analysis thread runs
// YIN on them. This keeps the callback bounded regardless of detector cost.
class AudioEngine final : public juce::AudioIODeviceCallback,
                          private juce::Thread
{
public:
    AudioEngine();
    ~AudioEngine() override;

    // Prepares the device manager and opens the most suitable input device.
    void initialise();
    void shutdown();

    juce::AudioDeviceManager& getDeviceManager() noexcept { return deviceManager; }
    PluginChain& getPluginChain() noexcept { return pluginChain; }

    // Re-prepares the plugin chain for the current device settings.
    void preparePluginChain();

    // Tries to open an input device, preferring low-latency backends and small buffers.
    juce::String openBestInputDevice();

    // Applies a buffer size to the current device. Returns an error string on failure.
    juce::String applyBufferSize (int samplesPerBlock);

    // Applies a sample rate to the current device. Returns an error string on failure.
    juce::String applySampleRate (double newSampleRate);

    // Snapshot values, safe to read from the UI thread.
    float getInputLevelDb() const noexcept { return inputLevelDb.load(); }
    float getDetectedFrequencyHz() const noexcept { return detectedFrequencyHz.load(); }
    double getCurrentSampleRate() const noexcept { return currentSampleRate.load(); }
    int getCurrentBlockSize() const noexcept { return currentBlockSize.load(); }
    double getEstimatedLatencyMs() const noexcept { return estimatedLatencyMs.load(); }
    bool isRunning() const noexcept { return running.load(); }
    juce::String getActiveBackendName() const;

    void audioDeviceIOCallbackWithContext (const float* const* inputChannelData,
                                           int numInputChannels,
                                           float* const* outputChannelData,
                                           int numOutputChannels,
                                           int numSamples,
                                           const juce::AudioIODeviceCallbackContext& context) override;

    void audioDeviceAboutToStart (juce::AudioIODevice* device) override;
    void audioDeviceStopped() override;

private:
    void pushSamplesToFifo (const float* data, int numSamples) noexcept;
    void run() override; // analysis thread: reads the FIFO, runs YIN

    juce::AudioDeviceManager deviceManager;

    // Peak level published as dB, updated from the audio thread.
    std::atomic<float> inputLevelDb { -100.0f };
    std::atomic<float> detectedFrequencyHz { 0.0f };
    std::atomic<double> currentSampleRate { 0.0 };
    std::atomic<int> currentBlockSize { 0 };
    std::atomic<double> estimatedLatencyMs { 0.0 };
    std::atomic<bool> running { false };

    // Lock-free handoff of input audio to the UI/analysis side.
    static constexpr int fifoSize = 1 << 14;
    juce::AbstractFifo audioFifo { fifoSize };
    std::array<float, fifoSize> fifoBuffer {};

    PitchDetector pitchDetector;
    PluginChain pluginChain;

    // Scratch buffer for the plugin chain, allocated once in audioDeviceAboutToStart.
    juce::AudioBuffer<float> pluginBuffer;
    juce::MidiBuffer pluginMidi;

    // Smooths the published level so the meter does not jump around.
    float levelSmoothingCoefficient = 0.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioEngine)
};

} // namespace cursomusica
