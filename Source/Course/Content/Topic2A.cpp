#include "Course/Content/Topics.h"

// Topic 2A — Intervalos musicais (Módulo 2, Etapa 2).
// Fonte de verdade do texto: docs/MUSIC.md §2.2 (bloco A).
namespace cursomusica::content
{

std::vector<ContentItem> topic2A()
{
    return {

        p (
            "Intervalo é a distância entre duas notas. Toda a música que você toca é feita de intervalos: a melodia é uma sequência deles e o acorde é um conjunto deles soando ao mesmo tempo. Entender intervalo é entender por que uma música soa alegre, triste, tensa ou repousada."),
        p (
            "Neste módulo você aprende a medir essa distância de duas formas que andam juntas: pelo número de semitons (a medida exata, que o instrumento mostra) e pelo nome do intervalo (a forma como os músicos falam). A partir daqui, boa parte dos exercícios será tocada no instrumento e o app vai reconhecer as notas para conferir se o intervalo que você tocou é o pedido."),
        c (
            "Objetivo do módulo: compreender a distância entre as notas e desenvolver a capacidade de identificar sonoridades. Não basta saber contar: é preciso ouvir."),

        h ("O que é um semitom e o que é um tom"),
        p (
            "A menor distância usada na música ocidental é o semitom. Na guitarra, um semitom é a distância de uma casa para a casa vizinha, na mesma corda. O tom vale dois semitons (duas casas). Toda a medição de intervalos parte daí."),
        b ("Semitom: 1 casa de diferença na mesma corda."),
        b ("Tom: 2 casas de diferença na mesma corda."),
        b ("A oitava tem 12 semitons: da corda solta até a casa 12, a nota se repete mais aguda."),
        img ("m2_semitons_piano", "Semitons no teclado e no braço: a régua com que se mede todo intervalo."),

        h ("Intervalo melódico e intervalo harmônico"),
        p (
            "O mesmo intervalo pode aparecer de duas maneiras. Quando as duas notas soam uma depois da outra, o intervalo é melódico: é o que se canta e o que aparece na melodia. Quando as duas soam juntas, ao mesmo tempo, o intervalo é harmônico: é o que forma os acordes e o que dá a cor da harmonia."),
        b ("Melódico: Dó e depois Mi (uma nota por vez)."),
        b ("Harmônico: Dó e Mi tocados juntos, como num acorde."),
        c (
            "O app demonstra os dois: o botão de ouvir toca as notas em sequência (melódico) ou juntas (harmônico), conforme o exemplo. Repare na diferença de sensação."),
        aud ({ "C4", "E4" }, "Terça maior melódica: Dó e depois Mi, uma nota por vez."),
        aud ({ "C4", "E4" }, "Terça maior harmônica: Dó e Mi soando juntos."),

        h ("Como se mede um intervalo"),
        p (
            "Medir um intervalo tem dois passos. Primeiro conta-se o número: quantas letras de nota existem de uma até a outra, incluindo as duas pontas. Depois define-se a qualidade, que vem da quantidade exata de semitons. O número dá o nome (segunda, terça, quarta…); a qualidade dá o adjetivo (maior, menor, justa, aumentada, diminuta)."),
        tbl ({ "Passo", "O que se faz", "Exemplo: Dó até Mi" }, {
            { "1. Contar as letras", "Incluir a primeira e a última letra", "Dó, Ré, Mi = três letras → terça" },
            { "2. Contar os semitons", "Medir a distância exata", "Dó até Mi = 4 semitons" },
            { "3. Dar a qualidade", "Semitons definem o adjetivo", "4 semitons numa terça = maior" },
            { "Resultado", "Nome completo do intervalo", "terça maior" },
        }),
        c (
            "Regra de ouro: o número nunca muda com a qualidade. Terça maior e terça menor são ambas terças; o que muda é a distância em semitons (4 e 3)."),

        h ("O intervalo dentro da escala"),
        p (
            "Quando medimos os intervalos a partir da tônica de uma escala, cada grau recebe um número: a tônica é o 1, a segunda nota é o 2, e assim por diante. Esses graus são a base para nomear acordes (a terça e a quinta definem se o acorde é maior ou menor) e para improvisar (a nona, a décima primeira e a décima terceira são os mesmos intervalos, uma oitava acima)."),
        b ("1 = tônica; 2 = segunda; 3 = terça; 4 = quarta; 5 = quinta; 6 = sexta; 7 = sétima."),
        b ("Acima da oitava, os graus se repetem com outro nome: 9 = segunda, 11 = quarta, 13 = sexta."),
        tbl ({ "Grau", "Nota em Dó maior", "Intervalo a partir da tônica", "Semitons" }, {
            { "1", "Dó", "uníssono", "0" },
            { "2", "Ré", "segunda maior", "2" },
            { "3", "Mi", "terça maior", "4" },
            { "4", "Fá", "quarta justa", "5" },
            { "5", "Sol", "quinta justa", "7" },
            { "6", "Lá", "sexta maior", "9" },
            { "7", "Si", "sétima maior", "11" },
            { "8", "Dó", "oitava justa", "12" },
        }),

        h ("Inversão de intervalos"),
        p (
            "Inverter um intervalo é subir a nota grave uma oitava ou descer a aguda uma oitava. Ao inverter, o número e a qualidade se transformam de forma previsível: a soma dos números dá 9 e a qualidade se completa (maior vira menor, justo continua justo)."),
        b ("Terça maior (4 semitons) inverte para sexta menor (8 semitons). 3 + 6 = 9."),
        b ("Quarta justa (5) inverte para quinta justa (7). Justos permanecem justos."),
        b ("Segunda maior (2) inverte para sétima menor (10)."),
        c (
            "A inversão explica por que um acorde maior e o seu relativo menor têm um som próximo: eles compartilham intervalos invertidos."),

        h ("Por que isso importa para o guitarrista"),
        p (
            "Na guitarra, o braço é uma régua de semitons. Uma vez que você aprende a localizar uma terça, uma quinta ou uma sétima a partir de qualquer nota, você constrói acordes em qualquer região sem decorar formas soltas. O CAGED, que você viu no módulo 1, nada mais é do que um mapa desses intervalos no braço."),
        b ("A mesma forma de acorde pode ser deslocada porque os intervalos entre as cordas são fixos."),
        b ("Identificar o intervalo pelo ouvido permite tocar uma melodia de memória em qualquer tom."),
        img ("m2_mapa_intervalos", "Intervalos no braço: cada corda é uma régua de semitons."),
        part ("m2_partitura_terca", { "C4", "E4" },
              "Partitura de uma terça maior (Dó–Mi). Pressione ouvir para escutar exatamente o que está escrito."),


        h ("Semitons: a régua do instrumento e do teclado"),
        p (
            "Para medir intervalos com segurança, você precisa ter a régua na cabeça. No teclado, a régua são as teclas: de Dó a Dó# há um semitom; de Dó a Ré, um tom. Na guitarra, a régua são as casas: cada casa é um semitom, e o braço inteiro é uma sequência contínua de semitons. Quando você aprende as duas réguas, mede qualquer intervalo em qualquer instrumento."),
        b ("Teclado: as teclas brancas são as notas naturais; as pretas, os semitons intermediários."),
        b ("Guitarra: as casas numeram os semitons; a casa 12 é a oitava."),
        b ("O mesmo intervalo tem o mesmo número de semitons nos dois instrumentos."),
        img ("m2_semitons_piano", "A régua de semitons no teclado: a mesma medida vale para o braço."),

        h ("Intervalos simples e compostos"),
        p (
            "Quando um intervalo passa da oitava, ele é composto. A nona, a décima primeira e a décima terceira são os intervalos simples (segunda, quarta e sexta) somados a uma oitava. Reconhecer isso simplifica tudo: para nomear um intervalo composto, basta descontar a oitava e nomear o simples correspondente."),
        tbl ({ "Intervalo simples", "Composto", "Semitons" }, {
            { "segunda", "nona", "14" },
            { "terça", "décima", "16" },
            { "quarta", "décima primeira", "17" },
            { "quinta", "décima segunda", "19" },
            { "sexta", "décima terceira", "21" },
        }),
        c (
            "Regra prática: subtraia 7 do número do intervalo composto para achar o simples (9 - 7 = 2; 11 - 7 = 4; 13 - 7 = 6)."),

        h ("Como o intervalo aparece na escrita"),
        p (
            "Na partitura, o intervalo é a distância vertical entre as notas: quanto mais separadas no pentagrama, maior o intervalo. A leitura à primeira vista depende de reconhecer o desenho do intervalo (segunda é nota ao lado, terça pula uma linha ou espaço, quarta pula duas). Treinar esse reconhecimento visual acelera muito a leitura."),
        b ("Notas vizinhas no pentagrama: segunda."),
        b ("Uma linha ou um espaço entre elas: terça."),
        b ("Duas linhas ou espaços: quarta."),
        part ("m2_partitura_terca", { "C4", "E4" },
              "Partitura de uma terça maior: no pentagrama, a segunda nota pula um grau. Ouça o que está escrito."),


        h ("Intervalos na melodia e na harmonia"),
        p (
            "Toda melodia é uma sequência de intervalos e todo acorde é um conjunto deles. Quando você canta uma melodia, está reproduzindo uma série de distâncias; quando toca um acorde, está soando várias distâncias ao mesmo tempo. Por isso o intervalo é a unidade básica da música: entender intervalo é entender como a melodia se move e como a harmonia se constrói."),
        p (
            "Na melodia, os intervalos podem ser conjuntos (notas vizinhas, segundas) ou disjuntos (saltos, terças ou maiores). Melodias cantáveis geralmente alternam passos e saltos: um salto cria expectativa e os passos seguintes resolvem essa expectativa. Perceber esse jogo é o que faz a música soar natural."),
        b ("Intervalos conjuntos: segundas, movimento suave, passo a passo."),
        b ("Intervalos disjuntos: saltos de terça, quarta, quinta ou mais."),
        b ("Alternar passos e saltos cria tensão e repouso na melodia."),
        aud ({ "C4", "D4", "E4", "G4" }, "Passos (Dó–Ré–Mi) e um salto de terça (Mi–Sol): a melodia respira."),

        h ("Intervalos e afinação"),
        p (
            "Os intervalos justos (quinta e oitava) são a base da afinação do instrumento. Quando você afina a guitarra, está igualando intervalos de quarta e de quinta entre as cordas. Ouvir esses intervalos com precisão é o que permite afinar de ouvido e perceber quando uma corda está levemente desafinada."),
        b ("A afinação padrão usa quartas entre as cordas e uma terça entre a 3ª e a 2ª."),
        b ("A quinta justa e a oitava são os intervalos mais fáceis de ouvir 'batendo' quando desafinados."),
        b ("Ouvir intervalos ajuda tanto a tocar quanto a manter o instrumento afinado."),

        h ("O caminho deste módulo"),
        p (
            "Este módulo percorre os intervalos em etapas: primeiro o conceito e a medição em semitons; depois o quadro móvel e as qualidades; em seguida a percepção e os intervalos práticos; por fim a construção de acordes, o treino de canto e a identificação. Cada tópico apoia o seguinte, e a prática com o instrumento aparece desde o começo."),
        b ("Conceito e medição: o que é um intervalo e como contá-lo."),
        b ("Quadro móvel e qualidades: os nomes e as variações."),
        b ("Percepção e prática: ouvir, cantar e tocar."),
        b ("Acordes e identificação: usar os intervalos para construir e reconhecer."),
        c (
            "Ao final, o objetivo é que você reconheça o que está sendo tocado: pelo instrumento, medindo os semitons, e pelo ouvido, nomeando o intervalo."),

        h ("Resumo do tópico"),
        b ("Intervalo é a distância entre duas notas, medida em semitons."),
        b ("Melódico soa em sequência; harmônico soa junto."),
        b ("O número vem da contagem das letras; a qualidade, dos semitons."),
        b ("Inverter troca o número (soma 9) e completa a qualidade."),
        b ("Na prática, o braço é a régua onde esses intervalos viram posições."),
        c (
            "Nos exercícios deste tópico, toque os intervalos pedidos no instrumento. O app reconhece as notas e confere a distância, então qualquer posição do braço vale — o que importa é o intervalo."),
    };
}

} // namespace cursomusica::content
