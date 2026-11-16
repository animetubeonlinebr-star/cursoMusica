#include "Course/Content/Topics.h"

// Topic 8B — Dominantes secundários (Módulo 8, Etapa 8).
// Fonte de verdade do texto: .agents/agents/mc-modulo-8.md (Etapa 8, tópico B).
namespace cursomusica::content
{

std::vector<ContentItem> topic8B()
{
    return {

        p (
            "O campo harmônico maior tem um único dominante natural, o V7. Mas a música real usa dominantes em quase todos os graus, apontando para alvos diferentes da tônica. Esses são os dominantes secundários: acordes de sétima dominante que resolvem em um grau que não é o I. Eles são a ferramenta mais usada para dar movimento e riqueza a uma progressão, e aparecem o tempo todo no jazz, na bossa nova e na MPB."),
        p (
            "A ideia é simples: qualquer grau de uma tonalidade pode virar, temporariamente, uma tônica. Para isso, colocamos antes dele o seu próprio V7. A notação V7/x lê-se \"o dominante do grau x\". Assim, V7/ii é o dominante do segundo grau, V7/V é o dominante do quinto grau, e assim por diante."),
        c (
            "Objetivo do tópico: entender o que são dominantes secundários, como se constroem e como reconhecê-los pela presença de uma nota estranha ao campo harmônico."),

        h ("O que é um dominante secundário"),
        p (
            "Um dominante secundário é um acorde de sétima dominante que resolve em um acorde que não é a tônica. Ele funciona como uma tônica temporária: cria uma pequena modulação que dura um compasso ou menos e volta para o tom principal. O efeito é de movimento, de virada, de caminho que se abre."),
        b ("V7/x significa \"o dominante do acorde x\"."),
        b ("Ele resolve em x, criando um centro temporário."),
        b ("Sua função é dar movimento sem mudar de tom definitivamente."),
        p (
            "O sinal de que um dominante secundário apareceu é a presença de uma nota que não pertence ao campo harmônico. Em Dó maior, o campo tem as notas Dó, Ré, Mi, Fá, Sol, Lá e Si. Se você encontra um Sol# em um acorde que resolve em Lá menor (Am), esse Sol# é a sensível de Lá — o acorde é E7, o V7/vi."),

        h ("Como construir um dominante secundário"),
        p (
            "Para construir o dominante de um alvo, siga três passos. Primeiro, identifique a fundamental do alvo. Segundo, suba uma quinta justa (sete semitons) a partir dessa fundamental: essa é a fundamental do dominante. Terceiro, acrescente a terça maior e a sétima menor a essa fundamental, formando o acorde V7 do alvo."),
        b ("Alvo Dm: suba uma quinta → Lá. O dominante é A7."),
        b ("Alvo Em: suba uma quinta → Si. O dominante é B7."),
        b ("Alvo F: suba uma quinta → Dó. O dominante é C7."),
        b ("Alvo G: suba uma quinta → Ré. O dominante é D7."),
        b ("Alvo Am: suba uma quinta → Mi. O dominante é E7."),
        img ("m8_dominantes_secundarios", "Os cinco dominantes secundários em Dó maior, com o alvo e as notas de cada acorde."),
        c (
            "Repare que o dominante do IV é C7. Em Dó maior, isso introduz um Sib, que não pertence ao campo: é o que faz o C7 puxar para o Fá."),

        h ("Os cinco dominantes secundários em Dó maior"),
        p (
            "Em Dó maior, os graus que recebem dominante secundário são o ii (Dm), o iii (Em), o IV (F), o V (G) e o vi (Am). O vii (Bm7b5) raramente recebe um dominante secundário porque é um acorde diminuto. Cada um desses dominantes acrescenta uma nota estranha que aponta para o alvo."),
        tbl ({ "Dominante", "Cifra", "Resolve em", "Nota estranha" }, {
            { "V7/ii", "A7", "Dm", "Dó# (sensível de Ré)" },
            { "V7/iii", "B7", "Em", "Ré# (sensível de Mi)" },
            { "V7/IV", "C7", "F", "Sib (7ª de Dó)" },
            { "V7/V", "D7", "G", "Fá# (sensível de Sol)" },
            { "V7/vi", "E7", "Am", "Sol# (sensível de Lá)" },
        }),
        p (
            "Observe o padrão: quando o alvo é maior (F, G), a nota estranha é a sétima menor do dominante. Quando o alvo é menor (Dm, Em, Am), a nota estranha é a sensível (terça maior) do dominante, que sobe meio-tom para a tônica do alvo."),
        aud ({ "E3", "G#3", "B3", "D4" }, "E7, o V7/vi de Dó: o Sol# aponta para o Lá do Am."),
        aud ({ "A3", "C#4", "E4", "G4", "D4", "F4", "A4" }, "A7 (V7/ii) resolvendo em Dm: ouça a chegada temporária."),

        h ("A cadeia de dominantes"),
        p (
            "Os dominantes secundários podem se encadear. Um dominante resolve em um acorde que também é dominante de outro, criando uma sequência que vai descendo em quintas. Essa cadeia é comum em turnarounds e em finais de frase, e é a base de boa parte do vocabulário harmônico do jazz."),
        b ("Exemplo: E7 → A7 → D7 → G7 → C (cada um resolve no próximo)."),
        b ("Cada seta é uma resolução de dominante."),
        b ("A cadeia dá sensação de aceleração e chegada."),
        tbl ({ "Passo", "Acorde", "Função" }, {
            { "1", "E7", "V7/vi (dominante de Lá menor)" },
            { "2", "A7", "V7/ii (dominante de Ré menor)" },
            { "3", "D7", "V7/V (dominante de Sol)" },
            { "4", "G7", "V7 (dominante de Dó)" },
            { "5", "C", "tônica (I)" },
        }),

        h ("Dominante secundário e modulação"),
        p (
            "A diferença entre um dominante secundário e uma modulação está na duração. No dominante secundário, o centro temporário dura pouco e a música volta ao tom principal. Na modulação, o novo centro se firma e a música passa a gravitar em torno dele. O dominante secundário é uma visita; a modulação é uma mudança de endereço."),
        b ("Dominante secundário: o tom de chegada não se confirma."),
        b ("Modulação: o novo tom recebe cadências e se estabelece."),
        b ("O mesmo acorde pode ser os dois, dependendo do contexto que vem depois."),

        h ("Como reconhecer de ouvido"),
        p (
            "O dominante secundário soa como uma \"virada\" dentro da frase. Você sente que a música saiu do caminho principal e está apontando para outro lugar, mas sem sair de vez. Treine ouvindo uma progressão e perguntando: para qual acorde esse dominante está puxando? A resposta costuma ser o acorde que vem logo depois."),
        b ("Ouça a progressão e localize o momento de maior tensão."),
        b ("Identifique para qual acorde a tensão resolve."),
        b ("Nomeie o dominante como V7 desse alvo."),
        aud ({ "C4", "E4", "G4", "A3", "C#4", "E4", "G4", "D4", "F4", "A4" },
             "C → A7 → Dm: o A7 é um dominante secundário apontando para o ii."),

        h ("Erros comuns"),
        p (
            "O erro mais frequente é achar que qualquer acorde com sétima é um dominante secundário. Só é dominante secundário o acorde de sétima dominante (0, 4, 7, 10) que resolve em um grau diferente do I. Outro erro é esquecer que o alvo precisa ser preparado: um dominante secundário sem resolução perde a função."),
        b ("Nem todo acorde com 7 é dominante: confira os intervalos."),
        b ("O alvo precisa vir depois, senão a função se perde."),
        b ("O alvo menor recebe dominante com terça maior (sensível), não menor."),
        c (
            "Dica: escreva o alvo acima do dominante. Ver a relação escrita ajuda o ouvido a fixar a função."),

        h ("Aplicação prática"),
        p (
            "No instrumento, pratique tocar a progressão I → V7/ii → ii → V7 → I. É a cadência mais comum da música popular, e tocar todos os dominantes secundários em sequência treina o ouvido e a mão ao mesmo tempo. Use o app para conferir se cada acorde que você monta tem as notas certas."),
        b ("Toque a sequência C → A7 → Dm → G7 → C."),
        b ("Repita trocando o alvo: C → D7 → G7 → C."),
        b ("Toque cada dominante como arpejo antes de tocar como acorde."),
        part ("m8_partitura_v7_do_v", { "D3", "F#3", "A3", "C4" },
              "Partitura do arpejo de D7 (V7/V de Dó) — o dominante que aponta para o Sol. Ouça o que está escrito."),

        h ("Dominantes secundários em outras tonalidades"),
        p (
            "Os dominantes secundários existem em qualquer tonalidade. Em Sol maior, o ii é Am, o V7/ii é E7; o V7/V é A7; o V7/vi é B7. Em Fá maior, o ii é Gm, o V7/ii é D7; o V7/V é G7. O processo é sempre o mesmo: identificar o alvo e subir uma quinta justa para achar a fundamental do dominante. Uma vez entendido o padrão, você o aplica em qualquer tom."),
        b ("Em Dó maior: A7, B7, C7, D7, E7."),
        b ("Em Sol maior: E7, F#7, G7, A7, B7."),
        b ("Em Fá maior: D7, E7, F7, G7, A7."),
        tbl ({ "Tonalidade", "V7/ii", "V7/V", "V7/vi" }, {
            { "Dó maior", "A7", "D7", "E7" },
            { "Sol maior", "E7", "A7", "B7" },
            { "Fá maior", "D7", "G7", "A7" },
            { "Si bemol maior", "G7", "C7", "D7" },
        }),

        h ("Dominantes secundários na guitarra"),
        p (
            "No instrumento, os dominantes secundários exigem um pouco mais de atenção porque introduzem notas que não estão no campo. É aí que a teoria vira prática: você precisa saber onde está o Dó sustenido no braço para tocar o A7. A boa notícia é que, uma vez que você aprende a forma do acorde de sétima dominante, pode deslocá-la para qualquer região do braço, mudando apenas a fundamental."),
        b ("Aprenda uma forma de acorde de sétima dominante e desloque-a."),
        b ("Confira a nota estranha: ela define o alvo."),
        b ("Toque o arpejo do dominante para ouvir cada intervalo."),
        p (
            "Uma forma de treinar é tocar a progressão I → V7/ii → ii → V7 → I em várias tonalidades. Ao deslocar a progressão inteira para outro tom, você treina a mão e o ouvido juntos, e fixa a relação entre cada dominante e o seu alvo. É um dos exercícios mais eficientes para internalizar o vocabulário harmônico."),
        aud ({ "C4", "E4", "G4", "A3", "C#4", "E4", "G4", "D3", "F3", "A3", "C4", "G3", "B3", "D4", "F4" },
             "C → A7 → Dm → G7: o V7/ii preparando o ii, e depois a volta ao V7."),

        h ("Dominantes secundários e substituições"),
        p (
            "Cada dominante secundário também pode ser substituído pelo seu SubV7. Em vez de A7 apontando para Dm, você pode usar Eb7 (o SubV7 de Dm). Em vez de D7 apontando para G, pode usar Ab7. Assim, cada dominante secundário dobra de possibilidades: uma versão que sobe em quarta e uma que desce em semitom. Essa é a base da reharmonização que você verá adiante."),
        b ("V7/ii (A7) pode virar SubV7/ii (Eb7)."),
        b ("V7/V (D7) pode virar SubV7/V (Ab7)."),
        b ("Cada dominante secundário tem o seu substituto a um trítono."),
        c (
            "Guarde isso: toda substituição que você aprendeu para o V7 vale também para os dominantes secundários."),

        h ("Onde os dominantes secundários aparecem"),
        p (
            "Os dominantes secundários aparecem em quase todos os estilos. No jazz, eles preparam cada acorde de um standard, criando a densidade harmônica característica do gênero. Na bossa nova, aparecem com frequência antes dos acordes menores, dando aquele colorido cromático. No rock e no pop, aparecem em passagens que precisam de movimento, como as viradas de refrão. Reconhecê-los é reconhecer o movimento da música."),
        b ("Jazz: preparam cada grau dos standards."),
        b ("Bossa nova: aparecem antes dos acordes menores."),
        b ("Rock e pop: criam movimento nas viradas."),
        c (
            "Quando você ouvir uma música e sentir que ela \"muda de cor\" por um instante, provavelmente é um dominante secundário apontando para um grau próximo."),

        h ("Resumo do tópico"),
        b ("Dominante secundário é o V7 de um grau que não é o I."),
        b ("Constrói-se subindo uma quinta justa a partir do alvo."),
        b ("A nota estranha ao campo é o que cria a tensão e aponta o alvo."),
        b ("Dominantes podem se encadear descendo em quintas."),
        b ("Dominante secundário é visita; modulação é mudança de tom."),
        c (
            "Nos exercícios deste tópico, toque os dominantes secundários e confira com o app. Ele reconhece as notas e verifica se o acorde montado é realmente um dominante do alvo pedido."),
    };
}

} // namespace cursomusica::content
