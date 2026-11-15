#include "Course/Content/Topics.h"

// Topic 10H — Harmonia-alvo (Módulo 10, Etapa 10).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 10). Harmonia-alvo = definir
// onde a frase quer chegar e construir a harmonia de trás para frente.
namespace cursomusica::content
{

std::vector<ContentItem> topic10H()
{
    return {

        p (
            "Harmonia-alvo é a ideia de que toda frase musical quer chegar a algum lugar, e que a harmonia deve ser construída em direção a essa chegada. Em vez de encadear acordes um atrás do outro e ver onde a música para, você decide primeiro qual é o acorde de chegada — o alvo — e depois constrói os acordes anteriores para preparar essa chegada. É trabalhar de trás para frente, do destino para o caminho."),
        p (
            "Esse é o princípio que organiza toda a reharmonização. Quando você reharmoniza sem alvo, o resultado é uma sequência de acordes bonitos que não leva a lugar nenhum. Quando você define o alvo, cada acorde tem um propósito: aproximar a música da chegada. Harmonia-alvo é o que transforma uma troca de acordes em uma frase com direção — e é o que dá sentido à análise, à verticalização e à reharmonização que você aprendeu nos tópicos anteriores."),
        c (
            "Ideia central: primeiro o destino, depois o caminho. Defina o acorde de chegada (o alvo) e construa a harmonia de trás para frente, para que cada acorde prepare a chegada."),

        h ("O que é o alvo"),
        p (
            "O alvo é o acorde onde a frase repousa — a chegada. Em geral é a tônica (o I), mas pode ser qualquer acorde de repouso: o vi, o iii, ou mesmo um acorde de uma nova tonalidade quando a frase modula. Identificar o alvo é identificar onde a melodia respira e onde o ouvinte sente que a frase 'fechou'. Sem esse ponto de repouso, a música soa como uma frase sem ponto final."),
        b ("O alvo é o acorde de chegada: onde a frase repousa."),
        b ("Quase sempre é a tônica, mas pode ser o vi, o iii ou o acorde de uma nova tonalidade."),
        b ("O alvo é o ponto que o ouvinte espera; a harmonia existe para prepará-lo."),
        aud ({ "G3", "B3", "D4", "F4", "C4", "E4", "G4", "B4" },
             "Um V que chega ao I: a tensão prepara o repouso. Ouça o alvo se concretizar."),

        h ("Construindo de trás para frente"),
        p (
            "A técnica da harmonia-alvo é construir a progressão de trás para frente. Comece pelo alvo (digamos, C7M) e pergunte: o que pode vir imediatamente antes dele? Um dominante (G7), um subV (Db7), um ii–V (Dm7–G7). Depois pergunte o que pode vir antes disso, e assim por diante, afastando-se do alvo. Cada passo para trás é uma escolha, e a soma das escolhas é a sua progressão reharmonizada — uma progressão que existe para chegar ao alvo."),
        b ("Passo 1: defina o alvo (ex.: C7M)."),
        b ("Passo 2: escolha o acorde imediatamente anterior (G7, Db7, Dm7–G7)."),
        b ("Passo 3: continue para trás, afastando-se do alvo."),
        b ("Passo 4: toque a melodia sobre o resultado e ajuste o que soar mal."),
        img ("m10_harmonia_alvo", "A harmonia-alvo: definir a chegada e construir a aproximação de trás para frente."),

        h ("As aproximações do alvo"),
        p (
            "Existem várias maneiras de preparar um alvo, e cada uma dá uma cor diferente à chegada. O ii–V é a mais comum e a mais forte. O subV (substituição de trítono) desce o baixo cromaticamente e soa mais moderno. O dominante secundário prepara o alvo a partir de uma nota vizinha. E o movimento cromático aproxima o alvo por semitom, criando uma chegada suave. Escolher a aproximação é escolher o 'tempero' da chegada."),
        tbl ({ "Aproximação", "Exemplo (alvo C7M)", "Efeito" }, {
            { "ii–V", "Dm7–G7–C7M", "cadência clássica, forte" },
            { "subV", "Dm7–Db7–C7M", "baixo cromático, moderno" },
            { "dominante secundário", "A7–Dm7–G7–C7M", "prepara o ii antes do V" },
            { "cromática", "B7–C7M", "chegada por semitom, suave" },
            { "emprestado", "Fm7–C7M", "chegada escura (iv–i)" },
        }),
        c (
            "Cada aproximação é um caminho até o alvo. O ii–V chega com força; o subV chega com elegância; a cromática chega de mansinho. Você escolhe a aproximação conforme a emoção que quer na chegada."),
        aud ({ "D4", "F4", "A4", "C5", "G3", "B3", "D4", "F4", "C4", "E4", "G4", "B4" },
             "Um ii–V–I chegando ao alvo: ouça a força da cadência clássica."),
        aud ({ "D4", "F4", "A4", "C5", "C#4", "F4", "G#4", "B4", "C4", "E4", "G4", "B4" },
             "Um subV chegando ao mesmo alvo: o baixo desce de cromatismo. Ouça a diferença de cor."),

        h ("O alvo e a melodia"),
        p (
            "A harmonia-alvo está intimamente ligada à melodia. O alvo não é só um acorde: é o ponto onde a melodia repousa, onde a frase respira. Então o alvo é, muitas vezes, revelado pela própria melodia. Se a melodia termina numa nota C e repousa, o alvo provavelmente é um acorde que contém C (C7M, Am7, F7M). Ouvir onde a melodia 'pousa' é o caminho mais seguro para encontrar o alvo — e, uma vez encontrado o alvo, a reharmonização se organiza em torno dele."),
        b ("O alvo é o ponto onde a melodia repousa."),
        b ("Encontre o alvo ouvindo onde a frase respira."),
        b ("O alvo é um acorde que contém a nota de repouso da melodia."),
        aud ({ "E4", "D4", "C4", "A3", "F4", "E4", "C4" },
             "Uma frase que repousa em C: o alvo é revelado pela própria melodia."),

        h ("Harmonia-alvo e reharmonização"),
        p (
            "A harmonia-alvo é o método que torna a reharmonização coerente. Em vez de trocar acordes aleatoriamente, você mantém o alvo e reconstrói o caminho até ele. Isso permite reharmonizar radicalmente uma música — mudando quase todos os acordes — sem que ela perca a direção, porque a chegada continua a mesma. É assim que os arranjadores reinventam standards: mantêm o ponto de repouso e reescrevem tudo o que vem antes. O alvo é a âncora da reharmonização."),
        b ("Mantenha o alvo e reescreva o caminho até ele."),
        b ("Reharmonizações radicais funcionam porque a chegada não muda."),
        b ("O alvo é a âncora que mantém a música reconhecível."),
        part ("m10_partitura_reharmonizado", { "C4", "E4", "G4", "A4", "D5", "F5", "G5", "C5" },
              "Partitura de uma melodia reharmonizada que chega ao alvo: a chegada organiza todo o caminho."),

        h ("Aplicando ao repertório curado"),
        p (
            "No repertório do curso, a harmonia-alvo aparece na forma de cada música. Uma música AABA tem um alvo no fim de cada seção A e outro no fim da seção B. Os turnarounds existem para levar a música de volta ao alvo do início. Em Equinox e Só Danço Samba, os ii–V no fim da forma são alvos que preparam a volta ao topo. Ouvir onde cada seção 'fecha' é ouvir os alvos da música — e é o que permite navegar a forma inteira sem se perder."),
        b ("Formas AABA têm alvos no fim de cada seção."),
        b ("O turnaround leva a música de volta ao alvo do início."),
        b ("Ouvir os alvos é o que permite navegar a forma."),
        aud ({ "D4", "F4", "A4", "C5", "G3", "B3", "D4", "F4", "C4", "E4", "G4", "B4" },
             "Um turnaround que volta ao alvo do início: ouça a música fechar o ciclo."),

        h ("Como praticar a harmonia-alvo"),
        p (
            "Pratique definir alvos e construir aproximações. Pegue uma melodia simples, defina o alvo (o acorde de chegada) e construa três aproximações diferentes: um ii–V, um subV e uma cromática. Toque a melodia sobre cada versão e escolha a que soa melhor. Depois faça o mesmo com uma música do repertório: escolha um trecho, defina o alvo e reharmonize o caminho. O app ajuda: ele reconhece os acordes que você toca e confere a progressão, então você pode testar suas aproximações com verificação."),
        b ("Defina o alvo de uma frase curta."),
        b ("Construa três aproximações diferentes do mesmo alvo."),
        b ("Toque a melodia sobre cada uma e confira com o app."),
        c (
            "Erro comum: reharmonizar sem alvo definido. A música fica bonita por alguns compassos e depois se perde. O alvo é o que dá direção — sem ele, não há frase."),

        h ("Erros comuns na harmonia-alvo"),
        p (
            "O erro mais comum é começar pelo primeiro acorde em vez de começar pelo alvo. Quando você constrói do início para o fim, a música pode não chegar a lugar nenhum. O segundo erro é definir um alvo que a melodia não pede: se a melodia repousa numa nota que o alvo não contém, a chegada soa falsa. O terceiro é preparar o alvo com acordes que não resolvem nele, criando uma chegada frustrada. A harmonia-alvo é um exercício de foco: tudo aponta para a chegada."),
        b ("Comece sempre pelo alvo, não pelo primeiro acorde."),
        b ("Escolha um alvo que contenha a nota de repouso da melodia."),
        b ("Garanta que a aproximação resolva de fato no alvo."),
        img ("m10_harmonia_alvo", "Tudo na frase aponta para o alvo. Uma chegada bem preparada faz a harmonia inteira soar com propósito."),

        h ("Harmonia-alvo em várias escalas"),
        p (
            "A harmonia-alvo funciona em qualquer estilo e em qualquer escala. Numa música modal, o alvo é o acorde do vamp para o qual a música volta. Numa música modulante, há um alvo em cada centro. Numa música de blues, o alvo é a volta ao I no fim da forma. Identificar os alvos de uma música é identificar a sua forma — e é o que permite navegá-la. Sem alvos, uma música longa é um labirinto; com alvos, é uma série de frases que chegam a lugares conhecidos."),
        b ("Música modal: o alvo é o vamp de retorno."),
        b ("Música modulante: um alvo em cada centro."),
        b ("Blues: o alvo é a volta ao I no fim da forma."),
        aud ({ "C4", "E4", "G4", "A4", "D4", "F4", "A4", "C5", "G3", "B3", "D4", "F4", "C4", "E4", "G4", "B4" },
             "Um turnaround que leva de volta ao alvo do início: ouça a música fechar o ciclo."),

        h ("Alvo e forma musical"),
        p (
            "Toda forma musical é um mapa de alvos. Uma forma AABA tem alvos no fim de cada seção: o fim da primeira A pode ser aberto (uma meia-cadência), o fim da segunda A fecha, o fim da B leva de volta. Reconhecer esses alvos é o que permite improvisar sobre a forma sem se perder. Músicos experientes não pensam em 'acorde por acorde': pensam em alvos e em como chegar até eles. É essa visão de conjunto que a harmonia-alvo desenvolve."),
        tbl ({ "Seção", "Alvo", "Tipo de chegada" }, {
            { "A (primeira)", "acorde de repouso ou meia-cadência", "aberta ou fechada" },
            { "A (segunda)", "tônica", "fechada" },
            { "B (bridge)", "tônica do retorno", "aberta, prepara a volta" },
            { "A final", "tônica", "fechada, conclusão" },
        }),
        b ("Cada seção de uma forma tem um alvo."),
        b ("Pense em alvos, não em acordes soltos."),
        b ("A forma musical é um mapa de chegadas."),

        h ("Construindo a aproximação passo a passo"),
        p (
            "Vamos construir uma aproximação do alvo C7M, de trás para frente. O alvo é C7M. Imediatamente antes, um dominante: G7. Antes do G7, o seu ii: Dm7. Antes do Dm7, um dominante secundário: A7. Antes do A7, o seu ii: Em7b5. A progressão resultante é Em7b5 – A7 – Dm7 – G7 – C7M: uma cadência longa que caminha por dois ii–V até o alvo. Cada passo foi escolhido por trabalhar de trás para frente, e o resultado é uma progressão que tem direção clara. É assim que se reharmoniza com alvo."),
        b ("Comece pelo alvo (C7M)."),
        b ("Coloque um dominante antes (G7)."),
        b ("Coloque o ii do dominante antes (Dm7)."),
        b ("Continue para trás (A7, Em7b5) até onde quiser começar."),
        aud ({ "E3", "G3", "A#3", "D4", "A3", "C#4", "E4", "G4", "D4", "F4", "A4", "C5", "G3", "B3", "D4", "F4", "C4", "E4", "G4", "B4" },
             "Uma cadência longa construída de trás para frente: Em7b5 – A7 – Dm7 – G7 – C7M. Ouça a direção."),
        part ("m10_partitura_turnaround", { "C4", "E4", "G4", "A4", "D5", "F5", "G5", "B4" },
              "Partitura de uma progressão construída em direção ao alvo. Ouça a chegada."),

        h ("Alvo e improvisação"),
        p (
            "A harmonia-alvo também guia a improvisação. Quando você improvisa pensando no alvo, a sua frase tem direção: você sabe para onde está indo e constrói a linha para chegar lá. Improvisar sem alvo é tocar notas; improvisar com alvo é contar uma história. Os grandes improvisadores pensam em alvos o tempo todo: eles constroem a frase para chegar a uma nota ou a um acorde específico no momento certo. A harmonia-alvo é, no fundo, a organização da improvisação em torno de chegadas."),
        b ("Improvise pensando no alvo: para onde a frase vai?"),
        b ("Construa a linha para chegar ao alvo no tempo certo."),
        b ("Uma frase com alvo conta uma história."),
        aud ({ "D4", "E4", "F4", "G4", "A4", "B4", "C5" },
             "Uma frase que caminha até o alvo (C): ouça a direção e a chegada."),

        h ("Resumo do tópico"),
        b ("Harmonia-alvo é definir a chegada da frase e construir a harmonia até ela."),
        b ("O alvo é o acorde de repouso, revelado muitas vezes pela melodia."),
        b ("Constrói-se de trás para frente: do alvo para as aproximações."),
        b ("As aproximações (ii–V, subV, cromática) dão cores diferentes à chegada."),
        b ("O alvo é a âncora que torna a reharmonização coerente e reconhecível."),
        c (
            "Objetivo do tópico: aprender a dar direção à harmonia. Antes de trocar acordes, defina o alvo; depois, construa o caminho de trás para frente, para que cada acorde prepare a chegada."),
    };
}

} // namespace cursomusica::content
