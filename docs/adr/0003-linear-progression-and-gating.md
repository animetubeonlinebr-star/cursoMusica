# 0003 — Progressão linear com níveis e gate de 90%

Status: accepted
Data: 2026-11-02
Autor: architect + pm (requisitos REQ-002, REQ-009)

## Contexto

O requisito pede **progressão linear** com **progressão baseada em níveis**: o
aluno avança por módulos em ordem e só passa ao próximo com **≥ 90% de acerto**,
e **todo processo é mensurado**. Além disso, o ensino de improvisação precisa
**verificar se o link e o pattern foram usados** (REQ-010) e avaliar notas de
repouso × tensão (REQ-011/REQ-012).

Isso é um modelo de estado do aluno + um motor de avaliação. Precisa ser
determinístico, auditável e testável.

## Decisão

1. **Modelo de curso como grafo linear de níveis.** Cada módulo tem um nível
   inteiro; `nível N+1` só é desbloqueado quando o `nível N` atinge o gate.
2. **Gate = 90% de acerto por módulo**, calculado sobre os desafios do módulo,
   com a fórmula: `acerto = acertos / tentativas`, mínimo de tentativas por
   desafio para a amostra ser válida (a definir com o musician/QA).
3. **Todo processo é mensurado.** Cada tentativa registra: módulo, desafio,
   início/fim, resultado, notas tocadas, classificação (repouso/tensão/erro),
   uso de link e uso de pattern. Nada é aprovado por "achismo".
4. **Avaliação de improvisação é determinística e explicável.** Dado o contexto
   harmônico (acorde/escala vigente) e o estado de improviso pedido, cada nota é
   classificada e a pontuação é derivada dessa classificação
   (`docs/MUSIC.md`). O aluno pode ver *por que* errou.
5. **Tensão só conta a favor se pedida.** Fora do estado que a solicita, tensão
   não pedida é erro (REQ-012).
6. **Uso de link/pattern é parte do gate.** Sem link estudado e pattern
   detectado, o exercício não conta como concluído (REQ-010).
7. **Override de teste.** Existe um modo de acesso liberado sem restrição para
   os instaladores da branch de teste (REQ-013): todos os módulos abertos, sem
   exigir os anteriores. Esse modo é explícito e não afeta o cálculo real.

## Alternativas rejeitadas

- **Progressão adaptativa/aleatória** — o requisito é linear; adaptativa
  contraria REQ-002.
- **Gate subjetivo ("o aluno parece pronto")** — não mensurável; contraria
  REQ-009.
- **Tensão sempre aceita** — contraria REQ-012.
- **Desbloqueio por tempo de uso** — mede presença, não acerto; contraria REQ-009.

## Consequências

- O **data-engineer** modela as tabelas de tentativa/resultado e o cálculo do
  gate (`docs/DATA.md`).
- O **musician** define a função de classificação repouso/tensão e o mínimo de
  tentativas por desafio.
- O **PO** escreve as histórias com os critérios numéricos; o **QA** testa o
  gate (90% passa, 89,9% não) e o override de teste.
- O **devops** publica o instalador da branch de teste com o acesso liberado
  (REQ-013).
