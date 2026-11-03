#include "UI/LevelMeter.h"

#include "UI/Design/Theme.h"

#include <cmath>

namespace cursomusica
{

namespace th = cursomusica::theme;

LevelMeter::LevelMeter()
{
    setInterceptsMouseClicks (false, false);
}

void LevelMeter::setLevelDb (float newLevelDb)
{
    const float clamped = juce::jlimit (minDb, maxDb, newLevelDb);
    if (std::abs (clamped - levelDb) < 0.1f)
        return;

    levelDb = clamped;
    repaint();
}

void LevelMeter::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();

    g.setColour (th::colour::surfaceRaised);
    g.fillRoundedRectangle (bounds, th::radius::sm);

    const float normalised = juce::jmap (levelDb, minDb, maxDb, 0.0f, 1.0f);
    auto filled = bounds.withWidth (bounds.getWidth() * normalised);

    // Green up to -12 dB, amber to -3 dB, red above, so level is readable at a glance.
    const auto barColour = levelDb > -3.0f ? th::colour::danger
                         : levelDb > -12.0f ? juce::Colour (0xffe0a83a)
                                            : th::colour::success;

    g.setColour (barColour);
    g.fillRoundedRectangle (filled, th::radius::sm);

    g.setColour (th::colour::border);
    g.drawRoundedRectangle (bounds.reduced (0.5f), th::radius::sm, 1.0f);
}

} // namespace cursomusica
