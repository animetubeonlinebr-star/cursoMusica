#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

#include <atomic>

#include "Course/TempoGrid.h"

namespace cursomusica
{

// Metronome click generator for the practice gate (REQ-015).
//
// Real-time safe: no allocation, no locks, no I/O. Parameters are published by
// the UI through atomics; the audio thread only reads them. The click is a
// short sine burst with a fast decay, accented on the first beat of the bar.
class Metronome
{
public:
    void prepare (double sampleRate) noexcept;
    void reset() noexcept;

    void setBpm (double newBpm) noexcept { bpm.store (juce::jlimit (20.0, 300.0, newBpm)); }
    void setSubdivision (course::TempoGrid::Subdivision s) noexcept { subdivision.store ((int) s); }
    void setBeatsPerBar (int beats) noexcept { beatsPerBar.store (juce::jmax (1, beats)); }
    void setRunning (bool shouldRun) noexcept { running.store (shouldRun); }
    void setGain (float linearGain) noexcept { gain.store (juce::jlimit (0.0f, 1.0f, linearGain)); }

    double getBpm() const noexcept { return bpm.load(); }
    bool isRunning() const noexcept { return running.load(); }

    // Number of clicks emitted since the last reset (used for the beat counter).
    int getBeatCount() const noexcept { return beatCount.load(); }

    // Adds the click into the output buffer. Called from the audio thread.
    void process (juce::AudioBuffer<float>& output, int numSamples) noexcept;

private:
    double sampleRate = 44100.0;

    std::atomic<double> bpm { 60.0 };
    std::atomic<int> subdivision { (int) course::TempoGrid::Subdivision::quarter };
    std::atomic<int> beatsPerBar { 4 };
    std::atomic<bool> running { false };
    std::atomic<float> gain { 0.6f };
    std::atomic<int> beatCount { 0 };

    // Audio-thread-only state.
    double samplesToNextClick = 0.0;
    double phase = 0.0;
    double phaseIncrement = 0.0;
    float envelope = 0.0f;
    float envelopeDecay = 0.0f;
    int beatIndex = 0;
};

} // namespace cursomusica
