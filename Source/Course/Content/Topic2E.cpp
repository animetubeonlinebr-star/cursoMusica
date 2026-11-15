#include "Course/Content/Topics.h"

// Topic 2E — Terças, quartas, quintas, sextas, sétimas e nonas.
// Fonte de verdade do texto: docs/MUSIC.md §2.2 (bloco E).
namespace cursomusica::content
{

std::vector<ContentItem> topic2E()
{
    return {

        p (
            "Este tópico percorre os intervalos que você mais vai usar na prática, um por um: terça, quarta, quinta, sexta, sétima e nona. Cada um tem uma função na música. Conhecer o papel de cada um é o que permite montar acordes, harmonizar melodias e escolher notas para improvisar."),
        p (
            "Você já sabe nomear todos pelo quadro móvel. Agora o objetivo é reconhecer cada um pelo som e pela posição, e entender para que ele serve."),

        h ("Terças: o coração do acorde"),
        p (
            "A terça define se um acorde é maior ou menor. É o intervalo que dá a cor básica da harmonia. Uma terça maior produz o som alegre; uma terça menor, o som triste. Por isso ela é o intervalo mais importante de todos."),
        b ("Terça maior: 4 semitons (Dó–Mi)."),
        b ("Terça menor: 3 semitons (Dó–Mib)."),
        b ("Empilhando duas terças, formam-se as tríades que você usa em todo acorde."),
        aud ({ "C4", "E4" }, "Terça maior: som maior, aberto."),
        aud ({ "C4", "D#4" }, "Terça menor: som menor, fechado."),

        h ("Quartas: movimento e suspensão"),
        p (
            "A quarta justa tem 5 semitons e um som firme, de chamada. É muito usada em riffs e em acordes suspensos (sus4), quando substitui a terça e cria uma sensação de suspensão que pede resolução."),
        b ("Quarta justa: 5 semitons (Dó–Fá)."),
        b ("No acorde sus4, a quarta substitui a terça temporariamente."),
        aud ({ "C4", "F4" }, "Quarta justa: firme, anunciadora."),

        h ("Quintas: a base do poder"),
        p (
            "A quinta justa tem 7 semitons e é o intervalo mais consonante depois da oitava. É a base dos power chords do rock e da estabilidade harmônica. Quando uma quinta aparece, o som soa cheio e resolvido."),
        b ("Quinta justa: 7 semitons (Dó–Sol)."),
        b ("Power chord: tônica + quinta, sem terça (nem maior nem menor)."),
        b ("Quinta diminuta: 6 semitons; quinta aumentada: 8 semitons."),
        aud ({ "C4", "G4" }, "Quinta justa: cheia, estável, base do power chord."),

        h ("Sextas: doçura e movimento"),
        p (
            "A sexta maior tem 9 semitons; a menor, 8. São intervalos expressivos, muito usados em melodias e em harmonizações de terças e sextas. Dão um som doce e cantável, com movimento."),
        b ("Sexta maior: 9 semitons (Dó–Lá)."),
        b ("Sexta menor: 8 semitons (Dó–Láb)."),
        aud ({ "C4", "A4" }, "Sexta maior: doce e expansiva."),

        h ("Sétimas: tensão e identidade"),
        p (
            "A sétima é o intervalo que define o tipo de acorde de quatro notas. A sétima maior (11 semitons) dá um som brilhante e suspenso; a sétima menor (10 semitons) cria o som do dominante e do blues, que pede resolução. A sétima é o motor da harmonia funcional."),
        b ("Sétima maior: 11 semitons (Dó–Si)."),
        b ("Sétima menor: 10 semitons (Dó–Sib)."),
        b ("Acordes de sétima são a base do jazz, da bossa e do blues."),
        aud ({ "C4", "B4" }, "Sétima maior: brilhante, suspensa."),
        aud ({ "C4", "A#4" }, "Sétima menor: tensa, pede resolução."),

        h ("Nonas: a segunda uma oitava acima"),
        p (
            "A nona é o mesmo intervalo que a segunda, mas uma oitava acima da tônica. Ela acrescenta cor sem mudar a função do acorde. Aparece nos acordes de nona (9) e nas tensões do jazz e da MPB."),
        b ("Nona maior: 14 semitons (a segunda maior uma oitava acima)."),
        b ("Nona menor: 13 semitons."),
        b ("Acordes com nona: som mais rico, sem perder a identidade."),
        aud ({ "C4", "E4", "G4", "D5" }, "Acorde com nona: tônica, terça, quinta e a nona por cima."),

        h ("Tabela-resumo dos intervalos práticos"),
        tbl ({ "Intervalo", "Semitons", "Papel na música" }, {
            { "terça maior", "4", "acorde maior; cor alegre" },
            { "terça menor", "3", "acorde menor; cor triste" },
            { "quarta justa", "5", "movimento, suspensão (sus4)" },
            { "quinta justa", "7", "estabilidade, power chord" },
            { "sexta maior", "9", "melodia doce, harmonização" },
            { "sétima maior", "11", "acorde de sétima maior; brilho" },
            { "sétima menor", "10", "dominante e blues; tensão" },
            { "nona", "14 (2 + 12)", "cor e tensão sobre o acorde" },
        }),


        img ("m2_intervalos_papeis", "O papel de cada intervalo na construção da música."),

        h ("Terças: o intervalo que decide o clima"),
        p (
            "A terça é o intervalo mais importante da harmonia porque decide se um acorde é maior ou menor. Em toda a música popular, é ela que dá a cor básica. Quando você ouve 'alegre' ou 'triste', na maioria das vezes está ouvindo a diferença entre uma terça maior e uma terça menor."),
        b ("Terça maior (4 semitons): base do acorde maior."),
        b ("Terça menor (3 semitons): base do acorde menor."),
        b ("Sobrepor terças constrói as tríades e as tétrades."),
        aud ({ "C4", "E4" }, "Terça maior: som maior."),
        aud ({ "C4", "D#4" }, "Terça menor: som menor."),

        h ("Quartas: o intervalo do movimento"),
        p (
            "A quarta justa tem um som firme e anunciador, muito usado em riffs e em acordes suspensos. Quando ela substitui a terça num acorde (acorde sus4), cria uma suspensão que pede resolução. É também o intervalo que separa a maioria das cordas da guitarra, o que faz dela um ponto de referência constante no braço."),
        b ("Quarta justa (5 semitons): firme, de movimento."),
        b ("Acorde sus4: a quarta substitui a terça temporariamente."),
        aud ({ "C4", "F4" }, "Quarta justa: som firme e anunciador."),

        h ("Quintas: o intervalo da estabilidade"),
        p (
            "A quinta justa é o intervalo mais consonante depois da oitava. Ela dá estabilidade e poder, e é a base dos power chords do rock. Quando a quinta é alterada (aumentada ou diminuta), o acorde ganha tensão — é o caso dos acordes aumentados e diminutos."),
        b ("Quinta justa (7 semitons): estável, cheia."),
        b ("Quinta aumentada (8 semitons): tensa, etérea."),
        b ("Quinta diminuta (6 semitons): instável, igual ao trítono."),
        aud ({ "C4", "G4" }, "Quinta justa: som cheio e estável."),

        h ("Sextas, sétimas e nonas: cor e tensão"),
        p (
            "A sexta dá um som doce e cantável; a sétima define o tipo de acorde de quatro notas e cria tensão; a nona acrescenta cor sem mudar a função do acorde. Juntas, essas extensões são o que dá riqueza à harmonia de jazz, bossa e MPB."),
        b ("Sexta maior (9) e sexta menor (8): som doce, melódico."),
        b ("Sétima maior (11): brilho; sétima menor (10): tensão de dominante."),
        b ("Nona (14 = 2 + 12): cor sobre o acorde."),
        aud ({ "C4", "A4" }, "Sexta maior: doce e expansiva."),
        aud ({ "C4", "B4" }, "Sétima maior: brilhante e suspensa."),
        aud ({ "C4", "A#4" }, "Sétima menor: tensa, pede resolução."),
        aud ({ "C4", "E4", "G4", "D5" }, "Acorde com nona: tônica, terça, quinta e nona."),

        h ("Combinando os intervalos na prática"),
        p (
            "Na prática, esses intervalos não aparecem isolados: eles se combinam para formar acordes e melodias. Um acorde de sétima maior, por exemplo, reúne a terça maior, a quinta justa e a sétima maior. Saber identificar cada intervalo permite entender qualquer acorde como uma soma deles."),
        tbl ({ "Acorde", "Intervalos que o formam" }, {
            { "maior", "terça maior + quinta justa" },
            { "menor", "terça menor + quinta justa" },
            { "sétima maior", "terça maior + quinta justa + sétima maior" },
            { "sétima dominante", "terça maior + quinta justa + sétima menor" },
            { "menor com sétima", "terça menor + quinta justa + sétima menor" },
            { "nona", "tríade + nona (segunda uma oitava acima)" },
        }),
        c (
            "Nos exercícios, você tocará cada um desses intervalos e o app vai conferir a distância. Pratique também cantá-los, para ligar o ouvido ao dedo."),


        h ("Terças e a formação das tríades"),
        p (
            "As tríades são construídas empilhando terças. A tríade maior é uma terça maior seguida de uma terça menor; a menor é o contrário. Entender essa construção permite montar acordes em qualquer tom, apenas escolhendo as terças corretas a partir da tônica."),
        b ("Maior: terça maior (4) + terça menor (3) = 0, 4, 7."),
        b ("Menor: terça menor (3) + terça maior (4) = 0, 3, 7."),
        b ("Diminuta: terça menor (3) + terça menor (3) = 0, 3, 6."),
        b ("Aumentada: terça maior (4) + terça maior (4) = 0, 4, 8."),

        h ("Quartas e quintas na condução"),
        p (
            "Quartas e quintas aparecem tanto em riffs quanto na condução das vozes. A quinta justa dá a base estável, e a quarta, o movimento. Em um acompanhamento, alternar quarta e quinta entre os acordes cria uma sensação de deslocamento suave, muito usada em música popular."),
        b ("Quinta justa: base estável do acorde."),
        b ("Quarta justa: movimento entre acordes."),
        b ("Alternar as duas conduz as vozes sem grandes saltos."),
        aud ({ "C4", "F4", "G4" }, "Quarta e quinta a partir de Dó: movimento e estabilidade lado a lado."),

        h ("Sétimas e nonas na cor do acorde"),
        p (
            "As sétimas e as nonas são extensões que dão cor sem mudar a função do acorde. A sétima define se o acorde é maior, dominante ou menor; a nona acrescenta brilho. Essas extensões são a base do som de jazz, bossa nova e MPB."),
        b ("Sétima maior: brilho e suspensão."),
        b ("Sétima menor: tensão de dominante."),
        b ("Nona: cor adicional, sem alterar a função."),
        aud ({ "C4", "E4", "G4", "D5" }, "Acorde com nona: a cor da nona sobre a tríade."),
        c (
            "Nos exercícios deste tópico, você toca os intervalos práticos e o app confere a distância, ligando o nome do intervalo à posição no braço."),


        h ("Intervalos compostos na prática"),
        p (
            "Na prática, muitos acordes usam intervalos compostos: a nona, a décima primeira e a décima terceira são versões agudas da segunda, da quarta e da sexta. Reconhecer que são os mesmos intervalos uma oitava acima simplifica a compreensão e permite nomear acordes complexos sem dificuldade."),
        b ("Nona = segunda uma oitava acima."),
        b ("Décima primeira = quarta uma oitava acima."),
        b ("Décima terceira = sexta uma oitava acima."),
        aud ({ "C4", "E4", "G4", "D5" }, "A nona (Ré agudo) é a segunda uma oitava acima da tônica."),

        h ("Escolhendo os intervalos certos"),
        p (
            "Cada estilo musical favorece certos intervalos. O rock valoriza a quinta (power chords) e a terça maior; o blues, a sétima menor; o jazz, as sétimas e nonas; a bossa nova, as sextas e sétimas maiores. Conhecer os intervalos permite reconhecer e reproduzir o som de cada estilo."),
        tbl ({ "Estilo", "Intervalos característicos" }, {
            { "rock", "quinta justa, terça maior" },
            { "blues", "sétima menor, terça menor" },
            { "jazz", "sétimas, nonas, décimas terceiras" },
            { "bossa nova", "sextas, sétimas maiores" },
            { "pop", "terças, quintas, sextas" },
        }),
        c (
            "Identificar esses intervalos de ouvido é o que permite reconhecer o estilo de uma música e escolher como acompanhá-la."),

        h ("Resumo do tópico"),
        b ("Terças definem maior/menor; são o coração do acorde."),
        b ("Quartas trazem movimento e suspensão."),
        b ("Quintas dão estabilidade e poder."),
        b ("Sextas dão doçura e movimento melódico."),
        b ("Sétimas definem o tipo de acorde e criam tensão."),
        b ("Nonas são segundas uma oitava acima; acrescentam cor."),
        c (
            "Nos exercícios, você tocará cada um desses intervalos e o app vai conferir a distância em semitons. Pratique também cantar cada um, para ligar o ouvido ao dedo."),
    };
}

} // namespace cursomusica::content
