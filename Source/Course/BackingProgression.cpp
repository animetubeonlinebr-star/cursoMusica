#include "Course/BackingProgression.h"

#include <cstdlib>

namespace cursomusica::course
{

namespace
{
    // A2, the bass root used when the chord does not imply a better one.
    constexpr int defaultBassMidi = 45;

    BackingChord toBackingChord (const std::vector<int>& pitchClasses)
    {
        BackingChord chord;
        for (int pc : pitchClasses)
            chord.pitchClasses.push_back (((pc % 12) + 12) % 12);

        // Put the bass an octave or two below the pad: the lowest chord tone
        // near A2 keeps the bass from colliding with the keyboard voicing.
        if (! chord.pitchClasses.empty())
        {
            int best = defaultBassMidi;
            int bestDistance = 1000;
            for (int midi = 33; midi <= 48; ++midi)
                if (((midi % 12) + 12) % 12 == chord.pitchClasses.front())
                {
                    const int distance = std::abs (midi - defaultBassMidi);
                    if (distance < bestDistance)
                    {
                        bestDistance = distance;
                        best = midi;
                    }
                }
            chord.bassMidi = best;
        }

        return chord;
    }
}

std::vector<BackingChord> backingProgressionFor (const CourseModule& module,
                                                const Exercise& exercise)
{
    std::vector<BackingChord> progression;

    if (! exercise.chordProgression.empty())
    {
        for (const auto& chord : exercise.chordProgression)
            progression.push_back (toBackingChord (chord));
        return progression;
    }

    if (! exercise.restNotes.chordPitchClasses.empty())
    {
        progression.push_back (toBackingChord (exercise.restNotes.chordPitchClasses));
        return progression;
    }

    // A drill with no harmony of its own: play the module's gate vamp, which is
    // the harmonic centre the module teaches — its progression when it declares
    // one, otherwise the chord it holds in force.
    for (const auto& candidate : module.exercises)
        if (candidate.isGate)
        {
            if (! candidate.chordProgression.empty())
            {
                for (const auto& chord : candidate.chordProgression)
                    progression.push_back (toBackingChord (chord));
                return progression;
            }

            if (! candidate.restNotes.chordPitchClasses.empty())
            {
                progression.push_back (toBackingChord (candidate.restNotes.chordPitchClasses));
                return progression;
            }
        }

    // Last resort: A minor, the centre of the module 11 licks.
    progression.push_back (toBackingChord ({ 9, 0, 4 }));
    return progression;
}

} // namespace cursomusica::course
