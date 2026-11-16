#include "Course/Content/Topics.h"

// Topic 9C — Ciclos diminutos (Modulo 9, Etapa 9).
// Fonte de verdade do texto: docs/MUSIC.md (bloco C da Etapa 9).
namespace cursomusica::content
{

std::vector<ContentItem> topic9C()
{
    return {

        p (
            "Ciclo, em harmonia, é um caminho que volta ao ponto de partida depois de alguns passos. Você já conhece o ciclo das quintas, que percorre as doze tonalidades. O ciclo diminuto é o caminho das terças menores: ele percorre apenas quatro notas e volta ao início. Entender esse ciclo é entender por que o diminuto tem só três formas e por que ele serve a tantos acordes."),
        p (
            "Este tópico olha para o diminuto como um sistema, não apenas como um acorde. A ideia de ciclo explica a simetria, as substituições e as relações entre tonalidades distantes."),

        h ("O ciclo das terças menores"),
        p (
            "Comece em qualquer nota e suba de terça menor em terça menor. Partindo de Do: Do, Mib, Solb, Lá, e de volta a Do. São apenas quatro notas, e o ciclo se fecha. Isso acontece porque 12 semitons divididos por 3 dão exatamente 4. A oitava se divide em quatro terças menores iguais, sem sobra."),
        p (
            "E dessa divisão exata que nasce a simetria do diminuto. Como o ciclo se fecha em quatro notas, um acorde construído sobre qualquer uma delas tem as mesmas notas. Por isso Cdim7, Ebdim7, Gbdim7 e Adim7 são o mesmo som, com nomes diferentes."),
        tbl ({ "Passo", "Nota (partindo de Do)", "Distância acumulada" }, {
            { "1", "Do", "0 semitons" },
            { "2", "Mib", "3 semitons" },
            { "3", "Solb", "6 semitons" },
            { "4", "Lá", "9 semitons" },
            { "volta", "Do", "12 semitons" },
        }),
        img ("m9_ciclos_diminutos", "O ciclo das terças menores: quatro passos e o retorno a nota inicial."),
        aud ({ "C4", "D#4", "F#4", "A4", "C5" }, "O ciclo diminuto subindo de terça menor em terça menor."),

        h ("Por que existem apenas três diminutos"),
        p (
            "Como o ciclo se fecha em quatro notas, cada diminuto abrange quatro nomes. Se você começar o ciclo em outra nota que não seja nenhuma dessas quatro, cai num grupo novo. Existem apenas três grupos possíveis: os que começam em Do, em Do sustenido e em Re. Todos os outros dim7 do mundo caem em um desses três."),
        b ("Grupo 1: Cdim7 = Ebdim7 = Gbdim7 = Adim7."),
        b ("Grupo 2: C#dim7 = Edim7 = Gdim7 = Bbdim7."),
        b ("Grupo 3: Ddim7 = Fdim7 = Abdim7 = Bdim7."),
        c (
            "Consequência prática: existem apenas três digitações de dim7 no braço inteiro. Aprender as três e cobrir toda a música."),

        h ("O ciclo diminuto e a modulação"),
        p (
            "O ciclo das terças menores também é um mapa de modulação. Como cada dim7 serve a quatro tonalidades, ele é uma ponte entre campos harmônicos distantes. Tocar um dim7 comum a duas tonalidades é uma forma elegante de passar de uma para outra sem quebrar a coerência."),
        b ("Um dim7 comum a duas tonalidades liga os dois campos."),
        b ("O ciclo mostra quais tonalidades compartilham o mesmo diminuto."),
        b ("Use o ciclo para planejar modulações suaves."),
        aud ({ "C4", "D#4", "F#4", "A4" }, "Um dim7 comum: serve a quatro tonalidades ao mesmo tempo."),

        h ("O ciclo diminuto é a improvisação"),
        p (
            "Para quem improvisa, o ciclo das terças menores é um recurso de deslocamento. Como o padrão se repete de três em três casas, você pode mover uma frase de dim7 pelo braço e continuar dentro da mesma sonoridade. Isso permite criar sequências que sobem por terças menores e soam modernas, muito usadas na fusão e no jazz."),
        b ("Mova a frase de três em três casas: ela continua no mesmo dim7."),
        b ("Combine o ciclo com a escala diminuta para improvisar."),
        b ("Use o deslocamento para criar tensão crescente antes da resolução."),

        h ("Comparando o ciclo diminuto com o ciclo das quintas"),
        p (
            "O ciclo das quintas percorre as doze notas, uma a uma, e por isso descreve todas as tonalidades. O ciclo das terças menores percorre apenas quatro e descreve a simetria do diminuto. Os dois ciclos são complementares: um mostra o movimento gradual, o outro mostra a repetição exata. Entender os dois dá uma visão completa da harmonia."),
        tbl ({ "Ciclo", "Passo", "Quantas notas percorre", "O que descreve" }, {
            { "Das quintas", "7 semitons", "12", "todas as tonalidades" },
            { "Das terças menores", "3 semitons", "4", "a simetria do diminuto" },
            { "Dos tons", "2 semitons", "6", "a escala de tons inteiros" },
        }),
        c (
            "Sempre que uma distância divide a oitava de forma exata, aparece um ciclo curto: é o sinal da simetria."),

        h ("Usando o ciclo na prática"),
        p (
            "Comece tocando o ciclo diminuto lentamente, ouvindo cada terça menor. Depois, toque o mesmo dim7 em cada uma das quatro posições do ciclo e confirme que o som não muda. Por fim, use o ciclo para resolver em quatro tonalidades diferentes, uma após a outra, e ouvir como um mesmo acorde conduz a quatro lugares distintos."),
        b ("Toque o ciclo devagar, ouvindo cada terça menor."),
        b ("Confirme que o som não muda ao mudar a grafia do dim7."),
        b ("Resolva o mesmo dim7 em quatro tonalidades."),
        aud ({ "C4", "D#4", "F#4", "A4", "F4", "A4", "C5" },
             "O dim7 resolvendo em Fa: um dos quatro destinos possíveis do mesmo acorde."),

        h ("Erros comuns"),
        p (
            "O erro mais frequente é tratar cada grafia do dim7 como um acorde diferente, o que leva a decorar muito mais do que o necessário. Outro erro é tentar usar o ciclo sem ouvir a resolução, o que faz o acorde soar solto."),
        b ("Tratar Cdim7 e Ebdim7 como acordes distintos: são o mesmo som."),
        b ("Tocar o ciclo sem resolver: o diminuto só faz sentido quando conduz a algum lugar."),
        b ("Esquecer que existem apenas três grupos de dim7."),
        c (
            "Se você estiver tocando muitos dim7 diferentes, pare e verifique: provavelmente há repetição entre eles."),

        h ("O ciclo diminuto e a rearmonização"),
        p (
            "Além de modulação, o ciclo diminuto permite rearmonizar. Trocar um acorde por um dim7 do mesmo ciclo muda a cor sem mudar a função. Como o ciclo se fecha em quatro notas, você tem quatro opções de baixo para o mesmo acorde. Escolher qual usar depende da condução que você quer para o baixo e da nota que o acorde seguinte pede."),
        b ("Quatro opções de baixo para o mesmo dim7."),
        b ("A escolha depende da condução do baixo."),
        b ("Rearmonizar com o ciclo muda a cor, não a função."),

        h ("O ciclo diminuto no braço"),
        p (
            "No braço da guitarra, o ciclo das terças menores aparece como um deslocamento simples. Uma digitação de dim7 movida três casas para cima continua no mesmo acorde, apenas com outra nota no baixo. Isso faz do ciclo uma ferramenta visual: você ve o padrão se repetir e sabe que está no mesmo som."),
        b ("Desloque a forma de três em três casas."),
        b ("O acorde continua o mesmo; só muda a nota do baixo."),
        b ("O padrão visual ajuda a decorar o ciclo."),
        img ("m9_ciclos_diminutos", "O ciclo das terças menores é o mesmo desenho repetido no braço."),

        h ("O ciclo diminuto e os dominantes"),
        p (
            "Cada dim7 do ciclo corresponde a quatro dominantes com nona bemol. O ciclo mostra isso de forma direta: as quatro notas do dim7 são as terceiras maiores de quatro dominantes. Assim, ao aprender o ciclo, você aprende de uma vez as quatro dominantes que dividem a mesma escala diminuta."),
        b ("As quatro notas do dim7 são as terces maiores de quatro dominantes."),
        b ("Cada dominante resolve numa tônica diferente."),
        b ("O ciclo organiza os quatro dominantes de uma só vez."),
        aud ({ "C4", "D#4", "F#4", "A4", "C#4", "E4", "G4", "A#4" },
             "Dois dim7 do mesmo ciclo: as notas coincidem, a grafia muda."),

        h ("O ciclo diminuto e o ouvido"),
        p (
            "Ouvir o ciclo das terças menores é treinar o ouvido para uma das distâncias mais características da harmonia. Cada salto de terça menor tem uma cor própria: soa como um passo pequeno, mas cheio de intenção. Ao percorrer o ciclo completo, o aluno ouve quatro vezes a mesma distância e aprende a reconhecê-la de imediato."),
        b ("Cada salto do ciclo é uma terça menor."),
        b ("Percorrer o ciclo quatro vezes treina o ouvido na distância."),
        b ("Reconhecer a terça menor é reconhecer o ciclo."),
        aud ({ "C4", "D#4", "F#4", "A4", "C5" },
             "O ciclo das terças menores, subindo: a distância se repete quatro vezes."),

        h ("O ciclo diminuto e a harmonia funcional"),
        p (
            "Apesar de a simetria não ter uma tônica clara, o ciclo diminuto funciona dentro da harmonia tonal. Ele serve como movimento de passagem, como cor e como ponte entre acordes. O segredo é sempre ter um destino: o ciclo só faz sentido quando conduz a um acorde que resolve. Sem destino, ele soa solto."),
        b ("O ciclo funciona como movimento de passagem."),
        b ("Ele precisa de um destino para soar coerente."),
        b ("Sem resolução, o ciclo soa solto e sem direção."),

        h ("Comparando o ciclo diminuto com o ciclo dos tons"),
        p (
            "Assim como o ciclo das terças menores divide a oitava em quatro, o ciclo dos tons inteiros divide-a em seis. Os dois são simétricos e os dois se repetem. O ciclo dos tons percorre seis notas; o das terças menores, quatro. Comparar os dois ajuda a entender que cada distância que divide a oitava gera um ciclo próprio, com o seu número de formas."),
        tbl ({ "Ciclo", "Passo", "Notas percorridas", "Formas" }, {
            { "Das terças menores", "3 semitons", "4", "3" },
            { "Dos tons inteiros", "2 semitons", "6", "2" },
            { "Das terças maiores", "4 semitons", "3", "4" },
        }),
        c (
            "Todo passo que divide a oitava em partes iguais cria um ciclo curto. O número de formas é o número de passos que cabem na oitava."),

        h ("O ciclo diminuto na composição"),
        p (
            "Ao compor, o ciclo das terças menores oferece um caminho para criar movimento sem modulação. O compositor pode tocar um dim7 que serve a vários campos e, com isso, preparar uma passagem que ainda não revelou o seu destino. É uma forma elegante de criar suspense harmônico, muito usada em introduções e em interlúdios de música instrumental."),
        b ("Use o ciclo para criar movimento sem modulação."),
        b ("O dim7 prepara o destino sem revelá-lo."),
        b ("Recurso comum em introduções e interlúdios."),

        h ("Praticando o ciclo"),
        p (
            "Praticar o ciclo significa tocar o mesmo dim7 em cada uma das quatro posições e ouvir que o som não muda. Depois, significa resolver o mesmo acorde em quatro tônicas diferentes e ouvir como um único acorde conduz a quatro lugares. Por fim, significa improvisar sobre o ciclo, movendo frases de terça menor em terça menor."),
        b ("Toque o mesmo dim7 nas quatro posições do ciclo."),
        b ("Resolva o mesmo dim7 em quatro tônicas."),
        b ("Improvise movendo frases de terça menor em terça menor."),
        aud ({ "C4", "D#4", "F#4", "A4", "C5", "A4", "F#4", "D#4" },
             "O ciclo completo subindo e descendo: a mesma distância, quatro vezes."),

        h ("Resumo do tópico"),
        b ("O ciclo diminuto percorre quatro notas em terças menores."),
        b ("Existem apenas três dim7 diferentes no total."),
        b ("O ciclo é um mapa de modulação entre campos harmônicos."),
        b ("Na improvisação, o ciclo permite deslocar frases pelo braço."),
        b ("O ciclo das quintas é o das terças menores se complementam."),
        c (
            "Nos exercícios, toque o ciclo diminuto e o mesmo acorde em quatro posições. O app confere as classes de altura reconhecidas."),
    };
}

} // namespace cursomusica::content
