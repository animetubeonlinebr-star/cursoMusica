#pragma once

#include "Course/BackingProgression.h"
#include "Course/Module.h"

#include <vector>

// Transposition of the material an exercise asks the student to play, together
// with the harmony that accompanies it (client, 2026-11-25: the student must be
// able to practise the same material in all twelve keys).
//
// Grading follows the transposition: an exercise whose targets stay in the
// original key would fail the student who plays the new key correctly, so the
// expected notes move with the bed. Everything here is pure and allocation-light
// (no audio-thread use), so it is exercised directly by the tests.
namespace cursomusica::course
{

inline int wrapPitchClass (int pitchClass) noexcept
{
    return ((pitchClass % 12) + 12) % 12;
}

inline std::vector<int> transposedPitchClasses (const std::vector<int>& pitchClasses,
                                                int semitones)
{
    std::vector<int> result;
    result.reserve (pitchClasses.size());
    for (int pc : pitchClasses)
        result.push_back (wrapPitchClass (pc + semitones));
    return result;
}

inline BackingChord transposedChord (const BackingChord& chord, int semitones)
{
    BackingChord result = chord;
    result.pitchClasses = transposedPitchClasses (chord.pitchClasses, semitones);
    result.bassMidi = chord.bassMidi + semitones;
    return result;
}

// The exercise as the student must play it in the chosen key. The id, the
// wording and the licks stay untouched; the notes, the chords and the
// improvisation context move by `semitones`.
inline Exercise transposedExercise (const Exercise& exercise, int semitones)
{
    if (semitones == 0)
        return exercise;

    Exercise result = exercise;

    for (auto& target : result.targets)
        target.midi += semitones;

    result.chordPitchClasses = transposedPitchClasses (exercise.chordPitchClasses, semitones);

    result.chordProgression.clear();
    result.chordProgression.reserve (exercise.chordProgression.size());
    for (const auto& chord : exercise.chordProgression)
        result.chordProgression.push_back (transposedPitchClasses (chord, semitones));

    result.restNotes.chordPitchClasses =
        transposedPitchClasses (exercise.restNotes.chordPitchClasses, semitones);
    result.restNotes.scalePitchClasses =
        transposedPitchClasses (exercise.restNotes.scalePitchClasses, semitones);
    result.restNotes.solicitedTensions =
        transposedPitchClasses (exercise.restNotes.solicitedTensions, semitones);

    // The declared form moves with the bed: judging the student against the
    // original changes while the audio plays the new key would fail a correct
    // performance.
    result.harmony.clear();
    result.harmony.reserve (exercise.harmony.size());
    for (const auto& segment : exercise.harmony)
    {
        auto moved = segment;
        moved.context.chordPitchClasses =
            transposedPitchClasses (segment.context.chordPitchClasses, semitones);
        moved.context.scalePitchClasses =
            transposedPitchClasses (segment.context.scalePitchClasses, semitones);
        moved.context.solicitedTensions =
            transposedPitchClasses (segment.context.solicitedTensions, semitones);
        result.harmony.push_back (std::move (moved));
    }

    // `interval` is a distance, not a pitch, so it does not transpose.
    return result;
}

// The key the bed of `chords` is in: the bass of its first chord. Returns -1
// when there is no harmony to read a tonic from.
inline int tonicPitchClass (const std::vector<BackingChord>& chords) noexcept
{
    if (chords.empty() || chords.front().pitchClasses.empty())
        return -1;

    return wrapPitchClass (chords.front().bassMidi);
}

// Semitones from `fromPitchClass` up to `toPitchClass` (always 0..11).
inline int semitonesUpTo (int fromPitchClass, int toPitchClass) noexcept
{
    return wrapPitchClass (toPitchClass - fromPitchClass);
}

} // namespace cursomusica::course
