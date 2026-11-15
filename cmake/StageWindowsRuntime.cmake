# Stages the runtime DLLs a Windows build needs next to the .exe (REQ-014).
#
# libpq is linked through its import library, so the produced .exe declares a
# dependency on libpq.dll. A machine without PostgreSQL installed then fails to
# start with "LIBPQ.dll was not found". The installer bundles whatever lands in
# build/runtime (see deploy/windows/installer.nsi and release.yml), so this
# script copies libpq.dll and the DLLs it transitively imports.
#
# Runs in script mode, from the generated build/stage-windows-runtime.cmake
# (see CMakeLists.txt): it sets EXE, OUT_DIR and PG_DIRS, then includes this file.

if(NOT DEFINED EXE OR NOT EXISTS "${EXE}")
    message(FATAL_ERROR "StageWindowsRuntime: EXE not found: ${EXE}")
endif()
if(NOT DEFINED OUT_DIR OR OUT_DIR STREQUAL "")
    message(FATAL_ERROR "StageWindowsRuntime: OUT_DIR not set")
endif()

# Candidate directories, in order: the PostgreSQL install tree, then PATH (a
# machine-wide install puts libpq.dll in its bin/ and on PATH). PG_DIRS is a
# CMake list (semicolon-separated); a "|" separator is also accepted.
set(_dirs "")
if(DEFINED PG_DIRS AND NOT PG_DIRS STREQUAL "")
    set(_dirs "${PG_DIRS}")
    string(REPLACE "|" ";" _dirs "${_dirs}")
endif()
if(DEFINED ENV{PATH})
    file(TO_CMAKE_PATH "$ENV{PATH}" _path_dirs)
    list(APPEND _dirs ${_path_dirs})
endif()

# The import table names every DLL the binary needs; the loader resolves them
# from the search path. System libraries (System32, SysWOW64, WinSxS) are part
# of Windows and must not be bundled, so they are excluded after resolution.
file(GET_RUNTIME_DEPENDENCIES
    EXECUTABLES "${EXE}"
    RESOLVED_DEPENDENCIES_VAR _resolved
    UNRESOLVED_DEPENDENCIES_VAR _unresolved
    DIRECTORIES ${_dirs}
    PRE_EXCLUDE_REGEXES "api-ms-" "ext-ms-"
    POST_EXCLUDE_REGEXES ".*[Ss]ystem32.*" ".*[Ss]ysWOW64.*" ".*[Ww]in[Ss]x[Ss].*")

file(MAKE_DIRECTORY "${OUT_DIR}")

set(_staged "")
set(_have_libpq FALSE)
foreach(_dep IN LISTS _resolved)
    get_filename_component(_name "${_dep}" NAME)
    string(TOLOWER "${_name}" _lower)
    if(_lower STREQUAL "libpq.dll")
        set(_have_libpq TRUE)
    endif()
    file(COPY "${_dep}" DESTINATION "${OUT_DIR}")
    list(APPEND _staged "${_name}")
endforeach()

if(_unresolved)
    message(STATUS "StageWindowsRuntime: unresolved dependencies: ${_unresolved}")
endif()

if(NOT _have_libpq)
    message(FATAL_ERROR
        "StageWindowsRuntime: libpq.dll was not resolved for ${EXE}, so the "
        "installed app would fail with 'LIBPQ.dll was not found'. Point the "
        "build at the PostgreSQL install, e.g. "
        "-DPostgreSQL_ROOT=\"C:/Program Files/PostgreSQL/<version>\".")
endif()

message(STATUS "StageWindowsRuntime: staged ${_staged} in ${OUT_DIR}")
