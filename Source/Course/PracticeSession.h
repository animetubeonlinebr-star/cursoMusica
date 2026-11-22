#pragma once

#include <juce_core/juce_core.h>

#include <vector>

#include "Course/ExerciseEvaluator.h"
#include "Course/Module.h"
#include "Course/TempoGrid.h"

namespace cursomusica::course
{

// Live state of one practice attempt. Updated on the message thread from the
// notes the engine captured; the UI polls it. No audio, no UI: pure logic.
struct PracticeState
{
    bool running = false;
    bool finished = false;
    int notesHeard = 0;
    int matched = 0;
    int targetCount = 0;
    double accuracy = 0.0;
    double onGridRatio = 0.0;
    bool accuracyPassed = false;
    bool gridPassed = false;
    bool tempoPassed = false;

    // Tempo of the attempt: `practiceBpm` is the metronome tempo the student
    // chose, `targetBpm` is the module's goal. The attempt only counts when the
    // student practices at or above the goal (REQ-015, client 2026-11-19).
    int practiceBpm = 0;
    int targetBpm = 0;
    bool tempoGated = false;

    bool passed = false;
    juce::String lastNote;   // last note heard, for live feedback
    juce::String message;    // human-readable verdict
};

// Drives one exercise: it consumes detected notes, scores them against the
// exercise target and applies the gates (REQ-009 accuracy, REQ-015 grid).
class PracticeSession
{
public:
    // Starts a fresh attempt for `exercise`, inheriting module defaults when the
    // exercise does not override the BPM or the alignment target. `chosenBpm`
    // is the metronome tempo the student set; 0 uses the exercise's goal.
    // `moduleUsesTempo` false disables the tempo gate (module 1).
    void start (const Exercise& exercise, int moduleTargetBpm, float moduleOnGridTarget,
                int chosenBpm = 0, bool moduleUsesTempo = true);

    void stop();
    bool isRunning() const noexcept { return state.running; }

    // Feeds the notes captured since the last drain. Called from the message
    // thread on a timer.
    void consume (const std::vector<NoteEvent>& events);

    // Finishes the attempt and computes the verdict.
    void finish();

    const PracticeState& getState() const noexcept { return state; }

    const TempoGrid& getGrid() const noexcept { return grid; }
    int getTargetBpm() const noexcept { return targetBpm; }
    int getPracticeBpm() const noexcept { return practiceBpm; }
    float getOnGridTarget() const noexcept { return onGridTarget; }

private:
    void recompute();

    const Exercise* current = nullptr;
    TempoGrid grid { 60.0, TempoGrid::Subdivision::quarter };
    int targetBpm = 60;
    int practiceBpm = 60;
    float onGridTarget = 0.75f;

    std::vector<TargetNote> target;
    std::vector<double> noteTimes;
    std::vector<int> detectedPitchClasses;
    std::vector<NoteEvent> played;
    evaluator::IntervalSpec intervalSpec;
    bool gridGated = true;
    bool tempoGated = true;

    PracticeState state;
};

} // namespace cursomusica::course
