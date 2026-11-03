#include "UI/TransportPanel.h"

#include "UI/Design/Theme.h"

namespace cursomusica
{

namespace th = cursomusica::theme;

TransportPanel::TransportPanel()
    : Panel ("Study")
{
    playButton.setClickingTogglesState (true);
    loopButton.setClickingTogglesState (true);
    addAndMakeVisible (playButton);
    addAndMakeVisible (loopButton);

    speedSlider.setRange (0.5, 1.5, 0.05);
    speedSlider.setValue (1.0);
    addAndMakeVisible (speedSlider);

    speedCaption.setText ("SPEED", juce::dontSendNotification);
    speedCaption.setFont (th::type::makeFont (th::type::caption));
    speedCaption.setColour (juce::Label::textColourId, th::colour::textSecondary);
    addAndMakeVisible (speedCaption);

    levelCaption.setText ("INPUT LEVEL", juce::dontSendNotification);
    levelCaption.setFont (th::type::makeFont (th::type::caption));
    levelCaption.setColour (juce::Label::textColourId, th::colour::textSecondary);
    addAndMakeVisible (levelCaption);

    addAndMakeVisible (levelMeter);
}

void TransportPanel::resized()
{
    auto content = getContentBounds();

    const int buttonHeight = 34;
    auto buttons = content.removeFromTop (buttonHeight);
    const int buttonWidth = juce::jmin (110, buttons.getWidth() / 2 - th::spacing::sm);
    playButton.setBounds (buttons.removeFromLeft (buttonWidth));
    buttons.removeFromLeft (th::spacing::sm);
    loopButton.setBounds (buttons.removeFromLeft (buttonWidth));

    content.removeFromTop (th::spacing::lg);

    auto speedArea = content.removeFromTop (16 + 24);
    speedCaption.setBounds (speedArea.removeFromTop (16));
    speedSlider.setBounds (speedArea.removeFromTop (24));

    content.removeFromTop (th::spacing::lg);

    auto meterArea = content.removeFromTop (16 + 14);
    levelCaption.setBounds (meterArea.removeFromTop (16));
    levelMeter.setBounds (meterArea.removeFromTop (14));
}

} // namespace cursomusica
