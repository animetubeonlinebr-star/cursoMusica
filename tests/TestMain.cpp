#include <juce_core/juce_core.h>

#include <cmath>
#include <iostream>
#include <vector>

#include "Audio/AudioPortClassifier.h"
#include "Audio/PluginSearchPaths.h"
#include "Course/Content/Diagrams.h"
#include "Course/Content/Topics.h"
#include "Course/ExerciseEvaluator.h"
#include "Course/ModuleCatalog.h"
#include "Course/NoteMath.h"
#include "Course/PracticeSession.h"
#include "Course/ProgressionRule.h"
#include "Course/QuizSession.h"
#include "Course/TempoGrid.h"
#include "Course/ProgressStore.h"
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

    for (const auto& m : modules)
        if (m.number > 1)
            check (! m.implemented, "modules 2..20 are still placeholders");

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
    testModuleCatalog();
    testProgressDatabase();
    testProgressStore();

    std::cout << "\n" << (checks - failures) << "/" << checks << " checks passed\n";
    if (failures > 0)
    {
        std::cout << failures << " FAILED\n";
        return 1;
    }

    std::cout << "ALL TESTS PASSED\n";
    return 0;
}
