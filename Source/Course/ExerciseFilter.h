#pragma once

#include <juce_core/juce_core.h>

#include <vector>

#include "Course/Module.h"

namespace cursomusica::course
{

// Indices of `module`'s exercises that belong to a topic.
//
// An empty `lessonId` means "every exercise of the module" (the "all topics"
// link). The panel filters against the module it currently holds, so the caller
// must pass the module the filter belongs to: applying module 1's topic id to
// another module's exercises matches nothing, which is what left the exercise
// list empty after visiting a different module.
inline std::vector<int> exercisesForTopic (const CourseModule& module, const juce::String& lessonId)
{
    std::vector<int> indices;

    for (int i = 0; i < (int) module.exercises.size(); ++i)
    {
        if (lessonId.isNotEmpty() && module.exercises[(size_t) i].lessonId != lessonId)
            continue;

        indices.push_back (i);
    }

    return indices;
}

} // namespace cursomusica::course
