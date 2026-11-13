#pragma once

#include <juce_data_structures/juce_data_structures.h>

#include <atomic>
#include <memory>

#include "Course/ProgressionRule.h"
#include "Data/ProgressDatabase.h"

namespace cursomusica::course
{

// Persists the student's progress through the linear course: the highest module
// passed. The gate result of a module (>= 90%, REQ-009) is recorded here and
// unlocks the next one. The test override of ADR 0003 (item 7) opens every
// module without touching the real record.
//
// Storage is offline-first (ADR 0006): the local PropertiesFile is the fast,
// always-available source, and a background thread mirrors every result to a
// PostgreSQL database (schema "curso-musica" by default). Neither the audio nor
// the UI thread ever touches the network. If the database is unreachable the
// app keeps working locally and reconnects on the next write.
class ProgressStore
{
public:
    ProgressStore();
    ~ProgressStore();

    // True when the module can be opened: either it is unlocked by the linear
    // rule or the test override is active.
    bool isModuleUnlocked (int moduleNumber) const noexcept;

    // Records the gate result for a module; a pass unlocks the next one and is
    // mirrored to the database in the background.
    void recordGateResult (int moduleNumber, bool passed);

    int getHighestPassedModule() const noexcept { return highestPassedModule.load(); }

    // ADR 0003, item 7: release builds on the test branch open everything.
    void setUnlockAll (bool shouldUnlockAll) noexcept { unlockAll = shouldUnlockAll; }
    bool isUnlockAll() const noexcept { return unlockAll.load(); }

    void reset();

    // Diagnostics (no secrets): whether remote storage is configured in this
    // environment and whether the background thread currently holds a live
    // connection. Used by logs and the settings screen.
    bool isRemoteConfigured() const noexcept { return remoteConfigured; }
    bool isRemoteConnected() const noexcept { return remoteConnected.load(); }
    juce::String getRemoteStatus() const;

private:
    class SyncThread;

    void load();
    void save() const;
    void enqueueRemote (int moduleNumber, bool passed);

    std::atomic<int> highestPassedModule { 0 };
    std::atomic<bool> unlockAll { false };
    std::atomic<bool> remoteConnected { false };
    bool remoteConfigured = false;

    std::unique_ptr<juce::PropertiesFile> properties;
    data::PostgresConfig config;
    std::unique_ptr<SyncThread> sync;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProgressStore)
};

} // namespace cursomusica::course
