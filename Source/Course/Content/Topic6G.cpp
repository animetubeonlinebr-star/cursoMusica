#include "Course/Content/Topics.h"

// Topic 6G — Subdominantes menores (Módulo 6, Etapa 6).
// Fonte de verdade do texto: docs/MUSIC.md §6.2 (bloco G).
namespace cursomusica::content
{

std::vector<ContentItem> topic6G()
{
    return {

        p (
            "Até agora você estudou os campos maior e menor separadamente. Mas na música real os dois se misturam o tempo todo: é muito comum uma música em tonalidade maior emprestar acordes do campo menor paralelo. Esses acordes são chamados de subdominantes menores, e eles são a ferramenta de cor mais usada na MPB, na bossa nova e no jazz."),
        p (
            "O subdominante menor mais famoso é o iv menor dentro de uma tonalidade maior. Em Dó maior, por exemplo, você troca o F (IV, maior) pelo Fm (iv, menor). Essa simples troca de terça (de E para Eb) cria um som mais melancólico e sofisticado que aparece em milhares de músicas."),
        c (
            "Ideia central: o campo menor paralelo empresta acordes ao campo maior. O subdominante menor (iv) é o empréstimo mais comum e dá a cor de MPB e bossa."),

        h ("O que é o subdominante menor"),
        p (
            "O subdominante menor é o acorde de quarto grau menor (iv) usado dentro de uma tonalidade maior. Ele pertence ao campo menor paralelo: em Dó maior, o campo menor paralelo é Dó menor, cujo iv é Fm. Emprestar o Fm para dentro de Dó maior é o que os músicos chamam de empréstimo modal ou acorde emprestado."),
        b ("Em Dó maior, o IV é Fá maior (F)."),
        b ("O iv emprestado é Fá menor (Fm)."),
        b ("A diferença está na terça: Lá (do F) vira Ab (do Fm)."),
        img ("m6_subdominante_menor", "Os subdominantes menores emprestados do campo menor paralelo, em Dó maior."),

        h ("Como reconhecer um acorde emprestado"),
        p (
            "Um acorde emprestado é aquele que não pertence ao campo da tonalidade, mas vem do campo paralelo. O jeito mais fácil de reconhecê-lo é comparar com os acordes do campo maior: se um acorde tem um grau abaixado (b3, b6 ou b7) que não existe no campo maior, ele é um empréstimo do campo menor."),
        tbl ({ "Acorde em Dó maior", "Grau", "De onde vem", "Nota emprestada" }, {
            { "Fm7 (iv)", "iv", "campo menor paralelo", "Ab (b6) e Eb (b3)" },
            { "Dm7(b5) (ii)", "ii", "campo menor paralelo", "F (b3 do ré) e Ab (b5)" },
            { "Abmaj7 (bVI)", "bVI", "campo menor paralelo", "Ab (b6)" },
            { "Bb7 (bVII)", "bVII", "campo menor paralelo", "Bb (b7)" },
            { "Ebmaj7 (bIII)", "bIII", "campo menor paralelo", "Eb (b3)" },
            { "Db (bII, napolitano)", "bII", "empréstimo cromático", "Db (b2)" },
        }),
        c (
            "Todos esses acordes têm pelo menos uma nota que \"não pertence\" à escala de Dó maior. É essa nota estranha que dá a cor — e é ela que o ouvido percebe imediatamente."),

        h ("O iv menor (subdominante menor)"),
        p (
            "O iv menor é o subdominante menor por excelência. Ele é usado no lugar do IV maior ou logo depois dele, criando um movimento de escurecimento. A progressão I → IV → iv → I é uma das mais bonitas e mais usadas da música popular."),
        b ("I → IV → iv → I: o sol maior escurece para o sol menor antes de voltar."),
        b ("I → iv → I: troca direta, com efeito melancólico."),
        b ("O iv também prepara o V7: iv → V7 → i é a cadência menor por excelência."),
        aud ({ "C4", "E4", "G4", "B4", "F4", "A4", "C5", "E5", "F4", "G#4", "C5", "D#5" },
             "I → IV → iv em Dó: C7M, F7M, Fm7 — o subdominante menor escurecendo a harmonia."),
        part ("m6_partitura_subdominante", { "C4", "E4", "G4", "B4", "F4", "A4", "C5", "D#5", "C4", "E4", "G4" },
              "Partitura de I - iv - I em Dó (C7M / Fm7 / C7M). Ouça o efeito do subdominante menor."),

        h ("O ii meio-diminuto"),
        p (
            "Outro empréstimo muito usado é o segundo grau meio-diminuto, Dm7(b5) em Dó maior. Ele vem do campo menor paralelo (onde o ii é sempre meio-diminuto) e aparece nas cadências menores e nas passagens de jazz. É o acorde que prepara o dominante numa cadência menor."),
        b ("Em Dó maior: o ii do campo maior é Dm7 (menor)."),
        b ("O ii emprestado do campo menor é Dm7(b5) (meio-diminuto)."),
        b ("Ele prepara o V7 e é muito usado em ii → V7 → i."),
        aud ({ "D4", "F4", "G#4", "C5" }, "Dm7(b5): o ii meio-diminuto emprestado do campo menor."),

        h ("O bVI e o bVII"),
        p (
            "Os acordes de sexto e sétimo graus abaixados (bVI e bVII) são empréstimos do campo menor paralelo que dão um som modal e suave. Em Dó maior, eles são Abmaj7 e Bb7. São muito usados na MPB, na bossa e no rock, e aparecem em progressões como I → bVII → IV → I."),
        b ("bVI em Dó maior: Abmaj7 (vem do campo de Dó menor)."),
        b ("bVII em Dó maior: Bb7 (vem do campo de Dó menor)."),
        b ("Progressão modal: I → bVII → IV → I (C → Bb → F → C)."),
        aud ({ "C4", "E4", "G4", "B4", "A#3", "D4", "F4", "A4", "F4", "A4", "C5", "F5" },
             "I → bVII → IV em Dó: C7M, Bb7, F7M — som modal e suave."),

        h ("O napolitano (bII)"),
        p (
            "O acorde napolitano é o segundo grau abaixado maior (bII), usado no primeiro grau invertido. Em Dó maior, é o Db (Réb) maior. Ele é um empréstimo cromático, muito usado na música clássica e na música dramática, e resolve com força na tônica. A sua sonoridade é dramática e cheia de tensão."),
        b ("Em Dó maior: Db (bII) é o napolitano."),
        b ("Ele costuma aparecer na primeira inversão e resolve na tônica."),
        b ("Som: dramático, usado em cadencias e passagens expressivas."),

        h ("Como usar os empréstimos na prática"),
        p (
            "Na prática, você usa os empréstimos quando quer dar cor à harmonia. Uma progressão simples como I → IV → V → I pode ganhar um toque de MPB se você trocar o IV pelo iv, ou um toque modal se você acrescentar o bVII. O importante é ouvir o efeito e usar com parcimônia: o empréstimo é uma especiaria, não o prato principal."),
        tbl ({ "Progressão", "Acordes em Dó", "Efeito" }, {
            { "I → IV → iv → I", "C → F → Fm → C", "escurecimento, MPB" },
            { "I → iv → V7 → I", "C → Fm → G7 → C", "cadência menor dentro do maior" },
            { "I → bVII → IV → I", "C → Bb → F → C", "modal, rock" },
            { "I → bVI → bVII → I", "C → Ab → Bb → C", "modal, épico" },
            { "ii → V7 → I", "Dm7 → G7 → C", "cadência de jazz" },
            { "ii(b5) → V7 → i", "Dm7(b5) → G7 → Cm", "cadência menor" },
        }),
        c (
            "Nos exercícios deste tópico, você reconhece os subdominantes menores pelo som e toca as progressões no instrumento. O app confere as notas dos acordes que você toca."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é usar o subdominante menor em excesso, o que deixa a música arrastada. Outro erro é esquecer que o iv traz duas notas emprestadas (o b6 e o b3): tocar só uma delas não produz o efeito. E há quem confunda o iv menor com o IV menor da tonalidade menor — são a mesma coisa, mas em contextos diferentes."),
        b ("Use o iv com moderação: é uma especiaria."),
        b ("Toque as duas notas emprestadas (b6 e b3) para o efeito completo."),
        b ("Ouça o efeito antes de usar na música."),

        h ("O bIII (relativa do campo menor)"),
        p (
            "Outro empréstimo muito usado é o terceiro grau abaixado (bIII), que em Dó maior é o Ebmaj7 (Mib maior com sétima maior). Ele é a relativa maior do campo menor paralelo: assim como Lá menor é a relativa de Dó maior, Mib maior é a relativa de Dó menor. O bIII dá um som escuro e ao mesmo tempo suave, muito usado em passagens que querem mudar de cor sem modular."),
        b ("Em Dó maior: Ebmaj7 (bIII) vem do campo de Dó menor."),
        b ("Ele é a relativa maior do campo menor paralelo."),
        b ("Som: escuro e suave, usado em passagens de transição."),
        aud ({ "D#4", "G4", "A#4", "D5" }, "Ebmaj7 (bIII): o terceiro grau abaixado, som escuro."),

        h ("De onde vêm as notas emprestadas"),
        p (
            "Todo acorde emprestado traz pelo menos uma nota que não pertence à escala da tonalidade. Essas notas são os graus abaixados do campo menor paralelo: o b3, o b6 e o b7. Em Dó maior, a escala é C D E F G A B; o campo menor paralelo (Dó menor) tem Eb, Ab e Bb. São essas três notas que, ao aparecerem, criam a cor do empréstimo."),
        tbl ({ "Nota emprestada", "Grau no campo menor", "Em que acorde aparece" }, {
            { "Eb", "b3", "Cm7 (i), Eb (bIII), Ab7M (bVI)" },
            { "Ab", "b6", "Fm7 (iv), Ab7M (bVI)" },
            { "Bb", "b7", "Bb7 (bVII), Gm7 (v)" },
        }),
        c (
            "Se você tocar uma dessas notas (Eb, Ab, Bb) dentro de uma música em Dó maior, o ouvido reconhece na hora o \"sabor\" de MPB, de bossa ou de música romântica. É a cor do empréstimo modal."),

        h ("O empréstimo na MPB e na bossa"),
        p (
            "A MPB e a bossa nova usam os empréstimos modais o tempo todo. A progressão I → iv → I é uma assinatura do gênero: ela aparece em milhares de músicas, do samba-canção à bossa. Os acordes bVI e bVII também são muito comuns, dando aquele som suave e modal que caracteriza o gênero."),
        b ("I → iv → I: o escurecimento clássico da MPB."),
        b ("I → bVII → IV → I: o som modal da bossa e do rock."),
        b ("I → bVI → bVII → I: o som épico, muito usado em trilhas."),
        aud ({ "C4", "E4", "G4", "B4", "F4", "A4", "C5", "E5", "F4", "A4", "C5", "F5" },
             "I → iv → I em Dó: C7M, Fm7, C7M — o escurecimento da MPB."),

        h ("Como praticar os empréstimos"),
        p (
            "Pratique os empréstimos de duas formas. Primeiro, toque uma progressão simples (I → IV → V → I) e depois troque um acorde pelo seu empréstimo, ouvindo a diferença. Depois, toque progressões que já usam empréstimos (I → iv → I; I → bVII → IV → I) e ouça como a cor aparece. O objetivo é reconhecer o efeito de ouvido."),
        b ("Toque a progressão original e depois a versão com o empréstimo."),
        b ("Ouça a diferença de cor entre o IV maior e o iv menor."),
        b ("Reconheça o empréstimo pelo ouvido, não só pelo nome."),
        c (
            "Nos exercícios deste tópico, toque as progressões com empréstimos no instrumento. O app reconhece as notas dos acordes que você toca e confere se elas formam o acorde pedido."),

        h ("O empréstimo e a modulação"),
        p (
            "Um uso especial do empréstimo é a modulação: quando você usa muitos acordes do campo menor paralelo, a música pode efetivamente mudar para a tonalidade menor. Uma música em Dó maior que passa por Cm7, Fm7, Ab7M e Bb7 pode estar caminhando para Dó menor. O empréstimo é, portanto, a ponte entre o campo maior e o campo menor."),
        b ("Poucos empréstimos: cor dentro da tonalidade maior."),
        b ("Muitos empréstimos: caminho para a modulação ao campo menor."),
        b ("A música pode terminar na tonalidade menor, sem que se perceba a transição."),
        c (
            "É isso que torna o estudo das relações entre os campos maior e menor (próximo tópico) tão importante: o empréstimo é a primeira ferramenta de modulação que você aprende."),

        h ("Resumo do tópico"),
        b ("Subdominante menor: acordes do campo menor paralelo usados no campo maior."),
        b ("O iv menor é o mais comum: I → IV → iv → I."),
        b ("O ii meio-diminuto prepara o dominante numa cadência menor."),
        b ("bVI, bVII e bII (napolitano) são empréstimos modais e cromáticos."),
        b ("Use os empréstimos com moderação, para dar cor sem arrastar."),
        b ("O bIII é a relativa maior do campo menor paralelo, som escuro e suave."),
        b ("Muitos empréstimos seguidos podem levar a música a modular para o campo menor."),
    };
}

} // namespace cursomusica::content
