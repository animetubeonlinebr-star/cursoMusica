#pragma once

#include <juce_core/juce_core.h>

namespace cursomusica::data
{

// Connection settings for the PostgreSQL progress database (ADR 0006).
//
// The values come from the environment, never from the binary: the standard
// libpq variables (PGHOST, PGPORT, PGUSER, PGPASSWORD, PGDATABASE) plus two
// CursoMusica-specific ones (CURSOMUSICA_PG_SCHEMA, CURSOMUSICA_PG_STUDENT).
// CURSOMUSICA_PG_DISABLE=1 forces local-only mode.
struct PostgresConfig
{
    juce::String host;
    juce::String port { "5432" };
    juce::String user;
    juce::String password;
    juce::String dbname;
    juce::String schema { "curso-musica" };
    juce::String student { "local" };
    bool disabled = false;

    static PostgresConfig fromEnvironment();

    // Remote persistence is only attempted when a host is set and the build was
    // not told to stay local. The password is optional (peer/trust auth).
    bool isEnabled() const noexcept { return host.isNotEmpty() && ! disabled; }
};

// Thin wrapper over libpq that stores the student's progress in a PostgreSQL
// schema (default "curso-musica"). Two tables (ADR 0006, docs/DATA.md v4):
//
//   progress        one row per student: highest_passed_module (monotonic)
//   module_result   append-only history of gate results, for audit/BI
//
// The class is deliberately low-level and synchronous: the caller decides the
// thread. The ProgressStore calls it from a background thread so neither the
// audio nor the UI thread ever blocks on the network (AGENTS.md §1).
//
// When the build has no libpq (CURSOMUSICA_HAS_POSTGRES undefined), every
// method degrades to a no-op: the app still runs, purely local.
class ProgressDatabase
{
public:
    ProgressDatabase();
    ~ProgressDatabase();

    // True when this build was compiled against libpq. False means the app runs
    // in local-only mode regardless of the environment.
    static bool isCompiledIn() noexcept;

    // Opens the connection. Returns false and sets lastError() on failure; the
    // caller falls back to local storage and keeps working.
    bool connect (const PostgresConfig& config);

    void disconnect();
    bool isConnected() const noexcept { return connection != nullptr; }

    // Creates the schema and the two tables if they do not exist (idempotent).
    bool ensureSchema();

    // Highest module passed in the database, or -1 when the row is absent or the
    // query fails.
    int loadHighestPassedModule();

    // Monotonic upsert: the stored value never goes backwards.
    bool saveHighestPassedModule (int moduleNumber);

    // Appends one gate result to the history (never updates, never deletes).
    bool recordModuleResult (int moduleNumber, bool passed);

    // Last error text, for logs and diagnostics. Never contains the password.
    const juce::String& lastError() const noexcept { return error; }

    const PostgresConfig& getConfig() const noexcept { return config; }

private:
    bool execCommand (const juce::String& sql);

    // PGconn* kept opaque so this header needs no libpq include; that keeps the
    // no-libpq build and the unit tests able to compile it.
    void* connection = nullptr;
    PostgresConfig config;
    juce::String error;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProgressDatabase)
};

} // namespace cursomusica::data
