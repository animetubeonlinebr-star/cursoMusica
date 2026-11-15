#include "Course/Content/Topics.h"

// Topic 5C — Função tônica (Módulo 5, Etapa 5).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 5, bloco C).
namespace cursomusica::content
{

std::vector<ContentItem> topic5C()
{
    return {

        p (
            "As funções harmônicas são o que dá sentido à progressão. Um acorde isolado é só um som; dentro de uma tonalidade, cada acorde cumpre um papel que empurra a música para frente ou a faz repousar. A primeira e mais importante dessas funções é a tônica: ela é o ponto de repouso, o 'lar' para onde a música quer voltar."),
        p (
            "Neste tópico você aprende a reconhecer a função tônica pelo som, a localizá-la no campo harmônico e a usá-la para criar sensação de estabilidade. É a função que você vai ouvir no fim de quase toda música, porque é ela que fecha a frase e dá a sensação de que a música 'terminou'."),

        h ("O que é a função tônica"),
        p (
            "Função tônica é a função de repouso da tonalidade. Ela é exercida pelo acorde construído sobre o primeiro grau da escala — o acorde de I. Quando a música está na tônica, ela soa estável, resolvida, como se estivesse 'em casa'. É o acorde em que a música começa e, na maioria das vezes, o acorde em que ela termina."),
        p (
            "Em Dó maior, a tônica é o acorde de C. Tocar C depois de uma sequência de acordes tensos produz uma sensação imediata de alívio: a tensão acumulada se resolve no repouso. Essa sensação de 'chegada' é a marca auditiva da função tônica, e reconhecê-la de ouvido é o primeiro passo para entender a harmonia funcional."),
        b ("Função tônica = repouso, estabilidade, sensação de 'lar'."),
        b ("Exercida pelo acorde de grau I (C, em Dó maior)."),
        b ("É onde a música começa e normalmente onde termina."),
        img ("m5_funcoes_tres", "As três funções harmônicas: tônica (repouso), subdominante (afastamento) e dominante (tensão)."),

        h ("A tônica no campo harmônico"),
        p (
            "No campo harmônico maior, a função tônica não é exercida só pelo acorde de I. Os acordes de iii e vi também são considerados de função tônica, porque compartilham notas com o I e podem substituí-lo sem mudar a sensação de repouso. São os chamados substitutos da tônica."),
        p (
            "Isso significa que, quando a música está 'em casa', ela pode usar C, Em ou Am para expressar esse repouso — cada um com uma cor ligeiramente diferente. O C é o repouso mais puro; o Am traz um repouso mais melancólico; o Em, um repouso mais suspenso. Mas todos mantêm a função de estabilidade."),
        tbl ({ "Grau", "Acorde (Dó maior)", "Relação com a tônica", "Cor" }, {
            { "I", "C", "tônica principal", "repouso claro" },
            { "iii", "Em", "substituto (2 notas em comum)", "repouso suspenso" },
            { "vi", "Am", "substituto (2 notas em comum)", "repouso melancólico" },
        }),
        c (
            "Os substitutos da tônica são usados para colorir o repouso sem sair dele. Trocar C por Am numa progressão mantém a sensação de estabilidade, mas muda a emoção."),
        aud ({ "C4", "E4", "G4", "A3", "C4", "E4", "E3", "G3", "B3" },
             "Tônica e seus substitutos em Dó: C (I), Am (vi) e Em (iii) — os três repousam, com cores diferentes."),

        h ("Como a tônica soa"),
        p (
            "O ouvido reconhece a tônica pela sensação de repouso. Quando uma frase musical termina no acorde de I, o ouvido 'assente': parece que a música disse tudo o que tinha de dizer. Quando a frase termina em outro acorde, o ouvido fica esperando algo — essa expectativa é justamente a tensão que as outras funções criam."),
        p (
            "Treinar esse reconhecimento é simples: toque uma progressão que saia da tônica e volte para ela, e repare no alívio da volta. Depois tente cantar a tônica antes de tocar. Com o tempo, você passa a saber instintivamente quando a música está 'em casa' e quando está pedindo resolução."),
        b ("A tônica soa estável e conclusiva."),
        b ("Voltar à tônica depois de uma tensão produz alívio audível."),
        b ("Cantar a tônica antes de tocar desenvolve o reconhecimento."),
        aud ({ "G4", "B4", "D5", "C5", "E5", "G5" },
             "Dominante (G) resolvendo na tônica (C): o ouvido sente a chegada em casa."),

        h ("A tônica e a sensação de conclusão"),
        p (
            "Toda música precisa de um ponto de chegada. A função tônica é o recurso que cria esse ponto. Uma progressão que nunca toca a tônica soa como uma pergunta sem resposta; uma progressão que termina na tônica soa como uma resposta. Por isso a tônica é tão presente no fim de frases, seções e músicas inteiras."),
        p (
            "É importante notar que a tônica não precisa ser o primeiro acorde nem aparecer o tempo todo. Ela pode chegar só no fim, depois de um longo caminho de tensão. Quanto mais tempo a música demora para voltar à tônica, maior a sensação de resolução quando finalmente chega. Esse controle do tempo de retorno é uma das ferramentas mais expressivas da harmonia."),
        b ("A tônica é o ponto de chegada da frase harmônica."),
        b ("Atrasar a volta à tônica aumenta a tensão e a resolução final."),
        b ("Terminar fora da tônica deixa a música em aberto, pedindo continuação."),

        h ("A tônica na guitarra"),
        p (
            "No braço, o acorde de tônica é a sua âncora. Você localiza a fundamental na 6ª ou na 5ª corda e monta a tríade. Como a tônica é o centro da tonalidade, todos os outros acordes do campo são encontrados a partir dela, contando os graus. Saber onde está a tônica em cada região do braço é o que permite transpor uma progressão para qualquer tom."),
        p (
            "Nos exercícios deste tópico, você toca o acorde de tônica e seus substitutos, e o app confere as notas reconhecidas. Isso confirma que você está tocando a tríade correta do grau I — e não uma forma parecida que pertence a outra função."),
        b ("Localize a fundamental da tônica na 6ª ou 5ª corda."),
        b ("Monte a tríade (fundamental, terça, quinta) sobre essa nota."),
        b ("Confirme no app se as notas formam o acorde de I."),
        part ("m5_partitura_triade_tonica", { "C4", "E4", "G4" },
              "Partitura da tríade de tônica (Dó maior): fundamental, terça e quinta. Ouça o som de repouso."),

        h ("Tônica maior e tônica menor"),
        p (
            "A função tônica existe também nas tonalidades menores, mas com uma cor diferente. Em Lá menor, a tônica é Am, e o repouso soa mais melancólico. Este módulo trata do campo harmônico maior, mas vale saber que a mesma lógica de funções se aplica ao menor — o que muda é a qualidade do acorde de repouso."),
        p (
            "Reconhecer que a tônica pode ser maior ou menor é importante para não confundir tonalidade com função. A função tônica é sempre 'repouso'; a qualidade (maior ou menor) é o tempero desse repouso. Duas músicas com a mesma progressão funcional podem soar completamente diferentes só por causa da qualidade da tônica."),
        b ("Tônica maior: repouso claro e afirmativo (C)."),
        b ("Tônica menor: repouso melancólico e introspectivo (Am)."),
        b ("A função é a mesma; a qualidade muda a emoção."),
        aud ({ "A3", "C4", "E4" }, "Tríade de Lá menor: o mesmo repouso, agora com cor menor."),

        h ("Tônica e centro tonal"),
        p (
            "A função tônica é o que estabelece o centro tonal de uma música. Quando o ouvido reconhece a tônica, ele automaticamente passa a medir todas as outras notas e acordes em relação a ela. Essa é a razão pela qual a mesma melodia pode soar diferente em tons diferentes: o que muda não são as distâncias relativas, mas o centro de referência."),
        p (
            "Na prática, a tônica é o 'ímã' da música. Tudo o que acontece na harmonia é um afastamento ou um retorno a esse centro. Quanto mais tempo a música fica longe da tônica, mais forte é a sensação de resolução quando ela volta. Controlar esse tempo de afastamento é uma das ferramentas mais poderosas de quem escreve ou improvisa."),
        b ("A tônica estabelece o centro tonal da música."),
        b ("Todas as notas e acordes são medidos em relação a ela."),
        b ("O afastamento e o retorno à tônica criam a tensão e a resolução."),

        h ("Exercícios para ouvir a tônica"),
        p (
            "Treinar o ouvido para reconhecer a tônica é mais fácil do que parece. Toque uma progressão que termine na tônica e repare na sensação de 'acabou'. Depois toque a mesma progressão parando um acorde antes do fim — o ouvido vai ficar incomodado. Essa diferença entre 'terminou' e 'falta algo' é o reconhecimento da função tônica em ação."),
        p (
            "Outro exercício útil é cantar a tônica depois de ouvir uma progressão. Feche os olhos, ouça uma sequência de acordes e tente cantar a nota para onde a música quer ir. Com a prática, você acerta quase sempre — e isso é a prova de que o seu ouvido já reconhece a função de repouso, mesmo sem saber o nome do acorde."),
        b ("Compare uma progressão que termina na tônica com uma que para antes."),
        b ("Cante a nota de repouso depois de ouvir a progressão."),
        b ("Confirme no instrumento se a nota cantada é a tônica."),
        aud ({ "C4", "E4", "G4", "G4", "B4", "D5" },
             "Tônica indo para o dominante e parando: o ouvido espera a volta para casa."),

        h ("Tônica na análise harmônica"),
        p (
            "Na análise harmônica, a tônica é o primeiro passo de qualquer leitura. Antes de nomear os outros acordes, você identifica a tônica e a tonalidade. Só então os graus fazem sentido: dizer que um acorde é o 'IV' só tem significado se você já sabe qual é o 'I'. É a tônica que dá significado a todos os outros graus."),
        p (
            "É por isso que os exercícios deste módulo insistem em tocar a tônica antes dos outros acordes. Tocar a tônica é estabelecer o centro; tocar os outros acordes é medir o afastamento em relação a esse centro. Sem a tônica, a análise vira uma lista de acordes sem sentido — com ela, vira uma história de tensão e repouso."),
        b ("A análise começa pela tônica: ela define a tonalidade."),
        b ("Os graus só têm significado em relação ao I."),
        b ("Tocar a tônica estabelece o centro para todo o resto."),

        h ("A tônica e os outros graus"),
        p (
            "A tônica não é apenas o primeiro acorde do campo: é a referência que dá sentido a todos os outros. O grau IV só é 'afastamento' porque existe um I de onde se afastar; o grau V só é 'tensão' porque existe um I para onde resolver. Sem a tônica, os graus seriam apenas acordes soltos, sem função nenhuma."),
        p (
            "É por isso que, ao analisar uma música, o primeiro passo é sempre encontrar a tônica. Só depois de identificá-la é possível nomear os outros acordes e entender as suas funções. Uma progressão lida sem a tônica é uma lista; lida com a tônica, é uma história de tensão e repouso que faz sentido musical."),
        b ("A tônica é a referência que dá função aos outros graus."),
        b ("O afastamento e a tensão só existem em relação a ela."),
        b ("Identificar a tônica é o primeiro passo da análise harmônica."),
        aud ({ "C4", "E4", "G4", "F4", "A4", "C5", "C4", "E4", "G4" },
             "Tônica, afastamento e volta à tônica: o repouso dá sentido ao movimento."),

        h ("A tônica em diferentes tonalidades"),
        p (
            "A tônica muda de nome conforme a tonalidade, mas a sua função é sempre a mesma. Em Dó maior é C; em Sol maior é G; em Fá maior é F. O que importa não é o nome do acorde, e sim o papel que ele cumpre: o ponto de repouso para onde a música quer voltar. Saber transpor a função, e não apenas o acorde, é o que permite tocar em qualquer tom."),
        p (
            "Um exercício útil é tocar a mesma progressão em três tonalidades diferentes, prestando atenção à sensação de repouso. Você vai notar que a sensação é idêntica nas três — só muda a altura. Isso confirma que a função tônica é uma relação, e não uma propriedade de um acorde específico. É a base da análise por graus que você usou em todo o módulo."),
        b ("A tônica muda de nome, mas a função é sempre a mesma."),
        b ("Transpor mantém a função e muda a altura."),
        b ("A sensação de repouso é a mesma em qualquer tonalidade."),
        tbl ({ "Tonalidade", "Tônica (I)", "Sensação" }, {
            { "Dó maior", "C", "repouso" },
            { "Sol maior", "G", "repouso" },
            { "Fá maior", "F", "repouso" },
            { "Ré maior", "D", "repouso" },
            { "Lá menor", "Am", "repouso (menor)" },
        }),

        h ("Resumo do tópico"),
        b ("Função tônica é a função de repouso da tonalidade."),
        b ("É exercida pelo grau I e pelos substitutos iii e vi."),
        b ("Soa estável e conclusiva; é o ponto de chegada da frase."),
        b ("Atrasar a volta à tônica aumenta a tensão e a resolução."),
        b ("No braço, é a âncora a partir da qual se contam os outros graus."),
        c (
            "Nos exercícios deste tópico, toque a tríade de tônica e seus substitutos no instrumento. O app reconhece as notas e confere se a função de repouso está sendo executada corretamente."),
    };
}

} // namespace cursomusica::content
