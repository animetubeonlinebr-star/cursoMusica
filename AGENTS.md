# AGENTS.md — CursoMusica (memória compartilhada)

Este arquivo é a **memória compartilhada** do time de agentes. Todo agente lê
este arquivo antes de começar e o atualiza ao terminar. Ele é a única fonte de
verdade sobre: contexto do produto, dono de cada arquivo, protocolo de handoff
e definição de pronto.

## 1. O que é o projeto

Aplicativo **desktop nativo para Windows** para **estudo de guitarra**. Captura
áudio da interface, analisa em tempo real (afinação, nível) e apoia o estudo.
O repositório também guarda os PDFs do curso.

| Item | Valor |
|---|---|
| Linguagem | C++17 |
| Framework | JUCE 8.0.4 (`External/JUCE`, clone raso) |
| Build | CMake ≥ 3.22 + Ninja (ou Visual Studio no Windows) |
| Alvo | Windows 10/11 |
| Desenvolvimento | Linux (sem dispositivo de áudio; valida só compilação) |
| UI | JUCE `Component` + `LookAndFeel_V4` customizado |
| Namespace raiz | `cursomusica` |

**Requisito nº 1:** latência baixíssima. Isso dita a arquitetura — ASIO quando
disponível, WASAPI exclusive, depois shared; buffer 64–128; a thread de áudio
nunca aloca, nunca faz lock, nunca faz I/O; UI ↔ áudio só por atomics e FIFO
lock-free; análise pesada (YIN) em thread dedicada.

## 2. Estado atual (mantenha isto atualizado)

> **Visão de produto (atualizada).** O CursoMusica é uma **plataforma de estudo
> modular**: ensina (explicação antes do desafio), demonstra com áudio, gera
> desafios, mede tudo e **avalia improvisação** (notas de repouso × tensão). O
> aluno avança por níveis com **gate de 90% de acerto** e faz tudo dentro do
> software. Requisitos rastreáveis: `docs/REQUIREMENTS.md` (REQ-001..REQ-016).

> **Afinador como ferramenta transversal.** O afinador é um **menu próprio**,
> acessível a qualquer momento, **fora dos módulos** — não é etapa de curso. Abre
> uma janela onde o aluno escolhe o *pitch* de referência (padrão **A = 440 Hz**,
> editável).

**Estrutura de diretórios (código do app):**

```
CMakeLists.txt
External/JUCE/            # dependência (não editar)
Source/
  Main.cpp                # entry point JUCEApplication
  MainComponent.h/.cpp    # janela principal, compõe os painéis e o menu
  Audio/                  # ENGINE (dono: developer)
    AudioEngine.h/.cpp    # device I/O, callback RT, análise em thread dedicada
    PitchDetector.h/.cpp  # YIN monofônico, allocation-free
    PluginHost.h/.cpp     # format manager, scan VST3, instanciação
    PluginChain.h/.cpp    # cadeia de plugins na entrada (RT-safe)
  UI/                     # INTERFACE (dono: designer)
    Design/Theme.h        # tokens de design (fonte única de verdade)
    Design/LookAndFeel.*  Design/Panel.*  Design/DESIGN.md
    LevelMeter.*  TunerDisplay.*
    DevicePanel.*  TransportPanel.*
    SettingsComponent.*   # menu de configuração (dispositivo + VST3)
.agents/agents/           # sub-agentes
docs/                     # requisitos, música, planos, ADRs
deploy/windows/           # instalador NSIS (REQ-014)
```

**Menu de configuração** (`Source/UI/SettingsComponent.*`), aberto pelo botão
**Settings** no cabeçalho:

- **Áudio:** `juce::AudioDeviceSelectorComponent` sobre o `AudioDeviceManager` —
  backend (ASIO/WASAPI), entrada, saída, taxa, buffer e roteamento.
- **VST3:** **Scan** em thread de fundo, lista de disponíveis, **Add to input
  chain**, lista da cadeia, **Remove** e **Open editor**.

O sinal capturado passa pelos plugins **antes** da análise, então o afinador e o
medidor refletem o que os plugins produzem. `PluginChain` mantém o contrato de
tempo real: a thread de áudio lê um array de ponteiros por índice atômico (sem
locks); a propriedade fica na message thread; mudança estrutural aplica → publica
índice → espera o callback reportar o índice processado → libera as instâncias
antigas.

## Estado atual (mantenha isto atualizado)

- [x] Estrutura CMake e dependência JUCE
- [x] Engine de áudio em tempo real (callback mínimo, FIFO lock-free)
- [x] Detecção de pitch (YIN) em thread de análise dedicada
- [x] Agente de design (`ux-ui-designer.md`) e design system (`Theme.h`, `DESIGN.md`)
- [x] Telas iniciais (layout, sem funcionalidade de estudo)
- [x] Menu de configuração: dispositivos, entrada, saída, buffer
- [x] Host VST3 com scan, cadeia na entrada e editor de plugin
- [x] Afinador transversal com referência A4 editável (REQ-017)
- [x] Módulo 1 jogável no app: explicação A–I (inclui rítmica), CAGED, trilha de prática, exercícios EX-1.A.1–EX-1.I.3 + gate (REQ-003/REQ-007/REQ-018); apostilas curadas citadas (REQ-006)
- [x] Diagramas do curso desenhados por `tools/make_diagrams.py` e embutidos no binário (`juce_add_binary_data`, `Source/Course/Content/Diagrams.*`); o painel central renderiza as imagens (REQ-003/REQ-006)
- [x] Explicação completa por tópico A–I (≥5 páginas cada) em `Source/Course/Content/Topic*.cpp`, e ≥3 exercícios por tópico (pedido do cliente, 2026-11-04)
- [x] Execução por seleção de tópico: menu de módulos expansível, explicação detalhada do tópico no centro e prática filtrada à direita (REQ-003/REQ-008)
- [x] Questionário do Módulo 1 (7 questões, uma por tela) e QuizSession com gate de 90% (REQ-006)
- [x] Motor de medição: NoteMath, ExerciseEvaluator (LCS + acordes), TempoGrid, PracticeSession (CM-008)
- [x] Metrônomo RT-safe com BPM meta e grade (CM-014)
- [x] Gate de progressão linear: módulo N+1 só abre com ≥90% no gate de N; progresso persistido (REQ-002/REQ-009)
- [x] Progresso espelhado em PostgreSQL (ADR 0006): `ProgressStore` offline-first grava numa thread dedicada, porta 5432 e schema `curso-musica` por padrão; banco opcional no build (libpq) e no ar (pedido do cliente, 2026-11-13)
- [x] Pastas de busca de plugins VST3 configuráveis na janela de Configurações (REQ-024, ADR 0007): botão "Pastas…" abre a janela de grid de duas colunas; a lista persiste em `vst3SearchPaths` e a varredura soma as pastas aos locais padrão (pedido do cliente, 2026-11-14)
- [x] Testes unitários da lógica pura (338 checagens) rodando no CI
- [x] Build validada no Linux: binário gerado, UI renderiza
- [x] Módulo 2 jogável no app (Etapa 2 — Teoria dos intervalos e percepção musical): 8 tópicos A–H, ≥5 páginas/tópico, imagens/tabelas/áudios e partituras com áudio, 3–5 exercícios por tópico (EX-2.*) e gate `C–F–G–C` a 64 BPM (2026-11-16)
- [x] Módulo 8 jogável no app (Etapa 8 — Dominantes, cadências e substituições harmônicas): 10 tópicos A–J, ≥5 páginas/tópico, imagens/tabelas/áudios e partituras com áudio, 40 exercícios (EX-8.*) + gate II-V-I maior a 88 BPM (2026-11-15)
- [ ] Ligar UI principal à engine (nível e afinação reais em vez de dummy)
- [x] Ajustes do `musica.docx` (CM-018..CM-021): módulo abre em branco e mantém o tópico no mesmo módulo (REQ-019/020), ≥1 exercício por tópico A–I (REQ-022), classificação correta de entradas/saídas de áudio (REQ-023)
- [x] Painéis do estudo prático (REQ-021, revisão 2026-11-07): questionário no painel central (questão + alternativas clicáveis), controles/placar/orientação no painel direito
- [x] Fluxo da tela Módulos por etapas (revisão do `musica.docx`, 2026-11-07): painel direito vazio ao abrir o módulo, seletor só após escolher o tópico e exercício armado só após escolher no combobox; Módulo 1 imprime traço em BPM META (`CourseModule::usesTempo`)
- [ ] Playback com controle de velocidade e loop
- [ ] Avaliação de improvisação (repouso × tensão, REQ-010/REQ-011/REQ-012)
- [ ] ASIO SDK no Windows (licença Steinberg, download separado)
- [x] Empacotamento / instalador: `instalador/Instalador CursoMusica.exe` (PE32) publicado na branch `test` pelo `release.yml` (`windows-2022`, `TEST_UNLOCK_ALL=ON`); instala escolhendo o diretório (CM-010/CM-013). Último build: commit `89b0498`, 3.154.601 bytes, sha256 `9e955335…` (conteúdo completo A–I, 29 exercícios e os 19 diagramas embutidos)

## 3. Mapa de propriedade de arquivos (contrato de escrita)

Cada caminho tem **um único dono**. Nenhum agente escreve fora do seu escopo;
quando precisa, ele **pede** ao dono (ver protocolo de handoff, seção 5).

| Caminho | Dono | Quem pode ler |
|---|---|---|
| `Source/Audio/**` | `developer` (linha de áudio) | todos |
| `Source/Course/**` | `developer` (conteúdo: co-own com `musician`) | todos |
| `Source/UI/**` | `ux-ui-designer` | todos |
| `CMakeLists.txt`, `Source/Main.cpp` | `architect` | todos |
| `Source/Data/**`, `tools/etl/**` | `data-engineer` | todos |
| `.github/workflows/**`, `Dockerfile*`, `deploy/**` | `devops` (jobs de teste: co-own com `set`) | todos |
| `tests/**` | `qa` (harness/infra: co-own com `set`) | todos |
| `docs/ROADMAP.md` | `pm` | todos |
| `docs/inbox/**` (fontes brutas: docx, e-mail) | `business-analyst` | todos |
| `docs/REQUIREMENTS.md` | `business-analyst` (co-own com `pm`) | todos |
| `docs/MUSIC.md` | `musician` (co-own com `pm`) | todos |
| `docs/BACKLOG.md`, `docs/stories/**` | `po` | todos |
| `docs/RESEARCH.md` | `ux-researcher` | todos |
| `docs/PLAN.md`, `docs/STATUS.md`, `docs/RISKS.md` | `engineering-manager` | todos |
| `docs/PROCESS.md` | `scrum-master` | todos |
| `docs/SECURITY.md` | `security-engineer` | todos |
| `docs/QA.md` | `qa` | todos |
| `docs/adr/**` | `architect` | todos |
| `docs/POSTGRESQL.md` | `architect` (co-own `data-engineer`) | todos |
| `AGENTS.md` | todos (append em "Registro de decisões") | todos |

Regra dura herdada do designer: quem não é dono de `Source/Audio/` ou
`CMakeLists.txt` **não edita** esses arquivos. Quem precisa de um arquivo novo no
build entrega a linha exata de `target_sources` ao dono.

## 4. Divisão de responsabilidade entre agentes

| Agente | Arquivo | Dono de | Pergunta que responde |
|---|---|---|---|
| Product Manager / Head de Produto | `.agents/agents/pm.md` | `docs/ROADMAP.md` (co-own `docs/REQUIREMENTS.md`), KPIs/OKRs | **Por quê / O quê** (macro, valor) |
| Músico Profissional | `.agents/agents/musician.md` | `docs/MUSIC.md` (co-own com PM) | **Está musicalmente correto? E ensina?** |
| Business Analyst | `.agents/agents/business-analyst.md` | `docs/REQUIREMENTS.md` (co-own com PM) | **Qual é a necessidade real (REQ-NNN)?** |
| UX Researcher | `.agents/agents/ux-researcher.md` | `docs/RESEARCH.md` | **O problema existe? A jornada funciona?** |
| UX/UI Designer | `.agents/agents/ux-ui-designer.md` | `Source/UI/**`, `design-references/**` | **Como se vê, se usa e se acessa?** |
| Product Owner | `.agents/agents/po.md` | `docs/BACKLOG.md`, `docs/stories/**` | **O quê** (detalhe, critérios de aceite) |
| Tech Lead | `.agents/agents/tech-lead.md` | (qualidade técnica; sem diretório próprio) | **É viável? Está bem desenhado e revisado?** |
| Arquiteto de Software | `.agents/agents/architect.md` | `CMakeLists.txt`, `Source/Main.cpp`, `docs/adr/**` | **Como estruturar** |
| Engineering Manager | `.agents/agents/engineering-manager.md` | `docs/PLAN.md`, `docs/STATUS.md`, `docs/RISKS.md` | **Capacidade, alocação, impedimentos** |
| Scrum Master / Agile Coach | `.agents/agents/scrum-master.md` | `docs/PROCESS.md` | **O processo e o escopo estão claros?** |
| Software Engineer | `.agents/agents/developer.md` | `Source/Audio/**` (e código geral) | **Construir** |
| Data Engineer | `.agents/agents/data-engineer.md` | `Source/Data/**`, `tools/etl/**` | **Dados: capturar, limpar, governar** |
| QA Engineer | `.agents/agents/qa.md` | `tests/**` (co-own `set`), `docs/QA.md` | **Prevenir falhas; veredito de release** |
| Software Engineer in Test (SET) | `.agents/agents/set.md` | harness e jobs de teste em `tests/**` e `.github/workflows/**` | **Automatizar teste em escala** |
| Security Engineer | `.agents/agents/security-engineer.md` | `docs/SECURITY.md` | **Está seguro? É lícito?** |
| DevOps | `.agents/agents/devops.md` | `.github/workflows/**`, `deploy/**`, infra | **Entregar automatizado** |
| Autor de Módulo | `.agents/agents/module-author.md` | `Source/Course/Content/Topic<N>*.cpp` de um módulo (co-own `musician`) | **Transformar uma Etapa em módulo completo** |
| Painel de Revisão do Módulo | `.agents/agents/module-reviewer.md` | (veredito; sem diretório próprio) | **O módulo passa no painel?** |
| Revisor de Release | `.agents/agents/release-reviewer.md` | (veredito final; sem diretório próprio) | **O curso integrado pode ir para `main`?** |

## 4.1. Pipeline de módulos (Etapas) — autor → painel → release

Cada Etapa do curso (`docs/MUSIC.md`) vira **um módulo**, seguindo exatamente o
padrão do **Módulo 2** (Etapa 2 — Teoria dos intervalos e percepção musical):
teoria com **mínimo de 5 páginas por tópico**, **imagens**, **áudios** e
**partituras** (toda partitura com seu áudio), **3 a 5 exercícios por tópico**, e
parte dos exercícios **tocada no instrumento**, com o app reconhecendo as notas
para verificar se o intervalo/acorde está correto.

O fluxo é:

```
docs/MUSIC.md (Etapa N)
   └─> module-author  → branch feat/modulo-<N>-<slug> + PR para `test`
          └─> module-reviewer (painel):
                1 Músico · 2 PM · 3 PO · 4 Tech Lead · 5 Arquiteto · 6 Tech Lead
                · 7 Software Engineers · 8 Tech Lead · 9 QA · 10 Security · 11 SET
                     ↳ qualquer problema volta ao module-author;
                       corrigido, o painel REINICIA do começo
                       até todos passarem na mesma rodada
          └─> merge do módulo em `test`
                 └─> (todos os módulos prontos) release-reviewer (revisão final):
                       1 Arquiteto · 2 Tech Lead · 3 Software Engineers · 4 Tech Lead
                            ↳ merge de `test` em `main` + instalador de teste
```

**Agentes por Etapa (3–10).** Além dos agentes genéricos
(`module-author`, `module-reviewer`, `release-reviewer`), cada Etapa 3–10 tem um
autor e um revisor próprios, já com objetivo, conteúdos, prática, tópicos
sugeridos e os dados fixados (nível, BPM meta, `on_grid_ratio`, branch) daquela
Etapa:

| Etapa | Autor | Revisor | Branch |
|---|---|---|---|
| 3 — Ritmo, leitura e levadas | `mc-modulo-3` | `mc-rv-modulo-3` | `feat/modulo-3-ritmo-leitura-e-levadas` |
| 4 — Construção de acordes: tríades e tétrades | `mc-modulo-4` | `mc-rv-modulo-4` | `feat/modulo-4-construcao-de-acordes-triades-e-tetrades` |
| 5 — Campo harmônico maior e funções harmônicas | `mc-modulo-5` | `mc-rv-modulo-5` | `feat/modulo-5-campo-harmonico-maior-e-funcoes-harmonicas` |
| 6 — Escalas menores e campos harmônicos | `mc-modulo-6` | `mc-rv-modulo-6` | `feat/modulo-6-escalas-menores-e-campos-harmonicos` |
| 7 — Empilhamentos, estruturas modais e sonoridades | `mc-modulo-7` | `mc-rv-modulo-7` | `feat/modulo-7-empilhamentos-estruturas-modais-e-sonoridades` |
| 8 — Dominantes, cadências e substituições harmônicas | `mc-modulo-8` | `mc-rv-modulo-8` | `feat/modulo-8-dominantes-cadencias-e-substituicoes-harmonicas` |
| 9 — Harmonia avançada e estruturas especiais | `mc-modulo-9` | `mc-rv-modulo-9` | `feat/modulo-9-harmonia-avancada-e-estruturas-especiais` |
| 10 — Análise harmônica, verticalização e reharmonização | `mc-modulo-10` | `mc-rv-modulo-10` | `feat/modulo-10-analise-harmonica-verticalizacao-e-reharmonizacao` |

As Etapas 3–10 são construídas **em paralelo** (uma branch por Etapa, a partir de
`test`). Como cada branch altera a mesma asserção final de `testModule2()` ("os
módulos 3..20 são placeholders"), essa asserção deve ser trocada por uma regra
que valha para qualquer conjunto implementado (números únicos, implementados
contíguos a partir de 1, `findModule(N)` devolve o módulo), de modo que as
branches não conflitem entre si.

**Regras do pipeline:**

- Um módulo por branch; um PR por módulo.
- Um problema encontrado **retorna ao autor**; a correção **reinicia o painel
  inteiro**, não apenas o revisor que falhou.
- Nenhum módulo é aceito sem o painel completo verde na mesma rodada.
- A revisão final do release cobre o **conjunto** dos módulos (o que os painéis
  por módulo não veem): duplicação, padrão inconsistente, quebra de integração.
- Merge só por PR, **nunca** reescrevendo histórico; backup antes de todo push
  (§11).

## 5. Protocolo de handoff (como os agentes conversam)

O trabalho flui em uma esteira. Cada etapa tem **entrada**, **saída** e um
**artefato verificável** que destrava a próxima.

```
Músico + PM + Business Analyst + UX Researcher
   (MUSIC + ROADMAP + REQUIREMENTS + RESEARCH: necessidade, valor, musical, evidência)
      └─> PO (BACKLOG: histórias + critérios de aceite, vindos de REQ-NNN)
             └─> Tech Lead (viabilidade + desenho técnico) ⇄ Arquiteto (ADR, build)
                    └─> Software Engineer / Data Engineer / UX-UI Designer (código)
                           └─> QA + SET (testes, regressão, carga, automação)
                                  └─> Security Engineer (SAST/DAST, dependências, licença)
                                         └─> DevOps (CI/CD, deploy, observabilidade)
   Engineering Manager observa tudo: capacidade, alocação, impedimentos.
   Scrum Master facilita o processo (planning, refinement, review, retro).
```

Regras do handoff:

1. **Nada entra em desenvolvimento sem critérios de aceite** escritos pelo PO,
   rastreáveis a um `REQ-NNN` do Business Analyst.
2. **Nada com dimensão musical entra sem revisão do músico** — o PM, o BA e o
   músico ajustam o requisito juntos; a verdade musical fica em `docs/MUSIC.md`.
3. **Nada entra em build sem decisão de arquitetura** quando toca estrutura,
   dependência ou contrato entre módulos, e sem o **veredito de viabilidade do
   Tech Lead**.
4. **Nada é considerado pronto sem evidência** (teste, build, log) anexada pelo
   QA/SET/DevOps.
5. Ao terminar uma etapa, o agente **escreve o artefato no seu arquivo** e
   **adiciona uma linha no Registro de decisões** (seção 7) com: data, agente,
   decisão, impacto.
6. Conflito de escopo se resolve **a favor do dono do arquivo**; quem discorda
   abre uma nota em `docs/RISKS.md` (dono: Engineering Manager).
7. **Mudança que carrega código externo ou dado do usuário** (host VST3, parsing
   de arquivo, telemetria) passa pelo Security Engineer antes do merge.

### Formato de uma história de usuário (padrão do PO)

```
### [ID] [Título]  —  valor: A/M/B  —  tamanho: P/M/G  —  status: ready/draft
Origem: REQ-NNN (docs/REQUIREMENTS.md)
Como um [tipo de usuário], eu quero [fazer algo] para que eu possa [benefício].

Critérios de aceite:
- Dado [contexto], quando [ação], então [resultado esperado].
- ...

Pronto quando (DoD):
- [ ] Veredito de viabilidade do Tech Lead (ready)
- [ ] Código revisado via PR (Tech Lead)
- [ ] Teste automatizado verde no CI (QA/SET)
- [ ] Build sem avisos novos
- [ ] Sem achado de segurança aberto (Security Engineer, quando aplicável)
- [ ] Documentação/memória atualizada
```

## 6. Definição de pronto (DoD) do projeto

Uma entrega só é "pronta" quando:

- [ ] Atende aos critérios de aceite do PO (evidência anexada) e rastreia um `REQ-NNN`.
- [ ] Passa no build (`cmake --build build`) sem avisos novos.
- [ ] Tem teste automatizado (quando houver lógica testável) verde no CI.
- [ ] Passou por `code review` do Tech Lead (PR).
- [ ] Passou pelo Security Engineer quando carrega código externo, parsing de arquivo ou dado do usuário.
- [ ] CI verde (`.github/workflows`).
- [ ] `AGENTS.md` e o doc do módulo atualizados.

## 7. Registro de decisões (append-only)

| Data | Agente | Decisão | Impacto |
|---|---|---|---|
| 2026-11-02 | orquestrador | Framework multi-agente criado; `AGENTS.md` vira memória compartilhada; donos de arquivo definidos na seção 3 | Todos os agentes passam a operar por este contrato |
| 2026-11-02 | pm | Roadmap inicial em `docs/ROADMAP.md` (v0.1 → v1.0) | PO pode derivar o backlog |
| 2026-11-02 | po | Backlog inicial em `docs/BACKLOG.md` priorizado por valor | Destrava arquitetura e desenvolvimento |
| 2026-11-02 | musician + pm | Agente músico profissional criado; requisitos musicais revisados juntos e fixados em `docs/MUSIC.md` (A4=440, tolerância ±5 cents, detecção 80–1400 Hz, playback 25–100% sem mudança de tom) | PO passa a derivar critérios de aceite musicais de `docs/MUSIC.md` |
| 2026-11-02 | pm + musician | Requisitos de sistema formalizados em `docs/REQUIREMENTS.md` (REQ-001..REQ-014): plataforma modular, progressão linear com níveis, gate de 90%, desafios, áudio obrigatório, notas de repouso/tensão, curadoria de apostilas/links/patterns, repertório, instalador Windows | PO deriva o backlog; architect decide a stack; data-engineer modela a medição |
| 2026-11-02 | architect | ADR 0002 (pugixml, midifile, FluidSynth/RtAudio, libsndfile fora da thread de áudio) e ADR 0003 (progressão linear, gate de 90%, avaliação explicável, override de teste) | Novas dependências e modelo de curso definidos |
| 2026-11-02 | data-engineer | Schema v2 de medição (`attempt`, `note_event`, `module_result`, uso de pattern/link) e cálculo determinístico do gate | Motor de progressão passa a ser auditável |
| 2026-11-02 | devops | Workflow de release com instalador Windows (REQ-014) e instaladores de teste por módulo (REQ-013) | Cada módulo tem artefato instalável na branch de teste |
| 2026-11-02 | musician | Catálogo de patterns com IDs estáveis (`PTN-*`): melódicos, rítmicos e de arpejo; mapa de standards como laboratório progressivo | PO pode citar pattern por ID; avaliação detecta assinatura (REQ-016) |
| 2026-11-02 | musician + pm | Direitos autorais: posição registrada (art. 46, II, Lei 9.610/98) para projeto pessoal, sem fins comerciais, só pequenos trechos de estudo | R-08 passa de bloqueante a condicional |
| 2026-11-02 | musician + pm | Regra de tensão refinada: tensão não solicitada é erro, salvo se a nota fizer parte do acorde | REQ-012 sem ambiguidade; QA testa os dois casos |
| 2026-11-02 | pm + musician + architect | REQ-015 (metrônomo com BPM meta como gate) e REQ-016 (catálogo de patterns); ADR 0004 (dois eixos de gate, tolerância rítmica) | Progressão passa a exigir acurácia ≥90% **e** BPM meta |
| 2026-11-02 | musician + pm | Faixa de `on_grid_ratio` fixada em **0,75–0,82** (precisão com respiração; 90% cedo engessa a execução), com **rampa linear até 0,90 do módulo 15 ao 20** | Corrige a calibração do gate de andamento (ADR 0004, R-13) |
| 2026-11-02 | musician | Análise harmônica por música registrada em `docs/MUSIC.md` (Maiden Voyage, Cantaloupe Island, Só Danço Samba, Equinox, Incompatibilidade de Gênios, 500 Miles High, Spain) com encadeamentos verificados e mapeamento música → nível | Currículo por standards passa a ser executável por módulo |
| 2026-11-02 | musician | Síncope brasileira exige grade própria na medição de tempo; `PTN-R-BOSSA` ligado a Só Danço Samba e Incompatibilidade de Gênios | Evita penalizar o aluno por tocar certo no estilo (R-13) |
| 2026-11-02 | musician + pm | **Confirmado: o BPM meta sobe progressivamente do módulo 15 ao 20** (120 → 140, +4 BPM/módulo), em paralelo com a rampa de `on_grid_ratio` (0,82 → 0,90); mapa módulo → nível (20 módulos nos 7 modelos) fixado | Currículo passa a ter velocidade e precisão crescentes, sem saltos |
| 2026-11-02 | architect + developer + designer | App JUCE mesclado na branch do framework (o projeto estava partido em duas branches); `AGENTS.md` unificado com o layout de código e a disciplina de branches (§11) | Código e framework passam a viver juntos; `main` ainda intocado |
| 2026-11-02 | pm + musician + developer + designer | **REQ-017: afinador transversal** (menu próprio, fora dos módulos) com pitch de referência A4 editável (padrão 440 Hz, faixa 400–480, persistido); implementado em `TunerComponent.*` + `TuningSettings.*`; presets incluem 415 Hz barroco (MUSIC.md) | Aluno afina a qualquer momento, em qualquer referência; build Linux validada sem avisos |
| 2026-11-02 | musician + pm | **Módulo 1 especificado** em `docs/MUSIC.md` (blocos A–H: partes do instrumento, notas, sustenidos/bemóis, braço, pestana, CAGED, tonalidades, cifrado; exercícios EX-1.1–EX-1.7; desafio de gate `C–G–Am–F` a 60 BPM; patterns `PTN-R-PALM`/`PTN-M-3`; links citados) | PO pode derivar a história; developer implementa o catálogo |
| 2026-11-02 | architect + developer | **ADR 0005** (conteúdo do curso é código compilado, sem dependência nova) e **REQ-018**; criados `Source/Course/Module.h`, `ModuleCatalog.*` e `Source/UI/ModuleComponent.*` (explicação antes do desafio, REQ-003) | Módulo 1 jogável dentro do app; build Linux validada sem avisos |
| 2026-11-02 | data-engineer + developer + musician | **Módulo 1 fechado**: motor de medição (`NoteMath`, `ExerciseEvaluator`, `TempoGrid`, `PracticeSession`), metrônomo RT-safe (CM-014), painel de prática e gate de progressão linear com persistência (`ProgressStore`, `ProgressionRule`); 50 checagens unitárias verdes no CI; pattern/links REQ-007 exibidos no módulo | Aluno conclui o Módulo 1 dentro do app e o Módulo 2 desbloqueia ao atingir ≥90%; gate auditável e testado |
| 2026-11-02 | musician + developer | **Revisão das apostilas (CM-012)**: PDFs sob LFS baixados e lidos (OCR nos digitalizados); mapa bloco → fonte em `docs/MUSIC.md` §1.1; lacuna fechada com o **bloco I — Rítmica** (pulsação, figuras, contagem TÁ/TÁ-KI, do cap. "Rítmica" de `pdf-fraseado-melodico`) e **EX-1.8**; `CourseModule::sources` + `rhythm` no modelo, exibidos na UI (seções "Apostilas" e "Rítmica e contagem"); corrigido `getRequiredHeight` (CAGED/prática subestimavam a altura e cortavam o fim do módulo); suíte em **85 checagens verdes** | Conteúdo do Módulo 1 lastreado na fonte e completo; fim do módulo deixa de ser cortado na UI |
| 2026-11-03 | devops | **Instalador de teste de ponta a ponta (CM-010/CM-013)**: `TEST_UNLOCK_ALL` virou opção de CMake e ativa `ProgressStore::unlockAll` (ADR 0003 item 7); `installer.nsi` gera `Instalador CursoMusica.exe` via staging `deploy/windows/dist/app` (makensis não resolve `..`) com runtime opcional (`/DRUNTIME`); `release.yml` roda em push da branch `test` no `windows-2022` (MSVC + Ninja) e publica o `.exe` em `instalador/` (artifact do run; commit sob `commit_installer=true`) | Validação passa a ter um instalador Windows real, com tudo liberado, entregue na raiz do projeto da branch de teste |
| 2026-11-03 | musician + developer + designer | **Execução do módulo por seleção (REQ-003/REQ-008/REQ-009)**: o painel de módulos virou três painéis dependentes — menu à esquerda (módulos expansíveis em tópicos, `TreeView`), explicação no centro (visão geral do módulo, tópico detalhado ou demonstração do exercício) e prática à direita; clicar num tópico carrega a explicação no centro e filtra os exercícios do tópico; a medição (Nota/Acertos/Grade) fica sempre visível acima da aplicação (exercício jogável ou questionário) | O aluno estuda cada tópico com a explicação e a prática do tópico lado a lado; o fim do módulo deixa de cortar conteúdo |
| 2026-11-03 | musician + developer | **Questionário do Módulo 1 (REQ-006)**: `Exercise::quiz` (`QuizQuestion`) e `QuizSession` (sessão pura, gate 90%); EX-1.1 virou "Questionário: conhecendo o instrumento" com as 7 questões de `Questionario_m1.pdf`, respondidas uma por tela no painel direito; explicações detalhadas do tópico A (partes da guitarra/violão) tiradas de `explica_painelEsquerdo.pdf`, com destaques e tabelas | Conteúdo das apostilas curadas vira exercício avaliável dentro do app; suíte em **122 checagens verdes** |
| 2026-11-03 | devops | **Varredura de duplicatas nas apostilas**: as 21 apostilas da branch `adequacao` foram comparadas por hash LFS e por assinatura de imagem multi-página (páginas 0/25/50/75/última), pegando também PDFs digitalizados sem texto; 3 eram cópias exatas com sufixo `(1)` no nome; removidas no commit `b4f284c`, restando 18 apostilas únicas | Acervo sem repetição, uma de cada, sem perder nenhum título |
| 2026-11-04 | devops + pm | **Merge do Módulo 1 em `test` e instalador de teste**: `feat/measurement-engine` mesclada em `test` com `--no-ff` (merge `4a434e3`; `test` era ancestral, sem conflitos); build Linux limpo e **122/122 testes verdes**; push disparou o `release.yml` e um `workflow_dispatch` com `commit_installer=true` publicou `instalador/Instalador CursoMusica.exe` na branch `test` (commit `956b80c`, ~1,9 MB, todos os módulos liberados). Backups `backup/pre-merge-modulo1-test` (cc06277) e `backup/feat-measurement-engine-839bc40` | Versão de teste com instalador Windows entregue na branch `test` (REQ-013); `main` intocado |
| 2026-11-04 | orquestrador + todo o time | **Reorganização do time de agentes** (pedido do usuário + `musica.docx`): criados `business-analyst`, `ux-researcher`, `tech-lead`, `engineering-manager`, `scrum-master`, `security-engineer` e `set`; `designer.md` renomeado para `ux-ui-designer.md` (ganhou UX, protótipos, acessibilidade) e `project-manager.md` para `engineering-manager.md`; `musician` passa a levar a necessidade ao PM **e** ao BA e a auditar se o curso ensina; `pm` vira Head de Produto alimentado por BA + UX Researcher; `po` decompõe `REQ-NNN` com veredito de viabilidade do Tech Lead; handoff, DoD e mapa de propriedade atualizados em `AGENTS.md` §3–6 e em `.agents/README.md` | Time passa a cobrir descoberta (BA/UX), liderança técnica (Tech Lead), segurança (InfoSec), automação de teste (SET) e processo (Scrum Master); nenhum papel de produto perdido |
| 2026-11-04 | business-analyst + musician + po | **Processamento do `musica.docx`** (fonte preservada em `docs/inbox/musica.docx`): elicitados 5 requisitos — REQ-019 (módulo abre em branco), REQ-020 (mantém tópico no mesmo módulo, limpa em outro), REQ-021 (exercício à direita, explicação no centro), REQ-022 (≥1 exercício por tópico), REQ-023 (classificação correta de entradas/saídas — bug VoiceMeeter Banana); decompostos em histórias CM-018..CM-021 no `docs/BACKLOG.md`, com critérios de aceite | Solicitação do cliente rastreada ponta a ponta (docx → REQ-NNN → história); CM-021 bloqueado por exigir Windows + VoiceMeeter |
| 2026-11-04 | developer + ux-ui-designer + musician | **Ajustes do `musica.docx` implementados (CM-018..CM-021, branch `feat/modulo1-completo`)**: (REQ-019/020) abrir um módulo mostra só o contexto, o tópico só carrega no clique e a memória de tópico é por módulo — módulo já lido lista os tópicos de novo, módulo novo abre em branco; (REQ-021) o centro traz só a explicação e o exercício executável fica no painel direito; (REQ-022) criados EX-1.9 (sustenidos/bemóis/enarmonia, tópico C) e EX-1.10 (tonalidade/campo harmônico, tópico G), fechando ≥1 exercício por tópico A–I; (REQ-023) novo `AudioPortClassifier` + `AudioPortsPanel` que rotulam cada porta pela direção real do app, corrigindo o VoiceMeeter (nome escrito pela ótica do mixer). Suíte em **146 checagens verdes**; build Linux limpa | Os 5 requisitos do cliente ficam verificáveis; falta só a validação de REQ-023 no Windows com o VoiceMeeter instalado |
| 2026-11-04 | devops | **Versão de teste com todos os ajustes publicada**: `feat/modulo1-completo` mesclada em `test` com `--no-ff` (merge `3603ee6`; backup `backup/pre-musica-docx-test`); push em `test` rodou o `release.yml` (run `41893051023`, success) e um `workflow_dispatch` com `commit_installer=true` (run `41893699833`, success) commitou o instalador em `test` (commit `d031d86`, `instalador/Instalador CursoMusica.exe`, 1.981.593 bytes, PE32, sha256 `4d853fbf…`), idêntico ao artifact do run | Versão de teste com REQ-019..023 entregue na branch `test` (REQ-013); `main` intocado |
| 2026-11-05 | musician + business-analyst | **Revisão das apostilas novas da `adequacao`**: a branch foi reescrita a partir da nova `main` (`1dc295f`) e trouxe **4 apostilas** identificadas por hash LFS vs. a versão anterior (`b70bdf7`) — CAGED (Marcelo Mello, bloco F), Teoria Elementar (Lacerda, blocos B/C/D), Teoria da Música (Bohumil Med 5ª ed., blocos B/C/G/I) e Manual de regulagem/manutenção (Mozart Carvalho, bloco A). O acervo curado do Módulo 1 passou de 3 para **7 fontes** em `CourseModule::sources`; `docs/MUSIC.md` §1.1 ganhou a tabela apostila → blocos e o mapa bloco → fonte; suíte em **150 checagens verdes** | Conteúdo do Módulo 1 lastreado também nas obras de teoria e no manual do instrumento; curadoria rastreável |
| 2026-11-05 | devops | **Instalador de teste atualizado publicado**: merge `800896e` de `feat/modulo1-completo` em `test` (backup `backup/pre-apostilas-adequacao-test`); push rodou o `release.yml` (run `41952764869`, success) e um `workflow_dispatch` com `commit_installer=true` (run `41953169200`, success) commitou o instalador (commit `f4f3e2a`, 1.982.038 bytes, PE32 `0x14c`, sha256 `7f997e64…`), idêntico ao artifact do run | Versão de teste com a curadoria atualizada entregue na branch `test` (REQ-013); `main` intocado |
| 2026-11-05 | developer + ux-ui-designer + musician | **Conformidade com o `musica.docx` (2ª revisão)**: extraídas as 9 capturas do documento e o app rodado sob Xvfb (1040×680, a mesma janela das capturas) para comparar estado a estado. REQ-019 corrigido — módulo nunca lido abre com o centro em branco (só contexto: cabeçalho, nível/BPM/gate, objetivo), sem CAGED/rítmica/trilha/fontes; REQ-022 corrigido — EX-1.7 (tópico H, cifrado) virou executável (ii–V–I Dm7–G7–C7M), fechando ≥1 exercício executável por tópico A–I; REQ-023 ganhou teste com o nome exato da captura ("CABLE In 16ch"). Suíte em **160 checagens verdes** | Os 5 requisitos do cliente ficam verificáveis no app real; falta só a validação de REQ-023 no Windows com o VoiceMeeter instalado |
| 2026-11-05 | devops | **Instalador de conformidade publicado**: merge `f40420c` de `feat/modulo1-completo` em `test`; push rodou o `release.yml` (run `42052071378`, success) e um `workflow_dispatch` com `commit_installer=true` (run `42053079008`, success) commitou o instalador (commit `01580a2`, 1.982.587 bytes, PE32 `0x14c`, sha256 `83e20f24…`), byte-a-byte idêntico ao artifact do run | Versão de teste com REQ-019/022 corrigidos entregue na branch `test` (REQ-013); `main` intocado |
| 2026-11-05 | developer + ux-ui-designer | **Correção do painel de prática (REQ-021)**: o painel direito passa a apresentar o exercício armado como linha clicável (ícone de play + `id — título`), como no mock-up do `musica.docx` (image7), em vez do botão textual "Demonstrar no centro"; o centro deixa de repetir o `id — título` e mostra só objetivo/como o app verifica. Validado sob Xvfb (1040×680) contra a captura. Instalador de teste republicado: push `a3a44c0` (run `42101567359`) + `workflow_dispatch` com `commit_installer=true` (run `42101586565`) commitou `9f5f70e` (1.983.923 bytes, PE32 `0x14c`, sha256 `abcf8194…`), idêntico ao artifact | Fecha a divergência apontada ("o que está no arquivo e o que foi feito continua divergente"); exercício no painel direito, explicação no centro |
| 2026-11-07 | developer + ux-ui-designer | **Painéis do estudo prático (REQ-021, revisão do cliente)**: o questionário (EX-1.1) passa a rodar no **painel central** — cabeçalho do módulo (nível/BPM/gate), instrução "Responda uma questão por vez.", "Questão X de Y", enunciado e alternativas clicáveis A–D; o **painel direito** fica só com os controles (cabeçalho + link "Todos os tópicos do módulo", seletor, botão de play com `id — título`, placar e caixa de orientação "Neste exercício…"). O centro responde por procuração à sessão do `PracticePanel` (`ContentView::onAnswerOption`/`setQuiz`); validado sob Xvfb (1040×680) respondendo uma alternativa (avança a questão e atualiza o placar); suíte em **160 checagens verdes** | Fecha a divergência apontada na revisão do painel de quiz; questão/alternativas no palco central, controles à direita |
| 2026-11-07 | devops | **Instalador de teste republicado**: push de `b9c7d97` em `test` rodou o `release.yml` (run `42391628451`, success) e um `workflow_dispatch` com `commit_installer=true` (run `42391642477`, success) commitou o instalador (commit `a878df7`, 1.990.940 bytes, PE32 `0x14c`, sha256 `e38d186b…`) | Versão de teste com o quiz no painel central entregue na branch `test` (REQ-013); `main` intocado |
| 2026-11-07 | developer + ux-ui-designer | **Responsividade das telas (resize/maximizar/minimizar)**: as telas overlay (`Módulos`, `Afinador`, `Configurações`) recebiam `setBounds(getLocalBounds())` só na criação, então mantinham o tamanho de quando foram abertas e não acompanhavam o resize. `MainComponent::resized()` passa a re-ajustar os overlays ativos a cada resize; `Main.cpp` define `setResizeLimits(980, 660, …)` para o layout de três painéis não cortar o próprio cabeçalho. Validado sob Xvfb+openbox (botões do overlay seguem a largura: 780–1016 em 1040px → 1060–1296 em 1320px); suíte em **160 checagens verdes** | Fecha o pedido "ao maximizar ou minimizar as telas, as janelas não se adequam ao tamanho da tela" |
| 2026-11-07 | devops | **Instalador de teste republicado (responsividade)**: push de `d433a90` em `test` rodou o `release.yml` (run `42401301219`, success) e um `workflow_dispatch` com `commit_installer=true` (run `42401311382`, success) commitou o instalador (commit `24ca1b3`, 1.990.974 bytes, PE32 `0x14c`, sha256 `846b4cd3…`) | Versão de teste com a responsividade corrigida entregue na branch `test` (REQ-013); `main` intocado |
| 2026-11-07 | developer + ux-ui-designer | **Fluxo da tela Módulos por etapas (REQ-019/020/021, revisão do `musica.docx`)**: o painel direito virou estritamente dependente do esquerdo — ao abrir o módulo mostra só o cabeçalho "Exercícios práticos" (image3), ao clicar num tópico revela o seletor com o primeiro exercício como dica (image4) e só **arma** o exercício quando o aluno escolhe no combobox, revelando placar e orientação (image6). `PracticePanel` ganhou `topicChosen`/`exerciseArmed`; o combobox usa `setTextWhenNothingSelected` (sem pré-seleção) para que escolher o primeiro item dispare `onChange`. `CourseModule::usesTempo` (novo) faz o Módulo 1 imprimir traço em BPM META no cabeçalho **e** no painel de prática, conforme pedido ("o BPM nesse módulo não será utilizado"). Validado sob Xvfb (1040×680) nos 5 estados (image3→image4→image5→image6→image8); suíte em **180 checagens verdes** | Fecha o comportamento errado apontado ("ao abrir Módulos o quiz já aparece aberto"); painel direito só se popula após a seleção de tópico/exercício |
| 2026-11-07 | devops | **Instalador de teste republicado (fluxo da tela Módulos)**: backup `backup/pre-modulos-flow-test` em `1ae25ff` (regra §11); `main` (`0d30ecb`) já era ancestral de `test`, sem merge a fazer; push de `a0bc0a7` em `test` rodou o `release.yml` (run `43087399261`, success) e um `workflow_dispatch` com `commit_installer=true` (run `43088022705`, success) commitou o instalador (commit `c0f6853`, 1.991.722 bytes, PE32 `0x14c`, sha256 `4298d2c7…`), byte-a-byte idêntico ao artifact `Instalador-CursoMusica-1` do run | Versão de teste com a correção do painel de Módulos entregue na branch `test` (REQ-013); `main` intocado |
| 2026-11-07 | musician + developer | **Conteúdo completo do Módulo 1 (pedido do cliente)**: cada tópico A–I ganhou a explicação completa (≥5 páginas, escrita para iniciante) em `Source/Course/Content/TopicA.cpp` … `TopicI.cpp`, extraída dos PDFs curados (CAGED de Marcelo Mello, Teoria Elementar de Lacerda, Teoria da Música de Bohumil Med, Fraseado Melódico e o manual de regulagem), com `LessonBlock::detail` composto por `content::topicX()`; o catálogo passou de 10 para **29 exercícios numerados + o gate**, com **≥3 exercícios por tópico** A–I (questionários verificáveis + exercícios tocáveis no detector); `docs/MUSIC.md` §1.2/§1.3 e `AGENTS.md` atualizados; suíte em **217 checagens verdes**, incluindo um teste que impõe ≥5 páginas (`content::minTopicChars`) e ≥3 exercícios por tópico | Fecha o pedido do cliente ("expandir o conteúdo do curso" e "≥3 exercícios por tópico"); painel central passa a ensinar cada assunto de verdade |
| 2026-11-07 | devops | **Correção do CI Linux**: o `ubuntu-latest` migrou e o `juceaide` passou a exigir os módulos `freetype2;fontconfig` no `pkg-config`; o `ci.yml` instalava `libfreetype6-dev` mas não `libfontconfig1-dev`, então o `Configure` falhava ("Package 'fontconfig' not found" → "Failed to build juceaide") em **qualquer** PR (o `ci.yml` só dispara em PR e push em `main`, e nunca havia rodado em PR). Adicionado `libfontconfig1-dev` à lista; PR #1 ficou verde (Linux build + Run tests) | CI de PR volta a funcionar; a falha era de ambiente, não do conteúdo |
| 2026-11-07 | devops | **Instalador de teste republicado (conteúdo completo do Módulo 1)**: PR #1 (base `test`) com CI Linux verde foi mesclada (`--no-ff`, commit `b93b32a`); o push em `test` rodou o `release.yml` (run `43100107104`, success) e um `workflow_dispatch` com `commit_installer=true` (run `43100645706`, success) commitou o instalador (commit `e94af76`, 2.062.802 bytes, PE32 `0x14c`, sha256 `8155e23a…`), byte-a-byte idêntico ao artifact `Instalador-CursoMusica-1`; backup `backup/pre-modulo1-conteudo-test` em `519fb91` criado antes do push (regra §11) | Versão de teste com o conteúdo completo dos tópicos A–I e os 29 exercícios disponível na branch `test` (REQ-013); `main` intocado |
| 2026-11-13 | musician + developer + ux-ui-designer | **Diagramas do curso como imagens embutidas e IDs de exercício por tópico (pedido do cliente)**: o material gráfico (braço, formas CAGED, teclado, ciclo das quintas, figuras rítmicas) deixou de ser arte textual e virou **19 diagramas JPG** desenhados por `tools/make_diagrams.py` com a paleta de `Theme.h`, embutidos no binário via `juce_add_binary_data` (target `CursoMusicaDiagrams`, acessor core-only `Source/Course/Content/Diagrams.*`); o `ContentView` decodifica cada JPEG uma vez (cache) e o desenha com legenda, com caixa "Diagrama indisponível" quando o recurso falta. Os exercícios passaram do formato `EX-1.<n>` para **`EX-1.<tópico>.<n>`** (EX-1.A.1 … EX-1.I.3, 29 + gate), numerados por tópico, com `docs/MUSIC.md` e o registro de IDs atualizados. Suíte em **295 checagens verdes** (valida que todo diagrama citado existe no binário e que os IDs seguem o formato por tópico); app validado sob Xvfb (1040×680) com o diagrama do braço renderizado no painel central | Fecha o pedido do cliente de mostrar o material gráfico como imagem (não texto) e de dar IDs de exercício que identifiquem módulo e tópico |
| 2026-11-13 | devops | **Instalador de teste republicado (diagramas e IDs por tópico)**: backup `backup/pre-diagramas-ids-test` em `dd282d9` (regra §11); `main` já era ancestral do branch (sem merge a fazer); PR #2 (base `test`, `feat/diagramas-e-ids`) com CI Linux verde foi mesclada (`--no-ff`, commit `a3f55c3`); o push em `test` rodou o `release.yml` (run `43471474448`, success) e um `workflow_dispatch` com `commit_installer=true` (run `43472197804`, success) commitou o instalador (commit `89b0498`, 3.154.601 bytes, PE32 `0x14c`, sha256 `9e955335…`) | Versão de teste com os diagramas embutidos e os IDs `EX-1.<tópico>.<n>` disponível na branch `test` (REQ-013); `main` intocado |
| 2026-11-13 | architect + data-engineer + security-engineer | **Persistência de progresso em PostgreSQL (ADR 0006)**: `ProgressStore` passa a espelhar o progresso (offline-first) numa thread dedicada, porta 5432 e schema `curso-musica` por padrão; novo `Source/Data/ProgressDatabase.*` com `PQconnectdbParams` (senha fora de logs) e schema/DDL idempotentes com identificador escapado; libpq é dependência opcional de build (`find_package(PostgreSQL)`) e o banco é opcional em execução; CI sobe um Postgres 17 e roda o teste de integração; suíte em **320 checagens verdes** | Progresso do aluno deixa de existir só na máquina local; credenciais ficam no ambiente e a thread de áudio segue sem I/O (§1) |
| 2026-11-13 | architect + data-engineer + devops | **Suporte explícito ao PostgreSQL 18 e caminho de configuração**: o app não fixa versão de servidor (usa libpq; CI já compilou com 18.6); `find_package(PostgreSQL)` ganhou `CURSOMUSICA_REQUIRE_POSTGRES` (falha o build se faltar, em vez de cair para local) e o guia aponta `PostgreSQL_ROOT` para `C:/Program Files/PostgreSQL/18`; novo `tools/setup_postgres.sh` (idempotente, agnóstico de versão) cria papel/banco/schema e novo `docs/POSTGRESQL.md` (setup Windows/Linux, `libpq.dll`, troubleshooting) | Usuário com PostgreSQL 18 passa a ligar o espelhamento sem tocar no código; build sem banco continua válido |
| 2026-11-14 | designer + developer + devops | **Ícone do sistema a partir do `ico.jpg` da `main` (pedido do cliente)**: o `ico.jpg` (631×648, commit `602c6c5`) virou `Assets/AppIcon.png` (quadrado 512×512, fundo `#1b1523` casando com o tema) e `Assets/AppIcon.ico` (16/24/32/48/64/128/256) por `tools/make_app_icon.py`; o CMake passou `ICON_BIG` ao `juce_add_gui_app` (JUCE gera o `.ico` do executável) e embutiu o PNG via `juce_add_binary_data` (target `CursoMusicaBranding`); `Main.cpp` chama `setIcon(...)` (logo também em builds Linux/dev) e o `installer.nsi` usa o `.ico` no instalador, no desinstalador e nos atalhos | Janela, taskbar, atalhos e instalador passam a mostrar a marca do curso; build Linux validado (app abre sob Xvfb) e o `.ico` do executável é gerado no CI Windows da `test` |
| 2026-11-14 | data-engineer + developer + musician | **Última percentagem de acertos por exercício (pedido do cliente)**: reabrir um exercício já realizado mostra o resultado da **última** tentativa. Nova tabela `exercise_result` (migração v5, `docs/DATA.md`; `UPSERT` por aluno+exercício grava a última, não a melhor) e chave local `exercise/<id>` no `ProgressStore` (offline-first, mesma disciplina do ADR 0006: espelho em thread dedicada, leitura na UI só do mapa local); `PracticePanel` ganhou `onExerciseResult`/`onQueryExerciseAccuracy` e `previousAccuracy`, exibido no placar do exercício tocável **e** do questionário; `finishExercise()` passa a publicar o veredito (antes o `updateFeedback()` não era chamado no fim) | Aluno vê "Último aproveitamento NN%" ao retomar o exercício; suíte em **333 checagens verdes** (315 offline) |
| 2026-11-15 | devops + developer | **Instalador Windows empacota a `libpq.dll` (ADR 0008, correção de REQ-014)**: o `.exe` é linkado contra `libpq` (ADR 0006) e o instalador não embutia a DLL, então numa máquina sem PostgreSQL o app abria com **"LIBPQ.dll não foi encontrado"**. Novo `cmake/StageWindowsRuntime.cmake` roda como `POST_BUILD` do alvo (só em `WIN32` e com `PostgreSQL_FOUND`) e usa `file(GET_RUNTIME_DEPENDENCIES)` para copiar `libpq.dll` e o fecho transitivo (OpenSSL etc.) em `build/runtime`, excluindo o que é do sistema; `installer.nsi` já copia esse diretório com `-DRUNTIME`. O script **falha o build** se a `libpq.dll` não for resolvida, e o `release.yml` confere `build/runtime/libpq.dll` antes do `makensis` | Instalador de teste passa a sair pronto para uso numa máquina limpa; `docs/POSTGRESQL.md` §5 deixa de listar a pendência; suíte em **338 checagens verdes** |
| 2026-11-14 | developer + qa | **Correção do grid de pastas VST3 (REQ-024): seleção de linha e "Remover"** — as linhas do grid são componentes customizados (rótulo + botão `…`) e interceptavam o clique, então `list.getSelectedRow()` nunca mudava e **"Remover" não fazia nada**; a `Row` agora usa `setInterceptsMouseClicks (false, true)`, deixando o `ListBox` tratar o clique na linha e mantendo o botão `…` clicável. Verificação sob Xvfb por OCR: adicionar pasta grava `vst3SearchPaths`; **remover zera a chave**; o botão `…` por linha abre o seletor; a lista recarrega após reiniciar; e a cadeia de **canal único** de áudio está intacta (`inputChannelData[0]` → `pluginChain.process` → meter/análise, `AudioEngine.cpp`). Suíte em **338 checagens verdes** | Remover pasta passa a funcionar e a seleção de linha responde; sem pasta configurada o scan segue usando só os locais padrão |
| 2026-11-14 | architect + developer + designer | **Pastas de busca de plugins VST3 configuráveis (REQ-024, ADR 0007, pedido do cliente: "estilo Reaper")**: novo `Source/Audio/PluginSearchPaths.*` (lógica pura: normaliza, recusa vazio/duplicata, cap de 32, serializa, resolve só pastas existentes) e janela `Source/UI/PluginPathsComponent.*` com grid de duas colunas (caminho | botão de seleção), aberta pelo botão "Pastas…" ao lado da tabela de plugins; `PluginHost` soma as pastas do usuário aos locais padrão do VST3 no scan e persiste em `vst3SearchPaths` com flush imediato, podando do cache os plugins fora das pastas (por descendência, `isAChildOf`); corrigida a iteração de `juce::FileSearchPath` (não é iterável — `getNumPaths()`/`getReference(i)`) | Usuário instala VST3 fora do padrão sem mexer no sistema; sem pasta configurada o comportamento é o de antes; suíte em **356 checagens verdes** |
| 2026-11-16 | architect + developer + data-engineer + designer | **Dois bugs do cliente: progresso perdido ao fechar e tópico de outro módulo sem exercícios.** (1) *Progresso perdido:* `ProgressStore`, `TuningSettings` e `PluginHost` abriam **três `PropertiesFile` sobre o mesmo `CursoMusica.settings`**; cada `save` reescreve o mapa inteiro, então a última instância a gravar (o `PluginHost`, no shutdown) apagava as chaves que não tinha carregado — o progresso entre elas. Reproduzido em teste. Correção: instância única compartilhada `Source/Data/AppSettings.*` (referência, não `unique_ptr`), consumida pelos três. (2) *Tópico sem exercícios:* `ModuleComponent::selectTopic`/`showModule` chamavam `PracticePanel::setTopicFilter` **sem antes apontar o painel para o módulo clicado**, então o filtro corria sobre o módulo anterior (o 2 é *placeholder*, sem exercícios) e a lista saía vazia; novo `PracticePanel::setModuleAndTopic(module, lessonId)` fixa módulo+tópico juntos e a filtragem virou a função pura `Course/ExerciseFilter.h` (testável). Bônus do mesmo pedido: o app **não tinha como configurar o banco** (só `PGHOST` do ambiente, que um app aberto pelo menu Iniciar não herda), então o schema `curso-musica` nunca era criado — nova janela **Configurações → Banco de dados…** (`Source/UI/DatabaseSettingsComponent.*`) grava host/porta/usuário/banco/schema no settings (**senha nunca**, vem de `PGPASSWORD`) e tem **Testar conexão**; `PostgresConfig::fromSettings()` passa a ter precedência sobre o ambiente | Progresso sobrevive ao fechamento, tópico lista os exercícios certos e o aluno liga o espelhamento pela UI; suíte em **377 checagens verdes** (359 offline) |
| 2026-11-16 | orquestrador + musician + pm + po + tech-lead + architect + developer + qa + security-engineer + set | **Pipeline de módulos (Etapas) e painel de revisão.** Criados três sub-agentes: `module-author` (transforma uma Etapa de `docs/MUSIC.md` em módulo completo, no padrão do Módulo 2 — teoria ≥5 páginas/tópico, imagens, áudios, partituras com áudio, 3–5 exercícios/tópico, exercícios tocados no instrumento reconhecidos pelo app), `module-reviewer` (painel: Músico, PM, PO, Tech Lead, Arquiteto, Tech Lead, Software Engineers, Tech Lead, QA, Security, SET; qualquer problema volta ao autor e o painel **reinicia do começo**) e `release-reviewer` (revisão final cross-módulo: Arquiteto, Tech Lead, Software Engineers, Tech Lead; merge para `main` + instalador de teste). Um módulo por branch/PR; nenhum módulo aceito sem painel verde na mesma rodada; merge só por PR, sem reescrever histórico, backup antes de todo push (§11) | Todo o curso (Etapas 2–10) passa a ser produzido e revisado pelo mesmo pipeline, com qualidade e padrão verificáveis |
| 2026-11-16 | musician + developer + architect + qa + set | **Módulo 2 (Etapa 2 — Teoria dos intervalos e percepção musical) implementado** como referência do padrão: `Source/Course/Intervals.*` (teoria pura de intervalos), `Source/Audio/TonePlayer.*` (áudio de exemplos, RT-safe, REQ-004), `ContentKind::audio`/`score` no modelo e na UI, `Exercise::interval` + `Exercise::usesGrid` e `evaluateIntervals` (o app reconhece as notas tocadas e confere a distância em semitons, em qualquer posição do braço); 8 tópicos (A–H), cada um com ≥5 páginas, imagens, tabelas, áudios e partitura com áudio; 3–5 exercícios por tópico (EX-2.*), gate `C–F–G–C` a 64 BPM; suíte em **950 checagens verdes** | Módulo 2 jogável e auditável; serve de gabarito para as Etapas seguintes |
| 2026-11-16 | orquestrador + musician + pm + po + tech-lead + architect + developer + qa + security-engineer + set | **16 sub-agentes por Etapa (3–10) criados.** Cada Etapa 3–10 ganhou um **autor** (`mc-modulo-<N>`) e um **revisor** (`mc-rv-modulo-<N>`), já com objetivo, conteúdos, prática, tópicos sugeridos e os dados fixados da Etapa (nível, BPM meta, `on_grid_ratio`, branch). O autor segue o padrão do Módulo 2 (teoria ≥5 páginas/tópico, imagens, áudios, partituras com áudio, 3–5 exercícios/tópico, exercícios tocados reconhecidos pelo app) numa branch própria; o revisor roda o painel completo (Músico, PM, PO, Tech Lead, Arquiteto, Tech Lead, Software Engineers, Tech Lead, QA, Security, SET) e qualquer achado devolve o item ao autor, reiniciando o painel até todos passarem. As Etapas 3–10 são construídas **em paralelo**; a asserção final de `testModule2()` ("3..20 são placeholders") passa a ser uma regra genérica para as branches não conflitarem | As Etapas 3–10 passam a ser produzidas e revisadas em paralelo pelo mesmo pipeline verificável do Módulo 2 |


| 2026-11-15 | mc-modulo-8 (module-author) | **Módulo 8 (Etapa 8 — Dominantes, cadências e substituições harmônicas) implementado** no padrão do Módulo 2 (branch `feat/modulo-8-dominantes-cadencias-e-substituicoes-harmonicas`): 10 tópicos A–J em `Source/Course/Content/Topic8A.cpp`…`Topic8J.cpp`, cada um com ≥5 páginas, imagens, tabelas e áudios (e partituras com o seu áudio em D/F/G/I/J); `makeModule8()` em `ModuleCatalog.cpp` com **40 exercícios** (`EX-8.<tópico>.<n>`, 4 por tópico A–J: questionários, montagem de acordes com `chordPitchClasses`, progressões com `chordProgression`, arpejo com `targets` e um exercício de intervalo) mais o gate `GATE-8` (`isGate`, II-V-I maior Dm7–G7–CM7 na grade a 88 BPM, `onGridTarget` 0,81) e os links de prática (pattern `PTN-A-DROP2`, Joe Pass/Wes Montgomery/Pat Metheny) e fontes curadas; 16 diagramas `m8_*` gerados por `tools/make_diagrams.py` e embutidos via `juce_add_binary_data` (19 após a correção do painel); `testModule8()` adicionado a `tests/TestMain.cpp` e a asserção final de `testModule2()` trocada por uma regra genérica (números únicos, `findModule(N)` devolve o módulo) para não conflitar com as Etapas 3–10 em paralelo. Suíte em **1882 checagens verdes** (inclui a verificação de que cada partitura toca exatamente o que escreve); app e testes compilam sem avisos novos no Linux | Aluno aprende dominantes, substituições e cadências (SubV7, SubIIm, empréstimos modais, II-V-I maior/menor) e o Módulo 9 desbloqueia ao atingir ≥90% no gate; PR contra `test` aberto para o painel de revisão |
| 2026-11-16 | mc-modulo-8 (module-author) | **Correção dos achados do painel do Módulo 8 (rodada 1)**: música — V7/V de Fá maior e a linha de Si bemol maior na tabela de dominantes secundários (`Topic8B.cpp`), cadeia E7→A7→D7→G7→C rotulada corretamente (V7/vi, V7/ii, V7/V, V7, I); áudio do trítono do G7 passou de Sol–Fá (7ª menor) para **Si–Fá** (`Topic8A.cpp`); áudio do Cm corrigido para **Cm6, Cm7M e Cm7** de verdade (`Topic8H.cpp`); SubV7 descrito como **trítono** e não semitom (`Topic8D.cpp`); a partitura de 8F (iv menor) ganhou o seu próprio diagrama `m8_partitura_iv_menor` (FM7–Fm7–C) casando imagem e áudio; QA — `testModule8()` agora **fixa as notas esperadas de cada partitura** (comparadas por classe de altura) e falha se o áudio divergir da imagem; corrigido o número da suíte no registro (**1882**) e as referências de fonte de verdade dos `Topic8*.cpp`; imagens duplicadas em 8C/8I ganharam diagramas próprios (`m8_alteracoes_tensao`, `m8_ii_v_i_substituicoes`). Suíte em **1882 checagens verdes** | Conteúdo musical do Módulo 8 verificado pelo painel; partitura e áudio passam a ser conferidos automaticamente |

## 8. Convenções de código

- Headers com `#pragma once`; prefixo `juce::` sempre explícito.
- Membros privados sem prefixo; parâmetros com nomes descritivos.
- Comentários só quando explicam algo não óbvio (invariante, workaround,
  requisito de tempo real). Não narrar o código.
- JUCE 8: usar `juce::FontOptions` (construtor antigo de `juce::Font` é
  depreciado).
- Real-time safety: no `Source/Audio/` nada de alocação, lock ou I/O no callback.

## 9. Comandos úteis

```bash
# Configurar e compilar (Linux, validação)
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build

# No Windows (Visual Studio)
cmake -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
```

## 10. Pendências e armadilhas conhecidas

- O ASIO SDK **não** acompanha o JUCE; não existe `JUCE_ASIO_SDK_PATH`. O CMake
  detecta em `ASIO_SDK_DIR`, `External/asio` ou variável de ambiente. Guia:
  `docs/ASIO-Windows.md`.
- Este ambiente Linux não tem dispositivo de áudio; validação aqui é só de
  compilação. Teste de latência real só no Windows.
- Plugins com mais de 8 entradas na cadeia são rejeitados (`PluginChain::maxPlugins`).
- A varredura de VST3 grava a lista em `CursoMusica.settings` (segundo launch
  não rescaneia).
- O ambiente de build pode reiniciar entre sessões: se `cmake` sumir, reinstale
  `cmake ninja-build pkg-config` e as libs de desenvolvimento do JUCE.

## 11. Disciplina de branches, backup e push (regra do usuário)

Pode-se criar quantas branches forem necessárias, mas **antes de qualquer push**:

1. **Backup da versão anterior.** Crie uma branch de backup apontando para o
   estado atual (`git branch backup/<nome> <sha>` ou `git tag backup-<nome>`)
   **antes** de reescrever história ou publicar.
2. **Merge antes do push.** Traga a linha principal (`main`/integração) para a
   branch de trabalho (`git merge`) e resolva conflitos **localmente**; só então
   publique. Nada é enviado sem ter passado pelo merge.
3. **Nunca reescrever história já publicada.** Se o push exigir força, pare e
   alinhe com o usuário.
4. **PR, não push direto.** A entrega vai por pull request com CI verde e
   revisão; `main` não recebe push direto.
