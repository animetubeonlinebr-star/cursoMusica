# BACKLOG — CursoMusica

Dono: **po**. Ordenado por valor (impacto no aluno × impacto no negócio).
Histórias em detalhe ficam em `docs/stories/` quando crescerem; aqui fica o
índice priorizado.

Deriva de `docs/ROADMAP.md` e `docs/REQUIREMENTS.md`. Formato de história e DoD:
`AGENTS.md` §5 e §6. Critérios musicais (referência de afinação, tolerância em
cents, alcance de detecção, tempo) derivam de `docs/MUSIC.md` (dono: `musician`).
Cada história cita o(s) requisito(s) que atende.

## Pronto para desenvolvimento (topo)

### [CM-001] Afinador e medidor reais na UI — valor: H — tamanho: M — status: ready
Requisito: REQ-001.
Como um aluno de guitarra, eu quero ver a afinação e o nível reais do meu som na
tela, para que eu possa confiar no app enquanto estudo.

Critérios de aceite:
- Dado que o dispositivo está aberto, quando eu toco uma corda, então o medidor
  de nível reage ao volume real em até 100 ms.
- Dado que eu toco a nota A2 (110 Hz), quando o detector estabiliza, então o
  afinador mostra "A" com desvio em cents dentro de ±5 cents.
- Dado que o dispositivo está parado, quando não há sinal, então a UI mostra
  estado vazio ("—") e não um valor falso.

Dependências: `AudioEngine` (getters já existem, ver `Source/Audio/AudioEngine.h`).
Notas técnicas (architect): consumir só os getters públicos e atomics; nenhuma
chamada bloqueante na UI.

### [CM-002] Pipeline de CI para build e testes — valor: H — tamanho: M — status: ready
Requisito: REQ-009 (base para medir), DoD.
Como o time de desenvolvimento, eu quero que cada PR compile e rode os testes
automaticamente, para que nenhum erro bobo chegue à main.

Critérios de aceite:
- Dado um PR, quando eu abro ou atualizo, então o CI clona JUCE 8.0.4 e compila
  no Linux sem novos avisos.
- Dado o build sem o ASIO SDK, quando o CI roda, então o build passa (ASIO é
  opcional por design).
- Dado um PR que quebra o build, quando o CI termina, então o check fica vermelho.

Dependências: nenhuma. Owner: devops.

### [CM-010] Instalador Windows com seleção de diretório — valor: H — tamanho: M — status: ready
Requisito: REQ-014 (e REQ-013 para a branch de teste).
Como um aluno, eu quero um instalador `.exe` que me deixe escolher onde instalar,
para que o app fique pronto para uso sem passos manuais.

Critérios de aceite:
- Dado o instalador, quando eu o executo, então ele oferece escolher o diretório
  de instalação (padrão `%ProgramFiles%`).
- Dado que eu instalei em `D:\CursoMusica`, quando o app abre, então ele
  reconhece o áudio e funciona sem configuração manual.
- Dado que eu desinstalo, quando a remoção termina, então os arquivos e atalhos
  instalados são removidos.

Dependências: CM-002 (CI gera o artefato). Owner: devops.

## Próximas (refinando)

### [CM-006] Estrutura de curso: módulos lineares, explicação e desafios — valor: H — tamanho: L — status: draft
Requisitos: REQ-002, REQ-003, REQ-008, REQ-005.
Como um aluno, eu quero percorrer módulos em ordem, com explicação antes e
desafios depois, para que eu estude dentro do próprio software.

Critérios de aceite (rascunho):
- Todo módulo tem uma seção de explicação **antes** do primeiro desafio.
- Todo módulo tem ≥1 desafio jogável.
- O módulo N+1 só fica acessível após o gate do módulo N (ver CM-008).
- Nenhuma tela exige abrir arquivo externo para estudar.

Dependências: CM-001. Bloqueio: modelo de curso (ADR 0003) e UI (designer).

### [CM-007] Conversão de partitura para áudio — valor: H — tamanho: L — status: draft
Requisitos: REQ-004; stack do ADR 0002.
Como um aluno, eu quero ouvir qualquer exemplo/partitura do app, para que eu
aprenda de ouvido além da leitura.

Critérios de aceite (rascunho):
- Toda partitura exibida tem áudio correspondente e reproduzível no app.
- A altura e a oitava do áudio batem com a partitura (respeitando a transposição
  da guitarra — soa uma oitava abaixo do escrito).
- O mesmo arquivo de entrada produz sempre o mesmo áudio (determinismo).

Dependências: ADR 0002 (pugixml/midifile/FluidSynth/libsndfile). Owner: developer.

### [CM-008] Motor de medição e gate de 90% — valor: H — tamanho: M — status: draft
Requisitos: REQ-009, REQ-002.
Como o sistema, eu quero medir toda tentativa e liberar o próximo módulo só com
≥90% de acerto, para que a progressão seja confiável.

Critérios de aceite (rascunho):
- Acurácia do módulo = acertos / tentativas válidas, com mínimo de tentativas.
- Acurácia ≥ 0,90 → módulo aprovado e próximo liberado; 0,899 → não libera.
- Histórico de tentativas é append-only e recalculável.

Dependências: CM-006, `docs/DATA.md` (schema v2). Owner: data-engineer + developer.

### [CM-009] Avaliação de improvisação: repouso × tensão — valor: H — tamanho: L — status: draft
Requisitos: REQ-011, REQ-012, REQ-010.
Como um aluno, eu quero que o app me diga se usei as notas certas na
improvisação, para que eu evolua com feedback objetivo.

Critérios de aceite (derivados de `docs/MUSIC.md`, dono: musician):
- Dado o contexto harmônico, cada nota tocada é classificada em
  repouso/tensão/erro/passagem.
- Tensão **não pedida** pelo estado de improviso conta como erro.
- Tensão **pedida** é aceita; tensão que resolve em repouso é aceita.
- O aluno vê *por que* errou (nota, contexto, veredito).

Dependências: CM-007 (contexto sonoro), CM-008. Owner: musician + developer.

### [CM-011] Módulos progressivos de improvisação (níveis 1–7) — valor: H — tamanho: L — status: draft
Requisitos: REQ-002, REQ-010, REQ-016; ordem e standards em `docs/MUSIC.md`.
Como um aluno, eu quero estudar improvisação em níveis crescentes, do vamp de 1
acorde até músicas reais, para que eu progrida sem pular etapas.

Critérios de aceite (rascunho):
- Níveis na ordem: 1 vamp/1 acorde → 2 vamps/2 acordes → 3 II–V–I →
  4 turnarounds → 5 blues 12 compassos → 6 standards com modulação →
  7 repertório.
- Cada nível é ancorado em standards concretos (mapa em `docs/MUSIC.md`).
- Cada nível ensina ≥1 link e ≥1 pattern do catálogo (CM-015) e verifica o uso
  (CM-012).

Dependências: CM-009. Owner: musician + po.

### [CM-014] Metrônomo com BPM meta como gate — valor: H — tamanho: M — status: draft
Requisitos: REQ-015; ADR 0004.
Como um aluno, eu quero praticar com metrônomo e ter uma meta de andamento, para
que eu só avance quando tocar certo na velocidade exigida.

Critérios de aceite (derivados de `docs/MUSIC.md`, dono: musician):
- Cada desafio tem `target_bpm`; o sistema mede o maior BPM executado dentro da
  tolerância rítmica (`achieved_bpm`).
- O alvo de `on_grid_ratio` é **0,75–0,82** nos módulos 1–14, sobe **linearmente**
  até **0,90** do 15 ao 20, e é **0,90** a partir do 20.
- Atingir `target_bpm` (com alinhamento à grade) → eixo de andamento aprovado;
  ficar 1 BPM abaixo → não aprova.
- Tocar rápido e fora do tempo **não** conta como BPM atingido.
- Em bossa/samba, tocar a síncope correta não é penalizado como fora da grade.
- O módulo só libera com acurácia ≥ 90% **e** BPM meta atingido.

Dependências: CM-008, `docs/DATA.md` (schema v3). Owner: musician + developer +
data-engineer.

### [CM-015] Catálogo de patterns (melódicos, rítmicos, arpejos) — valor: H — tamanho: M — status: draft
Requisitos: REQ-016, REQ-010; IDs em `docs/MUSIC.md` §"Catálogo de patterns".
Como um aluno, eu quero praticar os patterns do catálogo, para que eu desenvolva
fluência mecânica e fraseado.

Critérios de aceite (rascunho):
- O catálogo contém os grupos: melódicos (3, 4, terças, quartas, triquetra, 3-1,
  string skipping), rítmicos (funk, palm mute, bossa, hybrid) e arpejos (tríade,
  drop 2, drop 3).
- Cada pattern tem ID estável (`PTN-*`) e é citável por um módulo.
- A avaliação detecta a assinatura do pattern no trecho improvisado (CM-012).

Dependências: CM-011. Owner: musician.

### [CM-012] Curadoria de conteúdo: apostilas, links e patterns — valor: M — tamanho: M — status: draft
Requisitos: REQ-006, REQ-007, REQ-010, REQ-016.
Como o time de conteúdo, eu quero revisar as apostilas e anexar links e patterns
de guitarristas por módulo, para que o material seja coerente e verificável.

Critérios de aceite (rascunho):
- Cada módulo lista: fonte da apostila usada, ≥1 link, ≥1 pattern (ID do
  catálogo, CM-015).
- Guitarristas de referência considerados: Petrucci, Govan, Kotzen, Howe, Vai,
  Satriani, Juninho Afram, Edu Ardanuy, Kiko Loureiro.
- A avaliação detecta se o pattern ensinado foi usado.

Dependências: CM-011. Owner: musician.

### [CM-013] Instalador de teste por módulo com acesso liberado — valor: M — tamanho: M — status: draft
Requisitos: REQ-013.
Como o time de validação, eu quero um instalador por módulo na branch de teste,
com tudo liberado, para que eu veja o módulo novo sem desbloquear os anteriores.

Critérios de aceite (rascunho):
- Para cada módulo novo, o CI publica um instalador na branch de teste.
- O instalador abre com todos os módulos acessíveis (override de teste).
- O override não altera o cálculo real de acerto.

Dependências: CM-010, CM-006. Owner: devops.

## Não priorizado / ideias

- Metrônomo com detecção de tempo tocado.
- Registro local de sessões de estudo (dados → owner: data-engineer).
- Exportar progresso em PDF.

## Regras de priorização

1. Valor para o aluno × valor para o negócio.
2. Redução de risco (ex.: CI antes de features, para pegar regressão cedo).
3. Tamanho menor primeiro quando o valor empata.

**Por que CM-001 está no topo:** é o que transforma o app de mockup em
ferramenta real, tem o maior valor e o menor esforço entre os itens de alto
valor — destrava as histórias seguintes.
