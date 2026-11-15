#include "Course/Intervals.h"

#include "Course/NoteMath.h"

#include <array>

namespace cursomusica::course
{

namespace
{
    struct Definition
    {
        int number;
        const char* numberName;
        const char* quality;
        const char* shortName;
    };

    // One entry per semitone 0..12, in the order the movable frame is read.
    // The quality of a semitone distance is unambiguous in this range, so the
    // table is the single source of truth for every interval the course names.
    constexpr std::array<Definition, 13> table {{
        { 1, "uníssono", "justa",     "1J" },  // 0
        { 2, "segunda",  "menor",     "2m" },  // 1
        { 2, "segunda",  "maior",     "2M" },  // 2
        { 3, "terça",    "menor",     "3m" },  // 3
        { 3, "terça",    "maior",     "3M" },  // 4
        { 4, "quarta",   "justa",     "4J" },  // 5
        { 4, "quarta",   "aumentada", "4A" },  // 6 (trítono)
        { 5, "quinta",   "justa",     "5J" },  // 7
        { 5, "quinta",   "aumentada", "5A" },  // 8
        { 6, "sexta",    "menor",     "6m" },  // 9
        { 6, "sexta",    "maior",     "6M" },  // 10
        { 7, "sétima",   "maior",     "7M" },  // 11
        { 8, "oitava",   "justa",     "8J" },  // 12
    }};
}

IntervalInfo describeInterval (int semitones)
{
    const int clamped = juce::jlimit (0, 12, semitones);
    const auto& def = table[(size_t) clamped];

    IntervalInfo info;
    info.semitones = clamped;
    info.number = def.number;
    info.numberName = juce::String::fromUTF8 (def.numberName);
    info.quality = juce::String::fromUTF8 (def.quality);
    info.shortName = def.shortName;
    info.name = info.numberName + " " + info.quality;

    info.perfect = info.quality == "justa";
    info.major = info.quality == "maior";
    info.minor = info.quality == "menor";
    info.augmented = info.quality == "aumentada";
    info.diminished = info.quality == "diminuta";
    return info;
}

juce::String intervalName (int semitones)
{
    return describeInterval (semitones).name;
}

juce::String intervalShortName (int semitones)
{
    return describeInterval (semitones).shortName;
}

int semitonesBetween (int midiA, int midiB)
{
    return std::abs (midiB - midiA);
}

std::vector<MobileFrameRow> mobileFrame (int rootPitchClass)
{
    const int root = ((rootPitchClass % 12) + 12) % 12;
    std::vector<MobileFrameRow> rows;
    rows.reserve (13);

    for (int semitones = 0; semitones <= 12; ++semitones)
    {
        MobileFrameRow row;
        row.semitones = semitones;
        row.interval = intervalName (semitones);

        // Note name of the offset, spelled the way the course spells note names
        // (sharps). Octave 4 is arbitrary: the frame is movable, so only the
        // letter (and any sharp) is kept.
        row.noteName = music::midiToNoteName (60 + root + semitones)
                           .retainCharacters ("ABCDEFG#");
        rows.push_back (std::move (row));
    }

    return rows;
}

bool isConsonant (int semitones)
{
    const int s = juce::jlimit (0, 12, semitones);
    return s == 0 || s == 3 || s == 4 || s == 5 || s == 7 || s == 8 || s == 9 || s == 12;
}

} // namespace cursomusica::course
