#include "Course/Content/Topics.h"

// Topic 6A — Escala menor natural (Módulo 6, Etapa 6).
// Fonte de verdade do texto: docs/MUSIC.md §6.2 (bloco A).
namespace cursomusica::content
{

std::vector<ContentItem> topic6A()
{
    return {

        p (
            "Até aqui você estudou a escala maior e os intervalos que a constroem. Neste módulo você entra no mundo das tonalidades menores, que são a outra metade da música. Boa parte das músicas que você ouve — do rock ao samba, da bossa ao jazz — nasce de uma escala menor ou passa por ela. Entender a escala menor natural é o primeiro passo para tocar, acompanhar e improvisar nessas músicas."),
        p (
            "A escala menor natural também é chamada de modo eólio. Ela é feita com as mesmas sete notas de uma escala maior, mas começando por outro grau: o sexto. Por isso ela soa tão familiar e ao mesmo tempo tão diferente: as notas são as mesmas, o centro de repouso é outro, e o ouvido percebe imediatamente a mudança de clima."),
        c (
            "Objetivo do módulo: ampliar a compreensão harmônica e melódica para as tonalidades menores. Você vai montar campos harmônicos menores, comparar suas sonoridades com os campos maiores e reconhecer o que está sendo tocado — no instrumento e de ouvido."),

        h ("O que é a escala menor natural"),
        p (
            "A escala menor natural tem sete notas e a seguinte sequência de graus: 1, 2, b3, 4, 5, b6, b7. Os graus b3, b6 e b7 (terça, sexta e sétima menores) são o que dá à escala o seu caráter triste e melancólico. Se você comparar com a escala maior, verá que a única diferença é que esses três graus descem meio-tom."),
        b ("Escala maior de Dó: C D E F G A B (1 2 3 4 5 6 7)."),
        b ("Escala menor natural de Dó: C D Eb F G Ab Bb (1 2 b3 4 5 b6 b7)."),
        b ("A diferença está na terça, na sexta e na sétima: cada uma desce um semitom."),
        img ("m6_escala_menor_natural", "A escala de La menor natural no braço: tônica em roxo, notas da escala em ciano."),

        h ("O padrão de tons e semitons"),
        p (
            "Toda escala menor natural segue o mesmo padrão de distâncias entre as notas vizinhas: tom, semitom, tom, tom, semitom, tom, tom. É o padrão que garante que os graus caiam sempre em b3, b6 e b7, independentemente da nota de partida. Como na escala maior, esse padrão é o que permite transportar a escala para qualquer tonalidade."),
        tbl ({ "Passo", "De", "Para", "Distância" }, {
            { "1", "1 (tônica)", "2", "tom" },
            { "2", "2", "b3", "semitom" },
            { "3", "b3", "4", "tom" },
            { "4", "4", "5", "tom" },
            { "5", "5", "b6", "semitom" },
            { "6", "b6", "b7", "tom" },
            { "7", "b7", "8 (oitava)", "tom" },
        }),
        c (
            "Memorize assim: T - S - T - T - S - T - T. É o espelho do padrão maior (T T S T T T S), deslocado. Quem toca uma escala já toca a outra: basta começar três semitons abaixo (ou no sexto grau)."),

        h ("A relativa maior"),
        p (
            "Cada escala maior tem uma relativa menor, e cada escala menor natural tem uma relativa maior. As duas compartilham exatamente as mesmas notas e a mesma armadura de clave; o que muda é a nota que serve de repouso. A relativa menor começa no sexto grau da escala maior."),
        b ("Dó maior (C D E F G A B) tem como relativa menor Lá menor (A B C D E F G)."),
        b ("Sol maior tem como relativa menor Mi menor."),
        b ("Fá maior tem como relativa menor Ré menor."),
        tbl ({ "Escala maior", "Relativa menor", "Notas compartilhadas" }, {
            { "Dó maior (C)", "Lá menor (Am)", "nenhum acidente" },
            { "Sol maior (G)", "Mi menor (Em)", "F# (1 sustenido)" },
            { "Ré maior (D)", "Si menor (Bm)", "F# C# (2 sustenidos)" },
            { "Fá maior (F)", "Ré menor (Dm)", "Bb (1 bemol)" },
        }),
        aud ({ "A3", "B3", "C4", "D4", "E4", "F4", "G4", "A4" },
             "Escala de La menor natural subindo: A B C D E F G A."),
        part ("m6_partitura_menor_natural", { "A3", "B3", "C4", "D4", "E4", "F4", "G4", "A4" },
              "Partitura da escala de La menor natural. Pressione ouvir para escutar exatamente o que está escrito."),

        h ("Como localizar a escala no braço"),
        p (
            "Como o braço é uma régua de semitons, você localiza a escala menor natural de duas formas. A primeira é partir da tônica e aplicar o padrão T-S-T-T-S-T-T. A segunda é lembrar da relativa maior: a escala menor de Lá é a mesma escala de Dó maior, apenas começando três casas acima (ou três casas abaixo, conforme a corda)."),
        b ("Forma 1: ache a tônica e conte o padrão T-S-T-T-S-T-T."),
        b ("Forma 2: ache a relativa maior e toque a escala maior começando no sexto grau."),
        b ("No braço, a mesma nota aparece em várias cordas — use a posição que ficar mais confortável."),
        c (
            "Os exercícios deste tópico são tocados no instrumento: o app reconhece as notas que você toca e confere se elas pertencem à escala pedida, em qualquer posição do braço."),

        h ("O som da escala menor natural"),
        p (
            "A escala menor natural soa melancólica, introspectiva, às vezes nostálgica. Essa cor vem dos três graus abaixados. A terça menor é o que define o acorde menor; a sexta menor e a sétima menor dão o tom melancólico à melodia. Comparar a escala maior e a menor a partir da mesma tônica é a melhor forma de ouvir a diferença."),
        aud ({ "C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5" },
             "Escala de Dó maior: o som alegre e resolvido."),
        aud ({ "C4", "D4", "Eb4", "F4", "G4", "Ab4", "Bb4", "C5" },
             "Escala de Dó menor natural: as mesmas notas de partida e chegada, com a terça, a sexta e a sétima abaixadas."),
        c (
            "Ouça as duas escalas e perceba: a tônica é a mesma (Dó), mas o clima muda por completo. É a terça menor que faz toda a diferença."),

        h ("Graus e intervalos a partir da tônica"),
        p (
            "Assim como na escala maior, cada grau da escala menor natural forma um intervalo específico com a tônica. Conhecer esses intervalos é o que permite construir acordes, improvisar e reconhecer o material. A tabela abaixo mostra os intervalos a partir da tônica de La menor."),
        tbl ({ "Grau", "Nota em Lá menor", "Intervalo a partir da tônica", "Semitons" }, {
            { "1", "A", "uníssono", "0" },
            { "2", "B", "segunda maior", "2" },
            { "b3", "C", "terça menor", "3" },
            { "4", "D", "quarta justa", "5" },
            { "5", "E", "quinta justa", "7" },
            { "b6", "F", "sexta menor", "8" },
            { "b7", "G", "sétima menor", "10" },
            { "8", "A", "oitava justa", "12" },
        }),
        p (
            "Repare que a escala menor natural usa a terça menor (3 semitons), a sexta menor (8 semitons) e a sétima menor (10 semitons). Esses são exatamente os três intervalos que a distinguem da escala maior, que usa 4, 9 e 11 semitons."),

        h ("Aplicação prática"),
        p (
            "A escala menor natural é a base da improvisação em tonalidades menores e aparece o tempo todo no acompanhamento. Os três acordes principais de uma tonalidade menor natural são o i (menor), o iv (menor) e o v (menor). Só que o v menor não tem a sensível (a sétima maior), e por isso tem pouca força para puxar de volta à tônica — é o que motiva o estudo da escala menor harmônica, no próximo tópico."),
        b ("Tonalidade de Lá menor: i = Am, iv = Dm, v = Em."),
        b ("Para tocar uma música em Lá menor, você usa as notas da escala e os acordes do campo."),
        b ("A melodia tende a repousar na tônica, na terça menor ou na quinta."),
        aud ({ "A3", "C4", "E4", "A4" }, "Arpejo do acorde de Lá menor: tônica, terça menor e quinta."),

        h ("Erros comuns"),
        p (
            "Quem vem da escala maior costuma errar a terça (tocar a terça maior por hábito) e esquecer a sexta e a sétima menores. O app ajuda porque mede a distância real das notas tocadas e confirma se elas pertencem à escala. O jeito mais seguro é ouvir a escala e cantar junto antes de tocar, para o ouvido reconhecer o clima menor."),
        b ("Confira a terça: na escala menor, ela fica a 3 semitons da tônica."),
        b ("Confira a sexta e a sétima: abaixadas em relação à escala maior."),
        b ("Ouça e cante a escala antes de tocar — o ouvido guia o dedo."),

        h ("As três formas da escala menor"),
        p (
            "Quando se fala em \"escala menor\", na verdade existem três escalas diferentes: a menor natural, a menor harmônica e a menor melódica. Este módulo estuda as três, uma por vez. A menor natural é a base de todas: as outras duas são a menor natural com um ou dois graus alterados. Entender essa relação é o que evita a confusão mais comum de quem estuda tonalidades menores."),
        tbl ({ "Escala", "6º grau", "7º grau", "Para que serve" }, {
            { "menor natural", "b6", "b7", "base, campo menor natural" },
            { "menor harmônica", "b6", "7", "cadência V7 → i" },
            { "menor melódica", "6", "7", "jazz, acordes m7M" },
        }),
        c (
            "A diferença entre as três está apenas no sexto e no sétimo graus. Guarde esta tabela: ela resume todo o sistema das escalas menores."),

        h ("Como praticar a escala menor natural"),
        p (
            "Pratique a escala menor natural de três formas. Primeiro subindo e descendo, devagar, ouvindo cada nota. Depois em padrões de três notas (1-2-3, 2-3-4, 3-4-5…), que treinam a mecânica. Por fim, tocando a escala sobre um acorde menor de fundo, para ouvir como ela soa dentro da harmonia."),
        b ("Subida e descida: fixa a digitação e o som da escala."),
        b ("Padrões de três notas: treinam a independência dos dedos."),
        b ("Sobre o acorde de fundo: mostra a escala dentro da música."),
        c (
            "Nos exercícios deste tópico, toque a escala e os arpejos pedidos no instrumento. O app reconhece as notas e confere se elas pertencem à escala menor natural, em qualquer posição do braço."),

        h ("A escala menor na música que você ouve"),
        p (
            "Você já ouviu a escala menor natural milhares de vezes, mesmo sem saber o nome. Ela está no blues, no rock, no samba, na bossa e na MPB. Músicas tristes, introspectivas ou dramáticas costumam estar em tonalidade menor. Quando você aprende a escala menor natural, começa a reconhecer essa sonoridade nas músicas e a tocar junto."),
        b ("Blues e rock: usam a escala menor natural e a pentatônica menor (derivada dela)."),
        b ("Samba e bossa: usam a menor natural e os seus empréstimos."),
        b ("MPB: usa a menor natural com empréstimos do campo maior."),

        h ("A escala menor natural e a pentatônica menor"),
        p (
            "Uma consequência prática da escala menor natural é a pentatônica menor, que você provavelmente já toca. Ela é a escala menor natural sem o segundo e o sexto graus: ficam apenas cinco notas (1, b3, 4, 5, b7). É a escala mais usada no blues e no rock, justamente porque é a menor natural \"enxuta\", sem as notas que criam atrito."),
        b ("Menor natural: 1 2 b3 4 5 b6 b7 (sete notas)."),
        b ("Pentatônica menor: 1 b3 4 5 b7 (cinco notas)."),
        b ("Em Lá menor: A C D E G."),
        aud ({ "A3", "C4", "D4", "E4", "G4", "A4" }, "Pentatônica menor de Lá: a escala do blues e do rock."),
        c (
            "Se você já toca pentatônica menor, já toca a espinha dorsal da escala menor natural. Este módulo completa o que falta: o segundo, o sexto e a relação com o campo harmônico."),

        h ("Erros comuns ao estudar a escala menor"),
        p (
            "Quem começa nas tonalidades menores comete sempre os mesmos erros: esquece de abaixar a terça, a sexta ou a sétima; confunde a relativa maior com a paralela; ou toca a escala no braço inteiro sem saber onde está a tônica. Todos esses erros têm a mesma solução: ouvir e conferir."),
        b ("Abaixe a terça, a sexta e a sétima — as três são menores."),
        b ("Não confunda relativa (mesmas notas) com paralela (mesma tônica)."),
        b ("Saiba sempre onde está a tônica na posição em que você está tocando."),
        c (
            "O app é um bom conferente: ele reconhece as notas que você toca e verifica se elas pertencem à escala. Se você errar um grau, o feedback mostra na hora."),

        h ("Resumo do tópico"),
        b ("Escala menor natural (eólio): 1 2 b3 4 5 b6 b7."),
        b ("Padrão de intervalos: T-S-T-T-S-T-T."),
        b ("É a relativa menor de uma escala maior: mesmas notas, outro repouso."),
        b ("A terça menor define o caráter; a sexta e a sétima menores dão a cor melancólica."),
        b ("No braço, aplique o padrão a partir da tônica ou toque a relativa maior."),
        c (
            "Nos exercícios deste tópico, toque as escalas e os arpejos pedidos no instrumento. O app reconhece as notas e confere se elas pertencem à escala menor natural."),
    };
}

} // namespace cursomusica::content
