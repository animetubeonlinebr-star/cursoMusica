#include "Course/Content/Topics.h"

// Topic 9H — Relacoes entre campos harmonicos (Modulo 9, Etapa 9).
// Fonte de verdade do texto: docs/MUSIC.md (bloco H da Etapa 9).
namespace cursomusica::content
{

std::vector<ContentItem> topic9H()
{
    return {

        p (
            "Você já conhece vários campos harmônicos: o maior, o menor, os modos e os campos diminutos. Neste tópico o objetivo é olhar para as relações entre eles. Dois campos podem compartilhar acordes, e esses acordes comuns são as pontes que permitem passar de um campo para outro sem que a música perca a coerência."),
        p (
            "Entender as relações entre campos é o que permite modular, rearmonizar e improvisar com liberdade. Não se trata de decorar listas, mas de perceber quais acordes conectam duas tonalidades."),

        h ("Campos vizinhos no círculo das quintas"),
        p (
            "O círculo das quintas organiza as tonalidades pela distância entre elas. Duas tonalidades vizinhas no círculo — como Do maior e Sol maior — compartilham seis das sete notas. A diferença é apenas uma nota: em Do maior existe Fa natural; em Sol maior, Fa sustenido. Por compartilharem tanto, os dois campos tem muitos acordes em comum."),
        b ("Tonalidades vizinhas compartilham seis das sete notas."),
        b ("A diferença é uma única nota (a sensível de cada uma)."),
        b ("Por isso a modulação entre vizinhas é suave."),
        img ("m9_relacoes_campos", "Campos vizinhos no círculo das quintas compartilham quase todas as notas."),
        aud ({ "C4", "E4", "G4", "B4", "D5", "F#5" },
             "Do maior e Sol maior lado a lado: as duas tonalidades soam proximas."),

        h ("O acorde pivô"),
        p (
            "Um acorde pivô é um acorde que pertence aos dois campos ao mesmo tempo. Ele serve de ponte: tocar um acorde pivô prepara o ouvido para a nova tonalidade antes que ela chegue. Em Do maior e Sol maior, os acordes pivô são C, Em, G e Am. Eles existem nos dois campos e por isso podem ser usados para transitar entre eles."),
        tbl ({ "Campo", "Acordes", "Pivôs com Do maior" }, {
            { "Do maior", "C Dm Em F G Am Bdim", "-" },
            { "Sol maior", "G Am Bm C D Em F#dim", "G Am C Em" },
            { "Fa maior", "F Gm Am Bb C Dm Edim", "F Am C Dm" },
        }),
        c (
            "Achar o acorde pivô é o primeiro passo de qualquer modulação. Ele é o ponto onde os dois campos se tocam."),

        h ("Modulação por dominante secundário"),
        p (
            "Além do acorde pivô, existe a modulação por dominante secundário. Em vez de passar suavemente, o músico toca o dominante da nova tônica, criando uma chegada forte. Em Do maior, para modular a Sol maior, toca-se D7 (o dominante de Sol) antes de chegar ao Sol. Esse D7 é o dominante secundário, e ele sinaliza a nova tonalidade."),
        b ("Dominante secundario: o V7 da nova tônica."),
        b ("Cria uma chegada forte a nova tonalidade."),
        b ("E o recurso mais direto de modulação."),
        aud ({ "D4", "F#4", "A4", "C5", "G4", "B4", "D5" },
             "D7 (dominante de Sol) resolvendo em Sol: a modulação fica clara."),

        h ("Modulação por diminuto"),
        p (
            "O diminuto é outra ponte entre campos. Como cada dim7 serve a quatro tonalidades, ele pode ser usado para ligar campos distantes. Um dim7 comum a duas tonalidades cria uma transição elegante, porque o ouvido reconhece as notas sem saber ainda para onde a música vai. Esse é um recurso típico da música instrumental e do jazz."),
        b ("O dim7 comum a duas tonalidades liga os dois campos."),
        b ("A transição é elegante porque o ouvido não prevê o destino."),
        b ("Use o ciclo das terças menores para achar o dim7 comum."),
        aud ({ "C#4", "E4", "G4", "A#4", "C5" },
             "Um dim7 conduzindo a Do: a ponte entre campos distantes."),

        h ("Campos relativos"),
        p (
            "Dois campos são relativos quando compartilham a mesma armadura de clave. Do maior e Lá menor são relativos: as duas usam as mesmas notas, mas com centros tonais diferentes. Os acordes são os mesmos, o que muda é a importância de cada um. Essa relação permite que uma música flutue entre os dois campos sem modulação abrupta."),
        b ("Relativos compartilham as mesmas notas."),
        b ("O que muda é o centro tonal, não o material."),
        b ("A música pode transitar entre os dois sem modulação abrupta."),

        h ("Campos homônimos"),
        p (
            "Dois campos são homônimos quando tem a mesma tônica, mas modos diferentes. Do maior e Do menor são homônimos: a tônica é a mesma, mas o terceiro grau muda (Mi no maior, Mib no menor). Os campos homônimos compartilham poucos acordes, mas a troca entre eles é muito expressiva, porque muda a cor sem mudar o centro."),
        tbl ({ "Relação", "O que compartilham", "Efeito da troca" }, {
            { "Vizinhos", "seis das sete notas", "modulação suave" },
            { "Relativos", "as mesmas sete notas", "mudança de centro tonal" },
            { "Homônimos", "a tônica", "mudança de cor (maior/menor)" },
            { "Distantes", "pouco ou nada", "modulação precisa de preparação" },
        }),
        c (
            "Quanto mais notas dois campos compartilham, mais suave a passagem entre eles. Quanto menos, mais preparação a modulação exige."),

        h ("Como usar as relações na prática"),
        p (
            "Comece tocando uma progressão em Do maior e depois module para Sol maior usando um acorde pivô. Repita a modulação, mas agora com o dominante secundário D7, e compare a sensação. Depois, experimente a modulação por diminuto. Cada caminho dá uma sensação diferente de chegada."),
        b ("Module com acorde pivô: transição suave."),
        b ("Module com dominante secundário: chegada forte."),
        b ("Module com diminuto: transição elegante e imprevisível."),
        aud ({ "C4", "E4", "G4", "D4", "F#4", "A4", "C5", "G4" },
             "De Do maior para Sol maior por acorde pivô: a passagem quase não se percebe."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é modular sem preparação, o que faz a música soar cortada. Outro erro é confundir campos relativos com homônimos, o que leva a escolher os acordes errados para a ponte."),
        b ("Modular sem um acorde de preparação."),
        b ("Confundir relativo (mesmas notas) com homônimo (mesma tônica)."),
        b ("Usar o dominante errado: o V7 é sempre da nova tônica."),
        c (
            "Se a modulação soar abrupta, provavelmente faltou um acorde pivô ou um dominante preparatorio."),

        h ("Aplicando na prática"),
        p (
            "Escolha uma música do seu repertório e identifique os momentos de modulação. Analise qual recurso o compositor usou: pivô, dominante secundário ou diminuto. Depois, experimente trocar o recurso e ouça como a passagem muda. Esse exercício de análise é o que constrói a intuição harmônica."),
        b ("Identifique as modulações de uma música que você toca."),
        b ("Descubra qual recurso foi usado em cada uma."),
        b ("Experimente trocar o recurso e comparar."),
        aud ({ "C4", "E4", "G4", "B4", "D5", "G4", "B4", "D5" },
             "Uma progressão que passa por um pivô e chega na nova tônica."),

        h ("Modulação por empréstimo modal"),
        p (
            "Além do pivô, do dominante secundário e do diminuto, existe a modulação por empréstimo modal. Nela, o compositor pega um acorde emprestado de outro modo da mesma tônica — por exemplo, um acorde do campo menor usado dentro do campo maior. O efeito é uma mudança de cor sem mudança de centro, e é um recurso muito usado na música popular e na MPB."),
        b ("Empréstimo modal: acorde de outro modo sobre a mesma tônica."),
        b ("Muda a cor sem mudar o centro tonal."),
        b ("Muito usado na MPB e na música popular."),

        h ("Relacionando os campos com o círculo das quintas"),
        p (
            "O círculo das quintas é o mapa que organiza todas essas relações. Duas tonalidades vizinhas no círculo compartilham seis notas; quanto mais distantes, menos notas em comum. As modulações suaves seguem o círculo por passos pequenos; as modulações surpreendentes saltam. Entender o círculo é entender por que certas passagens soam naturais e outras, dramáticas."),
        b ("Vizinhos no círculo compartilham quase todas as notas."),
        b ("Passos pequenos no círculo dão modulações suaves."),
        b ("Saltos no círculo dão modulações surpreendentes."),
        img ("m9_relacoes_campos", "O círculo das quintas organiza as relações entre os campos harmônicos."),
        aud ({ "C4", "E4", "G4", "B4", "D5", "F#5", "C5" },
             "Do maior e Sol maior: campos vizinhos, passagem suave."),

        h ("Campos distantes e o cromatismo"),
        p (
            "Nem toda modulação é suave. Quando os campos são distantes no círculo das quintas, a passagem precisa de preparação. O cromatismo é o recurso mais direto: o compositor sobe ou desce de semitom em semitom até chegar à nova tonalidade. O ouvido aceita a mudança porque cada passo é pequeno, mesmo que o destino seja longe. É assim que se modula entre campos que quase não compartilham notas."),
        b ("Campos distantes exigem preparação."),
        b ("O cromatismo conduz de semitom em semitom."),
        b ("Cada passo pequeno torna a chegada natural."),

        h ("Aplicando as relações na análise"),
        p (
            "Analisar as relações entre campos é o que permite entender uma música por dentro. Ao identificar como o compositor passou de uma tonalidade para outra, o aluno aprende a reusar o mesmo recurso nas suas próprias composições. A análise transforma a harmonia de uma lista de acordes numa narrativa, com idas e vindas que o ouvido acompanha."),
        b ("Analise como cada música modula."),
        b ("Reuse os recursos que você identificou."),
        b ("A análise transforma acordes em narrativa."),
        aud ({ "C4", "E4", "G4", "D4", "F#4", "A4", "C5", "G4", "B4", "D5" },
             "Uma modulação com dominante secundário: a chegada à nova tonalidade é forte."),

        h ("O acorde pivô na prática"),
        p (
            "Encontrar o acorde pivô é o primeiro passo de qualquer modulação consciente. Para achar o pivô entre dois campos, liste os acordes de cada um e veja quais se repetem. Esses são os candidatos. Tocar um deles antes de chegar à nova tônica prepara o ouvido, e a mudança acontece sem sobressalto. É um exercício simples que desenvolve muito a percepção harmônica."),
        b ("Liste os acordes dos dois campos e ache os comuns."),
        b ("Toque o pivô antes de chegar à nova tônica."),
        b ("O pivô prepara o ouvido para a mudança."),

        h ("Relações entre os modos e os campos"),
        p (
            "Cada modo de uma escala gera um campo próprio, com os seus acordes e a sua cor. Os modos de Dó maior, por exemplo, dão sete campos diferentes, cada um com um centro tonal distinto. Entender que os modos são faces da mesma escala ajuda a perceber por que duas músicas podem usar as mesmas notas e soar completamente diferentes. O que muda é a nota que se trata como repouso."),
        b ("Cada modo gera um campo com a sua cor."),
        b ("Os modos são faces da mesma escala."),
        b ("O que muda é a nota tratada como repouso."),

        h ("Aplicando as relações na prática"),
        p (
            "Na prática, as relações entre campos aparecem em quase toda música que modula. Ao estudar uma peça, procure o momento em que a tonalidade muda e identifique o recurso usado. Com o tempo, você reconhecerá os padrões de modulação de ouvido, e a análise deixará de ser um exercício teórico para se tornar uma escuta ativa. Esse é o objetivo final do estudo da harmonia."),
        b ("Procure o momento da modulação em cada música."),
        b ("Identifique o recurso usado na passagem."),
        b ("A análise vira escuta ativa com a prática."),

        h ("Resumo do tópico"),
        b ("Campos vizinhos compartilham seis das sete notas."),
        b ("O acorde pivô pertence aos dois campos e prepara a passagem."),
        b ("O dominante secundário é o V7 da nova tônica."),
        b ("O diminuto liga campos distantes de forma elegante."),
        b ("Relativos compartilham notas; homônimos, a tônica."),
        c (
            "Nos exercícios, module entre campos e toque os acordes pivô. O app reconhece as notas e confere as progressões."),
    };
}

} // namespace cursomusica::content
