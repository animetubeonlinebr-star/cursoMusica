#include "UI/AudioPortsPanel.h"

#include "UI/Design/Theme.h"

namespace cursomusica
{

namespace th = cursomusica::theme;

AudioPortsPanel::AudioPortsPanel (juce::AudioDeviceManager& manager)
    : Panel (juce::String::fromUTF8 ("Portas de áudio")), deviceManager (manager)
{
    refresh();
}

void AudioPortsPanel::collect()
{
    entries.clear();
    mixerNote.clear();

    auto* type = deviceManager.getCurrentDeviceTypeObject();
    if (type == nullptr)
        return;

    type->scanForDevices();

    // The backend lists each device under the direction *it* reports. That is
    // right for ordinary hardware; the classifier corrects the virtual mixers.
    const auto captureNames  = type->getDeviceNames (true);
    const auto playbackNames = type->getDeviceNames (false);

    for (const auto& name : captureNames)
        entries.push_back ({ name, audio::classifyAudioPort (name, true) });

    for (const auto& name : playbackNames)
        entries.push_back ({ name, audio::classifyAudioPort (name, false) });

    for (const auto& entry : entries)
        if (audio::isVirtualMixerPort (entry.name))
        {
            mixerNote = juce::String::fromUTF8 (
                "VoiceMeeter / VB-Audio: o nome é escrito pela ótica do mixer. "
                "\"Voicemeeter Input\" é onde o app toca (saída) e \"Voicemeeter Out A1\" "
                "é o que o mixer devolve ao app (entrada).");
            break;
        }
}

void AudioPortsPanel::refresh()
{
    collect();
    repaint();
}

void AudioPortsPanel::paint (juce::Graphics& g)
{
    Panel::paint (g);

    auto content = getContentBounds();

    if (entries.empty())
    {
        g.setColour (th::colour::textDisabled);
        g.setFont (th::type::makeFont (th::type::body));
        g.drawFittedText (juce::String::fromUTF8 ("Nenhum dispositivo de áudio detectado."),
                          content, juce::Justification::topLeft, 2);
        return;
    }

    auto drawGroup = [&] (audio::PortKind kind)
    {
        g.setColour (th::colour::textPrimary);
        g.setFont (th::type::makeFont (th::type::body, true));
        g.drawText (audio::portKindLabel (kind), content.removeFromTop (22),
                    juce::Justification::centredLeft, false);

        g.setColour (th::colour::textDisabled);
        g.setFont (th::type::makeFont (th::type::caption));
        g.drawFittedText (audio::portKindDescription (kind), content.removeFromTop (18),
                          juce::Justification::topLeft, 1);

        for (const auto& entry : entries)
        {
            if (entry.kind != kind)
                continue;

            if (content.getHeight() < 18)
                return;

            g.setColour (th::colour::textSecondary);
            g.setFont (th::type::makeFont (th::type::body));
            g.drawText (juce::String::fromUTF8 ("• ") + entry.name,
                        content.removeFromTop (18), juce::Justification::centredLeft, true);
        }

        content.removeFromTop (th::spacing::sm);
    };

    drawGroup (audio::PortKind::capture);
    drawGroup (audio::PortKind::playback);

    const bool anyUnknown = std::any_of (entries.begin(), entries.end(),
                                         [] (const Entry& e) { return e.kind == audio::PortKind::unknown; });
    if (anyUnknown)
        drawGroup (audio::PortKind::unknown);

    if (mixerNote.isNotEmpty() && content.getHeight() > 30)
    {
        content.removeFromTop (th::spacing::sm);
        g.setColour (th::colour::accentAlt);
        g.setFont (th::type::makeFont (th::type::caption));
        g.drawFittedText (mixerNote, content.removeFromTop (juce::jmin (content.getHeight(), 60)),
                          juce::Justification::topLeft, 4);
    }
}

} // namespace cursomusica
