#pragma once

#include <juce_core/juce_core.h>

#include <vector>

#include "Course/ExerciseEvaluator.h"
#include "Course/RestNotes.h"
#include "Course/TempoGrid.h"

namespace cursomusica
{

// Data model for the course. Content lives in ModuleCatalog.cpp; the source of
// truth for the wording is docs/MUSIC.md (owner: musician).

// One rich piece of the detailed explanation rendered in the central panel.
enum class ContentKind { heading, paragraph, bullet, callout, table, image, audio, score };

struct ContentItem
{
    ContentKind kind = ContentKind::paragraph;
    juce::String text;                    // heading / paragraph / bullet / callout / caption
    juce::StringArray columns;            // table header cells (kind == table)
    std::vector<juce::StringArray> rows;  // table rows (kind == table)
    juce::String imageName;               // diagram stem (kind == image / score), e.g. "f_caged_conexao"
    std::vector<int> notes;               // MIDI notes played by an audio / score example

    static ContentItem heading (juce::String t) { return { ContentKind::heading, std::move (t), {}, {}, {}, {} }; }
    static ContentItem paragraph (juce::String t) { return { ContentKind::paragraph, std::move (t), {}, {}, {}, {} }; }
    static ContentItem bullet (juce::String t) { return { ContentKind::bullet, std::move (t), {}, {}, {}, {} }; }
    static ContentItem callout (juce::String t) { return { ContentKind::callout, std::move (t), {}, {}, {}, {} }; }

    static ContentItem table (juce::StringArray header, std::vector<juce::StringArray> body)
    {
        ContentItem item;
        item.kind = ContentKind::table;
        item.columns = std::move (header);
        item.rows = std::move (body);
        return item;
    }

    // A JPG diagram embedded through juce_add_binary_data (see
    // Course/Content/Diagrams.h). `name` is the file stem, e.g. "f_caged_conexao".
    static ContentItem image (juce::String name, juce::String caption = {})
    {
        ContentItem item;
        item.kind = ContentKind::image;
        item.imageName = std::move (name);
        item.text = std::move (caption);
        return item;
    }

    // A playable audio example (REQ-004): `notes` are MIDI notes the app plays
    // when the student presses the play button under the caption. Used to
    // demonstrate an interval or a musical excerpt by ear.
    static ContentItem audio (std::vector<int> notes, juce::String caption)
    {
        ContentItem item;
        item.kind = ContentKind::audio;
        item.notes = std::move (notes);
        item.text = std::move (caption);
        return item;
    }

    // A score (embedded image) that the app also plays (REQ-004): every score has
    // its audio. `name` is the score's image stem, `notes` what the app plays.
    static ContentItem score (juce::String name, std::vector<int> notes, juce::String caption)
    {
        ContentItem item;
        item.kind = ContentKind::score;
        item.imageName = std::move (name);
        item.notes = std::move (notes);
        item.text = std::move (caption);
        return item;
    }
};

// One teaching block (topic) of a module, shown before any exercise (REQ-003).
// `paragraphs` is the compact summary; `detail` is the full explanation the
// central panel unfolds when the topic is selected on the left.
struct LessonBlock
{
    juce::String id;      // "A", "B", ...
    juce::String title;
    juce::StringArray paragraphs;
    std::vector<ContentItem> detail;
};

// A multiple-choice question of a quiz exercise, answered one at a time.
struct QuizQuestion
{
    juce::String prompt;
    juce::StringArray options;
    int correctIndex = 0;
};

// A practice item with an automatic check (REQ-008, REQ-009).
//
// `targets` (ordered notes) and `chordPitchClasses` are the playable specs the
// evaluator uses; an exercise with neither is shown as text only.
struct Exercise
{
    juce::String id;      // "EX-1.A.1"
    juce::String title;
    juce::String goal;
    juce::String check;   // how the app verifies it

    std::vector<course::TargetNote> targets;
    std::vector<int> chordPitchClasses;
    std::vector<std::vector<int>> chordProgression; // ordered chords (the gate)
    bool isGate = false;
    int targetBpm = 0;            // 0 -> inherit the module's target BPM
    float onGridTarget = 0.0f;    // 0 -> inherit the module's alignment target
    course::TempoGrid::Subdivision subdivision = course::TempoGrid::Subdivision::quarter;

    // Interval recognition (module 2): the student plays a root and then the note
    // at this distance, and the app verifies the distance the instrument
    // produced (any position on the neck is accepted). `repeats` is how many
    // correct executions the exercise asks for. Mutually exclusive with
    // `targets`/`chordPitchClasses`/`chordProgression`.
    course::evaluator::IntervalSpec interval;

    // Whether the attempt is graded against the metronome grid (REQ-015). The
    // gate and the rhythmic exercises are; the interval-recognition exercises
    // are not, because the client asked only to identify the interval, at any
    // tempo. Defaults to true so existing exercises keep their grid gate.
    bool usesGrid = true;

    // Topic this exercise belongs to ("A".."I"), so the right panel can filter
    // the exercises for the topic selected on the left. Empty -> module-wide.
    juce::String lessonId;

    // Multiple-choice questions (a "quiz" exercise): answered one at a time,
    // scored like any other exercise (accuracy = correct / answered).
    std::vector<QuizQuestion> quiz;

    // The lick this exercise obliges (client: "no exercício do tópico é
    // obrigatório o uso do lick apresentado no mesmo tópico"). The student must
    // play the phrase (verified as a note sequence) for the exercise to pass.
    juce::String lickId;

    // Rest-note / tension evaluation (REQ-011, REQ-012): when set, the exercise
    // is graded by classifying every played note against the harmonic context
    // instead of matching an exact sequence. Used by the improvisation exercises.
    course::RestNoteSpec restNotes;
    bool isImprovisation() const noexcept { return ! restNotes.empty(); }

    bool isQuiz() const noexcept { return ! quiz.empty(); }
};

// The pattern and link a module must cite (REQ-007, REQ-010).
struct PracticeTrack
{
    juce::String patternId;     // "PTN-R-PALM"
    juce::String patternUse;
    juce::StringArray guitarists; // reference players, cited as links
};

// A short melodic phrase taught by a topic (client: "cada tópico deve ter um
// lick"). The student studies it and the topic's exercise obliges its use. The
// lick may come from a curated apostila or from a reference guitarist; when it
// does, `source` names it. `notes` are the MIDI notes the app plays and expects.
struct Lick
{
    juce::String id;         // "LK-11.A"
    juce::String title;
    juce::String guitarist;  // cited player (REQ-007), when it comes from one
    juce::String patternId;  // PTN-* the lick illustrates (REQ-010)
    juce::String tab;        // compact tab/fret reading of the phrase
    juce::String source;     // curated apostila (REQ-006), when it comes from one
    std::vector<int> notes;  // MIDI notes of the phrase

    // Listening reference (client request, 2026-11-18): a real, verified song in
    // which the cited player uses the same vocabulary. The lick itself is an
    // original phrase of the course, so the reference is *representative
    // listening*, never the origin of the lick. `referenceExcerptPending` marks
    // the one thing still missing: the exact excerpt (time range) the student
    // should listen to. The song/album/year are already checked; the UI must not
    // present the reference as the lick's source (AGENTS.md §10, MUSIC.md §11.5).
    juce::String referenceSong;
    juce::String referenceNote;
    bool referenceExcerptPending = true;
};

// A guitar shape of the CAGED system.
struct CagedShape
{
    juce::String shape;   // "C", "A", "G", "E", "D"
    juce::String bassString;
    juce::String region;
};

// A rhythmic figure the student counts while playing (REQ-004, REQ-015).
struct RhythmCell
{
    juce::String figure;    // "semínima"
    juce::String value;     // "1 tempo (1/4)"
    juce::String syllable;  // "TÁ"
};

struct CourseModule
{
    int number = 0;
    juce::String title;
    juce::String objective;
    int level = 0;              // 1..7 progressive model
    int targetBpm = 0;          // REQ-015
    float onGridTarget = 0.0f;  // alignment target for this module
    bool implemented = false;

    // Whether the module grades against a target BPM. The client asked that
    // module 1 not show a BPM target (it is only meaningful from later modules
    // on): the header then prints a dash instead of the number.
    bool usesTempo = true;

    std::vector<LessonBlock> lessons;
    std::vector<Exercise> exercises;
    std::vector<Lick> licks;    // one per topic (client, from module 11 on)
    juce::String gateChallenge;
    PracticeTrack practice;
    std::vector<CagedShape> caged;
    std::vector<RhythmCell> rhythm; // counting cells shown with the metronome (REQ-015)

    // Curated apostilas backing the blocks, by file stem (REQ-006, CM-012).
    juce::StringArray sources;
};

} // namespace cursomusica
