#pragma once

#include <juce_core/juce_core.h>

#include <vector>

#include "Course/Module.h"

namespace cursomusica::course
{

// Builds the backing-track progression of an exercise (client request,
// 2026-11-18: "adicionar áudio de base para acompanhar os exercícios").
//
// The exercise already declares the harmony it runs over, in one of two forms:
//   - `chordProgression` — the ordered chords (the gate and the vamp exercises);
//   - `restNotes.chordPitchClasses` — the chord in force for improvisation.
// A playable exercise with neither (a scale or lick drill) still needs a bed to
// play over, so it falls back to the module's gate vamp — the harmonic centre the
// module teaches — and, when the module has no gate, to A minor.
//
// Pure and UI-free so the choice is testable (tests/TestMain.cpp).
struct BackingChord
{
    std::vector<int> pitchClasses;
    int bassMidi = 45; // A2
};

// The chords to play under `exercise`, in bar order. Never empty.
std::vector<BackingChord> backingProgressionFor (const CourseModule& module,
                                                const Exercise& exercise);

} // namespace cursomusica::course
