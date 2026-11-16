#include "Course/Content/Topics.h"

// Topic 7D — Estruturas modais e tríades do meio (Módulo 7, Etapa 7).
// Fonte de verdade do texto: docs/MUSIC.md §7.2 (bloco D).
namespace cursomusica::content
{

std::vector<ContentItem> topic7D()
{
    return {

        p (
            "Até agora você empilhou notas a partir de uma tônica. Neste tópico você dá um passo importante: aprende a usar as estruturas modais — acordes que “vestem” um modo — e as tríades do meio, que são tríades construídas sobre graus internos da escala, não sobre a tônica. Essas duas ideias são a porta de entrada para toda a harmonia modal que vem a seguir."),
        p (
            "Uma estrutura modal é um acorde ou um conjunto de acordes que faz o ouvido perceber um modo (dórico, lídio, mixolídio…). Já as tríades do meio são uma ferramenta prática: em vez de tocar sempre a mesma tríade da tônica, você constrói tríades sobre os graus internos e obtém um som mais rico, com movimento e cor, mesmo sobre um único acorde."),

        h ("O que é uma estrutura modal"),
        p (
            "Quando você toca um vamp sobre um único acorde, o ouvido não recebe uma cadência que diga “esta é a tonalidade”. Ele recebe um centro e uma cor. Essa cor é o modo. As estruturas modais são os acordes que reforçam essa cor sem criar a sensação de resolução da harmonia tonal."),
        b ("Vamp modal: um centro, uma cor, sem função dominante."),
        b ("A estrutura modal é o acorde que “voz” o modo."),
        b ("Sem trítono pedindo resolução, o som permanece suspenso."),
        c (
            "Este é o mesmo princípio que você viu nos empilhamentos quartais: a harmonia modal não resolve, ela permanece. É por isso que este módulo trabalha com vamps de um e dois acordes (nível 3)."),

        h ("Tríades do meio: o que são"),
        p (
            "Tríades do meio são tríades construídas sobre graus internos da escala, usadas como estruturas sobre um acorde maior ou menor. Em vez de tocar a tríade de Dó sobre Dó, você toca, por exemplo, a tríade de Sol sobre Dó, ou a tríade de Ré sobre Dó. Cada uma dessas tríades acrescenta notas que colorem o acorde sem mudar o centro."),
        tbl ({ "Tríade do meio", "Notas sobre Dó", "Graus acrescentados" }, {
            { "Sol maior", "Sol Si Ré", "5, 7, 9" },
            { "Ré menor", "Ré Fá Lá", "9, 11, 13" },
            { "Fá maior", "Fá Lá Dó", "11, 13, 1" },
            { "Lá menor", "Lá Dó Mi", "13, 1, 3" },
            { "Mi menor", "Mi Sol Si", "3, 5, 7" },
        }),
        p (
            "Repare como cada tríade do meio “esconde” o acorde de Dó dentro de si. A tríade de Sol maior (Sol–Si–Ré) contém a quinta, a sétima e a nona de Dó. Tocar Sol maior sobre um baixo em Dó produz um acorde de Dó com nona — um som mais rico que a tríade simples."),
        aud ({ "G3", "B3", "D4" }, "Tríade de Sol maior sobre Dó: um som que soa como Dó com nona (Cmaj9)."),
        img ("m7_triades_do_meio", "Tríades do meio: cada tríade interna colore o acorde de base."),

        h ("Tríades do meio sobre acordes maiores"),
        p (
            "Sobre um acorde maior, as tríades do meio mais úteis são as que produzem nona, sexta e sétima maior sem criar atrito. A tríade de Sol maior dá o Cmaj9; a de Lá menor dá a sexta (Lá) e a nona; a de Ré menor dá a nona e a décima primeira. São os voicings típicos do jazz e da bossa."),
        b ("Tríade de Sol sobre Dó = Dó com nona (Cmaj9)."),
        b ("Tríade de Lá menor sobre Dó = Dó com sexta (C6/9)."),
        b ("Tríade de Ré menor sobre Dó = Dó com nona e décima primeira."),
        aud ({ "C3", "G3", "B3", "D4" }, "Dó com a tríade de Sol por cima: Cmaj9, som moderno e cheio."),

        h ("Tríades do meio sobre acordes menores"),
        p (
            "Sobre acordes menores, as tríades do meio produzem as cores típicas do modo dórico e do menor com nona. A tríade de Sol menor sobre Dó menor dá a quinta, a sétima menor e a nona; a de Fá maior dá a décima primeira. São os voicings que dão o som “aberto” da música modal menor."),
        b ("Tríade de Sol menor sobre Dó menor = Cm9."),
        b ("Tríade de Fá maior sobre Dó menor = Cm11."),
        b ("Tríade de Sib maior sobre Dó menor = Cm7 com nona e sexta."),

        h ("Como construir no braço"),
        p (
            "Na guitarra, as tríades do meio são fáceis de tocar porque você já conhece as formas do CAGED. Para tocar a tríade de Sol sobre Dó, você usa a forma de Sol maior em qualquer região e simplesmente deixa o baixo (ou o contexto) afirmar Dó. O ouvido percebe o centro pelo baixo e a cor pela tríade de cima."),
        b ("Toque a tríade do meio nas cordas agudas."),
        b ("Deixe o baixo (ou o acorde de base) afirmar a tônica."),
        b ("O ouvido combina as duas informações: centro + cor."),
        img ("m7_triades_do_meio", "No braço, a tríade do meio é uma forma conhecida do CAGED tocada sobre o centro."),

        h ("Estruturas modais na prática"),
        p (
            "Para tocar um vamp modal, você escolhe um centro e um modo, e usa as estruturas que reforçam esse modo. Sobre um Dm7 (dórico), por exemplo, você pode tocar a tríade de Dó maior (que dá a sétima, a nona e a décima primeira) ou a de Sol menor (que dá a quinta, a sétima e a nona). Cada escolha muda a cor do vamp."),
        b ("Escolha o centro e o modo."),
        b ("Escolha as estruturas que reforçam esse modo."),
        b ("Toque o vamp e ouça a cor resultante."),
        aud ({ "D3", "F3", "A3", "C4" }, "Vamp em Dm7 (dórico): a cor modal do modo dórico."),
        c (
            "Nos exercícios deste tópico, você toca estruturas modais e tríades do meio; o app reconhece as notas e confere o conjunto. Toque em qualquer região do braço."),

        h ("A diferença entre estrutura modal e harmonia funcional"),
        p (
            "Na harmonia funcional (tonal), os acordes têm funções: tônica, subdominante, dominante. Eles conduzem a música para frente e pedem resolução. Na harmonia modal, os acordes são cores: eles não conduzem, eles permanecem. Entender essa diferença é fundamental para tocar música modal sem tentar “resolver” o que não deve ser resolvido."),
        tbl ({ "Aspecto", "Harmonia funcional", "Harmonia modal" }, {
            { "Função", "tônica, subdominante, dominante", "cor, centro" },
            { "Movimento", "conduz e resolve", "permanece" },
            { "Acorde típico", "tríades e tétrades", "quartais, sus, tríades do meio" },
            { "Exemplo", "II–V–I", "vamp de um acorde" },
        }),

        h ("Ampliação: as tríades do meio como método de estudo"),
        p (
            "Um método prático de estudar harmonia é pegar um acorde e tocar todas as tríades do meio sobre ele, uma por uma, ouvindo a cor que cada uma acrescenta. Esse exercício treina o ouvido e a mão ao mesmo tempo e revela por que certos voicings soam bem e outros, não. Com o tempo, você reconhece a cor antes de tocar."),
        b ("Toque cada tríade do meio sobre o mesmo baixo."),
        b ("Nomeie a cor que cada uma acrescenta."),
        b ("Escolha as que combinam com a intenção musical."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é tocar a tríade do meio sem afirmar o centro, o que faz o ouvido perder a referência de tônica. Outro é usar uma tríade do meio que cria atrito indesejado — como a que contém a décima primeira natural sobre um acorde maior. O estudo do modo de cada acorde resolve esses casos."),
        b ("Sempre afirme o centro com o baixo ou o acorde de base."),
        b ("Verifique se a tríade do meio cria atrito com o modo do acorde."),
        b ("Ouça antes de fixar o voicing."),

        h ("Estruturas modais e o baixo pedal"),
        p (
            "Uma técnica muito usada com estruturas modais é o baixo pedal: manter uma nota no baixo (a tônica) enquanto os acordes de cima se movem. Isso reforça o centro e permite usar tríades do meio e estruturas quartais sem perder a referência. O ouvido percebe a tônica no baixo e a cor nos acordes superiores."),
        b ("Baixo fixo na tônica: centro sempre claro."),
        b ("Acordes superiores: a cor modal."),
        b ("Excelente para vamps longos e introduções."),
        aud ({ "C3", "G3", "B3", "D4", "C3" }, "Baixo pedal em Dó com a tríade de Sol por cima: centro claro e cor modal."),

        h ("Tríades do meio e inversões"),
        p (
            "As tríades do meio podem ser tocadas em qualquer inversão, o que multiplica as possibilidades. Inverter uma tríade do meio muda a nota mais grave dela, e isso muda a forma como ela se encaixa no acorde de base. Experimentar as inversões é o que permite encontrar o voicing ideal para cada situação."),
        b ("Posição fundamental: tônica da tríade no baixo dela."),
        b ("Primeira e segunda inversões: cores diferentes."),
        b ("Experimente todas para achar o voicing que combina."),

        h ("Construindo estruturas modais próprias"),
        p (
            "Depois de conhecer as tríades do meio e as estruturas quartais, você pode construir as suas próprias estruturas modais. Basta escolher as notas que reforçam o modo que você quer e combiná-las. O princípio é sempre o mesmo: afirmar o centro com o baixo e colorir com as notas de cima."),
        b ("Escolha o centro (a tônica)."),
        b ("Escolha o modo (a cor)."),
        b ("Escolha as notas que reforçam essa cor."),
        c (
            "As estruturas modais são um território de criatividade. Não há uma regra única: você escolhe as notas pela cor que quer ouvir."),

        h ("Estruturas modais na composição"),
        p (
            "Compor com estruturas modais é uma forma de criar música que respira sem depender de cadências. Você escolhe um centro e uma cor e constrói a música em torno deles, usando estruturas que reforçam o modo. Isso dá um som moderno e aberto, muito valorizado em música instrumental e em trilhas."),
        b ("Escolha o centro e o modo da seção."),
        b ("Use estruturas que reforçam o modo."),
        b ("Evite cadências que quebram o clima modal."),

        h ("Estudando as tríades do meio sistematicamente"),
        p (
            "Um bom método de estudo é percorrer todas as tríades do meio sobre um único acorde de base, tocando cada uma e ouvindo a cor que ela acrescenta. Comece sobre um acorde maior (Cmaj7) e depois sobre um menor (Cm7). Esse exercício desenvolve o ouvido harmônico e a mão ao mesmo tempo."),
        b ("Sobre Cmaj7: toque as tríades de Sol, Lá menor e Ré menor."),
        b ("Sobre Cm7: toque as tríades de Sol menor e Fá maior."),
        b ("Nomeie a cor de cada tríade de memória."),

        h ("Do estudo à música"),
        p (
            "As estruturas modais e as tríades do meio só fazem sentido quando viram música. Por isso, pratique-as sempre sobre um vamp, tocando frases e ouvindo a cor. A repetição consciente transforma a teoria em vocabulário, e o vocabulário é o que permite criar música com intenção, em vez de apenas reproduzir exercícios."),
        b ("Pratique as estruturas sobre um vamp."),
        b ("Toque frases curtas e ouça a cor."),
        b ("Transforme o exercício em música."),

        h ("Resumo do tópico"),
        b ("Estruturas modais são acordes que reforçam um modo sem criar resolução."),
        b ("Tríades do meio são tríades construídas sobre graus internos da escala."),
        b ("Cada tríade do meio acrescenta tensões ao acorde de base."),
        b ("Na guitarra, elas reaproveitam as formas do CAGED."),
        b ("A harmonia modal permanece; a funcional resolve."),
        part ("m7_partitura_triade_meio", { "C3", "G3", "B3", "D4" },
              "Partitura: Dó com a tríade de Sol por cima (Cmaj9), uma estrutura modal. Ouça a cor."),
    };
}

} // namespace cursomusica::content
