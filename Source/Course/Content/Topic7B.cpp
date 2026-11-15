#include "Course/Content/Topics.h"

// Topic 7B — Empilhamentos quartais (Módulo 7, Etapa 7).
// Fonte de verdade do texto: docs/MUSIC.md §7.2 (bloco B).
namespace cursomusica::content
{

std::vector<ContentItem> topic7B()
{
    return {

        p (
            "Se o empilhamento de terças constrói os acordes tradicionais, o empilhamento de quartas constrói um som diferente, moderno e aberto, que você ouve o tempo todo no jazz modal, na bossa, no rock e no pop. Aqui a distância entre as notas é a quarta, não a terça, e o resultado é um acorde sem cara de maior nem de menor — uma sonoridade suspensa, pairando, que parece não pedir resolução."),
        p (
            "Empilhar quartas é somar intervalos de quarta justa, um sobre o outro. É a técnica que dá origem aos acordes do jazz modal (o famoso acorde de So What) e a muitos voicings usados em vamps de um ou dois acordes, exatamente o nível em que este módulo se encontra."),

        h ("O que é uma quarta justa"),
        p (
            "A quarta justa tem 5 semitons. De Dó a Fá são 5 semitons; de Fá a Sib, outros 5. Uma quarta justa soa firme, de chamada, e é um dos intervalos mais estáveis da música. Empilhar quartas justas é colocar cada nota a 5 semitons da anterior."),
        tbl ({ "Nota", "Semitons a partir da tônica (Dó)", "Grau" }, {
            { "Dó", "0", "1" },
            { "Fá", "5", "4" },
            { "Sib", "10", "b7" },
            { "Mib", "15 (= 3)", "b3 (oitava acima)" },
        }),
        p (
            "Repare que, ao empilhar quartas, a segunda nota cai no quarto grau, a terceira no sétimo grau menor e a quarta volta a um grau da tríade, uma oitava acima. Como não há terça no empilhamento, o acorde não é nem maior nem menor: ele é modal, aberto."),
        c (
            "Fique atento: um empilhamento de quartas justas pode ser lido como uma tríade invertida com notas acrescentadas. Dó–Fá–Sib é o mesmo conjunto de notas que Fá–Sib–Dó, que é um acorde de Sib com quarta e nona. É essa ambiguidade que dá ao som quartal a sua riqueza."),

        h ("O acorde de So What"),
        p (
            "O exemplo mais conhecido de empilhamento quartal é o acorde que abre a música So What, de Miles Davis. Ele é feito de três quartas justas empilhadas com uma terça maior no topo: em Dó, isso dá as notas Dó–Fá–Sib–Mib–Sol. A terça do topo (Sol) é o que amarra o acorde à tonalidade."),
        b ("Base: três quartas justas empilhadas (Dó–Fá–Sib–Mib)."),
        b ("Topo: uma terça maior que define o centro (Mib–Sol)."),
        b ("O acorde é móvel: o mesmo desenho serve para qualquer centro."),
        aud ({ "C4", "F4", "A#3", "D#4", "G4" }, "Acorde quartal no estilo So What: quartas empilhadas com terça no topo. Som suspenso e modal."),
        img ("m7_quartais_empilhadas", "Empilhamento quartal: quartas justas sobrepostas, com a terça no topo."),

        h ("Quartas justas e quartas aumentadas"),
        p (
            "Dentro de uma escala, nem toda quarta é justa: a quarta entre Fá e Si, por exemplo, é aumentada (6 semitons), o famoso trítono. Quando você empilha quartas dentro de uma escala, essa quarta aumentada aparece naturalmente em uma das posições e é justamente ela que dá o caráter modal específico do acorde."),
        tbl ({ "Empilhamento dentro de Dó maior", "Semitons", "Efeito" }, {
            { "Dó–Fá–Si", "0, 5, 11", "quarta aumentada no topo (Si) = cor lídia" },
            { "Dó–Fá–Sib", "0, 5, 10", "quartas justas (Sib fora do tom) = som dominante" },
            { "Ré–Sol–Dó", "0, 5, 10", "quartal sobre Ré (dórico)" },
            { "Sol–Dó–Fá", "0, 5, 10", "quartal sobre Sol (mixolídio)" },
        }),
        p (
            "Por isso o empilhamento quartal é tão usado em música modal: ele “veste” o modo com muita naturalidade. Se você empilha quartas a partir de cada grau da escala, obtém acordes que soam como aquele modo."),

        h ("Quartal versus terça: como soa cada um"),
        p (
            "Comparar os dois empilhamentos é a melhor forma de entender a diferença. O empilhamento de terças define claramente maior ou menor; o de quartas é ambíguo. Essa ambiguidade é uma ferramenta: quando você quer um som suspenso, sem tensão de resolução, o quartal é a escolha."),
        tbl ({ "Empilhamento", "Som", "Onde se usa" }, {
            { "terças (1-3-5-7)", "define maior/menor", "harmonia tonal, jazz tradicional" },
            { "quartas (1-4-b7-b3)", "suspenso, modal", "jazz modal, vamps, bossa moderna" },
            { "quintas (1-5-9)", "aberto, forte", "power chords, rock" },
        }),
        aud ({ "C4", "E4", "G4", "B4" }, "Empilhamento de terças: Cmaj7, claro e definido."),
        aud ({ "C4", "F4", "A#3", "D#4" }, "Empilhamento de quartas: som suspenso, sem maior nem menor."),

        h ("Como usar na guitarra"),
        p (
            "Na guitarra, o empilhamento quartal é muito confortável. As cordas vizinhas (exceto a 2ª, que é afinada em terça) permitem tocar quartas com o mesmo desenho de mão, deslocando-o pelo braço. Um acorde quartal pode ser tocado com duas, três ou quatro cordas, e o mesmo desenho vale para qualquer tônica."),
        b ("Duas cordas vizinhas na mesma casa: uma quarta (exceto entre a 3ª e a 2ª)."),
        b ("Três cordas: quartas empilhadas."),
        b ("O desenho se move pelo braço sem mudar de forma."),
        img ("m7_quartais_empilhadas", "O desenho quartal no braço: o mesmo formato serve para qualquer centro modal."),

        h ("Quartal na prática"),
        p (
            "Você já ouviu acordes quartais em vamps de um acorde, em passagens de bossa e em trechos de rock. Toque um vamp com acordes quartais e perceba como a harmonia fica suspensa, sem a direção previsível da cadência. Esse é o som modal: um centro, uma cor, sem pressa de resolver."),
        b ("Use quartal em vamps de um ou dois acordes."),
        b ("Use para criar um som “moderno” sem sair do tom."),
        b ("Combine quartas com uma terça no topo para amarrar o centro."),
        c (
            "Os exercícios deste tópico pedem que você toque acordes quartais e o app reconhece as notas para conferir o empilhamento. Você pode tocar em qualquer região do braço; o que o app mede é o conjunto de notas."),

        h ("Vozes e dobramentos"),
        p (
            "Um acorde quartal pode ter duas, três ou quatro vozes. Quanto mais vozes, mais denso o som; quanto menos, mais claro. Em vamps modais, os voicings de três ou quatro vozes são os mais usados, porque preenchem o espectro sem competir com a melodia. Dobrar a nota do topo uma oitava acima dá brilho; dobrar a base dá peso."),
        b ("Duas vozes: um par de quartas, leve e aberto."),
        b ("Três vozes: o voicing modal mais comum."),
        b ("Quatro vozes: som cheio, ótimo para acompanhamento."),
        aud ({ "C4", "F4", "A#3", "D#4", "G4" }, "Quatro vozes quartais com a terça no topo: som modal completo."),

        h ("Quartal e a bossa moderna"),
        p (
            "Na bossa nova e na MPB, o empilhamento quartal aparece em acordes de passagem e em vamps, dando aquele som “aberto” característico. Combinado com a levada sincopada, ele cria a sensação de movimento sem mudança de centro, exatamente o que a música brasileira moderna faz tão bem."),
        b ("Vamps com quartas dão movimento sem cadência."),
        b ("Acordes de passagem quartais ligam áreas tonais."),
        b ("Combine com a levada de bossa para o som brasileiro."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é confundir quarta justa com quarta aumentada e “errar” a nota do topo. Outro é tentar usar o empilhamento quartal como se fosse um acorde tonal, esperando dele a mesma função de resolução. O quartal não resolve: ele permanece, e é isso que o torna modal."),
        b ("Contar os semitons: quarta justa = 5, aumentada = 6."),
        b ("Não esperar função dominante de um acorde quartal."),
        b ("Verificar a nota do topo, que amarra o acorde à tonalidade."),

        h ("Quartal e o som suspenso"),
        p (
            "Uma das razões pelas quais o empilhamento quartal é tão apreciado na música moderna é a sensação de suspensão que ele produz. Sem a terça, o ouvido não sabe dizer se o acorde é maior ou menor, e essa ambiguidade mantém a harmonia aberta. Em vez de conduzir a uma resolução, o acorde quartal convida a permanecer."),
        b ("Sem terça, o acorde é neutro quanto a maior/menor."),
        b ("A suspensão convida a permanecer, não a resolver."),
        b ("É a ferramenta ideal para vamps longos."),
        p (
            "Na prática, isso significa que um acorde quartal funciona bem sobre um baixo que se move lentamente, sem criar a expectativa de uma cadência. É por isso que ele aparece tanto em música modal, em trilhas sonoras e em passagens que precisam de um clima estável, mas não monótono."),

        h ("Quartal na guitarra: exemplos de desenho"),
        p (
            "Para tocar um empilhamento quartal na guitarra, você usa cordas vizinhas na mesma casa ou em casas próximas. Como as cordas (exceto a segunda) estão afinadas em quartas, tocar a mesma casa em duas cordas vizinhas produz exatamente uma quarta. Empilhando esse desenho, você obtém o acorde quartal completo."),
        b ("Duas cordas na mesma casa: uma quarta justa."),
        b ("Três cordas: duas quartas empilhadas."),
        b ("Quatro cordas: três quartas empilhadas."),
        b ("A terça no topo (para o som de So What) fica a uma casa de distância, na corda seguinte."),
        c (
            "Cuidado com a segunda corda: por ser afinada em terça, o desenho muda quando você passa por ela. Ajuste a mão uma casa para compensar."),

        h ("Quartal versus a tríade invertida"),
        p (
            "Um ponto importante: um empilhamento de quartas justas é, muitas vezes, o mesmo conjunto de notas que uma tríade invertida com notas acrescentadas. Por exemplo, Dó–Fá–Sib é o mesmo que Sib–Dó–Fá, que é um acorde de Sib com quarta e nona. Reconhecer essa equivalência ajuda a entender por que os acordes quartais soam tão familiares, mesmo sendo diferentes."),
        b ("Dó–Fá–Sib = Sib com nona (a partir do baixo Sib)."),
        b ("A leitura depende do baixo e do contexto."),
        b ("O mesmo conjunto de notas serve a várias funções."),

        h ("Aplicando o empilhamento quartal"),
        p (
            "Use o empilhamento quartal sempre que quiser um som suspenso, moderno e sem resolução. Ele é excelente para introduções, para vamps de um acorde e para passagens que precisam de um clima estável. Combinado com uma melodia simples, o acorde quartal cria um fundo rico sem competir com o solista."),
        b ("Introduções e vamps."),
        b ("Passagens de clima estável."),
        b ("Fundos para improvisação modal."),

        h ("Erros comuns no empilhamento quartal"),
        p (
            "O erro mais frequente é esperar que o acorde quartal resolva como um acorde tonal. Ele não resolve: ele permanece. Outro erro é tocar a quarta aumentada pensando que é justa, o que muda a cor do empilhamento. Conferir os semitons e aceitar a natureza suspensa do som são os dois cuidados que evitam esses tropeços."),
        b ("Não espere resolução de um acorde quartal."),
        b ("Confira se a quarta é justa (5 semitons) ou aumentada (6)."),
        b ("Aceite a suspensão: é a identidade do som quartal."),

        h ("Resumo do tópico"),
        b ("Empilhar quartas é somar intervalos de quarta justa (5 semitons)."),
        b ("O acorde quartal não é maior nem menor: é suspenso e modal."),
        b ("O acorde de So What empilha três quartas e uma terça no topo."),
        b ("É a ferramenta principal dos vamps modais."),
        b ("Cuidado com a quarta aumentada, que muda a cor do empilhamento."),
        part ("m7_partitura_quartal", { "C4", "F4", "A#3", "D#4", "G4" },
              "Partitura: acorde quartal no estilo So What (quartas empilhadas com terça no topo). Ouça o som modal."),
    };
}

} // namespace cursomusica::content
