#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "Audio/AudioEngine.h"
#include "Audio/TuningSettings.h"
#include "UI/Design/Panel.h"
#include "UI/TunerDisplay.h"

namespace cursomusica
{

// The tuner window: a standalone tool, not part of any module.
//
// Opened from the header at any time. Shows the live note/cents readout and
// lets the student choose the reference pitch (A4). The pitch is persisted by
// TuningSettings, so it is the same every session.
class TunerComponent final : public juce::Component,
                             private juce::Timer
{
public:
    explicit TunerComponent (AudioEngine& engine, TuningSettings& tuning);
    ~TunerComponent() override;

    void paint (juce::Graphics& g) override;
    void resized() override;

    std::function<void()> onCloseRequested;

private:
    void timerCallback() override;
    void applyReferenceFromEditor();
    void refreshPitchPresets();

    AudioEngine& audioEngine;
    TuningSettings& tuningSettings;

    juce::Label titleLabel;
    juce::Label subtitleLabel;
    juce::TextButton closeButton { "Close" };

    Panel tunerPanel { "Tuner" };
    TunerDisplay tunerDisplay;

    Panel referencePanel { "Reference pitch" };
    juce::Label referenceCaption;
    juce::Slider referenceSlider { juce::Slider::LinearHorizontal, juce::Slider::TextBoxRight };
    juce::ComboBox presetSelector;
    juce::TextButton resetButton { "Reset to 440" };
    juce::Label currentReferenceLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TunerComponent)
};

} // namespace cursomusica
