#include "MainComponent.h"

#include "UI/Design/Theme.h"

namespace cursomusica
{

namespace th = cursomusica::theme;

MainComponent::MainComponent()
{
    juce::LookAndFeel::setDefaultLookAndFeel (&lookAndFeel);

    audioEngine.initialise();
    pluginHost.loadKnownPlugins();

    titleLabel.setText ("Curso Musica Studio", juce::dontSendNotification);
    titleLabel.setFont (th::type::makeFont (th::type::title, true));
    titleLabel.setColour (juce::Label::textColourId, th::colour::textPrimary);
    addAndMakeVisible (titleLabel);

    subtitleLabel.setText (juce::String::fromUTF8 ("Estudo de guitarra com análise de áudio em tempo real"), juce::dontSendNotification);
    subtitleLabel.setFont (th::type::makeFont (th::type::body));
    subtitleLabel.setColour (juce::Label::textColourId, th::colour::textSecondary);
    addAndMakeVisible (subtitleLabel);

    settingsButton.onClick = [this] { showSettings(); };
    addAndMakeVisible (settingsButton);

    tunerButton.onClick = [this] { showTuner(); };
    addAndMakeVisible (tunerButton);

    modulesButton.onClick = [this] { showModules(); };
    addAndMakeVisible (modulesButton);

    addAndMakeVisible (tunerDisplay);
    addAndMakeVisible (devicePanel);
    addAndMakeVisible (transportPanel);

    tunerDisplay.setReferenceHz (tuningSettings.getReferenceHz());

    referenceLabel.setText (juce::String::fromUTF8 ("Nenhum material carregado"), juce::dontSendNotification);
    referenceLabel.setFont (th::type::makeFont (th::type::body));
    referenceLabel.setColour (juce::Label::textColourId, th::colour::textSecondary);
    referenceLabel.setJustificationType (juce::Justification::centredLeft);
    studyReferencePanel.addAndMakeVisible (referenceLabel);
    addAndMakeVisible (studyReferencePanel);

    setSize (1040, 680);

    // Poll the engine so the tuner and meter show real values, not dummies.
    startTimerHz (30);
}

MainComponent::~MainComponent()
{
    stopTimer();
    modules.reset();
    tuner.reset();
    settings.reset();
    audioEngine.shutdown();
    juce::LookAndFeel::setDefaultLookAndFeel (nullptr);
}

void MainComponent::showModules()
{
    if (modules == nullptr)
    {
        modules = std::make_unique<ModuleComponent> (audioEngine);
        modules->onCloseRequested = [this] { hideModules(); };
        addAndMakeVisible (*modules);
    }

    modules->setBounds (getLocalBounds());
    modules->toFront (true);
}

void MainComponent::hideModules()
{
    modules.reset();
}

void MainComponent::timerCallback()
{
    tunerDisplay.setFrequencyHz (audioEngine.getDetectedFrequencyHz());
}

void MainComponent::showTuner()
{
    if (tuner == nullptr)
    {
        tuner = std::make_unique<TunerComponent> (audioEngine, tuningSettings);
        tuner->onCloseRequested = [this] { hideTuner(); };
        addAndMakeVisible (*tuner);
    }

    tuner->setBounds (getLocalBounds());
    tuner->toFront (true);
}

void MainComponent::hideTuner()
{
    tuner.reset();
    // The pitch may have changed while the tuner was open.
    tunerDisplay.setReferenceHz (tuningSettings.getReferenceHz());
}

void MainComponent::showSettings()
{
    if (settings == nullptr)
    {
        settings = std::make_unique<SettingsComponent> (audioEngine, pluginHost);
        settings->onCloseRequested = [this] { hideSettings(); };
        addAndMakeVisible (*settings);
    }

    settings->setBounds (getLocalBounds());
    settings->toFront (true);
}

void MainComponent::hideSettings()
{
    settings.reset();
}

void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (th::colour::background);
}

void MainComponent::resized()
{
    auto bounds = getLocalBounds().reduced (th::spacing::lg);

    auto header = bounds.removeFromTop (64);
    settingsButton.setBounds (header.removeFromRight (110).withSizeKeepingCentre (110, 34));
    header.removeFromRight (th::spacing::sm);
    tunerButton.setBounds (header.removeFromRight (110).withSizeKeepingCentre (110, 34));
    header.removeFromRight (th::spacing::sm);
    modulesButton.setBounds (header.removeFromRight (110).withSizeKeepingCentre (110, 34));
    header.removeFromRight (th::spacing::md);
    auto titleArea = header;
    titleLabel.setBounds (titleArea.removeFromTop (32));
    subtitleLabel.setBounds (titleArea.removeFromTop (22));

    bounds.removeFromTop (th::spacing::md);

    // Tuner dominates; the right column supports it.
    auto rightColumn = bounds.removeFromRight (320);
    bounds.removeFromRight (th::spacing::lg);

    tunerDisplay.setBounds (bounds);

    devicePanel.setBounds (rightColumn.removeFromTop (200));
    rightColumn.removeFromTop (th::spacing::md);
    transportPanel.setBounds (rightColumn.removeFromTop (220));
    rightColumn.removeFromTop (th::spacing::md);
    studyReferencePanel.setBounds (rightColumn);
}

} // namespace cursomusica
