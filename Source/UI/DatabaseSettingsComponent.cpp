#include "UI/DatabaseSettingsComponent.h"

#include "UI/Design/Theme.h"

namespace cursomusica
{

namespace th = cursomusica::theme;

namespace
{
    // A labelled single-line field, laid out by the caller.
    void styleEditor (juce::TextEditor& editor, const juce::String& placeholder)
    {
        editor.setFont (th::type::makeFont (th::type::body));
        editor.setTextToShowWhenEmpty (placeholder, th::colour::textSecondary);
        editor.setColour (juce::TextEditor::backgroundColourId, th::colour::surfaceRaised);
        editor.setColour (juce::TextEditor::textColourId, th::colour::textPrimary);
        editor.setColour (juce::TextEditor::outlineColourId, th::colour::border);
    }
}

DatabaseSettingsComponent::DatabaseSettingsComponent (const data::PostgresConfig& initial)
{
    titleLabel.setText (juce::String::fromUTF8 ("Banco de dados (progresso)"), juce::dontSendNotification);
    titleLabel.setFont (th::type::makeFont (th::type::title, true));
    titleLabel.setColour (juce::Label::textColourId, th::colour::textPrimary);
    addAndMakeVisible (titleLabel);

    hintLabel.setText (juce::String::fromUTF8 (
                           "O progresso é salvo localmente e espelhado neste servidor PostgreSQL. "
                           "A senha vem da variável de ambiente PGPASSWORD e não é guardada aqui."),
                       juce::dontSendNotification);
    hintLabel.setFont (th::type::makeFont (th::type::caption));
    hintLabel.setColour (juce::Label::textColourId, th::colour::textSecondary);
    addAndMakeVisible (hintLabel);

    enabledButton.setButtonText (juce::String::fromUTF8 ("Espelhar o progresso neste servidor"));
    enabledButton.setToggleState (! initial.disabled, juce::dontSendNotification);
    addAndMakeVisible (enabledButton);

    struct Field
    {
        juce::Label& label;
        juce::TextEditor& editor;
        const char* text;
        const char* placeholder;
    };

    const Field fields[] = {
        { hostLabel,     hostEditor,     "Host",     "localhost" },
        { portLabel,     portEditor,     "Porta",    "5432" },
        { userLabel,     userEditor,     "Usuário",  "cursomusica" },
        { databaseLabel, databaseEditor, "Banco",    "curso-musica" },
        { schemaLabel,   schemaEditor,   "Schema",   "curso-musica" },
    };

    for (const auto& field : fields)
    {
        field.label.setText (field.text, juce::dontSendNotification);
        field.label.setFont (th::type::makeFont (th::type::caption));
        field.label.setColour (juce::Label::textColourId, th::colour::textSecondary);
        addAndMakeVisible (field.label);
        styleEditor (field.editor, field.placeholder);
        addAndMakeVisible (field.editor);
    }

    hostEditor.setText (initial.host, juce::dontSendNotification);
    portEditor.setText (initial.port, juce::dontSendNotification);
    userEditor.setText (initial.user, juce::dontSendNotification);
    databaseEditor.setText (initial.dbname, juce::dontSendNotification);
    schemaEditor.setText (initial.schema, juce::dontSendNotification);

    statusLabel.setFont (th::type::makeFont (th::type::caption));
    statusLabel.setColour (juce::Label::textColourId, th::colour::textSecondary);
    addAndMakeVisible (statusLabel);

    testButton.onClick = [this] { testConnection(); };
    addAndMakeVisible (testButton);

    saveButton.onClick = [this] { save(); };
    addAndMakeVisible (saveButton);

    closeButton.onClick = [this] { if (onCloseRequested != nullptr) onCloseRequested(); };
    addAndMakeVisible (closeButton);

    setSize (460, 360);
}

DatabaseSettingsComponent::~DatabaseSettingsComponent() = default;

void DatabaseSettingsComponent::paint (juce::Graphics& g)
{
    g.fillAll (th::colour::background);
}

data::PostgresConfig DatabaseSettingsComponent::collect() const
{
    data::PostgresConfig config;
    config.host   = hostEditor.getText().trim();
    config.port   = portEditor.getText().trim();
    config.user   = userEditor.getText().trim();
    config.dbname = databaseEditor.getText().trim();
    config.schema = schemaEditor.getText().trim();
    config.disabled = ! enabledButton.getToggleState();

    if (config.port.isEmpty())
        config.port = "5432";

    if (config.schema.isEmpty())
        config.schema = "curso-musica";

    return config;
}

void DatabaseSettingsComponent::testConnection()
{
    auto config = collect();

    if (config.host.isEmpty())
    {
        statusLabel.setColour (juce::Label::textColourId, th::colour::danger);
        statusLabel.setText (juce::String::fromUTF8 ("Informe o host do servidor."), juce::dontSendNotification);
        return;
    }

    if (! data::ProgressDatabase::isCompiledIn())
    {
        statusLabel.setColour (juce::Label::textColourId, th::colour::danger);
        statusLabel.setText (juce::String::fromUTF8 ("Esta compilação não tem o cliente PostgreSQL (libpq)."),
                             juce::dontSendNotification);
        return;
    }

    // A short, explicit, user-triggered probe: it runs on the message thread and
    // the connection timeout is bounded by the database layer (5 s).
    data::ProgressDatabase database;
    config.disabled = false;

    if (database.connect (config) && database.ensureSchema())
    {
        statusLabel.setColour (juce::Label::textColourId, th::colour::success);
        statusLabel.setText (juce::String::fromUTF8 ("Conectado. Schema \"") + config.schema
                                 + juce::String::fromUTF8 ("\" pronto."),
                             juce::dontSendNotification);
    }
    else
    {
        statusLabel.setColour (juce::Label::textColourId, th::colour::danger);
        statusLabel.setText (juce::String::fromUTF8 ("Falha: ") + database.lastError(),
                             juce::dontSendNotification);
    }
}

void DatabaseSettingsComponent::save()
{
    const auto config = collect();

    if (onSave != nullptr)
        onSave (config);

    statusLabel.setColour (juce::Label::textColourId, th::colour::success);
    statusLabel.setText (juce::String::fromUTF8 ("Salvo. Reabra os módulos para reconectar."),
                         juce::dontSendNotification);
}

void DatabaseSettingsComponent::resized()
{
    auto bounds = getLocalBounds().reduced (th::spacing::lg);

    titleLabel.setBounds (bounds.removeFromTop (28));
    bounds.removeFromTop (th::spacing::xs);
    hintLabel.setBounds (bounds.removeFromTop (44));
    bounds.removeFromTop (th::spacing::sm);

    enabledButton.setBounds (bounds.removeFromTop (26));
    bounds.removeFromTop (th::spacing::sm);

    struct Row
    {
        juce::Label& label;
        juce::TextEditor& editor;
    };

    const Row rows[] = {
        { hostLabel, hostEditor },
        { portLabel, portEditor },
        { userLabel, userEditor },
        { databaseLabel, databaseEditor },
        { schemaLabel, schemaEditor },
    };

    for (const auto& row : rows)
    {
        auto line = bounds.removeFromTop (28);
        row.label.setBounds (line.removeFromLeft (90));
        row.editor.setBounds (line);
        bounds.removeFromTop (th::spacing::xs);
    }

    statusLabel.setBounds (bounds.removeFromTop (32));

    auto footer = bounds.removeFromBottom (32);
    closeButton.setBounds (footer.removeFromRight (90));
    footer.removeFromRight (th::spacing::sm);
    saveButton.setBounds (footer.removeFromRight (90));
    footer.removeFromRight (th::spacing::sm);
    testButton.setBounds (footer.removeFromRight (140));
}

} // namespace cursomusica
