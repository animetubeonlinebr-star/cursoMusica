#include "Course/Content/Topics.h"

// Topic 5F — Acordes relativos (Módulo 5, Etapa 5).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 5, bloco F).
namespace cursomusica::content
{

std::vector<ContentItem> topic5F()
{
    return {

        p (
            "Os acordes relativos são pares de acordes que compartilham a mesma armadura de clave e quase as mesmas notas: um maior e um menor, separados por três semitons. Em Dó maior, o relativo menor é Lá menor; em Lá menor, o relativo maior é Dó maior. Essa relação é uma das mais úteis da harmonia, porque permite trocar a cor de uma música sem sair da tonalidade."),
        p (
            "Neste tópico você aprende a identificar os relativos, a entender por que eles soam próximos e a usá-los para criar variações. É também o tópico que prepara o terreno para entender as tonalidades menores, que serão tratadas com mais profundidade nos módulos seguintes."),

        h ("O que são acordes relativos"),
        p (
            "Chamamos de relativos dois acordes — um maior e um menor — que compartilham a mesma armadura de clave. Isso significa que as duas tonalidades usam exatamente as mesmas notas naturais e os mesmos acidentes; o que muda é a nota de repouso. Em Dó maior e Lá menor, por exemplo, as notas são as mesmas; só muda qual delas é a tônica."),
        p (
            "A distância entre um acorde maior e seu relativo menor é sempre de três semitons para baixo (ou nove semitons para cima). Assim, o relativo menor de Dó (C) é Lá (Am): três semitons abaixo. O relativo menor de Sol (G) é Mi (Em); o de Fá (F) é Ré (Dm). Esse padrão vale para qualquer tonalidade maior."),
        b ("Relativo menor de um acorde maior: 3 semitons abaixo."),
        b ("Dó maior (C) → Lá menor (Am). Sol maior (G) → Mi menor (Em)."),
        b ("Os dois compartilham a mesma armadura de clave (mesmas notas)."),
        img ("m5_relativos", "Os pares de relativos: cada acorde maior tem um relativo menor a três semitons abaixo, com as mesmas notas."),

        h ("Por que os relativos soam próximos"),
        p (
            "Os relativos soam próximos porque compartilham quase todas as notas. A tríade de C é Dó–Mi–Sol; a tríade de Am é Lá–Dó–Mi. Repare: Dó e Mi aparecem nas duas. Duas das três notas são as mesmas — só a fundamental muda. Por isso a passagem de C para Am soa suave, como uma troca de cor, e não como uma mudança de tom."),
        p (
            "Essa proximidade é o que torna os relativos tão versáteis. Você pode substituir C por Am no meio de uma progressão e o ouvido não sente que a música saiu do lugar: ele sente apenas que ela ficou mais melancólica. É uma das ferramentas mais simples e mais expressivas da harmonia."),
        tbl ({ "Acorde maior", "Relativo menor", "Notas em comum" }, {
            { "C (Dó maior)", "Am (Lá menor)", "Dó e Mi" },
            { "G (Sol maior)", "Em (Mi menor)", "Sol e Si" },
            { "F (Fá maior)", "Dm (Ré menor)", "Fá e Lá" },
            { "D (Ré maior)", "Bm (Si menor)", "Ré e Fá#" },
        }),
        aud ({ "C4", "E4", "G4", "A3", "C4", "E4" },
             "C (maior) e Am (relativo menor): as mesmas notas, cor diferente."),

        h ("Relativos dentro do campo harmônico"),
        p (
            "No campo harmônico maior, os relativos aparecem naturalmente. O grau I (C) tem como relativo o grau vi (Am); o grau IV (F) tem como relativo o grau ii (Dm); o grau V (G) tem como relativo o grau iii (Em). Ou seja, cada par de relativos dentro do campo é formado por um acorde maior e um acorde menor separados por dois graus."),
        p (
            "Isso explica por que o campo harmônico já contém, de fábrica, os relativos de todos os seus acordes maiores. Quando você troca C por Am, está apenas trocando o I pelo seu relativo; quando troca F por Dm, troca o IV pelo seu. Essas trocas mantêm a música dentro do campo, apenas mudando a cor."),
        b ("I ↔ vi (C ↔ Am) — par relativo principal."),
        b ("IV ↔ ii (F ↔ Dm) — par relativo da subdominante."),
        b ("V ↔ iii (G ↔ Em) — par relativo da dominante."),
        img ("m5_relativos_campo", "Os pares de relativos dentro do campo harmônico de Dó: I–vi, IV–ii e V–iii."),

        h ("Usando os relativos na prática"),
        p (
            "Na prática, os relativos servem para colorir uma progressão sem mudar a sua função. Se você tem uma progressão I – IV – V – I e quer uma versão mais melancólica, pode trocar o I por vi: vi – IV – V – vi. A progressão continua funcionando, mas o clima muda completamente. Isso é usado em toda a música pop e popular."),
        p (
            "Há também a substituição mais radical: trocar o acorde de tônica pelo seu relativo menor, transformando uma música maior em uma música com cara de menor. Muitas vezes, a mesma melodia pode ser harmonizada com C ou com Am como centro, e a escolha muda o significado emocional da música inteira."),
        b ("Troque I por vi para deixar a progressão mais melancólica."),
        b ("Troque IV por ii para suavizar o afastamento."),
        b ("Troque V por iii para reduzir a tensão do dominante."),
        aud ({ "C4", "E4", "G4", "F4", "A4", "C5", "G4", "B4", "D5", "C5", "E5", "G5" },
             "I – IV – V – I em Dó, para comparar com a versão que usa os relativos."),
        part ("m5_partitura_relativos", { "A3", "C4", "E4", "F4", "A4", "C5", "G4", "B4", "D5", "A3", "C4", "E4" },
              "Partitura de vi – IV – V – vi: a mesma progressão, começando pelo relativo menor."),

        h ("Relativo maior e relativo menor"),
        p (
            "A relação de relativos funciona nos dois sentidos. Assim como C tem o relativo Am, o Am tem o relativo C. Quando falamos de uma tonalidade menor, dizemos que o seu relativo maior é a tonalidade maior que compartilha a mesma armadura. Lá menor tem Dó maior como relativo maior; Mi menor tem Sol maior."),
        p (
            "Entender os dois sentidos é importante para a análise. Uma música pode parecer maior, mas ter o centro de gravidade no relativo menor — e vice-versa. Reconhecer qual é a tônica de verdade, e não apenas qual acorde começa, é o que permite identificar corretamente a tonalidade de uma música."),
        b ("Lá menor (Am) tem Dó maior (C) como relativo maior."),
        b ("O relativo maior está sempre 3 semitons acima do menor."),
        b ("A armadura é a mesma; o centro de gravidade é que muda."),

        h ("Os relativos na guitarra"),
        p (
            "No braço, o relativo menor de um acorde maior está sempre três casas abaixo, na mesma região. Se você toca C na 8ª posição (forma de E), o Am está a três casas abaixo. Essa relação física é o que torna tão fácil deslizar de um acorde para o seu relativo durante um acompanhamento."),
        p (
            "Os exercícios deste tópico pedem que você toque um acorde e o seu relativo, e o app confere as notas reconhecidas. Isso confirma que você entendeu a relação: as duas tríades compartilham duas notas e diferem apenas na fundamental. É uma verificação objetiva de um conceito que, de outro modo, ficaria só no papel."),
        b ("O relativo menor está três casas abaixo do acorde maior."),
        b ("Toque o par (maior e relativo) e ouça as notas em comum."),
        b ("Confirme no app se as tríades estão corretas."),

        h ("Relativos e tonalidade menor"),
        p (
            "Os acordes relativos são a porta de entrada para entender as tonalidades menores. Quando você sabe que Lá menor é o relativo de Dó maior, você já sabe que as duas tonalidades compartilham as mesmas notas e a mesma armadura. A diferença está apenas no centro: em Dó maior, o repouso é C; em Lá menor, o repouso é Am."),
        p (
            "Isso significa que uma música escrita com as mesmas notas pode estar em Dó maior ou em Lá menor, dependendo de onde está o seu centro de gravidade. Identificar qual é a tônica — e não apenas qual acorde começa — é o que define a tonalidade. É por isso que os relativos são tão importantes para a análise."),
        b ("Relativos compartilham a armadura e as notas."),
        b ("A diferença está no centro de repouso."),
        b ("As mesmas notas podem servir a duas tonalidades relativas."),

        h ("Exercícios com os relativos"),
        p (
            "Um bom exercício é tocar um acorde maior e o seu relativo menor em sequência, ouvindo as notas em comum. Toque C e depois Am e repare que duas notas permanecem. Depois toque G e Em, F e Dm, D e Bm. Com o tempo, a relação de três semitons fica automática, e você passa a achar o relativo de qualquer acorde no braço sem pensar."),
        p (
            "Outro exercício é pegar uma progressão conhecida e substituir cada acorde pelo seu relativo. Uma progressão I – IV – V – I vira vi – ii – iii – vi. O resultado soa diferente, mas continua coerente. Esse tipo de substituição é uma das ferramentas criativas mais simples e mais usadas para variar uma música sem mudar a sua estrutura."),
        b ("Toque um acorde maior e o seu relativo e ouça as notas em comum."),
        b ("Substitua acordes por seus relativos numa progressão conhecida."),
        b ("Confirme no app se as tríades estão corretas."),
        aud ({ "C4", "E4", "G4", "A3", "C4", "E4", "F4", "A4", "C5", "D4", "F4", "A4" },
             "I – vi – IV – ii: cada acorde maior seguido do seu relativo menor."),

        h ("Relativos no braço"),
        p (
            "No braço, a relação de relativos aparece como um deslocamento fixo: o relativo menor está sempre três casas abaixo do acorde maior, na mesma região. Se você toca o acorde de C na forma aberta, o Am está logo ao lado; se toca o C na 8ª posição (forma de E), o Am está três casas abaixo. Essa regularidade física é o que torna as substituições tão fáceis na prática."),
        p (
            "Além disso, as duas tríades compartilham duas notas, o que significa que, ao trocar um acorde pelo seu relativo, dois dedos permanecem na mesma posição. Esse é um dos motivos pelos quais a troca soa tão natural: o braço quase não se move, mas a cor muda completamente. É uma ferramenta de economia de movimento e de expressão ao mesmo tempo."),
        b ("O relativo menor está três casas abaixo do acorde maior."),
        b ("Dois dedos permanecem na mesma posição na troca."),
        b ("Isso torna as substituições fáceis e fluidas no braço."),
        img ("m5_relativos_campo", "Os pares de relativos no campo de Dó: as trocas mantêm a música dentro da tonalidade."),

        h ("Relativos e a emoção da música"),
        p (
            "Os relativos são uma das ferramentas mais poderosas para mudar a emoção de uma música sem mudar a sua estrutura. A mesma progressão, começando pelo relativo menor em vez da tônica maior, soa imediatamente mais melancólica. É por isso que tantas músicas que parecem tristes usam o relativo menor como centro, mesmo quando a armadura é de uma tonalidade maior."),
        p (
            "Saber usar os relativos é, portanto, saber controlar a cor emocional da música. Comece experimentando substituições simples (I por vi, IV por ii) e ouça o efeito. Com o tempo, você desenvolve a sensibilidade para escolher entre o maior e o menor conforme o que a música pede — e essa escolha é o que distingue um acompanhamento mecânico de um acompanhamento musical."),
        b ("O relativo menor deixa a progressão mais melancólica."),
        b ("Substituições simples mudam a cor sem mudar a estrutura."),
        b ("A escolha entre maior e menor é uma decisão expressiva."),

        h ("Resumo do tópico"),
        b ("Relativos são um par maior/menor com a mesma armadura de clave."),
        b ("O relativo menor está três semitons abaixo do maior."),
        b ("Eles compartilham duas das três notas e soam próximos."),
        b ("No campo harmônico, os pares são I–vi, IV–ii e V–iii."),
        b ("Servem para trocar a cor de uma progressão sem mudar a função."),
        c (
            "Nos exercícios deste tópico, toque um acorde e o seu relativo no instrumento. O app reconhece as notas e confere se o par está correto."),
    };
}

} // namespace cursomusica::content
