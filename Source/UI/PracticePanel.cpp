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
}

PracticePanel::PracticePanel (AudioEngine& engine)
    : audioEngine (engine)
{
    headingLabel.setText (juce::String::fromUTF8 ("Exercícios práticos"), juce::dontSendNotification);
    headingLabel.setFont (th::type::makeFont (th::type::body, true));
    headingLabel.setColour (juce::Label::textColourId, th::colour::textPrimary);
    addAndMakeVisible (headingLabel);

    topicLabel.setFont (th::type::makeFont (th::type::caption));
    topicLabel.setColour (juce::Label::textColourId, th::colour::accentAlt);
    addAndMakeVisible (topicLabel);

    exerciseBox.onChange = [this]
    {
        selectedExerciseIndex = exerciseBox.getSelectedItemIndex();
        updateApplication();
    };
    addAndMakeVisible (exerciseBox);

    demoButton.onClick = [this]
    {
        if (onExerciseSelected != nullptr)
            onExerciseSelected (selectedExercise());
    };
    addAndMakeVisible (demoButton);

    // Measurement: always on top of the application area.
    measurementLabel.setFont (th::type::makeFont (th::type::caption));
    measurementLabel.setColour (juce::Label::textColourId, th::colour::textSecondary);
    measurementLabel.setJustificationType (juce::Justification::topLeft);
    addAndMakeVisible (measurementLabel);

    feedbackLabel.setFont (th::type::makeFont (th::type::body));
    feedbackLabel.setColour (juce::Label::textColourId, th::colour::textSecondary);
    feedbackLabel.setJustificationType (juce::Justification::topLeft);
    addAndMakeVisible (feedbackLabel);

    // Application: playable exercise controls.
    metronomeButton.onClick = [this] { toggleMetronome(); };
    addAndMakeVisible (metronomeButton);

    startButton.onClick = [this] { startSelectedExercise(); };
    addAndMakeVisible (startButton);

    finishButton.onClick = [this] { finishExercise(); };
    addAndMakeVisible (finishButton);

    bpmLabel.setFont (th::type::makeFont (th::type::caption));
    bpmLabel.setColour (juce::Label::textColourId, th::colour::textSecondary);
    addAndMakeVisible (bpmLabel);

    // Application: quiz.
    quizPrompt.setFont (th::type::makeFont (th::type::body, true));
    quizPrompt.setColour (juce::Label::textColourId, th::colour::textPrimary);
    quizPrompt.setJustificationType (juce::Justification::topLeft);
    addAndMakeVisible (quizPrompt);

    updateApplication();
}

PracticePanel::~PracticePanel() = default;

void PracticePanel::setModule (const CourseModule* module)
{
    currentModule = module;
    topicFilter = {};
    selectedExerciseIndex = 0;
    session = {};
    quiz = {};
    refreshExerciseList();
    syncMetronomeFromModule();
}

void PracticePanel::setTopicFilter (const juce::String& lessonId)
{
    topicFilter = lessonId;
    selectedExerciseIndex = 0;
    session = {};
    quiz = {};
    refreshExerciseList();
}

void PracticePanel::refreshExerciseList()
{
    exerciseBox.clear (juce::dontSendNotification);
    filteredIndices.clear();

    if (currentModule != nullptr)
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

    if (exerciseBox.getNumItems() > 0)
        exerciseBox.setSelectedId (1, juce::dontSendNotification);

    topicLabel.setText (topicFilter.isEmpty()
                            ? juce::String::fromUTF8 ("Todos os tópicos do módulo")
                            : juce::String::fromUTF8 ("Tópico ") + topicFilter,
                        juce::dontSendNotification);

    updateApplication();
}

void PracticePanel::syncMetronomeFromModule()
{
    if (currentModule == nullptr)
        return;

    audioEngine.getMetronome().setBpm ((double) currentModule->targetBpm);
    audioEngine.getMetronome().setRunning (metronomeOn);
    bpmLabel.setText (juce::String::fromUTF8 ("BPM meta ") + juce::String (currentModule->targetBpm)
                        + juce::String::fromUTF8 ("  ·  alvo de grade ") + percent (currentModule->onGridTarget),
                      juce::dontSendNotification);
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

    // Playable-exercise controls vs. quiz widgets.
    metronomeButton.setVisible (! quizMode);
    startButton.setVisible (! quizMode);
    finishButton.setVisible (! quizMode);
    bpmLabel.setVisible (! quizMode);
    quizPrompt.setVisible (quizMode);

    if (quizMode)
    {
        if (! quiz.isRunning() && ! quiz.getState().finished)
            quiz.start (*exercise);

        updateButtonStates();
        updateFeedback();
        resized();
        return;
    }

    for (auto* button : quizOptions)
        button->setVisible (false);

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
    if (isQuizSelected())
    {
        quiz.restart();
        updateButtonStates();
        updateFeedback();
        resized();
        return;
    }

    const auto* exercise = selectedExercise();
    if (exercise == nullptr || currentModule == nullptr)
        return;

    session.start (*exercise, currentModule->targetBpm, currentModule->onGridTarget);
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

void PracticePanel::answerQuiz (int optionIndex)
{
    quiz.answer (optionIndex);
    updateButtonStates();
    updateFeedback();
    resized();
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

        measurementLabel.setText (juce::String::fromUTF8 ("Acertos ") + juce::String (q.correct)
                                    + "/" + juce::String (q.answered)
                                    + juce::String::fromUTF8 ("   ·   aproveitamento ") + percent (q.accuracy),
                                  juce::dontSendNotification);

        juce::String prompt;

        if (const auto* question = quiz.currentQuestion())
        {
            prompt = juce::String::fromUTF8 ("Questão ") + juce::String (q.currentQuestion + 1)
                       + "/" + juce::String (total) + "\n" + question->prompt;
        }
        else
        {
            prompt = q.message.isNotEmpty() ? q.message
                                            : juce::String::fromUTF8 ("Questionário concluído.");
        }

        quizPrompt.setText (prompt, juce::dontSendNotification);

        feedbackLabel.setColour (juce::Label::textColourId,
                                 q.finished
                                   ? (q.passed ? th::colour::success : th::colour::danger)
                                   : th::colour::textSecondary);
        feedbackLabel.setText (q.finished
                                   ? (q.passed ? juce::String::fromUTF8 ("Aprovado no questionário (≥90%).")
                                               : juce::String::fromUTF8 ("Refaça: acerto abaixo de 90%."))
                                   : juce::String::fromUTF8 ("Responda uma questão por vez."),
                               juce::dontSendNotification);
        return;
    }

    const auto& state = session.getState();

    if (! state.running && ! state.finished)
    {
        measurementLabel.setText (juce::String::fromUTF8 ("Nota: --   ·   acertos 0/0   ·   grade --%"),
                                  juce::dontSendNotification);
        feedbackLabel.setText (juce::String::fromUTF8 ("Selecione um exercício e toque Iniciar."),
                               juce::dontSendNotification);
        return;
    }

    measurementLabel.setText (juce::String::fromUTF8 ("Nota: ")
                                + (state.lastNote.isEmpty() ? juce::String ("--") : state.lastNote)
                                + juce::String::fromUTF8 ("   ·   acertos ") + juce::String (state.matched)
                                + "/" + juce::String (state.targetCount)
                                + juce::String::fromUTF8 ("   ·   grade ") + percent (state.onGridRatio),
                              juce::dontSendNotification);

    feedbackLabel.setText (state.finished ? state.message
                                          : juce::String::fromUTF8 ("Acerto ")
                                              + percent (state.accuracy) + juce::String::fromUTF8 (" até agora."),
                           juce::dontSendNotification);
    feedbackLabel.setColour (juce::Label::textColourId,
                             state.finished
                               ? (state.passed ? th::colour::success : th::colour::danger)
                               : th::colour::textSecondary);
}

void PracticePanel::updateButtonStates()
{
    const bool quizMode = isQuizSelected();

    if (quizMode)
    {
        const auto& q = quiz.getState();

        // Rebuild the option buttons for the question currently on screen.
        const auto* question = quiz.currentQuestion();
        const int wanted = question != nullptr ? question->options.size() : 0;

        while (quizOptions.size() > wanted)
            quizOptions.removeLast();

        for (int i = quizOptions.size(); i < wanted; ++i)
        {
            auto* button = quizOptions.add (new juce::TextButton());
            button->setColour (juce::TextButton::buttonColourId, th::colour::surfaceRaised);
            button->onClick = [this, i] { answerQuiz (i); };
            addAndMakeVisible (button);
        }

        for (int i = 0; i < quizOptions.size(); ++i)
        {
            if (question != nullptr && i < question->options.size())
                quizOptions[i]->setButtonText (juce::String::charToString ("ABCD"[i % 4])
                                                 + ") " + question->options[i]);
            quizOptions[i]->setVisible (question != nullptr);
        }

        startButton.setButtonText (q.finished ? juce::String::fromUTF8 ("Reiniciar")
                                              : juce::String::fromUTF8 ("Iniciar"));
        return;
    }

    for (auto* button : quizOptions)
        button->setVisible (false);

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

    headingLabel.setBounds (bounds.removeFromTop (20));
    topicLabel.setBounds (bounds.removeFromTop (16));
    bounds.removeFromTop (th::spacing::xs);

    exerciseBox.setBounds (bounds.removeFromTop (28));
    bounds.removeFromTop (th::spacing::xs);
    demoButton.setBounds (bounds.removeFromTop (26));
    bounds.removeFromTop (th::spacing::sm);

    // Measurement (Nota / Acertos / Grade), always present.
    measurementLabel.setBounds (bounds.removeFromTop (20));
    feedbackLabel.setBounds (bounds.removeFromTop (44));
    bounds.removeFromTop (th::spacing::sm);

    // Application below the measurement.
    if (isQuizSelected())
    {
        quizPrompt.setBounds (bounds.removeFromTop (56));
        bounds.removeFromTop (th::spacing::xs);

        const int perButton = 30;
        for (auto* button : quizOptions)
        {
            button->setBounds (bounds.removeFromTop (perButton));
            bounds.removeFromTop (th::spacing::xs);
        }

        bounds.removeFromTop (th::spacing::xs);
        startButton.setBounds (bounds.removeFromTop (30).removeFromLeft (140));
        return;
    }

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
