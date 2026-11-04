#include "Audio/AudioPortClassifier.h"

namespace cursomusica::audio
{

namespace
{
    juce::String lower (const juce::String& text)
    {
        return text.toLowerCase();
    }
}

bool isVirtualMixerPort (const juce::String& deviceName)
{
    const auto name = lower (deviceName);
    return name.contains ("voicemeeter")
        || name.contains ("vb-audio")
        || name.contains ("vb audio")
        || name.contains ("virtual cable")
        || name.contains ("cable input")
        || name.contains ("cable output");
}

PortKind classifyAudioPort (const juce::String& deviceName, bool driverListsItAsCapture)
{
    if (! isVirtualMixerPort (deviceName))
        return driverListsItAsCapture ? PortKind::capture : PortKind::playback;

    const auto name = lower (deviceName);

    // VoiceMeeter writes names from the mixer's side:
    //   "Voicemeeter Input" / "Voicemeeter AUX Input" / "Voicemeeter In N"
    //     are where the app *plays into* the mixer -> playback for the app.
    //   "Voicemeeter Out A1..A5 / B1..B3" and the "CABLE Output" pair
    //     are what the mixer *sends back* to the app -> capture for the app.
    // "Voicemeeter VAIO3 Input" and the plain "CABLE Input" follow the same rule.
    const bool mixerFeed  = name.contains ("voicemeeter") && name.contains ("input");
    const bool mixerIn    = name.contains ("voicemeeter") && name.contains (" in ");
    const bool mixerOut   = name.contains ("voicemeeter") && name.contains ("out");
    const bool cableIn    = name.contains ("cable input");
    const bool cableOut   = name.contains ("cable output");

    if (mixerFeed || mixerIn || cableIn)
        return PortKind::playback;

    if (mixerOut || cableOut)
        return PortKind::capture;

    // Unknown virtual port: trust the backend's own direction rather than guess.
    return driverListsItAsCapture ? PortKind::capture : PortKind::playback;
}

juce::String portKindLabel (PortKind kind)
{
    switch (kind)
    {
        case PortKind::capture:  return juce::String::fromUTF8 ("Entrada (captura)");
        case PortKind::playback: return juce::String::fromUTF8 ("Saída (reprodução)");
        case PortKind::unknown:
        default:                 return juce::String::fromUTF8 ("Indefinida");
    }
}

juce::String portKindDescription (PortKind kind)
{
    switch (kind)
    {
        case PortKind::capture:
            return juce::String::fromUTF8 ("O app recebe áudio daqui (ex.: microfone, instrumento).");
        case PortKind::playback:
            return juce::String::fromUTF8 ("O app envia áudio para cá (ex.: monitores, fones).");
        case PortKind::unknown:
        default:
            return juce::String::fromUTF8 ("Direção não informada pelo driver.");
    }
}

} // namespace cursomusica::audio
