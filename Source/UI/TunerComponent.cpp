#include "UI/TunerComponent.h"

#include "UI/Design/Theme.h"

namespace cursomusica
{

namespace th = cursomusica::theme;

namespace
{
    // Common reference pitches, as a quick way to pick a standard other than 440.
    struct Preset { const char* name; float hz; };
    const Preset pitchPresets[] {
        { "A = 415 Hz (barroco)", 415.0f },
        { "A = 432 Hz (Verdi)",   432.0f },
        { "A = 435 Hz",           435.0f },
        { "A = 438 Hz",           438.0f },
        { "A = 440 Hz (padrão)",  440.0f },
        { "A = 442 Hz",           442.0f },
        { "A = 443 Hz",           443.0f },
        { "A = 444 Hz",           444.0f },
    };
}

TunerComponent::TunerComponent (AudioEngine& engine, TuningSettings& tuning)
    : audioEngine (engine), tuningSettings (tuning)
{
    titleLabel.setText ("Tuner", juce::dontSendNotification);
    titleLabel.setFont (th::type::makeFont (th::type::title, true));
    titleLabel.setColour (juce::Label::textColourId, th::colour::textPrimary);
    addAndMakeVisible (titleLabel);

    subtitleLabel.setText ("Ferramenta de apoio — disponível a qualquer momento, fora dos modulos",
                           juce::dontSendNotification);
    subtitleLabel.setFont (th::type::makeFont (th::type::body));
    subtitleLabel.setColour (juce::Label::textColourId, th::colour::textSecondary);
    addAndMakeVisible (subtitleLabel);

    closeButton.onClick = [this] { if (onCloseRequested != nullptr) onCloseRequested(); };
    addAndMakeVisible (closeButton);

    tunerPanel.addAndMakeVisible (tunerDisplay);
    addAndMakeVisible (tunerPanel);

    referenceCaption.setText ("Reference pitch (A4)", juce::dontSendNotification);
    referenceCaption.setFont (th::type::makeFont (th::type::body));
    referenceCaption.setColour (juce::Label::textColourId, th::colour::textSecondary);
    referencePanel.addAndMakeVisible (referenceCaption);

    referenceSlider.setRange (TuningSettings::minReferenceHz, TuningSettings::maxReferenceHz, 0.1);
    referenceSlider.setTextValueSuffix (" Hz");
    referenceSlider.setValue (tuningSettings.getReferenceHz(), juce::dontSendNotification);
    referenceSlider.onValueChange = [this] { applyReferenceFromEditor(); };
    referencePanel.addAndMakeVisible (referenceSlider);

    for (int i = 0; i < (int) juce::numElementsInArray (pitchPresets); ++i)
        presetSelector.addItem (pitchPresets[i].name, i + 1);
    presetSelector.onChange = [this]
    {
        const int index = presetSelector.getSelectedId() - 1;
        if (index >= 0 && index < (int) juce::numElementsInArray (pitchPresets))
            referenceSlider.setValue (pitchPresets[index].hz, juce::sendNotificationSync);
    };
    referencePanel.addAndMakeVisible (presetSelector);

    resetButton.onClick = [this]
    {
        referenceSlider.setValue (TuningSettings::defaultReferenceHz, juce::sendNotificationSync);
    };
    referencePanel.addAndMakeVisible (resetButton);

    currentReferenceLabel.setFont (th::type::makeFont (th::type::caption, true));
    currentReferenceLabel.setColour (juce::Label::textColourId, th::colour::accentAlt);
    referencePanel.addAndMakeVisible (currentReferenceLabel);

    refreshPitchPresets();
    tunerDisplay.setReferenceHz (tuningSettings.getReferenceHz());

    startTimerHz (30);
}

TunerComponent::~TunerComponent()
{
    stopTimer();
}

void TunerComponent::timerCallback()
{
    tunerDisplay.setFrequencyHz (audioEngine.getDetectedFrequencyHz());
}

void TunerComponent::applyReferenceFromEditor()
{
    tuningSettings.setReferenceHz ((float) referenceSlider.getValue());
    tunerDisplay.setReferenceHz (tuningSettings.getReferenceHz());
    refreshPitchPresets();
}

void TunerComponent::refreshPitchPresets()
{
    const float current = tuningSettings.getReferenceHz();

    // Highlight the matching preset, or clear the selection for a custom value.
    presetSelector.setSelectedId (0, juce::dontSendNotification);
    for (int i = 0; i < (int) juce::numElementsInArray (pitchPresets); ++i)
        if (std::abs (pitchPresets[i].hz - current) < 0.05f)
            presetSelector.setSelectedId (i + 1, juce::dontSendNotification);

    currentReferenceLabel.setText ("Atual: A = " + juce::String (current, 1) + " Hz",
                                   juce::dontSendNotification);
}

void TunerComponent::paint (juce::Graphics& g)
{
    g.fillAll (th::colour::background);
}

void TunerComponent::resized()
{
    auto bounds = getLocalBounds().reduced (th::spacing::lg);

    auto header = bounds.removeFromTop (64);
    closeButton.setBounds (header.removeFromRight (110).withSizeKeepingCentre (110, 34));
    header.removeFromRight (th::spacing::md);
    titleLabel.setBounds (header.removeFromTop (32));
    subtitleLabel.setBounds (header.removeFromTop (22));

    bounds.removeFromTop (th::spacing::md);

    auto referenceArea = bounds.removeFromBottom (150);
    tunerPanel.setBounds (bounds);
    tunerDisplay.setBounds (tunerPanel.getContentBounds());

    referencePanel.setBounds (referenceArea);
    auto reference = referencePanel.getContentBounds().reduced (th::spacing::sm);

    auto topRow = reference.removeFromTop (28);
    referenceCaption.setBounds (topRow.removeFromLeft (180));
    currentReferenceLabel.setBounds (topRow);

    reference.removeFromTop (th::spacing::sm);
    auto sliderRow = reference.removeFromTop (30);
    resetButton.setBounds (sliderRow.removeFromRight (130));
    sliderRow.removeFromRight (th::spacing::sm);
    presetSelector.setBounds (sliderRow.removeFromRight (180));
    sliderRow.removeFromRight (th::spacing::sm);
    referenceSlider.setBounds (sliderRow);
}

} // namespace cursomusica
