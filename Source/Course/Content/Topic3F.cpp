#include "Course/Content/Topics.h"

// Topic 3F — Levadas com os dedos e mapa da mao direita (Modulo 3, Etapa 3).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 3, bloco F).
namespace cursomusica::content
{

std::vector<ContentItem> topic3F()
{
    return {

        p (
            "Sem palheta, a mão direita usa os dedos. Esse é o mundo do violão, da bossa nova, do choro e de boa parte da música brasileira. Tocar com os dedos dá um controle de vozes que a palheta não oferece: o polegar cuida do baixo enquanto os outros dedos puxam o acorde. Este tópico ensina as levadas com os dedos e o mapa da mão direita que as organiza."),
        p (
            "O segredo do fingerstyle é a independência: cada dedo tem uma função e um grupo de cordas. Quando essa divisão de trabalho está clara, o polegar pode manter o pulso grave enquanto os dedos tocam melodias e acordes agudos ao mesmo tempo. É essa separação que faz a mão direita soar como um pequeno ensemble."),
        c (
            "Objetivo: tocar levadas com os dedos, separando o baixo (polegar) das cordas agudas (indicador, médio, anelar). A independência da mão direita é o que cria a textura do fingerstyle."),

        h ("O mapa da mao direita"),
        p (
            "Na técnica de dedos, cada dedo recebe uma letra e um grupo de cordas. O polegar é p (de polegar), o indicador é i, o médio é m e o anelar é a. Essa nomenclatura vem da tradição do violão clássico e é universal. O polegar cuida das cordas graves (6ª, 5ª e 4ª); o indicador, o médio e o anelar cuidam das cordas agudas (3ª, 2ª e 1ª)."),
        tbl ({ "Dedo", "Letra", "Cordas" }, {
            { "Polegar", "p", "6a, 5a, 4a (graves)" },
            { "Indicador", "i", "3a corda" },
            { "Medio", "m", "2a corda" },
            { "Anelar", "a", "1a corda" },
        }),
        b ("p (polegar): cordas graves — o baixo do acorde."),
        b ("i (indicador), m (médio), a (anelar): cordas agudas."),
        b ("Cada dedo cuida do seu grupo: é a base da independência."),
        img ("m3_mapa_mao_direita", "O mapa da mão direita: cada dedo cuida de um grupo de cordas."),
        c (
            "A letra do dedo aparece nas partituras de violão. Saber lê-las é essencial para estudar o repertório de dedos, da bossa ao choro."),

        h ("A posicao da mao e do pulso"),
        p (
            "A posição da mão direita é diferente da palhetada. A mão fica mais próxima das cordas, com o pulso ligeiramente arqueado e os dedos curvados. O polegar toca com a lateral, descendo em direção ao chão; os dedos puxam as cordas para dentro da mão, em um movimento suave. Não se toca com as unhas se elas não estiverem cuidadas; o som pode vir da polpa do dedo ou da unha, conforme o timbre desejado."),
        b ("Pulso levemente arqueado, mão próxima às cordas."),
        b ("Polegar com a lateral; dedos puxando para dentro."),
        b ("O som vem da polpa (mais suave) ou da unha (mais brilhante)."),
        c (
            "A mão não deve ficar apoiada no cavalete como na palhetada. No fingerstyle, a mão 'flutua' sobre as cordas, livre para trabalhar as vozes."),

        h ("A levada basica: polegar + dedos"),
        p (
            "A levada mais comum do fingerstyle separa o baixo e o acorde. O polegar alterna as cordas graves (tocando a tônica e a quinta do acorde, por exemplo) nos tempos, enquanto os dedos puxam as cordas agudas nos contratempos. O resultado é um acompanhamento completo, com baixo e harmonia soando ao mesmo tempo."),
        tbl ({ "Tempo", "Polegar (p)", "Dedos (i/m/a)" }, {
            { "1", "baixo (tonica)", "-" },
            { "e", "-", "i (3a corda)" },
            { "2", "baixo (quinta)", "-" },
            { "e", "-", "m (2a corda)" },
            { "3", "baixo (tonica)", "-" },
            { "e", "-", "a (1a corda)" },
        }),
        b ("Polegar nos tempos: o baixo sustenta o pulso."),
        b ("Dedos nos contratempos: o acorde aparece entre os baixos."),
        b ("Separar grave e agudo é o que dá independência à mão."),
        img ("m3_levadas_dedos", "Levadas com os dedos: padrões que separam o baixo (polegar) das cordas agudas."),
        aud ({ "C4", "E4", "G4", "C5", "G4", "E4", "C4", "G3" }, "Arpejo de Dó maior com os dedos: baixo e acorde alternando."),

        h ("Arpejos: o acorde repartido"),
        p (
            "Em vez de tocar o acorde inteiro de uma vez, você pode tocar as notas uma a uma: isso é um arpejo. Com os dedos, o arpejo fica natural, porque cada nota tem o seu dedo. O arpejo ascendente (p, i, m, a) e o descendente (a, m, i, p) são os desenhos básicos, e aparecem em quase toda levada de fingerstyle."),
        b ("Arpejo ascendente: p (baixo), i, m, a (agudas)."),
        b ("Arpejo descendente: a, m, i, p."),
        b ("Arpejo é o acorde repartido no tempo."),
        c (
            "O arpejo é a ponte entre o acorde e a melodia: ele preenche o tempo sem que você precise de outra voz."),

        h ("Levadas de bossa nova"),
        p (
            "A bossa nova tem uma levada característica: o polegar marca os baixos (tônica e quinta) nos tempos, e os dedos puxam o acorde nas síncopes. Essa separação estrita entre grave e agudo é o que dá o balanço da bossa. Além disso, a bossa usa acordes com tensões (nona, décima terceira) e uma batida sincopada que exige muita precisão rítmica."),
        b ("Polegar: tônica e quinta nos tempos 1 e 3."),
        b ("Dedos: acorde nas síncopes (contratempo)."),
        b ("Síncope brasileira exige grade própria de medição."),
        c (
            "A levada de bossa é um dos maiores desafios rítmicos do violão brasileiro: exige independência total entre o polegar e os dedos."),

        h ("Travis picking e hybrid picking"),
        p (
            "O Travis picking é uma técnica de country em que o polegar alterna dois baixos enquanto os dedos tocam uma melodia. O hybrid picking combina palheta (cordas graves) e dedos (cordas agudas), unindo o ataque forte da palheta ao controle dos dedos. Ambas mostram como a mão direita pode trabalhar em camadas, com funções independentes."),
        tbl ({ "Tecnica", "Graves", "Agudos" }, {
            { "Fingerstyle", "polegar", "indicador, medio, anelar" },
            { "Travis picking", "polegar alternando", "indicador e medio" },
            { "Hybrid picking", "palheta", "dedos" },
        }),
        b ("Travis: o polegar vira um baixo em movimento."),
        b ("Hybrid: palheta nos graves, dedos nos agudos."),
        b ("Trabalhar em camadas dá textura ao acompanhamento."),

        h ("Erros comuns nas levadas de dedos"),
        p (
            "Os erros mais comuns são prender o polegar em uma corda só, tensionar a mão durante os arpejos e perder o pulso ao alternar grave e agudo. Outro erro é tocar o acorde agudo 'de uma vez' em vez de arpejar, o que achata a textura. Paciência e andamento lento corrigem tudo isso."),
        b ("Polegar preso em uma corda: falte o movimento do baixo."),
        b ("Tensão na mão durante os arpejos."),
        b ("Perder o pulso ao alternar grave e agudo."),
        b ("Tocar o acorde agudo de uma vez, sem arpejar."),
        c (
            "Dica: estude o polegar sozinho, marcando o baixo, antes de acrescentar os dedos. Depois, acrescente um dedo por vez. A independência se constrói por camadas."),

        h ("Como praticar levadas com os dedos"),
        p (
            "Comece com o polegar sozinho, alternando duas cordas graves no pulso. Depois acrescente o indicador, depois o médio e o anelar, sempre com o polegar firme. Só então junte tudo em um arpejo completo. Este módulo usa BPM meta 68: um andamento calmo que permite ouvir cada voz da mão direita."),
        b ("Polegar sozinho: o baixo no pulso."),
        b ("Acrescente um dedo por vez, mantendo o polegar."),
        b ("Junte em arpejo ascendente e descendente."),
        b ("Leve para a levada de bossa com síncope."),
        part ("m3_partitura_dedos", { "C4", "E4", "G4", "C5", "G4", "E4", "C4", "G3" },
              "Partitura: arpejo com os dedos em Dó maior. O polegar marca o baixo, os dedos o acorde."),

        h ("Resumo do topico"),
        b ("No fingerstyle, cada dedo tem uma função: p nos graves, i/m/a nos agudos."),
        b ("A levada básica separa o baixo (polegar) do acorde (dedos)."),
        b ("Arpejos repartem o acorde no tempo, uma nota por dedo."),
        b ("A bossa nova usa polegar nos tempos e dedos nas síncopes."),
        b ("Independência da mão direita é a base da textura de dedos."),
        c (
            "Nos exercícios, você tocará levadas de dedos na grade do metrônomo. O app mede o alinhamento e confere se o pulso se manteve firme."),

        h ("Timbres: polpa, unha e posicao da mao"),
        p (
            "A mão direita controla o timbre do som de dedos. Tocar com a polpa do dedo produz som suave e redondo; tocar com a unha produz som brilhante e definido. A posição da mão também importa: perto do cavalete o som fica mais metálico e curto; perto do braço, mais doce e sustentado. Aprender a variar o timbre é parte de tocar com expressão."),
        tbl ({ "Ponto de ataque", "Timbre", "Uso" }, {
            { "polpa do dedo", "suave, redondo", "bossa, balada" },
            { "unha", "brilhante, definido", "choro, solo de dedos" },
            { "perto do cavalete", "metalico, curto", "samba, ritmo" },
            { "perto do braco", "doce, sustentado", "melodia, acompanhamento" },
        }),
        b ("Polpa: som suave. Unha: som brilhante."),
        b ("Perto do cavalete: curto. Perto do braço: sustentado."),
        b ("O timbre é uma escolha, não um acidente."),
        c (
            "Ouvir grandes violonistas mostra que o timbre muda a cada frase. A mão direita é o 'pincel' do som: onde e como você toca define a cor."),

        h ("Polifonia: tocando duas vozes ao mesmo tempo"),
        p (
            "A grande vantagem dos dedos é tocar duas coisas ao mesmo tempo. O polegar mantém um baixo (uma linha melódica grave) enquanto os dedos tocam um acorde ou uma melodia aguda. Isso cria uma polifonia: duas vozes soando juntas, cada uma com o seu ritmo. É o que permite a um único violão soar como acompanhamento e melodia ao mesmo tempo."),
        b ("Voz grave: o polegar, com uma linha de baixo."),
        b ("Voz aguda: os dedos, com acorde ou melodia."),
        b ("As duas vozes podem ter ritmos diferentes."),
        c (
            "Tocar duas vozes independentes é o objetivo maior do fingerstyle. Comece separando-as no estudo e junte aos poucos — a independência é construída, não nasce pronta."),

        h ("Levada de dedos para baixo (baixo alternado)"),
        p (
            "Uma levada muito usada em baladas e no violão de acompanhamento é o baixo alternado: o polegar toca a tônica e a quinta do acorde, alternadamente, em cada tempo, enquanto os dedos puxam as cordas agudas nos contratempos. O resultado é um 'balanço' constante, como uma valsa em câmera lenta, que sustenta a melodia da voz."),
        b ("Tônica no tempo 1, quinta no tempo 2, tônica no 3..."),
        b ("Os dedos preenchem os contratempos com o acorde."),
        b ("É a levada clássica do violão de acompanhamento."),
        aud ({ "C4", "G4", "C4", "G4", "E4", "C4", "E4", "C4" }, "Baixo alternado em Dó: tônica e quinta no polegar, acorde nos dedos."),

        h ("Transicao da palheta para os dedos"),
        p (
            "Muitos guitarristas começam com palheta e depois descobrem os dedos. A transição exige desaprender alguns hábitos: a mão deixa de ficar apoiada e passa a flutuar; o ataque deixa de ser 'para baixo' e passa a ser 'para dentro'. Vá com calma e trate os dedos como uma técnica nova, começando do zero, sem pressa."),
        b ("A mão flutua, não fica apoiada no cavalete."),
        b ("O ataque é para dentro, não para baixo."),
        b ("Trate como técnica nova: comece devagar."),
        c (
            "Quem domina as duas técnicas ganha liberdade: pode escolher palheta ou dedos conforme a música pede, sem depender de uma só."),
    };
}

} // namespace cursomusica::content
