#pragma once

#include <juce_core/juce_core.h>

#include <vector>

namespace cursomusica
{

// User-configured folders that the VST3 scan must search, on top of the format's
// default locations. The client asked for a Reaper-like folder list so plugins
// installed outside the system default can still be found.
//
// Pure logic (juce_core only), so it is covered by the test suite: no
// filesystem access, no UI. The plugin host owns persistence; this type owns the
// rules (normalise, de-duplicate, serialise, resolve to existing directories).
class PluginSearchPaths
{
public:
    static constexpr int maxEntries = 32;

    // Normalises an entry the way it is stored and compared: trims, resolves the
    // absolute path and drops the trailing separator. An empty result means the
    // entry carries no usable path.
    static juce::String normalise (const juce::String& path);

    // Adds a path, returning false when it is empty, a duplicate (compared after
    // normalisation) or the list is already full.
    bool add (const juce::String& path);

    bool remove (const juce::String& path);

    void clear();

    int size() const noexcept { return (int) paths.size(); }
    bool isEmpty() const noexcept { return paths.empty(); }

    const std::vector<juce::String>& getAll() const noexcept { return paths; }
    juce::String operator[] (int index) const;
    juce::StringArray toArray() const;

    // Replaces the whole list, dropping empty/duplicate entries.
    void setFromArray (const juce::StringArray& newPaths);

    // Newline-separated form used in the properties file.
    juce::String serialise() const;
    static PluginSearchPaths deserialise (const juce::String& text);

    // Entries that currently exist on disk as directories, in order. Used by the
    // scan; a stale entry is kept in the list so the user can fix or remove it.
    juce::FileSearchPath resolveExisting() const;

private:
    std::vector<juce::String> paths;
};

} // namespace cursomusica
