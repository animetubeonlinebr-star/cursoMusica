#include "Course/Content/Topics.h"

// Topic 11E — Cinco desenhos da pentatônica (Módulo 11, Etapa 11).
namespace cursomusica::content
{

std::vector<ContentItem> topic11E()
{
    return {

        p (
            "A pentatônica menor cabe em cinco desenhos que cobrem o braço inteiro, um encaixado no outro. Cada desenho é uma região; juntos, eles formam um mapa completo do braço. Este tópico é o que liga a ideia de região (o primeiro tópico do módulo) à pentatônica que você já toca: as cinco posições são as cinco regiões da pentatônica."),
        p (
            "Conhecer as cinco posições é o que libera o braço. Quem só toca a posição 1 fica preso no mesmo lugar; quem conhece as cinco percorre o braço inteiro sem se perder. E as posições se conectam por notas comuns, de modo que você pode deslizar de uma para outra no meio de uma frase — que é exatamente o que os grandes solos fazem."),
        c (
            "As cinco posições da pentatônica menor cobrem o braço em sequência. Cada uma compartilha notas com as vizinhas, e é por essas notas comuns que a frase viaja de uma posição para a outra."),

        h ("As cinco posições"),
        p (
            "A pentatônica menor tem cinco notas por oitava, e cada posição começa numa dessas notas. Por isso há exatamente cinco desenhos: um para cada ponto de partida. Eles se encaixam como telhas no telhado — onde uma termina, a outra começa, sempre com notas em comum nas cordas de fronteira."),
        p (
            "A posição 1 é a que quase todo mundo aprende primeiro, com a tônica na 6ª corda. As posições 2 a 5 vão subindo o braço, e a posição 5 na casa 12 é a posição 1 uma oitava acima. Aprender as cinco em sequência é aprender o braço como um todo, não como cinco lugares isolados."),
        b ("São cinco posições porque a pentatônica tem cinco notas por oitava."),
        b ("Cada posição começa numa nota diferente da escala."),
        b ("Posições vizinhas compartilham notas nas cordas de fronteira."),
        b ("A posição 5 (casa 12) repete a posição 1 uma oitava acima."),
        img ("m11_pent_cinco_desenhos", "Os cinco desenhos da pentatônica menor, encaixados pelo braço. Cada desenho é uma região; juntos cobrem o braço inteiro."),

        h ("Ligar uma posição na outra"),
        p (
            "A passagem de uma posição para a seguinte usa a nota comum. Você toca um trecho da posição 1, desliza pela nota compartilhada e continua na posição 2, sem quebrar a frase. É esse deslize que dá a sensação de um solo que percorre o braço em vez de ficar parado."),
        p (
            "O treino clássico é subir e descer a pentatônica ligando as cinco posições numa única linha. Comece na posição 1, suba até a posição 5 e volte. Feito devagar e no metrônomo, esse exercício constrói de uma vez a memória das cinco posições e a ligação entre elas."),
        tbl ({ "Posição", "Tônica em", "Liga com" }, {
            { "1", "6ª corda (casa 5)", "posição 2" },
            { "2", "6ª corda (casa 8)", "posições 1 e 3" },
            { "3", "5ª corda (casa 10)", "posições 2 e 4" },
            { "4", "5ª corda (casa 12)", "posições 3 e 5" },
            { "5", "4ª/6ª corda (casa 12/17)", "posição 4 (e a 1 uma oitava acima)" },
        }),
        c (
            "Erro comum: aprender as cinco posições como cinco coisas separadas e nunca ligá-las. A pentatônica é uma só; as posições são recortes. Estude-as sempre em sequência, ligando uma na outra."),

        h ("O lick deste tópico"),
        p (
            "O lick abaixo sobe a pentatônica menor de Lá ligando a posição 1 à posição 2 pela nota comum, num gesto de Edu Ardanuy — pentatônica brasileira com licks de rock. Ouça como a frase não para na fronteira: ela atravessa a nota comum e continua, provando que as posições são um só braço."),
        aud ({ "A4", "C5", "D5", "E5", "G5", "A5", "G5", "E5", "D5", "C5", "A4" },
             "Lick do tópico E: pentatônica menor de Lá ligando duas posições pela nota comum. A frase atravessa a fronteira sem parar."),
        part ("m11_partitura_e", { "A4", "C5", "D5", "E5", "G5", "A5", "G5", "E5", "D5", "C5", "A4" },
              "Partitura do lick E: pentatônica menor ligando duas posições. A nota comum é a ponte entre os desenhos."),

        h ("Estudar as cinco posições"),
        p (
            "Aprenda uma posição por dia e sempre ligue a nova à anterior. Ao fim da semana, toque a pentatônica de ponta a ponta do braço, subindo e descendo pelas cinco posições. Quando você conseguir improvisar passando de posição sem pensar na fronteira, as cinco posições viraram um só braço."),

        h ("A posição 1 e a sua origem"),
        p (
            "A posição 1 da pentatônica menor é a mais conhecida porque é a mais fácil de visualizar: a tônica está na 6ª corda, e o desenho se organiza em torno dela. Muitos guitarristas passam anos só nessa posição. Ela é o ponto de partida, mas não pode ser o ponto de chegada: quem só toca a posição 1 improvisa sempre no mesmo lugar, e a frase fica previsível."),
        p (
            "A posição 1 serve de âncora para as outras quatro. Aprender a posição 2 é aprender a mesma escala uma tônica acima; a posição 3, duas; e assim por diante. Como a pentatônica tem cinco notas, depois da quinta posição você volta à primeira, uma oitava acima. O braço inteiro é, portanto, cinco desenhos que se repetem."),
        b ("A posição 1 tem a tônica na 6ª corda e é a mais conhecida."),
        b ("As posições 2 a 5 são as mesmas notas começando em outros pontos."),
        b ("Depois da posição 5, o desenho volta à posição 1 uma oitava acima."),
        tbl ({ "Posição", "Começa em", "Oitava" }, {
            { "1", "tônica (6ª corda)", "mais grave" },
            { "2", "b3", "—" },
            { "3", "4", "—" },
            { "4", "5", "—" },
            { "5", "b7", "a 5ª volta à 1 uma oitava acima" },
        }),

        h ("O exercício de ligação"),
        p (
            "O exercício clássico para integrar as cinco posições é subir a pentatônica ligando uma posição na outra, sem parar. Você começa na posição 1, sobe até a nota comum com a posição 2, continua pela posição 2, e assim por diante até a posição 5. Depois faz o caminho de volta, descendo. O objetivo não é velocidade: é memória de onde cada posição começa e termina."),
        p (
            "Feito devagar e no metrônomo, esse exercício constrói, de uma vez, o mapa do braço. Cada nota comum é uma dobradiça; cada posição é uma sala. Quando o exercício sai fluido, você tem o braço inteiro debaixo dos dedos — e pode improvisar atravessando as posições em vez de ficar preso numa caixa."),
        c (
            "Erro comum: aprender as posições fora de ordem e nunca praticar as emendas. A pentatônica é uma só; pratique sempre subindo e descendo o braço, ligando as posições, para que o cérebro entenda que elas são um contínuo."),

        h ("Improvisando com as cinco posições"),
        p (
            "Com as cinco posições integradas, a improvisação muda de escala. Você deixa de tocar sempre no mesmo lugar e passa a construir frases que viajam pelo braço: uma ideia na posição 1, a mesma ideia uma oitava acima na posição 3, e uma resolução na posição 5. A frase ganha dimensão vertical (as notas) e horizontal (o braço)."),
        p (
            "Um bom exercício é pegar uma frase curta de quatro notas e tocá-la nas cinco posições, subindo o braço. A frase é sempre a mesma; o que muda é a região. Depois, junte duas posições na mesma frase, ligando pela nota comum. É assim que a pentatônica deixa de ser cinco coisas e passa a ser uma."),


        h ("A pentatônica como um só sistema"),
        p (
            "O objetivo final das cinco posições é deixar de vê-las como cinco coisas e passar a vê-las como uma só. A pentatônica é um único conjunto de notas espalhado pelo braço; as posições são apenas recortes desse conjunto. Quando você pensa assim, a improvisação muda: você deixa de escolher \"em qual posição vou tocar\" e passa a pensar \"que nota quero agora\" — e a mão encontra essa nota na posição certa, sozinha."),
        p (
            "Para chegar a esse ponto, o exercício é tocar a pentatônica em frases que atravessam o braço, subindo e descendo pelas posições, sem parar em nenhuma. Você começa na posição 1, atravessa a 2, a 3, a 4 e a 5, e volta. Quando a travessia sai fluida, o braço inteiro virou uma região só — e a sua mão pode tocar qualquer frase em qualquer lugar."),
        p (
            "É esse domínio horizontal que separa o guitarrista que \"sabe a pentatônica\" do guitarrista que \"toca a pentatônica\". O primeiro tem cinco caixas decoradas; o segundo tem um mapa contínuo. O mapa é o que permite improvisar sobre harmonias que mudam, seguir o acorde pelo braço e construir frases com começo, meio e fim, sem ficar preso numa posição."),
        b ("As cinco posições são recortes de um único conjunto de notas."),
        b ("Pense na nota que quer, não na posição onde vai tocar."),
        b ("Frases que atravessam o braço transformam as cinco caixas num mapa só."),
        tbl ({ "Nível", "O que você vê", "Como improvisa" }, {
            { "Iniciante", "cinco caixas separadas", "preso numa posição" },
            { "Intermediário", "caixas ligadas por notas comuns", "atravessa duas ou três" },
            { "Avançado", "um mapa contínuo", "escolhe a nota, não a caixa" },
        }),


        h ("Ensinando a mão a viajar"),
        p (
            "A mão não gosta de viajar: ela prefere ficar parada na posição onde já está. Por isso, atravessar as cinco posições exige treino deliberado. O exercício é simples, mas cansativo: suba a pentatônica de ponta a ponta do braço, ligando as posições, e depois desça. Faça devagar, ouvindo cada nota comum. O cansaço é sinal de que a mão está aprendendo um caminho novo."),
        p (
            "Há um detalhe de digitação que ajuda muito: nas emendas entre posições, escolha a nota comum de modo que a mão possa deslizar em vez de pular. Deslizar mantém o contato com a corda e o som contínuo; pular cria um silêncio que quebra a frase. Aprender a deslizar nas emendas é o que faz a travessia soar como uma linha só, e não como cinco trechos colados."),
        p (
            "Depois de a travessia ficar fluida, comece a improvisar atravessando o braço. Toque uma ideia na posição grave, repita-a uma oitava acima na posição aguda, e resolva no meio. Esse tipo de frase dá ao solo uma dimensão que a posição única não tem. É a recompensa por ter ensinado a mão a viajar: a improvisação deixa de ter fronteiras no braço."),
        b ("A mão prefere ficar parada: atravessar as posições exige treino deliberado."),
        b ("Nas emendas, deslize pela nota comum em vez de pular."),
        b ("Improvisar atravessando o braço dá ao solo uma dimensão nova."),
        tbl ({ "Emenda", "Como ligar", "Resultado" }, {
            { "1 para 2", "nota comum", "frase contínua" },
            { "2 para 3", "nota comum", "frase contínua" },
            { "3 para 4", "nota comum", "frase contínua" },
            { "4 para 5", "nota comum", "frase contínua" },
        }),

        c (
            "Meta do módulo: 100 BPM. A prova de que as cinco posições estão integradas é subir e descer o braço inteiro ligando as posições no tempo, sem parar nas emendas."),
    };
}

} // namespace cursomusica::content
