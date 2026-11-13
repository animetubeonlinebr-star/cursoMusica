# BACKLOG — CursoMusica

Dono: **po**. Ordenado por valor (impacto no aluno × impacto no negócio).
Histórias em detalhe ficam em `docs/stories/` quando crescerem; aqui fica o
índice priorizado.

Deriva de `docs/ROADMAP.md` e `docs/REQUIREMENTS.md`. Formato de história e DoD:
`AGENTS.md` §5 e §6. Critérios musicais (referência de afinação, tolerância em
cents, alcance de detecção, tempo) derivam de `docs/MUSIC.md` (dono: `musician`).
Cada história cita o(s) requisito(s) que atende.

## Pronto para desenvolvimento (topo)

### [CM-018] Módulo abre em branco; conteúdo só ao clicar no tópico — valor: H — tamanho: S — status: **done** (merge `3603ee6`)
Requisito: REQ-019, REQ-020.
Como um aluno de guitarra, eu quero que a área de conteúdo fique em branco ao
abrir um módulo e mostre o conteúdo só quando eu clicar num tópico, para que eu
escolha consciente o que estudar em vez de receber conteúdo automático.

Critérios de aceite:
- Dado o app aberto, quando clico em **Módulos** e seleciono um módulo, então o
  painel central mostra só o contexto do módulo (título, objetivo) e **nenhum**
  tópico carregado.
- Dado o módulo aberto, quando clico no tópico "A. Partes da Guitarra e do
  Violão", então a explicação do tópico é carregada no centro.
- Dado que li um tópico do módulo A, quando volto ao módulo A, então o conteúdo
  do tópico continua carregado.
- Dado que li um tópico do módulo A, quando abro o módulo B, então o módulo B
  fica **em branco** (nenhum tópico carregado).

Dependências: `ModuleComponent` (estado de seleção por módulo). Hoje
`itemOpennessChanged`/`itemClicked` chamam `selectTopic(number, 0)` — é isso que
precisa deixar de acontecer no abrir.

### [CM-019] Exercício no painel central, controles no painel direito — valor: H — tamanho: S — status: **done** (revisado 2026-11-07)
Requisito: REQ-021.
Como um aluno de guitarra, eu quero executar o exercício no painel central e ver
apenas os controles e o placar no painel da direita, para que a questão e as
alternativas fiquem no palco principal, sem disputar espaço com os controles.

Critérios de aceite:
- Dado o questionário armado, quando o centro o demonstra, então ele mostra o
  cabeçalho do módulo (nível/BPM/gate), a instrução "Responda uma questão por
  vez.", a questão atual ("Questão X de Y") e as alternativas clicáveis (A–D).
- Dado o mesmo exercício, então o **painel direito** mantém apenas os controles
  (seletor, botão de play com `id — título`, placar "Acertos x/y · aproveitamento
  z%") e a caixa de orientação ("Neste exercício…").
- Dado um exercício tocável (não questionário), então o centro mostra só a
  explicação (objetivo, como o app verifica) e o executor fica à direita.

Dependências: `PracticePanel` (dono da sessão de quiz), `ModuleComponent::ContentView`.

Implementado (2026-11-07, revisão a pedido do cliente): o centro renderiza o
questionário — cabeçalho do módulo, instrução, "Questão X de Y", enunciado e as
alternativas clicáveis — e responde por procuração à sessão do `PracticePanel`
(`ContentView::onAnswerOption`); o painel direito passa a apresentar o cabeçalho
com o link "Todos os tópicos do módulo", o seletor, o botão de play, o placar e a
caixa de orientação, sem repetir a questão.

### [CM-020] Um exercício executável por tópico do Módulo 1 — valor: H — tamanho: L — status: **done** (Módulo 1)
Requisito: REQ-022 (com REQ-006/REQ-008). Conteúdo por **musician + pm +
business-analyst**.
Como um aluno de guitarra, eu quero ter ao menos um exercício prático para cada
tópico do módulo, para que eu pratique o assunto daquele tópico e não apenas
responda ao questionário.

Critérios de aceite:
- Dado o Módulo 1, quando abro cada um dos tópicos A–I, então cada tópico tem
  **≥1 exercício executável** associado (não só o questionário EX-1.A.1).
- Dado o exercício do tópico, então ele mede o desempenho (nota/acertos/grade)
  pelo motor de medição (CM-008) e respeita o gate de 90%.
- Dado o tópico, então o exercício cobre o assunto do tópico (validado pelo
  musician).

Dependências: curadoria de conteúdo (CM-012), catálogo (`ModuleCatalog.cpp`),
motor de medição (CM-008).

### [CM-021] Classificação correta de entradas/saídas de áudio — valor: H — tamanho: M — status: **done** (código; validação Windows pendente)
Requisito: REQ-023.
Como um aluno que usa o VoiceMeeter Banana, eu quero ver minhas entradas na
lista de *inputs* e minhas saídas na lista de *outputs*, para que eu selecione o
dispositivo certo sem adivinhar.

Critérios de aceite:
- Dado o VoiceMeeter Banana instalado no Windows, quando abro **Settings >
  Áudio**, então as **entradas** aparecem em *Input* e as **saídas** em *Output*
  (sem inversão).
- Dado qualquer backend (ASIO/WASAPI), então o rótulo de cada porta vem da
  direção real do canal (`getInputChannelNames()`/`getOutputChannelNames()` do
  `AudioIODevice`), não do nome bruto.
- Dado o dispositivo selecionado, quando toco uma corda, então o medidor de
  nível reage ao sinal de entrada (prova de que a porta escolhida é a captura).

Dependências: `SettingsComponent`/`AudioEngine` (device manager).
**Bloqueio:** validação exige Windows + VoiceMeeter Banana (ambiente Linux atual
só valida compilação). Requer revisão do **security-engineer** (driver ASIO de
terceiros).

### [CM-001] Afinador e medidor reais na UI — valor: H — tamanho: M — status: ready
Requisito: REQ-001.
Como um aluno de guitarra, eu quero ver a afinação e o nível reais do meu som na
tela, para que eu possa confiar no app enquanto estudo.

Critérios de aceite:
- Dado que o dispositivo está aberto, quando eu toco uma corda, então o medidor
  de nível reage ao volume real em até 100 ms.
- Dado que eu toco a nota A2 (110 Hz), quando o detector estabiliza, então o
  afinador mostra "A" com desvio em cents dentro de ±5 cents.
- Dado que o dispositivo está parado, quando não há sinal, então a UI mostra
  estado vazio ("—") e não um valor falso.

Dependências: `AudioEngine` (getters já existem, ver `Source/Audio/AudioEngine.h`).
Notas técnicas (architect): consumir só os getters públicos e atomics; nenhuma
chamada bloqueante na UI.

### [CM-017] Módulo 1 jogável: ambientação, instrumento e organização musical — valor: H — tamanho: L — status: done
Requisito: REQ-003, REQ-006, REQ-007, REQ-008. Conteúdo em `docs/MUSIC.md` §Módulo 1.
Como um aluno iniciante, eu quero estudar o Módulo 1 dentro do app (explicação
antes do desafio), para que eu aprenda as partes do instrumento, as notas, o
braço, a pestana, o CAGED, as tonalidades e o cifrado sem sair do software.

Critérios de aceite:
- Dado o app aberto, quando clico em **Modules**, então vejo a lista de módulos e
  o Módulo 1 selecionado com sua explicação.
- Dado o Módulo 1 aberto, quando leio, então os nove blocos (A–I) aparecem na
  ordem, antes de qualquer desafio (REQ-003). O bloco I cobre rítmica (pulsação,
  figuras e contagem), base do alinhamento à grade exigido pelo gate.
- Dado o módulo, então ele exibe nível 1, BPM meta 60 e gate 90%.
- Dado o módulo, então há ≥1 pattern (`PTN-R-PALM`) e ≥1 link de guitarrista
  citados (REQ-007).
- Dado o desafio de gate, então é `C – G – Am – F` a 60 BPM com ≥90% e
  `on_grid_ratio ≥ 0,75`.
- Dado o módulo, então as apostilas de curadoria (REQ-006) são citadas por
  arquivo-fonte (`CourseModule::sources`), visíveis na seção "Apostilas".

Pronto quando (DoD):
- [x] Conteúdo espelhado de `docs/MUSIC.md` para o catálogo (ADR 0005).
- [x] Build compila sem avisos novos.
- [x] Medição real dos exercícios (CM-008 — `PracticeSession`, `ExerciseEvaluator`, `TempoGrid`).
- [x] Gate de progressão linear com ≥90% e persistência do desbloqueio (REQ-002/REQ-009).
- [x] Teste automatizado no CI (CM-002 — 85 checagens, `ctest` no job Linux).
- [x] Pattern e links de guitarristas exibidos no módulo (REQ-007).
- [x] Apostilas curadas citadas no catálogo e exibidas na UI (REQ-006, CM-012).

### [CM-016] Afinador transversal com pitch de referência editável — valor: H — tamanho: S — status: done
Requisito: REQ-017. Deriva de `docs/MUSIC.md` (referência A4, tolerância ±5 cents).
Como um guitarrista, eu quero abrir um afinador a qualquer momento e escolher a
referência de afinação, para que eu possa afinar em A=440 ou em outra referência
(432, 442, barroco) sem depender do material do curso.

Critérios de aceite:
- Dado o app aberto em qualquer tela, quando clico em **Tuner**, então a janela do
  afinador abre sobre a tela atual, sem entrar em nenhum módulo.
- Dado sinal puro de 440 Hz com A4 = 440, quando o detector estabiliza, então o
  afinador mostra "A" e desvio 0 (±5 cents).
- Dado A4 = 440, quando eu mudo para 442 Hz, então as notas são recalculadas para
  a nova referência e o valor persiste após reabrir o app.
- Dado um valor fora de 400–480 Hz, quando confirmo, então o sistema limita ao
  intervalo válido.
- Dado "Reset to 440", quando clico, então a referência volta ao padrão.

Pronto quando (DoD):
- [x] Código compila sem avisos novos (build Linux validada).
- [x] `AGENTS.md`, `docs/REQUIREMENTS.md` e este backlog atualizados.
- [ ] Teste automatizado no CI (pendente: CM-002).

### [CM-002] Pipeline de CI para build e testes — valor: H — tamanho: M — status: done
Requisito: REQ-009 (base para medir), DoD.
Como o time de desenvolvimento, eu quero que cada PR compile e rode os testes
automaticamente, para que nenhum erro bobo chegue à main.

Critérios de aceite:
- Dado um PR, quando eu abro ou atualizo, então o CI clona JUCE 8.0.4 e compila
  no Linux sem novos avisos.
- Dado o build sem o ASIO SDK, quando o CI roda, então o build passa (ASIO é
  opcional por design).
- Dado um PR que quebra o build, quando o CI termina, então o check fica vermelho.
- Dado o alvo `CursoMusicaTests`, quando o CI roda, então `ctest` executa a suíte
  de lógica pura e falha o job se algum teste quebrar.

Dependências: nenhuma. Owner: devops.

### [CM-010] Instalador Windows com seleção de diretório — valor: H — tamanho: M — status: done
Requisito: REQ-014 (e REQ-013 para a branch de teste).
Como um aluno, eu quero um instalador `.exe` que me deixe escolher onde instalar,
para que o app fique pronto para uso sem passos manuais.

Critérios de aceite:
- Dado o instalador, quando eu o executo, então ele oferece escolher o diretório
  de instalação (padrão `%ProgramFiles%`).
- Dado que eu instalei em `D:\CursoMusica`, quando o app abre, então ele
  reconhece o áudio e funciona sem configuração manual.
- Dado que eu desinstalo, quando a remoção termina, então os arquivos e atalhos
  instalados são removidos.

Dependências: CM-002 (CI gera o artefato). Owner: devops.

## Próximas (refinando)

### [CM-006] Estrutura de curso: módulos lineares, explicação e desafios — valor: H — tamanho: L — status: draft
Requisitos: REQ-002, REQ-003, REQ-008, REQ-005.
Como um aluno, eu quero percorrer módulos em ordem, com explicação antes e
desafios depois, para que eu estude dentro do próprio software.

Critérios de aceite (rascunho):
- Todo módulo tem uma seção de explicação **antes** do primeiro desafio.
- Todo módulo tem ≥1 desafio jogável.
- O módulo N+1 só fica acessível após o gate do módulo N (ver CM-008).
- Nenhuma tela exige abrir arquivo externo para estudar.

Dependências: CM-001. Bloqueio: modelo de curso (ADR 0003) e UI (designer).

### [CM-007] Conversão de partitura para áudio — valor: H — tamanho: L — status: draft
Requisitos: REQ-004; stack do ADR 0002.
Como um aluno, eu quero ouvir qualquer exemplo/partitura do app, para que eu
aprenda de ouvido além da leitura.

Critérios de aceite (rascunho):
- Toda partitura exibida tem áudio correspondente e reproduzível no app.
- A altura e a oitava do áudio batem com a partitura (respeitando a transposição
  da guitarra — soa uma oitava abaixo do escrito).
- O mesmo arquivo de entrada produz sempre o mesmo áudio (determinismo).

Dependências: ADR 0002 (pugixml/midifile/FluidSynth/libsndfile). Owner: developer.

### [CM-008] Motor de medição e gate de 90% — valor: H — tamanho: M — status: draft
Requisitos: REQ-009, REQ-002.
Como o sistema, eu quero medir toda tentativa e liberar o próximo módulo só com
≥90% de acerto, para que a progressão seja confiável.

Critérios de aceite (rascunho):
- Acurácia do módulo = acertos / tentativas válidas, com mínimo de tentativas.
- Acurácia ≥ 0,90 → módulo aprovado e próximo liberado; 0,899 → não libera.
- Histórico de tentativas é append-only e recalculável.

Dependências: CM-006, `docs/DATA.md` (schema v2). Owner: data-engineer + developer.

### [CM-009] Avaliação de improvisação: repouso × tensão — valor: H — tamanho: L — status: draft
Requisitos: REQ-011, REQ-012, REQ-010.
Como um aluno, eu quero que o app me diga se usei as notas certas na
improvisação, para que eu evolua com feedback objetivo.

Critérios de aceite (derivados de `docs/MUSIC.md`, dono: musician):
- Dado o contexto harmônico, cada nota tocada é classificada em
  repouso/tensão/erro/passagem.
- Tensão **não pedida** pelo estado de improviso conta como erro.
- Tensão **pedida** é aceita; tensão que resolve em repouso é aceita.
- O aluno vê *por que* errou (nota, contexto, veredito).

Dependências: CM-007 (contexto sonoro), CM-008. Owner: musician + developer.

### [CM-011] Módulos progressivos de improvisação (níveis 1–7) — valor: H — tamanho: L — status: draft
Requisitos: REQ-002, REQ-010, REQ-016; ordem e standards em `docs/MUSIC.md`.
Como um aluno, eu quero estudar improvisação em níveis crescentes, do vamp de 1
acorde até músicas reais, para que eu progrida sem pular etapas.

Critérios de aceite (rascunho):
- Níveis na ordem: 1 vamp/1 acorde → 2 vamps/2 acordes → 3 II–V–I →
  4 turnarounds → 5 blues 12 compassos → 6 standards com modulação →
  7 repertório.
- Cada nível é ancorado em standards concretos (mapa em `docs/MUSIC.md`).
- Cada nível ensina ≥1 link e ≥1 pattern do catálogo (CM-015) e verifica o uso
  (CM-012).

Dependências: CM-009. Owner: musician + po.

### [CM-014] Metrônomo com BPM meta como gate — valor: H — tamanho: M — status: draft
Requisitos: REQ-015; ADR 0004.
Como um aluno, eu quero praticar com metrônomo e ter uma meta de andamento, para
que eu só avance quando tocar certo na velocidade exigida.

Critérios de aceite (derivados de `docs/MUSIC.md`, dono: musician):
- Cada desafio tem `target_bpm`; o sistema mede o maior BPM executado dentro da
  tolerância rítmica (`achieved_bpm`).
- O **BPM meta sobe progressivamente** (60 → 140, +4 BPM por módulo do 15 ao 20):
  nenhum módulo exige velocidade que o aluno não construiu.
- O alvo de `on_grid_ratio` é **0,75–0,82** nos módulos 1–14 e sobe
  **progressivamente** até **0,90** no módulo 20 (0,82 → 0,84 → 0,85 → 0,87 →
  0,88 → 0,90).
- Atingir `target_bpm` (com alinhamento à grade) → eixo de andamento aprovado;
  ficar 1 BPM abaixo → não aprova.
- Tocar rápido e fora do tempo **não** conta como BPM atingido.
- Em bossa/samba, tocar a síncope correta não é penalizado como fora da grade.
- O módulo só libera com acurácia ≥ 90% **e** BPM meta atingido.

Dependências: CM-008, `docs/DATA.md` (schema v3). Owner: musician + developer +
data-engineer.

### [CM-015] Catálogo de patterns (melódicos, rítmicos, arpejos) — valor: H — tamanho: M — status: draft
Requisitos: REQ-016, REQ-010; IDs em `docs/MUSIC.md` §"Catálogo de patterns".
Como um aluno, eu quero praticar os patterns do catálogo, para que eu desenvolva
fluência mecânica e fraseado.

Critérios de aceite (rascunho):
- O catálogo contém os grupos: melódicos (3, 4, terças, quartas, triquetra, 3-1,
  string skipping), rítmicos (funk, palm mute, bossa, hybrid) e arpejos (tríade,
  drop 2, drop 3).
- Cada pattern tem ID estável (`PTN-*`) e é citável por um módulo.
- A avaliação detecta a assinatura do pattern no trecho improvisado (CM-012).

Dependências: CM-011. Owner: musician.

### [CM-012] Curadoria de conteúdo: apostilas, links e patterns — valor: M — tamanho: M — status: in-progress
Requisitos: REQ-006, REQ-007, REQ-010, REQ-016.
Como o time de conteúdo, eu quero revisar as apostilas e anexar links e patterns
de guitarristas por módulo, para que o material seja coerente e verificável.

Progresso (2026-11-02, Módulo 1):
- [x] Apostilas sob Git LFS baixadas e revisadas bloco a bloco (OCR nos PDFs
  digitalizados); mapa bloco → fonte em `docs/MUSIC.md` §1.1.
- [x] `CourseModule::sources` registra as fontes por módulo; a UI exibe a seção
  "Apostilas" (REQ-006).
- [x] Lacuna de conteúdo fechada: **bloco I — Rítmica** (pulsação, figuras,
  contagem TÁ/TÁ-KI), extraído do capítulo "Rítmica" de `pdf-fraseado-melodico`;
  sustenta o `on_grid_ratio` do gate (REQ-015).
- [x] Tópico A detalhado a partir de `explica_painelEsquerdo.pdf` (16 páginas);
  `Questionario_m1.pdf` virou o exercício **EX-1.A.1** (7 questões, gate 90%).
- [x] Apostilas da branch `adequacao` varridas por duplicatas (hash LFS +
  assinatura de imagem); 3 cópias `(1)` removidas, 18 apostilas únicas.
- [x] Revisão da `adequacao` reescrita (2026-11-05): 4 apostilas novas por hash
  LFS — CAGED (Marcelo Mello, bloco F), Teoria Elementar (Lacerda, B/C/D),
  Teoria da Música (Bohumil Med, B/C/G/I), Manual de regulagem (Mozart
  Carvalho, A); `CourseModule::sources` passa de 3 para 7 fontes.
- [ ] Módulos 2..20: mesma revisão (owner: musician) quando o conteúdo for escrito.
- [ ] A avaliação detecta se o pattern ensinado foi usado (CM-015).

Critérios de aceite (rascunho):
- Cada módulo lista: fonte da apostila usada, ≥1 link, ≥1 pattern (ID do
  catálogo, CM-015).
- Guitarristas de referência considerados: Petrucci, Govan, Kotzen, Howe, Vai,
  Satriani, Juninho Afram, Edu Ardanuy, Kiko Loureiro.

Dependências: CM-011. Owner: musician.

### [CM-013] Instalador de teste por módulo com acesso liberado — valor: M — tamanho: M — status: done
Requisitos: REQ-013.
Como o time de validação, eu quero um instalador por módulo na branch de teste,
com tudo liberado, para que eu veja o módulo novo sem desbloquear os anteriores.

Critérios de aceite (rascunho):
- Para cada módulo novo, o CI publica um instalador na branch de teste.
- O instalador abre com todos os módulos acessíveis (override de teste).
- O override não altera o cálculo real de acerto.

Entregue: `release.yml` roda no push da branch `test`, compila no `windows-2022`
com `TEST_UNLOCK_ALL=ON` e publica `instalador/Instalador CursoMusica.exe`
(artifact do run; commitado na branch quando `commit_installer=true`).

Dependências: CM-010, CM-006. Owner: devops.

## Não priorizado / ideias

- Metrônomo com detecção de tempo tocado.
- Registro local de sessões de estudo (dados → owner: data-engineer).
- Exportar progresso em PDF.

## Regras de priorização

1. Valor para o aluno × valor para o negócio.
2. Redução de risco (ex.: CI antes de features, para pegar regressão cedo).
3. Tamanho menor primeiro quando o valor empata.

**Por que CM-001 está no topo:** é o que transforma o app de mockup em
ferramenta real, tem o maior valor e o menor esforço entre os itens de alto
valor — destrava as histórias seguintes.
