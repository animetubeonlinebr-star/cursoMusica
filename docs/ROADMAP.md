# ROADMAP — CursoMusica

Dono: **pm**. Altitude macro (trimestres), sem listas de tarefas. O detalhe
tático vive em `docs/BACKLOG.md` (PO).

## Visão

Um companheiro de estudo de guitarra para Windows, com latência baixíssima, que
afina, mede e ajuda a praticar junto com o curso CursoMusica.

## Descoberta (resumo)

> **Domínio musical.** Os requisitos musicais (referência de afinação,
> tolerância em cents, alcance de detecção, tempo/compasso, playback sem mudança
> de tom) são ajustados **junto com o músico profissional** e vivem em
> `docs/MUSIC.md`. Este roadmap só aceita um requisito musical após essa revisão.

- **Usuário:** aluno de guitarra do curso CursoMusica, estudando em casa no PC.
- **Jobs-to-be-done:** afinar o instrumento; saber se a nota está certa; praticar
  um trecho devagar e em loop; ouvir o próprio som processado.
- **Dores observadas (evidência):** o repositório já carrega 4 PDFs de estudo e
  uma referência visual de "studio-dark"; o app já tem engine, afinador,
  medidor, settings e host VST3, mas o afinador/medidor ainda mostram valor
  *dummy* (ver `AGENTS.md` §2).
- **Oportunidades (por valor):**
  1. Ligar a UI à engine → o afinador e o medidor viram reais (maior valor, menor
     esforço, destrava tudo).
  2. Playback com velocidade e loop → é o que transforma "afinador" em "estudo".
  3. Presets de configuração → reduz o tempo até a primeira nota.

## Métricas de sucesso (KPIs)

| Métrica | Baseline | Alvo | Horizonte |
|---|---|---|---|
| Tempo até a primeira nota afinada (novo usuário) | ~5 min (estimado) | ≤ 60 s | Q2 |
| Sessões de estudo com o loop usado | 0 (não existe) | 40% das sessões | Q3 |
| Latência de ida e volta (ASIO, 64–128) | não medida | ≤ 10 ms | Q2 |
| Build do CI verde em PRs | sem CI | 100% | Q1 |
| Taxa de xruns em 30 min de uso | não medida | 0 | Q3 |

## Roadmap por trimestre

### Q1 — Fundação confiável
- **Objetivo:** o que já existe fica verificável e pronto para crescer.
- **KPI:** build do CI verde em 100% dos PRs; suíte de testes rodando.
- **Owner:** devops + qa + architect.
- **Tamanho:** M.
- **Dependência:** decidir se `feature/juce-audio-app` é mesclada em `main`.

### Q2 — Do mock ao real
- **Objetivo:** afinador e medidor ligados à engine (nível e afinação reais);
  latência medida no Windows com ASIO.
- **KPI:** tempo até a primeira nota afinada ≤ 60 s; latência ≤ 10 ms.
- **Owner:** developer (+ designer para estados visuais reais).
- **Tamanho:** L.
- **Dependência:** ASIO SDK no Windows; máquina Windows para medir.

### Q3 — Estudar de verdade
- **Objetivo:** playback com controle de velocidade e loop; presets de estudo.
- **KPI:** 40% das sessões usam o loop; 0 xruns em 30 min.
- **Owner:** developer + designer + data-engineer (sessões).
- **Tamanho:** L.
- **Dependência:** Q2 concluído (engine real).

### Q4 — Empacotar e evoluir
- **Objetivo:** instalador Windows, telemetria opcional (opt-in, LGPD) e
  analytics de progresso.
- **KPI:** instalação sem passo manual; dados de progresso disponíveis.
- **Owner:** devops + data-engineer.
- **Tamanho:** M.
- **Dependência:** Q3 concluído.

## Riscos macro (detalhe em `docs/RISKS.md`, owner: project-manager)

- ASIO SDK é licenciado e não vem no JUCE → risco de licença e de ausência no CI.
- Sem máquina Windows de teste, a latência real fica não verificada.
- PDFs do curso têm direitos autorais → não embarcar no app sem permissão.
