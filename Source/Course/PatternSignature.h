#pragma once

#include <juce_core/juce_core.h>

#include <cstdlib>
#include <vector>

namespace cursomusica::course
{

// Whether `notes` carries the musical signature of the numeric pattern it cites
// (REQ-010). The lick card prints the pattern id beside the phrase, so a phrase
// that cites thirds while playing stepwise seconds tells the student to expect a
// sound that is not there.
//
// Patterns whose signature is not an interval shape (rhythmic ones, string
// skipping) return true: the check only constrains what it can prove.
inline bool patternSignatureHolds (const juce::String& patternId, const std::vector<int>& notes)
{
    if (notes.size() < 3)
        return true;

    std::vector<int> intervals;
    intervals.reserve (notes.size() - 1);
    for (size_t i = 1; i < notes.size(); ++i)
        intervals.push_back (notes[i] - notes[i - 1]);

    // 1-2-3, 2-3-4…: two steps up, then back down over the second one.
    int groupsOfThree = 0;
    for (size_t i = 0; i + 2 < intervals.size(); ++i)
        if (intervals[i] > 0 && intervals[i + 1] > 0 && intervals[i + 2] == -intervals[i + 1])
            ++groupsOfThree;

    // Longest streak of consecutive leaps in one semitone class.
    auto leaps = [&intervals] (int smallest, int largest)
    {
        int best = 0, run = 0;
        for (auto interval : intervals)
        {
            const auto size = std::abs (interval);
            run = (size >= smallest && size <= largest) ? run + 1 : 0;
            best = juce::jmax (best, run);
        }
        return best;
    };

    // Longest run of neighbouring notes walking one direction (a scale run).
    auto stepwiseNotes = [&intervals]
    {
        int best = 0, run = 0;
        for (size_t i = 0; i < intervals.size(); ++i)
        {
            const auto sameDirection = i > 0 && (intervals[i] > 0) == (intervals[i - 1] > 0);
            run = std::abs (intervals[i]) <= 4 ? (sameDirection ? run + 1 : 1) : 0;
            best = juce::jmax (best, run);
        }
        return best > 0 ? best + 1 : 0;
    };

    if (patternId == "PTN-M-3" || patternId == "PTN-M-TRIQ")
        return groupsOfThree >= 2;
    if (patternId == "PTN-M-3rds")
        return leaps (3, 4) >= 3;
    if (patternId == "PTN-M-4ths")
        return leaps (5, 6) >= 3;
    if (patternId == "PTN-A-TRIAD")
        return leaps (3, 4) >= 2;
    if (patternId == "PTN-A-DROP2" || patternId == "PTN-A-DROP3")
        return leaps (3, 4) >= 3;
    if (patternId == "PTN-M-SCALE")
        return stepwiseNotes() >= 5;

    // A rest/tension phrase is not an interval shape: it alternates chord tones
    // (rest) with a colour tension and resolves. What can be proven here is that
    // it moves by more than a scale run would — it leaps at least once — so a
    // phrase made only of neighbouring notes cannot claim to be one.
    if (patternId == "PTN-M-REST")
        return leaps (3, 12) >= 1 && stepwiseNotes() < (int) notes.size();

    return true;
}

} // namespace cursomusica::course
