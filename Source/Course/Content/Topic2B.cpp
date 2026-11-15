#include "Course/Content/Topics.h"

// Topic 2B — Quadro móvel de intervalos (Módulo 2, Etapa 2).
// Fonte de verdade do texto: docs/MUSIC.md §2.2 (bloco B).
namespace cursomusica::content
{

std::vector<ContentItem> topic2B()
{
    return {

        p (
            "O quadro móvel de intervalos é a ferramenta que transforma a teoria em algo que você usa no braço. Ele é uma tabela de doze linhas — os doze semitons — que mostra, para cada distância, o nome do intervalo e a nota em que ela cai. Como o quadro é móvel, você o coloca sobre qualquer nota de partida: a tônica muda, o desenho não."),
        p (
            "Decorar o quadro é decorar uma única sequência de nomes. Depois de aprendê-la, você constrói qualquer intervalo a partir de qualquer nota, em qualquer corda, sem contar casa por casa."),

        h ("O quadro a partir de Dó"),
        p (
            "Começando em Dó, cada semitom acrescenta um intervalo. Leia a tabela de cima para baixo e repare como o nome acompanha o número de semitons:"),
        tbl ({ "Semitons", "Intervalo", "Nota (a partir de Dó)" }, {
            { "0", "uníssono", "Dó" },
            { "1", "segunda menor", "Dó#" },
            { "2", "segunda maior", "Ré" },
            { "3", "terça menor", "Ré#" },
            { "4", "terça maior", "Mi" },
            { "5", "quarta justa", "Fá" },
            { "6", "quarta aumentada (trítono)", "Fá#" },
            { "7", "quinta justa", "Sol" },
            { "8", "sexta menor", "Sol#" },
            { "9", "sexta maior", "Lá" },
            { "10", "sétima menor", "Lá#" },
            { "11", "sétima maior", "Si" },
            { "12", "oitava justa", "Dó" },
        }),
        img ("m2_quadro_movel", "O quadro móvel: doze semitons, doze nomes de intervalo."),

        h ("Por que ele é móvel"),
        p (
            "O quadro não pertence a Dó. Se você começar em Sol, cada linha continua igual: 4 semitons acima de Sol é uma terça maior, que cai em Si. O nome do intervalo não depende da nota de partida, apenas da distância. Por isso a mesma tabela serve para todas as tonalidades."),
        b ("A partir de Dó: 4 semitons → terça maior → Mi."),
        b ("A partir de Sol: 4 semitons → terça maior → Si."),
        b ("A partir de Lá: 4 semitons → terça maior → Dó#."),
        c (
            "Móvel quer dizer isto: você move a origem e o quadro continua válido. É o mesmo princípio das formas do CAGED, que deslizam pelo braço."),

        h ("Lendo o quadro no braço"),
        p (
            "No braço, cada corda é uma linha do quadro. Para achar uma terça maior acima de uma nota, conte quatro casas na mesma corda ou use o desenho entre cordas. O quadro diz o nome; o braço diz a posição. Juntando os dois, você localiza qualquer intervalo a partir de qualquer nota."),
        b ("Na mesma corda: conte os semitons como casas."),
        b ("Entre cordas: o desenho se repete, com o ajuste de uma casa entre a 3ª e a 2ª corda."),
        img ("m2_mapa_intervalos", "O quadro aplicado ao braço: cada intervalo vira uma posição."),

        h ("O trítono: o intervalo do meio"),
        p (
            "No centro do quadro está o trítono, seis semitons, que pode ser lido como quarta aumentada ou quinta diminuta. É o intervalo mais instável, e é ele que dá tensão aos acordes dominantes. Vale a pena reconhecê-lo de ouvido desde já, porque ele aparece em quase toda música."),
        b ("6 semitons: quarta aumentada (Fá# acima de Dó) ou quinta diminuta (Fáb acima de Dó)."),
        b ("É o intervalo que divide a oitava exatamente ao meio."),
        aud ({ "C4", "F#4" }, "Trítono: seis semitons, o intervalo mais tenso do quadro."),

        h ("Usando o quadro para construir acordes"),
        p (
            "Um acorde maior é uma tônica, uma terça maior e uma quinta justa. Lendo o quadro, você pega as linhas 0, 4 e 7. Um acorde menor usa as linhas 0, 3 e 7. Com o quadro na cabeça, você constrói acordes por intervalo, sem decorar desenhos."),
        tbl ({ "Acorde", "Graus", "Linhas do quadro" }, {
            { "maior", "1, 3, 5", "0, 4, 7 semitons" },
            { "menor", "1, b3, 5", "0, 3, 7 semitons" },
            { "diminuto", "1, b3, b5", "0, 3, 6 semitons" },
            { "aumentado", "1, 3, #5", "0, 4, 8 semitons" },
            { "sétima dominante", "1, 3, 5, b7", "0, 4, 7, 10 semitons" },
        }),


        h ("Transpor com o quadro móvel"),
        p (
            "A grande utilidade do quadro móvel é transpor. Se você sabe que uma melodia usa uma terça maior e uma quinta justa a partir de Dó, então a partir de qualquer outra tônica você usa exatamente as mesmas distâncias. Transpor deixa de ser decorar uma nova digitação e passa a ser reaplicar o mesmo quadro em outro ponto do braço."),
        b ("Escolha a nova tônica."),
        b ("Aplique as mesmas distâncias do quadro (4 semitons para a terça, 7 para a quinta…)."),
        b ("As notas mudam; o nome dos intervalos e as distâncias não."),
        aud ({ "C4", "E4", "G4" }, "Terça maior e quinta justa a partir de Dó (Dó–Mi–Sol)."),
        aud ({ "G3", "B3", "D4" }, "As mesmas distâncias a partir de Sol (Sol–Si–Ré): o quadro apenas se moveu."),

        h ("O quadro e a construção de escalas"),
        p (
            "Uma escala maior nada mais é do que um padrão de intervalos a partir da tônica: tom, tom, semitom, tom, tom, tom, semitom. Em semitons, isso é 2-2-1-2-2-2-1. Com o quadro na cabeça, você constrói qualquer escala maior a partir de qualquer nota, sem decorar digitações."),
        tbl ({ "Grau da escala maior", "Semitons a partir da tônica", "Intervalo" }, {
            { "1", "0", "uníssono" },
            { "2", "2", "segunda maior" },
            { "3", "4", "terça maior" },
            { "4", "5", "quarta justa" },
            { "5", "7", "quinta justa" },
            { "6", "9", "sexta maior" },
            { "7", "11", "sétima maior" },
            { "8", "12", "oitava justa" },
        }),

        h ("Lendo o quadro no braço: o desenho entre cordas"),
        p (
            "Entre duas cordas vizinhas, o mesmo intervalo aparece deslocado. Como as cordas estão afinadas em quartas (exceto entre a 3ª e a 2ª), o desenho de um intervalo se repete subindo ou descendo uma corda, com um ajuste de uma casa na passagem entre a 3ª e a 2ª corda. Memorizar esse desenho permite tocar o intervalo sem contar casa por casa."),
        b ("Da 6ª para a 5ª corda: o mesmo intervalo desce duas casas (afinação em quarta)."),
        b ("Entre a 3ª e a 2ª corda: o ajuste é de três casas, por causa da afinação em terça."),
        b ("Com o desenho memorizado, você toca o intervalo em qualquer par de cordas."),

        h ("Do quadro para a música"),
        p (
            "O quadro móvel não é um fim em si: é a ferramenta que permite reconhecer e reproduzir intervalos na hora. Depois de internalizá-lo, você começa a ouvir a música como intervalos — uma melodia vira uma sequência de distâncias, um acorde vira um conjunto delas. É esse o salto de qualidade que este módulo busca."),
        c (
            "Nos exercícios, o app toca ou você toca o intervalo; em ambos os casos, o que está em jogo é a distância do quadro. Decorar o quadro é decorar uma única sequência."),


        h ("O quadro e as tríades"),
        p (
            "Uma tríade maior usa as linhas 0, 4 e 7 do quadro; uma tríade menor, as linhas 0, 3 e 7. Lendo o quadro, você constrói qualquer tríade sem decorar desenhos. O mesmo vale para as tétrades: acrescentando a linha 10 (sétima menor) ou a linha 11 (sétima maior), o acorde ganha a quarta nota."),
        tbl ({ "Acorde", "Linhas do quadro (semitons)", "Exemplo em Dó" }, {
            { "maior", "0, 4, 7", "Dó, Mi, Sol" },
            { "menor", "0, 3, 7", "Dó, Mib, Sol" },
            { "sétima maior", "0, 4, 7, 11", "Dó, Mi, Sol, Si" },
            { "sétima dominante", "0, 4, 7, 10", "Dó, Mi, Sol, Sib" },
            { "menor com sétima", "0, 3, 7, 10", "Dó, Mib, Sol, Sib" },
        }),
        aud ({ "C4", "E4", "G4", "A#4" }, "Lendo as linhas 0, 4, 7 e 10: a sétima dominante de Dó."),

        h ("Erros comuns ao usar o quadro"),
        p (
            "O erro mais comum é confundir o número do intervalo com o número de semitons. O número (segunda, terça…) vem da contagem das letras; os semitons vêm da medição exata. Outro erro é esquecer a enarmonia: 6 semitons podem ser quarta aumentada ou quinta diminuta, e o nome correto depende da escrita."),
        b ("Contar letras e contar semitons são operações diferentes."),
        b ("O mesmo número pode ter duas qualidades (terça maior/menor)."),
        b ("O mesmo número de semitons pode ter dois nomes (trítono)."),

        h ("Praticando o quadro no instrumento"),
        p (
            "A melhor forma de fixar o quadro é tocar cada linha a partir de várias tônicas. Escolha uma corda, toque a nota de partida e suba contando os semitons, dizendo o nome do intervalo em voz alta. Repita em outras cordas e outras regiões. Com o tempo, o quadro deixa de ser uma tabela e passa a ser algo que você vê no braço."),
        b ("Toque a tônica e conte as casas até o intervalo desejado."),
        b ("Diga o nome do intervalo em voz alta ao tocar."),
        b ("Repita em várias cordas para o desenho ficar automático."),
        c (
            "Nos exercícios, o app reconhece as notas que você toca e confere a distância. Assim você sabe, na hora, se o intervalo saiu correto."),


        h ("O quadro móvel e o CAGED"),
        p (
            "O sistema CAGED, estudado no módulo 1, e o quadro móvel de intervalos são duas formas de ver a mesma coisa. O CAGED mostra as formas dos acordes deslizando pelo braço; o quadro móvel mostra as distâncias que essas formas contêm. Quando você entende o quadro, deixa de decorar as cinco formas e passa a entender por que elas funcionam."),
        b ("Cada forma do CAGED é um arranjo diferente dos mesmos intervalos."),
        b ("Mover a forma é mover a tônica; as distâncias permanecem."),
        b ("O quadro explica o CAGED; o CAGED aplica o quadro ao braço."),
        img ("m2_mapa_intervalos", "O quadro aplicado ao braço: cada intervalo vira uma posição física."),

        h ("Resumo das aplicações do quadro"),
        p (
            "O quadro móvel serve para construir intervalos, montar escalas, formar acordes e transpor. Tudo isso é possível porque o quadro reduz a música a distâncias que se repetem em qualquer tônica. Aprender o quadro é aprender uma ferramenta que serve para todo o curso."),
        b ("Construir intervalos a partir de qualquer nota."),
        b ("Montar escalas e acordes por distância, não por decoreba."),
        b ("Transpor músicas sem aprender novas digitações."),
        c (
            "Nos exercícios, o app verifica se o intervalo que você toca corresponde à linha do quadro pedida, em qualquer posição."),


        h ("Um método de estudo do quadro"),
        p (
            "Para aprender o quadro móvel de forma duradoura, estude uma linha por dia: hoje a terça maior, amanhã a quinta justa, depois a sétima. Toque a linha a partir de várias tônicas, diga o nome em voz alta e confira com o app. Em poucas semanas, o quadro estará disponível na memória sem esforço consciente."),
        b ("Um intervalo por dia, em várias tônicas."),
        b ("Diga o nome do intervalo ao tocar."),
        b ("Confirme a distância com o app ao final de cada rodada."),

        h ("Resumo do tópico"),
        b ("O quadro móvel lista os doze semitons com o nome de cada intervalo."),
        b ("Ele é móvel: vale a partir de qualquer nota de partida."),
        b ("No braço, cada corda é uma linha do quadro."),
        b ("O trítono (6 semitons) fica no meio e traz a tensão."),
        b ("Lendo as linhas certas, você constrói acordes por intervalo."),
        c (
            "Pratique dizer o nome do intervalo antes de tocar. O objetivo é que o quadro deixe de ser uma tabela e passe a ser algo que você vê no braço."),
    };
}

} // namespace cursomusica::content
