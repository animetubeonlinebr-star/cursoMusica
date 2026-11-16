#include "Course/Content/Topics.h"

// Topic 10C — Escolha modal (Módulo 10, Etapa 10).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 10) e o laboratório de
// standards (Maiden Voyage, Cantaloupe Island: escolha modal por acorde).
namespace cursomusica::content
{

std::vector<ContentItem> topic10C()
{
    return {

        p (
            "Escolha modal é decidir qual modo tocar sobre cada acorde. Parece um detalhe, mas muda tudo: o mesmo acorde menor com sétima aceita o modo dórico (com a sexta maior) ou o eólio (com a sexta menor), e a diferença é audível na hora. A escolha modal é a terceira pergunta da análise harmônica — a escala — levada a sério: em vez de tocar 'a escala da música', você escolhe o modo que combina com o acorde que está soando."),
        p (
            "Este tópico é o coração da sonoridade modal. Ele explica por que Maiden Voyage e Cantaloupe Island soam como um 'mar aberto': nelas não há função dominante pedindo resolução, e a música vive da cor de cada modo. Depois de dominar a escolha modal, você deixa de improvisar 'por cima da tonalidade' e passa a improvisar 'dentro do acorde'."),
        c (
            "Ideia central: o modo não vem da escala da música — vem do acorde. Cada acorde é um mundo sonoro, e você escolhe o modo que habita esse mundo."),

        h ("Modos: a mesma escala começando em lugares diferentes"),
        p (
            "Os sete modos gregos são as sete rotações da escala maior. O jônio (I) é a escala maior; o dórico (II) é a escala maior começando na segunda nota; o frígio (III) na terceira; o lídio (IV) na quarta; o mixolídio (V) na quinta; o eólio (VI) na sexta (a menor natural); o lócrio (VII) na sétima. Como são a mesma coleção de notas em ordens diferentes, cada modo tem uma cor própria dada por uma nota característica."),
        tbl ({ "Modo", "Grau de origem", "Nota característica", "Cor" }, {
            { "jônio", "I", "7ª maior", "maior, repouso" },
            { "dórico", "II", "6ª maior", "menor suave, jazz" },
            { "frígio", "III", "2ª menor", "menor espanhol" },
            { "lídio", "IV", "4ª aumentada", "maior flutuante" },
            { "mixolídio", "V", "7ª menor", "dominante, blues" },
            { "eólio", "VI", "6ª menor", "menor natural" },
            { "lócrio", "VII", "5ª diminuta", "tensão escura" },
        }),
        img ("m10_escolha_modal", "Qual modo sobre cada acorde: a nota característica é o que dá a cor de cada escolha modal."),

        h ("A nota característica decide a cor"),
        p (
            "Cada modo se distingue dos vizinhos por uma única nota: a nota característica. O dórico se distingue do eólio pela sexta (maior contra menor). O lídio se distingue do jônio pela quarta (aumentada contra justa). O mixolídio se distingue do jônio pela sétima (menor contra maior). Escolher um modo é escolher uma nota característica — e essa nota é a que você deve valorizar quando quer que a sonoridade apareça."),
        b ("Dórico × eólio: a sexta maior do dórico é o que dá o brilho jazzístico."),
        b ("Lídio × jônio: a quarta aumentada do lídio é o que dá o som flutuante."),
        b ("Mixolídio × jônio: a sétima menor do mixolídio é o que dá o som de blues."),
        aud ({ "D4", "F4", "A4", "B4", "C5" }, "Dórico sobre Dm7: repare na sexta maior (B). É ela que dá a cor dórica."),
        aud ({ "D4", "F4", "A4", "A#4", "C5" }, "Eólio sobre Dm7: agora a sexta é menor (Bb). Ouça como escurece."),
        p (
            "A escolha modal, portanto, não é arbitrária: ela vem do contexto. Se o acorde menor aparece num ii–V–I de jazz, o dórico é a escolha natural; se ele aparece num contexto de menor natural ou de rock, o eólio combina melhor. O mesmo acorde, duas cores diferentes — e você escolhe de propósito."),

        h ("Escolha modal por tipo de acorde"),
        p (
            "Existe uma tabela de partida para a escolha modal: cada qualidade de acorde sugere um modo. Sobre acordes de sétima maior, jônio ou lídio; sobre menores com sétima, dórico ou eólio; sobre dominantes, mixolídio, lídio b7 ou alterado; sobre meio-diminutos, lócrio. Essa tabela é o ponto de partida — o refinamento vem do contexto e da melodia."),
        tbl ({ "Acorde", "Modo padrão", "Modo alternativo", "Quando trocar" }, {
            { "Cmaj7", "jônio", "lídio", "quando o #11 é bem-vindo" },
            { "Cm7", "dórico", "eólio", "quando o contexto é menor natural" },
            { "C7", "mixolídio", "lídio b7 / alterado", "dominante que resolve" },
            { "Cm7b5", "lócrio", "lócrio #2", "preparação do menor" },
            { "Cdim7", "diminuta de tons", "—", "acorde de passagem" },
        }),
        c (
            "Escolher o modo é escolher o que valorizar. Sobre um Cm7 num ii–V, use o dórico e destaque a sexta maior; sobre um Cm7 de clima menor natural, use o eólio. O acorde é o mesmo; a cor, não."),

        h ("Escolha modal e o repertório"),
        p (
            "O repertório curado do curso é o laboratório da escolha modal. Em Maiden Voyage, os acordes sus (7sus4) pedem escalas sus: nem maior nem menor, mas suspensas. Em Cantaloupe Island, cada vamp pede um modo diferente — Fm7 (dórico), Db7 (lídio dominante) e Dm7 (dórico). Tocar 'a escala da música' ali soa errado; tocar o modo de cada acorde soa certo. É o mesmo princípio que você usará em qualquer música modal."),
        b ("Acordes sus: escala sus (sem terça definida), 4ª no lugar da 3ª."),
        b ("Lídio dominante (7#11): o #11 é a nota característica; destaque-a."),
        b ("Vamps modais: mantenha o mesmo modo por vários compassos e explore a cor."),
        aud ({ "D4", "G4", "A4", "C5", "D5" }, "Som sus (7sus4): a quarta no lugar da terça. Ouça a suspensão — nem maior, nem menor."),
        img ("m10_conexao_campos", "Os centros modais se ligam por acordes-pivo. A escolha modal acompanha cada centro."),

        h ("Como praticar a escolha modal"),
        p (
            "Praticar escolha modal é tocar o mesmo acorde com modos diferentes e ouvir a diferença. Pegue um vamp de Dm7 e toque o dórico por um minuto; depois toque o eólio; depois o frígio. Grave, escute e compare. Em seguida, faça o mesmo sobre um Cmaj7 (jônio × lídio) e sobre um C7 (mixolídio × lídio b7 × alterado). Esse treino constrói o vocabulário modal na orelha, não só na memória."),
        b ("Um acorde, vários modos: toque e compare."),
        b ("Destaque a nota característica para que a cor apareça."),
        b ("Grave e escute: a diferença entre modos é auditiva, não teórica."),
        c (
            "Nos exercícios, o app toca o vamp e verifica as notas que você toca. Escolha o modo certo para o acorde e destaque a nota característica: é assim que a escolha modal vira som."),

        h ("Erros comuns na escolha modal"),
        p (
            "O erro clássico é tocar sempre a escala da tonalidade, ignorando o acorde. Isso funciona num campo harmônico simples, mas destrói a sonoridade modal: sobre um dominante que resolve, a escala da tonalidade deixa passar notas que pedem alteração. O segundo erro é misturar modos sem critério, criando uma colcha de retalhos sem direção. O terceiro é escolher o modo e depois não valorizar a nota característica, de modo que a escolha fica imperceptível."),
        b ("Não toque a escala da tonalidade sobre acordes que pedem modo próprio."),
        b ("Mantenha um modo por trecho suficiente para que a cor se estabeleça."),
        b ("Valorize a nota característica; sem ela, a escolha modal não se ouve."),
        aud ({ "D4", "F4", "A4", "C5", "B4", "A4", "F4", "D4" },
             "Frase dórica sobre Dm7 destacando a sexta maior (B). Ouça a cor aparecer."),

        h ("Escolha modal como ferramenta de reharmonização"),
        p (
            "A escolha modal não serve só para improvisar: ela também é uma ferramenta de reharmonização. Trocar o modo de um acorde — mantendo o acorde, mas mudando a escala — já muda a sonoridade da música. Mais ainda: é a escolha modal que justifica substituições como o lídio b7 no lugar do mixolídio, ou o dórico no lugar do eólio. Nos tópicos G a I você vai reharmonizar; aqui você aprende a escolher a cor."),
        b ("Mudar o modo de um acorde muda a sonoridade sem trocar o acorde."),
        b ("A escolha modal justifica substituições de escala (lídio b7, alterada)."),
        b ("A cor é uma decisão de análise, não um acidente."),
        part ("m10_partitura_modal", { "D4", "F4", "A4", "B4", "C5", "A4", "F4", "D4" },
              "Partitura: uma frase dórica sobre Dm7, destacando a sexta maior. Ouça a escolha modal em ação."),

        h ("Modos e a escala da tonalidade: o que muda"),
        p (
            "É comum o iniciante confundir 'escala da música' com 'escala do acorde'. Num campo harmônico simples (um ii–V–I em Dó), as duas coincidem: todos os acordes vêm da escala de Dó, então tocar Dó maior funciona em cima de todos. Mas quando a música sai do campo — um dominante alterado, um empréstimo modal, um acorde sus —, a escala da tonalidade deixa de servir. A escolha modal resolve isso: você troca a escala fixa pela escala do acorde, e o improviso acompanha a harmonia em vez de ignorá-la."),
        tbl ({ "Situação", "Escala da tonalidade serve?", "O que usar" }, {
            { "acordes do campo (I, ii, V)", "sim", "a escala da tonalidade já resolve" },
            { "dominante que resolve (V7alt)", "não", "a escala alterada do acorde" },
            { "acorde sus (7sus4)", "não", "a escala sus, sem terça" },
            { "empréstimo modal (iv, VI)", "não", "o modo do acorde emprestado" },
            { "vamp modal estático", "não", "o modo do vamp, mantido" },
        }),
        b ("No campo harmônico simples, a escala da tonalidade basta."),
        b ("Fora do campo, a escala do acorde é que manda."),
        b ("Escolha modal = trocar a escala fixa pela escala de cada acorde."),
        aud ({ "G3", "A#3", "C#4", "D#4", "F4" },
             "Escala alterada sobre um G7 que resolve: ouça a tensão apontando para o C."),

        h ("Escolha modal na prática: um vamp, vários modos"),
        p (
            "O exercício mais direto de escolha modal é tocar o mesmo vamp com modos diferentes. Pegue um Dm7 e toque o dórico por alguns compassos; depois toque o eólio; depois o frígio. Grave e compare. Você vai ouvir que o dórico soa jazzístico e suave, o eólio soa menor natural e o frígio soa espanhol. O acorde é o mesmo; a cor, três vezes diferente. Esse treino constrói o vocabulário modal na orelha — e é o que permite, depois, escolher o modo certo por instinto."),
        b ("Um acorde, vários modos: toque e compare."),
        b ("Destaque a nota característica para que a diferença apareça."),
        b ("Grave e escute: a cor modal é auditiva."),
        c (
            "Nos exercícios, o app toca o vamp e verifica as notas que você toca. Escolha o modo certo para o acorde e destaque a nota característica."),

        h ("Escolha modal e tensão"),
        p (
            "A escolha modal também decide quais tensões você usa. Sobre um acorde de sétima maior, o jônio aceita a nona e a décima terceira; o lídio acrescenta a quarta aumentada. Sobre um dominante, o mixolídio aceita a nona e a décima terceira, enquanto a escala alterada acrescenta b9, #9, #11 e b13. Escolher o modo é escolher o conjunto de tensões disponíveis — e é isso que dá o tempero do improviso. Uma escolha modal consciente sabe exatamente quais tensões estão em jogo."),
        tbl ({ "Modo", "Tensões disponíveis", "Som" }, {
            { "jônio", "9, 13 (11 evitada)", "maior limpo" },
            { "lídio", "9, #11, 13", "maior flutuante" },
            { "dórico", "9, 11, 13", "menor rico" },
            { "mixolídio", "9, 13 (11 evitada)", "dominante suave" },
            { "alterada", "b9, #9, #11, b13", "dominante tenso" },
        }),
        b ("Cada modo traz um conjunto de tensões."),
        b ("Escolher o modo é escolher o tempero do improviso."),
        b ("As tensões certas fazem a cor modal aparecer."),
        aud ({ "C4", "E4", "G4", "B4", "D5", "F#5" },
             "Lídio sobre C7M: a quarta aumentada (F#) é a nota característica. Ouça o brilho flutuante."),

        h ("Escolha modal e a melodia"),
        p (
            "A escolha modal não vive só no improviso: ela também decide como você harmoniza a melodia. Se a melodia toca uma nota característica de um modo, a harmonia deve acomodá-la. Uma melodia que insiste na quarta aumentada pede um acorde lídio; uma que valoriza a sexta maior pede um dórico. Escolher o modo certo é o que faz a melodia e a harmonia combinarem em vez de brigarem. É por isso que a escolha modal e a análise melódica (tópico B) andam juntas: uma revela as notas, a outra escolhe a cor."),
        b ("A melodia revela o modo: valorize a nota característica que ela toca."),
        b ("Escolher o modo certo faz melodia e harmonia combinarem."),
        b ("Escolha modal e análise melódica trabalham juntas."),
        aud ({ "D4", "F4", "A4", "B4", "D5" }, "Uma melodia que valoriza a sexta maior (B): o dórico acomoda essa nota. Ouça a coerência."),

        h ("Resumo do tópico"),
        b ("Escolha modal é decidir qual modo tocar sobre cada acorde."),
        b ("O modo vem do acorde, não da escala da música."),
        b ("Cada modo se distingue pela nota característica; valorize-a."),
        b ("Existe uma tabela de partida por qualidade de acorde, refinada pelo contexto."),
        b ("A escolha modal é a base da sonoridade e uma ferramenta de reharmonização."),
        c (
            "Objetivo do tópico: parar de improvisar 'por cima da tonalidade' e passar a improvisar 'dentro do acorde', escolhendo a cor de cada momento."),
    };
}

} // namespace cursomusica::content
