#pragma once

#include <juce_core/juce_core.h>

namespace cursomusica::audio
{

// Which way the audio flows, from the app's point of view.
//
//   capture   the app *receives* audio from this device (a recording source);
//   playback  the app *sends* audio to this device (a monitoring target).
//
// Virtual mixers (VoiceMeeter Banana, VB-Audio Cable) name their ports after
// their own mixer strips, not after the app's direction, so a device called
// "Voicemeeter Input" is in fact a playback target: the app plays into it and
// VoiceMeeter routes it on. Reading the raw name gives the wrong category, which
// is what REQ-023 asks us to correct.
enum class PortKind
{
    capture,
    playback,
    unknown
};

// Classifies one enumerated port. `driverListsItAsCapture` is the direction the
// audio backend reported (the list the name came from), used as the fallback for
// ordinary devices whose name carries no direction of its own.
PortKind classifyAudioPort (const juce::String& deviceName, bool driverListsItAsCapture);

// True when the name belongs to the VoiceMeeter / VB-Audio virtual family, where
// the raw name is written from the mixer's side and cannot be read literally.
bool isVirtualMixerPort (const juce::String& deviceName);

// Short PT-BR caption for a kind, e.g. "Entrada (captura)".
juce::String portKindLabel (PortKind kind);

// One-line explanation of what the app does with a port of this kind.
juce::String portKindDescription (PortKind kind);

} // namespace cursomusica::audio
