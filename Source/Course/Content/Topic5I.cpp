#include "Course/Content/Topics.h"

// Topic 5I — Modos gerados pela escala maior (Módulo 5, Etapa 5).
// Fonte de verdade do texto: .agents/agents/mc-modulo-5.md (Etapa 5, topico I); dados fixados em docs/MUSIC.md (nivel 3, BPM 76, on_grid 0,79).
namespace cursomusica::content
{

std::vector<ContentItem> topic5I()
{
    return {

        p (
            "Se você tocar a escala de Dó maior começando e terminando em notas diferentes, cada uma dessas versões soa com uma cor própria. Esses são os modos gerados pela escala maior: sete maneiras de organizar as mesmas notas, cada uma com um centro diferente. Entender os modos é entender por que a mesma escala pode produzir sete climas distintos."),
        p (
            "Este tópico apresenta os sete modos, a relação deles com os graus da escala maior e o caráter de cada um. É o tópico que fecha a teoria do módulo e abre caminho para a improvisação, porque os modos são exatamente as cores que você vai usar sobre cada acorde do campo harmônico."),

        h ("O que são modos"),
        p (
            "Modo é uma escala obtida a partir de outra, começando em um grau diferente. Quando você toca as notas de Dó maior começando em Ré, obtém o modo dórico; começando em Mi, o frígio; em Fá, o lídio; em Sol, o mixolídio; em Lá, o eólio; em Si, o lócrio. As notas são as mesmas — o que muda é onde está o centro e, portanto, o padrão de tons e semitons percebido."),
        p (
            "A ideia central é que a mesma coleção de notas gera sons diferentes conforme a tônica escolhida. Isso acontece porque o padrão de tons e semitons passa a cair em outras posições, criando intervalos característicos em cada modo. É esse intervalo característico que dá a cada modo a sua identidade sonora."),
        b ("Modo = escala começando em outro grau da escala maior."),
        b ("As notas são as mesmas; o centro (tônica) é que muda."),
        b ("Cada modo tem um intervalo característico que define a sua cor."),
        img ("m5_modos_escala", "Os sete modos gerados pela escala maior: mesmas notas, centros diferentes."),

        h ("Os sete modos e os seus graus"),
        p (
            "Cada modo nasce de um grau da escala maior. O primeiro grau gera o jônio (a própria escala maior); o segundo, o dórico; o terceiro, o frígio; o quarto, o lídio; o quinto, o mixolídio; o sexto, o eólio (a escala menor natural); e o sétimo, o lócrio. Essa ordem é fixa e vale para qualquer tonalidade."),
        p (
            "Repare que dois desses modos você já conhece bem: o jônio é a escala maior e o eólio é a escala menor natural. Os outros cinco são cores intermediárias, cada uma com um tempero próprio. Aprender a ouvi-los é aprender a distinguir, por exemplo, um som 'maior com um toque triste' (dórico) de um som 'maior brilhante' (lídio)."),
        tbl ({ "Grau", "Modo", "Notas em Dó maior", "Intervalo característico" }, {
            { "I", "Jônio (maior)", "Dó Ré Mi Fá Sol Lá Si", "—" },
            { "II", "Dórico", "Ré Mi Fá Sol Lá Si Dó", "6ª maior" },
            { "III", "Frígio", "Mi Fá Sol Lá Si Dó Ré", "2ª menor (b9)" },
            { "IV", "Lídio", "Fá Sol Lá Si Dó Ré Mi", "4ª aumentada" },
            { "V", "Mixolídio", "Sol Lá Si Dó Ré Mi Fá", "7ª menor" },
            { "VI", "Eólio (menor)", "Lá Si Dó Ré Mi Fá Sol", "6ª menor" },
            { "VII", "Lócrio", "Si Dó Ré Mi Fá Sol Lá", "5ª diminuta" },
        }),
        c (
            "A regra de ouro: os modos usam as MESMAS notas da escala maior. O que muda é a nota de partida — e isso muda o padrão de tons e semitons percebido, criando a cor de cada modo."),
        aud ({ "C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5" },
             "Jônio (Dó maior): a escala maior começando na tônica."),
        aud ({ "D4", "E4", "F4", "G4", "A4", "B4", "C5", "D5" },
             "Dórico: as mesmas notas, começando em Ré. Compare a cor com o jônio."),

        h ("O caráter de cada modo"),
        p (
            "Cada modo tem um caráter reconhecível. O jônio é claro e resolvido; o dórico é menor, mas com um brilho (a sexta maior) que o torna menos triste; o frígio é sombrio e tenso (a segunda menor); o lídio é brilhante e sonhador (a quarta aumentada); o mixolídio é maior, mas com um toque de blues (a sétima menor); o eólio é o menor natural, melancólico; e o lócrio é instável e quase nunca usado como centro."),
        p (
            "Reconhecer o caráter dos modos é o que permite escolher a cor certa para cada acorde. Sobre um acorde de Ré menor, por exemplo, o dórico soa mais rico que o eólio, porque a sexta maior adiciona um brilho. Sobre um acorde dominante, o mixolídio é o modo natural. Essas escolhas são a base da improvisação modal."),
        b ("Jônio: maior, claro, resolvido."),
        b ("Dórico: menor com brilho (6ª maior)."),
        b ("Frígio: sombrio (2ª menor). Lídio: brilhante (4ª aumentada)."),
        b ("Mixolídio: maior com blues (7ª menor). Eólio: menor natural."),
        b ("Lócrio: instável, raramente usado como centro."),
        aud ({ "E4", "F4", "G4", "A4", "B4", "C5", "D5", "E5" },
             "Frígio: começando em Mi, com a segunda menor que dá o som sombrio."),
        aud ({ "F4", "G4", "A4", "B4", "C5", "D5", "E5", "F5" },
             "Lídio: começando em Fá, com a quarta aumentada que dá o brilho."),

        h ("Modos e acordes do campo harmônico"),
        p (
            "Cada acorde do campo harmônico tem um modo que combina com ele. Sobre o acorde de I, você usa o jônio; sobre o ii, o dórico; sobre o iii, o frígio; sobre o IV, o lídio; sobre o V, o mixolídio; sobre o vi, o eólio; e sobre o vii°, o lócrio. Essa correspondência é direta: o modo de cada grau é a escala maior começando naquele grau."),
        p (
            "Isso significa que, ao improvisar sobre uma progressão do campo harmônico, você pode trocar de modo a cada acorde — ou manter o jônio da tonalidade e simplesmente realçar as notas do acorde. As duas abordagens funcionam, mas a troca de modo dá mais cor, porque cada acorde recebe a escala que realmente combina com ele."),
        tbl ({ "Acorde (Dó maior)", "Grau", "Modo para improvisar" }, {
            { "C", "I", "jônio" },
            { "Dm", "ii", "dórico" },
            { "Em", "iii", "frígio" },
            { "F", "IV", "lídio" },
            { "G", "V", "mixolídio" },
            { "Am", "vi", "eólio" },
            { "Bdim", "vii°", "lócrio" },
        }),

        h ("Ouvindo a diferença entre os modos"),
        p (
            "A melhor forma de entender modos é ouvir. Toque a escala de Dó maior e depois toque as mesmas notas começando em Ré. O som muda completamente: o que era claro e resolvido fica mais melancólico, mas com um brilho. Repita o processo começando em cada grau e você ouvirá as sete cores da escala maior."),
        p (
            "A diferença fica ainda mais clara quando você sustenta um acorde de fundo. Toque um acorde de Ré menor e, sobre ele, toque as notas de Dó maior começando em Ré: você ouvirá o dórico. Toque um acorde de Sol e as mesmas notas começando em Sol: você ouvirá o mixolídio. O acorde de fundo é o que define qual modo o ouvido percebe."),
        b ("Toque a escala começando em cada grau e compare as cores."),
        b ("Sustente um acorde de fundo para ouvir o modo correspondente."),
        b ("O acorde de fundo define qual modo o ouvido percebe."),
        aud ({ "G4", "A4", "B4", "C5", "D5", "E5", "F5", "G5" },
             "Mixolídio: começando em Sol, com a sétima menor que dá o toque de blues."),

        h ("Modos na guitarra"),
        p (
            "No braço, os modos são as mesmas posições da escala maior, começando em pontos diferentes. Como a guitarra tem várias formas para a escala maior (as formas do CAGED), cada uma delas corresponde a um modo. Isso facilita muito: você não precisa aprender sete escalas novas — precisa aprender a começar a mesma escala em pontos diferentes."),
        p (
            "Os exercícios deste tópico pedem que você toque os modos no instrumento e o app confere as notas. Como todos os modos usam as mesmas notas da escala maior, o app verifica se você tocou o padrão certo a partir da tônica do modo escolhido — confirmando que você entendeu a relação entre os modos e a escala que os gera."),
        b ("Os modos são as mesmas posições da escala, começando em pontos diferentes."),
        b ("Cada forma do CAGED corresponde a um modo."),
        b ("Toque o modo a partir da sua tônica e confirme com o app."),
        part ("m5_partitura_modo", { "D4", "E4", "F4", "G4", "A4", "B4", "C5", "D5" },
              "Partitura do modo dórico: as notas de Dó maior começando em Ré."),

        h ("Modos e percepção auditiva"),
        p (
            "Treinar o ouvido para os modos é um passo além de reconhecer funções. Cada modo tem um intervalo característico que o define: o dórico tem a sexta maior, o frígio a segunda menor, o lídio a quarta aumentada, o mixolídio a sétima menor, o eólio a sexta menor e o lócrio a quinta diminuta. Ouvir esse intervalo é o que permite distinguir um modo do outro."),
        p (
            "O melhor exercício é tocar um acorde de fundo e experimentar as notas do modo sobre ele. Sobre um acorde de Ré menor, toque o dórico e depois o eólio e compare: o dórico soa mais brilhante por causa da sexta maior. Esse tipo de comparação direta é a forma mais eficaz de internalizar a cor de cada modo."),
        b ("Cada modo tem um intervalo característico que o define."),
        b ("Toque um acorde de fundo e experimente as notas do modo sobre ele."),
        b ("Comparar dois modos sobre o mesmo acorde revela a diferença de cor."),
        aud ({ "D4", "E4", "F4", "G4", "A4", "B4", "C5", "D5" },
             "Dórico a partir de Ré: o brilho da sexta maior (Si) sobre o acorde de Ré menor."),

        h ("Modos e repertório"),
        p (
            "Os modos aparecem o tempo todo no repertório, mesmo quando ninguém os chama pelo nome. O som 'maior com um toque de blues' de muitas músicas de rock é o mixolídio; o som 'menor com brilho' de muitas músicas de jazz e MPB é o dórico. Reconhecer essas cores permite improvisar com muito mais propriedade sobre o repertório real."),
        p (
            "Para o guitarrista, os modos são também uma forma de organizar o braço. Como cada modo corresponde a uma posição da escala maior começando em um grau diferente, aprender os modos é aprender a tocar a mesma escala em todas as regiões. Isso amplia muito a liberdade de improvisação e de acompanhamento."),
        b ("Os modos aparecem no repertório mesmo sem serem nomeados."),
        b ("Mixolídio = som maior com blues; dórico = menor com brilho."),
        b ("Cada modo é uma região do braço começando em um grau diferente."),

        h ("Modos e o centro da música"),
        p (
            "Uma questão importante sobre modos é que eles mudam a sensação de centro da música. Quando você toca as notas de Dó maior começando e terminando em Ré, o ouvido passa a sentir Ré como o repouso, mesmo que as notas sejam as mesmas. É por isso que os modos são tão úteis para criar músicas que não soam nem totalmente maiores nem totalmente menores."),
        p (
            "Esse deslocamento do centro é o que diferencia o modalismo da tonalidade clássica. Na música modal, o centro é estabelecido pela repetição e pela ênfase, e não pela cadência dominante. É o que acontece em boa parte do rock, do folk e da música brasileira: a música orbita um centro modal em vez de resolver por cadências."),
        b ("Nos modos, o centro é estabelecido pela repetição e ênfase."),
        b ("O mesmo conjunto de notas pode ter centros diferentes."),
        b ("O modalismo aparece muito no rock, no folk e na música brasileira."),

        h ("Modos, escala e acorde"),
        p (
            "A relação entre modo, escala e acorde é o que fecha o entendimento. Cada acorde do campo harmônico combina com o modo do seu grau: sobre o I, jônio; sobre o ii, dórico; e assim por diante. Isso significa que, ao trocar de acorde numa progressão, você pode trocar de modo — mantendo a escala da tonalidade, mas mudando o ponto de partida."),
        p (
            "Na prática, existem duas abordagens para improvisar sobre uma progressão: manter a escala da tonalidade durante toda a música (visão tonal) ou trocar de modo a cada acorde (visão modal). As duas funcionam, e a escolha depende do estilo e do efeito desejado. O importante é entender que os modos e o campo harmônico são duas leituras do mesmo material."),
        b ("Cada acorde do campo combina com o modo do seu grau."),
        b ("Visão tonal: uma escala para toda a música."),
        b ("Visão modal: um modo por acorde."),
        c (
            "Modos e campo harmônico não são coisas separadas: são duas formas de olhar para as mesmas sete notas. Um é o mapa dos acordes; o outro é o mapa das escalas. Juntos, eles cobrem tudo o que você precisa para acompanhar e improvisar dentro de uma tonalidade."),

        h ("Resumo do tópico"),
        b ("Modo é a escala maior começando em um grau diferente."),
        b ("São sete modos: jônio, dórico, frígio, lídio, mixolídio, eólio e lócrio."),
        b ("As notas são as mesmas; muda o centro e o intervalo característico."),
        b ("Cada acorde do campo combina com o modo do seu grau."),
        b ("No braço, os modos são as mesmas posições, começando em pontos diferentes."),
        c (
            "Nos exercícios deste tópico, toque os modos no instrumento. O app reconhece as notas e confere se o padrão corresponde ao modo pedido."),
    };
}

} // namespace cursomusica::content
