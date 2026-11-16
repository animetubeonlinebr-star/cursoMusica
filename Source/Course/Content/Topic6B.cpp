#include "Course/Content/Topics.h"

// Topic 6B — Escala menor harmônica (Módulo 6, Etapa 6).
// Fonte de verdade do texto: docs/MUSIC.md §6.2 (bloco B).
namespace cursomusica::content
{

std::vector<ContentItem> topic6B()
{
    return {

        p (
            "A escala menor natural soa bem, mas tem um problema prático: o seu sétimo grau é menor (b7), ou seja, está a um tom inteiro da tônica. Numa cadência, esse grau não tem força para puxar de volta ao repouso. Para resolver isso, os compositores começaram a subir o sétimo grau meio-tom, criando a sensível — a nota que fica a um semitom da tônica. Nasce assim a escala menor harmônica."),
        p (
            "O nome \"harmônica\" vem justamente daí: essa escala foi criada para melhorar a harmonia, isto é, os acordes e as cadências da tonalidade menor. Ela é a base do campo harmônico menor clássico e aparece em toda a música tonal, do barroco ao flamenco, do rock ao jazz."),
        c (
            "Resumo: a escala menor harmônica é a menor natural com o sétimo grau elevado (7 em vez de b7). Em Lá menor harmônica: A B C D E F G#."),

        h ("Como se forma a escala menor harmônica"),
        p (
            "A escala menor harmônica tem os graus 1, 2, b3, 4, 5, b6, 7. Compare com a menor natural (1 2 b3 4 5 b6 b7): a única diferença é que o b7 sobe para 7. Esse pequeno ajuste muda tudo — a sensível aparece e o acorde de dominante ganha a força que faltava."),
        b ("Menor natural: 1 2 b3 4 5 b6 b7 (em Lá: A B C D E F G)."),
        b ("Menor harmônica: 1 2 b3 4 5 b6 7 (em Lá: A B C D E F G#)."),
        b ("O sétimo grau sobe meio-tom: G vira G# (a sensível de Lá menor)."),
        img ("m6_menor_harmonica", "A escala de La menor harmonica no braço: o 7º grau (G#) elevado cria a sensível."),

        h ("O padrão de tons e semitons"),
        p (
            "O padrão de distâncias da escala menor harmônica é: tom, semitom, tom, tom, semitom, tom e meio (de b6 para 7), semitom (de 7 para a oitava). Esse \"tom e meio\" entre o b6 e o 7 é a marca registrada da escala: ele cria o intervalo de segunda aumentada, que dá à escala um som oriental, dramático e reconhecível."),
        tbl ({ "Passo", "De", "Para", "Distância" }, {
            { "1", "1 (tônica)", "2", "tom" },
            { "2", "2", "b3", "semitom" },
            { "3", "b3", "4", "tom" },
            { "4", "4", "5", "tom" },
            { "5", "5", "b6", "semitom" },
            { "6", "b6", "7", "tom e meio" },
            { "7", "7", "8 (oitava)", "semitom" },
        }),
        c (
            "O salto de tom e meio entre o b6 e o 7 é o intervalo mais característico da escala menor harmônica. É ele que produz aquele som de música árabe ou de flamenco que você reconhece na hora."),

        h ("A segunda aumentada"),
        p (
            "O intervalo entre o b6 e o 7 mede três semitons, mas é escrito como uma segunda (de Fá a Sol#, por exemplo). Por isso ele se chama segunda aumentada: o número é 2 (segunda), mas a distância foi alargada em relação à segunda maior. É o único intervalo da escala que soa \"estranho\" para quem vem da escala maior — e é exatamente isso que dá o caráter à escala."),
        b ("Em Lá menor harmônica, o intervalo entre F e G# é uma segunda aumentada."),
        b ("Ele soa como um salto exótico e resolve na tônica (A)."),
        b ("É o intervalo que aparece quando você toca a escala rapidamente e ouve um \"degrau faltando\"."),
        aud ({ "A3", "B3", "C4", "D4", "E4", "F4", "G#4", "A4" },
             "Escala de La menor harmônica: repare no salto entre Fá (b6) e Sol# (7)."),

        h ("A sensível e a força da cadência"),
        p (
            "A grande conquista da escala menor harmônica é a sensível. Como o 7º grau fica a apenas um semitom da tônica, ele cria uma tensão que pede resolução. O acorde construído sobre o 5º grau (o dominante) passa a ser maior com sétima menor — um acorde de dominante de verdade — e a cadência V7 → i ganha a mesma força que na tonalidade maior."),
        b ("Sem a sensível, o v menor não puxa de volta à tônica."),
        b ("Com a sensível, o V7 (Mi7 em Lá menor) resolve com força no i (Am)."),
        b ("É essa força que faz a menor harmônica ser a base do campo harmônico menor."),
        aud ({ "E4", "G#4", "B4", "D5" }, "Acorde de Mi7: o dominante que resolve em Lá menor."),
        aud ({ "E4", "G#4", "B4", "D5", "A3", "C4", "E4" },
             "Cadência V7 → i em Lá menor: Mi7 resolvendo em Am."),

        h ("Como localizar no braço"),
        p (
            "Localizar a escala menor harmônica no braço é como localizar a menor natural, com um ajuste: onde você tocaria o b7, toque o 7 (um semitom acima). Você pode partir da menor natural que já conhece e subir o sétimo grau, ou aplicar o padrão T-S-T-T-S-T½-S a partir da tônica."),
        b ("Toque a menor natural e suba o sétimo grau meio-tom."),
        b ("Ou aplique o padrão T-S-T-T-S-T½-S a partir da tônica."),
        b ("O intervalo de tom e meio aparece sempre entre o b6 e o 7."),
        c (
            "Nos exercícios deste tópico, o app reconhece as notas tocadas e confere se elas formam a escala menor harmônica pedida, em qualquer posição."),

        h ("O som da escala menor harmônica"),
        p (
            "A escala menor harmônica soa mais dramática e tensa que a menor natural. O intervalo de segunda aumentada dá um toque exótico; a sensível dá a sensação de que a música está sempre \"chegando\" em algum lugar. É uma escala muito usada em trilhas de filme, música árabe, flamenco, metal neoclássico e jazz."),
        aud ({ "A3", "B3", "C4", "D4", "E4", "F4", "G#4", "A4" },
             "Escala de La menor harmônica: som dramático, com sensível."),
        c (
            "Compare com a menor natural (tópico A) e com a menor melódica (tópico D): são três climas diferentes partindo da mesma tônica."),

        h ("Uso na música"),
        p (
            "A escala menor harmônica é usada principalmente sobre o acorde de dominante (V7) de uma tonalidade menor, onde a sensível cria a tensão da cadência. Também é usada em passagens melódicas que querem aquele som exótico, e como base para os seus modos, que você verá no próximo tópico."),
        b ("Sobre o V7 de uma tonalidade menor: a sensível cria a resolução."),
        b ("Em passagens dramáticas: o intervalo de segunda aumentada dá o caráter."),
        b ("Nos modos da menor harmônica: cada grau gera uma sonoridade própria."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é subir o sétimo grau também na descida, o que soa \"duro\" para quem está acostumado com a menor natural. Na prática, a menor harmônica é uma escala de subida e de harmonia — o sétimo elevado serve à cadência. Outro erro é esquecer que a escala continua tendo o b6: subir o 6 também seria a menor melódica, não a harmônica."),
        b ("Suba apenas o 7º grau, não o 6º."),
        b ("A sensível existe para criar a cadência V7 → i."),
        b ("Ouça a escala antes de tocar para fixar o som."),

        h ("As três formas da escala menor"),
        p (
            "A escala menor harmônica é a segunda das três escalas menores. Ela parte da menor natural e sobe apenas o sétimo grau. Essa pequena alteração cria a sensível e o intervalo de segunda aumentada, que dão à escala o seu caráter inconfundível. Comparar as três escalas menores é a melhor forma de entender o papel de cada uma."),
        tbl ({ "Escala", "6º grau", "7º grau", "Caráter" }, {
            { "menor natural", "b6", "b7", "melancólico, simples" },
            { "menor harmônica", "b6", "7", "dramático, exótico" },
            { "menor melódica", "6", "7", "suave, moderno" },
        }),
        c (
            "A menor harmônica difere da natural só no sétimo grau. Se você já toca a natural, já toca 90% da harmônica: basta subir o sétimo grau meio-tom."),

        h ("Como praticar a escala menor harmônica"),
        p (
            "Pratique a menor harmônica como a natural, mas com atenção especial ao sétimo grau. Toque a escala devagar, ouvindo o intervalo de segunda aumentada, e depois toque-a sobre um acorde de dominante de fundo (E7, no caso de Lá menor), para ouvir a sensível resolvendo na tônica. Esse é o uso mais importante da escala."),
        b ("Subida e descida devagar, ouvindo o intervalo de segunda aumentada."),
        b ("Sobre o acorde V7 de fundo: ouça a sensível resolvendo."),
        b ("Padrões de três notas, para treinar a mecânica com o sétimo elevado."),
        c (
            "Nos exercícios deste tópico, toque a escala e o acorde de dominante no instrumento. O app reconhece as notas e confere se elas formam a escala menor harmônica ou o acorde pedido."),

        h ("A escala menor harmônica na música"),
        p (
            "A escala menor harmônica aparece sempre que uma música menor quer uma cadência forte. Ela é a base do campo harmônico menor clássico e da cadência V7 → i. Também é usada em passagens melódicas que querem o som exótico da segunda aumentada, do flamenco ao metal neoclássico."),
        b ("Cadências menores: V7 → i (Mi7 → Am)."),
        b ("Passagens dramáticas: o intervalo de segunda aumentada."),
        b ("Flamenco, música árabe e metal neoclássico: a cor da escala."),
        aud ({ "E4", "F4", "G#4", "A4" }, "O movimento b6 → 7 → 1: a segunda aumentada resolvendo na tônica."),

        h ("Por que não subir o sexto também"),
        p (
            "Se você subir o sexto grau além do sétimo, deixa de ter a escala menor harmônica e passa a ter a menor melódica (próximo tópico). A diferença é de um único semitom, mas o som muda bastante: a harmônica tem o salto de tom e meio; a melódica, não. Escolher entre as duas depende do efeito que você quer."),
        b ("Só o 7º elevado: menor harmônica (salto de tom e meio)."),
        b ("O 6º e o 7º elevados: menor melódica (linha suave)."),
        b ("As duas têm a sensível; a diferença está no sexto grau."),
        c (
            "O ouvido percebe a diferença na hora: a harmônica soa exótica e angular; a melódica, fluida e suave. Ouça as duas seguidas para fixar."),

        h ("A escala menor harmônica e os seus modos"),
        p (
            "Como toda escala, a menor harmônica gera sete modos, um para cada grau. O mais famoso é o quinto (o frígio dominante), que soa flamenco e é usado sobre o acorde de dominante. O próximo tópico estuda esses modos um por um. Por ora, guarde a ideia: a menor harmônica não é só uma escala, é uma família de sete sonoridades."),
        b ("O modo 1 é a própria menor harmônica."),
        b ("O modo 5 (frígio dominante) é o mais usado."),
        b ("Cada modo combina com um tipo de acorde."),
        aud ({ "E4", "F4", "G#4", "A4", "B4", "C5", "D5", "E5" },
             "Frígio dominante a partir de Mi: o quinto modo, uma prévia do próximo tópico."),

        h ("Resumo do tópico"),
        b ("Escala menor harmônica: 1 2 b3 4 5 b6 7."),
        b ("É a menor natural com o sétimo grau elevado (a sensível)."),
        b ("O intervalo de segunda aumentada (b6 → 7) dá o caráter exótico."),
        b ("A sensível dá força ao dominante (V7) e à cadência."),
        b ("É a base do campo harmônico menor clássico."),
        b ("Comparada com a menor natural, muda só o sétimo grau — e com ele o clima inteiro."),
        b ("É a escala da cadência menor: onde há V7 → i, há menor harmônica."),
        b ("O intervalo de segunda aumentada entre o b6 e o 7 é a sua assinatura sonora."),
        part ("m6_partitura_menor_harmonica", { "A3", "B3", "C4", "D4", "E4", "F4", "G#4", "A4" },
              "Partitura da escala de La menor harmônica, com o Sol# (sensível). Ouça o que está escrito."),
    };
}

} // namespace cursomusica::content
