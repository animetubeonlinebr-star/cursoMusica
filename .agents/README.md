# Time de agentes — CursoMusica

Este diretório define os **agentes individuais** do projeto. Cada arquivo
`.md` é um sub-agente com papel, escopo, fronteiras e formato de saída.

A **memória compartilhada** é o `AGENTS.md` na raiz do repositório: todos leem
antes de trabalhar e atualizam ao terminar. Ele contém o mapa de donos de
arquivo (quem escreve onde), o protocolo de handoff e a definição de pronto.

## Os agentes

| Agente | Arquivo | Dono de | Responde |
|---|---|---|---|
| Product Manager | `pm.md` | `docs/ROADMAP.md` | Por quê / O quê (macro) |
| Músico Profissional | `musician.md` | `docs/MUSIC.md` (co-own com PM) | Está musicalmente correto? |
| Product Owner | `po.md` | `docs/BACKLOG.md`, `docs/stories/**` | O quê (detalhe) |
| Arquiteto de Software | `architect.md` | `CMakeLists.txt`, `Source/Main.cpp`, `docs/adr/**` | Como estruturar |
| Data Engineer | `data-engineer.md` | `Source/Data/**`, `tools/etl/**`, `docs/DATA.md` | Dados |
| Project Manager | `project-manager.md` | `docs/PLAN.md`, `docs/STATUS.md`, `docs/RISKS.md` | Prazo, custo, risco |
| Desenvolvedor | `developer.md` | `Source/Audio/**` e código geral | Construir |
| QA Engineer | `qa.md` | `tests/**`, `docs/QA.md` | Prevenir falhas |
| DevOps | `devops.md` | `.github/workflows/**`, infra | Entregar automatizado |
| Designer | `designer.md` | `Source/UI/**` | Como se vê e se sente |

## Como o trabalho flui

```
PM + Músico ──> PO ──> Arquiteto ──> Developer / Data Engineer / Designer
                                        └──> QA ──> DevOps
Project Manager observa tudo (prazo, custo, risco).
```

Detalhes do handoff e do formato de história: `AGENTS.md` §5 e §6.

## Regras de convivência

1. Um arquivo tem **um** dono. Fora do seu escopo, você **pede**, não edita.
2. Nada começa sem critérios de aceite (PO).
3. Nada é "pronto" sem evidência (QA/DevOps).
4. Toda decisão não óbvia vira uma linha no Registro de decisões do `AGENTS.md`.
