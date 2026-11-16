#include "Course/Content/Topics.h"

// Topic 9E — Acorde m7(#5) (Modulo 9, Etapa 9).
// Fonte de verdade do texto: docs/MUSIC.md (bloco E da Etapa 9).
namespace cursomusica::content
{

std::vector<ContentItem> topic9E()
{
    return {

        p (
            "O acorde menor com sétima e quinta aumentada, escrito m7(#5), é uma das sonoridades mais interessantes da harmonia moderna. Ele soa suspenso, misterioso e um pouco ambíguo — nem maior, nem menor, nem dominante. Neste tópico você aprende como ele é construído, de onde ele vem e como usá-lo."),
        p (
            "Você já sabe montar o acorde menor com sétima (m7) é o acorde aumentado. O m7(#5) é a combinação dos dois: tem a terça menor e a sétima menor do m7, mas a quinta é aumentada em vez de justa. Esse único semitom de diferença muda completamente a cor."),

        h ("Como o m7(#5) e construído"),
        p (
            "Tomando Do como tônica, o m7(#5) tem as notas Do, Mib, Sol# e Sib. Os intervalos em semitons são 0, 3, 8 e 10: tônica, terça menor, quinta aumentada e sétima menor. Compare com o m7 comum, que tem a quinta justa (7 semitons): Do, Mib, Sol e Sib."),
        tbl ({ "Acorde", "Notas sobre Do", "Intervalos (semitons)" }, {
            { "Cm7", "Do - Mib - Sol - Sib", "0 - 3 - 7 - 10" },
            { "Cm7(#5)", "Do - Mib - Sol# - Sib", "0 - 3 - 8 - 10" },
            { "Cm7(b5)", "Do - Mib - Solb - Sib", "0 - 3 - 6 - 10" },
        }),
        c (
            "A diferença entre m7, m7(#5) e m7(b5) está toda na quinta. Justa, aumentada e diminuta: três cores diferentes a partir do mesmo esqueleto."),
        img ("m9_m7s5", "O acorde m7(#5): a quinta aumentada muda a cor do acorde menor com sétima."),
        aud ({ "C4", "D#4", "G4", "A#4" }, "Cm7: quinta justa. Som menor, estável."),
        aud ({ "C4", "D#4", "G#4", "A#4" }, "Cm7(#5): quinta aumentada. Som suspenso, sem repouso."),
        aud ({ "C4", "D#4", "F#4", "A#4" }, "Cm7(b5): quinta diminuta. Som instável, quase diminuto."),
        part ("m9_partitura_m7s5", { "C4", "D#4", "G#4", "A#4", "C5" },
              "Partitura do arpejo de Cm7(#5): Do-Mib-Sol#-Sib. Ouça a quinta aumentada."),

        h ("De onde o m7(#5) vem"),
        p (
            "O m7(#5) não é um acorde diatônico do campo harmônico maior: ele nasce da alteração da quinta do acorde menor com sétima. Subindo a quinta justa (Sol) meio tom, chega-se à quinta aumentada (Sol#) e o m7 vira m7(#5). É uma alteração de cor, não uma troca de função, e por isso o acorde costuma aparecer como passagem ou como sonoridade suspensa."),
        p (
            "Como não pertence ao campo de nenhuma escala maior, o m7(#5) se apoia na sua leitura enarmônica para ganhar uma escala. É por isso que ele é tão usado em passagens modais e em música de fusão: a sua origem é uma alteração, e a sua cor é suspensa."),
        b ("Não é diatônico do campo maior: nasce da alteração da quinta do m7."),
        b ("A quinta justa sobe meio tom e vira quinta aumentada."),
        b ("É comum em passagens modais e na fusão."),

        h ("A enarmonia do m7(#5)"),
        p (
            "Como a quinta aumentada de Do e Sol# (enarmonicamente Lá bemol), o m7(#5) tem uma relação enarmônica curiosa. Cm7(#5) tem as notas Do, Mib, Sol# (Lá bemol) e Sib — que são as mesmas de Ab(add9)/C, ou seja, um Lá bemol com nona sobre baixo de Do. Isso significa que o m7(#5) pode ser lido como uma inversão de outro acorde, o que dá ao arranjador duas formas de escrever a mesma sonoridade."),
        b ("Cm7(#5) = Ab(add9)/C (mesmas notas, outra grafia)."),
        b ("A ambiguidade é uma característica, não um erro."),
        b ("Escolha a grafia que melhor descreve a função do acorde."),
        c (
            "Se o acorde funciona como menor, escreva m7(#5); se funciona como uma inversão de Lá bemol, escreva Ab(add9)/C. O som é o mesmo; a leitura muda."),

        h ("Como tocar o m7(#5) no braço"),
        p (
            "Na guitarra, o m7(#5) tem formas ágeis. A quinta aumentada costuma ficar na corda aguda, onde a tensão soa mais clara. Uma forma comum usa quatro notas em cordas vizinhas, com a tônica no baixo. Explore as posições até encontrar a que melhor se encaixa no seu fraseado."),
        b ("Toque a tônica no baixo e a quinta aumentada na voz aguda."),
        b ("Use quatro notas em cordas vizinhas para um som limpo."),
        b ("Desloque a forma para outras tônicas mantendo o desenho."),
        c (
            "Nos exercícios, toque o acorde e o app vai reconhecer as notas. Qualquer posição do braço vale; o que importa é o conjunto de classes de altura."),

        h ("Ouvindo o m7(#5)"),
        p (
            "O som do m7(#5) é fácil de reconhecer depois que você o associa a uma sensação. Ele não repousa: a quinta aumentada cria uma instabilidade que parece flutuar. Diferente do m7, que é estável e cantável, o m7(#5) parece suspenso no ar, esperando resolver."),
        b ("Som suspenso, sem repouso claro."),
        b ("Mais misterioso que o m7 comum."),
        b ("Pede resolução, mas não de forma tão direta quanto o dominante."),
        aud ({ "C4", "D#4", "G#4", "A#4", "D#5" },
             "Cm7(#5) com a quinta aumentada no topo: a tensão fica ainda mais evidente."),

        h ("Usando o m7(#5) na prática"),
        p (
            "Comece tocando o m7 e o m7(#5) lado a lado, para ouvir a diferença de um único semitom. Depois, use o m7(#5) como acorde de passagem entre dois acordes menores. Por fim, explore a sua leitura enarmônica, tocando-o como uma inversão de acorde maior com nona."),
        b ("Compare m7 e m7(#5) na mesma tônica."),
        b ("Use-o como acorde de passagem entre acordes menores."),
        b ("Experimente a leitura como inversão de acorde maior com nona."),
        aud ({ "C4", "D#4", "G4", "A#4", "C4", "D#4", "G#4", "A#4" },
             "Cm7 e depois Cm7(#5): um semitom que muda toda a cor."),

        h ("Erros comuns"),
        p (
            "O erro mais frequente é tocar a quinta justa por hábito, transformando o acorde num m7 comum. Outro erro é não ouvir a tensão da quinta aumentada, o que faz o acorde passar despercebido."),
        b ("Tocar a quinta justa em vez da aumentada: vira m7."),
        b ("Não explorar a leitura enarmônica do acorde."),
        b ("Usar o m7(#5) como repouso: ele não resolve a frase."),
        c (
            "Se o acorde soar estável demais, verifique a quinta. A quinta aumentada é o que da identidade ao m7(#5)."),

        h ("O m7(#5) na improvisação"),
        p (
            "Para quem improvisa, o m7(#5) pede uma escala que contenha a sua quinta aumentada. A forma mais clara de chegar a ela é pela leitura enarmônica: como Cm7(#5) soa igual a Ab(add9)/C, a escala natural é o modo lídio de Lá bemol (Ab, Sib, Dó, Ré, Mib, Fá, Sol). Essa escala contém todas as notas do acorde — inclusive a quinta aumentada, que aparece como o Lá bemol do modo. É um recurso comum na fusão e no jazz moderno."),
        b ("Sobre o m7(#5), use a escala lídia do acorde uma terça maior abaixo."),
        b ("A escala contém a quinta aumentada do acorde (enarmônica)."),
        b ("O resultado soa moderno e fluido."),

        h ("O m7(#5) e a sonoridade modal"),
        p (
            "O m7(#5) soa modal porque a quinta aumentada enfraquece a direção tonal: o acorde não tem o empurrão de um dominante nem o repouso de um menor comum. A sua cor suspensa se apoia na leitura enarmônica — um acorde maior com nona sobre o baixo (Ab(add9)/C) — e a escala que descreve essa sonoridade é a lídia. Por isso ele flutua, sem a direção forte dos acordes tonais."),
        b ("O m7(#5) soa modal."),
        b ("A quinta aumentada enfraquece a direção tonal."),
        b ("O som flutua, sem direção tonal forte."),
        aud ({ "G#3", "A#3", "C4", "D4", "D#4", "F4", "G4" },
             "A escala lídia de Lá bemol: a quarta aumentada (Ré) é a marca da sonoridade."),

        h ("Combinando o m7(#5) com outros acordes"),
        p (
            "Na prática, o m7(#5) raramente aparece sozinho. Ele costuma ser usado como acorde de passagem entre dois acordes menores, ou como substituto colorido de um acorde menor comum. Também aparece em progressões modais, onde a harmonia fica suspensa por vários compassos sem resolver. Saber encaixa-lo na progressão é o que faz a sonoridade funcionar."),
        b ("Acorde de passagem entre acordes menores."),
        b ("Substituto colorido de um menor comum."),
        b ("Acorde suspenso em progressões modais."),

        h ("O m7(#5) e a escala menor melódica"),
        p (
            "A escala que contém as quatro notas do m7(#5) é a menor melódica de outra tônica, não a do próprio acorde. A menor melódica de Dó (Dó-Ré-Mib-Fá-Sol-Lá-Si) tem o primeiro grau m(maj7) = Do-Mib-Sol-Si, e não contém a quinta aumentada Sol#. Já a menor melódica de Dó# (Dó#-Ré#-Mi-Fá#-Sol#-Lá#-Dó) contém, sobre o baixo de Dó, exatamente Mib, Sol# e Sib — as notas do Cm7(#5). Por isso a escala que serve ao acorde é a menor melódica de Dó# (ou, enarmonicamente, de Ré bemol)."),
        b ("A menor melódica tem a sexta e a sétima elevadas."),
        b ("O acorde de sétima do primeiro grau da menor melódica de Dó é o m(maj7), não o m7(#5)."),
        b ("A menor melódica que contém a quinta aumentada do Cm7(#5) é a de Dó# (Ré bemol)."),

        h ("O m7(#5) na partitura"),
        p (
            "Na partitura, o m7(#5) mostra a terça menor e a sétima menor, com a quinta elevada em relação ao acorde menor comum. Ler essa quinta aumentada é o que distingue o m7(#5) do m7. Quando você vir um acorde menor com sétima e a quinta com sinal de sustenido, está diante de um m7(#5)."),
        b ("A quinta aparece aumentada na partitura."),
        b ("A terça menor e a sétima menor permanecem."),
        b ("É a quinta aumentada que dá identidade ao acorde."),

        h ("Comparando o m7(#5) com outros acordes menores"),
        p (
            "Vale colocar os três acordes menores com sétima lado a lado: o m7, o m7(#5) e o m7(b5). Os três têm a terça menor e a sétima menor; o que muda é a quinta. Justa no m7, aumentada no m7(#5) e diminuta no m7(b5). Ouvir os três em sequência fixa a diferença de cor de cada um."),
        tbl ({ "Acorde", "Quinta", "Intervalos (semitons)", "Caráter" }, {
            { "m7", "justa", "0 - 3 - 7 - 10", "estável" },
            { "m7(#5)", "aumentada", "0 - 3 - 8 - 10", "suspenso" },
            { "m7(b5)", "diminuta", "0 - 3 - 6 - 10", "instável" },
        }),
        c (
            "Um único semitom na quinta separa os três acordes. Ouvir a diferença é o primeiro passo para usar cada um no lugar certo."),
        aud ({ "C4", "D#4", "G4", "A#4", "C4", "D#4", "G#4", "A#4", "C4", "D#4", "F#4", "A#4" },
             "Cm7, Cm7(#5) e Cm7(b5): a quinta muda, a cor muda por completo."),

        h ("O m7(#5) como acorde de passagem"),
        p (
            "Na prática, o m7(#5) costuma aparecer como acorde de passagem entre dois acordes de um mesmo campo. Ele liga o acorde menor ao seu relativo, criando um cromatismo na quinta. Em arranjos de bossa e de jazz, esse movimento de meio tom na quinta é um dos recursos mais elegantes para conduzir as vozes sem saltos."),
        b ("Passagem entre dois acordes do mesmo campo."),
        b ("O cromatismo na quinta conduz as vozes."),
        b ("Recurso comum em bossa e jazz."),
        aud ({ "C4", "D#4", "G4", "A#4", "C4", "D#4", "G#4", "A#4", "F4", "A4", "C5" },
             "Cm7 passando por Cm7(#5) até Fá: a quinta conduz o movimento."),

        h ("Erros comuns ao estudar o m7(#5)"),
        p (
            "Além de tocar a quinta justa por hábito, o aluno costuma tratar o m7(#5) como um acorde de repouso, quando ele é, na verdade, um acorde suspenso. Outro erro é não ouvir a tensão da quinta aumentada, o que faz o acorde passar despercebido. Ouvir com atenção é o que separa o uso consciente do acidental."),
        b ("Tocar a quinta justa por hábito."),
        b ("Tratar o m7(#5) como acorde de repouso."),
        b ("Não ouvir a tensão da quinta aumentada."),

        h ("Resumo do tópico"),
        b ("m7(#5) = tônica, terça menor, quinta aumentada e sétima menor (0-3-8-10)."),
        b ("Difere do m7 apenas na quinta, mas a cor muda por completo."),
        b ("Não é diatônico do campo maior: nasce da alteração da quinta do m7."),
        b ("Tem leitura enarmônica: é uma inversão de acorde maior com nona."),
        b ("Soa suspenso e pede resolução."),
        c (
            "Nos exercícios, toque o m7(#5) e o m7 para comparar. O app confere as classes de altura reconhecidas."),
    };
}

} // namespace cursomusica::content
