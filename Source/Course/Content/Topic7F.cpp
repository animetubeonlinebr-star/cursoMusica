#include "Course/Content/Topics.h"

// Topic 7F — Modos estruturais pelo CAGED (Módulo 7, Etapa 7).
// Fonte de verdade do texto: docs/MUSIC.md §7.2 (bloco F).
namespace cursomusica::content
{

std::vector<ContentItem> topic7F()
{
    return {

        p (
            "Você já conhece o CAGED como um sistema de formas de acorde que se conectam pelo braço. Neste tópico você usa o CAGED de outra forma: como um mapa para tocar modos em qualquer região. Cada forma do CAGED carrega dentro de si a escala do tom, e reconhecer essa relação é o que permite tocar um modo em várias posições sem decorar escalas soltas."),
        p (
            "Os modos estruturais são exatamente isso: os modos (dórico, lídio, mixolídio…) organizados no braço pelas formas do CAGED. Em vez de estudar cada modo como uma escala independente, você aprende a ver o modo dentro das formas que já toca, o que acelera muito o aprendizado e conecta harmonia, escala e braço."),

        h ("O CAGED como mapa, não só como acorde"),
        p (
            "No módulo 1, o CAGED apareceu como cinco formas de acorde (C, A, G, E, D) que se conectam ao longo do braço. Agora você usa essas cinco formas como cinco “janelas” para a escala do tom: dentro de cada forma, a escala do tom está distribuída, e os modos são as escalas construídas sobre cada grau."),
        b ("As cinco formas cobrem o braço inteiro."),
        b ("Cada forma contém a escala do tom."),
        b ("Sobre cada grau, um modo."),
        img ("m7_caged_modos", "As formas do CAGED como mapa dos modos: cada janela contém a escala do tom."),

        h ("A escala maior dentro das formas"),
        p (
            "Para tocar um modo pelo CAGED, o primeiro passo é enxergar a escala maior dentro das cinco formas. Em Dó maior, as cinco formas contêm as sete notas da escala distribuídas nas seis cordas. Uma vez que você vê a escala dentro da forma, os modos aparecem: cada modo é a mesma escala começando em um grau diferente."),
        tbl ({ "Forma CAGED", "Tônica na", "Região típica" }, {
            { "C", "5ª corda", "casas 3–8" },
            { "A", "5ª corda", "casas 5–10" },
            { "G", "6ª corda", "casas 3–8" },
            { "E", "6ª corda", "casas 0–5 (aberta) ou 12+" },
            { "D", "4ª corda", "casas 10–15" },
        }),

        h ("Modos a partir das formas"),
        p (
            "Cada forma do CAGED, além de conter a escala, contém o desenho de cada modo. Por exemplo, na forma de Dó (5ª corda), você pode tocar o jônio começando na tônica, o dórico começando na segunda, o frígio na terça, e assim por diante. O desenho da mão muda pouco: você apenas desloca a “nota de repouso”."),
        b ("Jônio: comece na tônica da forma."),
        b ("Dórico: comece na segunda (um tom acima)."),
        b ("Frígio: comece na terça (meio tom acima da segunda)."),
        b ("Lídio: comece na quarta (uma quarta acima)."),
        b ("Mixolídio: comece na quinta."),
        c (
            "O segredo é não decorar sete escalas separadas, mas ver que todas são a mesma escala do tom vista a partir de uma nota de repouso diferente."),

        h ("Conectando as formas"),
        p (
            "A grande vantagem do CAGED é a conexão. As cinco formas se sobrepõem, de modo que você pode percorrer o braço inteiro tocando um modo sem “saltar” de posição. Isso é o que permite improvisar com fluidez, subindo e descendo o braço sem perder a referência da escala."),
        b ("As formas se sobrepõem nas bordas."),
        b ("Você passa de uma para outra sem perder as notas."),
        b ("O braço inteiro fica disponível para o modo."),
        aud ({ "C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5" }, "Escala de Dó maior dentro de uma forma: os sete graus e a oitava."),

        h ("Modos estruturais na prática"),
        p (
            "Na prática, você escolhe o modo pelo acorde (como viu no tópico anterior) e o toca usando as formas do CAGED. Sobre um Dm7 (dórico), por exemplo, você toca o dórico usando as cinco formas de Dó, começando na nota Dó. O ouvido percebe o centro e a cor; a mão percorre o braço com fluidez."),
        b ("Escolha o modo pela família do acorde."),
        b ("Toque o modo pelas cinco formas do CAGED."),
        b ("Percorra o braço sem perder a referência."),
        img ("m7_caged_modos", "Um modo tocado pelas cinco formas: o braço inteiro em uma única escala."),
        c (
            "Nos exercícios deste tópico, você toca modos e o app reconhece as notas. Você também responderá a questionários sobre a relação entre as formas do CAGED e os modos."),

        h ("Três posições para começar"),
        p (
            "Para não se perder, comece com três posições por modo: a forma com a tônica na 6ª corda, a forma com a tônica na 5ª corda e a forma com a tônica na 4ª corda. Com essas três, você cobre boa parte do braço. Depois, acrescente as formas restantes e conecte tudo."),
        b ("Forma na 6ª corda: som grave, boa para bases."),
        b ("Forma na 5ª corda: região média, a mais usada."),
        b ("Forma na 4ª corda: som agudo, boa para solos."),

        h ("Notas de repouso por modo"),
        p (
            "Cada modo tem notas de repouso características — as notas que soam estáveis sobre o acorde. No jônio, a tônica e a quinta; no dórico, a terça menor e a sexta maior; no lídio, a #11. Conhecer as notas de repouso ajuda a improvisar com intenção, porque você sabe onde “descansar” a frase."),
        tbl ({ "Modo", "Notas de repouso", "Cor" }, {
            { "jônio", "1, 3, 5, 7", "claro" },
            { "dórico", "1, b3, 5, 6", "aberto" },
            { "frígio", "1, b3, 5, b7", "espanhol" },
            { "lídio", "1, 3, #4, 7", "brilhante" },
            { "mixolídio", "1, 3, 5, b7", "dominante" },
        }),

        h ("Erros comuns"),
        p (
            "O erro mais comum é tentar decorar sete escalas separadas, em vez de ver que todas são a mesma escala do tom vista de graus diferentes. Outro é perder a referência de tônica ao percorrer as formas, o que faz a improvisação soar “sem centro”. Praticar com o baixo afirmando o centro resolve os dois."),
        b ("Veja os modos como a mesma escala, não como sete escalas."),
        b ("Mantenha o centro claro com o baixo ou o acorde."),
        b ("Pratique as três posições antes de acrescentar as outras."),

        h ("As cinco formas e a escala do tom"),
        p (
            "Para usar o CAGED como mapa dos modos, o primeiro passo é enxergar a escala do tom dentro das cinco formas. Cada forma contém as sete notas da escala distribuídas nas seis cordas. Uma vez que você vê a escala, os modos aparecem: cada modo é a mesma escala começando em um grau diferente."),
        b ("Forma de Dó: escala de Dó distribuída na região média."),
        b ("Forma de Sol: a mesma escala, outra região."),
        b ("Todas as formas juntas cobrem o braço."),
        img ("m7_caged_modos", "A escala do tom dentro das formas do CAGED: a base para tocar qualquer modo."),

        h ("Trocando de modo dentro da forma"),
        p (
            "Dentro de uma mesma forma, você pode tocar qualquer modo do tom, mudando apenas a nota de repouso. Se você começa e termina as frases na tônica, ouve o jônio; se começa e termina na segunda, ouve o dórico; se começa na quinta, ouve o mixolídio. A mão quase não muda: o que muda é a âncora da frase."),
        b ("Jônio: âncora na tônica."),
        b ("Dórico: âncora na segunda."),
        b ("Mixolídio: âncora na quinta."),
        c (
            "Essa é a grande vantagem de pensar por formas: você não decora sete escalas, você muda a âncora da frase dentro de uma escala que já conhece."),

        h ("Modos e o baixo"),
        p (
            "Para que o ouvido perceba o modo, o baixo (ou o acorde) precisa afirmar o centro. Se você toca a escala de Dó começando em Ré, mas o baixo está em Dó, o ouvido pode não perceber o dórico. Afirmar o centro com o baixo é o que faz o modo aparecer."),
        b ("O baixo define o centro."),
        b ("A frase na escala define a cor."),
        b ("Sem centro claro, o modo se dissolve."),

        h ("Conectando as formas para percorrer o braço"),
        p (
            "A conexão entre as formas é o que permite percorrer o braço inteiro sem perder a escala. Pratique passar de uma forma para outra nas bordas, onde elas se sobrepõem. Com o tempo, você enxerga o braço inteiro como uma única escala, dividida em regiões."),
        b ("Pratique as bordas, onde as formas se sobrepõem."),
        b ("Suba e desça o braço sem pular de posição."),
        b ("Enxergue o braço como uma escala contínua."),

        h ("Modos e a improvisação pelo CAGED"),
        p (
            "Improvisar pelos modos usando o CAGED é uma das formas mais eficientes de aprender. Você escolhe o modo pela cor, o centro pelo acorde e toca usando as formas que já conhece. Isso libera a sua atenção para a música, em vez de para a digitação."),
        b ("Escolha o modo pela cor."),
        b ("Escolha o centro pelo acorde."),
        b ("Toque pelas formas do CAGED."),

        h ("Um roteiro de estudo pelo CAGED"),
        p (
            "Um roteiro prático é escolher um modo por semana e tocar esse modo pelas cinco formas, sempre sobre o mesmo vamp. Na primeira sessão, toque a escala em cada forma, devagar. Na segunda, improvise frases curtas em cada forma. Na terceira, conecte as formas e improvise pelo braço inteiro. Esse roteiro fixa a escala e a cor ao mesmo tempo."),
        b ("Semana 1: a escala nas cinco formas."),
        b ("Semana 2: frases curtas em cada forma."),
        b ("Semana 3: conecte as formas e improvise."),

        h ("Modos pelo CAGED e a improvisação"),
        p (
            "Quando você enxerga os modos pelas formas do CAGED, a improvisação ganha fluidez. Em vez de pensar em sete escalas separadas, você pensa em uma escala que se estende pelo braço, com a âncora da frase mudando de grau. Isso libera a sua atenção para a música: você escolhe a nota pela cor que quer ouvir, não pela posição que decorou."),
        b ("Uma escala, cinco formas, sete modos."),
        b ("A âncora da frase define o modo."),
        b ("Liberdade para pensar na música, não na digitação."),

        h ("Exercícios de conexão entre formas"),
        p (
            "Para conectar as formas, toque a escala de uma ponta à outra do braço, sem parar nas bordas. Depois, toque a mesma escala em terças ou em outros padrões. Por fim, improvise frases que atravessam as formas. Esse treino é o que transforma cinco posições isoladas em um mapa contínuo do braço."),
        b ("Toque a escala de ponta a ponta do braço."),
        b ("Toque a escala em padrões (terças, grupos)."),
        b ("Improvise frases que atravessam as formas."),
        c (
            "Com as formas conectadas, você toca qualquer modo em qualquer região com naturalidade."),

        h ("Um resumo prático do CAGED modal"),
        p (
            "Resumindo: as cinco formas do CAGED cobrem o braço inteiro; cada forma contém a escala do tom; os modos são essa escala vista de graus diferentes; e a âncora da frase define o modo. Estudar assim é mais eficiente do que decorar sete escalas separadas, porque aproveita o que você já toca e conecta o braço inteiro em um único mapa."),
        b ("Cinco formas: braço inteiro."),
        b ("Cada forma: a escala do tom."),
        b ("Cada modo: a escala vista de um grau."),

        h ("Resumo do tópico"),
        b ("O CAGED é um mapa do braço, não só um conjunto de acordes."),
        b ("Cada forma contém a escala do tom e os seus modos."),
        b ("Os modos são a mesma escala vista de graus diferentes."),
        b ("As formas se conectam e cobrem o braço inteiro."),
        b ("As notas de repouso orientam a improvisação em cada modo."),
        part ("m7_partitura_caged", { "C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5" },
              "Partitura: a escala de Dó maior, a base de todos os modos, dentro das formas do CAGED."),
    };
}

} // namespace cursomusica::content
