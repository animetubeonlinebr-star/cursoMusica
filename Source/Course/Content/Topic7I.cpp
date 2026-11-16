#include "Course/Content/Topics.h"

// Topic 7I — Lócrio 9 e Alterado (Alt.7) (Módulo 7, Etapa 7).
// Fonte de verdade do texto: docs/MUSIC.md §7.2 (bloco I).
namespace cursomusica::content
{

std::vector<ContentItem> topic7I()
{
    return {

        p (
            "Chegamos às duas sonoridades mais tensas e sofisticadas do módulo: o lócrio 9 e o alterado (Alt.7). O lócrio 9 é a escala do acorde meio-diminuto com a nona natural, muito usada no II grau dos II–V–I menores. O alterado é a escala de tensão máxima sobre o dominante, com todas as alterações possíveis. As duas aparecem constantemente no jazz e na música instrumental."),
        p (
            "Estudar essas escalas é entrar no território da tensão controlada. Elas não são “difíceis” por serem complicadas, mas por exigirem um ouvido treinado para reconhecer quando usar tanta tensão. Neste tópico você aprende a estrutura de cada uma, quando usar e como elas resolvem."),

        h ("Lócrio 9"),
        p (
            "O modo lócrio é a escala do acorde meio-diminuto (Xm7b5): 1 b2 b3 4 b5 b6 b7. Ele tem três notas “problemáticas” (a b2, a b5 e a b6), o que o torna bastante instável. Por isso, na prática, muitos músicos preferem a variação chamada lócrio 9 (ou lócrio natural 9), em que a b2 é substituída pela segunda natural (9)."),
        tbl ({ "Grau", "Nota em Dó lócrio 9", "Intervalo a partir da tônica" }, {
            { "1", "Dó", "uníssono" },
            { "9", "Ré", "segunda maior (nona)" },
            { "b3", "Mib", "terça menor" },
            { "4", "Fá", "quarta justa" },
            { "b5", "Solb", "quinta diminuta" },
            { "b6", "Láb", "sexta menor" },
            { "b7", "Sib", "sétima menor" },
        }),
        b ("Fórmula do lócrio: 1 b2 b3 4 b5 b6 b7."),
        b ("Fórmula do lócrio 9: 1 2 b3 4 b5 b6 b7 (a nona natural substitui a b2)."),
        b ("Acorde típico: Xm7b5 (meio-diminuto), como II grau de um II–V–I menor."),
        aud ({ "C4", "D4", "D#4", "F4", "F#4", "G#4", "A#4" }, "Escala lócrio 9 em Dó: meio-diminuto com a nona natural. Som tenso, mas mais suave que o lócrio puro."),
        aud ({ "C4", "D#4", "F#4", "A#4" }, "Acorde meio-diminuto de Dó (Cm7b5): a base do lócrio 9."),
        c (
            "O lócrio 9 aparece no II grau dos II–V–I menores (por exemplo, Cm7b5 → F7alt → Bbm). A nona natural suaviza a tensão e faz a passagem para o dominante soar mais natural."),

        h ("Alterado (Alt.7)"),
        p (
            "O alterado é a escala de tensão máxima sobre um dominante. Ele é construído alterando todos os graus que podem ser alterados no dominante: a quinta (b5 ou #5) e a nona (b9 ou #9). A fórmula é 1 b2 #2 3 b5 #5 b7 — ou seja, tem as duas quintas alteradas e as duas nonas alteradas."),
        tbl ({ "Grau", "Nota em Dó alterado", "Intervalo a partir da tônica" }, {
            { "1", "Dó", "uníssono" },
            { "b9", "Réb", "segunda menor" },
            { "#9", "Ré#", "segunda aumentada" },
            { "3", "Mi", "terça maior" },
            { "b5", "Solb", "quinta diminuta" },
            { "#5", "Sol#", "quinta aumentada" },
            { "b7", "Sib", "sétima menor" },
        }),
        b ("Fórmula: 1 b9 #9 3 b5 #5 b7."),
        b ("Acorde típico: X7alt (dominante alterado)."),
        b ("Som de tensão máxima; resolve meio-tom abaixo (ou uma quinta abaixo)."),
        aud ({ "C4", "C#4", "D#4", "E4", "F#4", "G#4", "A#4" }, "Escala alterada em Dó: dominante com todas as tensões. Som máximo de tensão."),
        aud ({ "C4", "E4", "G#4", "A#4" }, "Acorde C7#5: uma das tensões do alterado (a quinta aumentada)."),
        img ("m7_locrio_alterado", "Lócrio 9 e alterado: as duas escalas de tensão do módulo."),

        h ("A resolução do alterado"),
        p (
            "O alterado existe para resolver. Ele é um dominante, e todo dominante pede resolução: normalmente meio-tom abaixo (o V7alt resolve no I) ou uma quinta abaixo (o V7alt resolve no I menor). A tensão do alterado cria uma expectativa muito forte, e a resolução é o alívio. Tocar alterado sem resolver é deixar a frase no ar."),
        b ("Resolve meio-tom abaixo: C7alt → Dbmaj7 (se o alvo for maior)."),
        b ("Resolve uma quinta abaixo: C7alt → Fm (se o alvo for menor)."),
        b ("A tensão existe para criar a resolução."),
        aud ({ "C4", "C#4", "D#4", "E4", "F#4", "G#4", "A#4", "F4" }, "C7alt resolvendo em Fá: ouça a tensão e o alívio da resolução."),

        h ("Lócrio 9 e alterado no II–V–I menor"),
        p (
            "As duas escalas se encontram no II–V–I menor. O II grau (Xm7b5) usa o lócrio 9; o V grau (X7alt) usa o alterado; e a resolução cai no I menor. Esse é um dos encadeamentos mais comuns do jazz e um excelente laboratório para praticar as duas escalas juntas."),
        b ("II grau: Xm7b5, escala lócrio 9."),
        b ("V grau: X7alt, escala alterada."),
        b ("I grau: Xm (menor), a resolução."),
        aud ({ "C4", "D#4", "F#4", "A#4" }, "II grau: Cm7b5 (lócrio 9)."),
        aud ({ "F3", "F#3", "G#3", "A3", "B3", "C#4", "D#4" }, "V grau: F7alt (alterado)."),
        aud ({ "A#3", "C#4", "F4" }, "I grau: Bbm (menor), a resolução do II–V–I menor."),

        h ("Comparando as duas escalas"),
        p (
            "As duas escalas têm em comum a instabilidade, mas em graus diferentes. O lócrio 9 é tenso, mas relativamente estável: ele é um acorde meio-diminuto, não um dominante. O alterado é a tensão máxima: ele é um dominante e exige resolução. Saber essa diferença é o que permite usá-las corretamente."),
        tbl ({ "Escala", "Acorde", "Função", "Tensão" }, {
            { "lócrio 9", "Xm7b5", "II grau (subdominante menor)", "moderada" },
            { "alterado", "X7alt", "V grau (dominante)", "máxima" },
        }),

        h ("Aplicações práticas"),
        p (
            "O lócrio 9 e o alterado aparecem em jazz, música instrumental, bossa e trilhas. São escalas de expressão, usadas quando o músico quer criar tensão e resolvê-la com estilo. Aprender a tocar essas escalas com intenção — e não apenas como exercício mecânico — é o que transforma a técnica em música."),
        b ("Jazz: II–V–I menores e maiores com alterações."),
        b ("Música instrumental: passagens de tensão e resolução."),
        b ("Bossa moderna: cores sofisticadas em acordes alterados."),
        c (
            "Nos exercícios deste tópico, o app toca as escalas para você ouvir e você toca acordes que o app reconhece. Toque em qualquer região do braço."),

        h ("Como praticar as duas escalas"),
        p (
            "Pratique cada escala sobre o seu acorde, devagar, ouvindo cada nota. Comece com o lócrio 9 (mais estável) e depois passe ao alterado. Tocar devagar e ouvir a cor de cada grau é mais valioso do que tocar rápido. Depois, improvise frases curtas, sempre resolvendo a tensão."),
        b ("Um acorde por escala, devagar, ouvindo cada nota."),
        b ("Improvise frases curtas e resolva a tensão."),
        b ("Compare o lócrio 9 (estável) com o alterado (tenso)."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é tocar o alterado sem resolver, deixando a frase “no ar”. Outro é confundir o lócrio com o lócrio 9 e tocar a b2 onde o contexto pede a nona natural. Ouvir o acorde e a resolução guia a escolha."),
        b ("Resolva o alterado: ele existe para isso."),
        b ("No lócrio 9, use a nona natural (não a b2)."),
        b ("Ouça a função do acorde antes de escolher a escala."),

        h ("Lócrio 9: a nona natural e o seu efeito"),
        p (
            "A diferença entre o lócrio e o lócrio 9 está em uma única nota: a segunda. No lócrio, a segunda é menor (b2), o que cria uma tensão forte; no lócrio 9, a segunda é maior (natural), o que suaviza o modo e o torna mais cantável. Por isso o lócrio 9 é preferido por muitos músicos sobre acordes meio-diminutos."),
        b ("Lócrio: 1 b2 b3 4 b5 b6 b7."),
        b ("Lócrio 9: 1 2 b3 4 b5 b6 b7."),
        b ("A nona natural suaviza a tensão do modo."),
        aud ({ "C4", "D4", "D#4", "F4", "F#4", "G#4", "A#4" }, "Lócrio 9 em Dó: a nona natural suaviza o som do meio-diminuto."),

        h ("Alterado: as duas quintas e as duas nonas"),
        p (
            "O que torna o alterado especial é que ele contém todas as alterações possíveis de um dominante: a b5 e a #5 (as duas quintas) e a b9 e a #9 (as duas nonas). Ter as duas quintas e as duas nonas ao mesmo tempo é o que dá ao alterado a sua tensão máxima e a sua riqueza."),
        b ("Quinta alterada: b5 e #5 (as duas)."),
        b ("Nona alterada: b9 e #9 (as duas)."),
        b ("Todas as tensões do dominante em uma só escala."),
        aud ({ "C4", "C#4", "D#4", "E4", "F#4", "G#4", "A#4" }, "Alterado em Dó: as duas quintas e as duas nonas alteradas."),

        h ("Como o alterado resolve"),
        p (
            "O alterado resolve de duas formas principais: meio-tom abaixo (para um acorde maior) ou uma quinta abaixo (para um acorde menor). Essas resoluções são a razão de ser do alterado: ele cria uma tensão tão forte que a resolução é sentida como um alívio. Tocar alterado sem resolver é deixar a frase incompleta."),
        b ("Meio-tom abaixo: C7alt resolve em Dbmaj7."),
        b ("Uma quinta abaixo: C7alt resolve em Fm."),
        b ("A resolução é o objetivo do alterado."),

        h ("Escalas de tensão no repertório"),
        p (
            "No repertório, o lócrio 9 e o alterado aparecem em momentos de tensão e resolução. O lócrio 9, no II grau dos II–V–I menores; o alterado, no V grau. Reconhecer esses momentos é o que permite escolher a escala certa e criar a tensão que a música pede."),
        b ("Lócrio 9: II grau de um II–V–I menor."),
        b ("Alterado: V grau de um II–V–I menor ou maior."),
        b ("A tensão existe para criar a resolução."),

        h ("Praticando as escalas de tensão"),
        p (
            "Pratique cada escala sobre o seu acorde, devagar, ouvindo cada nota. Comece com o lócrio 9 (mais estável) e depois passe ao alterado. Toque a escala na ordem, depois improvise frases curtas que resolvem a tensão. O objetivo é tocar essas escalas com intenção, não como exercício mecânico."),
        b ("Devagar, ouvindo cada nota."),
        b ("Do lócrio 9 (estável) ao alterado (tenso)."),
        b ("Improvise frases que resolvem a tensão."),
        img ("m7_locrio_alterado", "Do lócrio 9 ao alterado: da tensão moderada à tensão máxima."),

        h ("Comparando o lócrio 9 com o alterado no braço"),
        p (
            "No braço, as duas escalas ocupam regiões parecidas, mas as notas alteradas mudam a cor de forma radical. O lócrio 9 tem a quinta diminuta e a sexta menor, o que dá o som meio-diminuto; o alterado tem as duas quintas e as duas nonas, o que dá a tensão máxima. Tocar uma depois da outra ajuda a ouvir a diferença."),
        b ("Lócrio 9: som meio-diminuto, tensão moderada."),
        b ("Alterado: som de dominante, tensão máxima."),
        b ("Compare as duas e ouça a diferença de cor."),

        h ("Do estudo à música"),
        p (
            "As escalas de tensão só fazem sentido quando resolvem. Por isso, pratique sempre em pares: toque o lócrio 9 sobre o II grau e o alterado sobre o V, e resolva no I. O ouvido aprende a associar a tensão à resolução, e é essa associação que dá sentido musical às escalas. Tocar tensão sem resolver é deixar a frase incompleta."),
        b ("Pratique a tensão sempre em par com a resolução."),
        b ("II grau (lócrio 9) e V grau (alterado)."),
        b ("Resolva no I: a tensão existe para isso."),

        h ("Um laboratório: o II–V–I menor"),
        p (
            "O II–V–I menor é o laboratório ideal para as duas escalas. Monte o encadeamento Cm7b5 → F7alt → Bbm e toque, sobre cada acorde, a escala correspondente. Comece devagar, ouvindo cada nota e a forma como a tensão se acumula e se resolve. Esse exercício reúne harmonia, escala e percepção em um único estudo."),
        b ("Cm7b5: lócrio 9."),
        b ("F7alt: alterado."),
        b ("Bbm: a resolução."),
        c (
            "Domine esse encadeamento e você terá uma das ferramentas mais usadas do jazz na ponta dos dedos."),

        h ("Resumo do tópico"),
        b ("Lócrio: 1 b2 b3 4 b5 b6 b7; lócrio 9 usa a nona natural."),
        b ("Lócrio 9 combina com Xm7b5 (II grau do II–V–I menor)."),
        b ("Alterado: 1 b9 #9 3 b5 #5 b7 (tensão máxima)."),
        b ("Alterado combina com X7alt e resolve meio-tom abaixo."),
        b ("As duas aparecem juntas no II–V–I menor."),
        part ("m7_partitura_alterado", { "C4", "C#4", "D#4", "E4", "F#4", "G#4", "A#4" },
              "Partitura: escala alterada em Dó (Alt.7). Ouça a tensão máxima do dominante alterado."),
    };
}

} // namespace cursomusica::content
