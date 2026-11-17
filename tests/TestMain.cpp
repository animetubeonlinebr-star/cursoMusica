#include <juce_core/juce_core.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>

#include "Audio/AudioPortClassifier.h"
#include "Audio/PitchDetector.h"
#include "Audio/PluginChainModel.h"
#include "Audio/PluginSearchPaths.h"
#include "UI/PairedSlots.h"
#include "Course/Content/Diagrams.h"
#include "Course/Content/Topics.h"
#include "Course/Content/ScoreNotes.h"
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

// Generic catalog-shape rule, valid for any set of implemented modules. The
// Etapas (3..10) are implemented in parallel branches, each from `test`, so a
// branch that lands module 5 while 3 and 4 are still placeholders must not
// break — and must not conflict with the branches for 3 and 4. The rule is
// therefore invariant under any implemented subset:
//   (a) every number 1..20 appears exactly once in getModules();
//   (b) the anchor of "from 1" holds: module 1 is implemented;
//   (c) every module marked implemented really carries lessons and exercises,
//       and findModule() returns it.
// This replaces the old "modules 3..20 are placeholders" assertion, which
// stopped being true as soon as a later module landed. Strict contiguity from 1
// is deliberately NOT asserted: with one Etapa per branch, a branch delivering
// module 5 alone (3 and 4 pending) would fail it, and so would the branch for 4.
void checkModuleCatalogShape (const std::vector<cursomusica::CourseModule>& modules)
{
    using namespace cursomusica;
    std::cout << "ModuleCatalogShape\n";

    // (a) unique numbers, covering 1..20.
    for (int number = 1; number <= 20; ++number)
    {
        int occurrences = 0;
        for (const auto& m : modules)
            if (m.number == number)
                ++occurrences;
        check (occurrences == 1,
               juce::String ("module ") + juce::String (number) + " is listed exactly once");
    }

    // (b) the "from 1" anchor.
    const auto* first = ModuleCatalog::findModule (1);
    check (first != nullptr && first->implemented, "module 1 is implemented (anchor)");

    // (c) an implemented module carries content and exercises, and is found.
    for (const auto& m : modules)
        if (m.implemented)
        {
            check (! m.lessons.empty(),
                   juce::String ("implemented module ") + juce::String (m.number) + " has lessons");
            check (! m.exercises.empty(),
                   juce::String ("implemented module ") + juce::String (m.number) + " has exercises");
            const auto* found = ModuleCatalog::findModule (m.number);
            check (found != nullptr && found->implemented,
                   juce::String ("findModule(") + juce::String (m.number)
                       + ") returns the implemented module");
        }
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

    // The catalog shape is checked generically (see checkModuleCatalogShape):
    // it holds for any set of implemented Etapas, so the parallel module
    // branches do not conflict (AGENTS.md §4.1).
    checkModuleCatalogShape (modules);

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

    // The student can erase their data (docs/DATA.md): clearProgress() must wipe
    // every row of this student and leave the other students untouched.
    check (scoped.clearProgress(), "clearProgress wipes the student's rows");
    check (scoped.loadHighestPassedModule() == -1, "the progress record is gone");
    check (scoped.loadExerciseResult ("gate-1") == -1, "the exercise result is gone");
    check (scoped.loadExerciseResults().empty(), "no exercise result survives the wipe");
    check (scoped.clearProgress(), "clearing an already empty record is fine");

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

        // Regression: the mirror must not resurrect the erased record. A reset
        // also wipes the database rows, and until that wipe lands the background
        // reconcile is blocked; otherwise it would raise highestPassedModule back
        // from the stale remote row (this made the suite flaky in CI, where a
        // real PostgreSQL is present).
        if (reopened.isRemoteConfigured())
        {
            juce::Thread::sleep (2500);
            check (reopened.getHighestPassedModule() == 0,
                   "the mirror does not restore the erased record");
        }
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
    // the same topic against module 1 must list its exercises. The placeholder
    // is found dynamically so the parallel module branches do not conflict.
    const CourseModule* placeholder = nullptr;
    for (const auto& m : ModuleCatalog::getModules())
        if (! m.implemented)
        {
            placeholder = &m;
            break;
        }

    const juce::String topicC = "C";
    const auto inM1 = exercisesForTopic (*m1, topicC);

    check (! inM1.empty(), "module 1's topic C has exercises");
    if (placeholder != nullptr)
        check (exercisesForTopic (*placeholder, topicC).empty(),
               "a placeholder module has no exercises for topic C");

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

    // Regression (client bug 2026-11-16): the scan walked the whole computer
    // because it always added the format's default locations on top of the
    // selected folders. Once a configured folder exists, it must be the *only*
    // thing searched; the defaults apply only when nothing is configured.
    const auto existingFolder = juce::File::getSpecialLocation (juce::File::tempDirectory);
    const auto missingFolder = existingFolder.getChildFile ("cursomusica_pasta_inexistente_xyz");

    juce::FileSearchPath defaults;
    defaults.add (existingFolder.getChildFile ("vst3_defaults"));

    PluginSearchPaths onlyStale;
    onlyStale.add (missingFolder.getFullPathName());
    check (onlyStale.resolveExisting().getNumPaths() == 0, "a stale entry is not searched");
    check (onlyStale.resolveScanFolders (defaults).getNumPaths() == defaults.getNumPaths(),
           "with no usable folder the scan falls back to the default locations");

    PluginSearchPaths configured;
    configured.add (existingFolder.getFullPathName());
    const auto scan = configured.resolveScanFolders (defaults);
    check (scan.getNumPaths() == 1, "a configured folder replaces the default locations");
    check (scan[0] == existingFolder, "the scan searches the configured folder");
    bool defaultPresent = false;
    for (int i = 0; i < scan.getNumPaths(); ++i)
        if (scan[i] == defaults[0])
            defaultPresent = true;
    check (! defaultPresent, "the default locations are not searched once a folder is configured");

    PluginSearchPaths mixed;
    mixed.add (missingFolder.getFullPathName());
    mixed.add (existingFolder.getFullPathName());
    check (mixed.resolveScanFolders (defaults).getNumPaths() == 1,
           "only the folders that exist are searched");
}

// The upper panel must stop offering a plugin once it is in the input chain
// (client bug 2026-11-16: "Add input chain" left the plugin in both panels).
// The scan stores the .vst3 bundle path while the running instance reports the
// inner binary path, so createIdentifierString() differs between the two; the
// stable key (format + name + unique id) is what makes the two agree.
void testPluginChainModel()
{
    std::cout << "PluginChainModel\n";
    using cursomusica::audio::pluginchain::selectableIndices;
    using cursomusica::audio::pluginchain::stableKey;

    // Same plugin, two paths: scanned description vs running instance.
    const auto scannedKey = stableKey ("VST3", "CursoMusica Test Plugin", 96035362, 0);
    const auto instanceKey = stableKey ("VST3", "CursoMusica Test Plugin", 96035362, 0);
    check (scannedKey == instanceKey,
           "the stable key ignores the path, so scan and instance agree");

    const std::vector<juce::String> available {
        stableKey ("VST3", "Amp", 111, 0),
        stableKey ("VST3", "CursoMusica Test Plugin", 96035362, 0),
        stableKey ("VST3", "Reverb", 222, 0),
    };

    // Nothing chained: every plugin is offered.
    check (selectableIndices (available, {}).size() == 3,
           "with an empty chain every plugin is selectable");

    // One chained: it leaves the upper panel, the others stay, order preserved.
    const auto afterAdd = selectableIndices (available, { instanceKey });
    check (afterAdd.size() == 2, "the chained plugin leaves the upper panel");
    check (afterAdd[0] == 0 && afterAdd[1] == 2, "the remaining plugins keep their order");

    // Removing it puts it back.
    check (selectableIndices (available, {}).size() == 3,
           "removing the plugin from the chain offers it again");

    // Blank keys (a description with no identity) are never offered.
    check (selectableIndices ({ "", "x" }, {}).size() == 1,
           "a blank key is not selectable");
}

// Regression for the crash that closed the app when any topic of modules 2..10
// was opened (client bug 2026-11-16): the central pane kept two parallel arrays
// for the "Ouvir exemplo" buttons — the rectangles and the notes each plays —
// and grew only the first one, so writing the notes list ran past its end and
// corrupted the heap. ensurePairedSlots keeps them the same length.
void testPairedSlots()
{
    std::cout << "PairedSlots (audio button bookkeeping)\n";
    using cursomusica::ui::ensurePairedSlots;

    std::vector<int> slots;
    std::vector<std::vector<int>> payloads;

    ensurePairedSlots (slots, payloads, 0);
    check (slots.size() == 1 && payloads.size() == 1,
           "the first button grows both lists to one slot");

    // The old code only grew `slots`; indexing payloads[3] would then be
    // out of bounds. Both must reach the requested index together.
    ensurePairedSlots (slots, payloads, 3);
    check (slots.size() == 4, "the rectangle list reaches the requested index");
    check (payloads.size() == 4, "the notes list reaches the requested index too");
    check (payloads[3].empty(), "a freshly grown notes slot is empty, not garbage");

    // Writing at the last valid index of both lists is now safe.
    payloads[3] = { 60, 64, 67 };
    check (payloads[3].size() == 3, "the notes of the last button can be stored");

    // A later, smaller index must not shrink the lists (they are indexed by the
    // paint order, which can revisit an earlier button).
    ensurePairedSlots (slots, payloads, 1);
    check (slots.size() == 4 && payloads.size() == 4, "an earlier index does not shrink the lists");
}

// The tuner's signal path in isolation: the YIN detector must turn a known tone
// into the matching frequency and must report nothing for silence. This is the
// half of the "tuner shows no signal" bug that lives outside the audio device:
// even with the callback registered, a detector that never locks would leave the
// needle at "no signal".
void testPitchDetector()
{
    std::cout << "PitchDetector (tuner signal path)\n";

    constexpr double sampleRate = 48000.0;

    auto tone = [] (double frequency, double rate, int samples)
    {
        std::vector<float> data ((size_t) samples);
        for (int i = 0; i < samples; ++i)
            data[(size_t) i] = (float) (0.5 * std::sin (2.0 * juce::MathConstants<double>::pi
                                                        * frequency * (double) i / rate));
        return data;
    };

    cursomusica::PitchDetector detector;
    detector.prepare (sampleRate);

    const auto a2 = tone (110.0, sampleRate, 8192);
    float detected = 0.0f;
    for (int offset = 0; offset + 1024 <= (int) a2.size(); offset += 1024)
        detected = detector.processBlock (a2.data() + offset, 1024);

    check (detected > 0.0f, "a played tone is detected (not silence)");
    check (std::abs (detected - 110.0f) < 2.0f,
           "A2 (110 Hz) is reported within 2 Hz, got " + juce::String (detected, 1) + " Hz");

    const auto e4 = tone (329.63, sampleRate, 8192);
    for (int offset = 0; offset + 1024 <= (int) e4.size(); offset += 1024)
        detected = detector.processBlock (e4.data() + offset, 1024);
    check (std::abs (detected - 329.63f) < 3.0f,
           "E4 (329.63 Hz) is reported within 3 Hz, got " + juce::String (detected, 1) + " Hz");

    // Silence must not be reported as a pitch (the "no signal" state).
    std::vector<float> silence (4096, 0.0f);
    float silentReading = 0.0f;
    for (int offset = 0; offset + 1024 <= (int) silence.size(); offset += 1024)
        silentReading = detector.processBlock (silence.data() + offset, 1024);
    check (silentReading <= 0.0f, "silence is reported as no pitch (0 Hz)");
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

    // The catalog shape is asserted generically by checkModuleCatalogShape(),
    // called from testModuleCatalog(), so this test does not pin which later
    // modules exist (AGENTS.md §4.1).
    checkModuleCatalogShape (ModuleCatalog::getModules());
}

// Module 3 — Etapa 3: ritmo, leitura e levadas. It must follow the same shape as
// module 2: explanation (>=5 pages per topic) with images, audio and scores,
// 3..5 exercises per topic, and part of the exercises played on the instrument.
// This is the most rhythmic module of the level, so the playable exercises are
// graded on the metronome grid (usesGrid = true, REQ-015).
void testModule3()
{
    std::cout << "Module3\n";
    using namespace cursomusica;

    const auto* m3 = ModuleCatalog::findModule (3);
    check (m3 != nullptr, "module 3 exists");
    if (m3 == nullptr)
        return;

    check (m3->implemented, "module 3 is implemented");
    check (m3->number == 3, "module 3 has number 3");
    check (m3->usesTempo, "module 3 uses a BPM target");
    check (m3->targetBpm == 68, "module 3 target BPM is 68 (MUSIC.md)");
    checkClose (m3->onGridTarget, 0.77, 0.001, "module 3 on-grid target is 0.77 (MUSIC.md)");
    check (m3->level == 2, "module 3 is level 2 (vamps de 2 acordes, MUSIC.md)");
    check (m3->lessons.size() == 8, "module 3 has eight topics (A..H)");
    check (m3->exercises.size() >= 24, "module 3 lists a full exercise set");

    // Every topic A..H has 3..5 exercises (client: "de 3 a 5 exercícios por tópico").
    for (const auto& topic : m3->lessons)
    {
        int count = 0;
        for (const auto& e : m3->exercises)
            if (e.lessonId == topic.id)
                ++count;
        check (count >= 3, juce::String ("topic ") + topic.id + " has at least three exercises");
        check (count <= 5, juce::String ("topic ") + topic.id + " has at most five exercises");
    }

    // Every exercise is tied to a topic and its id follows EX-3.<topico>.<n>.
    for (const auto& e : m3->exercises)
    {
        check (e.lessonId.isNotEmpty(), "exercise " + e.id + " is tied to a topic");
        if (! e.isGate)
            check (e.id.startsWith ("EX-3."), "exercise " + e.id + " follows EX-3.<topico>.<n>");
    }

    // Part of the exercises is played on the instrument and verified by the
    // detector (client request): every topic needs at least one exercise that is
    // really played — a quiz alone does not satisfy this. A separate check below
    // covers the broader "has a playable exercise" notion.
    juce::StringArray playedTopics;
    juce::StringArray playableTopics;
    for (const auto& e : m3->exercises)
    {
        if (e.lessonId.isEmpty())
            continue;

        const bool played = ! e.targets.empty() || ! e.chordPitchClasses.empty()
                                || ! e.chordProgression.empty();
        if (played && ! playedTopics.contains (e.lessonId))
            playedTopics.add (e.lessonId);

        const bool playable = played || e.isQuiz();
        if (playable && ! playableTopics.contains (e.lessonId))
            playableTopics.add (e.lessonId);
    }
    for (const auto& topic : { "A", "B", "C", "D", "E", "F", "G", "H" })
    {
        check (playedTopics.contains (topic),
               juce::String ("topic ") + topic + " has an exercise played on the instrument");
        check (playableTopics.contains (topic),
               juce::String ("topic ") + topic + " has a playable exercise");
    }

    // The rhythmic module grades its playable exercises on the grid (REQ-015):
    // every playable non-quiz exercise keeps usesGrid = true, and carries a spec
    // the evaluator understands (targets, a chord or a chord progression).
    int gridExercises = 0;
    for (const auto& e : m3->exercises)
    {
        if (e.isQuiz() || e.isGate)
            continue;

        const bool playable = ! e.targets.empty() || ! e.chordPitchClasses.empty()
                                || ! e.chordProgression.empty();
        if (! playable)
            continue;

        check (e.usesGrid, "playable exercise " + e.id + " is graded on the grid");
        ++gridExercises;
    }
    check (gridExercises >= 8, "module 3 has several grid-graded playable exercises");

    // Every quiz question has a valid answer key.
    for (const auto& e : m3->exercises)
        for (const auto& q : e.quiz)
            check (q.correctIndex >= 0 && q.correctIndex < q.options.size(),
                   "quiz question of " + e.id + " has a valid answer key");

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
    for (const auto& topic : m3->lessons)
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
    check (anyAudio, "module 3 demonstrates the rhythm with audio (REQ-004)");
    check (anyScore, "module 3 has scores with their audio (REQ-004)");

    // Every diagram and score named by the content is embedded in the binary,
    // and every audio/score item actually carries notes to play.
    for (const auto& topic : m3->lessons)
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

    // The rhythmic cells the metronome shows (REQ-015): the counting syllables.
    check (m3->rhythm.size() >= 3, "module 3 teaches the counting cells (REQ-015)");
    check (m3->rhythm.front().syllable == juce::String::fromUTF8 ("TÁ"),
           "module 3 quarter-note cell is counted TÁ");

    // The module cites >=1 pattern and >=1 guitarist (REQ-007, REQ-010).
    check (m3->practice.patternId.isNotEmpty(), "module 3 cites a pattern");
    check (! m3->practice.guitarists.isEmpty(), "module 3 cites at least one guitarist");
    check (m3->sources.size() >= 1, "module 3 cites its curated apostilas (REQ-006)");

    // The gate closes the module as a two-chord vamp on the grid (REQ-009).
    bool hasGate = false;
    for (const auto& e : m3->exercises)
        if (e.isGate)
        {
            hasGate = true;
            check (e.chordProgression.size() == 4, "module 3 gate has four chords");
            check (e.chordProgression.front() == std::vector<int> ({ 0, 4, 7 }),
                   "module 3 gate opens on C major");
        }
    check (hasGate, "module 3 has a gate exercise");
}

void testModule4()
{
    std::cout << "Module4\n";
    using namespace cursomusica;

    const auto* m4 = ModuleCatalog::findModule (4);
    check (m4 != nullptr, "module 4 exists");
    if (m4 == nullptr)
        return;

    check (m4->implemented, "module 4 is implemented");
    check (m4->number == 4, "module 4 has number 4");
    check (m4->usesTempo, "module 4 uses a BPM target");
    check (m4->targetBpm == 72, "module 4 target BPM is 72 (MUSIC.md)");
    check (m4->level == 2, "module 4 is level 2 (MUSIC.md)");
    check (m4->title == juce::String::fromUTF8 ("Construção de acordes: tríades e tétrades"),
           "module 4 carries the Etapa 4 title");
    check (m4->lessons.size() == 9, "module 4 has nine topics (A..I)");
    check (m4->lessons.front().id == "A" && m4->lessons.back().id == "I",
           "module 4 blocks run A..I in order");

    // Every topic A..I has 3..5 exercises (client: "de 3 a 5 exercícios por tópico").
    for (const auto& topic : m4->lessons)
    {
        int count = 0;
        for (const auto& e : m4->exercises)
            if (e.lessonId == topic.id)
                ++count;
        check (count >= 3, juce::String ("topic ") + topic.id + " has at least three exercises");
        check (count <= 5, juce::String ("topic ") + topic.id + " has at most five exercises");
    }

    // Every exercise is tied to a topic and its id follows EX-4.<topico>.<n>,
    // numbered in order per topic.
    for (const auto& e : m4->exercises)
    {
        check (e.lessonId.isNotEmpty(), "exercise " + e.id + " is tied to a topic");
        if (! e.isGate)
            check (e.id.startsWith ("EX-4."), "exercise " + e.id + " follows EX-4.<topico>.<n>");
    }
    for (const auto& topic : m4->lessons)
    {
        const auto prefix = juce::String ("EX-4.") + topic.id + ".";
        int expected = 0;
        for (const auto& e : m4->exercises)
            if (e.lessonId == topic.id && ! e.isGate)
            {
                ++expected;
                check (e.id == prefix + juce::String (expected),
                       juce::String ("exercise ids of topic ") + topic.id
                           + " are numbered in order (" + e.id + ")");
            }
    }

    // Part of the exercises is played on the instrument and verified by the
    // detector: every topic owns at least one playable exercise (a chord the app
    // recognises by pitch classes, an interval it measures, or a quiz).
    for (const auto& topic : m4->lessons)
    {
        bool playable = false;
        for (const auto& e : m4->exercises)
            if (e.lessonId == topic.id)
                playable = playable || e.isQuiz() || ! e.chordPitchClasses.empty()
                            || e.interval.semitones > 0 || ! e.targets.empty()
                            || ! e.chordProgression.empty();
        check (playable, juce::String ("topic ") + topic.id + " has at least one executable exercise");
    }

    // At least one chord exercise per topic is verified by the detector (the app
    // recognises the notes of the chord, accepting any position on the neck).
    juce::StringArray chordTopics;
    for (const auto& e : m4->exercises)
        if (! e.chordPitchClasses.empty() && e.lessonId.isNotEmpty())
            chordTopics.addIfNotAlreadyThere (e.lessonId);
    for (const auto& topic : { "A", "B", "C", "D", "E", "F", "G", "H", "I" })
        check (chordTopics.contains (topic),
               juce::String ("topic ") + topic + " has a chord exercise recognised by the app");

    // A chord exercise must not gate on the grid, and its pitch classes are valid.
    for (const auto& e : m4->exercises)
        if (! e.chordPitchClasses.empty())
        {
            check (! e.usesGrid, "chord exercise " + e.id + " is not grid-gated");
            check (e.chordPitchClasses.size() >= 3,
                   "chord exercise " + e.id + " asks for at least three notes");
            for (const int pc : e.chordPitchClasses)
                check (pc >= 0 && pc <= 11,
                       "chord exercise " + e.id + " uses a valid pitch class");
        }

    // An interval exercise must not gate on the grid and must be valid.
    for (const auto& e : m4->exercises)
        if (e.interval.semitones > 0)
        {
            check (! e.usesGrid, "interval exercise " + e.id + " is not grid-gated");
            check (e.interval.repeats >= 1, "interval exercise " + e.id + " asks for at least one repeat");
            check (e.interval.semitones >= 1 && e.interval.semitones <= 12,
                   "interval exercise " + e.id + " has a valid semitone distance");
        }

    // Explanation: >=5 pages per topic, at least one table and one image, and the
    // media the client asked for (images, audio, scores with audio).
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
    for (const auto& topic : m4->lessons)
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
    check (anyAudio, "module 4 demonstrates chords with audio (REQ-004)");
    check (anyScore, "module 4 has scores with their audio (REQ-004)");

    // Every diagram and score named by the content is embedded in the binary,
    // and every audio/score item actually carries notes to play (a score without
    // its audio is a defect).
    for (const auto& topic : m4->lessons)
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

    // The module cites >=1 pattern and >=1 guitarist (REQ-007, REQ-010) and the
    // curated apostilas (REQ-006).
    check (m4->practice.patternId.isNotEmpty(), "module 4 cites a pattern");
    check (! m4->practice.guitarists.isEmpty(), "module 4 cites at least one guitarist");
    check (m4->sources.size() >= 3, "module 4 cites its curated apostilas");

    // The gate closes the module as a I–vi–IV–V vamp on the grid (REQ-009).
    bool hasGate = false;
    for (const auto& e : m4->exercises)
        if (e.isGate)
        {
            hasGate = true;
            check (e.chordProgression.size() == 4, "module 4 gate has four chords");
            check (e.chordProgression.front() == std::vector<int> ({ 0, 4, 7 }),
                   "module 4 gate opens on C major");
            check (e.chordProgression[1] == std::vector<int> ({ 9, 0, 4 }),
                   "module 4 gate moves to A minor");
        }
    check (hasGate, "module 4 has a gate exercise");

    // The score `m4_partitura_familia` shows the major triad and then the two
    // notes that move down to turn it into the diminished triad (Dó–Mi–Sol →
    // Dó–Mi♭–Sol♭). Its audio must match the image note for note: pitch classes
    // 0, 4, 7 (major) then 3, 6 (the diminished third and fifth). The visual
    // side is guaranteed by the single definition of the score in
    // tools/make_diagrams.py, which draws exactly these notes; this check
    // guards the audio that the app actually plays against that definition.
    for (const auto& topic : m4->lessons)
        for (const auto& item : topic.detail)
            if (item.kind == ContentKind::score && item.imageName == "m4_partitura_familia")
            {
                std::vector<int> pcs;
                for (const int m : item.notes)
                    pcs.push_back (m % 12);
                check (pcs == std::vector<int> ({ 0, 4, 7, 3, 6 }),
                       "family score audio matches the image (Dó–Mi–Sol → Mi♭–Sol♭)");
            }
}

// Module 5 — Etapa 5: campo harmônico maior e funções harmônicas. It must follow
// the same shape as module 2: explanation (>=5 pages per topic) with images,
// audio and scores, 3..5 exercises per topic, and part of the exercises played
// on the instrument and verified by the app (chords, scale notes or a
// progression).
void testModule5()
{
    std::cout << "Module5\n";
    using namespace cursomusica;

    const auto* m5 = ModuleCatalog::findModule (5);
    check (m5 != nullptr, "module 5 exists");
    if (m5 == nullptr)
        return;

    check (m5->implemented, "module 5 is implemented");
    check (m5->number == 5, "module 5 has number 5");
    check (m5->usesTempo, "module 5 uses a BPM target");
    check (m5->level == 3, "module 5 is level 3 (MUSIC.md)");
    check (m5->targetBpm == 76, "module 5 target BPM is 76 (MUSIC.md)");
    checkClose (m5->onGridTarget, 0.79, 1e-6, "module 5 on-grid target is 0.79 (MUSIC.md)");
    check (m5->lessons.size() == 10, "module 5 has ten topics (A..J)");
    check (m5->lessons.front().id == "A" && m5->lessons.back().id == "J",
           "module 5 topics run A..J in order");
    check (m5->exercises.size() >= 30, "module 5 lists a full exercise set");

    // Every topic A..J has 3..5 exercises (client: "de 3 a 5 exercícios por tópico").
    for (const auto& topic : m5->lessons)
    {
        int count = 0;
        for (const auto& e : m5->exercises)
            if (e.lessonId == topic.id)
                ++count;
        check (count >= 3, juce::String ("topic ") + topic.id + " has at least three exercises");
        check (count <= 5, juce::String ("topic ") + topic.id + " has at most five exercises");
    }

    // Every exercise is tied to a topic and its id follows EX-5.<topico>.<n>.
    for (const auto& e : m5->exercises)
    {
        check (e.lessonId.isNotEmpty(), "exercise " + e.id + " is tied to a topic");
        if (! e.isGate)
            check (e.id.startsWith ("EX-5."), "exercise " + e.id + " follows EX-5.<topico>.<n>");
    }

    // Part of the exercises is played on the instrument and verified by the
    // detector: at least one playable exercise per topic (client request).
    juce::StringArray playableTopics;
    for (const auto& e : m5->exercises)
    {
        const bool playable = e.isQuiz() || ! e.targets.empty() || ! e.chordPitchClasses.empty()
                                || ! e.chordProgression.empty();
        if (playable && e.lessonId.isNotEmpty() && ! playableTopics.contains (e.lessonId))
            playableTopics.add (e.lessonId);
    }
    for (const auto& topic : m5->lessons)
        check (playableTopics.contains (topic.id),
               juce::String ("topic ") + topic.id + " has a playable exercise");

    // At least one exercise per topic is played on the instrument (chords, notes
    // or a progression the app recognises) — not only a quiz.
    juce::StringArray instrumentTopics;
    for (const auto& e : m5->exercises)
        if (! e.targets.empty() || ! e.chordPitchClasses.empty() || ! e.chordProgression.empty())
            instrumentTopics.addIfNotAlreadyThere (e.lessonId);
    for (const auto& topic : { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" })
        check (instrumentTopics.contains (topic),
               juce::String ("topic ") + topic + " has an instrument-played exercise");

    // The playable identification exercises must not gate on the grid, and the
    // app must be able to verify them (chord/notes in a valid MIDI range).
    for (const auto& e : m5->exercises)
    {
        if (! e.targets.empty() || ! e.chordPitchClasses.empty())
        {
            check (! e.usesGrid, "identification exercise " + e.id + " is not grid-gated");
            for (const auto& t : e.targets)
                check (t.midi >= 0 && t.midi <= 127,
                       "exercise " + e.id + " uses a valid MIDI note");
            for (const int pc : e.chordPitchClasses)
                check (pc >= 0 && pc <= 11,
                       "exercise " + e.id + " uses a valid pitch class");
        }
        if (! e.chordProgression.empty())
        {
            // The gate is played on the metronome grid; the identification
            // progression exercises (EX-5.H.2/EX-5.J.2) are not.
            check (e.usesGrid == e.isGate,
                   "progression exercise " + e.id + " grid flag matches its gate role");
            for (const auto& chord : e.chordProgression)
                check (chord.size() >= 3, "exercise " + e.id + " chords have at least three notes");
        }
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
    for (const auto& topic : m5->lessons)
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
    check (anyAudio, "module 5 demonstrates the field with audio (REQ-004)");
    check (anyScore, "module 5 has scores with their audio (REQ-004)");

    // Every diagram and score named by the content is embedded in the binary,
    // and every audio/score item actually carries notes to play.
    for (const auto& topic : m5->lessons)
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
    check (m5->practice.patternId.isNotEmpty(), "module 5 cites a pattern");
    check (! m5->practice.guitarists.isEmpty(), "module 5 cites at least one guitarist");
    check (! m5->sources.isEmpty(), "module 5 cites its curated apostilas");

    // The quiz answers must not all sit on the same option, otherwise the
    // exercise could be passed by always ticking the first alternative and the
    // 90% gate would not measure learning (client request). Every answer index
    // used by any question must appear, and none may dominate the set.
    {
        std::map<int, int> answerCounts;
        int totalQuestions = 0;
        for (const auto& e : m5->exercises)
            for (const auto& q : e.quiz)
            {
                check (q.correctIndex >= 0 && q.correctIndex < q.options.size(),
                       "question '" + q.prompt.substring (0, 32) + "…' has a valid correct index");
                ++answerCounts[q.correctIndex];
                ++totalQuestions;
            }

        check (totalQuestions >= 50, "module 5 has a substantial question set");
        check (answerCounts.size() >= 3,
               "module 5 quiz answers are spread over at least three options");
        for (const auto& entry : answerCounts)
            check (entry.second < totalQuestions,
                   "no single option holds every answer of module 5");
        // The correct option must not always be the first one.
        const int firstOptionAnswers = answerCounts.count (0) > 0 ? answerCounts.at (0) : 0;
        check (firstOptionAnswers < totalQuestions,
               "module 5 does not put every answer on the first option");
    }

    // The gate closes the module as a I–IV–V–I progression of the harmonic field
    // on the grid (REQ-009).
    bool hasGate = false;
    for (const auto& e : m5->exercises)
        if (e.isGate)
        {
            hasGate = true;
            check (e.usesGrid, "module 5 gate is played on the metronome grid");
            check (e.chordProgression.size() == 4, "module 5 gate has four chords");
            check (e.chordProgression.front() == std::vector<int> ({ 0, 4, 7 }),
                   "module 5 gate opens on the tonic (C major)");
            check (e.chordProgression.back() == std::vector<int> ({ 0, 4, 7 }),
                   "module 5 gate closes on the tonic (C major)");
        }
    check (hasGate, "module 5 has a gate exercise");

    // The catalog shape (unique numbers, contiguous implementations, content in
    // every implemented module) is asserted generically by
    // checkModuleCatalogShape(), called from testModuleCatalog().
}

// A playable example is coherent when its notes really are what its caption
// declares: every chord named in the caption is a subset of the notes played,
// and every note belongs to the scale named in the caption. This catches the
// class of defect the review panel found (a score whose audio played F7 while
// the caption said Fm7, a mode whose audio had the wrong seventh).
namespace
{
    struct NamedChord { juce::String symbol; int root; std::vector<int> pitchClasses; };

    int pitchClassOfLetter (juce::juce_wchar c)
    {
        switch (c)
        {
            case 'C': return 0;  case 'D': return 2;  case 'E': return 4;
            case 'F': return 5;  case 'G': return 7;  case 'A': return 9;
            case 'B': return 11; default: return -1;
        }
    }

    bool isAsciiLetter (juce::juce_wchar c)
    {
        return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
    }

    // Chord qualities used across the course, longest symbol first so that
    // "m7(b5)" is matched before "m7" and "maj7" before "m".
    const std::vector<std::pair<juce::String, std::vector<int>>>& chordQualities()
    {
        static const std::vector<std::pair<juce::String, std::vector<int>>> qualities = {
            { "m7(b5)", { 0, 3, 6, 10 } }, { "maj7", { 0, 4, 7, 11 } },
            { "m7M",   { 0, 3, 7, 11 } },  { "dim7", { 0, 3, 6, 9 } },
            { "sus4",  { 0, 5, 7 } },      { "sus2", { 0, 2, 7 } },
            { "add9",  { 0, 2, 4, 7 } },   { "aug",  { 0, 4, 8 } },
            { "7M",    { 0, 4, 7, 11 } },  { "dim",  { 0, 3, 6 } },
            { "m7",    { 0, 3, 7, 10 } },  { "m",    { 0, 3, 7 } },
            { "7",     { 0, 4, 7, 10 } },  { "6",    { 0, 4, 7, 9 } },
        };
        return qualities;
    }

    std::vector<NamedChord> declaredChords (const juce::String& caption)
    {
        std::vector<NamedChord> out;
        for (int i = 0; i < caption.length(); ++i)
        {
            const auto c = caption[i];
            const int rootPc = pitchClassOfLetter (c);
            if (rootPc < 0)
                continue;
            if (i > 0 && isAsciiLetter (caption[i - 1]))
                continue;

            int j = i + 1;
            int root = rootPc;
            if (j < caption.length() && (caption[j] == '#' || caption[j] == 'b'))
            {
                root += (caption[j] == '#') ? 1 : -1;
                ++j;
            }

            for (const auto& q : chordQualities())
            {
                const auto& suffix = q.first;
                if (caption.substring (j, j + suffix.length()) != suffix)
                    continue;
                const int end = j + suffix.length();
                if (end < caption.length() && isAsciiLetter (caption[end]))
                    break;

                NamedChord chord;
                chord.symbol = caption.substring (i, end);
                chord.root = ((root % 12) + 12) % 12;
                for (const int interval : q.second)
                    chord.pitchClasses.push_back ((chord.root + interval) % 12);
                out.push_back (std::move (chord));
                i = end - 1;
                break;
            }
        }
        return out;
    }

    // Scales/modes named in captions, as pitch-class sets from the tonic. Longest
    // name first ("lidio aumentado" before "lidio").
    const std::vector<std::pair<juce::String, std::vector<int>>>& namedScales()
    {
        static const std::vector<std::pair<juce::String, std::vector<int>>> scales = {
            { "lidio aumentado",           { 0, 2, 4, 6, 8, 9, 11 } },
            { "locrio com segunda natural",{ 0, 2, 3, 5, 6, 8, 10 } },
            { "menor natural",             { 0, 2, 3, 5, 7, 8, 10 } },
            { "menor harmonica",           { 0, 2, 3, 5, 7, 8, 11 } },
            { "menor melodica",            { 0, 2, 3, 5, 7, 9, 11 } },
            { "lidio dominante",           { 0, 2, 4, 6, 7, 9, 10 } },
            { "frigio dominante",          { 0, 1, 4, 5, 7, 8, 10 } },
            { "escala alterada",           { 0, 1, 3, 4, 6, 8, 10 } },
            { "pentatonica menor",         { 0, 3, 5, 7, 10 } },
            { "mixolidio",                 { 0, 2, 4, 5, 7, 9, 10 } },
            { "dorico",                    { 0, 2, 3, 5, 7, 9, 10 } },
            { "frigio",                    { 0, 1, 3, 5, 7, 8, 10 } },
            { "lidio",                     { 0, 2, 4, 6, 7, 9, 11 } },
            { "locrio",                    { 0, 1, 3, 5, 6, 8, 10 } },
            { "jonio",                     { 0, 2, 4, 5, 7, 9, 11 } },
            { "eolio",                     { 0, 2, 3, 5, 7, 8, 10 } },
            { "escala maior",              { 0, 2, 4, 5, 7, 9, 11 } },
        };
        return scales;
    }

    juce::String foldAccents (juce::String s)
    {
        s = s.toLowerCase();
        const std::pair<const char*, const char*> replacements[] = {
            { "\xc3\xad", "i" }, { "\xc3\xb3", "o" }, { "\xc3\xb4", "o" },
            { "\xc3\xb5", "o" }, { "\xc3\xa1", "a" }, { "\xc3\xa2", "a" },
            { "\xc3\xa3", "a" }, { "\xc3\xa9", "e" }, { "\xc3\xaa", "e" },
            { "\xc3\xba", "u" }, { "\xc3\xa7", "c" },
        };
        for (const auto& r : replacements)
            s = s.replace (r.first, r.second);
        return s;
    }

    // Returns the pitch-class set of the scale named in the caption (rooted at
    // the caption's tonic implied by the first note), or empty if none is named.
    const std::pair<juce::String, std::vector<int>>* namedScale (const juce::String& caption)
    {
        const auto folded = foldAccents (caption);
        for (const auto& scale : namedScales())
            if (folded.contains (scale.first))
                return &scale;
        return nullptr;
    }
}

// Module 6 — Etapa 6: escalas menores e campos harmônicos. Same shape as module
// 2: >=5 pages per topic with images, tables, audio and scores, 3..5 exercises
// per topic, and part of the exercises played on the instrument and verified by
// the app.
void testModule6()
{
    std::cout << "Module6\n";
    using namespace cursomusica;

    const auto* m6 = ModuleCatalog::findModule (6);
    check (m6 != nullptr, "module 6 exists");
    if (m6 == nullptr)
        return;

    check (m6->implemented, "module 6 is implemented");
    check (m6->number == 6, "module 6 has number 6");
    check (m6->usesTempo, "module 6 uses a BPM target");
    check (m6->targetBpm == 80, "module 6 target BPM is 80 (MUSIC.md)");
    check (m6->level == 3, "module 6 is level 3 (MUSIC.md)");
    check (m6->lessons.size() == 9, "module 6 has nine topics (A..I)");
    check (m6->lessons.front().id == "A" && m6->lessons.back().id == "I",
           "module 6 topics run A..I in order");

    // Every topic A..I has 3..5 exercises (client: "de 3 a 5 exercícios por tópico").
    for (const auto& topic : m6->lessons)
    {
        int count = 0;
        for (const auto& e : m6->exercises)
            if (e.lessonId == topic.id)
                ++count;
        check (count >= 3, juce::String ("topic ") + topic.id + " has at least three exercises");
        check (count <= 5, juce::String ("topic ") + topic.id + " has at most five exercises");
    }

    // Every exercise is tied to a topic and its id follows EX-6.<topico>.<n>.
    for (const auto& e : m6->exercises)
    {
        check (e.lessonId.isNotEmpty(), "exercise " + e.id + " is tied to a topic");
        if (! e.isGate)
            check (e.id.startsWith ("EX-6."), "exercise " + e.id + " follows EX-6.<topico>.<n>");
    }

    // Ids are numbered in order per topic.
    for (const auto& topic : m6->lessons)
    {
        const auto prefix = juce::String ("EX-6.") + topic.id + ".";
        int expected = 0;
        for (const auto& e : m6->exercises)
            if (e.lessonId == topic.id && ! e.isGate)
            {
                ++expected;
                check (e.id == prefix + juce::String (expected),
                       juce::String ("exercise ids of topic ") + topic.id
                           + " are numbered in order (" + e.id + ")");
            }
    }

    // Part of the exercises is played on the instrument and verified by the
    // detector: at least one playable exercise per topic (quiz, interval or
    // chord), as module 1 and 2 require (client request).
    juce::StringArray playableTopics;
    for (const auto& e : m6->exercises)
    {
        const bool playable = e.isQuiz() || e.interval.semitones > 0
                                || ! e.targets.empty() || ! e.chordPitchClasses.empty()
                                || ! e.chordProgression.empty();
        if (playable && e.lessonId.isNotEmpty())
            playableTopics.addIfNotAlreadyThere (e.lessonId);
    }
    for (const auto& topic : { "A", "B", "C", "D", "E", "F", "G", "H", "I" })
        check (playableTopics.contains (topic),
               juce::String ("topic ") + topic + " has an executable exercise");

    // At least one interval exercise per topic (the app recognises the notes and
    // checks the distance, in any position of the neck).
    juce::StringArray intervalTopics;
    for (const auto& e : m6->exercises)
        if (e.interval.semitones > 0 && e.lessonId.isNotEmpty())
            intervalTopics.addIfNotAlreadyThere (e.lessonId);
    for (const auto& topic : { "A", "B", "C", "D", "E", "H", "I" })
        check (intervalTopics.contains (topic),
               juce::String ("topic ") + topic + " has a playable interval exercise");

    // An interval exercise must not gate on the grid, and the app must be able
    // to verify it.
    for (const auto& e : m6->exercises)
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
    for (const auto& topic : m6->lessons)
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
    check (anyAudio, "module 6 demonstrates the minor scales with audio (REQ-004)");
    check (anyScore, "module 6 has scores with their audio (REQ-004)");

    // Every diagram and score named by the content is embedded in the binary,
    // and every audio/score item actually carries notes to play.
    for (const auto& topic : m6->lessons)
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

                // Coherence (QA): the audio must really be what the caption says.
                // A score/audio whose caption names a chord or a scale has to
                // play those notes, so a musically wrong example fails the suite.
                std::set<int> played;
                for (const int midi : item.notes)
                    played.insert (((midi % 12) + 12) % 12);

                for (const auto& chord : declaredChords (item.text))
                {
                    if (played.count (chord.root) == 0)
                        continue; // the chord is only mentioned (e.g. a resolution target)
                    bool covered = true;
                    for (const int pc : chord.pitchClasses)
                        covered = covered && played.count (pc) > 0;
                    check (covered,
                           juce::String ("topic ") + topic.id + " plays " + chord.symbol
                               + " as its caption declares");
                }

                if (const auto* scale = namedScale (item.text))
                {
                    const int tonic = ((item.notes.front() % 12) + 12) % 12;
                    std::set<int> allowed;
                    for (const int interval : scale->second)
                        allowed.insert ((tonic + interval) % 12);
                    bool inScale = true;
                    for (const int pc : played)
                        inScale = inScale && allowed.count (pc) > 0;
                    check (inScale,
                           juce::String ("topic ") + topic.id + " plays the scale named in its caption ("
                               + scale->first + ")");

                    // Completeness (QA): the caption names the whole scale, so the
                    // example must sound every degree of it — an example that
                    // omits a degree (or, as a side effect, skips a step) is not
                    // the scale the caption declares.
                    bool complete = true;
                    for (const int pc : allowed)
                        complete = complete && played.count (pc) > 0;
                    check (complete,
                           juce::String ("topic ") + topic.id + " plays every degree of the scale named in its caption ("
                               + scale->first + ")");
                }
            }
        }

    // The module cites >=1 pattern and >=1 guitarist (REQ-007, REQ-010).
    check (m6->practice.patternId.isNotEmpty(), "module 6 cites a pattern");
    check (! m6->practice.guitarists.isEmpty(), "module 6 cites at least one guitarist");
    check (m6->sources.size() >= 1, "module 6 cites its curated apostilas");

    // The gate closes the module as a ii–V–i minor cadence on the grid (REQ-009).
    bool hasGate = false;
    for (const auto& e : m6->exercises)
        if (e.isGate)
        {
            hasGate = true;
            check (e.chordProgression.size() == 4, "module 6 gate has four chords");
            check (e.chordProgression.front() == std::vector<int> ({ 11, 2, 5, 9 }),
                   "module 6 gate opens on Bm7(b5) (ii of the minor field)");
            check (e.chordProgression.back() == std::vector<int> ({ 9, 0, 4, 7 }),
                   "module 6 gate closes on Am7 (i of the minor field)");
            check (e.usesGrid, "module 6 gate is grid-gated");
        }
    check (hasGate, "module 6 has a gate exercise");
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

// Module 8 — Etapa 8 (dominantes, cadências e substituições harmônicas). It must
// follow the same shape as module 2: explanation (>=5 pages per topic) with
// images, tables, audio and scores with audio, 3..5 exercises per topic, and
// part of the exercises played on the instrument and verified by the app.
void testModule8()
{
    std::cout << "Module8\n";
    using namespace cursomusica;

    const auto* m8 = ModuleCatalog::findModule (8);
    check (m8 != nullptr, "module 8 exists");
    if (m8 == nullptr)
        return;

    check (m8->implemented, "module 8 is implemented");
    check (m8->number == 8, "module 8 has number 8");
    check (m8->usesTempo, "module 8 uses a BPM target");
    check (m8->targetBpm == 88, "module 8 target BPM is 88 (MUSIC.md)");
    check (m8->level == 4, "module 8 is level 4 (MUSIC.md)");
    check (m8->lessons.size() == 10, "module 8 has ten topics (A..J)");
    check (m8->exercises.size() >= 30, "module 8 lists a full exercise set");

    // Every topic A..J has 3..5 exercises (client: "de 3 a 5 exercícios por tópico").
    for (const auto& topic : m8->lessons)
    {
        int count = 0;
        for (const auto& e : m8->exercises)
            if (e.lessonId == topic.id)
                ++count;
        check (count >= 3, juce::String ("topic ") + topic.id + " has at least three exercises");
        check (count <= 5, juce::String ("topic ") + topic.id + " has at most five exercises");
    }

    // Every exercise is tied to a topic and its id follows EX-8.<topico>.<n>.
    for (const auto& e : m8->exercises)
    {
        check (e.lessonId.isNotEmpty(), "exercise " + e.id + " is tied to a topic");
        if (! e.isGate)
            check (e.id.startsWith ("EX-8."), "exercise " + e.id + " follows EX-8.<topico>.<n>");
    }

    // Part of the exercises is played on the instrument and verified by the
    // detector: at least one playable exercise per topic (client request).
    // Playable = chord montage (chordPitchClasses), progression (chordProgression),
    // ordered notes (targets) or interval (interval.semitones).
    juce::StringArray playableTopics;
    for (const auto& e : m8->exercises)
        if (e.lessonId.isNotEmpty()
            && (! e.chordPitchClasses.empty() || ! e.chordProgression.empty()
                || ! e.targets.empty() || e.interval.semitones > 0))
            playableTopics.addIfNotAlreadyThere (e.lessonId);
    for (const auto& topic : { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" })
        check (playableTopics.contains (topic),
               juce::String ("topic ") + topic + " has a playable exercise");

    // The chord montage exercises carry real pitch classes and are not grid-gated;
    // every pitch class is a valid chromatic value.
    int chordMontages = 0;
    for (const auto& e : m8->exercises)
        if (! e.chordPitchClasses.empty())
        {
            ++chordMontages;
            check (! e.usesGrid, "chord exercise " + e.id + " is not grid-gated");
            for (const int pc : e.chordPitchClasses)
                check (pc >= 0 && pc <= 11, "chord exercise " + e.id + " uses a valid pitch class");
        }
    check (chordMontages >= 8, "module 8 asks the student to montage several chords");

    // The progressions carry ordered chords with valid pitch classes.
    int progressions = 0;
    for (const auto& e : m8->exercises)
        if (! e.chordProgression.empty())
        {
            ++progressions;
            check (e.chordProgression.size() >= 3, "progression " + e.id + " has at least three chords");
            for (const auto& chord : e.chordProgression)
                for (const int pc : chord)
                    check (pc >= 0 && pc <= 11, "progression " + e.id + " uses a valid pitch class");
        }
    check (progressions >= 5, "module 8 asks the student to play several progressions");

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
    for (const auto& topic : m8->lessons)
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
    check (anyAudio, "module 8 demonstrates the harmony with audio (REQ-004)");
    check (anyScore, "module 8 has scores with their audio (REQ-004)");

    // Every diagram and score named by the content is embedded in the binary,
    // and every audio/score item actually carries notes to play.
    for (const auto& topic : m8->lessons)
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

    // QA: every score must sound what it writes. The diagram is a fixed image, so
    // the only way to keep the image and the audio in sync is to pin the notes
    // each score image is allowed to carry; if the audio diverges from the
    // written score, this fails (the review caught a score whose image was a
    // II-V-I menor while the audio played FM7 -> Fm7 -> C). Pitch classes are
    // compared, not absolute octaves, because guitar music is notated an octave
    // above the sounding pitch.
    {
        auto pitchClasses = [] (const std::vector<int>& midis)
        {
            std::vector<int> pcs;
            for (const int midi : midis)
                pcs.push_back (music::pitchClassOf (midi));
            return pcs;
        };

        const std::map<juce::String, std::vector<int>> expected = {
            // arpejo de G7 (V7 de Do): G-B-D-F
            { "m8_partitura_v7",           { 7, 11, 2, 5 } },
            // arpejo de D7 (V7/V de Do): D-F#-A-C
            { "m8_partitura_v7_do_v",      { 2, 6, 9, 0 } },
            // G7 alterado (b5 e b9): G-B-Db-F-Ab
            { "m8_partitura_alterado",     { 7, 11, 1, 5, 8 } },
            // arpejo de Db7 (SubV7 de Do): Db-F-Ab-Cb(=B)
            { "m8_partitura_subv7",        { 1, 5, 8, 11 } },
            // II-V-I maior (Dm7 - G7 - CM7): D-F-A-C / G-B-D-F / C-E-G
            { "m8_partitura_ii_v_i",       { 2, 5, 9, 0, 7, 11, 2, 5, 0, 4, 7 } },
            // II-V-I menor (Dm7b5 - G7 - Cm7): D-F-Ab-C / G-B-D-F / C-Eb-G
            { "m8_partitura_ii_v_i_menor", { 2, 5, 8, 0, 7, 11, 2, 5, 0, 3, 7 } },
            // FM7 - Fm7 - C (iv menor emprestado): F-A-C-E / F-Ab-C-Eb / C-E-G
            { "m8_partitura_iv_menor",     { 5, 9, 0, 4, 5, 8, 0, 3, 0, 4, 7 } },
        };

        int scoresChecked = 0;
        for (const auto& topic : m8->lessons)
            for (const auto& item : topic.detail)
                if (item.kind == ContentKind::score)
                {
                    ++scoresChecked;
                    const auto it = expected.find (item.imageName);
                    check (it != expected.end(),
                           juce::String ("topic ") + topic.id + " score '"
                               + item.imageName + "' has a pinned expected audio");
                    if (it != expected.end())
                        check (pitchClasses (item.notes) == it->second,
                               juce::String ("topic ") + topic.id + " score '"
                                   + item.imageName + "' plays exactly what the score writes");
                }
        check (scoresChecked >= 10, "module 8 has at least one score per topic with audio");
    }

    // QA (review round 2): a theory table must agree with the scale it describes.
    // This pins the minor-field table of topic H: each chord symbol in the
    // Natural/Harmônica/Melódica columns must be the diatonic seventh chord of
    // that scale. Without it the table can teach chords that do not exist in the
    // scale it just defined (the review found Ab7M#5 / Bdim7 in the melodic
    // column). Chord symbols are parsed to pitch-class sets and compared.
    {
        using Pcs = std::vector<int>;
        auto chordPcs = [] (const juce::String& symbol) -> Pcs
        {
            const auto s = symbol.trim();
            if (s.isEmpty())
                return {};
            int pc = -1;
            switch (s[0])
            {
                case 'C': pc = 0;  break;
                case 'D': pc = 2;  break;
                case 'E': pc = 4;  break;
                case 'F': pc = 5;  break;
                case 'G': pc = 7;  break;
                case 'A': pc = 9;  break;
                case 'B': pc = 11; break;
                default: return {};
            }
            int i = 1;
            while (i < s.length())
            {
                const auto c = s[i];
                if (c == '#')      { ++pc; ++i; }
                else if (c == 'b') { --pc; ++i; }
                else break;
            }
            const auto quality = s.substring (i);
            Pcs intervals;
            if (quality == "m7M")        intervals = { 0, 3, 7, 11 };
            else if (quality == "m7")    intervals = { 0, 3, 7, 10 };
            else if (quality == "m7b5")  intervals = { 0, 3, 6, 10 };
            else if (quality == "7M#5")  intervals = { 0, 4, 8, 11 };
            else if (quality == "7M")    intervals = { 0, 4, 7, 11 };
            else if (quality == "7")     intervals = { 0, 4, 7, 10 };
            else if (quality == "dim7")  intervals = { 0, 3, 6, 9 };
            else return {};
            Pcs out;
            for (const int iv : intervals)
                out.push_back (((pc + iv) % 12 + 12) % 12);
            std::sort (out.begin(), out.end());
            return out;
        };

        // C minor: natural, harmonic and melodic scales.
        const Pcs natural  = { 0, 2, 3, 5, 7, 8, 10 };
        const Pcs harmonic = { 0, 2, 3, 5, 7, 8, 11 };
        const Pcs melodic  = { 0, 2, 3, 5, 7, 9, 11 };
        auto diatonic = [] (const Pcs& scale)
        {
            std::vector<Pcs> chords;
            for (std::size_t i = 0; i < 7; ++i)
            {
                Pcs c;
                for (const int step : { 0, 2, 4, 6 })
                    c.push_back (scale[(i + (std::size_t) step) % 7]);
                std::sort (c.begin(), c.end());
                chords.push_back (c);
            }
            return chords;
        };
        const auto natChords = diatonic (natural);
        const auto harChords = diatonic (harmonic);
        const auto melChords = diatonic (melodic);

        int minorTables = 0;
        for (const auto& topic : m8->lessons)
            for (const auto& item : topic.detail)
                if (item.kind == ContentKind::table && item.columns.size() == 4
                    && item.columns[0] == "Grau" && item.columns[1] == "Natural"
                    && item.columns[2] == "Harmônica" && item.columns[3] == "Melódica")
                {
                    ++minorTables;
                    int row = 0;
                    for (const auto& r : item.rows)
                    {
                        if (row >= 7 || r.size() < 4)
                            break;
                        const std::size_t idx = (std::size_t) row;
                        auto verify = [&] (int col, const Pcs& chord)
                        {
                            check (chordPcs (r[(std::size_t) col]) == chord,
                                   juce::String ("topic ") + topic.id + " minor-field row "
                                       + r[0] + " column " + item.columns[(std::size_t) col] + " = "
                                       + r[(std::size_t) col] + " is the diatonic seventh chord of the scale");
                        };
                        verify (1, natChords[idx]);
                        verify (2, harChords[idx]);
                        verify (3, melChords[idx]);
                        ++row;
                    }
                }
        check (minorTables >= 1, "module 8 has the minor-field comparison table");
    }

    // The module cites >=1 pattern and >=1 guitarist (REQ-007, REQ-010).
    check (m8->practice.patternId.isNotEmpty(), "module 8 cites a pattern");
    check (! m8->practice.guitarists.isEmpty(), "module 8 cites at least one guitarist");
    check (! m8->sources.isEmpty(), "module 8 cites curated sources (REQ-006)");

    // The gate closes the module as a II-V-I maior on the grid (REQ-009).
    bool hasGate = false;
    for (const auto& e : m8->exercises)
        if (e.isGate)
        {
            hasGate = true;
            check (e.chordProgression.size() == 3, "module 8 gate has three chords (II-V-I)");
            check (e.chordProgression.front() == std::vector<int> ({ 2, 5, 9, 0 }),
                   "module 8 gate opens on Dm7 (ii)");
            check (e.chordProgression.back() == std::vector<int> ({ 0, 4, 7, 11 }),
                   "module 8 gate closes on CM7 (I)");
            check (e.usesGrid, "module 8 gate is graded on the grid");
        }
    check (hasGate, "module 8 has a gate exercise");

    // End-to-end check of the gate spec: the II-V-I maior played in order, on
    // the grid, passes the evaluator (accuracy and alignment gates).
    {
        const Exercise* gate = nullptr;
        for (const auto& e : m8->exercises)
            if (e.isGate) gate = &e;
        check (gate != nullptr, "module 8 gate exercise is available");

        if (gate != nullptr)
        {
            course::PracticeSession session;
            session.start (*gate, m8->targetBpm, m8->onGridTarget);
            const double beat = 60.0 / (double) m8->targetBpm;
            session.consume ({
                { 0.0 * beat, 50, 0.0f }, { 0.0 * beat, 53, 0.0f },   // Dm7: D F A C
                { 0.0 * beat, 57, 0.0f }, { 0.0 * beat, 60, 0.0f },
                { 1.0 * beat, 55, 0.0f }, { 1.0 * beat, 59, 0.0f },   // G7: G B D F
                { 1.0 * beat, 62, 0.0f }, { 1.0 * beat, 65, 0.0f },
                { 2.0 * beat, 60, 0.0f }, { 2.0 * beat, 64, 0.0f },   // CM7: C E G B
                { 2.0 * beat, 67, 0.0f }, { 2.0 * beat, 71, 0.0f },
            });
            session.finish();
            const auto& state = session.getState();
            check (state.matched == 3, "module 8 gate recognises the three chords in order");
            check (state.passed, "module 8 gate passes the II-V-I maior on the grid");
        }
    }
}

// Module 9 — Etapa 9: harmonia avançada e estruturas especiais. Mirrors
// testModule2: topics, 3..5 exercises per topic, id shape, >=5 pages, media
// (images, tables, audio and scores with audio), playable exercises the app
// verifies by recognising notes, and the gate on the grid.
void testModule9()
{
    std::cout << "Module9\n";
    using namespace cursomusica;

    const auto* m9 = ModuleCatalog::findModule (9);
    check (m9 != nullptr, "module 9 exists");
    if (m9 == nullptr)
        return;

    check (m9->implemented, "module 9 is implemented");
    check (m9->number == 9, "module 9 has number 9");
    check (m9->usesTempo, "module 9 uses a BPM target");
    check (m9->targetBpm == 92, "module 9 target BPM is 92 (MUSIC.md)");
    check (m9->level == 4, "module 9 is level 4 (MUSIC.md)");
    check (m9->lessons.size() == 9, "module 9 has nine topics (A..I)");
    check (m9->lessons.front().id == "A" && m9->lessons.back().id == "I",
           "module 9 topics run A..I in order");
    check (m9->exercises.size() >= 27, "module 9 lists a full exercise set");

    // Every topic A..I has 3..5 exercises (client: "de 3 a 5 exercícios por tópico").
    for (const auto& topic : m9->lessons)
    {
        int count = 0;
        for (const auto& e : m9->exercises)
            if (e.lessonId == topic.id)
                ++count;
        check (count >= 3, juce::String ("topic ") + topic.id + " has at least three exercises");
        check (count <= 5, juce::String ("topic ") + topic.id + " has at most five exercises");
    }

    // Every exercise is tied to a topic and its id follows EX-9.<topico>.<n>.
    for (const auto& e : m9->exercises)
    {
        check (e.lessonId.isNotEmpty(), "exercise " + e.id + " is tied to a topic");
        if (! e.isGate)
            check (e.id.startsWith ("EX-9."), "exercise " + e.id + " follows EX-9.<topico>.<n>");
    }

    // Part of the exercises is played on the instrument and verified by the
    // detector: every topic owns at least one playable exercise (quiz, chord,
    // progression or interval the evaluator understands).
    juce::StringArray playableTopics;
    for (const auto& e : m9->exercises)
    {
        const bool playable = e.isQuiz() || ! e.targets.empty() || ! e.chordPitchClasses.empty()
                                || ! e.chordProgression.empty() || e.interval.semitones > 0;
        if (playable && e.lessonId.isNotEmpty())
            playableTopics.addIfNotAlreadyThere (e.lessonId);
    }
    for (const auto& topic : { "A", "B", "C", "D", "E", "F", "G", "H", "I" })
        check (playableTopics.contains (topic),
               juce::String ("topic ") + topic + " has a verifiable exercise");

    // An interval exercise must not gate on the grid, and its distance is valid.
    for (const auto& e : m9->exercises)
        if (e.interval.semitones > 0)
        {
            check (! e.usesGrid, "interval exercise " + e.id + " is not grid-gated");
            check (e.interval.repeats >= 1, "interval exercise " + e.id + " asks for at least one repeat");
            check (e.interval.semitones >= 1 && e.interval.semitones <= 12,
                   "interval exercise " + e.id + " has a valid semitone distance");
        }

    // Chord / progression exercises must not gate on the grid either (they are
    // recognition exercises), and they carry a spec the evaluator understands.
    for (const auto& e : m9->exercises)
        if (! e.isGate && (! e.chordPitchClasses.empty() || ! e.chordProgression.empty()))
        {
            check (! e.usesGrid, "recognition exercise " + e.id + " is not grid-gated");
            for (const int pc : e.chordPitchClasses)
                check (pc >= 0 && pc < 12, "chord exercise " + e.id + " uses a valid pitch class");
            for (const auto& chord : e.chordProgression)
                for (const int pc : chord)
                    check (pc >= 0 && pc < 12, "progression " + e.id + " uses a valid pitch class");
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
    for (const auto& topic : m9->lessons)
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
    check (anyAudio, "module 9 demonstrates the structures with audio (REQ-004)");
    check (anyScore, "module 9 has scores with their audio (REQ-004)");

    // Every diagram and score named by the content is embedded in the binary,
    // and every audio/score item actually carries notes to play.
    for (const auto& topic : m9->lessons)
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

            // A score must play exactly what its image draws (REQ-004): the notes
            // of the score item are compared with the notes the diagram tool
            // recorded for that image (Source/Course/Content/ScoreNotes.h).
            if (item.kind == ContentKind::score)
            {
                const content::scoreNotes::Entry* drawn = nullptr;
                for (const auto& e : content::scoreNotes::all())
                    if (item.imageName == e.stem)
                        drawn = &e;
                check (drawn != nullptr,
                       juce::String ("score '") + item.imageName + "' has a recorded score image");
                if (drawn != nullptr)
                    check (drawn->notes == item.notes,
                           juce::String ("score '") + item.imageName
                               + "' plays exactly the notes its image draws");
            }
        }

    // A dominant chord the content calls "7" must carry its minor seventh. D7 is
    // D-F#-A-C (2-6-9-0), never the bare triad D-F#-A (2-6-9). This is the bug
    // the panel caught: the test now pins the seventh.
    for (const auto& e : m9->exercises)
        if (e.id == "EX-9.H.3")
        {
            check (std::find (e.chordPitchClasses.begin(), e.chordPitchClasses.end(), 0)
                       != e.chordPitchClasses.end(),
                   "EX-9.H.3 (D7) includes the minor seventh (C = 0)");
            check (e.chordPitchClasses.size() == 4,
                   "EX-9.H.3 (D7) is a four-note dominant chord");
        }
    for (const auto& e : m9->exercises)
        if (e.id == "EX-9.H.2")
        {
            const auto& prog = e.chordProgression;
            check (prog.size() == 4, "EX-9.H.2 is a four-chord progression");
            check (std::find (prog[2].begin(), prog[2].end(), 0) != prog[2].end(),
                   "EX-9.H.2 secondary dominant D7 includes the minor seventh (C = 0)");
        }

    // The module cites >=1 pattern and >=1 guitarist (REQ-007, REQ-010).
    check (m9->practice.patternId.isNotEmpty(), "module 9 cites a pattern");
    check (! m9->practice.guitarists.isEmpty(), "module 9 cites at least one guitarist");
    check (m9->sources.size() >= 1, "module 9 cites its curated apostilas");

    // The gate closes the module on the grid: a turnaround built from the
    // material of the module (REQ-009).
    bool hasGate = false;
    for (const auto& e : m9->exercises)
        if (e.isGate)
        {
            hasGate = true;
            check (e.chordProgression.size() == 4, "module 9 gate has four chords");
            check (e.chordProgression.front() == std::vector<int> ({ 0, 4, 7 }),
                   "module 9 gate opens on C major");
        }
    check (hasGate, "module 9 has a gate exercise");

    // The registry shape holds with module 9 implemented.
    checkModuleCatalogShape (ModuleCatalog::getModules());
}

// Module 10 — Etapa 10 (análise harmônica, verticalização e reharmonização).
// Same shape as module 2: >=5 pages per topic with images, tables, audio and
// scores, 3..5 exercises per topic, and part of the exercises played on the
// instrument and verified by the app.
void testModule10()
{
    std::cout << "Module10\n";
    using namespace cursomusica;

    const auto* m10 = ModuleCatalog::findModule (10);
    check (m10 != nullptr, "module 10 exists");
    if (m10 == nullptr)
        return;

    check (m10->implemented, "module 10 is implemented");
    check (m10->number == 10, "module 10 has number 10");
    check (m10->usesTempo, "module 10 uses a BPM target");
    check (m10->targetBpm == 96, "module 10 target BPM is 96 (MUSIC.md)");
    check (m10->onGridTarget > 0.81f && m10->onGridTarget < 0.83f,
           "module 10 on_grid_ratio target is 0.82 (MUSIC.md)");
    check (m10->lessons.size() == 10, "module 10 has ten topics (A..J)");
    check (m10->lessons.front().id == "A" && m10->lessons.back().id == "J",
           "module 10 topics run A..J in order");
    check (m10->exercises.size() >= 30, "module 10 lists a full exercise set");

    // Every topic A..J has 3..5 exercises (client: "de 3 a 5 exercícios por tópico").
    for (const auto& topic : m10->lessons)
    {
        int count = 0;
        for (const auto& e : m10->exercises)
            if (e.lessonId == topic.id)
                ++count;
        check (count >= 3, juce::String ("topic ") + topic.id + " has at least three exercises");
        check (count <= 5, juce::String ("topic ") + topic.id + " has at most five exercises");
    }

    // Every exercise is tied to a topic and its id follows EX-10.<topico>.<n>.
    for (const auto& e : m10->exercises)
    {
        check (e.lessonId.isNotEmpty(), "exercise " + e.id + " is tied to a topic");
        if (! e.isGate)
            check (e.id.startsWith ("EX-10."), "exercise " + e.id + " follows EX-10.<topico>.<n>");
    }

    // Part of the exercises is played on the instrument and verified by the app:
    // every topic must own a playable exercise (quiz, chord spec or target).
    juce::StringArray playableTopics;
    for (const auto& e : m10->exercises)
    {
        const bool playable = e.isQuiz() || ! e.targets.empty() || ! e.chordPitchClasses.empty()
                                || ! e.chordProgression.empty();
        if (playable && e.lessonId.isNotEmpty() && ! playableTopics.contains (e.lessonId))
            playableTopics.add (e.lessonId);
    }
    for (const auto& topic : { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" })
        check (playableTopics.contains (topic),
               juce::String ("topic ") + topic + " has an executable exercise");

    // Chord-based exercises must not gate on the grid (they are about harmony,
    // not tempo), except the gate itself.
    for (const auto& e : m10->exercises)
        if ((! e.chordProgression.empty() || ! e.chordPitchClasses.empty()) && ! e.isGate)
            check (! e.usesGrid, "chord exercise " + e.id + " is not grid-gated");

    // Explanation: >=5 pages per topic, at least one table and one image, and the
    // media the client asked for (images, audio, scores with audio).
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
    for (const auto& topic : m10->lessons)
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
    check (anyAudio, "module 10 demonstrates harmony with audio (REQ-004)");
    check (anyScore, "module 10 has scores with their audio (REQ-004)");

    // Every diagram and score named by the content is embedded in the binary,
    // and every audio/score item actually carries notes to play.
    for (const auto& topic : m10->lessons)
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

    // The turnaround score must spell A7, not Am7: its audio has to contain the
    // C# (the major third of A7). Without it the printed score would teach the
    // wrong note (panel finding R2-1).
    bool foundTurnaround = false;
    for (const auto& topic : m10->lessons)
        for (const auto& item : topic.detail)
            if (item.kind == ContentKind::score
                && item.imageName == "m10_partitura_turnaround")
            {
                foundTurnaround = true;
                bool hasCSharp = false;
                for (const int midi : item.notes)
                    if (midi % 12 == 1)
                        hasCSharp = true;
                check (hasCSharp, "the turnaround score spells A7 with its C# (not Am7)");
            }
    check (foundTurnaround, "module 10 carries the turnaround score");

    // The module cites >=1 pattern and >=1 guitarist (REQ-007, REQ-010).
    check (m10->practice.patternId.isNotEmpty(), "module 10 cites a pattern");
    check (! m10->practice.guitarists.isEmpty(), "module 10 cites at least one guitarist");
    check (! m10->sources.isEmpty(), "module 10 cites its curated apostilas (REQ-006)");

    // The gate closes the module as a reharmonised ii–V–I on the grid (REQ-009).
    // Every chord is checked, not just the first and last: the tritone
    // substitution (Db7) must carry Cb (= 11), not C (= 0), or a student who
    // plays the correct chord would be failed (panel finding F1).
    const std::vector<std::vector<int>> gateChords {
        { 2, 5, 9, 0 },    // Dm7
        { 9, 1, 4, 7 },    // A7 (dominante secundário)
        { 2, 5, 9, 0 },    // Dm7
        { 1, 5, 8, 11 },   // Db7 (subV: Db–F–Ab–Cb)
        { 0, 4, 7, 11 },   // C7M (alvo)
    };
    bool hasGate = false;
    for (const auto& e : m10->exercises)
        if (e.isGate)
        {
            hasGate = true;
            check (e.chordProgression == gateChords, "module 10 gate spells every chord correctly");
            check (e.usesGrid, "module 10 gate is graded against the grid");
        }
    check (hasGate, "module 10 has a gate exercise");

    // The tritone-substitution exercises must spell Db7 with Cb (= 11). A wrong
    // spelling here would fail a student who plays the chord correctly (F1).
    int subVCount = 0;
    for (const auto& e : m10->exercises)
        for (const auto& chord : e.chordProgression)
            if (chord == std::vector<int> ({ 1, 5, 8, 11 }))
                ++subVCount;
    check (subVCount >= 4, "the Db7 (subV) is spelled correctly in every exercise");

    // No exercise may contain the mis-spelled Db7M (C instead of Cb).
    for (const auto& e : m10->exercises)
        for (const auto& chord : e.chordProgression)
            check (chord != std::vector<int> ({ 1, 5, 8, 0 }),
                   "no exercise spells Db7 as Db7M (" + e.id + ")");
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
    testPluginChainModel();
    testPairedSlots();
    testPitchDetector();
    testIntervals();
    testIntervalEvaluation();
    testModuleCatalog();
    testModule2();
    testModule3();
    testModule4();
    testModule5();
    testModule6();
    testModule7();
    testModule8();
    testModule9();
    testModule10();
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
