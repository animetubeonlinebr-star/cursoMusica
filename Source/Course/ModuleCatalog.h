#pragma once

#include "Course/Module.h"

#include <vector>

namespace cursomusica
{

// The course content, compiled into the binary (ADR 0005).
//
// docs/MUSIC.md is the source of truth for the wording; this catalogue is its
// executable mirror. Only modules with content here are playable.
class ModuleCatalog
{
public:
    static const std::vector<CourseModule>& getModules();

    // Returns the module with this number, or nullptr when it has no content yet.
    static const CourseModule* findModule (int number);
};

} // namespace cursomusica
