#include "Course/Content/Topics.h"

// Topic 6H — Relações entre os campos maior e menor (Módulo 6, Etapa 6).
// Fonte de verdade do texto: docs/MUSIC.md §6.2 (bloco H).
namespace cursomusica::content
{

std::vector<ContentItem> topic6H()
{
    return {

        p (
            "Você já montou o campo harmônico maior (módulo 1) e o campo harmônico menor (tópico F). Agora vamos entender como os dois se relacionam. Essa relação é o que explica por que uma música em Lá menor tem quase os mesmos acordes de uma música em Dó maior, e por que é tão fácil trocar de uma tonalidade para outra dentro da mesma música."),
        p (
            "Existem três relações que você precisa conhecer: a relativa (mesmas notas, tônica diferente), a paralela (mesma tônica, notas diferentes) e a mistura dos dois campos dentro da mesma música. Cada uma tem um uso e um som próprios."),
        c (
            "Ideia central: relativa = mesma armadura, outra tônica. Paralela = mesma tônica, outra armadura. A música real mistura as duas o tempo todo."),

        h ("A relativa maior e a relativa menor"),
        p (
            "Duas tonalidades são relativas quando compartilham exatamente as mesmas notas e a mesma armadura de clave, mas têm tônicas diferentes. Toda tonalidade maior tem uma relativa menor (começando no seu sexto grau) e toda tonalidade menor tem uma relativa maior (começando no seu terceiro grau)."),
        b ("Dó maior e Lá menor são relativas: as duas não têm acidentes."),
        b ("Sol maior e Mi menor são relativas: as duas têm um sustenido (F#)."),
        b ("A relativa menor começa no sexto grau da maior; a relativa maior, no terceiro grau da menor."),
        img ("m6_relacao_maior_menor", "Maior, menor relativa e menor paralela: três escalas, dois tipos de relação."),
        aud ({ "C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5" }, "Dó maior: 1 2 3 4 5 6 7."),
        aud ({ "A3", "B3", "C4", "D4", "E4", "F4", "G4", "A4" }, "Lá menor (relativa): as mesmas notas, começando no sexto grau."),

        h ("A relativa: os acordes compartilhados"),
        p (
            "Como a relativa maior e a relativa menor têm as mesmas notas, elas também têm os mesmos acordes — apenas em outra ordem e com outra função. O campo de Dó maior (C, Dm, Em, F, G, Am, Bdim) é o mesmo campo de Lá menor (Am, Bdim, C, Dm, Em, F, G). O que muda é qual acorde é a tônica."),
        tbl ({ "Grau em Dó maior", "Acorde", "Grau em Lá menor", "Função em Lá menor" }, {
            { "I", "C", "III", "relativa maior (tônica)" },
            { "ii", "Dm", "iv", "subdominante" },
            { "iii", "Em", "v", "dominante fraco" },
            { "IV", "F", "VI", "subdominante" },
            { "V", "G", "VII", "dominante" },
            { "vi", "Am", "i", "tônica menor" },
            { "vii", "Bdim", "ii", "subdominante" },
        }),
        c (
            "É por isso que uma música em Dó maior pode passar por Lá menor sem trocar nenhum acorde: basta fazer o Lá menor (Am) soar como repouso, em vez de um acorde de passagem."),

        h ("A paralela maior e a paralela menor"),
        p (
            "Duas tonalidades são paralelas quando têm a mesma tônica, mas escalas diferentes. Dó maior e Dó menor são paralelas: a tônica é a mesma (Dó), mas os acordes são diferentes por causa dos graus abaixados. A relação paralela é a base dos empréstimos modais (tópico G)."),
        b ("Dó maior: C, Dm, Em, F, G, Am, Bdim."),
        b ("Dó menor: Cm, Ddim, Eb, Fm, Gm, Ab, Bb."),
        b ("A diferença está nos graus b3, b6 e b7, que mudam três acordes."),
        aud ({ "C4", "E4", "G4", "B4" }, "C7M (campo de Dó maior): a tônica maior."),
        aud ({ "C4", "Eb4", "G4", "Bb4" }, "Cm7 (campo de Dó menor): a tônica paralela menor."),
        c (
            "Compare os dois acordes de tônica: C7M e Cm7 têm a mesma tônica (Dó), mas a terça muda (E contra Eb). É a diferença entre o campo maior e o paralelo menor."),

        h ("Comparando os dois campos"),
        p (
            "A tabela abaixo compara o campo maior e o campo menor a partir da mesma tônica. Repare que apenas três graus mudam (o III, o VI e o VII) — os outros quatro permanecem, embora com qualidades diferentes em alguns casos. Entender isso ajuda a lembrar os dois campos de uma só vez."),
        tbl ({ "Grau", "Campo maior de Dó", "Campo menor de Dó", "Diferença" }, {
            { "1", "C7M", "Cm7", "terça: E → Eb" },
            { "2", "Dm7", "Dm7(b5)", "quinta: A → Ab" },
            { "3", "Em7", "Ebmaj7", "raiz: E → Eb" },
            { "4", "F7M", "Fm7", "terça: A → Ab" },
            { "5", "G7", "Gm7", "terça: B → Bb" },
            { "6", "Am7", "Ab7M", "raiz: A → Ab" },
            { "7", "Bm7(b5)", "Bb7", "raiz: B → Bb" },
        }),
        c (
            "Note que o acorde de quinto grau muda de qualidade: no campo maior é G7 (dominante com terça maior); no campo menor natural é Gm7 (menor). Para ter a força da cadência no menor, usa-se o V7 da menor harmônica (G7)."),

        h ("A mistura dos dois campos"),
        p (
            "Na música real, os dois campos se misturam o tempo todo. Uma música em tonalidade maior empresta acordes do campo menor paralelo (subdominantes menores) e uma música menor usa acordes do campo maior relativo. Essa mistura é o que dá riqueza à harmonia e é a base do que os músicos chamam de harmonia funcional ampliada."),
        b ("Em tonalidade maior: empresta iv, ii(b5), bVI, bVII do campo menor paralelo."),
        b ("Em tonalidade menor: usa o V7 do campo maior paralelo para a cadência."),
        b ("A mistura cria cor sem mudar a tonalidade."),
        aud ({ "C4", "E4", "G4", "B4", "F4", "Ab4", "C5", "Eb5", "G4", "B4", "D5", "F5", "C4", "E4", "G4", "B4" },
             "I → iv → V → I em Dó: C7M, Fm7, G7, C7M — o IV escurecendo para iv na mistura dos campos."),

        h ("Tonalidades próximas e distantes"),
        p (
            "Quanto mais notas duas tonalidades compartilham, mais próximas elas são, e mais fácil é modular de uma para outra. A relativa é a mais próxima (compartilha todas as notas); a paralela compartilha a tônica, mas difere em três graus. Tonalidades vizinhas no ciclo das quintas são também próximas."),
        tbl ({ "Relação", "Exemplo", "Notas em comum" }, {
            { "relativa", "Dó maior ↔ Lá menor", "todas as sete" },
            { "paralela", "Dó maior ↔ Dó menor", "quatro graus" },
            { "vizinha (quinta acima)", "Dó maior ↔ Sol maior", "seis notas" },
            { "vizinha (quinta abaixo)", "Dó maior ↔ Fá maior", "seis notas" },
            { "distante", "Dó maior ↔ Fá# maior", "poucas notas" },
        }),
        c (
            "A modulação (mudança de tonalidade) é mais fácil entre tonalidades próximas. É por isso que as músicas costumam modular para a relativa, a paralela ou uma vizinha do ciclo das quintas."),

        h ("Aplicação prática"),
        p (
            "Na prática, você usa as relações para acompanhar, modular e improvisar. Saber que Lá menor e Dó maior compartilham os acordes permite tocar nas duas sem mudar a posição da mão. Saber que Dó maior e Dó menor são paralelas permite trocar acordes e dar cor. E saber as tonalidades próximas permite modular com naturalidade."),
        b ("Toque a mesma progressão em Dó maior e em Lá menor: os acordes são os mesmos."),
        b ("Troque o IV pelo iv para sentir a relação paralela."),
        b ("Use as tonalidades próximas para modular dentro de uma música."),
        c (
            "Nos exercícios deste tópico, você identifica as relações entre tonalidades e toca as progressões no instrumento. O app confere as notas que você toca."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é confundir relativa com paralela: a relativa compartilha as notas (Dó maior / Lá menor), a paralela compartilha a tônica (Dó maior / Dó menor). Outro erro é esquecer que o campo menor natural tem o v menor, e que para a cadência se usa o V7 da menor harmônica. Confira sempre a terça do acorde de dominante."),
        b ("Relativa: mesma armadura. Paralela: mesma tônica."),
        b ("Para a cadência menor, use o V7 (terça maior)."),
        b ("Ouça as duas tonalidades antes de escolher os acordes."),

        h ("O ciclo das quintas e as tonalidades vizinhas"),
        p (
            "O ciclo das quintas organiza as tonalidades pela proximidade. Subindo de quinta em quinta (Dó → Sol → Ré → Lá…), cada passo acrescenta um sustenido. Descendo (Dó → Fá → Sib → Mib…), cada passo acrescenta um bemol. Duas tonalidades vizinhas no ciclo compartilham seis das sete notas, e por isso a modulação entre elas é natural."),
        tbl ({ "Tonalidade", "Armadura", "Relativa menor" }, {
            { "Dó maior", "nenhum acidente", "Lá menor" },
            { "Sol maior", "1 sustenido (F#)", "Mi menor" },
            { "Ré maior", "2 sustenidos (F# C#)", "Si menor" },
            { "Lá maior", "3 sustenidos (F# C# G#)", "Fá# menor" },
            { "Fá maior", "1 bemol (Bb)", "Ré menor" },
            { "Sib maior", "2 bemóis (Bb Eb)", "Sol menor" },
        }),
        c (
            "A relativa menor fica sempre um tom e meio abaixo da tônica maior (ou três semitons). É por isso que a relativa menor de Dó maior é Lá menor, e não Si menor."),

        h ("Como escolher a tonalidade de uma música"),
        p (
            "Na prática, você escolhe a tonalidade de uma música pelo clima que quer e pela facilidade de execução. Uma tonalidade maior soa alegre e resolvida; uma menor, melancólica e introspectiva. Instrumentalmente, algumas tonalidades são mais confortáveis na guitarra (Dó, Sol, Lá, Mi, Ré) porque usam cordas soltas e formas abertas."),
        b ("Clima: maior para alegre, menor para melancólico."),
        b ("Facilidade: tonalidades com cordas soltas são mais confortáveis."),
        b ("Voz: a tonalidade pode mudar para caber na voz do cantor."),
        aud ({ "C4", "E4", "G4", "B4" }, "C7M: o clima alegre da tonalidade maior."),
        aud ({ "C4", "Eb4", "G4", "Bb4" }, "Cm7: o clima melancólico da tonalidade menor paralela."),

        h ("Como modular de uma tonalidade a outra"),
        p (
            "Modular é mudar de tonalidade dentro da mesma música. O caminho mais fácil é usar um acorde comum às duas tonalidades como ponte. Para ir de Dó maior a Lá menor (relativas), basta fazer o Am soar como repouso. Para ir de Dó maior a Dó menor (paralelas), use o iv ou o bVI como empréstimo. Para ir de Dó maior a Sol maior (vizinhas), use o acorde de Ré (ii em Dó, V em Sol) como ponte."),
        b ("Relativas: use o acorde comum como novo repouso."),
        b ("Paralelas: use um empréstimo (iv, bVI) como ponte."),
        b ("Vizinhas: use o acorde de passagem que pertence às duas (o V da nova)."),
        c (
            "A modulação mais comum na música popular é para a relativa menor (de Dó maior para Lá menor) e para a subdominante (de Dó maior para Fá maior). Ambas são naturais e fáceis de ouvir."),

        h ("Erros comuns ao estudar as relações"),
        p (
            "O erro mais comum é confundir relativa com paralela: a relativa compartilha as notas (Dó maior / Lá menor); a paralela compartilha a tônica (Dó maior / Dó menor). Outro erro é achar que uma música em Lá menor e uma em Dó maior são \"a mesma coisa\" — são o mesmo material, mas com centros diferentes, e por isso soam diferente. E há quem module sem preparação, o que soa abrupto."),
        b ("Relativa: mesma armadura. Paralela: mesma tônica."),
        b ("Mesmo material não significa mesma música: o centro importa."),
        b ("Prepare a modulação com um acorde comum às duas tonalidades."),
        c (
            "O app ajuda a ouvir: toque a mesma progressão em Dó maior e em Lá menor e compare os centros. Depois toque C7M e Cm7 e sinta a diferença entre maior e paralela menor."),

        h ("Resumo do tópico"),
        b ("Relativa: mesma armadura, outra tônica (Dó maior ↔ Lá menor)."),
        b ("Paralela: mesma tônica, outra armadura (Dó maior ↔ Dó menor)."),
        b ("Os dois campos compartilham quatro graus; três mudam."),
        b ("A música real mistura os dois campos (empréstimos modais)."),
        b ("Tonalidades próximas facilitam a modulação."),
    };
}

} // namespace cursomusica::content
