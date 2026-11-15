#include "Course/Content/Topics.h"

// Topic 4D — Inversões (Módulo 4, Etapa 4).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 4 — construção de acordes).
namespace cursomusica::content
{

std::vector<ContentItem> topic4D()
{
    return {

        p (
            "Uma tríade tem três notas, mas elas não precisam soar sempre na mesma ordem. Quando a tônica é a nota mais grave, o acorde está na posição fundamental; quando outra nota assume o baixo, o acorde está invertido. Inverter um acorde é mudar qual nota fica embaixo, mantendo as mesmas três notas. Isso não muda a identidade do acorde — um Dó maior invertido continua sendo Dó maior — mas muda completamente a forma como ele soa e como ele conduz a música."),
        p (
            "As inversões são uma das ferramentas mais úteis do acompanhamento. Elas permitem que a linha do baixo se mova suavemente de um acorde para o outro, criando a sensação de uma melodia grave. Também deixam o acompanhamento menos 'quadrado', porque o baixo deixa de pular e passa a caminhar. Neste tópico você aprende as duas inversões da tríade e como usá-las."),
        c (
            "Inverter é mudar a nota do baixo. As notas do acorde continuam as mesmas; só a ordem muda."),

        h ("Posição fundamental"),
        p (
            "A posição fundamental é quando a tônica está no baixo. Em Dó maior, isso significa tocar Dó como a nota mais grave, com Mi e Sol acima. É a posição mais estável e a mais comum. Quando você toca um acorde 'normal', geralmente está tocando a posição fundamental. Ela dá ao acorde o peso e a firmeza de repouso."),
        b ("Tônica no baixo."),
        b ("Som mais estável e conclusivo."),
        b ("É a posição padrão do acorde."),

        h ("Primeira inversão"),
        p (
            "Na primeira inversão, a terça vai para o baixo. Em Dó maior, você toca Mi embaixo, com Sol e Dó acima. O acorde continua sendo Dó maior, mas o baixo é Mi. O som fica mais leve e menos conclusivo: parece que o acorde 'não terminou'. Essa sensação é justamente o que se procura para criar movimento entre dois acordes."),
        b ("Terça no baixo (Mi, no caso de Dó)."),
        b ("Som mais leve e suspenso."),
        b ("Muito usada para conduzir a linha do baixo."),

        h ("Segunda inversão"),
        p (
            "Na segunda inversão, a quinta vai para o baixo. Em Dó maior, você toca Sol embaixo, com Dó e Mi acima. O baixo é Sol. O som é mais instável ainda que o da primeira inversão, e costuma ser usado como acorde de passagem ou como dominante suspensa. Quando o baixo sobe por graus — Sol, Lá, Si, Dó —, a segunda inversão encaixa perfeitamente no caminho."),
        b ("Quinta no baixo (Sol, no caso de Dó)."),
        b ("Som instável, de passagem."),
        b ("Ideal para a linha do baixo subindo ou descendo por graus."),
        img ("m4_inversoes", "As três posições da tríade de Dó: fundamental, 1ª inversão e 2ª inversão."),

        h ("As três posições lado a lado"),
        p (
            "Comparar as três posições do mesmo acorde é a melhor forma de entender as inversões. Repare que as notas nunca mudam: Dó, Mi e Sol aparecem sempre. O que muda é qual delas está embaixo. Toque as três em sequência e ouça como o acorde 'caminha' sem mudar de identidade."),
        tbl ({ "Posição", "Nota no baixo", "Notas em Dó maior", "Sensação" }, {
            { "Fundamental", "tônica (Dó)", "Dó–Mi–Sol", "estável, conclusiva" },
            { "1ª inversão", "terça (Mi)", "Mi–Sol–Dó", "leve, suspensa" },
            { "2ª inversão", "quinta (Sol)", "Sol–Dó–Mi", "instável, de passagem" },
        }),
        aud ({ "C4", "E4", "G4" }, "Dó maior na posição fundamental: Dó no baixo."),
        aud ({ "E4", "G4", "C5" }, "Dó maior na 1ª inversão: Mi no baixo."),
        aud ({ "G3", "C4", "E4" }, "Dó maior na 2ª inversão: Sol no baixo."),

        h ("Por que as inversões importam"),
        p (
            "Imagine uma progressão Dó – Fá – Sol – Dó. Se você tocar todos na posição fundamental, o baixo salta: Dó, Fá, Sol, Dó. Se usar inversões, o baixo pode caminhar por graus: Dó, Dó (com Fá em cima), Sol, Dó. A música soa muito mais fluida. Essa é a principal razão das inversões: manter a linha do baixo em movimento suave, sem saltos."),
        b ("Baixo em movimento suave, sem saltos."),
        b ("Acompanhamento menos 'quadrado'."),
        b ("Sensação de uma segunda melodia na região grave."),
        aud ({ "C4", "E4", "G4", "C4", "F4", "A4", "B3", "D4", "G4" },
             "Dó – Fá – Sol com o baixo caminhando: as inversões mantêm a linha grave em movimento."),

        h ("Como identificar uma inversão"),
        p (
            "Identificar a inversão é simples: olhe para a nota mais grave do acorde. Se for a tônica, é fundamental; se for a terça, é primeira inversão; se for a quinta, é segunda inversão. Na cifra, a inversão aparece depois de uma barra: C/E significa 'acorde de Dó com Mi no baixo' (primeira inversão); C/G significa 'Dó com Sol no baixo' (segunda inversão)."),
        tbl ({ "Cifra", "Acorde", "Nota no baixo", "Inversão" }, {
            { "C", "Dó maior", "Dó", "fundamental" },
            { "C/E", "Dó maior", "Mi", "1ª inversão" },
            { "C/G", "Dó maior", "Sol", "2ª inversão" },
            { "Am/C", "Lá menor", "Dó", "1ª inversão" },
        }),

        h ("Inversões no braço"),
        p (
            "No braço, as inversões aparecem como o mesmo conjunto de notas em ordens diferentes. Como a guitarra tem seis cordas, você pode tocar a tríade em grupos de três cordas e escolher qual nota fica na corda mais grave do grupo. Isso dá uma enorme variedade de posições. Uma boa prática é tocar o mesmo acorde nas três inversões em uma mesma região do braço."),
        b ("Três notas em três cordas: escolha qual fica embaixo."),
        b ("Mesmo acorde, três posições na mesma região."),
        b ("Treine as três inversões em sequência, sem parar."),

        h ("Inversões e a linha do baixo"),
        p (
            "A grande aplicação das inversões é construir uma linha de baixo. Em vez de tocar acordes soltos, você desenha uma melodia grave que sustenta a harmonia. Em uma progressão que desce por graus — Dó, Si, Lá, Sol —, você escolhe as inversões que colocam exatamente essas notas no baixo. O resultado é um acompanhamento que 'canta'."),
        b ("Escolha a inversão pela nota que você quer no baixo."),
        b ("Linhas por graus (Dó, Si, Lá, Sol) são muito eficazes."),
        b ("A linha do baixo dá coesão ao acompanhamento."),

        h ("Inversões e o baixo caminhante"),
        p (
            "Quando a linha do baixo se move por graus conjuntos, ela cria o efeito chamado de walking bass. Esse recurso é a alma do jazz e aparece também na bossa nova e no blues. As inversões são a ferramenta que permite ao guitarrista acompanhar essa linha sem perder a harmonia. Tocar a progressão com o baixo caminhando é uma das habilidades mais gratificantes do acompanhamento."),
        b ("Baixo caminhante: linha grave em movimento por graus."),
        b ("Cada nota do caminho pede uma inversão diferente."),
        b ("Presente no jazz, na bossa nova e no blues."),

        h ("Inversões e as cordas da guitarra"),
        p (
            "A guitarra favorece certas inversões em certas regiões. Nas cordas graves, a posição fundamental soa mais firme; nas cordas agudas, as inversões soam mais leves. Conhecer esse mapa ajuda a escolher onde tocar cada acorde. Uma boa prática é tocar a mesma progressão em três regiões diferentes do braço — grave, média e aguda — e ouvir como as inversões se comportam em cada uma."),
        b ("Região grave: posição fundamental tende a soar melhor."),
        b ("Região aguda: as inversões soam leves e claras."),
        b ("Explore a mesma progressão em três regiões."),

        h ("Inversão e o baixo como melodia"),
        p (
            "Em muitos estilos, o baixo deixa de ser apenas o 'chão' do acorde e passa a ser uma melodia em si. Na bossa nova, por exemplo, a linha do baixo é quase uma segunda voz, que dialoga com a melodia cantada. As inversões são o que permitem ao guitarrista tocar essa linha enquanto mantém a harmonia. Sem as inversões, o baixo ficaria preso à tônica e não poderia 'cantar'."),
        b ("O baixo pode ser uma melodia, não só o chão do acorde."),
        b ("Bossa nova e jazz exploram o baixo melódico."),
        b ("As inversões liberam o baixo para se mover."),

        h ("Inversões e a melodia"),
        p (
            "As inversões também ajudam quando você toca e canta ao mesmo tempo. Se a melodia está em uma região aguda, você pode escolher a inversão que deixa as notas do acorde mais graves, sem competir com a voz. Se a melodia está grave, faça o contrário. Assim, acorde e melodia ocupam espaços diferentes e o som fica limpo."),
        b ("Melodia aguda: acorde mais grave."),
        b ("Melodia grave: acorde mais agudo."),
        b ("Evite que acorde e melodia briguem pelo mesmo espaço."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é achar que o acorde invertido 'é outro acorde'. Não é: a identidade está nas notas, não na ordem. Outro erro é inverter sem intenção, deixando o baixo saltar justamente onde deveria caminhar. E há o erro de inverter acordes em que a inversão soa instável demais para o momento — a segunda inversão, por exemplo, pede resolução."),
        b ("Inversão não é outro acorde: são as mesmas notas."),
        b ("Inverta com intenção, olhando a linha do baixo."),
        b ("Cuidado com inversões instáveis em pontos de repouso."),

        h ("Treinando as inversões"),
        p (
            "Um treino eficiente é pegar uma única tríade e tocar as três posições em sequência, em uma mesma região do braço, sem parar e sem olhar. Comece devagar: fundamental, primeira inversão, segunda inversão, e de volta. Depois faça o mesmo com outras tônicas e em outras regiões. Com o tempo, a mão encontra qualquer inversão sem esforço, e o ouvido reconhece a sensação de cada uma."),
        b ("Uma tríade, três posições, sem parar."),
        b ("Repita em outras tônicas e outras regiões."),
        b ("Objetivo: achar a inversão sem olhar o braço."),
        p (
            "Depois de dominar as três posições de uma tríade, aplique em uma progressão: escolha as inversões que suavizam o baixo. Você vai perceber que, com as inversões, o acompanhamento deixa de ser uma sequência de formas e passa a ser uma linha musical. É um salto de qualidade que vale o esforço."),

        h ("Aplicação musical"),
        p (
            "Experimente tocar a progressão Dó – Fá – Sol – Dó duas vezes: primeiro toda na posição fundamental, depois com inversões escolhidas para suavizar o baixo. A segunda versão soa muito mais musical. Esse é o tipo de refinamento que faz a diferença em qualquer estilo — da bossa nova ao pop. O app reconhece as notas em qualquer inversão, porque confere o conjunto de notas, não a ordem."),
        b ("Toque a progressão fundamental, depois invertida."),
        b ("Compare a sensação das duas versões."),
        b ("O app confere as notas, não a inversão."),
        part ("m4_partitura_inversao", { "E4", "G4", "C5" },
              "Partitura da 1ª inversão de Dó maior (Mi–Sol–Dó), com Mi no baixo."),

        h ("Resumo do tópico"),
        b ("Inverter é mudar a nota do baixo, mantendo as mesmas notas."),
        b ("Fundamental: tônica no baixo. 1ª inversão: terça. 2ª inversão: quinta."),
        b ("Na cifra, a inversão aparece depois da barra (C/E, C/G)."),
        b ("A principal aplicação é suavizar a linha do baixo."),
        b ("O acorde invertido continua sendo o mesmo acorde."),
        c (
            "Nos exercícios deste tópico, toque as tríades pedidas nas diferentes inversões. O app reconhece as notas e confere a qualidade do acorde, aceitando qualquer inversão e qualquer posição do braço."),
    };
}

} // namespace cursomusica::content
