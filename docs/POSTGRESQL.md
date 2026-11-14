# PostgreSQL — configuração e uso

Dono: **architect + data-engineer**. Como ligar o app ao PostgreSQL que espelha o
progresso (ADR 0006). Referência de dados: `docs/DATA.md` §v4. Segurança:
`docs/SECURITY.md`.

## Resumo

O app **não fixa a versão do servidor**. Ele fala com o PostgreSQL pelo cliente
`libpq`, então **17, 18 e adiante funcionam igual**. O que decide se há
espelhamento é:

1. o app ter sido **compilado com `libpq`** (`find_package(PostgreSQL)`); e
2. o ambiente informar as variáveis de conexão (`PGHOST`, …).

Sem qualquer um dos dois, o app roda **local** (offline-first) e nada quebra.

## 1. Ter o cliente (libpq) disponível

- **Windows (PostgreSQL 18 instalado):** o próprio instalador já traz o `libpq`.
  Fica em `C:\Program Files\PostgreSQL\18\` — cabeçalho em `include\libpq-fe.h`,
  import lib em `lib\libpq.lib`, runtime em `bin\libpq.dll`. Não há nada a
  instalar.
- **Linux:** `sudo apt-get install libpq-dev` (cliente) — o servidor
  (`postgresql`) é separado.

## 2. Compilar com o libpq

O build procura o `libpq` sozinho. Se ele não estiver num caminho padrão (típico
no Windows com várias versões), aponte a raiz do PostgreSQL 18:

```bat
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release ^
      -DPostgreSQL_ROOT="C:/Program Files/PostgreSQL/18"
```

Para **exigir** o libpq (falha o build se não achar, em vez de cair para local):

```bat
cmake -B build -G Ninja -DCURSOMUSICA_REQUIRE_POSTGRES=ON ^
      -DPostgreSQL_ROOT="C:/Program Files/PostgreSQL/18"
```

A configuração imprime `libpq found (<versão>): progress mirrored to PostgreSQL`
quando dá certo (no CI já compilou com `libpq 18.6`).

> No Windows, o `PostgreSQL::PostgreSQL` linka `libpq.dll`. Em **tempo de
> execução** ela precisa estar ao lado do `.exe` ou no `PATH` — veja §5.

## 3. Criar o banco, o papel e o schema

Script idempotente (Linux, WSL ou Git Bash), agnóstico de versão:

```bash
tools/setup_postgres.sh
```

Variáveis úteis: `PGUSER` (admin, default `postgres`), `PGPASSWORD`,
`CURSOMUSICA_ROLE`, `CURSOMUSICA_ROLE_PASSWORD`, `CURSOMUSICA_DB`,
`CURSOMUSICA_PG_SCHEMA`. Ao final ele imprime os `export` prontos.

Sem Bash? Faça o mesmo no `psql` (PowerShell/CMD), como administrador:

```sql
CREATE ROLE cursomusica LOGIN PASSWORD 'cursomusica';
CREATE DATABASE "curso-musica" OWNER cursomusica;
```

Depois, conectado ao banco `curso-musica`:

```sql
CREATE SCHEMA IF NOT EXISTS "curso-musica" AUTHORIZATION cursomusica;
GRANT ALL ON SCHEMA "curso-musica" TO cursomusica;
ALTER DEFAULT PRIVILEGES IN SCHEMA "curso-musica"
    GRANT ALL ON TABLES TO cursomusica;
ALTER DEFAULT PRIVILEGES IN SCHEMA "curso-musica"
    GRANT ALL ON SEQUENCES TO cursomusica;
```

As **tabelas** (`progress`, `module_result`) não precisam ser criadas: o app cria
sozinho, de forma idempotente, na primeira conexão (`ProgressDatabase::ensureSchema`).

## 4. Configurar o app (variáveis de ambiente)

| Variável | Papel | Default |
|---|---|---|
| `PGHOST` | host; **sem ele não há tentativa remota** | (vazio) |
| `PGPORT` | porta | `5432` |
| `PGUSER` | usuário da aplicação | (vazio) |
| `PGPASSWORD` | senha | (vazio) |
| `PGDATABASE` | banco | (vazio) |
| `CURSOMUSICA_PG_SCHEMA` | schema | `curso-musica` |
| `CURSOMUSICA_PG_STUDENT` | id do aluno | `local` |
| `CURSOMUSICA_PG_DISABLE` | força modo local | (desligado) |

Windows (PowerShell):

```powershell
$env:PGHOST="localhost"; $env:PGPORT="5432"; $env:PGUSER="cursomusica"
$env:PGPASSWORD="cursomusica"; $env:PGDATABASE="curso-musica"
$env:CURSOMUSICA_PG_SCHEMA="curso-musica"
```

Linux:

```bash
export PGHOST=localhost PGPORT=5432 PGUSER=cursomusica
export PGPASSWORD=cursomusica PGDATABASE=curso-musica
export CURSOMUSICA_PG_SCHEMA=curso-musica
```

## 5. Windows: a `libpq.dll` em tempo de execução

O app precisa achar a `libpq.dll`. Duas opções:

- **Simples:** adicione `C:\Program Files\PostgreSQL\18\bin` ao `PATH` antes de
  abrir o app.
- **Distribuível:** copie `libpq.dll` (e as dependências que ela puxa — no
  PostgreSQL 18, tipicamente `libssl-3-x64.dll`, `libcrypto-3-x64.dll`,
  `libintl-*.dll`, `libwinpthread-1.dll`) para a pasta do `.exe`.

> O instalador (`release.yml`) ainda é gerado **sem** libpq. Empacotar a
> `libpq.dll` no instalador é um passo seguinte do devops, para o app entregue já
> sair com o espelhamento ligado.

## 6. Confirmar que está funcionando

O `ProgressStore` expõe o estado por `getRemoteStatus()` / `isRemoteConnected()`
(usado em logs e diagnóstico):

- `connected to PostgreSQL` — gravando no banco;
- `configured, connecting to PostgreSQL` — configurado, ainda conectando;
- `local-only (...)` — sem libpq no build ou sem ambiente configurado.

> Indicador visual na tela de configuração é um passo seguinte do ux-ui-designer.

A prova direta de que está gravando é consultar o banco:

```sql
SELECT * FROM "curso-musica".progress;
SELECT * FROM "curso-musica".module_result ORDER BY id DESC LIMIT 10;
```

O teste de integração (`tests/TestMain.cpp`, `testProgressDatabase`) também
exercita o caminho real quando um banco está acessível.

## 7. Troubleshooting

| Sintoma | Causa provável | Ação |
|---|---|---|
| Build diz `libpq not found` | libpq fora do caminho padrão | passe `-DPostgreSQL_ROOT="C:/Program Files/PostgreSQL/18"` |
| App abre mas status fica `local-only (build without libpq)` | compilado sem libpq | reconfigure com `-DCURSOMUSICA_REQUIRE_POSTGRES=ON` |
| Status `configured, connecting…` | banco fora do ar ou credenciais erradas | confira `PGHOST`/porta/usuário/senha e o serviço |
| `FATAL: database "..." does not exist` | banco não criado | rode `tools/setup_postgres.sh` (§3) |
| App não abre / erro de DLL no Windows | `libpq.dll` não encontrada | §5 |
| `password authentication failed` | senha do papel diferente | `setup_postgres.sh` (re)define a senha |

## 8. Comportamento e garantias

- **Offline-first:** o banco é espelho, não dependência de execução. A falha de
  rede só pausa a sincronização; o progresso continua salvo localmente.
- **Monotônico:** `progress.highest_passed_module` nunca regride (UPSERT com
  `GREATEST`).
- **Append-only:** `module_result` só cresce (histórico/auditoria).
- **Fora das threads críticas:** a conexão e a escrita rodam numa thread
  dedicada; a thread de áudio nunca toca o banco (`AGENTS.md` §1).
- **Sem segredos no binário:** credenciais só no ambiente; a senha não é logada
  (`docs/SECURITY.md`).
