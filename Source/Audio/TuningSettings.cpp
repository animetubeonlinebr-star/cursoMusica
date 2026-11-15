#include "Audio/TuningSettings.h"

namespace cursomusica
{

namespace
{
    constexpr const char* referenceKey = "tuner/referenceHz";
}

TuningSettings::TuningSettings()
    : properties (data::AppSettings::get())
{
    load();
}

void TuningSettings::load()
{
    const auto stored = (float) properties.getDoubleValue (referenceKey, defaultReferenceHz);
    referenceHz.store (juce::jlimit (minReferenceHz, maxReferenceHz, stored));
}

void TuningSettings::setReferenceHz (float newReferenceHz)
{
    const float clamped = juce::jlimit (minReferenceHz, maxReferenceHz, newReferenceHz);

    if (std::abs (clamped - referenceHz.load()) < 0.01f)
        return;

    referenceHz.store (clamped);
    save();
}

void TuningSettings::save() const
{
    properties.setValue (referenceKey, (double) referenceHz.load());
    properties.saveIfNeeded();
}

} // namespace cursomusica
