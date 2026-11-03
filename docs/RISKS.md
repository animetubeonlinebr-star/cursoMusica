# RISKS — CursoMusica

Dono: **project-manager**. Todo agente que identificar um risco registra aqui.
Probabilidade e impacto em H/M/L.

| ID | Risco | Prob. | Impacto | Mitigação / contingência | Dono | Status |
|---|---|---|---|---|---|---|
| R-01 | ASIO SDK é licenciado pela Steinberg e não vem no JUCE nem pode ir ao CI público | H | H | Detecção opcional no CMake (já existe); documentar download em `docs/ASIO-Windows.md`; nunca versionar o SDK | devops, architect | aberto |
| R-02 | Sem máquina Windows, a latência real (requisito nº 1) não é verificada | H | H | Manter validação de compilação no Linux; planejar janela de teste no Windows (M4); declarar a limitação em cada release | qa | aberto |
| R-03 | PDFs do curso têm direitos autorais; embarcá-los no app pode violar licença | M | H | Não empacotar PDFs no binário sem permissão explícita; tratar como conteúdo separado | pm, data-engineer | aberto |
| R-04 | Ambiente de build reinicia entre sessões e perde toolchain (cmake/ninja/JUCE) | M | M | Documentado em `AGENTS.md` §10; CI reproduzível (M2) reduz dependência do ambiente local | devops | aberto |
| R-05 | `feature/juce-audio-app` não mesclada → `main` não tem o app; trabalho pode divergir | M | M | Decisão D1 em `docs/PLAN.md`; alinhar donos de arquivo após a mesclagem | architect | aberto |
| R-06 | Cadeia de plugins VST3 pode alocar/travar na thread de áudio se o contrato for quebrado | M | H | Contrato real-time documentado (`AGENTS.md` §1 e §10); teste de invariantes pelo QA | developer, qa | aberto |
| R-07 | Telemetria/analytics pode coletar dado pessoal sem base legal (LGPD/GDPR) | M | H | Opt-in explícito; anonimização obrigatória; revisão pelo data-engineer antes de sair | data-engineer, pm | aberto |
| R-08 | Repertório protegido (Coltrane, Hancock, Corea, Jobim, João Bosco) e apostilas do curso: distribuir áudio/partitura sem licença viola direitos autorais | M | M | **Condicional (posição registrada em `docs/MUSIC.md`):** aceitável sob art. 46, II da Lei 9.610/98 enquanto o projeto for pessoal, sem fins comerciais, com apenas pequenos trechos para estudo, sem redistribuir a obra e com créditos. Se virar comercial ou distribuir a obra completa, a análise precisa ser refeita | musician, pm | condicional |
| R-09 | Novas dependências (pugixml, midifile, FluidSynth, RtAudio, libsndfile) trazem licenças distintas e aumentam o instalador | M | M | ADR 0002 documenta licenças; revisar antes de distribuir; empacotar no instalador (REQ-014) | architect, devops | aberto |
| R-10 | Avaliação de improvisação pode ser injusta (falso erro/negativo) e desmotivar o aluno | M | H | Classificação determinística e explicável (`docs/MUSIC.md`); tolerância para passagem cromática; o aluno vê o porquê | musician, qa | aberto |
| R-11 | Gate de 90% mal calibrado (amostra pequena, desafio mal escrito) libera ou bloqueia o aluno errado | M | M | Mínimo de tentativas por desafio; QA testa 90,0% vs 89,9% e amostra 1/1 | data-engineer, qa | aberto |
| R-12 | Sem certificado de assinatura de código, o instalador Windows dispara aviso do SmartScreen | H | M | Assinar quando houver certificado; documentar o aviso enquanto não houver | devops | aberto |
| R-13 | Meta de BPM/`on_grid_ratio` mal calibrada: tolerância apertada torna a execução robótica (exigir 90% cedo) ou frouxa demais libera quem não toca no tempo; a síncope brasileira pode ser lida como erro | M | H | Faixa de estudo 0,75–0,82 nos módulos 1–14, rampa linear até 0,90 no 20; a grade modela a síncope de bossa/samba; QA testa meta, meta−1, fora-do-tempo e síncope correta | musician, qa | aberto |

## Como usar

- Novo risco → nova linha, com dono e mitigação. Não deixe em branco.
- Risco que ameaça um milestone → escalar no `docs/STATUS.md`.
- Risco resolvido → status `fechado` com a evidência.
