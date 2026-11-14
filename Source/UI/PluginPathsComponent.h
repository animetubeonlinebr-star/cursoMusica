#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include <functional>
#include <memory>

#include "Audio/PluginSearchPaths.h"
#include "UI/Design/Panel.h"

namespace cursomusica
{

// Reaper-like window that lists the folders the VST3 scan must look into.
//
// The grid has two columns: the folder path on the left and a small "…" button on
// the right that opens a directory chooser for that row. Adding and removing
// entries is done from the footer. Every change is written through immediately,
// so the settings window does not have to know the list changed.
class PluginPathsComponent final : public juce::Component
{
public:
    // Owns the folder list; called on every add/edit/remove.
    explicit PluginPathsComponent (PluginSearchPaths& pathsToEdit);
    ~PluginPathsComponent() override;

    void paint (juce::Graphics& g) override;
    void resized() override;

    std::function<void()> onCloseRequested;
    // Fired after the list changes, so the owner can persist it and refresh.
    std::function<void()> onPathsChanged;

private:
    class RowModel;

    void addFolder();
    void removeSelectedFolder();
    void chooseFolderForRow (int row);
    void finishFolderChoice (int row, const juce::File& folder);

    PluginSearchPaths& paths;
    std::unique_ptr<RowModel> model;
    std::unique_ptr<juce::FileChooser> chooser;
    // Which row the pending chooser is editing; -1 means "adding a new folder".
    int chooserRow = -1;

    juce::Label titleLabel;
    juce::Label hintLabel;
    juce::Label pathHeader;
    juce::Label chooseHeader;
    juce::ListBox list;
    juce::TextButton addButton { juce::String::fromUTF8 ("Adicionar pasta") };
    juce::TextButton removeButton { juce::String::fromUTF8 ("Remover") };
    juce::TextButton closeButton { juce::String::fromUTF8 ("Fechar") };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginPathsComponent)
};

} // namespace cursomusica
