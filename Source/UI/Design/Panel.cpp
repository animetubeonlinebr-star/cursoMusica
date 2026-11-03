#include "UI/Design/Panel.h"

#include "UI/Design/Theme.h"

namespace cursomusica
{

namespace th = cursomusica::theme;

Panel::Panel (juce::String titleText)
    : title (std::move (titleText))
{
}

juce::Rectangle<int> Panel::getContentBounds() const
{
    return getLocalBounds().reduced (th::spacing::md).withTrimmedTop (th::spacing::lg);
}

void Panel::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();

    g.setColour (th::colour::surface);
    g.fillRoundedRectangle (bounds, th::radius::lg);

    g.setColour (th::colour::border);
    g.drawRoundedRectangle (bounds.reduced (0.5f), th::radius::lg, 1.0f);

    if (title.isNotEmpty())
    {
        g.setFont (th::type::makeFont (th::type::caption, true));
        g.setColour (th::colour::textSecondary);
        g.drawText (title.toUpperCase(),
                    getLocalBounds().reduced (th::spacing::md).withHeight (th::spacing::md),
                    juce::Justification::centredLeft, false);
    }
}

} // namespace cursomusica
