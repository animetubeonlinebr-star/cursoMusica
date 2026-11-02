#pragma once

#include "UI/Design/Panel.h"
#include "UI/LevelMeter.h"

namespace cursomusica
{

// Study controls: play, loop and speed. Placeholders for now.
class TransportPanel final : public Panel
{
public:
    TransportPanel();

    void resized() override;

private:
    juce::TextButton playButton { "Play" };
    juce::TextButton loopButton { "Loop" };
    juce::Slider speedSlider { juce::Slider::LinearHorizontal, juce::Slider::NoTextBox };
    juce::Label speedCaption;
    juce::Label levelCaption;
    LevelMeter levelMeter;
};

} // namespace cursomusica
