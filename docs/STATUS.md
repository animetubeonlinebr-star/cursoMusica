# STATUS — CursoMusica

Dono: **project-manager**. Atualizar ao fim de cada ciclo, a partir de evidência
do repositório (commits, CI, resultados de QA), nunca de otimismo.

## Ciclo atual — [data: 2026-11-05]

- **Milestone em foco:** M1 — Módulo 1 jogável com gate de progressão.
- **Progresso:** **Módulo 1 fechado de ponta a ponta.** O aluno lê a explicação
  (blocos A–I, incluindo rítmica/contagem), vê CAGED, trilha de prática
  (`PTN-R-PALM`, guitarristas citados, REQ-007), os exercícios EX-1.1–EX-1.10 e o
  desafio de gate; as apostilas curadas são citadas na seção "Apostilas"
  (REQ-006). A execução é por **seleção de tópico**: o menu de módulos é
  expansível, o tópico escolhido carrega a explicação detalhada no centro e
  filtra os exercícios à direita; o **EX-1.1** é um questionário de 7 questões
  (`QuizSession`, gate 90%). O motor de medição (`NoteMath`, `ExerciseEvaluator`, `TempoGrid`,
  `PracticeSession`) e o metrônomo RT-safe (CM-014) medem a execução; ao atingir
  **≥90%** o Módulo 2 desbloqueia e o resultado é persistido (`ProgressStore`).
- **Métricas:** suíte de lógica pura com **150 checagens, 100% verdes**, rodando no
  CI (`ctest` no job Linux). Velocity/Lead Time ainda sem baseline.
- **Blockers:** nenhum para M1. Pendente para M2+: decisão D4 (estratégia de
  síntese) — owner: architect.
- **Riscos (top 3):** R-10 (avaliação de improvisação injusta), R-13 (meta de BPM
  mal calibrada), R-12 (assinatura do instalador). R-08 condicional.
- **Apostilas novas (revisão da `adequacao`, 2026-11-04):** a branch `adequacao`
  foi reescrita a partir da nova `main` e trouxe **4 apostilas** (CAGED/Marcelo
  Mello, Teoria Elementar/Lacerda, Teoria da Música/Bohumil Med, Manual de
  regulagem/Mozart Carvalho). A curadoria do Módulo 1 passou de 3 para **7
  fontes** (`CourseModule::sources`), com o mapa bloco → fonte atualizado em
  `docs/MUSIC.md` §1.1.
- **Próximo:** publicar instalador de teste atualizado na branch `test`
  (Módulos 2–7 e engine na UI principal ficam para M2/CM-001).

## Histórico

| Ciclo | Milestone | Resultado | Evidência |
|---|---|---|---|
| 2026-11-05 | M1 | Curadoria ampliada com as 4 apostilas novas da `adequacao` (CAGED, teoria elementar, teoria da música, regulagem); instalador de teste atualizado | `docs/MUSIC.md` §1.1; `CourseModule::sources` (7); 150/150 testes |
| 2026-11-04 | M1 | Ajustes do `musica.docx` (REQ-019..023) publicados na branch `test` com instalador de teste | merge `3603ee6`; instalador commit `d031d86`; 146/146 testes |
| 2026-11-02 | M1 | Módulo 1 jogável + gate ≥90% com desbloqueio persistido + pattern/links REQ-007 | commit do Módulo 1 na branch `feat/measurement-engine`; 85/85 testes |
| 2026-11-02 | M0 | Agentes + memória compartilhada criados | commits na branch `feat/multi-agent-framework` |
| 2026-11-02 | M0 | Requisitos de sistema formalizados (REQ-001..REQ-014) e backlog/ADRs derivados | `docs/REQUIREMENTS.md`, `docs/adr/0002`, `docs/adr/0003` |
