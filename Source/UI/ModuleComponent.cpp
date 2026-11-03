#include "UI/ModuleComponent.h"

#include "Course/ModuleCatalog.h"
#include "UI/Design/Theme.h"

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

    int getRequiredHeight() const
    {
        int height = 150; // header, meta line and objective
        if (current != nullptr)
        {
            for (const auto& lesson : current->lessons)
                height += lessonHeight (lesson);

            height += 80; // gate challenge
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
            g.drawText (juce::String::fromUTF8 ("Selecione um módulo à esquerda."),
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
    }

private:
    const CourseModule* current = nullptr;
};

class ModuleComponent::ModuleListModel final : public juce::ListBoxModel
{
public:
    std::function<void (int)> onSelectionChanged;

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

        if (selected)
        {
            g.setColour (th::colour::accentMuted);
            g.fillRoundedRectangle (juce::Rectangle<float> (0.0f, 0.0f, (float) width, (float) height).reduced (2.0f),
                                    th::radius::sm);
        }

        g.setColour (selected ? th::colour::textPrimary : th::colour::textSecondary);
        g.setFont (th::type::makeFont (th::type::body, true));
        const auto label = juce::String::fromUTF8 ("Módulo ") + juce::String (m.number)
                             + (m.implemented ? juce::String() : juce::String::fromUTF8 ("  ·  em preparação"));
        g.drawText (label, 12, 4, width - 20, 20, juce::Justification::centredLeft, false);

        g.setColour (m.implemented ? th::colour::textSecondary : th::colour::accentMuted);
        g.setFont (th::type::makeFont (th::type::caption));
        g.drawFittedText (m.title, 12, 24, width - 20, 20, juce::Justification::centredLeft, 1);
    }

    void selectedRowsChanged (int lastRow) override
    {
        if (onSelectionChanged != nullptr)
            onSelectionChanged (lastRow);
    }
};

ModuleComponent::ModuleComponent()
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

    moduleList.setModel (listModel.get());
    moduleList.setRowHeight (48);
    moduleList.setColour (juce::ListBox::backgroundColourId, th::colour::surface);
    addAndMakeVisible (moduleList);

    contentView = std::make_unique<ModuleContentView>();
    contentViewport.setViewedComponent (contentView.get(), false);
    contentViewport.setScrollBarsShown (true, false);
    addAndMakeVisible (contentViewport);

    // Open on the first module so the explanation is visible immediately.
    moduleList.selectRow (0);
}

ModuleComponent::~ModuleComponent() = default;

void ModuleComponent::showModule (int number)
{
    contentView->setModule (ModuleCatalog::findModule (number));
    contentView->setSize (contentViewport.getMaximumVisibleWidth(),
                          contentView->getRequiredHeight());
}

void ModuleComponent::paint (juce::Graphics& g)
{
    g.fillAll (th::colour::background);
}

void ModuleComponent::resized()
{
    auto bounds = getLocalBounds().reduced (th::spacing::lg);

    auto header = bounds.removeFromTop (64);
    closeButton.setBounds (header.removeFromRight (110).withSizeKeepingCentre (110, 34));
    header.removeFromRight (th::spacing::md);
    titleLabel.setBounds (header.removeFromTop (32));
    subtitleLabel.setBounds (header.removeFromTop (22));

    bounds.removeFromTop (th::spacing::md);

    moduleList.setBounds (bounds.removeFromLeft (260));
    bounds.removeFromLeft (th::spacing::md);

    contentViewport.setBounds (bounds);
    contentView->setSize (contentViewport.getMaximumVisibleWidth(),
                          contentView->getRequiredHeight());
}

} // namespace cursomusica
