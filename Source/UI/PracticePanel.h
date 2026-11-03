#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "Audio/AudioEngine.h"
#include "Course/Module.h"
#include "Course/PracticeSession.h"

namespace cursomusica
{

// Practice strip for the selected module: metronome controls, exercise picker
// and the live gate feedback (REQ-008, REQ-009, REQ-015).
class PracticePanel final : public juce::Component
{
public:
    explicit PracticePanel (AudioEngine& engine);
    ~PracticePanel() override;

    // Points the panel at a module; refreshes the exercise list and the BPM.
    void setModule (const CourseModule* module);

    // Polled by the owner at UI rate: drains the engine and repaints the state.
    void poll();

    // Reports the gate result of a finished attempt (module number, passed).
    std::function<void (int, bool)> onGateResult;

    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    void startSelectedExercise();
    void finishExercise();
    void toggleMetronome();
    void refreshExerciseList();
    void syncMetronomeFromModule();
    void updateButtonStates();
    void updateFeedback();

    const Exercise* selectedExercise() const;

    AudioEngine& audioEngine;
    course::PracticeSession session;

    const CourseModule* currentModule = nullptr;
    int selectedExerciseIndex = 0;
    bool metronomeOn = false;

    juce::Label headingLabel;
    juce::Label bpmLabel;
    juce::TextButton metronomeButton { "Metronome" };
    juce::ComboBox exerciseBox;
    juce::TextButton startButton { "Start" };
    juce::TextButton finishButton { "Finish" };

    juce::Label feedbackLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PracticePanel)
};

} // namespace cursomusica
