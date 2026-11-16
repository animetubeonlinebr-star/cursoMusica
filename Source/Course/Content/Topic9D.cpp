#include "Course/Content/Topics.h"

// Topic 9D — Campos harmonicos diminutos (Modulo 9, Etapa 9).
// Fonte de verdade do texto: docs/MUSIC.md (bloco D da Etapa 9).
namespace cursomusica::content
{

std::vector<ContentItem> topic9D()
{
    return {

        p (
            "Campo harmônico é o conjunto de acordes que nasce de uma escala. Você já estudou o campo harmônico maior e o menor. Neste tópico você conhece os campos que nascem das escalas diminutas. Eles não substituem os campos tradicionais: eles acrescentam um vocabulário de cores e tensões que a música instrumental usa o tempo todo."),
        p (
            "Como as escalas diminutas tem oito notas, o campo que elas geram é mais denso do que o campo maior. Em vez de sete acordes, você encontra uma família de acordes que compartilham as mesmas tensões. Entender esse campo é o que permite harmonizar melodias com sonoridades mais ricas."),

        h ("Relembrando o campo maior"),
        p (
            "No campo harmônico maior de Do, os sete acordes são C, Dm, Em, F, G, Am e Bdim. Cada um nasce de empilhar terças sobre um grau da escala. O diminuto aparece aqui no sétimo grau, como acorde de sensível. Esse é o primeiro contato com o diminuto dentro de um campo harmônico, e é dele que partimos."),
        b ("I = C, ii = Dm, iii = Em, IV = F, V = G, vi = Am, vii = Bdim."),
        b ("O vii grau é diminuto e conduz a tônica."),
        b ("As funções se organizam em tônica, subdominante e dominante."),
        img ("m9_campo_diminuto", "Os dois campos das escalas diminutas e os acordes que eles geram."),

        h ("As duas escalas diminutas"),
        p (
            "Existem duas escalas diminutas, que são a mesma sequência começando em pontos diferentes. A primeira alterna tom e meio-tom: 0, 2, 3, 5, 6, 8, 9, 11. A segunda alterna meio-tom e tom: 0, 1, 3, 4, 6, 7, 9, 10. As duas tem oito notas e são simétricas. A escolha entre elas depende da sonoridade que se quer: uma favorece acordes de sétima maior, a outra favorece dominantes."),
        tbl ({ "Escala", "Intervalos (semitons)", "Acordes característicos" }, {
            { "Tom-meio-tom", "0 - 2 - 3 - 5 - 6 - 8 - 9 - 11", "dim7, m7, maj7, 7" },
            { "Meio-tom-tom", "0 - 1 - 3 - 4 - 6 - 7 - 9 - 10", "7, dim7, m7, m7(b5)" },
        }),
        c (
            "O campo do DomDim é o da escala meio-tom/tom. É por isso que ele é tão usado sobre dominantes: a escala já contém as tensões 9 bemol, 9 sustenida, 11 aumentada e 13."),

        h ("O campo diminuto tom-meio-tom"),
        p (
            "Quando empilhamos terças sobre a escala tom-meio-tom, obtemos um campo com acordes de sétima maior, menor e diminutos alternados. Ele é usado quando o centro tonal é uma tônica maior ou menor, e o arranjador quer um som mais colorido do que o campo maior tradicional permite."),
        b ("Contém dois acordes diminutos a um tom de distância."),
        b ("Alterna acordes maiores e menores de forma simétrica."),
        b ("Usado para harmonizar melodias com cromatismos."),

        h ("O campo diminuto meio-tom-tom"),
        p (
            "Quando empilhamos terças sobre a escala meio-tom-tom, o resultado é um campo dominado por acordes dominantes. Quatro deles, separados por terças menores, dividem a mesma escala. Esse é o campo do DomDim, e por isso ele é tão útil sobre progressões de jazz, onde o dominante precisa ser enriquecido."),
        b ("Quatro acordes dominantes a uma terça menor de distância."),
        b ("Todos usam as mesmas tensões (9 bemol, 9 sustenida, 11 aumentada e 13)."),
        b ("E o campo de onde vem o dim7 substituto."),

        h ("A relação entre campo diminuto e campo maior"),
        p (
            "O campo diminuto não vive separado do campo maior. Os dois se cruzam. O vii grau do campo maior é um diminuto, e ele pertence também ao campo diminuto. Por isso, ao passar do campo maior para o diminuto, a música não soa desconexa: há acordes em comum que servem de ponte."),
        b ("O vii grau do campo maior aparece também no campo diminuto."),
        b ("Acordes em comum servem de pivô entre os dois campos."),
        b ("O diminuto é a ponte natural entre eles."),
        aud ({ "B3", "D4", "F4", "G4" }, "O vii grau (Si diminuto) resolvendo em Do: a ponte entre os campos."),

        h ("Como usar o campo diminuto na prática"),
        p (
            "Comece identificando o vii grau do campo maior em que você está. Depois, experimente troca-lo por outros acordes do campo diminuto e ouça a diferença de cor. Por fim, use o campo meio-tom-tom para enriquecer os dominantes de uma progressão, substituindo o dominante simples pelo dim7 correspondente."),
        b ("Identifique o vii grau do campo maior e experimente trocas."),
        b ("Use o campo diminuto para colorir uma progressão simples."),
        b ("Substitua dominantes pelo dim7 correspondente."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é usar o campo diminuto sem preparação, o que faz a música soar desconexa. Outro erro é tentar classificar cada acorde do campo como tônica, subdominante ou dominante: o campo diminuto funciona mais por cor do que por função."),
        b ("Usar o campo diminuto sem um acorde de ponte: a música perde a coerência."),
        b ("Forçar as funções tradicionais sobre um campo simétrico."),
        b ("Confundir as duas escalas diminutas e as suas cores."),
        c (
            "Se a música soar desorganizada, volte ao campo maior e reintroduza o diminuto como cor, não como estrutura."),

        h ("Aplicando na prática"),
        p (
            "Tome uma progressão simples, como C - Am - Dm - G, e experimente trocar o G por um dominante com nona bemol. Depois, acrescente o dim7 substituto no lugar do dominante. O objetivo é ouvir como o campo diminuto muda a cor sem destruir a progressão original."),
        b ("Troque o V por um V7(b9) e ouça a tensão extra."),
        b ("Troque o V pelo dim7 substituto."),
        b ("Note como a resolução fica mais forte."),
        aud ({ "C4", "E4", "G4", "A#4", "C#5", "G4", "F4", "E4" },
             "Um dominante com nona bemol no meio de uma progressão: a cor do campo diminuto."),

        h ("O campo diminuto é a improvisação"),
        p (
            "Quando você improvisa sobre um acorde dominante, o campo diminuto dá as notas que soam modernas. Em vez de tocar apenas a escala do acorde, você usa a escala diminuta meio-tom/tom e obtém as tensões que caracterizam o som. O campo, portanto, não é só uma lista de acordes: é um conjunto de notas que orienta a melodia."),
        b ("Sobre o dominante, use a escala diminuta meio-tom/tom."),
        b ("As tensões 9 bemol, 9 sustenida, 11 aumentada e 13 aparecem na melodia."),
        b ("O campo orienta tanto a harmonia quanto a improvisação."),

        h ("As tensões do campo diminuto"),
        p (
            "As tensões do campo diminuto tem um papel específico. A nona bemol cria a tensão principal; a nona sustenida, a décima primeira aumentada e a décima terceira acrescentam cor. Juntas, elas dão ao acorde dominante uma sonoridade que não existe no campo maior tradicional. Saber nomear cada tensão ajuda a controlar a cor que você quer."),
        tbl ({ "Tensão", "Distância (semitons)", "Efeito" }, {
            { "9 bemol", "1", "tensão principal" },
            { "9 sustenida", "3", "cor (enarmonia da 3a menor)" },
            { "11 aumentada", "6", "tensão moderna" },
            { "13", "9", "cor, décima terceira" },
        }),
        c (
            "Não é preciso usar todas as tensões. Escolha uma ou duas e deixe que elas definam a cor do momento."),

        h ("O campo diminuto na composição"),
        p (
            "Ao compor, o campo diminuto dá uma paleta extra. Em vez de resolver sempre pelo campo maior, o compositor pode passar pelo campo diminuto para criar surpresa. Uma progressão que vai de um acorde maior para um dominante com nona bemol soa mais rica do que a mesma progressão com o dominante simples. É isso não exige mudar a melodia: apenas a cor da harmonia."),
        b ("Use o campo diminuto para criar surpresa na resolução."),
        b ("A melodia não precisa mudar: só a cor da harmonia."),
        b ("O campo diminuto amplia a paleta sem alterar a estrutura."),

        h ("Comparando com os campos tradicionais"),
        p (
            "O campo maior e o menor organizam a harmonia por função: tônica, subdominante e dominante. O campo diminuto organiza a harmonia por cor e tensão. Os dois se completam: o campo tradicional dá a estrutura, e o diminuto dá o tempero. Saber transitar entre os dois é o que faz a música soar ao mesmo tempo clara e sofisticada."),
        b ("Campo tradicional: organiza por função."),
        b ("Campo diminuto: organiza por cor e tensão."),
        b ("Os dois se completam na prática."),

        h ("Como harmonizar com o campo diminuto"),
        p (
            "Harmonizar com o campo diminuto é escolher, entre os acordes que ele oferece, os que melhor servem à melodia. Como o campo é simétrico, vários acordes compartilham notas, e a escolha depende do efeito que se quer. Um som mais estável pede os acordes maiores; um som mais tenso, os diminutos e dominantes alterados."),
        b ("Escolha os acordes do campo pela cor que a melodia pede."),
        b ("Acordes maiores dão estabilidade; diminutos e dominantes, tensão."),
        b ("A melodia decide qual acorde do campo encaixa melhor."),

        h ("O campo diminuto e a modulação"),
        p (
            "O campo diminuto é também um mapa de modulação. Como ele se cruza com vários campos maiores, os acordes comuns servem de ponte. Um acorde que pertence ao campo maior e ao campo diminuto permite passar de um para o outro sem quebra. Assim, o campo diminuto amplia as possibilidades de modulação além das vizinhas do círculo das quintas."),
        b ("Acordes comuns ligam o campo maior e o diminuto."),
        b ("A modulação pelo campo diminuto alcança tonalidades distantes."),
        b ("O dim7 é a ponte mais direta entre os campos."),
        aud ({ "C#4", "E4", "G4", "A#4", "D4", "F4", "A4" },
             "Um dim7 conduzindo a um novo campo: a modulação fica elegante."),

        h ("Erros comuns ao estudar os campos diminutos"),
        p (
            "Os erros mais frequentes vêm de tratar o campo diminuto como um substituto do campo maior, e não como um complemento. Outro erro é usar as duas escalas diminutas sem distinção, o que mistura duas cores diferentes. Fique atento a estes pontos ao praticar."),
        b ("Tratar o campo diminuto como substituto do campo maior."),
        b ("Confundir as duas escalas diminutas e as suas cores."),
        b ("Usar o campo sem um acorde de resolução à vista."),
        c (
            "O campo diminuto é um tempero: em excesso, descaracteriza a música. Use-o para colorir, não para substituir a estrutura."),

        h ("O campo diminuto e o instrumento"),
        p (
            "No instrumento, o campo diminuto é acessível porque as suas escalas são simétricas. O aluno aprende um desenho e o desloca pelo braço, cobrindo várias tonalidades. Isso torna a prática do campo mais econômica do que a de um campo assimétrico, e permite focar a atenção no som, e não na memorização. A mão encontra o desenho, e o ouvido julga a cor."),
        b ("As escalas simétricas são deslocáveis pelo braço."),
        b ("Um desenho cobre várias tonalidades."),
        b ("A prática foca o som, não a memorização."),

        h ("Aplicando o campo diminuto na improvisação"),
        p (
            "Improvisar com o campo diminuto significa escolher a escala certa para cada acorde. Sobre um dominante, usa-se a escala diminuta meio-tom/tom; sobre um diminuto, a escala diminuta tom-meio-tom. Com o tempo, o aluno associa cada tipo de acorde à sua escala e improvisa sem pensar, guiado pela cor que quer ouvir. É o fim natural do estudo da harmonia avançada."),
        b ("Sobre o dominante, a escala meio-tom/tom."),
        b ("Sobre o diminuto, a escala tom-meio-tom."),
        b ("A associação acorde-escala guia a improvisação."),
        aud ({ "C4", "C#4", "D#4", "E4", "F#4", "G4", "A4", "A#4", "C5" },
             "A escala do campo diminuto sobre um dominante: as tensões soam naturais."),

        h ("Resumo do tópico"),
        b ("Campo harmônico é o conjunto de acordes de uma escala."),
        b ("As escalas diminutas geram dois campos: tom-meio-tom e meio-tom-tom."),
        b ("O campo do DomDim é o da escala meio-tom/tom."),
        b ("O campo diminuto se cruza com o campo maior pelo vii grau."),
        b ("Ele funciona mais por cor do que por função tradicional."),
        c (
            "Nos exercícios, monte acordes do campo diminuto e toque as resoluções. O app reconhece as notas e confere as classes de altura."),
    };
}

} // namespace cursomusica::content
