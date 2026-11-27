#!/usr/bin/env bash
# Runs the CursoMusica usage test end-to-end on Linux.
#
# It prepares everything the test needs — a PostgreSQL on 5432, a JACK server
# (the audio backend JUCE can open without real hardware), and a real .vst3 built
# from tests/usage/TestPlugin.cpp — then runs the usage binary, which drives the
# real engine, plugin host, database and course objects.
#
# The Windows counterpart of this flow is .github/workflows/usage-test.yml; this
# script is for a local Linux run (the CI "linux-build" job can also run it).
#
# Usage: tools/usage-test.sh [build-dir]
set -uo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="${1:-$REPO_ROOT/build-usage}"

PG_CONTAINER="cursomusica-usage-pg"
PG_PORT=5432

# docker without sudo in CI, with sudo on a local box that only exposes it there.
if docker info >/dev/null 2>&1; then
    DOCKER="docker"
elif sudo -n docker info >/dev/null 2>&1; then
    DOCKER="sudo docker"
else
    DOCKER=""
fi

log() { printf '\n\033[1m== %s ==\033[0m\n' "$*"; }

cleanup() {
    if [ -n "${JACK_PID:-}" ]; then
        kill "$JACK_PID" 2>/dev/null || true
    fi
}
trap cleanup EXIT

log "1/4 PostgreSQL em :$PG_PORT"
if [ -z "$DOCKER" ]; then
    echo "docker indisponivel: pulando o passo de banco (o teste reporta SKIP)" >&2
else
    $DOCKER rm -f "$PG_CONTAINER" >/dev/null 2>&1 || true
    $DOCKER run -d --name "$PG_CONTAINER" \
        -e POSTGRES_USER=cursomusica \
        -e POSTGRES_PASSWORD=cursomusica \
        -e POSTGRES_DB=curso-musica \
        -p "${PG_PORT}:5432" postgres:17 >/dev/null
    for _ in $(seq 1 30); do
        if $DOCKER exec "$PG_CONTAINER" pg_isready -U cursomusica -d curso-musica >/dev/null 2>&1; then
            echo "PostgreSQL pronto"
            break
        fi
        sleep 1
    done
fi

log "2/4 Build (app + plugin de teste + teste de uso)"
cmake -B "$BUILD_DIR" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCURSOMUSICA_USAGE_TEST=ON \
    || { echo "FALHOU: o configure do build de uso falhou"; exit 1; }
# A failed build must stop the run: without this the script fell through and
# reported OK on the previous binary.
cmake --build "$BUILD_DIR" || { echo "FALHOU: o build de uso falhou"; exit 1; }

log "3/4 JACK (dummy) e pasta de plugins"
pkill -9 -f "jackd -d dummy" 2>/dev/null || true
sleep 1
export JACK_NO_AUDIO_RESERVATION=1
jackd -d dummy -r 48000 -p 512 >/tmp/cursomusica-jackd.log 2>&1 &
JACK_PID=$!
sleep 5

PLUGIN_SRC="$BUILD_DIR/CursoMusicaTestPlugin_artefacts/Release/VST3/CursoMusica Test Plugin.vst3"
PLUGIN_DIR="$(mktemp -d)"
cp -r "$PLUGIN_SRC" "$PLUGIN_DIR/"

log "4/4 Teste de uso"
export PGHOST=localhost PGPORT="$PG_PORT" PGUSER=cursomusica PGPASSWORD=cursomusica
export PGDATABASE=curso-musica CURSOMUSICA_PG_SCHEMA=curso
export XDG_CONFIG_HOME="$(mktemp -d)"

"$BUILD_DIR/CursoMusicaUsageTest_artefacts/Release/CursoMusicaUsageTest" \
    --vst3-folder="$PLUGIN_DIR"
