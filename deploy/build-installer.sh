#!/usr/bin/env bash
# Builds the CursoMusica Windows installer (REQ-013, REQ-014).
#
# Run from the repository root after the Release build. Leaves the deliverable
# at instalador/Instalador CursoMusica.exe. On Linux this wraps the Linux binary
# (it only validates the .nsi); the real Windows .exe comes from release.yml.
set -euo pipefail

root="$(cd "$(dirname "$0")/.." && pwd)"
cd "$root"

app="build/CursoMusica_artefacts/Release/Curso Musica Studio.exe"
if [[ ! -f "$app" ]]; then
    echo "Release binary not found; build first: cmake --build build --config Release" >&2
    exit 1
fi

nsis_defines=("-DAPPEXE=$root/$app" "-DOUTFILE=$root/instalador/Instalador CursoMusica.exe")
if [[ -d build/runtime ]]; then
    nsis_defines+=("-DRUNTIME")
fi

mkdir -p "$root/instalador"
makensis "${nsis_defines[@]}" deploy/windows/installer.nsi

echo "Installer written to instalador/Instalador CursoMusica.exe"
