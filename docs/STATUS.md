# STATUS — CursoMusica

Dono: **project-manager**. Atualizar ao fim de cada ciclo, a partir de evidência
do repositório (commits, CI, resultados de QA), nunca de otimismo.

## Ciclo atual — [data: 2026-11-07]

- **Milestone em foco:** M1 — Módulo 1 jogável com gate de progressão.
- **Progresso:** **Módulo 1 fechado de ponta a ponta.** O aluno lê a explicação
  (blocos A–I, incluindo rítmica/contagem), vê CAGED, trilha de prática
  (`PTN-R-PALM`, guitarristas citados, REQ-007), os exercícios EX-1.A.1–EX-1.I.3 e o
  desafio de gate; as apostilas curadas são citadas na seção "Apostilas"
  (REQ-006). A execução é por **seleção de tópico**: o menu de módulos é
  expansível, o tópico escolhido carrega a explicação detalhada no centro e
  filtra os exercícios à direita; o **EX-1.A.1** é um questionário de 7 questões
  (`QuizSession`, gate 90%). O motor de medição (`NoteMath`, `ExerciseEvaluator`, `TempoGrid`,
  `PracticeSession`) e o metrônomo RT-safe (CM-014) medem a execução; ao atingir
  **≥90%** o Módulo 2 desbloqueia e o resultado é persistido (`ProgressStore`).
- **Conformidade com o `musica.docx` (2026-11-05, 2ª revisão).** As 9 capturas
  do documento foram extraídas e o app foi executado (Xvfb, 1040×680 — a mesma
  janela das capturas) para comparar estado a estado. Corrigido: **REQ-019** —
  abrir um módulo nunca lido agora deixa o centro **em branco** (só o contexto
  do módulo: cabeçalho, nível/BPM/gate e objetivo), sem CAGED, rítmica, trilha
  nem fontes; **REQ-022** — o tópico H (cifrado) passou a ter exercício
  **executável** (EX-1.H.1, progressão ii–V–I Dm7–G7–C7M), de modo que todo tópico
  A–I tem ≥1 exercício que o app verifica, não só questionário. REQ-020 (mantém o
  tópico ao voltar ao mesmo módulo, limpa ao trocar de módulo), REQ-021
  (exercício à direita, explicação no centro) e REQ-023 (classificador de portas
  do VoiceMeeter) já estavam corretos.
- **Revisão do painel de quiz (2026-11-07).** A pedido do cliente, o
  **questionário (EX-1.A.1) passou a rodar no painel central** (REQ-021 revisado):
  o centro mostra o cabeçalho do módulo (nível/BPM/gate), a instrução "Responda
  uma questão por vez.", "Questão X de Y", o enunciado e as alternativas
  clicáveis A–D; o **painel direito** ficou com os controles — cabeçalho com o
  link "Todos os tópicos do módulo", seletor de exercício, botão de play com
  `id — título`, placar "Acertos x/y · aproveitamento z%" e a caixa de orientação
  ("Neste exercício, você deverá responder as questões…"). Validado sob Xvfb
  (1040×680): responder uma alternativa avança a questão e atualiza o placar.
- **Métricas:** suíte de lógica pura com **160 checagens, 100% verdes**, rodando no
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
- **Próximo:** M2 (Módulos 2–7 do currículo) e ligar a UI principal à engine
  (CM-001). Avaliação de improvisação fica para M2b. Instalador de teste com a
  conformidade REQ-019..023 e os diagramas embutidos publicada em `test`
  (commit `89b0498`).

## Histórico

| Ciclo | Milestone | Resultado | Evidência |
|---|---|---|---|
| 2026-11-13 | M1 | Diagramas do curso como **imagens embutidas** (19 JPG gerados por `tools/make_diagrams.py`, `juce_add_binary_data`) renderizadas no painel central, e **IDs de exercício por tópico** (`EX-1.<tópico>.<n>`, EX-1.A.1…EX-1.I.3). Instalador de teste republicado (`89b0498`) | `Source/Course/Content/Diagrams.*`; `CMakeLists.txt`; `ModuleComponent.cpp`; `ModuleCatalog.cpp`; `docs/MUSIC.md`; 295/295 testes |
| 2026-11-07 | M1 | Correção do painel de quiz (REQ-021, revisão do cliente): o **questionário roda no painel central** — cabeçalho do módulo (nível/BPM/gate), instrução "Responda uma questão por vez.", "Questão X de Y", enunciado e alternativas clicáveis A–D; o **painel direito** fica só com os controles (cabeçalho + link "Todos os tópicos do módulo", seletor, botão de play com `id — título`, placar e caixa de orientação "Neste exercício…") | `ModuleComponent.cpp` (`ContentView`); `PracticePanel.cpp/.h`; validado sob Xvfb (1040×680); 160/160 testes |
| 2026-11-05 | M1 | Correção do painel de prática (REQ-021): exercício vira linha clicável com ícone de play e id/título no painel direito, como no mock-up; centro mostra só a explicação (sem repetir o id/título) | `PracticePanel.cpp/.h`; `ModuleComponent.cpp`; instalador `9f5f70e` na `test` |
| 2026-11-05 | M1 | Conformidade com o `musica.docx`: REQ-019 (módulo abre em branco) e REQ-022 (tópico H com exercício executável); app validado contra as 9 capturas | `ModuleComponent.cpp`; `ModuleCatalog.cpp` (EX-1.H.1); 160/160 testes |
| 2026-11-05 | M1 | Curadoria ampliada com as 4 apostilas novas da `adequacao` (CAGED, teoria elementar, teoria da música, regulagem); instalador de teste atualizado | `docs/MUSIC.md` §1.1; `CourseModule::sources` (7); 150/150 testes |
| 2026-11-04 | M1 | Ajustes do `musica.docx` (REQ-019..023) publicados na branch `test` com instalador de teste | merge `3603ee6`; instalador commit `d031d86`; 146/146 testes |
| 2026-11-02 | M1 | Módulo 1 jogável + gate ≥90% com desbloqueio persistido + pattern/links REQ-007 | commit do Módulo 1 na branch `feat/measurement-engine`; 85/85 testes |
| 2026-11-02 | M0 | Agentes + memória compartilhada criados | commits na branch `feat/multi-agent-framework` |
| 2026-11-02 | M0 | Requisitos de sistema formalizados (REQ-001..REQ-014) e backlog/ADRs derivados | `docs/REQUIREMENTS.md`, `docs/adr/0002`, `docs/adr/0003` |
