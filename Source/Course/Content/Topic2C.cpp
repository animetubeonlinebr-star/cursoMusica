#include "Course/Content/Topics.h"

// Topic 2C — Intervalos maiores, menores, justos, aumentados e diminutos.
// Fonte de verdade do texto: docs/MUSIC.md §2.2 (bloco C).
namespace cursomusica::content
{

std::vector<ContentItem> topic2C()
{
    return {

        p (
            "Até aqui você mediu intervalos em semitons. Agora vem a parte que dá nome às coisas: a qualidade. Todo intervalo tem um número (segunda, terça, quarta…) e uma qualidade (maior, menor, justa, aumentada, diminuta). O número diz quantas letras existem entre as notas; a qualidade diz exatamente quantos semitons há entre elas."),
        p (
            "Entender a qualidade é o que separa quem apenas repete posições de quem realmente sabe o que está tocando. É ela que decide se um acorde é maior ou menor, se uma nota repousa ou tensiona, se a música fica estável ou instável."),

        h ("Os três grupos de qualidade"),
        p (
            "As qualidades se organizam em três grupos, e cada grupo corresponde a um conjunto de números de intervalo. Saber a que grupo o intervalo pertence já elimina metade das dúvidas."),
        b ("Justos: uníssono, quarta, quinta e oitava. São os intervalos 'puros', que não têm versão maior nem menor."),
        b ("Maiores e menores: segunda, terça, sexta e sétima. Cada um tem duas versões, uma maior (mais larga) e uma menor (mais estreita)."),
        b ("Aumentados e diminutos: qualquer intervalo pode receber essa qualidade quando é alargado ou estreitado em relação ao padrão."),
        tbl ({ "Número", "Grupo", "Versões possíveis" }, {
            { "1 (uníssono)", "justo", "justo, aumentado, diminuto" },
            { "2 (segunda)", "maior/menor", "maior, menor, aumentada, diminuta" },
            { "3 (terça)", "maior/menor", "maior, menor, aumentada, diminuta" },
            { "4 (quarta)", "justo", "justa, aumentada, diminuta" },
            { "5 (quinta)", "justo", "justa, aumentada, diminuta" },
            { "6 (sexta)", "maior/menor", "maior, menor, aumentada, diminuta" },
            { "7 (sétima)", "maior/menor", "maior, menor, aumentada, diminuta" },
            { "8 (oitava)", "justo", "justa, aumentada, diminuta" },
        }),

        h ("Intervalos justos"),
        p (
            "Os justos são os intervalos que a física das cordas produz naturalmente: a oitava, a quinta e a quarta. Quando duas notas formam um intervalo justo, o som se mistura de forma limpa, quase como uma só nota. Por isso eles são a base da afinação e da harmonia."),
        b ("Oitava justa: 12 semitons. Dó até o próximo Dó."),
        b ("Quinta justa: 7 semitons. Dó até Sol. É o intervalo mais consonante depois da oitava."),
        b ("Quarta justa: 5 semitons. Dó até Fá."),
        aud ({ "C4", "G4" }, "Quinta justa: o som se funde, quase uma nota só."),

        h ("Intervalos maiores e menores"),
        p (
            "As terças e as sextas aparecem em duas versões. A versão maior está um semitom acima da menor. Essa diferença de um semitom é o que faz o acorde soar alegre (maior) ou triste (menor), e é a distinção mais importante para o ouvido do guitarrista."),
        b ("Terça maior: 4 semitons (Dó–Mi). Terça menor: 3 semitons (Dó–Mib)."),
        b ("Sexta maior: 9 semitons (Dó–Lá). Sexta menor: 8 semitons (Dó–Láb)."),
        b ("Segunda maior: 2 semitons. Segunda menor: 1 semitom."),
        b ("Sétima maior: 11 semitons. Sétima menor: 10 semitons."),
        aud ({ "C4", "E4" }, "Terça maior (4 semitons): som aberto, estável."),
        aud ({ "C4", "D#4" }, "Terça menor (3 semitons): som fechado, melancólico."),
        c (
            "Ouça as duas terças seguidas. A diferença de apenas um semitom muda completamente o clima: é essa diferença que define acordes maiores e menores."),

        h ("Aumentados e diminutos"),
        p (
            "Quando um intervalo justo ou maior é alargado em um semitom, ele se torna aumentado; quando é estreitado em um semitom, torna-se diminuto. Esses intervalos aparecem nos acordes de tensão e nos acordes diminutos, e são os mais instáveis do sistema."),
        b ("Quarta aumentada: 6 semitons (Dó–Fá#). É o trítono."),
        b ("Quinta diminuta: 6 semitons (Dó–Solb). Também o trítono, com outro nome."),
        b ("Quinta aumentada: 8 semitons (Dó–Sol#)."),
        aud ({ "C4", "F#4" }, "Trítono (quarta aumentada / quinta diminuta): tensão máxima."),

        h ("Aumentado e diminuto são enarmônicos"),
        p (
            "Dois intervalos enarmônicos têm o mesmo som, mas nomes diferentes. A quarta aumentada e a quinta diminuta têm seis semitons cada; soam idênticos, mas são escritos de formas distintas porque a letra das notas muda. Nomear corretamente depende de saber de que nota se parte."),
        tbl ({ "Semitons", "Um nome", "Outro nome (enarmônico)" }, {
            { "6", "quarta aumentada (Dó–Fá#)", "quinta diminuta (Dó–Solb)" },
            { "3", "terça menor (Dó–Mib)", "segunda aumentada (Dó–Ré#)" },
            { "4", "terça maior (Dó–Mi)", "quarta diminuta (Dó–Fáb)" },
        }),


        img ("m2_qualidades_grupos", "Os três grupos de qualidade: justos, maiores/menores e alterados."),

        h ("Justos: por que não têm versão maior nem menor"),
        p (
            "Os intervalos justos são chamados assim porque soam 'puros': a relação entre as frequências é simples (a oitava é 2:1, a quinta é 3:2, a quarta é 4:3). Por isso eles não têm versão maior nem menor — ou são justos, ou foram alargados (aumentados) ou estreitados (diminutos). Essa pureza é a razão de eles serem a base da afinação."),
        b ("Oitava justa (12 semitons): a nota se repete."),
        b ("Quinta justa (7 semitons): o intervalo mais consonante depois da oitava."),
        b ("Quarta justa (5 semitons): som firme, de chamada."),
        aud ({ "C4", "G4" }, "Quinta justa: a relação 3:2 produz um som limpo e estável."),

        h ("Maiores e menores: a diferença de um semitom"),
        p (
            "Os intervalos de segunda, terça, sexta e sétima têm duas versões: maior e menor. A versão maior é um semitom mais larga que a menor. Essa diferença mínima é responsável por grande parte do clima da música: terça maior soa alegre, terça menor soa triste; sétima maior soa brilhante, sétima menor soa tensa."),
        tbl ({ "Intervalo", "Semitons (menor)", "Semitons (maior)" }, {
            { "segunda", "1", "2" },
            { "terça", "3", "4" },
            { "sexta", "8", "9" },
            { "sétima", "10", "11" },
        }),
        aud ({ "C4", "E4" }, "Terça maior (4 semitons): clima aberto."),
        aud ({ "C4", "D#4" }, "Terça menor (3 semitons): clima fechado. Ouça a diferença de um semitom."),

        h ("Aumentados e diminutos: o padrão alterado"),
        p (
            "Qualquer intervalo pode ser alterado. Alargar um intervalo justo ou maior em um semitom produz um intervalo aumentado; estreitar um intervalo justo ou menor em um semitom produz um intervalo diminuto. Esses intervalos aparecem nos acordes de tensão, nos acordes diminutos e nas passagens cromáticas."),
        b ("Quarta justa (5) alargada = quarta aumentada (6)."),
        b ("Quinta justa (7) estreitada = quinta diminuta (6)."),
        b ("Quinta justa (7) alargada = quinta aumentada (8)."),
        b ("Segunda maior (2) estreitada = segunda menor (1)."),

        h ("Enarmonia: dois nomes, um som"),
        p (
            "Alguns intervalos diferentes soam exatamente igual. A quarta aumentada e a quinta diminuta têm seis semitons cada; a terça menor e a segunda aumentada têm três. São intervalos enarmônicos: mesmo som, nomes diferentes. A escolha do nome depende de como o intervalo é escrito, isto é, de quais letras de nota ele usa."),
        b ("Escrever corretamente importa: um mesmo som pode ter função diferente conforme o nome."),
        b ("O trítono (seis semitons) é o exemplo clássico de intervalo com dois nomes."),
        part ("m2_partitura_tercas", { "C4", "E4", "C4", "D#4" },
              "Terça maior e terça menor escritas na partitura: mesmo número, qualidade diferente."),

        h ("Resumo das qualidades na prática"),
        p (
            "Na prática, identificar a qualidade é um processo de eliminação. Primeiro pergunte se o intervalo é justo (1, 4, 5, 8) ou não (2, 3, 6, 7). Se for justo, ele só pode ser justo, aumentado ou diminuto. Se não for, ele é maior ou menor, e a distância de um semitom decide qual. Esse raciocínio resolve a maioria dos casos rapidamente."),
        c (
            "Nos exercícios deste tópico, você toca cada qualidade no instrumento e o app confere a distância em semitons, confirmando a qualidade que você produziu."),


        h ("Reconhecendo a qualidade de ouvido"),
        p (
            "Cada qualidade tem uma sonoridade característica. Os justos soam estáveis e 'limpos'; os maiores soam abertos; os menores soam fechados; os aumentados soam tensos e os diminutos soam instáveis. Treinar o ouvido para essas sensações é o que permite identificar a qualidade mesmo sem contar os semitons."),
        b ("Justos: som estável, sem tensão."),
        b ("Maiores: som aberto e claro."),
        b ("Menores: som fechado e melancólico."),
        b ("Aumentados: som tenso, 'estranho'."),
        b ("Diminutos: som instável, quase desafinado."),
        aud ({ "C4", "G#4" }, "Quinta aumentada: som tenso e etéreo."),
        aud ({ "C4", "F#4" }, "Trítono: som instável, pede resolução."),

        h ("A importância da qualidade na harmonia"),
        p (
            "A qualidade dos intervalos é o que define a função dos acordes. Um acorde com terça maior e quinta justa soa estável; trocar a quinta por uma quinta diminuta cria um acorde instável, que pede resolução. Compreender a qualidade é, portanto, compreender por que a harmonia se move."),
        b ("Acordes estáveis usam intervalos justos e maiores."),
        b ("Acordes instáveis usam quintas alteradas e sétimas menores."),
        b ("A tensão e a resolução nascem da escolha da qualidade."),

        h ("Resumo prático"),
        p (
            "Para identificar a qualidade de um intervalo: conte os semitons, veja se o número pertence ao grupo dos justos ou dos maiores/menores, e compare com o padrão. Se estiver um semitom acima ou abaixo do padrão, o intervalo é aumentado ou diminuto. Com esse roteiro, qualquer intervalo pode ser nomeado corretamente."),
        c (
            "Na prática com o instrumento, o app mede os semitons e confirma a qualidade; no treino de ouvido, você compara a sensação com as referências deste tópico."),


        h ("Qualidade e escrita musical"),
        p (
            "Na partitura, a qualidade do intervalo é escrita com precisão, e ler essa qualidade corretamente é parte da leitura musical. Uma terça maior e uma terça menor têm o mesmo número (terça), mas se escrevem com notas diferentes. Aprender a reconhecer a qualidade na escrita complementa o reconhecimento de ouvido."),
        b ("A terça maior usa a nota natural; a menor, a nota alterada correspondente."),
        b ("O acidente (sustenido ou bemol) indica a alteração que muda a qualidade."),
        b ("Ler a qualidade corretamente evita erros de harmonia e de afinação."),
        part ("m2_partitura_tercas", { "C4", "E4", "C4", "D#4" },
              "Terça maior e terça menor na partitura: a diferença está na escrita e no som."),

        h ("Do nome à execução"),
        p (
            "Nomear corretamente um intervalo é o primeiro passo; executá-lo no instrumento é o segundo. Saber que uma terça menor tem três semitons permite encontrá-la a partir de qualquer nota. Essa ligação entre o nome e a distância física é o que transforma a teoria em prática."),
        b ("Identifique o nome e a qualidade do intervalo."),
        b ("Converta o nome em semitons."),
        b ("Localize a distância no braço e toque."),

        h ("Resumo do tópico"),
        b ("Todo intervalo tem número e qualidade."),
        b ("Justos: 1, 4, 5, 8. Maiores/menores: 2, 3, 6, 7."),
        b ("Maior e menor diferem por um semitom."),
        b ("Aumentado alarga o padrão; diminuto estreita."),
        b ("Intervalos enarmônicos soam iguais, mas têm nomes diferentes."),
        part ("m2_partitura_tercas", { "C4", "E4", "C4", "D#4" },
              "Partitura com a terça maior e a terça menor em sequência. Ouça a diferença de um semitom."),
        c (
            "Nos exercícios, você vai tocar cada qualidade no instrumento. O app confere a distância em semitons e confirma se a qualidade corresponde ao que foi pedido."),
    };
}

} // namespace cursomusica::content
