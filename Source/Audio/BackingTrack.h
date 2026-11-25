#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

#include <array>
#include <atomic>
#include <cstdint>
#include <vector>

namespace cursomusica
{

// Backing track for the practice exercises (client request, 2026-11-18): drums,
// bass and keyboard playing the exercise's chord vamp, so the student has
// something to play over instead of only reading "practice by playing".
//
// Real-time safe: no allocation, no locks, no I/O in the audio callback. The
// message thread publishes a chord progression (pitch classes) under a spin
// lock, exactly like TonePlayer; the audio thread only takes the lock when it is
// free, so a concurrent request can never stall the callback.
//
// Each part owns a fixed slice of the voice pool, so a chord held across the bar
// can never take the voice a drum needs. The keyboard holds the chord until the
// next downbeat instead of decaying away, which is what makes the harmony
// audible under the drums (client: "sem acordes na harmonia").
class BackingTrack
{
public:
    // One chord of the vamp: pitch classes (0 = C … 11 = B) and the MIDI note
    // used as its bass root.
    struct Chord
    {
        std::vector<int> pitchClasses;
        int bassMidi = 45; // A2 by default
    };

    // The two arrangements the course needs so far: a rock/pop bed (keyboard,
    // guitar riff, bass groove, drums) and a samba bed (cavaquinho, 7-string
    // guitar, surdo/pandeiro/rebolo). Client, 2026-11-18: the bed must sound like
    // the style the topic teaches, not the same vamp everywhere.
    enum class Style { rock, samba };

    void prepare (double sampleRate) noexcept;
    void reset() noexcept;

    void setStyle (Style newStyle) noexcept { style.store ((int) newStyle); }
    Style getStyle() const noexcept { return (Style) style.load(); }

    // Module level (1..4). Higher levels get a denser arrangement — a pickup
    // kick, sixteenth hi-hats and a bass answer on the fifth (client: complexity
    // proportional to the level).
    void setLevel (int newLevel) noexcept { level.store (juce::jlimit (1, 4, newLevel)); }
    int getLevel() const noexcept { return level.load(); }

    // Publishes the progression to play. Message thread. An empty progression
    // stops the track.
    void setProgression (const std::vector<Chord>& chords);
    void setBpm (double newBpm) noexcept { bpm.store (juce::jlimit (20.0, 300.0, newBpm)); }
    void setRunning (bool shouldRun) noexcept { running.store (shouldRun); }
    void setGain (float linearGain) noexcept { gain.store (juce::jlimit (0.0f, 1.0f, linearGain)); }

    double getBpm() const noexcept { return bpm.load(); }
    bool isRunning() const noexcept { return running.load(); }
    bool hasProgression() const noexcept { return chordCount.load() > 0; }

    // Index of the chord currently sounding (0-based), for the UI to follow.
    int getCurrentChordIndex() const noexcept { return currentChord.load(); }

    // Pitch-class bitmask (bit 0 = C … bit 11 = B) of the chord currently
    // sounding, so the UI can name it and a test can prove which harmony the
    // audio thread actually adopted. 0 when nothing is playing.
    unsigned getCurrentChordMask() const noexcept { return currentChordMask.load(); }

    // Peak level of the pad part since the last call, so a test can prove the
    // harmony is audible and not buried under the drums. Resets the reading.
    float takePadPeak() noexcept { return padPeak.exchange (0.0f); }

    // Peak level of the plucked part (guitar riff / cavaquinho) since the last
    // call, so a test can prove the style actually plays a second instrument.
    float takeGuitarPeak() noexcept { return guitarPeak.exchange (0.0f); }

    // Adds the backing track into the output buffer. Audio thread.
    void process (juce::AudioBuffer<float>& output, int numSamples) noexcept;

private:
    static constexpr int maxChords = 16;
    static constexpr int maxPitchClasses = 6;

    // One slice per part: a held chord can never starve the drums.
    static constexpr int drumFirst = 0;
    static constexpr int drumVoices = 8;
    static constexpr int bassFirst = drumFirst + drumVoices;
    static constexpr int bassVoices = 4;
    static constexpr int padFirst = bassFirst + bassVoices;
    static constexpr int padVoices = 12;
    static constexpr int guitarFirst = padFirst + padVoices;
    static constexpr int guitarVoices = 10;
    static constexpr int percFirst = guitarFirst + guitarVoices;
    static constexpr int percVoices = 8;
    static constexpr int maxVoices = percFirst + percVoices;

    struct StoredChord
    {
        int pitchClasses[maxPitchClasses] {};
        int count = 0;
        int bassMidi = 45;
    };

    enum class Stage { attack, hold, release };

    // Everything needed to start one voice. `count` voices sound `midi`,
    // `midi + 1`, … so a chord or a drum hit is a single call.
    struct VoiceSpec
    {
        int midi = 60;
        int count = 1;
        float velocity = 0.5f;
        double attackSeconds = 0.005;   // ramp up to full level
        double holdSeconds = 0.0;       // stay at full level, then release
        double releaseSeconds = 0.20;   // decay time constant is this / 4
        float harmonic = 0.0f;          // level of the 2nd partial
        float noiseMix = 0.0f;          // 0 = pure tone, 1 = pure noise
        float highpass = 0.0f;          // one-pole high-pass on the noise
    };

    struct Voice
    {
        bool active = false;
        Stage stage = Stage::attack;
        double phase = 0.0;
        double increment = 0.0;
        float envelope = 0.0f;
        float attackInc = 0.0f;
        float releaseMul = 0.0f;
        int holdSamples = 0;
        float level = 0.0f;
        float harmonic = 0.0f;
        float noiseMix = 0.0f;
        float highpass = 0.0f;
        float hpPrevIn = 0.0f;
        float hpPrevOut = 0.0f;
    };

    // Starts `spec.count` voices from the pool slice starting at `first`.
    void trigger (int first, int sliceSize, const VoiceSpec& spec) noexcept;
    float nextNoise() noexcept;

    double sampleRate = 44100.0;

    // Published by the message thread, read by the audio thread under the lock.
    juce::SpinLock requestLock;
    std::array<StoredChord, maxChords> pendingChords {};
    int pendingCount = 0;

    std::atomic<int> chordCount { 0 };
    std::atomic<unsigned> publishVersion { 0 };
    unsigned consumedVersion = 0;
    std::atomic<int> currentChord { 0 };
    std::atomic<unsigned> currentChordMask { 0 };
    std::atomic<double> bpm { 100.0 };
    std::atomic<bool> running { false };
    std::atomic<float> gain { 0.5f };
    std::atomic<int> style { (int) Style::rock };
    std::atomic<int> level { 1 };
    std::atomic<float> padPeak { 0.0f };
    std::atomic<float> guitarPeak { 0.0f };

    // Audio-thread-only state.
    std::array<StoredChord, maxChords> chords {};
    int activeChords = 0;
    int chordIndex = 0;

    double samplesToNextStep = 0.0;
    int stepInBar = 0; // sixteenth-note step within the bar (0..15)
    bool started = false;

    std::array<Voice, maxVoices> voices {};
    std::uint32_t rngState = 0x9e3779b9u;
};

} // namespace cursomusica
