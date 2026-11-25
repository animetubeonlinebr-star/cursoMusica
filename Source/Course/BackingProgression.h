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

// Instrumentation the bed should use. The client asked for the bed to sound like
// the style the topic teaches (2026-11-18): a rock/pop bed (keyboard, guitar
// riff, bass groove, drums) by default, and the samba bed (cavaquinho, 7-string
// guitar, surdo/pandeiro/rebolo) when the exercise is about samba/bossa.
enum class BackingStyle { rock, samba };

// The full bed for an exercise: which chords and which instrumentation.
struct BackingArrangement
{
    std::vector<BackingChord> chords;
    BackingStyle style = BackingStyle::rock;
};

// Chooses the harmony and the style for `exercise`. The harmony comes from, in
// order: the exercise's own progression, the chord it holds for improvisation,
// the chord-shaped examples of its topic (so each topic sounds like what it
// teaches instead of the same generic vamp), the module gate, A minor.
BackingArrangement backingArrangementFor (const CourseModule& module,
                                          const Exercise& exercise);

// The style of `exercise`, by its own wording. Pure and testable.
BackingStyle backingStyleFor (const Exercise& exercise);

} // namespace cursomusica::course
