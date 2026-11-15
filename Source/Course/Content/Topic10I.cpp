#include "Course/Content/Topics.h"

// Topic 10I — Ferramentas de reharmonização (Módulo 10, Etapa 10).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 10). Catálogo das ferramentas
// concretas para trocar a harmonia de uma música.
namespace cursomusica::content
{

std::vector<ContentItem> topic10I()
{
    return {

        p (
            "Depois de entender o que é reharmonizar e como dar direção à harmonia, falta o essencial: as ferramentas. Reharmonizar não é um dom misterioso — é um conjunto pequeno de recursos concretos que você aplica de forma consciente. Este tópico reúne essas ferramentas num catálogo: substituição de trítono, dominantes secundários, empréstimo modal, relativos e paralelos, acordes de passagem, inversões e a reharmonização melódica. Com esse conjunto, você cobre a quase totalidade das reharmonizações que vai encontrar e criar."),
        p (
            "Pense neste tópico como uma caixa de ferramentas. Cada ferramenta tem um nome, um efeito e um momento de usar. O objetivo não é decorar a lista, mas saber pegar a ferramenta certa quando a música pede: quando você quer um baixo cromático, pega a substituição de trítono; quando quer preparar um acorde, pega o dominante secundário; quando quer escurecer a tônica, pega o empréstimo modal. É essa escolha consciente que transforma teoria em música."),
        c (
            "Ideia central: reharmonizar é escolher, entre ferramentas conhecidas, a que dá à frase a cor e a direção que você quer — sempre respeitando a melodia."),

        h ("O catálogo das ferramentas"),
        p (
            "As ferramentas de reharmonização se organizam em famílias. Umas trocam um acorde por outro equivalente (substituição); outras acrescentam acordes (dominantes secundários, acordes de passagem); outras mudam a cor sem mudar a função (empréstimo modal, relativo); e outras reconstroem a harmonia a partir da melodia (verticalização). Conhecer as famílias ajuda a escolher: se você quer mudar a cor, use o empréstimo; se quer mais movimento, use acordes de passagem."),
        tbl ({ "Ferramenta", "O que faz", "Exemplo" }, {
            { "Substituição de trítono", "troca o V pelo dominante a um trítono", "Db7 no lugar de G7" },
            { "Dominante secundário", "cria o V de qualquer acorde", "A7 antes de Dm7" },
            { "Empréstimo modal", "pega acorde do menor paralelo", "Cm7 no campo de Dó" },
            { "Relativo / paralelo", "troca por acorde da mesma família", "Am7 por C7M" },
            { "Acorde de passagem", "preenche o salto com movimento", "Bm7b5 entre C e Dm" },
            { "Inversão", "muda a nota do baixo", "C/E no lugar de C" },
            { "Reharmonização melódica", "constrói o acorde a partir da nota", "verticalização" },
        }),
        img ("m10_ferramentas", "O catálogo das ferramentas de reharmonização: cada uma com seu efeito e seu exemplo."),

        h ("Ferramenta 1 — Substituição de trítono"),
        p (
            "O dominante a um trítono de distância do V tem o mesmo trítono interno, então pode substituí-lo. G7 (Sol, Si, Ré, Fá) e Db7 (Ré bemol, Fá, Lá bemol, Si bemol) compartilham o trítono Si–Fá, que é o que pede resolução para o Dó. Substituir G7 por Db7 mantém a resolução e cria um baixo que desce de cromatismo (Ré bemol para Dó). É a ferramenta mais usada do jazz, e uma das mais elegantes."),
        b ("G7 e Db7 têm o mesmo trítono (Si–Fá)."),
        b ("O baixo desce de semitom (Db → C): som cromático e moderno."),
        b ("Funciona em qualquer ii–V–I: troque o V pelo seu subV."),
        aud ({ "G3", "B3", "D4", "F4", "C#4", "F4", "G#4", "B4", "C4", "E4", "G4", "B4" },
             "G7 e Db7 chegando ao mesmo C7M: ouça o baixo cromático do subV."),

        h ("Ferramenta 2 — Dominantes secundários"),
        p (
            "Um dominante secundário é o V de qualquer acorde do campo. Se você tem Dm7, pode prepará-lo com um A7 (o V de Ré). Se tem Am7, pode prepará-lo com um E7. Os dominantes secundários criam movimento antes de cada acorde e são o recurso mais comum para 'colorir' uma progressão. Eles podem aparecer antes de qualquer acorde, desde que resolvam nele. É uma ferramenta simples e muito eficaz."),
        b ("O V de qualquer acorde prepara esse acorde."),
        b ("A7 prepara Dm7; E7 prepara Am7; D7 prepara G7."),
        b ("Use dominantes secundários para criar movimento antes de cada acorde."),
        aud ({ "A3", "C#4", "E4", "G4", "D4", "F4", "A4", "C5" },
             "A7 (V do ii) preparando Dm7: ouça o movimento antes do acorde."),

        h ("Ferramenta 3 — Empréstimo modal"),
        p (
            "O empréstimo modal pega acordes do campo menor paralelo e os usa no campo maior. Em Dó maior, você pode emprestar Fm7 (o iv do menor), Ab7M (o VI), Bb7 (o VII) e Cm7 (o i). Esses acordes escurecem a harmonia sem mudar a tonalidade — a música continua em Dó, mas com uma cor emprestada do Dó menor. É a ferramenta favorita de quem quer um som mais dramático ou mais melancólico sem modular."),
        b ("Empreste o iv, o VI, o VII ou o i do menor paralelo."),
        b ("A tonalidade não muda; só a cor."),
        b ("Use quando quiser escurecer a harmonia sem modular."),
        aud ({ "F3", "G#3", "C4", "D#4" }, "Fm7 emprestado do menor paralelo: a cor escurece dentro de Dó maior."),

        h ("Ferramenta 4 — Relativo, paralelo e inversões"),
        p (
            "Trocar um acorde pelo seu relativo ou paralelo é uma reharmonização suave, porque a família de notas é parecida. C7M e Am7 (relativo) compartilham três notas; C7M e Cm7 (paralelo) compartilham o baixo e mudam a terça. Já as inversões não trocam o acorde, mas mudam a nota do baixo — e isso muda a condução das vozes e a sensação da harmonia. São ferramentas discretas, mas muito úteis para dar fluidez."),
        tbl ({ "Original", "Troca", "Relação" }, {
            { "C7M", "Am7", "relativo menor (3 notas em comum)" },
            { "C7M", "Em7", "relativo (iii)" },
            { "C7M", "Cm7", "paralelo menor (muda a terça)" },
            { "C", "C/E", "inversão (baixo na terça)" },
            { "C", "C/G", "inversão (baixo na quinta)" },
        }),
        b ("Relativo: mesma família de notas, função parecida."),
        b ("Paralelo: muda a terça (maior ↔ menor), mantém o baixo."),
        b ("Inversão: muda a nota do baixo e a condução das vozes."),
        aud ({ "C4", "E4", "G4", "B4", "A3", "C4", "E4", "G4" },
             "C7M e Am7 (relativo): ouça como a troca é suave."),

        h ("Ferramenta 5 — Acordes de passagem e aproximações"),
        p (
            "Acordes de passagem preenchem o espaço entre dois acordes, criando movimento onde havia um salto. Onde havia C7M → Dm7, você pode inserir um Bm7b5 (movimento por graus) ou um Ab7 (dominante de aproximação). As aproximações também podem ser cromáticas: um acorde meio tom abaixo do alvo cria uma chegada suave. São ferramentas para dar densidade à harmonia sem mudar a estrutura."),
        b ("Acorde de passagem: preenche o salto entre dois acordes."),
        b ("Aproximação cromática: acorde meio tom abaixo do alvo."),
        b ("Use quando quiser mais movimento sem mudar a estrutura."),
        aud ({ "C4", "E4", "G4", "B4", "B3", "D4", "F4", "A4", "D4", "F4", "A4", "C5" },
             "C7M → Bm7b5 → Dm7: o acorde de passagem cria movimento por graus."),

        h ("Ferramenta 6 — Reharmonização melódica (verticalização)"),
        p (
            "A ferramenta mais ligada à melodia é a verticalização: você constrói o acorde a partir da nota que a melodia está tocando. É a ferramenta que garante que a reharmonização nunca brigue com a melodia, porque o acorde é feito dela. Quando as outras ferramentas não funcionam — porque a melodia insiste numa nota difícil —, a verticalização resolve: escolha um acorde que contenha aquela nota e pronto."),
        b ("Construa o acorde a partir da nota da melodia."),
        b ("Garante que a melodia sempre caiba na nova harmonia."),
        b ("É a ferramenta de último recurso quando a melodia é exigente."),
        part ("m10_partitura_verticalizacao", { "A4", "G4", "F4", "E4" },
              "Partitura da verticalização: a ferramenta que constrói a harmonia a partir da melodia."),

        h ("Combinando ferramentas"),
        p (
            "Na prática, você combina ferramentas. Reharmonizar um ii–V–I inteiro pode envolver: um dominante secundário antes do ii, uma substituição de trítono no V, um empréstimo modal no I. Cada ferramenta faz uma pequena mudança, e a soma delas é uma reharmonização rica. O segredo é não usar todas ao mesmo tempo: escolha duas ou três, para que a música continue reconhecível. A reharmonização é um acúmulo de pequenas decisões, não um único golpe."),
        b ("Combine poucas ferramentas por vez."),
        b ("Cada ferramenta faz uma mudança pequena e controlada."),
        b ("Mantenha a música reconhecível: não use tudo ao mesmo tempo."),
        aud ({ "D4", "F4", "A4", "C5", "A3", "C#4", "E4", "G4", "C#4", "F4", "G#4", "B4", "C4", "E4", "G4", "B4" },
             "Um ii–V–I com dominante secundário e subV combinados: ouça a soma das ferramentas."),

        h ("Como escolher a ferramenta certa"),
        p (
            "A escolha da ferramenta vem do efeito que você quer. Quer um baixo cromático? Substituição de trítono. Quer mais movimento? Acordes de passagem e dominantes secundários. Quer escurecer? Empréstimo modal. Quer suavizar? Relativo e inversões. Quer garantir a melodia? Verticalização. Definir o efeito antes de escolher a ferramenta é o que torna a reharmonização intencional em vez de aleatória."),
        tbl ({ "Efeito desejado", "Ferramenta" }, {
            { "baixo cromático, som moderno", "substituição de trítono" },
            { "mais movimento", "dominantes secundários, acordes de passagem" },
            { "cor mais escura", "empréstimo modal" },
            { "suavidade, fluidez", "relativos, inversões, condução de vozes" },
            { "respeitar a melodia", "verticalização" },
        }),
        c (
            "Nos exercícios, o app reconhece os acordes que você toca e confere a progressão reharmonizada. Escolha a ferramenta, toque, escute e verifique: é assim que o catálogo vira vocabulário."),

        h ("Erros comuns no uso das ferramentas"),
        p (
            "O erro mais comum é usar ferramentas demais, criando uma harmonia nervosa que perde a identidade. O segundo é escolher a ferramenta errada para o efeito desejado: usar empréstimo modal quando se queria movimento. O terceiro é esquecer a melodia — nenhuma ferramenta vale se ela entra em choque com as notas fortes. Reharmonizar bem é usar poucas ferramentas, escolhidas com critério, sempre em função da melodia e do efeito."),
        b ("Não use todas as ferramentas de uma vez."),
        b ("Escolha a ferramenta pelo efeito que você quer."),
        b ("Confira a melodia antes de fechar a reharmonização."),
        img ("m10_ferramentas", "A caixa de ferramentas: cada recurso tem um efeito. Escolher o certo é o que faz a reharmonização funcionar."),

        h ("Reharmonização com pedais e baixos"),
        p (
            "Uma ferramenta que merece destaque é o baixo pedalizado: manter a mesma nota no baixo enquanto os acordes mudam por cima. Isso cria uma sensação de suspensão e é muito usado na MPB e no samba — Incompatibilidade de Gênios faz isso em vários trechos, com o Lá no baixo sob acordes diferentes. A ferramenta oposta é o baixo que caminha: em vez de manter a fundamental, você faz o baixo andar por graus, criando movimento. Escolher entre baixo pedal e baixo caminhante muda a sensação da harmonia sem trocar os acordes."),
        tbl ({ "Recurso de baixo", "Como funciona", "Efeito" }, {
            { "baixo pedal", "mesma nota sob acordes diferentes", "suspensão, tensão" },
            { "baixo caminhante", "graus conjuntos ou cromáticos", "movimento, fluidez" },
            { "baixo em oitavas", "alternar a fundamental em oitavas", "estabilidade" },
            { "baixo invertido", "terça ou quinta no baixo", "suavidade, condução" },
        }),
        b ("Baixo pedal: suspende a harmonia e cria tensão."),
        b ("Baixo caminhante: move a harmonia por graus."),
        b ("Inversões: mudam a nota do baixo para suavizar."),
        aud ({ "A2", "C4", "E4", "G4", "A2", "D4", "F4", "A4" },
             "Baixo pedal em Lá sob dois acordes: ouça a suspensão que ele cria."),

        h ("Ferramentas de reharmonização no repertório"),
        p (
            "Vamos ver as ferramentas aplicadas no repertório curado. Em Só Danço Samba, o D7 no lugar do Dm7 é um dominante secundário que o compositor usou. Em Incompatibilidade de Gênios, os acordes de passagem com baixo pedalizado são acordes de passagem e baixo pedal combinados. Em Equinox, o Ab9 é um substituto do IV. Em Spain e 500 Miles High, a reharmonização aparece como modulação e reescalonamento. Estudar essas músicas é ver o catálogo de ferramentas em ação — e é a melhor forma de aprender a usá-las com bom gosto."),
        b ("Só Danço Samba: dominante secundário (D7)."),
        b ("Incompatibilidade de Gênios: passagem + baixo pedal."),
        b ("Equinox: substituto do IV (Ab9)."),
        b ("Spain / 500 Miles High: modulação e reescala."),
        aud ({ "C4", "D#4", "G4", "A#4", "F3", "A3", "C4", "D#4" },
             "Empréstimo modal em sequência: ouça a cor escura que as ferramentas trazem."),

        h ("Erros comuns ao combinar ferramentas"),
        p (
            "Combinar ferramentas exige cuidado. O erro mais comum é sobrecarregar: usar substituição de trítono, dominante secundário e empréstimo modal no mesmo compasso, criando uma harmonia ilegível. O segundo é usar ferramentas que se anulam: um subV seguido de um V logo depois confunde o ouvido. O terceiro é esquecer a melodia. Combinar ferramentas é como temperar comida: pouco de cada, na hora certa, e sempre provando. A reharmonização bem-feita é invisível — o ouvinte sente a música nova, mas não percebe a mecânica."),
        b ("Não sobrecarregue: poucas ferramentas por vez."),
        b ("Evite ferramentas que se anulam (subV + V no mesmo trecho)."),
        b ("Sempre confira a melodia antes de fechar."),
        img ("m10_ferramentas", "Combinar ferramentas é como temperar: pouco de cada, na hora certa, sempre provando com o ouvido."),

        h ("Resumo do tópico"),
        b ("Reharmonizar é aplicar um conjunto pequeno de ferramentas conhecidas."),
        b ("As principais são: substituição de trítono, dominante secundário, empréstimo modal, relativo/paralelo, passagem, inversão e verticalização."),
        b ("Cada ferramenta tem um efeito; escolha pelo efeito que você quer."),
        b ("Combine poucas ferramentas por vez para manter a música reconhecível."),
        b ("A melodia é sempre a restrição final."),
        c (
            "Objetivo do tópico: transformar a reharmonização em escolha consciente. Com o catálogo na mão, você reharmoniza com propósito — e cada troca tem uma razão de ser."),
    };
}

} // namespace cursomusica::content
