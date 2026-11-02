#include "UI/Design/LookAndFeel.h"

#include "UI/Design/Theme.h"

namespace cursomusica
{

namespace th = cursomusica::theme;

CursoLookAndFeel::CursoLookAndFeel()
{
    setColour (juce::ResizableWindow::backgroundColourId, th::colour::background);
    setColour (juce::Label::textColourId, th::colour::textPrimary);
    setColour (juce::ComboBox::backgroundColourId, th::colour::surfaceRaised);
    setColour (juce::ComboBox::textColourId, th::colour::textPrimary);
    setColour (juce::ComboBox::outlineColourId, th::colour::border);
    setColour (juce::ComboBox::arrowColourId, th::colour::textSecondary);
    setColour (juce::TextButton::buttonColourId, th::colour::surfaceRaised);
    setColour (juce::TextButton::buttonOnColourId, th::colour::accent);
    setColour (juce::TextButton::textColourOffId, th::colour::textPrimary);
    setColour (juce::TextButton::textColourOnId, th::colour::background);
    setColour (juce::Slider::thumbColourId, th::colour::accent);
    setColour (juce::Slider::trackColourId, th::colour::accentMuted);
    setColour (juce::Slider::backgroundColourId, th::colour::surfaceRaised);
}

void CursoLookAndFeel::drawButtonBackground (juce::Graphics& g,
                                             juce::Button& button,
                                             const juce::Colour& backgroundColour,
                                             bool shouldDrawButtonAsHighlighted,
                                             bool shouldDrawButtonAsDown)
{
    const auto bounds = button.getLocalBounds().toFloat().reduced (0.5f);
    const float corner = th::radius::md;

    auto fill = backgroundColour;
    if (shouldDrawButtonAsDown)
        fill = fill.brighter (0.15f);
    else if (shouldDrawButtonAsHighlighted)
        fill = fill.brighter (0.07f);

    g.setColour (fill);
    g.fillRoundedRectangle (bounds, corner);

    g.setColour (button.getToggleState() ? th::colour::accent : th::colour::border);
    g.drawRoundedRectangle (bounds, corner, button.getToggleState() ? 1.5f : 1.0f);
}

void CursoLookAndFeel::drawComboBox (juce::Graphics& g,
                                     int width, int height,
                                     bool /*isButtonDown*/,
                                     int /*buttonX*/, int /*buttonY*/, int /*buttonW*/, int /*buttonH*/,
                                     juce::ComboBox& box)
{
    const juce::Rectangle<float> bounds (0.0f, 0.0f, (float) width, (float) height);

    g.setColour (th::colour::surfaceRaised);
    g.fillRoundedRectangle (bounds.reduced (0.5f), th::radius::sm);

    g.setColour (box.isMouseOver() ? th::colour::accent : th::colour::border);
    g.drawRoundedRectangle (bounds.reduced (0.5f), th::radius::sm, 1.0f);

    juce::Path arrow;
    const float cx = (float) width - 14.0f;
    const float cy = (float) height * 0.5f;
    arrow.addTriangle (cx - 5.0f, cy - 2.5f, cx + 5.0f, cy - 2.5f, cx, cy + 3.5f);

    g.setColour (th::colour::textSecondary);
    g.fillPath (arrow);
}

juce::Font CursoLookAndFeel::getComboBoxFont (juce::ComboBox&)
{
    return th::type::makeFont (th::type::body);
}

juce::Font CursoLookAndFeel::getLabelFont (juce::Label& label)
{
    return label.getFont();
}

juce::Font CursoLookAndFeel::getTextButtonFont (juce::TextButton&, int buttonHeight)
{
    return th::type::makeFont (juce::jmin (th::type::body, (float) buttonHeight * 0.6f), true);
}

} // namespace cursomusica
