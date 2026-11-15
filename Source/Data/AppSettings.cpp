#include "Data/AppSettings.h"

#include <memory>

namespace cursomusica::data
{

namespace
{
    // Created on first use and intentionally never destroyed: tearing it down
    // during static destruction would re-introduce an ordering hazard, and the
    // OS reclaims the memory at exit. Any pending write is flushed by
    // PropertiesFile's own 3 s timer long before that.
    std::unique_ptr<juce::PropertiesFile>& instance()
    {
        static std::unique_ptr<juce::PropertiesFile> file;
        return file;
    }
}

juce::PropertiesFile& AppSettings::get()
{
    auto& file = instance();

    if (file == nullptr)
    {
        juce::PropertiesFile::Options options;
        options.applicationName = "CursoMusica";
        options.filenameSuffix = ".settings";
        options.folderName = "CursoMusica";
        options.osxLibrarySubFolder = "Application Support";
        options.storageFormat = juce::PropertiesFile::storeAsXML;

        file = std::make_unique<juce::PropertiesFile> (options);
    }

    return *file;
}

} // namespace cursomusica::data
