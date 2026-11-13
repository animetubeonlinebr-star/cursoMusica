# 0005 — Modelo de dados do curso e conteúdo do Módulo 1

Status: accepted
Data: 2026-11-02
Autor: architect + developer + musician (requisitos REQ-003, REQ-006, REQ-007,
REQ-008, REQ-016, REQ-017)

## Contexto

O currículo é linear (ADR 0003) e cada módulo precisa de: explicação antes do
desafio (REQ-003), curadoria de fontes (REQ-006), links e patterns citáveis
(REQ-007), exercícios mensuráveis (REQ-008) e padrão de andamento (REQ-015). O
primeiro módulo já existe como conteúdo (`docs/MUSIC.md`), mas ainda não existe
como dado dentro do aplicativo.

Isso levanta duas perguntas: **onde o conteúdo vive** e **como a UI o apresenta**.

## Decisão

1. **O conteúdo do curso é código, não um formato externo.** A fonte de verdade
   é `docs/MUSIC.md` (dono: musician); a versão executável é um catálogo em C++
   (`Source/Course/ModuleCatalog.cpp`), compilado no binário. O app não lê PDF
   nem arquivo externo em tempo de execução (REQ-005).
2. **Tipos de dados do curso** em `Source/Course/Module.h`:
   `CourseModule`, `LessonBlock`, `Exercise` e `PracticeTrack`.
3. **Sem dependência nova.** O modelo usa só `juce::String`/`std::vector`;
   nenhuma biblioteca de serialização entra por causa disto (mantém o ADR 0002
   intacto).
4. **Explicação antes do desafio é estrutural.** O módulo tem uma lista ordenada
   de blocos de aula e, só depois, os exercícios; a UI abre na explicação e não
   permite pular para o desafio sem passar por ela (REQ-003).
5. **Módulo 1 implementado por completo.** O catálogo traz o Módulo 1 com os nove
   blocos (A–I, incluindo rítmica/contagem), os exercícios EX-1.A.1 a EX-1.I.1, o
   desafio de gate e a trilha de prática, exatamente como especificado em
   `docs/MUSIC.md`. As apostilas de curadoria que sustentam os blocos são citadas
   em `CourseModule::sources` (REQ-006).
6. **CAGED, cifrado e rítmica são dados, não texto solto.** O módulo expõe a
   lista de formas CAGED, a tabela de cifras e as células rítmicas (`RhythmCell`)
   como dados, para a UI renderizar e para os exercícios poderem referenciá-los.
7. **Só o Módulo 1 nesta entrega.** Os módulos 2–20 ficam declarados no mapa
   módulo → nível (MUSIC.md) e entram em entregas seguintes; a UI mostra os não
   implementados como bloqueados, não como ausentes.

## Alternativas rejeitadas

- **Ler o conteúdo de arquivos (JSON/XML) em runtime** — adiciona I/O, formato e
  dependência; contraria "tudo dentro do software" e o ADR 0002 sem necessidade
  nesta fase.
- **Escrever o texto direto no código da UI** — acopla conteúdo a layout e
  impede o musician de manter o currículo sem mexer em UI.
- **Implementar os 20 módulos de uma vez** — entrega gigante e não revisável;
  contraria a disciplina de PR pequeno.

## Consequências

- O **musician** mantém `docs/MUSIC.md`; qualquer mudança de conteúdo é
  espelhada no catálogo (o QA confere que não divergiram).
- O **designer** renderiza `CourseModule` na UI de módulos, com a explicação
  primeiro.
- O **QA** verifica: módulo tem explicação, todo exercício tem verificação, todo
  módulo cita ≥1 pattern e ≥1 link (REQ-007).
- O **data-engineer** ligará, em CM-008, os resultados dos exercícios ao schema
  de medição já definido em `docs/DATA.md`.
