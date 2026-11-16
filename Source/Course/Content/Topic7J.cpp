#include "Course/Content/Topics.h"

// Topic 7J — Aplicações modais no rock e pop-rock (Módulo 7, Etapa 7).
// Fonte de verdade do texto: docs/MUSIC.md §7.2 (bloco J).
namespace cursomusica::content
{

std::vector<ContentItem> topic7J()
{
    return {

        p (
            "Este é o tópico de fechamento do módulo, e ele mostra por que tudo o que você estudou importa na música real. Os modos não são um exercício acadêmico: eles são a linguagem que sustenta uma enorme parte do rock, do pop-rock e da música instrumental. Quando você ouve um riff que “paira” sobre um acorde sem resolver, ou uma base que parece “suspensa”, muitas vezes está ouvindo harmonia modal."),
        p (
            "Aqui você aprende como os modos aparecem no rock e no pop-rock, quais são as aplicações típicas de cada um e como reconhecer a sonoridade modal nas músicas que você já conhece. O objetivo é levar a teoria para o contexto real, onde ela se torna ferramenta de composição e improvisação."),

        h ("Por que o rock ama os modos"),
        p (
            "O rock e o pop-rock usam muitos vamps de um ou dois acordes, em que a harmonia não conduz a uma resolução. Nesse contexto, a harmonia modal é natural: em vez de uma cadência, você tem um centro e uma cor. É por isso que os modos gregos são tão comuns no gênero — eles “vestem” exatamente esse tipo de harmonia estática."),
        b ("Vamps de um acorde: harmonia modal pura."),
        b ("Dois acordes: movimento modal interno."),
        b ("A cor vem do modo, não da cadência."),
        c (
            "Este é o nível 3 do curso (II–V–I, mas com foco na cor modal). Você vai aplicar os modos em progressões curtas, que é o que o rock e o pop-rock fazem o tempo todo."),

        h ("Mixolídio no rock"),
        p (
            "O mixolídio é provavelmente o modo mais usado no rock. Ele combina com acordes dominantes (X7) e dá aquele som que você ouve em riffs e vamps de um acorde. A b7 (sétima menor) é o que cria a tensão característica do gênero, sem a resolução “clássica” do dominante."),
        b ("Vamps de um acorde dominante (X7)."),
        b ("Riffs que não resolvem."),
        b ("Solos sobre bases estáticas."),
        aud ({ "C4", "D4", "E4", "F4", "G4", "A4", "A#4", "C5" }, "Mixolídio em Dó: o som dominante do rock, com a sétima menor (Sib)."),
        img ("m7_aplicacoes_rock", "Aplicações modais no rock: cada modo, um tipo de vamp e de cor."),

        h ("Dórico no rock e no pop"),
        p (
            "O dórico dá ao rock um som menor “aberto”, menos melancólico que o menor natural. Ele aparece em riffs menores que não soam tristes, mas sim cheios de energia. A sexta maior (6) é a nota que faz a diferença — é ela que dá o caráter do dórico."),
        b ("Riffs menores com energia."),
        b ("Vamps em Xm7."),
        b ("Solos que combinam menor com movimento."),
        aud ({ "C4", "D4", "D#4", "F4", "G4", "A4", "A#4", "C5" }, "Dórico em Dó: menor com a sexta maior (Lá). Menor cheio de energia."),

        h ("Lídio no rock progressivo e na música instrumental"),
        p (
            "O lídio é o modo do “brilho”. Ele aparece em rock progressivo, música instrumental e passagens que buscam um som etéreo, flutuante. A #4 (quarta aumentada) é a nota que dá esse caráter. É um modo menos comum no pop, mas muito valorizado na música instrumental e no prog."),
        b ("Rock progressivo e música instrumental."),
        b ("Passagens etéreas e flutuantes."),
        b ("Acordes com #11."),
        aud ({ "C4", "D4", "E4", "F#4", "G4", "A4", "B4", "C5" }, "Lídio em Dó: maior com a quarta aumentada (Fá#). Som brilhante e etéreo."),

        h ("A pentatônica e os modos"),
        p (
            "Muitos solos de rock usam a pentatônica, e é importante entender a relação entre ela e os modos. A pentatônica menor é uma “simplificação” dos modos menores (dórico, eólio): ela usa as notas mais estáveis, sem as tensões. Sobre uma base modal, a pentatônica continua funcionando porque as suas notas estão contidas nos modos menores."),
        b ("Pentatônica menor: contida no dórico e no eólio."),
        b ("Pentatônica maior: contida no jônio, lídio e mixolídio."),
        b ("A pentatônica é um bom ponto de partida; os modos acrescentam cor."),
        aud ({ "C4", "D#4", "F4", "G4", "A#4", "C5" }, "Pentatônica menor em Dó: as notas estáveis do menor, contidas nos modos menores."),

        h ("Aplicações por modo: resumo prático"),
        p (
            "A tabela abaixo resume as aplicações típicas de cada modo no rock e no pop-rock. Use-a como referência quando for compor ou improvisar: escolha o modo pela cor que a música pede e pelo acorde que está na base."),
        tbl ({ "Modo", "Acorde típico", "Aplicação" }, {
            { "jônio", "Xmaj7", "pop, baladas, música maior tradicional" },
            { "dórico", "Xm7", "rock e pop menores com energia" },
            { "frígio", "Xm7 (b2)", "metal, flamenco, som espanhol" },
            { "lídio", "Xmaj7#11", "prog, instrumental, passagens etéreas" },
            { "mixolídio", "X7", "rock, blues-rock, vamps de dominante" },
            { "eólio", "Xm7", "rock e metal menores, som melancólico" },
            { "lócrio 9", "Xm7b5", "II grau de II–V–I menor" },
        }),

        tbl ({ "Se você ouve...", "Provavelmente é...", "Modo típico" }, {
            { "vamp de um acorde sem cadência", "harmonia modal", "qualquer modo do centro" },
            { "acorde sus que não resolve", "cor suspensa", "mixolídio sus" },
            { "riff menor com energia", "menor aberto", "dórico" },
            { "passagem etérea e brilhante", "som flutuante", "lídio" },
            { "base de dominante que não resolve", "dominante estático", "mixolídio" },
            { "passagem espanhola", "menor com b2", "frígio" },
        }),

        h ("Reconhecendo o modal nas músicas que você ouve"),
        p (
            "Uma boa forma de consolidar o estudo é ouvir música e identificar a harmonia modal. Quando um trecho não tem uma cadência clara, mas tem um centro e uma cor, provavelmente é modal. Procure vamps de um acorde, bases estáticas e passagens que “não resolvem”. Anotar o que você ouve é o melhor exercício de percepção."),
        b ("Vamp de um acorde: provavelmente modal."),
        b ("Acorde sus sem resolução: cor modal."),
        b ("Riff que se repete sobre um centro: modal."),
        c (
            "Nos exercícios deste tópico, você toca vamps modais e o app reconhece as notas. Você também responderá a questionários sobre as aplicações de cada modo no rock e no pop-rock."),

        h ("Compondo com modos"),
        p (
            "Ao compor, você pode escolher o modo pela cor que quer. Uma introdução brilhante pede o lídio; um verso com energia pede o dórico; um refrão com tensão pede o mixolídio; uma passagem sombria pede o frígio ou o eólio. Compor com modos é pintar com a paleta que você estudou neste módulo."),
        b ("Escolha o modo pela emoção que quer transmitir."),
        b ("Use as tríades do meio para construir os voicings."),
        b ("Mantenha o centro claro para o ouvido não se perder."),
        aud ({ "C4", "D4", "D#4", "F4", "G4", "A4", "A#4", "C5" }, "Vamp modal em Dó dórico: o som do rock menor com energia."),

        h ("Improvisando sobre vamps modais"),
        p (
            "Sobre um vamp modal, a improvisação é diferente da improvisação sobre uma progressão funcional. Em vez de “seguir” os acordes, você “habita” o modo: explora a cor, as notas de repouso e as tensões, sem a pressão de resolver. É um espaço de liberdade, e dominá-lo é o objetivo final deste módulo."),
        b ("Habite o modo: explore as notas de repouso e as tensões."),
        b ("Use frases curtas e repetição para criar identidade."),
        b ("Não tente resolver o que é modal."),
        img ("m7_aplicacoes_rock", "Improvisar sobre um vamp modal: habitar a cor em vez de seguir acordes."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é tentar “resolver” um vamp modal como se fosse uma cadência funcional. Outro é escolher um modo que não combina com o acorde (por exemplo, mixolídio sobre um acorde menor). Ouvir o acorde e a intenção musical evita os dois."),
        b ("Não resolva o que é modal."),
        b ("Combine o modo com o acorde de base."),
        b ("Ouça antes de decidir."),

        h ("Frígio e eólio no rock e no metal"),
        p (
            "Além dos três modos principais, o frígio e o eólio também aparecem muito no rock e no metal. O frígio (menor com segunda menor) dá o sabor espanhol e é comum no metal e no flamenco; o eólio (menor natural) é o som melancólico clássico do rock e do metal. Reconhecer esses dois modos amplia o seu vocabulário."),
        b ("Frígio: som espanhol, comum no metal e no flamenco."),
        b ("Eólio: menor natural, som melancólico do rock e do metal."),
        b ("A segunda menor (frígio) é a nota característica do modo."),
        aud ({ "C4", "C#4", "D#4", "F4", "G4", "G#4", "A#4" }, "Frígio em Dó: menor com segunda menor (Réb). Som espanhol."),

        h ("Os modos e o riff de guitarra"),
        p (
            "Muitos riffs de guitarra são, na prática, modos tocados em uma região do braço. Um riff que usa a escala menor com a sexta maior está usando o dórico; um riff com a sétima menor e a terça maior está usando o mixolídio. Reconhecer o modo por trás do riff ajuda a improvisar sobre ele sem sair da cor."),
        b ("Riff menor com sexta maior: dórico."),
        b ("Riff maior com sétima menor: mixolídio."),
        b ("Riff menor natural: eólio."),
        img ("m7_aplicacoes_rock", "Os riffs de guitarra como modos tocados no braço: identifique a cor pelo riff."),

        h ("Modos e a progressão de dois acordes"),
        p (
            "Uma progressão de dois acordes é o laboratório perfeito para a harmonia modal. Você pode tocar o mesmo modo sobre os dois acordes (se eles pertencem ao mesmo campo modal) ou trocar de modo quando o centro muda. No nível 3, esse é o tipo de progressão que o módulo usa para ensinar a cor modal."),
        b ("Dois acordes do mesmo campo: um modo só."),
        b ("Dois centros diferentes: troque o modo."),
        b ("O ouvido percebe a cor e o movimento."),
        aud ({ "C4", "D4", "D#4", "F4", "G4", "A4", "A#4", "C5" }, "Vamp de dois acordes em Dó dórico: a cor modal em movimento."),

        h ("Transcrevendo e reconhecendo o modal"),
        p (
            "Uma excelente forma de consolidar o estudo é transcrever trechos de músicas que você gosta e identificar o modo usado. Comece por vamps de um acorde e por passagens que não resolvem. Anotar o modo e a cor é o melhor exercício de percepção modal, e ele conecta a teoria com a música real."),
        b ("Transcreva um vamp de um acorde e identifique o modo."),
        b ("Anote a cor que o modo produz."),
        b ("Compare com outros modos que você conhece."),

        h ("Do modal ao funcional"),
        p (
            "A harmonia modal que você estudou neste módulo é a base para a harmonia funcional que vem a seguir. Depois de entender os modos e as cores, você vai aprender a combiná-los em cadências (II–V–I, dominantes secundários, substituições) e a criar movimento harmônico. O modal é o vocabulário; o funcional é a sintaxe."),
        b ("Modal: um centro, uma cor, sem resolução."),
        b ("Funcional: funções que conduzem e resolvem."),
        b ("O domínio do modal prepara o funcional."),
        c (
            "Com este tópico, você fecha a Etapa 7 e está pronto para a harmonia funcional dos próximos módulos."),

        h ("Um roteiro para aplicar os modos"),
        p (
            "Um roteiro prático para aplicar os modos no rock e no pop-rock é começar pelos vamps de um acorde. Escolha um centro, defina o modo pela cor que quer e toque um vamp, improvisando frases curtas. Depois, acrescente um segundo acorde e observe como a cor muda quando o centro se move. Com o tempo, você constrói um repertório de vamps modais que serve de base para compor e improvisar."),
        b ("Comece com vamps de um acorde."),
        b ("Acrescente um segundo acorde e observe a cor."),
        b ("Construa um repertório de vamps modais."),

        h ("Fechando a Etapa 7"),
        p (
            "Com este tópico, você conclui a Etapa 7. Você conhece os empilhamentos além das tríades e tétrades, as estruturas modais, as tríades do meio, os modos principais e as suas variações, e sabe aplicá-los no rock e no pop-rock. Esse conjunto é a base para a harmonia funcional, as substituições e a reharmonização que vêm nos próximos módulos."),
        b ("Empilhamentos: terças, quartas, quintas, segundas e mistos."),
        b ("Estruturas modais e tríades do meio."),
        b ("Modos: dórico, lídio, mixolídio e as suas variações."),
        b ("Tensões: sus, #4, lócrio 9 e alterado."),
        b ("Aplicação: vamps modais no rock e no pop-rock."),
        part ("m7_partitura_vamp_modal", { "C4", "D4", "D#4", "F4", "G4", "A4", "A#4", "C5" },
              "Partitura: vamp modal em Dó dórico, o som do rock menor. Ouça a cor do modo."),
    };
}

} // namespace cursomusica::content
