#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace cursomusica
{

// Card surface with a title bar, used as the base for the app panels.
class Panel : public juce::Component
{
public:
    explicit Panel (juce::String titleText);

    void paint (juce::Graphics& g) override;

    juce::Rectangle<int> getContentBounds() const;

private:
    juce::String title;
};

} // namespace cursomusica
