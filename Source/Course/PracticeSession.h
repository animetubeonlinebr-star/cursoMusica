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
    // exercise does not override the BPM or the alignment target.
    void start (const Exercise& exercise, int moduleTargetBpm, float moduleOnGridTarget);

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
    float getOnGridTarget() const noexcept { return onGridTarget; }

private:
    void recompute();

    const Exercise* current = nullptr;
    TempoGrid grid { 60.0, TempoGrid::Subdivision::quarter };
    int targetBpm = 60;
    float onGridTarget = 0.75f;

    std::vector<TargetNote> target;
    std::vector<double> noteTimes;
    std::vector<int> detectedPitchClasses;
    std::vector<NoteEvent> played;

    PracticeState state;
};

} // namespace cursomusica::course
