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
| M2b | Instalador Windows com seleção de diretório (REQ-014) | Q1 | devops | M2 |
| M3 | Afinador e medidor reais (CM-001) | Q2 | developer, designer | M1 |
| M4 | Estrutura de curso: módulos, explicação, desafios (CM-006) | Q2 | developer, designer, musician | M3 |
| M5 | Motor de medição e gate de 90% (CM-008) | Q2 | data-engineer, developer | M4 |
| M6 | Latência medida no Windows com ASIO | Q2 | developer, qa | hardware Windows |
| M7 | Conversão partitura → áudio (CM-007) | Q3 | developer | ADR 0002 |
| M8 | Avaliação de improvisação repouso × tensão (CM-009) | Q3 | musician, developer | M5, M7 |
| M9 | Módulos progressivos níveis 1–7 (CM-011/CM-012) | Q3–Q4 | musician, po | M8 |
| M9b | Metrônomo com BPM meta como gate (CM-014) | Q3 | musician, developer | M5 |
| M9c | Catálogo de patterns (CM-015) | Q3 | musician | M9 |
| M10 | Instaladores de teste por módulo (REQ-013) | Q4 | devops | M2b, M4 |

## Marcos de decisão

- **D1:** mesclar a branch do app ou continuar nela? (architect + PM)
- **D2:** time-stretch por algoritmo próprio ou biblioteca? (architect, ADR)
- **D3:** telemetria ligada por padrão ou opt-in? (PM + data-engineer, LGPD)
- **D4:** estratégia de síntese — FluidSynth (SoundFont) como padrão? (architect, ADR 0002)
- **D5:** como detectar "uso de pattern" de forma confiável? (musician + architect)
- **D6:** quais músicas do repertório entram e sob qual licença? (pm + musician)

## Como acompanhar

- Progresso e métricas: `docs/STATUS.md`.
- Riscos e impedimentos: `docs/RISKS.md`.
