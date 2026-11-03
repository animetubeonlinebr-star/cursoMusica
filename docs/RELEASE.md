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

## Build e publicação

- Workflow: `.github/workflows/release.yml`.
- Dispara em tag `v*` e manualmente (`workflow_dispatch`), com o campo `module`
  (id do módulo) e `unlock_all` (override de teste).
- Artefato: `CursoMusica-Setup-<module|tag>.exe`, anexado ao release na tag e
  disponível como artifact do run na branch de teste.

## Instaladores de teste por módulo (REQ-013)

- Para **cada módulo criado**, publica-se um instalador na **branch de teste**
  com `unlock_all = true`: todos os módulos acessíveis, sem precisar liberar os
  anteriores.
- O override **não** altera o cálculo real de acerto (ADR 0003); ele só libera o
  acesso, para inspeção.
- A flag de build `TEST_UNLOCK_ALL` é lida em runtime como modo de inspeção.

## Runbook

```bash
# Reproduzir o build local (Linux, só compilação)
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release && cmake --build build

# Windows (com gerador do Visual Studio)
cmake -B build -G "Visual Studio 17 2022" -A x64 -DTEST_UNLOCK_ALL=ON
cmake --build build --config Release
makensis deploy/windows/installer.nsi
```

## Pendências

- Instalador de teste do **Módulo 1** (`module=1`, `unlock_all=true`) a publicar
  quando o workflow `release.yml` estiver no ar (CM-010).
- Assinatura de código (R-12): sem certificado, o Windows mostra aviso.
- Confirmar licenças de redistribuição das dependências (R-09) antes de
  distribuir publicamente.
