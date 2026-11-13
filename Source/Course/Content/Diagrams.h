#pragma once

#include <juce_core/juce_core.h>

// Access to the JPG diagrams embedded through juce_add_binary_data (see
// CMakeLists.txt and tools/make_diagrams.py). The resources are generated from
// Source/Course/Content/Diagrams/*.jpg; a ContentItem of kind image refers to
// one of them by its file stem (e.g. "f_caged_conexao").
//
// This header only needs juce_core, so the tests can check that every diagram
// named by the course content actually exists in the build.
namespace cursomusica::content
{

// The stems available in the build, in resource order.
juce::StringArray diagramNames();

// True when a diagram with this stem was embedded in the binary.
bool diagramExists (const juce::String& name);

// Raw JPEG bytes of a diagram (null when absent); `sizeInBytes` receives the
// length. Used by the UI to decode the image for painting.
const char* diagramData (const juce::String& name, int& sizeInBytes);

} // namespace cursomusica::content
