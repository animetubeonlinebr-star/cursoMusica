#include "Course/Content/Topics.h"

// Topic 5D — Função subdominante (Módulo 5, Etapa 5).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 5, bloco D).
namespace cursomusica::content
{

std::vector<ContentItem> topic5D()
{
    return {

        p (
            "Se a tônica é o repouso, a subdominante é o afastamento. A função subdominante cria a sensação de que a música saiu de casa: há movimento, há direção, mas ainda não há a tensão forte do dominante. É a função que prepara o terreno, que dá um passo para o lado antes de a música pedir a resolução."),
        p (
            "Entender a subdominante é entender o 'meio do caminho'. Muitas progressões vão da tônica direto para o dominante, mas as mais ricas passam pela subdominante — porque é ela que cria o movimento interno que faz a música parecer que está contando uma história, e não apenas pulando de repouso em repouso."),

        h ("O que é a função subdominante"),
        p (
            "Função subdominante é a função de afastamento da tônica. Ela é exercida pelo acorde de grau IV — em Dó maior, o acorde de F. Quando a música chega ao IV, o ouvido percebe que saiu do repouso, mas ainda não sente a tensão aguda do dominante. É um estado intermediário, de movimento, que pede continuação."),
        p (
            "A subdominante é o primeiro passo de um caminho muito comum: I → IV → V → I. Nesse caminho, o IV prepara o V, e o V prepara a volta ao I. Cada acorde tem um papel, e a subdominante é aquele que abre a porta para o afastamento antes de a música começar a pedir a volta."),
        b ("Função subdominante = afastamento, movimento, preparação."),
        b ("Exercida pelo acorde de grau IV (F, em Dó maior)."),
        b ("Soa como saída de casa, ainda sem a tensão do dominante."),
        img ("m5_campo_harmonico_maior", "No campo harmônico, o grau IV (subdominante) é o passo de afastamento entre o repouso e a tensão."),

        h ("A subdominante no campo harmônico"),
        p (
            "Assim como a tônica tem substitutos, a subdominante também tem. Além do grau IV, o grau ii exerce função subdominante — em Dó maior, o acorde de Dm. Ele compartilha notas com o F e pode substituí-lo, criando uma sensação de afastamento ainda mais suave e preparada."),
        p (
            "Essa é a razão pela qual a progressão ii – V – I é tão comum: o ii faz o papel de subdominante, o V faz o papel de dominante e o I fecha como tônica. As três funções aparecem em sequência, cada uma preparando a próxima, o que cria a sensação de um ciclo completo e satisfatório."),
        tbl ({ "Grau", "Acorde (Dó maior)", "Relação com a subdominante", "Cor" }, {
            { "IV", "F", "subdominante principal", "afastamento claro" },
            { "ii", "Dm", "substituto (2 notas em comum)", "afastamento suave" },
        }),
        c (
            "O ii é o substituto mais usado da subdominante. Em ii – V – I, ele prepara o dominante com mais movimento do que o IV faria sozinho."),
        aud ({ "F4", "A4", "C5", "D4", "F4", "A4" },
             "Subdominante e seu substituto em Dó: F (IV) e Dm (ii) — os dois afastam, com cores diferentes."),

        h ("Como a subdominante soa"),
        p (
            "O ouvido reconhece a subdominante pela sensação de movimento sem tensão. É como dar um passo para o lado: você saiu do lugar de repouso, mas ainda não está desconfortável. Comparada à tônica, a subdominante soa mais 'aberta'; comparada ao dominante, soa mais calma."),
        p (
            "Uma forma simples de perceber isso é tocar I → IV e depois I → V. O primeiro movimento parece um desvio tranquilo; o segundo já parece um empurrão em direção à resolução. Essa diferença de sensação é o que distingue as funções — e é ela que você vai aprender a ouvir nos exercícios."),
        b ("A subdominante soa como movimento, sem tensão forte."),
        b ("I → IV parece um desvio; I → V parece um empurrão."),
        b ("O ouvido espera continuação depois da subdominante."),
        aud ({ "C4", "E4", "G4", "F4", "A4", "C5" },
             "Tônica (C) indo para subdominante (F): um passo para o lado, ainda tranquilo."),

        h ("A subdominante na preparação do dominante"),
        p (
            "A principal função da subdominante é preparar o dominante. Quando a música passa pelo IV (ou pelo ii) antes de chegar ao V, a chegada ao dominante soa muito mais natural, porque houve um caminho construído. Sem a subdominante, o salto da tônica direto para o dominante pode soar abrupto."),
        p (
            "Por isso os compositores usam tanto a sequência I – IV – V – I ou ii – V – I. A subdominante é o 'preparador' do dominante: ela aquece o ouvido, cria expectativa e faz com que a tensão do dominante pareça inevitável, e não aleatória. É esse encadeamento que dá às progressões a sensação de lógica."),
        b ("Subdominante → dominante é um encadeamento natural."),
        b ("A subdominante prepara e suaviza a chegada ao dominante."),
        b ("I – IV – V – I é a forma mais básica de usar as três funções."),
        part ("m5_partitura_iv_v_i", { "F4", "A4", "C5", "G4", "B4", "D5", "C5", "E5", "G5" },
              "Partitura de IV – V – I em Dó: subdominante prepara o dominante, que resolve na tônica."),

        h ("Subdominante maior e menor"),
        p (
            "Na tonalidade maior, a subdominante principal é maior (F). Mas existe um recurso expressivo muito usado: a subdominante menor, que aparece quando se empresta o acorde de IV menor da tonalidade menor paralela. Em Dó maior, isso seria o acorde de Fm — que soa mais melancólico e é muito comum em músicas pop e MPB."),
        p (
            "Esse é um exemplo de como as funções podem ser coloridas sem perder o papel. A subdominante continua sendo a função de afastamento, mas a sua qualidade (maior ou menor) muda completamente a emoção. Guarde essa ideia: a função é o papel; a qualidade é a cor."),
        b ("Subdominante maior (F): afastamento claro e aberto."),
        b ("Subdominante menor (Fm): afastamento melancólico, emprestado do menor."),
        b ("A função permanece; a emoção muda com a qualidade."),
        aud ({ "F4", "Ab4", "C5" }, "Subdominante menor (Fm): o mesmo afastamento, agora com cor melancólica."),

        h ("A subdominante na guitarra"),
        p (
            "No braço, a subdominante está a uma quinta acima da tônica (ou a uma quarta abaixo, dependendo de como você conta). Em Dó maior, o F está na 6ª corda, casa 1, ou na 5ª corda, casa 8. Localizar a subdominante a partir da tônica é um dos gestos mais úteis do acompanhamento, porque é ela que abre o movimento das progressões."),
        p (
            "Os exercícios deste tópico pedem que você toque a tríade de subdominante e seu substituto, e o app confere as notas. Isso confirma que você está tocando o acorde certo do campo, com a qualidade certa — e não uma forma vizinha que pertence a outro grau."),
        b ("A subdominante fica a uma quinta acima da tônica."),
        b ("Monte a tríade (fundamental, terça, quinta) sobre o grau IV."),
        b ("Confirme no app se as notas formam o acorde de IV ou de ii."),

        h ("Subdominante e movimento interno"),
        p (
            "Uma das funções mais interessantes da subdominante é criar movimento interno na música. Quando a música passa pelo IV antes de chegar ao V, ela ganha uma sensação de deslocamento que a tônica sozinha não teria. É esse deslocamento que faz a música parecer que está contando uma história, com idas e voltas, em vez de apenas repetir o mesmo ponto."),
        p (
            "Esse movimento é especialmente importante em músicas mais lentas ou em baladas, onde a harmonia precisa criar o interesse que o ritmo não cria. Nesses casos, a subdominante é quem dá o primeiro passo para fora do repouso, criando a expectativa que o dominante vai resolver. Sem ela, a música pode soar estática."),
        b ("A subdominante cria movimento interno na harmonia."),
        b ("Ela dá o primeiro passo para fora do repouso."),
        b ("É especialmente útil em músicas lentas, onde a harmonia carrega o interesse."),

        h ("Exercícios para ouvir a subdominante"),
        p (
            "Para treinar o ouvido, toque a tônica e depois a subdominante, e repare na sensação de 'saída de casa'. Depois toque a tônica e o dominante, e repare na diferença: o dominante soa mais tenso. Alternar entre esses dois movimentos é a forma mais direta de aprender a distinguir a subdominante do dominante pelo ouvido."),
        p (
            "Outro exercício é tocar uma progressão e parar no IV. O ouvido não sente que a música terminou nem que está em tensão máxima — sente que ela está no meio do caminho. Essa sensação intermediária é a marca da subdominante, e reconhecê-la é o que permite escolher, na hora de acompanhar, entre o afastamento suave e a tensão do dominante."),
        b ("Compare I → IV (saída tranquila) com I → V (empurrão)."),
        b ("Pare no IV e note a sensação de meio do caminho."),
        b ("Reconhecer a subdominante ajuda a escolher o acorde certo."),
        aud ({ "C4", "E4", "G4", "F4", "A4", "C5", "G4", "B4", "D5" },
             "Tônica → subdominante → dominante: da saída tranquila à tensão que pede a volta."),

        h ("Subdominante e repertório"),
        p (
            "A subdominante aparece em praticamente todo repertório. Na música popular brasileira, a passagem pelo IV é quase obrigatória antes do V, e é ela que dá à harmonia o seu caráter de 'conversa'. Ouvir uma música com atenção e identificar onde está a subdominante é um exercício que vale a pena em qualquer estilo, do samba ao rock."),
        p (
            "Quando você começa a ouvir as funções em vez de apenas os acordes, o repertório fica muito mais fácil de acompanhar. Você deixa de tentar decorar sequências e passa a prever o próximo acorde pela função que ele cumpre. A subdominante é, muitas vezes, o acorde que 'anuncia' a chegada do dominante — e reconhecê-la é antecipar a harmonia."),
        b ("A subdominante está presente em quase todo repertório."),
        b ("Ouvir a função ajuda a prever o próximo acorde."),
        b ("Identificar o IV é antecipar a harmonia da música."),

        h ("Subdominante e a escala"),
        p (
            "A função subdominante está ligada diretamente à escala maior. O acorde de IV é construído sobre o quarto grau, e a sua tríade contém a fundamental, a terça e a quinta daquele grau. Em Dó maior, o IV é Fá maior (Fá–Lá–Dó). Repare que todas essas notas pertencem à escala de Dó maior — a subdominante não introduz nenhuma nota nova."),
        p (
            "Essa observação vale para todos os acordes do campo: nenhum deles usa notas de fora da escala. É justamente isso que faz o campo harmônico ser coerente. A subdominante, como os outros acordes, é apenas uma reorganização das mesmas sete notas, tomando o quarto grau como fundamental."),
        b ("O acorde de IV é a tríade construída sobre o quarto grau."),
        b ("Todas as suas notas pertencem à escala maior."),
        b ("Nenhum acorde do campo usa notas de fora da escala."),

        h ("Subdominante em diferentes tonalidades"),
        p (
            "Como o padrão é sempre o mesmo, a subdominante de qualquer tonalidade está a uma quinta acima da tônica. Em Sol maior, o IV é Dó maior; em Fá maior, o IV é Si bemol maior; em Ré maior, o IV é Sol maior. Saber isso permite achar a subdominante de qualquer tom rapidamente, sem precisar montar o campo harmônico inteiro."),
        p (
            "Esse é um exemplo prático de como os graus facilitam a vida do músico. Em vez de memorizar 'em Dó é F, em Sol é C, em Fá é Bb', você memoriza apenas 'a subdominante é o IV'. A regra é uma só, e vale para todos os tons — o que economiza muita memorização e reduz a chance de erro."),
        b ("A subdominante é sempre o grau IV da tonalidade."),
        b ("Em Sol maior é C; em Fá maior é Bb; em Ré maior é G."),
        b ("A regra do grau substitui a memorização de cada tom."),
        tbl ({ "Tonalidade", "Tônica (I)", "Subdominante (IV)" }, {
            { "Dó maior", "C", "F" },
            { "Sol maior", "G", "C" },
            { "Fá maior", "F", "Bb" },
            { "Ré maior", "D", "G" },
            { "Sib maior", "Bb", "Eb" },
        }),

        h ("Resumo do tópico"),
        b ("Função subdominante é a função de afastamento da tônica."),
        b ("É exercida pelo grau IV e pelo substituto ii."),
        b ("Soa como movimento, sem a tensão forte do dominante."),
        b ("Sua principal tarefa é preparar o dominante."),
        b ("Pode ser maior ou menor, mudando a cor sem perder a função."),
        c (
            "Nos exercícios deste tópico, toque a tríade de subdominante e seu substituto. O app reconhece as notas e confere se o acorde de afastamento está sendo executado corretamente."),
    };
}

} // namespace cursomusica::content
