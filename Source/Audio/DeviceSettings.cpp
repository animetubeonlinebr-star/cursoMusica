#include "Audio/DeviceSettings.h"

namespace cursomusica::audio
{

namespace
{
    constexpr const char* rootTag = "DEVICESELECTION";
}

juce::String serialiseDeviceSelection (const DeviceSelection& selection)
{
    juce::XmlElement xml (rootTag);
    xml.setAttribute ("deviceType", selection.deviceType);
    xml.setAttribute ("input", selection.inputDeviceName);
    xml.setAttribute ("output", selection.outputDeviceName);
    xml.setAttribute ("sampleRate", selection.sampleRate);
    xml.setAttribute ("bufferSize", selection.bufferSize);

    return xml.toString();
}

DeviceSelection parseDeviceSelection (const juce::String& text)
{
    DeviceSelection selection;

    const auto xml = juce::XmlDocument::parse (text);
    if (xml == nullptr || ! xml->hasTagName (rootTag))
        return selection;

    selection.deviceType = xml->getStringAttribute ("deviceType");
    selection.inputDeviceName = xml->getStringAttribute ("input");
    selection.outputDeviceName = xml->getStringAttribute ("output");
    selection.sampleRate = xml->getDoubleAttribute ("sampleRate", 0.0);
    selection.bufferSize = xml->getIntAttribute ("bufferSize", 0);

    return selection;
}

bool deviceSelectionIsAvailable (const DeviceSelection& selection,
                                 const juce::String& currentTypeName,
                                 const juce::StringArray& inputNames,
                                 const juce::StringArray& outputNames)
{
    if (selection.isEmpty())
        return false;

    // A device opened under one backend cannot be reopened under another.
    if (selection.deviceType.isNotEmpty() && selection.deviceType != currentTypeName)
        return false;

    const auto hasName = [] (const juce::StringArray& names, const juce::String& wanted)
    {
        for (const auto& name : names)
            if (name.trim().equalsIgnoreCase (wanted.trim()))
                return true;

        return false;
    };

    if (selection.inputDeviceName.isNotEmpty() && ! hasName (inputNames, selection.inputDeviceName))
        return false;

    if (selection.outputDeviceName.isNotEmpty() && ! hasName (outputNames, selection.outputDeviceName))
        return false;

    return true;
}

} // namespace cursomusica::audio
