# ROADMAP — CursoMusica

Dono: **pm**. Altitude macro (trimestres), sem listas de tarefas. O detalhe
tático vive em `docs/BACKLOG.md` (PO) e os requisitos rastreáveis em
`docs/REQUIREMENTS.md`.

## Visão

Uma **plataforma de estudo de guitarra** para Windows, com latência baixíssima,
que ensina, demonstra com áudio, gera desafios, mede o desempenho e **avalia
improvisação** — tudo dentro do software, sem arquivos externos.

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

### Q1 — Fundação confiável e distribuível
- **Objetivo:** o que já existe fica verificável, e o app passa a ter instalador
  Windows pronto para uso.
- **KPI:** CI verde em 100% dos PRs; instalador instala em diretório escolhido e
  abre pronto para uso (REQ-014).
- **Owner:** devops + qa + architect.
- **Tamanho:** M.
- **Dependência:** decidir se `feature/juce-audio-app` é mesclada em `main`.

### Q2 — Do mock ao real + estrutura de curso
- **Objetivo:** afinador e medidor ligados à engine; estrutura de módulos
  lineares com explicação e desafios; motor de medição com gate de 90%.
- **KPI:** tempo até a primeira nota afinada ≤ 60 s; gate de 90% funcionando
  (REQ-009); todo módulo com explicação e ≥1 desafio (REQ-003/REQ-008).
- **Owner:** developer + designer + data-engineer + musician.
- **Tamanho:** L.
- **Dependência:** ASIO SDK e máquina Windows para medir latência.

### Q3 — Improvisação avaliada
- **Objetivo:** conversão partitura → áudio; avaliação de improvisação
  (repouso × tensão); módulos progressivos níveis 1–4.
- **KPI:** toda partitura tem áudio (REQ-004); tensão não pedida conta como erro
  (REQ-012); 40% das sessões usam o loop.
- **Owner:** musician + developer + data-engineer.
- **Tamanho:** L.
- **Dependência:** Q2 (motor de medição).

### Q4 — Repertório e empacotamento final
- **Objetivo:** módulos 5–7 (blues, standards com modulação, repertório);
  curadoria de links/patterns; instaladores de teste por módulo.
- **KPI:** 7 níveis completos; cada módulo com ≥1 link e ≥1 pattern verificados
  (REQ-010); instalador por módulo na branch de teste (REQ-013).
- **Owner:** musician + po + devops.
- **Tamanho:** L.
- **Dependência:** Q3.

## Riscos macro (detalhe em `docs/RISKS.md`, owner: project-manager)

- ASIO SDK é licenciado e não vem no JUCE → risco de licença e de ausência no CI.
- Sem máquina Windows de teste, a latência real fica não verificada.
- PDFs do curso têm direitos autorais → não embarcar no app sem permissão.
- Repertório (Coltrane, Hancock, Corea, Jobim, João Bosco) é protegido → usar só
  progressões/estudo, nunca gravação ou partitura publicada sem licença.
