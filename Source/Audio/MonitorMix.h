#pragma once

namespace cursomusica::monitor
{

// Adds the captured input signal into every output channel, scaled by `gain`.
//
// This is the monitoring path the client asked for ("o aluno precisa ouvir o que
// está tocando"). It was missing: the audio callback cleared the outputs, mixed
// the metronome, the tone player and the backing track into them, and sent the
// input only to analysis — so the guitar was never audible.
//
// Header-only and JUCE-free so it can be unit-tested without a device, and so it
// adds no target to the build. Real-time safe: no allocation, no locks, no I/O.
inline void addToOutputs (float* const* outputs, int numOutputs,
                          const float* input, int numSamples, float gain) noexcept
{
    if (input == nullptr || gain <= 0.0f)
        return;

    for (int ch = 0; ch < numOutputs; ++ch)
    {
        float* const out = outputs[ch];
        if (out == nullptr)
            continue;

        for (int i = 0; i < numSamples; ++i)
            out[i] += input[i] * gain;
    }
}

} // namespace cursomusica::monitor
