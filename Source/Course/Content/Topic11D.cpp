#include "Course/Content/Topics.h"

// Topic 11D — Pentatônica menor 6 (Módulo 11, Etapa 11).
// "Pentatônica menor 6" = a pentatônica menor acrescentada da sexta (6) — a
// escala de seis notas 1-b3-4-5-6-b7. A sexta maior sobre a pentatônica menor
// dá o som dórico (a "pentatônica menor com cor"), uma cor muito usada no rock,
// no blues e na MPB.
namespace cursomusica::content
{

std::vector<ContentItem> topic11D()
{
    return {

        p (
            "Se a pentatônica menor 7 acrescenta uma tensão que resolve, a pentatônica menor 6 acrescenta uma cor que paira. As duas partem da mesma pentatônica menor; o que muda é a nota que entra. Na pentatônica menor 6, a nota nova é a sexta — e a sexta é a nota que dá à pentatônica o sabor dórico, aquele som levemente aveludado que aparece no rock, no blues e na MPB."),
        p (
            "Este tópico fecha o par de pentatônicas acrescentadas. Depois de estudar as duas, você terá dois recursos de cor sobre a mesma base: a sétima, que puxa para a tônica, e a sexta, que abre a frase para um lado mais cantável. Saber quando usar cada uma é o que separa o guitarrista que decora posições do guitarrista que fraseia."),
        c (
            "Pentatônica menor 6 = pentatônica menor + a sexta (6). Em Lá: A-C-D-E-G-A acrescentada da sexta maior (F#). A sexta é uma nota de cor: ela não puxa como a sétima, ela abre o som."),

        h ("A sexta como cor"),
        p (
            "A pentatônica menor é 1, b3, 4, 5 e b7. Acrescentando a sexta maior (6), chega-se a 1-b3-4-5-6-b7 — uma escala de seis notas. A sexta maior é a nota que, sobre um acorde menor, produz o som do modo dórico. Por isso a pentatônica menor 6 soa mais aberta e mais jazzística que a pentatônica menor pura."),
        p (
            "Diferente da sétima, a sexta não pede resolução: ela é uma nota estável, uma cor de repouso. Isso muda a frase. Com a sétima, você constrói tensão e resolve; com a sexta, você estende a frase e a mantém cantável. São duas ferramentas complementares — e o fraseado rico usa as duas."),
        b ("A pentatônica menor 6 tem seis notas: 1, b3, 4, 5, 6 e b7."),
        b ("A sexta maior é a nota característica do som dórico."),
        b ("A sexta é cor de repouso: ela estende a frase em vez de pedir resolução."),
        img ("m11_pent_menor6", "Pentatônica menor 6: a pentatônica menor acrescentada da sexta maior (o som dórico). A nota nova dá cor à frase."),

        h ("Quando usar a sexta"),
        p (
            "A sexta brilha em três situações. Sobre um vamp menor, ela dá a cor modal que caracteriza o dórico. No blues, ela aparece nos riffs mais abertos e nas frases de chegada. E na MPB e no samba, ela é a nota que dá o sabor brasileiro à pentatônica, muito presente nos solos de violão e guitarra."),
        p (
            "O cuidado é não empilhar a sexta com a sétima sem intenção. A sexta (repouso de cor) e a sétima (tensão) têm funções opostas; usadas juntas sem critério, a frase fica indecisa. A regra prática é escolher uma direção: ou a frase abre com a sexta, ou ela puxa com a sétima. Misturar as duas é um recurso avançado, para quando a frase já tem alvo claro."),
        tbl ({ "Nota acrescentada", "Efeito", "Uso" }, {
            { "Sétima (7)", "tensão que resolve na tônica", "fechar a frase com força" },
            { "Sexta (6)", "cor de repouso (som dórico)", "abrir a frase, soar cantável" },
            { "As duas", "recurso avançado", "só com alvo de frase já definido" },
        }),
        c (
            "Repouso × tensão: a sexta maior sobre o acorde menor é uma nota estável no contexto dórico — o exercício pode tratá-la como repouso. A sétima, ao contrário, é tensão e precisa ser pedida. Distinguir as duas é o objetivo deste par de tópicos."),

        h ("O lick deste tópico"),
        p (
            "O lick abaixo sobe a pentatônica menor de Lá e insere a sexta (Fá#) como nota de cor, resolvendo de volta na pentatônica. É um gesto de Greg Howe — pentatônicas deslocadas com legato amplo —, onde a sexta estende a linha antes de recolher. Ouça como a frase fica mais aberta do que a pentatônica pura."),
        aud ({ "A4", "C5", "D5", "E5", "F#5", "E5", "D5", "C5", "A4" },
             "Lick do tópico D: pentatônica menor de Lá com a sexta (F#) como cor. A sexta abre a frase e a pentatônica recolhe."),
        part ("m11_partitura_d", { "A4", "C5", "D5", "E5", "F#5", "E5", "D5", "C5", "A4" },
              "Partitura do lick D: a pentatônica menor 6. A sexta maior (Fá#) dá a cor dórica; a frase resolve de volta na pentatônica."),

        h ("Estudar as duas pentatônicas"),
        p (
            "Toque a pentatônica menor pura e, alternando, insira ora a sexta, ora a sétima. Sinta a diferença: com a sexta a frase respira; com a sétima ela puxa. Depois, toque o lick deste tópico e o do anterior lado a lado. É esse contraste que vai ensinar o seu ouvido a escolher a cor certa na hora de improvisar."),

        h ("A sexta e o som dórico"),
        p (
            "O modo dórico é a escala menor com a sexta maior. É essa nota que distingue o dórico do eólio (a menor natural): o eólio tem a sexta menor, o dórico tem a maior. Quando você acrescenta a sexta maior à pentatônica menor, a sua frase passa a sugerir o dórico, mesmo sem tocar a escala completa. É por isso que a pentatônica menor 6 soa modal."),
        p (
            "Na prática, a sexta maior é a nota que dá à frase menor um caráter mais aberto e menos melancólico. Onde a menor natural pura soa triste, a sexta a deixa mais luminosa. É esse brilho que os guitarristas usam em vamps modais, em solos de rock cantável e em passagens de MPB, onde a cor importa mais do que a tensão."),
        b ("O dórico é a menor natural com a sexta maior; a sexta é a nota que o define."),
        b ("A pentatônica menor 6 sugere o dórico sem tocar a escala completa."),
        b ("A sexta é cor de repouso: abre a frase em vez de pedir resolução."),
        tbl ({ "Modo", "Sexta", "Caráter" }, {
            { "Eólio (menor natural)", "sexta menor", "triste, fechado" },
            { "Dórico", "sexta maior", "aberto, luminoso" },
            { "Pentatônica menor 6", "sexta maior", "cor modal sobre a pentatônica" },
        }),

        h ("Escolhendo entre a sexta e a sétima"),
        p (
            "As duas pentatônicas acrescentadas partem da mesma base e divergem na nota nova. A sétima puxa para a tônica; a sexta abre o som. Saber escolher entre as duas é o que separa a frase que \"pede\" da frase que \"respira\". Uma regra prática: se você quer fechar a frase com força, use a sétima; se você quer manter a frase cantável, use a sexta."),
        p (
            "As duas também combinam, em frases mais longas. Você pode abrir com a sexta (cor) e fechar com a sétima (tensão e resolução), criando um arco de cor e tensão dentro de uma só frase. É esse tipo de arco que dá às improvisações um sentido de começo, meio e fim, em vez de uma sequência de notas soltas."),
        c (
            "Nota de repouso × tensão: a sexta maior é estável no contexto dórico (cor de repouso); a sétima é tensão que precisa resolver. As duas têm o seu lugar — o critério é a função que você quer dar à frase."),

        h ("Aplicando em vamps modais"),
        p (
            "O lugar onde a pentatônica menor 6 brilha é o vamp modal: um ou dois acordes repetidos, sobre os quais você improvisa explorando a cor. Sobre um vamp de Lá menor, a sexta (Fá#) dá a cor dórica e mantém a frase flutuando, sem pressa de resolver. É o oposto do blues, onde a tensão e a resolução são o motor."),
        p (
            "Improvisar sobre um vamp modal é um bom treino de cor: você não tem para onde resolver, então precisa construir a frase pela variação — mudar o ritmo, mudar a região, mudar entre a sexta e a pentatônica pura. É essa variação que mantém o interesse de uma frase longa sobre um acorde só."),


        h ("A sexta e o fraseado modal"),
        p (
            "A sexta maior é a nota que faz a frase \"flutuar\". Sobre um vamp modal, ela mantém a frase suspensa, sem a urgência de resolver que a sétima carrega. É por isso que o fraseado modal — sobre um ou dois acordes repetidos — usa tanto a sexta: sem uma progressão que resolva, a frase precisa de uma cor estável para não soar perdida. A sexta é essa cor."),
        p (
            "Na prática, você usa a sexta para estender uma ideia que ainda não quer terminar. Você toca a pentatônica, chega perto do fim, e em vez de resolver na tônica, passa pela sexta e continua. A frase ganha um compasso a mais, uma respiração, um desvio. É esse tipo de desvio que dá à improvisação modal o seu caráter contemplativo, em contraste com o blues, que é feito de tensões e resoluções."),
        p (
            "Vale notar que a sexta maior também aparece em contextos que não são modais. Sobre um blues, ela é a \"nota maior\" que dá brilho às passagens; sobre um rock menor, ela acrescenta um toque de esperança ao som triste. Em todos os casos, a função é a mesma: abrir a frase em vez de fechá-la. Aprender a dosar essa abertura é o que dá maturidade ao fraseado menor."),
        b ("A sexta maior mantém a frase flutuando, sem urgência de resolver."),
        b ("Ela estende a ideia: em vez de resolver, a frase respira e continua."),
        b ("No blues e no rock, ela dá brilho às passagens menores."),
        tbl ({ "Contexto", "Papel da sexta", "Efeito" }, {
            { "Vamp modal", "cor estável", "frase contemplativa" },
            { "Blues", "brilho de passagem", "alívio dentro da tensão" },
            { "Rock menor", "toque de esperança", "contraste com o som triste" },
        }),


        h ("Cor e tensão no mesmo solo"),
        p (
            "As duas pentatônicas acrescentadas não são rivais: elas se completam. A sexta dá cor; a sétima dá tensão. Um solo maduro usa as duas, alternando conforme a frase pede. Você abre uma ideia com a sexta, mantém a frase cantável, e no fim introduz a sétima para puxar a resolução. É esse vaivém entre cor e tensão que dá relevo ao fraseado."),
        p (
            "O segredo está na ordem. A sexta, por ser estável, funciona bem no começo da frase, quando você ainda está estabelecendo a ideia. A sétima, por ser tensa, funciona melhor no fim, quando você quer resolver. Inverter essa ordem costuma soar estranho: uma tensão no começo deixa a frase ansiosa, e uma cor no fim deixa a frase sem direção."),
        p (
            "Experimente tocar a mesma frase de duas formas: primeiro só com a sexta, depois trocando a última nota pela sétima. A primeira versão fica aberta, contemplativa; a segunda fica conclusiva, com uma resolução forte. É esse contraste que ensina o ouvido a escolher. Com o tempo, você usa as duas sem pensar, guiado apenas pela intenção da frase."),
        b ("A sexta dá cor; a sétima dá tensão: use as duas conforme a frase pede."),
        b ("Cor no começo da frase, tensão no fim, para dar relevo."),
        b ("Compare a mesma frase com e sem a sétima final para ouvir o efeito."),
        tbl ({ "Posição na frase", "Nota ideal", "Por quê" }, {
            { "Começo", "sexta (cor)", "estabelece a ideia sem pressa" },
            { "Meio", "pentatônica pura", "mantém o movimento" },
            { "Fim", "sétima (tensão)", "puxa a resolução" },
        }),

        c (
            "Meta do módulo: 100 BPM. Toque os dois licks (sexta e sétima) na mesma região do braço, no mesmo tempo. O ouvido aprende a diferença quando a mão toca as duas seguidas."),
    };
}

} // namespace cursomusica::content
