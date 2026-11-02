#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace cursomusica
{

// Horizontal level meter driven by a value in dB. Visual only for now.
class LevelMeter final : public juce::Component
{
public:
    LevelMeter();

    void setLevelDb (float newLevelDb);
    void paint (juce::Graphics& g) override;

private:
    float levelDb = -100.0f;
    static constexpr float minDb = -60.0f;
    static constexpr float maxDb = 0.0f;
};

} // namespace cursomusica
