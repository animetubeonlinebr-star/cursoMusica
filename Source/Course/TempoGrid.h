#pragma once

#include <juce_core/juce_core.h>

#include <vector>

namespace cursomusica::course
{

// Rhythmic grid of the metronome (ADR 0004). Pure math: given a BPM and a
// subdivision it produces the beat times and decides whether a note landed on
// the grid, within a tolerance proportional to the subdivision.
class TempoGrid
{
public:
    enum class Subdivision { quarter, eighth, triplet, sixteenth };

    TempoGrid (double bpm, Subdivision subdivision);

    double getBpm() const noexcept { return bpm; }
    Subdivision getSubdivision() const noexcept { return subdivision; }

    // Seconds between two grid ticks.
    double getTickInterval() const noexcept { return tickIntervalSeconds; }

    // Tolerance window (seconds) around a tick, from MUSIC.md.
    double getTolerance() const noexcept { return toleranceSeconds; }

    // True when a note at timeSeconds falls inside a tick's window.
    bool isOnGrid (double timeSeconds) const;

    // Fraction of the notes that landed on the grid (REQ-015).
    static double onGridRatio (const std::vector<double>& noteTimes, const TempoGrid& grid);

    // Highest BPM (from candidates) at which onGridRatio meets the target.
    static double achievedBpm (const std::vector<double>& noteTimes,
                               Subdivision subdivision,
                               const std::vector<double>& candidateBpms,
                               double targetRatio);

private:
    double bpm = 60.0;
    Subdivision subdivision = Subdivision::quarter;
    double tickIntervalSeconds = 1.0;
    double toleranceSeconds = 0.25;
};

} // namespace cursomusica::course
