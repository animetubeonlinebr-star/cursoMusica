# 0006 — Persistência do progresso em PostgreSQL

Status: accepted
Data: 2026-11-13
Autor: architect + data-engineer + developer (requisitos REQ-002, REQ-009,
REQ-013; pedido do cliente: "o progresso seja salvo, conecte o sistema ao banco
de dados PostgreSQL, porta 5432, schema curso-musica")

## Contexto

O progresso do aluno (maior módulo aprovado no gate de 90%, ADR 0003) é hoje
local: um `juce::PropertiesFile` (XML) em `Source/Course/ProgressStore.cpp`. Isso
resolve o desktop, mas o cliente pediu que o progresso seja **salvo em um banco
PostgreSQL** (porta 5432, schema `curso-musica`), para ter o registro fora da
máquina — base para relatório, suporte e o futuro modelo de IA (`docs/DATA.md`).

Restrições que a decisão precisa respeitar:

1. **Nada de I/O na thread de áudio** (`AGENTS.md` §1) e nada de bloquear a
   thread de UI: a gravação remota é assíncrona.
2. **O app é Windows e precisa continuar funcionando offline.** O instalador não
   pode depender de um Postgres no ar para abrir a tela de módulos.
3. **Nenhum segredo no binário nem no repositório.** Credenciais vêm do ambiente.
4. **O build não pode quebrar** quando o cliente PostgreSQL não está presente
   (mesmo padrão do ASIO SDK, já adotado no `CMakeLists.txt`).

## Decisão

1. **Cliente: `libpq` (C API oficial do PostgreSQL).** É a biblioteca cliente
   canônica, estável, sem dependências surpresa, e disponível para Windows
   (EDB/EnterpriseDB) e Linux (`libpq-dev`). Não entra `libpqxx` (wrapper C++,
   mais superfície) nem um driver puro-socket (reimplementar o protocolo é
   inaceitável).

2. **`libpq` é dependência opcional de compilação.** O CMake detecta o cabeçalho
   `libpq-fe.h` e a biblioteca; quando presentes, define
   `CURSOMUSICA_HAS_POSTGRES` e liga o alvo. Quando ausentes, o app compila e
   roda em **modo local** (comportamento atual), sem erro. O instalador Windows
   só passa a embarcar `libpq.dll` quando o SDK estiver disponível no build.

3. **Offline-first com espelho local.** O `ProgressStore` continua gravando no
   `PropertiesFile` (fonte rápida, sempre disponível). Em paralelo, um
   `ProgressDatabase` **espelha** cada resultado no Postgres, numa thread de
   fundo. No boot, o maior valor entre local e remoto vence (merge idempotente).

4. **Sem I/O na thread de áudio nem na de UI.** A thread de áudio nunca toca o
   banco. A UI só enfileira o resultado; a conexão e o `UPSERT` acontecem numa
   thread dedicada do `ProgressStore`.

5. **Schema `curso-musica`, configurável por ambiente.** O nome do schema é
   `curso-musica` por padrão (o pedido do cliente), mas vem de
   `CURSOMUSICA_PG_SCHEMA` para não engessar. Host/porta/usuário/senha/banco
   seguem as variáveis padrão do `libpq` (`PGHOST`, `PGPORT`, `PGUSER`,
   `PGPASSWORD`, `PGDATABASE`), com `PGPORT` default **5432**. O esquema é criado
   de forma idempotente (`CREATE SCHEMA IF NOT EXISTS`).

6. **Credenciais só no ambiente.** Senha nunca é embutida no binário, no
   repositório nem escrita em log. A conexão usa `PQconnectdbParams` (array de
   parâmetros), nunca uma string de conexão montada à mão que possa vazar em
   `lastError()`.

7. **Gravação idempotente e auditável.** Duas tabelas no schema:
   - `progress` — uma linha (a "carteira" do aluno): `highest_passed_module`.
     `UPSERT` monotônico (nunca regride).
   - `module_result` — histórico append-only por módulo (ADR 0003, `docs/DATA.md`
     v2): quem passou, quando. Serve de auditoria e de base para BI.

## Alternativas rejeitadas

- **SQLite local (o que `docs/DATA.md` previa).** Não atende ao pedido explícito
  (Postgres, 5432, schema `curso-musica`) e não dá o registro centralizado.
- **Gravar direto na thread de UI.** Um Postgres remoto lento travaria a tela de
  módulos; contraria §1 do `AGENTS.md`.
- **Postgres obrigatório (build falha sem ele).** Quebraria o build Windows e o
  modo offline; o desktop precisa abrir sem banco.
- **Guardar a senha no `PropertiesFile`.** Segredo em disco em texto claro e sem
  rotação; rejeitado pelo Security Engineer.
- **`libpqxx`.** Mais uma dependência transitiva para ganhar pouco sobre a C API
  que já usamos.

## Consequências

- O **data-engineer** mantém `Source/Data/ProgressDatabase.*` e o schema em
  `docs/DATA.md`; a migração v4 documenta as tabelas.
- O **architect** mantém a detecção de `libpq` no `CMakeLists.txt` (padrão do
  ASIO SDK: opcional, com aviso quando ausente).
- O **developer** mantém o `ProgressStore` (merge local/remoto, thread de fundo).
- O **devops** instala `libpq-dev` no CI Linux e, quando o cliente Windows
  estiver disponível, empacota `libpq.dll` no instalador.
- O **security-engineer** confere que nenhuma senha é logada nem versionada
  (`docs/SECURITY.md`).
- O **QA** cobre: idempotência do `UPSERT`, merge monotônico, fallback offline e
  o fato de que a ausência de banco não impede o app de abrir.
