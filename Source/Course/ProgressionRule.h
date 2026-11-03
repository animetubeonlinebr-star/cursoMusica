#pragma once

namespace cursomusica::course::progress
{

// Pure linear-progression rule (REQ-002, ADR 0003): module 1 is always open and
// module N opens only after module N-1 has been passed. Free of JUCE so it can
// be unit-tested in isolation.
inline bool isUnlocked (int moduleNumber, int highestPassedModule) noexcept
{
    if (moduleNumber <= 1)
        return true;

    return moduleNumber <= highestPassedModule + 1;
}

inline int highestUnlocked (int highestPassedModule) noexcept
{
    return highestPassedModule + 1;
}

} // namespace cursomusica::course::progress
