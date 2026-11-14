#include "UI/PracticePanel.h"

#include "Course/NoteMath.h"
#include "UI/Design/Theme.h"

namespace cursomusica
{

namespace th = cursomusica::theme;

namespace
{
    juce::String percent (double value)
    {
        return juce::String (juce::roundToInt (value * 100.0)) + "%";
    }

    juce::String percentFromInt (int value)
    {
        return juce::String (value) + "%";
    }
}

void PracticePanel::ExerciseRowButton::setExerciseText (const juce::String& newText)
{
    exerciseText = newText;
    repaint();
}

void PracticePanel::ExerciseRowButton::paintButton (juce::Graphics& g, bool highlighted, bool down)
{
    auto bounds = getLocalBounds().toFloat();

    g.setColour (th::colour::surfaceRaised.withAlpha (down ? 1.0f : (highlighted ? 0.9f : 0.7f)));
    g.fillRoundedRectangle (bounds, th::radius::sm);

    // Play glyph on the left, so the row reads as "this is the exercise to run".
    auto glyph = getLocalBounds().removeFromLeft (22);
    juce::Path triangle;
    triangle.addTriangle (0.0f, 0.0f, 0.0f, 8.0f, 8.0f, 4.0f);
    g.setColour (th::colour::accentAlt);
    g.fillPath (triangle, triangle.getTransformToScaleToFit (glyph.toFloat().withSizeKeepingCentre (10.0f, 10.0f), true));

    g.setColour (th::colour::textPrimary);
    g.setFont (th::type::makeFont (th::type::body, true));
    g.drawFittedText (exerciseText.isNotEmpty() ? exerciseText
                                                : juce::String::fromUTF8 ("Selecione um exercício"),
                      getLocalBounds().withTrimmedLeft (22).reduced (4, 0),
                      juce::Justification::centredLeft, 1);
}

PracticePanel::PracticePanel (AudioEngine& engine)
    : audioEngine (engine)
{
    headingLabel.setText (juce::String::fromUTF8 ("Exercícios práticos"), juce::dontSendNotification);
    headingLabel.setFont (th::type::makeFont (th::type::body, true));
    headingLabel.setColour (juce::Label::textColourId, th::colour::textPrimary);
    addAndMakeVisible (headingLabel);

    // Clears the topic filter, so the pane lists every exercise of the module
    // again (the "Todos os tópicos do módulo" link of the mock-up).
    topicLink.setColour (juce::HyperlinkButton::textColourId, th::colour::accentAlt);
    topicLink.setFont (th::type::makeFont (th::type::caption, false), false,
                       juce::Justification::centredRight);
    topicLink.onClick = [this]
    {
        topicFilter = {};
        topicChosen = true;
        exerciseArmed = false;
        selectedExerciseIndex = 0;
        session = {};
        quiz = {};
        previousAccuracy = -1;
        refreshExerciseList();
    };
    addAndMakeVisible (topicLink);

    topicLabel.setFont (th::type::makeFont (th::type::caption));
    topicLabel.setColour (juce::Label::textColourId, th::colour::accentAlt);
    addAndMakeVisible (topicLabel);

    exerciseBox.onChange = [this]
    {
        selectedExerciseIndex = exerciseBox.getSelectedItemIndex();
        exerciseArmed = true;   // picking an exercise is what arms it (client step 4)
        session = {};
        quiz = {};
        attemptReported = false;
        showPreviousResult();
        refreshExerciseRow();
        updateApplication();

        // Arming another exercise also demonstrates it in the centre.
        if (onExerciseSelected != nullptr)
            onExerciseSelected (selectedExercise());
    };
    addAndMakeVisible (exerciseBox);

    demoButton.onClick = [this]
    {
        if (onExerciseSelected != nullptr)
            onExerciseSelected (selectedExercise());

        // Clicking the row of a finished quiz starts it over.
        if (isQuizSelected() && quiz.getState().finished)
            restartQuiz();
    };
    addAndMakeVisible (demoButton);

    // Scoreboard: Acertos x/y · aproveitamento z%.
    measurementLabel.setFont (th::type::makeFont (th::type::caption));
    measurementLabel.setColour (juce::Label::textColourId, th::colour::textSecondary);
    measurementLabel.setJustificationType (juce::Justification::topLeft);
    addAndMakeVisible (measurementLabel);

    // Guidance box: what the student must do in the armed exercise.
    guidanceLabel.setFont (th::type::makeFont (th::type::body));
    guidanceLabel.setColour (juce::Label::textColourId, th::colour::textSecondary);
    guidanceLabel.setJustificationType (juce::Justification::topLeft);
    addAndMakeVisible (guidanceLabel);

    // Playable-exercise controls (the quiz runs in the centre pane).
    metronomeButton.onClick = [this] { toggleMetronome(); };
    addAndMakeVisible (metronomeButton);

    startButton.onClick = [this] { startSelectedExercise(); };
    addAndMakeVisible (startButton);

    finishButton.onClick = [this] { finishExercise(); };
    addAndMakeVisible (finishButton);

    bpmLabel.setFont (th::type::makeFont (th::type::caption));
    bpmLabel.setColour (juce::Label::textColourId, th::colour::textSecondary);
    addAndMakeVisible (bpmLabel);

    updateApplication();
}

PracticePanel::~PracticePanel() = default;

const course::QuizState& PracticePanel::getQuizState() const { return quiz.getState(); }

void PracticePanel::answerQuizOption (int optionIndex)
{
    if (! isQuizSelected())
        return;

    quiz.answer (optionIndex);
    updateButtonStates();
    updateFeedback();

    if (onQuizChanged != nullptr)
        onQuizChanged();
}

void PracticePanel::setModule (const CourseModule* module)
{
    currentModule = module;
    topicFilter = {};
    topicChosen = false;
    exerciseArmed = false;
    selectedExerciseIndex = 0;
    session = {};
    quiz = {};
    previousAccuracy = -1;
    attemptReported = false;
    refreshExerciseList();
    syncMetronomeFromModule();
}

void PracticePanel::setTopicFilter (const juce::String& lessonId)
{
    topicFilter = lessonId;
    topicChosen = true;
    exerciseArmed = false;
    selectedExerciseIndex = 0;
    session = {};
    quiz = {};
    previousAccuracy = -1;
    attemptReported = false;
    refreshExerciseList();
}

void PracticePanel::refreshExerciseList()
{
    exerciseBox.clear (juce::dontSendNotification);
    filteredIndices.clear();

    if (currentModule != nullptr && topicChosen)
    {
        for (int i = 0; i < (int) currentModule->exercises.size(); ++i)
        {
            const auto& e = currentModule->exercises[(size_t) i];
            if (topicFilter.isNotEmpty() && e.lessonId != topicFilter)
                continue;

            filteredIndices.push_back (i);
        }
    }

    if (currentModule != nullptr)
        for (size_t slot = 0; slot < filteredIndices.size(); ++slot)
        {
            const auto& e = currentModule->exercises[(size_t) filteredIndices[slot]];
            const bool playable = e.isQuiz() || ! e.targets.empty() || ! e.chordPitchClasses.empty()
                                    || ! e.chordProgression.empty();
            exerciseBox.addItem (e.id + " — " + e.title
                                   + (playable ? juce::String()
                                               : juce::String::fromUTF8 ("  (leitura)")),
                                 (int) slot + 1);
        }

    // The box shows the first exercise as a hint but arms nothing: arming only
    // happens when the student picks from the list (client steps 3-4). Leaving
    // no real selection is what makes picking even the first item register.
    exerciseBox.setTextWhenNothingSelected (exerciseBox.getNumItems() > 0
                                                ? exerciseBox.getItemText (0)
                                                : juce::String());
    exerciseBox.setSelectedId (0, juce::dontSendNotification);

    topicLabel.setText (topicFilter.isEmpty()
                            ? juce::String()
                            : juce::String::fromUTF8 ("Tópico ") + topicFilter,
                        juce::dontSendNotification);

    refreshExerciseRow();
    updateApplication();
    resized();
}

void PracticePanel::refreshExerciseRow()
{
    const auto* exercise = selectedExercise();
    demoButton.setExerciseText (exercise != nullptr
                                    ? exercise->id + " — " + exercise->title
                                    : juce::String());
}

void PracticePanel::syncMetronomeFromModule()
{
    if (currentModule == nullptr)
        return;

    audioEngine.getMetronome().setBpm ((double) currentModule->targetBpm);
    audioEngine.getMetronome().setRunning (metronomeOn);

    // Module 1 does not grade against a BPM target (client): it prints a dash,
    // like the module header, while later modules show the number.
    const juce::String bpm = currentModule->usesTempo ? juce::String (currentModule->targetBpm)
                                                      : juce::String::fromUTF8 ("—");
    bpmLabel.setText (juce::String::fromUTF8 ("BPM meta ") + bpm
                        + juce::String::fromUTF8 ("  ·  alvo de grade ") + percent (currentModule->onGridTarget),
                      juce::dontSendNotification);
}

void PracticePanel::showPreviousResult()
{
    previousAccuracy = -1;

    const auto* exercise = selectedExercise();
    if (exercise == nullptr || exercise->id.isEmpty())
        return;

    if (onQueryExerciseAccuracy != nullptr)
        previousAccuracy = onQueryExerciseAccuracy (exercise->id);
}

const Exercise* PracticePanel::selectedExercise() const
{
    if (currentModule == nullptr)
        return nullptr;

    const int slot = exerciseBox.getSelectedItemIndex();
    if (slot < 0 || slot >= (int) filteredIndices.size())
        return nullptr;

    return &currentModule->exercises[(size_t) filteredIndices[(size_t) slot]];
}

bool PracticePanel::isQuizSelected() const
{
    const auto* exercise = selectedExercise();
    return exercise != nullptr && exercise->isQuiz();
}

void PracticePanel::updateApplication()
{
    const auto* exercise = selectedExercise();
    const bool quizMode = exercise != nullptr && exercise->isQuiz();

    // The pane depends on the left one (client): with no topic chosen it stays
    // blank; once a topic is picked it shows the selector, but the play row and
    // the scoreboard only appear after the student arms an exercise.
    topicLabel.setVisible (topicChosen);
    exerciseBox.setVisible (topicChosen);
    topicLink.setVisible (topicChosen && topicFilter.isNotEmpty());

    demoButton.setVisible (exerciseArmed && exercise != nullptr);
    measurementLabel.setVisible (exerciseArmed && exercise != nullptr);
    guidanceLabel.setVisible (exerciseArmed && exercise != nullptr);

    // Playable-exercise controls (the quiz runs in the centre pane, which shows
    // the question and the options; this pane keeps only the scoreboard).
    const bool showPlayControls = exerciseArmed && exercise != nullptr && ! quizMode;
    metronomeButton.setVisible (showPlayControls);
    startButton.setVisible (showPlayControls);
    finishButton.setVisible (showPlayControls);
    bpmLabel.setVisible (showPlayControls);

    if (quizMode)
    {
        if (! quiz.isRunning() && ! quiz.getState().finished)
            quiz.start (*exercise);

        updateButtonStates();
        updateFeedback();
        resized();
        return;
    }

    updateButtonStates();
    updateFeedback();
    resized();
}

void PracticePanel::toggleMetronome()
{
    metronomeOn = ! metronomeOn;
    audioEngine.getMetronome().setRunning (metronomeOn);
    updateButtonStates();
    repaint();
}

void PracticePanel::startSelectedExercise()
{
    const auto* exercise = selectedExercise();
    if (exercise == nullptr || currentModule == nullptr)
        return;

    if (exercise->isQuiz())
    {
        restartQuiz();
        return;
    }

    session.start (*exercise, currentModule->targetBpm, currentModule->onGridTarget);
    attemptReported = false;
    audioEngine.resetNoteCapture();

    audioEngine.getMetronome().setBpm ((double) session.getTargetBpm());
    audioEngine.getMetronome().setSubdivision (exercise->subdivision);
    audioEngine.getMetronome().setRunning (true);
    metronomeOn = true;

    updateButtonStates();
    repaint();
}

void PracticePanel::finishExercise()
{
    session.finish();
    audioEngine.getMetronome().setRunning (false);
    metronomeOn = false;

    // Publish the verdict: updateFeedback paints the message and reports the
    // accuracy for persistence. Without it the finished attempt would be lost
    // (poll() stops once the session is no longer running).
    updateFeedback();
    updateButtonStates();
    repaint();

    // Only a gate attempt unlocks the next module (REQ-002, REQ-009).
    const auto* exercise = selectedExercise();
    if (onGateResult != nullptr && exercise != nullptr && exercise->isGate
        && currentModule != nullptr)
    {
        onGateResult (currentModule->number, session.getState().passed);
    }
}

void PracticePanel::restartQuiz()
{
    if (! isQuizSelected())
        return;

    // A fresh attempt: forget the previous result until the new one is reached.
    quiz.restart();
    attemptReported = false;
    previousAccuracy = -1;
    updateButtonStates();
    updateFeedback();

    if (onQuizChanged != nullptr)
        onQuizChanged();
}

void PracticePanel::poll()
{
    if (isQuizSelected())
        return;

    if (! session.isRunning())
        return;

    std::vector<course::NoteEvent> events;
    audioEngine.drainNoteEvents (events);
    session.consume (events);
    updateFeedback();
}

void PracticePanel::updateFeedback()
{
    if (isQuizSelected())
    {
        const auto& q = quiz.getState();
        const auto* exercise = selectedExercise();
        const int total = exercise != nullptr ? (int) exercise->quiz.size() : 0;

        // Client request: when the exercise was already done, the last accuracy
        // is shown again as soon as it is reopened, before any new answer.
        if (q.answered == 0 && previousAccuracy >= 0)
            measurementLabel.setText (juce::String::fromUTF8 ("Último aproveitamento ")
                                        + percentFromInt (previousAccuracy),
                                      juce::dontSendNotification);
        else
            measurementLabel.setText (juce::String::fromUTF8 ("Acertos ") + juce::String (q.correct)
                                        + "/" + juce::String (q.answered)
                                        + juce::String::fromUTF8 ("   ·   aproveitamento ") + percent (q.accuracy),
                                      juce::dontSendNotification);

        guidanceLabel.setColour (juce::Label::textColourId, th::colour::textSecondary);

        const int moduleNumber = currentModule != nullptr ? currentModule->number : 1;
        const juce::String part = (exercise != nullptr && exercise->lessonId.isNotEmpty())
                                    ? exercise->lessonId : juce::String();

        juce::String guidance = juce::String::fromUTF8 ("Neste exercício, você deverá responder as questões "
                                                        "com base no material do Módulo ")
                                  + juce::String (moduleNumber);
        if (part.isNotEmpty())
            guidance += juce::String::fromUTF8 (", parte ") + part;

        guidance += juce::String::fromUTF8 (".\nResponda uma questão por vez no painel central.");
        guidance += juce::String::fromUTF8 ("\n\nQuestões: ") + juce::String (total);

        guidanceLabel.setText (guidance, juce::dontSendNotification);

        if (q.finished)
        {
            guidanceLabel.setColour (juce::Label::textColourId,
                                     q.passed ? th::colour::success : th::colour::danger);
            guidanceLabel.setText (q.message, juce::dontSendNotification);

            // Same persistence as the playable exercises: the last percentage of
            // the quiz is what reopening it must show.
            if (! attemptReported)
            {
                attemptReported = true;
                previousAccuracy = juce::roundToInt (q.accuracy * 100.0);

                if (onExerciseResult != nullptr && exercise != nullptr)
                    onExerciseResult (exercise->id, q.accuracy * 100.0);
            }
        }

        return;
    }

    const auto& state = session.getState();

    if (! state.running && ! state.finished)
    {
        // Idle: either a fresh exercise or one already done before. When there
        // is a previous result, show it (client request) instead of the dashes.
        if (previousAccuracy >= 0)
            measurementLabel.setText (juce::String::fromUTF8 ("Último aproveitamento ")
                                        + percentFromInt (previousAccuracy),
                                      juce::dontSendNotification);
        else
            measurementLabel.setText (juce::String::fromUTF8 ("Nota: --   ·   acertos 0/0   ·   grade --%"),
                                      juce::dontSendNotification);

        guidanceLabel.setColour (juce::Label::textColourId, th::colour::textSecondary);
        guidanceLabel.setText (juce::String::fromUTF8 ("Selecione um exercício e toque Iniciar."),
                               juce::dontSendNotification);
        return;
    }

    // The verdict is reached once: persist the accuracy so reopening the
    // exercise shows this result again.
    if (state.finished && ! attemptReported)
    {
        attemptReported = true;
        previousAccuracy = juce::roundToInt (state.accuracy * 100.0);

        if (onExerciseResult != nullptr)
            if (const auto* exercise = selectedExercise())
                onExerciseResult (exercise->id, state.accuracy * 100.0);
    }

    measurementLabel.setText (juce::String::fromUTF8 ("Nota: ")
                                + (state.lastNote.isEmpty() ? juce::String ("--") : state.lastNote)
                                + juce::String::fromUTF8 ("   ·   acertos ") + juce::String (state.matched)
                                + "/" + juce::String (state.targetCount)
                                + juce::String::fromUTF8 ("   ·   grade ") + percent (state.onGridRatio),
                              juce::dontSendNotification);

    guidanceLabel.setColour (juce::Label::textColourId,
                             state.finished
                               ? (state.passed ? th::colour::success : th::colour::danger)
                               : th::colour::textSecondary);
    guidanceLabel.setText (state.finished
                               ? state.message
                               : juce::String::fromUTF8 ("Acerto ")
                                   + percent (state.accuracy) + juce::String::fromUTF8 (" até agora."),
                           juce::dontSendNotification);
}

void PracticePanel::updateButtonStates()
{
    if (isQuizSelected())
    {
        // The question and its options live in the centre pane; the restart is
        // driven from there too. Here only the scoreboard is refreshed.
        return;
    }

    const bool running = session.isRunning();
    startButton.setEnabled (! running);
    finishButton.setEnabled (running);
    metronomeButton.setButtonText (metronomeOn ? juce::String::fromUTF8 ("Metrônomo: ligado")
                                               : juce::String::fromUTF8 ("Metrônomo: desligado"));
}

void PracticePanel::paint (juce::Graphics& g)
{
    g.setColour (th::colour::surface);
    g.fillRoundedRectangle (getLocalBounds().toFloat(), th::radius::md);
}

void PracticePanel::resized()
{
    auto bounds = getLocalBounds().reduced (th::spacing::md);

    // Heading with the "Todos os tópicos do módulo" link on its right.
    auto heading = bounds.removeFromTop (20);
    if (topicLink.isVisible())
    {
        topicLink.setBounds (heading.removeFromRight (170));
        headingLabel.setBounds (heading);
    }
    else
    {
        headingLabel.setBounds (heading);
    }

    // Blank until a topic is picked on the left: only the heading shows.
    if (! topicChosen)
        return;

    topicLabel.setBounds (bounds.removeFromTop (16));
    bounds.removeFromTop (th::spacing::xs);

    exerciseBox.setBounds (bounds.removeFromTop (28));
    bounds.removeFromTop (th::spacing::xs);

    // The selector alone until an exercise is armed (client step 2): the play
    // row, the scoreboard and the guidance only appear after the choice.
    if (! exerciseArmed)
        return;

    demoButton.setBounds (bounds.removeFromTop (30));
    bounds.removeFromTop (th::spacing::sm);

    // Scoreboard (Acertos x/y · aproveitamento z%), always present.
    measurementLabel.setBounds (bounds.removeFromTop (20));
    bounds.removeFromTop (th::spacing::xs);

    // Guidance box: what the student must do in the armed exercise.
    guidanceLabel.setBounds (bounds.removeFromTop (72));
    bounds.removeFromTop (th::spacing::sm);

    // Playable-exercise controls (absent for a quiz, which runs in the centre).
    if (isQuizSelected())
        return;

    auto row = bounds.removeFromTop (30);
    metronomeButton.setBounds (row.removeFromLeft (150));
    row.removeFromLeft (th::spacing::sm);
    startButton.setBounds (row.removeFromLeft (80));
    row.removeFromLeft (th::spacing::sm);
    finishButton.setBounds (row.removeFromLeft (80));
    bounds.removeFromTop (th::spacing::xs);
    bpmLabel.setBounds (bounds.removeFromTop (18));
}

} // namespace cursomusica
