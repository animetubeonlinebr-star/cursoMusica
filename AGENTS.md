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
- [x] Módulo 1 jogável no app: explicação A–I (inclui rítmica), CAGED, trilha de prática, exercícios EX-1.1–EX-1.8 e gate (REQ-003/REQ-007/REQ-018); apostilas curadas citadas (REQ-006)
- [x] Execução por seleção de tópico: menu de módulos expansível, explicação detalhada do tópico no centro e prática filtrada à direita (REQ-003/REQ-008)
- [x] Questionário do Módulo 1 (7 questões, uma por tela) e QuizSession com gate de 90% (REQ-006)
- [x] Motor de medição: NoteMath, ExerciseEvaluator (LCS + acordes), TempoGrid, PracticeSession (CM-008)
- [x] Metrônomo RT-safe com BPM meta e grade (CM-014)
- [x] Gate de progressão linear: módulo N+1 só abre com ≥90% no gate de N; progresso persistido (REQ-002/REQ-009)
- [x] Testes unitários da lógica pura (146 checagens) rodando no CI
- [x] Build validada no Linux: binário gerado, UI renderiza
- [ ] Ligar UI principal à engine (nível e afinação reais em vez de dummy)
- [x] Ajustes do `musica.docx` (CM-018..CM-021): módulo abre em branco e mantém o tópico no mesmo módulo (REQ-019/020), exercício à direita e explicação no centro (REQ-021), ≥1 exercício por tópico A–I (REQ-022), classificação correta de entradas/saídas de áudio (REQ-023)
- [ ] Playback com controle de velocidade e loop
- [ ] Avaliação de improvisação (repouso × tensão, REQ-010/REQ-011/REQ-012)
- [ ] ASIO SDK no Windows (licença Steinberg, download separado)
- [x] Empacotamento / instalador: `instalador/Instalador CursoMusica.exe` (PE32) publicado na branch `test` pelo `release.yml` (`windows-2022`, `TEST_UNLOCK_ALL=ON`); instala escolhendo o diretório (CM-010/CM-013)

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
