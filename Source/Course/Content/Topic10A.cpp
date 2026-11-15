#include "Course/Content/Topics.h"

// Topic 10A — Análise harmônica (Módulo 10, Etapa 10).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 10) e o laboratório de
// standards. Análise = dizer o grau, a função e a escala de cada acorde.
namespace cursomusica::content
{

std::vector<ContentItem> topic10A()
{
    return {

        p (
            "Analisar a harmonia de uma música é descobrir o que cada acorde está fazendo ali. Não basta ler a cifra e tocar: analisar é responder, acorde por acorde, de onde ele vem (qual grau da escala), o que ele faz na frase (qual função) e como ele soa (qual escala o acompanha). Quando você consegue responder essas três perguntas, a música deixa de ser uma sequência de símbolos decorados e passa a ser um caminho que você entende."),
        p (
            "Este é o primeiro tópico da Etapa 10 e ele abre todos os outros. Toda reharmonização nasce de uma análise: só se pode trocar um acorde quando se sabe qual era a função dele. Este módulo usa uma música do repertório curado como laboratório — a mesma progressão que você analisa é a que você reharmoniza no fim. A análise é o mapa; a reharmonização é escolher um caminho novo sobre esse mapa."),
        c (
            "Objetivo da Etapa 10: aprender a analisar músicas e descobrir diferentes caminhos para modificar suas harmonias. A análise vem primeiro; a modificação é a consequência."),

        h ("O que é analisar uma harmonia"),
        p (
            "Analisar uma harmonia é reduzir uma sequência de acordes à sua lógica interna. Em vez de ver 'C7M, A7, Dm7, G7', você vê 'I, VI7, ii, V'. A diferença é enorme: a segunda leitura mostra uma função dominante secundária preparando o ii, um ciclo de quintas descendo e uma cadência que volta para a tônica. A primeira leitura é só uma lista; a segunda é uma história."),
        p (
            "O ponto de partida é sempre a tonalidade. A mesma nota é um grau diferente conforme o centro da música. O acorde de Sol maior é o V em Dó maior, mas é o I em Sol maior. Por isso a análise começa identificando a tônica: sem ela, os graus não têm sentido."),
        b ("Primeiro encontre a tônica (o centro de repouso da música)."),
        b ("Depois numere cada acorde como grau (I, ii, iii, IV, V, vi, vii)."),
        b ("Em seguida classifique a função: tônica, subdominante ou dominante."),
        b ("Por fim aponte a escala que combina com cada acorde."),
        img ("m10_analise_harmonica", "A ficha de análise: acorde, grau, função e escala. A análise responde às três perguntas de cada acorde."),

        h ("Grau: de onde o acorde vem"),
        p (
            "O grau é a posição do acorde dentro da escala da tonalidade. Em Dó maior, o campo harmônico é C7M (I), Dm7 (ii), Em7 (iii), F7M (IV), G7 (V), Am7 (vi) e Bm7b5 (vii). Cada acorde dessa lista nasce de empilhar as notas da escala de Dó de três em três. Quando você vê um acorde que não está na lista — um A7 num campo de Dó, por exemplo —, ele é um empréstimo ou um dominante secundário, e a análise precisa dizer qual."),
        tbl ({ "Grau", "Acorde em Dó maior", "Notas", "Qualidade" }, {
            { "I", "C7M", "C–E–G–B", "sétima maior" },
            { "ii", "Dm7", "D–F–A–C", "menor com sétima" },
            { "iii", "Em7", "E–G–B–D", "menor com sétima" },
            { "IV", "F7M", "F–A–C–E", "sétima maior" },
            { "V", "G7", "G–B–D–F", "sétima dominante" },
            { "vi", "Am7", "A–C–E–G", "menor com sétima" },
            { "vii", "Bm7b5", "B–D–F–A", "meio-diminuto" },
        }),
        c (
            "Regra prática: se o acorde não está no campo harmônico, procure de qual grau ele é dominante. Um A7 antes de Dm7 é o V/ii — o dominante do segundo grau. Isso já é análise."),

        h ("Função: o que o acorde faz"),
        p (
            "A função é o papel do acorde no movimento da frase. Existem três funções básicas. A tônica é o repouso (I, vi, iii): são os acordes onde a frase pode parar. A subdominante é o afastamento (IV, ii): ela cria movimento e prepara a volta. O dominante é a tensão (V, vii): ele pede resolução e quase sempre volta para a tônica. Reconhecer a função é o que permite prever para onde a música vai."),
        b ("Tônica (repouso): I, vi, iii — a frase descansa."),
        b ("Subdominante (afastamento): IV, ii — a frase se move."),
        b ("Dominante (tensão): V, vii — a frase pede resolução."),
        aud ({ "C4", "E4", "G4", "B4" }, "Tônica: o acorde de repouso (Dó com sétima maior). Ouça o som de chegada."),
        aud ({ "D4", "F4", "A4", "C5" }, "Subdominante: o acorde de movimento (Ré menor com sétima). Ouça a sensação de afastamento."),
        aud ({ "G3", "B3", "D4", "F4" }, "Dominante: o acorde de tensão (Sol com sétima). Ouça o pedido de resolução."),
        p (
            "O ciclo mais importante da música tonal é o ii–V–I: subdominante, dominante e tônica em sequência. Ele aparece em quase todo standard de jazz e em boa parte da MPB. Analisar uma música é, muitas vezes, encontrar os ii–V–I escondidos e ver como eles se encadeiam."),
        part ("m10_partitura_turnaround", { "C4", "E4", "G4", "A4", "D5", "F5", "G5", "B4" },
              "Partitura: os arpejos de um turnaround C7M – A7 – Dm7 – G7. Ouça como a harmonia caminha grau por grau."),

        h ("Escala: como o acorde soa"),
        p (
            "A terceira pergunta da análise é qual escala combina com cada acorde. Ela não é a mesma para todo mundo: cada qualidade de acorde pede uma escala própria. Sobre um acorde menor com sétima (Dm7) cabe o modo dórico; sobre um dominante (G7) cabe o mixolídio; sobre uma sétima maior (C7M) cabe o jônio. Saber isso é o que permite improvisar com intenção em vez de tocar notas ao acaso."),
        tbl ({ "Qualidade do acorde", "Escala que combina", "Cor" }, {
            { "sétima maior (7M)", "jônio / lídio", "brilho, repouso" },
            { "menor com sétima (m7)", "dórico / eólio", "menor, suave" },
            { "dominante (7)", "mixolídio", "tensão, blues" },
            { "meio-diminuto (m7b5)", "lócrio", "tensão escura" },
            { "dominante alterado (7alt)", "superlócrio / alterada", "tensão máxima" },
        }),
        c (
            "Análise completa de um acorde: grau + função + escala. 'G7 é o V, tem função dominante e combina com o mixolídio.' Com essas três informações você sabe tocar, acompanhar e improvisar sobre ele."),

        h ("Analisando uma progressão passo a passo"),
        p (
            "Vamos analisar a progressão C7M – A7 – Dm7 – G7 – C7M, que é o esqueleto de muitos turnarounds. O primeiro acorde é C7M: grau I, função de tônica, escala jônio. O segundo, A7, não está no campo de Dó — é o dominante secundário que prepara o Dm7; sua função é de dominante e ele pede a escala mixolídia (ou alterada). O Dm7 é o ii, função subdominante, escala dórica. O G7 é o V, função dominante, escala mixolídia. E o último C7M volta à tônica."),
        tbl ({ "Acorde", "Grau", "Função", "Escala" }, {
            { "C7M", "I", "tônica", "jônio" },
            { "A7", "VI7 (V/ii)", "dominante secundário", "mixolídio / alterada" },
            { "Dm7", "ii", "subdominante", "dórico" },
            { "G7", "V", "dominante", "mixolídio" },
            { "C7M", "I", "tônica", "jônio" },
        }),
        b ("A7 é um acorde de fora do campo, mas com função clara: prepara o ii."),
        b ("O par Dm7–G7 é um ii–V; o par G7–C7M é a cadência final."),
        b ("A análise transforma cinco acordes soltos em uma frase com sentido."),
        img ("m10_conexao_campos", "Os campos harmônicos se ligam por acordes-pivo. A análise mostra por onde uma tonalidade passa para outra."),

        h ("Erros comuns na análise"),
        p (
            "Quem está começando erra sempre nos mesmos pontos. O primeiro é analisar sem definir a tonalidade: sem centro, o grau é arbitrário. O segundo é confundir a nota com a função: o acorde de Lá menor é o vi em Dó maior e o ii em Sol maior, e tratá-lo sempre como 'acorde triste' não é análise. O terceiro é esquecer os dominantes secundários e achar que todo acorde fora do campo é 'erro' ou 'modulação'."),
        b ("Defina a tonalidade antes de numerar qualquer acorde."),
        b ("Um acorde fora do campo pode ser dominante secundário, empréstimo modal ou acorde de passagem — identifique qual."),
        b ("Não confunda a cor do acorde (maior/menor) com a função dele (tônica/subdominante/dominante)."),
        c (
            "Dica: escreva a análise no papel antes de tocar. Ver os graus enfileirados revela os padrões (ii–V–I, ciclos de quinta, cromatismos) que passam despercebidos na leitura apressada."),

        h ("A análise como base para tudo o que vem"),
        p (
            "Este tópico é a fundação do módulo. A análise melódica (tópico B) usa os mesmos graus para dizer quais notas são repouso e quais são tensão. A escolha modal (tópico C) usa a terceira pergunta da análise — a escala. A verticalização (tópico D) constrói acordes a partir da melodia analisada. A conexão entre campos (tópico E) é análise de duas tonalidades ao mesmo tempo. E a reharmonização (tópicos G a I) só existe porque sabemos qual função cada acorde tinha."),
        b ("Analisar = grau + função + escala."),
        b ("A tônica define os graus; a função define o movimento; a escala define a cor."),
        b ("A análise é o mapa sobre o qual toda reharmonização acontece."),
        img ("m10_analise_harmonica", "Volte à ficha de análise sempre que um acorde parecer fora de lugar: ela responde grau, função e escala."),

        h ("Análise em movimento: o ciclo das quintas"),
        p (
            "Muitas progressões andam de quinta em quinta descendente: Dm7 – G7 – C7M – F7M – Bm7b5 – E7 – Am7. Cada acorde prepara o seguinte por uma quinta abaixo, e é esse encadeamento que dá a sensação de movimento contínuo. Reconhecer o ciclo de quintas na análise é meio caminho para prever o próximo acorde — e para saber onde inserir um substituto."),
        tbl ({ "De", "Para (quinta abaixo)", "Relação" }, {
            { "Dm7 (ii)", "G7 (V)", "prepara a dominante" },
            { "G7 (V)", "C7M (I)", "cadência à tônica" },
            { "C7M (I)", "F7M (IV)", "afasta para o subdominante" },
            { "Bm7b5 (vii)", "E7 (V/vi)", "dominante do relativo" },
            { "E7 (V/vi)", "Am7 (vi)", "resolve no relativo menor" },
        }),
        c (
            "O ciclo de quintas é a espinha dorsal da harmonia tonal. Analisar uma música é, com frequência, encontrar onde o ciclo quebra — porque é exatamente onde a música surpreende."),
        aud ({ "D4", "F4", "A4", "C5", "G4", "B4", "D5", "F5", "C4", "E4", "G4", "B4" },
             "Um ii–V–I completo: o ciclo de quintas descendo até o repouso. Ouça o caminho inteiro."),

        h ("Analisando uma música inteira: o roteiro completo"),
        p (
            "Analisar uma música inteira é seguir sempre o mesmo roteiro. Primeiro, ouça a música duas ou três vezes sem instrumento, procurando o centro de repouso: onde ela 'termina' e onde ela 'respira'. Esse é o indício da tonalidade. Segundo, escreva a cifra e numere cada acorde em relação a essa tonalidade. Terceiro, marque os acordes que ficam fora do campo harmônico e descubra o papel de cada um: dominante secundário, empréstimo modal ou acorde de passagem. Quarto, agrupe os acordes em funções e identifique os ii–V–I. Quinto, aponte a escala de cada acorde para o improviso. Ao fim desse roteiro, você tem o mapa completo da música."),
        b ("Ouça e ache o centro de repouso (a tonalidade)."),
        b ("Numere cada acorde como grau."),
        b ("Explique os acordes de fora do campo (secundário, empréstimo, passagem)."),
        b ("Agrupe em funções e marque os ii–V–I."),
        b ("Aponte a escala de cada acorde."),
        p (
            "Esse roteiro é o que permite analisar uma música que você nunca viu. Ele transforma a leitura de cifra em compreensão: em vez de tocar os acordes na ordem, você entende por que eles estão ali e para onde a música vai. Depois de analisar algumas músicas com o roteiro, você começa a prever os acordes antes de olhar a cifra — porque reconhece os padrões (ii–V–I, ciclos de quinta, cadências) que se repetem em quase toda a música tonal."),
        c (
            "Dica de estudo: analise uma música nova por semana. Com o tempo, a análise deixa de ser um exercício e passa a ser um reflexo — você ouve a música e já sabe onde está o centro e quais são os caminhos."),

        h ("A análise revela os padrões"),
        p (
            "Analisar uma música é, em grande parte, reconhecer padrões. O ii–V–I é o padrão mais comum; o ciclo de quintas é o segundo; os turnarounds são um caso especial do ciclo. Quando você marca os graus, os padrões saltam aos olhos: dois acordes que descem de quinta em quinta, um dominante que prepara o acorde seguinte, uma cadência que fecha a seção. Ver os padrões é o que permite tocar uma música de memória, porque você não decora acordes soltos — você memoriza os caminhos."),
        tbl ({ "Padrão", "Como aparece nos graus", "O que fazer" }, {
            { "ii–V–I", "ii, V, I", "identificar como cadência principal" },
            { "ciclo de quintas", "vi, ii, V, I", "ver o movimento contínuo" },
            { "turnaround", "I, VI, ii, V", "reconhecer a volta ao início" },
            { "dominante secundário", "V/ii, V/vi", "explicar o acorde de fora" },
            { "empréstimo modal", "iv, VI, VII do menor", "identificar a cor emprestada" },
        }),
        b ("Marque os graus e procure os padrões."),
        b ("Reconhecer o padrão é o que permite memorizar os caminhos, não os acordes."),
        b ("Os padrões se repetem em quase toda a música tonal."),

        h ("Da análise à prática"),
        p (
            "A análise só vale se virar prática. Depois de analisar uma música, toque-a acompanhando com consciência dos graus: ao tocar o V, saiba que é o dominante e sinta a tensão; ao chegar ao I, sinta o repouso. Improvise sobre os acordes escolhendo a escala que a análise indicou para cada um. Reharmonize um trecho aplicando as ferramentas que você aprenderá nos próximos tópicos. A análise é o mapa; a prática é a viagem. Sem a viagem, o mapa é só papel."),
        b ("Toque acompanhando com consciência do grau de cada acorde."),
        b ("Improvisar escolhendo a escala que a análise indicou."),
        b ("Reharmonizar usando a função como critério."),
        c (
            "Nos exercícios deste módulo, você vai analisar progressões, tocar os acordes (o app reconhece e confere), improvisar com as notas certas e reharmonizar. Cada passo da análise vira um exercício jogável."),

        h ("Resumo do tópico"),
        b ("Analisar é responder grau, função e escala para cada acorde."),
        b ("O grau vem da escala da tonalidade; o acorde de fora se explica pelo papel que exerce."),
        b ("As três funções são tônica (repouso), subdominante (movimento) e dominante (tensão)."),
        b ("Cada qualidade de acorde combina com uma escala; a análise aponta qual."),
        b ("A análise é o mapa que sustenta toda a reharmonização do módulo."),
        c (
            "Nos exercícios deste tópico você analisa progressões e confirma a análise tocando os acordes no instrumento: o app reconhece as notas e confere se o acorde está correto."),
    };
}

} // namespace cursomusica::content
