#include "Course/Content/Topics.h"

// Topic 11D — Pentatônica menor 6 (Módulo 11, Etapa 11).
// Fonte primária: "Improvisação Pop" (Mozart Mello), que usa os nomes "Gm7 blues"
// e "Gm6 blues" para a pentatônica menor aplicada sobre o acorde m7 e sobre o
// acorde m6. A pentatônica menor 6 é a pentatônica menor com a sexta maior no
// lugar da sétima menor: 1-b3-4-5-6 (cinco notas). Em Lá: A-C-D-E-F#.
namespace cursomusica::content
{

std::vector<ContentItem> topic11D()
{
    return {

        p (
            "Se a pentatônica menor 7 é a pentatônica de sempre, a pentatônica menor 6 é a sua irmã de um só grau de diferença: no lugar da sétima menor entra a sexta maior. A escala continua tendo cinco notas — 1, b3, 4, 5 e 6 —, e é essa única troca que muda o som. Onde a menor 7 dá o som do acorde m7, a menor 6 dá o som do acorde m6, mais aberto e luminoso."),
        p (
            "A apostila de improvisação de Mozart Mello mostra as duas lado a lado: sobre um acorde Gm7, a pentatônica é a \"Gm7 blues\"; sobre um Gm6, é a \"Gm6 blues\". O nome acompanha o acorde. Este tópico fecha o par de pentatônicas menores: depois dele, você terá as duas cores — a do m7 (com a b7) e a do m6 (com a 6) — sobre a mesma base."),
        c (
            "Pentatônica menor 6 = pentatônica menor com a sexta maior no lugar da sétima menor = 1, b3, 4, 5 e 6. Em Lá: A-C-D-E-F#. Cinco notas. O seis do nome é a sexta maior (o Fá sustenido em Lá), que dá à escala o som do acorde m6."),

        h ("O que o nome 6 quer dizer"),
        p (
            "Assim como a menor 7, a pentatônica menor 6 tem cinco notas — o número do nome não é a quantidade de notas, e sim o grau que caracteriza a escala. Na menor 7, esse grau é a sétima menor; na menor 6, é a sexta maior. São graus diferentes no mesmo lugar da escala, e por isso as duas pentatônicas nunca aparecem juntas: você escolhe uma ou outra conforme o acorde."),
        p (
            "Em Lá, a pentatônica menor é A-C-D-E-G. Troque o Sol (b7) pelo Fá sustenido (6) e você tem A-C-D-E-F#, a pentatônica menor 6. Sobre um Am6, essas cinco notas caem perfeitamente: o Lá, o Dó e o Mi são as notas do acorde; o Ré é a quarta; e o Fá sustenido é a sexta maior, que dá o caráter do acorde m6. A escala inteira é repouso, como a menor 7."),
        b ("A pentatônica menor 6 tem cinco notas: 1, b3, 4, 5 e 6."),
        b ("O nome 6 descreve a sexta maior que caracteriza a escala."),
        b ("Em Lá, a escala é A-C-D-E-F#: a pentatônica menor com a sexta no lugar da sétima."),
        img ("m11_pent_menor6", "Pentatônica menor 6 de Lá: cinco notas (A C D E F#). A sexta maior (Fá#) dá o som do acorde m6."),

        h ("Quando usar a sexta maior"),
        p (
            "A sexta maior brilha em três situações. Sobre um acorde menor com sexta (m6), ela é a nota do acorde e dá a cor exata. Sobre um vamp menor modal, ela sugere o modo dórico (a menor com a sexta maior) sem precisar tocar a escala inteira. E no blues e na MPB, ela dá às frases menores um brilho mais aberto, menos melancólico que o da pentatônica menor 7."),
        p (
            "O cuidado é não confundir a sexta maior com a sétima menor. As duas pentatônicas menores diferem nesse único grau, e tocar a nota errada troca o acorde: sobre um Am6, o Sol (b7) soa como uma nota de fora; sobre um Am7, o Fá sustenido (6) soa como uma nota de fora. É o acorde que decide qual das duas pentatônicas encaixa."),
        tbl ({ "Acorde em Lá", "Pentatônica", "Nota característica" }, {
            { "Am7", "menor 7 (A C D E G)", "sétima menor (Sol)" },
            { "Am6", "menor 6 (A C D E F#)", "sexta maior (Fá#)" },
            { "Am (tríade)", "menor 7 ou menor 6", "a cor depende do contexto" },
        }),
        c (
            "Repouso × tensão: sobre o acorde menor, a sexta maior é nota estável — o exercício pode tratá-la como repouso. Como na pentatônica menor 7, todas as cinco notas da menor 6 são de repouso; a tensão só aparece quando você sai delas sem ser pedido."),

        h ("O lick deste tópico"),
        p (
            "O lick abaixo sobe a pentatônica menor 6 de Lá e insere a sexta maior (Fá#) como nota de cor, recolhendo de volta na pentatônica. É um gesto de cor modal, no estilo da apostila de improvisação: a sexta abre a frase e a escala recolhe. Ouça como o Fá sustenido muda o clima em relação ao lick anterior — o som fica mais luminoso."),
        aud ({ "A4", "C5", "D5", "E5", "F#5", "E5", "D5", "C5", "A4" },
             "Lick do tópico D: a pentatônica menor 6 de Lá. O Fá sustenido (6) é a nota que dá o nome e a cor de m6 à escala."),
        part ("m11_partitura_d", { "A4", "C5", "D5", "E5", "F#5", "E5", "D5", "C5", "A4" },
              "Partitura do lick D: a pentatônica menor 6 de Lá (A C D E F#). Cinco notas, com a sexta maior (Fá#) no topo da frase."),

        h ("Estudar as duas pentatônicas"),
        p (
            "Toque a pentatônica menor 7 e a menor 6 uma depois da outra, na mesma região do braço. A única diferença é o último grau: o Sol na menor 7, o Fá sustenido na menor 6. Ouvir as duas seguidas é o melhor jeito de fixar a diferença entre o som do m7 e o do m6. Depois, toque cada uma sobre o seu acorde — Am7 e Am6 — e sinta o encaixe."),

        h ("A sexta e o som dórico"),
        p (
            "O modo dórico é a escala menor com a sexta maior. É essa nota que distingue o dórico do eólio (a menor natural): o eólio tem a sexta menor, o dórico tem a maior. Quando você usa a pentatônica menor 6, está tocando o dórico reduzido às suas cinco notas essenciais. É por isso que a menor 6 soa modal: ela sugere o dórico sem precisar das sete notas."),
        p (
            "Na prática, a sexta maior é a nota que dá à frase menor um caráter mais aberto e menos melancólico. Onde a menor natural pura soa triste, a sexta a deixa mais luminosa. É esse brilho que os guitarristas usam em vamps modais, em solos de rock cantável e em passagens de MPB, onde a cor importa mais do que a tensão."),
        b ("O dórico é a menor natural com a sexta maior; a sexta é a nota que o define."),
        b ("A pentatônica menor 6 é o dórico reduzido às suas cinco notas essenciais."),
        b ("A sexta é cor: abre a frase em vez de pedir resolução."),
        tbl ({ "Modo", "Sexta", "Caráter" }, {
            { "Eólio (menor natural)", "sexta menor", "triste, fechado" },
            { "Dórico", "sexta maior", "aberto, luminoso" },
            { "Pentatônica menor 6", "sexta maior", "cor modal sobre a pentatônica" },
        }),

        h ("Escolhendo entre a menor 6 e a menor 7"),
        p (
            "As duas pentatônicas menores partem da mesma base e divergem num só grau. A menor 7 traz a sétima menor e combina com o acorde m7; a menor 6 traz a sexta maior e combina com o m6. Saber escolher é o que separa a frase que encaixa no acorde da frase que briga com ele. A regra prática é simples: olhe o acorde e use a pentatônica que contém o grau que ele pede."),
        p (
            "As duas também podem se alternar numa frase mais longa, se a harmonia mudar de m7 para m6. Você sustenta a menor 7 sobre o acorde m7 e troca para a menor 6 quando o acorde vira m6, acompanhando a harmonia. É esse tipo de troca que faz o solo seguir o acorde em vez de repetir uma posição só."),
        c (
            "Nota de repouso × tensão: a sexta maior é estável sobre o acorde menor (cor de repouso); a sétima menor é estável sobre o m7. O critério é o acorde: m7 pede a menor 7 (com a b7); m6 pede a menor 6 (com a 6)."),

        h ("Aplicando em vamps modais"),
        p (
            "O lugar onde a pentatônica menor 6 brilha é o vamp modal: um ou dois acordes repetidos, sobre os quais você improvisa explorando a cor. Sobre um vamp de Lá menor, a sexta (Fá#) dá a cor dórica e mantém a frase flutuando, sem pressa de resolver. É o oposto do blues, onde a sétima menor e o ritmo é que dão o movimento."),
        p (
            "Improvisar sobre um vamp modal é um bom treino de cor: você não tem para onde resolver, então precisa construir a frase pela variação — mudar o ritmo, mudar a região, alternar entre a sexta e a pentatônica pura. É essa variação que mantém o interesse de uma frase longa sobre um acorde só."),

        h ("A sexta e o fraseado modal"),
        p (
            "A sexta maior é a nota que faz a frase flutuar. Sobre um vamp modal, ela mantém a frase suspensa, sem a urgência de resolver que uma tensão carrega. É por isso que o fraseado modal — sobre um ou dois acordes repetidos — usa tanto a sexta: sem uma progressão que resolva, a frase precisa de uma cor estável para não soar perdida. A sexta é essa cor."),
        p (
            "Na prática, você usa a sexta para estender uma ideia que ainda não quer terminar. Você toca a pentatônica, chega perto do fim e, em vez de resolver na tônica, passa pela sexta e continua. A frase ganha um compasso a mais, uma respiração, um desvio. É esse tipo de desvio que dá à improvisação modal o seu caráter contemplativo, em contraste com o blues, que é feito de tempo e de tensão."),
        p (
            "Vale notar que a sexta maior também aparece em contextos que não são modais. Sobre um blues, ela é a nota que dá brilho às passagens; sobre um rock menor, ela acrescenta um toque de esperança ao som triste. Em todos os casos, a função é a mesma: abrir a frase em vez de fechá-la. Aprender a dosar essa abertura é o que dá maturidade ao fraseado menor."),
        b ("A sexta maior mantém a frase flutuando, sem urgência de resolver."),
        b ("Ela estende a ideia: em vez de resolver, a frase respira e continua."),
        b ("No blues e no rock, ela dá brilho às passagens menores."),
        tbl ({ "Contexto", "Papel da sexta", "Efeito" }, {
            { "Vamp modal", "cor estável", "frase contemplativa" },
            { "Blues", "brilho de passagem", "alívio dentro da tensão" },
            { "Rock menor", "toque de esperança", "contraste com o som triste" },
        }),

        h ("As duas cores no mesmo solo"),
        p (
            "As duas pentatônicas menores não são rivais: elas são duas cores do mesmo pincel. A menor 7 pinta o m7; a menor 6 pinta o m6. Um solo maduro troca de cor quando a harmonia troca de acorde. Você abre uma ideia sobre o Am7 com a menor 7 e, quando o acorde vira Am6, passa para a menor 6, acompanhando a mudança sem parar a frase."),
        p (
            "O segredo está em ouvir o acorde. Cada pentatônica menor tem o seu grau característico — a b7 ou a 6 —, e é esse grau que faz a frase encaixar ou brigar. Quando você ouve o acorde mudar de m7 para m6, a mão já sabe qual das duas pentatônicas usar. É esse reflexo que separa o guitarrista que decora posições do guitarrista que fraseia sobre a harmonia."),
        p (
            "Experimente tocar a mesma frase duas vezes: na primeira, com a menor 7 (terminando no Sol); na segunda, com a menor 6 (terminando no Fá sustenido). A primeira soa como m7; a segunda, como m6. É esse contraste que ensina o ouvido a escolher. Com o tempo, você usa as duas sem pensar, guiado apenas pelo acorde que está soando."),
        b ("A menor 7 pinta o m7; a menor 6 pinta o m6: troque de cor quando o acorde mudar."),
        b ("O grau característico (b7 ou 6) é o que faz a frase encaixar no acorde."),
        b ("Compare a mesma frase nas duas pentatônicas para ouvir a diferença."),
        tbl ({ "Acorde", "Pentatônica", "Grau que decide" }, {
            { "m7", "menor 7", "sétima menor (b7)" },
            { "m6", "menor 6", "sexta maior (6)" },
            { "m (tríade)", "menor 7 ou menor 6", "o contexto harmônico decide" },
        }),

        c (
            "Meta do módulo: 100 BPM. Toque os dois licks (menor 7 e menor 6) na mesma região do braço, no mesmo tempo. O ouvido aprende a diferença entre o som do m7 e o do m6 quando a mão toca as duas seguidas."),
    };
}

} // namespace cursomusica::content
