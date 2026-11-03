#include <juce_core/juce_core.h>

#include <cmath>
#include <iostream>
#include <vector>

#include "Course/ExerciseEvaluator.h"
#include "Course/NoteMath.h"
#include "Course/PracticeSession.h"
#include "Course/ProgressionRule.h"
#include "Course/TempoGrid.h"

// Minimal dependency-free test runner for the pure course logic (QA).
// Runs on the build machine with no audio device, so it is CI-friendly.

namespace
{
    int failures = 0;
    int checks = 0;

    void check (bool condition, const juce::String& what)
    {
        ++checks;
        if (! condition)
        {
            ++failures;
            std::cout << "  FAIL: " << what << "\n";
        }
    }

    void checkClose (double actual, double expected, double tolerance, const juce::String& what)
    {
        check (std::abs (actual - expected) <= tolerance,
               what + " (expected " + juce::String (expected, 3)
                    + ", got " + juce::String (actual, 3) + ")");
    }

    void testNoteMath()
    {
        std::cout << "NoteMath\n";
        using namespace cursomusica::music;

        checkClose (midiToFrequency (69.0), 440.0, 0.01, "A4 = 440 Hz");
        checkClose (midiToFrequency (69.0, 432.0), 432.0, 0.01, "A4 respects reference pitch");
        checkClose (midiToFrequency (60.0), 261.6256, 0.01, "C4 frequency");

        const auto a4 = analyseFrequency (440.0);
        check (a4.valid && a4.name == "A" && a4.octave == 4, "440 Hz is A4");
        checkClose (a4.cents, 0.0, 0.5, "A4 has no cents deviation");

        const auto sharp = analyseFrequency (440.0 * std::pow (2.0, 10.0 / 1200.0));
        checkClose (sharp.cents, 10.0, 1.0, "detunes by ~10 cents");

        check (analyseFrequency (0.0).valid == false, "silence is not a note");

        check (noteNameToMidi ("C4") == 60, "C4 -> 60");
        check (noteNameToMidi ("C#4") == 61, "C#4 -> 61");
        check (noteNameToMidi ("Db4") == 61, "Db4 -> 61");
        check (noteNameToMidi ("A4") == 69, "A4 -> 69");
        check (noteNameToMidi ("E2") == 40, "E2 -> 40");
        check (noteNameToMidi ("H4") == -1, "invalid letter rejected");

        check (midiToNoteName (61) == "C#4", "61 -> C#4");
    }

    void testEvaluator()
    {
        std::cout << "ExerciseEvaluator\n";
        using namespace cursomusica::course;

        const std::vector<TargetNote> scale { { 60, "C4" }, { 62, "D4" }, { 64, "E4" } };

        const std::vector<NoteEvent> perfect { { 0.0, 60, 2.0f }, { 0.5, 62, -3.0f }, { 1.0, 64, 0.0f } };
        const auto perfectResult = evaluator::evaluateSequence (scale, perfect);
        check (perfectResult.matched == 3 && perfectResult.passed, "perfect run passes");

        const std::vector<NoteEvent> sloppy { { 0.0, 60, 60.0f }, { 0.5, 62, 0.0f }, { 1.0, 64, 0.0f } };
        check (evaluator::evaluateSequence (scale, sloppy).matched == 2, "out-of-tune note is not counted");

        const std::vector<NoteEvent> wrongNote { { 0.0, 61, 0.0f }, { 0.5, 60, 0.0f }, { 1.0, 62, 0.0f }, { 1.5, 64, 0.0f } };
        check (evaluator::evaluateSequence (scale, wrongNote).matched == 3, "wrong note does not block the sequence");

        checkClose (evaluator::accuracyOf (9, 10), 0.9, 1e-9, "9/10 = 0.9");
        check (evaluator::gatePassed (0.90), "90% passes the gate");
        check (! evaluator::gatePassed (0.899), "89.9% fails the gate");
        checkClose (evaluator::accuracyOf (1, 1), 1.0, 1e-9, "1/1 is 100% (guard lives in the PO rule)");

        checkClose (evaluator::chordCoverage ({ 0, 4, 7 }, { 0, 4, 7, 2 }), 1.0, 1e-9, "full chord covered");
        checkClose (evaluator::chordCoverage ({ 0, 4, 7 }, { 0, 4 }), 2.0 / 3.0, 1e-6, "two of three notes");
        check (! evaluator::chordPassed ({ 0, 4, 7 }, { 0, 4 }), "2/3 chord fails the gate");
    }

    void testTempoGrid()
    {
        std::cout << "TempoGrid\n";
        using namespace cursomusica::course;

        const TempoGrid grid (60.0, TempoGrid::Subdivision::quarter);
        checkClose (grid.getTickInterval(), 1.0, 1e-9, "60 BPM quarter = 1 s");
        check (grid.isOnGrid (0.0), "beat 0 is on the grid");
        check (grid.isOnGrid (2.0), "beat 2 is on the grid");
        check (! grid.isOnGrid (0.5), "half a beat is off the grid");

        const TempoGrid eighth (120.0, TempoGrid::Subdivision::eighth);
        checkClose (eighth.getTickInterval(), 0.25, 1e-9, "120 BPM eighth = 0.25 s");

        const std::vector<double> onBeat { 0.0, 1.0, 2.0, 3.0 };
        checkClose (TempoGrid::onGridRatio (onBeat, grid), 1.0, 1e-9, "all notes on the grid");

        const std::vector<double> halfOff { 0.0, 0.5, 1.0, 1.5 };
        checkClose (TempoGrid::onGridRatio (halfOff, grid), 0.5, 1e-9, "half the notes on the grid");

        const std::vector<double> candidates { 60.0, 80.0, 100.0 };

        // Notes exactly on the 100 BPM grid: the top candidate is reached and
        // the lower ones fail because their grid no longer lines up.
        const std::vector<double> onFastGrid { 0.0, 0.6, 1.2, 1.8 };
        const double achieved = TempoGrid::achievedBpm (onFastGrid, TempoGrid::Subdivision::quarter, candidates, 0.9);
        checkClose (achieved, 100.0, 1e-9, "notes on the 100 BPM grid yield 100 BPM");

        // A slow, steady player only ever satisfies the 60 BPM grid.
        const std::vector<double> onSlowGrid { 0.0, 1.0, 2.0, 3.0 };
        checkClose (TempoGrid::achievedBpm (onSlowGrid, TempoGrid::Subdivision::quarter, candidates, 0.9),
                    60.0, 1e-9, "steady 60 BPM notes yield 60 BPM, not 100");

        const double none = TempoGrid::achievedBpm ({ 0.5, 1.5 }, TempoGrid::Subdivision::quarter, candidates, 0.9);
        checkClose (none, 0.0, 1e-9, "notes off the grid reach no BPM");
    }

    void testPracticeSession()
    {
        std::cout << "PracticeSession\n";
        using namespace cursomusica::course;

        // A note-sequence exercise: E2 then A2, at 60 BPM.
        cursomusica::Exercise sequence;
        sequence.id = "EX-1.2";
        sequence.targets = { { 40, "E2" }, { 45, "A2" } };

        PracticeSession session;
        session.start (sequence, 60, 0.75f);
        check (session.isRunning(), "session starts running");
        check (session.getTargetBpm() == 60, "inherits the module BPM");

        session.consume ({ { 0.0, 40, 0.0f }, { 1.0, 45, 0.0f } });
        session.finish();

        const auto& state = session.getState();
        check (state.matched == 2, "both notes matched");
        checkClose (state.accuracy, 1.0, 1e-9, "100% accuracy");
        checkClose (state.onGridRatio, 1.0, 1e-9, "both notes on the grid");
        check (state.passed, "a clean run passes both gates");

        // A chord progression (the gate): C then G, each covered in turn.
        cursomusica::Exercise gate;
        gate.id = "GATE-1";
        gate.chordProgression = { { 0, 4, 7 }, { 7, 11, 2 } };

        PracticeSession gateSession;
        gateSession.start (gate, 60, 0.75f);
        gateSession.consume ({ { 0.0, 60, 0.0f }, { 0.1, 64, 0.0f }, { 0.2, 67, 0.0f },
                               { 1.0, 67, 0.0f }, { 1.1, 71, 0.0f }, { 1.2, 62, 0.0f } });
        gateSession.finish();

        const auto& gateState = gateSession.getState();
        check (gateState.matched == 2, "both chords recognised in order");
        check (gateState.passed, "gate progression passes at 60 BPM");

        // Out-of-tune playing must fail the accuracy gate.
        PracticeSession sloppy;
        sloppy.start (sequence, 60, 0.75f);
        sloppy.consume ({ { 0.0, 40, 80.0f }, { 1.0, 45, 0.0f } });
        sloppy.finish();
        check (! sloppy.getState().accuracyPassed, "detuned note fails the accuracy gate");
    }
}

void testProgression()
{
    using namespace cursomusica::course::progress;

    check (isUnlocked (1, 0), "module 1 is always unlocked");
    check (! isUnlocked (2, 0), "module 2 is locked until module 1 is passed");
    check (isUnlocked (2, 1), "passing module 1 unlocks module 2");
    check (! isUnlocked (3, 1), "module 3 stays locked after only module 1");
    check (isUnlocked (3, 2), "passing module 2 unlocks module 3");
    check (highestUnlocked (0) == 1, "nothing passed unlocks only module 1");
    check (highestUnlocked (4) == 5, "passing up to module 4 unlocks module 5");
}

int main()
{
    testNoteMath();
    testEvaluator();
    testTempoGrid();
    testPracticeSession();
    testProgression();

    std::cout << "\n" << (checks - failures) << "/" << checks << " checks passed\n";
    if (failures > 0)
    {
        std::cout << failures << " FAILED\n";
        return 1;
    }

    std::cout << "ALL TESTS PASSED\n";
    return 0;
}
