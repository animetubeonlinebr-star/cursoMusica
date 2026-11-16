#include "Course/Content/Topics.h"

// Topic 10B — Análise melódica (Módulo 10, Etapa 10).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 10) e a regra de notas de
// repouso x tensão (REQ-011, REQ-012).
namespace cursomusica::content
{

std::vector<ContentItem> topic10B()
{
    return {

        p (
            "A análise melódica é irmã da análise harmônica: enquanto a harmônica pergunta o que cada acorde faz, a melódica pergunta o que cada nota da melodia faz sobre o acorde que está soando. A mesma nota pode ser repouso num acorde e tensão no acorde seguinte. Analisar a melodia é dizer, nota por nota, se ela repousa ou tensiona — e por quê."),
        p (
            "Essa análise é a base da avaliação de improvisação do curso (REQ-011 e REQ-012): o aluno deve escolher notas de repouso no tempo forte e usar a tensão de passagem, resolvendo-a no acorde seguinte. Este tópico ensina a enxergar isso na partitura e a ouvir isso no áudio, para que o improviso deixe de ser tentativa e vire decisão consciente."),
        c (
            "Regra do curso (REQ-012): a tensão não solicitada é erro, salvo quando a nota faz parte do próprio acorde. O repouso é a regra; a tensão precisa de contexto e de resolução."),

        h ("Notas do acorde e notas de tensão"),
        p (
            "Sobre qualquer acorde existem dois grupos de notas. As notas do acorde (fundamental, terça, quinta e sétima) são o esqueleto: quando a melodia cai nelas, o ouvido sente repouso, porque a nota 'pertence' ao acorde. As notas estranhas (segunda, quarta, sexta e seus equivalentes) são as tensões: elas criam atrito com o acorde e pedem movimento. A análise melódica consiste em classificar cada nota em um desses grupos."),
        tbl ({ "Nota sobre Dm7", "Intervalo", "Papel", "Sensação" }, {
            { "D", "fundamental", "nota do acorde", "repouso" },
            { "F", "terça menor", "nota do acorde", "repouso" },
            { "A", "quinta justa", "nota do acorde", "repouso" },
            { "C", "sétima menor", "nota do acorde", "repouso" },
            { "E", "nona", "tensão", "tensão suave" },
            { "B", "décima terceira", "tensão", "tensão" },
            { "G", "décima primeira", "tensão", "atrito (evitar)" },
        }),
        img ("m10_analise_melodica", "Sobre Dm7, cada nota da melodia tem um papel: repouso (nota do acorde) ou tensão (nota estranha)."),

        h ("Onde a nota cai muda tudo"),
        p (
            "Uma nota de tensão não é um erro por si só — ela é um erro quando cai no tempo forte e não resolve. A mesma nona (E sobre Dm7) soa linda se estiver na passagem e descer para a fundamental ou a terça; soa estranha se ficar parada no tempo forte. Por isso a análise melódica não olha só a nota, mas também a posição dela na frase e para onde ela vai."),
        b ("Tempo forte: prefira notas do acorde (repouso)."),
        b ("Passagem e contratempo: as tensões cabem, desde que resolvam."),
        b ("Tensão que resolve para uma nota do acorde soa intencional; tensão que não resolve soa erro."),
        aud ({ "D4", "F4", "A4", "C5" }, "Notas do acorde de Dm7 em sequência: todas soam como repouso. Ouça a estabilidade."),
        aud ({ "E4", "D4", "C4", "A3" }, "A nona (E) resolve para a fundamental (D): a tensão vira intenção. Ouça a resolução."),
        p (
            "O app treina exatamente essa escuta: ele reconhece as notas tocadas e verifica se a melodia repousa onde deve e resolve as tensões. Improvisar dentro dessa disciplina é o que separa o solo que 'fala' do solo que apenas toca notas."),

        h ("Analisando uma melodia por graus"),
        p (
            "Para analisar uma melodia, converta cada nota em um grau em relação ao acorde do momento. Uma nota que é a fundamental do acorde é o grau 1; a terça é o grau 3; a quinta, o grau 5; a sétima, o grau 7. Notas que não são do acorde aparecem como 2, 4, 6 ou 9, 11, 13. Escrever os graus enfileirados revela o desenho da melodia: se ela caminha por graus conjuntos, se salta entre notas do acorde, onde tensiona e onde repousa."),
        tbl ({ "Melodia", "Sobre o acorde", "Grau", "Papel" }, {
            { "F", "Dm7", "3", "repouso" },
            { "G", "Dm7", "4 (11)", "tensão" },
            { "A", "Dm7", "5", "repouso" },
            { "B", "Dm7", "6 (13)", "tensão" },
            { "C", "Dm7", "7", "repouso" },
            { "E", "Dm7", "2 (9)", "tensão" },
        }),
        c (
            "Escreva os graus embaixo das notas. O padrão que aparecer — subida por graus, arpejo, nota repetida — é a assinatura melódica da frase, e é o que você vai querer conservar quando reharmonizar."),

        h ("Melodia e harmonia: quem manda em quem"),
        p (
            "Há duas leituras possíveis de uma música: a melodia manda ou a harmonia manda. No repertório clássico e no jazz, a melodia costuma ser a voz principal e a harmonia existe para sustentá-la; no pop e no rock, muitas vezes a harmonia é fixa e a melodia se ajusta. A análise melódica decide qual é o caso: se a melodia tem notas fortes e definidas, a harmonia deve servi-la; se a melodia é simples e repetitiva, a harmonia pode variar mais. Saber quem manda é o que evita reharmonizações que 'brigam' com a melodia."),
        b ("Melodia definida: reharmonize sem mexer nas notas fortes dela."),
        b ("Melodia simples: você tem mais liberdade para mudar a harmonia embaixo."),
        b ("Nunca coloque uma nota forte da melodia em atrito não resolvido com o novo acorde."),
        img ("m10_verticalizacao", "A melodia A–G–F–E analisada e depois verticalizada: a harmonia nasce das próprias notas da melodia."),

        h ("A melodia revela a harmonia"),
        p (
            "Um exercício poderoso de análise é tentar deduzir a harmonia a partir da melodia. Se uma frase insiste na nota F e na nota A, é provável que exista um acorde que contenha essas notas — F7M, Dm7 ou Bb7M. A melodia, analisada por graus, sugere quais acordes 'cabem' embaixo dela. Esse raciocínio é exatamente o que sustenta a verticalização (tópico D) e a harmonia-alvo (tópico H): a melodia aponta o caminho da harmonia."),
        b ("Liste as notas fortes da melodia."),
        b ("Procure acordes que contenham essas notas como notas do acorde."),
        b ("Escolha entre os candidatos pela função que você quer dar à frase."),
        aud ({ "A4", "G4", "F4", "E4" }, "A melodia A–G–F–E: cada nota sugere um acorde. Ouça as notas e imagine a harmonia por baixo."),
        part ("m10_partitura_verticalizacao", { "A4", "G4", "F4", "E4" },
              "Partitura da melodia A–G–F–E. Ela será a base da verticalização no tópico D."),

        h ("Erros comuns na análise melódica"),
        p (
            "O erro mais comum é analisar a melodia isolada, sem o acorde. Uma nota só faz sentido em relação ao acorde que a sustenta. O segundo erro é tratar toda tensão como erro: a tensão é bem-vinda quando resolve. O terceiro é esquecer o tempo: a mesma nota de passagem no tempo fraco e no tempo forte muda de papel. A análise correta leva em conta a nota, o acorde e o momento."),
        b ("Analise a nota sempre contra o acorde do momento, nunca no vácuo."),
        b ("Distinga tensão resolvida (intenção) de tensão abandonada (erro)."),
        b ("Observe o tempo: a posição na frase muda o peso da nota."),
        c (
            "O app reforça essa disciplina: nos exercícios de improvisação, notas de tensão não resolvidas contam como erro (REQ-012). Treine resolver a tensão na nota do acorde seguinte."),

        h ("Do repouso à tensão: desenhando a frase"),
        p (
            "Toda boa melodia alterna repouso e tensão. Ela começa ou repousa numa nota do acorde, tensiona ao se afastar e volta a repousar na resolução. Esse vai-e-vem é o que dá respiração à frase. Analisar uma melodia é, no fundo, desenhar esse movimento: marcar onde ela respira (repouso) e onde ela segura o ar (tensão). É esse desenho que você vai querer reproduzir ao improvisar e conservar ao reharmonizar."),
        tbl ({ "Momento da frase", "Nota ideal", "Efeito" }, {
            { "início", "nota do acorde", "frase clara, firme" },
            { "meio", "tensão de passagem", "movimento, cor" },
            { "ápice", "tensão alta (9, 13)", "clímax" },
            { "fim", "nota do acorde", "resolução, repouso" },
        }),
        b ("Comece e termine em notas do acorde."),
        b ("Use as tensões no meio, resolvendo-as antes de parar."),
        b ("O ápice da frase combina com a tensão mais alta."),
        aud ({ "F4", "G4", "A4", "B4", "C5", "A4", "F4" },
             "Uma frase sobre Dm7: repousa, tensiona, atinge o ápice e resolve. Ouça o desenho."),

        h ("Analisando a melodia de uma música conhecida"),
        p (
            "Um bom treino de análise melódica é pegar uma melodia que você conhece e analisá-la nota a nota sobre a harmonia. Escolha um trecho curto, escreva os acordes e, embaixo de cada nota, escreva o grau dela em relação ao acorde. Você vai descobrir que as melodias bem-feitas quase sempre repousam nas notas do acorde nos tempos fortes e usam as tensões nas passagens. Ver isso numa melodia que você admira é a melhor aula de como escrever uma melodia que 'conversa' com a harmonia."),
        b ("Escolha uma melodia conhecida e um trecho curto."),
        b ("Escreva o grau de cada nota em relação ao acorde."),
        b ("Marque onde ela repousa e onde ela tensiona."),
        aud ({ "A4", "B4", "C5", "B4", "A4", "G4", "F4" },
             "Uma melodia que tensiona (B, C) e resolve (A, F): ouça como ela respira."),

        h ("Tensão boa e tensão ruim"),
        p (
            "Nem toda tensão é igual. A tensão boa é aquela que tem direção: ela aponta para uma resolução e chega lá. A tensão ruim é a que fica parada, sem resolver, criando a sensação de nota errada. A diferença está no movimento: a nona que resolve na fundamental é bonita; a nona que fica soando sozinha no fim da frase é estranha. Analisar a melodia é, em parte, distinguir essas duas tensões — e usar a boa a favor da música."),
        tbl ({ "Tensão", "Resolve para", "Resultado" }, {
            { "9ª (E sobre Dm7)", "fundamental ou 3ª", "tensão boa, com direção" },
            { "13ª (B sobre Dm7)", "5ª ou 7ª", "tensão boa" },
            { "11ª (G sobre Dm7)", "3ª (F)", "cuidado: atrito com a terça" },
            { "tensão parada no tempo forte", "nada", "soa como erro" },
        }),
        b ("A tensão precisa de direção: ela aponta e chega."),
        b ("A tensão parada, sem resolução, soa como nota errada."),
        b ("A 11ª sobre acorde menor pede cuidado (atrito com a terça)."),
        c (
            "O app aplica essa regra: nos exercícios de improvisação, a tensão não resolvida conta como erro (REQ-012). Treine resolver cada tensão na nota do acorde seguinte."),

        h ("Melodia, ritmo e respiração"),
        p (
            "A análise melódica também olha o ritmo. Uma melodia que só tem notas longas cansa; uma que só tem notas rápidas não respira. As boas melodias alternam movimento e repouso rítmico — uma frase de notas rápidas seguida de uma nota longa, ou um silêncio no lugar certo. Analisar a melodia inclui notar onde ela respira ritmicamente, porque esse desenho é tão importante quanto as notas escolhidas."),
        b ("Alterne movimento (notas rápidas) e repouso (notas longas)."),
        b ("Use silêncios: eles fazem parte da melodia."),
        b ("A respiração rítmica dá naturalidade à frase."),
        aud ({ "D4", "E4", "F4", "G4", "A4", "G4", "F4" },
             "Notas rápidas seguidas de uma nota longa: a frase ganha respiração. Ouça o desenho."),

        h ("Melodia e o ciclo de tensão e repouso"),
        p (
            "Toda música respira num ciclo de tensão e repouso. A análise melódica é a ferramenta que revela esse ciclo: onde a melodia tensiona, onde ela repousa, onde ela prepara a próxima tensão. Quando você entende o ciclo, você pode tocá-lo de propósito: tocar mais suave no repouso, mais intenso na tensão, e fazer a música 'respirar' junto. É esse controle que distingue um músico que apenas toca as notas certas de um músico que faz a música falar."),
        b ("Toda frase alterna tensão e repouso."),
        b ("Toque mais suave no repouso e mais intenso na tensão."),
        b ("Fazer a música respirar é controlar esse ciclo."),
        aud ({ "D4", "E4", "F4", "E4", "D4", "C4" },
             "Tensão (E, F) e repouso (D, C) alternando: ouça o ciclo respirando."),
        p (
            "Analisar a melodia é, portanto, um exercício de escuta atenta. Você aprende a ouvir cada nota em relação ao acorde, a perceber se ela repousa ou tensiona e a notar se a tensão resolve. Com o tempo, essa escuta se torna automática: você toca uma frase e já sabe onde ela respira e onde ela segura o ar. E é essa consciência que faz o improviso soar intencional, em vez de aleatório."),
        c (
            "Treine com o app: toque frases curtas sobre um acorde e verifique se as notas fortes caem nas notas do acorde. O retorno imediato acelera muito o aprendizado."),

        h ("Resumo do tópico"),
        b ("A análise melódica classifica cada nota como repouso (nota do acorde) ou tensão (nota estranha)."),
        b ("A posição na frase importa: a tensão precisa resolver."),
        b ("Converter a melodia em graus revela o desenho da frase."),
        b ("A melodia define o que a harmonia pode fazer; ela aponta os acordes possíveis."),
        b ("Improvisar é alternar repouso e tensão com intenção (REQ-011, REQ-012)."),
        part ("m10_partitura_modal", { "D4", "F4", "A4", "B4", "C5", "A4", "F4", "D4" },
              "Partitura de uma frase dórica sobre Dm7: repouso nas notas do acorde e tensão resolvida. Ouça o equilíbrio."),
    };
}

} // namespace cursomusica::content
