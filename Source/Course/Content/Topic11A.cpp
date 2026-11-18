#include "Course/Content/Topics.h"

// Topic 11A — Desenhos de escalas por regiões (Módulo 11, Etapa 11).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 11) e as apostilas curadas
// (CAGED de Marcelo Mello, fraseado melódico, guitarra fusion).
namespace cursomusica::content
{

std::vector<ContentItem> topic11A()
{
    return {

        p (
            "Até aqui você aprendeu as escalas como um conjunto de notas. A partir da Etapa 11 o objetivo muda: você vai transformar esse conjunto em referências para construir frases. E a primeira dessas referências é o desenho por região. Um desenho não é a escala inteira espalhada pelo braço — é a escala recortada numa região do braço, com começo, fim e uma digitação que a sua mão reconhece de memória."),
        p (
            "Este é o tópico que abre o módulo. Tudo o que vem depois — escalas ascendentes e descendentes, pentatônicas, trilhas abertas e fechadas, Sistema 5, menor harmônica, menor melódica e a relação escala-acorde — se apoia na ideia de região. Quando você pensa em regiões, o braço deixa de ser uma faixa comprida e vira um mapa de territórios que você percorre."),
        c (
            "Objetivo da Etapa 11: transformar o conhecimento de escalas em referências para a construção de frases. O desenho por região é a primeira referência: um território do braço onde a escala já está na sua mão."),

        h ("O que é uma região"),
        p (
            "Uma região é um trecho do braço de quatro a cinco casas onde você toca a escala com os quatro dedos, sem sair da posição. Na prática, é o que todo guitarrista faz quando toca um solo parado num trecho do braço: a mão fica naquela posição e os dedos cobrem as notas dali. Essa caixa é o que chamamos de região."),
        p (
            "O ganho de pensar por regiões é a segurança. Você não precisa enxergar o braço inteiro: precisa enxergar a caixa onde a frase está acontecendo. Frases nascem de uma região, respiram para a região vizinha e voltam. Quem tenta pensar no braço todo se perde; quem pensa por regiões toca com o pé no chão."),
        b ("Uma região cabe em quatro a cinco casas, sem trocar de posição."),
        b ("Os quatro dedos da mão esquerda cobrem, cada um, uma casa da região."),
        b ("A região tem a tônica em pelo menos uma corda — é o seu ponto de referência."),
        b ("Frases começam e terminam dentro de uma região antes de visitar a próxima."),
        img ("m11_desenhos_regioes", "Desenho por região: a escala recortada numa caixa de quatro a cinco casas. Cada região tem a tônica como ponto de referência."),

        h ("Como nasce um desenho"),
        p (
            "Um desenho nasce quando você toca a escala de forma fixa, sempre com a mesma digitação, dentro de uma região. A cada vez que você repete aquele caminho, a mão memoriza. O desenho é a escala com uma forma; a forma é o que sobra na memória depois que a teoria sai de cena."),
        p (
            "Por isso os desenhos são a base do fraseado: eles são o vocabulário motor. Quando você improvisa, a mão dispara desenhos que já conhece, e a cabeça cuida do alvo — onde a frase quer chegar. Sem desenhos, a improvisação vira um cálculo lento; com desenhos, ela vira conversa."),
        tbl ({ "Região", "Casas", "Tônica em", "Uso típico" }, {
            { "Região 1", "casa 1–4", "6ª corda", "frases graves, base" },
            { "Região 2", "casa 3–6", "5ª corda", "frases de transição" },
            { "Região 3", "casa 5–8", "6ª/4ª corda", "região central, solos" },
            { "Região 4", "casa 8–11", "5ª/3ª corda", "solos agudos" },
            { "Região 5", "casa 12–15", "6ª corda", "oitava acima da região 1" },
        }),
        c (
            "Regra prática: escolha a região pela tônica mais próxima da frase. Se a frase pede repouso em Lá, comece na região que tem o Lá debaixo do dedo — não importa se é a 5ª corda casa 12 ou a 6ª corda casa 5."),

        h ("Transitar entre regiões"),
        p (
            "Uma frase inteira presa numa região soa limitada. O que dá relevo ao solo é a viagem: começar numa região, deslizar para a vizinha e voltar. A passagem de uma região para a outra usa uma nota comum — a ponte — ou um deslize de mão (glissando) pela mesma corda."),
        p (
            "O erro comum é trocar de região no meio de uma subida rápida, quando a mão ainda não sabe onde vai. A troca boa acontece em tempo forte ou em nota longa: o ouvido percebe a mudança como intenção, não como deslize acidental."),
        b ("Procure a nota comum entre a região que você deixa e a que você chega."),
        b ("Troque de região em tempo forte ou em nota longa."),
        b ("Use o deslize (glissando) para esconder a troca quando a distância for grande."),
        img ("m11_regioes_transicao", "Transição entre regiões: a nota comum é a ponte; o deslize cobre a distância quando não há nota comum."),

        h ("Do desenho à frase"),
        p (
            "O desenho é matéria-prima, não a frase. A frase nasce quando você decide para onde o desenho vai: começa num grau, passa por um ponto alto e repousa numa nota do acorde. O desenho é o caminho; a frase é a decisão de onde parar."),
        p (
            "O lick deste tópico mostra um desenho em ação: uma sequência de grupos de três notas subindo dentro da região, do jeito que John Petrucci costuma usar para construir tensão antes de resolver. O desenho é sempre o mesmo; a frase é para onde ele aponta."),
        aud ({ "A4", "B4", "C5", "B4", "C5", "D5", "C5", "D5", "E5", "D5", "E5", "F5", "E5", "F5", "G5", "F5", "G5", "A5" },
             "Lick do tópico A: grupos de três notas subindo na região de Lá menor (A-B-C, B-C-D, C-D-E…). O desenho se repete; a frase cresce até repousar no A."),
        part ("m11_partitura_a", { "A4", "B4", "C5", "B4", "C5", "D5", "C5", "D5", "E5", "D5", "E5", "F5", "E5", "F5", "G5", "F5", "G5", "A5" },
              "Partitura do lick A: grupos de três (1-2-3, 2-3-4…) dentro da região. Toda partitura tem o seu áudio."),

        h ("Estudar com o metrônomo"),
        p (
            "O desenho se estuda lento e na grade. Comece na semínima, com o metrônomo em 60, e só suba o tempo quando a mão não errar a digitação. A meta deste módulo é 100 BPM: você chega lá somando, não saltando. Se travar, volte uma subdivisão e reconquiste a precisão."),

        h ("A digitação da região"),
        p (
            "A digitação de uma região segue uma regra simples: um dedo por casa. Com a mão na posição, o indicador cobre a primeira casa da caixa, o médio a segunda, o anelar a terceira e o mindinho a quarta. Quando a escala pede uma nota fora dessas quatro casas, você não estica a mão: você muda de região. É essa disciplina que mantém a mão relaxada e a frase limpa."),
        p (
            "Há duas exceções úteis a essa regra. A primeira é a nota da casa anterior à posição, que muitas vezes é alcançada com o indicador esticado para trás, sem trocar de região. A segunda é a nota da quinta casa, alcançada com o mindinho esticado para a frente. Essas duas extensões dão à região uma borda flexível, e é nelas que a frase costuma respirar antes de viajar."),
        b ("Um dedo por casa: indicador, médio, anelar e mindinho cobrem quatro casas."),
        b ("As notas de borda (casa anterior e quinta casa) entram por extensão, sem trocar de região."),
        b ("Se a frase precisa de mais de duas casas fora da caixa, mude de região."),
        tbl ({ "Dedo", "Casa (região na casa 5)", "Observação" }, {
            { "Indicador", "casa 5", "pode esticar para a casa 4 (borda)" },
            { "Médio", "casa 6", "dedo central da região" },
            { "Anelar", "casa 7", "dedo mais forte da mão" },
            { "Mindinho", "casa 8", "pode esticar para a casa 9 (borda)" },
        }),

        h ("Erros comuns ao trabalhar com regiões"),
        p (
            "O erro mais frequente é tentar cobrir o braço inteiro com a mão parada numa posição. Isso força a mão a esticar demais, e a frase sai tensa e desafinada. A região é uma caixa, e a caixa tem limites: quando a frase precisa passar do limite, a mão viaja. Tentar contrariar isso é a receita para o cansaço e para a imprecisão."),
        p (
            "O segundo erro é trocar de região sem planejar. A troca precisa acontecer numa nota comum ou num tempo forte, nunca no meio de uma subida rápida. Quando a troca é planejada, o ouvido percebe a mudança como intenção musical; quando é improvisada na correria, ela soa como um tropeço da mão. Planejar a troca é parte de compor a frase."),
        c (
            "Estudo diário sugerido: toque a escala de Lá menor nas cinco regiões, subindo o braço, e depois improvise 8 compassos começando e terminando cada frase numa região diferente. O objetivo é que a mão reconheça a região sem que a cabeça precise contar casas."),

        h ("Da região ao mapa do braço"),
        p (
            "Quando você domina uma região, ela deixa de ser um lugar e vira uma referência. Você passa a pensar \"aqui é onde a frase repousa\" em vez de \"aqui é a casa 5\". Com o tempo, as regiões se encaixam umas nas outras e o braço inteiro vira um mapa contínuo, onde cada trecho tem a sua cor e o seu ponto de repouso. É esse mapa que sustenta todo o fraseado dos próximos módulos."),
        p (
            "O desenho por região é, por isso, a base de tudo o que vem neste módulo. As escalas ascendentes e descendentes ensinam a percorrer a região; as pentatônicas acrescentadas dão a cor; as trilhas mostram a outra dimensão; o Sistema 5 liga a região ao acorde; e as escalas menores especiais dão o caráter. Sem a região, nada disso tem onde morar."),


        h ("Onde a região começa e onde termina"),
        p (
            "Toda região tem um começo e um fim, e saber onde eles estão é o que evita que a mão se perca. O começo costuma ser a nota mais grave da escala naquela caixa; o fim, a nota mais aguda. Entre os dois, a mão fica parada e os dedos trabalham. Quando você conhece os limites, sabe também quando está prestes a sair da região — e pode decidir, com antecedência, se vai mudar de caixa ou voltar."),
        p (
            "Esse conhecimento dos limites é o que separa o fraseado controlado do fraseado errático. Quem não conhece os limites toca até a mão \"não ter mais para onde ir\", e a frase morre no fim da caixa. Quem conhece os limites planeja a virada: termina a ideia na borda e já entra na região seguinte pela nota comum. A frase flui, e o ouvinte nem percebe que a mão mudou de lugar."),
        p (
            "Uma boa prática é tocar a escala de cada região subindo até a última nota e descendo até a primeira, muitas vezes, até que os limites fiquem automáticos. Depois, improvise sempre começando e terminando dentro dos limites. Com o tempo, você sente a região sem precisar contar casas, e o braço inteiro passa a ser um mapa de caixas que a sua mão reconhece."),
        b ("Cada região tem começo (nota grave) e fim (nota aguda): conheça os dois."),
        b ("Planeje a virada na borda, entrando na região seguinte pela nota comum."),
        b ("Termine as frases dentro da região até que os limites fiquem automáticos."),
        tbl ({ "Limite", "O que fazer", "Resultado" }, {
            { "Borda grave", "estender o indicador ou mudar de região", "a frase continua para baixo" },
            { "Borda aguda", "estender o mindinho ou mudar de região", "a frase continua para cima" },
            { "Meio da caixa", "trabalhar os dedos, sem sair", "frases estáveis e controladas" },
        }),

        c (
            "Meta do módulo: 100 BPM. O desenho por região é a primeira coisa a ficar automática — sem ela, nada do resto do módulo se sustenta."),
    };
}

} // namespace cursomusica::content
