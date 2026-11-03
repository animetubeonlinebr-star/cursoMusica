# 0002 — Stack de partitura, MIDI e áudio

Status: proposed
Data: 2026-11-02
Autor: architect (a partir do requisito de stack de `docs/REQUIREMENTS.md` §F)

## Contexto

O produto passa de afinador a **plataforma de estudo modular** que ensina,
demonstra com áudio, gera desafios e avalia improvisação
(`docs/REQUIREMENTS.md`). Isso exige, além da engine de entrada que já existe:

- ler partituras (XML) — REQ-004;
- construir eventos MIDI — REQ-004;
- sintetizar/reproduzir áudio (acompanhamento, exemplos, vamps) — REQ-003/REQ-004;
- carregar samples `.wav` de instrumentos — REQ-004.

O requisito propõe as bibliotecas abaixo. A restrição que domina tudo continua
sendo **latência e tempo real** (requisito nº 1): a reprodução/síntese **não**
pode rodar na thread de áudio nem introduzir locks no callback de entrada.

| Componente | Biblioteca proposta | Função |
|---|---|---|
| Parser de partitura | pugixml ou TinyXML2 | ler a estrutura XML da partitura |
| Manipulação MIDI | midifile (Craig Sapp) | criar e estruturar eventos MIDI |
| Motor de áudio / síntese | FluidSynth ou RtAudio | fluxo de saída de som e placas |
| Leitura de samples | libsndfile | carregar `.wav` de instrumentos |

## Decisão

1. **Parser de partitura: `pugixml`.** Mais leve, header-only opcional, API
   estável, licença MIT e sem dependências — preferível a TinyXML2 para
   performance de parsing de MusicXML.
2. **MIDI: `midifile` (Craig Sapp).** É a referência para leitura/escrita de
   SMF; cobre a criação e a estruturação de eventos exigidas.
3. **Síntese: `FluidSynth`** para acompanhamento baseado em SoundFont, atrás de
   um **adaptador** próprio; **RtAudio** é candidato para I/O de áudio adicional
   caso se precise de um segundo fluxo fora do JUCE. O JUCE continua sendo o
   dono do I/O principal e do callback de entrada.
4. **Samples: `libsndfile`.** Padrão para `.wav`; usado no carregamento de
   instrumentos fora da thread de áudio.
5. **Regra de tempo real inegociável:** parsing, MIDI, síntese e I/O de arquivo
   rodam em **threads de trabalho** (message thread ou worker dedicado). O
   callback de entrada só consome buffers já preparados, por FIFO lock-free ou
   buffer pré-alocado — nunca chama FluidSynth/libsndfile/parsers diretamente.

## Alternativas rejeitadas

- **TinyXML2** — viável, mas menos performático que pugixml no volume de um
  MusicXML completo.
- **Síntese dentro do callback de entrada** — viola o contrato de tempo real
  (ADR 0001). Rejeitado.
- **Um segundo framework de áudio disputando o dispositivo** — risco de conflito
  de driver e de latência. RtAudio só entra como fluxo auxiliar, nunca no lugar
  do JUCE para a entrada.

## Consequências

- Novas dependências externas entram no build → precisam de licença compatível
  (pugixml MIT, libsndfile LGPL, FluidSynth LGPL, midifile sem restrição) e de
  pinagem de versão no CMake. O **architect** é o dono do `CMakeLists.txt`.
- O **developer** implementa o adaptador de síntese e o caminho de conversão
  partitura → MIDI → áudio fora da thread de áudio.
- O **musician** valida a correção musical (altura, oitava/transposição,
  duração, dinâmica) do resultado.
- O **QA** testa: mesma partitura → mesmo áudio (determinismo), oitava correta
  para guitarra (transposição), e ausência de alocação no callback.

## Pendências

- Confirmar licenças e formas de distribuição de cada biblioteca no instalador
  (REQ-013).
- Definir o SoundFont base (licença) e o conjunto inicial de samples.
