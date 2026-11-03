#include "Course/ExerciseEvaluator.h"

#include "Course/NoteMath.h"

#include <algorithm>
#include <cmath>

namespace cursomusica::course::evaluator
{

SequenceResult evaluateSequence (const std::vector<TargetNote>& target,
                                 const std::vector<NoteEvent>& played,
                                 float centsTolerance,
                                 double passThreshold)
{
    SequenceResult result;
    result.total = (int) target.size();

    if (result.total == 0)
        return result;

    // Longest common subsequence between the target and what was played. A note
    // matches when it is the same pitch and within tolerance; wrong or extra
    // notes become insertions and missed notes become deletions, so one slip
    // does not desynchronise the rest of the exercise.
    const auto matches = [centsTolerance] (const TargetNote& t, const NoteEvent& p)
    {
        return p.midi == t.midi && std::abs (p.cents) <= centsTolerance;
    };

    const std::size_t n = target.size();
    const std::size_t m = played.size();
    std::vector<int> previous (m + 1, 0);
    std::vector<int> current (m + 1, 0);

    for (std::size_t i = 1; i <= n; ++i)
    {
        for (std::size_t j = 1; j <= m; ++j)
            current[j] = matches (target[i - 1], played[j - 1])
                           ? previous[j - 1] + 1
                           : juce::jmax (previous[j], current[j - 1]);

        std::swap (previous, current);
    }

    result.matched = previous[m];
    result.accuracy = accuracyOf (result.matched, result.total);
    result.passed = result.accuracy >= passThreshold;
    return result;
}

double chordCoverage (const std::vector<int>& targetPitchClasses,
                      const std::vector<int>& detectedPitchClasses)
{
    if (targetPitchClasses.empty())
        return 0.0;

    int covered = 0;
    for (const int wanted : targetPitchClasses)
    {
        const bool found = std::find (detectedPitchClasses.begin(),
                                      detectedPitchClasses.end(), wanted)
                             != detectedPitchClasses.end();
        if (found)
            ++covered;
    }

    return accuracyOf (covered, (int) targetPitchClasses.size());
}

bool chordPassed (const std::vector<int>& targetPitchClasses,
                  const std::vector<int>& detectedPitchClasses,
                  double threshold)
{
    return gatePassed (chordCoverage (targetPitchClasses, detectedPitchClasses),
                       threshold);
}

double accuracyOf (int hits, int attempts)
{
    if (attempts <= 0)
        return 0.0;

    return (double) hits / (double) attempts;
}

bool gatePassed (double accuracy, double threshold)
{
    return accuracy >= threshold;
}

} // namespace cursomusica::course::evaluator
