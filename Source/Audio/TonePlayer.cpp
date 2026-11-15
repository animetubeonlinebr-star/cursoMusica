#include "Audio/TonePlayer.h"

#include "Course/NoteMath.h"

#include <cmath>

namespace cursomusica
{

namespace
{
    constexpr double twoPi = 6.283185307179586;
    constexpr double attackSeconds = 0.012;
    constexpr double releaseSeconds = 0.18;
}

void TonePlayer::prepare (double newSampleRate) noexcept
{
    sampleRate = newSampleRate > 0.0 ? newSampleRate : 44100.0;
    samplesPerNote = noteSeconds.load() * sampleRate;

    for (auto& activeVoice : voiceActive)
        activeVoice = false;

    active.store (false);
    noteIndex = 0;
    noteCount = 0;
    samplesIntoNote = 0.0;
}

void TonePlayer::play (const std::vector<int>& midiNotes)
{
    if (midiNotes.empty())
        return;

    const juce::SpinLock::ScopedTryLockType lock (requestLock);
    if (! lock.isLocked())
        return; // a request is already being consumed; drop this one

    pendingCount = 0;
    for (const int midi : midiNotes)
    {
        if (pendingCount >= maxNotes)
            break;
        pendingNotes[(size_t) pendingCount++] = midi;
    }

    active.store (true);
}

void TonePlayer::stop() noexcept
{
    active.store (false);
}

void TonePlayer::process (juce::AudioBuffer<float>& output, int numSamples) noexcept
{
    // Pick up a new request when the audio thread is free to take the lock.
    if (active.load())
    {
        const juce::SpinLock::ScopedTryLockType lock (requestLock);
        if (lock.isLocked() && pendingCount > 0)
        {
            noteCount = pendingCount;
            for (int i = 0; i < noteCount; ++i)
                notes[(size_t) i] = pendingNotes[(size_t) i];

            pendingCount = 0;
            noteIndex = 0;
            samplesIntoNote = 0.0;
            for (auto& activeVoice : voiceActive)
                activeVoice = false;
        }
    }

    if (! active.load())
        return;

    const int channels = output.getNumChannels();
    if (channels <= 0)
        return;

    const int attackSamples = juce::jmax (1, (int) (attackSeconds * sampleRate));
    const int releaseSamples = juce::jmax (1, (int) (releaseSeconds * sampleRate));
    const int durationSamples = juce::jmax (1, (int) samplesPerNote);

    auto* left = output.getWritePointer (0);
    auto* right = channels > 1 ? output.getWritePointer (1) : nullptr;

    for (int sample = 0; sample < numSamples; ++sample)
    {
        // Trigger the next note when the current slot is done.
        if (noteIndex < noteCount && samplesIntoNote <= 0.0)
        {
            const int midi = notes[(size_t) noteIndex];
            for (int v = 0; v < maxVoices; ++v)
                if (! voiceActive[(size_t) v])
                {
                    voiceActive[(size_t) v] = true;
                    voicePhase[(size_t) v] = 0.0;
                    voiceIncrement[(size_t) v] = twoPi * music::midiToFrequency (midi) / sampleRate;
                    break;
                }

            samplesIntoNote = (double) durationSamples;
            ++noteIndex;
        }

        float value = 0.0f;

        for (int v = 0; v < maxVoices; ++v)
        {
            if (! voiceActive[(size_t) v])
                continue;

            // Envelope: linear attack, then release to zero over the tail.
            const double age = (double) durationSamples - samplesIntoNote;
            double envelope = 1.0;
            if (age < attackSamples)
                envelope = age / (double) attackSamples;
            else if (samplesIntoNote < releaseSamples)
                envelope = samplesIntoNote / (double) releaseSamples;

            envelope = juce::jlimit (0.0, 1.0, envelope);
            const double phase = voicePhase[(size_t) v];
            value += (float) (envelope * (0.22 * (std::sin (phase) + 0.25 * std::sin (2.0 * phase))));

            voicePhase[(size_t) v] = std::fmod (phase + voiceIncrement[(size_t) v], twoPi);

            if (samplesIntoNote <= 1.0)
                voiceActive[(size_t) v] = false;
        }

        left[sample] += value;
        if (right != nullptr)
            right[sample] += value;

        if (samplesIntoNote > 0.0)
            samplesIntoNote -= 1.0;

        if (noteIndex >= noteCount && samplesIntoNote <= 0.0)
        {
            bool anyVoice = false;
            for (const auto playing : voiceActive)
                anyVoice = anyVoice || playing;

            if (! anyVoice)
            {
                active.store (false);
                break;
            }
        }
    }
}

} // namespace cursomusica
