#include "Course/ProgressStore.h"

#include <vector>

namespace cursomusica::course
{

namespace
{
    constexpr const char* highestPassedKey = "course/highestPassedModule";
    constexpr const char* exerciseKeyPrefix = "exercise/";

    // One pending write for the background thread: either a module gate result
    // or the accuracy of an exercise attempt.
    struct QueueItem
    {
        enum class Kind { gate, exercise } kind = Kind::gate;
        int moduleNumber = 0;
        bool passed = false;
        juce::String exerciseId;
        double accuracyPercent = 0.0;
    };
}

// Mirrors the student's progress to PostgreSQL off the audio and UI threads
// (ADR 0006). Owns the connection, drains a small queue of gate results and, on
// startup, reconciles the local record with the database so progress made on
// another machine is not lost.
class ProgressStore::SyncThread : public juce::Thread
{
public:
    explicit SyncThread (ProgressStore& ownerToUse)
        : juce::Thread ("CursoMusicaProgressSync"), owner (ownerToUse)
    {
    }

    ~SyncThread() override { stop(); }

    void start (const data::PostgresConfig& configToUse)
    {
        config = configToUse;
        startThread();
    }

    void stop()
    {
        signalThreadShouldExit();
        wake.signal();
        stopThread (6000);
    }

    // Called from the message thread; never blocks on the network.
    void enqueue (int moduleNumber, bool passed)
    {
        {
            const juce::ScopedLock lock (queueLock);
            QueueItem item;
            item.kind = QueueItem::Kind::gate;
            item.moduleNumber = moduleNumber;
            item.passed = passed;
            queue.push_back (std::move (item));
        }

        wake.signal();
    }

    void enqueueExercise (const juce::String& exerciseId, double accuracyPercent)
    {
        {
            const juce::ScopedLock lock (queueLock);
            QueueItem item;
            item.kind = QueueItem::Kind::exercise;
            item.exerciseId = exerciseId;
            item.accuracyPercent = accuracyPercent;
            queue.push_back (std::move (item));
        }

        wake.signal();
    }

    bool isConnected() const noexcept { return connected.load(); }

private:
    void run() override
    {
        while (! threadShouldExit())
        {
            // (Re)connect lazily. While offline we idle on the waitable event
            // and retry on the next result, so the app never blocks on a
            // missing server.
            if (! connected.load() && ! connectAndPrepare())
            {
                wake.wait (5000);
                continue;
            }

            if (! drainQueue())
                wake.wait (5000);
        }

        // Best-effort final flush: a result queued just before the app closed
        // must not be lost. The merge on connect already keeps the highest
        // passed module safe, but the audit history lives only here.
        if (! connected.load())
            connectAndPrepare();

        drainQueue();
    }

    // Moves the queue out and pushes it. Returns false when there was nothing
    // to do (so the caller can idle instead of spinning).
    bool drainQueue()
    {
        std::vector<QueueItem> pending;

        {
            const juce::ScopedLock lock (queueLock);
            pending.swap (queue);
        }

        if (pending.empty())
            return false;

        if (! connected.load())
            connectAndPrepare();

        if (connected.load())
            for (const auto& item : pending)
                pushItem (item);

        return true;
    }

    bool connectAndPrepare()
    {
        database.disconnect();

        if (! database.connect (config))
        {
            connected.store (false);
            return false;
        }

        if (! database.ensureSchema())
        {
            connected.store (false);
            return false;
        }

        connected.store (true);

        // Reconcile: the higher of the two records wins, and the winner is
        // pushed back so both sides converge. The local value is only raised,
        // never lowered, so a failed read (returns -1) cannot lose progress.
        const int remote = database.loadHighestPassedModule();
        const int local = owner.highestPassedModule.load();

        int merged = local;
        if (remote > merged)
            merged = remote;

        if (merged > remote)
            database.saveHighestPassedModule (merged);

        if (merged > local)
            owner.highestPassedModule.store (merged);

        // Per-exercise results: the local record of this profile wins (it is the
        // most recent attempt on this machine); the database fills in the ones
        // this profile has never seen, so progress made elsewhere reappears.
        for (const auto& [exerciseId, accuracy] : database.loadExerciseResults())
        {
            const juce::ScopedLock lock (owner.exerciseLock);

            if (owner.exerciseAccuracy.find (exerciseId) == owner.exerciseAccuracy.end())
            {
                owner.exerciseAccuracy[exerciseId] = accuracy;
                owner.properties->setValue (ProgressStore::exerciseKey (exerciseId), accuracy);
            }
        }

        return true;
    }

    void pushItem (const QueueItem& item)
    {
        if (item.kind == QueueItem::Kind::gate)
            pushResult (item.moduleNumber, item.passed);
        else if (! database.saveExerciseResult (item.exerciseId, item.accuracyPercent))
            connected.store (false);
    }

    void pushResult (int moduleNumber, bool passed)
    {
        if (! database.recordModuleResult (moduleNumber, passed))
        {
            connected.store (false);
            return;
        }

        if (passed && ! database.saveHighestPassedModule (moduleNumber))
            connected.store (false);
    }

    ProgressStore& owner;
    data::PostgresConfig config;
    data::ProgressDatabase database;
    juce::CriticalSection queueLock;
    std::vector<QueueItem> queue;
    juce::WaitableEvent wake;
    std::atomic<bool> connected { false };
};

ProgressStore::ProgressStore()
{
    juce::PropertiesFile::Options options;
    options.applicationName = "CursoMusica";
    options.filenameSuffix = ".settings";
    options.folderName = "CursoMusica";
    options.osxLibrarySubFolder = "Application Support";
    options.storageFormat = juce::PropertiesFile::storeAsXML;

    properties = std::make_unique<juce::PropertiesFile> (options);
    load();

    config = data::PostgresConfig::fromEnvironment();

    // Remote storage needs both a configured environment and a build with libpq.
    remoteConfigured = config.isEnabled() && data::ProgressDatabase::isCompiledIn();

    if (remoteConfigured)
    {
        sync = std::make_unique<SyncThread> (*this);
        sync->start (config);
    }

   #ifdef TEST_UNLOCK_ALL
    // Test build (REQ-013, ADR 0003 item 7): every module is reachable for
    // inspection. This never touches the real progress record.
    unlockAll = true;
   #endif
}

ProgressStore::~ProgressStore()
{
    if (sync != nullptr)
        sync->stop();
}

bool ProgressStore::isModuleUnlocked (int moduleNumber) const noexcept
{
    return unlockAll.load() || progress::isUnlocked (moduleNumber, highestPassedModule.load());
}

void ProgressStore::recordGateResult (int moduleNumber, bool passed)
{
    if (passed && moduleNumber > highestPassedModule.load())
    {
        highestPassedModule.store (moduleNumber);
        save();
    }

    if (remoteConfigured)
        enqueueRemote (moduleNumber, passed);
}

void ProgressStore::enqueueRemote (int moduleNumber, bool passed)
{
    if (sync != nullptr)
        sync->enqueue (moduleNumber, passed);
}

void ProgressStore::enqueueRemoteExercise (const juce::String& exerciseId, double accuracyPercent)
{
    if (sync != nullptr)
        sync->enqueueExercise (exerciseId, accuracyPercent);
}

juce::String ProgressStore::exerciseKey (const juce::String& exerciseId)
{
    return juce::String (exerciseKeyPrefix) + exerciseId;
}

void ProgressStore::recordExerciseResult (const juce::String& exerciseId, double accuracyPercent)
{
    if (exerciseId.isEmpty())
        return;

    const int value = juce::jlimit (0, 100, juce::roundToInt (accuracyPercent));

    {
        const juce::ScopedLock lock (exerciseLock);
        exerciseAccuracy[exerciseId] = value;
    }

    properties->setValue (exerciseKey (exerciseId), value);
    properties->saveIfNeeded();

    if (remoteConfigured)
        enqueueRemoteExercise (exerciseId, (double) value);
}

int ProgressStore::getExerciseAccuracy (const juce::String& exerciseId) const
{
    if (exerciseId.isEmpty())
        return -1;

    const juce::ScopedLock lock (exerciseLock);

    if (const auto it = exerciseAccuracy.find (exerciseId); it != exerciseAccuracy.end())
        return it->second;

    return -1;
}

juce::String ProgressStore::getRemoteStatus() const
{
    if (! data::ProgressDatabase::isCompiledIn())
        return "local-only (build without libpq)";

    if (! remoteConfigured)
        return "local-only (no PostgreSQL configured)";

    return sync != nullptr && sync->isConnected()
               ? "connected to PostgreSQL"
               : "configured, connecting to PostgreSQL";
}

void ProgressStore::load()
{
    highestPassedModule.store ((int) properties->getIntValue (highestPassedKey, 0));

    const juce::ScopedLock lock (exerciseLock);
    exerciseAccuracy.clear();

    const auto& all = properties->getAllProperties();
    for (const auto& key : all.getAllKeys())
        if (key.startsWith (exerciseKeyPrefix))
            exerciseAccuracy[key.fromFirstOccurrenceOf (exerciseKeyPrefix, false, false)]
                = all.getValue (key, {}).getIntValue();
}

void ProgressStore::save() const
{
    properties->setValue (highestPassedKey, highestPassedModule.load());
    properties->saveIfNeeded();
}

void ProgressStore::reset()
{
    highestPassedModule.store (0);

    {
        const juce::ScopedLock lock (exerciseLock);

        for (const auto& exerciseId : exerciseAccuracy)
            properties->removeValue (exerciseKey (exerciseId.first));

        exerciseAccuracy.clear();
    }

    save();
    properties->saveIfNeeded();
}

} // namespace cursomusica::course
