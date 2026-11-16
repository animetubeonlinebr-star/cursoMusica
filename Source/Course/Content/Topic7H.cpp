#include "Course/Content/Topics.h"

// Topic 7H — Mixolídio sus e Mixolídio #4 (Módulo 7, Etapa 7).
// Fonte de verdade do texto: docs/MUSIC.md §7.2 (bloco H).
namespace cursomusica::content
{

std::vector<ContentItem> topic7H()
{
    return {

        p (
            "O mixolídio que você viu no tópico anterior é o dominante “natural”. Neste tópico você conhece duas variações muito usadas: o mixolídio sus (sem a terça, com a quarta) e o mixolídio #4 (com a quarta aumentada). Cada uma é uma ferramenta de cor e tensão que aparece constantemente em jazz, bossa, rock e pop."),
        p (
            "Essas variações mostram um princípio importante da harmonia modal: um mesmo acorde pode ser “vestido” com escalas ligeiramente diferentes, e cada diferença muda radicalmente a cor. Aprender a escolher entre o mixolídio natural e as suas variações é o que dá sofisticação à sua harmonia e à sua improvisação."),

        h ("Mixolídio sus"),
        p (
            "O mixolídio sus é a escala que combina com acordes suspensos de dominante (X7sus4). A diferença em relação ao mixolídio natural é que a terça é substituída pela quarta: em vez de 1 2 3 4 5 6 b7, você tem 1 2 4 5 6 b7. Sem a terça, o acorde não é nem maior nem menor — ele fica suspenso."),
        tbl ({ "Grau", "Nota em Dó sus", "Intervalo a partir da tônica" }, {
            { "1", "Dó", "uníssono" },
            { "2", "Ré", "segunda maior" },
            { "4", "Fá", "quarta justa" },
            { "5", "Sol", "quinta justa" },
            { "6", "Lá", "sexta maior" },
            { "b7", "Sib", "sétima menor" },
        }),
        b ("Fórmula: 1 2 4 5 6 b7 (sem a terça)."),
        b ("Acorde típico: X7sus4."),
        b ("Som suspenso, sem resolução imediata."),
        aud ({ "C4", "F4", "G4", "A#4" }, "Acorde sus de Dó (C7sus4): quarta no lugar da terça, som suspenso."),
        aud ({ "C4", "D4", "F4", "G4", "A4", "A#4", "C5" }, "Escala mixolídia sus em Dó: sem a terça, suspensa."),
        c (
            "O acorde sus aparece muito em música pop, gospel e bossa, porque o som suspenso cria expectativa sem definir maior ou menor. O mixolídio sus é a escala que combina com esse acorde."),

        h ("Mixolídio #4 (lídio dominante)"),
        p (
            "O mixolídio #4 — também chamado de lídio dominante — é o mixolídio com a quarta aumentada. A fórmula é 1 2 3 #4 5 6 b7. Ele combina com acordes dominantes que têm a #11, e o som é ao mesmo tempo tenso (pela b7) e brilhante (pela #4). É uma cor muito usada no jazz moderno e na música instrumental."),
        tbl ({ "Grau", "Nota em Dó #4", "Intervalo a partir da tônica" }, {
            { "1", "Dó", "uníssono" },
            { "2", "Ré", "segunda maior" },
            { "3", "Mi", "terça maior" },
            { "#4", "Fá#", "quarta aumentada" },
            { "5", "Sol", "quinta justa" },
            { "6", "Lá", "sexta maior" },
            { "b7", "Sib", "sétima menor" },
        }),
        b ("Fórmula: 1 2 3 #4 5 6 b7."),
        b ("Acorde típico: X7#11."),
        b ("Som tenso e brilhante ao mesmo tempo."),
        aud ({ "C4", "E4", "F#4", "G4", "A#4" }, "Acorde de Dó com #11 (C7#11): a cor do lídio dominante."),
        aud ({ "C4", "D4", "E4", "F#4", "G4", "A4", "A#4", "C5" }, "Escala mixolídia #4 em Dó: dominante com a quarta aumentada."),
        img ("m7_modos_sus_alt", "Mixolídio sus e mixolídio #4: duas variações do dominante, duas cores."),

        h ("Comparando as três variações do mixolídio"),
        p (
            "Comparar o mixolídio natural, o sus e o #4 é a melhor forma de entender as diferenças. Todos partem do mesmo esqueleto (1 2 5 6 b7), e o que muda é a terça/quarta. Essa comparação mostra como uma única nota pode mudar completamente a cor do acorde."),
        tbl ({ "Modo", "Fórmula", "Nota que muda", "Acorde" }, {
            { "mixolídio", "1 2 3 4 5 6 b7", "terça (3)", "X7" },
            { "mixolídio sus", "1 2 4 5 6 b7", "terça → quarta (4)", "X7sus4" },
            { "mixolídio #4", "1 2 3 #4 5 6 b7", "quarta → #4", "X7#11" },
        }),
        aud ({ "C4", "E4", "G4", "A#4" }, "C7: mixolídio natural, com a terça."),
        aud ({ "C4", "F4", "G4", "A#4" }, "C7sus4: mixolídio sus, com a quarta no lugar da terça."),
        aud ({ "C4", "E4", "F#4", "A#4" }, "C7#11: mixolídio #4, com a quarta aumentada."),

        h ("Aplicações do mixolídio sus"),
        p (
            "O mixolídio sus aparece em vamps de dominante suspensa, em passagens de gospel e soul, e em bossa. Ele é ótimo quando você quer um som de dominante que não pede resolução imediata, criando uma sensação de suspensão. Toque um X7sus4 e improvise com o mixolídio sus para sentir a cor."),
        b ("Vamps de dominante suspensa."),
        b ("Passagens de gospel e soul."),
        b ("Bossa e música brasileira moderna."),
        img ("m7_modos_sus_alt", "O acorde sus no braço: sem a terça, o som fica suspenso e aberto."),

        h ("Aplicações do mixolídio #4"),
        p (
            "O mixolídio #4 (lídio dominante) aparece em acordes dominantes com #11, muito comuns em jazz moderno, música instrumental e trilhas. Ele dá uma cor sofisticada, com tensão controlada. Também aparece em trechos de música brasileira instrumental."),
        b ("Acordes dominantes com #11."),
        b ("Jazz moderno e música instrumental."),
        b ("Trilhas e música contemporânea."),

        h ("Como escolher entre as variações"),
        p (
            "A escolha depende do acorde e da intenção. Se o acorde tem a quarta suspensa (sus4), use o mixolídio sus. Se o acorde tem a #11, use o mixolídio #4. Se o acorde é um dominante simples, use o mixolídio natural. Ouvir o acorde e identificar a tensão presente é o que guia a escolha."),
        tbl ({ "O acorde tem...", "Use o modo..." }, {
            { "terça e quarta justa", "mixolídio natural" },
            { "quarta, sem terça (sus4)", "mixolídio sus" },
            { "terça e #11", "mixolídio #4 (lídio dominante)" },
            { "terça e b13/#5", "alterado (próximo tópico)" },
        }),
        c (
            "Nos exercícios deste tópico, você toca os acordes sus e com #11 e o app reconhece as notas. Você também responderá a questionários sobre as variações do mixolídio."),

        h ("Do sus ao dominante alterado"),
        p (
            "As variações do mixolídio formam uma ponte para o próximo tópico. Enquanto o sus e o #4 mantêm a estrutura do dominante com uma alteração, o dominante alterado leva a tensão ao máximo, alterando a quinta e a nona. Entender as variações prepara você para o alterado."),
        b ("Sus: quarta no lugar da terça."),
        b ("#4: quarta aumentada."),
        b ("Alterado: quinta e nona alteradas (tensão máxima)."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é tocar a terça sobre um acorde sus (o que “desfaz” a suspensão) ou esquecer a #4 sobre o acorde #11. Outro é usar o mixolídio sus onde o acorde tem terça, criando atrito. Ouvir o acorde e identificar a tensão presente evita esses erros."),
        b ("Não toque a terça sobre um acorde sus4."),
        b ("Não esqueça a #4 sobre o acorde #11."),
        b ("Confira a tensão do acorde antes de escolher o modo."),

        h ("O acorde sus: origem e uso"),
        p (
            "O acorde suspenso (sus) surgiu da ideia de adiar a resolução: em vez de tocar a terça, que define maior ou menor, você toca a quarta (ou a segunda) e deixa a questão em aberto. O som suspenso cria expectativa e é muito usado em pop, gospel, bossa e música instrumental. Quando a terça finalmente aparece, o ouvido sente o alívio da definição."),
        b ("sus4: a quarta no lugar da terça."),
        b ("sus2: a segunda no lugar da terça."),
        b ("O sus cria expectativa; a terça resolve."),
        aud ({ "C4", "F4", "G4" }, "Tríade sus de Dó (Csus4): sem terça, som suspenso."),
        aud ({ "C4", "E4", "G4" }, "A mesma tríade com a terça (Dó maior): o som se define."),

        h ("Lídio dominante: contexto de uso"),
        p (
            "O lídio dominante (mixolídio #4) é muito usado em jazz moderno e em música instrumental, especialmente sobre acordes dominantes que funcionam como IV grau ou em passagens que buscam uma cor sofisticada. A combinação de tensão (b7) e brilho (#4) faz dele um dos modos mais expressivos do sistema."),
        b ("Jazz moderno e música instrumental."),
        b ("Acordes dominantes com #11."),
        b ("Passagens de cor sofisticada."),

        h ("Do sus ao dominante alterado: uma escala de tensão"),
        p (
            "As variações do mixolídio formam uma escala de tensão crescente. O mixolídio natural é o menos tenso; o sus e o #4 acrescentam uma cor; o alterado leva a tensão ao máximo, alterando a quinta e a nona. Conhecer essa escala ajuda a escolher o modo conforme a tensão que a música pede."),
        tbl ({ "Modo", "Tensão", "Uso" }, {
            { "mixolídio", "baixa", "dominante natural" },
            { "mixolídio sus", "média", "acorde suspenso" },
            { "mixolídio #4", "média-alta", "acorde com #11" },
            { "alterado", "máxima", "dominante alterado" },
        }),

        h ("Tocando os acordes sus e #11 na guitarra"),
        p (
            "Na guitarra, o acorde sus é fácil de tocar: basta mover a terça uma casa acima (para a quarta). O acorde com #11 é igualmente acessível: você altera a quinta ou acrescenta a #11 nas cordas agudas. Esses desenhos aparecem em muitas músicas, e reconhecê-los é o que permite usá-los no contexto certo."),
        b ("sus4: mova a terça uma casa acima."),
        b ("#11: acrescente a nota uma casa acima da quarta."),
        b ("Ouça a cor antes de fixar o voicing."),
        img ("m7_modos_sus_alt", "Os acordes sus e com #11 no braço: alterações simples, cores novas."),

        h ("Aplicando as variações no repertório"),
        p (
            "No repertório, as variações do mixolídio aparecem em momentos de cor e tensão. Uma introdução pode usar um acorde sus para criar expectativa; uma passagem instrumental pode usar o lídio dominante para dar brilho; uma cadência pode usar o alterado para criar tensão máxima antes da resolução. Reconhecer esses momentos é o que faz o músico escolher a cor certa."),
        b ("Introdução: acorde sus cria expectativa."),
        b ("Passagem instrumental: #11 dá brilho."),
        b ("Cadência: alterado cria tensão máxima."),

        h ("Comparando o sus e o #4 no braço"),
        p (
            "No braço, a diferença entre o acorde sus e o acorde com #11 é pequena: ambos alteram uma única nota em relação ao dominante natural. O sus move a terça uma casa acima (para a quarta); o #11 acrescenta a nota uma casa acima da quarta. Praticar os dois desenhos lado a lado ajuda a ouvir e a fixar cada cor."),
        b ("Dominante natural: tônica, terça, quinta e sétima menor."),
        b ("Sus: tônica, quarta, quinta e sétima menor."),
        b ("#11: dominante natural mais a quarta aumentada."),

        h ("Do sus ao #4: a escolha da cor"),
        p (
            "Escolher entre o sus e o #4 é escolher a cor do dominante. O sus deixa o acorde em aberto, sem maior nem menor, criando expectativa; o #4 mantém a terça e acrescenta o brilho da quarta aumentada. Ouvir o acorde e identificar a tensão presente é o que guia a escolha, e essa escuta consciente é o que dá sofisticação à harmonia."),
        b ("Sus: acorde em aberto, expectativa."),
        b ("#4: acorde com terça e brilho da #11."),
        b ("Escolha pela tensão que o acorde já apresenta."),

        h ("Praticando as duas cores"),
        p (
            "Pratique as duas cores lado a lado, sobre o mesmo centro. Toque um vamp com o acorde sus e, em seguida, o mesmo vamp com o acorde #11. Ouça como a terça muda tudo: o sus fica em aberto, o #4 fica tenso e brilhante. Esse exercício de comparação é o que fixa cada cor no ouvido e na mão."),
        b ("Um vamp com sus, outro com #11."),
        b ("Compare a presença ou ausência da terça."),
        b ("Fixe cada cor de ouvido e na mão."),
        img ("m7_modos_sus_alt", "Comparando o sus e o #4: uma nota muda a cor do acorde."),

        h ("Resumo do tópico"),
        b ("Mixolídio sus: 1 2 4 5 6 b7 (sem a terça), combina com X7sus4."),
        b ("Mixolídio #4: 1 2 3 #4 5 6 b7, combina com X7#11."),
        b ("As duas são variações do dominante, com cores diferentes."),
        b ("A escolha depende da tensão presente no acorde."),
        b ("Elas preparam o estudo do dominante alterado."),
        part ("m7_partitura_sus", { "C4", "F4", "G4", "A#4" },
              "Partitura: acorde sus de Dó (C7sus4). Ouça o som suspenso, sem a terça."),
    };
}

} // namespace cursomusica::content
