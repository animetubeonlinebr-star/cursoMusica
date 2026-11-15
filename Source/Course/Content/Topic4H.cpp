#include "Course/Content/Topics.h"

// Topic 4H — As cinco fases das famílias (Módulo 4, Etapa 4).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 4 — construção de acordes).
namespace cursomusica::content
{

std::vector<ContentItem> topic4H()
{
    return {

        p (
            "Aprender uma família de acordes não é decorar todas as formas de uma vez: é um processo em cinco fases. Cada fase acrescenta uma habilidade sobre a anterior, de modo que você constrói o domínio de forma sólida, sem pular etapas. Este tópico apresenta esse roteiro — as cinco fases das famílias — para que você saiba exatamente onde está e para onde vai em cada etapa do estudo."),
        p (
            "As fases valem para qualquer família: maior, menor, dominante, diminuta. Primeiro você reconhece a forma; depois a toca em todas as posições; em seguida aprende a mudar de acorde mantendo a forma; depois aplica em uma progressão real; e, por fim, cria e inverte livremente. É um caminho de dentro para fora, do concreto ao criativo."),
        c (
            "Cinco fases: reconhecer a forma → tocar em todas as posições → mudar de acorde → aplicar em progressão → criar livremente."),
        img ("m4_cinco_fases", "As cinco fases das famílias de acordes, da forma até a aplicação."),

        h ("Fase 1 — reconhecer a forma"),
        p (
            "A primeira fase é puramente visual e motora: você aprende a montar a forma no braço e a reconhecê-la de relance. Nesta fase não há preocupação com mudança de acorde nem com música; o objetivo é que a mão saiba onde cada dedo vai. É a fase da precisão e da limpeza do som, em que você confere se todas as cordas soam sem abafamento."),
        b ("Objetivo: montar a forma sem olhar."),
        b ("Confira: todas as cordas soam limpas."),
        b ("Não se preocupe com velocidade ainda."),

        h ("Fase 2 — tocar em todas as posições"),
        p (
            "Na segunda fase, você leva a forma para todas as posições do braço. Como cada casa é um semitom, deslocar a forma gera doze acordes diferentes. O objetivo é que a mão aprenda a transpor automaticamente, sem precisar pensar casa por casa. É a fase em que a forma deixa de ser um ponto fixo e passa a ser um molde móvel."),
        b ("Desloque a forma pelo braço, casa por casa."),
        b ("Diga o nome do acorde em cada posição."),
        b ("Objetivo: transpor sem hesitar."),
        aud ({ "F2", "C3", "F3", "A3", "C4", "F4", "G2", "D3", "G3", "B3", "D4", "G4" },
             "A mesma forma (de Fá) deslocada: Fá maior e depois Sol maior."),

        h ("Fase 3 — mudar de acorde mantendo a forma"),
        p (
            "A terceira fase introduz a mudança: sair de uma forma e ir para outra, ou mudar a qualidade da mesma forma, mantendo o tempo. Aqui entra a coordenação entre a mão que pressiona e a mão que ataca. O objetivo é trocar de acorde sem parar a música, com o mínimo de movimento. É a fase em que o acompanhamento começa a nascer."),
        b ("Troque entre duas formas sem parar o tempo."),
        b ("Mude a qualidade da mesma forma (maior → menor)."),
        b ("Minimize o movimento da mão."),

        h ("Fase 4 — aplicar em uma progressão"),
        p (
            "A quarta fase coloca a família em contexto: você toca uma progressão real, com vários acordes, usando as formas aprendidas. É aqui que a teoria encontra a música. O objetivo é acompanhar uma sequência de acordes com fluidez, escolhendo as formas que mantêm a mão em uma região confortável e a condução de vozes suave."),
        b ("Toque uma progressão de quatro acordes sem parar."),
        b ("Escolha formas próximas para a mão não saltar."),
        b ("Objetivo: acompanhar a música do começo ao fim."),
        aud ({ "C4", "E4", "G4", "A3", "C4", "E4", "D4", "F4", "A4", "G3", "B3", "D4", "C4", "E4", "G4" },
             "Progressão C – Am – Dm – G: a família maior e menor em contexto."),

        h ("Fase 5 — criar e inverter livremente"),
        p (
            "A quinta fase é a liberdade: você já não pensa em formas, mas em notas e sons. Consegue inverter acordes, omitir notas, escolher a região do braço pela cor que quer, criar vozes próprias. É o domínio da família. Nesta fase, a teoria se tornou linguagem, e você acompanha qualquer música com personalidade e precisão. É o objetivo de todo o estudo de acordes."),
        b ("Escolha a região do braço pela cor que deseja."),
        b ("Inverta e omita notas com intenção."),
        b ("Crie vozes próprias com base nas notas."),

        h ("As fases aplicadas à família maior"),
        p (
            "Vamos ver as cinco fases na família maior. Na fase 1, você aprende a forma de Dó maior. Na fase 2, desloca essa forma por todo o braço, gerando Dó, Ré, Mi, Fá e assim por diante. Na fase 3, troca entre maior e menor e entre formas diferentes. Na fase 4, toca uma progressão como Dó – Fá – Sol – Dó. Na fase 5, inverte e cria vozes. Cada fase prepara a seguinte."),
        tbl ({ "Fase", "Família maior", "O que você treina" }, {
            { "1", "forma de Dó maior", "montar e limpar" },
            { "2", "forma deslocada", "transpor" },
            { "3", "maior ↔ menor", "trocar" },
            { "4", "C – F – G – C", "aplicar" },
            { "5", "inversões e vozes", "criar" },
        }),

        h ("As fases aplicadas à família menor"),
        p (
            "A família menor segue o mesmo roteiro. Na fase 1, você aprende a forma de Lá menor. Na fase 2, desloca pelo braço (Lá menor, Si menor, Dó menor…). Na fase 3, troca entre menor e maior e entre formas. Na fase 4, toca uma progressão como Lá menor – Ré menor – Mi7 – Lá menor. Na fase 5, cria inversões e vozes. Note que a estrutura é idêntica: só mudam as notas."),
        b ("Fase 1: forma de Lá menor."),
        b ("Fase 2: deslocar pelo braço."),
        b ("Fase 3: trocar menor ↔ maior."),
        b ("Fase 4: progressão Am – Dm – E7 – Am."),
        b ("Fase 5: inversões e vozes próprias."),

        h ("Por que respeitar a ordem"),
        p (
            "É tentador pular para a fase 5 e tentar criar antes de dominar a forma. Mas cada fase dá a base para a seguinte: sem a forma limpa (fase 1), a transposição (fase 2) sai errada; sem a transposição, a troca (fase 3) trava; sem a troca, a progressão (fase 4) para no meio. Respeitar a ordem não é burocracia: é o caminho mais rápido para tocar bem."),
        b ("A fase 1 garante a base para todas as outras."),
        b ("Pular etapas gera vícios difíceis de corrigir."),
        b ("A ordem é o atalho, não o obstáculo."),

        h ("As fases aplicadas à família dominante"),
        p (
            "A família dominante tem um papel especial: ela cria tensão e pede resolução. Nas cinco fases, você aprende a forma de sétima dominante, transpõe pelo braço, troca entre dominante e tônica, aplica em uma cadência (V7 → I) e, por fim, cria alterações (b9, #9, b5). Dominar essa família é dominar o motor da harmonia funcional: quase toda resolução passa por um acorde dominante."),
        b ("Fase 1: forma de dominante (0–4–7–10)."),
        b ("Fase 2: deslocar pelo braço."),
        b ("Fase 3: trocar dominante ↔ tônica."),
        b ("Fase 4: cadência G7 → C7M."),
        b ("Fase 5: criar alterações (b9, #9, b5)."),
        aud ({ "G3", "B3", "D4", "F4", "C4", "E4", "G4", "B4" },
             "Família dominante em ação: G7 resolvendo em C7M."),

        h ("As fases na prática diária"),
        p (
            "Você pode organizar cada sessão de estudo pelas fases. Comece com cinco minutos de forma (fase 1), depois cinco de transposição (fase 2), depois cinco de troca (fase 3), depois toque uma música (fase 4) e, no fim, improvise vozes (fase 5). Essa rotina cobre todas as habilidades de uma família em uma única sessão, sem pular etapas. Com o tempo, você passa por várias famílias."),
        b ("Fase 1 e 2: aquecimento técnico."),
        b ("Fase 3: coordenação."),
        b ("Fase 4: música."),
        b ("Fase 5: criatividade."),

        h ("Como medir se você passou de fase"),
        p (
            "Cada fase tem um critério claro de conclusão. Na fase 1, você monta a forma sem olhar. Na fase 2, transpõe sem hesitar. Na fase 3, troca de acorde mantendo o tempo. Na fase 4, acompanha a progressão do começo ao fim. Na fase 5, cria sem depender de formas decoradas. O app ajuda a verificar as fases tocáveis, conferindo as notas que você toca."),
        b ("Fase 1: monta sem olhar."),
        b ("Fase 2: transpõe sem hesitar."),
        b ("Fase 3: troca no tempo."),
        b ("Fase 4: acompanha a progressão inteira."),
        b ("Fase 5: cria livremente."),
        part ("m4_partitura_familia", { "C4", "E4", "G4", "D#4", "F#4" },
              "Partitura da família de Dó: a forma maior (Dó–Mi–Sol) e a diminuta (Dó–Mi♭–Sol♭)."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é tentar tocar rápido antes de dominar a forma, o que cria tensão e som sujo. Outro erro é decorar apenas uma posição e travar nas outras. E há o erro de estudar várias famílias ao mesmo tempo, sem consolidar nenhuma. O caminho é dominar uma família por vez, uma fase por vez, com paciência."),
        b ("Velocidade vem depois da precisão."),
        b ("Aprenda a forma em todas as posições."),
        b ("Uma família por vez, uma fase por vez."),

        h ("As fases e o metrônomo"),
        p (
            "A partir da fase 3, o metrônomo entra como aliado. Trocar de acorde no tempo é o que separa o estudo técnico do acompanhamento real. Comece devagar — o BPM meta deste módulo é 72 — e aumente só quando a troca estiver limpa. Tocar no tempo certo vale mais do que tocar rápido: a grade do metrônomo mostra se você está estável. O gate deste módulo cobra exatamente isso."),
        b ("Fase 3 em diante: use o metrônomo."),
        b ("Comece devagar e aumente com segurança."),
        b ("Estabilidade rítmica vale mais que velocidade."),
        p (
            "Um treino eficiente é escolher dois acordes e alternar entre eles a cada dois tempos, na grade. Quando a troca estiver limpa, reduza para um tempo por acorde. Esse tipo de exercício prepara a fase 4 e constrói a segurança necessária para acompanhar qualquer música no tempo certo."),

        h ("As fases e a memorização"),
        p (
            "As cinco fases também organizam a memorização. Em vez de tentar guardar dezenas de formas soltas, você memoriza cinco formas e as suas qualidades. Cada forma é uma 'caixa' que contém maior, menor, dominante e sétima maior. Assim, sua memória trabalha com estruturas, não com listas. É por isso que o sistema CAGED, associado às cinco fases, multiplica o que você consegue tocar."),
        b ("Memorize estruturas, não listas de acordes."),
        b ("Cinco formas × várias qualidades = muitos acordes."),
        b ("A memória trabalha melhor com padrões."),

        h ("Aplicação musical"),
        p (
            "Escolha uma família — digamos, a menor com sétima — e percorra as cinco fases em uma única sessão de estudo. Comece montando a forma de Lá menor com sétima; depois desloque pelo braço; depois troque entre as formas; depois toque uma progressão de jazz ou de bossa que use acordes menores com sétima; e, por fim, crie inversões. Você vai sentir o progresso de fase em fase."),
        b ("Uma família, cinco fases, uma sessão."),
        b ("Comece pela forma, termine criando."),
        b ("O app confere as notas de cada fase tocável."),
        aud ({ "A3", "C4", "E4", "G4", "D4", "F4", "A4", "C5", "E3", "G3", "B3", "D4" },
             "Família menor com sétima: Am7, Dm7 e Em7 em sequência."),

        h ("Resumo do tópico"),
        b ("As cinco fases: forma → transposição → troca → progressão → criação."),
        b ("Cada fase dá a base para a seguinte; respeite a ordem."),
        b ("As fases valem para qualquer família (maior, menor, dominante…)."),
        b ("Cada fase tem um critério claro de conclusão."),
        b ("O objetivo final é criar vozes próprias com liberdade."),
        c (
            "Nos exercícios deste tópico, toque as progressões pedidas passando pelas fases. O app reconhece as notas e confere cada acorde, aceitando qualquer posição do braço."),
    };
}

} // namespace cursomusica::content
