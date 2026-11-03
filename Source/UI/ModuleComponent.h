#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "Audio/AudioEngine.h"
#include "Course/Module.h"
#include "Course/ProgressStore.h"

namespace cursomusica
{

// The course view: a list of modules on the left, the selected module on the
// right. The explanation is presented before the exercises (REQ-003).
class ModuleComponent final : public juce::Component,
                              private juce::Timer
{
public:
    explicit ModuleComponent (AudioEngine& engine);
    ~ModuleComponent() override;

    void paint (juce::Graphics& g) override;
    void resized() override;

    std::function<void()> onCloseRequested;

private:
    class ModuleListModel;
    class ModuleContentView;

    void showModule (int number);
    void timerCallback() override;
    void refreshModuleList();

    AudioEngine& audioEngine;
    course::ProgressStore progressStore;

    juce::Label titleLabel;
    juce::Label subtitleLabel;
    juce::Label hintLabel;
    juce::TextButton closeButton { "Close" };

    juce::ListBox moduleList;
    std::unique_ptr<ModuleListModel> listModel;

    juce::Viewport contentViewport;
    std::unique_ptr<ModuleContentView> contentView;

    std::unique_ptr<class PracticePanel> practicePanel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModuleComponent)
};

} // namespace cursomusica
