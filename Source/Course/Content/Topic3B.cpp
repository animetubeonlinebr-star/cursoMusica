#include "Course/Content/Topics.h"

// Topic 3B — Pulsacao e subdivisao (Modulo 3, Etapa 3).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 3, bloco B).
namespace cursomusica::content
{

std::vector<ContentItem> topic3B()
{
    return {

        p (
            "Toda música tem um pulso: uma batida regular que se repete e que o corpo reconhece sem pensar — o pé que bate sozinho. Sobre esse pulso, as notas se organizam em subdivisões. Entender pulso e subdivisão é entender por que a mesma sequência de notas soa diferente conforme o tempo em que ela é distribuída."),
        p (
            "Se a leitura rítmica (tópico A) ensinou a reconhecer as figuras, este tópico ensina a senti-las. Aqui você aprende a manter um pulso estável e a dividi-lo em duas, três ou quatro partes iguais. Essa divisão é o que dá movimento à levada e é o que o metrônomo mede quando avalia o seu alinhamento."),
        c (
            "Objetivo: sentir o pulso por dentro e saber subdividi-lo. Sem pulso estável, não existe groove; sem subdivisão, não existe levada."),

        h ("O pulso: a batida que nao para"),
        p (
            "O pulso é a unidade de tempo da música. Quando você bate o pé ao ouvir uma música, está marcando o pulso. Ele é constante e independente do que a melodia faz: pode haver muitas notas entre dois pulsos, ou nenhuma, e o pulso continua o mesmo. Manter esse pulso interno firme é a primeira habilidade de qualquer músico."),
        b ("O pulso é constante: não acelera nem atrasa."),
        b ("Bater o pé no pulso ajuda a internalizá-lo."),
        b ("O metrônomo é a versão externa e objetiva do pulso interno."),
        c (
            "Um erro muito comum é deixar o pulso 'seguir' a dificuldade: o aluno acelera nos trechos fáceis e trava nos difíceis. O metrônomo existe justamente para impedir isso."),

        h ("Subdivisao: dividindo o pulso"),
        p (
            "Subdividir é repartir cada pulso em partes iguais. A subdivisão binária divide o pulso em dois (colcheias) ou quatro (semicolcheias). A subdivisão ternária divide em três (tercinas). Cada nível de subdivisão multiplica a quantidade de notas que cabem no mesmo tempo, sem mudar o pulso."),
        tbl ({ "Subdivisao", "Partes por pulso", "Contagem em voz alta" }, {
            { "Seminima", "1", "1  2  3  4" },
            { "Colcheia", "2", "1 e 2 e 3 e 4 e" },
            { "Tercina", "3", "1 e a 2 e a 3 e a 4 e a" },
            { "Semicolcheia", "4", "1 e a e 2 e a e 3 e a e 4 e a e" },
        }),
        b ("Semínima: um ataque por pulso."),
        b ("Colcheia: dois ataques por pulso — a levada mais comum."),
        b ("Semicolcheia: quatro ataques por pulso — textura densa."),
        img ("m3_pulsacao_subdivisao", "O pulso fixo e seus níveis de subdivisão: cada nível dobra o número de notas."),
        c (
            "A subdivisão dobra a cada nível. É exatamente o que o metrônomo faz quando você escolhe semínima, colcheia ou semicolcheia: ele toca mais cliques por tempo, mas o pulso continua igual."),

        h ("Subdivisao binaria e ternaria"),
        p (
            "As duas subdivisões convivem na música, e escolher a certa muda o estilo. O rock, o pop e o samba usam subdivisão binária: o pulso se divide em dois ou quatro. O blues, o shuffle e a valsa usam subdivisão ternária: o pulso se divide em três. A sensação é completamente diferente."),
        tbl ({ "Estilo", "Subdivisao", "Sensacao" }, {
            { "Rock / pop", "binaria (colcheias)", "reta, com drive" },
            { "Funk", "binaria (semicolcheias)", "sincopada, densa" },
            { "Blues / shuffle", "ternaria (tercinas)", "balancada, 'swingada'" },
            { "Valsa", "ternaria (3 tempos)", "girando" },
        }),
        b ("Binária: '1 e 2 e' — divisão em partes iguais de dois."),
        b ("Ternária: '1 e a 2 e a' — divisão em três partes iguais."),
        b ("O mesmo lick pode ser tocado nas duas: muda o groove, não as notas."),
        aud ({ "C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5" }, "Oito colcheias: subdivisão binária, dois ataques por pulso."),
        aud ({ "C4", "C4", "C4", "D4", "D4", "D4", "E4", "E4", "E4" }, "Tercinas: subdivisão ternária, três ataques por pulso."),

        h ("Sentindo o pulso: o passo a passo"),
        p (
            "Sentir o pulso é uma habilidade treinável. Comece batendo o pé com o metrônomo, sem tocar nada. Depois, conte o pulso em voz alta. Só então acrescente a subdivisão, ainda sem tocar. Por fim, toque uma nota por pulso e vá adensando. Essa progressão evita o erro clássico de tentar tocar a levada antes de sentir o tempo."),
        b ("1. Bata o pé com o metrônomo, sem tocar."),
        b ("2. Conte o pulso em voz alta: 1, 2, 3, 4."),
        b ("3. Acrescente a subdivisão em voz alta: 1 e 2 e 3 e 4 e."),
        b ("4. Toque uma nota por pulso; depois duas; depois quatro."),
        c (
            "Se o pé sai do tempo, o pulso ainda não está firme. Volte um passo. A levada só existe quando o pulso é automático."),

        h ("Por que a subdivisao importa para o gate"),
        p (
            "O app avalia se a sua execução caiu na grade do metrônomo: a fração de notas alinhadas é o on_grid_ratio. Tocar na grade significa alinhar o ataque ao pulso ou a uma de suas subdivisões, dentro de uma tolerância. Quanto melhor você sente a subdivisão, maior o alinhamento — e mais fácil passa o gate."),
        b ("Tocar na grade = atacar exatamente no pulso ou na subdivisão."),
        b ("A tolerância cresce quanto mais lenta a subdivisão; aperta quando ela acelera."),
        b ("O alvo deste módulo é on_grid_ratio ≥ 0,77, na faixa de estudo (75–82%)."),
        img ("m3_compassos", "Compassos simples e compostos: quantos tempos e qual figura vale um tempo."),
        c (
            "A faixa de 75–82% existe porque exigir 90% de alinhamento engessa a execução. O pulso fica firme, mas a mão mantém a respiração natural."),

        h ("O pulso e o corpo"),
        p (
            "O pulso não é só um conceito mental: ele é corporal. Bater o pé, balançar a cabeça, respirar no tempo — tudo isso ajuda a internalizar o tempo. Músicos experientes sentem o pulso no corpo antes de pensar nele. Esse vínculo entre corpo e tempo é o que torna a execução natural em vez de mecânica."),
        b ("Marque o pulso com o pé, discretamente, mesmo tocando."),
        b ("Respire no tempo: frases longas precisam de ar."),
        b ("Evite prender a respiração nos trechos difíceis — isso rouba o tempo."),

        h ("Erros comuns com pulso e subdivisao"),
        p (
            "Os tropeços mais comuns são previsíveis. Acelerar nos trechos fáceis, atrasar nos difíceis, perder a subdivisão ao trocar de acorde ou confundir binário com ternário. Reconhecer cada um ajuda a corrigir antes que vire hábito."),
        b ("Acelerar nos trechos fáceis e travar nos difíceis."),
        b ("Perder a subdivisão quando a mão esquerda tem muito trabalho."),
        b ("Tocar binário onde a música pede ternário (ou o contrário)."),
        b ("Contar a subdivisão 'por fora', sem que ela apareça no som."),
        c (
            "Dica prática: toque apenas o pulso com a mão direita e deixe a esquerda trabalhar. Quando o pulso estiver firme, acrescente a subdivisão. Separar as mãos no estudo acelera muito a consolidação."),

        h ("Como praticar pulso e subdivisao"),
        p (
            "Um bom treino combina o metrônomo, a contagem em voz alta e a execução de uma nota simples. Comece em 60 BPM com semínimas, depois colcheias, depois semicolcheias. Só quando o alinhamento estiver firme, acrescente acordes e levadas. Este módulo tem BPM meta 68: um andamento calmo, ideal para consolidar o pulso antes de acelerar."),
        b ("Metrônomo em 60–68 BPM, começando lento."),
        b ("Uma nota por pulso, depois duas, depois quatro."),
        b ("Conte em voz alta enquanto toca."),
        b ("Aumente o BPM só quando o alinhamento estiver consistente."),
        c (
            "O pulso é a fundação de todo o resto. Um guitarrista com pulso firme soa profissional mesmo tocando coisas simples; sem pulso, até o difícil soa amador."),

        h ("Resumo do topico"),
        b ("Pulso é a batida regular e constante; subdivisão é reparti-lo em partes iguais."),
        b ("Binária divide em 2 ou 4; ternária divide em 3."),
        b ("Cada nível de subdivisão dobra as notas sem mudar o pulso."),
        b ("Tocar na grade é alinhar o ataque ao pulso ou à subdivisão (on_grid_ratio)."),
        b ("O pulso se sente no corpo: pé, cabeça e respiração ajudam a mantê-lo."),
        c (
            "Nos exercícios, toque na grade do metrônomo mantendo o pulso firme. O app mede o alinhamento e confere se a subdivisão está estável."),

        h ("Tempo forte e tempo fraco"),
        p (
            "Dentro de um compasso, os tempos não têm todos o mesmo peso. Em 4/4, o primeiro tempo é forte, o segundo fraco, o terceiro meio-forte e o quarto fraco. Essa hierarquia dá direção à música: o tempo forte sustenta e o fraco empurra para o próximo. Sentir essa diferença é o que faz a levada 'andar'."),
        tbl ({ "Tempo (4/4)", "Peso", "Papel" }, {
            { "1", "forte", "sustenta o compasso" },
            { "2", "fraco", "responde" },
            { "3", "meio-forte", "reafirma" },
            { "4", "fraco", "empurra para o proximo" },
        }),
        b ("Marcar o tempo forte dá estabilidade; o fraco dá impulso."),
        b ("O contratempo (a subdivisão entre dois tempos) é onde mora o groove."),
        b ("Acentuar o contratempo é a marca do samba, do funk e da bossa."),
        c (
            "Repare: acentuar o tempo fraco ou o contratempo não é 'tocar errado'. É a escolha rítmica que define o estilo."),

        h ("Subdivisao e sincope"),
        p (
            "Quando o ataque acontece no contratempo, entre dois pulsos, a música fica sincopada. A síncope é o coração de boa parte da música brasileira: samba, bossa e baião vivem de acentos fora do tempo forte. Subdividir bem é o que permite tocar síncope sem perder o pulso."),
        b ("Síncope: ataque no contratempo, com prolongamento sobre o tempo forte."),
        b ("Contratempo: a subdivisão 'entre' dois pulsos."),
        b ("Sem subdivisão interna, a síncope vira atraso."),
        aud ({ "C4", "E4", "C4", "E4", "C4", "E4", "C4", "E4" }, "Colcheias alternadas: o ataque no 'e' é o contratempo."),

        h ("Contando com o metronomo"),
        p (
            "O metrônomo pode marcar o pulso ou a subdivisão. Quando marca só o pulso, você é quem subdivide por dentro. Quando marca a subdivisão, ele ajuda a alinhar os ataques mais rápidos. Treine as duas formas: a primeira desenvolve o relógio interno; a segunda ajuda a acertar a grade quando a levada é densa."),
        b ("Metrônomo no pulso: você subdivide mentalmente."),
        b ("Metrônomo na subdivisão: alinha cada ataque."),
        b ("Alterne as duas para não ficar dependente de nenhuma."),
        c (
            "O objetivo final é dispensar o metrônomo: o pulso passa a vir de dentro. O metrônomo é uma muleta de estudo, não de performance."),

        h ("Aplicando na guitarra"),
        p (
            "Na guitarra, o pulso vive na mão direita e a subdivisão vive no ataque. Tocar o pulso com a palheta e subdividir com os dedos, ou alternar palhetada para marcar a subdivisão, são técnicas que ligam o corpo ao tempo. A mão esquerda não deve comandar o tempo: ela executa, enquanto a direita mantém o relógio."),
        b ("A mão direita marca o tempo; a esquerda só executa."),
        b ("Palhetada alternada facilita subdividir em colcheias e semicolcheias."),
        b ("Palm mute e abafamento reforçam a percepção do pulso."),
        part ("m3_partitura_subdivisao", { "C4", "D4", "E4", "F4", "G4", "F4", "E4", "D4" },
              "Partitura: escala em Dó, um passo por pulso. Toque alinhado ao metrônomo."),
    };
}

} // namespace cursomusica::content
