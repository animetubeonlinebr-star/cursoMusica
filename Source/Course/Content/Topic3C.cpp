#include "Course/Content/Topics.h"

// Topic 3C — Cifrado com divisao (Modulo 3, Etapa 3).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 3, bloco C).
namespace cursomusica::content
{

std::vector<ContentItem> topic3C()
{
    return {

        p (
            "Cifrar é descrever um acorde de forma compacta. A cifra diz qual acorde tocar, mas não diz como tocá-lo no tempo: essa parte é do ritmo. Quando a cifra e a divisão rítmica se encontram, nasce a levada. Este tópico ensina a ler a cifra junto com a divisão do compasso, transformando o símbolo em acompanhamento."),
        p (
            "O guitarrista que acompanha lê a cifra e decide a levada. A mesma progressão C – G – Am – F pode ser tocada em semínimas, colcheias ou com síncope, e o efeito muda por completo. Saber ler a cifra com a divisão é o que permite escolher a levada certa para cada música e cada estilo."),
        c (
            "Objetivo: ligar o acorde (cifra) ao tempo (divisão). A cifra sem divisão é um acorde parado; com divisão, é uma levada."),

        h ("Relembrando a cifra"),
        p (
            "A cifra usa letras para as notas (A a G) e símbolos para a qualidade do acorde. Um C é um acorde de Dó maior; Cm é Dó menor; C7 é Dó com sétima dominante; C7M é Dó com sétima maior. A barra indica a nota do baixo: C/E é Dó maior com Mi no baixo. Essas convenções vêm do módulo 1 e continuam valendo aqui."),
        tbl ({ "Cifra", "Significado", "Notas (exemplo)" }, {
            { "C", "Do maior", "Do - Mi - Sol" },
            { "Cm", "Do menor", "Do - Mib - Sol" },
            { "C7", "Do com setima dominante", "Do - Mi - Sol - Sib" },
            { "C7M", "Do com setima maior", "Do - Mi - Sol - Si" },
            { "C/E", "Do maior com Mi no baixo", "Mi (baixo) + Do - Mi - Sol" },
            { "C(9)", "Do maior com nona", "Do - Mi - Sol - Re" },
        }),
        b ("A letra diz a fundamental; o sufixo diz a qualidade."),
        b ("O número 7 indica sétima; 7M, sétima maior; m7, menor com sétima."),
        b ("A barra indica inversão: qual nota vai no baixo."),
        c (
            "Ler cifra é ler acorde. Mas a música só aparece quando a cifra ganha ritmo — e é aí que a divisão entra."),

        h ("Cifra com divisao: o acorde no tempo"),
        p (
            "Uma cifra sozinha não diz quando o acorde começa nem quanto ele dura. A divisão do compasso resolve isso. Se o compasso tem quatro tempos e há um acorde por compasso, você decide se toca o acorde inteiro no tempo 1, se repete o ataque em cada tempo ou se cria uma levada com síncope. A mesma cifra, dividida de formas diferentes, produz levadas diferentes."),
        tbl ({ "Divisao", "Como o acorde aparece", "Sensacao" }, {
            { "1 acorde por compasso", "ataque so no tempo 1", "amplo, sustentado" },
            { "1 acorde por tempo", "quatro ataques iguais", "marcado, direto" },
            { "2 acordes alternados", "C - G - C - G", "movimento, base" },
            { "com sincope", "ataque no contratempo", "balancado, groove" },
        }),
        b ("Acorde sustentado: o som dura o compasso inteiro."),
        b ("Acorde marcado: repete o ataque a cada tempo ou subdivisão."),
        b ("Acorde com síncope: o ataque cai entre os tempos."),
        img ("m3_cifrado_divisao", "A cifra e a divisão do compasso: como o acorde se reparte no tempo."),
        c (
            "A cifra é o 'o quê'; a divisão é o 'quando'. Toda levada nasce do encontro dos dois."),

        h ("Da cifra a levada: o passo a passo"),
        p (
            "Transformar uma cifra em levada tem um caminho claro. Primeiro identifique a progressão e a duração de cada acorde. Depois escolha a subdivisão (semínima, colcheia, síncope). Por fim, monte o desenho de ataques e teste com o metrônomo. Quanto mais você repete esse caminho, mais rápido reconhece a levada de uma música só de ouvir."),
        b ("1. Leia a progressão: C – G – Am – F, um acorde por compasso."),
        b ("2. Escolha a subdivisão: colcheias, por exemplo."),
        b ("3. Monte o desenho: ataques nos tempos e nos contratempos."),
        b ("4. Toque com o metrônomo e ajuste o alinhamento."),
        aud ({ "C4", "E4", "G4", "C4", "E4", "G4" }, "Arpejo de Dó maior: o acorde repartido em colcheias."),

        h ("Acordes com baixo em movimento"),
        p (
            "Um recurso muito usado no acompanhamento é mover o baixo enquanto o acorde se mantém. A cifra C/E diz que o baixo é Mi, mas o acorde continua sendo Dó maior. Alternar C e C/E cria um movimento interno que dá vida à levada sem mudar a harmonia. Esse recurso aparece muito na bossa, no choro e no pop."),
        b ("C/E: Dó maior com Mi no baixo."),
        b ("Alternar C e C/G cria movimento de baixo."),
        b ("O baixo em movimento enriquece a levada sem trocar o acorde."),
        c (
            "O baixo em movimento é a diferença entre um acompanhamento 'de acampamento' e um acompanhamento que respira."),

        h ("Ritmo de base por estilo"),
        p (
            "Cada estilo tem levadas típicas, e cada uma é uma divisão diferente da cifra. O rock marca os tempos fortes com acordes cheios; o samba usa síncope e abafamento; a bossa separa o baixo (polegar) dos acordes (dedos); o funk usa semicolcheias e notas abafadas. Conhecer a levada típica de cada estilo é ler a cifra com o corpo certo."),
        tbl ({ "Estilo", "Levada tipica", "Divisao" }, {
            { "Rock", "acordes marcados", "seminimas/colcheias" },
            { "Pop", "colcheias constantes", "colcheias" },
            { "Samba", "sincope + abafamento", "colcheias/semicolcheias" },
            { "Bossa", "polegar + dedos", "colcheias" },
            { "Funk", "semicolcheias + dead notes", "semicolcheias" },
        }),
        b ("O mesmo acorde soa diferente em cada estilo, por causa da levada."),
        b ("A levada é a assinatura rítmica do estilo."),
        b ("Estudar levadas é estudar a divisão característica de cada um."),

        h ("Cifra, harmonia e forma"),
        p (
            "Além do ritmo, a cifra organiza a harmonia da música. Ler uma sequência de cifras é entender a forma: onde está o repouso, onde está a tensão, para onde a música caminha. Uma progressão como C – Am – F – G cria uma expectativa que resolve no C. O ritmo reforça essa expectativa, dando mais ou menos ênfase a cada acorde."),
        b ("Repouso: acorde de tônica (I), estável."),
        b ("Tensão: dominante (V), pede resolução."),
        b ("Movimento: subdominante (IV), prepara a volta."),
        c (
            "Cifra lida com ritmo vira música: a harmonia diz o que, a divisão diz quando, e juntas dizem como a música caminha."),

        h ("Erros comuns ao ler cifra com divisao"),
        p (
            "O erro mais comum é tocar todos os acordes com a mesma levada, ignorando o estilo. Outro é perder o pulso ao trocar de acorde, porque a mão esquerda trava e arrasta a direita. E há quem leia a cifra 'por fora', sem ouvir o ritmo da música — o acompanhamento fica correto nas notas e errado na sensação."),
        b ("Tocar tudo com a mesma levada, sem ouvir o estilo."),
        b ("Travar o pulso na troca de acorde."),
        b ("Ignorar o baixo escrito na cifra (a barra)."),
        b ("Não deixar o acorde soar: abafar antes da hora."),
        c (
            "Dica: estude a troca de acorde separada do ritmo. Quando a mão esquerda troca sem hesitar, a direita mantém a levada firme."),

        h ("Como praticar cifra com divisao"),
        p (
            "Escolha uma progressão simples (C – G – Am – F), uma subdivisão e toque com o metrônomo. Varie a subdivisão sem trocar a progressão, e sinta como cada uma muda o caráter. Depois, acrescente o baixo em movimento e a síncope. Este módulo usa BPM meta 68, um andamento calmo que deixa claro cada ataque."),
        b ("Uma progressão, várias subdivisões."),
        b ("Metrônomo no pulso, contagem em voz alta."),
        b ("Troca de acorde lenta e limpa antes de acelerar."),
        b ("Grave e compare com o estilo que quer imitar."),
        part ("m3_partitura_cifrado", { "C4", "E4", "G4", "G4", "E4", "C4" },
              "Partitura: arpejo de Dó maior dividindo o compasso. Cada nota é um ataque."),

        h ("Resumo do topico"),
        b ("Cifra descreve o acorde; a divisão descreve como ele se distribui no tempo."),
        b ("Ler cifra com divisão é o que transforma o acorde em levada."),
        b ("Acorde sustentado, marcado ou sincopado: a escolha depende do estilo."),
        b ("O baixo em movimento (C/E, C/G) enriquece a levada sem trocar o acorde."),
        b ("A levada é a assinatura rítmica de cada estilo."),
        c (
            "Nos exercícios, você tocará progressões com a divisão pedida. O app reconhece os acordes e confere o alinhamento à grade do metrônomo."),

        h ("Lendo a cifra em tempo real"),
        p (
            "Acompanhar exige ler a cifra enquanto ela acontece. O segredo é antecipar: os olhos leem o próximo acorde antes de a mão chegar nele. Quem lê cifra com fluência olha um compasso à frente, prepara a troca e mantém o ritmo. Ler 'no atraso' — só quando o acorde já começou — é o que trava a levada."),
        b ("Olhe um compasso à frente do que está tocando."),
        b ("Prepare a forma do próximo acorde antes do tempo 1."),
        b ("Mantenha a levada da mão direita mesmo durante a troca."),
        c (
            "A leitura antecipada é o que separa o acompanhamento amador do profissional: a mão esquerda se move enquanto a direita continua o groove."),

        h ("Slash chords e conducao de baixo"),
        p (
            "Os slash chords (cifra com barra) são muito usados para criar uma linha de baixo. Uma sequência como C – C/B – Am – Am/G desce o baixo passo a passo, criando uma condução suave entre os acordes. É um recurso de arranjo: a harmonia permanece, mas o baixo caminha, dando movimento à levada."),
        tbl ({ "Cifra", "Baixo", "Efeito" }, {
            { "C", "Do", "repouso" },
            { "C/B", "Si", "conducao descendente" },
            { "Am", "La", "chegada" },
            { "Am/G", "Sol", "nova conducao" },
            { "F", "Fa", "subdominante" },
        }),
        b ("A barra indica a nota mais grave, não muda o acorde."),
        b ("Baixo em movimento cria uma melodia interna na levada."),
        b ("Muito comum em bossa, choro e pop de qualidade."),

        h ("O ritmo como assinatura do estilo"),
        p (
            "Dois guitarristas podem tocar a mesma progressão e soar completamente diferentes, porque a levada é a assinatura do estilo. O samba tem síncope e abafamento; o rock tem acordes marcados; a bossa tem o polegar no baixo e os dedos nas cordas agudas. Reconhecer a assinatura rítmica de cada estilo é o que permite acompanhar de verdade, e não apenas tocar as notas certas."),
        b ("Ouvir a levada antes de imitar: o ritmo vem primeiro."),
        b ("Cada estilo tem uma divisão característica e um acento típico."),
        b ("Tocar as notas certas com a levada errada soa errado."),
        c (
            "A frase 'o ritmo é o estilo' resume tudo: quando você acerta a levada, acerta o estilo, mesmo com harmonias simples."),

        h ("Cifra e forma: entendendo a musica inteira"),
        p (
            "Ler cifras em sequência é ler a forma da música. Uma progressão conta uma pequena história: sai do repouso, cria tensão e volta. O acompanhante que entende a forma sabe quando sustentar, quando empurrar e quando respira. Sem isso, a levada fica uniforme e a música perde o seu desenho no tempo."),
        b ("Repouso (tônica): o acorde que soa 'em casa'."),
        b ("Movimento (subdominante): o acorde que prepara."),
        b ("Tensão (dominante): o acorde que pede resolução."),
        b ("Cadência: o caminho de volta ao repouso."),
        c (
            "O ritmo reforça a forma: acentuar o tempo forte na tônica e empurrar na dominante faz a música caminhar. Acompanhar é, no fundo, contar essa história com o corpo."),

        h ("Estudando uma levada nova"),
        p (
            "Quando você quer aprender uma levada nova, o caminho é sempre o mesmo. Escute a levada várias vezes até conseguir cantar o ritmo. Depois leia a divisão e escreva os ataques. Em seguida toque lento com o metrônomo, uma parte por vez. Por fim, junte tudo e acelere gradualmente. Pular etapas é o que faz o aluno 'saber' a levada na cabeça mas não conseguir tocá-la."),
        b ("Escute até conseguir cantar o ritmo."),
        b ("Escreva os ataques (onde cada acorde entra)."),
        b ("Toque lento, por partes, com o metrônomo."),
        b ("Junte e acelere só quando estiver firme."),
        part ("m3_partitura_cifrado", { "C4", "E4", "G4", "G4", "E4", "C4" },
              "Ouça a partitura e conte os ataques: cada nota é uma divisão do acorde."),
    };
}

} // namespace cursomusica::content
