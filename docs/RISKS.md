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

## Como usar

- Novo risco → nova linha, com dono e mitigação. Não deixe em branco.
- Risco que ameaça um milestone → escalar no `docs/STATUS.md`.
- Risco resolvido → status `fechado` com a evidência.
