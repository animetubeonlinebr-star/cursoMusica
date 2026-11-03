# 0004 — Metrônomo com meta de andamento e currículo por standards

Status: accepted
Data: 2026-11-02
Autor: architect + musician + pm (requisitos REQ-015, REQ-016, REQ-002)

## Contexto

O requisito acrescenta duas coisas que afetam o modelo de progressão:

1. **REQ-015:** o aluno pratica com **metrônomo** e cada desafio tem um **BPM
   meta**; se o aluno **não atingir o BPM alvo, não avança** de módulo. Isso é um
   **segundo eixo de gate**, além da acurácia de 90% (REQ-009).
2. **REQ-016 / mapa de standards:** os standards funcionam como "livros de
   exercícios vivos" organizados por complexidade; cada nível de improvisação
   ancora-se em standards concretos (`docs/MUSIC.md`).

## Decisão

1. **Dois eixos de gate, ambos obrigatórios.** O módulo só libera quando:
   - `accuracy >= 0,90` (REQ-009), **e**
   - o aluno atinge o **BPM meta** do desafio com qualidade (REQ-015).
2. **BPM meta por desafio.** Cada desafio declara `target_bpm`. O sistema mede o
   **maior BPM em que o aluno executou o desafio dentro da tolerância**
   (`achieved_bpm`) e compara com a meta.
3. **O BPM meta sobe progressivamente ao longo do currículo.** Não há salto para
   uma velocidade não construída: o alvo cresce módulo a módulo (60 → 140),
   terminando na velocidade de performance. Do módulo 15 ao 20 a subida é de
   **+4 BPM por módulo**. Tabela completa em `docs/MUSIC.md`.
4. **Como medir o andamento atingido.** O tempo é derivado da grade de
   subdivisão do metrônomo e do alinhamento das notas detectadas: o aluno precisa
   tocar as notas na grade (tolerância de janela definida pelo musician) no BPM
   alvo. Não é "tocar rápido", é "tocar certo no tempo".
5. **O alvo de alinhamento cresce com o módulo.** Módulos 1–14 exigem
   `on_grid_ratio` na faixa **0,75–0,82** (precisão com respiração natural —
   exigir 0,90 cedo torna a execução robótica); do módulo 15 ao 20 a exigência
   sobe **progressivamente** (0,82 → 0,90). Racional completo em `docs/MUSIC.md`.
6. **A grade modela a síncope.** Em bossa/samba a síncope desloca a grade de
   propósito; a tolerância precisa refletir isso, senão o aluno é penalizado por
   tocar certo (R-13).
7. **O metrônomo é o árbitro.** O BPM vem do metrônomo do próprio app (REQ-015),
   então a medição é determinística e não depende de tempo externo.
8. **Currículo ancorado em standards.** Cada nível 1–7 cita o(s) standard(s) que
   materializam o conceito (`docs/MUSIC.md` §"Standards como laboratório
   progressivo"). O standard é usado como progressão de estudo, nunca como
   gravação.
9. **Sem regressão do ADR 0003.** O override de teste (REQ-013) continua
   liberando o acesso, mas **ambos** os gates seguem sendo calculados e
   registrados.

## Alternativas rejeitadas

- **Só acurácia, ignorando tempo** — o requisito exige meta de andamento; sem
  isso, "tocar certo" a qualquer velocidade passaria.
- **BPM como sugestão, não gate** — contraria REQ-015 ("não avançar").
- **Medir tempo por relógio externo** — não determinístico e não auditável.
- **Currículo sem standards concretos** — vira teoria solta; o requisito pede o
  laboratório (standards) por nível.

## Consequências

- O **data-engineer** acrescenta `target_bpm`/`achieved_bpm` ao schema
  (`docs/DATA.md`, migração v3) e o cálculo do gate de andamento.
- O **musician** define a janela de tolerância rítmica por subdivisão e o BPM
  meta de cada desafio, por nível.
- O **developer** implementa a medição de andamento a partir do metrônomo, fora
  da thread de áudio.
- O **QA** testa: atingir a meta libera; ficar 1 BPM abaixo não libera; tocar
  fora da grade não conta como BPM atingido.
- O **PO** escreve os critérios numéricos e o **devops** segue publicando o
  instalador de teste por módulo (REQ-013).
