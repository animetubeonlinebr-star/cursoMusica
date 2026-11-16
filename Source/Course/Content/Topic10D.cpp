#include "Course/Content/Topics.h"

// Topic 10D — Verticalização (Módulo 10, Etapa 10).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 10). Verticalizar = construir
// um acorde empilhando intervalos a partir de cada nota da melodia.
namespace cursomusica::content
{

std::vector<ContentItem> topic10D()
{
    return {

        p (
            "Verticalizar é transformar uma melodia horizontal em harmonia vertical. Em vez de uma nota por vez, você pega cada nota da melodia e empilha intervalos a partir dela, construindo um acorde. A melodia A–G–F–E, tocada sozinha, é uma linha; verticalizada, ela vira Am7–G7–F7M–Em7 — quatro acordes que carregam exatamente as notas que você cantou. A verticalização é a ponte entre o que você ouve (a melodia) e o que você harmoniza (os acordes)."),
        p (
            "Esse é um dos recursos mais usados por arranjadores e por guitarristas de jazz e bossa: em vez de aplicar uma harmonia pronta, eles 'ouvem' a melodia e constroem a harmonia a partir dela. O resultado é sempre coerente, porque cada acorde contém a nota que a melodia está tocando naquele momento. Verticalizar é, no fundo, deixar a melodia escolher a harmonia."),
        c (
            "Ideia central: cada nota da melodia vira a base de um acorde. A harmonia nasce das próprias notas — por isso ela nunca briga com a melodia."),

        h ("Da melodia à harmonia"),
        p (
            "O procedimento da verticalização tem três passos. Primeiro, escolha a melodia e toque-a sozinha, ouvindo cada nota. Segundo, para cada nota, pergunte: qual acorde contém essa nota como nota do acorde? Terceiro, empilhe o acorde a partir da nota (ou escolha um acorde da família que a contenha) e toque a melodia por cima. O resultado é uma harmonização em que a melodia é a voz de cima e os acordes são as vozes de baixo."),
        b ("Toque a melodia sozinha e identifique cada nota."),
        b ("Para cada nota, escolha um acorde que a contenha."),
        b ("Toque o acorde com a nota da melodia no topo."),
        img ("m10_verticalizacao", "A melodia A–G–F–E verticalizada: cada nota vira a base de um acorde (Am7–G7–F7M–Em7)."),

        h ("Empilhando intervalos a partir da nota"),
        p (
            "Verticalizar também pode ser feito de forma literal: a partir da nota da melodia, empilhe terças. A nota A gera A–C–E–G (Am7); a nota G gera G–B–D–F (G7); a nota F gera F–A–C–E (F7M); a nota E gera E–G–B–D (Em7). Empilhar terças é o jeito mais direto de construir acordes: tônica, terça, quinta e sétima. É a mesma lógica da construção de acordes do Módulo 2, agora aplicada nota a nota da melodia."),
        tbl ({ "Nota da melodia", "Empilhamento", "Acorde resultante", "Notas" }, {
            { "A", "A–C–E–G", "Am7", "A, C, E, G" },
            { "G", "G–B–D–F", "G7", "G, B, D, F" },
            { "F", "F–A–C–E", "F7M", "F, A, C, E" },
            { "E", "E–G–B–D", "Em7", "E, G, B, D" },
        }),
        c (
            "Empilhar terças a partir da nota da melodia garante que a nota seja a fundamental do acorde. Se você preferir que ela seja a terça ou a quinta, escolha outro acorde da mesma família — o resultado continua verticalizado, só muda a posição da melodia."),
        aud ({ "A3", "C4", "E4", "G4" }, "Empilhamento a partir de A: Am7. A nota da melodia vira a fundamental."),
        aud ({ "G3", "B3", "D4", "F4" }, "Empilhamento a partir de G: G7. Ouça como a cor muda mantendo o mesmo processo."),

        h ("Verticalização e a nota no topo"),
        p (
            "A verticalização fica mais rica quando a nota da melodia é a voz de cima do acorde. Para isso, você inverte o acorde até a nota da melodia ficar no topo. Se a melodia toca A sobre um F7M (F–A–C–E), você pode tocar o acorde com o A no soprano, criando uma sonoridade em que a melodia é claramente a voz principal. Esse cuidado é o que distingue uma harmonização amadora (acordes aleatórios embaixo da melodia) de uma harmonização profissional (acordes construídos para a melodia)."),
        b ("Coloque a nota da melodia na voz de cima (soprano) do acorde."),
        b ("Inverta o acorde para ajustar a posição da melodia."),
        b ("Evite que a melodia se perca no meio das vozes do acorde."),
        aud ({ "F3", "C4", "E4", "A4" }, "F7M com o A (nota da melodia) no topo: a melodia é a voz de cima."),
        img ("m10_vozes_internas", "Vozes internas e a melodia no topo: a verticalização cuida de conduzir cada voz, não só de escolher o acorde."),

        h ("Verticalização sobre acordes existentes"),
        p (
            "A verticalização não serve só para criar harmonia do zero: ela também serve para reharmonizar uma melodia que já tem acordes. Você pega a melodia, olha as notas fortes, e testa acordes alternativos que contenham essas notas. Se a melodia insiste em A e C, talvez o Am7 do original possa virar F7M (que também tem A e C) — a melodia continua a mesma, mas a cor muda. É exatamente essa liberdade que os tópicos de reharmonização exploram."),
        tbl ({ "Melodia", "Acorde original", "Alternativa verticalizada", "Notas em comum" }, {
            { "A, C", "Am7", "F7M", "A, C" },
            { "G, B", "G7", "Em7", "G, B" },
            { "F, A", "F7M", "Dm7", "F, A" },
            { "E, G", "Em7", "C7M", "E, G" },
        }),
        b ("Procure acordes alternativos que contenham as notas fortes da melodia."),
        b ("Mantenha as notas da melodia; mude a harmonia embaixo."),
        b ("Escolha a alternativa pela função que você quer dar à frase."),
        part ("m10_partitura_verticalizacao", { "A4", "G4", "F4", "E4" },
              "Partitura da melodia verticalizada: A–G–F–E. Cada nota pede um acorde; ouça a melodia que sustenta a harmonia."),

        h ("Verticalização em blocos (chord melody)"),
        p (
            "O estilo em que a melodia é tocada junto com os acordes se chama chord melody. Nele, cada nota da melodia vem acompanhada do acorde verticalizado — você toca melodia e harmonia ao mesmo tempo, com a melodia sempre no topo. É o estilo de guitarristas como Joe Pass e, no Brasil, de muitos violonistas de bossa. A verticalização é a técnica que torna o chord melody possível: sem ela, a melodia e os acordes seriam duas coisas separadas."),
        b ("Chord melody: melodia e acorde soam juntos."),
        b ("A melodia fica sempre na voz mais aguda."),
        b ("Os acordes preenchem as vozes internas e o baixo."),
        aud ({ "A4", "G4", "F4", "E4" }, "A melodia sozinha, para você memorizar o desenho antes de verticalizar."),
        aud ({ "A3", "C4", "E4", "G4", "F4", "E4" }, "A melodia com os acordes verticalizados embaixo: a mesma linha, agora harmonizada."),

        h ("Como praticar a verticalização"),
        p (
            "Pratique verticalizando melodias simples. Pegue uma escala, toque-a em terças (1-3, 2-4, 3-5) e ouça os acordes que aparecem; depois pegue uma melodia conhecida e teste acordes que contenham as notas fortes. Grave, escute e ajuste. O app ajuda: ele reconhece as notas que você toca e confere se o acorde escolhido realmente contém a melodia — assim você aprende a verticalizar com verificação, não só por tentativa."),
        b ("Toque uma escala em terças e identifique os acordes que surgem."),
        b ("Harmonize uma melodia simples com acordes que contenham suas notas fortes."),
        b ("Confira com o app: as notas do acorde precisam cobrir a melodia."),
        c (
            "Erro comum: escolher um acorde bonito que não contém a nota da melodia. A verticalização exige coerência — o acorde existe para sustentar a melodia, não para brilhar sozinho."),

        h ("Erros comuns na verticalização"),
        p (
            "O erro mais comum é verticalizar uma nota que não pertence ao acorde escolhido, criando um atrito não resolvido. O segundo é verticalizar tudo: nem toda nota da melodia precisa virar um acorde novo, ou a harmonia fica nervosa demais. O terceiro é esquecer a condução das vozes — os acordes devem se ligar por movimentos pequenos, não por saltos aleatórios. Verticalizar bem é escolher quais notas viram acorde e como esses acordes se conectam."),
        b ("Garanta que cada acorde contenha a nota da melodia que ele harmoniza."),
        b ("Não verticalize todas as notas: agrupe por frases."),
        b ("Conduza as vozes por graus próximos entre um acorde e o seguinte."),
        img ("m10_vozes_internas", "Verticalizar exige conduzir as vozes: os acordes se ligam por movimentos pequenos, não por saltos."),

        h ("Verticalização com notas de tensão"),
        p (
            "A verticalização não precisa se limitar às notas do acorde. Quando a melodia toca uma tensão — uma nona, uma décima primeira, uma décima terceira —, você pode verticalizar essa tensão também, desde que o acorde resultante a contenha como tensão. Sobre um C7M, a melodia tocando um D (nona) pode ser harmonizada com C7M9; o F# (quarta aumentada) com C7M(#11); o A (décima terceira) com C7M13. Verticalizar tensões é o que dá às harmonizações o som rico e moderno da bossa e do jazz."),
        tbl ({ "Nota da melodia", "Sobre o acorde", "Acorde verticalizado" }, {
            { "D", "C7M", "C7M9" },
            { "F#", "C7M", "C7M(#11)" },
            { "A", "C7M", "C7M13" },
            { "E", "Dm7", "Dm7(9)" },
            { "G", "Dm7", "Dm7(11)" },
        }),
        b ("Verticalize também as tensões: o acorde deve contê-las."),
        b ("Acordes com tensões (9, #11, 13) dão o som rico da bossa e do jazz."),
        b ("A nota da melodia define qual tensão o acorde precisa ter."),
        aud ({ "C3", "E3", "G3", "B3", "D4" }, "C7M9 verticalizado: a nona (D) no topo dá o brilho da bossa."),

        h ("Verticalização e reharmonização: um exemplo completo"),
        p (
            "Vamos verticalizar uma melodia simples e ver a reharmonização acontecer. A melodia é D–C–B–A sobre uma harmonia original de G7. Verticalizando: o D pode virar Dm7 (D, F, A, C) ou F7M; o C pode virar C7M ou Am7; o B pode virar G7 (com B no topo) ou Em7; o A pode virar Am7 ou F7M. Escolhendo os acordes que contêm cada nota, você reharmoniza a melodia inteira sem mudar nenhuma nota — e o resultado é uma progressão nova, coerente, porque cada acorde nasceu da melodia."),
        b ("Liste as notas fortes da melodia."),
        b ("Para cada nota, liste os acordes que a contêm."),
        b ("Escolha um acorde por nota e toque a melodia por cima."),
        b ("Ajuste pela condução de vozes (tópico F)."),
        part ("m10_partitura_verticalizacao", { "A4", "G4", "F4", "E4" },
              "Partitura da melodia verticalizada: a mesma linha A–G–F–E, que os acordes do tópico harmonizam acorde a acorde."),

        h ("Onde a verticalização se aplica"),
        p (
            "A verticalização é útil em muitos contextos. Na guitarra solo (chord melody), ela é a base: melodia e acordes soam juntos, com a melodia no topo. No arranjo de uma música para violão, ela permite criar uma versão só de acordes que carrega a melodia. Na reharmonização, ela garante que a nova harmonia contenha a melodia. E na composição, ela ajuda a escrever uma harmonia que 'nasce' da melodia em vez de ser aplicada por cima. Em todos esses casos, o princípio é o mesmo: a melodia escolhe os acordes."),
        b ("Chord melody: melodia e acordes ao mesmo tempo."),
        b ("Arranjo para violão: harmonia que carrega a melodia."),
        b ("Reharmonização: garantir que a melodia caiba na nova harmonia."),
        b ("Composição: harmonia que nasce da melodia."),
        aud ({ "D4", "F4", "A4", "C5", "D5" }, "Um trecho verticalizado: a melodia no topo, o acorde embaixo. Ouça como se completam."),

        h ("Verticalização e a melodia na voz de cima"),
        p (
            "O cuidado central da verticalização é manter a melodia como a voz mais aguda. Se a melodia se perde no meio das vozes, a harmonização deixa de 'carregar' a linha e passa a competir com ela. Para garantir isso, você ajusta a posição do acorde (a inversão) até a nota da melodia ficar no topo. Esse detalhe é o que faz uma harmonização soar como 'melodia com acompanhamento' em vez de 'acorde com nota estranha'. É a diferença entre um arranjo amador e um profissional."),
        b ("A melodia deve ser sempre a voz mais aguda do acorde."),
        b ("Ajuste a inversão para colocar a melodia no topo."),
        b ("Harmonizar é sustentar a melodia, não competir com ela."),
        aud ({ "E3", "G3", "B3", "E4", "D4" }, "Acorde verticalizado com a melodia no topo: ouça como ela se destaca."),

        h ("Resumo do tópico"),
        b ("Verticalizar é construir acordes a partir das notas da melodia."),
        b ("Empilhar terças a partir da nota é o caminho mais direto."),
        b ("A melodia deve ser a voz de cima do acorde verticalizado."),
        b ("A verticalização também reharmoniza: acordes alternativos que contenham as notas fortes."),
        b ("É a técnica por trás do chord melody e a base da reharmonização melódica."),
        c (
            "Objetivo do tópico: aprender a deixar a melodia escolher a harmonia, construindo acordes que a sustentam em vez de acordes prontos que talvez não caibam."),
    };
}

} // namespace cursomusica::content
