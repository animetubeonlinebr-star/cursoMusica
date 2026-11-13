#include "Data/ProgressDatabase.h"

#ifdef CURSOMUSICA_HAS_POSTGRES
 #include <libpq-fe.h>
#endif

namespace cursomusica::data
{

namespace
{
    juce::String envOr (const char* name, const juce::String& fallback)
    {
        if (const char* value = std::getenv (name))
            if (*value != '\0')
                return juce::String (value);

        return fallback;
    }

    bool envFlag (const char* name)
    {
        const auto value = envOr (name, {});
        return value == "1" || value.equalsIgnoreCase ("true") || value.equalsIgnoreCase ("yes");
    }
}

PostgresConfig PostgresConfig::fromEnvironment()
{
    PostgresConfig config;
    config.host     = envOr ("PGHOST", {});
    config.port     = envOr ("PGPORT", "5432");
    config.user     = envOr ("PGUSER", {});
    config.password = envOr ("PGPASSWORD", {});
    config.dbname   = envOr ("PGDATABASE", {});
    config.schema   = envOr ("CURSOMUSICA_PG_SCHEMA", "curso-musica");
    config.student  = envOr ("CURSOMUSICA_PG_STUDENT", "local");
    config.disabled = envFlag ("CURSOMUSICA_PG_DISABLE");
    return config;
}

ProgressDatabase::ProgressDatabase() = default;
ProgressDatabase::~ProgressDatabase() { disconnect(); }

bool ProgressDatabase::isCompiledIn() noexcept
{
   #ifdef CURSOMUSICA_HAS_POSTGRES
    return true;
   #else
    return false;
   #endif
}

void ProgressDatabase::disconnect()
{
   #ifdef CURSOMUSICA_HAS_POSTGRES
    if (connection != nullptr)
    {
        PQfinish (static_cast<PGconn*> (connection));
        connection = nullptr;
    }
   #endif
}

bool ProgressDatabase::connect (const PostgresConfig& newConfig)
{
    config = newConfig;
    error.clear();

   #ifndef CURSOMUSICA_HAS_POSTGRES
    error = "built without libpq";
    return false;
   #else
    disconnect();

    // Keyword/value arrays rather than a single connection string: a password
    // with spaces or quotes cannot corrupt the parameters, and nothing sensitive
    // is ever concatenated into a string we might log.
    const char* keywords[] = { "host", "port", "user", "password", "dbname", "connect_timeout", nullptr };
    const char* values[]   = { config.host.toRawUTF8(),
                               config.port.toRawUTF8(),
                               config.user.toRawUTF8(),
                               config.password.toRawUTF8(),
                               config.dbname.toRawUTF8(),
                               "5",
                               nullptr };

    connection = PQconnectdbParams (keywords, values, 0);

    if (connection == nullptr)
    {
        error = "out of memory while connecting";
        return false;
    }

    if (PQstatus (static_cast<PGconn*> (connection)) != CONNECTION_OK)
    {
        error = PQerrorMessage (static_cast<PGconn*> (connection));
        disconnect();
        return false;
    }

    return true;
   #endif
}

bool ProgressDatabase::execCommand (const juce::String& sql)
{
   #ifndef CURSOMUSICA_HAS_POSTGRES
    juce::ignoreUnused (sql);
    error = "built without libpq";
    return false;
   #else
    if (connection == nullptr)
    {
        error = "not connected";
        return false;
    }

    PGresult* result = PQexec (static_cast<PGconn*> (connection), sql.toRawUTF8());
    const auto status = PQresultStatus (result);
    const bool ok = status == PGRES_COMMAND_OK || status == PGRES_TUPLES_OK;

    if (! ok)
        error = PQresultErrorMessage (result);

    PQclear (result);
    return ok;
   #endif
}

bool ProgressDatabase::ensureSchema()
{
   #ifndef CURSOMUSICA_HAS_POSTGRES
    error = "built without libpq";
    return false;
   #else
    if (connection == nullptr)
    {
        error = "not connected";
        return false;
    }

    // The schema name comes from the environment, so it is escaped as an
    // identifier (never interpolated raw) before being used in DDL.
    char* escapedSchema = PQescapeIdentifier (static_cast<PGconn*> (connection),
                                              config.schema.toRawUTF8(),
                                              (size_t) config.schema.getNumBytesAsUTF8());
    if (escapedSchema == nullptr)
    {
        error = "invalid schema name";
        return false;
    }

    const juce::String schema (escapedSchema);
    PQfreemem (escapedSchema);

    const juce::String ddl =
        "CREATE SCHEMA IF NOT EXISTS " + schema + ";"
        "CREATE TABLE IF NOT EXISTS " + schema + ".progress ("
        "  student_id TEXT PRIMARY KEY,"
        "  highest_passed_module INTEGER NOT NULL DEFAULT 0,"
        "  updated_at TIMESTAMPTZ NOT NULL DEFAULT now()"
        ");"
        "CREATE TABLE IF NOT EXISTS " + schema + ".module_result ("
        "  id BIGSERIAL PRIMARY KEY,"
        "  student_id TEXT NOT NULL,"
        "  module_id INTEGER NOT NULL,"
        "  passed BOOLEAN NOT NULL,"
        "  recorded_at TIMESTAMPTZ NOT NULL DEFAULT now()"
        ");"
        "CREATE TABLE IF NOT EXISTS " + schema + ".exercise_result ("
        "  student_id TEXT NOT NULL,"
        "  exercise_id TEXT NOT NULL,"
        "  accuracy INTEGER NOT NULL,"
        "  recorded_at TIMESTAMPTZ NOT NULL DEFAULT now(),"
        "  PRIMARY KEY (student_id, exercise_id)"
        ");"
        "CREATE INDEX IF NOT EXISTS module_result_student_idx"
        "  ON " + schema + ".module_result (student_id, module_id);";

    return execCommand (ddl);
   #endif
}

int ProgressDatabase::loadHighestPassedModule()
{
   #ifndef CURSOMUSICA_HAS_POSTGRES
    error = "built without libpq";
    return -1;
   #else
    if (connection == nullptr)
    {
        error = "not connected";
        return -1;
    }

    char* escapedSchema = PQescapeIdentifier (static_cast<PGconn*> (connection),
                                              config.schema.toRawUTF8(),
                                              (size_t) config.schema.getNumBytesAsUTF8());
    if (escapedSchema == nullptr)
    {
        error = "invalid schema name";
        return -1;
    }

    const juce::String schema (escapedSchema);
    PQfreemem (escapedSchema);

    const juce::String sql =
        "SELECT highest_passed_module FROM " + schema + ".progress WHERE student_id = $1;";

    const char* values[] = { config.student.toRawUTF8() };
    PGresult* result = PQexecParams (static_cast<PGconn*> (connection), sql.toRawUTF8(),
                                     1, nullptr, values, nullptr, nullptr, 0);

    const auto status = PQresultStatus (result);
    if (status != PGRES_TUPLES_OK)
    {
        error = PQresultErrorMessage (result);
        PQclear (result);
        return -1;
    }

    if (PQntuples (result) == 0)
    {
        PQclear (result);
        return -1;
    }

    const int value = juce::String (PQgetvalue (result, 0, 0)).getIntValue();
    PQclear (result);
    return value;
   #endif
}

bool ProgressDatabase::saveHighestPassedModule (int moduleNumber)
{
   #ifndef CURSOMUSICA_HAS_POSTGRES
    juce::ignoreUnused (moduleNumber);
    error = "built without libpq";
    return false;
   #else
    if (connection == nullptr)
    {
        error = "not connected";
        return false;
    }

    char* escapedSchema = PQescapeIdentifier (static_cast<PGconn*> (connection),
                                              config.schema.toRawUTF8(),
                                              (size_t) config.schema.getNumBytesAsUTF8());
    if (escapedSchema == nullptr)
    {
        error = "invalid schema name";
        return false;
    }

    const juce::String schema (escapedSchema);
    PQfreemem (escapedSchema);

    // GREATEST keeps the stored value monotonic: a late or out-of-order write
    // can never lower the student's progress.
    const juce::String sql =
        "INSERT INTO " + schema + ".progress (student_id, highest_passed_module, updated_at)"
        " VALUES ($1, $2, now())"
        " ON CONFLICT (student_id) DO UPDATE"
        " SET highest_passed_module = GREATEST ("
        "   " + schema + ".progress.highest_passed_module, EXCLUDED.highest_passed_module),"
        " updated_at = now();";

    const juce::String moduleText (moduleNumber);
    const char* values[] = { config.student.toRawUTF8(), moduleText.toRawUTF8() };

    PGresult* result = PQexecParams (static_cast<PGconn*> (connection), sql.toRawUTF8(),
                                     2, nullptr, values, nullptr, nullptr, 0);
    const auto status = PQresultStatus (result);
    const bool ok = status == PGRES_COMMAND_OK;

    if (! ok)
        error = PQresultErrorMessage (result);

    PQclear (result);
    return ok;
   #endif
}

bool ProgressDatabase::recordModuleResult (int moduleNumber, bool passed)
{
   #ifndef CURSOMUSICA_HAS_POSTGRES
    juce::ignoreUnused (moduleNumber, passed);
    error = "built without libpq";
    return false;
   #else
    if (connection == nullptr)
    {
        error = "not connected";
        return false;
    }

    char* escapedSchema = PQescapeIdentifier (static_cast<PGconn*> (connection),
                                              config.schema.toRawUTF8(),
                                              (size_t) config.schema.getNumBytesAsUTF8());
    if (escapedSchema == nullptr)
    {
        error = "invalid schema name";
        return false;
    }

    const juce::String schema (escapedSchema);
    PQfreemem (escapedSchema);

    const juce::String sql =
        "INSERT INTO " + schema + ".module_result (student_id, module_id, passed)"
        " VALUES ($1, $2, $3);";

    const juce::String moduleText (moduleNumber);
    const char* values[] = { config.student.toRawUTF8(),
                             moduleText.toRawUTF8(),
                             passed ? "true" : "false" };

    PGresult* result = PQexecParams (static_cast<PGconn*> (connection), sql.toRawUTF8(),
                                     3, nullptr, values, nullptr, nullptr, 0);
    const auto status = PQresultStatus (result);
    const bool ok = status == PGRES_COMMAND_OK;

    if (! ok)
        error = PQresultErrorMessage (result);

    PQclear (result);
    return ok;
   #endif
}

bool ProgressDatabase::saveExerciseResult (const juce::String& exerciseId, double accuracyPercent)
{
   #ifndef CURSOMUSICA_HAS_POSTGRES
    juce::ignoreUnused (exerciseId, accuracyPercent);
    error = "built without libpq";
    return false;
   #else
    if (connection == nullptr)
    {
        error = "not connected";
        return false;
    }

    char* escapedSchema = PQescapeIdentifier (static_cast<PGconn*> (connection),
                                              config.schema.toRawUTF8(),
                                              (size_t) config.schema.getNumBytesAsUTF8());
    if (escapedSchema == nullptr)
    {
        error = "invalid schema name";
        return false;
    }

    const juce::String schema (escapedSchema);
    PQfreemem (escapedSchema);

    // One row per (student, exercise): the latest attempt replaces the previous
    // one, which is exactly what "the last percentage" means. The client asked
    // to see the last result, not the best.
    const juce::String sql =
        "INSERT INTO " + schema + ".exercise_result (student_id, exercise_id, accuracy, recorded_at)"
        " VALUES ($1, $2, $3, now())"
        " ON CONFLICT (student_id, exercise_id) DO UPDATE"
        " SET accuracy = EXCLUDED.accuracy, recorded_at = now();";

    const juce::String accuracyText (juce::roundToInt (accuracyPercent));
    const char* values[] = { config.student.toRawUTF8(),
                             exerciseId.toRawUTF8(),
                             accuracyText.toRawUTF8() };

    PGresult* result = PQexecParams (static_cast<PGconn*> (connection), sql.toRawUTF8(),
                                     3, nullptr, values, nullptr, nullptr, 0);
    const auto status = PQresultStatus (result);
    const bool ok = status == PGRES_COMMAND_OK;

    if (! ok)
        error = PQresultErrorMessage (result);

    PQclear (result);
    return ok;
   #endif
}

int ProgressDatabase::loadExerciseResult (const juce::String& exerciseId)
{
   #ifndef CURSOMUSICA_HAS_POSTGRES
    juce::ignoreUnused (exerciseId);
    error = "built without libpq";
    return -1;
   #else
    if (connection == nullptr)
    {
        error = "not connected";
        return -1;
    }

    char* escapedSchema = PQescapeIdentifier (static_cast<PGconn*> (connection),
                                              config.schema.toRawUTF8(),
                                              (size_t) config.schema.getNumBytesAsUTF8());
    if (escapedSchema == nullptr)
    {
        error = "invalid schema name";
        return -1;
    }

    const juce::String schema (escapedSchema);
    PQfreemem (escapedSchema);

    const juce::String sql =
        "SELECT accuracy FROM " + schema + ".exercise_result"
        " WHERE student_id = $1 AND exercise_id = $2;";

    const char* values[] = { config.student.toRawUTF8(), exerciseId.toRawUTF8() };
    PGresult* result = PQexecParams (static_cast<PGconn*> (connection), sql.toRawUTF8(),
                                     2, nullptr, values, nullptr, nullptr, 0);

    const auto status = PQresultStatus (result);
    if (status != PGRES_TUPLES_OK)
    {
        error = PQresultErrorMessage (result);
        PQclear (result);
        return -1;
    }

    if (PQntuples (result) == 0)
    {
        PQclear (result);
        return -1;
    }

    const int value = juce::String (PQgetvalue (result, 0, 0)).getIntValue();
    PQclear (result);
    return value;
   #endif
}

std::vector<std::pair<juce::String, int>> ProgressDatabase::loadExerciseResults()
{
    std::vector<std::pair<juce::String, int>> results;

   #ifndef CURSOMUSICA_HAS_POSTGRES
    error = "built without libpq";
    return results;
   #else
    if (connection == nullptr)
    {
        error = "not connected";
        return results;
    }

    char* escapedSchema = PQescapeIdentifier (static_cast<PGconn*> (connection),
                                              config.schema.toRawUTF8(),
                                              (size_t) config.schema.getNumBytesAsUTF8());
    if (escapedSchema == nullptr)
    {
        error = "invalid schema name";
        return results;
    }

    const juce::String schema (escapedSchema);
    PQfreemem (escapedSchema);

    const juce::String sql =
        "SELECT exercise_id, accuracy FROM " + schema + ".exercise_result"
        " WHERE student_id = $1;";

    const char* values[] = { config.student.toRawUTF8() };
    PGresult* result = PQexecParams (static_cast<PGconn*> (connection), sql.toRawUTF8(),
                                     1, nullptr, values, nullptr, nullptr, 0);

    const auto status = PQresultStatus (result);
    if (status != PGRES_TUPLES_OK)
    {
        error = PQresultErrorMessage (result);
        PQclear (result);
        return results;
    }

    const int rows = PQntuples (result);
    results.reserve ((size_t) rows);

    for (int i = 0; i < rows; ++i)
        results.emplace_back (juce::String (PQgetvalue (result, i, 0)),
                              juce::String (PQgetvalue (result, i, 1)).getIntValue());

    PQclear (result);
    return results;
   #endif
}

} // namespace cursomusica::data
