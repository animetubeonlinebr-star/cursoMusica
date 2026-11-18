#include "Course/Content/Topics.h"

// Topic 11B — Escalas ascendentes e descendentes (Módulo 11, Etapa 11).
namespace cursomusica::content
{

std::vector<ContentItem> topic11B()
{
    return {

        p (
            "Depois de aprender a escala recortada numa região, o passo seguinte é aprender a percorrê-la inteira, de baixo para cima e de cima para baixo. Escalas ascendentes e descendentes parecem exercício de aquecimento, mas são muito mais: são o alicerce da fluência. Quem sobe e desce a escala sem pensar tem a mão livre para a frase; quem hesita na descida trava no meio do solo."),
        p (
            "O motivo é simples. Quase toda frase musical é uma subida que resolve numa descida — ou o contrário. Se a descida é insegura, a frase inteira cambaleia. Por isso os grandes improvisadores tratam a escala nos dois sentidos como uma segunda natureza: sobem e descem com a mesma naturalidade com que respiram."),
        c (
            "Subir é fácil porque a tônica costuma estar embaixo; descer é onde o aluno fraqueja. Treine a descida com a mesma dedicação da subida — ela é a metade que você usa para resolver."),

        h ("Ascendente e descendente: o mesmo caminho ao contrário"),
        p (
            "A escala ascendente começa na tônica grave e sobe grau por grau. A descendente é exatamente o caminho de volta. No papel parecem a mesma coisa, mas na mão são tarefas diferentes: subir usa a extensão dos dedos para o agudo, descer usa o recuo da mão para o grave. Cada sentido tem a sua própria digitação de conforto."),
        p (
            "A digitação que serve para subir raramente é a melhor para descer. Os grandes guitarristas escolhem digitações diferentes para cada sentido, justamente para que a descida não tropece. Isso não é preguiça: é economia de movimento — e economia de movimento é velocidade."),
        b ("Estude a subida e a descida como dois exercícios separados."),
        b ("Na descida, escolha a digitação pelo conforto do recuo da mão."),
        b ("Toque a escala inteira em legato e depois em palhetada alternada."),
        img ("m11_asc_desc", "Escala ascendente e descendente: o mesmo caminho percorrido nos dois sentidos, com digitações pensadas para cada direção."),

        h ("A escala como termômetro da mão"),
        p (
            "A escala nos dois sentidos funciona como um termômetro: se a mão está aquecida e sincronizada, a escala sai parelha; se está travada, a escala expõe o problema na hora. Por isso ela abre todo estudo. Antes de tentar a frase difícil, suba e desça a escala devagar e sinta se as duas mãos estão conversando."),
        p (
            "O termômetro também mede tempo. Uma escala parelha no metrônomo em 100 BPM é a prova de que a sua mão está pronta para a meta do módulo. Uma escala que acelera na subida e freia na descida mostra onde a técnica ainda precisa de atenção."),
        tbl ({ "Sentido", "Desafio principal", "Como treinar" }, {
            { "Ascendente", "esticar a mão para o agudo", "comece devagar e acelere só no fim" },
            { "Descendente", "recuar a mão sem travar", "toque primeiro em legato" },
            { "Ambos", "manter o tempo parelho", "metrônomo em 60 e suba de 4 em 4" },
        }),
        c (
            "Meta do módulo: 100 BPM. Só considere a escala dominada quando subir e descer no mesmo tempo, sem acelerar nem frear."),

        h ("O lick deste tópico"),
        p (
            "O lick abaixo sobe a escala e volta no mesmo desenho, do jeito que Guthrie Govan costuma construir uma linha que respira: sobe, atinge o topo e desce resolvendo na tônica. Ele treina exatamente o que este tópico ensina — percorrer a escala nos dois sentidos sem tropeçar na volta."),
        aud ({ "A4", "B4", "C5", "D5", "E5", "F5", "G5", "A5", "G5", "F5", "E5", "D5", "C5", "B4", "A4" },
             "Lick do tópico B: a escala de Lá menor sobe até o A5 e desce resolvendo na tônica. O ponto de virada é a nota mais aguda."),
        part ("m11_partitura_b", { "A4", "B4", "C5", "D5", "E5", "F5", "G5", "A5", "G5", "F5", "E5", "D5", "C5", "B4", "A4" },
              "Partitura do lick B: escala ascendente e descendente. A descida tem a mesma digitação confortável da subida."),

        h ("Da escala à frase"),
        p (
            "Tocar a escala é o começo; fraseá-la é o objetivo. Em vez de subir a escala inteira, suba só um trecho, faça uma volta e resolva. O lick deste tópico já mostra esse gesto: a escala não é um fim, é o material com que a frase respira para cima e para baixo."),

        h ("Por que a descida trava"),
        p (
            "A descida trava por um motivo mecânico: subir e descer usam movimentos diferentes da mão. Na subida, o movimento natural é abrir a mão e estender os dedos para o agudo; na descida, é recolher a mão e dobrar os dedos para o grave. Como a subida é mais fácil de memorizar, ela fica automática primeiro, e a descida continua dependente de decisão consciente — e decisão consciente é lenta."),
        p (
            "A solução é tratar a descida como um exercício separado, com a sua própria digitação. Muitos guitarristas usam, na descida, uma digitação diferente da que usam na subida, justamente para que o movimento de recolher a mão seja o mais curto possível. Economizar movimento é economizar tempo, e a descida parelha é metade da frase bem-feita."),
        b ("Subir e descer são movimentos distintos: estender e recolher a mão."),
        b ("A descida merece a sua própria digitação, escolhida pelo conforto do recuo."),
        b ("Treine a descida isolada, em legato, antes de juntá-la à subida."),
        tbl ({ "Erro na descida", "Sintoma", "Correção" }, {
            { "Digitação copiada da subida", "o dedo fica preso na corda", "escolha a digitação pelo recuo" },
            { "Acelerar no topo", "a volta sai atropelada", "marque o topo e freie o tempo" },
            { "Mão tensa no registro grave", "som fraco nas últimas notas", "relaxe ao recolher a mão" },
        }),

        h ("A escala como base das sequências"),
        p (
            "Depois de subir e descer a escala em graus conjuntos, o passo seguinte é quebrá-la em sequências: grupos de três, de quatro, saltos de terça. As sequências transformam a escala em material melódico, porque repetem um desenho ao longo dos graus. O ouvido reconhece o padrão e a frase ganha coerência, mesmo que as notas mudem."),
        p (
            "A sequência mais comum é o grupo de três: toque as três primeiras notas, depois as três seguintes, e assim por diante, sempre subindo um grau. O resultado é um movimento contínuo que sobe a escala sem soar como um exercício. É exatamente esse tipo de sequência que o lick do tópico A usa, e é ele que dá à frase a sensação de subida constante."),
        c (
            "Prática recomendada: toque a escala ascendente, a descendente e um grupo de três, tudo no mesmo tempo. Quando os três saírem parelhos, a sua mão está pronta para frasea de verdade."),

        h ("Medindo a evolução"),
        p (
            "A escala nos dois sentidos é também o melhor medidor de progresso. Comece no metrônomo em 60 e só suba de 4 em 4 BPM quando os dois sentidos saírem parelhos, sem acelerar nem frear. Anote o tempo máximo em que a escala fica parelha nos dois sentidos: esse número é o seu termômetro real, mais confiável do que a sensação de velocidade."),
        p (
            "A meta do módulo é 100 BPM. Você chega lá somando, não saltando: cada sessão de estudo sobe um pouco o tempo, e o corpo vai assimilando. Forçar a velocidade antes de a digitação estar firme só consolida o erro. A escala é a fundação; é melhor gastar tempo nela do que corrigi-la depois."),


        h ("O metrônomo como professor"),
        p (
            "O metrônomo é o professor mais honesto que existe: ele não perdoa pressa nem atraso. Usá-lo bem é a diferença entre estudar e apenas tocar. Comece num tempo em que a escala saia perfeita nos dois sentidos; só então suba de 4 em 4 BPM. Se em algum tempo a descida travar, volte um degrau e consolide. A velocidade vem da repetição no tempo certo, nunca do esforço no tempo errado."),
        p (
            "Há duas formas de estudar com o metrônomo. Na primeira, você toca uma nota por clique; na segunda, duas ou quatro notas por clique. A segunda forma treina a subdivisão e a independência: a mão precisa distribuir as notas dentro do clique, sem correr nem frear. É essa segunda forma que prepara a escala para virar frase, porque a frase vive entre os cliques, não só sobre eles."),
        p (
            "Grave os tempos em que você consegue subir e descer a escala parelho. Esse número é o seu mapa de progresso: ele sobe devagar, mas sobe. Quando ele estagnar, mude o exercício (grupos de três, saltos de terça) em vez de insistir na força. A escala é uma ferramenta; forçá-la além do ponto só consolida a tensão que você vai ter de desfazer depois."),
        b ("Use o metrônomo num tempo em que a escala saia perfeita; suba de 4 em 4 BPM."),
        b ("Treine uma, duas e quatro notas por clique para ganhar subdivisão."),
        b ("Anote os tempos alcançados: o progresso é medido, não sentido."),
        tbl ({ "Notas por clique", "O que treina", "Quando usar" }, {
            { "1 nota", "precisão da digitação", "primeiro estágio" },
            { "2 notas", "subdivisão em colcheias", "segundo estágio" },
            { "4 notas", "subdivisão em semicolcheias", "terceiro estágio" },
        }),


        h ("Frases, não escalas"),
        p (
            "O objetivo final da escala não é tocar a escala, e sim construir frases com ela. Uma frase começa, desenvolve uma ideia e termina; a escala é só o material. Quando você domina a escala nos dois sentidos, deixa de pensar em notas soltas e passa a pensar em gestos: uma subida que resolve, uma volta que respira, um salto que surpreende. É esse pensamento que transforma o exercício em música."),
        p (
            "Para treinar isso, toque a escala ascendente e descendente e, no fim, improvise oito compassos usando só as notas dela. Comece e termine numa nota de repouso, como a tônica ou a terça. Você vai perceber que a escala, que parecia um exercício, vira vocabulário assim que ganha começo, meio e fim. A fluência que você construiu na escala é o que sustenta a frase."),
        p (
            "Guardar a escala como referência, e não como fim, é o que diferencia o aluno que estuda do aluno que toca. Nos próximos tópicos, você vai acrescentar notas de cor, ligar posições e resolver sobre acordes. Tudo isso se apoia na escala que você treinou aqui. Quanto mais firme ela estiver nos dois sentidos, mais fácil será todo o resto do módulo."),
        b ("A escala é o material; a frase é o que você faz com ele."),
        b ("Improvise frases de oito compassos usando só as notas da escala."),
        b ("Comece e termine numa nota de repouso para dar direção à frase."),
        tbl ({ "Estágio", "O que você toca", "Objetivo" }, {
            { "Escala", "notas em ordem", "memorizar o desenho" },
            { "Sequência", "grupos de três ou quatro", "ganhar movimento" },
            { "Frase", "ideia com começo e fim", "fazer música" },
        }),

        c (
            "Objetivo da Etapa 11: usar as escalas como ponto de partida para criar frases. A escala nos dois sentidos é a sua primeira frase completa: subida, topo e resolução."),
    };
}

} // namespace cursomusica::content
