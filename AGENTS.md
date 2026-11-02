# AGENTS.md — CursoMusica

Memória persistente do projeto. Leia antes de trabalhar no repositório e
atualize quando descobrir algo que economize tempo nas próximas sessões.

## O que é o projeto

Aplicativo **desktop nativo para Windows** voltado ao **estudo de guitarra**.
Captura áudio da interface de áudio, analisa em tempo real (afinação, nível) e
serve de apoio ao estudo. O repositório também guarda os PDFs do curso.

## Stack

| Item | Valor |
|---|---|
| Linguagem | C++17 |
| Framework | JUCE 8.0.4 (em `External/JUCE`, clone raso) |
| Build | CMake ≥ 3.22 + Ninja (ou Visual Studio no Windows) |
| Alvo | Windows 10/11 |
| Desenvolvimento | Linux (sem dispositivo de áudio real; só valida compilação) |
| UI | JUCE `Component` + `LookAndFeel_V4` customizado |

## Requisito crítico: latência

O requisito número um do produto é **latência baixíssima**. Isso dita a
arquitetura:

- Driver **ASIO** quando disponível (`JUCE_ASIO=1`), depois **WASAPI
  exclusive**, depois WASAPI shared.
- Buffer pequeno (64–128 samples) e maior sample rate disponível.
- A thread de áudio **nunca** aloca memória, nunca faz lock, nunca faz I/O.
- UI ↔ áudio só por **atomics** e **FIFO lock-free** (`juce::AbstractFifo`).
- Análise pesada (YIN) roda em **thread de análise dedicada**, nunca no
  callback de áudio.

## Estrutura de diretórios

```
CMakeLists.txt
External/JUCE/            # dependência (não editar)
Source/
  Main.cpp                # entry point JUCEApplication
  MainComponent.h/.cpp    # janela principal, compõe os painéis
  Audio/                  # ENGINE (dono: engenheiro de áudio)
    AudioEngine.h/.cpp    # device I/O, callback RT, análise em thread dedicada
    PitchDetector.h/.cpp  # YIN monofônico, allocation-free
    PluginHost.h/.cpp     # format manager, scan VST3, instanciação
    PluginChain.h/.cpp    # cadeia de plugins na entrada (RT-safe)
  UI/                     # INTERFACE (dono: agente designer)
    Design/Theme.h        # tokens de design (fonte única de verdade)
    Design/LookAndFeel.*  # estilo JUCE
    Design/Panel.*        # cartão base com título
    Design/DESIGN.md      # documentação do design system
    LevelMeter.*  TunerDisplay.*
    DevicePanel.*  TransportPanel.*
    SettingsComponent.*   # menu de configuração (dispositivo + VST3)
.agents/agents/           # sub-agentes (designer.md)
design-references/        # imagens de referência visual
desiongne-grafico.jpg     # referência de design (raiz do repo)
```

## Referência visual

`desiongne-grafico.jpg` (raiz do repositório) é o modelo de design. Paleta
extraída dela:

| Papel | Hex |
|---|---|
| Fundo | `#131418` |
| Superfície | `#1f2229` |
| Superfície elevada | `#2a2e37` |
| Acento violeta | `#6030a0` (usado como `#7b45c9`, clareado para contraste) |
| Acento ciano | `#387090` (usado como `#45a8c4`) |
| Texto | `#f8f8f8` |
| Texto secundário | `#b8b8c0` |
| Sucesso | `#30d080` |
| Perigo | `#f05058` |

Layout observado: cabeçalho no topo, coluna lateral à esquerda, área principal
à direita. O afinador é o elemento dominante.

## Menu de configuração

`Source/UI/SettingsComponent.*`, aberto pelo botão **Settings** no cabeçalho.

- **Áudio:** `juce::AudioDeviceSelectorComponent` sobre o `AudioDeviceManager` —
  backend (ASIO/WASAPI), dispositivo de entrada, dispositivo de saída, taxa de
  amostragem, tamanho de buffer e roteamento de canais.
- **VST3:** botão **Scan** (varredura em thread de fundo), lista de plugins
  disponíveis, botão **Add to input chain**, lista da cadeia ativa, **Remove** e
  **Open editor** (janela nativa do plugin).

### Cadeia de plugins na entrada

O sinal capturado passa pelos plugins **antes** da análise, então o afinador e o
medidor refletem o que os plugins produzem.

`PluginChain` mantém o contrato de tempo real:

- a thread de áudio só lê um array de ponteiros publicado por índice atômico —
  sem locks, sem alocação;
- a propriedade das instâncias fica na message thread;
- toda mudança estrutural segue: aplicar → publicar novo índice → esperar a
  thread de áudio reportar o índice processado → liberar as instâncias antigas.
  O relatório acontece no **fim** do callback, então um incremento prova que o
  callback anterior terminou;
- se o dispositivo está parado, a espera é ignorada (nada está lendo o array).

## Divisão de responsabilidade entre agentes

- **Engenheiro de áudio** (agente principal): `Source/Audio/`, `CMakeLists.txt`,
  arquitetura, threading, DSP, build.
- **Agente `designer`** (`.agents/agents/designer.md`): `Source/UI/`,
  design system, `LookAndFeel`, layout e estados visuais.

Regra: o designer **não** edita `Source/Audio/` nem `CMakeLists.txt`. Se
precisar de um arquivo novo no build, ele informa a linha `target_sources` para
o engenheiro adicionar.

## Convenções de código

- Namespace raiz: `cursomusica`.
- Headers com `#pragma once`.
- Prefixo `juce::` sempre explícito.
- Membros privados sem prefixo; parâmetros com nomes descritivos.
- Comentários só quando explicam algo não óbvio (invariante, workaround,
  requisito de tempo real). Não narrar o código.
- JUCE 8: usar `juce::FontOptions` para fontes (construtor antigo de `juce::Font`
  está depreciado).

## Comandos

```bash
# Configurar e compilar (Linux, validação)
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build

# No Windows (Visual Studio)
cmake -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
```

## Estado atual

- [x] Estrutura CMake e dependência JUCE
- [x] Engine de áudio em tempo real (callback mínimo, FIFO lock-free)
- [x] Detecção de pitch (YIN) em thread de análise dedicada
- [x] Agente de design criado (`.agents/agents/designer.md`)
- [x] Gerenciamento de memória do projeto (este arquivo)
- [x] Telas iniciais (layout, sem funcionalidade de estudo)
- [x] Referência visual lida e tema reconciliado com a paleta real
- [x] Menu de configuração: dispositivos de áudio, entrada, saída, buffer
- [x] Host VST3 com scan, cadeia na entrada e editor de plugin
- [x] Build validada no Linux: binário gerado, zero avisos, UI renderiza
- [ ] Ligar UI principal à engine (nível e afinação reais em vez de dummy)
- [ ] Playback com controle de velocidade e loop
- [ ] ASIO SDK no Windows (licença Steinberg, download separado)
- [ ] Empacotamento / instalador

## Pendências e armadilhas conhecidas

- O ASIO SDK **não** acompanha o JUCE. O JUCE só faz `#include <iasiodrv.h>`;
  **não existe** `JUCE_ASIO_SDK_PATH`. O CMake do projeto detecta o SDK em
  `ASIO_SDK_DIR`, `External/asio` ou na variável de ambiente, e só habilita
  `JUCE_ASIO=1` quando acha `common/iasiodrv.h`. Guia completo:
  `docs/ASIO-Windows.md`.
- Este ambiente Linux não tem dispositivo de áudio; a validação aqui é apenas
  de compilação. Teste de latência real só no Windows com a interface física.
- Plugins com mais de 8 entradas na cadeia são rejeitados (`PluginChain::maxPlugins`).
- A varredura de VST3 grava a lista em um `PropertiesFile` do usuário
  (`CursoMusica.settings`), então o segundo launch não precisa rescannear.
- O ambiente de build pode ser reiniciado entre sessões: se `cmake` sumir,
  reinstale `cmake ninja-build pkg-config` e as libs de desenvolvimento do JUCE.

## Build no Windows (passo a passo)

Guia detalhado do ASIO: `docs/ASIO-Windows.md`.

1. Instale **Visual Studio 2022** com a carga "Desenvolvimento para desktop com
   C++", **CMake** e **Ninja** (ou use o gerador do VS).
2. Baixe o **ASIO SDK** da Steinberg (<https://www.steinberg.net/developers/>) e
   descompacte em `External/asio`, de modo que exista
   `External/asio/common/iasiodrv.h`.
3. Configure e compile:

```powershell
cmake -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
```

   Para apontar para um SDK fora do projeto, use
   `-DASIO_SDK_DIR="C:\SDKs\ASIO"`. A configuração mostra
   `-- ASIO SDK found: ...` quando encontra.
4. No app, abra **Settings** e selecione o backend **ASIO** e a interface física.
5. Para latência mínima: buffer **64–128** samples e a maior taxa que a
   interface aceitar.

Sem o SDK o build **não quebra**: ele apenas compila com WASAPI em vez de ASIO.

### Alvo de latência

A meta é **round-trip abaixo de 5 ms**. Meça com o app aberto no painel de
dispositivo (`estimatedLatencyMs`) e valide com monitoramento ao vivo.

