#include "UI/SettingsComponent.h"

#include "UI/Design/Theme.h"

namespace cursomusica
{

namespace th = cursomusica::theme;

// Bridges a list of plugin descriptions (available) or chain entries to a ListBox.
class SettingsComponent::PluginListModel final : public juce::ListBoxModel
{
public:
    enum class Kind { available, chain };

    PluginListModel (SettingsComponent& ownerToUse, Kind kindToUse)
        : owner (ownerToUse), kind (kindToUse)
    {
    }

    int getNumRows() override
    {
        if (kind == Kind::available)
            return owner.pluginHost.getKnownPluginList().getNumTypes();

        return owner.audioEngine.getPluginChain().getNumPlugins();
    }

    void paintListBoxItem (int row, juce::Graphics& g, int width, int height, bool selected) override
    {
        if (selected)
        {
            g.setColour (th::colour::accent.withAlpha (0.35f));
            g.fillRect (0, 0, width, height);
        }

        juce::String text;
        if (kind == Kind::available)
        {
            const auto types = owner.pluginHost.getKnownPluginList().getTypes();
            if (row < types.size())
                text = types[row].name + "  (" + types[row].manufacturerName + ")";
        }
        else if (auto* plugin = owner.audioEngine.getPluginChain().getPlugin (row))
        {
            text = plugin->getName();
        }

        g.setColour (th::colour::textPrimary);
        g.setFont (th::type::makeFont (th::type::body));
        g.drawText (text, 8, 0, width - 16, height, juce::Justification::centredLeft, true);
    }

private:
    SettingsComponent& owner;
    Kind kind;
};

SettingsComponent::SettingsComponent (AudioEngine& engine, PluginHost& host)
    : audioEngine (engine), pluginHost (host)
{
    titleLabel.setText ("Settings", juce::dontSendNotification);
    titleLabel.setFont (th::type::makeFont (th::type::title, true));
    titleLabel.setColour (juce::Label::textColourId, th::colour::textPrimary);
    addAndMakeVisible (titleLabel);

    closeButton.onClick = [this] { if (onCloseRequested) onCloseRequested(); };
    addAndMakeVisible (closeButton);

    // ---- Audio device ----------------------------------------------------
    addAndMakeVisible (audioPanel);

    // ASIO / WASAPI selection, input/output device, sample rate, buffer size and
    // channel routing all come from the stock JUCE selector, which is the
    // canonical UI for AudioDeviceManager.
    deviceSelector = std::make_unique<juce::AudioDeviceSelectorComponent> (
        audioEngine.getDeviceManager(),
        1, 2,   // input channels
        0, 2,   // output channels
        false,  // no MIDI input
        false,  // no MIDI output
        false,  // not stereo pairs
        true);  // hide advanced options behind a button
    deviceSelector->setSize (400, 300);
    audioPanel.addAndMakeVisible (*deviceSelector);

    // ---- VST3 chain ------------------------------------------------------
    addAndMakeVisible (pluginPanel);

    scanButton.onClick = [this]
    {
        scanStatus.setText ("Scanning...", juce::dontSendNotification);
        pluginHost.scanForPlugins (
            [this] (float progress, const juce::String& current)
            {
                scanStatus.setText ("Scanning " + juce::String (juce::roundToInt (progress * 100.0f))
                                        + "% — " + current,
                                    juce::dontSendNotification);
            },
            [this]
            {
                scanStatus.setText ("Scan finished.", juce::dontSendNotification);
                refreshPluginList();
            });
    };
    pluginPanel.addAndMakeVisible (scanButton);

    availableModel = std::make_unique<PluginListModel> (*this, PluginListModel::Kind::available);
    availableList.setModel (availableModel.get());
    availableList.setRowHeight (24);
    availableList.setColour (juce::ListBox::backgroundColourId, th::colour::surfaceRaised);
    pluginPanel.addAndMakeVisible (availableList);

    addButton.onClick = [this] { addSelectedPluginToChain(); };
    pluginPanel.addAndMakeVisible (addButton);

    chainModel = std::make_unique<PluginListModel> (*this, PluginListModel::Kind::chain);
    chainList.setModel (chainModel.get());
    chainList.setRowHeight (24);
    chainList.setColour (juce::ListBox::backgroundColourId, th::colour::surfaceRaised);
    pluginPanel.addAndMakeVisible (chainList);

    removeButton.onClick = [this] { removeSelectedChainPlugin(); };
    editorButton.onClick = [this] { openEditorForSelectedChainPlugin(); };
    pluginPanel.addAndMakeVisible (removeButton);
    pluginPanel.addAndMakeVisible (editorButton);

    scanStatus.setText ("Not scanned yet.", juce::dontSendNotification);
    scanStatus.setFont (th::type::makeFont (th::type::caption));
    scanStatus.setColour (juce::Label::textColourId, th::colour::textSecondary);
    pluginPanel.addAndMakeVisible (scanStatus);

    pluginHost.loadKnownPlugins();
    refreshPluginList();
    refreshChainList();

    setSize (900, 620);
}

SettingsComponent::~SettingsComponent() = default;

void SettingsComponent::paint (juce::Graphics& g)
{
    g.fillAll (th::colour::background);
}

void SettingsComponent::refreshPluginList()
{
    availableList.updateContent();
    availableList.repaint();
}

void SettingsComponent::refreshChainList()
{
    chainList.updateContent();
    chainList.repaint();
}

void SettingsComponent::addSelectedPluginToChain()
{
    const int row = availableList.getSelectedRow();
    const auto types = pluginHost.getKnownPluginList().getTypes();

    if (row < 0 || row >= types.size())
        return;

    juce::String error;
    auto instance = pluginHost.createInstance (types[row],
                                              audioEngine.getCurrentSampleRate(),
                                              audioEngine.getCurrentBlockSize(),
                                              error);

    if (instance == nullptr)
    {
        scanStatus.setText ("Could not load plugin: " + error, juce::dontSendNotification);
        return;
    }

    audioEngine.getPluginChain().addPlugin (std::move (instance));
    audioEngine.preparePluginChain();
    refreshChainList();
}

void SettingsComponent::removeSelectedChainPlugin()
{
    const int row = chainList.getSelectedRow();
    if (row < 0)
        return;

    audioEngine.getPluginChain().removePlugin (row);
    refreshChainList();
}

void SettingsComponent::openEditorForSelectedChainPlugin()
{
    const int row = chainList.getSelectedRow();
    if (auto* plugin = audioEngine.getPluginChain().getPlugin (row))
    {
        if (! plugin->hasEditor())
        {
            scanStatus.setText ("This plugin has no editor.", juce::dontSendNotification);
            return;
        }

        if (auto* editor = plugin->createEditorIfNeeded())
        {
            editorWindow = std::make_unique<juce::DocumentWindow> (
                plugin->getName(),
                th::colour::background,
                juce::DocumentWindow::closeButton);

            editorWindow->setUsingNativeTitleBar (true);
            editorWindow->setContentOwned (editor, true);
            editorWindow->setResizable (true, true);
            editorWindow->centreWithSize (editorWindow->getWidth(), editorWindow->getHeight());
            editorWindow->setVisible (true);
        }
    }
}

void SettingsComponent::resized()
{
    auto bounds = getLocalBounds().reduced (th::spacing::lg);

    auto header = bounds.removeFromTop (40);
    closeButton.setBounds (header.removeFromRight (90).reduced (0, 4));
    titleLabel.setBounds (header);

    bounds.removeFromTop (th::spacing::md);

    auto left = bounds.removeFromLeft (bounds.getWidth() / 2 - th::spacing::sm);
    bounds.removeFromLeft (th::spacing::md);
    auto right = bounds;

    audioPanel.setBounds (left);

    auto audioContent = audioPanel.getContentBounds();
    if (deviceSelector != nullptr)
        deviceSelector->setBounds (audioContent);

    pluginPanel.setBounds (right);

    auto content = pluginPanel.getContentBounds();

    auto topRow = content.removeFromTop (32);
    scanButton.setBounds (topRow.removeFromLeft (100));
    topRow.removeFromLeft (th::spacing::sm);
    scanStatus.setBounds (topRow);

    content.removeFromTop (th::spacing::md);

    // Upper half: available plugins with the add action underneath.
    auto availableArea = content.removeFromTop (content.getHeight() / 2);
    auto addRow = availableArea.removeFromBottom (32);
    availableArea.removeFromBottom (th::spacing::sm);
    availableList.setBounds (availableArea);
    addButton.setBounds (addRow.removeFromLeft (juce::jmin (200, addRow.getWidth())));

    content.removeFromTop (th::spacing::md);

    // Lower half: the input chain with its actions underneath.
    auto chainArea = content;
    auto chainButtons = chainArea.removeFromBottom (32);
    chainArea.removeFromBottom (th::spacing::sm);
    chainList.setBounds (chainArea);

    const int half = (chainButtons.getWidth() - th::spacing::sm) / 2;
    removeButton.setBounds (chainButtons.removeFromLeft (half));
    chainButtons.removeFromLeft (th::spacing::sm);
    editorButton.setBounds (chainButtons);
}

} // namespace cursomusica
