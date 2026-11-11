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

    // The centre demonstrates the running exercise: it reads the quiz state and
    // sends the chosen option back here, so the right pane keeps only the
    // controls and the scoreboard (REQ-021).
    const course::QuizState& getQuizState() const;
    void answerQuizOption (int optionIndex);

    // Fired whenever the quiz advances, so the centre can redraw the question.
    std::function<void()> onQuizChanged;

    // Restarts the quiz from the first question (driven from the centre pane).
    void restartQuiz();

    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    void refreshExerciseList();
    void refreshExerciseRow();
    void syncMetronomeFromModule();
    void updateButtonStates();
    void updateFeedback();
    void updateApplication();

    const Exercise* selectedExercise() const;
    bool isQuizSelected() const;

    void startSelectedExercise();
    void finishExercise();
    void toggleMetronome();

    AudioEngine& audioEngine;
    course::PracticeSession session;
    course::QuizSession quiz;

    const CourseModule* currentModule = nullptr;
    juce::String topicFilter;
    bool topicChosen = false;     // the pane only lists exercises after a topic is picked
    bool exerciseArmed = false;   // the play row appears only after the student picks one
    std::vector<int> filteredIndices;
    int selectedExerciseIndex = 0;
    bool metronomeOn = false;

    juce::Label headingLabel;

    // "Todos os tópicos do módulo": clears the topic filter so the pane lists
    // every exercise of the module again.
    juce::HyperlinkButton topicLink { juce::String::fromUTF8 ("Todos os tópicos do módulo"), juce::URL() };

    juce::Label topicLabel;
    juce::ComboBox exerciseBox;

    // Presents the armed exercise as a playable row (play glyph + id/title),
    // matching the mock-up; clicking it asks the centre to demonstrate the
    // exercise (REQ-021). The exercise itself still runs in this pane.
    class ExerciseRowButton final : public juce::Button
    {
    public:
        ExerciseRowButton() : juce::Button ("Demonstrar no centro") {}
        void paintButton (juce::Graphics&, bool highlighted, bool down) override;
        void setExerciseText (const juce::String& newText);

    private:
        juce::String exerciseText;
    };

    ExerciseRowButton demoButton;

    // Scoreboard (Acertos x/y · aproveitamento z%), always shown.
    juce::Label measurementLabel;

    // Guidance box: what the student must do in the armed exercise.
    juce::Label guidanceLabel;

    // Playable-exercise controls.
    juce::TextButton metronomeButton { "Metronome" };
    juce::TextButton startButton { "Start" };
    juce::TextButton finishButton { "Finish" };
    juce::Label bpmLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PracticePanel)
};

} // namespace cursomusica
