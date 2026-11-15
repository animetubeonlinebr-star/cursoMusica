#include "Course/Content/Topics.h"

// Topic 3A — Leitura ritmica e convencoes de escrita (Modulo 3, Etapa 3).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 3, bloco A).
namespace cursomusica::content
{

std::vector<ContentItem> topic3A()
{
    return {

        p (
            "Ritmo é a organização do som no tempo. Se a melodia diz quais notas tocar e a harmonia diz quais soam juntas, o ritmo diz quando cada coisa acontece — e por quanto tempo. Um guitarrista pode acertar todas as notas e ainda soar errado se o ritmo não estiver firme; por isso este módulo começa pela leitura rítmica."),
        p (
            "Ler ritmo é traduzir um desenho escrito em uma sequência de ataques no tempo certo. Toda partitura carrega duas informações ao mesmo tempo: a altura (qual nota) e a duração (quanto tempo ela dura). Neste tópico você aprende a segunda: as figuras, seus valores, os silêncios e as convenções que a escrita usa para representar o tempo."),
        c (
            "Objetivo do módulo: desenvolver a compreensão rítmica e a capacidade de acompanhar diferentes estilos. A leitura é a ferramenta que transforma o que você ouve em algo que você consegue reproduzir e repetir."),

        h ("O que é pulso, tempo e compasso"),
        p (
            "Antes das figuras, três conceitos sustentam tudo. O pulso é a batida constante que você sente ao ouvir uma música — é o que o metrônomo marca. O tempo é cada uma dessas batidas contadas. O compasso é um grupo de tempos que se repete, separado por barras verticais na partitura."),
        b ("Pulso: a batida regular, sentida no pé ou no metrônomo."),
        b ("Tempo: cada batida contada (1, 2, 3, 4)."),
        b ("Compasso: o agrupamento que se repete (o 4/4 tem quatro tempos)."),
        img ("m3_leitura_ritmica", "As figuras rítmicas, seus valores em tempos e as sílabas de contagem."),
        c (
            "Sentir o pulso é a base de tudo. Sem pulso interno, nenhuma figura faz sentido: você lê os símbolos, mas não sabe onde encaixá-los no tempo."),

        h ("As figuras e seus valores"),
        p (
            "A escrita representa a duração por meio de figuras. Cada figura vale metade da anterior: a semibreve vale quatro tempos, a mínima vale dois, a semínima vale um, a colcheia vale meio e a semicolcheia vale um quarto de tempo. Essa relação de metade é o coração da leitura rítmica."),
        tbl ({ "Figura", "Valor em tempos (4/4)", "Silaba ritmica" }, {
            { "Semibreve", "4 tempos", "TA-A-A-A" },
            { "Minima", "2 tempos", "TA-A" },
            { "Seminima", "1 tempo", "TA" },
            { "Colcheia", "1/2 tempo", "TA-KI" },
            { "Semicolcheia", "1/4 tempo", "TA-KI-TA-KI" },
        }),
        b ("Semibreve: 4 tempos (o compasso 4/4 inteiro)."),
        b ("Mínima: 2 tempos; semínima: 1 tempo."),
        b ("Colcheia: 1/2 tempo; semicolcheia: 1/4 tempo."),
        c (
            "Para cada figura existe uma pausa de mesmo valor: o silêncio também é música, e ler a pausa é tão importante quanto ler a nota."),

        h ("Pausas e silencios"),
        p (
            "A música não é feita só de sons: os silêncios organizam a frase e criam respiração. Cada figura tem uma pausa correspondente, com o mesmo valor. Uma pausa de semínima ocupa um tempo inteiro em silêncio; uma pausa de colcheia ocupa meio tempo. Ignorar a pausa é um dos erros mais comuns de quem está começando a ler."),
        b ("Pausa de semibreve: um compasso 4/4 inteiro em silêncio."),
        b ("Pausa de mínima: dois tempos; de semínima: um tempo."),
        b ("Pausa de colcheia: meio tempo — o famoso 'espaço' entre as notas."),
        c (
            "Tocar a pausa corretamente é o que faz a levada 'respirar'. Uma levada sem pausas soa corrida e sem groove."),

        h ("Ponto de aumento e ligadura"),
        p (
            "Dois sinais ampliam a duração das notas. O ponto de aumento acrescenta metade do valor da figura: uma mínima pontuada vale dois tempos mais um (três tempos). A ligadura une duas notas de mesma altura, somando suas durações: uma semínima ligada a uma colcheia vale um tempo e meio."),
        tbl ({ "Sinal", "O que faz", "Exemplo" }, {
            { "Ponto de aumento", "acrescenta metade do valor", "minima pontuada = 3 tempos" },
            { "Ligadura de valor", "soma as duracoes", "seminima + colcheia = 1,5 tempo" },
            { "Ligadura de expressao", "une notas diferentes (legato)", "soa sem novo ataque" },
        }),
        c (
            "Ligadura de valor une a mesma nota; ligadura de expressão une notas diferentes para soar suave. Não confunda as duas."),

        h ("Convencoes de escrita do ritmo"),
        p (
            "A partitura organiza o tempo com algumas convenções fixas. As barras de compasso separam os grupos de tempos. A fórmula de compasso, no início, diz quantos tempos há e qual figura vale um tempo. As hastes das notas (colcheias, semicolcheias) podem ser ligadas em grupos que mostram a subdivisão."),
        b ("Barra de compasso: separa um compasso do seguinte."),
        b ("Formula de compasso (ex.: 4/4): em cima, quantos tempos; embaixo, a figura que vale 1 tempo."),
        b ("Hastes agrupadas: mostram como as colcheias se agrupam dentro do tempo."),
        img ("m3_pulsacao_subdivisao", "O pulso e a subdivisão: cada nível dobra a quantidade de notas por tempo."),
        c (
            "Agrupar as hastes é uma convenção visual: mostra ao leitor onde cada tempo começa e termina, o que facilita muito a leitura."),

        h ("Leitura a primeira vista do ritmo"),
        p (
            "Ler ritmo a primeira vista é uma habilidade separada de ler as notas. O segredo é não ler nota por nota: você lê grupos. Ao ver quatro colcheias, você já sabe que são quatro ataques em dois tempos; ao ver uma semínima seguida de duas colcheias, você reconhece o desenho como um todo."),
        b ("Leia o compasso em blocos de tempo, não nota por nota."),
        b ("Conte em voz alta (TÁ, TÁ-KI) enquanto lê."),
        b ("Bata o pé no pulso para manter a referência."),
        c (
            "Contar em voz alta antes de tocar é a técnica mais eficaz para ler ritmo. O que você fala, a mão executa."),

        h ("Como isso aparece na guitarra"),
        p (
            "Na guitarra, a leitura rítmica aparece na levada da mão direita: as figuras dizem quando a palheta ou os dedos atacam as cordas. Um mesmo acorde pode ser tocado em semínimas, colcheias ou semicolcheias, e o efeito muda completamente. A partitura é o mapa do ataque."),
        b ("Semínimas: quatro ataques por compasso 4/4 — som amplo e estável."),
        b ("Colcheias: oito ataques — movimento, levada típica de rock e pop."),
        b ("Semicolcheias: dezesseis ataques — textura densa, funk e samba."),
        part ("m3_partitura_leitura", { "C4", "C4", "D4", "E4" },
              "Partitura de leitura rítmica em Dó. Contar e tocar exatamente o que está escrito."),

        h ("Do simbolo ao som"),
        p (
            "O objetivo final da leitura rítmica é transformar símbolos em som sem hesitação. Isso exige que você reconheça a figura e saiba, na hora, quanto ela dura em relação ao pulso. Treine com exemplos curtos, sempre com o metrônomo ligado, até que a leitura se torne automática."),
        aud ({ "C4", "C4", "C4", "C4" }, "Quatro semínimas: um ataque por tempo, pulso firme."),
        aud ({ "C4", "E4", "C4", "E4", "C4", "E4", "C4", "E4" }, "Colcheias alternadas: dois ataques por tempo."),
        b ("Comece lento: a precisão vem antes da velocidade."),
        b ("Leia com o metrônomo: o pulso é a régua do ritmo."),
        b ("Aumente o andamento só quando acertar sem hesitar."),

        h ("Contando em voz alta: a tecnica que resolve"),
        p (
            "Existe uma técnica simples que resolve a maior parte das dificuldades de leitura: contar em voz alta. Antes de tocar, fale o ritmo. Ao falar, você separa o pulso da subdivisão e percebe onde cada ataque cai. Só depois leve a mão ao instrumento, mantendo a contagem. O que a boca já sabe, a mão repete com muito mais facilidade."),
        b ("Fale o pulso primeiro: 1, 2, 3, 4."),
        b ("Acrescente a subdivisão: 1 e 2 e 3 e 4 e (TÁ-KI)."),
        b ("Só então toque, mantendo a contagem em voz alta."),
        c (
            "Se você não consegue falar o ritmo, não vai conseguir tocar. Falar é o teste mais barato e mais rápido de que a leitura foi entendida."),

        h ("Andamento: a velocidade do pulso"),
        p (
            "O andamento é a velocidade com que o pulso bate, medido em batidas por minuto (BPM). O mesmo compasso pode ser tocado lento ou rápido sem que as figuras mudem: o que muda é quantas batidas cabem em um minuto. Este módulo tem BPM meta de 68, um andamento tranquilo, próprio para consolidar a leitura antes de acelerar."),
        tbl ({ "Andamento", "BPM aproximado", "Uso tipico" }, {
            { "Largo / Adagio", "50 a 70", "estudo, leitura lenta" },
            { "Andante / Moderato", "76 a 108", "levadas de estudo" },
            { "Allegro", "120 a 156", "rock, pop, samba" },
            { "Presto", "168 a 200", "virtuosismo, metal" },
        }),
        b ("Andamento lento: mais tempo para pensar cada figura."),
        b ("Andamento rápido: exige leitura automática e mão relaxada."),
        b ("O metrônomo é a referência objetiva: sem ele, o andamento 'escorrega'."),
        c (
            "A regra de ouro do estudo: toque na velocidade em que você acerta tudo. Aumentar o andamento antes da hora só consolida o erro."),

        h ("Erros comuns na leitura rítmica"),
        p (
            "Quem está começando comete alguns erros previsíveis. Reconhecê-los acelera o progresso. O mais comum é 'esticar' as notas curtas e 'encurtar' as longas, porque a mão tende a tocar no ritmo que já conhece, não no que está escrito."),
        b ("Tocar todas as figuras com o mesmo valor — não distinguir semínima de colcheia."),
        b ("Ignorar as pausas e emendar tudo sem respiro."),
        b ("Perder o pulso ao encontrar figuras mais rápidas."),
        c (
            "Dica: marque com o pé apenas o pulso (os tempos) e conte a subdivisão em voz alta. Assim você separa o que é pulso do que é subdivisão."),

        h ("Resumo do topico"),
        b ("Ritmo é a organização do som no tempo; pulso, tempo e compasso sustentam a leitura."),
        b ("Cada figura vale metade da anterior: semibreve, mínima, semínima, colcheia, semicolcheia."),
        b ("Pausas têm o mesmo valor das figuras; o ponto acrescenta metade; a ligadura soma durações."),
        b ("Ler ritmo é ler grupos de ataques, contando em voz alta com o metrônomo."),
        b ("Na guitarra, as figuras definem quando a mão direita ataca as cordas."),
        c (
            "Nos exercícios deste tópico, você vai contar as figuras e tocar na grade do metrônomo. O app mede o alinhamento (on_grid_ratio) e confere se o ataque caiu no tempo certo."),

        h ("Subdivisao binaria e ternaria"),
        p (
            "Existem duas formas de dividir o pulso. A subdivisão binária divide cada tempo em duas, quatro ou oito partes iguais: são as colcheias e semicolcheias. A subdivisão ternária divide cada tempo em três partes iguais: são as tercinas. Reconhecer qual das duas a música usa é essencial, porque a sensação rítmica muda completamente."),
        tbl ({ "Subdivisao", "Partes por tempo", "Exemplo" }, {
            { "Binaria", "2 (colcheias)", "rock, pop, samba" },
            { "Binaria", "4 (semicolcheias)", "funk, baião" },
            { "Ternaria", "3 (tercinas)", "blues, shuffle, valsa" },
            { "Ternaria", "6 (sextinas)", "baladas, baião lento" },
        }),
        b ("Binária: conta-se '1 e 2 e 3 e 4 e'."),
        b ("Ternária: conta-se '1 e a 2 e a' (a tercina)."),
        b ("Trocar a subdivisão no meio da música é uma escolha de estilo, não um erro."),
        c (
            "O blues e o shuffle usam subdivisão ternária: sem entender isso, o aluno 'endireita' o groove e a levada perde o balanço."),

        h ("Como praticar a leitura"),
        p (
            "A leitura rítmica se aprende com repetição curta e frequente. Escolha um compasso, conte-o em voz alta, toque-o devagar com o metrônomo e só depois aumente o andamento. Cinco minutos por dia rendem mais do que uma hora uma vez por semana, porque a leitura é uma habilidade motora que precisa de consolidação diária."),
        b ("Comece com um compasso; só avance quando ele sair limpo."),
        b ("Use o metrônomo em andamento lento antes de acelerar."),
        b ("Varie o material: leia ritmos que você nunca viu, não só os que já conhece."),
        b ("Grave a execução e compare com o que está escrito."),
        c (
            "A leitura é a ponte entre ouvir e reproduzir. Quanto mais automática ela for, mais rápido você aprende qualquer levada nova — e é isso que este módulo entrega."),
    };
}

} // namespace cursomusica::content
