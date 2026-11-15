#include "Course/Content/Topics.h"

// Topic 3H — Silabas ritmicas (Konokol), percussoes e efeito sanfona (Modulo 3, Etapa 3).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 3, bloco H).
namespace cursomusica::content
{

std::vector<ContentItem> topic3H()
{
    return {

        p (
            "Este é o tópico de fechamento do módulo. Aqui você junta as ferramentas rítmicas que aprendeu e acrescenta três recursos que dão vida ao acompanhamento: as sílabas rítmicas (incluindo o sistema indiano Konokol), as percussões no violão e o efeito sanfona. Com eles, o acompanhamento deixa de ser só acordes no tempo e passa a ser música com groove."),
        p (
            "Falar o ritmo antes de tocar é uma técnica milenar: o Konokol (a solfa rítmica do sul da Índia) sistematizou isso com sílabas que representam cada subdivisão. As percussões no violão (bater na madeira, abafar as cordas) e o efeito sanfona (abrir e fechar o acorde) são recursos que ampliam o vocabulário rítmico do violonista brasileiro. Este tópico ensina os três."),
        c (
            "Objetivo: falar o ritmo, percussão e efeito sanfona — recursos que transformam o acompanhamento em groove. O ritmo sai da mão e passa pela boca antes de voltar para o instrumento."),

        h ("Silabas ritmicas: falar antes de tocar"),
        p (
            "A sílaba rítmica é uma palavra curta que representa uma figura. TÁ representa a semínima; TÁ-KI, as colcheias; TA-KI-TA-KI, as semicolcheias. Falar o ritmo em voz alta antes de tocar é a técnica mais eficaz de estudo: o que a boca domina, a mão repete com muito mais facilidade. As sílabas transformam o ritmo abstrato em algo concreto e falável."),
        tbl ({ "Silaba", "Figura", "Uso" }, {
            { "TA", "seminima", "1 pulso" },
            { "TA-KI", "duas colcheias", "2 por pulso" },
            { "TA-KI-TA-KI", "quatro semicolcheias", "4 por pulso" },
            { "TA-KA", "duas tercinas", "subdivisao ternaria" },
            { "DIN", "acento forte", "marcar o tempo forte" },
        }),
        b ("TÁ: semínima (um pulso)."),
        b ("TÁ-KI: colcheias (dois por pulso)."),
        b ("TA-KI-TA-KI: semicolcheias (quatro por pulso)."),
        img ("m3_konokol", "Sílabas rítmicas (Konokol) e percussão vocal: falar o ritmo antes de tocar."),
        c (
            "Falar o ritmo é o teste mais rápido de que a leitura foi entendida. Se você não consegue falar, não vai conseguir tocar."),

        h ("Konokol: a solfa ritmica indiana"),
        p (
            "O Konokol é um sistema de solfejo rítmico do sul da Índia. Em vez de '1 e 2 e', ele usa sílabas como TA, KA, DI, MI, cada uma representando uma subdivisão. O sistema permite falar ritmos complexos com fluência e é usado por músicos de todo o mundo, inclusive guitarristas de jazz e fusão, para internalizar ritmos irregulares. A ideia central é a mesma: falar o ritmo até ele virar automático."),
        tbl ({ "Silaba (Konokol)", "Subdivisao" }, {
            { "TA", "1 tempo" },
            { "TA-KA", "2 partes iguais" },
            { "TA-KI-TA", "3 partes (tercina)" },
            { "TA-KA-DI-MI", "4 partes (semicolcheia)" },
            { "DIN", "acento/pausa" },
        }),
        b ("O Konokol fala o ritmo com sílabas curtas e precisas."),
        b ("Serve para internalizar ritmos irregulares (5/4, 7/8)."),
        b ("É usado por guitarristas de jazz e fusão."),
        aud ({ "C4", "C4", "C4", "C4", "D4", "D4", "D4", "D4" }, "Konokol em ação: grupos de três (TA-KI-TA) e de quatro (TA-KA-DI-MI)."),
        c (
            "Falar um 7/8 com Konokol é muito mais fácil do que contar '1 e 2 e 3 e 4'. As sílabas dão forma ao ritmo irregular."),

        h ("Percussao no violao"),
        p (
            "O violão é um instrumento de percussão também. Bater na madeira (tampo, cavalete, laterais) produz sons percussivos que se integram ao ritmo. Combinar acordes com percussão é o que dá ao acompanhamento brasileiro o seu balanço: o som seco da madeira marca o tempo enquanto o acorde soa. A percussão no violão é um recurso muito usado no samba, no baião e na música popular."),
        tbl ({ "Percussao", "Onde", "Efeito" }, {
            { "Batida na madeira", "tampo", "marca o tempo" },
            { "Batida no cavalete", "ponte", "som seco, contratempo" },
            { "Abafamento (chuck)", "cordas", "som percussivo curto" },
            { "Harmonico percussivo", "sobre o traste", "cor ritmica" },
        }),
        b ("Bater na madeira marca o tempo sem nota."),
        b ("O abafamento (chuck) produz som percussivo nas cordas."),
        b ("Combinar acorde e percussão dá balanço ao acompanhamento."),
        img ("m3_percussao_sanfona", "Percussão no violão e efeito sanfona: recursos que dão groove ao acompanhamento."),
        c (
            "A percussão no violão é o que faz um único instrumento soar como uma pequena banda: acorde, baixo e ritmo ao mesmo tempo."),

        h ("Efeito sanfona"),
        p (
            "O efeito sanfona é um recurso típico do violão brasileiro: consiste em abrir e fechar o acorde alternadamente. Você toca o acorde aberto (todas as notas soando) e, em seguida, abafa as cordas com a mão direita, criando um som curto e percussivo. Alternar os dois produz um 'abre e fecha' que dá pulsação ao acompanhamento — daí o nome sanfona. É muito usado no samba, no choro e na bossa."),
        b ("Acorde aberto: todas as notas soando."),
        b ("Acorde fechado: cordas abafadas, som curto."),
        b ("Alternar os dois cria a pulsação do efeito sanfona."),
        aud ({ "C4", "E4", "G4", "C4", "E4", "G4", "C4", "E4" }, "Efeito sanfona em Dó maior: alterne acorde aberto e abafado."),
        c (
            "O efeito sanfona é a marca do violão brasileiro. Dominá-lo é dominar o balanço do samba e do choro."),

        h ("Combinando os recursos"),
        p (
            "O segredo do acompanhamento rico é combinar os recursos: um baixo no polegar, um acorde nos dedos, uma percussão na madeira e o efeito sanfona. Cada recurso ocupa um espaço do tempo, e juntos criam uma textura completa. O domínio vem da prática lenta: comece com um recurso, acrescente outro e só junte tudo quando cada um estiver firme."),
        b ("Comece com um recurso; acrescente um por vez."),
        b ("Cada recurso ocupa um espaço do tempo."),
        b ("Junte tudo só quando cada parte estiver automática."),
        c (
            "A soma dos recursos é o que torna o acompanhamento brasileiro tão rico: um único violão pode fazer o papel de vários instrumentos."),

        h ("Erros comuns com esses recursos"),
        p (
            "Os erros mais comuns são falar o ritmo errado (silabar sem precisão), perder o pulso ao acrescentar a percussão e abafar demais no efeito sanfona (matando o som). Outro erro é tentar juntar todos os recursos de uma vez, antes de dominar cada um. A ordem importa: falar, depois tocar, depois acrescentar."),
        b ("Silabar sem precisão, só 'por cima'."),
        b ("Perder o pulso ao bater na madeira."),
        b ("Abafar demais no efeito sanfona."),
        b ("Juntar recursos antes de dominar cada um."),
        c (
            "Dica: grave-se falando o ritmo e depois tocando. Comparar os dois mostra se a execução corresponde ao que você falou."),

        h ("Como praticar o fechamento do modulo"),
        p (
            "Comece falando o ritmo com as sílabas. Depois, toque-o na grade do metrônomo. Em seguida, acrescente a percussão e o efeito sanfona. Este módulo usa BPM meta 68: um andamento calmo que permite ouvir cada recurso com clareza. O gate cobra tocar na grade com alinhamento ≥ 0,77, unindo tudo o que o módulo ensinou."),
        b ("Fale o ritmo (sílabas) antes de tocar."),
        b ("Toque na grade, mantendo o pulso."),
        b ("Acrescente percussão e efeito sanfona."),
        b ("Junte tudo no desafio de gate."),
        part ("m3_partitura_konokol", { "C4", "E4", "D4", "F4", "E4", "G4", "C5", "G4" },
              "Partitura: célula rítmica em Dó para falar e tocar. Fale as sílabas antes de executar."),

        h ("Resumo do topico"),
        b ("Falar o ritmo com sílabas (TÁ, TÁ-KI) é a base do estudo rítmico."),
        b ("O Konokol é a solfa rítmica indiana, ótima para ritmos irregulares."),
        b ("Percussão no violão (madeira, abafamento) dá groove ao acompanhamento."),
        b ("O efeito sanfona alterna acorde aberto e abafado, criando pulsação."),
        b ("Combinar os recursos transforma o acompanhamento em música completa."),
        c (
            "Com este tópico, o módulo fecha: você aprendeu a ler o ritmo, sentir o pulso, dividir o compasso, tocar levadas com palheta e com os dedos, e agora falar o ritmo, percussão e efeito sanfona. O gate une tudo na grade do metrônomo."),

        h ("Percussao vocal e corporal"),
        p (
            "Antes de bater na madeira do violão, você pode usar o próprio corpo como percussão. Bater palmas, estalar os dedos, bater o pé e até vocalizar o som da bateria (bumbo, caixa, chimbal) ajuda a internalizar o ritmo. Muitos professores usam a percussão corporal para ensinar ritmos complexos, porque o corpo entende o tempo antes da mão. Essa prática prepara o aluno para a percussão no instrumento."),
        b ("Palmas nos tempos fortes: sente o pulso."),
        b ("Pé marcando o tempo: mantém a referência."),
        b ("Vocalizar a bateria (bum-tss): internaliza o groove."),
        c (
            "O corpo é o primeiro metrônomo. Antes de tocar, sentir o ritmo no corpo é o que garante que a execução vai ser estável."),

        h ("Ritmos brasileiros e o efeito sanfona"),
        p (
            "O efeito sanfona é a base de vários ritmos brasileiros. No samba, ele cria o balanço entre o acorde aberto e o abafado. No choro, marca a pulsação com precisão. No baião, dá o caráter percussivo. Reconhecer o efeito sanfona de ouvido é reconhecer o sotaque do violão brasileiro. Estudar esses ritmos desenvolve a mão direita e amplia o vocabulário do acompanhamento."),
        tbl ({ "Ritmo brasileiro", "Uso do efeito sanfona", "Caracteristica" }, {
            { "Samba", "abre e fecha o acorde", "balanco constante" },
            { "Choro", "pulsacao precisa", "virtuosismo" },
            { "Baiao", "marca o tempo", "percussivo" },
            { "Bossa nova", "discreto, sutil", "sincopado" },
        }),
        b ("Samba: sanfona constante, com síncope."),
        b ("Choro: precisão e velocidade na mão direita."),
        b ("Baião: caráter percussivo e marcado."),
        c (
            "Cada ritmo brasileiro usa o efeito sanfona de um jeito. Estudar um por um é construir um vocabulário rico de acompanhamento."),

        h ("Do recurso ao estilo: fechando o modulo"),
        p (
            "Com os recursos deste tópico — sílabas, Konokol, percussão e efeito sanfona — você tem um vocabulário rítmico completo para o nível 2 do curso. A partir daqui, o caminho é aplicar esse vocabulário em contextos musicais reais: tocar sambas, baiões, rocks e baladas, escolhendo a levada e os recursos certos para cada um. O módulo entregou a base; o repertório vem a seguir."),
        b ("Aplique os recursos em músicas reais."),
        b ("Escolha a levada certa para cada estilo."),
        b ("Combine palheta, dedos, percussão e sanfona conforme a música."),
        c (
            "O objetivo do módulo é dar ferramentas. A música acontece quando você usa essas ferramentas para fazer o acompanhamento soar vivo, no estilo certo, sem perder o pulso."),

        h ("Montando um acompanhamento completo"),
        p (
            "Para montar um acompanhamento completo, reúna tudo o que o módulo ensinou. Escolha a progressão de acordes (cifra). Escolha a levada (palheta ou dedos) e a célula rítmica. Decida onde caem os acentos e as pausas. Acrescente percussão e efeito sanfona. Mantenha o pulso firme na grade. Cada escolha corresponde a um tópico deste módulo: cifra com divisão (C), células e acentos (D), levadas com palheta (E), levadas com dedos (F), compassos (G) e recursos de fechamento (H)."),
        tbl ({ "Escolha", "Topico", "Ferramenta" }, {
            { "Progressao de acordes", "C", "cifra com divisao" },
            { "Desenho ritmico", "D", "celula + acento" },
            { "Tipo de ataque", "E/F", "palheta ou dedos" },
            { "Agrupamento", "G", "compasso" },
            { "Recursos extras", "H", "percusao + sanfona" },
        }),
        b ("Cada escolha do acompanhamento vem de um tópico do módulo."),
        b ("O acompanhamento completo reúne todas as ferramentas."),
        b ("Mantenha o pulso firme em todas as escolhas."),
        c (
            "Um bom acompanhamento é a soma inteligente dessas escolhas, sempre a serviço da música — nunca um desfile de recursos."),

        h ("O gate: unindo tudo"),
        p (
            "O desafio de gate fecha o módulo. Ele pede que você toque uma progressão de dois acordes na grade do metrônomo, com alinhamento de pelo menos 0,77 e 90% de acerto nos acordes reconhecidos. Esse é o nível 2 do curso (vamps de dois acordes), tocado no BPM meta de 68. Para passar, use tudo o que o módulo ensinou: conte o pulso, sinta a subdivisão, toque a célula com acento e mantenha o alinhamento."),
        b ("Gate: progressão de dois acordes na grade."),
        b ("Alvo: ≥90% de acerto e on_grid_ratio ≥ 0,77."),
        b ("BPM meta: 68 — andamento de estudo."),
        b ("Use a contagem e a subdivisão para manter o alinhamento."),
        c (
            "Passar no gate significa que você domina o ritmo do nível 2. A partir daí, o curso avança para os vamps de dois acordes aplicados (módulo 4)."),
    };
}

} // namespace cursomusica::content
