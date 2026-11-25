#include "Audio/BackingTrack.h"

#include <cmath>

namespace cursomusica
{

namespace
{
    // Drum voices are a short pitched blip plus a noise burst; the pitch, the
    // noise mix and the decay carry the timbre.
    constexpr double kickFrequency = 55.0;
    constexpr double snareFrequency = 190.0;
    constexpr double hatFrequency = 8000.0;

    constexpr double kickAttack = 0.002;
    constexpr double snareAttack = 0.001;
    constexpr double hatAttack = 0.001;

    constexpr double kickRelease = 0.42;
    constexpr double snareRelease = 0.30;
    constexpr double hatRelease = 0.09;

    constexpr float kickLevel = 0.85f;
    constexpr float snareLevel = 0.50f;
    constexpr float hatLevel = 0.16f;
    constexpr float bassLevel = 0.40f;

    // The keyboard sat 5x below the kick and its envelope died before beat 3,
    // which is why the client heard "sem acordes na harmonia". It now sits at the
    // level of the other parts and holds the chord across the bar.
    constexpr float padLevel = 0.16f;

    constexpr float kickNoise = 0.10f;
    constexpr float snareNoise = 0.85f;
    constexpr float hatNoise = 0.98f;

    // Kick and bass keep a second partial so they read as a pitch; the pad is a
    // soft two-partial tone; the snare and hat are mostly noise.
    constexpr float kickHarmonic = 0.30f;
    constexpr float bassHarmonic = 0.35f;
    constexpr float padHarmonic = 0.22f;
    constexpr float snareHarmonic = 0.05f;
    constexpr float hatHarmonic = 0.0f;

    // One-pole high-pass applied to the noise burst, so the hat sits above the
    // snare and the snare above the kick instead of all three sounding alike.
    constexpr float kickHighpass = 0.20f;
    constexpr float snareHighpass = 0.62f;
    constexpr float hatHighpass = 0.90f;

    // The pad is released just before the next downbeat so the new chord starts
    // in silence instead of on top of the old one.
    constexpr double padReleaseSeconds = 0.18;

    // Plucked parts: a short pick transient on a bright tone. The guitar riff and
    // the cavaquinho share the timbre and differ in register and decay.
    constexpr float guitarLevel = 0.30f;
    constexpr float guitarHarmonic = 0.55f;
    constexpr float guitarNoise = 0.06f;
    constexpr double guitarRelease = 0.34;

    constexpr float cavaquinhoLevel = 0.26f;
    constexpr float cavaquinhoHarmonic = 0.65f;
    constexpr float cavaquinhoNoise = 0.10f;
    constexpr double cavaquinhoRelease = 0.16;

    // Samba percussion: surdo (low), pandeiro (mid noise), rebolo (high tick).
    constexpr double surdoFrequency = 82.0;
    constexpr float surdoLevel = 0.60f;
    constexpr float surdoNoise = 0.20f;
    constexpr float surdoHarmonic = 0.35f;
    constexpr float surdoHighpass = 0.15f;
    constexpr double surdoRelease = 0.34;

    constexpr double pandeiroFrequency = 1400.0;
    constexpr float pandeiroLevel = 0.18f;
    constexpr float pandeiroNoise = 0.95f;
    constexpr float pandeiroHighpass = 0.70f;
    constexpr double pandeiroRelease = 0.12;

    constexpr double reboloFrequency = 2600.0;
    constexpr float reboloLevel = 0.14f;
    constexpr float reboloNoise = 0.92f;
    constexpr float reboloHighpass = 0.82f;
    constexpr double reboloRelease = 0.07;

    // Voices sum rather than mix, so this keeps a full bar under full scale.
    constexpr float mixHeadroom = 0.28f;

    // One bar is sixteen sixteenth-notes; every pattern below is written on that
    // grid so the two styles share the same clock.
    constexpr int stepsPerBar = 16;

    double midiToFrequency (int midi) noexcept
    {
        return 440.0 * std::pow (2.0, (midi - 69) / 12.0);
    }
}

void BackingTrack::prepare (double sampleRateToUse) noexcept
{
    sampleRate = sampleRateToUse > 0.0 ? sampleRateToUse : 44100.0;
    reset();
}

void BackingTrack::reset() noexcept
{
    samplesToNextStep = 0.0;
    stepInBar = 0;
    started = false;
    chordIndex = 0;
    currentChord.store (0);
    currentChordMask.store (0);
    padPeak.store (0.0f);

    for (auto& voice : voices)
        voice = Voice {};
}

void BackingTrack::setProgression (const std::vector<Chord>& newChords)
{
    // Message thread: take the lock for real. Dropping the request on a busy
    // callback would leave the UI showing a progression the audio never got.
    // The audio thread only ever holds it for the short copy below, and it never
    // waits for it (try-lock), so this cannot stall the callback.
    const juce::SpinLock::ScopedLockType lock (requestLock);

    pendingCount = juce::jmin ((int) newChords.size(), maxChords);
    for (int c = 0; c < pendingCount; ++c)
    {
        auto& stored = pendingChords[(size_t) c];
        const auto& source = newChords[(size_t) c];
        stored.count = juce::jmin ((int) source.pitchClasses.size(), maxPitchClasses);
        for (int p = 0; p < stored.count; ++p)
            stored.pitchClasses[p] = ((source.pitchClasses[(size_t) p] % 12) + 12) % 12;
        stored.bassMidi = source.bassMidi;
    }

    chordCount.store (pendingCount);
    // The version lets the audio thread adopt a new progression even when the
    // chord count matches the previous one (two different 4-chord vamps).
    publishVersion.fetch_add (1);
}

float BackingTrack::nextNoise() noexcept
{
    // xorshift32: cheap, deterministic and allocation-free, so the drum timbre is
    // reproducible in a test.
    rngState ^= rngState << 13;
    rngState ^= rngState >> 17;
    rngState ^= rngState << 5;
    return (float) ((double) rngState / 2147483648.0 - 1.0);
}

void BackingTrack::trigger (int first, int sliceSize, const VoiceSpec& spec) noexcept
{
    const int notes = juce::jlimit (1, juce::jmax (1, sliceSize), spec.count);

    for (int n = 0; n < notes; ++n)
    {
        int slot = -1;
        for (int v = first; v < first + sliceSize; ++v)
            if (! voices[(size_t) v].active)
            {
                slot = v;
                break;
            }

        if (slot < 0)
            return; // this part's slice is full; the others are unaffected

        auto& voice = voices[(size_t) slot];
        voice = Voice {};
        voice.active = true;
        voice.stage = Stage::attack;
        voice.phase = 0.0;
        voice.increment = 2.0 * juce::MathConstants<double>::pi
                            * midiToFrequency (spec.midi + n) / sampleRate;
        voice.envelope = 0.0f;
        voice.attackInc = (float) (1.0 / juce::jmax (1.0, spec.attackSeconds * sampleRate));
        voice.holdSamples = (int) juce::jmax (0.0, spec.holdSeconds * sampleRate);
        voice.releaseMul = (float) std::exp (-4.0 / juce::jmax (1.0, spec.releaseSeconds * sampleRate));
        voice.level = spec.velocity;
        voice.harmonic = spec.harmonic;
        voice.noiseMix = spec.noiseMix;
        voice.highpass = spec.highpass;
    }
}

void BackingTrack::process (juce::AudioBuffer<float>& output, int numSamples) noexcept
{
    if (! running.load())
        return;

    // Take a new progression if the UI published one and the audio thread is not
    // already reading it (the lock is only ever held for the copy below).
    {
        const juce::SpinLock::ScopedTryLockType lock (requestLock);
        const unsigned published = publishVersion.load();
        if (lock.isLocked() && published != consumedVersion)
        {
            consumedVersion = published;
            activeChords = pendingCount;
            for (int c = 0; c < activeChords; ++c)
                chords[(size_t) c] = pendingChords[(size_t) c];
            chordIndex = 0;
            currentChord.store (0);
            samplesToNextStep = 0.0;
            stepInBar = 0;
            started = false;
        }
    }

    if (activeChords <= 0)
        return;

    const double currentBpm = juce::jmax (1.0, bpm.load());
    const double samplesPerStep = (15.0 / currentBpm) * sampleRate; // one sixteenth note
    const double barSeconds = (240.0 / currentBpm);
    const float currentGain = gain.load();
    const int channels = output.getNumChannels();
    // Arrangement density grows with the module level (client: complexity
    // proportional to the level), and the style decides the instrumentation.
    const int density = juce::jlimit (1, 4, level.load());
    const bool samba = style.load() == (int) Style::samba;

    for (int i = 0; i < numSamples; ++i)
    {
        if (samplesToNextStep <= 0.0)
        {
            if (stepInBar == 0)
            {
                // The downbeat starts a bar: move to the next chord, except on
                // the very first bar after a (re)start.
                if (started)
                    chordIndex = (chordIndex + 1) % activeChords;
                started = true;
                currentChord.store (chordIndex);

                const auto& sounding = chords[(size_t) chordIndex];
                unsigned mask = 0;
                for (int p = 0; p < sounding.count; ++p)
                    mask |= 1u << (unsigned) sounding.pitchClasses[(size_t) p];
                currentChordMask.store (mask);

                if (! samba)
                {
                    // Keyboard: the chord as a pad held for the whole bar. Without
                    // the hold the harmony died before beat 3 and the bed sounded
                    // like drums alone. One trigger per chord tone: the chord's
                    // pitches are not semitone neighbours.
                    for (int p = 0; p < sounding.count; ++p)
                    {
                        VoiceSpec pad;
                        pad.midi = 60 + sounding.pitchClasses[(size_t) p];
                        pad.velocity = padLevel;
                        pad.attackSeconds = 0.02;
                        pad.holdSeconds = juce::jmax (0.0, barSeconds - padReleaseSeconds);
                        pad.releaseSeconds = padReleaseSeconds;
                        pad.harmonic = padHarmonic;
                        trigger (padFirst, padVoices, pad);
                    }
                }
                else
                {
                    // Samba: the 7-string guitar (violao 7) holds a low voicing for
                    // the bar; the cavaquinho and the percussion mark the groove.
                    for (int p = 0; p < sounding.count; ++p)
                    {
                        VoiceSpec violao;
                        violao.midi = 48 + sounding.pitchClasses[(size_t) p];
                        violao.velocity = padLevel;
                        violao.attackSeconds = 0.006;
                        violao.holdSeconds = juce::jmax (0.0, barSeconds - padReleaseSeconds);
                        violao.releaseSeconds = padReleaseSeconds;
                        violao.harmonic = padHarmonic;
                        trigger (padFirst, padVoices, violao);
                    }
                }
            }

            const auto& chord = chords[(size_t) chordIndex];
            const int step = stepInBar;

            // A chord stab: one plucked voice per chord tone, in the given
            // octave (octave 5 = MIDI 60). Used by the guitar riff, the
            // cavaquinho and the violao 7.
            auto pluckChord = [&] (int first, int slice, int octave, float lvl,
                                   float harmonic, float noise, double release)
            {
                for (int p = 0; p < chord.count; ++p)
                {
                    VoiceSpec spec;
                    spec.midi = 12 * octave + chord.pitchClasses[(size_t) p];
                    spec.velocity = lvl;
                    spec.attackSeconds = 0.002;
                    spec.holdSeconds = 0.0;
                    spec.releaseSeconds = release;
                    spec.harmonic = harmonic;
                    spec.noiseMix = noise;
                    trigger (first, slice, spec);
                }
            };

            // A drum/percussion hit: a pitched blip plus a filtered noise burst.
            auto hit = [&] (int first, int slice, double frequency, float lvl,
                            float noise, float harmonic, float highpass,
                            double attack, double release)
            {
                VoiceSpec spec;
                spec.midi = (int) frequency;
                spec.velocity = lvl;
                spec.noiseMix = noise;
                spec.harmonic = harmonic;
                spec.highpass = highpass;
                spec.attackSeconds = attack;
                spec.releaseSeconds = release;
                trigger (first, slice, spec);
            };

            if (! samba)
            {
                // Rock/pop: kick on 1 and 3, snare on 2 and 4, hi-hat on every
                // eighth; denser levels add a pickup kick and sixteenth hats.
                if (step == 0 || step == 8 || (density >= 3 && step == 14))
                    hit (drumFirst, drumVoices, kickFrequency, kickLevel, kickNoise,
                         kickHarmonic, kickHighpass, kickAttack, kickRelease);

                if (step == 4 || step == 12)
                    hit (drumFirst, drumVoices, snareFrequency, snareLevel, snareNoise,
                         snareHarmonic, snareHighpass, snareAttack, snareRelease);

                if (step % 2 == 0)
                    hit (drumFirst, drumVoices, hatFrequency, hatLevel, hatNoise,
                         hatHarmonic, hatHighpass, hatAttack, hatRelease);
                else if (density >= 3)
                    hit (drumFirst, drumVoices, hatFrequency, hatLevel * 0.5f, hatNoise,
                         hatHarmonic, hatHighpass, hatAttack, hatRelease);

                // Guitar riff: the chord tones arpeggiated on eighths, so the
                // harmony is played and not only held by the keyboard.
                if (step == 0 || step == 3 || step == 6 || step == 8 || step == 11 || step == 14)
                    pluckChord (guitarFirst, guitarVoices, 5, guitarLevel, guitarHarmonic,
                                guitarNoise, guitarRelease);

                // Bass groove: root on 1 and 3; denser levels answer on the
                // fifth between them.
                if (chord.count > 0 && (step == 0 || step == 8))
                {
                    VoiceSpec bass;
                    bass.midi = chord.bassMidi;
                    bass.velocity = bassLevel;
                    bass.attackSeconds = 0.004;
                    bass.releaseSeconds = 0.55;
                    bass.harmonic = bassHarmonic;
                    trigger (bassFirst, bassVoices, bass);
                }
                else if (chord.count > 0 && density >= 2 && (step == 6 || step == 14))
                {
                    VoiceSpec bass;
                    bass.midi = chord.bassMidi + 7;
                    bass.velocity = bassLevel * 0.8f;
                    bass.attackSeconds = 0.004;
                    bass.releaseSeconds = 0.40;
                    bass.harmonic = bassHarmonic;
                    trigger (bassFirst, bassVoices, bass);
                }
            }
            else
            {
                // Samba: surdo on 1 and 3, pandeiro on every eighth, rebolo on
                // the off-beats (the "teleco-teco" of the tamborim/rebolo).
                if (step == 0 || step == 8)
                    hit (percFirst, percVoices, surdoFrequency, surdoLevel, surdoNoise,
                         surdoHarmonic, surdoHighpass, 0.003, surdoRelease);

                if (step % 2 == 0)
                    hit (percFirst, percVoices, pandeiroFrequency, pandeiroLevel, pandeiroNoise,
                         0.0f, pandeiroHighpass, 0.001, pandeiroRelease);

                if (step == 3 || step == 7 || step == 11 || step == 15)
                    hit (percFirst, percVoices, reboloFrequency, reboloLevel, reboloNoise,
                         0.0f, reboloHighpass, 0.001, reboloRelease);

                // Cavaquinho: partido-alto strumming on the eighths, accented on
                // the second and third beats (steps 6 and 12).
                if (step % 2 == 0)
                {
                    const bool accent = (step == 6 || step == 12);
                    pluckChord (guitarFirst, guitarVoices, 5,
                                cavaquinhoLevel * (accent ? 1.0f : 0.7f),
                                cavaquinhoHarmonic, cavaquinhoNoise, cavaquinhoRelease);
                }

                // Violao 7: the bass string on 1 and on the "and of 3".
                if (chord.count > 0 && (step == 0 || step == 10))
                {
                    VoiceSpec bass;
                    bass.midi = chord.bassMidi;
                    bass.velocity = bassLevel;
                    bass.attackSeconds = 0.004;
                    bass.releaseSeconds = 0.60;
                    bass.harmonic = bassHarmonic;
                    trigger (bassFirst, bassVoices, bass);
                }
            }

            samplesToNextStep += samplesPerStep;
            stepInBar = (stepInBar + 1) % stepsPerBar;
        }

        float padSample = 0.0f;
        float guitarSample = 0.0f;
        float sample = 0.0f;

        for (int v = 0; v < maxVoices; ++v)
        {
            auto& voice = voices[(size_t) v];
            if (! voice.active)
                continue;

            // Envelope: linear attack, flat hold, exponential release.
            switch (voice.stage)
            {
                case Stage::attack:
                    voice.envelope += voice.attackInc;
                    if (voice.envelope >= 1.0f)
                    {
                        voice.envelope = 1.0f;
                        voice.stage = Stage::hold;
                    }
                    break;
                case Stage::hold:
                    if (voice.holdSamples <= 0)
                        voice.stage = Stage::release;
                    else
                        --voice.holdSamples;
                    break;
                case Stage::release:
                    voice.envelope *= voice.releaseMul;
                    break;
            }

            const float tone = (float) std::sin (voice.phase)
                                 + voice.harmonic * (float) std::sin (2.0 * voice.phase);
            const float noise = nextNoise();
            // One-pole high-pass: y = hp * (yPrev + x - xPrev).
            const float filtered = voice.highpass * (voice.hpPrevOut + noise - voice.hpPrevIn);
            voice.hpPrevIn = noise;
            voice.hpPrevOut = filtered;

            const float source = (1.0f - voice.noiseMix) * tone
                                   + voice.noiseMix * filtered;
            const float out = source * voice.envelope * voice.level * currentGain * mixHeadroom;

            sample += out;
            if (v >= padFirst && v < guitarFirst)
                padSample += out;
            else if (v >= guitarFirst && v < percFirst)
                guitarSample += out;

            voice.phase += voice.increment;
            if (voice.phase > juce::MathConstants<double>::twoPi)
                voice.phase -= juce::MathConstants<double>::twoPi;

            if (voice.stage == Stage::release && voice.envelope < 0.0001f)
                voice.active = false;
        }

        for (int ch = 0; ch < channels; ++ch)
            output.addSample (ch, i, sample);

        const float padLevelNow = std::fabs (padSample);
        if (padLevelNow > padPeak.load (std::memory_order_relaxed))
            padPeak.store (padLevelNow, std::memory_order_relaxed);

        const float guitarLevelNow = std::fabs (guitarSample);
        if (guitarLevelNow > guitarPeak.load (std::memory_order_relaxed))
            guitarPeak.store (guitarLevelNow, std::memory_order_relaxed);

        samplesToNextStep -= 1.0;
    }
}

} // namespace cursomusica
