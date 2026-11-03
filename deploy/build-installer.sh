#!/usr/bin/env bash
# Builds the CursoMusica Windows installer (REQ-013, REQ-014).
#
# Run from the repository root after the Release build. Stages the app under
# deploy/windows/dist/app/ (NSIS resolves paths relative to the script and does
# not accept "..") and leaves the deliverable at
# instalador/Instalador CursoMusica.exe.
set -euo pipefail

root="$(cd "$(dirname "$0")/.." && pwd)"
cd "$root"

app="build/CursoMusica_artefacts/Release/Curso Musica Studio.exe"
if [[ ! -f "$app" ]]; then
    app="build/CursoMusica_artefacts/Release/Curso Musica Studio"
fi
if [[ ! -f "$app" ]]; then
    echo "Release binary not found; build first: cmake --build build --config Release" >&2
    exit 1
fi

stage="deploy/windows/dist/app"
rm -rf "$stage"
mkdir -p "$stage"
cp "$app" "$stage/Curso Musica Studio.exe"
nsis_defines=()
if [[ -d build/runtime ]]; then
    cp -r build/runtime "$stage/runtime"
    nsis_defines+=("/DRUNTIME")
fi

makensis "${nsis_defines[@]}" deploy/windows/installer.nsi

mkdir -p instalador
cp "deploy/windows/dist/Instalador CursoMusica.exe" "instalador/Instalador CursoMusica.exe"
echo "Installer written to instalador/Instalador CursoMusica.exe"
