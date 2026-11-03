#include "Audio/Metronome.h"

#include <cmath>

namespace cursomusica
{

namespace
{
    constexpr double clickFrequency = 1000.0;
    constexpr double accentFrequency = 1500.0;
    constexpr double clickDurationSeconds = 0.03;
}

void Metronome::prepare (double sampleRateToUse) noexcept
{
    sampleRate = sampleRateToUse > 0.0 ? sampleRateToUse : 44100.0;
    envelopeDecay = (float) std::exp (-1.0 / (clickDurationSeconds * sampleRate / 3.0));
    reset();
}

void Metronome::reset() noexcept
{
    samplesToNextClick = 0.0;
    phase = 0.0;
    phaseIncrement = 0.0;
    envelope = 0.0f;
    beatIndex = 0;
    beatCount.store (0);
}

void Metronome::process (juce::AudioBuffer<float>& output, int numSamples) noexcept
{
    if (! running.load())
        return;

    const double currentBpm = juce::jmax (1.0, bpm.load());
    const auto currentSubdivision = (course::TempoGrid::Subdivision) subdivision.load();

    // Seconds per click, matching TempoGrid so the audio and the math agree.
    double secondsPerClick = 60.0 / currentBpm;
    switch (currentSubdivision)
    {
        case course::TempoGrid::Subdivision::quarter:   secondsPerClick = 60.0 / currentBpm; break;
        case course::TempoGrid::Subdivision::eighth:    secondsPerClick = 30.0 / currentBpm; break;
        case course::TempoGrid::Subdivision::triplet:   secondsPerClick = 20.0 / currentBpm; break;
        case course::TempoGrid::Subdivision::sixteenth: secondsPerClick = 15.0 / currentBpm; break;
    }

    const double samplesPerClick = secondsPerClick * sampleRate;
    const float currentGain = gain.load();
    const int barLength = juce::jmax (1, beatsPerBar.load());
    const int channels = output.getNumChannels();

    for (int i = 0; i < numSamples; ++i)
    {
        if (samplesToNextClick <= 0.0)
        {
            const bool accent = (beatIndex % barLength) == 0;
            phase = 0.0;
            phaseIncrement = 2.0 * juce::MathConstants<double>::pi
                               * (accent ? accentFrequency : clickFrequency) / sampleRate;
            envelope = 1.0f;
            samplesToNextClick += samplesPerClick;
            ++beatIndex;
            beatCount.fetch_add (1);
        }

        if (envelope > 0.0001f)
        {
            const float sample = (float) std::sin (phase) * envelope * currentGain;
            for (int ch = 0; ch < channels; ++ch)
                output.addSample (ch, i, sample);

            phase += phaseIncrement;
            envelope *= envelopeDecay;
        }

        samplesToNextClick -= 1.0;
    }
}

} // namespace cursomusica
