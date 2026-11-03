cmake_minimum_required(VERSION 3.22)

project(CursoMusica VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/External/JUCE/CMakeLists.txt")
    message(FATAL_ERROR
        "JUCE not found. Run:\n"
        "  git clone --depth 1 --branch 8.0.4 https://github.com/juce-framework/JUCE.git External/JUCE")
endif()

add_subdirectory(External/JUCE)

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
    Source/Course/ModuleCatalog.cpp
    Source/UI/Design/LookAndFeel.cpp
    Source/UI/Design/Panel.cpp
    Source/UI/LevelMeter.cpp
    Source/UI/TunerDisplay.cpp
    Source/UI/TunerComponent.cpp
    Source/UI/ModuleComponent.cpp
    Source/UI/DevicePanel.cpp
    Source/UI/TransportPanel.cpp
    Source/UI/SettingsComponent.cpp)

target_include_directories(CursoMusica PRIVATE Source)

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
        juce::juce_audio_utils
        juce::juce_audio_processors
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags)
