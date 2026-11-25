# CursoMusica — verifica o banco de progresso no PostgreSQL (REQ-014, ADR 0006).
#
# O instalador roda este script depois de copiar os arquivos. Ele confere que o
# banco "curso-musica" existe na porta 5432 e que o schema "curso" existe,
# criando ambos quando o usuário do PostgreSQL tem permissão. O banco é opcional
# (ADR 0006: o app funciona só local sem ele), então uma falha aqui NUNCA aborta
# a instalação — apenas informa o aluno e registra o motivo no log.
#
# A senha nunca é passada por argumento: vem do ambiente (PGPASSWORD), como no
# restante do app (docs/SECURITY.md).
#
# Códigos de saída: 0 ok · 2 psql não encontrado · 3 sem conexão
#                   4 falha ao criar o banco · 5 falha ao criar o schema

param(
    [string]$DbHost  = "localhost",
    [int]   $DbPort  = 5432,
    [string]$Database = "curso-musica",
    [string]$Schema   = "curso",
    [string]$DbUser   = "postgres"
)

$ErrorActionPreference = "Continue"

if ($env:PGHOST)                 { $DbHost   = $env:PGHOST }
if ($env:PGPORT)                 { $DbPort   = [int]$env:PGPORT }
if ($env:PGDATABASE)             { $Database = $env:PGDATABASE }
if ($env:CURSOMUSICA_PG_SCHEMA)  { $Schema   = $env:CURSOMUSICA_PG_SCHEMA }
if ($env:PGUSER)                 { $DbUser   = $env:PGUSER }

$logPath = Join-Path $env:TEMP "cursomusica-db-check.log"
function Write-Log([string]$message) {
    $line = "{0} {1}" -f (Get-Date -Format "s"), $message
    Add-Content -Path $logPath -Value $line -ErrorAction SilentlyContinue
}

# Locate psql: on PATH first, otherwise the newest PostgreSQL install.
$psql = $null
$onPath = Get-Command psql.exe -ErrorAction SilentlyContinue
if ($onPath) { $psql = $onPath.Source }

if (-not $psql) {
    $roots = @("C:\Program Files\PostgreSQL", "C:\Program Files (x86)\PostgreSQL")
    $dirs = @()
    foreach ($root in $roots) {
        if (Test-Path $root) {
            $dirs += Get-ChildItem $root -Directory -ErrorAction SilentlyContinue
        }
    }
    foreach ($dir in ($dirs | Sort-Object Name -Descending)) {
        $candidate = Join-Path $dir.FullName "bin\psql.exe"
        if (Test-Path $candidate) { $psql = $candidate; break }
    }
}

if (-not $psql) {
    Write-Log "psql.exe nao encontrado; verificacao ignorada"
    exit 2
}

Write-Log "usando psql: $psql"

$common = @("-h", $DbHost, "-p", "$DbPort", "-U", $DbUser, "-v", "ON_ERROR_STOP=1", "-tA")

# 1. The database must exist. CREATE DATABASE cannot run inside a transaction,
#    so it is issued on its own against the maintenance database.
$dbExists = & $psql @common -d postgres -c "SELECT 1 FROM pg_database WHERE datname='$Database'" 2>> $logPath
if ($LASTEXITCODE -ne 0) {
    Write-Log "sem conexao em ${DbHost}:${DbPort} como $DbUser"
    exit 3
}

if ($dbExists -ne "1") {
    Write-Log "banco $Database ausente; criando"
    & $psql @common -d postgres -c "CREATE DATABASE `"$Database`"" 2>> $logPath
    if ($LASTEXITCODE -ne 0) {
        Write-Log "falha ao criar o banco $Database"
        exit 4
    }
} else {
    Write-Log "banco $Database existe"
}

# 2. The schema must exist (idempotent, same DDL the app runs on startup).
& $psql @common -d $Database -c "CREATE SCHEMA IF NOT EXISTS `"$Schema`"" 2>> $logPath
if ($LASTEXITCODE -ne 0) {
    Write-Log "falha ao criar o schema $Schema"
    exit 5
}

Write-Log "schema $Schema ok"
exit 0
