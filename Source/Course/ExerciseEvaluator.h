#pragma once

#include <juce_core/juce_core.h>

#include <vector>

namespace cursomusica::course
{

// A note the student actually played, with the moment it was detected.
struct NoteEvent
{
    double timeSeconds = 0.0;
    int midi = 0;
    float cents = 0.0f;
};

// A note the exercise expects, with a human label ("E2", "C").
struct TargetNote
{
    int midi = 0;
    juce::String label;
};

// Result of comparing a played sequence against a target sequence.
struct SequenceResult
{
    int matched = 0;
    int total = 0;
    double accuracy = 0.0;
    bool passed = false;
};

// Pure evaluation logic (REQ-009). No audio, no UI: it takes what was detected
// and decides whether the exercise was met. Deterministic and testable.
namespace evaluator
{
    // Matches the played notes against the target sequence, in order, allowing
    // wrong notes in between (they do not block the rest of the sequence).
    // A note counts when it is within centsTolerance of the target.
    SequenceResult evaluateSequence (const std::vector<TargetNote>& target,
                                     const std::vector<NoteEvent>& played,
                                     float centsTolerance = 25.0f,
                                     double passThreshold = 0.90);

    // Fraction of the target chord's pitch classes that were detected.
    // Used for strummed chords, where the detector reports the notes in turn.
    double chordCoverage (const std::vector<int>& targetPitchClasses,
                          const std::vector<int>& detectedPitchClasses);

    // True when the chord was covered at or above the threshold (REQ-009).
    bool chordPassed (const std::vector<int>& targetPitchClasses,
                      const std::vector<int>& detectedPitchClasses,
                      double threshold = 0.90);

    // Accuracy over a set of exercises, used for the module gate (REQ-009).
    double accuracyOf (int hits, int attempts);

    // The gate of REQ-009: >= 90% accuracy.
    bool gatePassed (double accuracy, double threshold = 0.90);
}

} // namespace cursomusica::course
