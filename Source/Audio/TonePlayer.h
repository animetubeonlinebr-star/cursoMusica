#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

#include <array>
#include <atomic>
#include <vector>

namespace cursomusica
{

// Plays a short sequence of notes for the audio examples in the lessons
// (REQ-004: "todo exemplo é demonstrado com áudio"). A soft sine tone with a
// short attack/release, so an interval can be heard without a sampled
// instrument.
//
// Real-time safe: the audio thread never allocates or blocks. The message
// thread writes the note list under a spin lock; the audio thread only takes the
// lock when it is free, so a concurrent request can never stall the callback.
class TonePlayer
{
public:
    void prepare (double sampleRate) noexcept;

    // Queues `midiNotes` (played in order) at the current tempo. Message thread.
    void play (const std::vector<int>& midiNotes);

    void stop() noexcept;

    bool isPlaying() const noexcept { return active.load(); }

    // Adds the tone into the output buffer. Audio thread.
    void process (juce::AudioBuffer<float>& output, int numSamples) noexcept;

private:
    static constexpr int maxNotes = 64;
    static constexpr int maxVoices = 8;

    void prepareVoice (int midi, double sampleRate) noexcept;

    double sampleRate = 44100.0;

    // Written by the message thread, read by the audio thread under the lock.
    juce::SpinLock requestLock;
    std::array<int, maxNotes> pendingNotes {};
    int pendingCount = 0;

    std::atomic<bool> active { false };
    std::atomic<double> noteSeconds { 0.55 };

    // Audio-thread-only playback state.
    std::array<int, maxNotes> notes {};
    int noteCount = 0;
    int noteIndex = 0;
    double samplesIntoNote = 0.0;
    double samplesPerNote = 0.0;

    std::array<double, maxVoices> voicePhase {};
    std::array<double, maxVoices> voiceIncrement {};
    std::array<bool, maxVoices> voiceActive {};
};

} // namespace cursomusica
