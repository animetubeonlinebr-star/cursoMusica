#pragma once

#include <juce_audio_utils/juce_audio_utils.h>

#include "Audio/AudioEngine.h"
#include "Audio/PluginHost.h"
#include "UI/AudioPortsPanel.h"
#include "UI/Design/Panel.h"
#include "UI/PluginPathsComponent.h"

namespace cursomusica
{

// Settings view: audio device configuration and the VST3 input chain.
class SettingsComponent final : public juce::Component,
                                private juce::ChangeListener
{
public:
    SettingsComponent (AudioEngine& engine, PluginHost& host);
    ~SettingsComponent() override;

    void paint (juce::Graphics& g) override;
    void resized() override;

    std::function<void()> onCloseRequested;

private:
    class PluginListModel;
    class PluginListBox;

    void refreshPluginList();
    void addSelectedPluginToChain();
    void removeSelectedChainPlugin();
    void openEditorForSelectedChainPlugin();
    void refreshChainList();
    void openSearchPathsWindow();
    void closeSearchPathsWindow();
    void searchPathsChanged();

    // Keeps the port list in step with the selected device (REQ-023).
    void changeListenerCallback (juce::ChangeBroadcaster* source) override;

    AudioEngine& audioEngine;
    PluginHost& pluginHost;

    juce::Label titleLabel;
    juce::TextButton closeButton { "Close" };

    // Audio tab.
    Panel audioPanel { "Audio device" };
    std::unique_ptr<juce::AudioDeviceSelectorComponent> deviceSelector;
    AudioPortsPanel audioPortsPanel;

    // Plugin tab.
    Panel pluginPanel { "VST3 plugins" };
    juce::TextButton scanButton { "Scan" };
    juce::TextButton pathsButton { juce::String::fromUTF8 ("Pastas…") };
    juce::TextButton addButton { "Add to input chain" };
    juce::Label scanStatus;
    juce::ListBox availableList;
    juce::ListBox chainList;
    juce::TextButton removeButton { "Remove" };
    juce::TextButton editorButton { "Open editor" };

    std::unique_ptr<PluginListModel> availableModel;
    std::unique_ptr<PluginListModel> chainModel;

    // Holds the currently open plugin editor window, if any.
    std::unique_ptr<juce::DocumentWindow> editorWindow;

    // Holds the VST3 folder-list window, if any.
    std::unique_ptr<juce::DocumentWindow> searchPathsWindow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsComponent)
};

} // namespace cursomusica
