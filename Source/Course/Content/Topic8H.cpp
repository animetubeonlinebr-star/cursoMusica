#include "Course/Content/Topics.h"

// Topic 8H — Dilatação do campo harmônico menor (Módulo 8, Etapa 8).
// Fonte de verdade do texto: .agents/agents/mc-modulo-8.md (Etapa 8, tópico H).
namespace cursomusica::content
{

std::vector<ContentItem> topic8H()
{
    return {

        p (
            "O campo harmônico menor é mais complexo do que o maior, porque existem três escalas menores diferentes: a natural, a harmônica e a melódica. Cada uma produz um conjunto de acordes. O campo menor dilatado é a união desses três conjuntos, e é isso que explica a riqueza do som menor — a presença simultânea do dominante (V7) e do bVII, por exemplo."),
        p (
            "Se você entender a dilatação do campo menor, entenderá por que a música em tom menor soa tão expressiva. O menor não tem uma única forma: ele alterna entre a suavidade da natural, a tensão da harmônica e a fluência da melódica. Este tópico organiza esse vocabulário."),
        c (
            "Objetivo do tópico: compreender como o campo menor se dilata pelas três escalas e como seus acordes se organizam em funções."),

        h ("As três escalas menores"),
        p (
            "A escala menor natural tem as notas da relativa maior, mas começando na tônica menor: em Dó menor, são Dó, Ré, Mi bemol, Fá, Sol, Lá bemol, Si bemol. A escala menor harmônica sobe o sétimo grau meio-tom (Si natural), criando a sensível. A escala menor melódica sobe também o sexto grau (Lá natural), suavizando o salto. Cada uma produz acordes diferentes."),
        b ("Menor natural: sem sensível, sem dominante."),
        b ("Menor harmônica: com sensível (7º grau elevado), gera o V7."),
        b ("Menor melódica: com 6º e 7º graus elevados, gera acordes de cor."),
        img ("m8_dilatacao_menor", "O campo menor dilatado: a união dos acordes das escalas natural, harmônica e melódica."),

        h ("Os acordes do campo menor natural"),
        p (
            "O campo menor natural de Dó produz: Cm7 (i), Dm7b5 (ii), Eb7M (bIII), Fm7 (iv), Gm7 (v), Ab7M (bVI) e Bb7 (bVII). Repare que o acorde do quinto grau é Gm7, um acorde menor — ele não tem a sensível (Si natural) e por isso não funciona como dominante. É a ausência do dominante que dá ao menor natural o seu caráter estático e modal."),
        tbl ({ "Grau", "Acorde em Dó menor", "Notas" }, {
            { "i", "Cm7", "C, Eb, G, Bb" },
            { "ii", "Dm7b5", "D, F, Ab, C" },
            { "bIII", "Eb7M", "Eb, G, Bb, D" },
            { "iv", "Fm7", "F, Ab, C, Eb" },
            { "v", "Gm7", "G, Bb, D, F" },
            { "bVI", "Ab7M", "Ab, C, Eb, G" },
            { "bVII", "Bb7", "Bb, D, F, Ab" },
        }),

        h ("A dilatação pela menor harmônica"),
        p (
            "Quando a escala menor harmônica entra, o sétimo grau sobe (Si bemol vira Si natural) e o campo se transforma. O Gm7 vira G7, o dominante que faltava. O acorde de bIII (Eb7M) pode virar Eb7M#5, e o bVII (Bb7) pode virar Bdim7. É essa dilatação que permite a cadência V7 → i no menor, a mais importante do campo menor."),
        b ("Gm7 (natural) vira G7 (harmônica): o dominante aparece."),
        b ("G7 → Cm7: a cadência fundamental do menor."),
        b ("O Si natural é a sensível que puxa para a tônica."),
        aud ({ "G3", "B3", "D4", "F4", "C3", "Eb3", "G3" },
             "G7 → Cm: o dominante do menor harmônico resolvendo na tônica menor."),

        h ("A dilatação pela menor melódica"),
        p (
            "A escala menor melódica sobe também o sexto grau (Lá bemol vira Lá natural). Isso muda vários acordes: o Dm7b5 vira Dm7, o Fm7 vira F7 e o Ab7M vira Am7b5 — o sexto grau naturalizado (Lá) forma um acorde meio-diminuto, não um maior. Esses acordes acrescentam cores novas ao campo menor, e são muito usados no jazz. A menor melódica é a fonte de grande parte das sonoridades sofisticadas do menor."),
        b ("Dm7b5 (natural) vira Dm7 (melódica)."),
        b ("Fm7 (natural) vira F7 (melódica): um dominante do bIII."),
        b ("A menor melódica gera os dominantes internos do campo menor."),
        tbl ({ "Grau", "Natural", "Harmônica", "Melódica" }, {
            { "i", "Cm7", "Cm7M", "Cm7M" },
            { "ii", "Dm7b5", "Dm7b5", "Dm7" },
            { "bIII", "Eb7M", "Eb7M#5", "Eb7M#5" },
            { "iv", "Fm7", "Fm7", "F7" },
            { "v", "Gm7", "G7", "G7" },
            { "bVI", "Ab7M", "Ab7M", "Am7b5" },
            { "bVII", "Bb7", "Bdim7", "Bm7b5" },
        }),

        h ("O mapa completo do campo menor"),
        p (
            "Reunindo as três escalas, o campo menor dilatado de Dó contém: Cm7, Cm7M, Cm6; Dm7b5, Dm7; Eb7M, Eb7M#5; Fm7, F7; Gm7, G7; Ab7M, Am7b5; Bb7, Bdim7, Bm7b5. Esse é o vocabulário completo do menor, e cada acorde exerce uma função. A tônica admite Cm7, Cm6 e Cm7M; a subdominante admite Fm7, F7, Dm7b5 e Dm7; o dominante admite G7, Gm7 e Bdim7."),
        tbl ({ "Função", "Acordes", "Origem" }, {
            { "Tônica", "Cm7, Cm6, Cm7M", "natural, melódica" },
            { "Subdominante", "Fm7, F7, Dm7b5, Dm7", "natural, melódica" },
            { "Dominante", "G7, Gm7, Bdim7", "harmônica, natural" },
            { "Cor", "Eb7M, Ab7M, Bb7", "natural" },
            { "Cor", "Eb7M#5, Am7b5", "harmônica, melódica" },
        }),

        h ("A cadência no campo menor"),
        p (
            "A cadência mais importante do campo menor é o II-V-I menor: Dm7b5 → G7 → Cm7. O ii é meio-diminuto (do campo natural), o V é dominante (do campo harmônico) e o i é menor. Essa mistura das escalas dentro de uma única progressão é o que define o som menor. É a progressão que você mais ouvirá em músicas menores."),
        b ("II-V-I menor: Dm7b5 → G7 → Cm7."),
        b ("O ii vem da escala natural; o V, da harmônica."),
        b ("A mistura das escalas é a assinatura do campo menor."),
        aud ({ "D3", "F3", "G#3", "C4", "G3", "B3", "D4", "F4", "C3", "Eb3", "G3" },
             "II-V-I menor completo: Dm7b5 → G7 → Cm7. Ouça as três escalas convivendo."),

        h ("Como usar o mapa menor"),
        p (
            "Assim como no maior, o mapa menor serve para escolher. Diante de um Cm7, você pode usar Cm6 ou Cm7M para variar a cor. Diante de um dominante, você pode usar G7, G7b9 ou G7alt. A dilatação do menor é especialmente rica porque permite misturar o estático (natural) com o resolutivo (harmônica) na mesma frase."),
        b ("Escolha a cor da tônica: Cm7, Cm6 ou Cm7M."),
        b ("Escolha o dominante: G7, G7b9 ou G7alt."),
        b ("Misture as escalas para criar movimento."),
        c (
            "Regra prática: no menor, o dominante é sempre um empréstimo da harmônica. Sem ele, a música não fecha."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é usar apenas a escala natural, o que deixa a música sem resolução. Outro erro é não perceber que o campo menor é a união de três escalas, e tentar achar um único conjunto de sete acordes. O menor não tem um campo único: tem três, e a dilatação é justamente essa união."),
        b ("Não esqueça o dominante (harmônica): sem ele não há cadência."),
        b ("O campo menor é a união de três escalas, não uma só."),
        b ("Escolha a cor com intenção, não ao acaso."),
        c (
            "Dica: escreva qual escala cada acorde vem. Isso esclarece a função e evita confusão."),

        h ("Aplicação prática"),
        p (
            "Pratique a progressão Dm7b5 → G7 → Cm7 e depois varie o dominante (G7b9, G7alt) e a tônica (Cm7, Cm6). Toque também a versão natural, com Gm7, e sinta a diferença: sem o dominante, a música não fecha. No instrumento, use o app para conferir se os acordes montados estão corretos."),
        b ("Toque o II-V-I menor e depois varie o dominante."),
        b ("Toque a versão natural (Gm7) e compare."),
        b ("Varie a cor da tônica: Cm7, Cm6, Cm7M."),
        part ("m8_partitura_ii_v_i_menor",
              { "D3", "F3", "G#3", "C4", "G3", "B3", "D4", "F4", "C3", "Eb3", "G3" },
              "Partitura do II-V-I menor dilatado (Dm7b5 – G7 – Cm7). Ouça o que está escrito."),

        h ("A dilatação do menor em outras tonalidades"),
        p (
            "A dilatação do campo menor vale para qualquer tonalidade. Em Lá menor, o campo natural é Am7, Bm7b5, C7M, Dm7, Em7, F7M, G7; a harmônica acrescenta E7 (o dominante); a melódica acrescenta Bm7, D7 e F#m7b5 — o sexto grau naturalizado (Fá sustenido) forma um acorde meio-diminuto. O processo é o mesmo em qualquer tom: reúna as três escalas e você tem o campo menor completo."),
        b ("Em Dó menor: Cm7, Dm7b5, Eb7M, Fm7, Gm7, Ab7M, Bb7 (natural)."),
        b ("Harmônica acrescenta: G7 (dominante)."),
        b ("Melódica acrescenta: Dm7, F7, Am7b5."),
        tbl ({ "Tonalidade", "i", "ii", "V7" }, {
            { "Dó menor", "Cm7", "Dm7b5", "G7" },
            { "Lá menor", "Am7", "Bm7b5", "E7" },
            { "Sol menor", "Gm7", "Am7b5", "D7" },
            { "Ré menor", "Dm7", "Em7b5", "A7" },
        }),

        h ("A dilatação do menor na guitarra"),
        p (
            "No instrumento, o campo menor dilatado oferece muitas opções. Diante de um Cm7, você pode tocar Cm6, Cm7M ou Cm7; diante do dominante, G7, G7b9 ou G7alt. Cada opção tem a sua digitação, e conhecer várias amplia o vocabulário. Praticar as variações do menor em várias tonalidades desenvolve a fluência no instrumento."),
        b ("Varie a tônica: Cm7, Cm6, Cm7M."),
        b ("Varie o dominante: G7, G7b9, G7alt."),
        b ("Pratique o II-V-I menor em várias tonalidades."),
        aud ({ "C3", "Eb3", "G3", "A3", "C3", "Eb3", "G3", "B3", "C3", "Eb3", "G3", "Bb3", "G3", "Eb3", "C3" },
             "Cm6, Cm7M e Cm7: as variações da tônica menor. Ouça as diferentes cores."),

        h ("A escala para improvisar no menor"),
        p (
            "Sobre o campo menor, a escala de improvisação acompanha a harmonia. Sobre o Cm7, use a escala dórica de Dó; sobre o Dm7b5, a lócria; sobre o G7, a mixolídia (ou a alterada, se o dominante estiver alterado). A escolha da escala é o que mantém a coerência entre o que você toca e o que a harmonia pede."),
        b ("Cm7: escala dórica de Dó."),
        b ("Dm7b5: escala lócria de Ré."),
        b ("G7: escala mixolídia ou alterada."),
        c (
            "Regra prática: no menor, a escala do ii é a lócria, a do V é a mixolídia (ou alterada) e a do i é a dórica."),

        h ("O menor e o empréstimo modal"),
        p (
            "O campo menor está intimamente ligado ao empréstimo modal. Quando uma música em Dó maior usa um acorde de Dó menor, está emprestando do campo menor. Isso significa que os acordes que você estudou aqui também servem como fonte de empréstimo para o campo maior. O menor e o maior são dois lados da mesma moeda, e a dilatação de um alimenta o outro."),
        b ("Acordes do menor emprestados ao maior: Cm, Fm7, Ab7M, Bb7, Eb7M."),
        b ("O iv menor do maior é o iv do menor natural."),
        b ("O bVI e o bVII do maior são do menor natural."),
        tbl ({ "Acorde do menor", "Emprestado ao maior como", "Cor" }, {
            { "Cm7 (i)", "Cm", "tônica menor" },
            { "Fm7 (iv)", "Fm7", "subdominante menor" },
            { "Ab7M (bVI)", "Ab7M", "drama" },
            { "Bb7 (bVII)", "Bb7", "cadência modal" },
        }),

        h ("A cadência deceptiva no menor"),
        p (
            "No campo menor, a cadência deceptiva também existe. O dominante pode resolver em outro grau em vez do i, criando a mesma surpresa do maior. Em Dó menor, um G7 que resolve em Ab7M (o bVI) em vez de Cm7 é uma deceptiva típica do menor. Reconhecer esse movimento é importante para não se perder na forma de uma música menor."),
        b ("Esperado: G7 → Cm7."),
        b ("Deceptivo no menor: G7 → Ab7M (resolve no bVI)."),
        b ("A surpresa funciona igual à do maior."),
        aud ({ "G3", "B3", "D4", "F4", "G#3", "C4", "D#4", "G4" },
             "G7 → Ab7M: cadência deceptiva no campo menor. Ouça a surpresa."),

        h ("Resumo do tópico"),
        b ("O campo menor é a união de três escalas: natural, harmônica e melódica."),
        b ("A natural não tem dominante; a harmônica o cria (V7)."),
        b ("A melódica acrescenta acordes de cor (Dm7, F7, Am7b5)."),
        b ("A cadência fundamental é o II-V-I menor (Dm7b5 → G7 → Cm7)."),
        b ("O dominante do menor é sempre um empréstimo da harmônica."),
        c (
            "Nos exercícios deste tópico, toque os acordes do campo menor e confira com o app. Ele reconhece as notas e verifica se o acorde montado corresponde ao pedido."),
    };
}

} // namespace cursomusica::content
