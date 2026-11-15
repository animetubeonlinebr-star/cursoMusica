#pragma once

#include <juce_core/juce_core.h>

#include <vector>

namespace cursomusica::course
{

// Pure interval theory for module 2 (Etapa 2 — teoria dos intervalos e percepção).
//
// Deliberately free of audio and UI: it turns a distance in semitones into the
// interval the student must name (terça maior, quinta justa, sétima menor…) and
// back, so the lesson text, the quizzes and the detector-based exercises all
// share one definition. Unit-tested headless (tests/TestMain.cpp).
//
// The number of an interval counts letter names (Dó→Mi is a third) and the
// quality comes from the exact semitone distance (Dó→Mi = 4 semitons = terça
// maior). Because that mapping is unambiguous within an octave, a semitone count
// is enough to name the interval in this course.

struct IntervalInfo
{
    int semitones = 0;          // 0..12 (0 = uníssono, 12 = oitava)
    int number = 1;             // 1, 2, 3, … (segunda, terça, …) — simple form
    juce::String numberName;    // "uníssono", "segunda", "terça", …
    juce::String quality;       // "justa", "maior", "menor", "aumentada", "diminuta"
    juce::String shortName;     // "3m", "3M", "5J", "4A", "5d"
    juce::String name;          // "terça maior"

    bool perfect = false;       // justo (1ª, 4ª, 5ª, 8ª)
    bool major = false;
    bool minor = false;
    bool augmented = false;
    bool diminished = false;
};

// Describes the interval of `semitones` (clamped to 0..12). Semitones above 12
// are described by their simple form (13 → the same as 1, an octave plus a
// second), which is how the course names compound intervals at this level.
IntervalInfo describeInterval (int semitones);

// Interval name in Portuguese ("terça maior"). Same as describeInterval().name.
juce::String intervalName (int semitones);

// Short label ("3M"). Same as describeInterval().shortName.
juce::String intervalShortName (int semitones);

// The interval between two notes, in semitones and with the direction. Returns
// the absolute distance; `ascending` tells which note was higher.
int semitonesBetween (int midiA, int midiB);

// The "quadro móvel": for a root pitch class, the semitone offsets 0..12 with
// the interval name and the note name that offset lands on. This is the movable
// chart the student transposes to any root; content renders it as a table and
// tests check it lines up with the note names.
struct MobileFrameRow
{
    int semitones = 0;
    juce::String interval;   // "terça maior"
    juce::String noteName;   // "E" (root C, 4 semitons)
};

std::vector<MobileFrameRow> mobileFrame (int rootPitchClass);

// True when the interval is consonant (justos 1/4/5/8 and terças/sextas). Used
// by the perception topic to sort the intervals the ear finds "stable".
bool isConsonant (int semitones);

} // namespace cursomusica::course
