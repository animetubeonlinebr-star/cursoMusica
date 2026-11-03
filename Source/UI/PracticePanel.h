#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "Audio/AudioEngine.h"
#include "Course/Module.h"
#include "Course/PracticeSession.h"
#include "Course/QuizSession.h"

#include <vector>

namespace cursomusica
{

// Right pane: the practical exercises of the selected topic, the live
// measurement of the attempt (Nota / Acertos / Grade) and, always below it, the
// application the student runs — a playable exercise or a one-question-at-a-time
// quiz (REQ-008, REQ-009, REQ-015).
class PracticePanel final : public juce::Component
{
public:
    explicit PracticePanel (AudioEngine& engine);
    ~PracticePanel() override;

    // Points the panel at a module and, optionally, filters to one topic
    // (empty lessonId -> every exercise of the module).
    void setModule (const CourseModule* module);
    void setTopicFilter (const juce::String& lessonId);

    // Polled by the owner at UI rate: drains the engine and repaints the state.
    void poll();

    // Reports the gate result of a finished attempt (module number, passed).
    std::function<void (int, bool)> onGateResult;

    // Reports the exercise currently armed, so the centre can demonstrate it.
    std::function<void (const Exercise*)> onExerciseSelected;

    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    void refreshExerciseList();
    void syncMetronomeFromModule();
    void updateButtonStates();
    void updateFeedback();
    void updateApplication();

    const Exercise* selectedExercise() const;
    bool isQuizSelected() const;

    void startSelectedExercise();
    void finishExercise();
    void toggleMetronome();
    void answerQuiz (int optionIndex);

    AudioEngine& audioEngine;
    course::PracticeSession session;
    course::QuizSession quiz;

    const CourseModule* currentModule = nullptr;
    juce::String topicFilter;
    std::vector<int> filteredIndices;
    int selectedExerciseIndex = 0;
    bool metronomeOn = false;

    juce::Label headingLabel;
    juce::Label topicLabel;
    juce::ComboBox exerciseBox;
    juce::TextButton demoButton { juce::String::fromUTF8 ("Demonstrar no centro") };

    // Measurement, always shown.
    juce::Label measurementLabel;
    juce::Label feedbackLabel;

    // Application area: play controls or the quiz.
    juce::TextButton metronomeButton { "Metronome" };
    juce::TextButton startButton { "Start" };
    juce::TextButton finishButton { "Finish" };
    juce::Label bpmLabel;

    juce::Label quizPrompt;
    juce::OwnedArray<juce::TextButton> quizOptions;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PracticePanel)
};

} // namespace cursomusica
