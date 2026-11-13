cmake_minimum_required(VERSION 3.22)

project(CursoMusica VERSION 0.1.0 LANGUAGES C CXX)

# Release builds on the test branch open every module without touching the real
# progress record (ADR 0003 item 7, REQ-013). Default off: normal builds keep
# the linear gate.
option(TEST_UNLOCK_ALL "Open every module in this build (test override)" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/External/JUCE/CMakeLists.txt")
    message(FATAL_ERROR
        "JUCE not found. Run:\n"
        "  git clone --depth 1 --branch 8.0.4 https://github.com/juce-framework/JUCE.git External/JUCE")
endif()

add_subdirectory(External/JUCE)

# ---------------------------------------------------------------------------
# Diagrams embedded in the binary (REQ-003/REQ-006).
#
# The teaching images (fretboard, CAGED shapes, rhythm figures...) are drawn by
# tools/make_diagrams.py into Source/Course/Content/Diagrams/*.jpg and embedded
# here, so the app ships self-contained. The stem of each file becomes its
# BinaryData resource name; ContentItem of kind image refers to it by that stem.
# ---------------------------------------------------------------------------
file(GLOB _diagram_files CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/Source/Course/Content/Diagrams/*.jpg")

if(NOT _diagram_files)
    message(FATAL_ERROR
        "No course diagrams found. Generate them with:\n"
        "  python3 tools/make_diagrams.py")
endif()

juce_add_binary_data(CursoMusicaDiagrams
    NAMESPACE CursoMusicaDiagrams
    HEADER_NAME BinaryData.h
    SOURCES ${_diagram_files})

juce_add_gui_app(CursoMusica
    PRODUCT_NAME "Curso Musica Studio"
    COMPANY_NAME "CursoMusica"
    VERSION "${PROJECT_VERSION}"
    NEEDS_CURL FALSE
    NEEDS_WEB_BROWSER FALSE
    MICROPHONE_PERMISSION_ENABLED TRUE
    MICROPHONE_PERMISSION_TEXT "Curso Musica Studio needs audio input to analyse your playing.")

target_sources(CursoMusica PRIVATE
    Source/Main.cpp
    Source/MainComponent.cpp
    Source/Audio/AudioEngine.cpp
    Source/Audio/PitchDetector.cpp
    Source/Audio/PluginHost.cpp
    Source/Audio/PluginChain.cpp
    Source/Audio/TuningSettings.cpp
    Source/Audio/Metronome.cpp
    Source/Audio/AudioPortClassifier.cpp
    Source/Course/NoteMath.cpp
    Source/Course/ExerciseEvaluator.cpp
    Source/Course/TempoGrid.cpp
    Source/Course/PracticeSession.cpp
    Source/Course/QuizSession.cpp
    Source/Course/ProgressStore.cpp
    Source/Course/ModuleCatalog.cpp
    Source/Data/ProgressDatabase.cpp
    Source/Course/Content/Topics.cpp
    Source/Course/Content/Diagrams.cpp
    Source/Course/Content/TopicA.cpp
    Source/Course/Content/TopicB.cpp
    Source/Course/Content/TopicC.cpp
    Source/Course/Content/TopicD.cpp
    Source/Course/Content/TopicE.cpp
    Source/Course/Content/TopicF.cpp
    Source/Course/Content/TopicG.cpp
    Source/Course/Content/TopicH.cpp
    Source/Course/Content/TopicI.cpp
    Source/UI/Design/LookAndFeel.cpp
    Source/UI/Design/Panel.cpp
    Source/UI/LevelMeter.cpp
    Source/UI/TunerDisplay.cpp
    Source/UI/TunerComponent.cpp
    Source/UI/ModuleComponent.cpp
    Source/UI/PracticePanel.cpp
    Source/UI/AudioPortsPanel.cpp
    Source/UI/DevicePanel.cpp
    Source/UI/TransportPanel.cpp
    Source/UI/SettingsComponent.cpp)

target_include_directories(CursoMusica PRIVATE Source)

if(TEST_UNLOCK_ALL)
    target_compile_definitions(CursoMusica PRIVATE TEST_UNLOCK_ALL=1)
endif()

# ---------------------------------------------------------------------------
# ASIO (Windows only)
#
# JUCE does not ship the Steinberg ASIO SDK and has no CMake variable for it:
# juce_audio_devices.cpp does a plain `#include <iasiodrv.h>`. The only thing
# the build needs is that header reachable from the include path, so we point
# at the SDK's `common` directory ourselves.
#
# Because the SDK is licensed separately, the build must not fail when it is
# absent: we enable ASIO only when the header is actually found.
# ---------------------------------------------------------------------------
if(WIN32)
    set(ASIO_SDK_DIR "" CACHE PATH "Path to the Steinberg ASIO SDK root (containing common/iasiodrv.h)")

    set(_asio_candidates
        "${ASIO_SDK_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/External/asio"
        "$ENV{ASIO_SDK_DIR}")

    foreach(_candidate IN LISTS _asio_candidates)
        if(_candidate AND EXISTS "${_candidate}/common/iasiodrv.h")
            set(_asio_include "${_candidate}/common")
            break()
        endif()
    endforeach()

    if(_asio_include)
        message(STATUS "ASIO SDK found: ${_asio_include}")
        target_include_directories(CursoMusica PRIVATE "${_asio_include}")
        target_compile_definitions(CursoMusica PRIVATE JUCE_ASIO=1)
    else()
        message(WARNING
            "ASIO SDK not found - building without ASIO (higher latency).\n"
            "Download it from https://www.steinberg.net/developers/ , unpack it, then\n"
            "reconfigure with:  -DASIO_SDK_DIR=<path-to-asio-sdk>")
    endif()
endif()

# ---------------------------------------------------------------------------
# PostgreSQL progress storage (optional, ADR 0006).
#
# The student's progress is mirrored to a PostgreSQL database when libpq is
# available at build time; otherwise the app compiles and runs purely local.
# Same discipline as the ASIO SDK above: absence is a warning, never an error,
# unless the builder explicitly asks for a guaranteed integration.
#
# Point the build at a specific server version (e.g. PostgreSQL 18 on Windows)
# with:  -DPostgreSQL_ROOT="C:/Program Files/PostgreSQL/18"
# Force a hard requirement with:  -DCURSOMUSICA_REQUIRE_POSTGRES=ON
#
# The connection details come from the environment at runtime, never the binary.
# ---------------------------------------------------------------------------
option(CURSOMUSICA_REQUIRE_POSTGRES
       "Fail the build when libpq is not found (guarantees progress mirroring)" OFF)

find_package(PostgreSQL QUIET)

if(PostgreSQL_FOUND)
    message(STATUS "libpq found (${PostgreSQL_VERSION_STRING}): progress mirrored to PostgreSQL")
    target_include_directories(CursoMusica PRIVATE ${PostgreSQL_INCLUDE_DIRS})
    target_link_libraries(CursoMusica PRIVATE PostgreSQL::PostgreSQL)
    target_compile_definitions(CursoMusica PRIVATE CURSOMUSICA_HAS_POSTGRES=1)
elseif(CURSOMUSICA_REQUIRE_POSTGRES)
    message(FATAL_ERROR
        "libpq not found, but CURSOMUSICA_REQUIRE_POSTGRES=ON.\n"
        "Install the PostgreSQL client library, then reconfigure. On Windows with\n"
        "PostgreSQL 18 installed, pass:\n"
        "  -DPostgreSQL_ROOT=\"C:/Program Files/PostgreSQL/18\"")
else()
    message(STATUS "libpq not found - building without PostgreSQL (progress stays local)")
endif()

target_compile_definitions(CursoMusica PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_MODAL_LOOPS_PERMITTED=1
    JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:CursoMusica,JUCE_PRODUCT_NAME>"
    JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:CursoMusica,JUCE_VERSION>"
    # Windows backends. ASIO is enabled above, only when the SDK is present.
    $<$<PLATFORM_ID:Windows>:JUCE_WASAPI=1>
    $<$<PLATFORM_ID:Windows>:JUCE_WASAPI_EXCLUSIVE=1>
    $<$<PLATFORM_ID:Windows>:JUCE_DIRECTSOUND=1>
    $<$<PLATFORM_ID:Linux>:JUCE_ALSA=1>
    # Plugin hosting: VST3 in, and on Windows the ASIO driver selection UI.
    JUCE_PLUGINHOST_VST3=1
    JUCE_PLUGINHOST_VST=0
    JUCE_PLUGINHOST_AU=0)

target_link_libraries(CursoMusica
    PRIVATE
        CursoMusicaDiagrams
        juce::juce_audio_utils
        juce::juce_audio_processors
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags)

# ---------------------------------------------------------------------------
# Unit tests for the pure course logic (no audio device, no UI).
#
# The tests link the pure sources directly instead of the GUI app, so they run
# headless on the build machine and in CI. Owned by the QA agent.
# ---------------------------------------------------------------------------
enable_testing()

juce_add_console_app(CursoMusicaTests
    PRODUCT_NAME "CursoMusicaTests")

target_sources(CursoMusicaTests PRIVATE
    tests/TestMain.cpp
    Source/Course/NoteMath.cpp
    Source/Course/ExerciseEvaluator.cpp
    Source/Course/TempoGrid.cpp
    Source/Course/PracticeSession.cpp
    Source/Course/QuizSession.cpp
    Source/Course/ModuleCatalog.cpp
    Source/Course/ProgressStore.cpp
    Source/Data/ProgressDatabase.cpp
    Source/Course/Content/Topics.cpp
    Source/Course/Content/Diagrams.cpp
    Source/Course/Content/TopicA.cpp
    Source/Course/Content/TopicB.cpp
    Source/Course/Content/TopicC.cpp
    Source/Course/Content/TopicD.cpp
    Source/Course/Content/TopicE.cpp
    Source/Course/Content/TopicF.cpp
    Source/Course/Content/TopicG.cpp
    Source/Course/Content/TopicH.cpp
    Source/Course/Content/TopicI.cpp
    Source/Audio/AudioPortClassifier.cpp)

target_include_directories(CursoMusicaTests PRIVATE Source)

target_compile_definitions(CursoMusicaTests PRIVATE
    JUCE_USE_CURL=0
    JUCE_WEB_BROWSER=0)

# The tests exercise the real libpq path when it is available (integration test
# against a local PostgreSQL), and degrade to the no-op path otherwise.
if(PostgreSQL_FOUND)
    target_include_directories(CursoMusicaTests PRIVATE ${PostgreSQL_INCLUDE_DIRS})
    target_link_libraries(CursoMusicaTests PRIVATE PostgreSQL::PostgreSQL)
    target_compile_definitions(CursoMusicaTests PRIVATE CURSOMUSICA_HAS_POSTGRES=1)
endif()

target_link_libraries(CursoMusicaTests
    PRIVATE
        CursoMusicaDiagrams
        juce::juce_core
        juce::juce_data_structures
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags)

add_test(NAME course_logic COMMAND CursoMusicaTests)
