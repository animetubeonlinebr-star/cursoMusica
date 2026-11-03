# STATUS — CursoMusica

Dono: **project-manager**. Atualizar ao fim de cada ciclo, a partir de evidência
do repositório (commits, CI, resultados de QA), nunca de otimismo.

## Ciclo atual — [data: 2026-11-02]

- **Milestone em foco:** M1 — Módulo 1 jogável com gate de progressão.
- **Progresso:** **Módulo 1 fechado de ponta a ponta.** O aluno lê a explicação
  (blocos A–H), vê CAGED, trilha de prática (`PTN-R-PALM`, guitarristas citados,
  REQ-007), os exercícios EX-1.1–EX-1.7 e o desafio de gate. O motor de medição
  (`NoteMath`, `ExerciseEvaluator`, `TempoGrid`, `PracticeSession`) e o metrônomo
  RT-safe (CM-014) medem a execução; ao atingir **≥90%** o Módulo 2 desbloqueia e
  o resultado é persistido (`ProgressStore`).
- **Métricas:** suíte de lógica pura com **50 checagens, 100% verdes**, rodando no
  CI (`ctest` no job Linux). Velocity/Lead Time ainda sem baseline.
- **Blockers:** nenhum para M1. Pendente para M2+: decisão D4 (estratégia de
  síntese) — owner: architect.
- **Riscos (top 3):** R-10 (avaliação de improvisação injusta), R-13 (meta de BPM
  mal calibrada), R-12 (assinatura do instalador). R-08 condicional.
- **Próximo:** M2 (Módulos 2–7 do currículo) e ligar a UI principal à engine
  (CM-001). Avaliação de improvisação fica para M2b.

## Histórico

| Ciclo | Milestone | Resultado | Evidência |
|---|---|---|---|
| 2026-11-02 | M1 | Módulo 1 jogável + gate ≥90% com desbloqueio persistido + pattern/links REQ-007 | commit do Módulo 1 na branch `feat/measurement-engine`; 50/50 testes |
| 2026-11-02 | M0 | Agentes + memória compartilhada criados | commits na branch `feat/multi-agent-framework` |
| 2026-11-02 | M0 | Requisitos de sistema formalizados (REQ-001..REQ-014) e backlog/ADRs derivados | `docs/REQUIREMENTS.md`, `docs/adr/0002`, `docs/adr/0003` |
