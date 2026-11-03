#pragma once

#include <juce_data_structures/juce_data_structures.h>

#include <memory>

#include "Course/ProgressionRule.h"

namespace cursomusica::course
{

// Persists the student's progress through the linear course: the highest module
// passed. The gate result of a module (>= 90%, REQ-009) is recorded here and
// unlocks the next one. The test override of ADR 0003 (item 7) opens every
// module without touching the real record.
class ProgressStore
{
public:
    ProgressStore();

    // True when the module can be opened: either it is unlocked by the linear
    // rule or the test override is active.
    bool isModuleUnlocked (int moduleNumber) const noexcept;

    // Records the gate result for a module; a pass unlocks the next one.
    void recordGateResult (int moduleNumber, bool passed);

    int getHighestPassedModule() const noexcept { return highestPassedModule; }

    // ADR 0003, item 7: release builds on the test branch open everything.
    void setUnlockAll (bool shouldUnlockAll) noexcept { unlockAll = shouldUnlockAll; }
    bool isUnlockAll() const noexcept { return unlockAll; }

    void reset();

private:
    void load();
    void save() const;

    int highestPassedModule = 0;
    bool unlockAll = false;
    std::unique_ptr<juce::PropertiesFile> properties;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProgressStore)
};

} // namespace cursomusica::course
