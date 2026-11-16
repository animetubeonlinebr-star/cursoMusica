#include "Course/Content/Topics.h"

// Topic 3G — Compassos simples, compostos e formulas incomuns (Modulo 3, Etapa 3).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 3, bloco G).
namespace cursomusica::content
{

std::vector<ContentItem> topic3G()
{
    return {

        p (
            "O compasso organiza os tempos em grupos que se repetem. A fórmula de compasso, escrita no início da partitura, diz quantos tempos há em cada compasso e qual figura vale um tempo. Conhecer as fórmulas é essencial para acompanhar: cada estilo tem os seus compassos favoritos, e saber contá-los é o primeiro passo para tocar no estilo certo."),
        p (
            "Além dos compassos comuns (2/4, 3/4, 4/4), existem os compostos (6/8, 12/8) e as fórmulas incomuns (5/4, 7/8). Cada um agrupa os tempos de forma diferente, e reconhecer esse agrupamento é o que permite tocar sem se perder. Este tópico ensina a ler e a contar cada tipo de compasso."),
        c (
            "Objetivo: reconhecer e contar compassos simples, compostos e incomuns. Contar o agrupamento certo é o que permite acompanhar músicas de estilos diferentes."),

        h ("A formula de compasso"),
        p (
            "A fórmula de compasso é uma fração escrita no início da pauta. O número de cima diz quantos tempos há no compasso; o de baixo diz qual figura vale um tempo. Em 4/4, há quatro tempos e a semínima vale um tempo. Em 3/4, há três tempos. Em 6/8, há seis tempos e a colcheia vale um tempo — mas, na prática, 6/8 é sentido como dois grupos de três."),
        tbl ({ "Formula", "Tempos", "Figura de 1 tempo" }, {
            { "2/4", "2", "seminima" },
            { "3/4", "3", "seminima" },
            { "4/4", "4", "seminima" },
            { "6/8", "6", "colcheia" },
            { "12/8", "12", "colcheia" },
        }),
        b ("O número de cima conta os tempos."),
        b ("O número de baixo diz qual figura vale 1 tempo."),
        b ("4/4 é o compasso mais comum: quatro semínimas por compasso."),
        img ("m3_compassos", "Compassos simples e compostos: quantos tempos e qual figura vale um tempo."),
        c (
            "A barra de compasso separa um grupo de tempos do seguinte. É o que mantém a música organizada e previsível para quem toca e para quem ouve."),

        h ("Compassos simples"),
        p (
            "Compassos simples são aqueles em que o tempo se divide em duas partes iguais. O 2/4, o 3/4 e o 4/4 são simples. No 2/4 (marcha, baião), há dois tempos por compasso. No 3/4 (valsa), há três. No 4/4 (rock, pop, samba), há quatro. Em todos eles, o pulso se subdivide em dois — colcheias e semicolcheias."),
        b ("2/4: dois tempos — marcha, baião, polca."),
        b ("3/4: três tempos — valsa, mazurca."),
        b ("4/4: quatro tempos — pop, rock, samba, jazz."),
        b ("Simples: cada tempo se divide em duas partes iguais."),
        c (
            "No 4/4, os tempos fortes são o 1 e o 3. É esse agrupamento que dá ao compasso a sua sensação de 'ida e volta'."),

        h ("Compassos compostos"),
        p (
            "Compassos compostos são aqueles em que o tempo se divide em três partes iguais. O 6/8, o 9/8 e o 12/8 são compostos. Apesar de a fórmula indicar muitos tempos, na prática eles são sentidos como grupos de três. O 6/8 é sentido como dois grupos de três; o 12/8, como quatro grupos de três. Por isso o compasso composto tem um balanço ternário, muito usado em baladas, baiões e blues lentos."),
        tbl ({ "Formula", "Grupos", "Sensacao" }, {
            { "6/8", "2 grupos de 3", "balada, baião" },
            { "9/8", "3 grupos de 3", "valsa composta" },
            { "12/8", "4 grupos de 3", "blues lento, shuffle" },
        }),
        b ("6/8: dois grupos de três colcheias — conta-se '1 2 3, 4 5 6'."),
        b ("12/8: quatro grupos de três — blues lento, balada."),
        b ("Composto: cada tempo se divide em três partes iguais."),
        aud ({ "C4", "C4", "C4", "D4", "D4", "D4" }, "6/8: dois grupos de três colcheias — o balanço ternário."),
        c (
            "A diferença entre 6/8 e 3/4 está no agrupamento: 6/8 são dois grupos de três (ternário); 3/4 são três tempos de dois (binário). Soam parecidos, mas o pulso é diferente."),

        h ("Formula de compasso incomum"),
        p (
            "Além dos compassos comuns, existem as fórmulas incomuns: 5/4, 7/8, 5/8, 11/8 e outras. Elas não têm um agrupamento fixo — o compositor escolhe como agrupar os tempos em blocos de 2 e 3. Um 5/4 pode ser 3+2 ou 2+3; um 7/8 pode ser 2+2+3, 3+2+2 ou 2+3+2. Reconhecer o agrupamento é o que permite contar e tocar sem se perder."),
        tbl ({ "Formula", "Agrupamentos comuns", "Exemplo" }, {
            { "5/4", "3 + 2 ou 2 + 3", "Take Five" },
            { "7/8", "2 + 2 + 3 ou 3 + 2 + 2", "prog rock, balkan" },
            { "5/8", "3 + 2 ou 2 + 3", "folk, jazz moderno" },
            { "11/8", "3 + 3 + 3 + 2", "jazz moderno" },
        }),
        b ("5/4 = 3 + 2 (conta-se 1 2 3, 1 2)."),
        b ("7/8 = 2 + 2 + 3 (conta-se 1 2, 1 2, 1 2 3)."),
        b ("O agrupamento é uma escolha do compositor, não da fórmula."),
        img ("m3_formulas_incomuns", "Fórmulas de compasso incomuns: agrupar os tempos em blocos de 2 e 3."),
        c (
            "Contar os grupos (ex.: '1 2 3 / 1 2') é o que torna um compasso incomum tocável. Sem agrupar, o músico se perde no meio do compasso."),

        h ("Como contar cada compasso"),
        p (
            "Contar um compasso é marcar os tempos e agrupar conforme a fórmula. Em 4/4, conta-se '1 2 3 4' e acentua-se o 1 e o 3. Em 3/4, conta-se '1 2 3' com acento no 1. Em 6/8, conta-se '1 2 3, 4 5 6' com acento no 1 e no 4. Em 5/4 (3+2), conta-se '1 2 3, 1 2' com acento no 1 e no 4."),
        b ("4/4: 1 2 3 4 (acento no 1 e 3)."),
        b ("3/4: 1 2 3 (acento no 1)."),
        b ("6/8: 1 2 3 4 5 6 (acento no 1 e 4)."),
        b ("5/4 (3+2): 1 2 3 1 2 (acento no 1 e no 4)."),
        c (
            "A contagem com acento é o que dá vida ao compasso. Sem acento, todos os tempos soam iguais e a música perde o seu balanço."),

        h ("Estilos e seus compassos"),
        p (
            "Cada estilo tem os seus compassos favoritos. O rock e o pop usam 4/4 quase sempre. A valsa usa 3/4. O baião e a balada usam 6/8. O blues lento e o shuffle usam 12/8. O jazz moderno explora 5/4 e 7/8. Reconhecer o compasso de um estilo é o primeiro passo para acompanhá-lo de forma convincente."),
        tbl ({ "Estilo", "Compasso", "Sensacao" }, {
            { "Rock / pop", "4/4", "pulsacao binaria" },
            { "Valsa", "3/4", "girando" },
            { "Baiao / balada", "6/8", "balanco ternario" },
            { "Blues lento", "12/8", "shuffle" },
            { "Jazz moderno", "5/4, 7/8", "irregular, surpreendente" },
        }),
        b ("O compasso define o 'chão' rítmico do estilo."),
        b ("Trocar de compasso no meio da música exige atenção extra."),
        b ("Reconhecer o compasso de ouvido acelera o aprendizado de repertório."),

        h ("Erros comuns com compassos"),
        p (
            "Os erros mais comuns são confundir 6/8 com 3/4, perder o agrupamento nas fórmulas incomuns e contar todos os tempos com o mesmo peso. Também é comum o aluno tentar tocar um 7/8 como se fosse 4/4 'esticado', perdendo o agrupamento que dá o caráter ao compasso. Contar os grupos é o que resolve."),
        b ("Confundir 6/8 (ternário) com 3/4 (binário)."),
        b ("Perder o agrupamento no 5/4 e no 7/8."),
        b ("Contar todos os tempos com o mesmo peso."),
        b ("Ignorar o acento do tempo forte."),
        c (
            "Dica: escreva os agrupamentos no papel (3+2, 2+2+3) e conte em voz alta. Ver e falar o agrupamento é o que fixa o compasso."),

        h ("Como praticar compassos"),
        p (
            "Comece pelo 4/4 e pelo 3/4, contando com acento. Depois, passe ao 6/8, cuidando do balanço ternário. Por fim, experimente um 5/4 ou 7/8, agrupando os tempos em blocos de 2 e 3. Sempre com o metrônomo, sempre contando em voz alta. Este módulo usa BPM meta 68, um andamento calmo para consolidar a contagem."),
        b ("4/4 e 3/4: a base, contando com acento."),
        b ("6/8: cuide do balanço ternário."),
        b ("5/4 e 7/8: agrupe em blocos de 2 e 3."),
        b ("Metrônomo e contagem em voz alta sempre."),
        part ("m3_partitura_compasso", { "C4", "D4", "E4", "D4", "C4", "D4" },
              "Partitura em 6/8: agrupe as colcheias em 3 + 3 e conte com acento."),

        h ("Resumo do topico"),
        b ("A fórmula de compasso diz quantos tempos e qual figura vale um tempo."),
        b ("Simples: o tempo se divide em 2. Compostos: divide-se em 3."),
        b ("Fórmulas incomuns (5/4, 7/8) agrupam os tempos em blocos de 2 e 3."),
        b ("Contar com acento é o que dá balanço ao compasso."),
        b ("Cada estilo tem os seus compassos favoritos."),
        c (
            "Nos exercícios, você tocará na grade do metrônomo respeitando o compasso. O app mede o alinhamento e confere se a contagem se manteve estável."),

        h ("Compasso e frase: a quadratura"),
        p (
            "Os compassos não existem isolados: eles se agrupam em frases. Uma frase musical costuma ter quatro compassos, e um período tem duas frases (oito compassos). Essa organização, chamada quadratura, é a base da maior parte da música popular. Entender a quadratura é o que permite ao acompanhante saber onde a música 'respira' e onde ela vira."),
        b ("Frase: normalmente quatro compassos."),
        b ("Período: duas frases (oito compassos)."),
        b ("O fim da frase é onde a música respira ou vira."),
        c (
            "Contar a quadratura ajuda a prever a música: quando você sente a frase de quatro compassos, sabe que uma virada se aproxima."),

        h ("Mudanca de formula no meio da musica"),
        p (
            "Algumas músicas trocam de fórmula no meio: começam em 4/4 e passam para 6/8, ou intercalam um compasso de 2/4 para 'encurtar' a frase. Essa mudança é um recurso de composição que cria surpresa. Para o acompanhante, ela exige atenção: é preciso contar o novo agrupamento desde o primeiro compasso, sem se perder."),
        b ("A fórmula pode mudar no meio da música."),
        b ("Mudanças criam surpresa e movimento."),
        b ("Conte o novo agrupamento desde o primeiro compasso."),
        c (
            "Músicas de prog rock e de música brasileira moderna usam muito a mudança de fórmula. Estudar essas músicas desenvolve a flexibilidade rítmica."),

        h ("Compasso e metrica: o que soa 'certo'"),
        p (
            "Cada compasso tem uma métrica: o padrão de tempos fortes e fracos. Tocar 'na métrica' é respeitar esse padrão. Quando o músico toca fora da métrica — acentuando o tempo errado, por exemplo — o som parece 'errado', mesmo que as notas estejam corretas. A métrica é o que dá a sensação de estar 'no lugar'."),
        b ("Métrica: o padrão de acentos do compasso."),
        b ("Respeitar a métrica faz a música soar 'no lugar'."),
        b ("Tocar fora da métrica soa errado, mesmo com as notas certas."),
        aud ({ "C4", "E4", "G4", "C5", "G4", "E4", "C4", "G3" }, "Compasso 4/4: acentue o tempo 1 e o 3 para sentir a métrica."),

        h ("Como o app avalia o compasso"),
        p (
            "O app avalia se a sua execução caiu na grade do metrônomo, respeitando a subdivisão escolhida. Para cada compasso, ele mede a fração de notas alinhadas (on_grid_ratio). Tocar dentro do compasso certo, com os acentos no lugar, mantém o alinhamento alto. Este módulo tem alvo de 0,77 — dentro da faixa de estudo de 75 a 82%."),
        b ("O app mede o alinhamento à grade (on_grid_ratio)."),
        b ("Alvo deste módulo: 0,77 (faixa de estudo)."),
        b ("Respeitar o compasso mantém o alinhamento alto."),
        c (
            "A faixa de 75–82% existe porque exigir 90% de alinhamento engessa a execução. O pulso fica firme, mas a mão mantém a respiração natural do estilo."),
    };
}

} // namespace cursomusica::content
