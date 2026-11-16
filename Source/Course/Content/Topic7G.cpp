#include "Course/Content/Topics.h"

// Topic 7G — Dórico, Lídio e Mixolídio (Módulo 7, Etapa 7).
// Fonte de verdade do texto: docs/MUSIC.md §7.2 (bloco G).
namespace cursomusica::content
{

std::vector<ContentItem> topic7G()
{
    return {

        p (
            "Dórico, lídio e mixolídio são os três modos mais usados da música moderna. Se você aprender esses três, já vai reconhecer a maior parte das sonoridades modais que ouve no jazz, na bossa, no rock e no pop. Cada um deles é a escala maior com uma pequena alteração, e essa alteração é o que define a cor do modo."),
        p (
            "Este tópico é o coração do módulo. Aqui você estuda os três modos em detalhe: as notas, a fórmula, as notas características, os acordes com que combinam e o som que produzem. Ao final, você vai saber escolher o modo pela cor que quer ouvir e reconhecê-lo de ouvido."),

        h ("A ideia central: a escala maior com uma alteração"),
        p (
            "Todos os modos gregos derivam da escala maior. O que muda é qual grau você trata como tônica e, portanto, quais alterações aparecem em relação à escala maior. Ver os modos como “a escala maior com uma nota alterada” é muito mais simples do que decorar sete escalas do zero."),
        tbl ({ "Modo", "Fórmula", "Comparação com a escala maior" }, {
            { "dórico", "1 2 b3 4 5 6 b7", "menor, com 6ª maior" },
            { "lídio", "1 2 3 #4 5 6 7", "maior, com 4ª aumentada" },
            { "mixolídio", "1 2 3 4 5 6 b7", "maior, com 7ª menor" },
        }),
        c (
            "Repare: o lídio e o mixolídio são maiores (têm a terça maior); o dórico é menor (tem a terça menor). A alteração característica é a que dá a cor: a 6ª maior no dórico, a #4 no lídio, a b7 no mixolídio."),

        h ("Dórico"),
        p (
            "O dórico é a escala menor com a sexta maior. Comparado ao menor natural (eólio), ele tem uma única nota diferente: a sexta. Essa sexta maior tira o “peso triste” do menor e dá um som mais aberto, otimista, muito usado no jazz e na música modal (pense em So What e em Cantaloupe Island)."),
        tbl ({ "Grau", "Nota em Dó dórico", "Intervalo a partir da tônica" }, {
            { "1", "Dó", "uníssono" },
            { "2", "Ré", "segunda maior" },
            { "b3", "Mib", "terça menor" },
            { "4", "Fá", "quarta justa" },
            { "5", "Sol", "quinta justa" },
            { "6", "Lá", "sexta maior" },
            { "b7", "Sib", "sétima menor" },
        }),
        b ("Fórmula: 1 2 b3 4 5 6 b7."),
        b ("Nota característica: a sexta maior (6)."),
        b ("Acorde típico: Xm7 ou Xm6 — combinam com o dórico."),
        aud ({ "C4", "D4", "D#4", "F4", "G4", "A4", "A#4", "C5" }, "Escala dórica em Dó: menor com sexta maior (Lá). Som aberto e modal."),
        img ("m7_modos_tres", "Dórico, lídio e mixolídio: a mesma escala maior vista de três graus diferentes."),

        h ("Lídio"),
        p (
            "O lídio é a escala maior com a quarta aumentada (#11). Comparado ao jônio, ele tem uma única nota diferente: a quarta. Essa #4 dá um brilho característico, um som “flutuante”, que é uma das cores mais bonitas da música modal. O lídio é o modo do IV grau da escala maior."),
        tbl ({ "Grau", "Nota em Dó lídio", "Intervalo a partir da tônica" }, {
            { "1", "Dó", "uníssono" },
            { "2", "Ré", "segunda maior" },
            { "3", "Mi", "terça maior" },
            { "#4", "Fá#", "quarta aumentada" },
            { "5", "Sol", "quinta justa" },
            { "6", "Lá", "sexta maior" },
            { "7", "Si", "sétima maior" },
        }),
        b ("Fórmula: 1 2 3 #4 5 6 7."),
        b ("Nota característica: a quarta aumentada (#4 / #11)."),
        b ("Acorde típico: Xmaj7 ou Xmaj7#11 — combinam com o lídio."),
        aud ({ "C4", "D4", "E4", "F#4", "G4", "A4", "B4", "C5" }, "Escala lídia em Dó: maior com quarta aumentada (Fá#). Som brilhante."),

        h ("Mixolídio"),
        p (
            "O mixolídio é a escala maior com a sétima menor. Comparado ao jônio, ele tem uma única nota diferente: a sétima. Essa b7 é o que dá o caráter de dominante ao modo, e é por isso que o mixolídio combina com acordes X7. É o modo do V grau da escala maior e aparece o tempo todo no blues, no rock e no jazz."),
        tbl ({ "Grau", "Nota em Dó mixolídio", "Intervalo a partir da tônica" }, {
            { "1", "Dó", "uníssono" },
            { "2", "Ré", "segunda maior" },
            { "3", "Mi", "terça maior" },
            { "4", "Fá", "quarta justa" },
            { "5", "Sol", "quinta justa" },
            { "6", "Lá", "sexta maior" },
            { "b7", "Sib", "sétima menor" },
        }),
        b ("Fórmula: 1 2 3 4 5 6 b7."),
        b ("Nota característica: a sétima menor (b7)."),
        b ("Acorde típico: X7 (dominante) ou X7sus4 — combinam com o mixolídio."),
        aud ({ "C4", "D4", "E4", "F4", "G4", "A4", "A#4", "C5" }, "Escala mixolídia em Dó: maior com sétima menor (Sib). Som de dominante."),

        h ("Comparando os três"),
        p (
            "A melhor forma de entender os três modos é compará-los lado a lado. Partindo de Dó, o dórico, o lídio e o mixolídio diferem do jônio em uma ou duas notas. Ouvir essas diferenças, uma por vez, é o que fixa a cor de cada modo no ouvido."),
        tbl ({ "Modo", "3ª", "Nota alterada", "Som" }, {
            { "dórico", "menor (b3)", "6 (maior)", "aberto, jazz" },
            { "lídio", "maior (3)", "#4 (aumentada)", "brilhante, flutuante" },
            { "mixolídio", "maior (3)", "b7 (menor)", "dominante, blues" },
        }),
        aud ({ "C4", "D#4", "G4", "A4" }, "Arpejo de Cm7 com a sexta (Lá): a cor do dórico."),
        aud ({ "C4", "E4", "F#4", "G4" }, "Acorde de Dó com a quarta aumentada (Fá#): a cor do lídio."),
        aud ({ "C4", "E4", "G4", "A#4" }, "Acorde de C7 (com Sib): a cor do mixolídio."),

        h ("Onde cada modo aparece"),
        p (
            "Cada modo tem aplicações típicas. O dórico aparece sobre acordes menores com função de II grau e em vamps modais menores. O lídio aparece sobre acordes maiores com #11 e em passagens brilhantes. O mixolídio aparece sobre acordes dominantes que não pedem resolução imediata, como os vamps de um acorde."),
        b ("Dórico: II grau (Dm7), vamps modais menores."),
        b ("Lídio: IV grau (Fmaj7), acordes com #11, passagens brilhantes."),
        b ("Mixolídio: V grau (G7), blues, rock, vamps de dominante."),

        h ("Praticando os três modos"),
        p (
            "Pratique cada modo sobre um vamp que combine com ele. Toque o dórico sobre um Dm7, o lídio sobre um Cmaj7#11 e o mixolídio sobre um C7. Ouça a cor e improvise frases curtas, sempre voltando às notas características. A repetição consciente é o que fixa a sonoridade."),
        b ("Um vamp por modo, um modo por sessão de estudo."),
        b ("Volte sempre à nota característica do modo."),
        b ("Improvise frases curtas e ouça a cor."),
        c (
            "Nos exercícios deste tópico, o app toca os modos para você ouvir e você toca acordes que o app reconhece. Toque em qualquer região do braço; o que importa é o conjunto de notas."),

        h ("Os três modos e as tríades do meio"),
        p (
            "Os três modos se conectam às tríades do meio. Sobre um vamp em Dm7 (dórico), a tríade de Dó maior dá a sétima, a nona e a décima primeira; a de Sol menor, a quinta, a sétima e a nona. Sobre um Cmaj7#11 (lídio), a tríade de Ré maior dá a nona, a #11 e a décima terceira. Essas estruturas são o que faz a improvisação soar “composta”."),
        b ("Dórico: tríades do meio a partir da tônica e da quinta."),
        b ("Lídio: tríades do meio a partir da segunda (dá a #11)."),
        b ("Mixolídio: tríades do meio a partir da tônica e da quinta."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é tocar o dórico como se fosse o menor natural (esquecendo a sexta maior), o lídio como jônio (esquecendo a #4) ou o mixolídio como jônio (esquecendo a b7). Outro é usar o modo errado para o acorde. Volte sempre à nota característica: é ela que define o modo."),
        b ("Dórico: cuidado para não tocar a sexta menor."),
        b ("Lídio: cuidado para não tocar a quarta justa."),
        b ("Mixolídio: cuidado para não tocar a sétima maior."),

        h ("Dórico: a nota característica e o seu efeito"),
        p (
            "A sexta maior é a nota que define o dórico. Sem ela, o modo seria o menor natural. Com ela, o som fica aberto, otimista, jazzístico. Ouvir essa nota dentro do contexto do acorde menor é o que permite reconhecer o dórico de ouvido. Toque um Dm7 e, em seguida, toque a sexta maior (Si, no caso de Dm) para sentir o efeito."),
        b ("A sexta maior é a nota característica do dórico."),
        b ("Ela transforma o menor natural em dórico."),
        b ("Reconheça o dórico ouvindo essa nota sobre o acorde menor."),

        h ("Lídio: a nota característica e o seu efeito"),
        p (
            "A quarta aumentada (#11) é a nota que define o lídio. Sem ela, o modo seria o jônio. Com ela, o som fica brilhante, flutuante. Tocar a #11 sobre um acorde maior cria uma tensão que, em vez de pedir resolução, permanece: é a assinatura do lídio. Experimente com um Cmaj7 e a nota Fá#."),
        b ("A #11 é a nota característica do lídio."),
        b ("Ela transforma o jônio em lídio."),
        b ("Reconheça o lídio ouvindo essa nota sobre o acorde maior."),

        h ("Mixolídio: a nota característica e o seu efeito"),
        p (
            "A sétima menor (b7) é a nota que define o mixolídio. Sem ela, o modo seria o jônio. Com ela, o som fica de dominante, bluesy. Tocar a b7 sobre um acorde maior cria a tensão característica do dominante. Experimente com um C7 e a nota Sib."),
        b ("A b7 é a nota característica do mixolídio."),
        b ("Ela transforma o jônio em mixolídio."),
        b ("Reconheça o mixolídio ouvindo essa nota sobre o acorde maior."),

        h ("Comparando os três modos de ouvido"),
        p (
            "A melhor forma de distinguir os três modos é ouvi-los em sequência, sobre o mesmo centro. Toque um vamp em Dó e improvise, primeiro com o dórico, depois com o mixolídio e, por fim, com o lídio. A diferença de cor fica evidente: o dórico é menor e aberto; o mixolídio é maior e de dominante; o lídio é maior e brilhante."),
        b ("Dórico: menor, aberto, sexta maior."),
        b ("Mixolídio: maior, de dominante, sétima menor."),
        b ("Lídio: maior, brilhante, quarta aumentada."),

        h ("Modos e as notas de repouso"),
        p (
            "Cada modo tem notas de repouso: as notas que soam estáveis sobre o acorde. No dórico, a terça menor e a sexta maior; no lídio, a terça maior e a #11; no mixolídio, a terça maior e a sétima menor. Conhecer as notas de repouso é o que permite improvisar com intenção, sabendo onde descansar a frase."),
        b ("Dórico: repouso na b3 e na 6."),
        b ("Lídio: repouso na 3 e na #4."),
        b ("Mixolídio: repouso na 3 e na b7."),

        h ("Erros comuns ao tocar os três modos"),
        p (
            "Além de esquecer a nota característica, um erro comum é tocar o modo sem afirmar o centro, o que faz o ouvido perder a referência. Outro é tocar as notas do modo na ordem, como um exercício, sem fazer música. A improvisação deve usar as notas do modo para criar frases, não apenas para mostrar que você sabe a escala."),
        b ("Afirme o centro antes de tocar o modo."),
        b ("Use as notas para fazer frases, não exercícios."),
        b ("Volte sempre às notas características e de repouso."),

        h ("Do estudo à música"),
        p (
            "Estudar os três modos é, antes de tudo, treinar o ouvido. Toque cada modo sobre o seu acorde, devagar, ouvindo a nota característica. Depois, improvise frases curtas e volte sempre a essa nota. A repetição consciente é o que faz o ouvido reconhecer a cor antes de a mão tocar, e é aí que a teoria vira música."),
        b ("Toque cada modo sobre o seu acorde."),
        b ("Volte sempre à nota característica."),
        b ("Improvise frases curtas e ouça a cor."),

        h ("Resumo do tópico"),
        b ("Dórico: menor com sexta maior (1 2 b3 4 5 6 b7)."),
        b ("Lídio: maior com quarta aumentada (1 2 3 #4 5 6 7)."),
        b ("Mixolídio: maior com sétima menor (1 2 3 4 5 6 b7)."),
        b ("Cada modo combina com uma família de acordes."),
        b ("A nota característica é o que define o modo."),
        part ("m7_partitura_dorico", { "C4", "D4", "D#4", "F4", "G4", "A4", "A#4", "C5" },
              "Partitura: escala dórica em Dó. Ouça a sexta maior (Lá), a nota que dá a cor do modo."),
    };
}

} // namespace cursomusica::content
