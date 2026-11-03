# Design system — CursoMusica

## Status

**Reconciliado com a referência.** Os tokens vêm de
`desiongne-grafico.jpg` (raiz do repositório), a imagem de modelo de design.
Qualquer mudança de paleta deve ser reextraída da imagem, não inventada.

## Princípios

1. **O afinador domina.** É o elemento que o músico olha enquanto toca. Recebe
   o maior espaço, a maior tipografia e o maior contraste da janela.
2. **Nada compete com o som.** A interface é escura e de baixa saturação para
   não cansar a vista em sessões longas de estudo.
3. **Estado nunca só por cor.** Cada estado (afinado / desafinado / silêncio)
   combina cor com posição, forma ou texto.
4. **Tokens, não valores soltos.** Nenhum componente usa hex ou número mágico;
   tudo vem de `Theme.h`.

## Tokens

### Cor (`theme::colour`)

Valores amostrados de `desiongne-grafico.jpg`. Acentos foram clareados para
atingir contraste de texto (o valor bruto da imagem aparece entre parênteses).

| Token | Hex | Uso |
|---|---|---|
| `background` | `#131418` | Fundo da janela |
| `surface` | `#1f2229` | Cartões e painéis |
| `surfaceRaised` | `#2a2e37` | Controles sobre painéis |
| `accent` | `#7b45c9` (`#6030a0`) | Foco, seleção, agulha ativa |
| `accentMuted` | `#4a2d7a` | Trilhas de slider |
| `accentAlt` | `#45a8c4` (`#387090`) | Destaques secundários |
| `textPrimary` | `#f8f8f8` | Texto principal |
| `textSecondary` | `#b8b8c0` | Legendas e rótulos |
| `border` | `#343841` | Contornos |
| `danger` | `#f05058` | Nível alto, erro |
| `success` | `#30d080` | Afinado, nível saudável |

### Tipografia (`theme::type`)

| Token | Tamanho | Uso |
|---|---|---|
| `display` | 72 px | Nome da nota no afinador |
| `title` | 22 px | Título da janela |
| `body` | 15 px | Texto corrente |
| `caption` | 12 px | Rótulos em maiúsculas |

`makeFont(size, bold)` centraliza a criação de fontes (usa `juce::FontOptions`,
API do JUCE 8).

### Espaçamento (`theme::spacing`)

Escala `xs=4`, `sm=8`, `md=16`, `lg=24`, `xl=40`.

### Raios (`theme::radius`)

`sm=4`, `md=8`, `lg=14`.

### Movimento (`theme::motion`)

`fast=120 ms`, `normal=220 ms`.

## Componentes

| Componente | Arquivo | Responsabilidade |
|---|---|---|
| `CursoLookAndFeel` | `Design/LookAndFeel.*` | Estilo de botões, combos e fontes |
| `Panel` | `Design/Panel.*` | Cartão base com título |
| `TunerDisplay` | `TunerDisplay.*` | Arco, agulha, nota e cents |
| `LevelMeter` | `LevelMeter.*` | Barra de nível em dB |
| `DevicePanel` | `DevicePanel.*` | Seleção de dispositivo, taxa e buffer |
| `TransportPanel` | `TransportPanel.*` | Play, loop, velocidade e nível |
| `SettingsComponent` | `SettingsComponent.*` | Configuração de dispositivo e cadeia VST3 |

## Contraste

Os pares principais superam 4.5:1:

- `textPrimary` (`#f8f8f8`) sobre `background` (`#131418`): ~16.5:1
- `textPrimary` sobre `surface` (`#1f2229`): ~14.6:1
- `textSecondary` (`#b8b8c0`) sobre `surface`: ~7.5:1

Revalidar sempre que a paleta for reconciliada com a referência.

## Como aplicar

```cpp
#include "UI/Design/Theme.h"
namespace th = cursomusica::theme;

g.setColour (th::colour::surface);
g.fillRoundedRectangle (bounds, th::radius::lg);
g.setFont (th::type::makeFont (th::type::body, true));
```
