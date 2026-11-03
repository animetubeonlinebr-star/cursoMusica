#include "Audio/AudioEngine.h"

namespace cursomusica
{

namespace
{
    // Ordered by latency preference. ASIO is exclusive and lowest-latency on Windows;
    // WASAPI exclusive avoids the shared-mode mixer; ALSA/JACK fill the Linux roles.
    juce::StringArray preferredDeviceTypes()
    {
        return { "ASIO", "Windows Audio (Exclusive Mode)", "Windows Audio", "ALSA", "JACK", "CoreAudio" };
    }
}

AudioEngine::AudioEngine()
    : juce::Thread ("CursoMusica analysis")
{
}

AudioEngine::~AudioEngine()
{
    shutdown();
}

void AudioEngine::initialise()
{
    // Ask for input only; 2 outputs keeps the callback path symmetric without extra cost.
    deviceManager.initialiseWithDefaultDevices (1, 2);
    levelSmoothingCoefficient = 0.3f;

    startThread (juce::Thread::Priority::high);
}

void AudioEngine::shutdown()
{
    if (running.load())
    {
        deviceManager.removeAudioCallback (this);
        deviceManager.closeAudioDevice();
        running.store (false);
    }

    stopThread (1000);
}

juce::String AudioEngine::openBestInputDevice()
{
    auto& types = deviceManager.getAvailableDeviceTypes();

    juce::AudioIODeviceType* chosen = nullptr;
    for (const auto& wanted : preferredDeviceTypes())
        for (auto* type : types)
            if (type != nullptr && type->getTypeName() == wanted)
            {
                chosen = type;
                break;
            }

    if (chosen == nullptr)
        return "No supported audio backend found.";

    chosen->scanForDevices();
    deviceManager.setCurrentAudioDeviceType (chosen->getTypeName(), true);

    auto setup = deviceManager.getAudioDeviceSetup();

    const auto inputs = chosen->getDeviceNames (true);
    const auto outputs = chosen->getDeviceNames (false);

    if (inputs.isEmpty())
        return "No audio input device available.";

    setup.inputDeviceName = inputs[0];
    if (! outputs.isEmpty())
        setup.outputDeviceName = outputs[0];

    setup.useDefaultInputChannels = true;
    setup.useDefaultOutputChannels = true;

    const auto error = deviceManager.setAudioDeviceSetup (setup, true);
    if (error.isNotEmpty())
        return error;

    if (auto* device = deviceManager.getCurrentAudioDevice())
    {
        // Now that the device is open, narrow it down to the lowest-latency options.
        auto refined = deviceManager.getAudioDeviceSetup();

        const auto bufferSizes = device->getAvailableBufferSizes();
        if (! bufferSizes.isEmpty())
            refined.bufferSize = bufferSizes[0];

        const auto sampleRates = device->getAvailableSampleRates();
        if (! sampleRates.isEmpty())
            refined.sampleRate = sampleRates.getLast();

        const auto refineError = deviceManager.setAudioDeviceSetup (refined, true);
        if (refineError.isNotEmpty())
            return refineError;
    }

    if (auto* device = deviceManager.getCurrentAudioDevice())
    {
        const double sr = device->getCurrentSampleRate();
        const int block = device->getCurrentBufferSizeSamples();
        const double latency = device->getInputLatencyInSamples() / juce::jmax (1.0, sr)
                             + device->getOutputLatencyInSamples() / juce::jmax (1.0, sr);
        currentSampleRate.store (sr);
        currentBlockSize.store (block);
        estimatedLatencyMs.store (latency * 1000.0);
    }

    if (! running.load())
    {
        deviceManager.addAudioCallback (this);
        running.store (true);
    }

    return {};
}

juce::String AudioEngine::applyBufferSize (int samplesPerBlock)
{
    auto setup = deviceManager.getAudioDeviceSetup();
    setup.bufferSize = samplesPerBlock;
    const auto error = deviceManager.setAudioDeviceSetup (setup, true);

    if (error.isEmpty())
        currentBlockSize.store (samplesPerBlock);

    return error;
}

juce::String AudioEngine::applySampleRate (double newSampleRate)
{
    auto setup = deviceManager.getAudioDeviceSetup();
    setup.sampleRate = newSampleRate;
    const auto error = deviceManager.setAudioDeviceSetup (setup, true);

    if (error.isEmpty())
        currentSampleRate.store (newSampleRate);

    return error;
}

juce::String AudioEngine::getActiveBackendName() const
{
    if (auto* device = deviceManager.getCurrentAudioDevice())
        return device->getTypeName();

    return "none";
}

void AudioEngine::preparePluginChain()
{
    if (auto* device = deviceManager.getCurrentAudioDevice())
        pluginChain.prepare (device->getCurrentSampleRate(), device->getCurrentBufferSizeSamples());
}

void AudioEngine::audioDeviceAboutToStart (juce::AudioIODevice* device)
{
    const double sr = device->getCurrentSampleRate();
    const int block = device->getCurrentBufferSizeSamples();

    currentSampleRate.store (sr);
    currentBlockSize.store (block);

    const double latency = device->getInputLatencyInSamples() / juce::jmax (1.0, sr)
                         + device->getOutputLatencyInSamples() / juce::jmax (1.0, sr);
    estimatedLatencyMs.store (latency * 1000.0);

    pitchDetector.prepare (sr);
    audioFifo.reset();
    metronome.prepare (sr);

    // Allocate the plugin scratch buffer once, on the device-open (non-audio) thread.
    pluginBuffer.setSize (2, juce::jmax (block, 2048), false, true, true);
    pluginChain.setDeviceRunning (true);
    pluginChain.prepare (sr, block);
}

void AudioEngine::audioDeviceStopped()
{
    running.store (false);
    pluginChain.setDeviceRunning (false);
    inputLevelDb.store (-100.0f);
    detectedFrequencyHz.store (0.0f);
}

void AudioEngine::audioDeviceIOCallbackWithContext (const float* const* inputChannelData,
                                                    int numInputChannels,
                                                    float* const* outputChannelData,
                                                    int numOutputChannels,
                                                    int numSamples,
                                                    const juce::AudioIODeviceCallbackContext&)
{
    // Always clear outputs so a missing input never leaks stale audio.
    for (int ch = 0; ch < numOutputChannels; ++ch)
        if (outputChannelData[ch] != nullptr)
            juce::FloatVectorOperations::clear (outputChannelData[ch], numSamples);

    // Metronome plays on its own, independent of the input signal.
    if (outputChannelData[0] != nullptr && numOutputChannels > 0)
    {
        juce::AudioBuffer<float> outputView (outputChannelData, numOutputChannels, numSamples);
        metronome.process (outputView, numSamples);
    }

    const double blockSeconds = numSamples / juce::jmax (1.0, currentSampleRate.load());
    elapsedSeconds.store (elapsedSeconds.load() + blockSeconds);

    const float* in = (numInputChannels > 0 && inputChannelData[0] != nullptr) ? inputChannelData[0] : nullptr;

    if (in == nullptr)
    {
        inputLevelDb.store (-100.0f);
        detectedFrequencyHz.store (0.0f);
        pluginChain.process (pluginBuffer, pluginMidi); // keep the chain ticking
        return;
    }

    // Route the input through the plugin chain before analysis, so the tuner and
    // the meter reflect what the plugins actually produce.
    float* pluginChannel = nullptr;
    if (pluginBuffer.getNumSamples() >= numSamples && pluginBuffer.getNumChannels() > 0)
    {
        pluginBuffer.clear();
        pluginChannel = pluginBuffer.getWritePointer (0);
        juce::FloatVectorOperations::copy (pluginChannel, in, numSamples);

        // Mono input duplicated to stereo so stereo plugins see a full signal.
        if (pluginBuffer.getNumChannels() > 1)
            juce::FloatVectorOperations::copy (pluginBuffer.getWritePointer (1), in, numSamples);

        pluginMidi.clear();
        pluginChain.process (pluginBuffer, pluginMidi);
    }

    const float* analysed = pluginChannel != nullptr ? pluginChannel : in;

    // Peak level in dB, smoothed, no allocation.
    float peak = 0.0f;
    for (int i = 0; i < numSamples; ++i)
        peak = juce::jmax (peak, std::abs (analysed[i]));

    const float previous = inputLevelDb.load();
    const float target = peak > 0.0f ? juce::Decibels::gainToDecibels (peak, -100.0f) : -100.0f;
    inputLevelDb.store (previous + levelSmoothingCoefficient * (target - previous));

    // Hand the block to the analysis thread; nothing heavy happens here.
    pushSamplesToFifo (analysed, numSamples);
}

void AudioEngine::run()
{
    constexpr int analysisBlockSize = 512;
    std::array<float, analysisBlockSize> scratch {};
    int filled = 0;

    while (! threadShouldExit())
    {
        int start1 = 0, size1 = 0, start2 = 0, size2 = 0;
        audioFifo.prepareToRead (analysisBlockSize - filled, start1, size1, start2, size2);

        if (size1 > 0)
            std::copy_n (fifoBuffer.begin() + start1, size1, scratch.begin() + filled);
        if (size2 > 0)
            std::copy_n (fifoBuffer.begin() + start2, size2, scratch.begin() + filled + size1);

        audioFifo.finishedRead (size1 + size2);
        filled += size1 + size2;

        if (filled == analysisBlockSize)
        {
            const float hz = pitchDetector.processBlock (scratch.data(), analysisBlockSize);
            detectedFrequencyHz.store (hz);
            publishDetectedNote (hz);
            filled = 0;
        }
        else
        {
            // Nothing complete yet; avoid a busy spin.
            juce::Thread::sleep (2);
        }
    }
}

void AudioEngine::pushSamplesToFifo (const float* data, int numSamples) noexcept
{
    int start1 = 0, size1 = 0, start2 = 0, size2 = 0;
    audioFifo.prepareToWrite (numSamples, start1, size1, start2, size2);

    if (size1 > 0)
        std::copy_n (data, size1, fifoBuffer.begin() + start1);
    if (size2 > 0)
        std::copy_n (data + size1, size2, fifoBuffer.begin() + start2);

    audioFifo.finishedWrite (size1 + size2);
}

void AudioEngine::publishDetectedNote (float frequencyHz) noexcept
{
    const int midi = music::analyseFrequency (frequencyHz, 440.0).midi;

    // Only queue a note when a new, stable note starts: skip silence and the
    // repeated frames of the note already sounding.
    if (midi <= 0)
    {
        lastQueuedMidi = -1;
        return;
    }

    const double now = elapsedSeconds.load();
    if (midi == lastQueuedMidi && (now - lastNoteTime) < 0.05)
        return;

    lastQueuedMidi = midi;
    lastNoteTime = now;

    const int write = noteWriteIndex.load();
    const int next = (write + 1) % noteQueueSize;
    if (next == noteReadIndex.load())
        return; // queue full: drop rather than block the analysis thread

    noteQueue[(std::size_t) write] = { now, midi,
                                       music::analyseFrequency (frequencyHz, 440.0).cents };
    noteWriteIndex.store (next);
}

void AudioEngine::drainNoteEvents (std::vector<course::NoteEvent>& out)
{
    int read = noteReadIndex.load();
    const int write = noteWriteIndex.load();

    while (read != write)
    {
        out.push_back (noteQueue[(std::size_t) read]);
        read = (read + 1) % noteQueueSize;
    }

    noteReadIndex.store (read);
}

void AudioEngine::resetNoteCapture()
{
    noteReadIndex.store (noteWriteIndex.load());
    lastQueuedMidi = -1;
    elapsedSeconds.store (0.0);
}

} // namespace cursomusica
