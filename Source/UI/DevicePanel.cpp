#include "UI/DevicePanel.h"

#include "UI/Design/Theme.h"

namespace cursomusica
{

namespace th = cursomusica::theme;

DevicePanel::DevicePanel()
    : Panel ("Audio device")
{
    auto setupCaption = [] (juce::Label& label, const juce::String& text)
    {
        label.setText (text, juce::dontSendNotification);
        label.setFont (th::type::makeFont (th::type::caption));
        label.setColour (juce::Label::textColourId, th::colour::textSecondary);
        label.setJustificationType (juce::Justification::centredLeft);
    };

    setupCaption (deviceCaption, "INPUT");
    setupCaption (sampleRateCaption, "SAMPLE RATE");
    setupCaption (bufferSizeCaption, "BUFFER");

    addAndMakeVisible (deviceCaption);
    addAndMakeVisible (sampleRateCaption);
    addAndMakeVisible (bufferSizeCaption);

    deviceSelector.addItem ("No device selected", 1);
    deviceSelector.setSelectedId (1);

    sampleRateSelector.addItemList ({ "44100 Hz", "48000 Hz", "96000 Hz" }, 1);
    sampleRateSelector.setSelectedId (2);

    bufferSizeSelector.addItemList ({ "64", "128", "256", "512" }, 1);
    bufferSizeSelector.setSelectedId (1);

    addAndMakeVisible (deviceSelector);
    addAndMakeVisible (sampleRateSelector);
    addAndMakeVisible (bufferSizeSelector);

    backendLabel.setText ("backend: --", juce::dontSendNotification);
    backendLabel.setFont (th::type::makeFont (th::type::caption));
    backendLabel.setColour (juce::Label::textColourId, th::colour::accent);
    backendLabel.setJustificationType (juce::Justification::centredLeft);
    addAndMakeVisible (backendLabel);
}

void DevicePanel::resized()
{
    auto content = getContentBounds();

    const int rowHeight = 28;
    const int captionHeight = 16;

    auto deviceRow = content.removeFromTop (captionHeight + rowHeight);
    deviceCaption.setBounds (deviceRow.removeFromTop (captionHeight));
    deviceSelector.setBounds (deviceRow);

    content.removeFromTop (th::spacing::md);

    auto selectors = content.removeFromTop (captionHeight + rowHeight);
    auto rateArea = selectors.removeFromLeft (selectors.getWidth() / 2).withTrimmedRight (th::spacing::sm);
    auto bufferArea = selectors;

    sampleRateCaption.setBounds (rateArea.removeFromTop (captionHeight));
    sampleRateSelector.setBounds (rateArea);

    bufferSizeCaption.setBounds (bufferArea.removeFromTop (captionHeight));
    bufferSizeSelector.setBounds (bufferArea);

    content.removeFromTop (th::spacing::md);
    backendLabel.setBounds (content.removeFromTop (20));
}

} // namespace cursomusica
