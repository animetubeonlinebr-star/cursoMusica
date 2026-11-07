#include <juce_gui_extra/juce_gui_extra.h>

#include "MainComponent.h"
#include "UI/Design/Theme.h"

namespace cursomusica
{

class CursoMusicaApplication final : public juce::JUCEApplication
{
public:
    const juce::String getApplicationName() override    { return "Curso Musica Studio"; }
    const juce::String getApplicationVersion() override { return "0.1.0"; }
    bool moreThanOneInstanceAllowed() override          { return true; }

    void initialise (const juce::String&) override
    {
        mainWindow = std::make_unique<MainWindow> (getApplicationName());
    }

    void shutdown() override
    {
        mainWindow = nullptr;
    }

    void systemRequestedQuit() override
    {
        quit();
    }

private:
    class MainWindow final : public juce::DocumentWindow
    {
    public:
        explicit MainWindow (const juce::String& name)
            : DocumentWindow (name, theme::colour::background, DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new MainComponent(), true);
            setResizable (true, false);
            // Below this the three-pane study layout clips its own header.
            setResizeLimits (980, 660, 10000, 10000);
            centreWithSize (getWidth(), getHeight());
            setVisible (true);
        }

        void closeButtonPressed() override
        {
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

    std::unique_ptr<MainWindow> mainWindow;
};

} // namespace cursomusica

START_JUCE_APPLICATION (cursomusica::CursoMusicaApplication)
