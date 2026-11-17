#pragma once

#include <juce_core/juce_core.h>

namespace cursomusica::audio
{

// The audio device the student chose in Settings, in a form that survives a
// restart.
//
// The tuner reads whatever device the engine has open, so the choice made in
// Settings must be remembered: without it, every launch reopened the first
// device the backend offered and the tuner listened to the wrong input.
struct DeviceSelection
{
    juce::String deviceType;       // e.g. "ASIO", "Windows Audio"
    juce::String inputDeviceName;
    juce::String outputDeviceName;
    double sampleRate = 0.0;       // 0 = let the device choose
    int bufferSize = 0;            // 0 = let the device choose

    bool isEmpty() const noexcept
    {
        return inputDeviceName.isEmpty() && outputDeviceName.isEmpty();
    }
};

// Serialises a selection to a stable string for the settings file.
juce::String serialiseDeviceSelection (const DeviceSelection&);

// Parses a value written by serialiseDeviceSelection. Missing or corrupt input
// yields an empty selection (isEmpty() == true), never a throw.
DeviceSelection parseDeviceSelection (const juce::String&);

// True when a saved selection can still be reopened against the device list the
// backend currently reports: the type matches and every non-empty device name is
// present. A saved device that was unplugged therefore fails and the caller
// falls back to a fresh scan instead of staying silent.
bool deviceSelectionIsAvailable (const DeviceSelection&,
                                 const juce::String& currentTypeName,
                                 const juce::StringArray& inputNames,
                                 const juce::StringArray& outputNames);

} // namespace cursomusica::audio
