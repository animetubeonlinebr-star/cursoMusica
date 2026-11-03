#pragma once

#include <juce_core/juce_core.h>

#include <vector>

namespace cursomusica
{

// Data model for the course. Content lives in ModuleCatalog.cpp; the source of
// truth for the wording is docs/MUSIC.md (owner: musician).

// One teaching block of a module, shown before any exercise (REQ-003).
struct LessonBlock
{
    juce::String id;      // "A", "B", ...
    juce::String title;
    juce::StringArray paragraphs;
};

// A practice item with an automatic check (REQ-008, REQ-009).
struct Exercise
{
    juce::String id;      // "EX-1.1"
    juce::String title;
    juce::String goal;
    juce::String check;   // how the app verifies it
};

// The pattern and link a module must cite (REQ-007, REQ-010).
struct PracticeTrack
{
    juce::String patternId;     // "PTN-R-PALM"
    juce::String patternUse;
    juce::StringArray guitarists; // reference players, cited as links
};

// A guitar shape of the CAGED system.
struct CagedShape
{
    juce::String shape;   // "C", "A", "G", "E", "D"
    juce::String bassString;
    juce::String region;
};

struct CourseModule
{
    int number = 0;
    juce::String title;
    juce::String objective;
    int level = 0;              // 1..7 progressive model
    int targetBpm = 0;          // REQ-015
    float onGridTarget = 0.0f;  // alignment target for this module
    bool implemented = false;

    std::vector<LessonBlock> lessons;
    std::vector<Exercise> exercises;
    juce::String gateChallenge;
    PracticeTrack practice;
    std::vector<CagedShape> caged;
};

} // namespace cursomusica
