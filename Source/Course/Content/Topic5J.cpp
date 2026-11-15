#include "Course/Content/Topics.h"

// Topic 5J — Harmonização da escala maior (Módulo 5, Etapa 5).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 5, bloco J).
namespace cursomusica::content
{

std::vector<ContentItem> topic5J()
{
    return {

        p (
            "Harmonizar a escala maior é transformar cada uma das sete notas da escala em um acorde. É o passo que fecha este módulo: você pega a escala que estudou no tópico A, empilha as notas em terças sobre cada grau e obtém os sete acordes do campo harmônico. Esse é o gesto que liga toda a teoria do módulo à prática de acompanhar e compor."),
        p (
            "Neste tópico você aprende o procedimento completo da harmonização, vê o resultado em várias tonalidades e entende por que as qualidades dos acordes caem sempre nos mesmos graus. Ao final, você terá o mapa completo: escala → acordes → funções → cadências."),

        h ("O que é harmonizar a escala"),
        p (
            "Harmonizar é acrescentar acordes a uma escala — ou seja, construir, sobre cada grau, um acorde que use as notas da própria escala. O resultado é o campo harmônico: uma família de sete acordes que pertencem todos à mesma tonalidade. Harmonizar a escala maior é, portanto, o processo que gera o campo harmônico que você estudou no tópico B."),
        p (
            "A ideia é simples e poderosa: em vez de escolher acordes aleatoriamente, você os deriva da escala. Como todos usam as mesmas notas, todos soam coerentes entre si. É esse princípio que faz com que qualquer progressão montada com acordes do campo harmônico soe 'certa' — mesmo antes de você saber por quê."),
        b ("Harmonizar = construir um acorde sobre cada grau da escala."),
        b ("Os acordes usam apenas as notas da escala (nada de fora)."),
        b ("O resultado é o campo harmônico da tonalidade."),
        img ("m5_harmonizacao", "A harmonização da escala maior: cada grau da escala se transforma em um acorde do campo harmônico."),

        h ("O procedimento passo a passo"),
        p (
            "O procedimento é sempre o mesmo. Primeiro, escreva a escala maior da tonalidade escolhida. Depois, para cada grau, empilhe a nota do grau, a nota dois graus acima e a nota quatro graus acima — todas dentro da escala. Esse empilhamento de terças produz uma tríade, e a qualidade da tríade (maior, menor ou diminuto) depende das distâncias que aparecem."),
        p (
            "Fazendo isso em Dó maior: sobre Dó, empilha-se Dó–Mi–Sol (maior); sobre Ré, Ré–Fá–Lá (menor); sobre Mi, Mi–Sol–Si (menor); sobre Fá, Fá–Lá–Dó (maior); sobre Sol, Sol–Si–Ré (maior); sobre Lá, Lá–Dó–Mi (menor); sobre Si, Si–Ré–Fá (diminuto). Está pronto o campo harmônico."),
        tbl ({ "Grau", "Empilhamento", "Tríade", "Qualidade" }, {
            { "I", "Dó – Mi – Sol", "C", "maior" },
            { "ii", "Ré – Fá – Lá", "Dm", "menor" },
            { "iii", "Mi – Sol – Si", "Em", "menor" },
            { "IV", "Fá – Lá – Dó", "F", "maior" },
            { "V", "Sol – Si – Ré", "G", "maior" },
            { "vi", "Lá – Dó – Mi", "Am", "menor" },
            { "vii°", "Si – Ré – Fá", "Bdim", "diminuto" },
        }),
        c (
            "O empilhamento é sempre de dois em dois graus: 1–3–5, 2–4–6, 3–5–7 e assim por diante, voltando ao começo da escala quando necessário. Esse é o gesto que transforma escala em harmonia."),
        aud ({ "C4", "E4", "G4", "D4", "F4", "A4", "E4", "G4", "B4", "F4", "A4", "C5", "G4", "B4", "D5" },
             "Harmonização de Dó maior: os cinco primeiros acordes do campo, arpejados em sequência."),
        part ("m5_partitura_campo", { "C4", "E4", "G4", "D4", "F4", "A4", "E4", "G4", "B4" },
              "Partitura da harmonização: C – Dm – Em, os três primeiros graus da escala harmonizados."),

        h ("Por que as qualidades se repetem"),
        p (
            "As qualidades dos acordes harmonizados caem sempre nos mesmos graus porque os semitons da escala maior estão sempre nas mesmas posições relativas. O semitom entre os graus 3–4 e entre 7–8 faz com que os empilhamentos sobre certos graus contenham terças menores, e sobre outros, terças maiores. Como o padrão da escala é fixo, o padrão das qualidades também é."),
        p (
            "Esse é o motivo pelo qual você pode decorar apenas uma coisa — o padrão I – ii – iii – IV – V – vi – vii° — e aplicá-lo a qualquer tonalidade. Não é uma regra arbitrária: é uma consequência matemática da escala maior. Entender isso elimina a necessidade de memorizar o campo harmônico de cada tom."),
        b ("Os semitons da escala caem sempre nos graus 3–4 e 7–8."),
        b ("Isso faz as qualidades se repetirem: M – m – m – M – M – m – d."),
        b ("Como o padrão da escala é fixo, o padrão das qualidades também é."),

        h ("Harmonização em outras tonalidades"),
        p (
            "Aplicar a harmonização em outras tonalidades é só uma questão de trocar as notas mantendo o padrão. Em Sol maior, os acordes são G – Am – Bm – C – D – Em – F#dim; em Fá maior, F – Gm – Am – Bb – C – Dm – Edim. As qualidades seguem sempre a mesma ordem, só mudam os nomes dos acordes."),
        p (
            "É por isso que a harmonização é uma ferramenta de transposição tão poderosa. Se você sabe que uma música usa I – vi – ii – V em Dó, automaticamente sabe que em Sol ela usa G – Em – Am – D. Você não precisa recalcular nada: o padrão de graus carrega a informação."),
        tbl ({ "Tonalidade", "I", "ii", "iii", "IV", "V", "vi", "vii°" }, {
            { "Dó maior", "C", "Dm", "Em", "F", "G", "Am", "Bdim" },
            { "Sol maior", "G", "Am", "Bm", "C", "D", "Em", "F#dim" },
            { "Ré maior", "D", "Em", "F#m", "G", "A", "Bm", "C#dim" },
            { "Fá maior", "F", "Gm", "Am", "Bb", "C", "Dm", "Edim" },
        }),
        aud ({ "G3", "B3", "D4", "A3", "C4", "E4", "B3", "D4", "F#4" },
             "Harmonização de Sol maior: G – Am – Bm, o mesmo padrão em outro tom."),

        h ("Harmonização e acompanhamento"),
        p (
            "Na prática do acompanhamento, a harmonização é o que permite escolher acordes para uma melodia. Se você tem uma melodia em Dó maior e quer acompanhá-la, procura, em cada trecho, o acorde do campo harmônico que contém as notas daquele trecho. Assim, a harmonia nasce da melodia e da escala, e não de tentativa e erro."),
        p (
            "É também o que permite criar variações harmônicas. A mesma melodia pode ser harmonizada com I – IV – V – I ou com I – vi – ii – V, porque ambos os conjuntos vêm do mesmo campo. A escolha depende da emoção que você quer — e, para tomar essa decisão com consciência, você precisa conhecer a harmonização da escala."),
        b ("Escolha, para cada trecho da melodia, um acorde do campo que contenha as notas."),
        b ("Harmonizações diferentes da mesma melodia dão climas diferentes."),
        b ("Toda a harmonia nasce da escala harmonizada."),
        img ("m5_harmonizacao_braco", "A escala harmonizada no braço: as tríades do campo em uma região, prontas para acompanhar."),

        h ("Fechando o módulo"),
        p (
            "Com a harmonização, o módulo fecha o ciclo completo da harmonia funcional: você parte da escala maior, harmoniza cada grau, identifica as funções (tônica, subdominante, dominante), reconhece os relativos, lê as armaduras e monta cadências e progressões. Esse conjunto é a base de tudo o que vem depois — os modos, os campos menores e as substituições harmônicas."),
        p (
            "O gate deste módulo cobra exatamente isso: tocar uma progressão do campo maior na grade do metrônomo, com os acordes reconhecidos pelo app. Não é um exercício isolado: é a prova de que você sabe construir e executar a harmonia de uma tonalidade. Ao passar, você está pronto para os módulos de II–V–I."),
        b ("Harmonizar fecha o ciclo: escala → acordes → funções → cadências."),
        b ("O gate cobra a progressão do campo maior na grade."),
        b ("Esse é o alicerce dos módulos de II–V–I e do repertório."),
        aud ({ "C4", "E4", "G4", "F4", "A4", "C5", "G4", "B4", "D5", "C5", "E5", "G5" },
             "I – IV – V – I: a progressão do gate, com as três funções em sequência."),
        part ("m5_partitura_iv_v_i", { "F4", "A4", "C5", "G4", "B4", "D5", "C5", "E5", "G5" },
              "Partitura da progressão do gate: IV – V – I, a resolução completa da harmonia funcional."),

        h ("Harmonização com tétrades"),
        p (
            "A harmonização básica usa tríades (três notas), mas você pode ir além e acrescentar a sétima a cada acorde, formando tétrades. Em Dó maior, isso dá C7M – Dm7 – Em7 – F7M – G7 – Am7 – Bm7(b5). As tétrades adicionam cor e são a base da harmonia do jazz e da MPB, mas o princípio é o mesmo: as notas continuam vindo da escala harmonizada."),
        p (
            "O padrão das tétrades também é fixo: I e IV são sétima maior, ii, iii e vi são sétima menor, V é sétima dominante e vii é meio-diminuto. Essa extensão mostra como a harmonização é um processo que pode crescer em complexidade sem perder a lógica original — tudo continua sendo derivado da escala maior."),
        b ("Tríades = três notas; tétrades = três notas + sétima."),
        b ("Em Dó maior: C7M – Dm7 – Em7 – F7M – G7 – Am7 – Bm7(b5)."),
        b ("As tétrades dão cor, mas vêm da mesma escala harmonizada."),
        aud ({ "C4", "E4", "G4", "B4", "D4", "F4", "A4", "C5", "G4", "B4", "D5", "F5" },
             "Tétrades do campo de Dó: C7M, Dm7 e G7, com as sétimas que dão a cor."),

        h ("Harmonização e composição"),
        p (
            "Quando você compõe, a harmonização da escala é o seu ponto de partida. Escolhida a tonalidade, você tem à disposição os sete acordes do campo — e pode combiná-los em progressões que criam os climas que você quer. Quer algo resolvido? Use I – IV – V – I. Quer algo circular? Use I – V – vi – IV. Cada combinação tem um efeito."),
        p (
            "A grande vantagem de compor a partir da harmonização é que você nunca fica 'sem opções'. Se a melodia que você tem usa uma certa nota, existe sempre um acorde do campo que a contém. Aprender a escolher esse acorde é o que transforma uma melodia solta em uma música com harmonia coerente."),
        b ("A harmonização dá o conjunto de acordes para compor."),
        b ("Cada progressão combina os acordes com um efeito diferente."),
        b ("Para cada nota da melodia existe um acorde do campo que a contém."),
        c (
            "A harmonização é, ao mesmo tempo, o fim da teoria e o começo da prática. É a ponte entre entender a escala e usá-la para fazer música — e é por isso que ela fecha este módulo."),

        h ("Harmonização e o gate do módulo"),
        p (
            "A harmonização da escala é o material do gate deste módulo. O desafio final pede que você toque uma progressão do campo maior — construída com as funções que você estudou — na grade do metrônomo, e o app confere os acordes reconhecidos. É a prova prática de que você sabe derivar e executar a harmonia de uma tonalidade."),
        p (
            "Para se preparar para o gate, pratique a progressão IV – V – I devagar, acorde por acorde, até que a execução fique automática. Só depois acrescente a grade do metrônomo. A meta de andamento do módulo é 76 BPM, e a meta de alinhamento é 0,79 — ou seja, a maioria das notas precisa cair na grade. Treinar a progressão sem o metrônomo primeiro, e depois com ele, é o caminho mais eficiente."),
        b ("O gate cobra a progressão do campo maior na grade."),
        b ("Pratique acorde por acorde antes de acrescentar o metrônomo."),
        b ("BPM meta 76 e alinhamento 0,79 para fechar o módulo."),
        img ("m5_progressao_padrao", "A progressão do gate no braço: I – IV – V – I, com as funções de cada acorde."),

        h ("Conclusão do módulo"),
        p (
            "Ao terminar este módulo, você percorreu o caminho completo da harmonia funcional: da escala maior aos acordes, dos acordes às funções, das funções às cadências, e das cadências à harmonização. Esse conjunto é a base de tudo o que vem depois no curso — os módulos de II–V–I, os campos harmônicos menores, as substituições e o repertório."),
        p (
            "Mais importante do que decorar os acordes de cada tonalidade é entender a lógica por trás deles: o padrão I – ii – iii – IV – V – vi – vii° vem da escala maior, e as funções de tônica, subdominante e dominante vêm das relações entre esses acordes. Uma vez que essa lógica está clara, você pode aplicá-la em qualquer tom, em qualquer estilo, para analisar, acompanhar e compor."),
        b ("O módulo cobre escala, campo harmônico, funções, cadências e harmonização."),
        b ("A lógica é mais importante que a memorização."),
        b ("Esse é o alicerce dos próximos módulos e do repertório."),
        aud ({ "C4", "E4", "G4", "F4", "A4", "C5", "G4", "B4", "D5", "C5", "E5", "G5" },
             "A progressão completa do módulo: I – IV – V – I, do repouso à resolução."),

        h ("Resumo do tópico"),
        b ("Harmonizar a escala é construir um acorde sobre cada grau."),
        b ("O empilhamento de terças (1–3–5) produz as tríades do campo."),
        b ("As qualidades seguem I – ii – iii – IV – V – vi – vii° em qualquer tom."),
        b ("A harmonização é a base do acompanhamento e da transposição."),
        b ("Fechar o módulo é saber construir e tocar a harmonia de uma tonalidade."),
        c (
            "Nos exercícios deste tópico, toque as tríades harmonizadas e a progressão do gate. O app reconhece as notas e confere se a harmonia está correta na grade do metrônomo."),
    };
}

} // namespace cursomusica::content
