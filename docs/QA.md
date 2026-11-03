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
- **Gate de 90% (REQ-009)** → 90,0% libera; 89,9% não libera; amostra pequena
  (1/1) não vale como aprovação.
- **Tensão não pedida (REQ-012)** → conta como erro; tensão pedida é aceita;
  tensão não pedida **que faz parte do acorde** é aceita.
- **Metrônomo/BPM meta (REQ-015)** → atingir a meta libera o eixo de andamento;
  meta−1 BPM não libera; tocar rápido fora da grade não conta como atingido.
- **Catálogo de patterns (REQ-016)** → cada ID `PTN-*` é citável por um módulo e
  detectável pela avaliação.
- **Nota de repouso identificada corretamente (REQ-011)** → nota do acorde e nota
  de fora classificadas de forma distinta e explicável.
- **Conversão partitura → áudio (REQ-004)** → mesma entrada produz o mesmo áudio;
  oitava correta (guitarra transpositora).
- **Override de teste (REQ-013)** → instalador de teste abre tudo liberado, mas o
  cálculo real de acerto permanece correto.
- **Instalador Windows (REQ-014)** → instala em `C:\` e `D:\`; abre pronto; o
  desinstalador remove arquivos e atalhos.

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
