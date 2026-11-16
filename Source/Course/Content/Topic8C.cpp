#include "Course/Content/Topics.h"

// Topic 8C — Dominantes alterados e resoluções (Módulo 8, Etapa 8).
// Fonte de verdade do texto: .agents/agents/mc-modulo-8.md (Etapa 8, tópico C).
namespace cursomusica::content
{

std::vector<ContentItem> topic8C()
{
    return {

        p (
            "O dominante simples, com as quatro notas básicas, já cria tensão. Mas a música moderna costuma ir além: acrescenta ou altera notas do dominante para intensificar essa tensão e controlar para onde ele aponta. São os dominantes alterados. Eles são a assinatura sonora do jazz, da bossa nova e de boa parte da música brasileira instrumental."),
        p (
            "Alterar um dominante significa mudar uma ou mais notas em relação à forma básica. A fundamental, a terça maior e a sétima menor permanecem — elas definem o acorde como dominante. O que muda é a quinta e as extensões (nona, décima primeira, décima terceira). Alterar essas notas muda a cor e a intensidade da resolução."),
        c (
            "Objetivo do tópico: conhecer as principais alterações do dominante, entender o efeito de cada uma e saber usá-las para enriquecer a resolução."),

        h ("O que se pode alterar"),
        p (
            "Num acorde dominante, as notas essenciais são a fundamental, a terça maior e a sétima menor. As notas que podem ser alteradas são a quinta e as extensões. A quinta justa pode virar quinta diminuta (b5) ou quinta aumentada (#5). As extensões podem ser nona menor (b9), nona aumentada (#9), décima primeira aumentada (#11) e décima terceira menor (b13)."),
        b ("Fundamental, terça maior e sétima menor: nunca mudam (definem o dominante)."),
        b ("Quinta: pode ser b5 (diminuta) ou #5 (aumentada)."),
        b ("Extensões: b9, #9, #11, b13 acrescentam cor e tensão."),
        img ("m8_dominantes_alterados", "Alterações do G7: cada nota acrescentada aumenta a tensão e aponta a resolução."),

        h ("Nona menor (b9)"),
        p (
            "A nona menor é a alteração mais comum. Ela acrescenta à fundamental a distância de treze semitons (uma oitava mais um semitom), ou, mais simplesmente, um semitom acima da fundamental na oitava seguinte. Em G7, a nona menor é o Lá bemol (Ab). Ela cria uma tensão forte porque forma um semitom com a fundamental, e costuma aparecer quando o dominante resolve em um acorde menor."),
        b ("G7b9 = G, B, D, F, Ab."),
        b ("O Ab é a nona menor: um semitom acima do Sol."),
        b ("Muito comum resolvendo em menor (G7b9 → Cm)."),
        aud ({ "G3", "B3", "D4", "F4", "G#4" }, "G7b9: o Lá bemol no topo cria uma tensão aguda que pede resolução."),

        h ("Nona aumentada (#9)"),
        p (
            "A nona aumentada sobe mais um semitom em relação à nona maior, formando um som de blues. Em G7, a nona aumentada é o Lá sustenido (A#), enarmônico do Si bemol. O acorde resultante é o famoso \"acorde hendrix\", usado à exaustão no rock e no funk. Ele combina a terça maior (Si) com a nona aumentada (Si bemol), criando uma fricção que soa ao mesmo tempo maior e menor."),
        b ("G7#9 = G, B, D, F, A#."),
        b ("O A# (Si bemol) fica um tom e meio acima do Sol."),
        b ("Som de blues e de rock: o \"acorde hendrix\"."),
        aud ({ "G3", "B3", "F4", "A#4" }, "G7#9: a terça maior e a nona aumentada juntas dão o som de blues."),

        h ("Quinta diminuta e quinta aumentada"),
        p (
            "Alterar a quinta muda o equilíbrio do acorde. A quinta diminuta (b5) estreita o acorde e cria um som mais fechado, próximo do dominante alterado. A quinta aumentada (#5) alarga o acorde e produz um som suspenso, que resolve com um movimento descendente. Essas duas alterações são muito usadas em combinação com a nona menor, formando o som \"altered\"."),
        b ("G7b5 = G, B, Db, F."),
        b ("G7#5 = G, B, D#, F."),
        b ("A quinta alterada muda a direção da resolução (b5 desce, #5 sobe)."),
        tbl ({ "Acorde", "Notas", "Efeito" }, {
            { "G7b5", "G, B, Db, F", "fechado, tenso" },
            { "G7#5", "G, B, D#, F", "suspenso, expansivo" },
            { "G7b9", "G, B, D, F, Ab", "tensão aguda" },
            { "G7#9", "G, B, D, F, A#", "blues, fricção" },
            { "G7#11", "G, B, D, F, C#", "cor lídia dominante" },
            { "G7alt", "G, B, F + alterações", "tensão máxima" },
        }),

        h ("O acorde alterado (alt)"),
        p (
            "Quando se acumulam várias alterações, o acorde é chamado simplesmente de alterado, cifrado como G7alt. Nessa forma, as notas essenciais (fundamental, terça e sétima) permanecem, e as demais são substituídas por versões alteradas. O som é de tensão máxima: é o dominante que mais pede resolução e o que dá mais cor à chegada."),
        b ("G7alt mantém G, B e F; altera quinta e extensões."),
        b ("É o dominante mais tenso antes da resolução."),
        b ("Aparece muito em finais de frase e em II-V-I menores."),
        c (
            "Regra prática: quanto mais alterações, mais o ouvido espera a resolução. Use o dominante alterado no ponto de maior tensão da frase."),

        h ("Resoluções de dominantes"),
        p (
            "A resolução de um dominante pode ser de dois tipos. A resolução regular leva o dominante à sua tônica (G7 → C). A resolução irregular leva a um acorde que não é a tônica esperada (G7 → Am, a chamada cadência deceptiva). Reconhecer o tipo de resolução é fundamental para identificar o que está acontecendo na música."),
        b ("Regular: G7 → C (a tônica esperada)."),
        b ("Irregular (deceptiva): G7 → Am (resolve no vi)."),
        b ("O tipo de resolução muda a sensação: a regular fecha, a deceptiva surpreende."),
        img ("m8_alteracoes_tensao", "Do dominante simples ao alterado: mais notas alteradas, mais tensão, mais expectativa de resolução."),

        h ("A resolução do dominante alterado"),
        p (
            "As alterações não mudam o alvo: continuam resolvendo por meio-tom. O que muda é o caminho. A nona menor (Ab) desce meio-tom para a quinta do acorde de chegada; a quinta aumentada (#5) sobe meio-tom; a décima primeira aumentada (#11) desce. Cada nota alterada tem uma direção natural de resolução."),
        b ("Ab (b9) desce meio-tom → Sol (5ª do C)."),
        b ("D# (#5) sobe meio-tom → Mi (3ª do C)."),
        b ("C# (#11) desce meio-tom → Dó (fundamental do C)."),
        aud ({ "G3", "B3", "F4", "G#4", "C4", "E4", "G4" }, "G7b9 resolvendo em C: o Lá bemol desce para Sol, o alívio da chegada."),

        h ("Como identificar de ouvido"),
        p (
            "O dominante alterado soa mais \"sujo\" e mais tenso do que o dominante simples. O ouvido percebe um atrito, um som que quase desafina. Treine comparando: toque G7 e depois G7b9 e note a diferença. Depois toque cada um resolvendo e perceba como a resolução do alterado é mais satisfatória porque a tensão era maior."),
        b ("Compare G7 e G7b9: o segundo é mais tenso."),
        b ("Note a direção da resolução: b9 desce, #5 sobe."),
        b ("Pergunte: o dominante estava alterado ou simples?"),
        aud ({ "G3", "B3", "D4", "F4", "G3", "B3", "D4", "F4", "G#4" },
             "G7 e depois G7b9: a diferença de tensão é a alteração."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é alterar a terça ou a sétima, o que descaracteriza o dominante. Só a quinta e as extensões podem ser alteradas. Outro erro é usar o alterado em qualquer lugar: ele pertence aos momentos de maior tensão, e usá-lo o tempo todo dilui o efeito."),
        b ("Nunca altere a terça maior nem a sétima menor."),
        b ("Use o alterado onde a tensão precisa ser maior."),
        b ("Não altere todos os dominantes: o contraste é o que dá efeito."),
        c (
            "Dica: comece pela b9, que é a alteração mais fácil de ouvir e de tocar. Só depois acrescente #9, b5 e #5."),

        h ("Aplicação prática"),
        p (
            "Pratique tocar o mesmo dominante em várias formas alteradas e resolva cada um na tônica. Depois compare as resoluções e escolha a que soa melhor no contexto. No instrumento, o dominante alterado aparece em digitações diferentes; use o app para conferir se as notas que você toca formam o acorde alterado pedido."),
        b ("Toque G7, G7b9 e G7#9, resolvendo cada um em C."),
        b ("Toque G7alt resolvendo em Cm."),
        b ("Compare qual alteração você prefere e por quê."),
        part ("m8_partitura_alterado", { "G3", "B3", "Db4", "F4", "Ab4" },
              "Partitura de um G7 alterado (b5 e b9) resolvendo. Ouça a tensão e a resolução."),

        h ("Os dominantes alterados em outras tonalidades"),
        p (
            "As alterações não dependem da tonalidade: valem para qualquer dominante. O b9 de D7 (dominante de Sol) é o Mi bemol; o #9 é o Fá (Mi sustenido); o #11 é o Sol sustenido. O processo é sempre o mesmo: identifique o dominante e aplique as alterações. Uma vez que você internaliza as alterações como notas específicas do braço, pode aplicá-las em qualquer acorde."),
        b ("D7b9: D, F#, A, C, Eb."),
        b ("D7#9: D, F#, A, C, F."),
        b ("D7#11: D, F#, A, C, G#."),
        tbl ({ "Dominante", "b9", "#9", "#11" }, {
            { "G7", "Ab", "A#", "C#" },
            { "D7", "Eb", "F", "G#" },
            { "C7", "Db", "D#", "F#" },
            { "F7", "Gb", "G#", "B" },
        }),

        h ("Escalas para improvisar sobre dominantes alterados"),
        p (
            "Quando você improvisa sobre um dominante alterado, a escala acompanha as alterações. Sobre um G7alt, você pode usar a escala alterada (o sétimo modo da menor melódica), que contém justamente as notas b9, #9, b5 e #5. Usar a escala certa faz a frase soar coerente com o acorde. É a ponte entre a harmonia e a melodia."),
        b ("Escala alterada: contém b9, #9, b5, #5."),
        b ("Escala lídia dominante: contém #11 (para G7#11)."),
        b ("A escala deve casar com as alterações do acorde."),
        aud ({ "G3", "G#3", "A#3", "B3", "C#4", "D#4", "F4" },
             "Escala alterada sobre G7: ouça as notas b9, #9, #11 e #5."),

        h ("Onde usar dominantes alterados"),
        p (
            "Os dominantes alterados aparecem onde a tensão precisa ser maior: em finais de frase, em II-V-I menores, em modulações e em momentos de clímax. Usá-los em excesso dilui o efeito; usá-los nos pontos certos dá dramaticidade à música. É uma questão de gosto e de contexto, mas a regra geral é: quanto mais tensão o momento pede, mais alterações o dominante pode receber."),
        b ("Finais de frase: aumentam a expectativa."),
        b ("II-V-I menores: casam com a cor menor."),
        b ("Clímax: dão dramaticidade à resolução."),
        c (
            "Compare sempre: toque o mesmo trecho com o dominante simples e com o alterado. O ouvido dirá qual combina melhor."),

        h ("Resolução regular e irregular na prática"),
        p (
            "Na prática, a resolução regular fecha a frase e a irregular a prolonga. Quando você improvisa ou acompanha, saber qual das duas está acontecendo muda as notas que você escolhe. Na regular, você pode tocar as notas da tônica; na irregular, precisa acompanhar o novo alvo. Ouvir a resolução antes de tocar é o que evita tocar fora do contexto."),
        b ("Regular (G7 → C): toque as notas de Dó maior."),
        b ("Irregular (G7 → Am): acompanhe o Lá menor."),
        b ("Escute o alvo antes de escolher as notas."),
        tbl ({ "Resolução", "Exemplo", "Efeito" }, {
            { "Regular", "G7 → CM7", "fecha a frase" },
            { "Irregular (deceptiva)", "G7 → Am7", "surpreende e prolonga" },
            { "Irregular (para o IV)", "G7 → FM7", "reabre o movimento" },
        }),

        h ("Resumo do tópico"),
        b ("Alterar o dominante é mudar quinta e extensões, nunca terça ou sétima."),
        b ("Principais alterações: b5, #5, b9, #9, #11."),
        b ("Cada alteração tem uma direção natural de resolução por meio-tom."),
        b ("O acorde alterado (alt) é o dominante de tensão máxima."),
        b ("A resolução pode ser regular (→ I) ou irregular (→ outro grau)."),
        c (
            "Nos exercícios deste tópico, toque o dominante alterado e confira com o app. Ele reconhece as notas e verifica se o acorde montado corresponde ao pedido."),
    };
}

} // namespace cursomusica::content
