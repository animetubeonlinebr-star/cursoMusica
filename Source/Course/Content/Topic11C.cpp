#include "Course/Content/Topics.h"

// Topic 11C — Pentatônica menor 7 (Módulo 11, Etapa 11).
// "Pentatônica menor 7" = a pentatônica menor acrescentada da sétima (b7) — a
// escala de seis notas 1-b3-4-5-b7-7 que completa a pentatônica menor para o som
// do blues/jazz. É a pentatônica menor "com a sétima maior por cima".
namespace cursomusica::content
{

std::vector<ContentItem> topic11C()
{
    return {

        p (
            "A pentatônica menor você já toca. Este tópico dá o passo que transforma a pentatônica de sempre numa ferramenta de fraseado mais rica: acrescentar a sétima maior. A pentatônica menor 7 é a escala de cinco notas mais a sétima maior — seis notas no total —, e essa nota extra muda tudo, porque cria uma tensão pronta para resolver na tônica."),
        p (
            "A pentatônica menor pura é segura demais: todas as notas soam bem, e por isso é difícil fazer uma frase que peça alguma coisa. Acrescentando a sétima maior, você ganha uma nota que puxa para casa. É esse puxão que dá direção à frase — o mesmo recurso que os guitarristas de blues e de rock usam para encerrar um solo com força."),
        c (
            "Pentatônica menor 7 = pentatônica menor + a sétima maior (7). Em Lá: A-C-D-E-G-A acrescentada do Sol#. A nota nova é o ímã que resolve na tônica."),

        h ("O que a sétima acrescenta"),
        p (
            "A pentatônica menor é formada pelos graus 1, b3, 4, 5 e b7. Se você acrescentar a sétima maior (7), chega a uma escala de seis notas: 1-b3-4-5-b7-7. Essa nota nova fica a um semitom abaixo da tônica, e é justamente esse semitom que faz a frase querer resolver. O ouvido ouve a sétima e já espera a tônica."),
        p (
            "Sobre um acorde menor, a sétima funciona como a sétima maior da tonalidade — em Lá, o Sol#. Sobre um blues, ela dá aquele brilho de passagem antes da tônica. Em ambos os casos, a sétima não é uma nota de repouso: é uma nota de tensão que pede resolução. Este módulo vai justamente cobrar que você reconheça quando uma nota é repouso e quando é tensão."),
        b ("A pentatônica menor 7 tem seis notas: 1, b3, 4, 5, b7 e 7."),
        b ("A sétima fica a um semitom da tônica e resolve nela."),
        b ("A sétima é tensão, não repouso: use-a para pedir a resolução."),
        img ("m11_pent_menor7", "Pentatônica menor 7: a pentatônica menor acrescentada da sétima. A nota nova fica a um semitom da tônica."),

        h ("Onde a pentatônica menor 7 vive"),
        p (
            "A pentatônica menor 7 aparece principalmente em três contextos. No blues, como cor da chegada: você sobe pela pentatônica e insere a sétima antes de cair na tônica. No rock e no metal, como tensão melódica: a sétima dá um sabor que a pentatônica sozinha não tem. E no jazz, sobre acordes menores, como a ponte entre a pentatônica e o som dórico."),
        p (
            "Cada contexto pede uma dosagem diferente. No blues, a sétima entra em gesto — uma passada rápida. No jazz, ela pode durar, porque o acorde já espera por ela. Aprender a dosar a sétima é aprender a frase: a nota é a mesma, o tempo que ela dura é que muda o efeito."),
        tbl ({ "Contexto", "Função da sétima", "Dose" }, {
            { "Blues", "cor da chegada", "passagem rápida antes da tônica" },
            { "Rock / metal", "tensão melódica", "nota de apoio, resolve logo" },
            { "Jazz (menor)", "ponte para o dórico", "pode durar como cor do acorde" },
        }),
        c (
            "Nota de repouso × tensão (REQ-011/REQ-012): sobre um acorde de Lá menor, A-C-E são repouso; a sétima (G#) é tensão e só é aceita quando o exercício pede o seu uso. Tocar G# sem pedir é erro — este módulo cobra essa distinção."),

        h ("O lick deste tópico"),
        p (
            "O lick abaixo sobe a pentatônica menor de Lá e insere a sétima (Sol#) no topo, resolvendo na tônica. É um gesto típico de Richie Kotzen: a pentatônica com fraseado vocal, onde a sétima aparece só na hora de resolver. Ouça como a nota nova cria o puxão e a tônica fecha a frase."),
        aud ({ "A4", "C5", "D5", "E5", "G5", "G#5", "A5", "G5", "E5", "D5", "C5", "A4" },
             "Lick do tópico C: pentatônica menor de Lá subindo, com a sétima (G#) resolvendo na tônica. A sétima é a tensão; o A é o repouso."),
        part ("m11_partitura_c", { "A4", "C5", "D5", "E5", "G5", "G#5", "A5", "G5", "E5", "D5", "C5", "A4" },
              "Partitura do lick C: a pentatônica menor 7. A sétima (Sol#) aparece no topo e resolve na tônica (Lá)."),

        h ("Estudar a pentatônica menor 7"),
        p (
            "Comece tocando a pentatônica menor de sempre e, só no fim da frase, insira a sétima. Depois inverta: comece pela sétima e resolva. Por último, toque a escala completa de seis notas nos dois sentidos. O objetivo não é decorar mais uma escala, e sim aprender onde a nota de tensão cabe para fazer a frase pedir a resolução."),

        h ("A sétima no blues e no rock"),
        p (
            "No blues, a sétima maior aparece como cor de chegada. Você sobe pela pentatônica menor e, no fim da frase, insere a sétima antes de cair na tônica. O efeito é imediato: a frase que estava apenas \"andando\" passa a \"pedir\" a resolução. É por isso que muitos solos de blues terminam com esse gesto — a sétima cria a expectativa e a tônica a satisfaz."),
        p (
            "No rock e no metal, a pentatônica menor 7 é usada como cor de tensão. Em vez de resolver imediatamente, o guitarrista sustenta a sétima por um tempo e só depois cai na tônica. Esse atraso da resolução é o que dá dramaticidade à frase. O mesmo recurso, usado em dose maior, transforma a pentatônica de sempre num som mais sofisticado."),
        tbl ({ "Uso", "Duração da sétima", "Efeito" }, {
            { "Blues (chegada)", "passagem curta", "pede a tônica" },
            { "Rock (tensão)", "nota sustentada", "dramatiza a resolução" },
            { "Jazz (menor)", "nota de cor", "liga a pentatônica ao dórico" },
        }),
        b ("A sétima maior fica a um semitom abaixo da tônica e puxa para ela."),
        b ("No blues, ela aparece na chegada; no rock, sustenta a tensão."),
        b ("Dosar a duração da sétima é o que define o efeito da frase."),

        h ("Comparando com a pentatônica pura"),
        p (
            "A diferença entre a pentatônica menor pura e a pentatônica menor 7 é uma só nota, mas o efeito é grande. A pura é estável em todas as notas, o que a torna segura — e um pouco sem direção. A 7 tem uma nota que desequilibra a frase de propósito, e é esse desequilíbrio que cria a tensão e a resolução. Frases boas precisam das duas: momentos de estabilidade e momentos de tensão."),
        p (
            "Um exercício útil é tocar a mesma frase duas vezes: na primeira, só com as notas da pentatônica pura; na segunda, substituindo uma nota pela sétima. Ouça como a segunda versão pede a resolução e a primeira não. É esse contraste que ensina o ouvido a escolher quando usar a sétima."),
        c (
            "Este tópico é o primeiro a introduzir, de propósito, uma nota de tensão na pentatônica. Guarde a ideia: tensão só é boa quando resolve. A sétima sem a tônica logo depois é uma pergunta sem resposta."),

        h ("A sétima e o ouvido"),
        p (
            "Toda tensão musical é uma promessa. A sétima maior promete a tônica, porque está a um semitom dela. Quando a frase toca a sétima e resolve na tônica, o ouvido sente a promessa cumprida; quando a sétima fica no ar, o ouvido sente a promessa quebrada. Aprender a pentatônica menor 7 é aprender a fazer e cumprir essa promessa na hora certa."),
        p (
            "Nos próximos módulos, o app vai avaliar exatamente isso: se a sua nota de tensão foi resolvida e se ela era pedida. Sobre um vamp menor, a sétima maior é tensão — você só a usa quando a frase pede. Este tópico é onde essa distinção começa a virar prática de mão e de ouvido."),


        h ("A sétima e as posições do braço"),
        p (
            "A sétima maior não vive numa posição só: ela aparece em todas as regiões da pentatônica menor, sempre a um semitom abaixo de uma tônica. Isso significa que, quando você aprende a pentatônica menor 7 numa posição, aprende também onde a sétima está nas outras. É esse mapeamento que permite usar a tensão em qualquer lugar do braço, sem depender de uma região específica."),
        p (
            "Um bom exercício é tocar a sétima em cada posição da pentatônica e resolver na tônica mais próxima. Você percebe que a sétima é sempre o mesmo gesto (um semitom abaixo da tônica), apenas transportado para outra região. Quando o gesto fica automático, a tensão deixa de ser uma nota \"difícil\" e passa a ser um recurso que a mão encontra sozinha."),
        p (
            "Há também a sétima menor, que pertence à própria pentatônica. Não confunda as duas: a sétima menor (b7) é nota de repouso da pentatônica; a sétima maior (7) é a nota acrescentada, de tensão. Saber distinguir as duas é essencial para não usar a tensão sem querer. O nome \"pentatônica menor 7\" refere-se à sétima maior acrescentada."),
        b ("A sétima maior está sempre um semitom abaixo de uma tônica, em toda região."),
        b ("Tocar a sétima e resolver na tônica mais próxima fixa o gesto."),
        b ("Não confunda a sétima menor (repouso da pentatônica) com a sétima maior (tensão)."),
        tbl ({ "Nota", "Grau", "Função" }, {
            { "b7 (Sol em Lá)", "sétima menor", "repouso (já está na pentatônica)" },
            { "7 (Sol# em Lá)", "sétima maior", "tensão acrescentada" },
            { "1 (Lá)", "tônica", "resolução da tensão" },
        }),


        h ("A tensão como pergunta"),
        p (
            "Toda tensão musical é uma pergunta. A sétima maior pergunta; a tônica responde. Quando você toca a pentatônica menor 7, está fazendo uma pergunta que só a resolução responde. Se a frase para na sétima, a pergunta fica no ar, e o ouvinte sente que falta algo. Aprender a pentatônica menor 7 é, no fundo, aprender a fazer perguntas que você mesmo responde."),
        p (
            "Há dois erros comuns com a sétima. O primeiro é não resolvê-la: a frase fica sem resposta. O segundo é resolvê-la tarde demais: a pergunta esfria e a resposta soa desconectada. O ponto certo da resolução é logo depois da tensão, no tempo forte seguinte. É esse encaixe entre a pergunta e a resposta que dá à frase o seu sentido musical."),
        p (
            "Treine perguntas e respostas: toque a sétima, resolva na tônica, pare; toque de novo, com uma tensão diferente, e resolva. Cada par de tensão e resolução é uma frase completa. Quando você tiver vários pares, comece a ligá-los, formando frases mais longas. A pentatônica menor 7 deixa de ser uma escala e passa a ser um jeito de conversar com a música."),
        b ("A sétima é uma pergunta; a tônica é a resposta."),
        b ("Resolva logo depois da tensão, no tempo forte seguinte."),
        b ("Treine pares de tensão e resolução antes de ligá-los em frases longas."),
        tbl ({ "Gesto", "Nota", "Efeito" }, {
            { "Pergunta", "sétima maior", "cria expectativa" },
            { "Resposta", "tônica", "satisfaz a expectativa" },
            { "Silêncio", "pausa", "deixa a pergunta respirar" },
        }),

        c (
            "Meta do módulo: 100 BPM. Toque o lick com a sétima no metrônomo até a resolução cair exatamente no tempo forte — é ali que a tensão resolve com convicção."),
    };
}

} // namespace cursomusica::content
