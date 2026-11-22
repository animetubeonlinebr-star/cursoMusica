#include "Audio/BackingTrack.h"

#include <cmath>

namespace cursomusica
{

namespace
{
    // Drum voices are short pitched blips; the pitch and decay carry the timbre.
    constexpr double kickFrequency = 55.0;
    constexpr double snareFrequency = 190.0;
    constexpr double hatFrequency = 8000.0;

    constexpr double kickDecay = 0.16;
    constexpr double snareDecay = 0.10;
    constexpr double hatDecay = 0.035;

    constexpr double bassDecay = 0.55;
    constexpr double padDecay = 1.60;

    constexpr float kickLevel = 0.85f;
    constexpr float snareLevel = 0.45f;
    constexpr float hatLevel = 0.18f;
    constexpr float bassLevel = 0.42f;
    constexpr float padLevel = 0.16f;

    // Kick + hat + bass + a four-note pad peak near 2.1 before this factor. The
    // mix headroom keeps the sum under full scale so the bed never clips when the
    // user gain is at 1.0 (the voices are summed, not mixed).
    constexpr float mixHeadroom = 0.38f;

    double midiToFrequency (int midi) noexcept
    {
        return 440.0 * std::pow (2.0, (midi - 69) / 12.0);
    }
}

void BackingTrack::prepare (double sampleRateToUse) noexcept
{
    sampleRate = sampleRateToUse > 0.0 ? sampleRateToUse : 44100.0;
    reset();
}

void BackingTrack::reset() noexcept
{
    samplesToNextStep = 0.0;
    stepInBar = 0;
    started = false;
    chordIndex = 0;
    currentChord.store (0);
    currentChordMask.store (0);

    for (int v = 0; v < maxVoices; ++v)
    {
        voiceActive[(size_t) v] = false;
        voiceEnvelope[(size_t) v] = 0.0f;
        voicePhase[(size_t) v] = 0.0;
    }
}

void BackingTrack::setProgression (const std::vector<Chord>& newChords)
{
    // Message thread: take the lock for real. Dropping the request on a busy
    // callback would leave the UI showing a progression the audio never got.
    // The audio thread only ever holds it for the short copy below, and it never
    // waits for it (try-lock), so this cannot stall the callback.
    const juce::SpinLock::ScopedLockType lock (requestLock);

    pendingCount = juce::jmin ((int) newChords.size(), maxChords);
    for (int c = 0; c < pendingCount; ++c)
    {
        auto& stored = pendingChords[(size_t) c];
        const auto& source = newChords[(size_t) c];
        stored.count = juce::jmin ((int) source.pitchClasses.size(), maxPitchClasses);
        for (int p = 0; p < stored.count; ++p)
            stored.pitchClasses[p] = ((source.pitchClasses[(size_t) p] % 12) + 12) % 12;
        stored.bassMidi = source.bassMidi;
    }

    chordCount.store (pendingCount);
    // The version lets the audio thread adopt a new progression even when the
    // chord count matches the previous one (two different 4-chord vamps).
    publishVersion.fetch_add (1);
}

void BackingTrack::triggerVoice (int midi, float velocity, double decaySeconds) noexcept
{
    for (int v = 0; v < maxVoices; ++v)
    {
        if (voiceActive[(size_t) v])
            continue;

        voiceActive[(size_t) v] = true;
        voicePhase[(size_t) v] = 0.0;
        voiceIncrement[(size_t) v] = 2.0 * juce::MathConstants<double>::pi
                                       * midiToFrequency (midi) / sampleRate;
        voiceEnvelope[(size_t) v] = 1.0f;
        voiceDecay[(size_t) v] = (float) std::exp (-1.0 / juce::jmax (1.0, decaySeconds * sampleRate / 4.0));
        voiceLevel[(size_t) v] = velocity;
        return;
    }
}

void BackingTrack::process (juce::AudioBuffer<float>& output, int numSamples) noexcept
{
    if (! running.load())
        return;

    // Take a new progression if the UI published one and the audio thread is not
    // already reading it (the lock is only ever held for the copy below).
    {
        const juce::SpinLock::ScopedTryLockType lock (requestLock);
        const unsigned published = publishVersion.load();
        if (lock.isLocked() && published != consumedVersion)
        {
            consumedVersion = published;
            activeChords = pendingCount;
            for (int c = 0; c < activeChords; ++c)
                chords[(size_t) c] = pendingChords[(size_t) c];
            chordIndex = 0;
            currentChord.store (0);
            samplesToNextStep = 0.0;
            stepInBar = 0;
            started = false;
        }
    }

    if (activeChords <= 0)
        return;

    const double currentBpm = juce::jmax (1.0, bpm.load());
    const double samplesPerStep = (30.0 / currentBpm) * sampleRate; // one eighth note
    const float currentGain = gain.load();
    const int channels = output.getNumChannels();

    for (int i = 0; i < numSamples; ++i)
    {
        if (samplesToNextStep <= 0.0)
        {
            if (stepInBar == 0)
            {
                // The downbeat starts a bar: move to the next chord, except on
                // the very first bar after a (re)start.
                if (started)
                    chordIndex = (chordIndex + 1) % activeChords;
                started = true;
                currentChord.store (chordIndex);

                const auto& sounding = chords[(size_t) chordIndex];
                unsigned mask = 0;
                for (int p = 0; p < sounding.count; ++p)
                    mask |= 1u << (unsigned) sounding.pitchClasses[(size_t) p];
                currentChordMask.store (mask);
            }

            const auto& chord = chords[(size_t) chordIndex];
            const bool downbeat = stepInBar == 0;
            const bool backbeat = stepInBar == 4;

            // Drums: kick on 1 and 3, snare on 2 and 4, hi-hat on every eighth.
            if (downbeat || backbeat)
                triggerVoice ((int) kickFrequency, kickLevel, kickDecay);
            if (stepInBar == 2 || stepInBar == 6)
                triggerVoice ((int) snareFrequency, snareLevel, snareDecay);
            triggerVoice ((int) hatFrequency, hatLevel, hatDecay);

            if (chord.count > 0)
            {
                // Bass: root on the downbeat and beat 3, fifth on 2 and 4.
                const int root = chord.bassMidi;
                triggerVoice (downbeat || backbeat ? root : root + 7, bassLevel, bassDecay);

                // Keyboard: the chord's notes held as a pad, re-struck each bar.
                if (downbeat)
                    for (int p = 0; p < chord.count; ++p)
                        triggerVoice (48 + chord.pitchClasses[(size_t) p], padLevel, padDecay);
            }

            samplesToNextStep += samplesPerStep;
            stepInBar = (stepInBar + 1) % 8;
        }

        for (int v = 0; v < maxVoices; ++v)
        {
            if (! voiceActive[(size_t) v])
                continue;

            const float sample = (float) std::sin (voicePhase[(size_t) v])
                                   * voiceEnvelope[(size_t) v] * voiceLevel[(size_t) v]
                                   * currentGain * mixHeadroom;

            for (int ch = 0; ch < channels; ++ch)
                output.addSample (ch, i, sample);

            voicePhase[(size_t) v] += voiceIncrement[(size_t) v];
            voiceEnvelope[(size_t) v] *= voiceDecay[(size_t) v];

            if (voiceEnvelope[(size_t) v] < 0.0001f)
                voiceActive[(size_t) v] = false;
        }

        samplesToNextStep -= 1.0;
    }
}

} // namespace cursomusica
