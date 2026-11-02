# BACKLOG — CursoMusica

Dono: **po**. Ordenado por valor (impacto no aluno × impacto no negócio).
Histórias em detalhe ficam em `docs/stories/` quando crescerem; aqui fica o
índice priorizado.

Deriva de `docs/ROADMAP.md`. Formato de história e DoD: `AGENTS.md` §5 e §6.
Critérios musicais (referência de afinação, tolerância em cents, alcance de
detecção, tempo) derivam de `docs/MUSIC.md` (dono: `musician`).

## Pronto para desenvolvimento (topo)

### [CM-001] Afinador e medidor reais na UI — valor: H — tamanho: M — status: ready
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
Como o time de desenvolvimento, eu quero que cada PR compile e rode os testes
automaticamente, para que nenhum erro bobo chegue à main.

Critérios de aceite:
- Dado um PR, quando eu abro ou atualizo, então o CI clona JUCE 8.0.4 e compila
  no Linux sem novos avisos.
- Dado o build sem o ASIO SDK, quando o CI roda, então o build passa (ASIO é
  opcional por design).
- Dado um PR que quebra o build, quando o CI termina, então o check fica vermelho.

Dependências: nenhuma. Owner: devops.

## Próximas (refinando)

### [CM-003] Playback com velocidade e loop — valor: H — tamanho: L — status: draft
Como um aluno, eu quero tocar um trecho em loop e mais devagar, para que eu
possa estudar passagens difíceis.

Critérios de aceite (rascunho — precisam virar testáveis):
- Loop definido por pontos A/B com precisão de amostra.
- Velocidade de 25% a 100% sem mudar o tom (a definir com o architect).

Dependências: CM-001. Bloqueio: precisa de decisão de arquitetura (time-stretch).

### [CM-004] Presets de configuração de áudio — valor: M — tamanho: S — status: draft
Como um aluno, eu quero que o app lembre meu dispositivo, buffer e plugins, para
que eu não reconfigure a cada sessão.

Critérios de aceite (rascunho): salvar/restaurar backend, dispositivo, sample
rate, buffer e cadeia de plugins entre execuções.

### [CM-005] Metrônomo de estudo — valor: M — tamanho: M — status: draft
Como um aluno, eu quero um metrônomo configurável, para que eu possa praticar no
tempo e no compasso certos.

Critérios de aceite (derivados de `docs/MUSIC.md`, dono: musician):
- BPM ajustável de 20 a 300, com acento audivelmente distinto no tempo forte.
- Subdivisões: 1/4, 1/8, tercinas, 1/16.
- Compassos: 2/4, 3/4, 4/4, 6/8, 12/8 e métricas ímpares (5/4, 7/8).

Dependências: nenhuma. Bloqueio: confirmar se haverá detecção de tempo tocado.

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
