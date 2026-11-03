#include "Course/TempoGrid.h"

#include <algorithm>
#include <cmath>

namespace cursomusica::course
{

namespace
{
    // Beats per minute -> seconds per tick, by subdivision.
    double tickIntervalFor (double bpm, TempoGrid::Subdivision subdivision)
    {
        const double safeBpm = juce::jmax (1.0, bpm);
        switch (subdivision)
        {
            case TempoGrid::Subdivision::quarter:   return 60.0 / safeBpm;
            case TempoGrid::Subdivision::eighth:    return 30.0 / safeBpm;
            case TempoGrid::Subdivision::triplet:   return 20.0 / safeBpm;
            case TempoGrid::Subdivision::sixteenth: return 15.0 / safeBpm;
        }

        return 60.0 / safeBpm;
    }

    // Tolerance as a fraction of the tick interval (MUSIC.md §tolerância rítmica).
    double toleranceFractionFor (TempoGrid::Subdivision subdivision)
    {
        switch (subdivision)
        {
            case TempoGrid::Subdivision::quarter:   return 0.25;
            case TempoGrid::Subdivision::eighth:    return 0.20;
            case TempoGrid::Subdivision::triplet:   return 0.18;
            case TempoGrid::Subdivision::sixteenth: return 0.15;
        }

        return 0.25;
    }
}

TempoGrid::TempoGrid (double bpmToUse, Subdivision subdivisionToUse)
    : bpm (bpmToUse), subdivision (subdivisionToUse)
{
    tickIntervalSeconds = tickIntervalFor (bpm, subdivision);
    toleranceSeconds = tickIntervalSeconds * toleranceFractionFor (subdivision);
}

bool TempoGrid::isOnGrid (double timeSeconds) const
{
    const auto nearestTick = std::llround (timeSeconds / tickIntervalSeconds);
    const double tickTime = (double) nearestTick * tickIntervalSeconds;
    return std::abs (timeSeconds - tickTime) <= toleranceSeconds;
}

double TempoGrid::onGridRatio (const std::vector<double>& noteTimes, const TempoGrid& grid)
{
    if (noteTimes.empty())
        return 0.0;

    int onGrid = 0;
    for (const double time : noteTimes)
        if (grid.isOnGrid (time))
            ++onGrid;

    return (double) onGrid / (double) noteTimes.size();
}

double TempoGrid::achievedBpm (const std::vector<double>& noteTimes,
                               Subdivision subdivision,
                               const std::vector<double>& candidateBpms,
                               double targetRatio)
{
    double best = 0.0;
    for (const double candidate : candidateBpms)
    {
        const TempoGrid grid (candidate, subdivision);
        if (onGridRatio (noteTimes, grid) >= targetRatio)
            best = juce::jmax (best, candidate);
    }

    return best;
}

} // namespace cursomusica::course
