#include "Course/Content/Topics.h"

// Topic 11F — Trilhas abertas e fechadas (Módulo 11, Etapa 11).
// "Trilha" = o caminho por onde a escala anda no braço. Trilha FECHADA = o
// caminho confinado a uma posição (a mão não sai da caixa, sem cordas soltas).
// Trilha ABERTA = o caminho linear, ao longo de uma ou duas cordas, com a mão
// viajando pelo braço. As duas se completam.
namespace cursomusica::content
{

std::vector<ContentItem> topic11F()
{
    return {

        p (
            "Você já pensa em regiões e conhece as cinco posições da pentatônica. Falta a segunda dimensão do braço: as trilhas. Uma trilha é o caminho por onde a escala anda. Há duas famílias de trilhas — as fechadas e as abertas — e aprender as duas é o que faz a sua mão enxergar o braço tanto na horizontal quanto na vertical."),
        p (
            "A trilha fechada é a que você já estuda: a escala confinada a uma posição, a mão parada na caixa, sem cordas soltas. A trilha aberta é o oposto: a escala percorrida ao longo de uma ou duas cordas, com a mão viajando pelo braço e, muitas vezes, usando cordas soltas. Uma pensa em caixas; a outra pensa em linhas."),
        c (
            "Trilha fechada = escala dentro da posição (mão parada, sem soltas). Trilha aberta = escala ao longo das cordas (mão viajando, com soltas). O fraseado completo usa as duas."),

        h ("Trilha fechada: o caminho dentro da caixa"),
        p (
            "Na trilha fechada, você toca a escala inteira sem sair da posição. Os quatro dedos cobrem quatro casas, e a mão não se move. É o desenho por região que você estudou no começo do módulo. A vantagem é o controle: tudo está debaixo dos dedos, e a frase fica estável."),
        p (
            "A limitação da trilha fechada é justamente o confinamento. Uma frase presa numa só posição soa igual do começo ao fim. Para dar relevo, você liga uma trilha fechada na vizinha — mas isso é o tópico das cinco posições. Aqui, a trilha fechada é o ponto de partida, a base sobre a qual a trilha aberta vai se apoiar."),
        b ("Trilha fechada: mão parada, quatro casas, sem cordas soltas."),
        b ("Vantagem: controle e estabilidade da frase."),
        b ("É a base — a trilha aberta se apoia nela."),

        h ("Trilha aberta: o caminho ao longo da corda"),
        p (
            "Na trilha aberta, você toca a escala ao longo de uma ou duas cordas, subindo ou descendo o braço. A mão viaja: o mesmo dedo desliza de casa em casa seguindo a escala. É a maneira mais linear de pensar o braço — em vez de caixas, você vê uma corda comprida com as notas marcadas nela."),
        p (
            "A trilha aberta é ótima para frases rápidas e para o legato, porque cada nota está a poucas casas da anterior, na mesma corda. Também é onde entram as cordas soltas: uma corda solta é o ponto mais estável da trilha, e usá-la como nota de repouso dá um som aberto e ressonante, muito presente no violão e na guitarra brasileira."),
        b ("Trilha aberta: a escala ao longo de uma ou duas cordas."),
        b ("A mão viaja pelo braço seguindo a escala na corda."),
        b ("Cordas soltas entram como notas de repouso, com som aberto."),
        img ("m11_trilhas", "Trilhas abertas e fechadas: a fechada é a caixa (mão parada); a aberta é a linha ao longo da corda (mão viajando)."),

        h ("Combinar as duas trilhas"),
        p (
            "O fraseado maduro alterna as duas. Você começa numa trilha fechada, onde tem controle; ao chegar numa nota comum, desliza para uma trilha aberta e sobe a corda; no topo, volta para a trilha fechada e resolve. É esse vaivém entre caixa e linha que dá ao solo a sensação de espaço e movimento."),
        p (
            "Um bom exercício é tocar a mesma escala de duas maneiras: primeiro toda em trilha fechada, depois toda em trilha aberta na 3ª corda. Sentir a diferença entre as duas mãos (a parada e a viajante) ensina o braço de verdade, porque agora você tem duas coordenadas: a posição e a corda."),
        tbl ({ "Trilha", "A mão", "Pensa em", "Uso" }, {
            { "Fechada", "parada na caixa", "posições", "controle, frases estáveis" },
            { "Aberta", "viajando pela corda", "linhas", "legato, frases rápidas, cordas soltas" },
            { "Combinada", "alternando", "posição + corda", "frases com relevo e movimento" },
        }),
        c (
            "Dica: quando a frase travar numa posição, tente tocar a mesma ideia em trilha aberta numa só corda. Muitas vezes a linha aparece justamente quando você deixa a caixa e pensa em corda."),

        h ("O lick deste tópico"),
        p (
            "O lick abaixo é uma trilha aberta na 3ª corda (Sol): a escala de Lá menor sobe linearmente pela corda, do Sol grave ao Lá agudo, num gesto de Joe Satriani — linhas modais cantáveis e legato. Ouça como a frase flui numa só direção, sem caixas, e como a corda solta (Sol) serve de ponto de apoio."),
        aud ({ "G3", "A3", "B3", "C4", "D4", "E4", "F4", "G4", "A4" },
             "Lick do tópico F: trilha aberta na 3ª corda. A escala sobe linearmente pela corda, com a corda solta como apoio."),
        part ("m11_partitura_f", { "G3", "A3", "B3", "C4", "D4", "E4", "F4", "G4", "A4" },
              "Partitura do lick F: trilha aberta na 3ª corda. A mão viaja pelo braço seguindo a escala na mesma corda."),

        h ("Estudar as trilhas"),
        p (
            "Estude a mesma escala nas duas trilhas, todos os dias. Depois de dominar as duas, improvise alternando: comece fechado, abra para a trilha da corda e volte. Quando você não precisar mais pensar qual trilha está usando, o braço virou um mapa de duas coordenadas — posição e corda — e a sua frase ganhou o espaço de que precisava."),

        h ("As cordas soltas na trilha aberta"),
        p (
            "As cordas soltas são o ponto mais estável de uma trilha aberta. Uma corda solta ressoa com o corpo inteiro do instrumento e soa cheia, sem o esforço da mão esquerda. Por isso, na trilha aberta, a corda solta costuma ser usada como nota de repouso: você conduz a frase até ela e deixa o som respirar. É um recurso muito presente no violão e na guitarra brasileira."),
        p (
            "Há dois cuidados com as cordas soltas. O primeiro é o som: a corda solta soa diferente das cordas pisadas, e usá-la no meio de uma frase pisada pode criar um contraste indesejado se não for intencional. O segundo é a afinação: como a corda solta é a referência, qualquer desvio nela é ouvido na hora. Afine antes de estudar e confira a corda solta de vez em quando."),
        b ("A corda solta é o ponto de repouso natural da trilha aberta."),
        b ("Ela soa mais cheia, mas com timbre diferente das notas pisadas."),
        b ("Como é a referência de afinação, mantenha-a sempre afinada."),
        tbl ({ "Trilha", "Vantagem", "Cuidado" }, {
            { "Fechada", "controle e estabilidade", "frase presa numa só região" },
            { "Aberta", "movimento e legato", "mão viaja: exige precisão" },
            { "Aberta com solta", "som cheio e ressonante", "timbre e afinação da solta" },
        }),

        h ("Quando usar cada trilha"),
        p (
            "A escolha entre trilha fechada e aberta depende do que a frase precisa. Frases que exigem controle, notas próximas e mudanças de corda ficam melhores na trilha fechada. Frases rápidas, de legato, ou que precisam de cordas soltas ficam melhores na trilha aberta. E frases longas, que atravessam o braço, quase sempre alternam as duas."),
        p (
            "Aprender a escolher a trilha é parte de compor a frase. Antes de tocar, pergunte: a ideia pede estabilidade ou movimento? Se pede estabilidade, fique na caixa; se pede movimento, abra para a corda. Com o tempo, a escolha vira instinto, e a mão vai para a trilha certa sem que você pense."),
        c (
            "Exercício: toque a mesma escala de duas maneiras — primeiro toda em trilha fechada, depois toda em trilha aberta na 3ª corda. Sinta a diferença entre a mão parada e a mão viajante. As duas trilhas são ferramentas; o fraseado maduro usa as duas."),

        h ("A trilha como caminho melódico"),
        p (
            "Pensar em trilhas muda a forma como você enxerga o braço. Em vez de um bloco de notas, você vê caminhos: linhas que sobem e descem ao longo das cordas. Uma trilha é, no fundo, uma melodia em potencial — um caminho por onde a frase pode andar. Quem pensa em trilhas compõe com direção; quem pensa em posições compõe com pontos."),
        p (
            "É por isso que este tópico vem depois das cinco posições da pentatônica. As posições ensinam o braço na vertical (caixas); as trilhas ensinam o braço na horizontal (linhas). Com as duas coordenadas, você tem o mapa completo e pode escolher, para cada frase, o caminho que faz mais sentido."),


        h ("Velocidade, precisão e a escolha da trilha"),
        p (
            "Em passagens rápidas, a escolha da trilha decide se a frase sai limpa ou embaralhada. Na trilha fechada, a mão parada permite mudanças de corda rápidas e precisas, mas cada corda nova exige um ajuste. Na trilha aberta, o legato ao longo da corda é fluido, mas a mão precisa viajar com exatidão. O guitarrista experiente escolhe a trilha que torna a passagem mais fácil, e não a que parece mais bonita."),
        p (
            "Um erro comum é tocar rápido demais na trilha errada. Uma sequência que sobe uma corda só é natural na trilha aberta; tentar fazê-la na trilha fechada força mudanças de corda desnecessárias. O contrário também vale: uma passagem que muda de corda a cada nota é natural na trilha fechada. Reconhecer isso é metade do caminho para a execução limpa."),
        p (
            "Treine a mesma frase nas duas trilhas e compare. Em geral, uma delas vai parecer \"certa\" e a outra \"forçada\". Anote qual é a natural para cada tipo de frase; com o tempo, você desenvolve um instinto para escolher a trilha antes de tocar. É esse instinto que faz a velocidade parecer fácil — porque, na trilha certa, ela é."),
        b ("Escolha a trilha que torna a passagem mais fácil, não a mais bonita."),
        b ("Passagens de uma corda só pedem trilha aberta; mudanças frequentes, trilha fechada."),
        b ("Treine a mesma frase nas duas trilhas e anote qual é a natural."),
        tbl ({ "Tipo de frase", "Trilha natural", "Por quê" }, {
            { "Sequência numa corda só", "aberta", "legato fluido, sem mudanças" },
            { "Arpejo que muda de corda", "fechada", "mão parada, mudanças precisas" },
            { "Frase longa pelo braço", "combinada", "alterna controle e movimento" },
        }),


        h ("Fraseado com relevo"),
        p (
            "Alternar trilha fechada e trilha aberta dá à frase um relevo: a mesma melodia soa diferente conforme a trilha. Na trilha fechada, o som é mais uniforme e controlado; na trilha aberta, mais aberto e cantável. Um bom fraseado usa esse contraste como um pintor usa tons diferentes: para dar profundidade e variedade à mesma ideia musical."),
        p (
            "Um exercício útil é tocar uma melodia conhecida nas duas trilhas. Você percebe que a versão fechada é mais fácil de controlar e a aberta mais fácil de cantar. Nenhuma é melhor; são recursos. O guitarrista experiente escolhe a trilha conforme o efeito que quer: controle para passagens técnicas, cantabilidade para melodias, movimento para frases longas."),
        p (
            "Com o tempo, você passa a escolher a trilha no instante em que imagina a frase. É uma decisão que acontece antes de tocar, e é o que dá à execução uma sensação de facilidade: a mão já sabe por onde vai, porque a trilha foi escolhida a favor da música. É esse planejamento silencioso que separa o fraseado amador do fraseado profissional."),
        b ("Alternar as trilhas dá relevo e profundidade à mesma melodia."),
        b ("Escolha a trilha conforme o efeito: controle, cantabilidade ou movimento."),
        b ("Decida a trilha antes de tocar, a favor da frase."),
        tbl ({ "Efeito desejado", "Trilha", "Exemplo" }, {
            { "Controle", "fechada", "passagem técnica rápida" },
            { "Cantabilidade", "aberta", "melodia longa" },
            { "Movimento", "combinada", "frase que atravessa o braço" },
        }),

        c (
            "Meta do módulo: 100 BPM. Toque a trilha aberta no metrônomo até a mão viajar pela corda sem hesitar na mudança de casa."),
    };
}

} // namespace cursomusica::content
