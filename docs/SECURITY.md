# SECURITY — CursoMusica

Dono: **security-engineer**. Revisão de segurança, licenças e lícito.

## Escopo desta fase

Aplicativo desktop (Windows, C++17/JUCE). Nenhum dado pessoal é coletado
(`docs/DATA.md`). A partir da ADR 0006 o app pode **espelhar o progresso** em um
PostgreSQL; este documento cobre essa superfície.

## Credenciais do banco de dados

- As credenciais vêm **apenas do ambiente** (`PGHOST`, `PGPORT`, `PGUSER`,
  `PGPASSWORD`, `PGDATABASE`). Nunca são embutidas no binário nem versionadas.
- A senha **nunca é escrita em log**. A conexão usa `PQconnectdbParams` com
  array de parâmetros, e não uma string de conexão montada à mão — assim a senha
  não pode vazar por interpolação nem aparecer em `lastError()`.
- O nome do schema (`CURSOMUSICA_PG_SCHEMA`, default `curso-musica`) é escapado
  como identificador com `PQescapeIdentifier` antes de entrar em qualquer DDL;
  os valores das consultas usam parâmetros (`$1`, `$2`, …), nunca concatenação.
- Nenhum segredo é gravado no `PropertiesFile` local.
- Repositório e instalador não contêm credenciais. O `.gitignore` cobre arquivos
  de ambiente locais.

## Superfície de rede

- Conexão de saída (cliente libpq) para o host configurado; **desligada** quando
  `PGHOST` está vazio ou `CURSOMUSICA_PG_DISABLE=1`.
- `connect_timeout` curto (5 s) e gravação em **thread dedicada**: um banco lento
  ou malicioso não trava a UI nem a thread de áudio.
- O app é **local-first**: sem banco, o progresso continua sendo salvo
  localmente. A falha de rede não é um modo degradado de segurança, apenas de
  sincronização.

## Dados

- O que trafega é progresso do curso (`student_id` local, módulo, passou/não).
  **Nenhum dado pessoal** nesta fase.
- Se dado pessoal for introduzido no futuro, exige opt-in explícito e
  anonimização **antes** de sair da máquina (`docs/DATA.md`).

## Dependências e licenças

- **libpq** (cliente PostgreSQL): licença PostgreSQL (permissiva, tipo BSD).
  Compatível com o uso comercial do app. É dependência **opcional** de build;
  quando embarcada no instalador Windows, deve acompanhar a licença.
- JUCE 8.0.4: ver termos de licença vigentes do projeto.

## Revisão

- Mudança que carrega código externo ou dado do usuário passa por este agente
  antes do merge (`AGENTS.md` §5, regra 7). A ADR 0006 foi revisada quanto a
  segredos, injeção de SQL e I/O fora das threads críticas.
