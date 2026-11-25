#include "Course/BackingProgression.h"

#include <algorithm>
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

    // One group of an example's notes that can be a chord: the notes are
    // collected while the line does not descend, because a chord example is
    // played bottom-up (C, E, G, B) while a melody keeps moving on.
    struct Segment
    {
        std::vector<int> pitchClasses;
        int lowest = 0;
        int highest = 0;
    };

    std::vector<Segment> segmentNotes (const std::vector<int>& notes)
    {
        std::vector<Segment> segments;
        Segment current;
        int previous = -1000;

        auto closeCurrent = [&]
        {
            if (! current.pitchClasses.empty())
                segments.push_back (current);
            current = Segment {};
        };

        for (int midi : notes)
        {
            if (! current.pitchClasses.empty() && midi <= previous)
                closeCurrent();

            const int pc = ((midi % 12) + 12) % 12;
            if (std::find (current.pitchClasses.begin(), current.pitchClasses.end(), pc)
                == current.pitchClasses.end())
            {
                if (current.pitchClasses.empty())
                    current.lowest = midi;

                current.pitchClasses.push_back (pc);
                current.highest = midi;
            }

            previous = midi;
        }

        closeCurrent();
        return segments;
    }

    // A chord-shaped segment has 3..5 distinct tones packed in a chord span. A
    // scale run has more tones and a wider span, which is what keeps melodic
    // examples (licks and scale drills) out of the backing harmony.
    bool isChordSegment (const Segment& segment)
    {
        const int count = (int) segment.pitchClasses.size();
        if (count < 3 || count > 5)
            return false;

        return segment.highest - segment.lowest <= 14;
    }

    // The chords of the topic's own chord-shaped example. Empty when the topic
    // has none (a lick or a scale topic), so the caller falls back.
    std::vector<BackingChord> chordsFromTopic (const CourseModule& module,
                                               const Exercise& exercise)
    {
        if (exercise.lessonId.isEmpty())
            return {};

        const LessonBlock* lesson = nullptr;
        for (const auto& candidate : module.lessons)
            if (candidate.id == exercise.lessonId)
            {
                lesson = &candidate;
                break;
            }

        if (lesson == nullptr)
            return {};

        const std::vector<int>* bestNotes = nullptr;
        std::size_t bestChords = 0;

        for (const auto& item : lesson->detail)
        {
            if (item.notes.empty())
                continue;

            const auto segments = segmentNotes (item.notes);
            const auto chordCount = (std::size_t) std::count_if (segments.begin(), segments.end(),
                                                                 isChordSegment);

            // The example must be chord-shaped as a whole: a single chord inside
            // a melodic line is not a harmony the topic teaches.
            if (chordCount == 0 || chordCount * 2 < segments.size())
                continue;

            if (chordCount > bestChords)
            {
                bestChords = chordCount;
                bestNotes = &item.notes;
            }
        }

        if (bestNotes == nullptr)
            return {};

        std::vector<BackingChord> result;
        for (const auto& segment : segmentNotes (*bestNotes))
            if (isChordSegment (segment))
                result.push_back (toBackingChord (segment.pitchClasses));

        // A bar holds one chord per beat at most: four is the useful maximum.
        if (result.size() > 4)
            result.resize (4);

        return result;
    }

    std::vector<BackingChord> chordsFor (const CourseModule& module,
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

        // The topic's own chord example: the bed then sounds like the harmony
        // the topic teaches instead of the same generic vamp in every topic.
        if (auto fromTopic = chordsFromTopic (module, exercise); ! fromTopic.empty())
            return fromTopic;

        // A drill with no harmony of its own: play the module's gate vamp, which
        // is the harmonic centre the module teaches — its progression when it
        // declares one, otherwise the chord it holds in force.
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
}

std::vector<BackingChord> backingProgressionFor (const CourseModule& module,
                                                const Exercise& exercise)
{
    return chordsFor (module, exercise);
}

BackingStyle backingStyleFor (const Exercise& exercise)
{
    const juce::String text = (exercise.title + " " + exercise.goal + " " + exercise.check).toLowerCase();

    if (text.contains ("samba") || text.contains ("bossa") || text.contains ("partido")
        || text.contains ("cavaquinho"))
        return BackingStyle::samba;

    return BackingStyle::rock;
}

BackingArrangement backingArrangementFor (const CourseModule& module,
                                          const Exercise& exercise)
{
    BackingArrangement arrangement;
    arrangement.style = backingStyleFor (exercise);
    arrangement.chords = chordsFor (module, exercise);
    return arrangement;
}

} // namespace cursomusica::course
