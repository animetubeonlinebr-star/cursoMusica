#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace cursomusica
{

// Large, high-contrast tuner: note name, cents deviation and a needle arc.
// Visual only for now; the value is set externally.
class TunerDisplay final : public juce::Component
{
public:
    TunerDisplay();

    // Frequency in Hz, or 0 when no pitch is detected.
    void setFrequencyHz (float newFrequencyHz);

    void paint (juce::Graphics& g) override;

private:
    void updateFromFrequency();

    float frequencyHz = 0.0f;
    juce::String noteName { "--" };
    int octave = 0;
    float centsOffset = 0.0f;
    bool hasPitch = false;

    static constexpr float concertA = 440.0f;
};

} // namespace cursomusica
