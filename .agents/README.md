# Time de agentes — CursoMusica

Este diretório define os **agentes individuais** do projeto. Cada arquivo
`.md` é um sub-agente com papel, escopo, fronteiras e formato de saída.

A **memória compartilhada** é o `AGENTS.md` na raiz do repositório: todos leem
antes de trabalhar e atualizam ao terminar. Ele contém o mapa de donos de
arquivo (quem escreve onde), o protocolo de handoff e a definição de pronto.

## Os agentes

### Produto e descoberta

| Agente | Arquivo | Dono de | Responde |
|---|---|---|---|
| Product Manager / Head de Produto | `pm.md` | `docs/ROADMAP.md`, KPIs/OKRs | Por quê / O quê (macro, valor) |
| Músico Profissional | `musician.md` | `docs/MUSIC.md` (co-own com PM) | Está musicalmente correto? E ensina? |
| Business Analyst | `business-analyst.md` | `docs/REQUIREMENTS.md` (co-own com PM) | Qual é a necessidade real (REQ-NNN)? |
| UX Researcher | `ux-researcher.md` | `docs/RESEARCH.md` | O problema existe? A jornada funciona? |
| UX/UI Designer | `ux-ui-designer.md` | `Source/UI/**`, `design-references/**` | Como se vê, se usa e se acessa? |
| Product Owner | `po.md` | `docs/BACKLOG.md`, `docs/stories/**` | O quê (detalhe, critérios de aceite) |

### Engenharia e entrega

| Agente | Arquivo | Dono de | Responde |
|---|---|---|---|
| Tech Lead | `tech-lead.md` | qualidade técnica (sem diretório) | É viável? Está bem desenhado e revisado? |
| Arquiteto de Software | `architect.md` | `CMakeLists.txt`, `Source/Main.cpp`, `docs/adr/**` | Como estruturar |
| Engineering Manager | `engineering-manager.md` | `docs/PLAN.md`, `docs/STATUS.md`, `docs/RISKS.md` | Capacidade, alocação, impedimentos |
| Scrum Master / Agile Coach | `scrum-master.md` | `docs/PROCESS.md` | O processo e o escopo estão claros? |
| Software Engineer | `developer.md` | `Source/Audio/**` e código geral | Construir |
| Data Engineer | `data-engineer.md` | `Source/Data/**`, `tools/etl/**` | Dados: capturar, limpar, governar |
| QA Engineer | `qa.md` | `tests/**` (co-own `set`), `docs/QA.md` | Prevenir falhas; veredito de release |
| Software Engineer in Test (SET) | `set.md` | harness e jobs de teste | Automatizar teste em escala |
| Security Engineer | `security-engineer.md` | `docs/SECURITY.md` | Está seguro? É lícito? |
| DevOps | `devops.md` | `.github/workflows/**`, `deploy/**`, infra | Entregar automatizado |

## Como o trabalho flui

```
Músico + PM + Business Analyst + UX Researcher
   (necessidade, valor, musical, evidência)
      └─> PO (histórias + critérios de aceite, a partir de REQ-NNN)
             └─> Tech Lead (viabilidade + desenho) ⇄ Arquiteto (ADR, build)
                    └─> Software Engineer / Data Engineer / UX-UI Designer
                           └─> QA + SET ──> Security Engineer ──> DevOps
Engineering Manager observa tudo (capacidade, alocação, impedimentos).
Scrum Master facilita o processo (planning, refinement, review, retro).
```

Detalhes do handoff e do formato de história: `AGENTS.md` §5 e §6.

## Regras de convivência

1. Um arquivo tem **um** dono. Fora do seu escopo, você **pede**, não edita.
2. Nada começa sem critérios de aceite (PO), rastreáveis a um `REQ-NNN` (BA).
3. Nada é "pronto" sem evidência (QA/SET/DevOps) e sem revisão do Tech Lead.
4. Toda decisão não óbvia vira uma linha no Registro de decisões do `AGENTS.md`.

## Histórico de reorganização (2026-11-04)

Revisão da estrutura de agentes, alinhada ao pedido do usuário e ao `musica.docx`:

- **Criados:** `business-analyst`, `ux-researcher`, `tech-lead`,
  `engineering-manager`, `scrum-master`, `security-engineer`, `set`.
- **Realocados:** `designer.md` → `ux-ui-designer.md` (ganhou UX, protótipos e
  acessibilidade); `project-manager.md` → `engineering-manager.md` (absorvido
  pelo papel de gestão de engenharia, alinhado ao pedido).
- **Realinhados:** `musician` (passa a necessidade ao PM **e** ao BA, e revisa se
  o projeto cumpre o objetivo do estudante), `pm` (Head de Produto, alimentado
  por BA + UX Researcher), `po` (decompõe `REQ-NNN`, com veredito do Tech Lead),
  `architect`, `developer`, `qa`, `devops`.
- **Nenhum agente foi excluído** — `designer` e `project-manager` foram
  renomeados/realocados.
