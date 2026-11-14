#include "UI/PluginPathsComponent.h"

#include "UI/Design/Theme.h"

namespace cursomusica
{

namespace th = cursomusica::theme;

namespace
{
    constexpr int rowHeight = 30;
}

// One grid row: the folder path on the left, the "…" button on the right. The
// row owns its widgets and tells the component which row a click came from.
class PluginPathsComponent::RowModel final : public juce::Component,
                                             public juce::ListBoxModel
{
public:
    explicit RowModel (PluginPathsComponent& ownerToUse) : owner (ownerToUse) {}

    int getNumRows() override
    {
        return owner.paths.size();
    }

    juce::Component* refreshComponentForRow (int rowNumber, bool /*isRowSelected*/,
                                             juce::Component* existingComponentToUpdate) override
    {
        auto* row = dynamic_cast<Row*> (existingComponentToUpdate);
        if (row == nullptr)
        {
            row = new Row (*this, rowNumber);
            existingComponentToUpdate = row;
        }

        row->setRow (rowNumber, owner.paths[rowNumber]);
        return existingComponentToUpdate;
    }

    void paintListBoxItem (int, juce::Graphics&, int, int, bool) override
    {
        // The row component paints itself; nothing to do here.
    }

    void editRow (int row) { owner.chooseFolderForRow (row); }

private:
    class Row final : public juce::Component
    {
    public:
        Row (RowModel& modelToUse, int rowToUse)
            : model (modelToUse)
        {
            setRow (rowToUse, {});

            pathLabel.setFont (th::type::makeFont (th::type::body));
            pathLabel.setColour (juce::Label::textColourId, th::colour::textPrimary);
            pathLabel.setInterceptsMouseClicks (false, false);
            addAndMakeVisible (pathLabel);

            browseButton.setButtonText ("...");
            browseButton.setTooltip (juce::String::fromUTF8 ("Escolher a pasta"));
            browseButton.onClick = [this] { model.editRow (getRow()); };
            addAndMakeVisible (browseButton);
        }

        void setRow (int rowToUse, const juce::String& path)
        {
            row = rowToUse;
            pathLabel.setText (path, juce::dontSendNotification);
        }

        int getRow() const noexcept { return row; }

        void paint (juce::Graphics& g) override
        {
            g.setColour (th::colour::surfaceRaised.withAlpha (0.35f));
            g.fillRoundedRectangle (getLocalBounds().toFloat().reduced (2.0f), th::radius::sm);
        }

        void resized() override
        {
            auto bounds = getLocalBounds().reduced (4, 3);
            browseButton.setBounds (bounds.removeFromRight (34));
            bounds.removeFromRight (th::spacing::xs);
            pathLabel.setBounds (bounds);
        }

    private:
        RowModel& model;
        int row = 0;
        juce::Label pathLabel;
        juce::TextButton browseButton;
    };

    PluginPathsComponent& owner;
};

PluginPathsComponent::PluginPathsComponent (PluginSearchPaths& pathsToEdit)
    : paths (pathsToEdit)
{
    titleLabel.setText (juce::String::fromUTF8 ("Pastas de plugins VST3"), juce::dontSendNotification);
    titleLabel.setFont (th::type::makeFont (th::type::title, true));
    titleLabel.setColour (juce::Label::textColourId, th::colour::textPrimary);
    addAndMakeVisible (titleLabel);

    hintLabel.setText (juce::String::fromUTF8 (
                           "Informe as pastas onde estão os arquivos .vst3. A varredura procura "
                           "também nos locais padrão do sistema."),
                       juce::dontSendNotification);
    hintLabel.setFont (th::type::makeFont (th::type::caption));
    hintLabel.setColour (juce::Label::textColourId, th::colour::textSecondary);
    addAndMakeVisible (hintLabel);

    model = std::make_unique<RowModel> (*this);
    list.setModel (model.get());
    list.setRowHeight (rowHeight);
    list.setColour (juce::ListBox::backgroundColourId, th::colour::surface);
    list.setColour (juce::ListBox::outlineColourId, th::colour::border);
    list.setOutlineThickness (1);
    addAndMakeVisible (list);

    // Column captions, so the two-column grid reads as "path | choose".
    pathHeader.setText (juce::String::fromUTF8 ("Pasta"), juce::dontSendNotification);
    chooseHeader.setText (juce::String::fromUTF8 ("Selecionar"), juce::dontSendNotification);
    for (auto* header : { &pathHeader, &chooseHeader })
    {
        header->setFont (th::type::makeFont (th::type::caption, true));
        header->setColour (juce::Label::textColourId, th::colour::textSecondary);
        addAndMakeVisible (*header);
    }

    addButton.onClick = [this] { addFolder(); };
    removeButton.onClick = [this] { removeSelectedFolder(); };
    closeButton.onClick = [this] { if (onCloseRequested) onCloseRequested(); };
    addAndMakeVisible (addButton);
    addAndMakeVisible (removeButton);
    addAndMakeVisible (closeButton);

    setSize (640, 420);
}

PluginPathsComponent::~PluginPathsComponent() = default;

void PluginPathsComponent::paint (juce::Graphics& g)
{
    g.fillAll (th::colour::background);
}

void PluginPathsComponent::resized()
{
    auto bounds = getLocalBounds().reduced (th::spacing::lg);

    auto header = bounds.removeFromTop (32);
    closeButton.setBounds (header.removeFromRight (100));
    titleLabel.setBounds (header);

    bounds.removeFromTop (th::spacing::sm);
    hintLabel.setBounds (bounds.removeFromTop (34));
    bounds.removeFromTop (th::spacing::md);

    auto footer = bounds.removeFromBottom (32);
    addButton.setBounds (footer.removeFromLeft (160));
    footer.removeFromLeft (th::spacing::sm);
    removeButton.setBounds (footer.removeFromLeft (120));

    bounds.removeFromBottom (th::spacing::sm);

    // The header row must line up with the row layout in Row::resized().
    auto headerRow = bounds.removeFromTop (20);
    headerRow.removeFromLeft (4);
    chooseHeader.setBounds (headerRow.removeFromRight (34 + 4));
    headerRow.removeFromRight (th::spacing::xs);
    pathHeader.setBounds (headerRow);

    list.setBounds (bounds);
}

void PluginPathsComponent::addFolder()
{
    chooserRow = -1;

    chooser = std::make_unique<juce::FileChooser> (
        juce::String::fromUTF8 ("Selecione a pasta com plugins VST3"),
        juce::File::getSpecialLocation (juce::File::userHomeDirectory),
        "*");

    chooser->launchAsync (juce::FileBrowserComponent::openMode
                              | juce::FileBrowserComponent::canSelectDirectories,
                          [this] (const juce::FileChooser& fc)
                          {
                              finishFolderChoice (-1, fc.getResult());
                          });
}

void PluginPathsComponent::removeSelectedFolder()
{
    const int row = list.getSelectedRow();
    if (row < 0 || row >= paths.size())
        return;

    paths.remove (paths[row]);
    list.updateContent();
    list.repaint();
    if (onPathsChanged)
        onPathsChanged();
}

void PluginPathsComponent::chooseFolderForRow (int row)
{
    chooserRow = row;

    const juce::File start = paths[row].isNotEmpty() ? juce::File (paths[row])
                                                     : juce::File::getSpecialLocation (juce::File::userHomeDirectory);

    chooser = std::make_unique<juce::FileChooser> (
        juce::String::fromUTF8 ("Selecione a pasta com plugins VST3"), start, "*");

    chooser->launchAsync (juce::FileBrowserComponent::openMode
                              | juce::FileBrowserComponent::canSelectDirectories,
                          [this, row] (const juce::FileChooser& fc)
                          {
                              finishFolderChoice (row, fc.getResult());
                          });
}

void PluginPathsComponent::finishFolderChoice (int row, const juce::File& folder)
{
    if (! folder.isDirectory())
        return;

    const auto selected = folder.getFullPathName();

    if (row >= 0)
    {
        // Editing a row: replace it, but ignore a no-op choice.
        if (paths[row].equalsIgnoreCase (selected))
            return;

        paths.remove (paths[row]);
    }

    if (! paths.add (selected))
    {
        // A duplicate or a full list: restore what the row had and tell the user.
        if (row >= 0)
            paths.add (folder.getFullPathName());

        hintLabel.setText (juce::String::fromUTF8 ("Pasta já adicionada (ou limite de ")
                               + juce::String (PluginSearchPaths::maxEntries)
                               + juce::String::fromUTF8 (" pastas atingido)."),
                           juce::dontSendNotification);
        hintLabel.setColour (juce::Label::textColourId, th::colour::danger);
        return;
    }

    hintLabel.setColour (juce::Label::textColourId, th::colour::textSecondary);
    list.updateContent();
    list.repaint();
    if (onPathsChanged)
        onPathsChanged();
}

} // namespace cursomusica
