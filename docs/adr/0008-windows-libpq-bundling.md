# 0008 — Empacotar a `libpq.dll` no instalador Windows

Status: accepted
Data: 2026-11-15
Autor: devops + developer (correção de REQ-014; defeito relatado pelo cliente:
"erro ao tentar iniciá-lo após instalação: LIBPQ.dll não foi encontrado")

## Contexto

O instalador de teste (`instalador/Instalador CursoMusica.exe`, produzido pelo
`release.yml`) instala o app e abre sem passos manuais — exceto por um detalhe:
o executável foi linkado contra `libpq` (`find_package(PostgreSQL)` no
`CMakeLists.txt`, ADR 0006), então o `.exe` declara uma dependência de
`libpq.dll`. O instalador não embutia essa DLL.

O runner do GitHub Actions já traz PostgreSQL instalado (o log do release
mostra `libpq found (14.24)`), então o build passava e o instalador era gerado
sem erro. Numa máquina sem PostgreSQL, porém, o Windows falhava ao abrir:

> A execução de código não pode continuar porque LIBPQ.dll não foi encontrado.

Isso viola REQ-014 ("o sistema fica pronto para uso"), que é o requisito que o
próprio `installer.nsi` cita. O `docs/POSTGRESQL.md` §5 já registrava a
pendência ("o instalador ainda é gerado sem libpq"), mas ela ficou sem dono.

Restrições:

1. **Não transformar a dependência em opcional no Windows.** O espelhamento do
   progresso é um recurso do produto; tirar o link só esconderia o problema.
2. **O instalador já sabe embutir DLLs**: `installer.nsi` copia `build/runtime`
   quando o build passa `-DRUNTIME`. A correção cabe nesse caminho.
3. **Falhar cedo**: um instalador que não abre é pior que um build vermelho.

## Decisão

1. **O staging vive no CMake**, em `cmake/StageWindowsRuntime.cmake`, rodado
   como passo `POST_BUILD` do alvo `CursoMusica` (só em `WIN32`, e só quando
   `PostgreSQL_FOUND`). Ele usa `file(GET_RUNTIME_DEPENDENCIES)` sobre o `.exe`,
   que lê a import table e resolve as DLLs a partir de diretórios informados
   (a árvore do PostgreSQL e o `PATH`), excluindo o que é do sistema
   (`System32`, `SysWOW64`, `WinSxS`) e os encaminhadores `api-ms-*`/`ext-ms-*`.
2. **O staging é fechado transitivamente.** A `libpq.dll` do PostgreSQL puxa
   OpenSSL e outras bibliotecas; o `GET_RUNTIME_DEPENDENCIES` já resolve esse
   fecho, então o bundle não fica pela metade.
3. **A ausência da `libpq.dll` falha o build.** O script emite `FATAL_ERROR` se
   `libpq.dll` não for resolvida — melhor um build vermelho do que um instalador
   que não abre.
4. **O `release.yml` confere antes de empacotar.** Além do CMake, o workflow
   verifica `build/runtime/libpq.dll` e aborta antes do `makensis` se faltar,
   para que a falha apareça como mensagem clara e não como bug de runtime no
   cliente.

## Consequências

- O instalador de teste passa a sair pronto para uso numa máquina limpa
  (REQ-014), com `libpq.dll` e suas dependências ao lado do `.exe`.
- O bundle cresce um pouco (libpq + OpenSSL); aceitável frente ao app já
  empacotar JUCE, SoundFont e amostras.
- A regra é verificável: o workflow falha se a DLL não estiver no bundle, e o
  log do CMake lista as DLLs estagiadas.
- O `docs/POSTGRESQL.md` §5 deixa de descrever a pendência e passa a descrever o
  comportamento real.
