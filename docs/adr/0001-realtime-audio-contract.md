# 0001 — Contrato de tempo real entre áudio e UI

Status: accepted
Data: 2026-11-02
Autor: architect

## Contexto

O requisito nº 1 do produto é latência baixíssima (alvo ≤ 10 ms de ida e volta,
buffer 64–128 samples, ASIO). A UI precisa mostrar nível e afinação em tempo
real, e a cadeia de plugins VST3 processa o sinal na entrada.

Qualquer alocação, lock ou I/O na thread de áudio causa glitch/xrun e destrói o
requisito. Portanto o contrato entre a thread de áudio e o resto do sistema
precisa ser explícito e verificável.

## Decisão

1. A thread de áudio **nunca** aloca, nunca faz lock, nunca faz I/O.
2. A comunicação UI ↔ áudio usa **apenas** `std::atomic` e FIFO lock-free
   (`juce::AbstractFifo`).
3. A análise pesada (YIN) roda em uma **thread de análise dedicada** que drena o
   FIFO; o callback apenas publica amostras e lê o nível calculado.
4. A cadeia de plugins publica um array de ponteiros por **índice atômico**; a
   troca estrutural segue aplicar → publicar índice → esperar a thread de áudio
   reportar o índice processado → liberar as instâncias antigas.
5. A UI consome **somente** os getters públicos de `cursomusica::AudioEngine`
   (nível, frequência, sample rate, block size, latência estimada, running).

## Alternativas rejeitadas

- **Mutex/`std::lock_guard` entre UI e áudio:** risco de inversão de prioridade e
  bloqueio do callback → rejeitado.
- **Análise YIN no callback:** custo não limitado, estoura o orçamento de tempo
  do buffer → rejeitado.
- **UI lendo estado interno do engine diretamente:** acopla camadas e quebra o
  contrato de tempo real → rejeitado.

## Consequências

- O QA pode testar os invariantes (nenhuma alocação no caminho do callback) de
  forma estática/harness.
- O developer deve manter o callback mínimo; qualquer feature que precise de
  trabalho pesado vai para a thread de análise ou para um worker.
- O designer só usa os getters públicos; nunca alcança internals do engine.
