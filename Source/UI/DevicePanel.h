#pragma once

#include "UI/Design/Panel.h"

namespace cursomusica
{

// Input device, backend, sample rate and buffer size selectors.
// Layout only for now; wired to dummy values.
class DevicePanel final : public Panel
{
public:
    DevicePanel();

    void resized() override;

private:
    juce::ComboBox deviceSelector;
    juce::ComboBox sampleRateSelector;
    juce::ComboBox bufferSizeSelector;
    juce::Label backendLabel;
    juce::Label deviceCaption;
    juce::Label sampleRateCaption;
    juce::Label bufferSizeCaption;
};

} // namespace cursomusica
