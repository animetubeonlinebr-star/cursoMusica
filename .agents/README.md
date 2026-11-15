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

### Pipeline de módulos (Etapas)

| Agente | Arquivo | Dono de | Responde |
|---|---|---|---|
| Autor de Módulo (genérico) | `module-author.md` | conteúdo de um módulo (`Source/Course/Content/Topic<N>*.cpp`) | Transformar uma Etapa em módulo completo |
| Painel de Revisão do Módulo (genérico) | `module-reviewer.md` | veredito do módulo (sem diretório) | O módulo passa no painel? |
| Revisor de Release | `release-reviewer.md` | veredito final (sem diretório) | O curso integrado pode ir para `main`? |

### Autores por Etapa (3–10)

Um agente por Etapa, já com objetivo, conteúdos, prática, tópicos sugeridos e os
dados fixados (nível, BPM meta, `on_grid_ratio`, nome da branch) daquela Etapa.

| Etapa | Autor | Revisor | Branch |
|---|---|---|---|
| 3 — Ritmo, leitura e levadas | `mc-modulo-3.md` | `mc-rv-modulo-3.md` | `feat/modulo-3-ritmo-leitura-e-levadas` |
| 4 — Construção de acordes: tríades e tétrades | `mc-modulo-4.md` | `mc-rv-modulo-4.md` | `feat/modulo-4-construcao-de-acordes-triades-e-tetrades` |
| 5 — Campo harmônico maior e funções harmônicas | `mc-modulo-5.md` | `mc-rv-modulo-5.md` | `feat/modulo-5-campo-harmonico-maior-e-funcoes-harmonicas` |
| 6 — Escalas menores e campos harmônicos | `mc-modulo-6.md` | `mc-rv-modulo-6.md` | `feat/modulo-6-escalas-menores-e-campos-harmonicos` |
| 7 — Empilhamentos, estruturas modais e sonoridades | `mc-modulo-7.md` | `mc-rv-modulo-7.md` | `feat/modulo-7-empilhamentos-estruturas-modais-e-sonoridades` |
| 8 — Dominantes, cadências e substituições harmônicas | `mc-modulo-8.md` | `mc-rv-modulo-8.md` | `feat/modulo-8-dominantes-cadencias-e-substituicoes-harmonicas` |
| 9 — Harmonia avançada e estruturas especiais | `mc-modulo-9.md` | `mc-rv-modulo-9.md` | `feat/modulo-9-harmonia-avancada-e-estruturas-especiais` |
| 10 — Análise harmônica, verticalização e reharmonização | `mc-modulo-10.md` | `mc-rv-modulo-10.md` | `feat/modulo-10-analise-harmonica-verticalizacao-e-reharmonizacao` |

Cada autor (`mc-modulo-N`) implementa a sua Etapa numa branch própria, seguindo o
padrão do Módulo 2, e entrega ao revisor da mesma Etapa (`mc-rv-modulo-N`), que
roda o painel completo. Um achado devolve o item ao autor e reinicia o painel até
todos passarem. Depois de todos os módulos aprovados, o `release-reviewer` faz a
revisão cruzada e autoriza o merge para `main` e o instalador de teste.

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
