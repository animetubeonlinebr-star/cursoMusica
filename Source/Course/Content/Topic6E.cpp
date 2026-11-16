#include "Course/Content/Topics.h"

// Topic 6E — Modos da menor melódica (Módulo 6, Etapa 6).
// Fonte de verdade do texto: docs/MUSIC.md §6.2 (bloco E).
namespace cursomusica::content
{

std::vector<ContentItem> topic6E()
{
    return {

        p (
            "Assim como a menor harmônica, a escala menor melódica gera sete modos. E aqui está a boa notícia: os modos da menor melódica são os mais usados do jazz moderno. Quatro deles aparecem o tempo todo em standards, na bossa nova e na MPB. Estudá-los é abrir a porta para a improvisação moderna."),
        p (
            "Cada modo tem a sua fórmula de graus e combina com um tipo de acorde. Neste tópico você conhece os sete, com destaque para o quarto (lídio dominante) e o sétimo (escala alterada), que são os mais tocados sobre acordes de dominante."),
        c (
            "Ideia central: um modo é a mesma escala vista de outro ponto de partida. As notas não mudam; o que muda é o centro e o clima."),

        h ("O que é um modo"),
        p (
            "Modo é uma escala obtida começando por outro grau de uma escala existente. A escala de Lá menor melódica gera sete modos, um para cada grau. Como as notas são as mesmas, os intervalos a partir da nova tônica mudam, e com eles o som."),
        b ("Modo 1: começa no 1º grau — é a própria menor melódica."),
        b ("Modo 2: começa no 2º grau — notas da escala, tônica em Si."),
        b ("E assim por diante, até o modo 7, começando no 7º grau."),
        img ("m6_modos_melodica", "Os sete modos da escala menor melódica, com a fórmula de graus de cada um."),

        h ("Modo 1 — menor melódica (1 2 b3 4 5 6 7)"),
        p (
            "O primeiro modo é a própria escala menor melódica. Ele soa suave e moderno, com a terça menor e a sexta e sétima maiores. É usado sobre acordes menores com sétima maior (m7M) e é a base da sonoridade menor moderna do jazz."),
        b ("Fórmula: 1 2 b3 4 5 6 7."),
        b ("Som: suave, sofisticado, menor com brilho."),
        b ("Uso: sobre acordes m7M."),
        aud ({ "A3", "B3", "C4", "D4", "E4", "F#4", "G#4", "A4" }, "Modo 1: a própria escala menor melódica."),

        h ("Modo 2 — dórico com segunda menor (1 b2 b3 4 5 6 b7)"),
        p (
            "O segundo modo é um dórico com a segunda abaixada (b2). Ele é usado sobre acordes menores com sétima suspensa (m7sus) e sobre o acorde de segundo grau de uma cadência menor. A b2 dá um toque de tensão ao som dórico, que normalmente é suave."),
        b ("Fórmula: 1 b2 b3 4 5 6 b7."),
        b ("Som: dórico com tensão na segunda."),
        b ("Uso: sobre acordes m7sus4 e o ii do campo menor."),

        h ("Modo 3 — lídio aumentado (1 2 3 #4 #5 6 7)"),
        p (
            "O terceiro modo tem a quarta aumentada (#4) e a quinta aumentada (#5). Ele é usado sobre acordes maiores com quinta aumentada (maj7#5) e tem um som flutuante e etéreo, típico da música impressionista. É uma das sonoridades mais bonitas dos modos da melódica."),
        b ("Fórmula: 1 2 3 #4 #5 6 7."),
        b ("Som: flutuante, etéreo, com quinta aumentada."),
        b ("Uso: sobre acordes maj7(#5)."),
        aud ({ "E4", "F#4", "G#4", "A#4", "C5", "C#5", "D#5", "E5" },
             "Lídio aumentado a partir de Mi: som etéreo, com a quinta aumentada."),

        h ("Modo 4 — lídio dominante (1 2 3 #4 5 6 b7)"),
        p (
            "O quarto modo é o lídio dominante, uma das escalas mais usadas sobre acordes de dominante no jazz. Ele tem a terça maior (som de dominante) e a quarta aumentada (#4, que dá o \"trítono\" característico). O seu som é brilhante, tenso e resolvido ao mesmo tempo, e cai perfeitamente sobre acordes V7, especialmente os que resolvem por quinta abaixo."),
        b ("Fórmula: 1 2 3 #4 5 6 b7."),
        b ("Som: brilhante, moderno, com #4 (o trítono do dominante)."),
        b ("Uso: sobre acordes V7 que resolvem por quinta abaixo."),
        aud ({ "F4", "G4", "A4", "B4", "C5", "D5", "Eb5", "F5" },
             "Lídio dominante a partir de Fá: o som clássico sobre o V7."),

        h ("Modo 5 — mixolídio com sexta menor (1 2 3 4 5 b6 b7)"),
        p (
            "O quinto modo é um mixolídio com a sexta abaixada (b6). Ele é usado sobre acordes de dominante com nona e décima terceira alteradas (7(b13)), e a b6 dá um toque melancólico ao som do dominante. É comum em cadências menores, quando o dominante resolve num acorde menor."),
        b ("Fórmula: 1 2 3 4 5 b6 b7."),
        b ("Som: dominante com cor menor."),
        b ("Uso: sobre acordes V7(b13) que resolvem em acordes menores."),

        h ("Modo 6 — lócrio com segunda natural (1 2 b3 4 b5 b6 b7)"),
        p (
            "O sexto modo é um lócrio com a segunda natural (2). Ele é usado sobre acordes meio-diminutos (m7(b5)) e tem um som instável, mas menos tenso que o lócrio comum, por causa da segunda natural. É uma escala importante para quem improvisa sobre o ii do campo menor."),
        b ("Fórmula: 1 2 b3 4 b5 b6 b7."),
        b ("Som: meio-diminuto com um toque de cor."),
        b ("Uso: sobre acordes m7(b5)."),
        aud ({ "B3", "C#4", "D4", "E4", "F4", "G4", "A4", "B4" },
             "Lócrio com segunda natural a partir de Si: som meio-diminuto."),

        h ("Modo 7 — escala alterada (1 b2 b3 b4 b5 b6 b7)"),
        p (
            "O sétimo modo é a escala alterada, também chamada de super-lócrio ou escala diminuta do dominante. Ele tem praticamente todas as notas alteradas e cria o máximo de tensão. É a escala mais usada sobre o dominante alterado no jazz, quando se quer o som mais tenso possível antes da resolução na tônica."),
        b ("Fórmula: 1 b2 b3 b4 b5 b6 b7."),
        b ("Som: máxima tensão, dominante alterado."),
        b ("Uso: sobre o V7 alterado (7alt) no jazz."),
        aud ({ "G3", "G#3", "A#3", "B3", "C#4", "D#4", "F4", "G4" },
             "Escala alterada a partir de Sol: a sonoridade mais tensa do dominante."),

        h ("Como usar os modos na prática"),
        p (
            "Como sempre, você escolhe o modo pelo acorde que está soando. O quarto modo (lídio dominante) e o sétimo (alterada) são os mais usados sobre dominantes; o primeiro (menor melódica) sobre acordes menores; o sexto sobre meio-diminutos. Os outros completam o mapa para situações específicas."),
        tbl ({ "Acorde", "Modo da menor melódica", "Cor" }, {
            { "m7M (i)", "modo 1 — menor melódica", "suave" },
            { "m7sus4", "modo 2 — dórico b2", "tenso" },
            { "maj7(#5)", "modo 3 — lídio aumentado", "etéreo" },
            { "7 (V7)", "modo 4 — lídio dominante", "brilhante" },
            { "7(b13)", "modo 5 — mixolídio b6", "melancólico" },
            { "m7(b5)", "modo 6 — lócrio 2 natural", "instável" },
            { "7alt", "modo 7 — escala alterada", "tensa" },
        }),
        c (
            "Nos exercícios deste tópico, você reconhece os modos pelo som e toca as suas fórmulas no instrumento. O app confere as notas que você toca."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é confundir os modos da menor melódica com os da menor harmônica: eles têm fórmulas parecidas, mas partem de escalas diferentes. Outro erro é usar o lídio dominante sobre qualquer acorde — ele pede um dominante que resolva por quinta abaixo. Escolha sempre o modo pelo acorde."),
        b ("Não confunda modos da melódica com modos da harmônica."),
        b ("O lídio dominante pede um V7 que resolve por quinta abaixo."),
        b ("Ouça o modo antes de tocar, para fixar o caráter."),

        h ("A tabela completa dos modos"),
        p (
            "A tabela abaixo reúne os sete modos da menor melódica com as suas fórmulas e os acordes com que combinam. É a referência que você consulta enquanto não memorizou os sete. Repare que o primeiro é a própria escala e que os outros seis alteram a fórmula de forma sistemática, à medida que o ponto de partida sobe na escala."),
        tbl ({ "Modo", "Fórmula", "Tônica (em Lá menor melódica)", "Acorde" }, {
            { "1 — menor melódica", "1 2 b3 4 5 6 7", "A", "m7M" },
            { "2 — dórico b2", "1 b2 b3 4 5 6 b7", "B", "m7sus4" },
            { "3 — lídio aumentado", "1 2 3 #4 #5 6 7", "C", "maj7(#5)" },
            { "4 — lídio dominante", "1 2 3 #4 5 6 b7", "D", "7" },
            { "5 — mixolídio b6", "1 2 3 4 5 b6 b7", "E", "7(b13)" },
            { "6 — lócrio 2 natural", "1 2 b3 4 b5 b6 b7", "F#", "m7(b5)" },
            { "7 — escala alterada", "1 b2 b3 b4 b5 b6 b7", "G#", "7alt" },
        }),
        c (
            "Note que cada modo tem a tônica num grau da escala: A, B, C, D, E, F#, G#. São as sete notas da escala de Lá menor melódica, cada uma virando a tônica de um modo."),

        h ("Por que os modos da melódica são tão usados"),
        p (
            "Os modos da menor melódica são tão usados porque cobrem todos os tipos de acorde do jazz. Sobre acordes menores, o modo 1 (m7M) e o modo 6 (m7(b5)). Sobre acordes maiores, o modo 3 (maj7#5). Sobre acordes de dominante, o modo 4 (lídio dominante), o modo 5 (7b13) e o modo 7 (alterado). Com essa família, você improvisa sobre praticamente qualquer acorde."),
        b ("Menores: modo 1 (m7M) e modo 6 (m7(b5))."),
        b ("Maiores: modo 3 (maj7#5)."),
        b ("Dominantes: modos 4, 5 e 7 (do lídio dominante ao alterado)."),
        c (
            "Esta é a razão pela qual a menor melódica é uma das escalas mais estudadas no jazz: ela não é uma escala só, é um conjunto de sonoridades que cobre a harmonia inteira."),

        h ("Como praticar os modos da menor melódica"),
        p (
            "Pratique os modos de duas formas, como sempre. Primeiro, toque todos a partir da mesma tônica (Lá menor melódica, Lá dórico b2, Lá lídio aumentado…) para ouvir a diferença de clima com a mesma nota de partida. Depois, toque todos a partir das notas da escala de Lá menor melódica (Lá, Si, Dó, Ré, Mi, Fá#, Sol#), para sentir que são a mesma escala vista de pontos diferentes."),
        b ("Mesma tônica: fixa a diferença de clima entre os modos."),
        b ("Mesma escala: mostra que os modos são uma família."),
        b ("Toque cada modo sobre o acorde correspondente, para ouvir o uso real."),
        c (
            "Nos exercícios deste tópico, toque as fórmulas dos modos no instrumento. O app reconhece as notas e confere se elas formam o modo pedido, em qualquer posição do braço."),

        h ("Erros comuns ao estudar os modos da melódica"),
        p (
            "O erro mais comum é confundir os modos da menor melódica com os da menor harmônica: eles têm fórmulas parecidas, mas partem de escalas diferentes e soam diferente. Outro erro é usar o lídio dominante sobre qualquer acorde — ele pede um dominante que resolva por quinta abaixo. E há quem decore as fórmulas sem ouvir o som, o que torna o estudo mecânico e sem música."),
        b ("Não confunda os modos da melódica com os da harmônica."),
        b ("O lídio dominante pede um V7 que resolve por quinta abaixo."),
        b ("Ouça o modo antes de decorar a fórmula."),
        c (
            "O app ajuda: ele reconhece as notas que você toca e verifica se elas formam o modo pedido. Assim você confere a fórmula antes de levar o modo para a música."),

        h ("Resumo do tópico"),
        b ("Modo é a escala vista de outro ponto de partida."),
        b ("A menor melódica gera sete modos, um por grau."),
        b ("O 4º (lídio dominante) e o 7º (alterada) são os mais usados no jazz."),
        b ("Cada modo combina com um tipo de acorde."),
        b ("Escolha o modo pelo acorde, não pela fórmula decorada."),
        b ("Cada modo tem a sua tônica num grau da escala — A, B, C, D, E, F#, G#."),
        b ("Os modos 4 e 7 são as escalas de dominante mais usadas no jazz moderno."),
    };
}

} // namespace cursomusica::content
