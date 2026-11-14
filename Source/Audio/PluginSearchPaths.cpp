#include "Audio/PluginSearchPaths.h"

#include <algorithm>

namespace cursomusica
{

juce::String PluginSearchPaths::normalise (const juce::String& path)
{
    auto trimmed = path.trim();
    if (trimmed.isEmpty())
        return {};

    return juce::File (trimmed).getFullPathName().trimCharactersAtEnd ("/\\");
}

bool PluginSearchPaths::add (const juce::String& path)
{
    const auto normalised = normalise (path);
    if (normalised.isEmpty() || (int) paths.size() >= maxEntries)
        return false;

    const bool duplicate = std::any_of (paths.begin(), paths.end(), [&normalised] (const juce::String& existing)
    {
        return existing.equalsIgnoreCase (normalised);
    });

    if (duplicate)
        return false;

    paths.push_back (normalised);
    return true;
}

bool PluginSearchPaths::remove (const juce::String& path)
{
    const auto normalised = normalise (path);
    const auto found = std::find_if (paths.begin(), paths.end(), [&normalised] (const juce::String& existing)
    {
        return existing.equalsIgnoreCase (normalised);
    });

    if (found == paths.end())
        return false;

    paths.erase (found);
    return true;
}

void PluginSearchPaths::clear()
{
    paths.clear();
}

juce::String PluginSearchPaths::operator[] (int index) const
{
    if (index < 0 || index >= (int) paths.size())
        return {};

    return paths[(size_t) index];
}

juce::StringArray PluginSearchPaths::toArray() const
{
    juce::StringArray result;
    for (const auto& path : paths)
        result.add (path);

    return result;
}

void PluginSearchPaths::setFromArray (const juce::StringArray& newPaths)
{
    paths.clear();
    for (const auto& path : newPaths)
        add (path);
}

juce::String PluginSearchPaths::serialise() const
{
    return toArray().joinIntoString ("\n");
}

PluginSearchPaths PluginSearchPaths::deserialise (const juce::String& text)
{
    PluginSearchPaths result;
    result.setFromArray (juce::StringArray::fromLines (text));
    return result;
}

juce::FileSearchPath PluginSearchPaths::resolveExisting() const
{
    juce::FileSearchPath result;
    for (const auto& path : paths)
    {
        const juce::File directory (path);
        if (directory.isDirectory())
            result.add (directory);
    }

    return result;
}

} // namespace cursomusica
