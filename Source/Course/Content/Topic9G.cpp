#include "Course/Content/Topics.h"

// Topic 9G — Simetria e escalas simetricas (Modulo 9, Etapa 9).
// Fonte de verdade do texto: docs/MUSIC.md (bloco G da Etapa 9).
namespace cursomusica::content
{

std::vector<ContentItem> topic9G()
{
    return {

        p (
            "Simetria, na música, significa que um padrão se repete a distâncias iguais. Você já viu isso no diminuto, que se repete de três em três semitons. Neste tópico você estuda as escalas simétricas — as que dividem a oitava em partes iguais — e entende por que elas dão ao guitarrista uma vantagem enorme no braço."),
        p (
            "As escalas simétricas não são mais difíceis do que as outras; elas são apenas organizadas de outra forma. Como o padrão se repete, a mesma digitação serve em várias posições. Entender isso reduz o esforço de decorar e amplia o vocabulário."),

        h ("O que torna uma escala simétrica"),
        p (
            "Uma escala é simétrica quando a distância entre as suas notas se repete em ciclo. A escala cromática, que sobe de semitom em semitom, é o exemplo mais simples. A escala de tons inteiros, que sobe de tom em tom, é outro. A escala diminuta, que alterna tom e semitom, é o terceiro exemplo. Em todas, a oitava se divide em partes iguais."),
        tbl ({ "Escala", "Intervalos (semitons)", "Divisão da oitava", "Transposições" }, {
            { "Cromática", "0-1-2-3-4-5-6-7-8-9-10-11", "12 semitons", "1" },
            { "Tons inteiros", "0-2-4-6-8-10", "6 tons", "2" },
            { "Diminuta (tom-meio-tom)", "0-2-3-5-6-8-9-11", "4 terças menores", "3" },
            { "Diminuta (meio-tom-tom)", "0-1-3-4-6-7-9-10", "4 terças menores", "3" },
            { "Aumentada", "0-3-4-7-8-11", "3 terças maiores", "4" },
        }),
        c (
            "A última coluna é a chave: quanto mais simétrica a escala, menos transposições ela tem. A escala de tons inteiros tem apenas duas formas; a diminuta, três."),

        h ("A escala de tons inteiros"),
        p (
            "A escala de tons inteiros sobe apenas de tom em tom: 0, 2, 4, 6, 8 e 10. Ela tem seis notas e se repete a cada dois tons. Por ser totalmente simétrica, existem apenas duas escalas de tons inteiros em toda a música. Ela cria uma sonoridade flutuante, sem repouso, e é muito usada sobre acordes dominantes aumentados."),
        b ("Seis notas, todas separadas por um tom."),
        b ("Apenas duas formas em toda a música."),
        b ("Som flutuante, sem centro tonal claro."),
        aud ({ "C4", "D4", "E4", "F#4", "G#4", "A#4", "C5" },
             "A escala de tons inteiros a partir de Do: cada salto é um tom exato."),

        h ("A escala diminuta"),
        p (
            "A escala diminuta alterna tom e semitom: 0, 1, 3, 4, 6, 7, 9, 10. Ela tem oito notas e se repete a cada terça menor. Por isso existem apenas três escalas diminutas. Você já a encontrou no tópico do DomDim; aqui ela aparece como estrutura simétrica, e não apenas como escala de improvisação."),
        b ("Oito notas, alternando tom e semitom."),
        b ("Repete-se a cada terça menor: três formas no total."),
        b ("Da acesso ao dim7, ao dominante com nona bemol e ao m7(b5)."),
        aud ({ "C4", "C#4", "D#4", "E4", "F#4", "G4", "A4", "A#4" },
             "A escala diminuta meio-tom/tom: a alternância de semitom e tom se repete."),

        h ("A escala aumentada"),
        p (
            "A escala aumentada combina terças maiores e semitons: 0, 3, 4, 7, 8, 11. Ela tem seis notas e se repete a cada terça maior. Existem quatro escalas aumentadas. Ela é usada sobre acordes aumentados e em passagens de fusão, onde a sonoridade exótica é bem-vinda."),
        b ("Seis notas, alternando terça maior e semitom."),
        b ("Repete-se a cada terça maior: quatro formas."),
        b ("Usada sobre acordes aumentados."),
        aud ({ "C4", "D#4", "E4", "G4", "G#4", "B4", "C5" },
             "A escala aumentada: terças maiores e semitons alternados."),

        h ("A simetria no braço da guitarra"),
        p (
            "A simetria tem uma consequência prática enorme na guitarra. Como o padrão se repete, a mesma digitação se desloca pelo braço sem mudar de forma. Você aprende uma forma de escala diminuta e ela serve em quatro posições, separadas por terças menores. Isso economiza memorização e permite frasear com mais liberdade."),
        b ("Uma digitação de escala diminuta serve em quatro posições."),
        b ("A escala de tons inteiros tem apenas duas formas no braço."),
        b ("Desloque as frases pelo braço mantendo o desenho."),
        img ("m9_simetria", "Escalas simétricas: cada uma divide a oitava em partes iguais."),
        c (
            "Ao praticar uma escala simétrica, procure o momento em que o padrão se repete. Quando você ouve a repetição, a escala se torna previsível."),

        h ("Ouvindo as escalas simétricas"),
        p (
            "As escalas simétricas tem sonoridades muito características. A de tons inteiros flutua, sem tensão direcional. A diminuta cria tensão controlada, que resolve bem sobre dominantes. A aumentada soa exótica e instável. Reconhecer cada uma pelo ouvido é o que permite escolher a escala certa para cada acorde."),
        b ("Tons inteiros: flutuante, sem direção."),
        b ("Diminuta: tensa, mas com resolução clara."),
        b ("Aumentada: exótica e instável."),
        aud ({ "C4", "D4", "E4", "F#4", "G#4", "A#4" },
             "A escala de tons inteiros soando: repare que ela não tem repouso."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é tratar as escalas simétricas como se fossem escalas maiores ou menores, esperando um repouso que elas não tem. Outro erro é decorar cada transposição separadamente, o que é desnecessário justamente por causa da simetria."),
        b ("Procurar um repouso que a escala simétrica não tem."),
        b ("Decorar todas as transposições em vez de usar a simetria."),
        b ("Usar a escala simétrica fora do acorde que a pede."),
        c (
            "Se a escala soar deslocada do acorde, verifique a relação entre a fundamental da escala e a do acorde. A simetria funciona quando essa relação está clara."),

        h ("Aplicando na prática"),
        p (
            "Comece tocando cada escala simétrica lentamente, ouvindo a repetição do padrão. Depois, toque a mesma escala em duas ou três posições diferentes do braço, confirmando que o desenho se repete. Por fim, improvise uma frase curta sobre um acorde e use a escala simétrica correspondente."),
        b ("Toque cada escala devagar, ouvindo a repetição."),
        b ("Toque a mesma escala em várias posições."),
        b ("Improvise uma frase curta sobre o acorde adequado."),
        aud ({ "C4", "C#4", "D#4", "E4", "F#4", "G4", "A4", "A#4", "C5" },
             "A escala diminuta inteira, subindo até a oitava: a simetria fica audível."),

        h ("As escalas simétricas é a improvisação"),
        p (
            "Para quem improvisa, as escalas simétricas são um recurso de deslocamento. Como o padrão se repete, uma frase construída sobre a escala pode ser movida de terça menor em terça menor e continuar dentro da mesma sonoridade. Isso permite criar sequências longas e modernas, muito usadas na fusão e no jazz. A simetria transforma a escala num padrão móvel."),
        b ("Mova a frase de terça menor em terça menor."),
        b ("A frase continua dentro da mesma sonoridade."),
        b ("A simetria cria sequências longas e modernas."),

        h ("A simetria e a memória"),
        p (
            "A simetria também ajuda a memória. Quando você entende que uma escala se repete, deixa de decorar cada transposição separadamente. Aprender três formas de escala diminuta é suficiente para cobrir as doze tonalidades, porque cada forma serve a quatro. Isso reduz o esforço e libera a atenção para o que realmente importa: a música."),
        b ("Três formas de escala diminuta cobrem as doze tonalidades."),
        b ("Duas formas de tons inteiros cobrem todas as tônicas."),
        b ("Entender a simetria reduz o esforço de memorização."),

        h ("Simetria e assimetria"),
        p (
            "Nem toda escala é simétrica, e isso é bom. As escalas maiores e menores são assimétricas justamente porque tem um centro tonal claro. A assimetria cria a direção e o repouso que a música tonal precisa. A simetria, por outro lado, cria flutuação e tensão. Saber quando usar cada uma é parte da linguagem harmônica."),
        tbl ({ "Tipo de escala", "Simetria", "Efeito" }, {
            { "Maior e menor", "assimétrica", "centro tonal, repouso" },
            { "Diminuta", "simétrica", "tensão controlada" },
            { "Tons inteiros", "simétrica", "flutuação, sem repouso" },
            { "Aumentada", "simétrica", "exotismo, instabilidade" },
        }),
        c (
            "A música tonal vive da assimetria; a música modal e a instrumental exploram a simetria. As duas convivem."),

        h ("A escala aumentada e a sua simetria"),
        p (
            "A escala aumentada também é simétrica: ela combina terças maiores e semitons, dividindo a oitava em três partes iguais de quatro semitons. Por isso existem apenas quatro escalas aumentadas. Ela é usada sobre acordes aumentados, que têm a mesma estrutura de simetria, e cria uma sonoridade exótica, muito usada em passagens de fusão e de música contemporânea."),
        b ("Combina terças maiores e semitons."),
        b ("Divide a oitava em três partes iguais."),
        b ("Existem apenas quatro escalas aumentadas."),

        h ("Simetria e transposição"),
        p (
            "A simetria transforma a transposição numa operação simples. Numa escala assimétrica, transpor exige reconstruir todo o desenho no braço. Numa escala simétrica, basta deslocar a digitação por uma distância que divide a oitava, e o desenho se repete. Isso é o que torna as escalas simétricas tão econômicas para o guitarrista: menos memorização, mais música."),
        b ("Transpor uma escala simétrica é deslocar o desenho."),
        b ("O deslocamento é por uma distância que divide a oitava."),
        b ("Menos memorização, mais liberdade no braço."),
        aud ({ "C4", "D#4", "E4", "G4", "G#4", "B4", "C5" },
             "A escala aumentada: terças maiores e semitons, um desenho que se repete."),

        h ("Simetria e a percepção de repouso"),
        p (
            "A simetria tem uma consequência profunda para a percepção. Quando uma escala divide a oitava em partes iguais, não há uma nota que se destaque como repouso: todas têm o mesmo peso. Isso cria a sensação de flutuação que caracteriza a música modal e a contemporânea. O ouvido, acostumado ao repouso tonal, percebe a simetria como algo suspenso e aberto."),
        b ("Numa escala simétrica, nenhuma nota é o repouso."),
        b ("Todas as notas têm o mesmo peso."),
        b ("A sensação é de flutuação, não de direção."),

        h ("A simetria e o ouvido absoluto relativo"),
        p (
            "Estudar escalas simétricas desenvolve uma forma especial de ouvir: o ouvido relativo. Como o padrão se repete a distâncias iguais, o aluno aprende a reconhecer a distância independentemente da nota de partida. Essa habilidade é valiosa para tirar músicas de ouvido, porque permite identificar um trecho pelo seu contorno, e não pela nota absoluta."),
        b ("A simetria treina o ouvido relativo."),
        b ("A distância é reconhecida independentemente da nota."),
        b ("Habilidade valiosa para tirar músicas de ouvido."),

        h ("Simetria e composição"),
        p (
            "Na composição, a simetria é uma ferramenta de estrutura. O compositor pode construir uma passagem inteira sobre uma escala simétrica e obter uma sonoridade coerente e moderna. Também pode usar a simetria como contraste: um trecho simétrico que flutua, seguido de um trecho tonal que repousa. É esse jogo entre o estável e o suspenso que dá riqueza à música."),
        b ("Construa uma passagem sobre uma escala simétrica."),
        b ("Use a simetria como contraste com trechos tonais."),
        b ("O jogo entre estável e suspenso dá riqueza."),

        h ("Resumo do tópico"),
        b ("Escala simétrica divide a oitava em partes iguais."),
        b ("Tons inteiros: seis notas, duas formas."),
        b ("Diminuta: oito notas, três formas."),
        b ("Aumentada: seis notas, quatro formas."),
        b ("Na guitarra, a mesma digitação se desloca pelo braço."),
        c (
            "Nos exercícios, toque as escalas simétricas e os acordes que elas geram. O app reconhece as notas e confere as classes de altura."),
    };
}

} // namespace cursomusica::content
