#include "Course/Content/Topics.h"

// Topic 7A — Empilhamentos de terças (Módulo 7, Etapa 7).
// Fonte de verdade do texto: docs/MUSIC.md §7.2 (bloco A).
namespace cursomusica::content
{

std::vector<ContentItem> topic7A()
{
    return {

        p (
            "Até aqui você construiu acordes empilhando notas a distâncias fixas: a tônica, a terça e a quinta formam a tríade; acrescentar a sétima forma a tétrade. Neste módulo você dá o passo seguinte: passa a escolher a distância de cada salto e, com isso, constrói estruturas que vão muito além das tríades e tétrades convencionais. O primeiro e mais importante desses empilhamentos é o de terças."),
        p (
            "Empilhar terças é somar intervalos de terça, um sobre o outro. É a forma mais natural de construir acordes na música ocidental e a origem de praticamente todo acorde que você já tocou. Entender esse empilhamento é entender por que um acorde soa maior, menor, suspenso, tenso ou repousado."),
        c (
            "Objetivo do módulo: conhecer estruturas harmônicas além das tríades e tétrades convencionais. Não basta decorar formas no braço: é preciso saber que notas estão empilhadas e por quê."),

        h ("O que é empilhar terças"),
        p (
            "Uma terça é um intervalo de três letras: de Dó a Mi, de Mi a Sol, de Sol a Si. Quando você coloca três terças em sequência, cada nova terça começa na nota em que a anterior terminou. Em Dó, isso dá Dó–Mi–Sol–Si: tônica, terça, quinta e sétima. Cada terça acrescentada amplia o acorde e muda a sua sonoridade."),
        b ("Três notas (duas terças empilhadas): tríade."),
        b ("Quatro notas (três terças): tétrade."),
        b ("Cinco notas (quatro terças): acorde de nona."),
        b ("Seis notas (cinco terças): acorde de décima primeira."),
        b ("Sete notas (seis terças): acorde de décima terceira."),
        p (
            "Note que o nome do acorde cresce de dois em dois: 1-3-5 (tríade), 1-3-5-7 (tétrade), 1-3-5-7-9 (nona), 1-3-5-7-9-11 (décima primeira), 1-3-5-7-9-11-13 (décima terceira). Os graus ímpares são os que se empilham; os pares (2, 4, 6) aparecem como tensões uma oitava acima (9, 11, 13)."),
        img ("m7_tercas_empilhadas", "Empilhamento de terças: cada nota nova começa onde a anterior terminou."),

        h ("Terças maiores e terças menores"),
        p (
            "Existem dois tamanhos de terça. A terça maior tem 4 semitons; a terça menor tem 3. Como o empilhamento pode misturar os dois tamanhos, a combinação escolhida define a qualidade do acorde. É essa mistura que separa um acorde maior de um menor, um dominante de um meio-diminuto."),
        tbl ({ "Terça", "Semitons", "Exemplo em Dó" }, {
            { "terça maior", "4", "Dó → Mi" },
            { "terça menor", "3", "Mi → Sol (a partir de Mi)" },
        }),
        p (
            "A primeira terça, medida a partir da tônica, é a que dá o caráter principal: terça maior faz o acorde maior, terça menor faz o acorde menor. As terças seguintes acrescentam cor e tensão, mas não mudam esse caráter básico."),
        b ("Tônica + terça maior = som aberto, alegre."),
        b ("Tônica + terça menor = som fechado, melancólico."),
        b ("A quinta (a terceira terça empilhada) confirma a estrutura e dá estabilidade."),
        c (
            "Truque de escuta: toque só a tônica e a terça. Se soa alegre, é maior; se soa triste, é menor. Todo o resto do acorde é decoração sobre esse par."),

        h ("As qualidades que nascem do empilhamento"),
        p (
            "Combinando terças maiores e menores de formas diferentes, obtêm-se todas as qualidades de acorde do sistema tonal. A tabela abaixo reúne as principais, com os intervalos em semitons a partir da tônica. Use-a como mapa: cada linha é um empilhamento de terças que você pode construir no braço."),
        tbl ({ "Acorde", "Notas (a partir da tônica)", "Semitons", "Fórmula" }, {
            { "maior (7M)", "1 3 5 7", "0 4 7 11", "3M 3m 3M" },
            { "dominante (7)", "1 3 5 b7", "0 4 7 10", "3M 3m 3m" },
            { "menor (m7)", "1 b3 5 b7", "0 3 7 10", "3m 3M 3m" },
            { "meio-diminuto (m7b5)", "1 b3 b5 b7", "0 3 6 10", "3m 3m 3M" },
            { "diminuto (º7)", "1 b3 b5 bb7", "0 3 6 9", "3m 3m 3m" },
            { "menor com 7M (m7M)", "1 b3 5 7", "0 3 7 11", "3m 3M 3M" },
            { "aumentado (7M#5)", "1 3 #5 7", "0 4 8 11", "3M 3M 3M" },
        }),
        p (
            "Repare no padrão: cada linha é uma sequência de terças maiores (3M) e menores (3m). O acorde diminuto usa três terças menores; o aumentado usa três maiores; as demais qualidades misturam os dois tamanhos. Aprender a ver a fórmula de terças é o que permite construir qualquer acorde em qualquer tônica."),
        aud ({ "C4", "E4", "G4", "B4" }, "Dó com sétima maior (Cmaj7): terças 3M–3m–3M, som brilhante e suspenso."),
        aud ({ "C4", "E4", "G4", "A#3" }, "Dó com sétima dominante (C7): 3M–3m–3m, som que pede resolução."),
        aud ({ "C4", "D#4", "G4", "A#3" }, "Dó menor com sétima (Cm7): 3m–3M–3m, som fechado e estável."),

        h ("Do empilhamento às tensões"),
        p (
            "Continuando a empilhar terças acima da sétima, chegam as tensões: a nona (9), a décima primeira (11) e a décima terceira (13). Elas não são notas “estranhas” ao acorde — são simplesmente os graus 2, 4 e 6 uma oitava acima. Acrescentar tensões é o que dá riqueza, brilho e modernidade ao acorde."),
        b ("9 = a segunda, uma oitava acima (2 semitons + 12)."),
        b ("11 = a quarta, uma oitava acima (5 semitons + 12)."),
        b ("13 = a sexta, uma oitava acima (9 semitons + 12)."),
        tbl ({ "Acorde", "Notas", "Som" }, {
            { "Cmaj7", "Dó Mi Sol Si", "brilhante" },
            { "Cmaj9", "Dó Mi Sol Si Ré", "mais aberto" },
            { "Cmaj13", "Dó Mi Sol Si Lá", "cheio, sofisticado" },
            { "C7", "Dó Mi Sol Sib", "dominante, tenso" },
            { "C9", "Dó Mi Sol Sib Ré", "dominante com cor" },
            { "C13", "Dó Mi Sol Sib Lá", "dominante rico" },
        }),
        c (
            "Quando o acorde já tem sete notas (a décima terceira), o empilhamento de terças chegou ao fim: a próxima terça seria a tônica uma oitava acima. Empilhar além disso é repetir o que já existe."),

        h ("Omissões: o que se pode tirar"),
        p (
            "Na guitarra, tocar sete notas ao mesmo tempo é praticamente impossível e, muitas vezes, desnecessário. Por isso os acordes de tensão costumam vir com omissões: a quinta (que só confirma a estrutura) é a primeira a sair; a tônica pode sair quando o baixo a sustenta; a nona pode substituir a tônica. O que nunca sai é a terça, porque é ela que define o caráter, e a sétima, quando o acorde é de sétima."),
        b ("Omite-se a quinta: ela não define a qualidade."),
        b ("Omite-se a tônica: o baixo e o contexto já a sugerem."),
        b ("Mantém-se a terça: define maior ou menor."),
        b ("Mantém-se a sétima: define o tipo de acorde (7M, 7, m7…)."),
        img ("m7_tercas_empilhadas", "O mesmo empilhamento pode ser reduzido a poucas notas sem perder a identidade."),

        h ("Empilhamento de terças na guitarra"),
        p (
            "O braço da guitarra facilita o empilhamento de terças porque as cordas estão afinadas, em sua maioria, em quartas. Uma terça maior ou menor aparece a poucas casas de distância entre cordas vizinhas, e o mesmo desenho se desloca para qualquer tônica. É por isso que as formas do CAGED, que você viu no módulo 1, funcionam: cada forma é um empilhamento de terças desenhado no braço."),
        b ("A terça a partir da tônica aparece a uma corda e duas casas de distância, na maioria das posições."),
        b ("A quinta aparece a uma corda e duas casas acima da terça."),
        b ("O desenho inteiro se transposta movendo a mão pelo braço."),
        aud ({ "C4", "E4", "G4" }, "Tríade de Dó maior: as duas terças empilhadas (Dó–Mi, Mi–Sol)."),

        h ("Por que isso importa"),
        p (
            "Empilhar terças é o alicerce de toda a harmonia que você vai estudar daqui em diante. Acordes de nona, décima primeira e décima terceira, substituições, reharmonizações e voicings de jazz são todos variações do mesmo princípio: escolher quais terças empilhar e quais omitir. Quando você entende a fórmula de terças, para de decorar centenas de formas e passa a construir qualquer acorde a partir das notas que o formam."),
        b ("Todo acorde tradicional é um empilhamento de terças."),
        b ("A qualidade vem da mistura de terças maiores e menores."),
        b ("As tensões (9, 11, 13) são os graus 2, 4 e 6 uma oitava acima."),
        b ("Omite-se a quinta e, às vezes, a tônica; nunca a terça."),
        part ("m7_partitura_tercas", { "C4", "E4", "G4", "B4" },
              "Partitura: Cmaj7 (Dó–Mi–Sol–Si), um empilhamento de terças 3M–3m–3M. Pressione ouvir para escutar exatamente o que está escrito."),


        h ("A fórmula de terças como ferramenta de construção"),
        p (
            "Saber a fórmula de terças permite construir qualquer acorde sem decorar o braço. Você escolhe a tônica, decide a qualidade (maior, menor, dominante, meio-diminuto…), aplica a sequência de terças correspondente e pronto: o acorde está montado. Essa é a diferença entre tocar acordes de memória e realmente entender a harmonia."),
        tbl ({ "Quero um acorde…", "Fórmula", "Notas em Dó" }, {
            { "maior com nona", "1 3 5 7 9", "Dó Mi Sol Si Ré" },
            { "menor com nona", "1 b3 5 b7 9", "Dó Mib Sol Sib Ré" },
            { "dominante com 13", "1 3 5 b7 13", "Dó Mi Sol Sib Lá" },
            { "meio-diminuto com 11", "1 b3 b5 b7 11", "Dó Mib Solb Sib Fá" },
            { "menor com 11", "1 b3 5 b7 11", "Dó Mib Sol Sib Fá" },
        }),
        p (
            "Note que algumas tensões combinam melhor com certas qualidades. A décima primeira natural sobre um acorde maior costuma soar áspera (é uma nota de evitação); por isso o acorde maior prefere a #11, que veremos adiante. A décima primeira sobre acordes menores e dominantes sus funciona muito bem."),
        b ("Maior: use 9 e 13; evite a 11 natural."),
        b ("Menor: 9 e 11 soam naturais."),
        b ("Dominante: 9 e 13 dão o som clássico."),
        c (
            "Regra de bolso: empilhe terças e, quando uma tensão soar áspera, verifique se ela não é uma nota de evitação do modo daquele acorde. Esse assunto volta nos tópicos sobre famílias modais."),

        h ("Inversões e o baixo"),
        p (
            "O empilhamento de terças define quais notas formam o acorde; a inversão define qual delas está no baixo. Inverter é apenas reordenar as mesmas notas, sem mudar o acorde. Na guitarra, as inversões são o que permitem tocar o mesmo acorde em várias regiões do braço, com o baixo em cordas diferentes."),
        b ("Posição fundamental: a tônica no baixo."),
        b ("Primeira inversão: a terça no baixo."),
        b ("Segunda inversão: a quinta no baixo."),
        b ("Terceira inversão (tétrades): a sétima no baixo."),
        aud ({ "C4", "E4", "G4" }, "Dó maior na posição fundamental: tônica no baixo."),
        aud ({ "E3", "G3", "C4" }, "A mesma tríade na primeira inversão: a terça no baixo muda a cor sem mudar o acorde."),

        h ("Do empilhamento ao voicing"),
        p (
            "Um voicing é a forma concreta como você distribui as notas do acorde no braço — quais notas toca, em que oitavas e em que ordem. O mesmo empilhamento de terças pode gerar voicings muito diferentes: fechado (notas juntas), aberto (notas espalhadas), com ou sem dobramentos. Escolher o voicing é o que faz um acorde soar “cheio”, “moderno” ou “limpo”, mesmo sendo o mesmo acorde na teoria."),
        b ("Voicing fechado: as notas ficam dentro de uma oitava."),
        b ("Voicing aberto: as notas se espalham por mais de uma oitava."),
        b ("Drop 2 e drop 3: técnicas de espalhar as notas de uma tétrade."),
        img ("m7_tercas_empilhadas", "O mesmo acorde, distribuído de formas diferentes no braço: o voicing muda a sonoridade."),
        c (
            "Todo o assunto de voicings, drops e estruturas parte do mesmo princípio: você tem um empilhamento de terças e escolhe como apresentá-lo. Dominar o empilhamento é o pré-requisito."),

        h ("Erros comuns neste tópico"),
        p (
            "Os tropeços mais frequentes vêm de confundir o número do grau com a distância e de esquecer que as tensões são graus pares uma oitava acima. Outro erro é tentar tocar todas as notas de um acorde de décima terceira na guitarra, quando o correto é omitir o que não define a qualidade."),
        b ("Confundir nona com segunda: a nona é a segunda uma oitava acima."),
        b ("Achar que 11 é uma nota nova: é a quarta, uma oitava acima."),
        b ("Tocar todas as sete notas: quase sempre é impossível e desnecessário."),
        b ("Esquecer a terça ao simplificar o acorde: é a nota que define maior ou menor."),

        h ("Resumo do tópico"),
        b ("Empilhar terças é somar intervalos de terça, um sobre o outro."),
        b ("A mistura de terças maiores e menores define a qualidade do acorde."),
        b ("Acrescentar terças acima da sétima gera as tensões 9, 11 e 13."),
        b ("Omite-se a quinta e, às vezes, a tônica; nunca a terça."),
        b ("O voicing é como você distribui o empilhamento no braço."),
        c (
            "Nos exercícios deste tópico, você toca tríades e tétrades e o app reconhece as notas para conferir o empilhamento. Qualquer posição do braço vale — o que importa é o conjunto de notas."),
    };
}

} // namespace cursomusica::content
