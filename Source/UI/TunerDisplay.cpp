#include "UI/TunerDisplay.h"

#include "UI/Design/Theme.h"

#include <cmath>

namespace cursomusica
{

namespace th = cursomusica::theme;

namespace
{
    const juce::StringArray noteNames { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
}

TunerDisplay::TunerDisplay()
{
    setInterceptsMouseClicks (false, false);
}

void TunerDisplay::setFrequencyHz (float newFrequencyHz)
{
    if (std::abs (newFrequencyHz - frequencyHz) < 0.5f)
        return;

    frequencyHz = newFrequencyHz;
    updateFromFrequency();
    repaint();
}

void TunerDisplay::updateFromFrequency()
{
    if (frequencyHz <= 0.0f)
    {
        hasPitch = false;
        noteName = "--";
        centsOffset = 0.0f;
        return;
    }

    hasPitch = true;

    // MIDI note number, with A4 = 69.
    const float midi = 69.0f + 12.0f * std::log2 (frequencyHz / concertA);
    const int nearest = juce::roundToInt (midi);
    centsOffset = (midi - (float) nearest) * 100.0f;

    octave = nearest / 12 - 1;
    noteName = noteNames[((nearest % 12) + 12) % 12];
}

void TunerDisplay::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();

    g.setColour (th::colour::surface);
    g.fillRoundedRectangle (bounds, th::radius::lg);

    g.setColour (th::colour::border);
    g.drawRoundedRectangle (bounds.reduced (0.5f), th::radius::lg, 1.0f);

    // Arc scale across the top half.
    const auto centre = juce::Point<float> (bounds.getCentreX(), bounds.getBottom() - 40.0f);
    const float radius = juce::jmin (bounds.getWidth() * 0.42f, bounds.getHeight() * 0.85f);

    constexpr float startAngle = juce::MathConstants<float>::pi * 1.25f;
    constexpr float endAngle   = juce::MathConstants<float>::pi * 1.75f;

    juce::Path arc;
    arc.addCentredArc (centre.x, centre.y, radius, radius, 0.0f, startAngle, endAngle, true);
    g.setColour (th::colour::border);
    g.strokePath (arc, juce::PathStrokeType (2.0f));

    // Centre tick.
    const float midAngle = (startAngle + endAngle) * 0.5f;
    const juce::Point<float> tickInner (centre.x + std::cos (midAngle) * (radius - 14.0f),
                                        centre.y + std::sin (midAngle) * (radius - 14.0f));
    const juce::Point<float> tickOuter (centre.x + std::cos (midAngle) * radius,
                                        centre.y + std::sin (midAngle) * radius);
    g.setColour (th::colour::textSecondary);
    g.drawLine ({ tickInner, tickOuter }, 2.0f);

    // Needle, clamped to +-50 cents.
    if (hasPitch)
    {
        const float clampedCents = juce::jlimit (-50.0f, 50.0f, centsOffset);
        const float t = juce::jmap (clampedCents, -50.0f, 50.0f, 0.0f, 1.0f);
        const float angle = juce::jmap (t, 0.0f, 1.0f, startAngle, endAngle);

        const juce::Point<float> tip (centre.x + std::cos (angle) * (radius - 6.0f),
                                      centre.y + std::sin (angle) * (radius - 6.0f));

        const bool inTune = std::abs (centsOffset) <= 5.0f;
        g.setColour (inTune ? th::colour::success : th::colour::accent);
        g.drawLine ({ centre, tip }, 3.0f);

        g.fillEllipse (juce::Rectangle<float> (10.0f, 10.0f).withCentre (centre));
    }

    // Note readout.
    g.setFont (th::type::makeFont (th::type::display, true));
    g.setColour (hasPitch ? th::colour::textPrimary : th::colour::textSecondary);

    const auto noteText = hasPitch ? noteName + juce::String (octave) : noteName;
    g.drawText (noteText, bounds.withTrimmedTop (bounds.getHeight() * 0.18f).withHeight (th::type::display),
                juce::Justification::centredTop, false);

    // Cents readout.
    g.setFont (th::type::makeFont (th::type::body));
    g.setColour (th::colour::textSecondary);

    juce::String centsText = hasPitch
        ? (centsOffset >= 0.0f ? "+" : "") + juce::String (centsOffset, 1) + " cents"
        : "no signal";

    g.drawText (centsText, bounds.withTrimmedBottom (th::spacing::md).removeFromBottom (th::spacing::lg),
                juce::Justification::centredBottom, false);
}

} // namespace cursomusica
