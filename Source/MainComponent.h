#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "UI/Design/LookAndFeel.h"
#include "UI/Design/Panel.h"
#include "UI/DevicePanel.h"
#include "UI/SettingsComponent.h"
#include "UI/TunerDisplay.h"
#include "UI/TransportPanel.h"
#include "Audio/AudioEngine.h"
#include "Audio/PluginHost.h"

namespace cursomusica
{

class MainComponent final : public juce::Component
{
public:
    MainComponent();
    ~MainComponent() override;

    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    void showSettings();
    void hideSettings();

    CursoLookAndFeel lookAndFeel;

    AudioEngine audioEngine;
    PluginHost pluginHost;

    juce::Label titleLabel;
    juce::Label subtitleLabel;
    juce::TextButton settingsButton { "Settings" };

    TunerDisplay tunerDisplay;
    DevicePanel devicePanel;
    TransportPanel transportPanel;
    Panel studyReferencePanel { "Study material" };
    juce::Label referenceLabel;

    std::unique_ptr<SettingsComponent> settings;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

} // namespace cursomusica
