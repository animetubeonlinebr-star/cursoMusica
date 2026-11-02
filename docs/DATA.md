# DATA — CursoMusica

Dono: **data-engineer**. Inventário de dados, schema, pipeline e governança.
Restrição dura: **nada de I/O na thread de áudio** (`AGENTS.md` §1).

## Inventário de dados

| Entidade / evento | Classificação | Retenção | Base legal |
|---|---|---|---|
| Sessão de estudo (início/fim, duração) | interna | local, até o usuário apagar | legítimo interesse / consentimento |
| Leituras do afinador (frequência, cents) | interna (pode revelar áudio) | efêmera / agregada | consentimento |
| Configuração de áudio (dispositivo, buffer, plugins) | interna | local, persistente | execução do serviço |
| Progresso do curso (lições concluídas) | interna | local, persistente | consentimento |
| Dado pessoal (nome, e-mail) | **pessoal** | não coletar nesta fase | — |

Regra: nada de dado pessoal é coletado nesta fase. Se um dia for, precisa de
opt-in explícito e anonimização antes de sair da máquina.

## Schema (proposto — migração versionada)

Armazenamento local (desktop): um único arquivo SQLite em `Source/Data/`.

| Tabela | Colunas | Chaves | Versão |
|---|---|---|---|
| `session` | id, started_at, ended_at, device_name | PK id | v1 |
| `tuner_sample` | id, session_id, hz, cents, at | PK id, FK session_id | v1 |
| `settings` | key, value | PK key | v1 |

Migração v1 inicial; toda mudança vem com rollback documentado.

## Pipeline (ETL/ELT)

- **Extract:** eventos publicados por um FIFO lock-free drenado por um worker
  (nunca no callback de áudio).
- **Transform:** funções puras e testáveis (ex.: agregação de tempo de prática,
  normalização de cents).
- **Load:** gravação idempotente no SQLite local; re-executar não duplica.
- **Serve:** views agregadas (tempo por dia, progresso por lição) para BI local e
  para o futuro modelo de IA (ex.: detectar erro recorrente).

## Governança

- Campos pessoais: nenhum nesta fase. Se introduzidos → cifrar ou anonimizar,
  com base legal registrada aqui antes de qualquer coleta.
- Telemetria (se houver) é **opt-in** e sai agregada/anonimizada.
- Retenção: o usuário pode apagar os dados locais; o app oferece essa ação.

## Pendências

- Pipeline ainda não implementado (depende de M2/M5 no `docs/PLAN.md`).
- Decisão de telemetria (D3) pendente com o PM.
