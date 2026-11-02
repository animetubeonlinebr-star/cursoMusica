# PLAN — CursoMusica

Dono: **project-manager**. Milestones, datas, donos, dependências e premissas de
capacidade. Direção do produto fica em `docs/ROADMAP.md` (PM).

## Premissas de capacidade

- Time composto por agentes (PM, PO, architect, data-engineer, project-manager,
  developer, qa, devops, designer).
- Ambiente Linux sem dispositivo de áudio → só valida compilação.
- Sem máquina Windows dedicada no momento → teste de latência fica pendente.
- "Capacidade" = orçamento de passos/agente e tempo de parede, medido de forma
  honesta.

## Milestones

| ID | Milestone | Alvo | Dono | Depende de |
|---|---|---|---|---|
| M0 | Framework multi-agente + memória compartilhada | Q1 | orquestrador | — |
| M1 | Mesclar `feature/juce-audio-app` em `main` | Q1 | architect | M0 |
| M2 | CI verde (build + testes) em PRs | Q1 | devops, qa | M1 |
| M3 | Afinador e medidor reais (CM-001) | Q2 | developer, designer | M1 |
| M4 | Latência medida no Windows com ASIO | Q2 | developer, qa | hardware Windows |
| M5 | Playback com velocidade e loop (CM-003) | Q3 | developer | M3, ADR de time-stretch |
| M6 | Instalador + telemetria opt-in | Q4 | devops, data-engineer | M5 |

## Marcos de decisão

- **D1:** mesclar a branch do app ou continuar nela? (architect + PM)
- **D2:** time-stretch por algoritmo próprio ou biblioteca? (architect, ADR)
- **D3:** telemetria ligada por padrão ou opt-in? (PM + data-engineer, LGPD)

## Como acompanhar

- Progresso e métricas: `docs/STATUS.md`.
- Riscos e impedimentos: `docs/RISKS.md`.
