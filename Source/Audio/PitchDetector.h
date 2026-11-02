#pragma once

#include <juce_core/juce_core.h>

#include <array>

namespace cursomusica
{

// Monophonic pitch detector based on the YIN algorithm
// (de Cheveigne & Kawahara, 2002).
//
// Allocation-free: all storage is fixed-size, so it is safe to drive from
// either the audio thread or a dedicated analysis thread.
class PitchDetector
{
public:
    static constexpr int windowSize = 2048; // correlation window
    static constexpr int maxTau    = 1024;  // lowest detectable period

    void prepare (double sampleRateToUse);
    void reset();

    // Appends a block and returns the detected frequency in Hz, or 0 if none.
    float processBlock (const float* data, int numSamples);

private:
    float runYin();

    double sampleRate = 44100.0;

    static constexpr int historySize = windowSize + maxTau;
    float history[historySize] {};
    int stored = 0;

    float difference[maxTau] {};
    float cumulative[maxTau] {};
};

} // namespace cursomusica
