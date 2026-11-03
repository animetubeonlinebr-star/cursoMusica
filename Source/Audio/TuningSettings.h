#pragma once

#include <juce_data_structures/juce_data_structures.h>

#include <atomic>
#include <memory>

namespace cursomusica
{

// Reference pitch for the tuner: the frequency assigned to A4.
//
// The value is edited on the message thread (tuner window) and read from the
// UI/analysis path, so it lives in an atomic. 440 Hz is the default; the range
// is clamped to a musically sane window so a stray keystroke cannot produce a
// nonsense reference. The choice is persisted, so it survives restarts.
class TuningSettings
{
public:
    static constexpr float defaultReferenceHz = 440.0f;
    static constexpr float minReferenceHz     = 400.0f;
    static constexpr float maxReferenceHz     = 480.0f;

    TuningSettings();

    float getReferenceHz() const noexcept { return referenceHz.load(); }

    // Clamps to [minReferenceHz, maxReferenceHz], stores and persists.
    void setReferenceHz (float newReferenceHz);

    // Restores the A4 = 440 Hz default.
    void resetToDefault() { setReferenceHz (defaultReferenceHz); }

private:
    void load();
    void save() const;

    std::atomic<float> referenceHz { defaultReferenceHz };
    std::unique_ptr<juce::PropertiesFile> properties;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TuningSettings)
};

} // namespace cursomusica
