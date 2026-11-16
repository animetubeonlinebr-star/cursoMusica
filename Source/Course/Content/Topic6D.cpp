#include "Course/Content/Topics.h"

// Topic 6D — Escala menor melódica (Módulo 6, Etapa 6).
// Fonte de verdade do texto: docs/MUSIC.md §6.2 (bloco D).
namespace cursomusica::content
{

std::vector<ContentItem> topic6D()
{
    return {

        p (
            "A escala menor harmônica resolveu o problema da cadência, mas criou outro: o salto de tom e meio entre o b6 e o 7 soa duro numa melodia. Para suavizar a linha melódica, os compositores subiram também o sexto grau, criando a escala menor melódica. Ela sobe suave, com o sexto e o sétimo graus elevados, e é a base de várias sonoridades modernas do jazz."),
        p (
            "No uso clássico, a escala menor melódica subia com o 6 e o 7 elevados e descia como a menor natural. Hoje, o jazz e a música moderna usam a escala melódica de forma fixa, tanto na subida quanto na descida, como uma escala própria — e é assim que vamos estudá-la."),
        c (
            "Resumo: a escala menor melódica é a menor natural com o sexto e o sétimo graus elevados. Em Lá menor melódica: A B C D E F# G#."),

        h ("Como se forma a escala menor melódica"),
        p (
            "A escala menor melódica tem os graus 1, 2, b3, 4, 5, 6, 7. Compare com a menor natural (1 2 b3 4 5 b6 b7): aqui o b6 sobe para 6 e o b7 sobe para 7. O resultado é uma escala que tem a terça menor (som menor) mas a sexta e a sétima maiores (linha ascendente suave)."),
        b ("Menor natural: 1 2 b3 4 5 b6 b7 (em Lá: A B C D E F G)."),
        b ("Menor melódica: 1 2 b3 4 5 6 7 (em Lá: A B C D E F# G#)."),
        b ("O 6º e o 7º graus sobem meio-tom: F vira F# e G vira G#."),
        img ("m6_menor_melodica", "A escala de La menor melodica no braço: o 6º (F#) e o 7º (G#) graus elevados."),

        h ("O padrão de tons e semitons"),
        p (
            "O padrão de distâncias da escala menor melódica é: tom, semitom, tom, tom, tom, tom, semitom. Repare que a partir do 5º grau ela sobe como uma escala maior (5 6 7 8 = T T S), o que dá a sensação de resolução suave. É o padrão mais \"melódico\" das três escalas menores."),
        tbl ({ "Passo", "De", "Para", "Distância" }, {
            { "1", "1 (tônica)", "2", "tom" },
            { "2", "2", "b3", "semitom" },
            { "3", "b3", "4", "tom" },
            { "4", "4", "5", "tom" },
            { "5", "5", "6", "tom" },
            { "6", "6", "7", "tom" },
            { "7", "7", "8 (oitava)", "semitom" },
        }),
        c (
            "Memorize assim: T - S - T - T - T - T - S. Só há dois semitons na escala (entre 2 e b3 e entre 7 e 8), e é por isso que ela soa tão fluida."),

        h ("Diferença entre as três escalas menores"),
        p (
            "As três escalas menores partem das mesmas notas e diferem apenas no 6º e no 7º graus. Entender essa tabela é entender todo o sistema das escalas menores — e é o que permite escolher a escala certa para cada acorde e cada momento da música."),
        tbl ({ "Escala", "Graus", "Em Lá", "Uso típico" }, {
            { "menor natural", "1 2 b3 4 5 b6 b7", "A B C D E F G", "campo menor natural, relativa maior" },
            { "menor harmônica", "1 2 b3 4 5 b6 7", "A B C D E F G#", "cadência V7 → i, som exótico" },
            { "menor melódica", "1 2 b3 4 5 6 7", "A B C D E F# G#", "jazz, bossa, acordes m7M" },
        }),
        aud ({ "A3", "B3", "C4", "D4", "E4", "F4", "G4", "A4" }, "La menor natural: b6 e b7."),
        aud ({ "A3", "B3", "C4", "D4", "E4", "F4", "G#4", "A4" }, "La menor harmônica: b6 e 7."),
        aud ({ "A3", "B3", "C4", "D4", "E4", "F#4", "G#4", "A4" }, "La menor melódica: 6 e 7."),
        c (
            "Ouça as três seguidas: a diferença está só no sexto e no sétimo graus, mas o clima muda bastante. A melódica é a mais \"cantável\" das três."),

        h ("Como localizar no braço"),
        p (
            "Localizar a menor melódica no braço é como localizar a menor harmônica, com um ajuste a mais: onde você tocaria o b6, toque o 6 (um semitom acima), e onde tocaria o b7, toque o 7. Você pode partir da menor natural e subir o sexto e o sétimo graus, ou aplicar o padrão T-S-T-T-T-T-S a partir da tônica."),
        b ("Toque a menor natural e suba o sexto e o sétimo graus."),
        b ("Ou aplique o padrão T-S-T-T-T-T-S a partir da tônica."),
        b ("A partir do 5º grau, ela sobe como uma escala maior."),
        c (
            "Nos exercícios deste tópico, o app reconhece as notas tocadas e confere se elas formam a escala menor melódica pedida, em qualquer posição."),

        h ("O som da escala menor melódica"),
        p (
            "A escala menor melódica soa mais suave e moderna que a harmônica. Como tem a terça menor (som menor) e a sexta e a sétima maiores (brilho), ela cria um som ambíguo, sofisticado, muito usado no jazz, na bossa nova e na MPB. É a escala preferida para improvisar sobre acordes menores com sétima maior (m7M) e sobre acordes meio-diminutos."),
        aud ({ "A3", "B3", "C4", "D4", "E4", "F#4", "G#4", "A4" },
             "Escala de La menor melódica: som suave, sofisticado."),
        c (
            "Sobre um acorde m7M (menor com sétima maior), a menor melódica cai como uma luva: é a escala que contém exatamente as notas do acorde mais as tensões naturais."),

        h ("Uso na música"),
        p (
            "A escala menor melódica é a base dos modos mais usados do jazz. Sobre o acorde de dominante, o seu quarto modo (o lídio dominante) é uma das escalas preferidas; sobre o dominante alterado, o sétimo modo (a escala alterada) é a escolha mais tensa. Por isso ela é uma das escalas mais importantes para quem estuda improvisação."),
        b ("Sobre m7M: a própria escala menor melódica."),
        b ("Sobre dominantes: o lídio dominante (4º modo) e a escala alterada (7º modo)."),
        b ("Sobre acordes meio-diminutos: o 6º modo."),
        aud ({ "F4", "G4", "A4", "B4", "C5", "D5", "Eb5", "F5" },
             "Lídio dominante a partir de Fá: uma das sonoridades mais usadas sobre o V7."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é misturar a menor melódica com a harmônica — trocar o 6º grau (natural na melódica, abaixado na harmônica). Outro erro é esquecer que a melódica tem a terça menor: quem sobe o 6 e o 7 e também a terça acaba tocando uma escala maior, não uma menor melódica. Confira sempre a terça."),
        b ("Confira a terça: na menor melódica, ela é menor (3 semitons)."),
        b ("Suba o 6º e o 7º graus, não o 3º."),
        b ("Ouça a escala antes de tocar para fixar o som."),

        h ("A escala menor melódica e os seus modos"),
        p (
            "Como toda escala, a menor melódica gera sete modos, um para cada grau. E aqui está a sua importância maior: os modos da menor melódica são a base do jazz moderno. O quarto modo (o lídio dominante) e o sétimo (a escala alterada) são as duas escalas mais usadas sobre acordes de dominante. O próximo tópico estuda esses modos um por um."),
        b ("O modo 1 é a própria menor melódica."),
        b ("O modo 4 (lídio dominante) é o mais usado sobre o V7."),
        b ("O modo 7 (escala alterada) é o mais tenso, sobre o V7 alterado."),
        aud ({ "F4", "G4", "A4", "B4", "C5", "D5", "Eb5", "F5" },
             "Lídio dominante a partir de Fá: uma prévia do quarto modo da melódica."),

        h ("As três formas da escala menor"),
        p (
            "A escala menor melódica é a terceira das três escalas menores. Ela parte da menor natural e sobe o sexto e o sétimo graus. Comparar as três escalas menores é a melhor forma de entender o papel de cada uma e de escolher a certa para cada situação musical."),
        tbl ({ "Escala", "6º grau", "7º grau", "Onde aparece" }, {
            { "menor natural", "b6", "b7", "campo menor natural, relativa maior" },
            { "menor harmônica", "b6", "7", "cadência V7 → i, som exótico" },
            { "menor melódica", "6", "7", "jazz, bossa, acordes m7M" },
        }),
        c (
            "A menor melódica é a mais \"moderna\" das três: sobe suave e é a base das sonoridades do jazz contemporâneo."),

        h ("Como praticar a escala menor melódica"),
        p (
            "Pratique a menor melódica como as outras, com atenção ao sexto e ao sétimo graus elevados. Toque a escala devagar, ouvindo a subida suave a partir do quinto grau. Depois toque-a sobre um acorde menor com sétima maior de fundo (Am7M, no caso de Lá menor), para ouvir como ela cai dentro da harmonia. Por fim, toque o quarto modo (lídio dominante) sobre um acorde de dominante."),
        b ("Subida e descida devagar, ouvindo a subida suave do 5º grau."),
        b ("Sobre o acorde m7M de fundo: ouça a escala dentro da harmonia."),
        b ("O quarto modo (lídio dominante) sobre um acorde de dominante."),
        c (
            "Nos exercícios deste tópico, toque a escala e o arpejo de m7M no instrumento. O app reconhece as notas e confere se elas formam a escala menor melódica ou o acorde pedido."),

        h ("A escala menor melódica na música"),
        p (
            "A escala menor melódica está por toda parte na música moderna. Ela é a base da sonoridade do jazz sobre dominantes (lídio dominante e escala alterada) e aparece na bossa nova, na MPB e no choro. Sempre que você ouve um acorde de dominante com um som sofisticado e tenso, há uma boa chance de ser um modo da menor melódica."),
        b ("Jazz: lídio dominante e escala alterada sobre o V7."),
        b ("Bossa nova e MPB: acordes menores com sétima maior."),
        b ("Choro e samba: passagens melódicas modernas."),
        aud ({ "A3", "B3", "C4", "D4", "E4", "F#4", "G#4", "A4" },
             "Escala de La menor melódica: o som suave que sustenta o jazz moderno."),

        h ("A escala menor melódica e a harmonia"),
        p (
            "A menor melódica tem uma ligação especial com a harmonia. O acorde de menor com sétima maior (m7M) contém exatamente a tônica, a terça menor, a quinta justa e a sétima maior — as notas 1, b3, 5 e 7 da escala. Por isso a menor melódica cai tão bem sobre ele: ela é, na prática, o m7M com as tensões naturais (a nona e a sexta maior) acrescentadas."),
        b ("Acorde m7M: 1, b3, 5 e 7 (as notas da escala menor melódica)."),
        b ("Sobre ele, a escala acrescenta a nona (2) e a sexta maior (6)."),
        b ("É por isso que a menor melódica é a escala preferida sobre m7M."),
        aud ({ "A3", "C4", "E4", "G#4" }, "Arpejo de Am7M: tônica, terça menor, quinta e sétima maior."),

        h ("Erros comuns ao estudar a menor melódica"),
        p (
            "Os erros mais comuns são: esquecer de elevar o sexto grau (tocando a harmônica por engano); elevar também a terça (tocando uma escala maior); e usar a escala sobre o acorde errado. A menor melódica só soa bem sobre acordes menores (m7M, m7) ou, nos seus modos, sobre acordes maiores e dominantes específicos."),
        b ("Eleve o sexto e o sétimo, não a terça."),
        b ("Não confunda com a menor harmônica (o sexto é diferente)."),
        b ("Use a escala sobre o acorde certo."),
        c (
            "O app confere as notas que você toca: se você esquecer de elevar o sexto grau, o feedback mostra que a nota está fora da escala."),

        h ("Resumo do tópico"),
        b ("Escala menor melódica: 1 2 b3 4 5 6 7."),
        b ("É a menor natural com o sexto e o sétimo graus elevados."),
        b ("Padrão: T-S-T-T-T-T-S; sobe suave a partir do 5º grau."),
        b ("Som suave e moderno; base do jazz e da bossa."),
        b ("É a base dos modos do jazz sobre dominantes (lídio dominante, alterada)."),
        b ("A terça continua menor: é ela que mantém o som menor da escala."),
        b ("Escolha entre as três menores pelo 6º e o 7º grau: natural, harmônica ou melódica."),
        b ("É a única das três menores que sobe e desce igual na prática moderna."),
        part ("m6_partitura_menor_melodica", { "A3", "B3", "C4", "D4", "E4", "F#4", "G#4", "A4" },
              "Partitura da escala de La menor melódica, com Fá# e Sol#. Ouça o que está escrito."),
    };
}

} // namespace cursomusica::content
