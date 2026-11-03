#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "Audio/AudioEngine.h"
#include "Course/Module.h"
#include "Course/ProgressStore.h"

namespace cursomusica
{

// The course view, laid out as three dependent panes:
//
//   left    the subject menu: modules, each expandable into its topics;
//   centre  what the current selection explains (module, topic or exercise);
//   right   the practical exercises and the live measurement of the attempt.
//
// Selecting a topic on the left loads its explanation in the centre and points
// the right pane at that topic's exercises; the centre also demonstrates the
// exercise that is armed (REQ-003, REQ-008, REQ-009).
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
    class ContentView;
    class SubjectTreeItem;
    class TopicTreeItem;

    // What the central pane is currently explaining.
    struct Selection
    {
        const CourseModule* module = nullptr;
        const LessonBlock* topic = nullptr;   // null -> the module overview
        const Exercise* exercise = nullptr;   // null -> no exercise demonstrated
    };

    void buildTree();
    void showModule (int number);
    void selectTopic (int moduleNumber, int topicIndex);
    void showExercise (const Exercise* exercise);
    void updateContent();

    void timerCallback() override;
    void refreshSubjectTree();
    void setListVisible (bool shouldBeVisible);
    void setPracticeVisible (bool shouldBeVisible);

    AudioEngine& audioEngine;
    course::ProgressStore progressStore;

    Selection selection;

    juce::Label titleLabel;
    juce::Label subtitleLabel;
    juce::Label hintLabel;
    juce::TextButton closeButton { "Close" };
    juce::TextButton listToggle { juce::String::fromUTF8 ("Módulos") };
    juce::TextButton practiceToggle { juce::String::fromUTF8 ("Prática") };

    bool listVisible = true;
    bool practiceVisible = true;

    juce::TreeView subjectTree;
    std::unique_ptr<juce::TreeViewItem> subjectRoot;   // owns every module/topic item

    juce::Viewport contentViewport;
    std::unique_ptr<ContentView> contentView;

    std::unique_ptr<class PracticePanel> practicePanel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModuleComponent)
};

} // namespace cursomusica
