#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include <functional>

#include "Data/ProgressDatabase.h"
#include "UI/Design/Panel.h"

namespace cursomusica
{

// Window that configures the PostgreSQL progress database (ADR 0006).
//
// The client asked for the progress to be stored in a PostgreSQL server (port
// 5432, schema "curso-musica"), but a Windows app started from the Start menu
// never inherits PGHOST: without this window the mirror could never be turned
// on, the schema was never created and the progress never left the machine.
//
// Only the non-secret fields are edited here; the password is taken from the
// PGPASSWORD environment variable and is never typed into nor stored by the app
// (docs/SECURITY.md).
class DatabaseSettingsComponent final : public juce::Component
{
public:
    explicit DatabaseSettingsComponent (const data::PostgresConfig& initial);
    ~DatabaseSettingsComponent() override;

    void paint (juce::Graphics& g) override;
    void resized() override;

    std::function<void()> onCloseRequested;
    // Fired when the user saves, with the settings to persist.
    std::function<void (const data::PostgresConfig&)> onSave;

private:
    // Reads the fields back into a PostgresConfig (password from the environment).
    data::PostgresConfig collect() const;
    void testConnection();
    void save();

    juce::Label titleLabel;
    juce::Label hintLabel;

    juce::ToggleButton enabledButton;
    juce::Label hostLabel, portLabel, userLabel, databaseLabel, schemaLabel;
    juce::TextEditor hostEditor, portEditor, userEditor, databaseEditor, schemaEditor;
    juce::Label statusLabel;

    juce::TextButton testButton { juce::String::fromUTF8 ("Testar conexão") };
    juce::TextButton saveButton { "Salvar" };
    juce::TextButton closeButton { "Fechar" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DatabaseSettingsComponent)
};

} // namespace cursomusica
