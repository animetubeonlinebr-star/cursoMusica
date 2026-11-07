#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include <unordered_map>

#include "Audio/AudioEngine.h"
#include "Course/Module.h"
#include "Course/ProgressStore.h"

namespace cursomusica
{

// The course view, laid out as three dependent panes:
//
//   left    the subject menu: modules, each expandable into its topics;
//   centre  what the current selection explains (module, topic or exercise) —
//           for a quiz it is the exercise itself (question + clickable options);
//   right   the practical controls: exercise selector, play row, scoreboard and
//           the guidance box of the attempt.
//
// Opening a module never loads a topic by itself (REQ-019): the centre shows
// only the module's own context until the student clicks a topic. Returning to
// a module keeps the topic last read in it; opening another module clears the
// centre (REQ-020). The centre demonstrates the armed exercise and, for a quiz,
// runs it there (REQ-021); the right pane keeps only the controls.
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

    // Mirrors the practice pane's quiz state into the centre, which renders the
    // question and the options while the pane keeps the controls (REQ-021).
    void syncQuizToCentre();

    // Remembers, per module, the topic the student last read there (REQ-020).
    void rememberTopic (int moduleNumber, int topicIndex);
    int recalledTopic (int moduleNumber) const;
    void restoreTopicInTree (int moduleNumber, int topicIndex);

    void timerCallback() override;
    void refreshSubjectTree();
    void setListVisible (bool shouldBeVisible);
    void setPracticeVisible (bool shouldBeVisible);

    AudioEngine& audioEngine;
    course::ProgressStore progressStore;

    Selection selection;

    // module number -> topic index last read in it (REQ-020).
    std::unordered_map<int, int> lastTopicPerModule;

    // Set while the component drives the tree itself (restoring a remembered
    // topic), so the tree callbacks do not re-enter the selection logic.
    bool suppressTreeCallbacks = false;

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
