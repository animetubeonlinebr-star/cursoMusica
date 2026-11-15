#include "Course/Content/Topics.h"

// Topic 4E — Tétrades (Módulo 4, Etapa 4).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 4 — construção de acordes).
namespace cursomusica::content
{

std::vector<ContentItem> topic4E()
{
    return {

        p (
            "Até aqui você estudou tríades: acordes de três notas. Acrescentando uma quarta nota — a sétima — você obtém uma tétrade. As tétrades são o som do jazz, da bossa nova, da MPB e de boa parte da música popular mais elaborada. Elas têm mais cor e mais tensão do que as tríades, e por isso carregam mais informação harmônica: dizem ao ouvido não só qual é o acorde, mas para onde ele quer ir."),
        p (
            "A tétrade é formada empilhando mais uma terça sobre a tríade: tônica, terça, quinta e sétima. A sétima pode ser maior (11 semitons acima da tônica) ou menor (10 semitons), e é ela que define a família do acorde. Neste tópico você aprende as principais tétrades, como elas se formam e como reconhecê-las no braço e de ouvido."),
        c (
            "Tétrade = tríade + sétima. É a diferença entre o som 'básico' da tríade e o som 'cheio' do acorde de sétima."),

        h ("A sétima: a nota que dá a família"),
        p (
            "A sétima é a nota que está uma terça acima da quinta. Na escala maior, ela pode ser maior (11 semitons) ou menor (10 semitons). A escolha entre essas duas distâncias define as famílias mais importantes: a sétima maior produz o som brilhante e suspenso; a sétima menor, o som tenso e 'de blues'. Junto com a terça, a sétima define praticamente toda a identidade do acorde."),
        tbl ({ "Nota (C7M)", "Grau", "Semitons", "Intervalo" }, {
            { "Dó", "1 (tônica)", "0", "uníssono" },
            { "Mi", "3", "4", "terça maior" },
            { "Sol", "5", "7", "quinta justa" },
            { "Si", "7", "11", "sétima maior" },
        }),
        tbl ({ "Nota (C7)", "Grau", "Semitons", "Intervalo" }, {
            { "Dó", "1 (tônica)", "0", "uníssono" },
            { "Mi", "3", "4", "terça maior" },
            { "Sol", "5", "7", "quinta justa" },
            { "Si♭", "7", "10", "sétima menor" },
        }),

        h ("As tétrades principais"),
        p (
            "Existem várias tétrades, mas quatro cobrem a maior parte do repertório. A sétima maior (0–4–7–11) é o acorde de repouso 'sofisticado', muito usado como tônica no jazz e na MPB. A sétima dominante (0–4–7–10) é o acorde de tensão que pede resolução; é o famoso 'acorde de dominante'. A menor com sétima (0–3–7–10) é o som do blues, do soul e da bossa. E a meio-diminuta (0–3–6–10) é o acorde tenso usado como segundo grau no campo menor."),
        tbl ({ "Tétrade", "Semitons", "Notas em Dó", "Sensação" }, {
            { "Sétima maior (C7M)", "0–4–7–11", "Dó–Mi–Sol–Si", "brilhante, suspensa" },
            { "Sétima dominante (C7)", "0–4–7–10", "Dó–Mi–Sol–Si♭", "tensa, pede resolução" },
            { "Menor com sétima (Cm7)", "0–3–7–10", "Dó–Mi♭–Sol–Si♭", "blues, suave" },
            { "Meio-diminuta (Cm7♭5)", "0–3–6–10", "Dó–Mi♭–Sol♭–Si♭", "tensa, instável" },
        }),
        img ("m4_tetrades", "As tétrades de Dó: sétima maior, dominante, menor e meio-diminuta."),

        h ("Da tríade à tétrade"),
        p (
            "A tétrade é a tríade com uma nota a mais. Em Dó maior (Dó–Mi–Sol), acrescentar Si produz Dó7M; acrescentar Si♭ produz Dó7. Em Dó menor (Dó–Mi♭–Sol), acrescentar Si♭ produz Cm7; acrescentar Si natural produz Cm(maj7), um acorde raro de som misterioso. Essa lógica é a mesma em qualquer tônica: identifique a tríade, escolha a sétima, e você tem a tétrade."),
        b ("Tríade maior + sétima maior = 7M."),
        b ("Tríade maior + sétima menor = 7 (dominante)."),
        b ("Tríade menor + sétima menor = m7."),
        b ("Tríade menor + sétima maior = m(maj7) — raro, som suspenso."),
        aud ({ "C4", "E4", "G4", "B4" }, "Dó com sétima maior (Dó7M): brilho e suspensão."),
        aud ({ "C4", "E4", "G4", "A#4" }, "Dó com sétima dominante (Dó7): tensão que pede resolução."),

        h ("O que cada tétrade comunica"),
        p (
            "Cada tétrade tem um papel na harmonia. A sétima maior soa como repouso elevado: é a tônica de uma música de jazz. A sétima dominante soa como movimento: ela empurra para o acorde seguinte, geralmente uma quinta abaixo. A menor com sétima soa como um repouso suave e um pouco melancólico. A meio-diminuta soa como tensão preparatória. Ouvir esses papéis é o primeiro passo para a harmonia funcional."),
        b ("7M: repouso sofisticado (tônica)."),
        b ("7: movimento e resolução (dominante)."),
        b ("m7: repouso suave, cor de blues."),
        b ("m7♭5: tensão preparatória (ii do menor)."),

        h ("Tétrades no braço"),
        p (
            "As tétrades são mais desafiadoras no braço do que as tríades, porque quatro notas exigem quatro cordas e, muitas vezes, um alongamento maior da mão. Uma boa estratégia é começar pelas tétrades com a fundamental na 6ª ou na 5ª corda, que caem em posições confortáveis. Com o tempo, você aprende as formas em vários grupos de cordas."),
        b ("Comece com a fundamental na 6ª corda."),
        b ("Depois aprenda as formas com a fundamental na 5ª corda."),
        b ("Treine as quatro notas soando juntas e depois em arpejo."),
        part ("m4_partitura_tetrade", { "C4", "E4", "G4", "B4", "C5" },
              "Partitura da tétrade de Dó7M (Dó–Mi–Sol–Si–Dó)."),

        h ("Tétrades e a escala"),
        p (
            "As tétrades nascem da escala, exatamente como as tríades. Em Dó maior, os sete acordes de sétima são C7M, Dm7, Em7, F7M, G7, Am7 e Bm7♭5. Repare na distribuição: o I e o IV são de sétima maior; o V é dominante; os graus ii, iii e vi são menores com sétima; e o vii é meio-diminuto. Essa é a base da harmonia funcional que você estudará em módulos mais avançados."),
        tbl ({ "Grau", "Acorde em Dó", "Tétrade", "Semitons" }, {
            { "I", "C7M", "sétima maior", "0–4–7–11" },
            { "ii", "Dm7", "menor com sétima", "0–3–7–10" },
            { "iii", "Em7", "menor com sétima", "0–3–7–10" },
            { "IV", "F7M", "sétima maior", "0–4–7–11" },
            { "V", "G7", "sétima dominante", "0–4–7–10" },
            { "vi", "Am7", "menor com sétima", "0–3–7–10" },
            { "vii", "Bm7♭5", "meio-diminuta", "0–3–6–10" },
        }),

        h ("O trítono dentro da dominante"),
        p (
            "O acorde de sétima dominante tem uma característica sonora muito forte: entre a terça e a sétima existe um trítono (6 semitons). Em G7, a terça é Si e a sétima é Fá — a distância entre elas é de 6 semitons. Esse trítono é o que faz o acorde 'pedir' resolução. É por isso que o V7 puxa para o I: a tensão do trítono se resolve quando as duas notas se movem."),
        b ("G7: terça = Si; sétima = Fá; distância = trítono (6 semitons)."),
        b ("O trítono é o motor da resolução do dominante."),
        b ("Ouvir o trítono é ouvir a 'vontade' do acorde de resolver."),
        aud ({ "G3", "B3", "D4", "F4", "C4", "E4", "G4", "C5" },
             "G7 resolve em Dó: o trítono Si–Fá se abre para Dó–Mi."),

        h ("A sétima e o movimento das vozes"),
        p (
            "Quando você vai de um acorde para o outro, as sétimas têm um comportamento previsível: a sétima de um acorde costuma descer um semitom para virar a terça do próximo. Em Dm7 – G7 – C7M, a sétima do Dm7 (Dó) desce para a terça do G7 (Si), e a sétima do G7 (Fá) desce para a terça do C7M (Mi). Essa condução suave é o que faz o ii–V–I soar tão natural."),
        b ("A sétima tende a descer um semitom na passagem."),
        b ("O resultado é uma condução de vozes suave."),
        b ("É a base do acompanhamento de jazz e bossa."),
        img ("m4_formacao_acordes", "Formação de acordes: tríades e tétrades como empilhamento de terças."),

        h ("Tétrade ou tríade: quando usar"),
        p (
            "Não existe resposta única. Em um acompanhamento de rock, as tríades (ou power chords) muitas vezes soam melhores, porque a sétima deixa o som 'ocupado'. Em jazz, bossa nova e MPB, as tétrades são a norma, porque a sétima acrescenta a cor que define o estilo. A escolha depende do estilo e do momento: se você quer clareza, use tríade; se quer riqueza, use tétrade."),
        b ("Rock e pop simples: tríades costumam bastar."),
        b ("Jazz, bossa, MPB: tétrades dão a cor do estilo."),
        b ("Em dúvida, comece pela tríade e acrescente a sétima se pedir."),

        h ("Inversões de tétrades"),
        p (
            "Assim como as tríades, as tétrades podem ser invertidas. Com quatro notas, existem três inversões possíveis além da fundamental (com a terça, a quinta ou a sétima no baixo). As inversões de tétrade são muito usadas em arranjos de jazz para suavizar a condução de vozes e para manter as notas comuns entre acordes vizinhos. O princípio é o mesmo: mudar o baixo, manter as notas."),
        b ("Fundamental: tônica no baixo."),
        b ("1ª inversão: terça no baixo."),
        b ("2ª inversão: quinta no baixo."),
        b ("3ª inversão: sétima no baixo."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é confundir a sétima maior com a dominante. A diferença é de um semitom (11 contra 10), mas o efeito é enorme: a sétima maior repousa, a menor pede resolução. Outro erro é acrescentar a sétima em todos os acordes, deixando o som carregado. E há o erro de omitir notas sem entender: em uma tétrade, a quinta costuma ser a nota mais dispensável, e a terça e a sétima, as essenciais."),
        b ("7M (11 semitons) repousa; 7 (10 semitons) resolve."),
        b ("Nem todo acorde precisa de sétima."),
        b ("Na dúvida, preserve a terça e a sétima; a quinta é dispensável."),

        h ("Tétrades de nona e tensões"),
        p (
            "Depois da sétima, o próximo passo é acrescentar a nona (que é a segunda, uma oitava acima). As tétrades de nona (C7M(9), C7(9), Cm7(9)) são muito comuns no jazz e na MPB, e dão ao acorde um som ainda mais rico sem perder a identidade. Mais adiante vêm a décima primeira e a décima terceira. Por ora, o importante é saber que a sétima é a base: sem ela, as tensões não se sustentam."),
        b ("Nona = segunda uma oitava acima."),
        b ("C7M(9), C7(9), Cm7(9): tétrades com nona."),
        b ("A sétima é a base para todas as outras tensões."),

        h ("Como estudar as tétrades"),
        p (
            "Um bom roteiro é estudar uma família por vez. Comece com a sétima maior, em várias tônicas, e depois passe para a dominante. Toque cada tétrade em arpejo (nota por nota) e depois com as quatro notas juntas. Diga o nome de cada nota em voz alta, para ligar o dedo ao pensamento. Quando as quatro famílias estiverem confortáveis, aplique-as em progressões como o ii–V–I."),
        b ("Uma família por vez: 7M, 7, m7, m7♭5."),
        b ("Arpejo primeiro, depois acorde."),
        b ("Diga o nome das notas enquanto toca."),
        p (
            "Depois de dominar as formas, treine a transposição: pegue a mesma tétrade e toque-a em três tônicas diferentes. Como as receitas são fixas (0–4–7–11, 0–4–7–10, 0–3–7–10, 0–3–6–10), você pode construir qualquer tétrade contando semitons. Essa é a vantagem de entender a formação em vez de decorar formas: o conhecimento vale em qualquer lugar do braço."),

        h ("Aplicação musical"),
        p (
            "Experimente tocar a progressão Dm7 – G7 – C7M. Esse é o famoso ii–V–I, a célula mais importante da música popular. Repare como o Dm7 prepara, o G7 tensiona e o C7M repousa. Toque a mesma progressão com tríades e depois com tétrades, e compare: as tétrades dão a condução suave típica do jazz e da bossa. O app reconhece as notas e confere se a tétrade está correta, aceitando qualquer posição do braço."),
        b ("ii–V–I: preparação, tensão, repouso."),
        b ("Tríades dão clareza; tétrades dão condução."),
        b ("O app confere as notas da tétrade, não a posição."),
        aud ({ "D4", "F4", "A4", "C5", "G3", "B3", "D4", "F4", "C4", "E4", "G4", "B4" },
             "ii–V–I em Dó com tétrades: Dm7, G7 e C7M."),

        h ("Resumo do tópico"),
        b ("Tétrade = tríade + sétima."),
        b ("Sétima maior = 11 semitons (brilho); sétima menor = 10 (tensão)."),
        b ("Principais tétrades: 7M, 7, m7 e m7♭5."),
        b ("O campo harmônico maior gera uma tétrade por grau."),
        b ("Tétrades dão a cor do jazz, da bossa e da MPB."),
        c (
            "Nos exercícios deste tópico, toque as tétrades pedidas no instrumento. O app reconhece as notas e confere o conjunto, então qualquer posição do braço vale."),
    };
}

} // namespace cursomusica::content
