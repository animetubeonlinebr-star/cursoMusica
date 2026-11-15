#include "Course/Content/Topics.h"

// Topic 5H — Cadências e progressões harmônicas (Módulo 5, Etapa 5).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 5, bloco H).
namespace cursomusica::content
{

std::vector<ContentItem> topic5H()
{
    return {

        p (
            "As cadências são as fórmulas de movimento da harmonia. Se as funções (tônica, subdominante, dominante) são os papéis, as cadências são as frases que combinam esses papéis em sequências que soam naturais. Toda música que você conhece usa um punhado de cadências — e reconhecê-las é reconhecer a estrutura por baixo da melodia."),
        p (
            "Neste tópico você aprende as cadências mais importantes, o que cada uma comunica e como usá-las para construir progressões. É também o tópico que prepara o gate do módulo: a progressão do desafio final é uma cadência construída com o material que você estudou."),

        h ("O que é uma cadência"),
        p (
            "Cadência é uma fórmula de dois ou mais acordes que cria um efeito de conclusão, de suspensão ou de continuidade. Em outras palavras: é uma 'pontuação' harmônica. Assim como uma frase escrita termina em ponto, vírgula ou ponto de interrogação, uma frase musical termina com uma cadência que diz ao ouvido se a música acabou, se continua ou se está pedindo algo."),
        p (
            "As cadências nascem da combinação das funções. Toda cadência é, no fundo, um encadeamento de tônica, subdominante e dominante em alguma ordem. Aprender a reconhecer essas combinações é aprender a 'ler' a harmonia de uma música — mesmo sem partitura, só pelo ouvido."),
        b ("Cadência = fórmula harmônica que cria conclusão, suspensão ou continuidade."),
        b ("Combina as funções tônica, subdominante e dominante."),
        b ("Funciona como a pontuação de uma frase musical."),
        img ("m5_cadencias", "As principais cadências: autêntica, plagal, meia cadência e de engano — cada uma com um efeito diferente."),

        h ("A cadência autêntica (V → I)"),
        p (
            "A cadência autêntica é o V → I, a resolução do dominante na tônica. É a cadência mais forte e mais conclusiva da música tonal. Quando você ouve uma música 'terminar', na maioria das vezes está ouvindo um V → I. É a fórmula que dá a sensação de ponto final."),
        p (
            "A cadência autêntica pode aparecer de duas formas: perfeita, quando os acordes estão na posição fundamental e a melodia termina na tônica, criando a conclusão máxima; e imperfeita, quando há uma inversão ou a melodia termina em outra nota, criando uma conclusão um pouco menos definitiva. No dia a dia, você vai usar as duas."),
        b ("V → I: resolução do dominante na tônica."),
        b ("É a cadência mais conclusiva (ponto final)."),
        b ("Perfeita quando os acordes estão na fundamental e a melodia fecha na tônica."),
        aud ({ "G4", "B4", "D5", "C5", "E5", "G5" },
             "Cadência autêntica: G (V) resolve em C (I). O som de ponto final."),

        h ("A cadência plagal (IV → I)"),
        p (
            "A cadência plagal é o IV → I, a resolução da subdominante direto na tônica. Ela é mais suave que a autêntica, sem a tensão do dominante. É por isso que a cadência plagal soa como um 'amém' — um encerramento sereno, usado em hinos e em músicas que querem terminar com tranquilidade, sem drama."),
        p (
            "A diferença entre a cadência autêntica e a plagal é justamente a presença do dominante. A autêntica passa pela tensão antes de resolver; a plagal vai da subdominante direto para a tônica, o que dá uma sensação de repouso mais imediato e menos elaborado. Ambas fecham, mas com climas diferentes."),
        b ("IV → I: resolução da subdominante na tônica."),
        b ("Mais suave que a autêntica, sem a tensão do dominante."),
        b ("Soa como um encerramento sereno ('amém')."),
        aud ({ "F4", "A4", "C5", "C5", "E5", "G5" },
             "Cadência plagal: F (IV) resolve em C (I). O som de encerramento suave."),

        h ("A meia cadência (I → V)"),
        p (
            "A meia cadência é o I → V, que termina no dominante em vez de resolver. Ela não fecha a frase: deixa a música suspensa, pedindo continuação. É a 'vírgula' da harmonia. Aparece no meio de frases musicais, preparando a segunda metade, e é muito usada para criar expectativa antes de uma resolução."),
        p (
            "Reconhecer a meia cadência é importante porque ela é o oposto da conclusão. Quando a música termina uma seção no dominante, o ouvido sente que ainda falta algo — e é justamente essa falta que empurra a música para a seção seguinte. Sem a meia cadência, as músicas soariam como uma sequência de pontos finais."),
        b ("I → V: termina no dominante, sem resolver."),
        b ("É a 'vírgula' da harmonia: deixa a música suspensa."),
        b ("Cria expectativa para a seção seguinte."),
        aud ({ "C4", "E4", "G4", "G4", "B4", "D5" },
             "Meia cadência: C (I) indo para G (V). A frase fica em suspenso, pedindo continuação."),

        h ("A cadência de engano (V → vi)"),
        p (
            "A cadência de engano é o V → vi: o dominante resolve, mas não na tônica, e sim no relativo menor. O ouvido espera o I e recebe o vi, o que produz uma surpresa agradável — por isso o nome 'de engano'. É um recurso expressivo muito usado para adiar a conclusão e prolongar a música."),
        p (
            "Como o vi compartilha notas com o I, a cadência de engano não soa errada: soa apenas inesperada. Em vez de fechar, ela dá uma guinada na cor da música e mantém o movimento. É uma das ferramentas mais úteis para quem quer escrever progressões que não terminam cedo demais."),
        b ("V → vi: o dominante resolve no relativo menor."),
        b ("Surpreende o ouvido, que esperava a tônica."),
        b ("Adia a conclusão e prolonga a música."),
        aud ({ "G4", "B4", "D5", "A3", "C4", "E4" },
             "Cadência de engano: G (V) resolve em Am (vi), não em C. O ouvido é surpreendido."),
        part ("m5_partitura_cadencia", { "C4", "E4", "G4", "G4", "B4", "D5", "C5", "E5", "G5" },
              "Partitura de I – V – I: a cadência autêntica preparada pela tônica. Ouça a resolução."),

        h ("Progressões harmônicas comuns"),
        p (
            "Uma progressão é uma sequência de acordes que se repete ao longo da música. As mais comuns nascem das cadências: I – IV – V – I, ii – V – I, I – vi – IV – V e I – V – vi – IV. Cada uma tem um caráter próprio, mas todas usam as mesmas três funções em ordens diferentes."),
        p (
            "Aprender essas progressões é aprender o vocabulário básico do acompanhamento. Com elas você acompanha uma enorme quantidade de músicas e pode começar a reconhecer, de ouvido, o que está acontecendo na harmonia. É por isso que os exercícios deste módulo insistem em tocar progressões e deixar o app conferir."),
        tbl ({ "Progressão", "Graus", "Caráter" }, {
            { "Clássica", "I – IV – V – I", "conclusiva, direta" },
            { "Jazz", "ii – V – I", "preparada, com movimento" },
            { "Pop", "I – V – vi – IV", "circular, sempre em aberto" },
            { "Décadas", "I – vi – IV – V", "nostálgica, ciclo de retorno" },
        }),
        c (
            "Todas essas progressões usam as mesmas três funções. O que muda é a ordem e o ponto em que a música respira. Reconhecer a função de cada acorde é mais útil do que decorar as progressões."),

        h ("Cadências e frases musicais"),
        p (
            "As cadências marcam as frases da música. Uma frase musical típica tem duas partes: a primeira termina em meia cadência (suspensa) e a segunda termina em cadência autêntica (conclusiva). Esse par — pergunta e resposta — é a estrutura básica de incontáveis músicas, do clássico ao pop."),
        p (
            "Perceber essa estrutura muda a forma como você ouve música. Em vez de um fluxo contínuo de acordes, você passa a ouvir blocos que começam, desenvolvem e fecham. Essa consciência é o que permite acompanhar uma música de ouvido, prever o próximo acorde e até improvisar sobre a harmonia com segurança."),
        b ("Frase típica: primeira metade em meia cadência, segunda em autêntica."),
        b ("A meia cadência cria a pergunta; a autêntica, a resposta."),
        b ("Ouvir cadências permite prever o próximo acorde."),

        h ("Aplicando as cadências na prática"),
        p (
            "Na prática, você usa as cadências para dar forma às suas progressões. Comece tocando I – IV – V – I e sinta a conclusão. Depois experimente I – IV – V – vi e sinta a surpresa. Troque o final para IV – I e sinta a suavidade da plagal. Essas pequenas variações são o que dão personalidade a uma música."),
        p (
            "Os exercícios deste tópico pedem que você toque progressões e cadências no instrumento, e o app confere os acordes reconhecidos. O gate do módulo fecha com uma progressão do campo maior tocada na grade do metrônomo, cobrando a execução completa das funções estudadas."),
        b ("Toque I – IV – V – I e sinta a conclusão da cadência autêntica."),
        b ("Troque o final para V – vi e sinta a cadência de engano."),
        b ("Confirme no app se os acordes tocados correspondem à progressão."),
        img ("m5_progressao_padrao", "Uma progressão I – IV – V – I no braço, com as funções marcadas sobre cada acorde."),

        h ("Progressões na prática do acompanhamento"),
        p (
            "Na prática do acompanhamento, as progressões são o que você toca o tempo todo. Saber de cor as progressões mais comuns — I – IV – V – I, ii – V – I, I – vi – IV – V, I – V – vi – IV — permite acompanhar uma enorme quantidade de músicas sem partitura. São os 'chavões' da harmonia, e conhecê-los é parte do vocabulário de qualquer músico."),
        p (
            "O segredo é reconhecer a progressão pela função, e não pelo nome dos acordes. Se você ouve que a música vai de repouso para afastamento, depois para tensão e volta ao repouso, você já sabe que é um I – IV – V – I, mesmo sem saber o tom. A função é a mesma em qualquer tonalidade; só os nomes mudam."),
        b ("As progressões mais comuns cobrem grande parte do repertório."),
        b ("Reconheça a progressão pela função, não pelo nome do acorde."),
        b ("I – IV – V – I, ii – V – I e I – V – vi – IV são as mais frequentes."),
        aud ({ "C4", "E4", "G4", "G4", "B4", "D5", "A3", "C4", "E4", "F4", "A4", "C5" },
             "I – V – vi – IV: a progressão pop mais usada, dentro do campo de Dó."),

        h ("Cadências e forma musical"),
        p (
            "As cadências não são apenas fórmulas harmônicas: elas estruturam a forma da música. Uma música em duas partes costuma ter a primeira parte terminando em meia cadência (suspensa) e a segunda terminando em cadência autêntica (conclusiva). Essa estrutura de pergunta e resposta é a base de incontáveis músicas, do clássico ao pop."),
        p (
            "Perceber as cadências permite entender onde estão as seções de uma música. Quando você ouve uma cadência autêntica forte, é sinal de que uma seção terminou; uma meia cadência indica que a música está no meio de uma frase. Essa consciência da forma é o que permite acompanhar uma música inteira sem se perder."),
        b ("As cadências marcam o fim das frases e das seções."),
        b ("Autêntica = fim de seção; meia cadência = meio de frase."),
        b ("A forma em duas partes usa meia cadência e depois autêntica."),
        c (
            "Ouvir cadências é ouvir a pontuação da música. Uma vez que você reconhece onde a música 'respira', acompanhar, improvisar e até prever o próximo acorde ficam muito mais fáceis."),

        h ("Resumo do tópico"),
        b ("Cadência é a pontuação da frase musical."),
        b ("Autêntica (V → I): conclusão forte. Plagal (IV → I): conclusão suave."),
        b ("Meia cadência (I → V): suspensão. De engano (V → vi): surpresa."),
        b ("As progressões comuns combinam as funções em ordens conhecidas."),
        b ("As cadências marcam as frases: pergunta (meia) e resposta (autêntica)."),
        c (
            "Nos exercícios deste tópico, toque as cadências e progressões no instrumento. O app reconhece as notas e confere se a progressão está sendo executada na ordem correta."),
    };
}

} // namespace cursomusica::content
