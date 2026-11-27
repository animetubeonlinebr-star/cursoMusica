#pragma once

#include <juce_core/juce_core.h>

#include <algorithm>
#include <vector>

#include "Course/RestNotes.h"

namespace cursomusica::course::harmony
{

// Harmonic library of the improvisation programme (docs/MUSIC.md, "Programa de
// estudo de improvisação"). Two catalogues, with different jobs:
//
//   - cadences C01..C31 name the *harmonic model* a topic teaches (a cadence,
//     a cycle, a blues, a turnaround);
//   - backing models H1..H20 are the operational beds: the exact chords the app
//     plays, and what the student's notes are judged against.
//
// The programme's central rule: no improvisation exercise runs on a bare scale.
// Every exercise declares the bed it runs over, and the bed the student hears is
// the bed the evaluation uses — both come from the same model here, so they
// cannot drift apart.
//
// Pitch classes are 0..11 (0 = C). Chords carry their root so the app can pick
// the chord scale without guessing from the label.
//
// Pure data and pure functions: no audio, no UI (tests/TestMain.cpp).

struct Chord
{
    juce::String label;            // "Dm7", "Cmaj7"
    int rootPitchClass = 0;
    std::vector<int> pitchClasses; // sorted, unique
};

struct CadenceDef
{
    juce::String code;     // "C22"
    juce::String family;   // "F7"
    juce::String name;     // "II–V–I maior"
    juce::String degrees;  // "ii7 – V7 – Imaj7"
    juce::String example;  // "Dm7 – G7 – Cmaj7"
    std::vector<Chord> chords;
};

struct BackingModelDef
{
    juce::String code;      // "H8"
    juce::String name;      // "II–V–I maior"
    juce::String example;   // "Dm7 – G7 – Cmaj7"
    std::vector<Chord> chords;
    bool sambaBed = false;  // H20: the samba instrumentation (BackingStyle::samba)
};

namespace detail
{
    inline std::vector<int> pcs (std::initializer_list<int> values)
    {
        std::vector<int> out (values);
        for (auto& pc : out)
            pc = ((pc % 12) + 12) % 12;
        std::sort (out.begin(), out.end());
        out.erase (std::unique (out.begin(), out.end()), out.end());
        return out;
    }

    inline Chord chord (const char* label, int root, std::initializer_list<int> values)
    {
        return { juce::String::fromUTF8 (label), ((root % 12) + 12) % 12, pcs (values) };
    }

    inline bool hasInterval (const Chord& c, int interval)
    {
        const int pc = ((c.rootPitchClass + interval) % 12 + 12) % 12;
        return std::find (c.pitchClasses.begin(), c.pitchClasses.end(), pc) != c.pitchClasses.end();
    }
}

// The chord scale the app expects the student to use over `chord` (docs/MUSIC.md,
// "Relação entre escalas e acordes"): major and maj7 take the major scale,
// dominant sevenths the mixolydian, minor sevenths the dorian, half-diminished
// the locrian, diminished sevenths the whole-half diminished, minor with a major
// seventh the melodic minor. The scale is returned as pitch classes.
inline std::vector<int> chordScaleFor (const Chord& chord)
{
    using namespace detail;

    std::vector<int> intervals { 0, 2, 4, 5, 7, 9, 11 };   // major / ionian

    const bool minorThird = hasInterval (chord, 3);
    const bool majorThird = hasInterval (chord, 4);
    const bool flatFifth = hasInterval (chord, 6);
    const bool minorSeventh = hasInterval (chord, 10);
    const bool majorSeventh = hasInterval (chord, 11);

    // A chord with a major third is a major-family chord, even when it also
    // carries an altered ninth (E7#9 holds both G and G#): the quality is read
    // from the third first, then from the fifth and the seventh.
    if (majorThird && minorSeventh && flatFifth)
        intervals = { 0, 2, 4, 6, 7, 9, 10 };              // lydian dominant
    else if (majorThird && minorSeventh)
        intervals = { 0, 2, 4, 5, 7, 9, 10 };              // mixolydian
    else if (majorThird)
        intervals = { 0, 2, 4, 5, 7, 9, 11 };              // major
    else if (minorThird && flatFifth && minorSeventh)
        intervals = { 0, 1, 3, 5, 6, 8, 10 };              // locrian
    else if (minorThird && flatFifth && majorSeventh)
        intervals = { 0, 2, 3, 5, 6, 8, 11 };              // locrian natural 9
    else if (minorThird && majorSeventh)
        intervals = { 0, 2, 3, 5, 7, 9, 11 };              // melodic minor
    else if (minorThird)
        intervals = { 0, 2, 3, 5, 7, 9, 10 };              // dorian

    std::vector<int> out;
    out.reserve (intervals.size());
    for (auto interval : intervals)
        out.push_back (((chord.rootPitchClass + interval) % 12 + 12) % 12);
    std::sort (out.begin(), out.end());
    return out;
}

// The 31 cadences of the catalogue (doc §2.1). Chords are written in C; the
// exercise transposes them with the student's key (Course/Transposition.h).
inline const std::vector<CadenceDef>& cadences()
{
    using namespace detail;
    static const std::vector<CadenceDef> list {
        { "C01", "F1", "Vamp maior", "I – IV", "C – F",
          { chord ("C", 0, { 0, 4, 7 }), chord ("F", 5, { 5, 9, 0 }) } },
        { "C02", "F1", "Vamp menor", "i – iv", "Am – Dm",
          { chord ("Am", 9, { 9, 0, 4 }), chord ("Dm", 2, { 2, 5, 9 }) } },
        { "C03", "F2", "Cadência plagal", "IV – I", "F – C",
          { chord ("F", 5, { 5, 9, 0 }), chord ("C", 0, { 0, 4, 7 }) } },
        { "C04", "F2", "Cadência autêntica simples", "V – I", "G – C",
          { chord ("G", 7, { 7, 11, 2 }), chord ("C", 0, { 0, 4, 7 }) } },
        { "C05", "F2", "Cadência autêntica completa", "I – IV – V – I", "C – F – G – C",
          { chord ("C", 0, { 0, 4, 7 }), chord ("F", 5, { 5, 9, 0 }),
            chord ("G", 7, { 7, 11, 2 }), chord ("C", 0, { 0, 4, 7 }) } },
        { "C06", "F2", "Cadência dominante menor", "i – iv – V7 – i", "Am – Dm – E7 – Am",
          { chord ("Am", 9, { 9, 0, 4 }), chord ("Dm", 2, { 2, 5, 9 }),
            chord ("E7", 4, { 4, 8, 11, 2 }), chord ("Am", 9, { 9, 0, 4 }) } },
        { "C07", "F2", "Progressão tonal tradicional", "I – V – I", "C – G – C",
          { chord ("C", 0, { 0, 4, 7 }), chord ("G", 7, { 7, 11, 2 }),
            chord ("C", 0, { 0, 4, 7 }) } },
        { "C08", "F2", "Progressão country", "I – V – I – IV – I – V – I", "C – G – C – F – C – G – C",
          { chord ("C", 0, { 0, 4, 7 }), chord ("G", 7, { 7, 11, 2 }),
            chord ("C", 0, { 0, 4, 7 }), chord ("F", 5, { 5, 9, 0 }),
            chord ("C", 0, { 0, 4, 7 }), chord ("G", 7, { 7, 11, 2 }),
            chord ("C", 0, { 0, 4, 7 }) } },
        { "C09", "F3", "Progressão blues básica", "I7 – IV7 – V7", "C7 – F7 – G7",
          { chord ("C7", 0, { 0, 4, 7, 10 }), chord ("F7", 5, { 5, 9, 0, 3 }),
            chord ("G7", 7, { 7, 11, 2, 5 }) } },
        { "C10", "F3", "Blues de 12 compassos", "I7 | IV7 | I7 | V7–IV7–I7–V7",
          "C7 | F7 | C7 | G7–F7–C7–G7",
          { chord ("C7", 0, { 0, 4, 7, 10 }), chord ("C7", 0, { 0, 4, 7, 10 }),
            chord ("C7", 0, { 0, 4, 7, 10 }), chord ("C7", 0, { 0, 4, 7, 10 }),
            chord ("F7", 5, { 5, 9, 0, 3 }), chord ("F7", 5, { 5, 9, 0, 3 }),
            chord ("C7", 0, { 0, 4, 7, 10 }), chord ("C7", 0, { 0, 4, 7, 10 }),
            chord ("G7", 7, { 7, 11, 2, 5 }), chord ("F7", 5, { 5, 9, 0, 3 }),
            chord ("C7", 0, { 0, 4, 7, 10 }), chord ("G7", 7, { 7, 11, 2, 5 }) } },
        { "C11", "F3", "Blues com quick change", "I7 – IV7 – I7", "C7 – F7 – C7",
          { chord ("C7", 0, { 0, 4, 7, 10 }), chord ("F7", 5, { 5, 9, 0, 3 }),
            chord ("C7", 0, { 0, 4, 7, 10 }), chord ("C7", 0, { 0, 4, 7, 10 }) } },
        { "C12", "F4", "Plagal com subdominante menor", "I – iv – I", "C – Fm – C",
          { chord ("C", 0, { 0, 4, 7 }), chord ("Fm", 5, { 5, 8, 0 }),
            chord ("C", 0, { 0, 4, 7 }) } },
        { "C13", "F5", "Circular maior", "I – V – vi – IV", "C – G – Am – F",
          { chord ("C", 0, { 0, 4, 7 }), chord ("G", 7, { 7, 11, 2 }),
            chord ("Am", 9, { 9, 0, 4 }), chord ("F", 5, { 5, 9, 0 }) } },
        { "C14", "F5", "Circular alternativa", "I – vi – IV – V", "C – Am – F – G",
          { chord ("C", 0, { 0, 4, 7 }), chord ("Am", 9, { 9, 0, 4 }),
            chord ("F", 5, { 5, 9, 0 }), chord ("G", 7, { 7, 11, 2 }) } },
        { "C15", "F5", "Modal mixolídia", "I – bVII – IV – I", "C – Bb – F – C",
          { chord ("C", 0, { 0, 4, 7 }), chord ("Bb", 10, { 10, 2, 5 }),
            chord ("F", 5, { 5, 9, 0 }), chord ("C", 0, { 0, 4, 7 }) } },
        { "C16", "F5", "Modal menor", "i – bVII – bVI – bVII", "Am – G – F – G",
          { chord ("Am", 9, { 9, 0, 4 }), chord ("G", 7, { 7, 11, 2 }),
            chord ("F", 5, { 5, 9, 0 }), chord ("G", 7, { 7, 11, 2 }) } },
        { "C17", "F5", "Modal menor com dominante", "i – bVII – bVI – V7", "Am – G – F – E7",
          { chord ("Am", 9, { 9, 0, 4 }), chord ("G", 7, { 7, 11, 2 }),
            chord ("F", 5, { 5, 9, 0 }), chord ("E7", 4, { 4, 8, 11, 2 }) } },
        { "C18", "F5", "Tonal descendente", "I – IV – I – V", "C – F – C – G",
          { chord ("C", 0, { 0, 4, 7 }), chord ("F", 5, { 5, 9, 0 }),
            chord ("C", 0, { 0, 4, 7 }), chord ("G", 7, { 7, 11, 2 }) } },
        { "C19", "F4", "Subdominante menor", "Imaj7 – I7 – IVmaj7 – iv7", "Cmaj7 – C7 – Fmaj7 – Fm7",
          { chord ("Cmaj7", 0, { 0, 4, 7, 11 }), chord ("C7", 0, { 0, 4, 7, 10 }),
            chord ("Fmaj7", 5, { 5, 9, 0, 4 }), chord ("Fm7", 5, { 5, 8, 0, 3 }) } },
        { "C20", "F6", "Movimento descendente diatônico", "Imaj7 – vii7 – iii7 – vi7",
          "Cmaj7 – Bm7 – Em7 – Am7",
          { chord ("Cmaj7", 0, { 0, 4, 7, 11 }), chord ("Bm7", 11, { 11, 2, 6, 9 }),
            chord ("Em7", 4, { 4, 7, 11, 2 }), chord ("Am7", 9, { 9, 0, 4, 7 }) } },
        { "C21", "F6", "Neo Soul com empréstimo modal", "Imaj7 – bIIImaj7 – ii7 – V7",
          "Cmaj7 – Ebmaj7 – Dm7 – G7",
          { chord ("Cmaj7", 0, { 0, 4, 7, 11 }), chord ("Ebmaj7", 3, { 3, 7, 10, 2 }),
            chord ("Dm7", 2, { 2, 5, 9, 0 }), chord ("G7", 7, { 7, 11, 2, 5 }) } },
        { "C22", "F7", "II–V–I maior", "ii7 – V7 – Imaj7", "Dm7 – G7 – Cmaj7",
          { chord ("Dm7", 2, { 2, 5, 9, 0 }), chord ("G7", 7, { 7, 11, 2, 5 }),
            chord ("Cmaj7", 0, { 0, 4, 7, 11 }) } },
        { "C23", "F7", "II–V–I menor", "iiø7 – V7(b9) – im7", "Dm7(b5) – G7(b9) – Cm7",
          { chord ("Dm7(b5)", 2, { 2, 5, 8, 0 }), chord ("G7(b9)", 7, { 7, 11, 2, 8 }),
            chord ("Cm7", 0, { 0, 3, 7, 10 }) } },
        { "C24", "F7", "Turnaround diatônico", "Imaj7 – vi7 – ii7 – V7", "Cmaj7 – Am7 – Dm7 – G7",
          { chord ("Cmaj7", 0, { 0, 4, 7, 11 }), chord ("Am7", 9, { 9, 0, 4, 7 }),
            chord ("Dm7", 2, { 2, 5, 9, 0 }), chord ("G7", 7, { 7, 11, 2, 5 }) } },
        { "C25", "F7", "Turnaround com dominantes secundárias", "I – VI7 – II7 – V7",
          "C – A7 – D7 – G7",
          { chord ("C", 0, { 0, 4, 7 }), chord ("A7", 9, { 9, 1, 4, 7 }),
            chord ("D7", 2, { 2, 6, 9, 0 }), chord ("G7", 7, { 7, 11, 2, 5 }) } },
        { "C26", "F7", "Ciclo de quintas ampliado", "iii7 – vi7 – ii7 – V7 – Imaj7",
          "Em7 – Am7 – Dm7 – G7 – Cmaj7",
          { chord ("Em7", 4, { 4, 7, 11, 2 }), chord ("Am7", 9, { 9, 0, 4, 7 }),
            chord ("Dm7", 2, { 2, 5, 9, 0 }), chord ("G7", 7, { 7, 11, 2, 5 }),
            chord ("Cmaj7", 0, { 0, 4, 7, 11 }) } },
        { "C27", "F7", "Dominantes secundárias encadeadas", "I – III7 – vi – II7 – V7 – I",
          "C – E7 – Am – D7 – G7 – C",
          { chord ("C", 0, { 0, 4, 7 }), chord ("E7", 4, { 4, 8, 11, 2 }),
            chord ("Am", 9, { 9, 0, 4 }), chord ("D7", 2, { 2, 6, 9, 0 }),
            chord ("G7", 7, { 7, 11, 2, 5 }), chord ("C", 0, { 0, 4, 7 }) } },
        { "C28", "F7", "Backdoor cadence", "iv7 – bVII7 – Imaj7", "Fm7 – Bb7 – Cmaj7",
          { chord ("Fm7", 5, { 5, 8, 0, 3 }), chord ("Bb7", 10, { 10, 2, 5, 8 }),
            chord ("Cmaj7", 0, { 0, 4, 7, 11 }) } },
        { "C29", "F3", "Blues com diminuto de passagem", "I7 – #Iº7 – ii7 – V7",
          "C7 – C#º7 – Dm7 – G7",
          { chord ("C7", 0, { 0, 4, 7, 10 }), chord ("C#º7", 1, { 1, 4, 7, 10 }),
            chord ("Dm7", 2, { 2, 5, 9, 0 }), chord ("G7", 7, { 7, 11, 2, 5 }) } },
        { "C30", "F3", "Turnaround blues com dominantes", "I7 – VI7 – II7 – V7",
          "C7 – A7 – D7 – G7",
          { chord ("C7", 0, { 0, 4, 7, 10 }), chord ("A7", 9, { 9, 1, 4, 7 }),
            chord ("D7", 2, { 2, 6, 9, 0 }), chord ("G7", 7, { 7, 11, 2, 5 }) } },
        { "C31", "F8", "II–V–I com extensões", "ii9 – V13 – Imaj9", "Dm9 – G13 – Cmaj9",
          { chord ("Dm9", 2, { 2, 5, 9, 0, 4 }), chord ("G13", 7, { 7, 11, 2, 5, 4 }),
            chord ("Cmaj9", 0, { 0, 4, 7, 11, 2 }) } },
    };
    return list;
}

// The 20 backing models (doc §3), in the key the document writes them.
inline const std::vector<BackingModelDef>& models()
{
    using namespace detail;
    static const std::vector<BackingModelDef> list {
        { "H1", "Vamp de 1 acorde menor", "Am7",
          { chord ("Am7", 9, { 9, 0, 4, 7 }) }, false },
        { "H2", "Vamp de 1 acorde maior", "Cmaj7",
          { chord ("Cmaj7", 0, { 0, 4, 7, 11 }) }, false },
        { "H3", "Vamp de 1 acorde dominante", "E7#9",
          { chord ("E7#9", 4, { 4, 8, 11, 2, 7 }) }, false },
        { "H4", "Vamp modal de 2 acordes", "Dm7 – G7",
          { chord ("Dm7", 2, { 2, 5, 9, 0 }), chord ("G7", 7, { 7, 11, 2, 5 }) }, false },
        { "H5", "Vamp de 2 acordes", "Am7 – D7",
          { chord ("Am7", 9, { 9, 0, 4, 7 }), chord ("D7", 2, { 2, 6, 9, 0 }) }, false },
        { "H6", "Célula harmônica maior", "Cmaj7 – Fmaj7",
          { chord ("Cmaj7", 0, { 0, 4, 7, 11 }), chord ("Fmaj7", 5, { 5, 9, 0, 4 }) }, false },
        { "H7", "Célula harmônica menor", "Am7 – Fmaj7",
          { chord ("Am7", 9, { 9, 0, 4, 7 }), chord ("Fmaj7", 5, { 5, 9, 0, 4 }) }, false },
        { "H8", "II–V–I maior", "Dm7 – G7 – Cmaj7",
          { chord ("Dm7", 2, { 2, 5, 9, 0 }), chord ("G7", 7, { 7, 11, 2, 5 }),
            chord ("Cmaj7", 0, { 0, 4, 7, 11 }) }, false },
        { "H9", "II–V–I menor", "Bm7(b5) – E7 – Am7",
          { chord ("Bm7(b5)", 11, { 11, 2, 5, 9 }), chord ("E7", 4, { 4, 8, 11, 2 }),
            chord ("Am7", 9, { 9, 0, 4, 7 }) }, false },
        { "H10", "Turnaround maior", "Cmaj7 – Am7 – Dm7 – G7",
          { chord ("Cmaj7", 0, { 0, 4, 7, 11 }), chord ("Am7", 9, { 9, 0, 4, 7 }),
            chord ("Dm7", 2, { 2, 5, 9, 0 }), chord ("G7", 7, { 7, 11, 2, 5 }) }, false },
        { "H11", "Turnaround dominante", "C7 – A7 – D7 – G7",
          { chord ("C7", 0, { 0, 4, 7, 10 }), chord ("A7", 9, { 9, 1, 4, 7 }),
            chord ("D7", 2, { 2, 6, 9, 0 }), chord ("G7", 7, { 7, 11, 2, 5 }) }, false },
        { "H12", "Blues maior", "Blues de 12 compassos em A",
          { chord ("A7", 9, { 9, 1, 4, 7 }), chord ("A7", 9, { 9, 1, 4, 7 }),
            chord ("A7", 9, { 9, 1, 4, 7 }), chord ("A7", 9, { 9, 1, 4, 7 }),
            chord ("D7", 2, { 2, 6, 9, 0 }), chord ("D7", 2, { 2, 6, 9, 0 }),
            chord ("A7", 9, { 9, 1, 4, 7 }), chord ("A7", 9, { 9, 1, 4, 7 }),
            chord ("E7", 4, { 4, 8, 11, 2 }), chord ("D7", 2, { 2, 6, 9, 0 }),
            chord ("A7", 9, { 9, 1, 4, 7 }), chord ("E7", 4, { 4, 8, 11, 2 }) }, false },
        { "H13", "Blues menor", "Blues de 12 compassos em Am",
          { chord ("Am7", 9, { 9, 0, 4, 7 }), chord ("Am7", 9, { 9, 0, 4, 7 }),
            chord ("Am7", 9, { 9, 0, 4, 7 }), chord ("Am7", 9, { 9, 0, 4, 7 }),
            chord ("Dm7", 2, { 2, 5, 9, 0 }), chord ("Dm7", 2, { 2, 5, 9, 0 }),
            chord ("Am7", 9, { 9, 0, 4, 7 }), chord ("Am7", 9, { 9, 0, 4, 7 }),
            chord ("F7", 5, { 5, 9, 0, 3 }), chord ("E7", 4, { 4, 8, 11, 2 }),
            chord ("Am7", 9, { 9, 0, 4, 7 }), chord ("E7", 4, { 4, 8, 11, 2 }) }, false },
        { "H14", "Blues jazzístico", "Blues de 12 compassos em F",
          { chord ("F7", 5, { 5, 9, 0, 3 }), chord ("F7", 5, { 5, 9, 0, 3 }),
            chord ("F7", 5, { 5, 9, 0, 3 }), chord ("F7", 5, { 5, 9, 0, 3 }),
            chord ("Bb7", 10, { 10, 2, 5, 8 }), chord ("Bb7", 10, { 10, 2, 5, 8 }),
            chord ("F7", 5, { 5, 9, 0, 3 }), chord ("F7", 5, { 5, 9, 0, 3 }),
            chord ("C7", 0, { 0, 4, 7, 10 }), chord ("Bb7", 10, { 10, 2, 5, 8 }),
            chord ("F7", 5, { 5, 9, 0, 3 }), chord ("C7", 0, { 0, 4, 7, 10 }) }, false },
        { "H15", "Standard AABA", "Rhythm Changes em Bb",
          { chord ("Bb", 10, { 10, 2, 5 }), chord ("G7", 7, { 7, 11, 2, 5 }),
            chord ("Cm7", 0, { 0, 3, 7, 10 }), chord ("F7", 5, { 5, 9, 0, 3 }),
            chord ("Bb", 10, { 10, 2, 5 }), chord ("G7", 7, { 7, 11, 2, 5 }),
            chord ("Cm7", 0, { 0, 3, 7, 10 }), chord ("F7", 5, { 5, 9, 0, 3 }),
            chord ("D7", 2, { 2, 6, 9, 0 }), chord ("G7", 7, { 7, 11, 2, 5 }),
            chord ("C7", 0, { 0, 4, 7, 10 }), chord ("F7", 5, { 5, 9, 0, 3 }),
            chord ("Bb", 10, { 10, 2, 5 }), chord ("G7", 7, { 7, 11, 2, 5 }),
            chord ("Cm7", 0, { 0, 3, 7, 10 }), chord ("F7", 5, { 5, 9, 0, 3 }),
            chord ("Bb", 10, { 10, 2, 5 }), chord ("G7", 7, { 7, 11, 2, 5 }),
            chord ("Cm7", 0, { 0, 3, 7, 10 }), chord ("F7", 5, { 5, 9, 0, 3 }),
            chord ("Bb", 10, { 10, 2, 5 }), chord ("Bb", 10, { 10, 2, 5 }),
            chord ("Bb", 10, { 10, 2, 5 }), chord ("Bb", 10, { 10, 2, 5 }) }, false },
        { "H16", "Standard com modulação", "II–V–I encadeados em tons diferentes",
          { chord ("Dm7", 2, { 2, 5, 9, 0 }), chord ("G7", 7, { 7, 11, 2, 5 }),
            chord ("Cmaj7", 0, { 0, 4, 7, 11 }), chord ("Em7", 4, { 4, 7, 11, 2 }),
            chord ("A7", 9, { 9, 1, 4, 7 }), chord ("Dmaj7", 2, { 2, 6, 9, 1 }) }, false },
        { "H17", "Progressão fusion", "Am9 – D13 – Gmaj9 – Cmaj9",
          { chord ("Am9", 9, { 9, 0, 4, 7, 11 }), chord ("D13", 2, { 2, 6, 9, 0, 11 }),
            chord ("Gmaj9", 7, { 7, 11, 2, 6, 9 }), chord ("Cmaj9", 0, { 0, 4, 7, 11, 2 }) }, false },
        { "H18", "Progressão modal", "Em7 – Fmaj7",
          { chord ("Em7", 4, { 4, 7, 11, 2 }), chord ("Fmaj7", 5, { 5, 9, 0, 4 }) }, false },
        { "H19", "Progressão espanhola", "Am – Bb – E7",
          { chord ("Am", 9, { 9, 0, 4 }), chord ("Bb", 10, { 10, 2, 5 }),
            chord ("E7", 4, { 4, 8, 11, 2 }) }, false },
        { "H20", "Standard brasileiro", "Samba em tonalidade definida",
          { chord ("Cmaj7", 0, { 0, 4, 7, 11 }), chord ("A7", 9, { 9, 1, 4, 7 }),
            chord ("Dm7", 2, { 2, 5, 9, 0 }), chord ("G7", 7, { 7, 11, 2, 5 }) }, true },
    };
    return list;
}

inline const CadenceDef* findCadence (const juce::String& code)
{
    for (const auto& cadence : cadences())
        if (cadence.code == code)
            return &cadence;
    return nullptr;
}

inline const BackingModelDef* findModel (const juce::String& code)
{
    for (const auto& model : models())
        if (model.code == code)
            return &model;
    return nullptr;
}

// Doc §3.1: which cadences each backing model can represent. Used to check that
// an exercise declares a cadence its bed can actually deliver.
inline std::vector<juce::String> compatibleCadences (const juce::String& modelCode)
{
    if (modelCode == "H1" || modelCode == "H2" || modelCode == "H3")
        return { "C01", "C02" };
    if (modelCode == "H4" || modelCode == "H5" || modelCode == "H6" || modelCode == "H7")
        return { "C01", "C15", "C16", "C18" };
    if (modelCode == "H8" || modelCode == "H9")
        return { "C22", "C23", "C31" };
    if (modelCode == "H10" || modelCode == "H11")
        return { "C24", "C25", "C26", "C27", "C30" };
    if (modelCode == "H12" || modelCode == "H13" || modelCode == "H14")
        return { "C09", "C10", "C11", "C29", "C30" };
    if (modelCode == "H15" || modelCode == "H16")
        return { "C20", "C21", "C22", "C23", "C24", "C25", "C26", "C27", "C28" };
    if (modelCode == "H17" || modelCode == "H18" || modelCode == "H19")
        return { "C15", "C16", "C17", "C19", "C21", "C27", "C28" };
    if (modelCode == "H20")
        return { "C13", "C14", "C21", "C24", "C31" };
    return {};
}

// The seven harmonic levels of doc §1.1 (P1..P7), which replace "more chords =
// harder" with an explicit progression: static centre, two-chord movement,
// harmonic cell, turnaround, twelve-bar blues, a full form, a form that
// modulates.
inline juce::String levelCode (int level)
{
    return "P" + juce::String (level);
}

inline juce::String levelName (int level)
{
    switch (level)
    {
        case 1: return juce::String::fromUTF8 ("vamp de 1 acorde");
        case 2: return juce::String::fromUTF8 ("vamp de 2 acordes");
        case 3: return juce::String::fromUTF8 ("célula harmônica");
        case 4: return juce::String::fromUTF8 ("turnaround");
        case 5: return juce::String::fromUTF8 ("blues de 12 compassos");
        case 6: return juce::String::fromUTF8 ("standard / forma musical");
        case 7: return juce::String::fromUTF8 ("standard com modulação");
        default: return {};
    }
}

// The form of `model` as improvisation segments: one chord per bar, each with
// the chord scale the app expects. This is the single source of the harmonic
// context — the bed the student hears and the notes the app accepts.
inline std::vector<HarmonicSegment> timelineFor (const BackingModelDef& model)
{
    std::vector<HarmonicSegment> timeline;
    timeline.reserve (model.chords.size());

    for (const auto& chord : model.chords)
    {
        HarmonicSegment segment;
        segment.bars = 1;
        segment.context.chordPitchClasses = chord.pitchClasses;
        segment.context.scalePitchClasses = chordScaleFor (chord);
        timeline.push_back (std::move (segment));
    }

    return timeline;
}

// Total bars of a timeline, so the caller knows when the form repeats.
inline int totalBars (const std::vector<HarmonicSegment>& timeline)
{
    int bars = 0;
    for (const auto& segment : timeline)
        bars += segment.bars;
    return bars;
}

// The segment in force at a given bar (the form loops, like the bed does).
inline const HarmonicSegment* segmentAtBar (const std::vector<HarmonicSegment>& timeline, int bar)
{
    const int bars = totalBars (timeline);
    if (timeline.empty() || bars <= 0)
        return nullptr;

    int wrapped = ((bar % bars) + bars) % bars;
    for (const auto& segment : timeline)
    {
        if (wrapped < segment.bars)
            return &segment;
        wrapped -= segment.bars;
    }
    return &timeline.back();
}

} // namespace cursomusica::course::harmony
