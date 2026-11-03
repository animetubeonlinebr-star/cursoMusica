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

   #ifdef TEST_UNLOCK_ALL
    // Test build (REQ-013, ADR 0003 item 7): every module is reachable for
    // inspection. This never touches the real progress record.
    unlockAll = true;
   #endif
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
