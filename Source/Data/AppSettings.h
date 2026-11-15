#pragma once

#include <juce_data_structures/juce_data_structures.h>

namespace cursomusica::data
{

// The one PropertiesFile of the application, shared by every component that
// persists a preference.
//
// A PropertiesFile keeps the whole key/value map in memory and rewrites the
// entire file on save. Two instances over the same file therefore fight: the
// one that saves last wins and drops the keys it never loaded. That is not
// hypothetical — the course progress (`ProgressStore`), the tuner reference
// (`TuningSettings`) and the VST3 list (`PluginHost`) all used the same
// `CursoMusica.settings`, and because `PluginHost` rewrites it on shutdown the
// progress recorded during the session was erased when the app closed.
//
// Sharing a single instance removes the class of bug: every writer edits the
// same map and the last flush is the union of all changes.
class AppSettings
{
public:
    // Lazily creates the file on first use and returns the process-wide
    // instance. Never returns null.
    static juce::PropertiesFile& get();

private:
    AppSettings() = delete;
};

} // namespace cursomusica::data
