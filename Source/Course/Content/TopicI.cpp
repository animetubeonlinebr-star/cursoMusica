#include "Course/Content/Topics.h"

// Topic I — Rítmica: pulsação, figuras e contagem.
// Source: pdf-fraseado-melodico (chapter "Rítmica": figures, values, time
// signature, tempo, subdivision, ties and the rhythmic syllables).
namespace cursomusica::content
{

std::vector<ContentItem> topicI()
{
    return {
        p ("Até aqui você aprendeu o que tocar: notas, acordes, tonalidades. "
           "Rítmica responde a outra pergunta: quando tocar. É a dimensão do "
           "tempo, e é o que faz a música ter movimento, balanço e vida. Sem "
           "ritmo, notas certas soam erradas. O app mede toda a execução na grade "
           "do metrônomo, então este tópico é essencial para passar nos "
           "exercícios."),

        h ("Pulsação: o coração da música"),
        p ("Pulsação, ou tempo, é a batida constante que você sente na música — "
           "aquela que faz o pé bater. É o metrônomo por dentro: um pulso "
           "regular, que se repete sempre no mesmo intervalo. Quando alguém toca "
           "\"no tempo\", está alinhado a essa pulsação."),
        p ("A pulsação é medida em BPM (batidas por minuto). A 60 BPM, há uma "
           "batida por segundo. A 120 BPM, duas batidas por segundo. O BPM é a "
           "velocidade da música: quanto maior, mais rápida."),
        tbl ({ "BPM", "Batidas por segundo", "Sensação" },
             { { "40–60", "menos de 1", "lento, calmo" },
               { "60–80", "1 a 1,3", "moderado, andante" },
               { "80–120", "1,3 a 2", "andante a allegro" },
               { "120–168", "2 a 2,8", "rápido, dançante" },
               { "acima de 168", "mais de 2,8", "muito rápido, presto" } }),
        c ("O ouvido humano organiza a pulsação em grupos. É impossível ouvir "
           "batidas regulares sem agrupá-las mentalmente — geralmente em grupos de "
           "2, 3 ou 4. Esse agrupamento é o compasso, e vem a seguir."),

        h ("Compasso: agrupando os tempos"),
        img ("i_compasso_4_4", "Compasso 4/4: quatro tempos e a subdivisão."),
        p ("Compasso é a divisão da música em grupos de tempos, marcados por "
           "barras de compasso. O primeiro tempo de cada compasso é o mais forte "
           "(o \"tempo forte\"), e é ele que dá a sensação de ciclo."),
        tbl ({ "Compasso", "Tempos por compasso", "Sensação" },
             { { "4/4", "quatro semínimas", "o mais comum; marcha, rock, pop" },
               { "3/4", "três semínimas", "valsa; balanço ternário" },
               { "2/4", "duas semínimas", "marcha, baião" },
               { "6/8", "seis colcheias", "composto; balada, toada" } }),
        p ("O número de cima da fórmula de compasso diz quantos tempos há no "
           "compasso; o de baixo diz qual figura vale um tempo. Em 4/4, são quatro "
           "tempos e a semínima vale um tempo. Em 6/8, são seis tempos e a "
           "colcheia vale um tempo."),
        c ("Você não precisa contar o tempo o tempo todo, mas no início contar em "
           "voz alta ajuda muito. O app usa a grade do metrônomo justamente para "
           "que você sinta os tempos fortes e fracos."),

        h ("As figuras rítmicas e seus valores"),
        img ("i_figuras_ritmicas", "Da semibreve à semicolcheia: cada figura vale metade da anterior."),
        p ("As figuras são símbolos que representam a duração das notas. Cada "
           "figura vale uma fração do tempo, e cada uma é metade da anterior. "
           "Conhecer as figuras é o que permite ler e tocar ritmos."),
        tbl ({ "Figura", "Valor", "Duração relativa", "Sílaba rítmica" },
             { { "Semibreve", "4 tempos", "inteira", "—" },
               { "Mínima", "2 tempos", "metade da semibreve", "TÁ–A" },
               { "Semínima", "1 tempo", "metade da mínima", "TÁ" },
               { "Colcheia", "1/2 tempo", "metade da semínima", "TÁ-KI" },
               { "Semicolcheia", "1/4 tempo", "metade da colcheia", "TA-KI-TA-KI" } }),
        p ("Repare na relação de metades: uma semibreve equivale a duas mínimas, "
           "quatro semínimas, oito colcheias ou dezesseis semicolcheias. Essa "
           "progressão é a base da leitura rítmica."),
        c ("Sílaba rítmica é um recurso de origem indiana: em vez de contar "
           "\"um, dois, três\", você fala sílabas que correspondem à subdivisão. "
           "TÁ para o tempo, TÁ-KI para duas metades, TA-KI-TA-KI para quatro. "
           "Falar a sílaba enquanto toca é o que alinha a execução à grade."),

        h ("Subdivisão: dividindo o tempo"),
        p ("Subdividir é dividir cada tempo em partes menores. Uma semínima é o "
           "tempo inteiro; duas colcheias dividem o tempo em dois; quatro "
           "semicolcheias dividem em quatro. A subdivisão é o que permite tocar "
           "ritmos mais complexos sem perder a pulsação."),
        tbl ({ "Subdivisão", "Sílabas", "Figuras por tempo" },
             { { "sem subdivisão", "TÁ", "1 semínima" },
               { "em 2", "TÁ-KI", "2 colcheias" },
               { "em 3", "TÁ-KI-TA (tercina)", "3 terças" },
               { "em 4", "TA-KI-TA-KI", "4 semicolcheias" } }),
        p ("As tercinas são um caso especial: dividem o tempo em três partes "
           "iguais, em vez de duas ou quatro. São muito comuns em blues, jazz e "
           "MPB, e dão uma sensação de balanço (o famoso \"swing\")."),
        c ("Truque: conte sempre a subdivisão em voz alta enquanto toca. Mesmo "
           "que a música tenha poucas notas, manter a subdivisão interna é o que "
           "faz o tempo ficar estável."),

        h ("Ponto de aumento e ligadura"),
        p ("Dois recursos alteram a duração das notas: o ponto de aumento e a "
           "ligadura. Os dois servem para somar durações, mas de formas "
           "diferentes."),
        b ("Ponto de aumento: um ponto à direita da figura soma metade do valor "
           "dela. Uma semínima pontuada vale 1,5 tempo (1 + 0,5); uma mínima "
           "pontuada vale 3 tempos (2 + 1)."),
        b ("Ligadura: uma curva liga duas notas de mesma altura, somando suas "
           "durações. Uma semínima ligada a outra semínima vale 2 tempos, como uma "
           "mínima."),
        p ("A ligadura também pode atravessar o tempo forte: você mantém a nota "
           "soando de um compasso para o outro. Isso cria o efeito de síncope, "
           "muito usado em samba, funk e jazz."),
        c ("Ponto e ligadura são fáceis de confundir. Lembre-se: o ponto soma "
           "metade do valor da própria figura; a ligadura soma o valor inteiro de "
           "outra nota."),

        h ("Contratempo e síncope"),
        p ("Quando as notas caem fora dos tempos fortes, temos contratempo e "
           "síncope. Esses recursos criam o balanço e a \"malandragem\" de muitos "
           "ritmos brasileiros e do blues."),
        b ("Contratempo: tocar nos tempos fracos (o \"e\" entre os tempos), "
           "deixando os tempos fortes silenciosos."),
        b ("Síncope: deslocar o acento para uma parte fraca do tempo, prolongando "
           "uma nota por cima do tempo forte."),
        p ("O contratempo e a síncope são o que diferenciam um ritmo mecânico de "
           "um ritmo com vida. No início, você toca nos tempos; depois, aprende a "
           "brincar com eles."),
        c ("Ouvido: ouça um samba ou um funk e tente identificar os tempos "
           "fortes. Você percebe que as notas muitas vezes \"fogem\" deles — isso "
           "é a síncope em ação."),

        h ("Andamento: lento, moderado, rápido"),
        p ("O andamento é a velocidade geral da música, definida por palavras "
           "tradicionais ou por BPM. As palavras vêm do italiano e são usadas em "
           "todo o mundo."),
        tbl ({ "Termo", "Andamento", "BPM aproximado" },
             { { "Largo / Adágio", "muito lento", "40–60" },
               { "Andante", "moderado, caminhando", "60–80" },
               { "Moderato", "moderado", "80–100" },
               { "Allegro", "rápido e alegre", "100–140" },
               { "Presto", "muito rápido", "140–180" },
               { "Accelerando / Ritardando", "acelerar / desacelerar",
                 "muda gradualmente" } }),
        p ("No app, o andamento é definido em BPM e você deve tocar alinhado à "
           "grade do metrônomo. No módulo 1, o alvo é tocar devagar e no tempo — "
           "clareza e regularidade valem mais que velocidade."),
        c ("Conselho de ouro: sempre estude devagar primeiro. Um exercício "
           "tocado a 60 BPM limpo vale mais que a 120 BPM desalinhado. A "
           "velocidade vem sozinha quando o movimento está correto."),

        h ("Como contar e tocar na grade"),
        p ("Tocar na grade significa alinhar suas notas à pulsação do metrônomo. "
           "O app mede isso pelo on_grid_ratio: a fração das notas que caíram no "
           "lugar certo. No módulo 1, a meta é 0,75 (75%)."),
        b ("Passo 1: ouça a pulsação do metrônomo por alguns compassos antes de "
           "tocar."),
        b ("Passo 2: conte a subdivisão em voz alta (TÁ, TÁ-KI, TA-KI-TA-KI) "
           "junto com o metrônomo."),
        b ("Passo 3: toque uma única nota nos tempos fortes, sentindo a grade."),
        b ("Passo 4: acrescente as subdivisões, mantendo a contagem."),
        p ("O erro mais comum do iniciante é acelerar nos trechos fáceis e "
           "desacelerar nos difíceis. O metrônomo é o juiz imparcial: ele não "
           "acelera nem desacelera. Tocar com ele revela e corrige essa "
           "irregularidade."),
        c ("Dica: se você erra sempre no mesmo ponto, o problema pode ser técnico "
           "(um movimento difícil) e não rítmico. Reduza o BPM até conseguir "
           "tocar aquele ponto sem erro, depois suba de novo."),

        h ("Rítmica aplicada à guitarra"),
        p ("Na guitarra, a mão direita (a que toca as cordas) é a guardiã do "
           "ritmo. Ela mantém o movimento constante, mesmo quando não toca uma "
           "nota — é o chamado \"movimento contínuo\"."),
        b ("Mão direita em pêndulo: movimentos alternados (para baixo e para "
           "cima) mantêm o tempo, mesmo nos silêncios."),
        b ("Levadas: padrões de baixo/cima que definem o ritmo do acompanhamento."),
        b ("Abafamento: a mão que não toca pode abafar as cordas para criar "
           "silêncios precisos."),
        c ("Exercício clássico: toque a 6ª corda solta em semínimas, contando "
           "TÁ a cada tempo, a 60 BPM. Depois em colcheias (TÁ-KI) e depois em "
           "semicolcheias (TA-KI-TA-KI). É exatamente o exercício EX-1.I.1."),

        h ("Fórmula de compasso em detalhe"),
        p ("A fórmula de compasso aparece no início da música, como duas "
           "números empilhados (por exemplo, 4 sobre 4). Entender os dois números "
           "evita confusão na hora de ler."),
        tbl ({ "Fórmula", "Número de cima", "Número de baixo", "Exemplo prático" },
             { { "4/4", "4 tempos", "semínima = 1 tempo", "rock, pop, marcha" },
               { "3/4", "3 tempos", "semínima = 1 tempo", "valsa" },
               { "2/4", "2 tempos", "semínima = 1 tempo", "baião, marchinha" },
               { "6/8", "6 tempos", "colcheia = 1 tempo", "toada, balada" } }),
        p ("Compassos simples têm subdivisão binária (o tempo se divide em dois); "
           "compassos compostos têm subdivisão ternária (o tempo se divide em "
           "três). O 6/8 é composto: você sente dois grupos de três colcheias, não "
           "seis batidas isoladas."),
        c ("Dica de leitura: em 6/8, conte \"UM-dois-três, DOIS-dois-três\", "
           "sentindo dois pulsos por compasso, cada um dividido em três. É "
           "diferente de contar seis batidas soltas."),

        h ("Dinâmica e articulação: a expressão do ritmo"),
        p ("Ritmo não é só quando tocar, mas também como tocar. A intensidade "
           "(dinâmica) e a forma de atacar a nota (articulação) dão expressão à "
           "música."),
        b ("Dinâmica: forte (f) e piano (p) indicam volume. Crescendo e "
           "diminuendo indicam aumento e diminuição gradual."),
        b ("Acento: uma nota tocada com mais força, marcando um ponto do ritmo."),
        b ("Staccato: nota curta e destacada; legato: notas ligadas e fluidas."),
        b ("Palm mute: abafar as cordas com a mão direita, criando som percussivo "
           "(muito usado no rock e no metal)."),
        p ("No app, o pattern PTN-R-PALM (pedal point abafado + power chords) "
           "trabalha justamente a articulação do palm mute — seu primeiro contato "
           "com o controle rítmico da mão direita."),
        c ("Tocar sempre com a mesma intensidade é monótono. Mesmo num exercício "
           "simples, procure variar a força para dar forma à frase."),

        h ("Resumo do tópico I"),
        tbl ({ "Ideia", "O que fixar" },
             { { "Pulsação", "batida constante, medida em BPM" },
               { "Compasso", "grupo de tempos (4/4, 3/4, 6/8)" },
               { "Figuras", "semibreve a semicolcheia, cada uma metade da anterior" },
               { "Subdivisão", "dividir o tempo em 2, 3 ou 4 partes" },
               { "Sílabas", "TÁ, TÁ-KI, TA-KI-TA-KI" },
               { "Ponto/ligadura", "somam durações" },
               { "Síncope", "deslocar o acento para fora do tempo forte" },
               { "Andamento", "velocidade (adágio a presto)" },
               { "Grade", "on_grid_ratio ≥ 0,75 no módulo 1" } }),

        h ("Como estudar o tópico I na prática"),
        p ("Ritmo é hábito corporal: só se aprende praticando com o metrônomo. "
           "Faça destes exercícios uma rotina."),
        b ("Ouça o metrônomo e bata o pé no tempo por um minuto, sem tocar."),
        b ("Conte TÁ, TÁ-KI e TA-KI-TA-KI em voz alta junto com o metrônomo."),
        b ("Toque uma nota só em semínimas, depois colcheias, depois "
           "semicolcheias, sempre a 60 BPM."),
        b ("Toque um padrão com pausa (toque, silêncio, toque) para treinar o "
           "tempo interno."),
        b ("Aumente o BPM apenas quando conseguir tocar limpo e alinhado."),
        c ("Meta do tópico: tocar em semínimas e colcheias alinhado ao metrônomo, "
           "contando em voz alta, com on_grid_ratio ≥ 0,75. Esse é o requisito "
           "rítmico do módulo 1."),
    };
}

} // namespace cursomusica::content
