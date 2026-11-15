#include "Course/Content/Topics.h"

// Topic 7C — Outros empilhamentos (Módulo 7, Etapa 7).
// Fonte de verdade do texto: docs/MUSIC.md §7.2 (bloco C).
namespace cursomusica::content
{

std::vector<ContentItem> topic7C()
{
    return {

        p (
            "Terças e quartas são os empilhamentos mais usados, mas não são os únicos. A música moderna explora empilhamentos de quintas, de segundas, de sétimas e até combinações mistas. Cada escolha muda radicalmente a sonoridade do acorde e abre um leque de cores que você pode usar para compor, acompanhar e improvisar."),
        p (
            "Neste tópico você conhece os outros empilhamentos: o de quintas (base do power chord e dos acordes abertos), o de segundas (som denso e moderno, cheio de tensão) e os empilhamentos mistos, em que você escolhe cada intervalo. O objetivo não é decorar todos, mas entender o princípio: a distância que você escolhe entre as notas é a sonoridade que você obtém."),

        h ("Empilhamento de quintas"),
        p (
            "Empilhar quintas é somar intervalos de quinta justa (7 semitons). Em Dó, isso dá Dó–Sol–Ré–Lá. É um empilhamento forte, aberto, muito estável, e é exatamente a base do power chord, o acorde de duas notas (tônica e quinta) que sustenta o rock e o metal."),
        tbl ({ "Nota", "Semitons a partir da tônica (Dó)", "Grau" }, {
            { "Dó", "0", "1" },
            { "Sol", "7", "5" },
            { "Ré", "14 (= 2)", "9 (oitava acima)" },
            { "Lá", "21 (= 9)", "13 (duas oitavas acima)" },
        }),
        p (
            "Como o empilhamento de quintas não inclui a terça, o acorde também é ambíguo quanto a maior/menor — e é isso que faz o power chord funcionar tão bem no rock: ele pode ser usado sobre harmonias maiores ou menores sem soar “errado”."),
        aud ({ "C3", "G3", "C4" }, "Power chord de Dó: tônica e quinta, o som forte e aberto do rock."),
        aud ({ "C3", "G3", "D4", "A4" }, "Empilhamento de quintas (Dó–Sol–Ré–Lá): aberto e ressonante."),
        img ("m7_outros_empilhamentos", "Empilhamentos de quintas, segundas e mistos: cada distância, uma cor."),

        h ("Empilhamento de segundas"),
        p (
            "Empilhar segundas é somar intervalos de segunda (1 ou 2 semitons). O resultado é um acorde denso, cheio de atrito, com um som moderno e tenso. Empilhamentos de segundas aparecem em música contemporânea, trilhas e jazz moderno, e são um recurso poderoso quando você quer tensão sem resolver."),
        tbl ({ "Empilhamento", "Semitons", "Sensação" }, {
            { "segundas maiores (Dó–Ré–Mi)", "0, 2, 4", "aglomerado aberto" },
            { "segundas menores (Dó–Réb–Ré)", "0, 1, 2", "aglomerado denso, tenso" },
            { "segundas mistas", "0, 2, 3", "cluster com cor" },
        }),
        b ("Cluster: um grupo de notas vizinhas tocadas juntas."),
        b ("Quanto mais próximas as notas, mais tenso o som."),
        b ("Empilhamentos de segundas raramente resolvem: eles permanecem tensos."),
        c (
            "Cuidado com a densidade: empilhar muitas segundas na região grave deixa o som “embolado”. Use clusters nas regiões médias e agudas, onde o ouvido distingue as notas."),

        h ("Empilhamento de sétimas"),
        p (
            "Empilhar sétimas é somar intervalos de sétima. É um empilhamento menos comum, mas muito expressivo: gera acordes com grande abertura e um som flutuante. Aparece em voicings de jazz e em composições que buscam um som “amplo”."),
        b ("Sétimas maiores empilhadas dão um som brilhante e suspenso."),
        b ("Sétimas menores empilhadas dão um som mais escuro."),
        b ("O empilhamento de sétimas é raro, mas ótimo para efeitos de cor."),

        h ("Empilhamentos mistos"),
        p (
            "Os empilhamentos mistos combinam intervalos diferentes: uma quarta seguida de uma terça, uma quinta seguida de uma segunda, e assim por diante. É o território dos voicings modernos, em que cada acorde é desenhado sob medida para o contexto. O princípio é simples: você escolhe as notas pela cor que quer ouvir, não pela regra fixa."),
        tbl ({ "Combinação", "Exemplo em Dó", "Uso" }, {
            { "quarta + terça", "Dó–Fá–Lá", "acorde suspenso com cor" },
            { "quinta + segunda", "Dó–Sol–Ré", "som aberto e moderno" },
            { "terça + quarta", "Dó–Mi–Lá–Ré", "tensão controlada" },
            { "quinta + quarta", "Dó–Sol–Dó–Fá", "base suspensa" },
        }),
        b ("Não há fórmula fixa: o voicing é desenhado caso a caso."),
        b ("Ouça a combinação antes de fixá-la em uma música."),
        b ("Empilhamentos mistos são a base dos voicings de jazz moderno."),
        aud ({ "C4", "F4", "A4" }, "Empilhamento misto (quarta + terça): Dó–Fá–Lá, suspenso com cor."),

        h ("Escolher o empilhamento é escolher a cor"),
        p (
            "Depois de conhecer os empilhamentos, você percebe que a harmonia é uma questão de escolha. O mesmo centro (por exemplo, Dó) pode ser harmonizado de dezenas de formas, cada uma com uma sonoridade própria. O empilhamento de terças define maior/menor; o de quartas suspende; o de quintas abre; o de segundas tensiona; os mistos pintam com precisão."),
        b ("Quer definição? Empilhe terças."),
        b ("Quer suspensão? Empilhe quartas."),
        b ("Quer força? Empilhe quintas."),
        b ("Quer tensão? Empilhe segundas."),
        b ("Quer cor sob medida? Combine intervalos (mistos)."),

        h ("Como praticar os empilhamentos"),
        p (
            "Pratique construindo o mesmo acorde com empilhamentos diferentes e ouvindo a diferença. Toque Dó com terças, com quartas, com quintas e com segundas, um depois do outro, e sinta como a cor muda sem mudar a tônica. Esse exercício de escuta é o que desenvolve o ouvido harmônico."),
        b ("Toque o mesmo centro com cada empilhamento."),
        b ("Compare as sensações: definido, suspenso, aberto, tenso."),
        b ("Escolha o empilhamento que combina com a intenção musical."),
        c (
            "Nos exercícios deste tópico, o app reconhece as notas que você toca e confere o conjunto. Você pode tocar o empilhamento em qualquer posição do braço; o que importa é o resultado sonoro."),

        h ("Empilhamentos e o registro (altura)"),
        p (
            "A mesma combinação de intervalos soa muito diferente conforme a região do braço em que você toca. Um cluster de segundas no grave soa pesado e confuso; nas cordas agudas, soa delicado e moderno. Aprender a escolher o registro é tão importante quanto escolher o empilhamento."),
        b ("Grave: sons densos pedem intervalos largos (quartas, quintas)."),
        b ("Médio: os empilhamentos fechados funcionam bem."),
        b ("Agudo: clusters de segundas ficam brilhantes e claros."),

        h ("Empilhamentos na composição"),
        p (
            "Compositores usam empilhamentos para criar a atmosfera de uma música. Uma balada pode começar com acordes de terça (claros) e evoluir para acordes quartais (suspensos) e clusters (tensos) no clímax. Entender os empilhamentos dá a você um vocabulário de cores para conduzir a emoção da música."),
        b ("Introdução clara: empilhamentos de terça."),
        b ("Desenvolvimento suspenso: quartais."),
        b ("Clímax tenso: clusters e mistos."),

        h ("Erros comuns"),
        p (
            "O erro mais frequente é empilhar muitos intervalos pequenos no grave, criando um som confuso. Outro é usar um empilhamento tenso onde a música pede repouso, ou o contrário. A escolha do empilhamento deve servir à intenção musical, não à vontade de mostrar virtuosismo."),
        b ("Cuidado com clusters no registro grave."),
        b ("Combine o empilhamento com o momento da música."),
        b ("Ouça sempre antes de decidir."),

        h ("Empilhamentos e a função do acorde"),
        p (
            "O empilhamento escolhido também influencia a função percebida do acorde. Um empilhamento de terças deixa a função clara (tônica, subdominante, dominante); um empilhamento de quartas embaralha a função e deixa o acorde suspenso. Entender essa relação ajuda a escolher o empilhamento conforme a função que você quer na música."),
        b ("Terças: função clara, harmonia tonal."),
        b ("Quartas: função ambígua, harmonia modal."),
        b ("Quintas: função neutra, boa para bases fortes."),
        b ("Segundas: função tensa, boa para clímax."),

        h ("Empilhamentos e o estilo"),
        p (
            "Cada estilo musical favorece certos empilhamentos. O rock e o metal usam muito o empilhamento de quintas (power chords); o jazz usa terças e quartas; a música contemporânea explora segundas e mistos. Conhecer o vocabulário de cada estilo é o que permite soar autêntico em cada contexto."),
        tbl ({ "Estilo", "Empilhamento predominante", "Som" }, {
            { "rock / metal", "quintas", "forte, aberto" },
            { "jazz", "terças e quartas", "definido e suspenso" },
            { "bossa / MPB", "terças e quartas", "aberto e sofisticado" },
            { "contemporâneo", "segundas e mistos", "denso e moderno" },
        }),

        h ("Empilhamentos e a densidade do acorde"),
        p (
            "A quantidade de notas e a proximidade entre elas definem a densidade do acorde. Um empilhamento de quintas é aberto e leve; um de segundas é fechado e denso. Aprender a controlar a densidade é o que permite usar a harmonia como parte do arranjo: um trecho esparso pede acordes abertos; um clímax pede densidade."),
        b ("Poucas notas e intervalos largos: som aberto e leve."),
        b ("Muitas notas e intervalos curtos: som denso e tenso."),
        b ("Controle a densidade conforme o momento da música."),

        h ("Combinando empilhamentos em uma música"),
        p (
            "Em uma música, você pode combinar empilhamentos diferentes em seções diferentes, criando um arco de tensão. Comece com acordes de terça (claros), passe para quartais (suspensos) no desenvolvimento e use clusters (tensos) no clímax. Esse uso consciente dos empilhamentos é o que dá forma à música."),
        b ("Seções claras: terças."),
        b ("Seções suspensas: quartas."),
        b ("Clímax: segundas e mistos."),

        h ("Empilhamentos como exercício de ouvido"),
        p (
            "Tocar o mesmo centro com empilhamentos diferentes é um excelente exercício de ouvido. Você aprende a reconhecer a cor de cada empilhamento e, com o tempo, identifica de ouvido qual empilhamento está sendo usado. Esse treino é valioso para transcrever músicas e para compor com intenção."),
        b ("Toque o centro com cada empilhamento em sequência."),
        b ("Nomeie a cor de cada um de memória."),
        b ("Depois, ouça uma música e tente identificar o empilhamento."),

        h ("Empilhamentos e a intenção musical"),
        p (
            "No fim, a escolha do empilhamento é uma escolha de intenção. Antes de tocar, pergunte-se que sensação você quer: definição, suspensão, força ou tensão. A resposta indica o empilhamento. Assim, a teoria deixa de ser uma lista de regras e passa a ser um vocabulário a serviço da música que você quer fazer."),
        b ("Definição: terças. Suspensão: quartas."),
        b ("Força: quintas. Tensão: segundas."),
        b ("Cor sob medida: empilhamentos mistos."),

        h ("Resumo do tópico"),
        b ("Além de terças e quartas, existem empilhamentos de quintas, segundas, sétimas e mistos."),
        b ("Quintas dão força e abertura; segundas dão tensão; mistos dão cor sob medida."),
        b ("O empilhamento escolhido define a sonoridade do acorde."),
        b ("O registro em que você toca também muda a cor."),
        b ("Escolher o empilhamento é escolher a intenção musical."),
        part ("m7_partitura_outros", { "C3", "G3", "D4", "A4" },
              "Partitura: empilhamento de quintas (Dó–Sol–Ré–Lá). Ouça o som aberto e ressonante."),
    };
}

} // namespace cursomusica::content
