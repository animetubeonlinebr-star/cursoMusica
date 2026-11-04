#pragma once

#include <juce_audio_utils/juce_audio_utils.h>

#include <vector>

#include "Audio/AudioPortClassifier.h"
#include "UI/Design/Panel.h"

namespace cursomusica
{

// Lists the audio ports the app can actually use, grouped by the direction the
// app sees them (REQ-023): capture ports the app records from, playback ports
// the app plays to.
//
// The stock JUCE device selector labels its lists from the backend, which is
// correct, but a virtual mixer (VoiceMeeter Banana, VB-Audio Cable) names its
// ports from the mixer's side: "Voicemeeter Input" is a place the app *plays
// into*, not a microphone. Read literally, the raw names look swapped, so this
// panel states the true direction next to each name and explains the convention.
class AudioPortsPanel final : public Panel
{
public:
    explicit AudioPortsPanel (juce::AudioDeviceManager& manager);

    // Re-reads the device list from the manager. Call after a device change.
    void refresh();

    void paint (juce::Graphics& g) override;

private:
    struct Entry
    {
        juce::String name;
        audio::PortKind kind = audio::PortKind::unknown;
    };

    void collect();

    juce::AudioDeviceManager& deviceManager;
    std::vector<Entry> entries;
    juce::String mixerNote;
};

} // namespace cursomusica
