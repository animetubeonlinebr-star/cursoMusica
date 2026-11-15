#include "Course/Content/Topics.h"

// Topic 7E — Acordes e famílias modais (Módulo 7, Etapa 7).
// Fonte de verdade do texto: docs/MUSIC.md §7.2 (bloco E).
namespace cursomusica::content
{

std::vector<ContentItem> topic7E()
{
    return {

        p (
            "Cada acorde carrega dentro de si uma família de modos possíveis. Quando você vê um Cmaj7, um C7 ou um Cm7, não está vendo apenas um conjunto de notas: está vendo um leque de escalas que combinam com aquele acorde. Escolher a escala certa para cada acorde é o que faz a improvisação soar como música, e não como uma sequência aleatória de notas."),
        p (
            "Neste tópico você aprende a associar acordes às suas famílias modais: quais modos combinam com acordes maiores, menores e dominantes, e como reconhecer a família pelo som. Esse é o mapa que liga a harmonia (os acordes) à melodia (as escalas e os modos) — a ponte para tudo o que vem nos tópicos seguintes."),

        h ("Por que um acorde tem uma família de modos"),
        p (
            "Um acorde de sétima define alguns intervalos fixos: a terça, a quinta e a sétima. Mas ele deixa “livres” outros graus, como a nona, a décima primeira e a décima terceira. Esses graus livres podem ser preenchidos de formas diferentes, e cada combinação corresponde a um modo. É por isso que o mesmo acorde pode “vestir” modos diferentes."),
        b ("A terça define maior ou menor; a sétima define o tipo de acorde."),
        b ("As tensões (9, 11, 13) definem o modo."),
        b ("Um acorde, várias escalas possíveis."),
        c (
            "Este tópico é a ponte entre harmonia e melodia. Depois de aprendê-lo, você escolhe a escala pelo acorde, e não por tentativa e erro."),

        img ("m7_familias_modais", "As famílias modais: cada família de acorde e os modos que combinam com ela."),

        h ("A família dos acordes maiores"),
        p (
            "Acordes maiores com sétima maior (Xmaj7) combinam com três modos principais: o jônio (a escala maior), o lídio (com a quarta aumentada) e, mais raramente, o lídio b7. O jônio é o som padrão; o lídio dá um brilho especial, com a #11, e é muito usado em vamps modais."),
        tbl ({ "Acorde", "Modos que combinam", "Cor característica" }, {
            { "Xmaj7", "jônio (I), lídio (IV)", "claro; lídio dá brilho com #11" },
            { "Xmaj7#11", "lídio", "brilho modal, som moderno" },
            { "X6", "jônio, mixolídio", "sexta no lugar da sétima" },
            { "Xmaj9", "jônio, lídio", "aberto e sofisticado" },
        }),
        b ("Jônio: a escala maior — o som “natural” do acorde maior."),
        b ("Lídio: a escala maior com a quarta aumentada (#11)."),
        aud ({ "C4", "E4", "G4", "B4", "D4" }, "Cmaj9: som claro e aberto do acorde maior."),

        h ("A família dos acordes menores"),
        p (
            "Acordes menores combinam com três modos principais: o dórico (menor com sexta maior), o eólio (menor natural) e o frígio (menor com segunda menor). O dórico é o som do jazz e da música modal menor; o eólio é o menor “clássico”; o frígio tem um sabor espanhol."),
        tbl ({ "Acorde", "Modos que combinam", "Cor característica" }, {
            { "Xm7", "dórico (II), eólio (VI)", "dórico dá a sexta maior" },
            { "Xm6", "dórico", "sexta maior no acorde" },
            { "Xm9", "dórico", "aberto, som de jazz" },
            { "Xm7b5", "lócrio", "meio-diminuto, tenso" },
        }),
        b ("Dórico: menor com sexta maior — som aberto, jazzístico."),
        b ("Eólio: menor natural — som melancólico."),
        b ("Frígio: menor com segunda menor — sabor espanhol."),
        aud ({ "D3", "F3", "A3", "C4", "E4" }, "Dm9 (dórico): o som menor aberto do jazz."),

        h ("A família dos acordes dominantes"),
        p (
            "Acordes dominantes (X7) têm a maior variedade de modos: mixolídio, lídio dominante, mixolídio #4, alterado e mixolídio sus. Isso acontece porque o dominante é o acorde de maior tensão, e a música usa essa tensão de várias formas. Cada modo muda a forma como a tensão é criada e resolvida."),
        tbl ({ "Acorde", "Modos que combinam", "Cor característica" }, {
            { "X7", "mixolídio", "dominante natural" },
            { "X7sus4", "mixolídio sus", "sem a terça, suspenso" },
            { "X7#11", "lídio dominante", "tensão com #11" },
            { "X7alt", "alterado", "tensão máxima, resolve meio-tom abaixo" },
        }),
        b ("Mixolídio: a escala maior com sétima menor."),
        b ("Lídio dominante: maior com sétima menor e #11."),
        b ("Alterado: a escala de tensão máxima sobre o dominante."),
        aud ({ "C4", "E4", "G4", "A#3", "F#4" }, "C7#11 (lídio dominante): tensão com brilho."),

        h ("O acorde meio-diminuto"),
        p (
            "O acorde meio-diminuto (Xm7b5) combina com o modo lócrio, que é a escala menor com a segunda menor e a quinta diminuta. É o som do II grau nos II–V–I menores, e aparece o tempo todo no jazz. Reconhecer esse acorde e o seu modo é essencial para tocar sobre progressões menores."),
        b ("Lócrio: menor com segunda menor e quinta diminuta."),
        b ("É o II grau do II–V–I menor."),
        b ("O lócrio 9 (com a nona natural) é uma variação importante, vista adiante."),

        h ("Aplicação: escolher a escala pelo acorde"),
        p (
            "Na prática, o músico olha o acorde e escolhe a escala pela família. Sobre um Cmaj7, ele pode tocar jônio (som natural) ou lídio (som brilhante); sobre um Cm7, dórico (aberto) ou eólio (melancólico); sobre um C7, mixolídio (natural) ou alterado (tenso). Essa escolha é a expressão da intenção musical."),
        b ("Leia o acorde e identifique a família (maior, menor, dominante, meio-diminuto)."),
        b ("Escolha o modo pela cor que você quer."),
        b ("Toque e ouça: a cor muda conforme o modo."),
        c (
            "Nos exercícios deste tópico, você toca acordes e o app reconhece as notas. Você também responderá a questionários que associam acordes às suas famílias modais."),

        h ("Famílias modais e o círculo das quintas"),
        p (
            "As famílias modais se organizam ao longo do campo harmônico. Em Dó maior, os graus I (Cmaj7), IV (Fmaj7) e V (G7) formam as três famílias principais; os graus II (Dm7), III (Em7) e VI (Am7) formam as famílias menores. Reconhecer o grau do acorde ajuda a escolher o modo: o II é dórico, o IV é lídio, o V é mixolídio."),
        tbl ({ "Grau em Dó maior", "Acorde", "Modo" }, {
            { "I", "Cmaj7", "jônio" },
            { "II", "Dm7", "dórico" },
            { "III", "Em7", "frígio" },
            { "IV", "Fmaj7", "lídio" },
            { "V", "G7", "mixolídio" },
            { "VI", "Am7", "eólio" },
            { "VII", "Bm7b5", "lócrio" },
        }),

        h ("Como estudar as famílias"),
        p (
            "O estudo das famílias modais é um trabalho de escuta e prática. Toque o mesmo acorde com modos diferentes e ouça a cor que cada um acrescenta; depois, improvise sobre vamps usando cada modo. Com o tempo, você reconhece a família pelo som do acorde e escolhe o modo instintivamente."),
        b ("Toque o acorde com cada modo de sua família."),
        b ("Improvisse sobre vamps, um modo por vez."),
        b ("Compare as cores e memorize as sensações."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é tocar uma nota de evitação — um grau que cria atrito com o modo do acorde, como a décima primeira natural sobre um acorde maior. Outro é usar o modo errado para o acorde, esquecendo que a sétima do acorde restringe as opções. Estudar a família resolve os dois casos."),
        b ("Verifique se a nota que você toca cria atrito com o modo."),
        b ("Lembre-se de que a sétima do acorde restringe as opções."),
        b ("Ouça o resultado antes de fixar a escolha."),

        h ("Famílias modais e a nota de evitação"),
        p (
            "Cada modo tem notas que combinam e notas que criam atrito com o acorde. Essas notas de atrito são chamadas de notas de evitação, e reconhecê-las é fundamental para improvisar sem soar errado. Por exemplo, a décima primeira natural (a quarta) sobre um acorde maior é uma nota de evitação; o modo lídio resolve isso usando a #11."),
        b ("Maior: a 11 natural é nota de evitação; use a #11 (lídio)."),
        b ("Menor: a 13 (sexta maior) pode criar atrito no eólio; o dórico a aceita."),
        b ("Dominante: a 11 natural costuma funcionar; a #11 dá o lídio dominante."),
        c (
            "Notas de evitação não são proibidas: são notas que pedem cuidado e contexto. Saber onde elas estão evita os momentos em que a improvisação trava."),

        h ("Escolhendo o modo pelo contexto"),
        p (
            "A escolha do modo não depende só do acorde: depende também do contexto. O mesmo Cmaj7 pode receber jônio em uma balada e lídio em uma passagem instrumental. O músico escolhe a cor pela intenção da música, não apenas pela estrutura do acorde. Isso é o que separa o executante do intérprete."),
        b ("Balada: prefira o jônio (cor natural)."),
        b ("Passagem instrumental: o lídio acrescenta brilho."),
        b ("Vamp modal: o modo é o próprio material da música."),

        h ("Famílias modais e as tríades do meio"),
        p (
            "As famílias modais se conectam às tríades do meio que você estudou no tópico D. Cada tríade do meio produz uma cor que corresponde a um modo. Sobre um Cmaj7, a tríade de Ré maior (Ré–Fá#–Lá) produz a #11 e a 13, ou seja, a cor do lídio. Sobre um Cm7, a tríade de Sol menor produz a cor do dórico."),
        b ("Cmaj7 + tríade de Ré maior = cor lídia (#11)."),
        b ("Cm7 + tríade de Sol menor = cor dórica (9)."),
        b ("A tríade do meio é uma forma prática de tocar a cor do modo."),

        h ("O círculo das quintas e as famílias"),
        p (
            "O círculo das quintas ajuda a organizar as famílias modais. Cada acorde está a uma quinta do próximo, e as suas famílias de modos se relacionam por proximidade. Entender o círculo é entender como as famílias se conectam na harmonia real e como modular de um centro para outro."),
        b ("Cada passo no círculo é uma quinta."),
        b ("Acordes vizinhos compartilham notas e cores."),
        b ("O círculo orienta as modulações."),

        h ("Praticando as famílias modais"),
        p (
            "A prática das famílias modais combina audição e execução. Toque um acorde, escolha um modo da sua família e improvise uma frase curta, sempre voltando à nota característica do modo. Depois, troque o modo e repita. Com o tempo, você associa cada modo à sua cor e escolhe instintivamente."),
        b ("Um acorde, um modo, uma frase por vez."),
        b ("Volte sempre à nota característica."),
        b ("Compare as cores dos diferentes modos."),

        h ("Famílias modais e a prática musical"),
        p (
            "Saber a família modal de cada acorde é o que permite improvisar sem tentativa e erro. Ao olhar uma progressão, você identifica a família de cada acorde e escolhe o modo correspondente. A improvisação deixa de ser uma busca às cegas e passa a ser uma escolha consciente de cor, sempre guiada pela harmonia que está soando."),
        b ("Identifique a família de cada acorde da progressão."),
        b ("Escolha o modo pela família e pela intenção."),
        b ("Improvise com consciência da cor escolhida."),
        c (
            "Este é o hábito que transforma a teoria das famílias modais em ferramenta de palco."),

        h ("Resumo do tópico"),
        b ("Cada acorde tem uma família de modos possíveis."),
        b ("Maiores: jônio e lídio. Menores: dórico, eólio, frígio."),
        b ("Dominantes: mixolídio, lídio dominante, alterado, sus."),
        b ("Meio-diminuto: lócrio."),
        b ("Escolher a escala pelo acorde é a base da improvisação."),
        part ("m7_partitura_familias", { "D3", "F3", "A3", "C4", "E4" },
              "Partitura: Dm9 (dórico), um acorde da família menor com a sua cor. Ouça o som modal."),
    };
}

} // namespace cursomusica::content
