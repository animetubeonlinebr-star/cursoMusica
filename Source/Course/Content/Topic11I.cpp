#include "Course/Content/Topics.h"

// Topic 11I — Escala menor melódica (Módulo 11, Etapa 11).
namespace cursomusica::content
{

std::vector<ContentItem> topic11I()
{
    return {

        p (
            "A escala menor melódica é o passo seguinte da menor harmônica. Se a harmônica eleva só o sétimo grau, a melódica eleva também o sexto. O resultado é uma escala menor que sobe com a suavidade da escala maior — sem o salto da segunda aumentada — e que, por isso, é muito mais cantável. É a escala menor \"elegante\" do jazz e da música clássica."),
        p (
            "Você também já viu a menor melódica no Módulo 6. Aqui ela volta como ferramenta de fraseado. A sua grande qualidade é a fluência: elevando o sexto grau, a segunda aumentada da harmônica desaparece, e a escala sobe por graus conjuntos. Isso a torna ideal para linhas longas e cantáveis — o tipo de frase que sobe sem tropeçar."),
        c (
            "Menor melódica = menor natural com o 6º e o 7º graus elevados. Em Lá: A-B-C-D-E-F#-G#-A. Sem a segunda aumentada, ela sobe por graus conjuntos e é muito cantável."),

        h ("A diferença em relação à harmônica"),
        p (
            "A menor harmônica eleva o sétimo grau e cria a segunda aumentada. A menor melódica eleva também o sexto, e é essa segunda elevação que fecha a brecha: com o Fá# no lugar do Fá, o intervalo Fá#-Sol# vira um tom inteiro, e a escala sobe sem o salto dramático. A melódica é a menor harmônica \"domada\" para a melodia."),
        p (
            "Na prática, a melódica é mais fácil de cantar e de frasea. Onde a harmônica dá um gesto exótico, a melódica dá uma linha suave. Os dois nomes dizem o que cada uma faz: a harmônica serve à harmonia (a dominante forte), a melódica serve à melodia (a linha cantável)."),
        b ("A menor melódica eleva o 6º e o 7º graus (em Lá: Fá# e Sol#)."),
        b ("Elevar o 6º grau elimina a segunda aumentada da harmônica."),
        b ("A escala sobe por graus conjuntos — é mais cantável."),
        b ("Serve à melodia; a harmônica serve à harmonia."),
        img ("m11_menor_melodica", "Escala menor melódica: a menor natural com o 6º e o 7º graus elevados. Sem segunda aumentada, sobe por graus conjuntos."),

        h ("Ascendente e descendente"),
        p (
            "Na tradição clássica, a menor melódica sobe com os graus elevados e desce como a menor natural — uma escala que muda de forma no caminho. No jazz e na música moderna, adota-se a melódica ascendente nos dois sentidos: sobe e desce com o Fá# e o Sol#. Neste módulo usamos a forma moderna (a mesma nos dois sentidos), porque é a que se aplica ao fraseado."),
        p (
            "Essa escolha importa para a frase: com os graus elevados nos dois sentidos, a escala mantém a sua cor em toda a extensão. A linha não muda de caráter no meio, e a improvisação fica coerente do começo ao fim."),
        tbl ({ "Grau", "Nota em Lá", "Observação" }, {
            { "1", "A", "tônica" },
            { "b3", "C", "terça menor" },
            { "4", "D", "subdominante" },
            { "5", "E", "dominante" },
            { "6", "F#", "sexta elevada (dá a fluência)" },
            { "7", "G#", "sétima elevada (puxa a tônica)" },
        }),
        c (
            "Repouso × tensão: A-C-E são repouso; o F# é a nota característica (a sexta elevada, que dá o som da melódica) e o G# é a tensão que resolve na tônica. O exercício reconhece as três."),

        h ("O lick deste tópico"),
        p (
            "O lick abaixo sobe a menor melódica de Lá nos dois sentidos, destacando a sexta elevada (Fá#) e a sétima elevada (Sol#) e resolvendo na tônica. É um gesto de Steve Vai — linhas cantáveis com amplo alcance —, onde a melódica dá a fluência e a frase fecha com naturalidade."),
        aud ({ "A4", "B4", "C5", "D5", "E5", "F#5", "G#5", "A5", "G#5", "F#5", "E5", "D5", "C5", "B4", "A4" },
             "Lick do tópico I: menor melódica de Lá. A sexta (F#) e a sétima (G#) elevadas dão a fluência; a frase resolve na tônica."),
        part ("m11_partitura_i", { "A4", "B4", "C5", "D5", "E5", "F#5", "G#5", "A5", "G#5", "F#5", "E5", "D5", "C5", "B4", "A4" },
              "Partitura do lick I: escala menor melódica ascendente e descendente. A sexta e a sétima elevadas mantêm a cor nos dois sentidos."),

        h ("Estudar a menor melódica"),
        p (
            "Toque a melódica e a harmônica seguidas, na mesma tonalidade, e ouça a diferença: a harmônica salta, a melódica flui. Depois, toque a melódica em sequências de grupos de três e de quatro, sempre destacando a sexta elevada. Por fim, improvise sobre um vamp menor usando a melódica para linhas longas e cantáveis."),

        h ("Por que a melódica é mais cantável"),
        p (
            "A menor melódica é mais cantável porque sobe por graus conjuntos. Na harmônica, o salto da segunda aumentada quebra a linha; na melódica, esse salto não existe, porque o sexto grau também sobe. O resultado é uma escala menor que flui como a maior, sem os saltos que dificultam o canto. Por isso a melódica é a escala menor preferida de quem fraseia linhas longas."),
        p (
            "A diferença está em uma nota: a harmônica tem o Fá natural, a melódica tem o Fá#. Essa única mudança transforma a escala de \"dramática\" em \"fluente\". Onde a harmônica pede um gesto de tensão, a melódica oferece uma linha contínua. As duas são úteis; a escolha depende do caráter que a frase pede."),
        b ("A melódica eleva o 6º e o 7º graus; a harmônica só o 7º."),
        b ("Sem a segunda aumentada, a melódica sobe por graus conjuntos."),
        b ("Ela é a escala menor das linhas longas e cantáveis."),
        tbl ({ "Escala", "6º grau", "7º grau", "Caráter" }, {
            { "Menor natural", "menor", "menor", "melancólico" },
            { "Menor harmônica", "menor", "maior", "dramático" },
            { "Menor melódica", "maior", "maior", "fluente, cantável" },
        }),

        h ("A forma moderna da melódica"),
        p (
            "Na tradição clássica, a menor melódica sobe com os graus elevados e desce como a menor natural. No jazz e na música moderna, adota-se a forma ascendente nos dois sentidos: a escala mantém o Fá# e o Sol# tanto na subida quanto na descida. É essa forma que usamos no fraseado, porque mantém a cor da escala em toda a extensão."),
        p (
            "Essa escolha tem uma consequência prática: a frase não muda de caráter no meio. Se você sobe com a sexta elevada e desce com a sexta menor, a linha fica incoerente. Mantendo os graus elevados nos dois sentidos, a improvisação soa coesa, e o ouvido reconhece uma única escala do começo ao fim."),
        c (
            "Nota característica: a sexta elevada (Fá# em Lá) é o que distingue a melódica. É ela que dá o brilho da escala; a sétima elevada (Sol#) é a que puxa para a tônica. Juntas, dão à melódica a sua assinatura."),

        h ("Aplicando a menor melódica"),
        p (
            "A menor melódica brilha em três contextos. No jazz, sobre acordes menores com sétima maior e sobre dominantes alterados. Na música clássica, nas passagens melódicas em menor. E na música moderna, como escala de linhas longas e expressivas. Cada contexto explora a fluência da escala de uma forma diferente."),
        p (
            "Para o aluno, a menor melódica é a escala que fecha o par das menores especiais. Depois de estudar a harmônica (drama) e a melódica (fluência), você tem duas ferramentas para o modo menor: uma para tensão, outra para cantabilidade. Saber escolher entre as duas é o que dá variedade ao fraseado menor."),


        h ("A menor melódica no braço"),
        p (
            "A menor melódica, ao contrário da harmônica, sobe por graus conjuntos em toda a extensão — não há salto. Isso a torna natural de tocar em todas as regiões, sem digitações especiais. O que exige atenção é a memória: como a escala difere da menor natural em duas notas (a sexta e a sétima elevadas), é fácil tocar a sexta menor por hábito. Toque devagar, ouvindo a sexta elevada, até que ela fique automática."),
        p (
            "Um bom exercício é comparar a menor natural e a menor melódica, nota a nota. Você toca a natural e depois a melódica, destacando as duas notas que mudam (a sexta e a sétima). Ouvindo o contraste, o ouvido memoriza a cor da melódica, e a mão passa a encontrá-la sem depender de cálculo. É esse reconhecimento auditivo que sustenta a improvisação."),
        p (
            "Depois de dominar a escala em todas as regiões, o passo é usá-la em frases. A menor melódica é ideal para linhas longas e cantáveis, porque sobe por graus conjuntos e mantém a cor nos dois sentidos. Improvise sobre um acorde menor com sétima maior, buscando frases que subam e desçam sem salto. A fluência da escala vai aparecer naturalmente nas suas linhas."),
        b ("A menor melódica sobe por graus conjuntos: não tem salto, é fácil de tocar."),
        b ("Compare com a menor natural e destaque a sexta e a sétima elevadas."),
        b ("Use-a para linhas longas e cantáveis sobre acordes menores."),
        tbl ({ "Nota", "Na natural", "Na melódica" }, {
            { "6º grau", "sexta menor (Fá)", "sexta maior (Fá#)" },
            { "7º grau", "sétima menor (Sol)", "sétima maior (Sol#)" },
            { "Efeito", "melancólico", "fluente e cantável" },
        }),


        h ("Cantar com o instrumento"),
        p (
            "A menor melódica é a escala menor que se canta. Sua fluência por graus conjuntos faz com que a frase soe vocal, como se você estivesse cantando pelo instrumento. É por isso que muitos guitarristas melódicos preferem a melódica à harmônica: ela deixa a linha respirar, sem os saltos que quebram o canto. Cantar com o instrumento é o objetivo de quem estuda a melódica."),
        p (
            "Para desenvolver esse canto, toque a escala e, em seguida, improvise como se estivesse cantando. Frases curtas, respirações claras, notas de chegada bem escolhidas. A menor melódica ajuda porque cada grau conduz naturalmente ao próximo; não há salto que exija preparação. A frase flui, e o ouvinte acompanha como se ouvisse uma voz."),
        p (
            "Um bom exercício é cantarolar uma frase e depois tocá-la. Se a frase é cantável, ela cabe na menor melódica. Se a escala não couber, talvez você esteja pensando nela como exercício, e não como melodia. Lembre-se: a escala é uma ferramenta de canto. Usá-la para cantar é o que dá sentido a tudo o que você estudou sobre ela."),
        b ("A menor melódica é a escala menor que se canta."),
        b ("Frases curtas e respirações claras soam mais vocais."),
        b ("Cante a frase antes de tocá-la para testar a sua cantabilidade."),
        tbl ({ "Qualidade", "Escala ideal", "Por quê" }, {
            { "Fluência", "menor melódica", "sobe por graus conjuntos" },
            { "Drama", "menor harmônica", "tem a segunda aumentada" },
            { "Tristeza", "menor natural", "sem graus elevados" },
        }),

        c (
            "Meta do módulo: 100 BPM. A prova da menor melódica é a fluência: a linha sobe e desce sem tropeçar, mantendo a sexta e a sétima elevadas do começo ao fim."),
    };
}

} // namespace cursomusica::content
