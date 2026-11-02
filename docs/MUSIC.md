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
