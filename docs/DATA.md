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

---

# Medição e progressão (REQ-009, REQ-002, REQ-010)

Todo processo do sistema é mensurado (REQ-009). O aluno passa de módulo com
**≥ 90% de acerto**; a progressão é **linear** e **baseada em níveis**
(ADR 0003). Tudo é local, determinístico e auditável.

## Schema adicional (migração v2)

| Tabela | Colunas | Chaves | Versão |
|---|---|---|---|
| `module` | id, level, title, explanation_ref | PK id, UNIQUE level | v2 |
| `challenge` | id, module_id, kind, prompt_ref | PK id, FK module_id | v2 |
| `attempt` | id, challenge_id, started_at, ended_at, score, passed | PK id, FK challenge_id | v2 |
| `note_event` | id, attempt_id, at, hz, pitch_class, cents, verdict | PK id, FK attempt_id | v2 |
| `pattern_use` | id, attempt_id, pattern_ref, detected | PK id, FK attempt_id | v2 |
| `link_use` | id, attempt_id, link_ref, opened | PK id, FK attempt_id | v2 |
| `module_result` | module_id, attempts, hits, accuracy, gate_passed, passed_at | PK module_id | v2 |

`verdict` ∈ {repouso, tensão_pedida, tensão_não_pedida, erro, passagem}.

## Cálculo do gate (determinístico)

```
accuracy(module) = hits / attempts          # por módulo, sobre os desafios
gate_passed      = accuracy >= 0.90
```

Regras de integridade:

- `attempts` só conta tentativas válidas (mínimo de tentativas por desafio,
  definido com o musician) — evita "1 acerto em 1 = 100%".
- `passed` por tentativa é derivado da classificação das notas
  (`docs/MUSIC.md`), nunca de opinião.
- O gate é recalculado a cada tentativa; o histórico é imutável (append-only).
- **Modo de teste (REQ-013):** quando o override está ativo, `module_result`
  ignora o gate para fins de *acesso*, mas o cálculo real continua registrado.

## Pipeline de dados (local, fora da thread de áudio)

- **Extract:** o motor de avaliação publica eventos de nota em um FIFO
  lock-free; um worker drena. Nada é persistido no callback de áudio.
- **Transform:** funções puras — classificação repouso/tensão, agregação de
  acurácia, detecção de uso de pattern.
- **Load:** gravação idempotente no SQLite local.
- **Serve:** views `v_module_accuracy`, `v_progress`, `v_weak_notes` para a UI de
  progresso e para o relatório do aluno.

## Governança e privacidade

- As notas tocadas são dado do aluno; ficam **locais** e são apagáveis pelo
  usuário (LGPD). Nenhum dado pessoal é coletado nesta fase.
- Telemetria de "link estudado" é **local** e opt-in; sem consentimento, o
  critério de link (REQ-010) é registrado mas não enviado a lugar algum.
- Retenção: o usuário pode limpar o histórico de tentativas.

---

# Gate de andamento (metrônomo) — migração v3 (REQ-015)

Segundo eixo de gate (ADR 0004): além da acurácia, o aluno precisa **atingir o
BPM meta** para avançar. O BPM vem do metrônomo do próprio app.

## Schema adicional (migração v3)

| Tabela / coluna | Descrição | Versão |
|---|---|---|
| `challenge.target_bpm` | BPM meta do desafio (definido pelo musician) | v3 |
| `attempt.achieved_bpm` | maior BPM em que o aluno executou o desafio dentro da tolerância | v3 |
| `tempo_sample` (id, attempt_id, bpm, on_grid_ratio, at) | amostras de alinhamento à grade | v3 |
| `module_result.bpm_passed` | se o BPM meta do módulo foi atingido | v3 |

## Cálculo do gate de andamento

```
target_grid(module) = 0.75..0.82        # módulos 1–14: faixa de estudo
target_grid(module) = 0.82..0.90        # módulos 15–19: rampa linear
target_grid(module) = 0.90              # módulos 20+: performance

bpm_passed(module) = achieved_bpm >= target_bpm AND on_grid_ratio >= target_grid(module)
gate_passed(module) = accuracy >= 0.90 AND bpm_passed
```

Regras:

- O alvo de `on_grid_ratio` **cresce com o módulo** (rampa linear do 15 ao 20),
  refletindo a pedagogia: primeiro a precisão rítmica com respiração (75–82%),
  depois a precisão de performance (90%).
- `achieved_bpm` só conta se `on_grid_ratio` atingir o alvo do módulo.
- Síncope brasileira (bossa/samba) exige que a grade modele o deslocamento —
  senão o aluno é penalizado por tocar certo (ver `docs/MUSIC.md`, R-13).
- O BPM é medido contra o metrônomo interno, o que torna o resultado
  determinístico.
- Continua valendo: histórico append-only; override de teste (REQ-013) libera
  acesso mas não altera os dois cálculos.
