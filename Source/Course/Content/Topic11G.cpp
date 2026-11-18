#include "Course/Content/Topics.h"

// Topic 11G — Sistema 5 (CAGED) (Módulo 11, Etapa 11).
namespace cursomusica::content
{

std::vector<ContentItem> topic11G()
{
    return {

        p (
            "O Sistema 5 é o mapa que liga acordes e escalas pelo braço inteiro. Você já viu o CAGED no Módulo 1 como um jeito de organizar acordes; aqui ele volta como a espinha dorsal do fraseado: cada forma de acorde é também a tônica de um desenho de escala. Aprender o Sistema 5 é aprender onde a escala tem a sua casa em cada região do braço."),
        p (
            "A ideia central é simples e poderosa: para cada acorde, existe uma forma (C, A, G, E, D) e, dentro dessa forma, uma escala. Quando você improvisa sobre um acorde, toca o desenho da escala que mora dentro da forma daquele acorde. É assim que o solo acompanha a harmonia em vez de flutuar sobre ela."),
        c (
            "Sistema 5: as cinco formas de acorde (C-A-G-E-D) e os cinco desenhos de escala que vivem dentro delas. Cada forma é uma região; cada região tem a tônica na forma."),

        h ("As cinco formas e os cinco desenhos"),
        p (
            "O Sistema 5 parte das cinco formas de acorde maior. Cada forma, quando você a estende, revela um desenho de escala ao seu redor. A forma de C tem a escala na posição 1; a de A na posição 2; a de G na 3; a de E na 4; a de D na 5 — e depois volta à de C uma oitava acima. As cinco formas cobrem o braço inteiro."),
        p (
            "O que faz o Sistema 5 tão útil no fraseado é a ligação acorde-escala. Quando a harmonia muda para outro acorde, você muda a forma e, com ela, o desenho da escala. O solo passa a seguir a progressão: cada acorde tem a sua casa, e a frase viaja de casa em casa junto com a harmonia."),
        b ("Cinco formas de acorde: C, A, G, E e D."),
        b ("Cada forma carrega um desenho de escala ao seu redor."),
        b ("As formas cobrem o braço e se repetem uma oitava acima."),
        b ("Trocar de acorde é trocar de forma — e de desenho de escala."),
        img ("m11_caged_sistema5", "Sistema 5 (CAGED): as cinco formas de acorde e os desenhos de escala que vivem dentro delas, cobrindo o braço."),

        h ("Acorde e escala na mesma mão"),
        p (
            "O grande ganho do Sistema 5 é ter o acorde e a escala no mesmo lugar. Se você toca a forma de Lá menor na posição 2, a escala de Lá menor está ali, em volta dos seus dedos. Isso significa que, ao improvisar, você não precisa calcular: a tônica está na forma, e a frase nasce dela."),
        p (
            "Para o fraseado, a tônica dentro da forma é o alvo. Você conduz a frase para a nota da forma (a tônica do acorde) e ali repousa. É o que faz a frase soar \"dentro\" da harmonia. Sem o Sistema 5, o aluno improvisa escalas soltas; com ele, a frase aponta sempre para a nota certa."),
        tbl ({ "Forma", "Posição (ex.: Lá)", "Tônica na", "Escala ao redor" }, {
            { "E", "casa 5", "6ª corda", "desenho da posição 1" },
            { "D", "casa 5", "4ª corda", "desenho da posição 2" },
            { "C", "casa 8", "5ª corda", "desenho da posição 3" },
            { "A", "casa 12", "5ª corda", "desenho da posição 4" },
            { "G", "casa 12", "6ª corda", "desenho da posição 5" },
        }),
        c (
            "Regra de ouro do fraseado: mire a tônica da forma. Toda frase que resolve numa nota do acorde soa \"certa\"; toda frase que resolve fora dele soa perdida. O Sistema 5 coloca o alvo debaixo dos seus dedos."),

        h ("O lick deste tópico"),
        p (
            "O lick abaixo sobe o desenho da escala que vive dentro da forma de Lá menor (forma de E, posição 1) e resolve na tônica da forma. É um gesto de Kiko Loureiro — fraseado melódico que usa o CAGED para guiar o solo. Ouça como a frase aponta sempre para a nota do acorde."),
        aud ({ "A4", "C5", "D5", "E5", "F5", "G5", "A5", "G5", "E5", "C5", "A4" },
             "Lick do tópico G: o desenho da escala dentro da forma de Lá menor, resolvendo na tônica do acorde."),
        part ("m11_partitura_g", { "A4", "C5", "D5", "E5", "F5", "G5", "A5", "G5", "E5", "C5", "A4" },
              "Partitura do lick G: a escala dentro da forma de acorde (Sistema 5). A frase resolve na tônica da forma."),

        h ("Estudar o Sistema 5"),
        p (
            "Toque cada forma de acorde e, em seguida, o desenho de escala que mora dentro dela. Faça isso para as cinco formas na mesma tonalidade, subindo o braço. Depois, improvise sobre um vamp trocando de forma a cada acorde. Quando a mão encontrar a tônica da forma sem pensar, o Sistema 5 virou a sua bússola no braço."),

        h ("Do acorde à escala, sem cálculo"),
        p (
            "O Sistema 5 resolve um problema prático do improvisador: saber, na hora, qual escala tocar sobre o acorde que está soando. Se você conhece as cinco formas de acorde e os desenhos de escala que vivem dentro delas, a resposta está debaixo dos seus dedos. Não há cálculo: você olha a forma do acorde e a escala está ali, ao redor."),
        p (
            "Isso é especialmente útil quando a harmonia se move rápido. Em vez de pensar \"agora é Dm7, então a escala é...\", você pensa \"agora é a forma de Dm na casa X\", e a escala aparece. O Sistema 5 transforma a harmonia em posições no braço, e o braço em um mapa que a mão já conhece."),
        b ("Cada forma de acorde carrega um desenho de escala ao seu redor."),
        b ("A tônica da forma é o alvo natural da frase."),
        b ("Trocar de acorde é trocar de forma — e de escala — sem cálculo."),
        tbl ({ "Forma", "Tipo de acorde", "Tônica em" }, {
            { "E", "maior/menor com pestana", "6ª corda" },
            { "A", "maior/menor com pestana", "5ª corda" },
            { "C", "aberto/transposto", "5ª corda" },
            { "G", "aberto/transposto", "6ª corda" },
            { "D", "aberto/transposto", "4ª corda" },
        }),

        h ("O Sistema 5 e a harmonia"),
        p (
            "O grande valor do Sistema 5 aparece quando a harmonia tem mais de um acorde. Sobre um ii–V–I, por exemplo, você toca a forma do ii, depois a forma do V e depois a forma do I, e cada forma traz a sua escala. A frase segue a harmonia passo a passo, resolvendo na tônica de cada forma. É isso que faz o solo \"conversar\" com os acordes em vez de flutuar sobre eles."),
        p (
            "Para o fraseado tonal deste módulo, o Sistema 5 é a ferramenta que liga a escala ao acorde. Quando o vamp muda de acorde, a forma muda, e a sua frase muda com ela. O ouvido percebe a mudança como intenção harmônica, e o solo passa a ter a cor de cada acorde, não só a cor do centro."),
        c (
            "Exercício: toque as cinco formas do acorde de Lá menor subindo o braço, e dentro de cada forma toque o desenho de escala que vive nela. Depois improvise sobre um vamp trocando de forma a cada acorde, sempre resolvendo na tônica da forma."),

        h ("CAGED: a ponte entre acorde e escala"),
        p (
            "O CAGED é, no fundo, uma ponte. De um lado estão os acordes que você já toca; do outro, as escalas que você estuda. O Sistema 5 liga os dois, mostrando que cada acorde tem a sua escala e cada escala tem o seu acorde. Para o improvisador, essa ponte é o que permite tocar a escala certa sobre o acorde certo, em qualquer lugar do braço."),
        p (
            "Dominar o Sistema 5 é, portanto, dominar a relação entre harmonia e melodia no braço. É o pré-requisito para o fraseado tonal dos módulos de blues e standards, e a base para entender por que certas notas soam bem sobre certos acordes. Quando o Sistema 5 estiver automático, a improvisação deixa de ser tentativa e erro."),


        h ("Sistema 5 sobre progressões"),
        p (
            "O Sistema 5 mostra todo o seu valor quando a harmonia tem mais de um acorde. Sobre um ii–V–I, cada acorde tem a sua forma, e cada forma traz a sua escala. Você toca a forma do ii, resolve na sua tônica; passa para a forma do V, resolve na sua tônica; e chega na forma do I, resolvendo na tônica final. A frase segue a harmonia passo a passo, e o ouvinte percebe a mudança como intenção, não como acidente."),
        p (
            "Esse encadeamento de formas é o que faz o solo \"conversar\" com os acordes. Em vez de tocar a mesma escala sobre toda a progressão, você muda de forma a cada acorde e, com isso, muda as notas de repouso. A frase passa a ter a cor de cada acorde, e a resolução acontece sempre no lugar certo. É a diferença entre improvisar \"em cima\" da música e improvisar \"dentro\" dela."),
        p (
            "O treino é simples, mas exige paciência. Escolha uma progressão de três ou quatro acordes e toque as formas correspondentes em sequência, resolvendo na tônica de cada uma. Depois, improvise uma frase curta sobre cada forma, sempre resolvendo na tônica. Quando as transições ficarem suaves, você terá o Sistema 5 funcionando como ferramenta de improvisação, e não só como teoria."),
        b ("Sobre uma progressão, cada acorde tem a sua forma e a sua escala."),
        b ("Mude de forma a cada acorde e resolva na tônica de cada uma."),
        b ("Treine formas em sequência sobre ii–V–I até as transições ficarem suaves."),
        tbl ({ "Acorde", "Forma", "Resolve em" }, {
            { "ii (Dm7)", "forma de Dm", "D" },
            { "V (G7)", "forma de G", "G" },
            { "I (C7M)", "forma de C", "C" },
        }),


        h ("O braço como mapa harmônico"),
        p (
            "Depois de dominar o Sistema 5, o braço deixa de ser um conjunto de posições e passa a ser um mapa harmônico. Cada região do braço corresponde a um acorde e à sua escala. Você olha para um trecho do braço e sabe qual acorde vive ali. É esse mapa que permite improvisar sobre harmonias complexas sem decorar escala por escala: a harmonia está desenhada no braço."),
        p (
            "Esse mapa é especialmente útil quando a música modula. Em vez de recalcular as escalas, você simplesmente move a forma do acorde para a nova região e a escala vem junto. A improvisação sobre modulações deixa de ser um problema de teoria e passa a ser um problema de posição no braço. É a harmonia resolvida pela geometria do instrumento."),
        p (
            "Construir esse mapa leva tempo, mas o retorno é grande. Toque as cinco formas do acorde de Lá menor subindo o braço, e dentro de cada uma o desenho da escala. Depois, faça o mesmo com o acorde maior e com o dominante. Quando as três famílias estiverem mapeadas, você terá o braço inteiro organizado por acorde e escala, pronto para qualquer música."),
        b ("O Sistema 5 transforma o braço num mapa harmônico."),
        b ("Sobre modulações, mova a forma do acorde e a escala vem junto."),
        b ("Mapeie as cinco formas do menor, do maior e do dominante."),
        tbl ({ "Família", "Formas", "Uso" }, {
            { "Menor", "m7 em cinco posições", "frases sobre acordes menores" },
            { "Maior", "7M em cinco posições", "frases sobre acordes maiores" },
            { "Dominante", "7 em cinco posições", "frases sobre dominantes" },
        }),

        c (
            "Meta do módulo: 100 BPM. A prova do Sistema 5 é improvisar sobre um vamp trocando de forma a cada acorde, sempre resolvendo na tônica da forma — é o primeiro passo para o fraseado tonal deste módulo."),
    };
}

} // namespace cursomusica::content
