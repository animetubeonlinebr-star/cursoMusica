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
> software. Requisitos rastreáveis: `docs/REQUIREMENTS.md` (REQ-001..REQ-014).

> **Nota de branch.** O código do aplicativo JUCE está hoje em
> `feature/juce-audio-app` (ainda não mesclado em `main`). O mapa de
> propriedade da seção 3 descreve o projeto-alvo: quando essa branch for
> mesclada, os donos passam a valer diretamente. Enquanto isso, trabalhe na
> branch do app para código e nesta branch para o framework de agentes.

- [x] Estrutura CMake e dependência JUCE
- [x] Engine de áudio em tempo real (callback mínimo, FIFO lock-free)
- [x] Detecção de pitch (YIN) em thread de análise dedicada
- [x] Agente de design (`designer.md`) e design system (`Theme.h`, `DESIGN.md`)
- [x] Telas iniciais (layout, sem funcionalidade de estudo)
- [x] Menu de configuração: dispositivos, entrada, saída, buffer
- [x] Host VST3 com scan, cadeia na entrada e editor de plugin
- [x] Build validada no Linux: binário gerado, UI renderiza
- [ ] Ligar UI principal à engine (nível e afinação reais em vez de dummy)
- [ ] Playback com controle de velocidade e loop
- [ ] ASIO SDK no Windows (licença Steinberg, download separado)
- [ ] Empacotamento / instalador

## 3. Mapa de propriedade de arquivos (contrato de escrita)

Cada caminho tem **um único dono**. Nenhum agente escreve fora do seu escopo;
quando precisa, ele **pede** ao dono (ver protocolo de handoff, seção 5).

| Caminho | Dono | Quem pode ler |
|---|---|---|
| `Source/Audio/**` | `developer` (linha de áudio) | todos |
| `Source/UI/**` | `designer` | todos |
| `CMakeLists.txt`, `Source/Main.cpp` | `architect` | todos |
| `Source/Data/**`, `tools/etl/**` | `data-engineer` | todos |
| `.github/workflows/**`, `Dockerfile*`, `deploy/**` | `devops` | todos |
| `docs/ROADMAP.md`, `docs/REQUIREMENTS.md` | `pm` | todos |
| `docs/MUSIC.md` | `musician` (co-own com `pm`) | todos |
| `docs/BACKLOG.md`, `docs/stories/**` | `po` | todos |
| `docs/PLAN.md`, `docs/STATUS.md`, `docs/RISKS.md` | `project-manager` | todos |
| `tests/**`, `docs/QA.md` | `qa` | todos |
| `AGENTS.md` | todos (append em "Registro de decisões") | todos |

Regra dura herdada do designer: quem não é dono de `Source/Audio/` ou
`CMakeLists.txt` **não edita** esses arquivos. Quem precisa de um arquivo novo no
build entrega a linha exata de `target_sources` ao dono.

## 4. Divisão de responsabilidade entre agentes

| Agente | Arquivo | Dono de | Pergunta que responde |
|---|---|---|---|
| Product Manager | `.agents/agents/pm.md` | `docs/ROADMAP.md`, `docs/REQUIREMENTS.md`, KPIs | **Por quê / O quê** (macro) |
| Músico Profissional | `.agents/agents/musician.md` | `docs/MUSIC.md` (co-own com PM) | **Está musicalmente correto?** |
| Product Owner | `.agents/agents/po.md` | `docs/BACKLOG.md`, histórias | **O quê** (detalhe, critérios de aceite) |
| Arquiteto de Software | `.agents/agents/architect.md` | `CMakeLists.txt`, `Source/Main.cpp`, decisões técnicas | **Como estruturar** |
| Data Engineer | `.agents/agents/data-engineer.md` | `Source/Data/**`, `tools/etl/**` | **Dados: capturar, limpar, governar** |
| Project Manager | `.agents/agents/project-manager.md` | `docs/PLAN.md`, `docs/STATUS.md`, `docs/RISKS.md` | **Prazo, custo, risco** |
| Desenvolvedor | `.agents/agents/developer.md` | `Source/Audio/**` (e código geral) | **Construir** |
| QA Engineer | `.agents/agents/qa.md` | `tests/**`, `docs/QA.md` | **Prevenir falhas** |
| DevOps | `.agents/agents/devops.md` | `.github/workflows/**`, infra | **Entregar automatizado** |
| Designer | `.agents/agents/designer.md` | `Source/UI/**` | **Como se vê e se sente** |

## 5. Protocolo de handoff (como os agentes conversam)

O trabalho flui em uma esteira. Cada etapa tem **entrada**, **saída** e um
**artefato verificável** que destrava a próxima.

```
PM + Músico (ROADMAP + MUSIC: o quê, musicalmente correto, KPIs)
   └─> PO (BACKLOG, histórias + critérios de aceite)
          └─> Arquiteto (decisões técnicas, ADR, esqueleto de build)
                 └─> Developer / Data Engineer / Designer (código)
                        └─> QA (testes, regressão, carga)
                               └─> DevOps (CI/CD, deploy, observabilidade)
   Project Manager observa tudo: prazo, custo, risco, capacidade.
```

Regras do handoff:

1. **Nada entra em desenvolvimento sem critérios de aceite** escritos pelo PO.
2. **Nada com dimensão musical entra sem revisão do músico** — o PM e o músico
   ajustam o requisito juntos; a verdade musical fica em `docs/MUSIC.md`.
3. **Nada entra em build sem decisão de arquitetura** quando toca estrutura,
   dependência ou contrato entre módulos.
4. **Nada é considerado pronto sem evidência** (teste, build, log) anexada pelo
   QA/DevOps.
5. Ao terminar uma etapa, o agente **escreve o artefato no seu arquivo** e
   **adiciona uma linha no Registro de decisões** (seção 7) com: data, agente,
   decisão, impacto.
6. Conflito de escopo se resolve **a favor do dono do arquivo**; quem discorda
   abre uma nota em `docs/RISKS.md` (dono: Project Manager).

### Formato de uma história de usuário (padrão do PO)

```
Como um [tipo de usuário], eu quero [fazer algo] para que eu possa [benefício].

Critérios de aceite:
- Dado [contexto], quando [ação], então [resultado esperado].
- ...

Pronto quando (DoD):
- [ ] Código revisado via PR
- [ ] Teste automatizado verde no CI
- [ ] Build sem avisos novos
- [ ] Documentação/memória atualizada
```

## 6. Definição de pronto (DoD) do projeto

Uma entrega só é "pronta" quando:

- [ ] Atende aos critérios de aceite do PO (evidência anexada).
- [ ] Passa no build (`cmake --build build`) sem avisos novos.
- [ ] Tem teste automatizado (quando houver lógica testável).
- [ ] Passou por `code review` de outro agente (PR).
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
