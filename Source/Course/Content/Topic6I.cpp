#include "Course/Content/Topics.h"

// Topic 6I — Modos dórico, frígio, lídio, mixolídio e lócrio (Módulo 6, Etapa 6).
// Fonte de verdade do texto: docs/MUSIC.md §6.2 (bloco I).
namespace cursomusica::content
{

std::vector<ContentItem> topic6I()
{
    return {

        p (
            "Você já viu os modos da menor harmônica e da menor melódica. Agora vamos estudar os modos gregos clássicos, que nascem da escala maior: jônio, dórico, frígio, lídio, mixolídio, eólio e lócrio. Eles são a base da música modal — do rock ao jazz, da MPB ao funk — e o vocabulário que todo guitarrista precisa ter na ponta dos dedos."),
        p (
            "A ideia é a mesma dos outros modos: a mesma escala vista de pontos de partida diferentes. Mas aqui partimos da escala maior, o que torna os modos gregos mais fáceis de entender e de tocar. Este tópico apresenta os sete, com destaque para o dórico, o frígio, o lídio e o mixolídio, que são os mais usados na prática."),
        c (
            "Ideia central: cada modo grego é a escala maior começando num grau diferente. As notas não mudam; o centro e o clima, sim."),

        h ("O que são os modos gregos"),
        p (
            "Os modos gregos são sete escalas que compartilham as notas da escala maior, mas têm tônicas diferentes. Se você tocar todas as notas brancas do piano começando em Dó, obtém o jônio (a escala maior). Começando em Ré, obtém o dórico; em Mi, o frígio; em Fá, o lídio; em Sol, o mixolídio; em Lá, o eólio (a menor natural); e em Si, o lócrio."),
        b ("Modo 1 (jônio): começa no 1º grau — é a escala maior."),
        b ("Modo 2 (dórico): começa no 2º grau."),
        b ("Modo 3 (frígio): começa no 3º grau."),
        b ("Modo 4 (lídio): começa no 4º grau."),
        b ("Modo 5 (mixolídio): começa no 5º grau."),
        b ("Modo 6 (eólio): começa no 6º grau — é a menor natural."),
        b ("Modo 7 (lócrio): começa no 7º grau."),
        img ("m6_modos_gregos", "Os sete modos gregos, com a fórmula de graus de cada um."),

        h ("Jônio (1 2 3 4 5 6 7)"),
        p (
            "O jônio é a própria escala maior. Ele soa alegre, resolvido e familiar. É usado sobre acordes maiores com sétima maior (maj7) e é o ponto de partida de todos os outros modos."),
        b ("Fórmula: 1 2 3 4 5 6 7."),
        b ("Som: alegre, resolvido, familiar."),
        b ("Uso: sobre acordes maj7 (I)."),
        aud ({ "C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5" }, "Jônio a partir de Dó: a escala maior."),

        h ("Dórico (1 2 b3 4 5 6 b7)"),
        p (
            "O dórico é um modo menor com a sexta maior (6). Ele soa menor, mas com um brilho que a menor natural não tem — é o modo do jazz, do funk e da música celta. É usado sobre acordes menores com sétima (m7), especialmente o ii de uma cadência."),
        b ("Fórmula: 1 2 b3 4 5 6 b7."),
        b ("Som: menor com brilho, sofisticado."),
        b ("Uso: sobre acordes m7 (ii do campo maior e i do modal)."),
        aud ({ "D4", "E4", "F4", "G4", "A4", "B4", "C5", "D5" }, "Dórico a partir de Ré: menor com sexta maior."),
        part ("m6_partitura_dorico", { "D4", "E4", "F4", "G4", "A4", "B4", "C5", "D5" },
              "Partitura da escala de Ré dórico. Ouça o brilho da sexta maior."),

        h ("Frígio (1 b2 b3 4 5 b6 b7)"),
        p (
            "O frígio é um modo menor com a segunda abaixada (b2). A b2 dá um som espanhol, flamenco e dramático. É usado sobre acordes menores com sétima e sobre o acorde de terceiro grau de uma tonalidade maior. É o modo do flamenco e de muito heavy metal."),
        b ("Fórmula: 1 b2 b3 4 5 b6 b7."),
        b ("Som: espanhol, dramático, flamenco."),
        b ("Uso: sobre acordes m7 (iii do campo maior; i do modal espanhol)."),
        aud ({ "E4", "F4", "G4", "A4", "B4", "C5", "D5", "E5" },
             "Frígio a partir de Mi: o som espanhol, com a segunda abaixada."),

        h ("Lídio (1 2 3 #4 5 6 7)"),
        p (
            "O lídio é um modo maior com a quarta aumentada (#4). Ele soa brilhante, etéreo e flutuante, e é usado sobre acordes maiores com sétima maior (maj7), especialmente o acorde de quarto grau de uma tonalidade maior. É um dos modos mais bonitos e mais usados do jazz."),
        b ("Fórmula: 1 2 3 #4 5 6 7."),
        b ("Som: brilhante, etéreo, flutuante."),
        b ("Uso: sobre acordes maj7 (IV do campo maior; i do modal)."),
        aud ({ "F4", "G4", "A4", "B4", "C5", "D5", "E5", "F5" },
             "Lídio a partir de Fá: o brilho da quarta aumentada."),

        h ("Mixolídio (1 2 3 4 5 6 b7)"),
        p (
            "O mixolídio é um modo maior com a sétima menor (b7). Ele soa como um dominante \"relaxado\", sem a tensão do dominante clássico — é o som do blues, do rock e do funk. É usado sobre acordes de dominante com sétima (7) e é o modo mais tocado sobre o V de uma tonalidade maior."),
        b ("Fórmula: 1 2 3 4 5 6 b7."),
        b ("Som: blues, rock, relaxado."),
        b ("Uso: sobre acordes 7 (V do campo maior; i do modal blues)."),
        aud ({ "G4", "A4", "B4", "C5", "D5", "E5", "F5", "G5" },
             "Mixolídio a partir de Sol: o som do blues e do rock."),

        h ("Eólio (1 2 b3 4 5 b6 b7)"),
        p (
            "O eólio é a própria escala menor natural (tópico A). Ele soa melancólico e introspectivo. É usado sobre acordes menores com sétima (m7) e é a base da tonalidade menor."),
        b ("Fórmula: 1 2 b3 4 5 b6 b7."),
        b ("Som: melancólico, introspectivo."),
        b ("Uso: sobre acordes m7 (vi do campo maior; i do campo menor)."),
        aud ({ "A3", "B3", "C4", "D4", "E4", "F4", "G4", "A4" }, "Eólio a partir de Lá: a escala menor natural."),

        h ("Lócrio (1 b2 b3 4 b5 b6 b7)"),
        p (
            "O lócrio é o modo mais instável: ele tem a quinta diminuta (b5), que é o intervalo mais tenso da escala. Ele é usado sobre acordes meio-diminutos (m7(b5)) e raramente aparece como tonalidade. É o modo do acorde de sétimo grau de uma tonalidade maior."),
        b ("Fórmula: 1 b2 b3 4 b5 b6 b7."),
        b ("Som: instável, tenso, meio-diminuto."),
        b ("Uso: sobre acordes m7(b5) (vii do campo maior)."),
        aud ({ "B3", "C4", "D4", "E4", "F4", "G4", "A4", "B4" },
             "Lócrio a partir de Si: o som instável da quinta diminuta."),

        h ("Os modos e o campo harmônico"),
        p (
            "Cada acorde do campo harmônico maior tem um modo que combina com ele. Isso é a ponte entre a harmonia (os acordes) e a melodia (a improvisação). Quando você vê um acorde, você sabe qual modo usar — e é isso que permite improvisar com sentido."),
        tbl ({ "Grau", "Acorde em Dó maior", "Modo", "Cor" }, {
            { "I", "C7M", "jônio", "alegre" },
            { "ii", "Dm7", "dórico", "menor com brilho" },
            { "iii", "Em7", "frígio", "espanhol" },
            { "IV", "F7M", "lídio", "etéreo" },
            { "V", "G7", "mixolídio", "blues" },
            { "vi", "Am7", "eólio", "melancólico" },
            { "vii", "Bm7(b5)", "lócrio", "instável" },
        }),
        c (
            "Esta tabela é a ponte entre os módulos anteriores e a improvisação. Guarde-a: para cada acorde, há um modo que cai como uma luva."),

        h ("Modos e acordes: o som de cada um na música"),
        p (
            "Na música, cada modo aparece sobre um tipo de acorde e cria uma cor específica. O dórico dá ao acorde menor um brilho de jazz; o frígio dá ao menor um som espanhol; o lídio dá ao acorde maior um brilho flutuante; o mixolídio dá ao dominante um som de blues relaxado. Reconhecer essas cores é o que permite escolher o modo certo para cada momento."),
        b ("Dórico sobre m7: som de jazz, funk e música celta."),
        b ("Frígio sobre m7: som espanhol, flamenco, metal."),
        b ("Lídio sobre maj7: som etéreo, de trilha sonora."),
        b ("Mixolídio sobre 7: som de blues, rock e funk."),
        aud ({ "E4", "F4", "G4", "A4", "B4", "C5", "D5", "E5" }, "Frígio sobre Mi: o som espanhol do modo."),
        c (
            "Note que o modo e o acorde andam juntos: tocar dórico sobre um acorde maior soa errado. A escolha do modo depende sempre do acorde que está soando."),

        h ("Como praticar os modos"),
        p (
            "Pratique os modos de duas formas. Primeiro, toque todos a partir da mesma tônica (Dó dórico, Dó frígio, Dó lídio…) para ouvir a diferença de clima com a mesma nota de partida. Depois, toque todos a partir das notas brancas (Dó jônio, Ré dórico, Mi frígio…) para sentir que são a mesma escala vista de pontos diferentes."),
        b ("Mesma tônica: C jônio, C dórico, C frígio, C lídio, C mixolídio, C eólio, C lócrio."),
        b ("Mesma escala: C jônio, D dórico, E frígio, F lídio, G mixolídio, A eólio, B lócrio."),
        b ("Compare os pares e ouça o que muda."),
        c (
            "Nos exercícios deste tópico, você reconhece os modos pelo som e toca as suas fórmulas no instrumento. O app confere as notas que você toca, em qualquer posição."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é tocar um modo sem respeitar o acorde que está soando: o dórico só soa dórico sobre um acorde menor; o lídio, sobre um acorde maior. Outro erro é confundir o frígio (b2) com o frígio dominante (3 maior, do tópico C). Ouça o acorde de fundo antes de escolher o modo."),
        b ("Respeite o acorde: cada modo combina com um tipo de acorde."),
        b ("Não confunda frígio (b3) com frígio dominante (3)."),
        b ("Toque o modo sobre um acorde de fundo para ouvir o caráter."),

        h ("A tabela completa dos modos gregos"),
        p (
            "A tabela abaixo reúne os sete modos gregos com as suas fórmulas e os acordes com que combinam. É a referência que você consulta enquanto não memorizou os sete. Repare que os três primeiros modos são menores (terça menor) e os três seguintes são maiores (terça maior), e que o último é diminuto."),
        tbl ({ "Modo", "Fórmula", "Tônica (a partir de Dó maior)", "Acorde" }, {
            { "jônio", "1 2 3 4 5 6 7", "C", "maj7" },
            { "dórico", "1 2 b3 4 5 6 b7", "D", "m7" },
            { "frígio", "1 b2 b3 4 5 b6 b7", "E", "m7" },
            { "lídio", "1 2 3 #4 5 6 7", "F", "maj7" },
            { "mixolídio", "1 2 3 4 5 6 b7", "G", "7" },
            { "eólio", "1 2 b3 4 5 b6 b7", "A", "m7" },
            { "lócrio", "1 b2 b3 4 b5 b6 b7", "B", "m7(b5)" },
        }),
        c (
            "Note que cada modo tem a tônica num grau da escala de Dó maior: C, D, E, F, G, A, B. São as sete notas da escala, cada uma virando a tônica de um modo."),

        h ("A cor de cada modo"),
        p (
            "Cada modo tem uma nota característica que o diferencia dos outros. O dórico tem a sexta maior; o frígio, a segunda menor; o lídio, a quarta aumentada; o mixolídio, a sétima menor. É essa nota que dá a cor do modo e que você deve procurar na melodia e no acorde de fundo. Identificar a nota característica é o atalho para reconhecer o modo de ouvido."),
        b ("Dórico: a sexta maior (6) dá o brilho."),
        b ("Frígio: a segunda menor (b2) dá o som espanhol."),
        b ("Lídio: a quarta aumentada (#4) dá o brilho etéreo."),
        b ("Mixolídio: a sétima menor (b7) dá o som do blues."),
        aud ({ "D4", "E4", "F4", "G4", "A4", "B4", "C5", "D5" }, "Dórico: a sexta maior (Si) é a nota característica."),
        aud ({ "G4", "A4", "B4", "C5", "D5", "E5", "F5", "G5" }, "Mixolídio: a sétima menor (Fá) é a nota característica."),

        h ("Como os modos se relacionam com a escala maior"),
        p (
            "Os sete modos gregos nada mais são do que a escala maior vista de sete pontos de partida. Isso tem uma consequência prática enorme: se você já sabe a escala maior, já sabe os sete modos. Basta começar a escala num grau diferente. A única coisa que muda é a nota de repouso — e é isso que muda o clima."),
        b ("Escala de Dó maior: C D E F G A B."),
        b ("Comece em Ré: Ré dórico (mesmas notas)."),
        b ("Comece em Mi: Mi frígio (mesmas notas)."),
        b ("E assim por diante, até o lócrio em Si."),
        c (
            "Esta é a razão pela qual os modos gregos são fáceis de estudar: você não aprende sete escalas novas, aprende uma só — vista de sete ângulos."),

        h ("Resumo do tópico"),
        b ("Modos gregos: sete escalas que compartilham as notas da escala maior."),
        b ("Jônio (maior), dórico, frígio, lídio, mixolídio, eólio (menor) e lócrio."),
        b ("Dórico, frígio, lídio e mixolídio são os mais usados na prática."),
        b ("Cada acorde do campo tem um modo que combina com ele."),
        b ("Praticar com a mesma tônica e com a mesma escala revela a diferença de clima."),
        part ("m6_partitura_gregos", { "C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5" },
              "Partitura do modo jônio (escala de Dó maior), a base dos modos. Ouça o que está escrito."),
    };
}

} // namespace cursomusica::content
