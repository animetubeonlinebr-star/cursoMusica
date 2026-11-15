#include "Course/Content/Topics.h"

// Topic 5A — Escala maior (Módulo 5, Etapa 5).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 5, bloco A).
namespace cursomusica::content
{

std::vector<ContentItem> topic5A()
{
    return {

        p (
            "A escala maior é a régua de onde nasce toda a harmonia deste módulo. Antes de falar de acordes e de funções, você precisa ter na cabeça o desenho da escala maior: sete notas que sobem da tônica até a oitava seguindo sempre o mesmo padrão de tons e semitons. É desse padrão fixo que saem os acordes do campo harmônico, as funções de tônica, subdominante e dominante e, mais adiante, as cadências e os modos."),
        p (
            "A boa notícia é que você já conhece a escala maior sem saber o nome dela. Toda melodia que soa 'alegre', 'clara' ou 'resolvida' provavelmente vive dentro de uma escala maior. O que faremos aqui é organizar esse som em graus numerados, para que você possa construir a mesma escala em qualquer tonalidade e, a partir dela, montar os acordes certos."),
        c (
            "Objetivo do módulo: entender como os acordes se relacionam dentro de uma tonalidade. A escala maior é o mapa que dá sentido a essas relações — sem ela, os acordes são apenas formas soltas no braço."),

        h ("O que é a escala maior"),
        p (
            "Escala é uma sequência ordenada de notas dentro de uma oitava. A escala maior é a mais comum da música ocidental e tem um desenho muito específico: partindo da tônica (o primeiro grau), ela sobe em sete passos até repetir a tônica uma oitava acima. O que faz a escala ser maior não são as notas em si, mas a distância entre elas."),
        p (
            "Essa distância é medida em tons (T) e semitons (S). A escala maior é o único padrão que combina dois tons, um semitom, três tons e um semitom final, sempre nesta ordem: T – T – S – T – T – T – S. Os semitons caem sempre entre o terceiro e o quarto grau e entre o sétimo e a oitava. Guarde essa posição: é ela que dá à escala maior o seu som característico."),
        b ("Escala maior = T – T – S – T – T – T – S."),
        b ("Semitons entre os graus 3–4 e 7–8; tons em todos os outros pares."),
        b ("A oitava é a tônica de novo, uma oitava acima."),
        img ("m5_escala_maior_graus", "A escala maior: sete graus, o padrão de tons e semitons e a oitava que fecha o ciclo."),

        h ("A escala de Dó maior"),
        p (
            "A escala de Dó maior é a referência porque usa apenas as sete notas naturais, sem nenhum acidente. Partindo de Dó, o padrão T – T – S – T – T – T – S cai exatamente sobre Dó, Ré, Mi, Fá, Sol, Lá, Si e volta ao Dó. Repare onde estão os semitons: entre Mi e Fá (graus 3 e 4) e entre Si e Dó (graus 7 e 8). Todo o resto são tons."),
        p (
            "Numerar os graus é o passo que transforma a escala em ferramenta. Em vez de decorar notas, você passa a pensar em graus: o 1 é a tônica, o 5 é a quinta, o 7 é a sétima. Isso permite transpor qualquer ideia para qualquer tom sem recomeçar do zero — basta manter o padrão e mudar a nota de partida."),
        tbl ({ "Grau", "Nota (Dó maior)", "Distância do grau anterior", "Semitons da tônica" }, {
            { "1 (I)", "Dó", "—", "0" },
            { "2 (II)", "Ré", "tom", "2" },
            { "3 (III)", "Mi", "tom", "4" },
            { "4 (IV)", "Fá", "semitom", "5" },
            { "5 (V)", "Sol", "tom", "7" },
            { "6 (VI)", "Lá", "tom", "9" },
            { "7 (VII)", "Si", "tom", "11" },
            { "8 (I)", "Dó", "semitom", "12" },
        }),
        aud ({ "C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5" },
             "Escala de Dó maior subindo: repare nos semitons entre Mi–Fá e Si–Dó."),
        part ("m5_partitura_escala", { "C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5" },
              "Partitura da escala de Dó maior. Ouça o que está escrito: o mesmo desenho que você toca no braço."),

        h ("Construindo a escala em outras tonalidades"),
        p (
            "Para construir a escala maior em qualquer tonalidade, siga sempre o mesmo procedimento: escolha a tônica, aplique o padrão T – T – S – T – T – T – S e use sustenidos ou bemóis quando o padrão exigir uma nota que não existe naturalmente. É assim que surgem as escalas de Sol (com Fá#), de Ré (com Fá# e Dó#) e por aí adiante."),
        p (
            "O processo é sempre o mesmo, mas o resultado muda de nome conforme as notas que aparecem. Uma escala que só precisa de sustenidos pertence a uma tonalidade com sustenidos; uma que só precisa de bemóis, a uma tonalidade com bemóis. No tópico G deste módulo você verá que essas escolhas formam o ciclo das quintas — mas o motor é sempre este padrão de tons e semitons."),
        b ("Sol maior: Sol Lá Si Dó Ré Mi Fá# (aparece o Fá#)."),
        b ("Fá maior: Fá Sol Lá Sib Dó Ré Mi (aparece o Sib)."),
        b ("A tônica muda; o padrão de tons e semitons nunca muda."),
        tbl ({ "Tonalidade", "Notas", "Acidentes" }, {
            { "Dó maior", "Dó Ré Mi Fá Sol Lá Si", "nenhum" },
            { "Sol maior", "Sol Lá Si Dó Ré Mi Fá#", "1 sustenido" },
            { "Fá maior", "Fá Sol Lá Sib Dó Ré Mi", "1 bemol" },
            { "Ré maior", "Ré Mi Fá# Sol Lá Si Dó#", "2 sustenidos" },
            { "Sib maior", "Sib Dó Ré Mib Fá Sol Lá", "2 bemóis" },
        }),

        h ("Graus da escala: a numeração que organiza tudo"),
        p (
            "Cada nota da escala recebe um número de grau, escrito em algarismo romano. O primeiro grau (I) é a tônica e dá nome à tonalidade. Os graus não são apenas uma contagem: eles carregam funções e é sobre eles que os acordes do campo harmônico serão construídos. Um acorde sobre o grau I tem um papel; um acorde sobre o grau V tem outro completamente diferente."),
        p (
            "A convenção de maiúsculas e minúsculas é importante e aparece em toda a análise harmônica. Algarismo romano maiúsculo indica acorde maior; minúsculo, acorde menor; e o pequeno círculo (°) indica acorde diminuto. Assim, quando você lê I – ii – iii – IV – V – vi – vii°, já sabe de antemão a qualidade de cada acorde sem precisar tocar."),
        b ("Maiúsculo (I, IV, V): acorde maior."),
        b ("Minúsculo (ii, iii, vi): acorde menor."),
        b ("Com círculo (vii°): acorde diminuto."),
        img ("m5_graus_romanos", "Os graus em algarismo romano: maiúsculo é maior, minúsculo é menor e o círculo marca o diminuto."),

        h ("Escala maior no braço da guitarra"),
        p (
            "No braço, a escala maior é uma sequência de posições que segue a régua de semitons que você aprendeu nos módulos anteriores. Cada corda é uma linha da escala e cada casa é um semitom. Uma vez que você localiza a tônica, o padrão de tons e semitons vira um desenho de dedos que pode ser deslocado para qualquer região — exatamente como as formas do CAGED."),
        p (
            "A vantagem de aprender a escala maior no braço é que ela conecta a teoria à execução. Saber que o grau 3 é Mi em Dó maior é uma coisa; saber onde o grau 3 está em cada região do braço, para poder tocar sobre o acorde de tônica, é o que permite usar a escala na prática. Por isso os exercícios deste tópico incluem tocar a escala no instrumento e deixar o app conferir as notas."),
        b ("Localize a tônica na 6ª corda e suba aplicando o padrão T–T–S–T–T–T–S."),
        b ("Use as casas 3, 5, 7 e 12 como referência de posição."),
        b ("A mesma digitação se desloca para qualquer tonalidade."),
        aud ({ "G3", "A3", "B3", "C4", "D4", "E4", "F#4", "G4" },
             "Escala de Sol maior: as mesmas distâncias, agora com Fá#."),

        h ("Por que a escala maior importa para a harmonia"),
        p (
            "A escala maior é a matéria-prima da harmonia. Quando você empilha notas da própria escala sobre cada grau, obtém os acordes do campo harmônico — e esses acordes se organizam em três famílias de função. Toda a lógica de tensão e repouso que faz a música 'andar' vem da relação entre essas famílias, e todas elas existem porque a escala maior tem aquele padrão específico de tons e semitons."),
        p (
            "Pense na escala maior como um vocabulário. Isoladamente, cada nota é apenas um som; dentro do campo harmônico, cada nota vira parte de um acorde; e dentro da progressão, cada acorde vira uma função que empurra a música para frente ou a faz repousar. Este módulo percorre exatamente esse caminho: da escala para os acordes, dos acordes para as funções, das funções para as cadências."),
        b ("Escala → acordes (empilhando notas da escala)."),
        b ("Acordes → funções (tônica, subdominante, dominante)."),
        b ("Funções → cadências (o jogo de tensão e repouso)."),

        h ("Erros comuns ao estudar a escala maior"),
        p (
            "O erro mais frequente é tocar a escala de ouvido sem respeitar o padrão, o que faz aparecer uma nota errada justamente onde o semitom deveria estar. Outro erro é decorar as notas de uma tonalidade sem entender que o padrão é sempre o mesmo, o que impede de transpor. E há quem toque a escala subindo e descendo rápido, mas não saiba dizer qual nota é o grau 3 ou o grau 7 — e sem isso a escala não serve para harmonizar."),
        b ("Esquecer o semitom entre os graus 3–4 e 7–8 deixa a escala desafinada."),
        b ("Decorar notas sem o padrão trava a transposição."),
        b ("Tocar sem saber o grau de cada nota não ajuda a montar acordes."),
        c (
            "Dica de estudo: cante cada grau pelo número antes de tocar. Dizer 'um, dois, três, quatro…' enquanto sobe a escala fixa a numeração no ouvido e prepara o terreno para as funções harmônicas dos próximos tópicos."),

        h ("A escala maior e a escala cromática"),
        p (
            "Para entender a escala maior, vale comparar com a escala cromática, que contém todas as doze notas dentro da oitava, uma por semitom. A escala maior é uma seleção de sete dessas doze notas, escolhidas exatamente para produzir o padrão T – T – S – T – T – T – S. As cinco notas que ficam de fora são justamente as que criariam os semitons 'extras' e mudariam o caráter da escala."),
        p (
            "Essa relação explica por que a escala maior soa tão 'natural' ao ouvido ocidental: ela é a seleção cromática que produz o maior número de consonâncias e a sensação de repouso mais clara. As escalas menores e os modos que você verá mais adiante são outras seleções das mesmas doze notas, escolhidas para produzir outros climas."),
        b ("Cromática: 12 notas, uma por semitom, dentro da oitava."),
        b ("Maior: 7 dessas 12 notas, escolhidas para dar o padrão T–T–S–T–T–T–S."),
        b ("As 5 notas de fora são as que mudariam o caráter da escala."),
        img ("m5_escala_maior_graus", "A escala maior como uma seleção da escala cromática: sete notas entre as doze."),

        h ("A escala maior no teclado e no braço"),
        p (
            "No teclado, a escala de Dó maior são todas as teclas brancas. Repare que o desenho do teclado foi feito justamente para mostrar isso: os dois semitons da escala (Mi–Fá e Si–Dó) correspondem aos dois pares de teclas brancas que não têm tecla preta entre elas. Tocar a escala de Dó no teclado é tocar de uma tecla branca à seguinte, sem tocar nenhuma preta."),
        p (
            "No braço da guitarra, o desenho é menos evidente porque as cordas estão afinadas em intervalos diferentes, mas o princípio é o mesmo. Cada casa é um semitom e a tônica pode estar em qualquer corda. Por isso a escala maior no braço aparece como uma sequência de posições que se desloca conforme a região — e é esse deslocamento que os exercícios deste tópico vão treinar."),
        b ("No teclado, Dó maior são só as teclas brancas."),
        b ("No braço, a escala é uma sequência de posições que se desloca."),
        b ("A mesma régua de semitons vale nos dois instrumentos."),
        aud ({ "C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5", "B4", "A4", "G4", "F4", "E4", "D4", "C4" },
             "Escala de Dó maior subindo e descendo: o mesmo padrão nos dois sentidos."),

        h ("Como praticar a escala maior"),
        p (
            "A prática da escala maior tem três objetivos: fixar o desenho no braço, ouvir o padrão de tons e semitons e saber nomear o grau de cada nota. Comece tocando devagar, uma nota por tempo do metrônomo, dizendo o número do grau em voz alta. Só acelere quando conseguir tocar sem errar e sem parar de contar."),
        p (
            "Depois de dominar a escala subindo, pratique descendo e em padrões (1–2–3, 2–3–4, 3–4–5…). Esses padrões são a base das frases que você vai improvisar mais adiante e, ao mesmo tempo, reforçam a memória dos graus. É um dos exercícios mais antigos e mais eficientes do estudo da guitarra."),
        b ("Toque devagar, contando o grau em voz alta."),
        b ("Pratique subindo, descendo e em padrões de três notas."),
        b ("Confirme com o app se as notas tocadas respeitam o padrão."),
        c (
            "O app reconhece as notas da escala e confere se você tocou o padrão correto. Se uma nota sair meio tom fora do lugar, o exercício acusa — o que torna a prática da escala uma verificação objetiva, e não só uma repetição mecânica."),

        h ("Escala maior e tonalidade"),
        p (
            "Dizer que uma música está 'em Dó maior' significa que a sua escala de referência é a de Dó maior e que o seu centro de repouso é o acorde de Dó. A tonalidade é, portanto, a combinação de uma escala com um centro. A escala fornece as notas; o centro define para onde a música quer ir."),
        p (
            "É por isso que este módulo começa pela escala e termina pela harmonização. A escala maior é a matéria-prima; a tonalidade é o uso dessa matéria-prima em torno de um centro. Todas as funções harmônicas que você vai estudar — tônica, subdominante e dominante — só fazem sentido dentro de uma tonalidade definida."),
        b ("Tonalidade = escala + centro de repouso."),
        b ("A escala fornece as notas; o centro define o repouso."),
        b ("As funções harmônicas só existem dentro de uma tonalidade."),

        h ("Resumo do tópico"),
        b ("A escala maior segue o padrão T – T – S – T – T – T – S."),
        b ("Os semitons ficam entre os graus 3–4 e 7–8."),
        b ("Cada grau tem um número romano e uma qualidade de acorde prevista."),
        b ("O padrão é o mesmo em toda tonalidade; só muda a tônica."),
        b ("A escala maior é a matéria-prima do campo harmônico e das funções."),
        c (
            "Nos exercícios deste tópico, toque a escala maior e as notas dos graus pedidos no instrumento. O app reconhece as notas e confere se você respeitou o padrão — em qualquer posição do braço."),
    };
}

} // namespace cursomusica::content
