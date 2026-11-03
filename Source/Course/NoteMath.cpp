#include "Course/NoteMath.h"

#include <cmath>

namespace cursomusica::music
{

namespace
{
    constexpr double a4Midi = 69.0;
    constexpr int semitonesPerOctave = 12;

    const char* const sharpNames[] { "C", "C#", "D", "D#", "E", "F",
                                     "F#", "G", "G#", "A", "A#", "B" };
}

double midiToFrequency (double midiNote, double referenceHz)
{
    return referenceHz * std::pow (2.0, (midiNote - a4Midi) / semitonesPerOctave);
}

double frequencyToMidi (double frequencyHz, double referenceHz)
{
    if (frequencyHz <= 0.0 || referenceHz <= 0.0)
        return 0.0;

    return a4Midi + semitonesPerOctave * std::log2 (frequencyHz / referenceHz);
}

DetectedNote analyseFrequency (double frequencyHz, double referenceHz)
{
    DetectedNote result;

    if (frequencyHz <= 0.0)
        return result;

    const double midiExact = frequencyToMidi (frequencyHz, referenceHz);
    const int midiRounded = (int) std::llround (midiExact);
    const double cents = (midiExact - (double) midiRounded) * 100.0;

    result.midi = midiRounded;
    result.octave = midiRounded / semitonesPerOctave - 1;
    result.name = sharpNames[pitchClassOf (midiRounded)];
    result.cents = (float) cents;
    result.valid = true;
    return result;
}

int noteNameToMidi (const juce::String& name)
{
    auto text = name.trim().toUpperCase();
    if (text.isEmpty())
        return -1;

    int pitchClass = -1;
    switch (text[0])
    {
        case 'C': pitchClass = 0;  break;
        case 'D': pitchClass = 2;  break;
        case 'E': pitchClass = 4;  break;
        case 'F': pitchClass = 5;  break;
        case 'G': pitchClass = 7;  break;
        case 'A': pitchClass = 9;  break;
        case 'B': pitchClass = 11; break;
        default: return -1;
    }

    int index = 1;
    while (index < text.length())
    {
        const auto c = text[index];
        if (c == '#')      { ++pitchClass; ++index; }
        else if (c == 'B') { --pitchClass; ++index; } // 'B' as flat after the letter
        else               break;
    }

    // Octave digits (may be negative).
    const auto octaveText = text.substring (index);
    if (octaveText.isEmpty() || ! octaveText.containsOnly ("-0123456789"))
        return -1;

    const int octave = octaveText.getIntValue();
    return (octave + 1) * semitonesPerOctave + pitchClass;
}

juce::String midiToNoteName (int midiNote)
{
    return juce::String (sharpNames[pitchClassOf (midiNote)])
             + juce::String (midiNote / semitonesPerOctave - 1);
}

} // namespace cursomusica::music
