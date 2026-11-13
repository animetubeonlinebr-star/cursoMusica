#!/usr/bin/env bash
#
# Cria (ou atualiza) o banco de progresso do CursoMusica no PostgreSQL.
# Idempotente e agnostico de versao: funciona no PostgreSQL 17, 18 e adiante,
# no Linux e no Windows (Git Bash / WSL), desde que o `psql` esteja no PATH.
#
# Uso:
#   tools/setup_postgres.sh
#
# Configuracao (variaveis de ambiente, com defaults):
#   PGHOST                        host do servidor          (localhost)
#   PGPORT                        porta                     (5432)
#   PGUSER                        usuario administrador     (postgres)
#   PGPASSWORD                    senha do administrador    (vazio; peer auth)
#   CURSOMUSICA_ROLE              papel da aplicacao        (cursomusica)
#   CURSOMUSICA_ROLE_PASSWORD     senha da aplicacao        (cursomusica)
#   CURSOMUSICA_DB                banco                     (curso-musica)
#   CURSOMUSICA_PG_SCHEMA         schema                    (curso-musica)
#
# Ao final, imprime os `export` que o app le (ver docs/POSTGRESQL.md).

set -u

PGHOST="${PGHOST:-localhost}"
PGPORT="${PGPORT:-5432}"
PGUSER="${PGUSER:-postgres}"
ROLE="${CURSOMUSICA_ROLE:-cursomusica}"
ROLE_PASSWORD="${CURSOMUSICA_ROLE_PASSWORD:-cursomusica}"
DB="${CURSOMUSICA_DB:-curso-musica}"
SCHEMA="${CURSOMUSICA_PG_SCHEMA:-curso-musica}"

say() { printf '%s\n' "$*"; }
die() { printf 'erro: %s\n' "$*" >&2; exit 1; }

command -v psql >/dev/null 2>&1 \
    || die "psql nao encontrado no PATH. Instale o cliente do PostgreSQL (o servidor 18 ja traz o psql)."

# O psql/createdb consomem estas variaveis (a senha do admin, se houver).
export PGHOST PGPORT PGUSER
[ -n "${PGPASSWORD:-}" ] && export PGPASSWORD

# Toda interpolacao de valor passa por stdin (heredoc): o psql NAO substitui
# :'var' / :"var" em comandos -c. Assim :'var' vira literal escapado e :"var"
# vira identificador escapado, sem concatenacao de string no shell.

# Espera o servidor aceitar conexoes (util logo apos subir o servico).
say "Conectando em ${PGUSER}@${PGHOST}:${PGPORT} ..."
ready=0
for _ in $(seq 1 30); do
    if psql -tA -d postgres -c 'SELECT 1' >/dev/null 2>&1; then
        ready=1
        break
    fi
    sleep 1
done
[ "$ready" = 1 ] || die "nao consegui conectar em ${PGHOST}:${PGPORT} como ${PGUSER}. O servidor esta no ar?"

# Papel da aplicacao: cria se faltar, (re)define a senha e habilita LOGIN.
role_exists="$(psql -tA -d postgres -v role="$ROLE" <<'SQL'
SELECT 1 FROM pg_roles WHERE rolname = :'role'
SQL
)"

if [ "$role_exists" = "1" ]; then
    psql -v ON_ERROR_STOP=1 -q -d postgres \
         -v role="$ROLE" -v pw="$ROLE_PASSWORD" <<'SQL'
SELECT format('ALTER ROLE %I WITH LOGIN PASSWORD %L', :'role', :'pw') \gexec
SQL
    say "papel '${ROLE}' atualizado (LOGIN e senha)."
else
    psql -v ON_ERROR_STOP=1 -q -d postgres \
         -v role="$ROLE" -v pw="$ROLE_PASSWORD" <<'SQL'
SELECT format('CREATE ROLE %I LOGIN PASSWORD %L', :'role', :'pw') \gexec
SQL
    say "papel '${ROLE}' criado."
fi

# Banco: CREATE DATABASE nao roda em bloco DO/transacao, entao o \gexec cria so
# quando falta. Idempotente.
psql -v ON_ERROR_STOP=1 -q -d postgres -v db="$DB" -v role="$ROLE" <<'SQL'
SELECT format('CREATE DATABASE %I OWNER %I', :'db', :'role')
 WHERE NOT EXISTS (SELECT FROM pg_database WHERE datname = :'db') \gexec
SQL
say "banco '${DB}' pronto."

# Schema e permissoes. O proprio app tambem cria o schema (ensureSchema), mas
# deixamos pronto aqui para o papel ja ter os direitos de escrita.
psql -v ON_ERROR_STOP=1 -q -d "$DB" -v schema="$SCHEMA" -v role="$ROLE" <<'SQL'
CREATE SCHEMA IF NOT EXISTS :"schema" AUTHORIZATION :"role";
GRANT ALL ON SCHEMA :"schema" TO :"role";
ALTER DEFAULT PRIVILEGES IN SCHEMA :"schema" GRANT ALL ON TABLES TO :"role";
ALTER DEFAULT PRIVILEGES IN SCHEMA :"schema" GRANT ALL ON SEQUENCES TO :"role";
SQL
say "schema '${SCHEMA}' pronto (as tabelas sao criadas pelo proprio app)."

cat <<EOF

Pronto. Configure o ambiente do app com:

  export PGHOST=${PGHOST}
  export PGPORT=${PGPORT}
  export PGUSER=${ROLE}
  export PGPASSWORD=${ROLE_PASSWORD}
  export PGDATABASE=${DB}
  export CURSOMUSICA_PG_SCHEMA=${SCHEMA}

No Windows (PowerShell):

  \$env:PGHOST="${PGHOST}"; \$env:PGPORT="${PGPORT}"; \$env:PGUSER="${ROLE}"
  \$env:PGPASSWORD="${ROLE_PASSWORD}"; \$env:PGDATABASE="${DB}"
  \$env:CURSOMUSICA_PG_SCHEMA="${SCHEMA}"

Para confirmar: consulte o banco (docs/POSTGRESQL.md, secao 6).
Para forcar modo local: CURSOMUSICA_PG_DISABLE=1
EOF
