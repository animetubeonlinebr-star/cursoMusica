# REQUIREMENTS — CursoMusica

Dono: **business-analyst** (elicitação e IDs) em conjunto com o **pm**
(requisitos de produto) e o **musician** (requisitos musicais). Cada requisito
tem um ID estável e rastreável: o PO cria histórias a partir daqui, o QA valida
contra a coluna de verificação, o arquiteto decide a implementação.

Legenda: **MoSCoW** = Must / Should / Could / Won't (nesta fase).

## Visão de produto (o que mudou)

O CursoMusica deixa de ser apenas um afinador/medidor e passa a ser uma
**plataforma de estudo de guitarra modular**, que ensina, demonstra com áudio,
gera desafios, mede o desempenho do aluno e **avalia improvisação**. O aluno
faz tudo dentro do software, sem arquivos externos.

## A. Áudio e reconhecimento

| ID | Requisito | MoSCoW | Verificação |
|---|---|---|---|
| REQ-001 | O sistema reconhece o áudio enviado via interface de áudio (entrada real) | Must | sinal sintético/conhecido → leitura correta de nível e afinação |
| REQ-002 | O sistema roda os modelos em **progressão linear** com **progressão baseada em níveis** | Must | módulo N só libera após o gate de N-1; trilha linear auditável |

## B. Ensino, demonstração e áudio

| ID | Requisito | MoSCoW | Verificação |
|---|---|---|---|
| REQ-003 | Antes dos desafios, o sistema **explica o módulo** | Must | todo módulo tem seção de explicação antes do primeiro desafio |
| REQ-004 | Todo exemplo é **demonstrado com áudio**; qualquer partitura é **convertida para áudio** | Must | toda partitura no app tem áudio correspondente; A/B confere |
| REQ-005 | O aluno faz **tudo dentro do software**, sem arquivos externos para estudo | Must | nenhuma tela exige abrir PDF/arquivo externo |
| REQ-006 | Antes de construir um módulo, as **apostilas são revisadas** e o que se enquadra no módulo é incluído | Must | checklist de curadoria por módulo (fonte → conteúdo) |
| REQ-007 | Antes de construir um módulo, **links e patterns de guitarristas específicos** podem ser acrescentados | Must | cada módulo cita ≥1 link e ≥1 pattern de guitarrista |

**Guitarristas de referência (REQ-007):** John Petrucci, Guthrie Govan, Richie
Kotzen, Greg Howe, Steve Vai, Joe Satriani, Juninho Afram, Edu Ardanuy, Kiko
Loureiro.

## C. Desafios e progressão

| ID | Requisito | MoSCoW | Verificação |
|---|---|---|---|
| REQ-008 | O sistema cria **desafios em todos os módulos** | Must | todo módulo tem ≥1 desafio jogável |
| REQ-009 | **Todo processo é mensurado**; o aluno precisa de **≥90% de acerto** para passar ao próximo módulo | Must | métrica por desafio/módulo; gate bloqueia < 90% |
| REQ-010 | No ensino de improvisação, cada tópico ensina **≥1 link e ≥1 pattern**, e verifica-se **se foram usados** | Must | o módulo registra link+pattern e a avaliação detecta o uso |

## D. Improvisação (avaliação musical)

| ID | Requisito | MoSCoW | Verificação |
|---|---|---|---|
| REQ-011 | O sistema identifica **notas de repouso** para saber quando o aluno erra na improvisação | Must | dado contexto harmônico, classifica nota como repouso/tensão |
| REQ-012 | **Notas de tensão** só são aceitas se o **estado de improviso pedir** o seu uso; qualquer tensão não solicitada é erro, **a menos que faça parte do acorde** | Must | a avaliação rejeita tensão fora de contexto e aceita quando solicitada ou quando a nota pertence ao acorde |

## D2. Metrônomo com meta de andamento

| ID | Requisito | MoSCoW | Verificação |
|---|---|---|---|
| REQ-015 | O sistema usa **metrônomo para praticar**; estipula um **valor meta** (BPM alvo) e, **se o aluno não o atingir, não avança** nos módulos | Must | BPM alvo por desafio; abaixo da meta → módulo não libera |

## D3. Catálogo de patterns

| ID | Requisito | MoSCoW | Verificação |
|---|---|---|---|
| REQ-016 | O sistema deve oferecer o **catálogo de patterns** (melódicos, rítmicos e de arpejo) com IDs estáveis, aplicáveis por módulo e verificáveis | Must | cada pattern do catálogo é citável por um módulo e detectável pela avaliação |

Catálogo detalhado (IDs `PTN-*`) em `docs/MUSIC.md` §"Catálogo de patterns".

## D4. Afinador transversal

| ID | Requisito | MoSCoW | Verificação |
|---|---|---|---|
| REQ-017 | O sistema oferece um **afinador como ferramenta transversal**, acessível a qualquer momento por um menu próprio, **fora de qualquer módulo**; a janela permite **selecionar o pitch de referência (A4)**, padrão **440 Hz**, editável e persistido | Must | afinador abre em qualquer momento, sem módulo ativo; valor de A4 editável de 400 a 480 Hz e mantido entre sessões |

## D5. Apresentação dos módulos no app

| ID | Requisito | MoSCoW | Verificação |
|---|---|---|---|
| REQ-018 | O sistema apresenta os **módulos do curso dentro do software** (lista navegável + conteúdo do módulo), com a **explicação antes de qualquer desafio** (REQ-003); o conteúdo é espelho de `docs/MUSIC.md` | Must | módulo abre com os blocos de explicação na ordem; nenhum desafio antes da explicação |

## E. Modelos progressivos de improvisação (REQ-002, REQ-010)

Ordem obrigatória (progressão linear):

1. Vamps de 1 acorde — **estatismo modal**
2. Vamps de 2 acordes — **movimento modal interno**
3. A célula fundamental: **II–V–I**
4. **Turnarounds** — ciclos harmônicos repetitivos
5. **Blues** — 12 compassos
6. **Standards / standard forms com mudança de tom** (modulação)
7. **Uso de músicas** (repertório real)

**Repertório (REQ-012/repertório):**

| Música | Compositor / referência |
|---|---|
| Equinox | John Coltrane |
| Cantaloupe Island | Herbie Hancock |
| Incompatibilidade de Gênios | João Bosco |
| 500 Miles High | Chick Corea / Return to Forever |
| Maiden Voyage | Herbie Hancock |
| Só Danço Samba | Tom Jobim & Vinicius de Moraes (João Gilberto, Os Cariocas) |
| Spain | Chick Corea / Return to Forever |

> **Nota de direitos autorais (musician + pm):** as músicas são usadas como
> *progressões/estudo* (acordes e escalas), não como gravação. Não distribuir
> áudio ou partitura protegida sem licença; ver `docs/RISKS.md` R-08.

## F. Stack técnica de partitura/MIDI/áudio (proposta pelo requisito)

| Componente | Biblioteca | Função no sistema |
|---|---|---|
| Parser de partitura | **pugixml** ou **TinyXML2** | ler a estrutura XML da partitura |
| Manipulação MIDI | **midifile** (Craig Sapp) | criar e estruturar eventos MIDI |
| Motor de áudio / síntese | **FluidSynth** ou **RtAudio** | fluxo de saída de som e placas de áudio |
| Leitura de samples | **libsndfile** | carregar `.wav` de instrumentos |

Isso convive com o que já existe (JUCE 8 + engine própria, `Source/Audio/`).
A decisão de arquitetura (incluindo o trade-off latência × síntese) fica no
**ADR 0002** (`docs/adr/0002-score-midi-audio-stack.md`).

## G. Distribuição / validação (REQ-013, REQ-014)

| ID | Requisito | MoSCoW | Verificação |
|---|---|---|---|
| REQ-013 | Para **cada módulo criado**, liberar na **branch de teste** um **instalador com acesso liberado sem restrição** (sem precisar liberar os módulos anteriores) | Must | artefato de instalador anexado ao release da branch de teste; override de acesso ativo |
| REQ-014 | Deve haver um **instalador para Windows**: ao executá-lo, o usuário **seleciona o local de instalação** e o sistema fica **pronto para uso** | Must | instalar em `C:\...` e em `D:\...`; app abre e reconhece áudio sem passos manuais |

**Detalhe de REQ-014:** instalador único `.exe` (NSIS ou Inno Setup), com:

- tela de seleção de diretório de instalação (padrão em `%ProgramFiles%`, com
  opção de mudar);
- criação de atalhos (menu iniciar e desktop);
- inclusão das dependências de runtime (JUCE, SoundFont/samples, DLLs das
  bibliotecas do ADR 0002) para o app abrir "pronto para uso";
- desinstalador que remove o que instalou;
- assinatura de código (quando houver certificado) para evitar aviso do Windows.

## H. Ajustes solicitados pelo cliente (fonte: `docs/inbox/musica.docx`)

Fonte: `docs/inbox/musica.docx` (solicitação do usuário/cliente, 2026-11-04).
Elicitação: **business-analyst**, com revisão do **musician** (dimensão musical)
e do **ux-researcher** (jornada). Requisitos de produto (necessidade), não de
solução.

| ID | Requisito | MoSCoW | Verificação |
|---|---|---|---|
| REQ-019 | Ao abrir um módulo, a área de conteúdo inicia **em branco** (apenas o contexto do módulo), sem carregar automaticamente o conteúdo de nenhum tópico; o conteúdo só aparece quando o aluno **clica em um tópico** | Must | abrir módulo → conteúdo do tópico **não** exibido; clicar tópico → exibido |
| REQ-020 | O sistema **mantém o conteúdo do tópico carregado** ao retornar ao mesmo módulo; mas, se o aluno abrir **outro módulo**, a área de conteúdo volta a ficar **em branco** | Must | módulo A→tópico→módulo A mantém; módulo A→tópico→módulo B → B em branco |
| REQ-021 | No estudo prático, o **painel central** demonstra o **exercício executável** (o questionário com a questão e as opções clicáveis) e o **painel lateral (direito)** apresenta apenas os **controles** (seletor, botão de play, placar e a caixa de orientação "Neste exercício…"), sem repetir a questão | Must | painel central = exercício (questão + opções); painel direito = controles, placar e orientação |
| REQ-022 | O sistema oferece **≥1 exercício por tópico** do módulo, cobrindo o assunto daquele tópico, para o aluno praticar (não apenas o questionário) | Must | todo tópico tem ≥1 exercício executável próprio |
| REQ-023 | A **lista de dispositivos de áudio** classifica cada porta na categoria correta: **entradas de captura** em *inputs* e **saídas de reprodução** em *outputs* (hoje o VoiceMeeter Banana aparece invertido) | Must | com VoiceMeeter Banana instalado, entradas em Input e saídas em Output |
| REQ-024 | O aluno pode **configurar as pastas onde o app procura plugins VST3** numa janela própria ("Pastas de plugins VST3"), aberta por um botão ao lado da tabela de plugins nas Configurações; a varredura passa a procurar nessas pastas **além** dos locais padrão do sistema, e a lista é lembrada entre execuções | Should | Configurações → "Pastas…" → adicionar/remover pasta → varrer e o plugin da pasta aparece; reabrir o app mantém a lista |

**Nota de elicitação (BA).** O item de "módulo sem conteúdo" é um problema de
*jornada/UX*, não de dados: o catálogo tem conteúdo, mas o app o carrega no
abrir. O item do VoiceMeeter é um **bug de classificação** de portas: o
`juce::AudioDeviceSelectorComponent` deriva os rótulos das flags de canal do
driver e, para o driver ASIO virtual do VoiceMeeter, a convenção de captura/
reprodução fica invertida. **Vetor técnico:** usar
`AudioIODevice::getInputChannelNames()` / `getOutputChannelNames()` e o
`AudioIODeviceType` correto para rotular, em vez de confiar no nome bruto do
canal — investigar com o VoiceMeeter instalado (Windows).

**Escopo musical (musician).** REQ-022 exige que o **musician + PM + BA**
pesquisem e criem os exercícios de cada tópico — é trabalho de curadoria de
conteúdo (REQ-006), não só de código.

## Matriz de rastreabilidade

| Requisito | Agente responsável | Artefato | Estado |
|---|---|---|---|
| REQ-001 | developer | `Source/Audio/` | existe (engine), falta ligar à UI |
| REQ-002 | architect + pm | ADR + `docs/DATA.md` | decisão pendente |
| REQ-003 | musician + designer | módulos | pendente |
| REQ-004 | architect + musician | ADR 0002 | pendente |
| REQ-005 | designer + pm | UI | pendente |
| REQ-006 | musician + pm | curadoria por módulo | pendente |
| REQ-007 | musician | `docs/MUSIC.md` | pendente |
| REQ-008 | po + developer | módulos | pendente |
| REQ-009 | data-engineer + qa | `docs/DATA.md` | pendente |
| REQ-010 | musician + qa | `docs/MUSIC.md` | pendente |
| REQ-011 | musician + developer | `docs/MUSIC.md` | pendente |
| REQ-012 | musician + developer | `docs/MUSIC.md` | pendente |
| REQ-013 | devops | `.github/workflows/` | pendente |
| REQ-014 | devops | instalador Windows | pendente |
| REQ-015 | musician + developer + data-engineer | ADR 0004 | pendente |
| REQ-016 | musician | `docs/MUSIC.md` | catalogado (IDs PTN-*) |
| REQ-017 | developer + designer | `Source/UI/TunerComponent.*`, `Source/Audio/TuningSettings.*` | **implementado** |
| REQ-018 | developer + designer + musician | `Source/Course/**`, `Source/UI/ModuleComponent.*`, ADR 0005 | **implementado (Módulo 1)** |
| REQ-019 | developer + ux-ui-designer | `Source/UI/ModuleComponent.*` | **implementado** |
| REQ-020 | developer | `Source/UI/ModuleComponent.*` | **implementado** |
| REQ-021 | developer + ux-ui-designer | `Source/UI/PracticePanel.*`, `Source/UI/ModuleComponent.*` | **implementado** |
| REQ-022 | musician + pm + business-analyst + developer | `Source/Course/ModuleCatalog.cpp` | **implementado (Módulo 1)** |
| REQ-023 | developer + security-engineer | `Source/Audio/AudioPortClassifier.*`, `Source/UI/AudioPortsPanel.*`, `Source/UI/SettingsComponent.*` | **implementado** (validar no Windows com VoiceMeeter) |
| REQ-024 | developer + designer | `Source/Audio/PluginSearchPaths.*`, `Source/Audio/PluginHost.*`, `Source/UI/PluginPathsComponent.*`, `Source/UI/SettingsComponent.*` | **implementado** |

**Detalhe de REQ-018:** o sistema apresenta os **módulos do curso** dentro do
software, com a **explicação antes de qualquer desafio** (REQ-003) e a lista de
módulos navegável. O conteúdo vive no catálogo compilado (ADR 0005) e é espelho
de `docs/MUSIC.md`. Módulos ainda sem conteúdo aparecem como bloqueados, não
como ausentes.
