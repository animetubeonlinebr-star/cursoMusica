#include "Course/Content/Topics.h"

// Topic 10F — Estudo das vozes internas (Módulo 10, Etapa 10).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 10). Conduzir as vozes =
// movimentar cada linha do acorde com o menor movimento possível.
namespace cursomusica::content
{

std::vector<ContentItem> topic10F()
{
    return {

        p (
            "Quando você toca um acorde, está tocando várias notas ao mesmo tempo — e cada uma dessas notas é uma voz. A voz de cima é o soprano; a de baixo é o baixo; e entre elas ficam as vozes internas (contralto e tenor). Estudar as vozes internas é aprender a movimentar cada uma dessas linhas com o menor movimento possível, de modo que os acordes se conectem suavemente em vez de saltar. É o que separa uma sequência de acordes de uma harmonia que 'canta'."),
        p (
            "A condução de vozes é a técnica que faz os acordes fluírem. Quando cada voz anda por graus próximos — e não por saltos aleatórios — a harmonia ganha uma sensação de continuidade. É por isso que guitarristas de jazz e violonistas de bossa usam inversões e acordes de poucas cordas: eles estão conduzindo as vozes, não apenas 'pegando o acorde'. Este tópico ensina a ouvir e a controlar essas linhas."),
        c (
            "Ideia central: cada nota do acorde é uma voz com vida própria. Conduzir vozes é movimentar cada linha pelo caminho mais curto entre um acorde e o próximo."),

        h ("As quatro vozes"),
        p (
            "Na harmonia tradicional, os acordes são pensados em quatro vozes: soprano (a mais aguda), contralto, tenor e baixo (a mais grave). Cada voz tem um registro preferido e um comportamento próprio. O baixo é a voz mais estável e define a harmonia; o soprano costuma ser a melodia; as vozes internas preenchem o acorde. Estudar as vozes internas é, portanto, cuidar do 'miolo' da harmonia — a parte que ninguém canta sozinha, mas que decide se os acordes se ligam bem."),
        tbl ({ "Voz", "Registro típico", "Papel" }, {
            { "soprano", "agudo", "melodia, voz principal" },
            { "contralto", "médio-agudo", "voz interna, completa o acorde" },
            { "tenor", "médio-grave", "voz interna, liga com o baixo" },
            { "baixo", "grave", "define a harmonia" },
        }),
        img ("m10_vozes_internas", "Quatro vozes (soprano, contralto, tenor, baixo) conduzindo por graus próximos entre os acordes."),

        h ("Condução por graus próximos"),
        p (
            "O princípio básico da condução de vozes é: cada voz deve se mover o mínimo possível. Se o acorde seguinte tem uma nota comum, mantenha-a parada; se não tem, mova a voz apenas um grau. No exemplo C7M – Am7 – Dm7 – G7, a nota F é comum a Dm7 e G7: ela fica parada, amarrando os dois acordes. Essa nota comum é o que faz a progressão soar coesa — e é justamente o que a condução de vozes procura."),
        b ("Nota comum entre dois acordes: mantenha-a na mesma voz."),
        b ("Sem nota comum: mova cada voz um grau, para o lado mais próximo."),
        b ("Evite saltos grandes nas vozes internas."),
        aud ({ "E4", "E4", "F4", "F4", "G4", "A4", "B4", "D5" },
             "Uma voz interna caminhando por graus próximos de C7M a G7. Ouça o quanto ela se move pouco."),
        img ("m10_vozes_internas", "O F comum a Dm7 e G7 fica parado: é a nota que amarra os dois acordes."),

        h ("Inversões e a posição das vozes"),
        p (
            "Inverter um acorde é mudar a nota do baixo — e isso muda a posição de todas as vozes. Inverter é a ferramenta principal para conduzir vozes: se o acorde seguinte pede que o baixo se mova por grau próximo, você inverte o acorde para que o baixo esteja onde você precisa. As inversões permitem que uma progressão caminhe suavemente, com o baixo descendo ou subindo por graus conjuntos em vez de saltar."),
        tbl ({ "Inversão", "Nota no baixo", "Cifra", "Efeito" }, {
            { "estado fundamental", "fundamental", "C", "estável, firme" },
            { "1ª inversão", "terça", "C/E", "baixo sobe, leve" },
            { "2ª inversão", "quinta", "C/G", "baixo firme, suspenso" },
            { "3ª inversão", "sétima", "C7M/B", "baixo instável, pede resolução" },
        }),
        c (
            "Inverter não muda o acorde, só a nota do baixo. Mas muda tudo na condução das vozes: é a inversão que permite que o baixo ande por graus próximos enquanto a harmonia muda."),
        aud ({ "C4", "E4", "G4", "E4", "C4", "G3" }, "C com o baixo subindo (C → C/E → C/G): o baixo caminha por graus, não por saltos."),

        h ("Aplicação na guitarra: acordes de poucas cordas"),
        p (
            "Na guitarra, conduzir vozes é mais fácil com acordes de poucas cordas. Um acorde de quatro notas (tônica, terça, quinta e sétima) em cordas internas permite movimentar cada voz quase independentemente. É por isso que os guitarristas de jazz usam tanto os acordes de 3 e 4 notas no meio do braço: eles são mais fáceis de conduzir do que os acordes de seis cordas, que prendem as vozes num bloco fixo. Menos notas, mais controle."),
        b ("Prefira acordes de 3 ou 4 notas (shell voicings) para conduzir vozes."),
        b ("Toque nas cordas internas para deixar cada voz independente."),
        b ("Deixe o baixo livre para caminhar; não prenda todas as cordas."),
        aud ({ "C4", "E4", "A#3", "D#4" }, "Um acorde de poucas notas (shell): mais fácil de conduzir cada voz."),

        h ("Condução de vozes na reharmonização"),
        p (
            "A condução de vozes é o que faz uma reharmonização soar bem ou mal. Você pode escolher os acordes 'certos' pela análise e ainda assim a progressão soar dura, se as vozes saltarem. Por outro lado, uma escolha de acordes apenas razoável soa ótima se as vozes forem bem conduzidas. Por isso este tópico vem antes da reharmonização: antes de trocar acordes, aprenda a ligá-los. Nos tópicos G a I, cada reharmonização que você fizer vai passar por aqui."),
        b ("Reharmonize pensando nas vozes, não só nos acordes."),
        b ("Conduza o baixo por graus próximos sempre que possível."),
        b ("Mantenha as notas comuns paradas para amarrar os acordes."),
        part ("m10_partitura_vozes", { "E4", "E4", "F4", "F4", "G4", "A4", "B4", "D5" },
              "Partitura de uma voz interna conduzindo por graus próximos. Ouça como ela se move pouco."),

        h ("Como praticar a condução de vozes"),
        p (
            "Pratique com progressões curtas e poucas vozes. Pegue um ii–V–I (Dm7–G7–C7M) e toque-o várias vezes, sempre mudando a inversão para que cada voz se mova o mínimo. Depois acrescente uma voz de melodia por cima. O app ajuda: ele reconhece as notas que você toca e confere se o acorde está correto, então você pode treinar inversões e condução com verificação. Conduzir vozes é uma habilidade auditiva — você aprende ouvindo o quanto a harmonia flui."),
        b ("Toque um ii–V–I variando as inversões."),
        b ("Mova cada voz pelo caminho mais curto."),
        b ("Confira com o app: os acordes precisam estar corretos em cada inversão."),
        c (
            "Erro comum: tocar todos os acordes na mesma posição, deixando as vozes saltarem. A harmonia 'funciona', mas soa dura. A condução de vozes é o que dá fluidez."),

        h ("Erros comuns no estudo das vozes internas"),
        p (
            "O erro mais comum é ignorar as vozes internas e pensar só no baixo e na melodia. São justamente as vozes internas que dão corpo ao acorde e que decidem a suavidade da ligação. O segundo erro é mover todas as vozes ao mesmo tempo, criando um 'bloco' que sobe e desce inteiro em vez de linhas independentes. O terceiro é usar sempre a mesma posição, esquecendo as inversões. Estudar vozes internas é aprender a ouvir cada linha separadamente, mesmo tocando todas juntas."),
        b ("Ouça cada voz separadamente, mesmo tocando o acorde inteiro."),
        b ("Mova uma voz de cada vez; evite o bloco que sobe inteiro."),
        b ("Use inversões para variar a posição e suavizar as ligações."),
        img ("m10_vozes_internas", "As vozes internas dão corpo ao acorde e decidem se a ligação entre dois acordes é suave ou dura."),

        h ("Vozes internas na guitarra: shell voicings e drop 2"),
        p (
            "Na guitarra, a condução de vozes acontece principalmente com dois tipos de acorde. Os shell voicings usam só três ou quatro notas (tônica, terça e sétima, às vezes com a quinta) e deixam as vozes livres para se movimentar. Os acordes drop 2 são arranjos de quatro notas em que uma voz é 'derrubada' uma oitava para facilitar a execução no braço. Ambos permitem conduzir cada voz de forma independente — e é por isso que os guitarristas de jazz tocam tanto com esses acordes em vez dos acordes de seis cordas."),
        tbl ({ "Tipo", "Notas", "Uso" }, {
            { "shell voicing", "tônica, 3ª, 7ª (3 notas)", "condução livre, base de jazz" },
            { "drop 2", "4 notas, uma oitava abaixo", "chord melody, arranjo" },
            { "drop 3", "4 notas, duas oitavas abaixo", "baixo + acorde" },
            { "acorde de 6 cordas", "todas as notas", "bloco fixo, menos flexível" },
        }),
        b ("Shell voicings: menos notas, mais liberdade de condução."),
        b ("Drop 2 e drop 3: quatro notas, vozes distribuídas para o braço."),
        b ("Acordes de seis cordas prendem as vozes; evite-os para conduzir."),
        aud ({ "C4", "E4", "A#3" }, "Um shell voicing (tônica, terça e sétima): só o essencial, com as vozes livres."),

        h ("Paralelo e contrário: como as vozes se movem"),
        p (
            "As vozes podem se mover de três maneiras entre dois acordes: em movimento paralelo (todas na mesma direção), em movimento contrário (umas sobem, outras descem) ou em movimento oblíquo (uma voz fica parada enquanto as outras se movem). A condução ideal mistura os três: mantém as notas comuns paradas (oblíquo), move as outras por graus (paralelo suave) e, às vezes, cria um movimento contrário entre o baixo e o soprano para dar interesse. Evitar que todas as vozes subam ou desçam juntas em blocos é o que dá naturalidade à harmonia."),
        b ("Paralelo: todas as vozes na mesma direção (evite em excesso)."),
        b ("Oblíquo: uma voz fica parada (nota comum), as outras se movem."),
        b ("Contrário: baixo e soprano em direções opostas (dá interesse)."),
        aud ({ "C4", "E4", "G4", "B4", "B3", "D4", "F4", "A4" },
             "Movimento oblíquo: o B fica parado entre C7M e G7. Ouça a nota que amarra."),

        h ("Condução de vozes e o baixo"),
        p (
            "O baixo é a voz mais importante da condução, porque é ele que define a harmonia e que o ouvido segue. Uma boa condução de baixo caminha por graus próximos, muitas vezes cromáticos, em vez de saltar de fundamental em fundamental. É por isso que as inversões existem: elas permitem que o baixo ande suavemente enquanto a harmonia muda. Um baixo bem conduzido faz uma progressão simples soar sofisticada; um baixo que salta faz uma progressão rica soar dura."),
        b ("Conduza o baixo por graus próximos (de preferência cromáticos)."),
        b ("Use inversões para ajustar a nota do baixo."),
        b ("Um bom baixo faz a progressão fluir."),
        aud ({ "C3", "B2", "A2", "G2", "F2" }, "Um baixo descendo por graus: a harmonia ganha movimento contínuo."),

        h ("Erros comuns na condução de vozes"),
        p (
            "Além do erro de tocar tudo no mesmo bloco, há outros comuns. Mover todas as vozes na mesma direção por muitos acordes cria um som mecânico. Duplicar a mesma nota em vozes diferentes enfraquece o acorde. Saltos grandes nas vozes internas quebram a fluidez. E deixar a melodia (soprano) presa no meio do acorde esconde a linha principal. Uma boa condução de vozes é discreta: você não a nota, mas sente a harmonia fluir — e é justamente por isso que ela é difícil de perceber e importante de estudar."),
        b ("Evite mover todas as vozes na mesma direção por muito tempo."),
        b ("Não duplique a mesma nota em vozes diferentes."),
        b ("Mantenha a melodia (soprano) como a voz mais aguda."),
        b ("Prefira movimentos pequenos nas vozes internas."),

        h ("Resumo do tópico"),
        b ("Cada nota do acorde é uma voz; o estudo das vozes internas cuida do miolo da harmonia."),
        b ("Conduzir vozes é mover cada linha pelo caminho mais curto."),
        b ("Notas comuns ficam paradas; sem nota comum, move-se um grau."),
        b ("Inversões mudam a nota do baixo e permitem conduzir as vozes."),
        b ("Na guitarra, acordes de poucas notas facilitam a condução."),
        c (
            "Objetivo do tópico: fazer os acordes fluírem. Antes de reharmonizar, aprenda a ligar os acordes com vozes bem conduzidas — é isso que faz a nova harmonia soar natural."),
    };
}

} // namespace cursomusica::content
