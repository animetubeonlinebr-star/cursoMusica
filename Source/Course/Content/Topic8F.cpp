#include "Course/Content/Topics.h"

// Topic 8F — Empréstimos modais (Módulo 8, Etapa 8).
// Fonte de verdade do texto: docs/MUSIC.md §8 (bloco F).
namespace cursomusica::content
{

std::vector<ContentItem> topic8F()
{
    return {

        p (
            "Empréstimo modal é pegar um acorde de um modo paralelo e usá-lo dentro do modo principal. Modos paralelos compartilham a mesma tônica, mas têm qualidades diferentes: Dó maior e Dó menor são paralelos. Assim, os acordes do campo de Dó menor podem ser emprestados para o campo de Dó maior, criando cores que o campo maior não possui."),
        p (
            "Essa é uma das técnicas mais antigas e mais usadas da música. Aparece em Bach, no rock, na bossa nova e na MPB. O empréstimo modal não muda o tom: a música continua em Dó maior, mas momentaneamente usa um acorde que só existiria em Dó menor. O efeito é de cor, de surpresa controlada, de drama."),
        c (
            "Objetivo do tópico: entender o que é empréstimo modal, quais acordes podem ser emprestados e como reconhecê-los pela presença de notas bemóis."),

        h ("Modos paralelos"),
        p (
            "Dois modos são paralelos quando compartilham a mesma tônica. Dó maior (jônio) e Dó menor (eólio) são paralelos. Dó dórico, Dó frígio, Dó lídio, Dó mixolídio e Dó lócrio também são paralelos a Dó maior, porque todos começam em Dó. Cada modo tem um conjunto próprio de acordes, e o empréstimo modal consiste em misturar esses conjuntos."),
        b ("Paralelos: mesma tônica, qualidades diferentes."),
        b ("Dó maior e Dó menor são os paralelos mais usados."),
        b ("O empréstimo não muda o tom: só acrescenta cor."),
        img ("m8_emprestimos_modais", "Acordes emprestados do Dó menor dentro do Dó maior: cada um traz uma cor nova."),

        h ("Os acordes emprestados do menor paralelo"),
        p (
            "O campo harmônico de Dó menor fornece vários acordes úteis para o Dó maior. O i menor (Cm) traz a tônica menor; o iv menor (Fm7) traz a subdominante menor; o bVI (Ab7M) traz uma cor dramática; o bVII (Bb7) traz a cadência mixolídia; o bIII (Eb7M) traz um brilho modal. Cada um desses acordes introduz notas bemóis que não pertencem ao Dó maior."),
        b ("Cm (i menor): tônica menor."),
        b ("Fm7 (iv menor): subdominante menor."),
        b ("Ab7M (bVI): cor dramática."),
        b ("Bb7 (bVII): cadência mixolídia."),
        b ("Eb7M (bIII): brilho modal."),
        tbl ({ "Acorde emprestado", "Grau", "Notas", "Nota estranha" }, {
            { "Cm", "i", "C, Eb, G", "Eb (b3)" },
            { "Fm7", "iv", "F, Ab, C, Eb", "Ab, Eb" },
            { "Gm7", "v", "G, Bb, D, F", "Bb" },
            { "Ab7M", "bVI", "Ab, C, Eb, G", "Ab, Eb" },
            { "Bb7", "bVII", "Bb, D, F, Ab", "Bb, Ab" },
            { "Eb7M", "bIII", "Eb, G, Bb, D", "Eb, Bb" },
        }),

        h ("O iv menor: o empréstimo mais comum"),
        p (
            "O iv menor é o empréstimo mais frequente da música popular. Em Dó maior, ele é Fm7. Aparece tipicamente antes do I, criando uma cadência suave e melancólica: FM7 → Fm7 → CM7. A nota que muda é o Lá, que vira Lá bemol; essa única nota altera completamente a cor do trecho. Você já ouviu isso em milhares de músicas."),
        b ("FM7 → Fm7 → CM7: a cadência do suspiro."),
        b ("O Lá bemol é a nota que muda tudo."),
        b ("É o empréstimo modal mais reconhecível."),
        aud ({ "F3", "A3", "C4", "E4", "F3", "G#3", "C4", "D#4" },
             "FM7 e depois Fm7: a única nota que muda (Lá → Lá bemol) transforma a cor."),

        h ("O bVII: a cadência mixolídia"),
        p (
            "O bVII é o acorde de Bb em Dó maior, formado a partir do sétimo grau rebaixado. Ele cria a chamada cadência mixolídia, uma resolução que soa \"roqueira\" e modal: Bb → C. Essa cadência aparece muito no rock e no folk, e é um dos empréstimos mais usados fora do jazz."),
        b ("bVII em Dó: Bb (Bb, D, F, Ab)."),
        b ("Cadência mixolídia: Bb → C."),
        b ("Som modal e roqueiro, sem a tensão do V7."),
        aud ({ "A#2", "D3", "F3", "G#3", "C3", "E3", "G3" },
             "Bb (bVII) resolvendo em C: a cadência mixolídia."),

        h ("O bVI: a cor dramática"),
        p (
            "O bVI é o acorde de Ab em Dó maior. Ele acrescenta duas notas bemóis (Lá bemol e Mi bemol) e por isso soa dramático, quase cinematográfico. É muito usado em finais de música e em passagens que precisam de peso emocional. O bVI costuma vir antes do bVII ou do V, preparando a resolução."),
        b ("bVI em Dó: Ab7M (Ab, C, Eb, G)."),
        b ("Introduz o Lá bemol e o Mi bemol."),
        b ("Som dramático, usado em finais de música."),

        h ("Empréstimo modal e modulação"),
        p (
            "É importante não confundir empréstimo modal com modulação. No empréstimo, a música usa um acorde de fora e volta imediatamente ao tom principal. Na modulação, o novo tom se estabelece. O empréstimo é uma cor passageira; a modulação é uma mudança permanente de centro."),
        b ("Empréstimo: acorde passageiro, o tom não muda."),
        b ("Modulação: o novo tom se firma com cadências."),
        b ("O mesmo acorde pode ser empréstimo ou modulação, conforme o que vem depois."),
        c (
            "Regra prática: se depois do acorde emprestado você volta ao tom de origem, foi empréstimo. Se o tom novo continua, foi modulação."),

        h ("Como identificar de ouvido"),
        p (
            "O empréstimo modal tem um som reconhecível: parece que a música entrou num clima diferente por um instante, sem sair do lugar. As notas bemóis criam essa sensação. Treine ouvindo a diferença entre o IV maior e o iv menor, ou entre o V7 e o bVII. Cada um dos dois deixa uma marca distinta no ouvido."),
        b ("Ouça a mudança de cor sem mudança de centro."),
        b ("Identifique a nota bemol que apareceu."),
        b ("Pergunte: essa cor vem de qual grau do menor paralelo?"),
        aud ({ "C3", "E3", "G3", "F3", "G#3", "C4", "D#4", "C3", "E3", "G3" },
             "C → Fm7 → C: um empréstimo modal (iv menor) que volta ao tom."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é achar que qualquer acorde de fora é empréstimo modal. Só é empréstimo quando vem do modo paralelo (mesma tônica). Um dominante secundário, por exemplo, não é empréstimo modal. Outro erro é usar empréstimos em excesso, o que dilui o efeito e faz a música perder o centro."),
        b ("Empréstimo vem do modo paralelo, não de qualquer tom."),
        b ("Dominante secundário não é empréstimo modal."),
        b ("Use empréstimos com moderação: o contraste é o efeito."),
        c (
            "Dica: comece pelo iv menor e pelo bVII, que são os mais fáceis de ouvir e de encaixar."),

        h ("Aplicação prática"),
        p (
            "Pratique inserir empréstimos modais em progressões que você já conhece. Toque C → F → Fm → C e note o efeito. Depois experimente C → Ab → Bb → C e compare. No instrumento, os acordes emprestados exigem digitações diferentes; use o app para conferir se as notas que você toca formam os acordes certos."),
        b ("Toque C → FM7 → Fm7 → C (iv menor)."),
        b ("Toque C → Ab7M → Bb7 → C (bVI + bVII)."),
        b ("Compare o efeito de cada empréstimo."),
        part ("m8_partitura_ii_v_i_menor",
              { "F3", "A3", "C4", "E4", "F3", "G#3", "C4", "D#4", "C3", "E3", "G3" },
              "Partitura de FM7 → Fm7 → C: o iv menor como empréstimo modal. Ouça a cor melancólica."),

        h ("Empréstimos modais em outras tonalidades"),
        p (
            "Os empréstimos modais funcionam em qualquer tonalidade. Em Sol maior, os empréstimos do Sol menor são Gm, Cm7, Eb7M, F7 e Bb7M. Em Fá maior, são Fm, Bbm7, Db7M, Eb7 e Ab7M. O processo é sempre o mesmo: pegue o tom paralelo menor e importe os seus acordes para o tom maior. Uma vez entendido o princípio, você o aplica em qualquer tom."),
        b ("Em Dó maior: Cm, Fm7, Ab7M, Bb7, Eb7M."),
        b ("Em Sol maior: Gm, Cm7, Eb7M, F7, Bb7M."),
        b ("Em Fá maior: Fm, Bbm7, Db7M, Eb7, Ab7M."),
        tbl ({ "Tonalidade", "iv menor", "bVI", "bVII" }, {
            { "Dó maior", "Fm7", "Ab7M", "Bb7" },
            { "Sol maior", "Cm7", "Eb7M", "F7" },
            { "Fá maior", "Bbm7", "Db7M", "Eb7" },
            { "Si bemol maior", "Ebm7", "Gb7M", "Ab7" },
        }),

        h ("Empréstimos modais na guitarra"),
        p (
            "No instrumento, os acordes emprestados exigem digitações diferentes porque introduzem notas bemóis. O iv menor, por exemplo, tem a terça bemol, o que muda a forma do acorde. Praticar os empréstimos ajuda a expandir o vocabulário de acordes e a familiaridade com o braço. O app confere se as notas que você toca formam o acorde emprestado pedido."),
        b ("Aprenda a forma do iv menor e desloque-a."),
        b ("Confira as notas bemóis: são elas que definem o empréstimo."),
        b ("Toque o arpejo para ouvir a cor."),
        aud ({ "C3", "E3", "G3", "F3", "G#3", "C4", "D#4", "A#2", "D3", "F3", "G#3", "C3", "E3", "G3" },
             "C → Fm7 → Bb7 → C: dois empréstimos modais (iv menor e bVII) antes da resolução."),

        h ("Empréstimo modal e a escala"),
        p (
            "Quando você improvisa sobre um acorde emprestado, a escala acompanha a cor. Sobre o iv menor (Fm7), use a escala dórica de Fá; sobre o bVI (Ab7M), use a escala lídia de Lá bemol; sobre o bVII (Bb7), use a mixolídia de Si bemol. Usar a escala certa mantém a coerência entre a harmonia e a melodia, e evita notas que soariam erradas."),
        b ("Fm7 (iv): escala dórica de Fá."),
        b ("Ab7M (bVI): escala lídia de Lá bemol."),
        b ("Bb7 (bVII): escala mixolídia de Si bemol."),
        c (
            "Regra prática: a escala de um acorde emprestado vem do modo paralelo, não do tom principal. É isso que dá a cor."),

        h ("Empréstimos modais e o bIII"),
        p (
            "O bIII é o acorde de Eb em Dó maior. Ele acrescenta as notas Mi bemol e Si bemol, criando um brilho modal característico. Aparece muito em músicas que misturam o maior com o menor, e costuma vir antes do bVII ou do iv menor. O bIII é um dos empréstimos que mais claramente anuncia a passagem pelo modo paralelo."),
        b ("bIII em Dó: Eb7M (Eb, G, Bb, D)."),
        b ("Introduz o Mi bemol e o Si bemol."),
        b ("Costuma vir antes do bVII ou do iv menor."),
        aud ({ "D#3", "G3", "A#3", "D4", "C3", "E3", "G3" },
             "Eb7M (bIII) resolvendo em C: o brilho modal do empréstimo."),

        h ("Empréstimo modal e reharmonização"),
        p (
            "Os empréstimos modais são uma ferramenta importante de reharmonização. Trocar um acorde do campo maior por um empréstimo do menor muda a cor da música sem mudar a melodia. É uma forma elegante de dar nova vida a uma progressão conhecida, e aparece muito em arranjos de bossa nova e de MPB."),
        b ("Substitua o IV maior pelo iv menor para uma cor melancólica."),
        b ("Acrescente um bVII antes do I para uma cadência modal."),
        b ("Use o bVI para dar drama a um final."),
        tbl ({ "Acorde original", "Empréstimo", "Efeito" }, {
            { "FM7 (IV)", "Fm7 (iv)", "melancolia" },
            { "G7 (V)", "Bb7 (bVII)", "cadência modal" },
            { "Am7 (vi)", "Ab7M (bVI)", "drama" },
        }),

        h ("Empréstimos modais e a forma da música"),
        p (
            "Os empréstimos modais aparecem em pontos específicos da forma de uma música. O iv menor costuma marcar o fim de uma frase, criando uma cadência melancólica antes da resolução. O bVI e o bVII aparecem em finais de seção, dando peso ao fechamento. Reconhecer onde cada empréstimo cabe é parte do bom gosto musical, e vem com a prática de ouvir e tocar."),
        b ("iv menor: fim de frase, cor melancólica."),
        b ("bVI e bVII: finais de seção, peso e drama."),
        b ("O bIII: transições e brilho modal."),
        aud ({ "F3", "A3", "C4", "E4", "F3", "G#3", "C4", "D#4", "C3", "E3", "G3" },
             "FM7 → Fm7 → C: o iv menor fechando a frase com cor melancólica."),

        h ("Resumo do tópico"),
        b ("Empréstimo modal é usar um acorde do modo paralelo."),
        b ("Os modos paralelos compartilham a mesma tônica."),
        b ("Principais empréstimos do menor: i, iv, bIII, bVI, bVII."),
        b ("O iv menor é o mais comum; o bVII dá a cadência mixolídia."),
        b ("Empréstimo é passageiro; modulação é permanente."),
        c (
            "Nos exercícios deste tópico, toque os acordes emprestados e confira com o app. Ele reconhece as notas e verifica se o acorde montado corresponde ao pedido."),
    };
}

} // namespace cursomusica::content
