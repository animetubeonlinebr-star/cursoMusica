#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

#include <array>
#include <atomic>
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
// The rhythm is a fixed study groove (one chord per bar, four beats):
//   drums    — kick on 1 and 3, snare on 2 and 4, hi-hat on every eighth
//   bass     — root on 1 and 3, fifth on 2 and 4 (an octave below the pad)
//   keyboard — the chord's notes held as a soft pad, re-struck each bar
//
// All three voices are synthesised (sine partials with a short envelope), so no
// sample data is needed and the module stays dependency-free.
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

    void prepare (double sampleRate) noexcept;
    void reset() noexcept;

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

    // Adds the backing track into the output buffer. Audio thread.
    void process (juce::AudioBuffer<float>& output, int numSamples) noexcept;

private:
    static constexpr int maxChords = 16;
    static constexpr int maxPitchClasses = 6;
    static constexpr int maxVoices = 16;

    struct StoredChord
    {
        int pitchClasses[maxPitchClasses] {};
        int count = 0;
        int bassMidi = 45;
    };

    void triggerVoice (int midi, float velocity, double decaySeconds) noexcept;

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

    // Audio-thread-only state.
    std::array<StoredChord, maxChords> chords {};
    int activeChords = 0;
    int chordIndex = 0;

    double samplesToNextStep = 0.0;
    int stepInBar = 0; // eighth-note step within the bar (0..7)
    bool started = false;

    std::array<double, maxVoices> voicePhase {};
    std::array<double, maxVoices> voiceIncrement {};
    std::array<float, maxVoices> voiceEnvelope {};
    std::array<float, maxVoices> voiceDecay {};
    std::array<float, maxVoices> voiceLevel {};
    std::array<bool, maxVoices> voiceActive {};
};

} // namespace cursomusica
