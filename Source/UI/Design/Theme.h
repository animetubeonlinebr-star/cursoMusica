#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

// Single source of truth for the visual language.
//
// Values extracted from design-references/desiongne-grafico.jpg
// (the file also lives at the repository root as desiongne-grafico.jpg):
//   background #131418, surface #1f2229, violet accent #6030a0,
//   cyan accent #387090, success #30d080, danger #f05058.
namespace cursomusica::theme
{

namespace colour
{
    inline const juce::Colour background    { 0xff131418 };
    inline const juce::Colour surface       { 0xff1f2229 };
    inline const juce::Colour surfaceRaised { 0xff2a2e37 };
    inline const juce::Colour accent        { 0xff7b45c9 }; // violet, lifted for contrast
    inline const juce::Colour accentMuted   { 0xff4a2d7a };
    inline const juce::Colour accentAlt     { 0xff45a8c4 }; // cyan
    inline const juce::Colour textPrimary   { 0xfff8f8f8 };
    inline const juce::Colour textSecondary { 0xffb8b8c0 };
    inline const juce::Colour textDisabled  { 0xff6a6a74 };
    inline const juce::Colour border        { 0xff343841 };
    inline const juce::Colour danger        { 0xfff05058 };
    inline const juce::Colour success       { 0xff30d080 };
}

namespace type
{
    inline constexpr float display = 72.0f;
    inline constexpr float title   = 22.0f;
    inline constexpr float body    = 15.0f;
    inline constexpr float caption = 12.0f;

    inline juce::Font makeFont (float size, bool bold = false)
    {
        return juce::Font (juce::FontOptions().withHeight (size)
                                            .withStyle (bold ? "Bold" : "Regular"));
    }
}

namespace spacing
{
    inline constexpr int xs = 4;
    inline constexpr int sm = 8;
    inline constexpr int md = 16;
    inline constexpr int lg = 24;
    inline constexpr int xl = 40;
}

namespace radius
{
    inline constexpr float sm = 4.0f;
    inline constexpr float md = 8.0f;
    inline constexpr float lg = 14.0f;
}

namespace motion
{
    inline constexpr int fast   = 120;
    inline constexpr int normal = 220;
}

} // namespace cursomusica::theme
