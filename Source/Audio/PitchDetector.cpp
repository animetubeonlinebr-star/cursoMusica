#include "Audio/PitchDetector.h"

#include <cmath>

namespace cursomusica
{

namespace
{
    constexpr float yinThreshold = 0.15f;
    constexpr float minRms = 0.01f; // silence gate, avoids tracking noise
}

void PitchDetector::prepare (double sampleRateToUse)
{
    sampleRate = sampleRateToUse > 0.0 ? sampleRateToUse : 44100.0;
    reset();
}

void PitchDetector::reset()
{
    std::fill (std::begin (history), std::end (history), 0.0f);
    std::fill (std::begin (difference), std::end (difference), 0.0f);
    std::fill (std::begin (cumulative), std::end (cumulative), 0.0f);
    stored = 0;
}

float PitchDetector::processBlock (const float* data, int numSamples)
{
    if (data == nullptr || numSamples <= 0)
        return 0.0f;

    // Keep the most recent historySize samples in a fixed-size ring.
    for (int i = 0; i < numSamples; ++i)
    {
        history[stored % historySize] = data[i];
        ++stored;
    }

    if (stored < windowSize)
        return 0.0f;

    return runYin();
}

float PitchDetector::runYin()
{
    // Copy the most recent windowSize samples in chronological order.
    float frame[windowSize] {};
    const int startIndex = stored - windowSize;
    for (int i = 0; i < windowSize; ++i)
        frame[i] = history[(startIndex + i) % historySize];

    double sumSquares = 0.0;
    for (float s : frame)
        sumSquares += static_cast<double> (s) * s;

    const float rms = static_cast<float> (std::sqrt (sumSquares / windowSize));
    if (rms < minRms)
        return 0.0f;

    // Difference function.
    for (int tau = 1; tau < maxTau; ++tau)
    {
        double sum = 0.0;
        for (int i = 0; i < maxTau; ++i)
        {
            const double delta = static_cast<double> (frame[i]) - frame[i + tau];
            sum += delta * delta;
        }
        difference[tau] = static_cast<float> (sum);
    }

    // Cumulative mean normalised difference.
    cumulative[0] = 1.0f;
    double runningSum = 0.0;
    for (int tau = 1; tau < maxTau; ++tau)
    {
        runningSum += difference[tau];
        cumulative[tau] = runningSum > 0.0
                            ? static_cast<float> (difference[tau] * tau / runningSum)
                            : 1.0f;
    }

    // Absolute threshold: first dip below the threshold, else the global minimum.
    int tauEstimate = -1;
    for (int tau = 2; tau < maxTau; ++tau)
    {
        if (cumulative[tau] < yinThreshold)
        {
            while (tau + 1 < maxTau && cumulative[tau + 1] < cumulative[tau])
                ++tau;
            tauEstimate = tau;
            break;
        }
    }

    if (tauEstimate == -1)
    {
        float best = cumulative[2];
        tauEstimate = 2;
        for (int tau = 3; tau < maxTau; ++tau)
            if (cumulative[tau] < best)
            {
                best = cumulative[tau];
                tauEstimate = tau;
            }

        if (best > 0.5f)
            return 0.0f; // not confident enough to report a pitch
    }

    // Parabolic interpolation around the estimate for sub-sample accuracy.
    float betterTau = static_cast<float> (tauEstimate);
    if (tauEstimate > 0 && tauEstimate < maxTau - 1)
    {
        const float x0 = cumulative[tauEstimate - 1];
        const float x2 = cumulative[tauEstimate + 1];
        const float denom = 2.0f * (2.0f * cumulative[tauEstimate] - x2 - x0);
        if (std::abs (denom) > 1.0e-9f)
            betterTau += (x2 - x0) / denom;
    }

    if (betterTau <= 0.0f)
        return 0.0f;

    return static_cast<float> (sampleRate) / betterTau;
}

} // namespace cursomusica
