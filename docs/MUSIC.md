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



# Módulo 1 — Ambientação, instrumento e organização musical

**Nível:** 1 (vamp de 1 acorde) · **BPM meta:** 60 (REQ-015) · **Gate:** 90% (REQ-009)
**Objetivo:** preparar o aluno para acompanhar os estudos e compreender a
organização do instrumento.

> **Regra de ouro (REQ-003):** a explicação vem **antes** de qualquer desafio.
> Nenhum desafio abre sem que o conteúdo abaixo tenha sido apresentado.

## 1.1 Conteúdo (curadoria — REQ-006)

| Bloco | Conteúdo | Fonte a revisar (REQ-006) |
|---|---|---|
| A | Partes da guitarra e do violão | `pdf-mozart-mello-livroestudosdeguitarra4em1` (cap. introdutório) |
| B | Notas musicais (natural, sustenido, bemol) | `pdf-fraseado-melodico` (fundamentos) |
| C | Sustenidos e bemóis (enarmonia) | `pdf-fraseado-melodico` (fundamentos) |
| D | Localização das notas no braço | `pdf-mozart-mello-livroestudosdeguitarra4em1` |
| E | Pestanas (barré e meio barré) | `pdf-mozart-mello-livroestudosdeguitarra4em1` |
| F | Sistema 5 (CAGED) | `pdf-fraseado-melodico` (§Sistema 5, item 13 do índice) |
| G | Organização das tonalidades | `pdf-desvendando-os-segredos-da-guitarra-fusion` |
| H | Introdução ao cifrado | `pdf-mozart-mello-livroestudosdeguitarra4em1` |
| I | Rítmica: pulsação, figuras e contagem | `pdf-fraseado-melodico` (§Rítmica, item 1 do índice) |

**Nota de curadoria (revisão de 2026-11-02).** As apostilas estão sob **Git LFS**;
o conteúdo real foi baixado (`git lfs pull`) e revisado bloco a bloco:

- `pdf-fraseado-melodico` e `pdf-mozart-mello-improvisacion-pop` são **PDFs
  digitalizados** (imagem, sem camada de texto); o índice foi lido por OCR. O
  índice do `fraseado-melodico` confirma o item **"Sistema 5 + Acordes x
  Escalas"** (bloco F), a seção de campos harmônicos maiores/menores (bloco G) e
  o capítulo **"Rítmica"** (bloco I): figuras (semibreve → semicolcheia), valor,
  compasso, andamento, subdivisão, ligaduras e as **sílabas rítmicas** (TÁ,
  TÁ-KI, TA-KI-TA-KI).
- `pdf-mozart-mello-livroestudosdeguitarra4em1` é um **livro de estudos** (27
  estudos em 9 estilos, partitura + áudio) — cobre o introdutório (blocos A/D/E/H),
  não teoria iniciante isolada.
- `pdf-desvendando-os-segredos-da-guitarra-fusion` é o material de **harmonia
  funcional** (escalas, tríades, tétrades); sustenta o bloco G.

A letra de cada linha acima agora **coincide com os blocos A–I do módulo**; a
tabela anterior usava 7 letras e não cobria sustenidos/bemóis nem rítmica. Este
mapa é o que o catálogo registra por módulo (`CourseModule::sources`, exibido no
app).

**Detalhamento do tópico A e questionário (revisão de 2026-11-03).** O tópico A
(partes da guitarra e do violão) ganhou a explicação completa de
`explica_painelEsquerdo.pdf` (16 páginas, anexado à branch `adequacao`), com
destaques e duas tabelas (nomes das partes por região e função). O
`Questionario_m1.pdf` virou o exercício **EX-1.A.1 "Questionário: conhecendo o
instrumento"**, com as 7 questões do teste de aprendizagem respondidas uma por
tela no painel direito e gate de 90% (`QuizSession`).

**Acervo sem repetição (2026-11-03).** As apostilas da branch `adequacao` foram
varridas por hash LFS e por assinatura de imagem multi-página (páginas
0/25/50/75/última), o que também pega PDFs digitalizados sem texto. Três eram
cópias exatas com sufixo `(1)` no nome e foram removidas (`b4f284c`); o acervo
fica com **18 apostilas únicas**, uma de cada.

**Revisão da `adequacao` (2026-11-04).** A branch foi reescrita a partir da nova
`main` e recebeu **4 apostilas novas** (identificadas por hash LFS, comparando a
versão anterior `b70bdf7` com a atual `1dc295f`):

| Apostila | Conteúdo | Blocos que sustenta |
|---|---|---|
| `pdf-caged-e-derivaoes-de-acordes-marcelo-mello-apostila-de-violao-e-guitarra-vol1` | Sistema CAGED: 5 formas móveis, conexão das regiões, escala sobre a forma (5 págs., texto) | F |
| `pdf-teoria-elementar-da-musica-ricordi-osvaldo-lacerda` | *Compêndio de Teoria Elementar da Música* (152 págs.): notas, pauta, claves, semitom/tom, escalas maiores/menores | B, C, D |
| `pdf-p-classtruncatedtext-module-lineclamped-85ulhh-style-max-lines5bohumil-med-teoria-da-musica-5-edicao-p` | *Teoria da Música* (Bohumil Med, 5ª ed., 424 págs.): intervalos, enarmonia, séries harmônicas, escala/grau, métrica | B, C, G, I |
| `pdf-manual-de-regulagem-e-manutenao-em-guitarra-contrabaixos-e-violoes-mozart-carvalho` | *Manual de regulagem e manutenção* (Mozart Carvalho, 129 págs.): partes do instrumento, regulagem, manutenção | A |

O nome do arquivo Bohumil Med traz um prefixo de layout do site
(`p-classtruncatedtext-module-lineclamped-85ulhh-style-max-lines5…`) colado pela
origem; é mantido **como está** porque o app cita o arquivo pelo *stem*
(`CourseModule::sources`). O mapa bloco → fonte passa a ser:

| Bloco | Fonte primária | Fonte de apoio (revisão 2026-11-04) |
|---|---|---|
| A | `pdf-mozart-mello-livroestudosdeguitarra4em1` | `pdf-manual-de-regulagem-e-manutenao-…-mozart-carvalho` |
| B, C | `pdf-fraseado-melodico` | `pdf-teoria-elementar-…-lacerda`, `pdf-p-…-bohumil-med-…` |
| D | `pdf-mozart-mello-livroestudosdeguitarra4em1` | `pdf-teoria-elementar-…-lacerda` |
| E | `pdf-mozart-mello-livroestudosdeguitarra4em1` | — |
| F | `pdf-fraseado-melodico` | `pdf-caged-e-derivaoes-de-acordes-marcelo-mello-…` |
| G | `pdf-desvendando-os-segredos-da-guitarra-fusion` | `pdf-p-…-bohumil-med-…` |
| H | `pdf-mozart-mello-livroestudosdeguitarra4em1` | — |
| I | `pdf-fraseado-melodico` | `pdf-p-…-bohumil-med-…` |

O acervo curado do Módulo 1 passa de 3 para **7 fontes** citadas no catálogo
(`CourseModule::sources`), todas verificadas contra o conteúdo dos blocos.

## 1.2 Teoria apresentada no módulo

> **Explicação completa por tópico (2026-11-04).** Os resumos abaixo são a versão
> curta. A explicação completa (≥5 páginas por tópico, escrita para iniciante) de
> cada bloco A–I vive em `Source/Course/Content/TopicA.cpp` … `TopicI.cpp`, que
> compõem o `LessonBlock::detail` renderizado no painel central. Este documento
> permanece a fonte de verdade do *conteúdo*; os arquivos `Topic*.cpp` são o
> espelho executável dele.

### Bloco A — Partes do instrumento

Corpo, braço, escala (braço), cavalete (ponte), rastilho, pestana (nut), tarraxas
(cabeça), trastes, casas, cordas (6ª a 1ª), captadores, botões de volume e tom.
No violão: a boca, o tampo e as cordas de nylon (som mais doce, menor tensão).

A nomenclatura das partes segue o **Manual de regulagem e manutenção** de Mozart
Carvalho (fonte de apoio do bloco A, revisão 2026-11-04), que ainda serve de
referência para regulagem e conservação do instrumento.

### Bloco B — Notas musicais

Sete nomes naturais: **Dó Ré Mi Fá Sol Lá Si** (C D E F G A B). Entre Mi–Fá e
Si–Dó **não há** nota intermediária (semitonos naturais). As demais notas
naturais estão a um **tom** de distância e admitem uma nota intermediária.

### Bloco C — Sustenidos e bemóis

- **Sustenido (♯):** sobe meio-tom. `Fá♯` está meio-tom acima de `Fá`.
- **Bemol (♭):** desce meio-tom. `Si♭` está meio-tom abaixo de `Si`.
- **Enarmonia:** `Fá♯ = Sol♭`, `Dó♯ = Ré♭` — mesmo som, nomes diferentes.
- **Regra prática:** não existe `Mi♯` nem `Si♯` na escala natural (e nem
  `Fá♭`/`Dó♭`); o intervalo Mi–Fá e Si–Dó já é de meio-tom.

### Bloco D — Localização das notas no braço

Afinação padrão, da **6ª (mais grave) à 1ª (mais aguda)**: `E2 A2 D3 G3 B3 E4`.

| Corda | Solta | Casa 1 | Casa 2 | Casa 3 | Casa 5 | Casa 7 | Casa 12 |
|---|---|---|---|---|---|---|---|
| 6ª | E2 | F2 | F#2 | G2 | A2 | B2 | E3 |
| 5ª | A2 | A#2 | B2 | C3 | D3 | E3 | A3 |
| 4ª | D3 | D#3 | E3 | F3 | G3 | A3 | D4 |
| 3ª | G3 | G#3 | A3 | A#3 | C4 | D4 | G4 |
| 2ª | B3 | C4 | C#4 | D4 | E4 | F#4 | B4 |
| 1ª | E4 | F4 | F#4 | G4 | A4 | B4 | E5 |

- **Regra do oitavo grau:** a casa 12 repete a corda solta **uma oitava acima**.
- **Transpositor (convenção de partitura — REQ-004):** a guitarra **soa uma
  oitava abaixo** do que está escrito. A conversão partitura→áudio deve aplicar
  essa transposição; o `E4` escrito soa como `E3`.

### Bloco E — Pestanas

- **Pestana completa (barré):** um dedo (geralmente o indicador) pressiona
  **todas** as cordas na mesma casa; os demais dedos montam o acorde à frente.
- **Meio barré:** o indicador cobre apenas **2 a 4 cordas**.
- **Por que existe:** permite usar a **mesma forma** de acorde em qualquer região
  do braço — é o alicerce do CAGED.
- **Erro comum:** a corda abafada no meio da pestana soa "morta". Ajuste o dedo
  para trás do traste e aproxime o polegar do centro do braço.

### Bloco F — Sistema 5 (CAGED)

Cinco **formas** de acorde maior (C, A, G, E, D) cobrem todo o braço e se
**repetem** a cada 12 casas, na ordem que dá nome ao sistema: **C → A → G → E → D**.

| Forma | Acorde (exemplo em Dó) | Baixo na corda | Região |
|---|---|---|---|
| C | Dó (C) | 5ª | casas 0–3 |
| A | Dó (C) | 5ª | casas 3–5 |
| G | Dó (C) | 6ª | casas 5–8 |
| E | Dó (C) | 6ª | casas 8–12 |
| D | Dó (C) | 4ª | casas 10–12 |

- As formas **conectam-se**: a última nota de uma é a primeira da seguinte.
- A **mesma forma** vale para acordes menores, de 7ª, etc. (muda a qualidade).
- O CAGED é a ponte entre **acorde** e **escala**: cada forma contém a
  pentatônica/modo daquele centro (ligação com o nível 1 de improvisação).

Apostila de apoio do bloco F (revisão 2026-11-04): **"CAGED e derivações de
acordes"** (Marcelo Mello, *Apostila de violão e guitarra vol. 1*, cap. 14),
que descreve as cinco formas móveis, sua conexão e o uso da escala sobre cada
forma.

### Bloco G — Organização das tonalidades

- **Campo harmônico maior:** `I – ii – iii – IV – V – vi – vii°`.
  Exemplo em Dó: `C – Dm – Em – F – G – Am – Bdim`.
- **Círculo das quintas:** `C → G → D → A → E → B → F# → C# → …`; a cada passo,
  acrescenta-se um sustenido. No sentido inverso (`C → F → Bb → Eb…`),
  acrescenta-se um bemol.
- **Armadura de clave:** quantos sustenidos/bemóis a tonalidade tem.
- **Relativa menor:** cada maior tem uma menor com a mesma armadura (`C` ↔ `Am`).

### Bloco H — Introdução ao cifrado

| Cifra | Significado | Exemplo |
|---|---|---|
| `C` | acorde maior | Dó maior |
| `Cm` | acorde menor | Dó menor |
| `C7` | sétima dominante | Dó com 7ª menor |
| `C7M` (`Cmaj7`) | sétima maior | Dó com 7ª maior |
| `Cm7` | menor com sétima | Dó menor com 7ª |
| `C/E` | acorde com baixo na nota após a barra | Dó com baixo em Mi |
| `C(9)`, `C(#11)` | tensões adicionadas | nona, quarta aumentada |

Cifrar é **descrever o acorde de forma compacta**; ler a cifra e achar a forma no
braço (via CAGED) é a habilidade prática do módulo.

### Bloco I — Rítmica: pulsação, figuras e contagem

Toda execução no app é medida **na grade do metrônomo** (REQ-015), então o aluno
precisa contar antes de tocar.

- **Pulsação (tempo):** a batida constante do metrônomo. O **compasso** agrupa os
  tempos (4/4 = quatro semínimas por compasso; 3/4; 6/8).
- **Figuras e valores:**

| Figura | Valor | Subdivisão do tempo | Sílaba rítmica |
|---|---|---|---|
| Semibreve | 4 tempos (1/1) | — | — |
| Mínima | 2 tempos (1/2) | — | TÁ–A |
| Semínima | 1 tempo (1/4) | 1 por tempo | TÁ |
| Colcheia | 1/2 tempo (1/8) | 2 por tempo | TÁ-KI |
| Semicolcheia | 1/4 tempo (1/16) | 4 por tempo | TA-KI-TA-KI |

- **Ponto de aumento:** soma metade do valor da figura (semínima pontuada = 1,5
  tempo). **Ligadura:** soma a duração de duas notas, atravessando o tempo forte.
- **Andamento:** lento (adágio), moderado (andante/moderato), rápido (allegro),
  definido em BPM — no app, o BPM meta do módulo.
- **Contagem:** dizer a sílaba em voz alta **enquanto** toca é o que alinha a
  execução à grade. O `on_grid_ratio ≥ 0,75` do gate mede exatamente isso.

## 1.3 Prática (exercícios e desafios — REQ-008)

Cada exercício tem **explicação antes da execução** (REQ-003) e é **medido**
(REQ-009). BPM meta 60 (REQ-015).

Cada tópico A–I tem **pelo menos três exercícios** (pedido do cliente), entre
questionários (verificáveis por pergunta) e exercícios tocáveis (verificáveis
pelo detector de altura/acorde). O catálogo registra o tópico de cada exercício
em `Exercise::lessonId`.

| ID | Tópico | Exercício | Habilidade | Verificação automática |
|---|---|---|---|---|
| EX-1.A.1 | A | Nomear as 6 cordas soltas e dizer a nota de cada uma | identificar cordas | pergunta com resposta esperada |
| EX-1.A.2 | A | Nomear as partes do instrumento (pestana, cavalete, captador, tarraxas, tirante) | partes do instrumento | questionário ≥90% |
| EX-1.A.3 | A | Dizer a região de cada peça (corpo, braço, cabeça) | partes do instrumento | questionário ≥90% |
| EX-1.B.1 | B | Tocar a escala de Dó na 1ª posição (2 oitavas) | ler o braço | sequência de notas esperada, 90% |
| EX-1.B.2 | B | Dizer as sete notas naturais e suas cifras | notas musicais | questionário ≥90% |
| EX-1.B.3 | B | Dizer a distância (tom/semitom) entre notas naturais | intervalos | questionário ≥90% |
| EX-1.B.4 | B | Tocar a 6ª solta (Mi) e cantar a mesma nota | percepção | detector: E2 sustentado |
| EX-1.C.1 | C | Nomear a nota que falta e identificar enarmonia | sustenidos/bemóis | questionário ≥90% |
| EX-1.C.2 | C | Tocar Fá/Fá♯ na 6ª e Si/Si♭ (sustenido e bemol no braço) | acidentes | detector: F2, F♯2, B3, A♯3 |
| EX-1.C.3 | C | Tocar a escala cromática na 6ª corda (casa 0 a 12) | cromatismo | detector: 13 notas E2→E3 |
| EX-1.D.1 | D | Tocar a 6ª solta (Mi) e a casa 5 (Lá) | localizar notas | detector: E2 e A2 |
| EX-1.D.2 | D | Tocar E2 (6ª solta) e E3 (casa 12) — oitava | localizar notas | detector: E2 e E3 |
| EX-1.D.3 | D | Tocar a casa 5 da 6ª (Lá) e a 5ª solta (Lá) | referências do braço | detector: A2 duas vezes |
| EX-1.E.1 | E | Pestana de Fá (F) na 1ª casa; todas as cordas devem soar | pestana | nível/ataque em todas as cordas |
| EX-1.E.2 | E | Meio barré de Si menor (Bm) na 2ª casa | pestana | detector: acorde Bm |
| EX-1.E.3 | E | Pestana completa, meio barré e posição correta | pestana | questionário ≥90% |
| EX-1.F.1 | F | Montar `C`, `G`, `D`, `Am`, `Em` e identificar a forma CAGED | acordes simples | detecção de acorde |
| EX-1.F.2 | F | Mover a forma de `E` pelo braço e nomear o acorde | CAGED | identificar acorde por região |
| EX-1.F.3 | F | Tocar as cinco formas (C, A, G, E, D) de Dó maior | CAGED | detector: C maior em 5 regiões |
| EX-1.F.4 | F | Nomear o acorde pela forma móvel | CAGED | questionário ≥90% |
| EX-1.G.1 | G | Montar o campo harmônico maior de Dó e achar a relativa menor | tonalidade | questionário ≥90% |
| EX-1.G.2 | G | Tocar I–vi–IV–V em Dó (C – Am – F – G) | campo harmônico | detector: C, Am, F, G |
| EX-1.G.3 | G | Tocar a escala de Dó maior (padrão T–T–S–T–T–T–S) | escala maior | detector: C4→C5 |
| EX-1.H.1 | H | Dado `Dm7`, `G7`, `C7M`, dizer o campo harmônico e tocar as tríades | cifrado + tonalidade | detecção de acorde e resposta |
| EX-1.H.2 | H | Dizer o significado de `C`, `Cm`, `C7`, `C7M`, `Cm7`, `C/E` | cifrado | questionário ≥90% |
| EX-1.H.3 | H | Tocar uma cifra com inversão (`C/E`) | cifrado | detector: C maior com baixo em E |
| EX-1.I.1 | I | Contar (`TÁ`/`TÁ-KI`) e tocar a 6ª solta em semínimas na grade | rítmica + grade | `on_grid_ratio ≥ 0,75` a 60 BPM |
| EX-1.I.2 | I | Tocar a 6ª solta em colcheias (`TÁ-KI`) a 60 BPM | subdivisão | `on_grid_ratio ≥ 0,75` |
| EX-1.I.3 | I | Dizer o valor das figuras e as sílabas rítmicas | rítmica | questionário ≥90% |

**Desafio de gate (CM-014/CM-016 do currículo):** tocar a progressão
`C – G – Am – F` (vamp de 1 acorde, nível 1) a **60 BPM** com **≥90% de acerto**
de acordes e `on_grid_ratio ≥ 0,75`.

**Conformidade com `musica.docx` (2026-11-04).** O cliente pediu **≥3 exercícios
por tópico** e **≥5 páginas de explicação por tópico** (A–I), com base nos PDFs
encaminhados. O catálogo agora tem **29 exercícios numerados + o gate**, com
≥3 por tópico, e cada tópico traz a explicação completa em
`Source/Course/Content/Topic*.cpp` (≥5 páginas medidas em `content::minTopicChars`,
verificadas em `tests/TestMain.cpp`). O texto de cada tópico foi escrito para um
iniciante que nunca tocou guitarra e conferido contra as fontes curadas de §1.1.

## 1.4 Patterns e links do módulo (REQ-007, REQ-010)

- **Pattern obrigatório:** `PTN-R-PALM` (pedal point abafado + power chords) —
  primeiro contato com o ritmo e o abafamento; alternativa `PTN-R-BOSSA` para
  quem já tem base de violão.
- **Pattern de escala:** `PTN-M-3` (grupos de 3) sobre a escala de Dó, na 1ª
  posição, para ligar braço × fluência.
- **Links (guitarristas de referência — REQ-007):** um vídeo-aula por referência,
  curado com **citação da fonte** (sem copiar material protegido):
  - **Juninho Afram** — didática de rock nacional e formação de acordes.
  - **Kiko Loureiro** — organização do braço e CAGED aplicado.
  - **John Petrucci** — exercícios mecânicos de aquecimento (ligação com
    `PTN-M-3`).

**Verificação de uso (REQ-010):** o módulo registra o pattern (`PTN-R-PALM`) e o
link; a avaliação confere a assinatura do pattern no trecho tocado (ver
§"Detecção do uso de pattern"). Sem assinatura detectada, o exercício não conta.

# Módulo 6 — Escalas menores e campos harmônicos

> **Etapa 6.** Nível 3, BPM meta **80**, alvo de `on_grid_ratio` **0,80**
> (faixa de estudo 75–82 %). Branch
> `feat/modulo-6-escalas-menores-e-campos-harmonicos`. Fonte de verdade do
> texto: as seções abaixo; o espelho executável vive em
> `Source/Course/Content/Topic6A.cpp` … `Topic6I.cpp` (≥5 páginas por tópico,
> medidas por `content::minTopicChars`).

## 6.1 Conteúdo (curadoria — REQ-006)

As apostilas curadas do módulo (ver §1.1) cobrem as escalas menores e a
formação dos acordes. O texto de cada tópico foi conferido contra elas:

| Apostila | Blocos que sustenta |
|---|---|
| Teoria Elementar da Música (Lacerda) | A, B, D, F, H (escalas, graus, tonalidades) |
| Teoria da Música (Bohumil Med, 5ª ed.) | B, C, D, E, F, I (escalas menores, modos) |
| CAGED e derivações de acordes (Marcelo Mello) | F, G (tríades, acordes do campo) |
| Livro de estudos de guitarra 4 em 1 (Mozart Mello) | F, G (digitações e levadas) |
| Desvendando os segredos da guitarra fusion | E, I (modos e sonoridades modernas) |

## 6.2 Teoria apresentada no módulo

> **Explicação completa por tópico.** Os resumos abaixo são a versão curta. A
> explicação completa (≥5 páginas por tópico, escrita para iniciante) de cada
> bloco A–I vive em `Source/Course/Content/Topic6A.cpp` … `Topic6I.cpp`. Este
> documento permanece a fonte de verdade do conteúdo.

### Bloco A — Escala menor natural

Escala menor natural (ou **eólio**): graus **1 2 b3 4 5 b6 b7**. Em Lá menor:
`A B C D E F G`. É a **relativa menor** de uma escala maior — mesmas notas, outro
repouso (Lá menor = Dó maior). A **terça menor** (b3) define o caráter
melancólico; o b6 e o b7 completam o som escuro. Padrão de tons e semitons:
`T S T T S T T`.

### Bloco B — Escala menor harmônica

Escala menor harmônica: **1 2 b3 4 5 b6 7** — a menor natural com o **7º grau
elevado**. Em Lá menor harmônica: `A B C D E F G#`. O G# é a **sensível** de Lá,
que cria a cadência `V7 → i` (E7 → Am). O salto entre o b6 (Fá) e o 7 (Sol#) é
uma **segunda aumentada**, que dá o caráter exótico ao modo.

### Bloco C — Modos da menor harmônica

A menor harmônica gera **sete modos**, um por grau: (1) menor harmônica, (2)
lócrio 6 natural, (3) jônio #5, (4) dórico #4, (5) **frígio dominante**, (6)
lídio #2, (7) superlócrio bb7. O **5º modo** (frígio dominante, som do flamenco
e do `V7(b9)`) é o mais usado; o 1º e o 4º vêm em seguida. Cada modo combina com
um tipo de acorde do campo menor harmônico.

### Bloco D — Escala menor melódica

Escala menor melódica: **1 2 b3 4 5 6 7** — o **6º e o 7º graus elevados**. Em Lá
menor melódica: `A B C D E F# G#`. Ela sobe suave a partir do 5º grau (sem o
salto da harmônica) e é a base das sonoridades modernas do jazz e da bossa
(acordes `m7M`).

### Bloco E — Modos da menor melódica

A menor melódica também gera **sete modos**: (1) menor melódica, (2) dórico b2,
(3) **lídio aumentado** (`1 2 3 #4 #5 6 7`), (4) **lídio dominante** (`1 2 3 #4 5
6 b7`), (5) mixolídio b6, (6) lócrio 2 natural, (7) **escala alterada**. O 4º
(lídio dominante) e o 7º (alterada) são os mais usados sobre acordes dominantes.

### Bloco F — Campos harmônicos menores e funções dos acordes

**Campo harmônico** é o conjunto de acordes que nasce da escala. O campo **menor
natural** em Lá: `Am  Bm7(b5)  C7M  Dm7  Em7  F7M  G7` (i, ii, III, iv, v, VI,
VII). O campo **menor harmônico** troca o `v` pelo **V7** (E7), criando a
cadência forte. Funções: **tônica** (i, III), **subdominante** (ii, iv, VI),
**dominante** (v/V, VII).

### Bloco G — Subdominantes menores

**Subdominante menor** é um acorde do campo menor paralelo usado dentro do campo
maior. O mais comum é o **iv** menor: `I → IV → iv → I`. Em Dó maior: `C7M –
Fm7` (com `Ab` e `Eb` emprestados). Outros empréstimos: `ii(b5)` (Dm7(b5)),
`bVI` (Abmaj7), `bVII` (Bb7), `bIII` (Ebmaj7) e `bII` (Db, napolitano). São a
cor da MPB, da bossa e do rock.

### Bloco H — Relações entre os campos maior e menor

**Relativa**: mesma armadura, outra tônica (Dó maior ↔ Lá menor). **Paralela**:
mesma tônica, outra armadura (Dó maior ↔ Dó menor). Tonalidades **próximas**
(vizinhas no ciclo das quintas) facilitam a modulação; as **distantes** exigem
acordes-pivô. A mistura dos dois campos é a base da harmonia funcional ampliada.

### Bloco I — Modos dórico, frígio, lídio, mixolídio e lócrio

Os **sete modos gregos** são a escala maior vista de sete pontos de partida:
jônio (maior), dórico (`1 2 b3 4 5 6 b7`), frígio (`1 b2 b3 4 5 b6 b7`), lídio
(`1 2 3 #4 5 6 7`), mixolídio (`1 2 3 4 5 6 b7`), eólio (menor natural) e lócrio
(`1 b2 b3 4 b5 b6 b7`). Cada acorde do campo tem um modo que combina com ele.

## 6.3 Prática (exercícios e desafios — REQ-008)

Cada exercício tem **explicação antes da execução** (REQ-003) e é **medido**
(REQ-009). BPM meta 80 (REQ-015). Cada tópico A–I tem de **3 a 5 exercícios**,
entre questionários (verificáveis por pergunta) e exercícios tocados no
instrumento (verificáveis pelo detector de altura/acorde); o catálogo registra o
tópico em `Exercise::lessonId`.

| ID | Tópico | Exercício | Verificação automática |
|---|---|---|---|
| EX-6.A.1 | A | Questionário: escala menor natural | questionário ≥90% |
| EX-6.A.2 | A | Tocar a terça menor | detector: intervalo de 3 semitons |
| EX-6.A.3 | A | Tocar a sétima menor | detector: intervalo de 10 semitons |
| EX-6.A.4 | A | Graus da menor natural | questionário ≥90% |
| EX-6.B.1 | B | Questionário: escala menor harmônica | questionário ≥90% |
| EX-6.B.2 | B | Tocar a sétima maior (sensível) | detector: intervalo de 11 semitons |
| EX-6.B.3 | B | Tocar a sexta menor | detector: intervalo de 8 semitons |
| EX-6.B.4 | B | Menor natural x harmônica | questionário ≥90% |
| EX-6.C.1 | C | Questionário: modos da menor harmônica | questionário ≥90% |
| EX-6.C.2 | C | Tocar a segunda menor (frígio dominante) | detector: intervalo de 1 semitom |
| EX-6.C.3 | C | Aplicar os modos | questionário ≥90% |
| EX-6.D.1 | D | Questionário: escala menor melódica | questionário ≥90% |
| EX-6.D.2 | D | Tocar a sétima maior | detector: intervalo de 11 semitons |
| EX-6.D.3 | D | Tocar a sexta maior | detector: intervalo de 9 semitons |
| EX-6.D.4 | D | As três menores | questionário ≥90% |
| EX-6.E.1 | E | Questionário: modos da menor melódica | questionário ≥90% |
| EX-6.E.2 | E | Tocar o trítono (lídio dominante) | detector: intervalo de 6 semitons |
| EX-6.E.3 | E | Tocar a segunda menor (alterada) | detector: intervalo de 1 semitom |
| EX-6.E.4 | E | Modos e acordes da melódica | questionário ≥90% |
| EX-6.F.1 | F | Questionário: campos harmônicos menores | questionário ≥90% |
| EX-6.F.2 | F | Montar a tríade menor | detector: acorde menor |
| EX-6.F.3 | F | Montar a tríade diminuta | detector: acorde diminuto |
| EX-6.F.4 | F | Funções no campo menor | questionário ≥90% |
| EX-6.G.1 | G | Questionário: subdominantes menores | questionário ≥90% |
| EX-6.G.2 | G | Montar o iv menor | detector: acorde menor |
| EX-6.G.3 | G | Tocar a progressão I–iv–I | detector: C7M – Fm7 – C7M |
| EX-6.G.4 | G | Empréstimos do campo menor | questionário ≥90% |
| EX-6.H.1 | H | Questionário: relações entre os campos | questionário ≥90% |
| EX-6.H.2 | H | Tocar a sexta maior (relativa) | detector: intervalo de 9 semitons |
| EX-6.H.3 | H | Maior, relativa e paralela | questionário ≥90% |
| EX-6.I.1 | I | Questionário: modos gregos | questionário ≥90% |
| EX-6.I.2 | I | Tocar a quarta aumentada (lídio) | detector: intervalo de 6 semitons |
| EX-6.I.3 | I | Tocar a sétima menor (mixolídio) | detector: intervalo de 10 semitons |
| EX-6.I.4 | I | Modos e acordes | questionário ≥90% |

**Desafio de gate:** tocar a cadência menor **ii–V–i** `Bm7(b5) – E7 – Am7 –
Am7` a **80 BPM** com **≥90 % de acerto** de acordes e `on_grid_ratio ≥ 0,80`.
Os acordes vêm do campo harmônico menor estudado no módulo (REQ-009, REQ-015).

## 6.4 Patterns e links do módulo (REQ-007, REQ-010)

- **Pattern obrigatório:** `PTN-M-3rds` (terças: 1-3, 2-4, 3-5…) sobre a escala
  menor, para ouvir a terça — que define o caráter menor — em movimento.
- **Complemento:** `PTN-A-TRIAD` (arpejos de tríade) para tocar os acordes do
  campo menor.
- **Links (guitarristas de referência — REQ-007):** um vídeo-aula por referência,
  curado com **citação da fonte** (sem copiar material protegido):
  - **Wes Montgomery** — acordes e terças no jazz.
  - **Pat Metheny** — sonoridades modais e campos harmônicos.
  - **Santana** — o modo dórico e o som modal latino.

**Verificação de uso (REQ-010):** o módulo registra o pattern (`PTN-M-3rds`) e os
links; a avaliação confere a assinatura do pattern no trecho tocado (ver
§"Detecção do uso de pattern"). Sem assinatura detectada, o exercício não conta.

# Módulo 7 — Empilhamentos, estruturas modais e sonoridades

**Nível:** 3 (II–V–I) · **BPM meta:** 84 (REQ-015) · **Gate:** 90% (REQ-009) ·
**`on_grid_ratio`:** 0,80 (faixa de estudo 75–82%)
**Objetivo:** conhecer estruturas harmônicas além das tríades e tétrades
convencionais — empilhamentos, estruturas modais, tríades do meio e as
sonoridades modais do dórico ao alterado.

> **Regra de ouro (REQ-003):** a explicação vem **antes** de qualquer desafio.
> Nenhum desafio abre sem que o conteúdo abaixo tenha sido apresentado.

## 7.1 Conteúdo (curadoria — REQ-006)

| Tópico | Tema | Apostila de referência |
|---|---|---|
| A | Empilhamentos de terças | `pdf-caged-e-derivaoes-de-acordes-marcelo-mello-…-vol1` |
| B | Empilhamentos quartais | `pdf-caged-e-derivaoes-de-acordes-marcelo-mello-…-vol1` |
| C | Outros empilhamentos | `pdf-caged-e-derivaoes-de-acordes-marcelo-mello-…-vol1` |
| D | Estruturas modais e tríades do meio | `pdf-caged-e-derivaoes-de-acordes-marcelo-mello-…-vol1` |
| E | Acordes e famílias modais | `pdf-teoria-elementar-…-lacerda`, `pdf-p-…-bohumil-med-…` |
| F | Modos estruturais pelo CAGED | `pdf-caged-e-derivaoes-de-acordes-marcelo-mello-…-vol1` |
| G | Dórico, Lídio e Mixolídio | `pdf-desvendando-os-segredos-da-guitarra-fusion` |
| H | Mixolídio sus e Mixolídio #4 | `pdf-desvendando-os-segredos-da-guitarra-fusion` |
| I | Lócrio 9 e Alterado (Alt.7) | `pdf-desvendando-os-segredos-da-guitarra-fusion` |
| J | Aplicações modais no rock e pop-rock | `pdf-mozart-mello-livroestudosdeguitarra4em1` |

## 7.2 Teoria apresentada no módulo

- **A — Empilhamentos de terças.** Somar terças sobrepostas; a mistura de
  terças maiores e menores define a qualidade; as tensões 9, 11 e 13 são os
  graus 2, 4 e 6 uma oitava acima.
- **B — Empilhamentos quartais.** Quartas justas (5 semitons) produzem um som
  suspenso e modal (o acorde de *So What* empilha quartas com uma terça no topo);
  sem a terça, o acorde não é maior nem menor.
- **C — Outros empilhamentos.** Quintas dão força (power chords); segundas dão
  tensão (clusters); mistos dão cor sob medida.
- **D — Estruturas modais e tríades do meio.** Estruturas que reforçam um modo
  sem criar resolução; tríades construídas sobre graus internos da escala.
- **E — Acordes e famílias modais.** Cada acorde carrega uma família de modos:
  maiores (jônio, lídio), menores (dórico, eólio, frígio), dominantes
  (mixolídio, lídio dominante, alterado, sus), meio-diminuto (lócrio).
- **F — Modos estruturais pelo CAGED.** O CAGED como mapa do braço: cada forma
  contém a escala do tom; os modos são a mesma escala vista de graus diferentes.
- **G — Dórico, Lídio e Mixolídio.** Fórmulas 1 2 b3 4 5 6 b7 (dórico),
  1 2 3 #4 5 6 7 (lídio) e 1 2 3 4 5 6 b7 (mixolídio); notas características e
  de repouso.
- **H — Mixolídio sus e Mixolídio #4.** 1 2 4 5 6 b7 (sus, combina com X7sus4) e
  1 2 3 #4 5 6 b7 (#4, combina com X7#11).
- **I — Lócrio 9 e Alterado (Alt.7).** 1 2 b3 4 b5 b6 b7 (lócrio 9, II grau do
  II–V–I menor) e 1 b9 #9 3 b5 #5 b7 (alterado, V grau; resolve meio-tom abaixo).
- **J — Aplicações modais no rock e pop-rock.** Vamps de um ou dois acordes; cada
  modo tem um tipo de vamp e uma cor; do modal se chega à harmonia funcional.

## 7.3 Prática (exercícios e desafios — REQ-008)

Cada tópico A–J tem **de 3 a 5 exercícios** (ids `EX-7.<tópico>.<n>`), misturando
questionários verificáveis e exercícios **tocados no instrumento** que o app
reconhece (por classes de altura ou por sequência de notas). Os exercícios de
identificação **não** são presos à grade (`usesGrid = false`).

**Desafio de gate (REQ-009/REQ-015):** tocar `Dm7 – G7 – C7M – C7M` (II–V–I,
nível 3) a **84 BPM** com **≥90% de acerto** de acordes e `on_grid_ratio ≥ 0,80`.

## 7.4 Patterns e links do módulo (REQ-007, REQ-010)

- **Pattern de acordes:** `PTN-A-DROP2` (tétrades em drop 2 nas quatro cordas),
  que mostra na prática os empilhamentos de terça e as tríades do meio.
- **Complemento:** `PTN-M-4ths` (empilhamento de quartas) para as estruturas
  modais.
- **Links (guitarristas de referência — REQ-007):** Joe Satriani, Steve Vai e
  Guthrie Govan (uso de estruturas modais e empilhamentos).

---

# Módulo 11 — Referências de escalas e domínio do braço

**Nível:** 5 (blues) · **BPM meta:** 100 (REQ-015) · **Gate:** 90% (REQ-009) ·
**`on_grid_ratio`:** 0,82 (faixa de estudo 75–82%)
**Objetivo:** transformar o conhecimento das escalas em **referências para
construir frases** — desenhos por região, escalas nos dois sentidos,
pentatônicas acrescentadas (menor 6 e menor 7), as cinco posições, trilhas
abertas e fechadas, o Sistema 5 (CAGED), as menores harmônica e melódica, e a
relação entre escalas e acordes que sustenta o **improviso**.

> **Regra de ouro (REQ-003):** a explicação vem **antes** de qualquer desafio.
> Nenhum desafio abre sem que o conteúdo abaixo tenha sido apresentado.

> **Dois requisitos do cliente.** (1) **Cada tópico tem um lick** — uma frase
> que o aluno deve tocar para completar o exercício do tópico. (2) Todo exercício
> é **tocado no instrumento** e verificado pelo app; não há questionário neste
> módulo. É também o **primeiro módulo com avaliação de improvisação**
> (REQ-011/REQ-012): o app classifica cada nota contra o contexto harmônico.

## 11.1 Conteúdo (curadoria — REQ-006)

| Tópico | Tema | Lick (guitarrista) | Apostila de referência |
|---|---|---|---|
| A | Desenhos de escalas por regiões | LK-11.A (John Petrucci) | `pdf-fraseado-melodico` |
| B | Escalas ascendentes e descendentes | LK-11.B (Guthrie Govan) | `pdf-fraseado-melodico` |
| C | Pentatônica menor 7 | LK-11.C (Richie Kotzen) | `pdf-desvendando-os-segredos-da-guitarra-fusion` |
| D | Pentatônica menor 6 | LK-11.D (Greg Howe) | `pdf-mozart-mello-improvisacion-pop` |
| E | Cinco desenhos da pentatônica | LK-11.E (Edu Ardanuy) | `pdf-mozart-mello-livroestudosdeguitarra4em1` |
| F | Trilhas abertas e fechadas | LK-11.F (Joe Satriani) | `pdf-fraseado-melodico` |
| G | Sistema 5 (CAGED) | LK-11.G (Kiko Loureiro) | `pdf-caged-e-derivaoes-de-acordes-marcelo-mello-…-vol1` |
| H | Escala menor harmônica | LK-11.H (Yngwie Malmsteen) | `pdf-fraseado-melodico` |
| I | Escala menor melódica | LK-11.I (Steve Vai) | `pdf-fraseado-melodico` |
| J | Relação entre escalas e acordes | LK-11.J (Santana) | `pdf-mozart-mello-improvisacion-pop` |

## 11.2 Teoria apresentada no módulo

- **A — Desenhos de escalas por regiões.** Uma região é um trecho de 4–5 casas
  onde a escala cabe sob os quatro dedos (um dedo por casa); o desenho é a
  escala com forma fixa; as regiões se ligam pela nota comum.
- **B — Escalas ascendentes e descendentes.** Subir e descer pedem digitações
  diferentes; a descida é o ponto onde a mão trava; a escala parelha no
  metrônomo é o termômetro da mão antes da frase.
- **C — Pentatônica menor 7.** É a **própria pentatônica menor** (1-b3-4-5-b7,
  **cinco notas** em Lá: A C D E G). O "7" nomeia a **sétima menor** que já
  pertence à escala e dá o som do acorde **m7** — a apostila de fusion é
  explícita ("a escala pentatônica menor 7 é formada por 5 notas").
- **D — Pentatônica menor 6.** A pentatônica menor com a **sexta maior no lugar
  da sétima menor** (1-b3-4-5-6, **cinco notas** em Lá: A C D E F#); a sexta
  maior é a nota característica do **m6** (som dórico) e é **cor de repouso**.
  Sobre m7 usa-se a menor 7; sobre m6, a menor 6.
- **E — Cinco desenhos da pentatônica.** Cinco posições (uma por nota da
  pentatônica); posições vizinhas compartilham notas; a posição 5 é a 1 uma
  oitava acima.
- **F — Trilhas abertas e fechadas.** Trilha fechada: escala dentro da posição
  (mão parada); trilha aberta: escala ao longo de uma ou duas cordas (mão
  viajando); o fraseado maduro alterna as duas.
- **G — Sistema 5 (CAGED).** Cinco formas de acorde (C-A-G-E-D), cada uma com um
  desenho de escala ao redor; trocar de acorde é trocar de forma e de escala.
- **H — Escala menor harmônica.** A menor natural com o 7º grau elevado
  (1-2-b3-4-5-b6-7); a elevação cria a **segunda aumentada** (F–G# em Lá) e
  transforma o 5º grau em dominante.
- **I — Escala menor melódica.** A menor natural com o 6º e o 7º graus elevados
  (1-2-b3-4-5-6-7); sem a segunda aumentada, sobe por graus conjuntos — a escala
  menor cantável.
- **J — Relação entre escalas e acordes.** A escala vem do acorde (7M → maior/
  lídia; m7 → dórica/menor; 7 → mixolídia/alterada; m7(b5) → lócrio); a escala
  define as **notas de repouso**; fora do centro, a nota é **tensão não pedida**
  — erro (REQ-012).

## 11.3 Prática (exercícios e desafios — REQ-008)

Cada tópico A–J tem **3 exercícios** (ids `EX-11.<tópico>.<n>`), todos **tocados
no instrumento** e verificados pelo app — não há questionário neste módulo. O
**primeiro exercício de cada tópico obriga o lick do tópico** (o aluno toca a
frase, nota a nota). Os exercícios de **improvisação** (REQ-011/REQ-012) são
avaliados pela classificação das notas contra o contexto (repouso, tensão pedida
ou erro) e **não** são presos à grade (`usesGrid = false`).

**Desafio de gate (REQ-009/REQ-015):** tocar o lick do tópico J (frase de
repouso e tensão sobre o vamp de Lá menor) a **100 BPM** com **≥90% de acerto**
de notas e `on_grid_ratio ≥ 0,82`.

## 11.4 Patterns e links do módulo (REQ-007, REQ-010)

- **Pattern de escalas:** `PTN-M-3` (grupos de 3: 1-2-3, 2-3-4, 3-4-5…) — o
  padrão que constrói as frases do módulo; complemento `PTN-M-3rds` (terças).
- **Links (guitarristas de referência — REQ-007):** John Petrucci, Guthrie Govan
  e Kiko Loureiro (uso de desenhos de escala e domínio do braço).
