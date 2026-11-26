#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "Audio/AudioEngine.h"
#include "Course/Module.h"
#include "Course/PracticeSession.h"
#include "Course/Transposition.h"
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

    // Sets the module and the topic filter together. The pane filters the
    // exercises of the module it currently holds, so applying a lesson filter
    // without pointing it at the right module first lists the wrong module's
    // exercises (empty when the lesson id does not occur there). Use this from
    // the tree, where both values come from the clicked topic.
    void setModuleAndTopic (const CourseModule* module, const juce::String& lessonId);

    // Polled by the owner at UI rate: drains the engine and repaints the state.
    void poll();

    // Reports the gate result of a finished attempt (module number, passed).
    std::function<void (int, bool)> onGateResult;

    // Reports the accuracy (0..100) of a finished exercise attempt, so the
    // owner can persist it and show it again next time (client request).
    std::function<void (const juce::String&, double)> onExerciseResult;

    // Last stored accuracy (0..100) of an exercise, or -1 when never attempted.
    // Read when the student arms an exercise, to show the previous result.
    std::function<int (const juce::String&)> onQueryExerciseAccuracy;

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
    void showPreviousResult();

    const Exercise* selectedExercise() const;
    bool isQuizSelected() const;

    void startSelectedExercise();
    void finishExercise();
    void toggleMetronome();
    void toggleBacking();
    void syncBackingFromExercise();

    // Key of the bed (client, 2026-11-25): the student may move the material to
    // any of the twelve keys. `chosenKeyPc` is the pitch class the student
    // picked; -1 follows the exercise's own key.
    void setChosenKey (int pitchClass);
    void updateKeyBox();
    int keyOffsetSemitones() const;
    void publishBackingChords();
    void applyChosenBpm();
    int exerciseGoalBpm() const;

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
    bool backingOn = false;       // backing track under the exercise (client, 2026-11-18)

    // Harmony of the armed exercise in its own key, kept untransposed so the
    // key selector can move it again without compounding offsets.
    std::vector<course::BackingChord> baseChords;
    int baseTonicPc = -1;
    int chosenKeyPc = -1;         // -1 -> follow the exercise's key

    // Last stored accuracy (percent) of the armed exercise, -1 when never
    // attempted. Shown until a new attempt produces a fresh verdict.
    int previousAccuracy = -1;

    // Guards against reporting the same finished attempt more than once (the
    // verdict is reached from both poll() and finish()).
    bool attemptReported = false;

    juce::Label headingLabel;

    // "Todos os tópicos do módulo": clears the topic filter so the pane lists
    // every exercise of the module again.
    juce::HyperlinkButton topicLink { juce::String::fromUTF8 ("Todos os tópicos do módulo"), juce::URL() };

    juce::Label topicLabel;
    juce::ComboBox exerciseBox;

    // Metronome tempo of the attempt (client 2026-11-19): the student may
    // practice slower than the module goal, but only an attempt at or above the
    // goal concludes the exercise (REQ-015).
    juce::Label bpmCaption;
    juce::Slider bpmSlider;
    int chosenBpm = 0;            // 0 -> follows the exercise/module goal

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
    juce::TextButton backingButton { "Base" };

    // Key of the bed: "Tom" + the twelve keys. Moving the key moves the exercise
    // with it, so the student practises the same material in every key.
    juce::Label keyCaption;
    juce::ComboBox keyBox;
    juce::TextButton startButton { "Start" };
    juce::TextButton finishButton { "Finish" };
    juce::Label bpmLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PracticePanel)
};

} // namespace cursomusica
