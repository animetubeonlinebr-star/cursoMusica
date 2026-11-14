# 0007 — Pastas de busca de plugins VST3 configuráveis

Status: accepted
Data: 2026-11-14
Autor: architect + developer (requisito REQ-024; pedido do cliente: "que seja
possível configurar as pastas de plugins na janela de configurações, estilo
Reaper")

## Contexto

O `PluginHost` (`Source/Audio/PluginHost.cpp`) já varre os locais padrão que o
formato VST3 informa (`AudioPluginFormat::getDefaultLocationsToSearch()`) e
guarda o resultado em cache no arquivo de propriedades. Isso cobre a instalação
típica, mas não o caso comum de quem organiza os plugins em uma pasta própria
(`D:\VST3`, um HD externo, uma pasta de coleção).

O cliente pediu uma tela no estilo do Reaper: uma lista de pastas que a varredura
também deve percorrer.

Restrições:

1. **Nada de I/O na thread de áudio** (`AGENTS.md` §1). A lista só é tocada na
   thread de mensagens, pelo diálogo de configurações.
2. **O app é offline-first.** Sem nenhuma pasta configurada, o comportamento tem
   de continuar idêntico ao de hoje (só os locais padrão).
3. **A lista é dado do usuário**, não do curso: precisa sobreviver entre
   execuções e não pode ficar no binário.

## Decisão

1. **A regra vive em `PluginSearchPaths`** (`Source/Audio/PluginSearchPaths.*`),
   um tipo de lógica pura que depende só de `juce_core`. Ele normaliza (caminho
   absoluto, sem separador final), recusa vazio e duplicata (comparação sem
   diferenciar maiúsculas), limita a 32 pastas e serializa como uma linha por
   caminho. Sem UI e sem tocar o disco na validação, é testável pela suíte de
   lógica pura.
2. **A persistência fica no `PluginHost`**, sob a chave `vst3SearchPaths` do
   mesmo `PropertiesFile` que já guarda o cache de plugins. Gravar chama
   `saveIfNeeded()` na hora: a janela escreve a cada edição e o app pode fechar
   antes do temporizador do `PropertiesFile`.
3. **A varredura soma os dois conjuntos**, sem duplicar: locais padrão do
   formato mais as pastas do usuário que existem no disco
   (`resolveExisting()`). Uma pasta apagada não quebra o scan nem desaparece da
   lista — o usuário vê e corrige.
4. **A poda é por descendência, não igualdade.** Ao remover uma pasta, os
   plugins que moravam nela saem do cache; a checagem usa `File::isAChildOf`
   para reconhecer o arquivo `.vst3` dentro da pasta, e os locais padrão são
   sempre considerados válidos.
5. **A UI é uma janela própria** (`Source/UI/PluginPathsComponent.*`), aberta
   pelo botão "Pastas…" ao lado da tabela de plugins. O grid tem duas colunas
   (o caminho e um botão que abre o seletor de diretório da linha) e o rodapé
   tem adicionar/remover/fechar. A janela é modal para o app e é fechada no
   destrutor do `SettingsComponent`.

## Consequências

- O usuário passa a instalar VST3 fora dos locais padrão sem mexer no sistema.
- O teste de lógica cobre a parte arriscada (normalização, duplicatas, cap,
  serialização); a UI fica coberta por validação manual sob Xvfb.
- Custo baixo: nenhuma dependência nova, nenhum caminho novo na thread de áudio.
- A poda é conservadora: só age sobre plugins que o cache conhece e cujo arquivo
  existe; formatos sem arquivo (ex.: ids de AudioUnit) ficam intocados.
