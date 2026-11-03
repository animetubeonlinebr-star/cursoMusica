#pragma once

#include <juce_core/juce_core.h>

namespace cursomusica::music
{

// Pure music theory: pitch <-> frequency <-> name conversions.
//
// Deliberately free of audio and UI dependencies so it can be unit-tested and
// reused by the tuner, the evaluator and the lesson content.

struct DetectedNote
{
    juce::String name;   // "A", "C#", ...
    int octave = 0;
    int midi = 0;
    float cents = 0.0f;  // deviation from the nearest tempered pitch
    bool valid = false;
};

// MIDI note number to frequency. A4 (MIDI 69) equals referenceHz.
double midiToFrequency (double midiNote, double referenceHz = 440.0);

// Frequency to fractional MIDI note. Returns 0 when frequency is not positive.
double frequencyToMidi (double frequencyHz, double referenceHz = 440.0);

// Nearest note name/octave/cents for a frequency.
DetectedNote analyseFrequency (double frequencyHz, double referenceHz = 440.0);

// Parses a scientific pitch name such as "C#4" or "Eb3" into a MIDI note.
// Returns -1 when the string is not a valid note.
int noteNameToMidi (const juce::String& name);

// Formats a MIDI note as a scientific pitch name ("C#4").
juce::String midiToNoteName (int midiNote);

// Pitch class (0..11) of a MIDI note; C = 0.
inline int pitchClassOf (int midiNote) { return ((midiNote % 12) + 12) % 12; }

} // namespace cursomusica::music
