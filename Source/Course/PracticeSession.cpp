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

void PracticeSession::start (const Exercise& exercise, int moduleTargetBpm, float moduleOnGridTarget,
                             int chosenBpm, bool moduleUsesTempo)
{
    current = &exercise;
    targetBpm = exercise.targetBpm > 0 ? exercise.targetBpm : moduleTargetBpm;
    onGridTarget = exercise.onGridTarget > 0.0f ? exercise.onGridTarget : moduleOnGridTarget;

    // The student may practice slower than the goal, but the attempt only counts
    // at the goal tempo or above (REQ-015, client 2026-11-19). The tempo is only
    // graded where the app measures the grid: an exercise played off the grid
    // (interval identification, improvisation) has no tempo to hold.
    practiceBpm = chosenBpm > 0 ? chosenBpm : targetBpm;
    tempoGated = moduleUsesTempo && exercise.usesGrid && ! exercise.isQuiz();

    grid = TempoGrid ((double) practiceBpm, exercise.subdivision);

    target = exercise.targets;
    intervalSpec = exercise.interval;
    gridGated = exercise.usesGrid;
    played.clear();
    noteTimes.clear();
    detectedPitchClasses.clear();

    state = {};
    state.running = true;
    state.targetCount = (int) target.size();
    state.practiceBpm = practiceBpm;
    state.targetBpm = targetBpm;
    state.tempoGated = tempoGated;

    if (! exercise.chordProgression.empty())
        state.targetCount = (int) exercise.chordProgression.size();
    else if (intervalSpec.semitones > 0)
        state.targetCount = juce::jmax (1, intervalSpec.repeats);
    else if (exercise.isImprovisation())
        state.targetCount = 0;   // grows with the notes played (set in recompute())
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
    else if (! state.tempoPassed)
        state.message = juce::String::fromUTF8 ("Abaixo do BPM meta (")
                         + juce::String (state.targetBpm)
                         + juce::String::fromUTF8 ("): suba o metrônomo para ")
                         + juce::String (state.targetBpm)
                         + juce::String::fromUTF8 (" ou mais e repita. A execução a ")
                         + juce::String (state.practiceBpm)
                         + juce::String::fromUTF8 (" BPM não conta para a conclusão.");
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
    else if (intervalSpec.semitones > 0)
    {
        const auto result = evaluator::evaluateIntervals (intervalSpec, played);
        state.matched = result.matched;
        state.accuracy = result.accuracy;
    }
    else if (current->isImprovisation())
    {
        // Rest-note evaluation (REQ-011/REQ-012): every note is classified
        // against the context; a tension outside the context is an error.
        const auto result = evaluateImprovisation (played, current->restNotes);
        state.matched = result.rest + result.tension + result.passing;
        state.targetCount = result.total;   // the attempt is graded over its own notes
        state.accuracy = result.accuracy;
    }

    const auto& gridTimes = onsets.empty() ? noteTimes : onsets;
    state.onGridRatio = TempoGrid::onGridRatio (gridTimes, grid);

    state.accuracyPassed = evaluator::gatePassed (state.accuracy);
    // Interval exercises are not measured against the grid: the client asked to
    // identify the interval, not to play it in time.
    state.gridPassed = ! gridGated || state.onGridRatio >= (double) onGridTarget;

    // Tempo gate (REQ-015): practicing below the goal does not conclude the
    // exercise, however clean the execution was.
    state.tempoPassed = ! tempoGated || practiceBpm >= targetBpm;

    state.passed = state.accuracyPassed && state.gridPassed && state.tempoPassed;
}

} // namespace cursomusica::course
