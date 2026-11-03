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
    headingLabel.setText (juce::String::fromUTF8 ("Prática"), juce::dontSendNotification);
    headingLabel.setFont (th::type::makeFont (th::type::body, true));
    headingLabel.setColour (juce::Label::textColourId, th::colour::textPrimary);
    addAndMakeVisible (headingLabel);

    bpmLabel.setFont (th::type::makeFont (th::type::caption));
    bpmLabel.setColour (juce::Label::textColourId, th::colour::textSecondary);
    addAndMakeVisible (bpmLabel);

    metronomeButton.onClick = [this] { toggleMetronome(); };
    addAndMakeVisible (metronomeButton);

    exerciseBox.onChange = [this]
    {
        selectedExerciseIndex = exerciseBox.getSelectedItemIndex();
        updateButtonStates();
    };
    addAndMakeVisible (exerciseBox);

    startButton.onClick = [this] { startSelectedExercise(); };
    addAndMakeVisible (startButton);

    finishButton.onClick = [this] { finishExercise(); };
    addAndMakeVisible (finishButton);

    feedbackLabel.setFont (th::type::makeFont (th::type::body));
    feedbackLabel.setColour (juce::Label::textColourId, th::colour::textSecondary);
    feedbackLabel.setJustificationType (juce::Justification::topLeft);
    addAndMakeVisible (feedbackLabel);

    updateButtonStates();
}

PracticePanel::~PracticePanel() = default;

void PracticePanel::setModule (const CourseModule* module)
{
    currentModule = module;
    selectedExerciseIndex = 0;
    session = {};
    refreshExerciseList();
    syncMetronomeFromModule();
    updateButtonStates();
    repaint();
}

void PracticePanel::refreshExerciseList()
{
    exerciseBox.clear (juce::dontSendNotification);

    if (currentModule == nullptr)
        return;

    for (int i = 0; i < (int) currentModule->exercises.size(); ++i)
    {
        const auto& e = currentModule->exercises[(size_t) i];
        const bool playable = ! e.targets.empty() || ! e.chordPitchClasses.empty()
                                || ! e.chordProgression.empty();
        exerciseBox.addItem (e.id + " — " + e.title
                               + (playable ? juce::String() : juce::String::fromUTF8 ("  (leitura)")),
                             i + 1);
    }

    if (exerciseBox.getNumItems() > 0)
        exerciseBox.setSelectedId (1, juce::dontSendNotification);
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

    const int index = exerciseBox.getSelectedItemIndex();
    if (index < 0 || index >= (int) currentModule->exercises.size())
        return nullptr;

    return &currentModule->exercises[(size_t) index];
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

void PracticePanel::poll()
{
    if (! session.isRunning())
        return;

    std::vector<course::NoteEvent> events;
    audioEngine.drainNoteEvents (events);
    session.consume (events);
    updateFeedback();
}

void PracticePanel::updateFeedback()
{
    const auto& state = session.getState();

    if (! state.running && ! state.finished)
    {
        feedbackLabel.setText ({}, juce::dontSendNotification);
        return;
    }

    auto text = juce::String::fromUTF8 ("Nota: ") + (state.lastNote.isEmpty() ? juce::String ("--") : state.lastNote)
                  + juce::String::fromUTF8 ("   ·   acerto ") + percent (state.accuracy)
                  + " (" + juce::String (state.matched) + "/" + juce::String (state.targetCount) + ")"
                  + juce::String::fromUTF8 ("   ·   grade ") + percent (state.onGridRatio);

    if (state.finished)
        text << "\n" << state.message;

    feedbackLabel.setText (text, juce::dontSendNotification);
    feedbackLabel.setColour (juce::Label::textColourId,
                             state.finished
                               ? (state.passed ? th::colour::success : th::colour::danger)
                               : th::colour::textSecondary);
}

void PracticePanel::updateButtonStates()
{
    const bool running = session.isRunning();
    startButton.setEnabled (! running);
    finishButton.setEnabled (running);
    metronomeButton.setButtonText (metronomeOn ? "Metronome: on" : "Metronome: off");
    updateFeedback();
}

void PracticePanel::paint (juce::Graphics& g)
{
    g.setColour (th::colour::surface);
    g.fillRoundedRectangle (getLocalBounds().toFloat(), th::radius::md);
}

void PracticePanel::resized()
{
    auto bounds = getLocalBounds().reduced (th::spacing::md);

    auto top = bounds.removeFromTop (22);
    headingLabel.setBounds (top.removeFromLeft (90));
    bpmLabel.setBounds (top);

    auto row1 = bounds.removeFromTop (32);
    metronomeButton.setBounds (row1.removeFromLeft (130));
    row1.removeFromLeft (th::spacing::sm);
    startButton.setBounds (row1.removeFromLeft (80));
    row1.removeFromLeft (th::spacing::sm);
    finishButton.setBounds (row1.removeFromLeft (80));

    bounds.removeFromTop (th::spacing::sm);
    exerciseBox.setBounds (bounds.removeFromTop (28));

    bounds.removeFromTop (th::spacing::sm);
    feedbackLabel.setBounds (bounds);
}

} // namespace cursomusica
