#include "Course/Content/Topics.h"

// Topic 6C — Modos da menor harmônica (Módulo 6, Etapa 6).
// Fonte de verdade do texto: docs/MUSIC.md §6.2 (bloco C).
namespace cursomusica::content
{

std::vector<ContentItem> topic6C()
{
    return {

        p (
            "Toda escala gera modos: se você começar a escala por um grau diferente, mantendo as mesmas notas, obtém uma sonoridade nova, com outro centro e outra cor. Isso vale para a escala menor harmônica. Os seus sete modos são muito usados no jazz, na música árabe, no flamenco e no metal, e cada um tem um caráter próprio."),
        p (
            "Este tópico apresenta os sete modos da menor harmônica, um por um, com a sua fórmula de graus e a sua sonoridade. Você não precisa decorar os sete de uma vez: comece pelo primeiro (a própria menor harmônica) e pelo quinto (o frígio dominante), que são os mais usados, e vá acrescentando os outros."),
        c (
            "Ideia central: um modo é a mesma escala vista de outro ponto de partida. As notas não mudam; o que muda é onde a melodia repousa e, portanto, o clima que se ouve."),

        h ("O que é um modo"),
        p (
            "Modo é uma escala obtida começando por outro grau de uma escala já existente. Como as notas são as mesmas, o conjunto de intervalos a partir da nova tônica muda, e com ele muda o som. A escala de Lá menor harmônica gera sete modos, um para cada grau."),
        b ("Modo 1: começa no 1º grau — é a própria menor harmônica."),
        b ("Modo 2: começa no 2º grau — notas da escala, tônica em Si."),
        b ("E assim por diante, até o modo 7, começando no 7º grau."),
        img ("m6_modos_harmonica", "Os sete modos da escala menor harmônica, com a fórmula de graus de cada um."),

        h ("Modo 1 — menor harmônica (1 2 b3 4 5 b6 7)"),
        p (
            "O primeiro modo é a própria escala menor harmônica. Ele soa dramático e exótico, com a sensível criando tensão e o intervalo de segunda aumentada dando o caráter. É usado sobre o acorde menor com sétima maior (m7M) e em passagens de tonalidade menor."),
        b ("Fórmula: 1 2 b3 4 5 b6 7."),
        b ("Som: dramático, com sensível e segunda aumentada."),
        b ("Uso: sobre o i (m7M) e em passagens menores."),
        aud ({ "A3", "B3", "C4", "D4", "E4", "F4", "G#4", "A4" }, "Modo 1: a própria escala menor harmônica."),

        h ("Modo 2 — lócrio com sexta natural (1 b2 b3 4 b5 6 b7)"),
        p (
            "O segundo modo começa no segundo grau. Ele tem a quinta diminuta (b5) do modo lócrio, mas com a sexta natural (6), o que o diferencia do lócrio comum. É usado sobre acordes meio-diminutos e tem um som instável, que pede resolução."),
        b ("Fórmula: 1 b2 b3 4 b5 6 b7."),
        b ("Som: instável, meio-diminuto com um toque de cor."),
        b ("Uso: sobre acordes m7(b5)."),

        h ("Modo 3 — jônio com quinta aumentada (1 2 3 4 #5 6 7)"),
        p (
            "O terceiro modo soa como uma escala maior com a quinta aumentada. Ele é usado sobre acordes maiores com quinta aumentada (maj7#5) e tem um som flutuante, suspenso, que não repousa. É uma sonoridade típica de música impressionista e de jazz moderno."),
        b ("Fórmula: 1 2 3 4 #5 6 7."),
        b ("Som: flutuante, suspenso, com quinta aumentada."),
        b ("Uso: sobre acordes maj7(#5)."),

        h ("Modo 4 — dórico com quarta aumentada (1 2 b3 #4 5 6 b7)"),
        p (
            "O quarto modo é um dórico com a quarta aumentada (#4). Ele é usado sobre acordes menores com sétima, e a quarta aumentada dá um toque de tensão e de cor moderna. É comum no jazz, sobre o acorde de segundo grau de uma cadência menor."),
        b ("Fórmula: 1 2 b3 #4 5 6 b7."),
        b ("Som: dórico com um toque de tensão."),
        b ("Uso: sobre acordes m7, especialmente o ii do campo menor."),

        h ("Modo 5 — frígio dominante (1 b2 3 4 5 b6 b7)"),
        p (
            "O quinto modo é o mais famoso: o frígio dominante. Ele combina a terça maior (3) com a segunda menor (b2) e a sexta menor (b6), criando o som do flamenco, da música árabe e do dominante alterado do jazz. É usado sobre o acorde V7 de uma tonalidade menor, e a sua b2 dá a tensão que resolve na tônica."),
        b ("Fórmula: 1 b2 3 4 5 b6 b7."),
        b ("Som: flamenco, árabe, tenso — o mais reconhecível dos modos."),
        b ("Uso: sobre o V7 de uma tonalidade menor (E7 em Lá menor)."),
        aud ({ "E4", "F4", "G#4", "A4", "B4", "C5", "D5", "E5" },
             "Frígio dominante a partir de Mi: o som do flamenco e do V7(b9)."),

        h ("Modo 6 — lídio com segunda aumentada (1 #2 3 #4 5 6 7)"),
        p (
            "O sexto modo tem a segunda aumentada (#2) e a quarta aumentada (#4). Ele é muito tenso e é usado em passagens de jazz moderno e de música contemporânea. Não é um modo do dia a dia, mas conhecer a sua fórmula completa o mapa das sonoridades da menor harmônica."),
        b ("Fórmula: 1 #2 3 #4 5 6 7."),
        b ("Som: tenso, com duas notas alteradas."),
        b ("Uso: passagens de jazz moderno e música contemporânea."),

        h ("Modo 7 — superlócrio com sétima diminuta (1 b2 b3 b4 b5 b6 bb7)"),
        p (
            "O sétimo modo é o superlócrio, também chamado de escala alterada. Ele tem praticamente todas as notas alteradas e cria o máximo de tensão. É usado sobre o acorde de dominante alterado no jazz, quando se quer o som mais tenso possível antes da resolução."),
        b ("Fórmula: 1 b2 b3 b4 b5 b6 bb7."),
        b ("Som: máxima tensão, escala alterada."),
        b ("Uso: sobre o V7 alterado no jazz."),
        c (
            "Note que o superlócrio da menor harmônica é diferente da escala alterada derivada da menor melódica (tópico E). Ambos existem e têm fórmulas parecidas, mas partem de escalas diferentes."),

        h ("Como usar os modos na prática"),
        p (
            "Na prática, você não pensa nos sete modos de uma vez. Você olha para o acorde que está soando e escolhe o modo que combina com ele. O frígio dominante (modo 5) é o mais usado; o modo 1 e o modo 4 vêm em seguida. Os outros aparecem em situações específicas."),
        tbl ({ "Acorde", "Modo da menor harmônica", "Cor" }, {
            { "m7M (i)", "modo 1 — menor harmônica", "dramática" },
            { "m7(b5) (ii)", "modo 2 — lócrio 6 natural", "instável" },
            { "maj7(#5) (III+)", "modo 3 — jônio #5", "flutuante" },
            { "m7 (iv)", "modo 4 — dórico #4", "moderna" },
            { "7(b9) (V7)", "modo 5 — frígio dominante", "flamenca" },
            { "7alt", "modo 7 — superlócrio", "tensa" },
        }),
        c (
            "Nos exercícios deste tópico, você reconhece os modos pelo som e toca as suas fórmulas no instrumento. O app confere as notas que você toca."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é confundir os modos da menor harmônica com os da menor melódica: eles têm fórmulas parecidas, mas partem de escalas diferentes e soam diferente. Outro erro é tocar um modo sem levar em conta o acorde que está soando — o modo só faz sentido sobre o acorde certo."),
        b ("Não confunda modos da menor harmônica com os da menor melódica."),
        b ("Escolha o modo pelo acorde que está soando."),
        b ("Ouça o modo antes de tocar, para fixar o caráter."),

        h ("A tabela completa dos modos"),
        p (
            "A tabela abaixo reúne os sete modos da menor harmônica com as suas fórmulas. É a referência que você consulta enquanto não memorizou os sete. Repare que o primeiro é a própria escala e que os outros seis alteram a fórmula de forma sistemática, à medida que o ponto de partida sobe na escala."),
        tbl ({ "Modo", "Fórmula", "Tônica (em Lá menor harmônica)", "Acorde" }, {
            { "1 — menor harmônica", "1 2 b3 4 5 b6 7", "A", "m7M" },
            { "2 — lócrio 6 natural", "1 b2 b3 4 b5 6 b7", "B", "m7(b5)" },
            { "3 — jônio #5", "1 2 3 4 #5 6 7", "C", "maj7(#5)" },
            { "4 — dórico #4", "1 2 b3 #4 5 6 b7", "D", "m7" },
            { "5 — frígio dominante", "1 b2 3 4 5 b6 b7", "E", "7(b9)" },
            { "6 — lídio #2", "1 #2 3 #4 5 6 7", "F", "maj7(#5)" },
            { "7 — superlócrio", "1 b2 b3 b4 b5 b6 bb7", "G#", "dim7" },
        }),
        c (
            "Note que cada modo tem a tônica num grau da escala: A, B, C, D, E, F, G#. São as sete notas da escala de Lá menor harmônica, cada uma virando a tônica de um modo."),

        h ("Como praticar os modos da menor harmônica"),
        p (
            "Pratique os modos de duas formas, como no estudo dos modos gregos. Primeiro, toque todos a partir da mesma tônica (Lá menor harmônica, Lá lócrio 6 natural, Lá jônio #5…) para ouvir a diferença de clima com a mesma nota de partida. Depois, toque todos a partir das notas da escala de Lá menor harmônica (Lá, Si, Dó, Ré, Mi, Fá, Sol#), para sentir que são a mesma escala vista de pontos diferentes."),
        b ("Mesma tônica: fixa a diferença de clima entre os modos."),
        b ("Mesma escala: mostra que os modos são uma família."),
        b ("Toque cada modo sobre o acorde correspondente, para ouvir o uso real."),
        c (
            "Nos exercícios deste tópico, toque as fórmulas dos modos no instrumento. O app reconhece as notas e confere se elas formam o modo pedido, em qualquer posição do braço."),

        h ("Os modos da menor harmônica na música"),
        p (
            "O frígio dominante (modo 5) é a sonoridade mais reconhecível do grupo: ele está no flamenco, na música árabe e no heavy metal. No jazz, os modos da menor harmônica aparecem sobre o dominante alterado de uma cadência menor. Conhecer os sete completa o vocabulário de quem toca em tonalidades menores."),
        b ("Flamenco e música árabe: frígio dominante (modo 5)."),
        b ("Jazz: modos da menor harmônica sobre dominantes alterados."),
        b ("Metal neoclássico: passagens da menor harmônica e dos seus modos."),
        aud ({ "E4", "F4", "G#4", "A4", "B4", "C5", "D5", "E5" },
             "Frígio dominante: a sonoridade flamenca do modo 5."),

        h ("Erros comuns ao estudar os modos"),
        p (
            "O erro mais comum é tocar um modo sem respeitar o acorde de fundo: um modo só revela o seu caráter sobre o acorde certo. Outro erro é decorar as fórmulas sem ouvir o som — o modo vira um exercício mecânico e não musical. E há quem confunda os modos da menor harmônica com os da menor melódica, que têm fórmulas parecidas mas partem de escalas diferentes."),
        b ("Toque sempre sobre um acorde de fundo que combine com o modo."),
        b ("Ouça o modo antes de decorar a fórmula."),
        b ("Não confunda os modos da harmônica com os da melódica."),
        c (
            "O app ajuda: ele reconhece as notas que você toca e verifica se elas formam o modo pedido. Assim você confere se a fórmula está correta antes de levar o modo para a música."),

        h ("Resumo do tópico"),
        b ("Modo é a escala vista de outro ponto de partida."),
        b ("A menor harmônica gera sete modos, um por grau."),
        b ("O modo 5 (frígio dominante) é o mais usado; o 1 e o 4 vêm em seguida."),
        b ("Cada modo combina com um tipo de acorde e tem um caráter próprio."),
        b ("Escolha o modo pelo acorde, não pela fórmula decorada."),
        b ("Toque os modos com e sem acorde de fundo para ouvir o caráter."),
        b ("A família da menor harmônica completa o vocabulário das tonalidades menores."),
        b ("Cada modo tem a sua tônica num grau da escala — A, B, C, D, E, F, G#."),
        b ("O intervalo de segunda aumentada da escala original aparece também em alguns modos."),
    };
}

} // namespace cursomusica::content
