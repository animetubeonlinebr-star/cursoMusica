#include "Course/Content/Topics.h"

// Topic 4C — Tríades abertas e fechadas (Módulo 4, Etapa 4).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 4 — construção de acordes).
namespace cursomusica::content
{

std::vector<ContentItem> topic4C()
{
    return {

        p (
            "Um mesmo acorde pode ser tocado de várias maneiras. As notas são sempre as mesmas — em Dó maior, Dó, Mi e Sol —, mas a forma como elas se distribuem pelo braço muda completamente o som. A essa organização das notas dentro do acorde chamamos de disposição, e as duas mais importantes são a fechada e a aberta. Entender a diferença é o que permite escolher o acorde certo para cada momento da música."),
        p (
            "Disposição fechada (ou cerrada) é quando as notas do acorde ficam próximas umas das outras, dentro de uma oitava. Disposição aberta (ou espalhada) é quando as notas se distribuem por uma extensão maior, com saltos entre elas. A escolha entre as duas não é decorativa: ela muda o peso, a clareza e a cor do acorde."),
        c (
            "Disposição é a ordem e o espaçamento das notas do acorde. A tônica, a terça e a quinta não mudam — só a forma como estão distribuídas."),

        h ("O que é disposição fechada"),
        p (
            "Na disposição fechada, as três notas ficam o mais próximo possível uma da outra. Em Dó maior, tocando Dó–Mi–Sol com as notas vizinhas, o acorde soa compacto, direto e claro. É a disposição mais comum no acompanhamento de guitarra e de violão, porque cabe facilmente na mão e projeta bem o som. Quando você toca um acorde 'normal', geralmente está tocando uma disposição fechada."),
        b ("Notas próximas, dentro de uma oitava."),
        b ("Som compacto e direto."),
        b ("Fácil de segurar e de projetar."),
        img ("m4_abertas_fechadas", "Disposição fechada (notas vizinhas) e aberta (notas espalhadas) do acorde de Dó."),

        h ("O que é disposição aberta"),
        p (
            "Na disposição aberta, as notas se espalham por uma região maior do braço. Em vez de Dó–Mi–Sol juntos, você pode tocar Dó grave, Sol no meio e Mi agudo, por exemplo. O som fica mais amplo, mais 'largo' e mais rico, porque cada nota ocupa um registro diferente. É a disposição típica de arranjos de violão, de introduções e de acordes com cordas soltas."),
        b ("Notas espalhadas por uma região maior do braço."),
        b ("Som amplo, aberto e cheio."),
        b ("Cada nota ocupa um registro diferente."),

        h ("Fechada e aberta lado a lado"),
        p (
            "A melhor forma de entender a diferença é ouvir as duas versões do mesmo acorde, uma depois da outra. O acorde é o mesmo (Dó maior), as notas são as mesmas (Dó, Mi, Sol), mas o efeito é diferente. A fechada soa como um bloco; a aberta soa como um acorde 'desenhado' no espaço. Nenhuma é melhor: cada uma serve a um propósito."),
        tbl ({ "Disposição", "Distribuição", "Som", "Uso típico" }, {
            { "Fechada", "notas próximas, dentro da oitava", "compacto, direto", "acompanhamento" },
            { "Aberta", "notas espalhadas, com saltos", "amplo, cheio", "arranjo, introdução" },
        }),
        aud ({ "C4", "E4", "G4" }, "Dó maior em disposição fechada: notas vizinhas, som compacto."),
        aud ({ "C3", "G3", "E4" }, "Dó maior em disposição aberta: notas espalhadas, som amplo."),

        h ("Como medir o espaçamento"),
        p (
            "O espaçamento é a distância entre as notas. Na disposição fechada, cada nota está a uma terça (ou a um intervalo pequeno) da seguinte. Na aberta, as distâncias são maiores: pode haver uma quinta, uma sexta ou até uma oitava entre uma nota e a próxima. O ouvido percebe essa diferença como 'aperto' ou 'largura' — e o braço mostra essa diferença como notas mais juntas ou mais distantes."),
        tbl ({ "Notas (fechada)", "Distância", "Notas (aberta)", "Distância" }, {
            { "Dó → Mi", "terça maior (4 semitons)", "Dó → Sol", "quinta justa (7 semitons)" },
            { "Mi → Sol", "terça menor (3 semitons)", "Sol → Mi", "sexta maior (9 semitons)" },
        }),
        c (
            "Regra de ouro: as notas do acorde não mudam com a disposição; só o espaçamento e a ordem mudam."),

        h ("Disposição e condução de vozes"),
        p (
            "A disposição aberta é muito usada na condução de vozes: quando você acompanha uma progressão, escolher disposições abertas ajuda a manter cada voz (a linha aguda, a linha do meio) em movimento suave, sem saltos. Um arranjo bem escrito costuma alternar disposições fechadas e abertas conforme o registro de cada acorde, mantendo as notas comuns no lugar."),
        b ("Procure manter as notas comuns entre um acorde e o seguinte."),
        b ("Use disposições abertas quando o registro é mais grave."),
        b ("Use disposições fechadas quando precisa de clareza e ataque."),

        h ("As três vozes do acorde"),
        p (
            "Quando você pensa em disposição, é útil imaginar o acorde como três vozes: a voz grave, a voz do meio e a voz aguda. Na disposição fechada, as três vozes ficam próximas; na aberta, elas se separam. Ao acompanhar uma progressão, você pode manter cada voz se movendo suavemente, uma por vez, em vez de mover o acorde inteiro de uma vez. Isso é a base do voice leading, ou condução de vozes."),
        b ("Voz grave: geralmente a tônica ou a nota do baixo."),
        b ("Voz do meio: a terça ou a quinta."),
        b ("Voz aguda: a nota que 'canta' no acorde."),
        p (
            "Um exercício excelente é tocar a progressão mantendo a voz aguda parada enquanto as outras se movem. Você vai ouvir a música 'se sustentar' em uma nota comum. Depois, mova a voz aguda um passo e mantenha as outras. Esse tipo de controle é o que separa o acompanhamento mecânico do acompanhamento musical."),

        h ("Disposição e registro"),
        p (
            "A disposição também depende do registro em que você toca. Um acorde em região grave precisa de espaçamento maior para não embolar; um acorde agudo pode ser fechado sem problema. Essa é uma regra prática de arranjo: quanto mais grave, mais aberto. Se você tocar um acorde fechado muito grave, as notas se misturam e o som fica confuso."),
        b ("Região grave: prefira disposição aberta."),
        b ("Região aguda: a disposição fechada funciona bem."),
        b ("Evite notas graves muito próximas: elas embolam o som."),

        h ("Disposição e a mão direita"),
        p (
            "A disposição não depende só da mão esquerda: a mão direita define quais cordas soam. Você pode montar uma disposição aberta na mão esquerda e escolher tocar apenas algumas cordas com a direita, criando um som ainda mais controlado. Essa combinação — disposição da mão esquerda e seleção da mão direita — é o que dá ao guitarrista o controle total do acorde."),
        b ("Mão esquerda: monta as notas."),
        b ("Mão direita: escolhe quais cordas soam."),
        b ("Juntas, definem a disposição final que o ouvido percebe."),

        h ("Disposição e o número de cordas"),
        p (
            "Na guitarra, a disposição depende de quantas cordas você toca e em quais casas. Uma tríade pode ser tocada em três cordas adjacentes (som fechado) ou espalhada por cordas não adjacentes (som aberto). O mesmo acorde, tocado em três regiões diferentes do braço, produz três cores diferentes — todas corretas. Saber explorar essas regiões é o que dá vocabulário ao acompanhamento."),
        b ("Três cordas adjacentes: som fechado."),
        b ("Cordas não adjacentes: som aberto."),
        b ("Três regiões diferentes do braço: três cores do mesmo acorde."),

        h ("Quando usar cada disposição"),
        p (
            "Não existe regra fixa, mas há orientações úteis. A disposição fechada é ideal para o acompanhamento rítmico, onde você precisa de ataque e clareza. A disposição aberta é ideal para partes mais lentas, introduções e arranjos, onde você quer um som amplo e sustentado. Em uma mesma música, você pode alternar as duas para criar contraste entre as seções."),
        b ("Fechada: acompanhamento rítmico, ataque, clareza."),
        b ("Aberta: introduções, arranjos, som sustentado."),
        b ("Alternar as duas cria contraste entre seções."),

        h ("Disposição aberta com cordas soltas"),
        p (
            "Uma das belezas da guitarra é poder usar cordas soltas na disposição aberta. Isso dá um som cristalino, com muito corpo, típico do violão. Em Dó maior, você pode tocar Dó na 5ª corda, Sol na 1ª corda solta e Mi na 4ª — a corda solta acrescenta brilho e ressonância. Esse recurso é explorado em arranjos de MPB, de bossa nova e de música instrumental."),
        b ("Cordas soltas acrescentam brilho e ressonância."),
        b ("Som típico do violão e da música instrumental."),
        b ("Explore as cordas soltas dentro do acorde."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é achar que uma disposição é 'mais certa' que a outra. Não é: são recursos diferentes. Outro erro é abafar notas sem perceber ao tentar uma disposição aberta — como as notas estão mais distantes, é fácil encostar em uma corda que não deveria soar. E há o erro de mudar de disposição sem motivo, quebrando a continuidade do acompanhamento."),
        b ("Não existe disposição 'mais certa': existem propósitos diferentes."),
        b ("Na disposição aberta, cuide para não abafar notas."),
        b ("Mude de disposição com intenção, não por acaso."),

        h ("Do acorde isolado para a música"),
        p (
            "Tocar um acorde bonito isolado é fácil; o desafio é fazer vários acordes soarem bem em sequência. É aí que a disposição mostra seu valor. Se todos os acordes de uma progressão estiverem em disposição fechada, a música soa 'quadrada'; se todos estiverem abertos, ela pode soar vaga. O equilíbrio entre as duas, escolhido a cada mudança de acorde, é o que faz o acompanhamento respirar."),
        b ("Pense na progressão inteira, não em cada acorde isolado."),
        b ("Alterne disposições para criar movimento e contraste."),
        b ("Mantenha as notas comuns para dar continuidade."),
        p (
            "Um bom treino é pegar uma progressão de quatro acordes e tocá-la de quatro maneiras: toda fechada, toda aberta, alternando, e com a voz aguda sempre na mesma nota quando possível. Cada versão soa diferente, e todas são corretas. Você está construindo repertório de decisões musicais — e isso é o que diferencia um acompanhador experiente."),

        h ("Aplicação musical"),
        p (
            "Experimente tocar a progressão Dó – Lá menor – Ré menor – Sol duas vezes: primeiro em disposição fechada, depois em disposição aberta. Repare como a mesma música muda de caráter. Depois misture: algumas partes fechadas, outras abertas. Esse é o tipo de decisão que faz um acompanhamento soar profissional. E o app reconhece as notas em qualquer disposição, porque o que importa é o conjunto de notas, não a ordem."),
        b ("Toque a progressão fechada, depois aberta, depois mista."),
        b ("Escolha pela música, não pela forma mais fácil."),
        b ("O app confere as notas, não a disposição."),
        part ("m4_partitura_progressao", { "C4", "A4", "D4", "G4" },
              "Partitura das fundamentais da progressão Dó – Lá menor – Ré menor – Sol."),

        h ("Resumo do tópico"),
        b ("Disposição é a ordem e o espaçamento das notas do acorde."),
        b ("Fechada: notas próximas, som compacto — ideal para acompanhar."),
        b ("Aberta: notas espalhadas, som amplo — ideal para arranjo."),
        b ("As notas do acorde não mudam; só a distribuição muda."),
        b ("Cordas soltas deixam a disposição aberta ainda mais bonita."),
        c (
            "Nos exercícios deste tópico, toque as tríades pedidas em disposição fechada e aberta. O app reconhece as notas e confere a qualidade do acorde, aceitando qualquer disposição."),
    };
}

} // namespace cursomusica::content
