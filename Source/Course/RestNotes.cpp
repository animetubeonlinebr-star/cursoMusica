#include "Course/RestNotes.h"

#include "Course/NoteMath.h"

#include <algorithm>

namespace cursomusica::course
{

namespace
{
    bool contains (const std::vector<int>& values, int value)
    {
        return std::find (values.begin(), values.end(), value) != values.end();
    }

    // A chromatic passing tone: a semitone away from an accepted neighbour on
    // either side, and moving by step into the next note (the resolution).
    bool isPassingTone (std::size_t index,
                        const std::vector<NoteEvent>& played,
                        const RestNoteSpec& spec)
    {
        const int pc = music::pitchClassOf (played[index].midi);

        const bool nextIsTarget = index + 1 < played.size()
                                    && classifyNote (music::pitchClassOf (played[index + 1].midi), spec)
                                           != NoteRole::error;
        if (! nextIsTarget)
            return false;

        const int nextPc = music::pitchClassOf (played[index + 1].midi);
        const int step = ((nextPc - pc) % 12 + 12) % 12;
        return step == 1 || step == 11;
    }
}

NoteRole classifyNote (int pitchClass, const RestNoteSpec& spec)
{
    if (contains (spec.chordPitchClasses, pitchClass))
        return NoteRole::rest;

    if (contains (spec.solicitedTensions, pitchClass))
        return NoteRole::tension;

    if (contains (spec.scalePitchClasses, pitchClass))
        return NoteRole::rest;

    return NoteRole::error;
}

ImprovisationResult evaluateImprovisation (const std::vector<NoteEvent>& played,
                                           const RestNoteSpec& spec,
                                           double passThreshold)
{
    ImprovisationResult result;
    result.total = (int) played.size();

    for (std::size_t i = 0; i < played.size(); ++i)
    {
        auto role = classifyNote (music::pitchClassOf (played[i].midi), spec);

        if (role == NoteRole::error && spec.allowPassing && isPassingTone (i, played, spec))
            role = NoteRole::passing;

        switch (role)
        {
            case NoteRole::rest:    ++result.rest; break;
            case NoteRole::tension: ++result.tension; break;
            case NoteRole::passing: ++result.passing; break;
            case NoteRole::error:   ++result.errors; break;
        }
    }

    const int accepted = result.rest + result.tension + result.passing;
    result.accuracy = evaluator::accuracyOf (accepted, result.total);
    result.passed = result.total > 0 && result.accuracy >= passThreshold;
    return result;
}

} // namespace cursomusica::course