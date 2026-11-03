#include "Course/PracticeSession.h"

#include "Course/NoteMath.h"

#include <algorithm>
#include <cmath>

namespace cursomusica::course
{

namespace
{
    // Greedy ordered chord matcher: walks the played notes and advances through
    // the progression once a chord's pitch classes are covered. Returns the
    // matched chord count and records each chord's onset time.
    int matchChordProgression (const std::vector<std::vector<int>>& progression,
                               const std::vector<NoteEvent>& played,
                               std::vector<double>& onsetsOut)
    {
        std::size_t chordIndex = 0;
        std::vector<int> heard;

        for (const auto& event : played)
        {
            if (chordIndex >= progression.size())
                break;

            const int pc = music::pitchClassOf (event.midi);
            if (std::find (heard.begin(), heard.end(), pc) == heard.end())
                heard.push_back (pc);

            if (evaluator::chordPassed (progression[chordIndex], heard))
            {
                onsetsOut.push_back (event.timeSeconds);
                heard.clear();
                ++chordIndex;
            }
        }

        return (int) chordIndex;
    }
}

void PracticeSession::start (const Exercise& exercise, int moduleTargetBpm, float moduleOnGridTarget)
{
    current = &exercise;
    targetBpm = exercise.targetBpm > 0 ? exercise.targetBpm : moduleTargetBpm;
    onGridTarget = exercise.onGridTarget > 0.0f ? exercise.onGridTarget : moduleOnGridTarget;

    grid = TempoGrid ((double) targetBpm, exercise.subdivision);

    target = exercise.targets;
    played.clear();
    noteTimes.clear();
    detectedPitchClasses.clear();

    state = {};
    state.running = true;
    state.targetCount = (int) target.size();

    if (! exercise.chordProgression.empty())
        state.targetCount = (int) exercise.chordProgression.size();
}

void PracticeSession::stop()
{
    state.running = false;
}

void PracticeSession::consume (const std::vector<NoteEvent>& events)
{
    if (! state.running || events.empty())
        return;

    for (const auto& event : events)
    {
        played.push_back (event);
        noteTimes.push_back (event.timeSeconds);
        detectedPitchClasses.push_back (music::pitchClassOf (event.midi));
        state.lastNote = music::midiToNoteName (event.midi);
    }

    state.notesHeard = (int) played.size();
    recompute();
}

void PracticeSession::finish()
{
    if (! state.running)
        return;

    recompute();
    state.running = false;
    state.finished = true;

    if (state.passed)
        state.message = juce::String::fromUTF8 ("Aprovado: você pode avançar.");
    else if (! state.accuracyPassed)
        state.message = juce::String::fromUTF8 ("Acerto abaixo de 90% — tente novamente.");
    else
        state.message = juce::String::fromUTF8 ("Fora da grade — toque junto com o metrônomo.");
}

void PracticeSession::recompute()
{
    if (current == nullptr)
        return;

    std::vector<double> onsets;

    if (! current->chordProgression.empty())
    {
        state.matched = matchChordProgression (current->chordProgression, played, onsets);
        state.accuracy = evaluator::accuracyOf (state.matched, state.targetCount);
    }
    else if (! target.empty())
    {
        const auto result = evaluator::evaluateSequence (target, played);
        state.matched = result.matched;
        state.accuracy = result.accuracy;
    }
    else if (! current->chordPitchClasses.empty())
    {
        state.accuracy = evaluator::chordCoverage (current->chordPitchClasses, detectedPitchClasses);
        state.matched = (int) std::llround (state.accuracy * 3.0);
    }

    const auto& gridTimes = onsets.empty() ? noteTimes : onsets;
    state.onGridRatio = TempoGrid::onGridRatio (gridTimes, grid);

    state.accuracyPassed = evaluator::gatePassed (state.accuracy);
    state.gridPassed = state.onGridRatio >= (double) onGridTarget;
    state.passed = state.accuracyPassed && state.gridPassed;
}

} // namespace cursomusica::course
