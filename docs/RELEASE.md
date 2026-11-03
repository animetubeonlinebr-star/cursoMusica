# RELEASE — CursoMusica

Dono: **devops**. Como cada módulo chega às mãos de quem valida (REQ-013) e como
o instalador Windows funciona (REQ-014).

## Instalador Windows (REQ-014)

- Script: `deploy/windows/installer.nsi` (NSIS, Unicode, PT-BR + EN).
- O instalador inclui a página **Directory**, onde o usuário escolhe o local de
  instalação (padrão `%ProgramFiles%\CursoMusica`).
- Instala o executável e as dependências de runtime (bibliotecas do ADR 0002,
  SoundFont/samples) para o app abrir **pronto para uso**.
- Cria atalhos (menu iniciar e desktop) e registra o desinstalador.
- O desinstalador remove arquivos, atalhos e chaves de registro.
- O entregável é **`instalador/Instalador CursoMusica.exe`**, na raiz do
  projeto. O NSIS resolve caminhos relativos ao próprio `.nsi` e não aceita
  `..`, então o build primeiro faz staging em `deploy/windows/dist/app/` e
  depois copia o resultado para `instalador/`.
- Runtime opcional: se `build/runtime/` existir, o build passa `/DRUNTIME` e o
  NSIS o inclui; sem essa pasta o instalador continua sendo gerado.

## Build e publicação

- Workflow: `.github/workflows/release.yml`.
- Dispara em push na branch `test` e manualmente (`workflow_dispatch`), com os
  campos `module`, `unlock_all` (override de teste) e `commit_installer`.
- O build **só** roda no `windows-latest`: a máquina de desenvolvimento é Linux
  e não produz um `.exe` Windows de verdade. O workflow é a única forma de gerar
  o binário entregável.
- Artefato: `Instalador CursoMusica.exe`, disponível como artifact do run. Com
  `commit_installer = true`, o workflow também commita o `.exe` em `instalador/`
  na branch de teste (satisfaz "instalador na raiz do projeto teste").

## Instaladores de teste por módulo (REQ-013)

- Para **cada módulo criado**, publica-se um instalador na **branch de teste**
  com `unlock_all = true`: todos os módulos acessíveis, sem precisar liberar os
  anteriores.
- O override **não** altera o cálculo real de acerto (ADR 0003); ele só libera o
  acesso, para inspeção.
- A flag de build `TEST_UNLOCK_ALL` (CMake `-DTEST_UNLOCK_ALL=ON`) ativa o modo
  de inspeção: `ProgressStore` abre todos os módulos sem tocar no registro real
  de progresso.

## Runbook

```bash
# Reproduzir o build local (Linux, só compilação)
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DTEST_UNLOCK_ALL=ON
cmake --build build
ctest --test-dir build

# Empacotar o instalador local (embrulha o binário Linux; só para validar o .nsi)
./deploy/build-installer.sh

# Windows (com gerador do Visual Studio) — gera o .exe real
cmake -B build -G "Visual Studio 17 2022" -A x64 -DTEST_UNLOCK_ALL=ON
cmake --build build --config Release
makensis deploy/windows/installer.nsi
```

## Pendências

- Instalador de teste do **Módulo 1** (`module=1`, `unlock_all=true`): o build
  roda na branch `test`; baixe o artifact do run ou use `commit_installer=true`
  para tê-lo em `instalador/` (CM-010).
- Assinatura de código (R-12): sem certificado, o Windows mostra aviso.
- Confirmar licenças de redistribuição das dependências (R-09) antes de
  distribuir publicamente.
