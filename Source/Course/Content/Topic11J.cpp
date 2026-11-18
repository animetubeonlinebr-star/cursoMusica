#include "Course/Content/Topics.h"

// Topic 11J — Relação entre escalas e acordes (Módulo 11, Etapa 11).
// Fecha o módulo: a escala escolhida nasce do acorde, e é essa escolha que
// define as notas de repouso e as notas de tensão do improviso (REQ-011/012).
namespace cursomusica::content
{

std::vector<ContentItem> topic11J()
{
    return {

        p (
            "Este tópico fecha a Etapa 11 amarrando tudo: a escala não é escolhida no vácuo, ela nasce do acorde. Para cada acorde existe uma escala que combina, e é essa escala que define quais notas repousam e quais pedem resolução. Aprender a relação escala-acorde é o que transforma o fraseado de \"tocar a escala certa\" em \"dizer algo sobre a harmonia\"."),
        p (
            "E é aqui que o módulo encontra o improviso. Quando você improvisa sobre um vamp, o acorde em vigor define a escala, a escala define as notas de repouso e de tensão, e a frase precisa respeitar isso. Este é o primeiro módulo com avaliação de improvisação de verdade: o app vai ouvir o que você toca e verificar se você está dentro ou fora do centro."),
        c (
            "Regra central: a escala vem do acorde. Sobre um acorde menor, a pentatônica menor e a menor natural/dórica; sobre um 7M, a maior/lídia; sobre um dominante, a mixolídia/alterada. Escolher o acorde é escolher a escala — e as notas de repouso."),

        h ("Cada acorde, a sua escala"),
        p (
            "A relação escala-acorde é o coração do fraseado tonal. Um acorde de sétima maior pede a escala maior (ou lídia); um acorde menor pede a menor natural, a dórica ou a pentatônica menor; um dominante pede a mixolídia, e — quando alterado — a escala alterada. A escala certa faz as notas do acorde caírem em pontos de repouso e as tensões soarem como tensões."),
        p (
            "O erro do iniciante é tocar a mesma escala sobre acordes diferentes. Isso funciona no vamp de um só acorde, mas quebra quando a harmonia muda. Ao ouvir a mudança de acorde, a sua escala tem que mudar — ou, no mínimo, a sua frase tem que apontar para as novas notas de repouso."),
        b ("Acorde de sétima maior (7M): escala maior ou lídia."),
        b ("Acorde menor (m7): menor natural, dórica ou pentatônica menor."),
        b ("Acorde dominante (7): mixolídia; alterado quando pede tensão."),
        b ("A escala escolhida define as notas de repouso da frase."),
        img ("m11_escala_acorde", "Relação escala-acorde: cada tipo de acorde pede uma escala, e a escala define onde estão as notas de repouso."),

        h ("Notas de repouso e notas de tensão"),
        p (
            "Dentro da escala escolhida, algumas notas repousam e outras pedem resolução. As notas do acorde (fundamental, terça, quinta e sétima) são repouso. As demais notas da escala são tensões de cor, aceitas no contexto. E as notas fora da escala são tensões não pedidas — erros, a menos que sejam passagens cromáticas que resolvem."),
        p (
            "É exatamente essa classificação que o app usa para avaliar o seu improviso neste módulo (REQ-011, REQ-012). Você toca livremente sobre o vamp; o app compara cada nota com o acorde e a escala em vigor e diz se você repousou, pediu tensão ou saiu do centro. Tocar fora do centro — sem pedir — conta como erro."),
        tbl ({ "Situação da nota", "Veredito" }, {
            { "Pertence ao acorde (1, 3, 5, 7)", "repouso — aceita" },
            { "Pertence à escala do centro", "repouso de cor — aceita" },
            { "Tensão pedida pelo exercício", "aceita" },
            { "Fora do centro, não pedida", "erro" },
            { "Passagem cromática que resolve", "aceita (passagem)" },
        }),
        c (
            "Notas de tensão (REQ-012): só são aceitas quando o estado de improviso pede o seu uso, ou quando fazem parte do acorde. Fora disso, tensão não pedida é erro. O improviso deste módulo roda sobre um vamp tonal, então as notas de repouso são as do acorde e da escala em vigor."),

        h ("O lick deste tópico"),
        p (
            "O lick abaixo é uma frase que mistura repouso e tensão sobre um vamp de Lá menor: começa na escala (repouso), passa por uma tensão de cor (a sexta) e resolve numa nota do acorde. É um gesto de fraseado sobre vamp modal, na linha de Santana — frases cantáveis que respiram sobre um só centro. Ouça como a frase sabe quando repousar e quando pedir."),
        aud ({ "A4", "C5", "D5", "E5", "D5", "C5", "A4", "E5", "D5", "C5", "A4" },
             "Lick do tópico J: frase sobre o vamp de Lá menor. As notas do acorde repousam; a sexta é tensão de cor; a frase resolve no A."),
        part ("m11_partitura_j", { "A4", "C5", "D5", "E5", "D5", "C5", "A4", "E5", "D5", "C5", "A4" },
              "Partitura do lick J: frase de repouso e tensão sobre o vamp. A resolução cai numa nota do acorde."),

        h ("O vamp tonal deste módulo"),
        p (
            "O módulo começa a usar vamps — trechos harmônicos que se repetem para o aluno improvisar sobre eles. Os vamps deste módulo ainda são tonais (um centro definido, um acorde menor ou maior), mas já preparam os vamps modais das etapas seguintes. Sobre o vamp, você toca a escala do acorde e a frase respeita as notas de repouso."),
        p (
            "O vamp de Lá menor é o laboratório: o acorde é Am7, a escala é a de Lá menor (natural, dórica ou pentatônica), e as notas de repouso são A, C, E e G. Tudo o que você toca é comparado a esse centro. Improvisar sobre o vamp é a prova final de que as escalas deste módulo viraram referências para a frase."),

        h ("A escala como escolha consciente"),
        p (
            "Escolher a escala sobre um acorde é uma decisão consciente, não um acaso. Sobre um acorde maior, você pode usar a maior (sons mais estáveis) ou a lídia (com a quarta aumentada, mais etérea). Sobre um menor, pode escolher entre a menor natural, a dórica (com a sexta maior) ou a pentatônica (mais enxuta). Cada escolha muda as notas de repouso e as tensões."),
        p (
            "O improvisador experiente não toca \"a escala da música\"; toca a escala do acorde que está soando. Quando o acorde muda, a escala muda, e com ela mudam as notas de repouso. É essa sensibilidade harmônica que faz o solo soar \"dentro\" da música, e não apenas \"em cima\" dela. É o objetivo do fraseado tonal deste módulo."),
        b ("A escala vem do acorde, não da música inteira."),
        b ("Cada escala traz o seu conjunto de notas de repouso e tensões."),
        b ("Trocar de acorde é trocar de escala — e de notas de repouso."),
        tbl ({ "Tipo de acorde", "Escala", "Repouso", "Tensão típica" }, {
            { "7M", "maior / lídia", "1 3 5 7", "4 (lídia), 6" },
            { "m7", "dórica / menor", "1 b3 5 b7", "9, 11, 13" },
            { "7", "mixolídia / alterada", "1 3 5 b7", "b9, #9, #11, b13" },
            { "m7(b5)", "lócrio", "1 b3 b5 b7", "11 (natural)" },
        }),

        h ("Repouso e tensão na prática"),
        p (
            "Na prática, o improvisador alterna repouso e tensão de forma consciente. Ele repousa nas notas do acorde (sobretudo nos tempos fortes) e usa as tensões nas passagens, resolvendo sempre. É esse vaivém que dá à frase um sentido de movimento: a tensão cria a expectativa e o repouso a satisfaz. Uma frase sem repouso soa ansiosa; uma frase sem tensão soa monótona."),
        p (
            "A avaliação deste módulo captura exatamente isso. O app classifica cada nota que você toca: repouso (acorde ou escala), tensão pedida (quando o exercício solicita) e erro (tensão não pedida, fora do centro). Tocar dentro do centro é o que faz a frase passar. É a primeira vez que o app avalia improvisação de verdade — e o critério é o mesmo que os músicos usam."),
        c (
            "Repouso × tensão (REQ-011/REQ-012): repouse nas notas do acorde nos tempos fortes; use as tensões nas passagens e resolva. A tensão não pedida, fora do centro, conta como erro. Este é o critério que o app aplica ao seu improviso."),

        h ("Improvisar é conversar"),
        p (
            "Improvisar sobre uma harmonia é como conversar: você ouve o que a música diz (os acordes) e responde com frases que fazem sentido naquele contexto. As notas de repouso são as palavras que todos entendem; as tensões são as ideias novas, que precisam ser bem colocadas para não soar fora de propósito. Uma boa improvisação equilibra o familiar e o novo."),
        p (
            "É por isso que este módulo termina aqui, na relação escala-acorde. Tudo o que você estudou — desenhos, trilhas, pentatônicas, Sistema 5, menores especiais — serve para dar vocabulário à conversa. Agora você tem as ferramentas; o próximo passo é usá-las sobre vamps cada vez mais ricos, nos módulos de blues e de standards. A improvisação começa a sério aqui."),


        h ("Construindo frases com repouso e tensão"),
        p (
            "Uma frase bem construída alterna repouso e tensão como uma conversa alterna afirmações e perguntas. Você começa num repouso (uma nota do acorde), cria uma tensão (uma nota de passagem ou uma cor) e volta ao repouso. É esse ciclo que dá à frase um sentido de direção. Frases que só repousam soam monótonas; frases que só tensionam soam ansiosas. O equilíbrio é o que faz a música respirar."),
        p (
            "Na prática, os tempos fortes pedem repouso e as passagens pedem tensão. Colocar uma nota do acorde no tempo forte ancora a frase; usar uma tensão na passagem e resolvê-la no tempo forte seguinte dá movimento. É essa distribuição — repouso onde a música \"pesa\", tensão onde ela \"corre\" — que faz o solo soar dentro da harmonia, e não apenas por cima dela."),
        p (
            "O app avalia exatamente essa distribuição. Cada nota que você toca é classificada: repouso (acorde ou escala), tensão pedida (quando o exercício solicita) e erro (tensão não pedida). Tocar respeitando a harmonia é o que faz a frase passar. É a primeira vez que a avaliação de improvisação entra no curso — e o critério é o mesmo que um músico usaria para julgar um solo."),
        b ("Alterne repouso e tensão: repouse nos tempos fortes, tensione nas passagens."),
        b ("Resolva sempre a tensão no repouso seguinte, para dar direção à frase."),
        b ("O app classifica cada nota: repouso, tensão pedida ou erro."),
        tbl ({ "Momento", "Nota típica", "Efeito" }, {
            { "Tempo forte", "nota do acorde (repouso)", "ancora a frase" },
            { "Passagem", "tensão ou cor", "cria movimento" },
            { "Chegada", "tônica (repouso)", "fecha a ideia" },
        }),


        h ("O centro tonal e o ouvido"),
        p (
            "Improvisar dentro do centro tonal é aprender a ouvir a harmonia. O centro é o conjunto de notas que soam em casa sobre um acorde; fora dele, as notas soam como visitantes. O ouvido reconhece o centro mesmo sem pensar: você sabe quando uma nota está bem e quando está pedindo resolução. Tocar dentro do centro é tocar de acordo com o que o ouvido já sabe."),
        p (
            "Desenvolver esse ouvido exige prática deliberada. Toque uma nota e pergunte: ela repousa ou tensiona? Toque o acorde e cante a tônica; depois cante a terça, a quinta, a sétima. Você está mapeando as notas de repouso do acorde no seu ouvido. Quando esse mapa estiver firme, a improvisação deixa de ser cálculo e passa a ser intuição treinada."),
        p (
            "O app avalia exatamente esse mapeamento. Cada nota que você toca é classificada contra o centro: repouso, tensão pedida ou erro. Se a sua frase respeita o centro, ela passa. É a avaliação de improvisação que o curso prometia, e ela chega aqui, no fim do módulo 11, quando você já tem o vocabulário de escalas para improvisar com sentido."),
        b ("O centro tonal é o conjunto de notas que soam em casa sobre o acorde."),
        b ("Treine o ouvido perguntando, nota a nota, se ela repousa ou tensiona."),
        b ("O app classifica cada nota contra o centro: repouso, tensão pedida ou erro."),
        tbl ({ "Nota tocada", "Relação com o centro", "Veredito" }, {
            { "Nota do acorde", "repouso", "aceita" },
            { "Nota da escala", "repouso de cor", "aceita" },
            { "Tensão não pedida", "fora do centro", "erro" },
        }),

        c (
            "Meta do módulo: 100 BPM. O objetivo da Etapa 11 está cumprido quando você improvisa sobre o vamp tocando dentro do centro, resolvendo nas notas de repouso e usando as tensões só quando a frase pede."),
    };
}

} // namespace cursomusica::content
