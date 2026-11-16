#include "Course/Content/Topics.h"

// Topic 6F — Campos harmônicos menores e funções dos acordes (Módulo 6, Etapa 6).
// Fonte de verdade do texto: docs/MUSIC.md §6.2 (bloco F).
namespace cursomusica::content
{

std::vector<ContentItem> topic6F()
{
    return {

        p (
            "Você já conhece a escala maior e o seu campo harmônico (módulo 1). Agora vai montar o campo harmônico menor: os sete acordes que nascem da escala menor, com as suas funções. É esse campo que sustenta o acompanhamento, a harmonia e a improvisação nas tonalidades menores — e é o que você usa quando toca uma música em Lá menor, em Ré menor ou em qualquer outra tonalidade menor."),
        p (
            "Montar o campo harmônico é empilhar terças sobre cada grau da escala. Sobre o primeiro grau nasce o acorde de tônica; sobre o segundo, o segundo acorde; e assim por diante. Como a escala menor tem os graus b3, b6 e b7, os acordes resultantes são diferentes dos do campo maior."),
        c (
            "Ideia central: o campo harmônico é o conjunto de acordes que nasce da escala. Cada acorde tem uma função (tônica, subdominante ou dominante) e a música caminha de uma função a outra."),

        h ("Como se monta o campo harmônico"),
        p (
            "Para montar o campo, você empilha terças sobre cada grau da escala. Sobre o 1º grau de Lá menor natural (A), empilhando terças, você obtém A, C, E, G — o acorde Am7. Sobre o 2º grau (B): B, D, F, A — o acorde Bm7(b5). E assim por diante, até o 7º grau."),
        b ("1º grau: A C E G = Am7 (i)."),
        b ("2º grau: B D F A = Bm7(b5) (ii)."),
        b ("3º grau: C E G B = Cmaj7 (III)."),
        b ("4º grau: D F A C = Dm7 (iv)."),
        b ("5º grau: E G B D = Em7 (v)."),
        b ("6º grau: F A C E = Fmaj7 (VI)."),
        b ("7º grau: G B D F = G7 (VII)."),
        img ("m6_campo_harmonico_menor", "O campo harmônico menor de Lá, com os sete acordes e as suas funções."),

        h ("O campo harmônico menor natural"),
        p (
            "O campo harmônico menor natural usa os acordes que nascem da escala menor natural. Ele é o campo \"básico\" das tonalidades menores. A sua característica é que o acorde de dominante (o v) é menor, e por isso não tem a sensível — o que enfraquece a cadência."),
        tbl ({ "Grau", "Acorde em Lá menor", "Qualidade", "Função" }, {
            { "i", "Am7", "menor com sétima", "tônica" },
            { "ii", "Bm7(b5)", "meio-diminuto", "subdominante" },
            { "III", "Cmaj7", "maior com sétima", "relativa maior (tônica)" },
            { "iv", "Dm7", "menor com sétima", "subdominante" },
            { "v", "Em7", "menor com sétima", "dominante fraco" },
            { "VI", "Fmaj7", "maior com sétima", "subdominante" },
            { "VII", "G7", "dominante", "dominante do III" },
        }),
        aud ({ "A3", "C4", "E4", "G4" }, "Acorde de i (Am7): tônica menor."),
        aud ({ "D4", "F4", "A4", "C5" }, "Acorde de iv (Dm7): subdominante menor."),
        aud ({ "E4", "G4", "B4", "D5" }, "Acorde de v (Em7): dominante fraco, sem sensível."),
        c (
            "Repare que o v (Em7) não tem a sensível (G#). É por isso que a cadência v → i soa fraca: falta a nota que puxa para a tônica."),

        h ("As funções dos acordes"),
        p (
            "Os acordes do campo se agrupam em três funções: tônica (repouso), subdominante (afastamento) e dominante (tensão que pede resolução). Entender as funções é o que permite escolher acordes que fazem sentido e conduzir a música para o repouso."),
        tbl ({ "Função", "Graus no campo menor", "Papel" }, {
            { "Tônica", "i, III", "repouso, estabilidade" },
            { "Subdominante", "ii, iv, VI", "afastamento, cor" },
            { "Dominante", "v, VII", "tensão, movimento de volta" },
        }),
        p (
            "A função não depende do acorde isolado, mas do contexto: um mesmo acorde pode ter papéis diferentes conforme a música. Mas os graus acima dão o mapa básico: i é repouso, iv é afastamento, v é tensão. A música menor mais comum caminha i → iv → v → i, ou i → VI → VII → i."),
        aud ({ "A3", "C4", "E4", "G4", "D4", "F4", "A4", "C5", "E4", "G4", "B4", "D5", "A3", "C4", "E4", "G4" },
             "Cadência i → iv → v → i em Lá menor: Am7, Dm7, Em7, Am7."),

        h ("O campo harmônico menor harmônico"),
        p (
            "Como o v menor não tem a sensível, na prática os compositores usam o acorde de dominante maior com sétima menor, que vem da escala menor harmônica. Esse é o campo harmônico menor harmônico: ele troca o v menor pelo V7 maior, o que dá a força da cadência."),
        tbl ({ "Grau", "Acorde em Lá menor", "Qualidade", "Diferença" }, {
            { "i", "Am7M", "menor com sétima maior", "sétima maior (da harmônica)" },
            { "ii", "Bm7(b5)", "meio-diminuto", "igual ao natural" },
            { "III", "Cmaj7(#5)", "maior com quinta aumentada", "quinta aumentada" },
            { "iv", "Dm7", "menor com sétima", "igual ao natural" },
            { "V", "E7", "dominante", "terça maior (sensível!)" },
            { "VI", "Fmaj7", "maior com sétima", "igual ao natural" },
            { "vii", "G#dim7", "diminuto", "sensível no baixo" },
        }),
        aud ({ "E4", "G#4", "B4", "D5" }, "V7 (E7): o dominante com sensível, que resolve em Am."),
        aud ({ "G#3", "B3", "D4", "F4" }, "vii°7 (G#dim7): diminuto com a sensível no baixo."),
        c (
            "A troca do v menor (Em7) pelo V7 maior (E7) é o que dá força à cadência menor. É a diferença entre o campo menor natural e o menor harmônico."),

        h ("Comparando com o campo maior"),
        p (
            "O campo maior e o campo menor têm a mesma lógica — três funções, sete graus — mas os acordes são diferentes por causa dos graus abaixados. Comparar os dois campos a partir da mesma tônica (Dó maior e Dó menor) é a melhor forma de ouvir a diferença de clima."),
        tbl ({ "Grau", "Campo maior de Dó", "Campo menor de Dó" }, {
            { "i", "Cmaj7 (I)", "Cm7 (i)" },
            { "ii", "Dm7 (ii)", "Dm7(b5) (ii)" },
            { "III", "Em7 (iii)", "Ebmaj7 (III)" },
            { "IV", "Fmaj7 (IV)", "Fm7 (iv)" },
            { "V", "G7 (V)", "Gm7 / G7 (v / V)" },
            { "VI", "Am7 (vi)", "Abmaj7 (VI)" },
            { "VII", "Bm7(b5) (vii)", "Bb7 (VII)" },
        }),
        aud ({ "C4", "E4", "G4", "B4" }, "Campo maior: C7M (I), som alegre e resolvido."),
        aud ({ "C4", "Eb4", "G4", "Bb4" }, "Campo menor: Cm7 (i), som triste e melancólico."),
        c (
            "A diferença entre C7M e Cm7 está só na terça (E contra Eb). Mas essa única nota muda toda a cor da música."),

        h ("Aplicação prática"),
        p (
            "Na prática, você usa o campo harmônico menor para acompanhar uma música em tonalidade menor. Os acordes mais usados são o i, o iv, o V7 e o VI. Uma progressão clássica é i → iv → V7 → i (Am → Dm → E7 → Am), que é a cadência menor por excelência."),
        b ("Progressão clássica: i → iv → V7 → i."),
        b ("Progressão modal: i → VI → VII → i (Am → F → G → Am)."),
        b ("Progressão jazz: ii → V7 → i (Bm7(b5) → E7 → Am7)."),
        aud ({ "A3", "C4", "E4", "D4", "F4", "A4", "E4", "G#4", "B4", "A3", "C4", "E4" },
             "i → iv → V7 → i em Lá menor: a cadência menor por excelência."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é usar o v menor (Em7) onde a música pede o V7 maior (E7): a cadência fica fraca. Outro erro é esquecer o b3 nos acordes menores (tocar C em vez de Cm). O app ajuda porque reconhece as notas dos acordes que você toca e confere se elas formam o acorde do campo."),
        b ("No campo menor harmônico, o dominante é maior (V7), não menor."),
        b ("Confira as terças: o i e o iv são menores (b3)."),
        b ("Toque a progressão devagar e ouça a função de cada acorde."),

        h ("O campo menor melódico"),
        p (
            "Existe ainda um terceiro campo harmônico menor, o melódico, que nasce da escala menor melódica (tópico D). Ele é o campo do jazz moderno: os seus acordes são mais ricos e tensos que os do campo natural e do harmônico. O i é um m7M, o IV é um dominante e o vii é um meio-diminuto. É um campo avançado, mas vale conhecer."),
        tbl ({ "Grau", "Acorde em Lá menor", "Qualidade", "Uso" }, {
            { "i", "Am7M", "menor com sétima maior", "tônica moderna" },
            { "ii", "Bm7", "menor com sétima", "subdominante" },
            { "III", "Cmaj7(#5)", "maior com quinta aumentada", "cor" },
            { "IV", "D7", "dominante", "dominante do i" },
            { "V", "E7", "dominante", "dominante" },
            { "vi", "F#m7(b5)", "meio-diminuto", "subdominante" },
            { "vii", "G#m7(b5)", "meio-diminuto", "sensível" },
        }),
        aud ({ "A3", "C4", "E4", "G#4" }, "i do campo melódico: Am7M, o acorde menor moderno."),
        c (
            "Os três campos menores (natural, harmônico e melódico) compartilham os mesmos graus, mas com qualidades diferentes. Na prática, o campo harmônico do jazz usa o que soa melhor em cada momento."),

        h ("Comparando os três campos menores"),
        p (
            "A tabela abaixo compara os três campos menores a partir da mesma tônica (Lá). Repare que o i muda de sétima (menor, maior ou maior com sétima maior), o v muda de qualidade (menor no natural, maior no harmônico) e alguns graus aparecem com quinta aumentada. Entender essas diferenças é o que permite escolher o campo certo para cada música."),
        tbl ({ "Grau", "Menor natural", "Menor harmônico", "Menor melódico" }, {
            { "i", "Am7", "Am7M", "Am7M" },
            { "ii", "Bm7(b5)", "Bm7(b5)", "Bm7" },
            { "III", "Cmaj7", "Cmaj7(#5)", "Cmaj7(#5)" },
            { "iv", "Dm7", "Dm7", "D7" },
            { "v / V", "Em7", "E7", "E7" },
            { "VI", "Fmaj7", "Fmaj7", "F#m7(b5)" },
            { "VII / vii", "G7", "G#dim7", "G#m7(b5)" },
        }),
        c (
            "Esta tabela é o mapa completo das tonalidades menores. Guarde-a: ela mostra que os três campos menores são variações do mesmo material, com o v/V e o VII/vii mudando de qualidade."),

        h ("Progressões menores para praticar"),
        p (
            "Pratique as progressões abaixo, tocando os acordes no instrumento. Cada uma usa um material diferente do campo menor e serve para você ouvir a diferença entre eles. Comece devagar, com o metrônomo, e só aumente a velocidade quando os acordes estiverem limpos."),
        b ("i → iv → v → i: a cadência do campo menor natural."),
        b ("i → iv → V7 → i: a cadência do campo menor harmônico."),
        b ("ii → V7 → i: a cadência de jazz (Bm7(b5) → E7 → Am7)."),
        b ("i → VI → VII → i: a progressão modal (Am → F → G → Am)."),
        c (
            "Nos exercícios deste tópico, toque essas progressões no instrumento. O app reconhece as notas dos acordes que você toca e confere se elas formam o acorde do campo."),

        h ("Por que o campo menor tem três versões"),
        p (
            "Pode parecer estranho que a tonalidade menor tenha três campos harmônicos. A razão é histórica e prática: a escala menor natural tem o v menor, que não puxa para a tônica; para a cadência, os compositores subiram o sétimo grau (menor harmônica); para a melodia, subiram também o sexto (menor melódica). Cada necessidade gerou um campo. Na prática, a música menor usa os três, escolhendo o que soa melhor em cada momento."),
        b ("Natural: o campo de partida, com o v menor."),
        b ("Harmônico: o campo da cadência, com o V7 maior."),
        b ("Melódico: o campo moderno, com o i m7M."),
        c (
            "Não é preciso escolher um só: a música real mistura os três campos o tempo todo. O importante é saber qual acorde vem de qual campo, para usar a cor certa."),

        h ("Erros comuns ao montar o campo menor"),
        p (
            "O erro mais comum é esquecer que o i, o iv e o v são menores (terça menor) no campo natural, e tocar as terças maiores por hábito da tonalidade maior. Outro erro é usar o v menor onde a música pede o V7 maior. E há quem misture as sétimas dos três campos sem critério, criando acordes que não pertencem a nenhum deles."),
        b ("No campo natural, i, iv e v são menores."),
        b ("No campo harmônico, o dominante é o V7 maior (com sensível)."),
        b ("Não misture as sétimas dos três campos sem intenção."),
        c (
            "O app é um bom conferente: ele reconhece as notas dos acordes que você toca e verifica se elas formam o acorde do campo, em qualquer posição do braço."),

        h ("Resumo do tópico"),
        b ("Campo harmônico = os sete acordes que nascem da escala."),
        b ("Campo menor natural: i, ii, III, iv, v, VI, VII."),
        b ("Campo menor harmônico: i, ii, III+, iv, V7, VI, vii°."),
        b ("Funções: tônica (i, III), subdominante (ii, iv, VI), dominante (v/V, VII)."),
        b ("A cadência menor por excelência é i → iv → V7 → i."),
        b ("Escolha o campo (natural, harmônico ou melódico) pelo som que a música pede."),
        b ("Toque as progressões devagar e ouça a função de cada acorde."),
        part ("m6_partitura_campo_menor", { "A3", "C4", "E4", "D4", "F4", "A4", "E4", "G#4", "B4", "A3", "C4", "E4" },
              "Partitura de i - iv - V7 - i em Lá menor (Am / Dm / E7 / Am). Ouça o que está escrito."),
    };
}

} // namespace cursomusica::content
