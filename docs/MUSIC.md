# MUSIC — CursoMusica

Dono: **musician** (músico profissional), em conjunto com o **pm**. Requisitos
musicalmente corretos do sistema: números, unidades e tolerâncias. O PO deriva
os critérios de aceite daqui.

## Padrões de afinação

| Parâmetro | Valor padrão | Observação |
|---|---|---|
| Referência (A4) | 440 Hz | 432 Hz e 415 Hz (barroco) selecionáveis |
| Temperamento | igual (12-TET) | outros temperamentos são configuração futura |
| Unidade de erro | cents | 1 semitom = 100 cents |
| Tolerância "afinado" | ±5 cents | mostrar resolução de 1 cent |
| "Muito desafinado" | \|cents\| > 50 | mostrar estado, não nome de nota |

Matemática de referência (para QA e para o developer):

- MIDI `n` → frequência: `f = 440 * 2^((n - 69) / 12)` (A4 = MIDI 69).
- Erro em cents: `cents = 1200 * log2(f / f0)`.
- Cordas soltas da guitarra em afinação padrão:

| Corda | Nota | Frequência |
|---|---|---|
| 6ª | E2 | 82.41 Hz |
| 5ª | A2 | 110.00 Hz |
| 4ª | D3 | 146.83 Hz |
| 3ª | G3 | 196.00 Hz |
| 2ª | B3 | 246.94 Hz |
| 1ª | E4 | 329.63 Hz |

## Domínio do instrumento

- **Alcance de detecção (guitarra 6 cordas):** E2 (82.41 Hz) até ~E6 (1318.5 Hz,
  24ª casa da 1ª corda). Mínimo prático do afinador: **80–1400 Hz**.
- **Afinações alternativas:** drop D (D2 A2 D3 G3 B3 E4), DADGAD, meio-tom abaixo
  (Eb). Se o app afirmar suportar 7/8 cordas, o alcance precisa descer até B1
  (~61.74 Hz) ou F#1.
- **Capotraste e transposição:** o app deve permitir indicar o capotraste sem
  alterar a referência de afinação.
- **Harmônicos e entonação:** a leitura deve refletir a altura real tocada; a
  corda pode estar afinada na corda solta e desafinada na casa (entonação) —
  comportamento correto, não bug.

## Ritmo e compasso

| Parâmetro | Valor |
|---|---|
| BPM | 20–300 |
| Subdivisões | 1/4, 1/8, tercinas, 1/16 |
| Compassos | 2/4, 3/4, 4/4, 6/8, 12/8 e métricas ímpares (5/4, 7/8) |
| Acento | tempo forte audivelmente distinto |

## Playback e estudo

- **Velocidade:** 25%–100% (prática desacelera, nunca acelera) **sem mudar o
  tom**.
- **Loop:** pontos A/B com precisão de amostra; *crossfade* curto na emenda para
  evitar clique; rampa de tempo opcional para prática progressiva.
- **Pedagogia:** prática lenta, por trechos, intercalada e em loop. O app treina
  o ouvido — **não** afina a guitarra pelo aluno.

## Revisão conjunta PM × Musician

Toda exigência com dimensão musical passa por aqui antes de virar história. O PM
mantém o enquadramento de negócio; o musician fornece a verdade musical.

| Requisito (como estava) | Veredito | Requisito corrigido |
|---|---|---|
| "Afinador mostra a nota" | precisa mudar | mostrar nota **+ cents** com tolerância ±5 cents e referência A4 explícita |
| "Detectar qualquer nota" | precisa mudar | detectar 80–1400 Hz (6 cordas); fora disso, mostrar "—"/"muito baixo/alto" |
| "Playback mais rápido para estudar" | precisa mudar | 25–100% **sem mudança de tom**; acima de 100% não é prática de estudo |
| "Metrônomo simples" | incompleto | BPM 20–300, subdivisões, compassos, acento no tempo forte |

## Critérios de aceite musicais (para o PO/QA)

- Dado sinal puro de **440 Hz** com referência A4 = 440, então o afinador mostra
  **A4 com 0 ± 1 cent**.
- Dado sinal puro de **110.00 Hz**, então mostra **A2 com 0 ± 5 cents**.
- Dado sinal de **82.41 Hz** (E2), então detecta E2 (não uma oitava acima).
- Dado ruído/silêncio, então mostra estado vazio ("—"), nunca uma nota falsa.
- Dado loop A/B, quando o playback passa da emenda, então não há clique audível.
- Dado BPM 120 em 4/4, então o acento cai a cada 4 batidas, audivelmente.

## Restrição de engenharia (não óbvia)

Detectar E2 (82.41 Hz) exige uma **janela de análise longa o bastante** para
conter vários períodos (a ~48 kHz, uma janela de 2048 amostras resolve ~23 Hz,
mas a confiança do YIN melhora com mais períodos). Há um trade-off real entre
precisão nas notas graves e tempo de resposta. Ver `docs/adr/` e
`Source/Audio/PitchDetector.h`.

## Questões musicais abertas

- Quais afinações alternativas entram no v1 (drop D, DADGAD, meio-tom)?
- O metrônomo deve ter detecção de tempo tocado ou só geração?
- Mostrar a nota escrita (com bemol) ou sempre sustenido? (depende do tom)

---

# Notas de repouso, tensão e improvisação

Esta seção atende a REQ-011, REQ-012 e REQ-010 (`docs/REQUIREMENTS.md`).

## Notas de repouso × notas de tensão

Para um dado acorde, classificamos a altura tocada em três estados:

| Estado | Definição | Exemplo em Cmaj7 |
|---|---|---|
| **Repouso** | nota do acorde ou da escala estável no contexto | C, E, G, B |
| **Tensão ativa** | tensão que resolve no contexto (9, 11, 13, 6, ♭9, ♯11) | D, F#, A em contexto de dominante |
| **Tensão não pedida** | tensão **fora** do contexto pedido pelo exercício | qualquer nota de fora do centro |

**Regra de aceitação (REQ-012):** uma nota de tensão só é aceita se o *estado de
improviso* a pedir (ex.: "resolva com ♭9 no V7", "use a escala alterada",
"toque tensão e resolva em repouso"). Fora desse estado, **qualquer tensão não
solicitada é erro, a menos que a nota faça parte do acorde**. Não há tolerância
zero ambígua: a regra é binária e explicável.

**Critério exato (definitivo):**

| Situação da nota | Veredito |
|---|---|
| Pertence ao acorde (fundamental, 3ª, 5ª, 7ª) | repouso (aceita) |
| Tensão **solicitada** pelo estado de improviso | aceita |
| Tensão **não solicitada** e **fora** do acorde | **erro** |
| Tensão não solicitada **que faz parte do acorde** (ex.: 9ª/13ª que está no acorde) | aceita |
| Passagem cromática que resolve no tempo forte | passagem (aceita) |

**Matemática da classificação:** a nota é comparada ao acorde pela sua **classe
de altura** (pitch class, 0–11) e pela sua distância em semitons à fundamental do
acorde, com o campo harmônico em vigor:

- repouso se a classe de altura ∈ {fundamental, 3ª, 5ª, 7ª} do acorde, ajustado
  pela escala do centro;
- tensão ativa se a classe ∈ {9, 11, 13} e o exercício pedir tensão;
- erro caso contrário (ou tensão fora de contexto).

O sistema deve também aceitar **aproximação cromática** como gesto legítimo
(nota de passagem) sem contá-la como erro, desde que resolva no tempo forte.

## Modelos progressivos de improvisação (ordem obrigatória)

Progressão **linear**: o módulo N+1 só é liberado após o gate do módulo N
(≥ 90%, REQ-009). Progressão **baseada em níveis**: cada modelo é um nível.

| Nível | Modelo | Objetivo musical | Notas de repouso |
|---|---|---|---|
| 1 | Vamps de 1 acorde (estatismo modal) | ouvir o centro e a cor do modo | fundamental, 3ª, 5ª, 7ª |
| 2 | Vamps de 2 acordes (movimento modal interno) | perceber o movimento entre dois centros | notas comuns aos dois campos |
| 3 | II–V–I (célula fundamental) | ouvir a função e a resolução | 3ª e 7ª guiam (voice leading) |
| 4 | Turnarounds (ciclos repetitivos) | reconhecer o ciclo e antecipar a volta | repouso no I ao fechar o ciclo |
| 5 | Blues (12 compassos) | forma, swing e o blues scale | I, IV, V e a blue note |
| 6 | Standards com modulação | acompanhar mudança de tom | repouso segue o tom vigente |
| 7 | Uso de músicas (repertório real) | aplicar tudo em contexto | idem, por trecho |

## Metrônomo e meta de andamento (REQ-015)

O aluno pratica com metrônomo e precisa **atingir o BPM meta** do desafio para
avançar (segundo eixo de gate, além dos 90% — ADR 0004).

### Mapa módulo → nível

O currículo tem **20 módulos** agrupados nos 7 modelos progressivos:

| Módulos | Nível / modelo |
|---|---|
| 1–2 | 1 — Vamp de 1 acorde |
| 3–4 | 2 — Vamps de 2 acordes |
| 5–7 | 3 — II–V–I |
| 8–10 | 4 — Turnarounds |
| 11–14 | 5 — Blues (12 compassos) |
| 15–17 | 6 — Standards com modulação |
| 18–20 | 7 — Repertório |

### BPM meta progressivo por módulo

O BPM **aumenta progressivamente** ao longo do currículo — nunca "pula" para uma
velocidade que o aluno não construiu. A subida é mais fina nos módulos
avançados (15–20), onde a exigência é maior.

| Módulo | BPM meta | Módulo | BPM meta |
|---|---|---|---|
| 1 | 60 | 11 | 100 |
| 2 | 64 | 12 | 104 |
| 3 | 68 | 13 | 108 |
| 4 | 72 | 14 | 112 |
| 5 | 76 | 15 | 120 |
| 6 | 80 | 16 | 124 |
| 7 | 84 | 17 | 128 |
| 8 | 88 | 18 | 132 |
| 9 | 92 | 19 | 136 |
| 10 | 96 | 20 | 140 |

O degrau maior no módulo 15 (112 → 120) marca a entrada no **nível 6**
(modulação), onde o tempo de performance começa a ser cobrado. Do 15 ao 20 a
subida é de **+4 BPM por módulo**, chegando à meta de repertório (140).

> Estes valores são uma **proposta do musician**; ajustáveis por módulo conforme
> o material real de cada desafio.

### Tolerância rítmica e alvo de `on_grid_ratio` (75–82%)

`achieved_bpm` só conta se o aluno tocar **na grade** do metrônomo. A tolerância
é uma janela em torno do tempo esperado, proporcional à subdivisão:

| Subdivisão | Janela de tolerância (aprox.) |
|---|---|
| Semínima (1/4) | ±25% do intervalo entre batidas |
| Colcheia (1/8) | ±20% |
| Tercina | ±18% |
| Semicolcheia (1/16) | ±15% |

`on_grid_ratio` = fração das notas que caíram dentro da janela.

**Por que 75–82% é a faixa ideal de estudo (e não 90%).** Exigir ≥90% de
alinhamento num instrumento de cordas obriga a uma **rigidez mecânica quase
robótica**: o braço e os dedos perdem a *respiração* (o micro-timing natural).
Na faixa de 75–82% o aluno mantém a precisão rítmica cirúrgica **sem soar
engessado** — o pulso fica firme e o *swing/groove* natural do estilo sobrevive.
90% é meta de **performance**, não de **aprendizado**.

**Rampa de exigência (progressão baseada em níveis):**

| Módulos | Alvo de `on_grid_ratio` |
|---|---|
| 1–14 | 0,75 a 0,82 (faixa de estudo) |
| 15 | 0,82 |
| 16 | 0,84 |
| 17 | 0,85 |
| 18 | 0,87 |
| 19 | 0,88 |
| 20 | 0,90 (precisão de performance) |

Do módulo 15 ao 20 a exigência sobe **progressivamente**, em paralelo com o BPM
meta: o aluno "afina o relógio interno" antes de exigir precisão de palco. Tocar
rápido e fora do tempo continua **não** contando.

## Patterns de guitarristas (REQ-007, REQ-010)

Cada módulo deve citar **≥1 link** e **≥1 pattern**. Sugestões por referência
(sempre citando a fonte, sem copiar material protegido):

| Guitarrista | Foco de pattern sugerido |
|---|---|
| John Petrucci | alternate picking mecânico; sequências de 3 e 4 notas |
| Guthrie Govan | fusão de escalas, híbrido legato/palhetada |
| Richie Kotzen | bends expressivos, pentatônica com fraseado vocal |
| Greg Howe | fusão, pentatônicas deslocadas, legato amplo |
| Steve Vai | modos exóticos, arpejos e "luthier" de frases |
| Joe Satriani | escalas modais sobre vamps, legato cantável |
| Juninho Afram | fraseado de rock nacional, melodismo |
| Edu Ardanuy | pentatônica brasileira, licks de rock/hard |
| Kiko Loureiro | fusão brasileira + metal, ritmos de síncope |

## Verificação do uso de link/pattern (REQ-010)

O módulo registra, por exercício, qual link e qual pattern foram ensinados. A
avaliação de improvisação confere:

- o aluno **abriu/estudou** o link (telemetria local, opt-in);
- o **pattern foi usado**: detectado por assinatura musical (grau da escala,
  intervalo, direção) dentro do trecho improvisado;
- sem esses dois itens, o exercício não conta como concluído.

## Conversão de partitura para áudio (REQ-004)

Toda partitura exibida deve ter áudio. O caminho musical:

1. partitura (XML/MusicXML) → eventos de nota (altura, duração, dinâmica);
2. eventos → MIDI (programa por instrumento: guitarra, baixo, bateria);
3. MIDI → síntese/samples (FluidSynth com SoundFont, ou samples `.wav`);
4. conferência: a altura MIDI ↔ a frequência em cents deve bater com a tabela de
   afinação desta seção.

Ponto de atenção: **transposição**. A guitarra é instrumento transpositor (soa
uma oitava abaixo do escrito). A conversão precisa respeitar isso para o áudio
soar na oitava correta.

---

# Standards como laboratório progressivo

Standards de jazz e clássicos da MPB/Bossa Nova não são só repertório: são o
**laboratório definitivo**, "livros de exercícios vivos" organizados por
complexidade harmônica e conceitual. Cada standard entra no nível em que o
conceito que ele ensina aparece pela primeira vez.

| Estágio | Conceito foco | Standards sugeridos |
|---|---|---|
| 1 — Estatismo modal | um centro, uma cor | *Maiden Voyage*, *Cantaloupe Island* (vamps) |
| 2 — Movimento modal interno | dois centros, notas comuns | *Maiden Voyage*, *Cantaloupe Island* |
| 3 — II–V–I | função e resolução | *Só Danço Samba*, *Equinox* |
| 4 — Turnarounds | ciclo e volta | *Só Danço Samba*, *Equinox* |
| 5 — Blues | forma de 12 compassos | *Equinox*, *Incompatibilidade de Gênios* |
| 6 — Modulação | mudança de tom | *500 Miles High*, *Spain*, *Incompatibilidade de Gênios* |
| 7 — Repertório | tudo em contexto | *Spain*, *500 Miles High*, *Equinox* |

Repertório completo: ver `docs/REQUIREMENTS.md` (REQ-012/repertório).

> Cada standard é usado **como progressão para estudo** (acordes, escalas,
> trechos), nunca como gravação. Ver "Direitos autorais" abaixo.

## Detalhamento harmônico por música

Dados verificados em fontes públicas (lead sheets/Real Book e análises
publicadas). Onde a tonalidade difere entre gravação original e Real Book, ambas
são citadas. **Toda altura abaixo é concert pitch.**

### Maiden Voyage — Herbie Hancock
- **Tom / forma:** D (modal), 32 compassos, AABA, 4/4.
- **Harmonia:** quase toda em acordes **sus** (7sus4): `Dsus`, `Fsus`, `Ebsus`,
  `Dbsus`. No original, o quarto acorde soa como **sus com 3ª menor** (o Real
  Book grafa `Dbsus`); a diferença é audível e vale como exercício de escuta.
- **Conceito (níveis 1–2):** **estatismo modal** — sem função dominante, sem
  trítono pedindo resolução. É o "mar aberto".
- **Foco de estudo:** ouvir o **centro** e a cor de cada modo; notas de repouso =
  fundamental, 4ª, 5ª, 7ª.
- **Pattern sugerido:** `PTN-M-3rds` (terças) e frases com intervalos de 4ª (o
  tema abre e fecha em quartas).

### Cantaloupe Island — Herbie Hancock
- **Tom / forma:** F menor, 16 compassos, ABAB, hard bop/funk.
- **Harmonia:** três vamps estáticos de 2 compassos — `Fm7` (F dórico),
  `Db7` (**lídio dominante**), `Dm7` (D dórico) — e volta a `Fm7`.
  Sem movimento harmônico funcional; a "forma" é o groove.
- **Conceito (níveis 1–2):** **vamps e movimento modal interno** (o baixo desce
  F → Db → D).
- **Foco de estudo:** trocar de escala por centro — Dórico em Fm7/Dm7, Lídio
  dominante em Db7.
- **Pattern sugerido:** `PTN-R-FUNK` (levada sincopada) e `PTN-M-P31`.

### Só Danço Samba — Tom Jobim & Vinicius de Moraes
- **Tom / forma:** Dó maior (Real Book), forma de 32 compassos (AABA), bossa.
- **Harmonia:** a **progressão de bossa do Jobim** — tônica, VI7, **II7
  prolongado** (o `D7` onde se esperaria `Dm7`; a "luz" da bossa), V7, I. O
  dominante secundário alongado é a assinatura.
- **Conceito (nível 3):** **II–V–I** e dominantes secundários.
- **Foco de estudo:** ouvir a resolução; o `II7` pede **tensão** e é o exemplo
  perfeito da regra REQ-012 (tensão aceita só quando o contexto a pede).
- **Pattern sugerido:** `PTN-R-BOSSA` — polegar nos tempos 1 e 3, dedos nas
  síncopas. É o pattern que define a **levada brasileira** e afeta o
  `on_grid_ratio` (a síncope desloca a grade de propósito).

### Equinox — John Coltrane
- **Tom / forma:** **Dó# menor** (gravação original) / Dó menor (Real Book),
  **blues menor de 12 compassos**.
- **Harmonia:** `C#m7`, `F#m7`, `G#7alt`, `C#7#9`; no 9º compasso o acorde
  inesperado é `Ab9` (substituto do IV, colocando o D da melodia como trítono).
- **Conceito (nível 5):** **blues de 12 compassos** + blues menor modal.
- **Foco de estudo:** forma de 12, a blue note e o `#9` (som "Trane").
- **Pattern sugerido:** `PTN-M-4` (grupos de 4) sobre a escala de blues menor.

### Incompatibilidade de Gênios — João Bosco & Aldir Blanc
- **Tom / forma:** **Lá menor**; harmonia **repetida** (intro + tema), samba com
  levada de **cuíca** no violão.
- **Harmonia (encadeamento verificado):**
  `Am9` → `Dm9` (Dm11 com baixo em Lá) → `G7(9b)` → `C7M(#11)` (com baixo em Sol)
  → `F7M` (com baixo em Lá) → `Bm7(b5)` (com baixo em Lá) → `E7` → `Am9`.
  São **10 acordes**, com **empréstimos modais** e baixos pedalizados.
- **Conceito (níveis 5–6):** blues/forma brasileira **+ modulação e empréstimo
  modal**; aqui a harmonia **foge do ciclo diatônico previsível** do jazz
  americano (ao contrário de *Autumn Leaves*).
- **Foco de estudo:** o **`C7M(#11)`** (o #11 = 4ª aumentada) e o **`Bm7(b5)`
  com baixo em Lá** — acordes de passagem que dão o "molho" do samba.
- **Atenção ao `on_grid_ratio`:** a **rítmica brasileira é altamente sincopada**;
  a grade do metrônomo precisa considerar o deslocamento da síncope, senão o
  aluno é penalizado por tocar **certo** no estilo. Este é o caso que mais exige
  cuidado na calibração da tolerância (R-13).
- **Pattern sugerido:** `PTN-R-BOSSA` + `PTN-M-3rds` (terças sobre os acordes de
  passagem).

### 500 Miles High — Chick Corea / Return to Forever
- **Tom / forma:** **Mi menor** (lead sheet em Dó menor), **18 compassos**
  (forma atípica, sem A/B simétrico), latin ~100 BPM.
- **Harmonia:** `Em7` → `Gm6/9` → `BbMaj7` → `Bm7(b5)` → `E7#9` → `Am7` →
  `F#m7(b5)` → `Fm7` → `Cm7` → `B7#5#9`. O `B7#5#9` é o V que volta ao topo.
  A ligação entre áreas usa **movimento por graus conjuntos** (cromatismo), não
  ciclos de quintas.
- **Conceito (nível 6):** **modulação e áreas tonais distantes** — duas áreas
  (Em/Am e Fm/Cm) sem cadências óbvias.
- **Foco de estudo:** ouvir os centros e as resoluções escondidas (`Bm7b5 →
  E7#9 → Am7` é um II–V–I menor dentro da peça).
- **Pattern sugerido:** `PTN-M-TRIQ` (vai-e-vem) sobre os cromatismos.

### Spain — Chick Corea / Return to Forever
- **Tom / forma:** Si menor; forma longa com **introdução** citada do
  *Concierto de Aranjuez* (Joaquín Rodrigo) e uma seção C que modula.
- **Harmonia:** intro `Bm` → `Em` → `F#7`; seção principal `GMaj7` → `F#7` →
  `Em7` → `A7` → `DMaj7` → `C#7` → `F#7` → `Bm` → `B7`; a seção C modula e
  retorna.
- **Conceito (nível 6–7):** **modulação** e **forma longa**; o laboratório final
  do repertório.
- **Foco de estudo:** navegar a forma inteira e as modulações sem perder o pulso.
- **Pattern sugerido:** `PTN-A-TRIAD` (arpejos de tríade em varredura) e
  `PTN-M-SKIP`.

### Resumo de mapeamento música → nível

| Música | Nível | Conceito foco |
|---|---|---|
| Maiden Voyage | 1–2 | estatismo modal / movimento interno |
| Cantaloupe Island | 1–2 | vamps modais |
| Só Danço Samba | 3 | II–V–I, dominante secundário |
| Equinox | 4–5 | turnaround / blues 12 |
| Incompatibilidade de Gênios | 5–6 | empréstimo modal, modulação, síncope |
| 500 Miles High | 6 | áreas tonais distantes |
| Spain | 6–7 | modulação, forma longa |

# Catálogo de patterns

Os patterns são padrões **numéricos** aplicados sobre escalas (sobretudo
pentatônicas e modos gregos) para desenvolver fluência mecânica e gerar frases.
Cada pattern tem um ID estável para o módulo citar e a avaliação detectar
(REQ-010).

## 1. Patterns melódicos e de escala (licks e digitações)

### 1.A Grupos de notas (sequências)

Avança na escala em blocos repetitivos.

| ID | Pattern | Fórmula |
|---|---|---|
| PTN-M-3 | Grupos de 3 (tercinas) | 1-2-3, 2-3-4, 3-4-5, 4-5-6… |
| PTN-M-4 | Grupos de 4 (semicolcheias) | 1-2-3-4, 2-3-4-5, 3-4-5-6, 4-5-6-7… |

### 1.B Salto de intervalos

Avança saltando notas para quebrar o som linear de "sobe e desce".

| ID | Pattern | Fórmula |
|---|---|---|
| PTN-M-3rds | Terças | 1-3, 2-4, 3-5, 4-6, 5-7… |
| PTN-M-4ths | Quartas | 1-4, 2-5, 3-6, 4-7… |

### 1.C Triquetra / vai-e-vem

Muda a direção a cada grupo de notas.

| ID | Pattern | Fórmula |
|---|---|---|
| PTN-M-TRIQ | Triquetra | 1-2-3-2, 2-3-4-3, 3-4-5-4… |

### 1.D Patterns na pentatônica

| ID | Pattern | Fórmula |
|---|---|---|
| PTN-M-P31 | Pattern 3-1 (em 5 posições) | sobe 3 notas, volta 1, retoma a subida |
| PTN-M-SKIP | String skipping | toca na 6ª corda, pula para a 4ª, toca na 5ª, pula para a 3ª… |

## 2. Patterns rítmicos e de acompanhamento (base/groove)

### 2.A Funk / R&B — 16th note scratching

| ID | Pattern | Característica |
|---|---|---|
| PTN-R-FUNK | [acorde – abafado – abafado – acorde] | semicolcheias constantes alternando dead notes e acordes pequenos nas cordas agudas (inversões nas cordas 1, 2 e 3), sincopado |

### 2.B Rock / Metal — palm muting e power chords

| ID | Pattern | Característica |
|---|---|---|
| PTN-R-PALM | pedal point abafado + power chords | palm mute na ponte em colcheias/semicolcheias na tônica (ex.: E5 na 6ª solta) intercalado com power chords abertos |

### 2.C Bossa Nova e Samba — fingerstyle

| ID | Pattern | Característica |
|---|---|---|
| PTN-R-BOSSA | polegar nos tempos, dedos nas síncopas | separação estrita: polegar marca a tônica nos tempos 1 e 3; indicador, médio e anelar puxam o acorde nos contratempos |

### 2.D Country / Blues — hybrid picking e Travis picking

| ID | Pattern | Característica |
|---|---|---|
| PTN-R-HYBRID | palheta + dedos | palheta nas cordas graves, dedos nas agudas; alternância do baixo com tônica e quinta do acorde |

## 3. Patterns de arpejo

| ID | Pattern | Característica |
|---|---|---|
| PTN-A-TRIAD | arpejos de 3 cordas (tríades) | varredura (sweep) em E–B–G e retorno; usado em rock neoclássico e fusion |
| PTN-A-DROP2 | arpejos de 7ª em Drop 2 | digitação fixa 1-3-5-7, horizontal ou vertical no braço |
| PTN-A-DROP3 | arpejos de 7ª em Drop 3 | digitação fixa 1-3-5-7, drop 3 |

## Detecção do uso de pattern (REQ-010)

A avaliação confere o pattern ensinado por assinatura musical dentro do trecho
improvisado:

- **Melódicos:** sequência de graus (ex.: 1-2-3, 2-3-4…), direção e repetição do
  bloco; intervalos (terças/quartas) medidos em semitons; inversão de direção
  (triquetra); relação de cordas para string skipping.
- **Rítmicos:** posição das notas na grade de subdivisão (dead notes, acentos,
  contratempos), presença de palm mute (ataque curto) e separação grave/agudo.
- **Arpejos:** graus 1-3-5(-7) em ordem e o padrão de varredura entre cordas.

Sem assinatura detectada, o exercício não conta como concluído.

# Direitos autorais (posição registrada)

**Decisão (musician + pm):** para este projeto **pessoal, sem fins comerciais**,
com as músicas usadas **apenas para estudo e sem execução por completa**, a
inclusão de pequenos trechos é considerada aceitável sob o **art. 46, inciso II**
da Lei 9.610/98:

- reprodução de um **único exemplar** de **pequenos trechos**;
- para **uso privado do próprio copista**;
- realizada **pelo próprio copista**;
- **sem finalidade de lucro**.

**Condições que mantêm a decisão válida** (se qualquer uma deixar de valer, a
análise precisa ser refeita):

1. O projeto permanece **pessoal e sem fins comerciais** (sem venda, sem
   assinatura, sem publicidade, sem distribuição pública ampla).
2. São usados apenas **pequenos trechos**, com finalidade de estudo — **nunca a
   obra completa**.
3. O material **não é redistribuído** como partitura/áudio da obra (o app não
   publica o arquivo do autor; ele contém a progressão para exercício).
4. Os créditos de composição são sempre exibidos.

Impacto: o risco **R-08** deixa de ser bloqueante e passa a **condicional**
(ver `docs/RISKS.md`). Se o projeto virar comercial, esta seção deve ser
substituída por licenciamento formal.


