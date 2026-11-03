#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace cursomusica
{

// Applies the project design tokens to the stock JUCE widgets.
class CursoLookAndFeel final : public juce::LookAndFeel_V4
{
public:
    CursoLookAndFeel();

    void drawButtonBackground (juce::Graphics& g,
                               juce::Button& button,
                               const juce::Colour& backgroundColour,
                               bool shouldDrawButtonAsHighlighted,
                               bool shouldDrawButtonAsDown) override;

    void drawComboBox (juce::Graphics& g,
                       int width, int height,
                       bool isButtonDown,
                       int buttonX, int buttonY, int buttonW, int buttonH,
                       juce::ComboBox& box) override;

    juce::Font getComboBoxFont (juce::ComboBox& box) override;
    juce::Font getLabelFont (juce::Label& label) override;
    juce::Font getTextButtonFont (juce::TextButton& button, int buttonHeight) override;
};

} // namespace cursomusica
