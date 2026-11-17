#pragma once

#include <juce_core/juce_core.h>

#include <vector>

namespace cursomusica::audio
{

// Pure bookkeeping for the VST3 panel (REQ-024 flow).
//
// The upper list shows the plugins the student can still insert; the lower list
// shows the input chain. Once a plugin is added it must leave the upper list and
// appear in the lower one, so the two panels never show the same plugin at the
// same time.
//
// Identity is the plugin's stable key (format + name + unique id), so the same
// plugin scanned twice — or the scanned description versus its running instance
// — is one entry. No JUCE audio types here: the caller passes the key strings,
// which keeps the rule unit-testable without a plugin format manager.
namespace pluginchain
{

// The stable identity of a scanned plugin.
//
// juce::PluginDescription::createIdentifierString() is NOT stable between the
// scan and the instantiated plugin: the scan stores `fileOrIdentifier` as the
// .vst3 bundle path, while the running instance reports the inner binary path
// (e.g. Contents/x86_64-linux/Plugin.so). Their identifier strings therefore
// differ and juce::PluginDescription::isDuplicateOf() returns false for the very
// same plugin — which is what made "Add input chain" leave the plugin in the
// upper panel.
//
// Format + name + unique id is stable across both, so it is the key used to tell
// "already in the chain" from "still available".
inline juce::String stableKey (const juce::String& formatName,
                               const juce::String& pluginName,
                               int uniqueId,
                               int deprecatedUid)
{
    return formatName + "-" + pluginName + "-"
         + juce::String (uniqueId != 0 ? uniqueId : deprecatedUid);
}

// Indices into `available` whose identifier is not present in `chain`, in order.
inline std::vector<int> selectableIndices (const std::vector<juce::String>& available,
                                           const std::vector<juce::String>& chain)
{
    std::vector<int> result;
    result.reserve (available.size());

    for (int i = 0; i < (int) available.size(); ++i)
    {
        const auto& id = available[(size_t) i];

        if (id.isEmpty())
            continue;

        bool inChain = false;
        for (const auto& chained : chain)
            if (chained == id)
            {
                inChain = true;
                break;
            }

        if (! inChain)
            result.push_back (i);
    }

    return result;
}

} // namespace pluginchain
} // namespace cursomusica::audio
