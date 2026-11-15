#include "Course/Content/Topics.h"

// Topic 8E — SubIIm (Módulo 8, Etapa 8).
// Fonte de verdade do texto: docs/MUSIC.md §8 (bloco E).
namespace cursomusica::content
{

std::vector<ContentItem> topic8E()
{
    return {

        p (
            "O SubIIm é a substituição do segundo grau. No II-V-I maior, o ii é um acorde de sétima menor (Dm7). Substituindo-o pelo seu equivalente menor com quinta diminuta (Dm7b5), o campo harmônico ganha a cor do modo menor, e o dominante seguinte ganha tensão. É uma substituição simples e muito eficaz, que aparece em toda a música popular."),
        p (
            "A ideia por trás do SubIIm é o empréstimo modal: pegar um acorde do campo harmônico menor e usá-lo dentro do maior. O ii menor com quinta diminuta é o segundo grau do campo menor. Ao trazê-lo para o contexto maior, criamos uma tensão que não existiria de outra forma, e preparamos o dominante para resolver com mais força."),
        c (
            "Objetivo do tópico: entender o SubIIm, como ele transforma o ii e como ele afeta o dominante que vem depois."),

        h ("O ii no campo maior e no campo menor"),
        p (
            "No campo harmônico maior de Dó, o segundo grau é Dm7 (Ré, Fá, Lá, Dó): um acorde de sétima menor com quinta justa. No campo harmônico menor natural de Dó, o segundo grau é Dm7b5 (Ré, Fá, Lá bemol, Dó): um acorde de sétima menor com quinta diminuta. A diferença está apenas na quinta: Lá vira Lá bemol."),
        b ("Campo maior: ii = Dm7 (Ré, Fá, Lá, Dó)."),
        b ("Campo menor: ii = Dm7b5 (Ré, Fá, Lá bemol, Dó)."),
        b ("A quinta diminuta (Lá bemol) é o que muda a cor."),
        img ("m8_subiim", "O ii vira SubIIm: o Lá bemol acrescenta a cor do menor e prepara o G7."),

        h ("O efeito do SubIIm no dominante"),
        p (
            "Quando o ii é menor com quinta diminuta, o dominante seguinte costuma ganhar a nona menor (b9). Por que? Porque o Lá bemol do Dm7b5 é justamente a nona menor do G7. O ouvido já ouviu o Lá bemol no ii, então o G7b9 parece a continuação natural. Assim, o SubIIm prepara o dominante alterado."),
        b ("Dm7b5 → G7b9 → Cm: o Lá bemol do ii reaparece como b9 do V7."),
        b ("A resolução soa mais tensa e mais coerente."),
        b ("O SubIIm e o dominante b9 andam juntos."),
        tbl ({ "Progressão", "Acordes", "Cor" }, {
            { "II-V-I maior", "Dm7 – G7 – CM7", "luminosa" },
            { "II-V-I com SubIIm", "Dm7b5 – G7b9 – Cm7", "sombria" },
            { "II-V-I maior com SubIIm", "Dm7b5 – G7b9 – CM7", "mista" },
        }),
        aud ({ "D3", "F3", "G#3", "C4" }, "Dm7b5: ouça o Lá bemol (a quinta diminuta) que dá a cor menor."),

        h ("O SubIIm no II-V-I menor"),
        p (
            "No II-V-I menor, o SubIIm não é uma substituição: é o acorde natural. Em Cm, a progressão é Dm7b5 → G7 → Cm7. Aqui o ii já é meio-diminuto desde o início, porque o campo menor exige essa qualidade. O SubIIm do campo maior é justamente trazer essa sonoridade para dentro do maior."),
        b ("II-V-I menor natural: Dm7b5 → G7 → Cm7."),
        b ("O SubIIm no maior imita essa sonoridade."),
        b ("A diferença está no acorde de chegada: Cm7 (menor) ou CM7 (maior)."),
        c (
            "Regra prática: sempre que você quiser uma cor menor dentro de um contexto maior, use o SubIIm no lugar do ii."),

        h ("O iv menor"),
        p (
            "Há ainda outra forma de empréstimo menor: transformar o IV maior em iv menor. Em Dó, o IV é FM7; o iv menor é Fm7. Essa troca cria um movimento cromático (Lá vira Lá bemol) e prepara o I com uma cor melancólica. O iv menor é muito usado em finais de música, criando um efeito de \"suspiro\" antes da resolução."),
        b ("IV maior: FM7 (Fá, Lá, Dó, Mi)."),
        b ("iv menor: Fm7 (Fá, Lá bemol, Dó, Mi bemol)."),
        b ("O iv menor prepara o I com uma cor de saudade."),
        aud ({ "F3", "G#3", "C4", "D#4" }, "Fm7, o iv menor de Dó: a cor melancólica antes da resolução."),

        h ("SubIIm e SubV7 juntos"),
        p (
            "As duas substituições podem ser combinadas. Em vez de Dm7 → G7 → C, temos Dm7b5 → Db7 → C. O baixo desce Ré → Réb → Dó, e a cor é a mais suave possível. Essa combinação é a base de muitas reharmonizações de bossa nova e de baladas de jazz."),
        b ("Dm7b5 → Db7 → CM7: SubIIm + SubV7."),
        b ("O baixo desce cromaticamente do ii até o I."),
        b ("O resultado é a resolução mais suave do vocabulário harmônico."),
        tbl ({ "Progressão", "Acordes", "Baixo" }, {
            { "II-V-I", "Dm7 – G7 – CM7", "Ré – Sol – Dó" },
            { "SubIIm + V", "Dm7b5 – G7b9 – CM7", "Ré – Sol – Dó" },
            { "SubIIm + SubV7", "Dm7b5 – Db7 – CM7", "Ré – Réb – Dó" },
        }),

        h ("Como identificar de ouvido"),
        p (
            "O SubIIm soa mais escuro do que o ii maior. Compare Dm7 e Dm7b5: o primeiro é suave, o segundo tem um atrito que já anuncia tensão. Depois de ouvir o SubIIm, o ouvido espera um dominante mais tenso. Treine reconhecer essa progressão: ii meio-diminuto seguido de dominante b9."),
        b ("Ouça o ii: ele tem quinta justa ou diminuta?"),
        b ("Se for diminuta, o dominante provavelmente terá b9."),
        b ("A resolução será mais tensa que o normal."),
        aud ({ "D3", "F3", "A3", "C4", "D3", "F3", "G#3", "C4" },
             "Dm7 e depois Dm7b5: compare o ii maior com o SubIIm."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é chamar de SubIIm o ii normal. O SubIIm é especificamente o ii menor com quinta diminuta. Outro erro é esquecer o bemol da quinta: Dm7b5 tem Lá bemol, não Lá natural. Sem esse bemol, o acorde deixa de ter a cor menor."),
        b ("SubIIm tem quinta diminuta: não esqueça o bemol."),
        b ("Não confunda com o ii normal do campo maior."),
        b ("O SubIIm prepara o dominante b9, então use os dois juntos."),
        c (
            "Dica: escreva o acorde completo (Dm7b5) para não esquecer a quinta diminuta."),

        h ("Aplicação prática"),
        p (
            "Pratique a progressão Dm7b5 → G7b9 → CM7 e compare com a versão sem substituição. Depois experimente Dm7b5 → Db7 → CM7. No instrumento, o acorde meio-diminuto tem uma digitação própria; use o app para conferir se as notas que você toca formam o acorde certo."),
        b ("Toque Dm7 → G7 → CM7 e depois Dm7b5 → G7b9 → CM7."),
        b ("Toque o SubIIm como arpejo."),
        b ("Combine com o SubV7: Dm7b5 → Db7 → CM7."),
        part ("m8_partitura_ii_v_i_menor",
              { "D3", "F3", "G#3", "C4", "G3", "B3", "D4", "F4", "C4", "Eb4", "G4" },
              "Partitura de um II-V-I menor (Dm7b5 – G7 – Cm7): o SubIIm em ação. Ouça a resolução sombria."),

        h ("SubIIm em outras tonalidades"),
        p (
            "O SubIIm é o segundo grau menor com quinta diminuta. Em qualquer tonalidade, ele é construído sobre o segundo grau, com a quinta rebaixada. Em Sol maior, o SubIIm é Am7b5; em Fá maior, é Gm7b5; em Si bemol maior, é Cm7b5. O processo é sempre o mesmo: tome o ii, rebaixe a quinta e você tem o SubIIm."),
        b ("Em Dó maior: Dm7b5."),
        b ("Em Sol maior: Am7b5."),
        b ("Em Fá maior: Gm7b5."),
        b ("Em Si bemol maior: Cm7b5."),
        tbl ({ "Tonalidade", "II (maior)", "SubIIm" }, {
            { "Dó maior", "Dm7", "Dm7b5" },
            { "Sol maior", "Am7", "Am7b5" },
            { "Fá maior", "Gm7", "Gm7b5" },
            { "Si bemol maior", "Cm7", "Cm7b5" },
        }),

        h ("SubIIm na guitarra"),
        p (
            "No instrumento, o acorde meio-diminuto tem uma digitação própria, diferente da do acorde menor comum. Vale a pena aprender uma forma de acorde meio-diminuto e deslocá-la pelo braço, porque ela aparece em todo lugar no campo menor. O app ajuda: toque o acorde e ele confere se as notas formam um meio-diminuto (fundamental, terça menor, quinta diminuta e sétima menor)."),
        b ("Aprenda uma forma de acorde meio-diminuto e desloque-a."),
        b ("Confira a quinta diminuta: é o que define o SubIIm."),
        b ("Toque o arpejo para ouvir cada nota."),
        aud ({ "D3", "F3", "G#3", "C4", "G3", "B3", "D4", "F4", "C3", "Eb3", "G3" },
             "Dm7b5 → G7 → Cm7: o SubIIm levando ao dominante e à tônica menor."),

        h ("O SubIIm no contexto modal"),
        p (
            "O SubIIm também aparece no contexto modal. Quando a música está num tom menor, o ii é naturalmente meio-diminuto. Quando está num tom maior mas quer uma cor menor, o SubIIm traz essa sonoridade. É uma ponte entre os dois mundos, e por isso aparece tanto em baladas quanto em músicas modais. Reconhecer o meio-diminuto é reconhecer a cor menor dentro do maior."),
        b ("Tom menor: o ii é meio-diminuto naturalmente."),
        b ("Tom maior: o SubIIm traz a cor menor."),
        b ("O meio-diminuto é a ponte entre os dois mundos."),

        h ("O SubIIm e a escala"),
        p (
            "Sobre o SubIIm, a escala natural é a lócria, o sétimo modo da escala maior. Ela contém a fundamental, a terça menor, a quinta diminuta e a sétima menor, mais as tensões. Improvisar sobre o SubIIm pede atenção à quinta diminuta, que é a nota característica. Usar a escala lócria mantém a coerência entre o acorde e a melodia."),
        b ("Escala lócria sobre Dm7b5: D, Eb, F, G, Ab, Bb, C."),
        b ("A quinta diminuta (Ab) é a nota característica."),
        b ("A escala casa com o acorde e prepara o dominante."),
        aud ({ "D3", "Eb3", "F3", "G3", "G#3", "A#3", "C4" },
             "Escala lócria sobre Dm7b5: a escala que acompanha o SubIIm."),

        h ("SubIIm e a cor da resolução"),
        p (
            "O SubIIm muda a cor da resolução de duas formas. Primeiro, o ii já soa menor, o que prepara o ouvido para uma chegada menor ou para uma tensão extra. Segundo, o dominante seguinte costuma receber a nona menor, que casa com o Lá bemol do ii. O resultado é uma resolução mais rica, com mais notas cromáticas, sem perder a função."),
        b ("O ii menor já anuncia a cor sombria."),
        b ("O dominante ganha b9 para casar com o ii."),
        b ("A resolução final pode ser maior (CM7) ou menor (Cm7)."),
        tbl ({ "Versão", "Acordes", "Cor final" }, {
            { "Simples", "Dm7 – G7 – CM7", "luminosa" },
            { "Com SubIIm", "Dm7b5 – G7b9 – CM7", "sombria, mas maior" },
            { "Com SubIIm e SubV7", "Dm7b5 – Db7 – CM7", "suave e cromática" },
        }),

        h ("SubIIm e o dominante b9"),
        p (
            "O casamento entre o SubIIm e o dominante b9 é uma das relações mais elegantes da harmonia. O Lá bemol que aparece na quinta do Dm7b5 é exatamente a nona menor do G7. Assim, quando você toca Dm7b5 → G7b9, o ouvido reconhece a mesma nota nos dois acordes, o que cria uma sensação de continuidade e de lógica. É por isso que os dois andam juntos."),
        b ("Dm7b5 tem Lá bemol como quinta diminuta."),
        b ("G7b9 tem Lá bemol como nona menor."),
        b ("A mesma nota liga os dois acordes: som de coerência."),
        aud ({ "D3", "F3", "G#3", "C4", "G3", "B3", "D4", "F4", "G#4" },
             "Dm7b5 → G7b9: o Lá bemol aparece nos dois acordes, criando continuidade."),
        c (
            "Sempre que usar o SubIIm, experimente o dominante com b9. A ligação entre os dois é o que dá o som coeso."),

        h ("SubIIm e a substituição do dominante"),
        p (
            "O SubIIm costuma vir acompanhado de outro SubV7, formando a cadência Dm7b5 → Db7 → CM7. Aqui o ii menor e o dominante substituto aparecem juntos, criando uma resolução duplamente cromática. Essa combinação é muito usada no jazz, porque oferece uma alternativa suave ao II-V-I tradicional sem perder a função. É a substituição mais completa que você aprendeu neste módulo."),
        b ("Cadência completa: Dm7b5 → Db7 → CM7."),
        b ("Dois movimentos cromáticos até a tônica."),
        b ("Alternativa suave ao II-V-I tradicional."),
        c (
            "Compare Dm7 → G7 → CM7, Dm7b5 → G7 → CM7 e Dm7b5 → Db7 → CM7. Cada versão tem uma cor diferente; o ouvido aprende a escolher."),

        h ("Resumo do tópico"),
        b ("SubIIm é o ii menor com quinta diminuta (Dm7b5)."),
        b ("Ele traz a cor do campo menor para dentro do maior."),
        b ("Prepara o dominante com nona menor (b9)."),
        b ("No II-V-I menor, ele é o acorde natural."),
        b ("Combinado com o SubV7, dá a resolução mais suave."),
        c (
            "Nos exercícios deste tópico, toque o SubIIm e confira com o app. Ele reconhece as notas e verifica se o acorde montado corresponde ao pedido."),
    };
}

} // namespace cursomusica::content
