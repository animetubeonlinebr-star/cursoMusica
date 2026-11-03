#include "UI/ModuleComponent.h"

#include "Course/ModuleCatalog.h"
#include "UI/Design/Theme.h"
#include "UI/PracticePanel.h"

namespace cursomusica
{

namespace th = cursomusica::theme;

namespace
{
    int lessonHeight (const LessonBlock& lesson)
    {
        int height = 22; // block title
        for (const auto& paragraph : lesson.paragraphs)
            height += juce::jmax (20, 18 * (paragraph.length() / 78 + 1));
        return height + th::spacing::sm;
    }

    int exerciseHeight (const Exercise& exercise)
    {
        int height = 20; // id + title
        height += juce::jmax (18, 18 * (exercise.goal.length() / 78 + 1));
        return height + th::spacing::sm;
    }
}

// Renders the selected module: explanation blocks first, then the gate
// challenge (REQ-003). The exercises follow in a later story.
class ModuleComponent::ModuleContentView final : public juce::Component
{
public:
    void setModule (const CourseModule* module)
    {
        current = module;
        repaint();
    }

    void setLockedMessage (const juce::String& message)
    {
        lockedMessage = message;
        repaint();
    }

    int getRequiredHeight() const
    {
        int height = 150; // header, meta line and objective
        if (current != nullptr)
        {
            for (const auto& lesson : current->lessons)
                height += lessonHeight (lesson);

            height += 30; // exercises heading
            for (const auto& exercise : current->exercises)
                height += exerciseHeight (exercise);

            // Each CAGED shape paints on two lines (name, then bass/region).
            if (! current->caged.empty())
                height += 24 + 40 * (int) current->caged.size() + th::spacing::sm;

            if (! current->rhythm.empty())
                height += 24 + 20 * (int) current->rhythm.size() + th::spacing::sm;

            if (current->practice.patternId.isNotEmpty())
                height += 24 + 20 + 20 + 20 * (int) current->practice.guitarists.size()
                          + th::spacing::sm;

            height += 22 + 40; // gate challenge heading + body

            if (! current->sources.isEmpty())
                height += th::spacing::sm + 24 + 18 * (int) current->sources.size();
        }

        return juce::jmax (height, 400);
    }

    void paint (juce::Graphics& g) override
    {
        auto bounds = getLocalBounds().reduced (th::spacing::lg);

        if (current == nullptr)
        {
            g.setColour (th::colour::textSecondary);
            g.setFont (th::type::makeFont (th::type::body));
            g.drawText (lockedMessage.isNotEmpty() ? lockedMessage
                                                   : juce::String::fromUTF8 ("Selecione um módulo à esquerda."),
                        bounds, juce::Justification::centred, false);
            return;
        }

        const auto& m = *current;

        g.setColour (th::colour::textPrimary);
        g.setFont (th::type::makeFont (th::type::title, true));
        g.drawFittedText (juce::String::fromUTF8 ("Módulo ") + juce::String (m.number) + " — " + m.title,
                          bounds.removeFromTop (34), juce::Justification::centredLeft, 1);

        g.setColour (th::colour::accentAlt);
        g.setFont (th::type::makeFont (th::type::caption, true));
        g.drawText (juce::String::fromUTF8 ("NÍVEL ") + juce::String (m.level)
                        + juce::String::fromUTF8 ("   ·   BPM META ") + juce::String (m.targetBpm)
                        + juce::String::fromUTF8 ("   ·   GATE 90%"),
                    bounds.removeFromTop (20), juce::Justification::centredLeft, false);

        g.setColour (th::colour::textSecondary);
        g.setFont (th::type::makeFont (th::type::body));
        g.drawFittedText (m.objective, bounds.removeFromTop (40),
                          juce::Justification::topLeft, 2);

        bounds.removeFromTop (th::spacing::md);

        for (const auto& lesson : m.lessons)
        {
            g.setColour (th::colour::accent);
            g.setFont (th::type::makeFont (th::type::body, true));
            g.drawText (lesson.id + ". " + lesson.title, bounds.removeFromTop (22),
                        juce::Justification::centredLeft, false);

            g.setColour (th::colour::textSecondary);
            g.setFont (th::type::makeFont (th::type::body));
            for (const auto& paragraph : lesson.paragraphs)
            {
                const int height = juce::jmax (20, 18 * (paragraph.length() / 78 + 1));
                g.drawFittedText (paragraph, bounds.removeFromTop (height),
                                  juce::Justification::topLeft, 3);
            }

            bounds.removeFromTop (th::spacing::sm);
        }

        if (! m.exercises.empty())
        {
            g.setColour (th::colour::textPrimary);
            g.setFont (th::type::makeFont (th::type::body, true));
            g.drawText (juce::String::fromUTF8 ("Exercícios"), bounds.removeFromTop (30),
                        juce::Justification::centredLeft, false);

            for (const auto& exercise : m.exercises)
            {
                g.setColour (th::colour::accentAlt);
                g.setFont (th::type::makeFont (th::type::body, true));
                g.drawText (exercise.id + " — " + exercise.title, bounds.removeFromTop (20),
                            juce::Justification::centredLeft, false);

                g.setColour (th::colour::textSecondary);
                g.setFont (th::type::makeFont (th::type::body));
                const int height = juce::jmax (18, 18 * (exercise.goal.length() / 78 + 1));
                g.drawFittedText (exercise.goal, bounds.removeFromTop (height),
                                  juce::Justification::topLeft, 2);

                bounds.removeFromTop (th::spacing::sm);
            }
        }

        if (! m.caged.empty())
        {
            g.setColour (th::colour::textPrimary);
            g.setFont (th::type::makeFont (th::type::body, true));
            g.drawText (juce::String::fromUTF8 ("Sistema CAGED"), bounds.removeFromTop (24),
                        juce::Justification::centredLeft, false);

            g.setFont (th::type::makeFont (th::type::body));
            for (const auto& shape : m.caged)
            {
                g.setColour (th::colour::accent);
                g.drawText (juce::String::fromUTF8 ("Forma ") + shape.shape,
                            bounds.removeFromTop (20).removeFromLeft (110),
                            juce::Justification::centredLeft, false);
                g.setColour (th::colour::textSecondary);
                g.drawText (juce::String::fromUTF8 ("baixo na ") + shape.bassString
                                + "   ·   " + shape.region,
                            bounds.removeFromTop (20), juce::Justification::centredLeft, false);
            }

            bounds.removeFromTop (th::spacing::sm);
        }

        if (! m.rhythm.empty())
        {
            g.setColour (th::colour::textPrimary);
            g.setFont (th::type::makeFont (th::type::body, true));
            g.drawText (juce::String::fromUTF8 ("Rítmica e contagem"), bounds.removeFromTop (24),
                        juce::Justification::centredLeft, false);

            g.setFont (th::type::makeFont (th::type::body));
            for (const auto& cell : m.rhythm)
            {
                g.setColour (th::colour::accent);
                g.drawText (cell.figure, bounds.removeFromTop (20).removeFromLeft (150),
                            juce::Justification::centredLeft, false);
                g.setColour (th::colour::textSecondary);
                g.drawText (cell.value + juce::String::fromUTF8 ("   ·   ") + cell.syllable,
                            bounds.removeFromTop (20), juce::Justification::centredLeft, false);
            }

            bounds.removeFromTop (th::spacing::sm);
        }

        if (m.practice.patternId.isNotEmpty())
        {
            g.setColour (th::colour::textPrimary);
            g.setFont (th::type::makeFont (th::type::body, true));
            g.drawText (juce::String::fromUTF8 ("Trilha de prática"), bounds.removeFromTop (24),
                        juce::Justification::centredLeft, false);

            g.setColour (th::colour::accent);
            g.setFont (th::type::makeFont (th::type::body, true));
            g.drawText (m.practice.patternId, bounds.removeFromTop (20),
                        juce::Justification::centredLeft, false);

            g.setColour (th::colour::textSecondary);
            g.setFont (th::type::makeFont (th::type::body));
            g.drawFittedText (m.practice.patternUse, bounds.removeFromTop (20),
                              juce::Justification::topLeft, 1);

            for (const auto& guitarist : m.practice.guitarists)
            {
                g.setColour (th::colour::textSecondary);
                g.drawText (juce::String::fromUTF8 ("Referência: ") + guitarist,
                            bounds.removeFromTop (20), juce::Justification::centredLeft, false);
            }

            bounds.removeFromTop (th::spacing::sm);
        }

        if (m.gateChallenge.isNotEmpty())
        {
            g.setColour (th::colour::textPrimary);
            g.setFont (th::type::makeFont (th::type::body, true));
            g.drawText (juce::String::fromUTF8 ("Desafio de gate"), bounds.removeFromTop (22),
                        juce::Justification::centredLeft, false);

            g.setColour (th::colour::success);
            g.setFont (th::type::makeFont (th::type::body));
            g.drawFittedText (m.gateChallenge, bounds.removeFromTop (40),
                              juce::Justification::topLeft, 2);
        }

        if (! m.sources.isEmpty())
        {
            bounds.removeFromTop (th::spacing::sm);

            g.setColour (th::colour::textPrimary);
            g.setFont (th::type::makeFont (th::type::body, true));
            g.drawText (juce::String::fromUTF8 ("Apostilas (curadoria — REQ-006)"),
                        bounds.removeFromTop (24), juce::Justification::centredLeft, false);

            g.setColour (th::colour::textSecondary);
            g.setFont (th::type::makeFont (th::type::caption));
            for (const auto& source : m.sources)
                g.drawText (source, bounds.removeFromTop (18),
                            juce::Justification::centredLeft, false);
        }
    }

private:
    const CourseModule* current = nullptr;
    juce::String lockedMessage;
};

class ModuleComponent::ModuleListModel final : public juce::ListBoxModel
{
public:
    std::function<void (int)> onSelectionChanged;
    std::function<bool (int)> isUnlocked;

    int getNumRows() override
    {
        return (int) ModuleCatalog::getModules().size();
    }

    void paintListBoxItem (int row, juce::Graphics& g, int width, int height, bool selected) override
    {
        const auto& modules = ModuleCatalog::getModules();
        if (row < 0 || row >= (int) modules.size())
            return;

        const auto& m = modules[(size_t) row];
        const bool unlocked = isUnlocked == nullptr || isUnlocked (m.number);

        if (selected)
        {
            g.setColour (th::colour::accentMuted);
            g.fillRoundedRectangle (juce::Rectangle<float> (0.0f, 0.0f, (float) width, (float) height).reduced (2.0f),
                                    th::radius::sm);
        }

        g.setColour (selected ? th::colour::textPrimary
                              : (unlocked ? th::colour::textSecondary : th::colour::textDisabled));
        g.setFont (th::type::makeFont (th::type::body, true));
        const auto label = juce::String::fromUTF8 ("Módulo ") + juce::String (m.number)
                             + (m.implemented ? juce::String()
                                              : juce::String::fromUTF8 ("  ·  em preparação"));
        g.drawText (label, 12, 4, width - 20, 20, juce::Justification::centredLeft, false);

        g.setColour (m.implemented ? th::colour::textSecondary : th::colour::accentMuted);
        g.setFont (th::type::makeFont (th::type::caption));
        g.drawFittedText (m.title, 12, 24, width - 20, 20, juce::Justification::centredLeft, 1);

        if (! unlocked)
        {
            g.setColour (th::colour::textDisabled);
            g.setFont (th::type::makeFont (th::type::caption, true));
            g.drawText (juce::String::fromUTF8 ("bloqueado"),
                        width - 90, 4, 78, 20, juce::Justification::centredRight, false);
        }
    }

    void selectedRowsChanged (int lastRow) override
    {
        if (onSelectionChanged != nullptr)
            onSelectionChanged (lastRow);
    }
};

ModuleComponent::ModuleComponent (AudioEngine& engine)
    : audioEngine (engine)
{
    titleLabel.setText (juce::String::fromUTF8 ("Módulos do curso"), juce::dontSendNotification);
    titleLabel.setFont (th::type::makeFont (th::type::title, true));
    titleLabel.setColour (juce::Label::textColourId, th::colour::textPrimary);
    addAndMakeVisible (titleLabel);

    subtitleLabel.setText (juce::String::fromUTF8 ("Explicação antes do desafio, progressão linear"),
                           juce::dontSendNotification);
    subtitleLabel.setFont (th::type::makeFont (th::type::body));
    subtitleLabel.setColour (juce::Label::textColourId, th::colour::textSecondary);
    addAndMakeVisible (subtitleLabel);

    closeButton.onClick = [this] { if (onCloseRequested != nullptr) onCloseRequested(); };
    addAndMakeVisible (closeButton);

    listModel = std::make_unique<ModuleListModel>();
    listModel->onSelectionChanged = [this] (int row) { showModule (row + 1); };
    listModel->isUnlocked = [this] (int number) { return progressStore.isModuleUnlocked (number); };

    moduleList.setModel (listModel.get());
    moduleList.setRowHeight (48);
    moduleList.setColour (juce::ListBox::backgroundColourId, th::colour::surface);
    addAndMakeVisible (moduleList);

    contentView = std::make_unique<ModuleContentView>();
    contentViewport.setViewedComponent (contentView.get(), false);
    contentViewport.setScrollBarsShown (true, false);
    addAndMakeVisible (contentViewport);

    practicePanel = std::make_unique<PracticePanel> (audioEngine);
    practicePanel->onGateResult = [this] (int moduleNumber, bool passed)
    {
        progressStore.recordGateResult (moduleNumber, passed);
        refreshModuleList();
    };
    addAndMakeVisible (*practicePanel);

    hintLabel.setFont (th::type::makeFont (th::type::caption));
    hintLabel.setColour (juce::Label::textColourId, th::colour::textDisabled);
    hintLabel.setJustificationType (juce::Justification::centredLeft);
    hintLabel.setText (juce::String::fromUTF8 (
        "Progressão linear: conclua o gate (≥90%) do módulo atual para abrir o próximo."),
        juce::dontSendNotification);
    addAndMakeVisible (hintLabel);

    // Open on the first module so the explanation is visible immediately.
    moduleList.selectRow (0);

    startTimerHz (20); // drains detected notes while an exercise runs
}

ModuleComponent::~ModuleComponent()
{
    stopTimer();
}

void ModuleComponent::timerCallback()
{
    if (practicePanel != nullptr)
        practicePanel->poll();
}

void ModuleComponent::refreshModuleList()
{
    moduleList.updateContent();
    moduleList.repaint();
}

void ModuleComponent::showModule (int number)
{
    const auto* module = ModuleCatalog::findModule (number);
    const bool unlocked = module != nullptr && progressStore.isModuleUnlocked (module->number);

    contentView->setLockedMessage (juce::String::fromUTF8 ("Módulo ") + juce::String (number)
                                     + juce::String::fromUTF8 (" bloqueado.\nConclua o gate do módulo ")
                                     + juce::String (juce::jmax (1, number - 1))
                                     + juce::String::fromUTF8 (" com ≥90% para abrir."));
    contentView->setModule (unlocked ? module : nullptr);
    contentView->setSize (contentViewport.getMaximumVisibleWidth(),
                          contentView->getRequiredHeight());

    if (practicePanel != nullptr)
        practicePanel->setModule (unlocked ? module : nullptr);

    if (! unlocked && module != nullptr)
    {
        hintLabel.setColour (juce::Label::textColourId, th::colour::danger);
        hintLabel.setText (juce::String::fromUTF8 ("Módulo ") + juce::String (module->number)
                             + juce::String::fromUTF8 (" bloqueado: conclua o gate do módulo ")
                             + juce::String (module->number - 1)
                             + juce::String::fromUTF8 (" (≥90%) para abrir."),
                           juce::dontSendNotification);
    }
    else
    {
        hintLabel.setColour (juce::Label::textColourId, th::colour::textDisabled);
        hintLabel.setText (juce::String::fromUTF8 (
            "Progressão linear: conclua o gate (≥90%) do módulo atual para abrir o próximo."),
            juce::dontSendNotification);
    }
}

void ModuleComponent::paint (juce::Graphics& g)
{
    g.fillAll (th::colour::background);
}

void ModuleComponent::resized()
{
    auto bounds = getLocalBounds().reduced (th::spacing::lg);

    hintLabel.setBounds (bounds.removeFromBottom (20));
    bounds.removeFromBottom (th::spacing::sm);

    auto header = bounds.removeFromTop (64);
    closeButton.setBounds (header.removeFromRight (110).withSizeKeepingCentre (110, 34));
    header.removeFromRight (th::spacing::md);
    titleLabel.setBounds (header.removeFromTop (32));
    subtitleLabel.setBounds (header.removeFromTop (22));

    bounds.removeFromTop (th::spacing::md);

    moduleList.setBounds (bounds.removeFromLeft (260));
    bounds.removeFromLeft (th::spacing::md);

    // Practice strip on the right, the scrollable lesson content fills the rest.
    practicePanel->setBounds (bounds.removeFromRight (320));
    bounds.removeFromRight (th::spacing::md);

    contentViewport.setBounds (bounds);
    contentView->setSize (contentViewport.getMaximumVisibleWidth(),
                          contentView->getRequiredHeight());
}

} // namespace cursomusica
