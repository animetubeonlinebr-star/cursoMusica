#include "Course/Content/Topics.h"

// Topic 5G — Armaduras de clave e tonalidades com sustenidos e bemóis (Módulo 5, Etapa 5).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 5, bloco G).
namespace cursomusica::content
{

std::vector<ContentItem> topic5G()
{
    return {

        p (
            "Toda tonalidade maior tem a sua armadura de clave: o conjunto de sustenidos ou bemóis que aparecem na escala daquele tom. Saber ler a armadura é saber, só de olhar a partitura, em que tonalidade a música está — e, portanto, quais acordes pertencem ao campo harmônico. É a ponte entre a teoria que você aprendeu e a leitura no papel."),
        p (
            "Neste tópico você aprende a origem das armaduras, a ordem em que os sustenidos e bemóis aparecem e como o ciclo das quintas organiza todas as tonalidades. Esse é o mapa completo que permite transpor qualquer progressão para qualquer tom com segurança."),

        h ("O que é a armadura de clave"),
        p (
            "A armadura de clave é o conjunto de acidentes (sustenidos ou bemóis) escritos logo depois da clave, no início da pauta, e que valem para toda a música. Ela não é decorativa: cada armadura indica exatamente uma tonalidade maior (e a sua relativa menor). Uma armadura com um sustenido é Sol maior (ou Mi menor); com um bemol, é Fá maior (ou Ré menor)."),
        p (
            "A armadura existe para simplificar a escrita. Em vez de escrever um Fá# em cada Fá da música de Sol maior, escreve-se um sustenido na armadura e todos os Fás já saem sustenidos. Isso economiza sinais e deixa claro, à primeira vista, o tom da música."),
        b ("Armadura = conjunto de acidentes que define a tonalidade."),
        b ("Aparece no início da pauta e vale para toda a música."),
        b ("Cada armadura corresponde a uma tonalidade maior e à sua relativa menor."),
        img ("m5_ciclo_quintas", "O ciclo das quintas: cada passo acrescenta um sustenido (sentido horário) ou um bemol (sentido anti-horário)."),

        h ("A ordem dos sustenidos e dos bemóis"),
        p (
            "Os acidentes aparecem sempre na mesma ordem, nunca em ordem aleatória. Os sustenidos seguem a ordem Fá–Dó–Sol–Ré–Lá–Mi–Si, e os bemóis seguem a ordem inversa, Si–Mi–Lá–Ré–Sol–Dó–Fá. Essa ordem é fixa porque vem do próprio ciclo das quintas: cada nova tonalidade acrescenta o próximo acidente da sequência."),
        p (
            "Conhecer a ordem é prático: se uma partitura tem três sustenidos, você já sabe que são Fá#, Dó# e Sol# — e que a tonalidade é Lá maior. Se tem dois bemóis, são Si e Mi, e a tonalidade é Si bemol maior. Não é preciso contar nota por nota."),
        tbl ({ "Armadura", "Tonalidade maior", "Relativa menor", "Acidentes" }, {
            { "sem acidentes", "Dó maior", "Lá menor", "—" },
            { "1 sustenido", "Sol maior", "Mi menor", "Fá#" },
            { "2 sustenidos", "Ré maior", "Si menor", "Fá#, Dó#" },
            { "3 sustenidos", "Lá maior", "Fá# menor", "Fá#, Dó#, Sol#" },
            { "1 bemol", "Fá maior", "Ré menor", "Sib" },
            { "2 bemóis", "Sib maior", "Sol menor", "Sib, Mib" },
            { "3 bemóis", "Mib maior", "Dó menor", "Sib, Mib, Láb" },
        }),
        c (
            "Ordem dos sustenidos: Fá–Dó–Sol–Ré–Lá–Mi–Si. Ordem dos bemóis: Si–Mi–Lá–Ré–Sol–Dó–Fá. As duas são exatamente inversas."),

        h ("O ciclo das quintas"),
        p (
            "O ciclo das quintas é o mapa que organiza todas as tonalidades. Partindo de Dó maior (sem acidentes) e subindo de quinta em quinta, você acrescenta um sustenido por vez: Dó → Sol → Ré → Lá → Mi → Si → Fá#. Descendo de quinta em quinta (ou subindo de quarta), você acrescenta um bemol por vez: Dó → Fá → Sib → Mib → Láb → Réb → Solb."),
        p (
            "Esse ciclo explica por que as tonalidades com poucos acidentes são mais usadas: elas ficam no centro do mapa, com nomes simples. Também explica a relação de relativos que você viu no tópico anterior: cada tonalidade maior e a sua relativa menor ficam no mesmo ponto do ciclo, porque compartilham a mesma armadura."),
        b ("Subir de quinta acrescenta um sustenido (Dó → Sol → Ré…)."),
        b ("Descer de quinta acrescenta um bemol (Dó → Fá → Sib…)."),
        b ("Tonalidades vizinhas no ciclo têm poucos acidentes de diferença."),
        aud ({ "C4", "G4", "D5", "A4", "E5", "B5" },
             "Ciclo das quintas: Dó → Sol → Ré → Lá → Mi, subindo de quinta em quinta."),

        h ("Tonalidades com sustenidos e com bemóis"),
        p (
            "As tonalidades se dividem em dois grupos: as que usam sustenidos e as que usam bemóis. Sol, Ré, Lá, Mi e Si maior usam sustenidos; Fá, Si bemol, Mi bemol, Lá bemol e Ré bemol maior usam bemóis. Dó maior é neutra, sem nenhum acidente. Essa divisão importa porque as notas da escala mudam de nome conforme o grupo."),
        p (
            "Por exemplo: a escala de Ré maior usa Fá# e Dó#; a escala de Si bemol maior usa Sib e Mib. Tocar as duas no braço dá as mesmas posições relativas, mas as notas escritas são diferentes. Entender isso evita o erro de escrever uma tonalidade com a grafia errada — o que muda o campo harmônico na análise."),
        b ("Tonalidades com sustenidos: Sol, Ré, Lá, Mi, Si, Fá#, Dó#."),
        b ("Tonalidades com bemóis: Fá, Sib, Mib, Láb, Réb, Solb, Dób."),
        b ("Cada grupo tem a sua própria forma de escrever as notas da escala."),

        h ("Armadura, campo harmônico e transposição"),
        p (
            "A armadura de uma tonalidade determina o seu campo harmônico. Se a armadura tem dois sustenidos, você sabe que a tonalidade é Ré maior e que o campo harmônico é D – Em – F#m – G – A – Bm – C#dim. Aplicar o padrão I – ii – iii – IV – V – vi – vii° sobre as notas da tonalidade dá, imediatamente, os sete acordes certos."),
        p (
            "É por isso que a armadura é tão útil para transpor. Se você tem uma progressão em Dó e quer tocar em Ré, basta olhar a armadura de Ré, aplicar o mesmo padrão de graus e os acordes aparecem. Não é preciso calcular nota por nota — o padrão de graus se mantém e só muda o tom."),
        tbl ({ "Tonalidade", "Campo harmônico (I – ii – iii – IV – V – vi – vii°)" }, {
            { "Dó maior", "C – Dm – Em – F – G – Am – Bdim" },
            { "Sol maior", "G – Am – Bm – C – D – Em – F#dim" },
            { "Ré maior", "D – Em – F#m – G – A – Bm – C#dim" },
            { "Fá maior", "F – Gm – Am – Bb – C – Dm – Edim" },
            { "Sib maior", "Bb – Cm – Dm – Eb – F – Gm – Adim" },
        }),
        part ("m5_partitura_campo", { "C4", "E4", "G4", "D4", "F4", "A4", "E4", "G4", "B4" },
              "Partitura dos primeiros acordes do campo de Dó. Trocar de armadura troca as notas, mas o padrão de graus é o mesmo."),

        h ("Lendo a armadura na partitura"),
        p (
            "Na partitura, a armadura aparece imediatamente depois da clave. Os sustenidos e bemóis são escritos em posições específicas do pentagrama, mas você não precisa decorar as posições para saber a tonalidade: basta contar quantos são e seguir a ordem fixa. Um sustenido é Sol maior; dois, Ré maior; três, Lá maior."),
        p (
            "Com a prática, a leitura da armadura se torna instantânea. Você olha a partitura, conta os acidentes, e já sabe em que tom está — e, portanto, quais acordes esperar. Essa é uma das habilidades que mais aceleram a leitura musical, porque elimina a surpresa: você já sabe o que vem antes de tocar."),
        b ("Conte os acidentes e siga a ordem fixa para achar a tonalidade."),
        b ("A tonalidade define os acordes esperados na música."),
        b ("Com a prática, a leitura da armadura se torna instantânea."),

        h ("Transpondo com a ajuda da armadura"),
        p (
            "Transpor é mudar a tonalidade de uma música mantendo as relações entre os graus. Com o mapa das armaduras, transpor fica simples: você identifica a tonalidade original pela armadura, escolhe a nova tonalidade, e move todos os graus o mesmo número de passos no ciclo das quintas. As distâncias entre os acordes permanecem, só mudam os nomes."),
        p (
            "Na guitarra, transpor é ainda mais fácil, porque as formas do braço se deslocam. Mas a armadura é o que garante que você não vai esquecer um acidente pelo caminho: ao mudar de tom, as notas que eram naturais podem virar sustenidos ou bemóis, e a armadura registra exatamente quais mudaram."),
        b ("Transpor mantém as distâncias entre os graus."),
        b ("A armadura registra quais notas mudaram de nome."),
        b ("No braço, as formas se deslocam; a armadura garante a grafia correta."),
        aud ({ "F4", "A4", "C5", "G4", "B4", "D5", "C5", "E5", "G5" },
             "IV – V – I em Dó maior: o mesmo padrão que, transposto, vale em qualquer armadura."),

        h ("Como memorizar as armaduras"),
        p (
            "Memorizar as armaduras é mais fácil do que parece quando se usa a ordem fixa dos acidentes. Para as tonalidades com sustenidos, basta lembrar que o último sustenido da armadura é a sensível da tonalidade — ou seja, meio tom abaixo da tônica. Se a armadura tem três sustenidos (Fá#, Dó#, Sol#), o último é o Sol#, meio tom abaixo de Lá: a tonalidade é Lá maior."),
        p (
            "Para as tonalidades com bemóis, a regra é diferente: o penúltimo bemol é a tônica. Se a armadura tem dois bemóis (Si, Mi), o penúltimo é o Si bemol: a tonalidade é Si bemol maior. Essas duas regras cobrem quase todas as armaduras e dispensam a memorização de tabelas — o que é muito útil na hora de ler uma partitura."),
        b ("Com sustenidos: o último acidente é a sensível (meio tom abaixo da tônica)."),
        b ("Com bemóis: o penúltimo bemol é a tônica."),
        b ("Essas regras cobrem quase todas as armaduras sem tabela."),
        c (
            "Uma exceção a memorizar: a armadura de um bemol (Si bemol) corresponde a Fá maior, e não se aplica a regra do penúltimo bemol (que não existe). É o único caso que precisa ser lembrado à parte."),

        h ("Armaduras na prática do guitarrista"),
        p (
            "Na prática, o guitarrista usa as armaduras de duas formas. Primeiro, para ler partituras: saber a tonalidade pela armadura permite antecipar os acidentes e os acordes. Segundo, para transpor: ao mudar de tom, você consulta a armadura da nova tonalidade para saber quais notas mudam de nome, evitando erros de grafia na hora de escrever a harmonia."),
        p (
            "Há também uma utilidade menos óbvia: a armadura indica quantos acidentes a tonalidade tem, e isso dá uma pista sobre a dificuldade da música. Tonalidades com muitas armaduras (como Fá# maior, com seis sustenidos) são mais difíceis de ler, e por isso menos usadas em material didático. As tonalidades do centro do ciclo são as mais confortáveis."),
        b ("Ler a armadura permite antecipar acidentes e acordes."),
        b ("Transpor exige consultar a armadura da nova tonalidade."),
        b ("Mais acidentes = leitura mais difícil; menos acidentes = mais confortável."),

        h ("Resumo do tópico"),
        b ("Armadura de clave é o conjunto de acidentes que define a tonalidade."),
        b ("Sustenidos seguem Fá–Dó–Sol–Ré–Lá–Mi–Si; bemóis, a ordem inversa."),
        b ("O ciclo das quintas organiza todas as tonalidades."),
        b ("A armadura determina o campo harmônico e permite transpor."),
        b ("Ler a armadura é saber o tom antes de tocar."),
        c (
            "Nos exercícios deste tópico, identifique a tonalidade pela armadura e toque acordes do campo correspondente. O app reconhece as notas e confere se o tom está correto."),
    };
}

} // namespace cursomusica::content
