#include "Course/Content/Topics.h"

// Topic 8I — Progressão II-V-I maior e menor (Módulo 8, Etapa 8).
// Fonte de verdade do texto: .agents/agents/mc-modulo-8.md (Etapa 8, tópico I).
namespace cursomusica::content
{

std::vector<ContentItem> topic8I()
{
    return {

        p (
            "O II-V-I é a progressão mais importante da música tonal. Ela reúne, numa única célula, as três funções harmônicas: a subdominante (II), o dominante (V) e a tônica (I). Quase toda música popular e todo standard de jazz usam o II-V-I em algum momento. Entender essa progressão é entender a espinha dorsal da harmonia."),
        p (
            "Neste módulo você já estudou cada peça do II-V-I separadamente: o dominante, os dominantes secundários, as substituições. Agora você junta tudo. O II-V-I maior e o II-V-I menor são as duas formas básicas, e a diferença entre elas está na qualidade dos acordes, que vêm das escalas maior e menor."),
        c (
            "Objetivo do tópico: compreender a progressão II-V-I nas formas maior e menor, o voice leading que a conduz e como ela fecha uma frase."),

        h ("A forma maior: Dm7 → G7 → CM7"),
        p (
            "No II-V-I maior de Dó, o II é Dm7, o V é G7 e o I é CM7. O ii prepara, o V tensiona e o I resolve. O que faz a progressão funcionar é o movimento das vozes: cada nota instável caminha por meio-tom para uma nota estável do acorde seguinte. Esse encadeamento suave é o que dá a sensação de fluidez."),
        b ("II: Dm7 (Ré, Fá, Lá, Dó)."),
        b ("V: G7 (Sol, Si, Ré, Fá)."),
        b ("I: CM7 (Dó, Mi, Sol, Si)."),
        img ("m8_ii_v_i", "O II-V-I maior: o baixo sobe em quartas (Ré–Sol–Dó) e as vozes se conduzem por meio-tom."),

        h ("O voice leading do II-V-I maior"),
        p (
            "O voice leading (condução de vozes) é o segredo do II-V-I. Observe o que acontece: o Fá do Dm7 permanece como Fá do G7 (é a sétima do dominante); o Dó do Dm7 desce para o Si do G7 (a terça do dominante). No passo seguinte, o Fá do G7 desce para o Mi do CM7 (terça do acorde de chegada) e o Si do G7 permanece como Si do CM7 (sétima maior). São movimentos mínimos, de um semitom."),
        b ("Dm7 → G7: o Fá fica, o Dó desce para Si."),
        b ("G7 → CM7: o Fá desce para Mi, o Si fica."),
        b ("Cada nota anda o mínimo possível: por isso soa fluido."),
        tbl ({ "Acorde", "Notas", "Movimento" }, {
            { "Dm7", "D, F, A, C", "—" },
            { "G7", "G, B, D, F", "F fica; C → B" },
            { "CM7", "C, E, G, B", "F → E; B fica" },
        }),

        h ("A forma menor: Dm7b5 → G7 → Cm7"),
        p (
            "No II-V-I menor de Dó, o II é Dm7b5 (meio-diminuto), o V é G7 (dominante) e o I é Cm7. A grande diferença está no II: ele tem a quinta diminuta (Lá bemol), que dá a cor menor. O dominante pode ganhar a nona menor (b9) para casar com o Lá bemol do ii. A tônica é menor, com a terça bemol (Mi bemol)."),
        b ("II: Dm7b5 (Ré, Fá, Lá bemol, Dó)."),
        b ("V: G7 ou G7b9 (Sol, Si, Ré, Fá)."),
        b ("I: Cm7 (Dó, Mi bemol, Sol, Si bemol)."),
        aud ({ "D3", "F3", "G#3", "C4", "G3", "B3", "D4", "F4", "C3", "Eb3", "G3" },
             "II-V-I menor: Dm7b5 → G7 → Cm7. Ouça a cor sombria e a resolução."),

        h ("Comparando maior e menor"),
        p (
            "As duas formas são idênticas na estrutura (II-V-I), mas opostas na cor. No maior, a terça é natural (Mi) e o ii tem quinta justa (Lá); no menor, a terça é bemol (Mi bemol) e o ii tem quinta diminuta (Lá bemol). Essas duas notas bemóis — Mi bemol e Lá bemol — são o que separa o mundo luminoso do mundo sombrio."),
        tbl ({ "Grau", "Maior (Dó)", "Menor (Dó)" }, {
            { "II", "Dm7", "Dm7b5" },
            { "V", "G7", "G7 (ou G7b9)" },
            { "I", "CM7", "Cm7" },
            { "3ª da tônica", "Mi (natural)", "Mi bemol" },
            { "5ª do ii", "Lá (justa)", "Lá bemol" },
        }),

        h ("O II-V-I com substituições"),
        p (
            "Nos tópicos anteriores você aprendeu as substituições. Agora elas entram no II-V-I. O V7 pode virar SubV7 (Db7), o ii pode virar SubIIm (Dm7b5), e o ii e o V podem ser trocados ao mesmo tempo. Cada combinação produz uma cor diferente, e todas fecham a frase. O II-V-I é o laboratório onde você aplica tudo o que estudou."),
        b ("II-V-I tradicional: Dm7 → G7 → CM7."),
        b ("Com SubV7: Dm7 → Db7 → CM7."),
        b ("Com SubIIm: Dm7b5 → G7b9 → CM7."),
        b ("Com os dois: Dm7b5 → Db7 → CM7."),
        img ("m8_ii_v_i_substituicoes", "O II-V-I e as suas substituições: o baixo pode subir em quartas ou descer em semitons."),

        h ("O II-V-I como célula de frases"),
        p (
            "O II-V-I aparece em muitos contextos. No fim de uma frase, ele fecha; no meio, ele prepara uma nova seção. Pode aparecer completo (três acordes), ou reduzido (só o V-I, ou só o ii-V). Reconhecer essas formas reduzidas é fundamental para tocar standards, porque muitos trechos usam apenas parte da célula."),
        b ("Completo: ii → V → I (três acordes)."),
        b ("Reduzido: V → I (dois acordes)."),
        b ("Meia cadência: ii → V (sem resolver)."),
        c (
            "Regra prática: sempre que você encontrar um ii seguido de V, procure o I logo adiante. Se ele não vier, a cadência foi interrompida (resolução deceptiva)."),

        h ("Identificando o II-V-I de ouvido"),
        p (
            "O II-V-I tem uma sonoridade característica: preparação, tensão, repouso. O ouvido reconhece a chegada, mesmo sem saber os nomes dos acordes. Treine ouvindo progressões e identificando o momento em que a música \"chega em casa\". Esse ponto é o I, e o que vem antes é o ii e o V."),
        b ("Ouça a progressão e localize o repouso (o I)."),
        b ("O acorde imediatamente anterior é o V."),
        b ("O anterior ao V é o ii."),
        aud ({ "D3", "F3", "A3", "C4", "G3", "B3", "D4", "F4", "C4", "E4", "G4" },
             "II-V-I maior tocado como arpejos: ouça a preparação, a tensão e o repouso."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é tocar o II-V-I sem perceber o voice leading, tocando os acordes como blocos independentes. Outro erro é não distinguir a forma maior da menor, o que faz a resolução soar errada. Preste atenção à terça do acorde de chegada: natural (maior) ou bemol (menor)."),
        b ("Ouça o movimento das vozes, não só os acordes."),
        b ("Confira a terça do I: natural ou bemol?"),
        b ("Toque o arpejo para ouvir cada nota."),
        c (
            "Dica: comece tocando as três notas-guia (terça e sétima de cada acorde). Elas conduzem a progressão."),

        h ("Aplicação prática"),
        p (
            "Pratique o II-V-I nas duas formas, em várias tonalidades. Comece em Dó, depois em Sol, em Fá, em Lá. Toque primeiro como acordes, depois como arpejos, depois aplicando substituições. No instrumento, use o app para conferir se os acordes que você toca formam a progressão correta."),
        b ("Toque o II-V-I maior em Dó, Sol e Fá."),
        b ("Toque o II-V-I menor em Dó, Sol e Fá."),
        b ("Aplique o SubV7 e o SubIIm e compare."),
        part ("m8_partitura_ii_v_i", { "D3", "F3", "A3", "C4", "G3", "B3", "D4", "F4", "C4", "E4", "G4" },
              "Partitura do II-V-I maior (Dm7 – G7 – CM7). Ouça a preparação, a tensão e o repouso."),

        h ("O II-V-I em outras tonalidades"),
        p (
            "O II-V-I existe em todas as tonalidades. Em Sol maior, é Am7 → D7 → GM7; em Fá maior, é Gm7 → C7 → FM7; em Si bemol maior, é Cm7 → F7 → BbM7. No menor, em Lá menor é Bm7b5 → E7 → Am7; em Ré menor, é Em7b5 → A7 → Dm7. Aprender o II-V-I em todos os tons é o que permite tocar qualquer música."),
        b ("Dó maior: Dm7 → G7 → CM7."),
        b ("Sol maior: Am7 → D7 → GM7."),
        b ("Fá maior: Gm7 → C7 → FM7."),
        b ("Lá menor: Bm7b5 → E7 → Am7."),
        tbl ({ "Tonalidade", "II", "V", "I" }, {
            { "Dó maior", "Dm7", "G7", "CM7" },
            { "Sol maior", "Am7", "D7", "GM7" },
            { "Fá maior", "Gm7", "C7", "FM7" },
            { "Dó menor", "Dm7b5", "G7", "Cm7" },
            { "Lá menor", "Bm7b5", "E7", "Am7" },
        }),

        h ("O II-V-I na guitarra"),
        p (
            "No instrumento, o II-V-I pode ser tocado de várias formas: como acordes, como arpejos, ou com as notas-guia (terça e sétima). Tocar as notas-guia é a forma mais eficiente de acompanhar, porque são elas que definem a qualidade dos acordes e conduzem a progressão. Praticar o II-V-I em várias posições do braço é essencial para a fluência."),
        b ("Tocar como acordes, na região que preferir."),
        b ("Tocar como arpejos, para ouvir cada nota."),
        b ("Tocar as notas-guia (terça e sétima) para o voice leading."),
        aud ({ "D3", "F3", "A3", "C4", "G3", "B3", "D4", "F4", "C4", "E4", "G4" },
             "II-V-I maior como arpejos: ouça a preparação, a tensão e o repouso."),

        h ("O II-V-I e a improvisação"),
        p (
            "Na improvisação, o II-V-I guia as escolhas melódicas. Sobre o ii, você toca as notas do campo maior (ou da escala dórica); sobre o V, as tensões (b9, #9, #11); sobre o I, as notas do repouso. Perceber essa mudança de cor é o que faz a improvisação soar conectada à harmonia, em vez de solta."),
        b ("Sobre o ii: escala dórica (ou as notas do campo)."),
        b ("Sobre o V: mixolídia ou alterada (tensões)."),
        b ("Sobre o I: notas do repouso (tônica, terça, quinta, sétima)."),
        c (
            "Dica: toque as notas-guia com a mão esquerda e improvise com a direita. O ouvido aprende a ligar melodia e harmonia."),

        h ("O II-V-I e a forma da música"),
        p (
            "O II-V-I aparece em pontos previsíveis da forma de uma música. No fim de cada seção, uma cadência fecha a frase. Em standards, o II-V-I costuma aparecer nos últimos dois compassos, criando a sensação de chegada. Reconhecer onde as cadências estão é o que permite acompanhar uma música inteira sem se perder, mesmo sem decorá-la."),
        b ("Fins de seção: cadências fecham a frase."),
        b ("Turnarounds: preparam a volta ao início."),
        b ("Meios de frase: meias cadências mantêm o movimento."),
        tbl ({ "Posição", "Tipo", "Efeito" }, {
            { "Fim da música", "II-V-I completo", "fecha" },
            { "Fim de seção", "II-V-I ou V-I", "prepara a volta" },
            { "Meio da frase", "II-V", "mantém o movimento" },
        }),

        h ("O II-V-I menor com dominante alterado"),
        p (
            "No II-V-I menor, o dominante costuma ser alterado. G7b9 ou G7alt casam com a cor menor e resolvem com mais força. A nona menor (Ab) do G7b9 é justamente a quinta diminuta do Dm7b5, o que liga os dois acordes. Usar o dominante alterado no II-V-I menor é a prática mais comum e a que soa mais coerente."),
        b ("II-V-I menor: Dm7b5 → G7b9 → Cm7."),
        b ("O Ab do G7b9 liga-se ao Ab do Dm7b5."),
        b ("O dominante alterado dá mais tensão à resolução menor."),
        aud ({ "D3", "F3", "G#3", "C4", "G3", "B3", "D4", "F4", "G#4", "C3", "Eb3", "G3" },
             "II-V-I menor com G7b9: o dominante alterado resolvendo na tônica menor."),

        h ("O II-V-I e as notas-guia"),
        p (
            "As notas-guia de um acorde são a terça e a sétima. São elas que definem a qualidade (maior, menor, dominante) e são elas que conduzem a progressão por meio-tom. Tocar apenas as notas-guia do II-V-I é um exercício excelente: você ouve a essência da cadência sem as notas de preenchimento. É o esqueleto da harmonia."),
        b ("Dm7: notas-guia Fá (terça) e Dó (sétima)."),
        b ("G7: notas-guia Si (terça) e Fá (sétima)."),
        b ("CM7: notas-guia Mi (terça) e Si (sétima)."),
        b ("O Fá permanece do Dm7 ao G7; o Si permanece do G7 ao CM7."),
        aud ({ "F3", "C4", "B3", "F4", "E4", "B4" },
             "Notas-guia do II-V-I: o esqueleto da cadência, conduzido por meio-tom."),

        h ("Resumo do tópico"),
        b ("O II-V-I reúne as três funções: subdominante, dominante e tônica."),
        b ("Forma maior: Dm7 → G7 → CM7."),
        b ("Forma menor: Dm7b5 → G7 → Cm7."),
        b ("O voice leading conduz as vozes por meio-tom."),
        b ("As substituições podem trocar o ii e o V sem perder a função."),
        c (
            "Nos exercícios deste tópico, toque o II-V-I no instrumento e confira com o app. Ele reconhece as notas e verifica se a progressão está correta."),
    };
}

} // namespace cursomusica::content
