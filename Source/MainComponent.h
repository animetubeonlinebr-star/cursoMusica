#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "UI/Design/LookAndFeel.h"
#include "UI/Design/Panel.h"
#include "UI/DevicePanel.h"
#include "UI/SettingsComponent.h"
#include "UI/TunerComponent.h"
#include "UI/TunerDisplay.h"
#include "UI/TransportPanel.h"
#include "Audio/AudioEngine.h"
#include "Audio/PluginHost.h"
#include "Audio/TuningSettings.h"

namespace cursomusica
{

class MainComponent final : public juce::Component,
                            private juce::Timer
{
public:
    MainComponent();
    ~MainComponent() override;

    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    void timerCallback() override;
    void showSettings();
    void hideSettings();
    void showTuner();
    void hideTuner();

    CursoLookAndFeel lookAndFeel;

    AudioEngine audioEngine;
    PluginHost pluginHost;
    TuningSettings tuningSettings;

    juce::Label titleLabel;
    juce::Label subtitleLabel;
    juce::TextButton tunerButton { "Tuner" };
    juce::TextButton settingsButton { "Settings" };

    TunerDisplay tunerDisplay;
    DevicePanel devicePanel;
    TransportPanel transportPanel;
    Panel studyReferencePanel { "Study material" };
    juce::Label referenceLabel;

    std::unique_ptr<SettingsComponent> settings;
    std::unique_ptr<TunerComponent> tuner;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

} // namespace cursomusica
