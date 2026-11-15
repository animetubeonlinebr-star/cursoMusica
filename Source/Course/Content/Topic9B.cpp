#include "Course/Content/Topics.h"

// Topic 9B — Dominantes diminutos (DomDim) (Modulo 9, Etapa 9).
// Fonte de verdade do texto: docs/MUSIC.md (bloco B da Etapa 9).
namespace cursomusica::content
{

std::vector<ContentItem> topic9B()
{
    return {

        p (
            "O dominante diminuto, abreviado DomDim, é o acorde dominante enriquecido com a nona bemol e outras tensões. Ele é a sonoridade típica do jazz e da música instrumental, e aparece sempre que um acorde de sétima precisa resolver com mais força. Neste tópico você aprende a escala que o gera e as substituições que ela permite."),
        p (
            "Você já conhece o acorde diminuto do tópico anterior. Agora o objetivo é entender a ponte entre ele e o dominante: as duas sonoridades compartilham notas e por isso podem se substituir. Essa é a chave do DomDim."),

        h ("O que é o acorde dominante com nona bemol"),
        p (
            "Um dominante comum, como C7, tem as notas Do, Mi, Sol e Sib (0, 4, 7 e 10). Quando acrescentamos a nona bemol (Reb), obtemos C7(b9): Do, Mi, Sol, Sib e Reb. A nona bemol é uma tensão forte, que empurra o acorde com mais urgência para a resolução."),
        p (
            "O interessante é o que acontece quando empilhamos as notas desse dominante sem a fundamental. Sem o Do, sobram Mi, Sol, Sib e Reb. Essas quatro notas — 3, 5, 7 e 9 bemol do dominante — formam exatamente um acorde diminuto de sétima. É o famoso acorde diminuto substituto."),
        tbl ({ "Acorde", "Notas", "Intervalos (semitons)" }, {
            { "C7", "Do - Mi - Sol - Sib", "0 - 4 - 7 - 10" },
            { "C7(b9)", "Do - Mi - Sol - Sib - Reb", "0 - 4 - 7 - 10 - 13" },
            { "Dim7 substituto (sobre Mi)", "Mi - Sol - Sib - Reb", "0 - 3 - 6 - 9 a partir de Mi" },
        }),
        c (
            "Regra prática: o dim7 que resolve para um acorde está sempre um semitom acima dele. Para resolver em Do, use o dim7 de Reb (ou de Si, sua enarmonia)."),
        aud ({ "C4", "E4", "G4", "A#4", "C#5" }, "C7(b9): o dominante com a nona bemol, tenso e resoluto."),
        aud ({ "E4", "G4", "A#4", "C#5" }, "O mesmo sem a fundamental: é exatamente um dim7 sobre Mi."),
        part ("m9_partitura_domdim", { "C4", "E4", "G4", "A#4", "C#5" },
              "Partitura do C7(b9): Do-Mi-Sol-Sib-Reb. A nona bemol (Reb) é a tensão que resolve."),

        h ("A escala diminuta meio-tom / tom"),
        p (
            "Toda sonoridade nasce de uma escala. O DomDim nasce da escala diminuta na forma meio-tom, tom, meio-tom, tom. Partindo de Do, a escala é: Do, Reb, Mib, Mi, Fa#, Sol, Lá, Sib. Repare na alternância: um semitom, um tom, um semitom, um tom, e assim por diante."),
        p (
            "O nome DomDim vem justamente de o acorde ser dominante e a escala ser diminuta. Sobre cada nota dessa escala, o dominante ganha as tensões 9 bemol, 11 justa e 13 bemol — o pacote completo do jazz."),
        tbl ({ "Grau na escala", "Nota a partir de Do", "Distância (semitons)", "Papel no acorde" }, {
            { "1", "Do", "0", "fundamental" },
            { "b2", "Reb", "1", "nona bemol" },
            { "b3", "Mib", "3", "nona sustenida (enarmonia)" },
            { "3", "Mi", "4", "terça maior" },
            { "#4", "Fa#", "6", "quarta aumentada" },
            { "5", "Sol", "7", "quinta justa" },
            { "6", "Lá", "9", "décima terceira" },
            { "b7", "Sib", "10", "sétima menor" },
        }),
        img ("m9_domdim_escala", "A escala diminuta meio-tom/tom e os quatro dominantes que ela serve."),
        aud ({ "C4", "C#4", "D#4", "E4", "F#4", "G4", "A4", "A#4" },
             "A escala diminuta meio-tom/tom a partir de Do: cada salto é meio-tom ou tom."),

        h ("Os quatro dominantes da mesma escala"),
        p (
            "Como a escala diminuta se repete a cada três semitons, a mesma escala serve a quatro dominantes diferentes, separados por terças menores. A escala de C7(b9) também é a escala de Eb7(b9), de Gb7(b9) e de A7(b9). Isso dá ao Dominante Diminuto um poder enorme de rearmonização: um único padrão de escala cobre quatro acordes."),
        b ("C7(b9), Eb7(b9), Gb7(b9) e A7(b9) compartilham a mesma escala diminuta."),
        b ("Cada um resolve em um acorde diferente: Fa, Lá bemol, Si e Re."),
        b ("Trocar a fundamental entre eles é uma substituição clássica de jazz."),
        c (
            "Essa propriedade é a mesma simetria do dim7, vista de outro ângulo: o acorde e a escala descrevem o mesmo ciclo de terças menores."),

        h ("Como tocar o DomDim"),
        p (
            "Na guitarra, o DomDim é abordado por dois caminhos. O primeiro é tocar o acorde dominante com a nona bemol na parte aguda, o que já dá a cor. O segundo é tocar o dim7 substituto um semitom acima da tônica de destino, o que é muito mais simples no braço e produz o mesmo efeito harmônico."),
        b ("Caminho 1: forma de dominante com a nona bemol no topo."),
        b ("Caminho 2: dim7 um semitom acima do acorde de resolução."),
        b ("No jazz, a escala diminuta é usada em improvisos sobre o dominante."),
        aud ({ "C#4", "E4", "G4", "A#4", "C#5" },
             "Dim7 substituto sobre Reb, resolvendo em Do: o mesmo som do C7(b9) sem a fundamental."),

        h ("Como o DomDim aparece na música"),
        p (
            "O DomDim aparece sempre que um dominante precisa de mais tensão. Em vez de tocar um C7 simples, o arranjador usa C7(b9) ou o dim7 substituto. O efeito é imediato: a resolução fica mais forte e o som, mais sofisticado. Você ouve isso em standards de jazz, em choros e em sambas mais elaborados."),
        b ("Antes da tônica: substitui o dominante por um som mais tenso."),
        b ("Em modulações: o dim7 conduz a uma nova tonalidade."),
        b ("Em finais de frase: a nona bemol cria suspense antes da resolução."),

        h ("A nona bemol na prática"),
        p (
            "A nona bemol é a nota que define a sonoridade do DomDim. Ela fica a um semitom acima da fundamental — no caso de C7(b9), é o Reb. Ao tocar, procure ouvir essa nota como uma tensão que quer cair meio tom na tônica. Esse movimento cromático é o que dá força a resolução."),
        b ("Nona bemol: um semitom acima da fundamental."),
        b ("Ela resolve descendo meio tom na tônica."),
        b ("Tocar a nona bemol na voz aguda deixa a tensão mais evidente."),
        aud ({ "C#5", "C5" }, "A nona bemol (Reb) resolvendo na tônica (Do): o coração do DomDim."),

        h ("Erros comuns com o DomDim"),
        p (
            "A maioria dos problemas com o DomDim vem de confundir o acorde com o dominante comum ou de errar a posição do dim7 substituto. Fique atento a estes pontos."),
        b ("Tocar a nona natural em vez da nona bemol: a cor desaparece."),
        b ("Colocar o dim7 substituto no lugar errado: ele vai um semitom acima da resolução."),
        b ("Esquecer que a escala também serve a quatro dominantes."),
        c (
            "Se o acorde soar apenas como um dominante comum, provavelmente a nona bemol não foi tocada ou foi substituída pela nona natural."),

        h ("Aplicando na prática"),
        p (
            "Pratique resolvendo um DomDim na tônica. Comece tocando o C7(b9) e depois a tônica Fa, para ouvir a resolução de quarta. Em seguida, toque o dim7 substituto e note que o efeito é o mesmo. Por fim, experimente improvisar sobre a escala diminuta meio-tom/tom e ouvir como as tensões pedem resolução."),
        b ("Toque C7(b9) resolvendo em Fa maior."),
        b ("Toque o dim7 substituto no lugar do dominante."),
        b ("Improvisar sobre a escala diminuta meio-tom/tom."),
        aud ({ "C4", "E4", "G4", "A#4", "C#5", "F4", "A4", "C5" },
             "C7(b9) resolvendo em Fa maior: a tensão cede ao repouso."),

        h ("O DomDim no blues e no jazz"),
        p (
            "O dominante diminuto aparece muito no blues e no jazz, justamente porque nesses estilos o dominante é tratado como um momento de tensão máxima. No blues, a troca de um dominante simples por um dominante com nona bemol acrescenta a tensão que o estilo pede. No jazz, o DomDim é a base do vocabulário de improvisação sobre acordes dominantes."),
        b ("Blues: a nona bemol sobre o V grau."),
        b ("Jazz: escala diminuta sobre dominantes."),
        b ("Bossa: cor sobre os dominantes das passagens."),

        h ("A relação entre o DomDim e o diminuto comum"),
        p (
            "Vale fixar a relação entre os dois. O diminuto comum é um acorde por si mesmo, que pode ter função própria. O DomDim é uma sonoridade aplicada sobre um dominante. Mas, na prática, os dois se confundem, porque o acorde diminuto substituto é exatamente a parte superior do dominante com nona bemol. Saber disso permite usar o dim7 como uma ferramenta para colorir dominantes."),
        b ("Diminuto comum: acorde com função própria."),
        b ("DomDim: sonoridade sobre o dominante."),
        b ("O dim7 substituto é a parte superior do dominante."),
        aud ({ "C4", "D#4", "F#4", "A4" }, "Diminuto comum sobre Do: som instável, sem função definida."),
        aud ({ "C#4", "E4", "G4", "A#4" },
             "O mesmo tipo de acorde sobre Reb, agora lido como parte de um dominante."),

        h ("A condução cromática do DomDim"),
        p (
            "O DomDim conduz as vozes por semitons, assim como o diminuto comum. A nona bemol resolve descendo meio tom, a terça maior pode subir ou descer, e as demais notas também se movem por semitons. Essa condução cromática é o que faz a resolução soar tão satisfatória: o ouvido percebe cada voz se aproximando do destino."),
        b ("A nona bemol desce meio tom para a tônica."),
        b ("A terça maior conduz para a tônica ou para a terça menor."),
        b ("A condução cromática é a marca do DomDim."),

        h ("Escolhendo entre DomDim e dominante comum"),
        p (
            "Nem todo dominante pede a nona bemol. Em estilos mais simples, um dominante comum resolve melhor. O DomDim entra quando a harmonia pede mais cor: em baladas, em jazz, em bossa e em arranjos mais elaborados. O critério é o contexto: quanto mais rica a harmonia ao redor, mais o DomDim se encaixa."),
        b ("Estilos simples: dominante comum."),
        b ("Harmonia rica: dominante com nona bemol."),
        b ("O critério é sempre o contexto da música."),

        h ("Por que o DomDim tem quatro dominantes"),
        p (
            "A razão pela qual quatro dominantes dividem a mesma escala vem da simetria da escala diminuta. Como ela se repete de três em três semitons, ao deslocar a escala para cima de uma terça menor obtemos exatamente as mesmas notas, apenas com outro nome. Assim, a escala que serve a C7(b9) também serve a Eb7(b9), Gb7(b9) e A7(b9), e cada um desses dominantes resolve numa tônica diferente."),
        p (
            "Essa propriedade é o que dá ao DomDim o seu poder de rearmonização. Um único desenho de escala, aprendido uma vez, cobre quatro acordes distintos. Em vez de decorar quatro escalas, o aluno decora uma e desloca-a de terça menor em terça menor. É economia de esforço com ganho de vocabulário."),
        b ("Uma escala, quatro dominantes, quatro tônicas de resolução."),
        b ("Deslocar a escala de terça menor em terça menor repete as notas."),
        b ("O mesmo desenho serve para improvisar sobre os quatro acordes."),
        aud ({ "C4", "C#4", "D#4", "E4", "F#4", "G4", "A4", "A#4", "C5" },
             "A escala do DomDim subindo: a partir de qualquer nota do ciclo, as notas se repetem."),

        h ("O DomDim e a nona bemol na partitura"),
        p (
            "Na partitura, o dominante com nona bemol aparece como um acorde de cinco notas, com a nona bemol destacada acima da tétrade. Ler essa nona é o que permite reconhecer o DomDim de imediato. Quando você vir um acorde de sétima dominante com uma nota a um semitom acima da fundamental, está diante de um DomDim."),
        b ("A nona bemol fica um semitom acima da fundamental."),
        b ("Ela é a nota que caracteriza o DomDim na partitura."),
        b ("Sem ela, o acorde é apenas um dominante comum."),

        h ("Resumo do tópico"),
        b ("DomDim = dominante com nona bemol (e outras tensões)."),
        b ("Nasce da escala diminuta meio-tom / tom."),
        b ("Sem a fundamental, o dominante com nona bemol vira um dim7."),
        b ("A mesma escala serve a quatro dominantes a uma terça menor."),
        b ("O dim7 substituto fica um semitom acima da resolução."),
        c (
            "Nos exercícios, toque o dominante com nona bemol e o dim7 substituto. O app reconhece as notas e confere as classes de altura."),
    };
}

} // namespace cursomusica::content
