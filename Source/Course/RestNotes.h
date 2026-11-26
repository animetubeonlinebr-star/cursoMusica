#pragma once

#include <juce_core/juce_core.h>

#include <vector>

#include "Course/ExerciseEvaluator.h"

namespace cursomusica::course
{

// Rest-note and tension classification (REQ-011, REQ-012).
//
// Pure, audio- and UI-free: given the harmonic context in force and the notes
// the student played, it decides which notes rest, which are the solicited
// tensions and which are errors. The exact criterion is fixed in docs/MUSIC.md
// ("Notas de repouso × notas de tensão"):
//
//   - a chord tone is a rest;
//   - a scale tone of the centre in force is a rest (stable in context);
//   - a tension the improvisation state asks for is accepted;
//   - any other note is an error, unless it is a chromatic passing tone that
//     resolves on the next (strong) note.
//
// Deterministic and headless-testable (tests/TestMain.cpp).

enum class NoteRole
{
    rest,      // chord tone or stable scale tone
    tension,   // a tension the exercise solicited
    passing,   // chromatic approach that resolves on the next note (accepted)
    error      // tension outside the context, not solicited
};

// The harmonic context an improvisation exercise runs in.
struct RestNoteSpec
{
    std::vector<int> chordPitchClasses;   // pitch classes of the chord in force
    std::vector<int> scalePitchClasses;   // pitch classes of the centre's scale
    std::vector<int> solicitedTensions;   // tensions the exercise explicitly asks for
    bool allowPassing = true;             // accept chromatic passing tones

    bool empty() const noexcept
    {
        return chordPitchClasses.empty() && scalePitchClasses.empty();
    }
};

// Classifies one pitch class against the context (no look-ahead).
NoteRole classifyNote (int pitchClass, const RestNoteSpec& spec);

struct ImprovisationResult
{
    int total = 0;
    int rest = 0;
    int tension = 0;
    int passing = 0;
    int errors = 0;
    double accuracy = 0.0;   // (rest + tension + passing) / total
    bool passed = false;
};

// Scores an improvisation: every note is classified, and a note outside the
// context is only forgiven when it is a chromatic passing tone that resolves on
// the next accepted note. Accuracy = accepted / total, gated at `passThreshold`.
ImprovisationResult evaluateImprovisation (const std::vector<NoteEvent>& played,
                                           const RestNoteSpec& spec,
                                           double passThreshold = 0.90);

// One stretch of a form under improvisation: `bars` bars of one context. A form
// with more than one chord is a sequence of segments, and each played note is
// judged against the segment in force when it sounded (docs/MUSIC.md,
// "Programa de estudo de improvisação": no exercise runs on a bare scale, and
// no student is failed for playing the chord that is actually sounding).
struct HarmonicSegment
{
    int bars = 1;
    RestNoteSpec context;
};

// Scores an improvisation over a declared form. Each note is classified against
// the chord in force when it sounded, so a phrase that follows the changes is
// accepted and a phrase that ignores them is not. `bpm` and `beatsPerBar` map the
// note times to bars; the form loops, exactly like the backing bed does.
ImprovisationResult evaluateImprovisationOverTimeline (
    const std::vector<NoteEvent>& played,
    const std::vector<HarmonicSegment>& timeline,
    double bpm,
    int beatsPerBar = 4,
    double passThreshold = 0.90);

} // namespace cursomusica::course
