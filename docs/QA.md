# QA — CursoMusica

Dono: **qa**. Estratégia de teste, execuções e defeitos. Evidência obrigatória;
"compila" não é "funciona".

## Estratégia

| Camada | Ferramenta | O que cobre |
|---|---|---|
| Unidade (C++) | Catch2 / GoogleTest | PitchDetector (YIN), FIFO lock-free, PluginChain, migrações de dados |
| Invariantes real-time | Asserção estática / harness | Callback não aloca, não faz lock, não faz I/O |
| Integração | Harness de áudio com buffer sintético | Afinador e medidor ponta a ponta com sinal conhecido |
| Regressão | Suíte completa por PR | Nova feature não quebra tela/engine antigos |
| Carga/performance | Medição de CPU e xruns | Buffer 64–128 samples; headroom de CPU |

## Cenários de falha a considerar (por história)

- **Sinal vazio / silêncio** → afinador e medidor devem mostrar estado vazio, não
  valor falso nem NaN.
- **Clipping / sinal muito alto** → medidor satura de forma legível; sem overflow.
- **Troca de dispositivo em execução** → sem crash, sem deadlock; engine re-prepara.
- **Plugin VST3 instável** → a cadeia isola a falha; a UI continua responsiva.
- **Buffer mínimo (64)** → sem xruns em carga típica.
- **Migração de schema em dados existentes** → dados antigos continuam legíveis.

## Execuções

| Data | Escopo (SHA/branch) | Resultado | Evidência |
|---|---|---|---|
| 2026-11-02 | `feat/multi-agent-framework` | Build não aplicável (só docs/agentes neste ciclo); sem suíte ainda | — |

## Defeitos

| ID | Severidade | Descrição | Dono | Status |
|---|---|---|---|---|
| — | — | Nenhum registrado | — | — |

## Pendências

- Suíte de testes automatizados ainda não existe (depende de M2 no `docs/PLAN.md`).
- Teste de latência real pendente de máquina Windows (risco R-02).
