#include "Course/Content/Diagrams.h"

#if JUCE_TARGET_HAS_BINARY_DATA
 #include <BinaryData.h>
#endif

namespace cursomusica::content
{

#if JUCE_TARGET_HAS_BINARY_DATA
namespace
{
    using namespace CursoMusicaDiagrams;

    // juce_add_binary_data derives the resource name from the file name,
    // replacing '.' with '_' — so "f_caged_conexao.jpg" becomes
    // "f_caged_conexao_jpg". Content refers to a diagram by its stem, so we
    // strip that suffix to present readable names and add it back on lookup.
    juce::String stemForResource (const juce::String& resourceName)
    {
        for (const auto* suffix : { "__jpeg", "__jpg", "_jpeg", "_jpg" })
            if (resourceName.endsWithIgnoreCase (suffix))
                return resourceName.dropLastCharacters ((int) juce::String (suffix).length());
        return resourceName;
    }

    const char* findResource (const juce::String& stem, int& sizeInBytes)
    {
        int size = 0;
        if (const auto* data = getNamedResource (stem.toRawUTF8(), size))
        {
            sizeInBytes = size;
            return data;
        }

        for (const auto* suffix : { "_jpg", "_jpeg", "__jpg", "__jpeg" })
        {
            const auto mangled = stem + suffix;
            if (const auto* data = getNamedResource (mangled.toRawUTF8(), size))
            {
                sizeInBytes = size;
                return data;
            }
        }

        sizeInBytes = 0;
        return nullptr;
    }
}
#endif

juce::StringArray diagramNames()
{
    juce::StringArray names;

   #if JUCE_TARGET_HAS_BINARY_DATA
    for (int i = 0; i < namedResourceListSize; ++i)
        names.add (stemForResource (namedResourceList[i]));
   #endif

    return names;
}

bool diagramExists (const juce::String& name)
{
   #if JUCE_TARGET_HAS_BINARY_DATA
    int size = 0;
    return findResource (name, size) != nullptr;
   #else
    juce::ignoreUnused (name);
    return false;
   #endif
}

const char* diagramData (const juce::String& name, int& sizeInBytes)
{
   #if JUCE_TARGET_HAS_BINARY_DATA
    return findResource (name, sizeInBytes);
   #else
    juce::ignoreUnused (name);
    sizeInBytes = 0;
    return nullptr;
   #endif
}

} // namespace cursomusica::content

