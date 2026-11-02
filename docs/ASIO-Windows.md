# ASIO no Windows — passo a passo

Guia verificado contra o código do JUCE 8.0.4 que está em `External/JUCE`.

## Por que o ASIO não vem pronto

O JUCE **não** inclui o ASIO SDK da Steinberg e **não** tem variável de CMake
para ele. O que o JUCE faz é apenas:

```cpp
// External/JUCE/modules/juce_audio_devices/juce_audio_devices.cpp
#if JUCE_ASIO
  #include <iasiodrv.h>                          // <-- vem do SDK da Steinberg
  #include "native/juce_ASIO_windows.cpp"        // <-- implementação do JUCE
#endif
```

Ou seja: o JUCE implementa toda a lógica (`ASIOAudioIODeviceType` está no
próprio JUCE), e só precisa que o **`iasiodrv.h` do SDK esteja no include
path**. Os comentários no próprio JUCE explicam a razão:

> "unfortunately that would break Steinberg's license agreement for use of
> their SDK, so I'm not allowed to do this."

Não existe `JUCE_ASIO_SDK_PATH`. Se você viu isso em algum lugar, é incorreto.

## Passo 1 — Baixar o ASIO SDK

1. Acesse o portal de desenvolvedores da Steinberg:
   <https://www.steinberg.net/developers/>
2. Baixe o **ASIO SDK** (arquivo `.zip`, ~5,7 MB).
3. Aceite a licença. Desde outubro de 2025 o ASIO é **dual-licenciado**:
   GPLv3 para projetos open source, ou a licença proprietária Steinberg para
   produtos fechados. Escolha conforme a distribuição que você pretende fazer.

> Como o CursoMusica é um app distribuído (não open source), verifique a
> licença proprietária antes de publicar. Para uso interno/estudo, qualquer
> uma serve.

## Passo 2 — Descompactar

Descompacte em `External/asio`, de forma que o caminho fique assim:

```
cursoMusica/
└── External/
    └── asio/
        ├── common/
        │   ├── iasiodrv.h      <-- o arquivo que o JUCE procura
        │   ├── asio.h
        │   └── ...
        ├── host/
        ├── pc/
        └── ...
```

O importante é que **`common/iasiodrv.h`** exista. O CMake confere exatamente
esse caminho.

> O SDK costuma vir com uma pasta extra no meio (ex.: `ASIOSDK2.3.4/common`).
> Se for o caso, mova o conteúdo para que `External/asio/common` fique correto,
> ou aponte `ASIO_SDK_DIR` para a pasta que contém `common` (passo 3).

## Passo 3 — Configurar o CMake

O `CMakeLists.txt` já detecta o SDK automaticamente em três lugares:

1. a variável `ASIO_SDK_DIR`;
2. a pasta `External/asio` do projeto;
3. a variável de ambiente `ASIO_SDK_DIR`.

Se você descompactou em `External/asio` (passo 2), **não precisa fazer nada** —
a configuração padrão já encontra. Para apontar para outro lugar:

```powershell
cmake -B build -G "Visual Studio 17 2022" -A x64 -DASIO_SDK_DIR="C:\SDKs\ASIO"
```

Para confirmar que foi encontrado, procure no log da configuração:

```
-- ASIO SDK found: C:/SDKs/ASIO/common
```

Se aparecer o aviso `ASIO SDK not found`, o build continua (com WASAPI em vez de
ASIO) — ele não quebra, só perde a opção de baixa latência.

## Passo 4 — Compilar

```powershell
cmake -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
```

Com o SDK presente, o CMake define `JUCE_ASIO=1` automaticamente. Sem ele, o
define não é aplicado e o ASIO simplesmente não aparece na lista de backends.

## Passo 5 — Usar no aplicativo

1. Abra o app e clique em **Settings**.
2. No painel **Audio device**, em *Audio device type*, escolha **ASIO**.
3. Selecione a **interface física** em *Device*.
4. Escolha o **buffer** (o painel também mostra taxa de amostragem).
5. Aplique.

## Passo 6 — Ajustar para latência mínima

| Ajuste | Valor | Por quê |
|---|---|---|
| Buffer | **64** samples (depois teste 128) | Cada bloco a 48 kHz ≈ 1,33 ms |
| Taxa de amostragem | a maior que a interface aceitar | Reduz o tempo por bloco |
| Driver | o **ASIO** do fabricante da interface | Evita o mixer do Windows |

O painel de configuração mostra o backend ativo. A meta do projeto é
**round-trip abaixo de 5 ms**.

Se ouvir estalos, aumente o buffer de 64 para 128 antes de mexer em qualquer
outra coisa — 64 samples é agressivo e depende da qualidade do driver.

## Problemas comuns

**`Cannot open include file: 'iasiodrv.h'`**
O CMake não achou o SDK. Confirme que `common/iasiodrv.h` existe no caminho e
que `ASIO_SDK_DIR` aponta para a pasta **que contém** `common`.

**ASIO não aparece na lista de backends**
Faltou reconfigurar do zero depois de instalar o SDK. Apague a pasta `build/` e
rode o CMake de novo (o resultado fica em cache).

**ASIO aparece, mas a interface não**
Instale o driver ASIO **do fabricante** da interface (Focusrite, Behringer,
Presonus, etc.). O Windows não traz driver ASIO genérico; sem ele a interface
não é enumerada.

**Estalos, cliques ou cortes**
Buffer pequeno demais, ou o driver não está em modo exclusivo. Suba o buffer e
feche outros apps que usam áudio.

## Alternativa sem o SDK

Se você ainda não quer baixar o SDK, o build funciona com **WASAPI exclusive**,
que já está habilitado. É um pouco mais lento que o ASIO, mas muito melhor que o
modo compartilhado do Windows. Serve para desenvolver; para o objetivo final de
latência mínima, o ASIO é o caminho.
