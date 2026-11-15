#include "Course/Content/Topics.h"

// Topic 8A — Dominante V7 (Módulo 8, Etapa 8).
// Fonte de verdade do texto: docs/MUSIC.md §8 (bloco A).
namespace cursomusica::content
{

std::vector<ContentItem> topic8A()
{
    return {

        p (
            "O acorde dominante é o motor da harmonia tonal. Ele existe para criar tensão e apontar o caminho de volta para casa. Quando você ouve um acorde que \"pede\" o próximo, quase sempre está ouvindo um dominante. Neste módulo você aprende a reconhecer o dominante, a construí-lo sobre qualquer nota e a usá-lo como ferramenta de movimento — inclusive nas substituições que dão cor ao jazz, à bossa e à MPB."),
        p (
            "O dominante mais comum é o quinto grau de uma tonalidade, escrito V7. Em Dó maior, o quinto grau é Sol, e o acorde V7 é Sol7 (G7). Ele é a ponte que leva de volta à tônica. Entender o V7 é entender por que a música caminha, para onde ela caminha e o que faz o ouvido sentir que uma frase terminou."),
        c (
            "Objetivo do tópico: compreender o acorde dominante V7 — o que ele é, de onde vem, como se constrói e por que ele pede resolução."),

        h ("O que é um acorde dominante"),
        p (
            "Um acorde de sétima dominante é formado por quatro notas: a fundamental, a terça maior, a quinta justa e a sétima menor. Em semitons, a partir da fundamental, temos 0, 4, 7 e 10. Essa combinação de intervalos é única: nenhuma outra sétima soa como ela. A terça maior dá brilho e a sétima menor dá a tensão que faz o acorde querer resolver."),
        b ("Fórmula em semitons: 0, 4, 7, 10 (fundamental, terça maior, quinta justa, sétima menor)."),
        b ("Cifra: a nota com o número 7 (Sol7, Ré7, Dó7) indica sétima dominante."),
        b ("Exemplo em Dó maior: G7 = Sol, Si, Ré, Fá."),
        p (
            "É importante não confundir as três sétimas. O acorde de sétima maior (0, 4, 7, 11) soa suspenso e estável; o de sétima menor (0, 3, 7, 10) é suave e triste; o de sétima dominante (0, 4, 7, 10) é o único que soa instável e resolutivo. Essa instabilidade é a assinatura do dominante."),
        tbl ({ "Tipo de sétima", "Intervalos (semitons)", "Som", "Exemplo em Dó" }, {
            { "sétima maior", "0, 4, 7, 11", "suspenso, estável", "CM7" },
            { "sétima menor", "0, 3, 7, 10", "suave, melancólico", "Cm7" },
            { "sétima dominante", "0, 4, 7, 10", "tenso, resolutivo", "C7" },
        }),

        h ("A função dominante e a tensão"),
        p (
            "Cada acorde de uma tonalidade tem uma função. A tônica (I) é o repouso; a subdominante (IV) prepara o movimento; o dominante (V) cria a tensão que leva de volta à tônica. Essa sequência — repouso, preparação, tensão, repouso — é o que dá sentido às frases musicais. O dominante é o momento de maior tensão."),
        b ("Tônica (I): o lar, onde a música descansa."),
        b ("Subdominante (IV): afasta do lar e prepara a volta."),
        b ("Dominante (V7): a maior tensão, que exige a resolução."),
        c (
            "A tensão do dominante é tão forte que o ouvido espera a tônica logo depois. É por isso que o V7 funciona mesmo quando aparece em outro tom: ele sempre promete uma chegada."),
        aud ({ "G3", "B3", "D4", "F4" }, "Arpejo de G7 (V7 de Dó): ouça como a última nota, o Fá, pede para resolver."),

        h ("O trítono: o motor do dominante"),
        p (
            "O que faz o dominante soar tenso é o intervalo entre a terça maior e a sétima menor. Em G7, esse intervalo é Si–Fá, que mede seis semitons: o trítono. O trítono é a distância mais instável da música ocidental, e ele quer se abrir para uma terça ou uma sexta. Essa vontade de se abrir é o que empurra a harmonia para a frente."),
        b ("Em G7, o trítono é Si–Fá (6 semitons)."),
        b ("Na resolução para Dó maior, o Si sobe para Dó e o Fá desce para Mi."),
        b ("O trítono é o intervalo que o ouvido identifica como \"dominante\"."),
        img ("m8_dominante_v7", "O V7 de Dó (G7): a terça (Si) e a sétima (Fá) formam o trítono que pede resolução."),
        c (
            "Regra prática: se você ouvir um trítono, procure o acorde dominante. Ele é o coração de todo V7."),

        h ("A resolução V7 → I"),
        p (
            "A resolução do dominante na tônica acontece por movimento de meio-tom. Cada nota instável anda a menor distância possível até uma nota estável do acorde de chegada. Esse movimento chama-se condução de vozes (voice leading) e é o que faz a resolução soar natural."),
        b ("A terça maior do V7 (sensível) sobe meio-tom para a tônica."),
        b ("A sétima menor do V7 desce meio-tom para a terça do I."),
        b ("Em G7 → C: o Si sobe para Dó e o Fá desce para Mi."),
        tbl ({ "Nota em G7", "Função", "Vai para", "Em CM7" }, {
            { "Sol", "fundamental", "permanece ou desce", "Sol (5ª do acorde)" },
            { "Si", "terça maior", "sobe 1 semitom", "Dó (fundamental)" },
            { "Ré", "quinta justa", "permanece", "Ré (9ª) ou desce" },
            { "Fá", "sétima menor", "desce 1 semitom", "Mi (terça maior)" },
        }),

        h ("O dominante no campo harmônico maior"),
        p (
            "No campo harmônico maior, o único acorde de sétima dominante natural é o V7. Os outros graus formam sétimas maiores ou menores. É por isso que o V7 se destaca: ele é o acorde que \"não pertence\" ao repouso e por isso cria movimento. Reconhecer essa exceção é o primeiro passo para entender as substituições que virão nos próximos tópicos."),
        tbl ({ "Grau", "Acorde em Dó maior", "Tipo de sétima" }, {
            { "I", "CM7", "sétima maior" },
            { "II", "Dm7", "sétima menor" },
            { "III", "Em7", "sétima menor" },
            { "IV", "FM7", "sétima maior" },
            { "V", "G7", "sétima dominante" },
            { "VI", "Am7", "sétima menor" },
            { "VII", "Bm7b5", "sétima menor com quinta diminuta" },
        }),

        h ("Como reconhecer um V7 de ouvido"),
        p (
            "O dominante tem uma sonoridade inconfundível: parece que a música está suspensa, esperando algo. Treine associando o som à sensação de \"volta\". Toque um G7 e cante a nota que você sente que vem depois; quase sempre será o Dó. Esse exercício simples afina o ouvido para toda a harmonia funcional."),
        b ("Ouça o acorde e pergunte: para onde ele quer ir?"),
        b ("Cante a nota de chegada antes de tocar o acorde seguinte."),
        b ("Confira tocando a resolução e perceba o alívio."),
        aud ({ "G3", "F4" }, "Só o trítono (Sol–Fá) do G7: ouça a tensão pedindo resolução."),
        aud ({ "G3", "B3", "D4", "F4", "C4", "E4", "G4" }, "G7 resolvendo em C: a tensão se transforma em repouso."),

        h ("Erros comuns ao estudar o dominante"),
        p (
            "Quem está começando costuma tratar qualquer acorde com número 7 como dominante. Isso gera confusão: CM7 não é dominante, é sétima maior. Outro erro é tocar o dominante sem ouvir a resolução, o que transforma o estudo em decoreba. O dominante só faz sentido na relação com o acorde que ele resolve."),
        b ("Confundir C7 (dominante) com CM7 (sétima maior): são acordes diferentes."),
        b ("Esquecer a sétima menor e tocar só a tríade: perde-se a tensão."),
        b ("Tocar o V7 sem resolver: estude sempre o par V7 → I."),
        c (
            "Dica: escreva o alvo antes de tocar o dominante. Saber para onde vai é metade do caminho."),

        h ("Aplicação prática"),
        p (
            "Na guitarra, o dominante aparece em muitas formas. Você pode tocá-lo como acorde (com pestana, na região do braço que preferir) ou como arpejo, percorrendo as quatro notas. Tocar o arpejo é a melhor forma de ouvir cada intervalo do acorde e entender como cada nota se comporta na resolução."),
        b ("Toque o acorde G7 em pelo menos duas regiões do braço."),
        b ("Toque o arpejo Sol–Si–Ré–Fá subindo e descendo."),
        b ("Resolva em CM7 e escute a condução das vozes."),
        part ("m8_partitura_v7", { "G3", "B3", "D4", "F4" },
              "Partitura do arpejo de G7 (V7 de Dó). Pressione ouvir para escutar exatamente o que está escrito."),

        h ("O dominante em outras tonalidades"),
        p (
            "O dominante não pertence só a Dó maior. Em qualquer tonalidade, o V7 é construído da mesma forma: sobre o quinto grau, com a fórmula 0, 4, 7, 10. Em Sol maior, o V7 é D7; em Fá maior, é C7; em Lá maior, é E7. Aprender a construir o dominante em todas as tonalidades é o que permite tocar as músicas em qualquer tom, sem depender de decorar acordes soltos."),
        b ("Dó maior → V7 = G7."),
        b ("Sol maior → V7 = D7."),
        b ("Fá maior → V7 = C7."),
        b ("Lá maior → V7 = E7."),
        p (
            "Repare que o dominante de uma tonalidade é sempre a nota que está uma quinta justa acima da tônica. Essa relação é tão constante que os músicos chamam o movimento V7 → I de \"resolução por quintas\". Ela é a base de quase toda a harmonia tonal, e você a encontrará em toda a música que estudar."),
        tbl ({ "Tonalidade", "Tônica", "Dominante V7", "Notas" }, {
            { "Dó maior", "C", "G7", "G, B, D, F" },
            { "Sol maior", "G", "D7", "D, F#, A, C" },
            { "Fá maior", "F", "C7", "C, E, G, Bb" },
            { "Si bemol maior", "Bb", "F7", "F, A, C, Eb" },
            { "Lá menor", "Am", "E7", "E, G#, B, D" },
        }),

        h ("O dominante na guitarra"),
        p (
            "Na guitarra, o dominante aparece em muitas posições. Uma das formas mais úteis é o acorde de sétima dominante com a fundamental na quinta ou na sexta corda. Como a guitarra repete as notas em várias oitavas, o mesmo acorde pode ser tocado em regiões diferentes do braço, e cada região produz um timbre diferente. Conhecer várias posições do dominante é essencial para acompanhar."),
        b ("G7 com baixo na 6ª corda (casa 3)."),
        b ("G7 com baixo na 5ª corda (casa 10)."),
        b ("G7 na região aguda, com inversões nas cordas 1 a 4."),
        p (
            "Além dos acordes, o dominante pode ser tocado como arpejo. Tocar as quatro notas separadamente (Sol, Si, Ré, Fá) permite ouvir cada intervalo e perceber como cada nota se comporta. É também a base para improvisar sobre o dominante, porque os arpejos são o material melódico mais direto sobre qualquer acorde."),
        aud ({ "G3", "B3", "D4", "F4", "D4", "B3", "G3" },
             "Arpejo de G7 subindo e descendo: ouça as quatro notas do dominante."),

        h ("Dominante e blues"),
        p (
            "O blues usa o dominante de forma particular: todos os acordes são dominantes, mesmo quando a teoria diz que não deveriam ser. No blues de Dó, os três acordes são C7, F7 e G7 — todos dominantes. Isso cria uma sonoridade própria, que não resolve da forma tradicional e por isso soa ao mesmo tempo tensa e estável. O blues é um laboratório do dominante."),
        b ("Blues de 12 compassos em Dó: C7, F7 e G7."),
        b ("Todos os acordes são dominantes, mesmo o I."),
        b ("A sonoridade do blues vem dessa contradição."),
        aud ({ "C3", "E3", "G3", "A#3", "F3", "A3", "C4", "D#4", "G3", "B3", "D4", "F4" },
             "C7 → F7 → G7: os três dominantes do blues de Dó."),

        h ("Resumo do tópico"),
        b ("O dominante V7 é o quinto grau de uma tonalidade, com sétima menor."),
        b ("Fórmula em semitons: 0, 4, 7, 10."),
        b ("O trítono entre a terça e a sétima é o que cria a tensão."),
        b ("A resolução V7 → I acontece por meio-tom (voice leading)."),
        b ("No campo maior, o V7 é o único acorde de sétima dominante natural."),
        c (
            "Nos exercícios deste tópico, toque o trítono e o acorde dominante no instrumento. O app reconhece as notas e confere se o acorde que você montou é realmente um dominante."),
    };
}

} // namespace cursomusica::content
