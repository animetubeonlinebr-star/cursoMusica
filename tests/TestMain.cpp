#include <juce_core/juce_core.h>

#include <cmath>
#include <iostream>
#include <map>
#include <vector>

#include "Audio/AudioPortClassifier.h"
#include "Audio/PluginSearchPaths.h"
#include "Course/Content/Diagrams.h"
#include "Course/Content/Topics.h"
#include "Course/ExerciseEvaluator.h"
#include "Course/Intervals.h"
#include "Course/ModuleCatalog.h"
#include "Course/NoteMath.h"
#include "Course/PracticeSession.h"
#include "Course/ProgressionRule.h"
#include "Course/QuizSession.h"
#include "Course/TempoGrid.h"
#include "Course/ExerciseFilter.h"
#include "Course/ProgressStore.h"
#include "Data/AppSettings.h"
#include "Data/ProgressDatabase.h"

// Minimal dependency-free test runner for the pure course logic (QA).
// Runs on the build machine with no audio device, so it is CI-friendly.

namespace
{
    int failures = 0;
    int checks = 0;

    void check (bool condition, const juce::String& what)
    {
        ++checks;
        if (! condition)
        {
            ++failures;
            std::cout << "  FAIL: " << what << "\n";
        }
    }

    void checkClose (double actual, double expected, double tolerance, const juce::String& what)
    {
        check (std::abs (actual - expected) <= tolerance,
               what + " (expected " + juce::String (expected, 3)
                    + ", got " + juce::String (actual, 3) + ")");
    }

    void testNoteMath()
    {
        std::cout << "NoteMath\n";
        using namespace cursomusica::music;

        checkClose (midiToFrequency (69.0), 440.0, 0.01, "A4 = 440 Hz");
        checkClose (midiToFrequency (69.0, 432.0), 432.0, 0.01, "A4 respects reference pitch");
        checkClose (midiToFrequency (60.0), 261.6256, 0.01, "C4 frequency");

        const auto a4 = analyseFrequency (440.0);
        check (a4.valid && a4.name == "A" && a4.octave == 4, "440 Hz is A4");
        checkClose (a4.cents, 0.0, 0.5, "A4 has no cents deviation");

        const auto sharp = analyseFrequency (440.0 * std::pow (2.0, 10.0 / 1200.0));
        checkClose (sharp.cents, 10.0, 1.0, "detunes by ~10 cents");

        check (analyseFrequency (0.0).valid == false, "silence is not a note");

        check (noteNameToMidi ("C4") == 60, "C4 -> 60");
        check (noteNameToMidi ("C#4") == 61, "C#4 -> 61");
        check (noteNameToMidi ("Db4") == 61, "Db4 -> 61");
        check (noteNameToMidi ("A4") == 69, "A4 -> 69");
        check (noteNameToMidi ("E2") == 40, "E2 -> 40");
        check (noteNameToMidi ("H4") == -1, "invalid letter rejected");

        check (midiToNoteName (61) == "C#4", "61 -> C#4");
    }

    void testEvaluator()
    {
        std::cout << "ExerciseEvaluator\n";
        using namespace cursomusica::course;

        const std::vector<TargetNote> scale { { 60, "C4" }, { 62, "D4" }, { 64, "E4" } };

        const std::vector<NoteEvent> perfect { { 0.0, 60, 2.0f }, { 0.5, 62, -3.0f }, { 1.0, 64, 0.0f } };
        const auto perfectResult = evaluator::evaluateSequence (scale, perfect);
        check (perfectResult.matched == 3 && perfectResult.passed, "perfect run passes");

        const std::vector<NoteEvent> sloppy { { 0.0, 60, 60.0f }, { 0.5, 62, 0.0f }, { 1.0, 64, 0.0f } };
        check (evaluator::evaluateSequence (scale, sloppy).matched == 2, "out-of-tune note is not counted");

        const std::vector<NoteEvent> wrongNote { { 0.0, 61, 0.0f }, { 0.5, 60, 0.0f }, { 1.0, 62, 0.0f }, { 1.5, 64, 0.0f } };
        check (evaluator::evaluateSequence (scale, wrongNote).matched == 3, "wrong note does not block the sequence");

        checkClose (evaluator::accuracyOf (9, 10), 0.9, 1e-9, "9/10 = 0.9");
        check (evaluator::gatePassed (0.90), "90% passes the gate");
        check (! evaluator::gatePassed (0.899), "89.9% fails the gate");
        checkClose (evaluator::accuracyOf (1, 1), 1.0, 1e-9, "1/1 is 100% (guard lives in the PO rule)");

        checkClose (evaluator::chordCoverage ({ 0, 4, 7 }, { 0, 4, 7, 2 }), 1.0, 1e-9, "full chord covered");
        checkClose (evaluator::chordCoverage ({ 0, 4, 7 }, { 0, 4 }), 2.0 / 3.0, 1e-6, "two of three notes");
        check (! evaluator::chordPassed ({ 0, 4, 7 }, { 0, 4 }), "2/3 chord fails the gate");
    }

    void testTempoGrid()
    {
        std::cout << "TempoGrid\n";
        using namespace cursomusica::course;

        const TempoGrid grid (60.0, TempoGrid::Subdivision::quarter);
        checkClose (grid.getTickInterval(), 1.0, 1e-9, "60 BPM quarter = 1 s");
        check (grid.isOnGrid (0.0), "beat 0 is on the grid");
        check (grid.isOnGrid (2.0), "beat 2 is on the grid");
        check (! grid.isOnGrid (0.5), "half a beat is off the grid");

        const TempoGrid eighth (120.0, TempoGrid::Subdivision::eighth);
        checkClose (eighth.getTickInterval(), 0.25, 1e-9, "120 BPM eighth = 0.25 s");

        const std::vector<double> onBeat { 0.0, 1.0, 2.0, 3.0 };
        checkClose (TempoGrid::onGridRatio (onBeat, grid), 1.0, 1e-9, "all notes on the grid");

        const std::vector<double> halfOff { 0.0, 0.5, 1.0, 1.5 };
        checkClose (TempoGrid::onGridRatio (halfOff, grid), 0.5, 1e-9, "half the notes on the grid");

        const std::vector<double> candidates { 60.0, 80.0, 100.0 };

        // Notes exactly on the 100 BPM grid: the top candidate is reached and
        // the lower ones fail because their grid no longer lines up.
        const std::vector<double> onFastGrid { 0.0, 0.6, 1.2, 1.8 };
        const double achieved = TempoGrid::achievedBpm (onFastGrid, TempoGrid::Subdivision::quarter, candidates, 0.9);
        checkClose (achieved, 100.0, 1e-9, "notes on the 100 BPM grid yield 100 BPM");

        // A slow, steady player only ever satisfies the 60 BPM grid.
        const std::vector<double> onSlowGrid { 0.0, 1.0, 2.0, 3.0 };
        checkClose (TempoGrid::achievedBpm (onSlowGrid, TempoGrid::Subdivision::quarter, candidates, 0.9),
                    60.0, 1e-9, "steady 60 BPM notes yield 60 BPM, not 100");

        const double none = TempoGrid::achievedBpm ({ 0.5, 1.5 }, TempoGrid::Subdivision::quarter, candidates, 0.9);
        checkClose (none, 0.0, 1e-9, "notes off the grid reach no BPM");
    }

    void testQuizSession()
    {
        std::cout << "QuizSession\n";
        using namespace cursomusica::course;

        cursomusica::Exercise quiz;
        quiz.id = "EX-1.A.1";
        quiz.quiz = {
            { "Q1", { "a", "b", "c" }, 1 },
            { "Q2", { "a", "b", "c" }, 2 },
            { "Q3", { "a", "b", "c" }, 0 },
        };

        QuizSession session;
        session.start (quiz);
        check (session.isRunning(), "quiz starts running");
        check (session.getNumQuestions() == 3, "quiz exposes its three questions");
        check (session.currentQuestion() != nullptr, "first question is on screen");
        check (session.currentQuestion()->prompt == "Q1", "first question is Q1");

        session.answer (1);   // correct
        check (session.getState().answered == 1, "one question answered");
        check (session.getState().correct == 1, "the correct answer scores");
        check (session.currentQuestion()->prompt == "Q2", "advances to the next question");

        session.answer (0);   // wrong
        session.answer (0);   // correct (Q3)

        const auto& state = session.getState();
        check (! state.running, "quiz stops after the last question");
        check (state.finished, "quiz is finished");
        check (state.correct == 2 && state.answered == 3, "two of three correct");
        checkClose (state.accuracy, 2.0 / 3.0, 1e-6, "accuracy is 2/3");
        check (! state.passed, "2/3 fails the 90% gate");
        check (session.currentQuestion() == nullptr, "no question left on screen");

        // A perfect run passes the same gate as the playable exercises.
        QuizSession perfect;
        perfect.start (quiz);
        perfect.answer (1);
        perfect.answer (2);
        perfect.answer (0);
        checkClose (perfect.getState().accuracy, 1.0, 1e-9, "perfect quiz is 100%");
        check (perfect.getState().passed, "perfect quiz passes the gate");

        // An empty quiz never runs.
        cursomusica::Exercise empty;
        QuizSession none;
        none.start (empty);
        check (! none.isRunning(), "a quiz with no questions does not run");
    }

    void testPracticeSession()
    {
        std::cout << "PracticeSession\n";
        using namespace cursomusica::course;

        // A note-sequence exercise: E2 then A2, at 60 BPM.
        cursomusica::Exercise sequence;
        sequence.id = "EX-1.D.1";
        sequence.targets = { { 40, "E2" }, { 45, "A2" } };

        PracticeSession session;
        session.start (sequence, 60, 0.75f);
        check (session.isRunning(), "session starts running");
        check (session.getTargetBpm() == 60, "inherits the module BPM");

        session.consume ({ { 0.0, 40, 0.0f }, { 1.0, 45, 0.0f } });
        session.finish();

        const auto& state = session.getState();
        check (state.matched == 2, "both notes matched");
        checkClose (state.accuracy, 1.0, 1e-9, "100% accuracy");
        checkClose (state.onGridRatio, 1.0, 1e-9, "both notes on the grid");
        check (state.passed, "a clean run passes both gates");

        // A chord progression (the gate): C then G, each covered in turn.
        cursomusica::Exercise gate;
        gate.id = "GATE-1";
        gate.chordProgression = { { 0, 4, 7 }, { 7, 11, 2 } };

        PracticeSession gateSession;
        gateSession.start (gate, 60, 0.75f);
        gateSession.consume ({ { 0.0, 60, 0.0f }, { 0.1, 64, 0.0f }, { 0.2, 67, 0.0f },
                               { 1.0, 67, 0.0f }, { 1.1, 71, 0.0f }, { 1.2, 62, 0.0f } });
        gateSession.finish();

        const auto& gateState = gateSession.getState();
        check (gateState.matched == 2, "both chords recognised in order");
        check (gateState.passed, "gate progression passes at 60 BPM");

        // Out-of-tune playing must fail the accuracy gate.
        PracticeSession sloppy;
        sloppy.start (sequence, 60, 0.75f);
        sloppy.consume ({ { 0.0, 40, 80.0f }, { 1.0, 45, 0.0f } });
        sloppy.finish();
        check (! sloppy.getState().accuracyPassed, "detuned note fails the accuracy gate");
    }
}

void testProgression()
{
    using namespace cursomusica::course::progress;

    check (isUnlocked (1, 0), "module 1 is always unlocked");
    check (! isUnlocked (2, 0), "module 2 is locked until module 1 is passed");
    check (isUnlocked (2, 1), "passing module 1 unlocks module 2");
    check (! isUnlocked (3, 1), "module 3 stays locked after only module 1");
    check (isUnlocked (3, 2), "passing module 2 unlocks module 3");
    check (highestUnlocked (0) == 1, "nothing passed unlocks only module 1");
    check (highestUnlocked (4) == 5, "passing up to module 4 unlocks module 5");
}

void testAudioPortClassifier()
{
    std::cout << "AudioPortClassifier\n";
    using namespace cursomusica::audio;

    // Ordinary hardware keeps the direction the backend reported.
    check (classifyAudioPort ("Microfone (Logi C270 HD WebCam)", true) == PortKind::capture,
           "a real microphone stays a capture port");
    check (classifyAudioPort ("Alto-falantes (USB Audio Device)", false) == PortKind::playback,
           "real speakers stay a playback port");

    // VoiceMeeter names its ports from the mixer's side (REQ-023): the raw name
    // looks swapped, so the classifier must correct it.
    check (classifyAudioPort ("Voicemeeter Input (VB-Audio Voicemeeter VAIO)", false) == PortKind::playback,
           "Voicemeeter Input is a playback target for the app");
    check (classifyAudioPort ("Voicemeeter AUX Input (VB-Audio Voicemeeter VAIO)", false) == PortKind::playback,
           "Voicemeeter AUX Input is a playback target for the app");
    check (classifyAudioPort ("Voicemeeter In 3 (VB-Audio Voicemeeter VAIO)", false) == PortKind::playback,
           "Voicemeeter In N is a playback target for the app");
    check (classifyAudioPort ("Voicemeeter VAIO3 Input (VB-Audio Voicemeeter VAIO)", false) == PortKind::playback,
           "Voicemeeter VAIO3 Input is a playback target for the app");

    check (classifyAudioPort ("Voicemeeter Out A1 (VB-Audio Voicemeeter VAIO)", true) == PortKind::capture,
           "Voicemeeter Out A1 is a capture source for the app");
    check (classifyAudioPort ("Voicemeeter Out B1 (VB-Audio Voicemeeter VAIO)", true) == PortKind::capture,
           "Voicemeeter Out B1 is a capture source for the app");

    check (classifyAudioPort ("CABLE Input (VB-Audio Virtual Cable)", false) == PortKind::playback,
           "VB-Audio CABLE Input is a playback target for the app");
    check (classifyAudioPort ("CABLE Output (VB-Audio Virtual Cable)", true) == PortKind::capture,
           "VB-Audio CABLE Output is a capture source for the app");
    check (classifyAudioPort ("CABLE In 16ch (VB-Audio Virtual Cable)", false) == PortKind::playback,
           "CABLE In 16ch (as in the VoiceMeeter screenshot) is a playback target");

    // Even when the backend mislabels a virtual port, the name wins.
    check (classifyAudioPort ("Voicemeeter Input (VB-Audio Voicemeeter VAIO)", true) == PortKind::playback,
           "a mislabelled virtual input is still corrected to playback");

    check (isVirtualMixerPort ("Voicemeeter Out A1 (VB-Audio Voicemeeter VAIO)"),
           "VoiceMeeter ports are recognised as virtual mixer ports");
    check (! isVirtualMixerPort ("Alto-falantes (High Definition Audio Device)"),
           "ordinary hardware is not a virtual mixer port");
}

void testModuleCatalog()
{
    using namespace cursomusica;

    const auto& modules = ModuleCatalog::getModules();
    check (modules.size() == 20, "catalogue has 20 modules");

    const auto* m1 = ModuleCatalog::findModule (1);
    check (m1 != nullptr, "module 1 exists");
    if (m1 == nullptr)
        return;

    check (m1->implemented, "module 1 is implemented");
    check (m1->lessons.size() == 9, "module 1 has nine explanation blocks (REQ-003)");
    check (m1->lessons.front().id == "A" && m1->lessons.back().id == "I",
           "module 1 blocks run A..I in order");

    // Counting cells backing the metronome grid (REQ-015).
    check (m1->rhythm.size() == 3, "module 1 teaches the three basic counting cells");
    check (m1->rhythm.front().syllable == juce::String::fromUTF8 ("TÁ"),
           "quarter-note cell is counted TÁ");

    // Curated apostilas backing the blocks (REQ-006, CM-012).
    check (m1->sources.size() == 7, "module 1 cites its curated apostilas");
    check (m1->sources.contains ("pdf-fraseado-melodico"),
           "CAGED source (fraseado-melodico) is cited");
    check (m1->sources.contains ("pdf-desvendando-os-segredos-da-guitarra-fusion"),
           "harmony source (fusion) is cited");
    check (m1->sources.contains (
               "pdf-caged-e-derivaoes-de-acordes-marcelo-mello-apostila-de-violao-e-guitarra-vol1"),
           "CAGED source (marcelo-mello) added in the 2026-11-04 review is cited");
    check (m1->sources.contains ("pdf-teoria-elementar-da-musica-ricordi-osvaldo-lacerda"),
           "elementary theory source (Lacerda) is cited");
    check (m1->sources.contains (
               "pdf-p-classtruncatedtext-module-lineclamped-85ulhh-style-max-lines5bohumil-med-teoria-da-musica-5-edicao-p"),
           "music theory source (Bohumil Med) is cited");
    check (m1->sources.contains (
               "pdf-manual-de-regulagem-e-manutenao-em-guitarra-contrabaixos-e-violoes-mozart-carvalho"),
           "instrument setup source (Mozart Carvalho) is cited");

    // Pattern and reference players (REQ-007).
    check (m1->practice.patternId == "PTN-R-PALM", "module 1 cites PTN-R-PALM");
    check (m1->practice.guitarists.size() >= 1, "module 1 cites at least one guitarist link");

    // The gate is a playable chord progression (REQ-009, REQ-015).
    bool hasGate = false;
    for (const auto& e : m1->exercises)
        if (e.isGate)
        {
            hasGate = true;
            check (e.chordProgression.size() == 4, "gate progression has four chords");
            check (e.chordProgression.front() == std::vector<int> ({ 0, 4, 7 }),
                   "gate opens on C major");
        }
    check (hasGate, "module 1 has a gate exercise");
    check (m1->exercises.size() == 30, "module 1 lists EX-1.A.1..EX-1.I.3 plus the gate");

    // EX-1.A.1 is the learning quiz (Questionario_m1), answered one at a time.
    check (m1->exercises.front().isQuiz(), "EX-1.A.1 is a multiple-choice quiz");
    check (m1->exercises.front().quiz.size() == 7, "the quiz has seven questions");
    for (const auto& q : m1->exercises.front().quiz)
        check (q.correctIndex >= 0 && q.correctIndex < q.options.size(),
               "every quiz question has a valid answer key");
    check (m1->exercises.front().lessonId == "A", "the quiz belongs to topic A");

    // Every topic A..I is served by at least one exercise (REQ-022).
    juce::StringArray coveredTopics;
    for (const auto& e : m1->exercises)
        if (e.lessonId.isNotEmpty() && ! coveredTopics.contains (e.lessonId))
            coveredTopics.add (e.lessonId);
    for (const auto& topic : { "A", "B", "C", "D", "E", "F", "G", "H", "I" })
        check (coveredTopics.contains (topic),
               juce::String ("topic ") + topic + " has at least one exercise (REQ-022)");

    // REQ-022 asks for a *playable* exercise per topic, not only a questionnaire:
    // each topic must own an exercise the app can verify (quiz or playable spec).
    juce::StringArray playableTopics;
    for (const auto& e : m1->exercises)
    {
        const bool playable = e.isQuiz() || ! e.targets.empty() || ! e.chordPitchClasses.empty()
                                || ! e.chordProgression.empty();
        if (playable && e.lessonId.isNotEmpty() && ! playableTopics.contains (e.lessonId))
            playableTopics.add (e.lessonId);
    }
    for (const auto& topic : { "A", "B", "C", "D", "E", "F", "G", "H", "I" })
        check (playableTopics.contains (topic),
               juce::String ("topic ") + topic + " has at least one executable exercise (REQ-022)");

    // Every exercise is tied to a topic so the right panel follows the left.
    for (const auto& e : m1->exercises)
        check (e.lessonId.isNotEmpty(), "exercise " + e.id + " is tied to a topic");

    // The detailed explanation backing topic A (the full text of the apostila).
    const auto& topicA = m1->lessons.front();
    check (! topicA.detail.empty(), "topic A carries a detailed explanation");
    bool hasTable = false;
    for (const auto& item : topicA.detail)
        if (item.kind == cursomusica::ContentKind::table)
            hasTable = true;
    check (hasTable, "topic A renders at least one table");

    // The client asked for at least five "pages" of explanation on every topic
    // A..I, and at least three exercises per topic. A page is a fixed amount of
    // body text (content::charsPerPage); both rules are enforced here so the
    // central panel really teaches each subject.
    auto detailChars = [] (const cursomusica::LessonBlock& topic)
    {
        int total = 0;
        for (const auto& item : topic.detail)
        {
            total += item.text.length();
            for (const auto& cell : item.columns)
                total += cell.length();
            for (const auto& row : item.rows)
                for (const auto& cell : row)
                    total += cell.length();
        }
        return total;
    };

    for (const auto& topic : m1->lessons)
    {
        const int chars = detailChars (topic);
        check (chars >= cursomusica::content::minTopicChars,
               juce::String ("topic ") + topic.id + " has at least "
                   + juce::String (cursomusica::content::minPages)
                   + " pages of explanation (" + juce::String (chars) + " chars)");

        int count = 0;
        for (const auto& e : m1->exercises)
            if (e.lessonId == topic.id)
                ++count;
        check (count >= 3, juce::String ("topic ") + topic.id
                               + " has at least three exercises (" + juce::String (count) + ")");
    }

    // The client asked that module 1 not use the BPM target (it is only
    // meaningful from module 2 on): the header then prints a dash. Later
    // modules keep the tempo, so the flag defaults to true.
    check (! m1->usesTempo, "module 1 does not use a BPM target (client)");
    for (const auto& m : modules)
        if (m.number > 1)
            check (m.usesTempo, "modules 2..20 still use a BPM target");

    // The catalogue lists each module number exactly once (generic rule: a
    // module branch replaces its own placeholder with an implemented module, so
    // the set of implemented modules grows without duplicating a number).
    for (std::size_t i = 0; i < modules.size(); ++i)
        for (std::size_t j = i + 1; j < modules.size(); ++j)
            check (modules[i].number != modules[j].number,
                   "catalogue lists each module number once");

    // The client asked the graphical material (fretboard, CAGED shapes, rhythm
    // figures) to be shown as images instead of text art. Every diagram named by
    // the content must be embedded in the binary (see tools/make_diagrams.py).
    check (content::diagramNames().size() >= 19, "the build embeds the course diagrams");
    for (const auto& topic : m1->lessons)
        for (const auto& item : topic.detail)
            if (item.kind == cursomusica::ContentKind::image)
                check (content::diagramExists (item.imageName),
                       juce::String ("topic ") + topic.id + " references the diagram '"
                           + item.imageName + "'");

    // The client asked the exercise ids to carry the module and the topic:
    // EX-1.<topico>.<n> (e.g. EX-1.A.1, EX-1.E.1), numbered per topic.
    for (const auto& topic : m1->lessons)
    {
        const auto prefix = juce::String ("EX-1.") + topic.id + ".";
        int expected = 0;
        for (const auto& e : m1->exercises)
            if (e.lessonId == topic.id && ! e.isGate)
            {
                ++expected;
                check (e.id.startsWith (prefix),
                       juce::String ("exercise ") + e.id + " of topic " + topic.id
                           + " follows EX-1.<topico>.<n>");
                check (e.id == prefix + juce::String (expected),
                       juce::String ("exercise ids of topic ") + topic.id
                           + " are numbered in order (" + e.id + ")");
            }
    }
}

// Progress persistence in PostgreSQL (ADR 0006). The unit part always runs; the
// integration part runs only when a real database is reachable, so CI without a
// server still passes and a developer with one gets the real path exercised.
void testProgressDatabase()
{
    std::cout << "ProgressDatabase\n";
    using namespace cursomusica::data;

    const auto config = PostgresConfig::fromEnvironment();
    check (config.port == "5432", "default PostgreSQL port is 5432");
    check (config.schema == "curso-musica", "default schema is curso-musica");
    check (config.student.isNotEmpty(), "a student id is always present");

    ProgressDatabase database;

    if (! ProgressDatabase::isCompiledIn())
    {
        // Local-only build: every call must be a safe no-op, never a crash.
        check (! database.connect (config), "connect is a no-op without libpq");
        check (database.loadHighestPassedModule() == -1, "load returns -1 without libpq");
        check (! database.saveHighestPassedModule (1), "save is a no-op without libpq");
        check (! database.ensureSchema(), "ensureSchema is a no-op without libpq");
        std::cout << "  (built without libpq: local-only path verified)\n";
        return;
    }

    if (! config.isEnabled() || ! database.connect (config))
    {
        // No database in this environment (CI): the code must degrade cleanly.
        check (! database.isConnected(), "not connected without a server");
        check (database.loadHighestPassedModule() == -1, "load returns -1 when offline");
        check (database.lastError().isNotEmpty(), "an offline attempt reports an error");
        std::cout << "  (no PostgreSQL reachable: offline path verified)\n";
        return;
    }

    check (database.isConnected(), "connected to PostgreSQL");
    check (database.ensureSchema(), "schema and tables are created (idempotent)");
    check (database.ensureSchema(), "ensureSchema is idempotent");

    // Use a throwaway student id, unique per run, so the test never disturbs
    // real progress and is repeatable (each run starts from a clean row).
    auto testConfig = config;
    testConfig.student = "qa-integration-" + juce::String (juce::Time::currentTimeMillis());
    ProgressDatabase scoped;
    check (scoped.connect (testConfig), "scoped connection opens");

    check (scoped.ensureSchema(), "scoped schema ready");

    check (scoped.loadHighestPassedModule() == -1, "a fresh student has no record");

    check (scoped.saveHighestPassedModule (3), "first save succeeds");
    check (scoped.loadHighestPassedModule() == 3, "saved value is read back");

    // Monotonicity: a lower value must never overwrite a higher one.
    check (scoped.saveHighestPassedModule (1), "lower save is accepted");
    check (scoped.loadHighestPassedModule() == 3, "progress never goes backwards");

    check (scoped.saveHighestPassedModule (5), "higher save succeeds");
    check (scoped.loadHighestPassedModule() == 5, "progress advances");

    check (scoped.recordModuleResult (5, true), "gate result is appended");
    check (scoped.recordModuleResult (5, false), "a failed attempt is appended too");

    // Per-exercise accuracy: last value wins, and reading an unknown id misses.
    check (scoped.loadExerciseResult ("gate-1") == -1, "an unseen exercise has no result");
    check (scoped.saveExerciseResult ("gate-1", 80.0), "exercise result is saved");
    check (scoped.loadExerciseResult ("gate-1") == 80, "the exercise result is read back");
    check (scoped.saveExerciseResult ("gate-1", 95.0), "a later attempt overwrites it");
    check (scoped.loadExerciseResult ("gate-1") == 95, "the last percentage is what stays");
    check (scoped.saveExerciseResult ("gate-2", 100.0), "a second exercise is saved");

    const auto all = scoped.loadExerciseResults();
    check (all.size() == 2, "all exercise results of the student are listed");

    std::cout << "  (integration against PostgreSQL verified)\n";
}

// End-to-end: the ProgressStore must save locally and mirror to PostgreSQL
// without blocking, and the module gate must follow the saved record.
void testProgressStore()
{
    std::cout << "ProgressStore\n";
    using namespace cursomusica::course;

    {
        ProgressStore store;
        store.setUnlockAll (false);

        check (! store.isModuleUnlocked (2), "module 2 starts locked");

        store.recordGateResult (1, true);
        check (store.getHighestPassedModule() == 1, "passing module 1 is recorded");
        check (store.isModuleUnlocked (2), "passing module 1 unlocks module 2");
        check (! store.isModuleUnlocked (3), "module 3 stays locked");

        // A failure never advances, and never regresses an earlier pass.
        store.recordGateResult (2, false);
        check (store.getHighestPassedModule() == 1, "a failure does not advance");
        store.recordGateResult (1, true);
        check (store.getHighestPassedModule() == 1, "re-passing does not regress");
    }

    // The local record survives a new instance (offline persistence).
    {
        ProgressStore reopened;
        check (reopened.getHighestPassedModule() == 1,
               "local progress survives a restart");

        // Per-exercise accuracy is remembered locally too (client request).
        check (reopened.getExerciseAccuracy ("never-attempted") == -1,
               "an exercise never attempted has no stored percentage");
        reopened.recordExerciseResult ("gate-1", 80.4);
        check (reopened.getExerciseAccuracy ("gate-1") == 80,
               "the last accuracy is stored (rounded)");

        // A later attempt replaces the previous percentage.
        reopened.recordExerciseResult ("gate-1", 92.0);
        check (reopened.getExerciseAccuracy ("gate-1") == 92,
               "a new attempt updates the stored percentage");

        // Out-of-range values are clamped, so the UI can never show 130%.
        reopened.recordExerciseResult ("gate-1", 130.0);
        check (reopened.getExerciseAccuracy ("gate-1") == 100,
               "the stored percentage is clamped to 100");

        // Clean up the shared local record so reruns start from scratch.
        reopened.reset();
        check (reopened.getHighestPassedModule() == 0, "reset clears the record");
        check (reopened.getExerciseAccuracy ("gate-1") == -1,
               "reset clears the per-exercise percentages too");
    }

    // And the per-exercise percentage survives a restart as well.
    {
        ProgressStore store;
        store.recordExerciseResult ("gate-9", 55.0);

        ProgressStore reopened;
        check (reopened.getExerciseAccuracy ("gate-9") == 55,
               "the per-exercise percentage survives a restart");
        reopened.reset();
    }
}



void testExerciseFilter()
{
    std::cout << "ExerciseFilter (topic -> exercises)\n";
    using namespace cursomusica;
    using namespace cursomusica::course;

    const auto* m1 = ModuleCatalog::findModule (1);
    check (m1 != nullptr, "module 1 is available");
    if (m1 == nullptr)
        return;

    // The scenario from the client: a module without content has no exercises,
    // so filtering another module's topic against it returns nothing. Filtering
    // the same topic against module 1 must list its exercises.
    const auto* m3 = ModuleCatalog::findModule (3);
    check (m3 != nullptr, "module 3 is available (still a placeholder)");

    const juce::String topicC = "C";
    const auto inM1 = exercisesForTopic (*m1, topicC);
    const auto inM3 = exercisesForTopic (*m3, topicC);

    check (! inM1.empty(), "module 1's topic C has exercises");
    check (inM3.empty(), "module 3 has no exercises for topic C (placeholder)");

    // Every returned index really belongs to the topic, and none is missed.
    int totalC = 0;
    for (const auto& e : m1->exercises)
        if (e.lessonId == topicC)
            ++totalC;

    check ((int) inM1.size() == totalC, "every topic C exercise is returned");
    for (int index : inM1)
        check (m1->exercises[(size_t) index].lessonId == topicC,
               "a returned exercise belongs to topic C");

    // An empty filter means "all exercises of the module" (the all-topics link).
    check ((int) exercisesForTopic (*m1, {}).size() == (int) m1->exercises.size(),
           "an empty filter lists the whole module");
}

void testDatabaseConfigPersistence()
{
    std::cout << "PostgresConfig persistence (Settings window)\n";
    using namespace cursomusica::data;

    auto& settings = AppSettings::get();

    // Clean slate: with nothing saved and no PGHOST, the mirror is off, so the
    // app never tried to create the schema (the reported bug).
    settings.removeValue ("database/enabled");
    settings.removeValue ("database/host");
    check (! PostgresConfig::fromSettings().isEnabled(),
           "no saved configuration means local-only mode");

    // What the Settings window writes must round-trip, host and all.
    PostgresConfig saved;
    saved.host   = "db.example";
    saved.port   = "5433";
    saved.user   = "cursomusica";
    saved.dbname = "curso-musica";
    saved.schema = "curso-musica";
    saved.disabled = false;
    saved.saveToSettings();

    const auto loaded = PostgresConfig::fromSettings();
    check (loaded.isEnabled(), "a saved host turns the mirror on");
    check (loaded.host == "db.example", "the host round-trips");
    check (loaded.port == "5433", "the port round-trips");
    check (loaded.user == "cursomusica", "the user round-trips");
    check (loaded.schema == "curso-musica", "the schema round-trips");

    // The password must never be written to the settings file (docs/SECURITY.md).
    const auto text = settings.getFile().loadFileAsString();
    check (! text.contains ("PGPASSWORD"), "the settings file never mentions the password");
    check (! text.contains ("database/password"), "no password key is stored");

    // Turning the mirror off again is honoured.
    auto off = saved;
    off.disabled = true;
    off.saveToSettings();
    check (! PostgresConfig::fromSettings().isEnabled(),
           "clearing the toggle returns to local-only mode");

    settings.removeValue ("database/enabled");
    settings.removeValue ("database/host");
    settings.removeValue ("database/port");
    settings.removeValue ("database/user");
    settings.removeValue ("database/name");
    settings.removeValue ("database/schema");
    settings.saveIfNeeded();
}

void testSharedSettings()
{
    std::cout << "AppSettings (single shared properties file)\n";
    using cursomusica::data::AppSettings;

    auto& settings = AppSettings::get();
    check (&settings == &AppSettings::get(),
           "every caller gets the same shared instance");

    // The shutdown bug: two components each held their own PropertiesFile over
    // this file, and the one that saved last rewrote the whole map, dropping the
    // other's keys (the course progress among them). Writing both through the
    // shared instance must keep both on disk.
    settings.setValue ("test/component-a", "progress");
    settings.saveIfNeeded();
    settings.setValue ("test/component-b", "plugins");
    settings.saveIfNeeded();

    const auto text = settings.getFile().loadFileAsString();
    check (text.contains ("test/component-a"),
           "the first component's key survives the second component's save");
    check (text.contains ("test/component-b"),
           "the second component's key is written too");

    settings.removeValue ("test/component-a");
    settings.removeValue ("test/component-b");
    settings.saveIfNeeded();
}

void testPluginSearchPaths()
{
    std::cout << "PluginSearchPaths\n";
    using cursomusica::PluginSearchPaths;

    PluginSearchPaths paths;
    check (paths.isEmpty(), "a new list is empty");

    check (paths.add ("C:/VST3"), "a folder is added");
    check (paths.add ("C:/VST3/Second"), "a second folder is added");
    check (paths.size() == 2, "both folders are kept");
    check (! paths.add ("  C:/VST3  "), "an entry is de-duplicated after trimming");
    check (! paths.add (""), "an empty entry is rejected");
    check (! paths.add ("   "), "a blank entry is rejected");
    check (paths.size() == 2, "rejected entries do not change the list");

    // Normalisation drops the trailing separator, so the same folder written two
    // ways is one entry.
    check (paths.add ("C:/VST3/Third/"), "a folder with a trailing separator is added");
    check (paths.size() == 3, "the normalised folder is stored once");
    check (! paths.add ("C:/VST3/Third"), "the normalised form is a duplicate");
    check (paths[2].endsWith ("Third"), "the stored entry has no trailing separator");

    // Serialisation round-trips through the properties file format.
    const auto serialised = paths.serialise();
    check (serialised.contains ("\n"), "entries are newline-separated");
    const auto restored = PluginSearchPaths::deserialise (serialised);
    check (restored.size() == 3, "deserialise restores every entry");
    check (restored[0] == paths[0] && restored[2] == paths[2], "deserialise preserves order and text");

    check (paths.remove ("C:/VST3"), "an entry is removed");
    check (paths.size() == 2, "removing drops exactly one entry");
    check (! paths.remove ("C:/VST3"), "removing a missing entry reports failure");

    // A stale entry stays in the list but is not searched.
    check (paths.resolveExisting().getNumPaths() == 0, "non-existent folders are not searched");

    paths.clear();
    check (paths.isEmpty(), "clear empties the list");

    // The list is capped, so a runaway config cannot grow without bound.
    PluginSearchPaths capped;
    for (int i = 0; i < PluginSearchPaths::maxEntries; ++i)
        capped.add ("C:/Plugins/" + juce::String (i));
    check (capped.size() == PluginSearchPaths::maxEntries, "the list fills up to the cap");
    check (! capped.add ("C:/Plugins/overflow"), "an entry past the cap is rejected");

    PluginSearchPaths fromArray;
    fromArray.setFromArray ({ "C:/A", "", "C:/A", "C:/B" });
    check (fromArray.size() == 2, "setFromArray drops blanks and duplicates");
}

// Interval theory (module 2): the mapping between semitones and interval names
// is the single source of truth for the lesson text, the quizzes and the
// detector-based exercises, so it is checked here.
void testIntervals()
{
    std::cout << "Intervals\n";
    using namespace cursomusica::course;

    check (intervalShortName (0) == "1J", "0 semitons is a perfect unison");
    check (describeInterval (3).name == juce::String::fromUTF8 ("terça menor"),
           "3 semitons is a minor third");
    check (describeInterval (4).name == juce::String::fromUTF8 ("terça maior"),
           "4 semitons is a major third");
    check (intervalShortName (5) == "4J", "5 semitones is a perfect fourth");
    check (intervalShortName (6) == "4A", "6 semitones is an augmented fourth (tritone)");
    check (intervalShortName (7) == "5J", "7 semitones is a perfect fifth");
    check (intervalShortName (11) == "7M", "11 semitones is a major seventh");
    check (intervalShortName (12) == "8J", "12 semitones is a perfect octave");

    check (describeInterval (7).perfect, "the fifth is a perfect interval");
    check (describeInterval (4).major, "the major third is major");
    check (describeInterval (3).minor, "the minor third is minor");
    check (describeInterval (6).augmented, "the tritone reads as augmented");
    check (! describeInterval (7).major, "the fifth is not major");

    // Just intervals have no major/minor form.
    for (int s : { 0, 5, 7, 12 })
        check (describeInterval (s).perfect, "perfect interval at " + juce::String (s));

    check (semitonesBetween (60, 64) == 4, "C4 to E4 is 4 semitones");
    check (semitonesBetween (64, 60) == 4, "the distance is absolute");

    const auto frame = mobileFrame (0);   // C
    check (frame.size() == 13, "the movable frame lists 0..12 semitones");
    check (frame[0].noteName == "C", "frame row 0 from C is C");
    check (frame[4].noteName == "E", "4 semitones from C is E (major third)");
    check (frame[7].noteName == "G", "7 semitones from C is G (perfect fifth)");
    check (frame[12].noteName == "C", "12 semitones from C is C again");
    check (frame[4].interval == juce::String::fromUTF8 ("terça maior"),
           "frame row 4 names the major third");

    // The frame is movable: from G the same distances land on transposed notes.
    const auto fromG = mobileFrame (7);
    check (fromG[4].noteName == "B", "4 semitones from G is B");
    check (fromG[7].noteName == "D", "7 semitones from G is D");

    check (isConsonant (7), "the fifth is consonant");
    check (isConsonant (4), "the major third is consonant");
    check (! isConsonant (6), "the tritone is not consonant");
    check (! isConsonant (11), "the major seventh is not consonant");
}

// The interval recogniser: the app verifies the distance the instrument
// produced, not absolute pitches, so any position on the neck passes.
void testIntervalEvaluation()
{
    std::cout << "IntervalEvaluation\n";
    using namespace cursomusica::course;

    auto note = [] (int midi) { return NoteEvent { 0.0, midi, 0.0f }; };

    evaluator::IntervalSpec majorThird;
    majorThird.semitones = 4;
    majorThird.repeats = 3;

    // C4->E4, D4->F#4, G3->B3: three major thirds, different positions.
    std::vector<NoteEvent> correct { note (60), note (64), note (62), note (66), note (55), note (59) };
    auto r = evaluator::evaluateIntervals (majorThird, correct);
    check (r.matched == 3, "three major thirds are recognised");
    check (r.passed, "three of three passes the 90% gate");

    // A wrong distance (minor third) does not count.
    std::vector<NoteEvent> wrong { note (60), note (63) };
    auto rWrong = evaluator::evaluateIntervals (majorThird, wrong);
    check (rWrong.matched == 0, "a minor third does not count as a major third");
    check (! rWrong.passed, "a wrong interval fails the gate");

    // Descending intervals do not count when only ascending is accepted.
    std::vector<NoteEvent> descending { note (64), note (60) };
    check (evaluator::evaluateIntervals (majorThird, descending).matched == 0,
           "a descending interval does not count when only ascending is asked");

    // An out-of-tune note is rejected by the cents tolerance.
    NoteEvent detuned { 0.0, 64, 60.0f };
    std::vector<NoteEvent> offPitch { note (60), detuned };
    check (evaluator::evaluateIntervals (majorThird, offPitch).matched == 0,
           "a note far from the tempered pitch is rejected");

    // Two correct executions of two asked: 100%; one of two: 50%.
    evaluator::IntervalSpec twice = majorThird;
    twice.repeats = 2;
    std::vector<NoteEvent> two { note (60), note (64), note (62), note (66) };
    check (evaluator::evaluateIntervals (twice, two).matched == 2, "two thirds recognised");
    std::vector<NoteEvent> one { note (60), note (64) };
    auto rOne = evaluator::evaluateIntervals (twice, one);
    check (rOne.matched == 1, "one third recognised");
    checkClose (rOne.accuracy, 0.5, 1e-9, "one of two is 50%");
    check (! rOne.passed, "one of two fails the gate");

    // No notes at all: never passes.
    check (! evaluator::evaluateIntervals (majorThird, {}).passed, "an empty attempt fails");

    // An interval exercise does not gate on the metronome grid (client asked
    // only to identify the interval, at any tempo).
    cursomusica::Exercise intervalEx;
    intervalEx.interval = twice;
    intervalEx.usesGrid = false;
    PracticeSession session;
    session.start (intervalEx, 64, 0.76f);
    session.consume (two);
    session.finish();
    check (session.getState().passed, "an interval exercise passes without the grid gate");
}

// Module 2 — Etapa 2. It must follow the same shape as module 1: explanation
// (>=5 pages per topic) with images, audio and scores, 3..5 exercises per topic,
// and part of the exercises played on the instrument and verified by the app.
void testModule2()
{
    std::cout << "Module2\n";
    using namespace cursomusica;

    const auto* m2 = ModuleCatalog::findModule (2);
    check (m2 != nullptr, "module 2 exists");
    if (m2 == nullptr)
        return;

    check (m2->implemented, "module 2 is implemented");
    check (m2->number == 2, "module 2 has number 2");
    check (m2->usesTempo, "module 2 uses a BPM target");
    check (m2->targetBpm == 64, "module 2 target BPM is 64 (MUSIC.md)");
    check (m2->lessons.size() == 8, "module 2 has eight topics (A..H)");
    check (m2->exercises.size() >= 30, "module 2 lists a full exercise set");

    // Every topic A..H has 3..5 exercises (client: "de 3 a 5 exercícios por tópico").
    for (const auto& topic : m2->lessons)
    {
        int count = 0;
        for (const auto& e : m2->exercises)
            if (e.lessonId == topic.id)
                ++count;
        check (count >= 3, juce::String ("topic ") + topic.id + " has at least three exercises");
        check (count <= 5, juce::String ("topic ") + topic.id + " has at most five exercises");
    }

    // Every exercise is tied to a topic and its id follows EX-2.<topico>.<n>.
    for (const auto& e : m2->exercises)
    {
        check (e.lessonId.isNotEmpty(), "exercise " + e.id + " is tied to a topic");
        if (! e.isGate)
            check (e.id.startsWith ("EX-2."), "exercise " + e.id + " follows EX-2.<topico>.<n>");
    }

    // Part of the exercises is played on the instrument and verified by the
    // detector: at least one interval exercise per topic (client request).
    juce::StringArray intervalTopics;
    for (const auto& e : m2->exercises)
        if (e.interval.semitones > 0 && e.lessonId.isNotEmpty())
            intervalTopics.addIfNotAlreadyThere (e.lessonId);
    for (const auto& topic : { "A", "B", "C", "D", "E", "G", "H" })
        check (intervalTopics.contains (topic),
               juce::String ("topic ") + topic + " has a playable interval exercise");

    // An interval exercise must not gate on the grid, and the app must be able
    // to verify it (playable = quiz or a spec the evaluator understands).
    for (const auto& e : m2->exercises)
        if (e.interval.semitones > 0)
        {
            check (! e.usesGrid, "interval exercise " + e.id + " is not grid-gated");
            check (e.interval.repeats >= 1, "interval exercise " + e.id + " asks for at least one repeat");
            check (e.interval.semitones >= 1 && e.interval.semitones <= 12,
                   "interval exercise " + e.id + " has a valid semitone distance");
        }

    // Explanation: >=5 pages per topic, at least one table and one image, and
    // the media the client asked for (images, audio, scores with audio).
    auto detailChars = [] (const LessonBlock& topic)
    {
        int total = 0;
        for (const auto& item : topic.detail)
        {
            total += item.text.length();
            for (const auto& cell : item.columns)
                total += cell.length();
            for (const auto& row : item.rows)
                for (const auto& cell : row)
                    total += cell.length();
        }
        return total;
    };

    bool anyAudio = false;
    bool anyScore = false;
    for (const auto& topic : m2->lessons)
    {
        const int chars = detailChars (topic);
        check (chars >= content::minTopicChars,
               juce::String ("topic ") + topic.id + " has at least "
                   + juce::String (content::minPages) + " pages (" + juce::String (chars) + " chars)");

        int images = 0, tables = 0, audios = 0, scores = 0;
        for (const auto& item : topic.detail)
        {
            if (item.kind == ContentKind::image) ++images;
            else if (item.kind == ContentKind::table) ++tables;
            else if (item.kind == ContentKind::audio) ++audios;
            else if (item.kind == ContentKind::score) ++scores;
        }
        check (images >= 1, juce::String ("topic ") + topic.id + " has at least one image");
        check (tables >= 1, juce::String ("topic ") + topic.id + " has at least one table");
        anyAudio = anyAudio || audios > 0;
        anyScore = anyScore || scores > 0;
    }
    check (anyAudio, "module 2 demonstrates intervals with audio (REQ-004)");
    check (anyScore, "module 2 has scores with their audio (REQ-004)");

    // Every diagram and score named by the content is embedded in the binary,
    // and every audio/score item actually carries notes to play.
    for (const auto& topic : m2->lessons)
        for (const auto& item : topic.detail)
        {
            if (item.kind == ContentKind::image || item.kind == ContentKind::score)
                check (content::diagramExists (item.imageName),
                       juce::String ("topic ") + topic.id + " references the image '"
                           + item.imageName + "'");
            if (item.kind == ContentKind::audio || item.kind == ContentKind::score)
            {
                check (! item.notes.empty(),
                       juce::String ("topic ") + topic.id + " has a playable example");
                for (const int midi : item.notes)
                    check (midi >= 0 && midi <= 127,
                           juce::String ("topic ") + topic.id + " example uses a valid MIDI note");
            }
        }

    // The module cites >=1 pattern and >=1 guitarist (REQ-007, REQ-010).
    check (m2->practice.patternId.isNotEmpty(), "module 2 cites a pattern");
    check (! m2->practice.guitarists.isEmpty(), "module 2 cites at least one guitarist");

    // The gate closes the module as a I–IV–V–I vamp on the grid (REQ-009).
    bool hasGate = false;
    for (const auto& e : m2->exercises)
        if (e.isGate)
        {
            hasGate = true;
            check (e.chordProgression.size() == 4, "module 2 gate has four chords");
            check (e.chordProgression.front() == std::vector<int> ({ 0, 4, 7 }),
                   "module 2 gate opens on C major");
        }
    check (hasGate, "module 2 has a gate exercise");

    // Generic rule for the implemented modules (so parallel module branches do
    // not conflict): every implemented module has a unique number in the
    // catalogue, and findModule returns each implemented module. A branch
    // implements only its own module, so the set of implemented modules is not
    // necessarily contiguous until every module branch has merged; the rule
    // therefore does not assert contiguity (that would fail on a single-module
    // branch), it asserts uniqueness and reachability.
    const auto& modules = ModuleCatalog::getModules();

    for (std::size_t i = 0; i < modules.size(); ++i)
        for (std::size_t j = i + 1; j < modules.size(); ++j)
            check (modules[i].number != modules[j].number,
                   "catalogue lists each module number once");

    int implemented = 0;
    for (const auto& m : modules)
        if (m.implemented)
        {
            ++implemented;
            const auto* found = ModuleCatalog::findModule (m.number);
            check (found != nullptr && found->implemented,
                   juce::String ("findModule returns implemented module ")
                       + juce::String (m.number));
        }
    check (implemented >= 2, "modules 1 and 2 are implemented");
    check (ModuleCatalog::findModule (1) != nullptr && ModuleCatalog::findModule (1)->implemented,
           "findModule(1) returns an implemented module");
    check (ModuleCatalog::findModule (2) != nullptr && ModuleCatalog::findModule (2)->implemented,
           "findModule(2) returns an implemented module");
}

// Module 7 — Etapa 7 (empilhamentos, estruturas modais e sonoridades). Same
// shape as module 2: >=5 pages per topic with images and tables, audio and
// scores with audio, 3..5 exercises per topic, part of them played on the
// instrument, and a gate on the grid.
void testModule7()
{
    std::cout << "Module7\n";
    using namespace cursomusica;

    const auto* m7 = ModuleCatalog::findModule (7);
    check (m7 != nullptr, "module 7 exists");
    if (m7 == nullptr)
        return;

    check (m7->implemented, "module 7 is implemented");
    check (m7->number == 7, "module 7 has number 7");
    check (m7->level == 3, "module 7 is level 3 (MUSIC.md)");
    check (m7->usesTempo, "module 7 uses a BPM target");
    check (m7->targetBpm == 84, "module 7 target BPM is 84 (MUSIC.md)");
    checkClose (m7->onGridTarget, 0.80, 1e-6, "module 7 on_grid target is 0.80");
    check (m7->lessons.size() == 10, "module 7 has ten topics (A..J)");
    check (m7->lessons.front().id == "A" && m7->lessons.back().id == "J",
           "module 7 topics run A..J in order");

    // Every topic A..J has 3..5 exercises (client: "de 3 a 5 exercícios por tópico").
    for (const auto& topic : m7->lessons)
    {
        int count = 0;
        for (const auto& e : m7->exercises)
            if (e.lessonId == topic.id)
                ++count;
        check (count >= 3, juce::String ("topic ") + topic.id + " has at least three exercises");
        check (count <= 5, juce::String ("topic ") + topic.id + " has at most five exercises");
    }

    // Every exercise is tied to a topic and its id follows EX-7.<topico>.<n>.
    for (const auto& e : m7->exercises)
    {
        check (e.lessonId.isNotEmpty(), "exercise " + e.id + " is tied to a topic");
        if (! e.isGate)
            check (e.id.startsWith ("EX-7."), "exercise " + e.id + " follows EX-7.<topico>.<n>");
    }

    // Part of the exercises is played on the instrument and verified by the
    // detector: at least one playable exercise per topic.
    for (const auto& topic : m7->lessons)
    {
        bool playable = false;
        for (const auto& e : m7->exercises)
            if (e.lessonId == topic.id
                && (! e.targets.empty() || ! e.chordPitchClasses.empty() || e.interval.semitones > 0))
                playable = true;
        check (playable, juce::String ("topic ") + topic.id + " has a playable exercise");
    }

    // Playable identification exercises must not gate on the grid, and the app
    // must be able to verify them.
    for (const auto& e : m7->exercises)
        if (e.interval.semitones > 0 || ! e.chordPitchClasses.empty() || ! e.targets.empty())
        {
            if (! e.isGate)
                check (! e.usesGrid, "playable exercise " + e.id + " is not grid-gated");
            check (e.interval.semitones >= 0 && e.interval.semitones <= 12,
                   "exercise " + e.id + " has a valid semitone distance");
        }

    // Explanation: >=5 pages per topic, at least one table and one image, and
    // the media the client asked for (images, audio, scores with audio).
    auto detailChars = [] (const LessonBlock& topic)
    {
        int total = 0;
        for (const auto& item : topic.detail)
        {
            total += item.text.length();
            for (const auto& cell : item.columns)
                total += cell.length();
            for (const auto& row : item.rows)
                for (const auto& cell : row)
                    total += cell.length();
        }
        return total;
    };

    bool anyAudio = false;
    bool anyScore = false;
    for (const auto& topic : m7->lessons)
    {
        const int chars = detailChars (topic);
        check (chars >= content::minTopicChars,
               juce::String ("topic ") + topic.id + " has at least "
                   + juce::String (content::minPages) + " pages (" + juce::String (chars) + " chars)");

        int images = 0, tables = 0, audios = 0, scores = 0;
        for (const auto& item : topic.detail)
        {
            if (item.kind == ContentKind::image) ++images;
            else if (item.kind == ContentKind::table) ++tables;
            else if (item.kind == ContentKind::audio) ++audios;
            else if (item.kind == ContentKind::score) ++scores;
        }
        check (images >= 1, juce::String ("topic ") + topic.id + " has at least one image");
        check (tables >= 1, juce::String ("topic ") + topic.id + " has at least one table");
        check (scores >= 1, juce::String ("topic ") + topic.id + " has a score");
        anyAudio = anyAudio || audios > 0;
        anyScore = anyScore || scores > 0;
    }
    check (anyAudio, "module 7 demonstrates the material with audio (REQ-004)");
    check (anyScore, "module 7 has scores with their audio (REQ-004)");

    // Every diagram and score named by the content is embedded in the binary,
    // and every audio/score item actually carries notes to play.
    for (const auto& topic : m7->lessons)
        for (const auto& item : topic.detail)
        {
            if (item.kind == ContentKind::image || item.kind == ContentKind::score)
                check (content::diagramExists (item.imageName),
                       juce::String ("topic ") + topic.id + " references the image '"
                           + item.imageName + "'");
            if (item.kind == ContentKind::audio || item.kind == ContentKind::score)
            {
                check (! item.notes.empty(),
                       juce::String ("topic ") + topic.id + " has a playable example");
                for (const int midi : item.notes)
                    check (midi >= 0 && midi <= 127,
                           juce::String ("topic ") + topic.id + " example uses a valid MIDI note");
            }
        }

    // Content correctness (the review found audio that did not match the
    // notated score and a target the student could not pass). These assertions
    // check the actual musical content, not just its presence.

    // (a) A score's audio must be exactly what the score image notates, and an
    //     audio example that teaches an ascending stack/scale must sound
    //     ascending (its caption announces a scale/empilhamento).
    auto ascendingLine = [] (const std::vector<int>& notes)
    {
        for (size_t i = 1; i < notes.size(); ++i)
            if (notes[i] <= notes[i - 1])
                return false;
        return true;
    };

    const std::map<juce::String, std::vector<int>> scoreNotation {
        { "m7_partitura_tercas",      { 60, 64, 67, 71 } },                 // Cmaj7
        { "m7_partitura_quartal",     { 60, 65, 70, 75, 79 } },             // C F Bb Eb G
        { "m7_partitura_outros",      { 48, 55, 62, 69 } },                 // quintas
        { "m7_partitura_triade_meio", { 48, 55, 59, 62 } },                 // Cmaj9
        { "m7_partitura_familias",    { 50, 53, 57, 60, 64 } },             // Dm9
        { "m7_partitura_caged",       { 60, 62, 64, 65, 67, 69, 71, 72 } }, // C maior
        { "m7_partitura_dorico",      { 60, 62, 63, 65, 67, 69, 70, 72 } }, // dorico
        { "m7_partitura_sus",         { 60, 65, 67, 70 } },                 // C7sus4
        { "m7_partitura_alterado",    { 60, 61, 63, 64, 66, 68, 70 } },     // alterado
        { "m7_partitura_vamp_modal",  { 60, 62, 63, 65, 67, 69, 70, 72 } }, // dorico
    };

    int scoresChecked = 0;
    for (const auto& topic : m7->lessons)
        for (const auto& item : topic.detail)
        {
            if (item.kind == ContentKind::score)
            {
                const auto it = scoreNotation.find (item.imageName);
                check (it != scoreNotation.end(),
                       "score " + item.imageName + " is known to the content test");
                if (it != scoreNotation.end())
                    check (item.notes == it->second,
                           "score " + item.imageName + " audio matches the notated image");
                ++scoresChecked;
            }
            else if (item.kind == ContentKind::audio)
            {
                if (item.text.containsIgnoreCase ("escala")
                    || item.text.containsIgnoreCase ("empilhamento"))
                    check (ascendingLine (item.notes),
                           "ascending example '" + item.text.substring (0, 24) + "...' rises");
            }
        }
    check (scoresChecked >= 10, "module 7 has all ten scores checked for notation");

    // (b) A scale exercise's target is the correct ascending sequence, and (c)
    //     playing that sequence correctly must pass the real evaluator (this is
    //     the regression for EX-7.G.2, which failed with matched=7/8).
    const std::map<juce::String, std::vector<int>> scaleTargets {
        { "EX-7.F.2", { 60, 62, 64, 65, 67, 69, 71, 72 } }, // C maior
        { "EX-7.F.3", { 62, 64, 65, 67, 69, 71, 72, 74 } }, // D dorico (no tom)
        { "EX-7.G.2", { 60, 62, 63, 65, 67, 69, 70, 72 } }, // C dorico
        { "EX-7.G.3", { 60, 62, 64, 66, 67, 69, 71, 72 } }, // C lidio
    };

    for (const auto& e : m7->exercises)
    {
        const auto it = scaleTargets.find (e.id);
        if (it == scaleTargets.end())
            continue;

        std::vector<int> actual;
        for (const auto& t : e.targets)
            actual.push_back (t.midi);
        check (actual == it->second, "exercise " + e.id + " target is the correct ascending scale");

        std::vector<course::NoteEvent> played;
        double t = 0.0;
        for (const int midi : it->second)
        {
            played.push_back ({ t, midi, 0.0f });
            t += 0.4;
        }
        const auto result = course::evaluator::evaluateSequence (e.targets, played);
        check (result.passed,
               "playing " + e.id + " correctly passes the evaluator (matched="
                   + juce::String (result.matched) + "/" + juce::String (result.total) + ")");
    }

    // The module cites >=1 pattern and >=1 guitarist (REQ-007, REQ-010).
    check (m7->practice.patternId.isNotEmpty(), "module 7 cites a pattern");
    check (! m7->practice.guitarists.isEmpty(), "module 7 cites at least one guitarist");

    // Curated apostilas (REQ-006, CM-012).
    check (m7->sources.size() >= 1, "module 7 cites its curated apostilas");

    // The gate closes the module as a II–V–I on the grid (REQ-009).
    bool hasGate = false;
    for (const auto& e : m7->exercises)
        if (e.isGate)
        {
            hasGate = true;
            check (e.chordProgression.size() == 4, "module 7 gate has four chords");
            check (e.chordProgression.front() == std::vector<int> ({ 2, 5, 9, 0 }),
                   "module 7 gate opens on Dm7 (the II of the II–V–I)");
        }
    check (hasGate, "module 7 has a gate exercise");

    // findModule(7) returns the implemented module, and the catalogue lists
    // each number once (generic rule; parallel module branches add 3..6, 8..20).
    check (ModuleCatalog::findModule (7) != nullptr && ModuleCatalog::findModule (7)->implemented,
           "findModule(7) returns an implemented module");
    const auto& modules = ModuleCatalog::getModules();
    int seen7 = 0;
    for (const auto& m : modules)
        if (m.number == 7)
            ++seen7;
    check (seen7 == 1, "module 7 appears exactly once in the catalogue");
}

int main()
{
    testNoteMath();
    testEvaluator();
    testTempoGrid();
    testQuizSession();
    testPracticeSession();
    testProgression();
    testAudioPortClassifier();
    testPluginSearchPaths();
    testIntervals();
    testIntervalEvaluation();
    testModuleCatalog();
    testModule2();
    testModule7();
    testProgressDatabase();
    testProgressStore();
    testSharedSettings();
    testExerciseFilter();
    testDatabaseConfigPersistence();

    std::cout << "\n" << (checks - failures) << "/" << checks << " checks passed\n";
    if (failures > 0)
    {
        std::cout << failures << " FAILED\n";
        return 1;
    }

    std::cout << "ALL TESTS PASSED\n";
    return 0;
}
