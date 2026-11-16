#include "Course/Content/Topics.h"

// Topic 9I — Sonoridades especiais (Modulo 9, Etapa 9).
// Fonte de verdade do texto: docs/MUSIC.md (bloco I da Etapa 9).
namespace cursomusica::content
{

std::vector<ContentItem> topic9I()
{
    return {

        p (
            "Ao longo deste módulo você estudou acordes diminutos, dominantes diminutos, ciclos, campos harmônicos e policordes. Neste último tópico você conhece outras sonoridades especiais: estruturas que fogem do acorde tradicional empilhado em terças e que dão cores novas a harmonia. São os acordes quartais, os clusters, as estruturas superiores e as inversões expressivas."),
        p (
            "O objetivo não é decorar cada uma, mas entender a lógica de cada estrutura e saber quando usá-la. Cada sonoridade especial tem um uso: dar cor, criar tensão, movimentar a harmonia ou suspender a resolução."),

        h ("O acorde quartal"),
        p (
            "O acorde quartal é construído empilhando quartas em vez de terças. Sobre Do, por exemplo: Do, Fa, Sib e Mib (0, 5, 10 e 15). O som é aberto, sem a terça que define maior ou menor, o que dá ao acorde uma qualidade ambígua e moderna. É a sonoridade clássica do jazz modal, imortalizada em Só What, de Miles Davis."),
        b ("Empilha quartas em vez de terças."),
        b ("Sem terça: não é maior nem menor."),
        b ("Som aberto, moderno, sem direção."),
        aud ({ "C4", "F4", "A#4", "D#5" },
             "Acorde quartal sobre Do: quartas empilhadas, som aberto e ambíguo."),

        h ("O cluster"),
        p (
            "Cluster é um conjunto de notas vizinhas soando ao mesmo tempo. Em vez de distribuir as notas por terças, o cluster as junta em semitons ou tons. O efeito é denso e tenso, e por isso o cluster é usado em momentos de clímax ou de suspensao. Na guitarra, um cluster pode ser feito tocando duas ou três cordas vizinhas em casas proximas."),
        b ("Notas vizinhas soando juntas."),
        b ("Som denso, usado em clímax."),
        b ("Na guitarra, cordas vizinhas em casas proximas."),
        aud ({ "C4", "C#4", "D4", "D#4" },
             "Um cluster: quatro notas vizinhas soando juntas. A densidade é o efeito."),

        h ("As estruturas superiores"),
        p (
            "Estrutura superior é uma tríade tocada sobre um acorde dominante, criando as tensões de forma organizada. Em vez de pensar em cada tensão separadamente, o músico toca uma tríade inteira por cima. Por exemplo, sobre C7, uma tríade de Re maior (D) traz as tensões 9, #11 e 13. É o mesmo princípio do policorde, aplicado especificamente sobre dominantes."),
        b ("Tríade sobre um dominante."),
        b ("Cada tríade traz um conjunto de tensões."),
        b ("Simplifica o pensamento sobre tensões complexas."),
        aud ({ "C4", "E4", "A#4", "D5", "F#5", "A5" },
             "Estrutura superior de Re maior sobre C7: as tensões aparecem de forma organizada."),

        h ("Acordes com nona e sexta"),
        p (
            "Outro grupo de sonoridades especiais vem de acrescentar a nona ou a sexta a uma tríade. O acorde add9 mantém a tríade e acrescenta a nona, dando um som luminoso e moderno. O acorde 6/9 acrescenta a sexta e a nona, criando uma sonoridade doce muito usada na bossa nova. Esses acordes não substituem a função do acorde; eles apenas o colorem."),
        tbl ({ "Acorde", "Notas sobre Do", "Intervalos (semitons)", "Uso" }, {
            { "Cadd9", "Do - Mi - Sol - Re", "0 - 4 - 7 - 14", "som luminoso" },
            { "C6", "Do - Mi - Sol - Lá", "0 - 4 - 7 - 9", "som doce" },
            { "C6/9", "Do - Mi - Sol - Lá - Re", "0 - 4 - 7 - 9 - 14", "bossa nova" },
        }),
        c (
            "A nona e a sexta não mudam a função do acorde. Elas acrescentam cor sem transformar um maior em dominante ou em menor."),
        aud ({ "C4", "E4", "G4", "D5" }, "Cadd9: a nona sobre a tríade, som luminoso."),
        aud ({ "C4", "E4", "G4", "A4" }, "C6: a sexta no lugar da sétima, som doce."),
        aud ({ "C4", "E4", "G4", "A4", "D5" }, "C6/9: sexta e nona juntas, a cor da bossa nova."),

        h ("Inversões expressivas"),
        p (
            "Uma inversão acontece quando a nota mais grave do acorde não é a tônica. Já estudamos isso no módulo de acordes, mas vale lembrar aqui o efeito expressivo. Uma inversão muda o baixo sem mudar o acorde, e por isso é uma forma de conduzir as vozes suavemente de um acorde para outro. Em passagens de bossa e de jazz, as inversões são a base da condução."),
        b ("Inversão muda o baixo, não as notas."),
        b ("Conduz as vozes com menos saltos."),
        b ("Muito usada em bossa e jazz."),
        aud ({ "E4", "G4", "C5" }, "Do maior na primeira inversão: Mi no baixo. O acorde é o mesmo, o baixo mudou."),

        h ("Escolhendo a sonoridade certa"),
        p (
            "Cada sonoridade especial tem um lugar. O acorde quartal funciona em passagens modais e como acorde suspenso. O cluster é para momentos de tensão máxima. As estruturas superiores são para dominantes que precisam de cor. Os acordes com nona e sexta dão brilho a tríades simples. As inversões conduzem as vozes. Saber qual usar é o que separa o arranjo comum do arranjo expressivo."),
        b ("Quartal: modal, suspenso, moderno."),
        b ("Cluster: tensão máxima, clímax."),
        b ("Estrutura superior: dominantes coloridos."),
        b ("Add9 e 6/9: brilho e doçura."),
        b ("Inversões: condução de vozes."),
        img ("m9_sonoridades", "Sonoridades especiais: quartal, cluster, add9, slash e estrutura superior."),

        h ("Combinando as sonoridades"),
        p (
            "Na prática, as sonoridades especiais raramente aparecem isoladas. Um arranjo de jazz pode combinar um policorde, uma estrutura superior e uma inversão no mesmo compasso. O que importa é que a soma tenha lógica: cada estrutura deve estar a servico da música, e não apenas empilhada por empilhar."),
        b ("Combine as sonoridades dentro de uma progressão."),
        b ("Cada estrutura deve ter uma função clara."),
        b ("Ouça sempre o resultado final, não as partes."),
        aud ({ "C4", "E4", "A#4", "D5", "F#5", "A5", "G4", "C5" },
             "Uma estrutura superior resolvendo: a cor complexa cede para a tônica simples."),

        h ("Erros comuns"),
        p (
            "O erro mais frequente é usar sonoridades especiais em excesso, o que faz a música soar confusa. Outro erro é usá-las sem entender a função, apenas porque soam diferentes. A sonoridade especial é um tempero: em exagero, estraga o prato."),
        b ("Usar sonoridades especiais em excesso."),
        b ("Empilhar estruturas sem função clara."),
        b ("Esquecer que o repouso também é importante."),
        c (
            "Se a música soar carregada demais, simplifique. A sonoridade especial funciona melhor quando contrasta com momentos simples."),

        h ("Aplicando na prática"),
        p (
            "Escolha uma progressão simples e experimente substituir um acorde por cada sonoridade especial que você estudou. Toque a versão simples, depois a colorida, e compare. O objetivo é aprender a dosar: a música deve continuar reconhecível, apenas mais rica."),
        b ("Substitua um acorde por um acorde quartal."),
        b ("Acrescente uma nona ou sexta a uma tríade."),
        b ("Use uma estrutura superior sobre um dominante."),
        aud ({ "C4", "E4", "G4", "C4", "F4", "A#4", "D#5" },
             "Uma tríade simples e depois um acorde quartal: o contraste de cor."),

        h ("O acorde quartal na partitura"),
        p (
            "Na partitura, o acorde quartal é escrito como uma pilha de quartas, e não de terças. Isso faz com que a sua leitura seja diferente da dos acordes tradicionais: as notas não formam uma tríade reconhecível. Ler um acorde quartal é reconhecer o intervalo de quarta entre cada par de notas vizinhas, e não uma fundamental com terça e quinta."),
        b ("As notas são empilhadas em quartas."),
        b ("Não há terça, então o acorde é ambíguo."),
        b ("Ler um quartal é reconhecer as quartas entre as notas."),

        h ("As sonoridades especiais na improvisação"),
        p (
            "Na improvisação, as sonoridades especiais abrem um vocabulário novo. Sobre um acorde quartal, o improvisador pode tocar a escala quartal ou simplesmente arpejar as quartas. Sobre um cluster, pode explorar as notas vizinhas. Sobre uma estrutura superior, pode tocar as notas da tríade de cima. Cada sonoridade pede uma abordagem própria, e conhecê-las amplia muito o que se pode dizer num solo."),
        b ("Sobre o quartal, arpejar as quartas."),
        b ("Sobre o cluster, explorar as notas vizinhas."),
        b ("Sobre a estrutura superior, tocar a tríade de cima."),

        h ("Dosando as sonoridades especiais"),
        p (
            "O uso das sonoridades especiais depende do equilíbrio. Uma música inteira de quartais e clusters soa densa demais; um único momento de cluster, no lugar certo, é devastador. O músico experiente alterna momentos simples e momentos ricos, e é esse contraste que dá expressão à música. A sonoridade especial é um recurso de expressão, não um fim em si."),
        b ("Alterne momentos simples e momentos ricos."),
        b ("O contraste é o que dá expressão."),
        b ("A sonoridade especial é um recurso, não um fim."),
        aud ({ "C4", "E4", "G4", "C5", "C4", "F4", "A#4", "D#5" },
             "Uma tríade simples e depois um acorde quartal: o contraste de cor fica claro."),

        h ("As sonoridades especiais na composição"),
        p (
            "Ao compor, o músico escolhe a sonoridade especial de acordo com o momento da música. Uma introdução pode usar um acorde quartal para criar abertura; um clímax, um cluster para a máxima tensão; uma resolução, uma estrutura superior que se desfaz na tônica. Ter esse vocabulário à mão é o que permite dar à música uma forma expressiva, com momentos de tensão e de repouso bem marcados."),
        b ("Escolha a sonoridade pelo momento da música."),
        b ("Introdução: quartal; clímax: cluster; resolução: estrutura superior."),
        b ("O vocabulário dá forma expressiva à música."),

        h ("As sonoridades especiais e o estilo"),
        p (
            "Cada estilo tem as suas sonoridades preferidas. A bossa nova explora os acordes com nona e sexta; o jazz, as estruturas superiores e os policordes; a fusão, os clusters e os quartais; o rock progressivo, as sobreposições densas. Conhecer essas preferências ajuda o aluno a escolher a sonoridade certa para cada contexto e a reconhecer o estilo pelo ouvido."),
        b ("Bossa: acordes com nona e sexta."),
        b ("Jazz: estruturas superiores e policordes."),
        b ("Fusão: clusters e quartais; rock progressivo: sobreposições densas."),
        aud ({ "C4", "E4", "G4", "A4", "D5" },
             "Um acorde com sexta e nona: a cor doce típica da bossa nova."),

        h ("Reconhecendo as sonoridades especiais"),
        p (
            "Cada sonoridade especial tem uma assinatura sonora. O quartal soa aberto e sem direção; o cluster, denso e tenso; a estrutura superior, brilhante e tensa; o acorde com nona e sexta, doce e luminoso. Aprender a reconhecer cada uma pelo ouvido permite identificar o estilo de uma música e reproduzir a sonoridade que se quer. É o último passo do estudo da harmonia avançada."),
        b ("Quartal: aberto e sem direção."),
        b ("Cluster: denso e tenso."),
        b ("Estrutura superior: brilhante e tenso; add9/6-9: doce e luminoso."),

        h ("Praticando as sonoridades especiais"),
        p (
            "Praticar as sonoridades especiais começa por ouvir cada uma isoladamente e associá-la a uma sensação. Depois, toca-se a mesma progressão em versões diferentes, uma simples e uma com a sonoridade especial, para comparar. Por fim, usa-se a sonoridade escolhida numa música real. O objetivo é que a escolha deixe de ser teórica e passe a ser guiada pelo ouvido."),
        b ("Ouça cada sonoridade isoladamente."),
        b ("Compare a versão simples com a versão colorida."),
        b ("Use a sonoridade escolhida numa música real."),
        aud ({ "C4", "E4", "G4", "A4", "D5", "C4", "F4", "A#4", "D#5" },
             "Add9 e depois quartal: duas cores diferentes sobre a mesma tônica."),

        h ("Resumo do tópico"),
        b ("Quartal: quartas empilhadas, som aberto e ambíguo."),
        b ("Cluster: notas vizinhas, som denso."),
        b ("Estrutura superior: tríade sobre dominante."),
        b ("Add9 e 6/9: cor sem mudar a função."),
        b ("Inversões: condução suave das vozes."),
        b ("Todas funcionam melhor em contraste com momentos simples."),
        c (
            "Nos exercícios, toque as sonoridades especiais e as suas resoluções. O app reconhece as notas e confere as classes de altura."),
    };
}

} // namespace cursomusica::content
