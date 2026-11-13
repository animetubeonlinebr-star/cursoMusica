#include "Course/ProgressStore.h"

#include <vector>

namespace cursomusica::course
{

namespace
{
    constexpr const char* highestPassedKey = "course/highestPassedModule";
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
            queue.emplace_back (moduleNumber, passed);
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
        std::vector<std::pair<int, bool>> pending;

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
                pushResult (item.first, item.second);

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

        return true;
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
    std::vector<std::pair<int, bool>> queue;
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
}

void ProgressStore::save() const
{
    properties->setValue (highestPassedKey, highestPassedModule.load());
    properties->saveIfNeeded();
}

void ProgressStore::reset()
{
    highestPassedModule.store (0);
    save();
}

} // namespace cursomusica::course
