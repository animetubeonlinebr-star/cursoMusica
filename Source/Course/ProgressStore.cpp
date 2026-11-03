#include "Course/ProgressStore.h"

namespace cursomusica::course
{

namespace
{
    constexpr const char* highestPassedKey = "course/highestPassedModule";
}

ProgressStore::ProgressStore()
{
    juce::PropertiesFile::Options options;
    options.applicationName = "CursoMusica";
    options.filenameSuffix = ".settings";
    options.folderName = "CursoMusica";
    options.osxLibrarySubFolder = "Application Support";
    options.storageFormat = juce::PropertiesFile::storeAsXML;

    properties = std::make_unique<juce::PropertiesFile> (options);
    load();
}

bool ProgressStore::isModuleUnlocked (int moduleNumber) const noexcept
{
    return unlockAll || progress::isUnlocked (moduleNumber, highestPassedModule);
}

void ProgressStore::recordGateResult (int moduleNumber, bool passed)
{
    if (! passed || moduleNumber <= highestPassedModule)
        return;

    highestPassedModule = moduleNumber;
    save();
}

void ProgressStore::load()
{
    highestPassedModule = (int) properties->getIntValue (highestPassedKey, 0);
}

void ProgressStore::save() const
{
    properties->setValue (highestPassedKey, highestPassedModule);
    properties->saveIfNeeded();
}

void ProgressStore::reset()
{
    highestPassedModule = 0;
    save();
}

} // namespace cursomusica::course
