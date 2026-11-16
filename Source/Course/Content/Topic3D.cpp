#include "Course/Content/Topics.h"

// Topic 3D — Celulas ritmicas e acentuacoes (Modulo 3, Etapa 3).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 3, bloco D).
namespace cursomusica::content
{

std::vector<ContentItem> topic3D()
{
    return {

        p (
            "Uma célula rítmica é um pequeno desenho de ataques que se repete. Em vez de inventar cada ataque do zero, o músico usa células: combinações de notas e pausas que já têm um caráter e que se encaixam no compasso. Aprender células é aprender o vocabulário do ritmo — com elas você constrói qualquer levada."),
        p (
            "Sobre as células atuam as acentuações: algumas notas soam mais fortes que outras. Acentuar é dar relevo a um tempo ou a um contratempo, e é o que faz uma levada soar viva em vez de mecânica. Neste tópico você aprende a reconhecer, criar e tocar células, e a acentuá-las para dar groove ao acompanhamento."),
        c (
            "Objetivo: montar levadas a partir de células rítmicas e dar-lhes relevo com acentos. A célula dá o desenho; o acento dá a vida."),

        h ("O que e uma celula ritmica"),
        p (
            "Uma célula rítmica é um padrão curto — normalmente de um ou dois tempos — que se repete ao longo do compasso. Ela combina figuras e pausas. Pense nela como um 'tijolo': em vez de tocar cada tempo isoladamente, você encaixa tijolos que formam a parede do acompanhamento. Quanto mais células você domina, mais rápido monta uma levada."),
        b ("Célula de semínimas: TA TA TA TA — um ataque por tempo."),
        b ("Célula de colcheias: TA-KI TA-KI TA-KI TA-KI — dois ataques por tempo."),
        b ("Célula de rock: TA (TA-KI) TA (TA-KI) — tempo forte seguido de duas colcheias."),
        b ("Célula de samba: (TA-KI) TA (TA-KI) — síncope com ataques no contratempo."),
        img ("m3_celulas_ritmicas", "Células rítmicas de acompanhamento: desenhos que se repetem no compasso."),
        c (
            "Repetir uma célula mantendo o pulso firme é o que cria o groove. A repetição não é preguiça: é o que faz o ouvido reconhecer o padrão."),

        h ("Montando levadas com celulas"),
        p (
            "Com duas ou três células você monta praticamente qualquer levada de acompanhamento. O processo é simples: escolha a subdivisão (colcheias, semicolcheias), escolha as células e combine-as em um ciclo que caiba no compasso. Depois, toque o ciclo repetidamente com o metrônomo até virar automático."),
        tbl ({ "Celula", "Contagem", "Onde aparece" }, {
            { "Semininas", "TA TA TA TA", "rock lento, balada" },
            { "Colcheias", "TA-KI TA-KI TA-KI TA-KI", "pop, rock" },
            { "Tempo + duas colcheias", "TA (TA-KI) TA (TA-KI)", "rock, reggae" },
            { "Sincope de samba", "(TA-KI) TA (TA-KI)", "samba, bossa" },
            { "Semicolcheias funk", "TA-KI-TA-KI TA-KI-TA-KI", "funk, soul" },
        }),
        b ("Combine células em um ciclo que caiba no compasso."),
        b ("Mantenha o pulso firme enquanto repete o ciclo."),
        b ("Varie a célula no fim do ciclo para criar 'respostas'."),
        c (
            "Um truque de composição: use a mesma célula para o acompanhamento e, no fim da frase, troque-a por outra. Isso cria um 'call and response' que prende o ouvido."),

        h ("Acentuacoes: dando relevo ao ataque"),
        p (
            "Acentuar é tocar uma nota mais forte que as outras. Na partitura, o acento é indicado por um sinal (>). No acompanhamento, acentuar certos tempos ou contratempos dá o caráter da levada. Um mesmo padrão de notas soa completamente diferente conforme os acentos: eles são o 'tempero' do ritmo."),
        tbl ({ "Acento em...", "Efeito", "Estilo tipico" }, {
            { "tempos fortes (1 e 3)", "estabilidade, marcha", "rock, marcha" },
            { "tempos fracos (2 e 4)", "impulso, 'backbeat'", "pop, soul" },
            { "contratempo (o 'e')", "sincope, groove", "samba, funk" },
            { "grupos de 3", "balanco ternario", "blues, shuffle" },
        }),
        b ("Acento no tempo forte: som pesado e estável."),
        b ("Acento no tempo fraco (2 e 4): sensação de empurrão."),
        b ("Acento no contratempo: síncope, a marca do groove brasileiro."),
        img ("m3_acentuacoes", "Onde o ataque fica forte: tempos fortes, fracos e contratempos."),
        c (
            "No samba e no funk, o acento cai no contratempo — o 'e' do tempo. É o que dá o balanço característico desses estilos."),

        h ("Celulas com pausas e abafamento"),
        p (
            "As células mais interessantes usam pausas e abafamentos. Em vez de tocar todas as subdivisões, você deixa algumas em silêncio (pausa) ou as abafa (dead note). O funk explora isso à exaustão: alterna acordes curtos com notas abafadas que soam como percussão. O silêncio, dentro da célula, é tão importante quanto o som."),
        b ("Pausa: um ataque que não acontece, deixando espaço."),
        b ("Dead note (abafada): som percussivo, sem altura definida."),
        b ("Alternar som e silêncio é o que dá 'respiração' à levada."),
        aud ({ "C4", "E4", "C4", "E4", "C4", "E4", "C4", "E4" }, "Colcheias com acento no contratempo: o groove do samba."),

        h ("Do desenho ao groove"),
        p (
            "Groove é a sensação que nasce da combinação entre a célula e o acento, tocados com o pulso firme. Duas pessoas podem tocar a mesma célula e uma soar mecânica e a outra soar viva: a diferença está no acento, na intensidade e na respiração. Trabalhar o groove é trabalhar esses detalhes até eles virarem hábito."),
        b ("O groove nasce da repetição com intenção."),
        b ("Acento e dinâmica criam o relevo."),
        b ("A respiração (pausas) evita que a levada fique corrida."),
        c (
            "Tocar a célula certa com o acento certo vale mais do que tocar muitas notas. O groove mora no detalhe, não na quantidade."),

        h ("Erros comuns com celulas e acentos"),
        p (
            "Os erros mais frequentes são perder o pulso ao repetir a célula, acentuar sempre no mesmo lugar por hábito e ignorar as pausas. Outro erro comum é tocar o acento 'por força' e não por intenção: o acento não é bater mais forte, é dar relevo, mantendo o pulso estável."),
        b ("Perder o pulso ao repetir a célula várias vezes."),
        b ("Acentuar sempre igual, sem variar o relevo."),
        b ("Ignorar as pausas e emendar tudo."),
        b ("Acentuar 'por força', desalinhando o tempo."),
        c (
            "Dica: estude a célula em andamento lento, exagerando o acento. Depois, reduza o exagero até o acento ficar natural, sem perder o pulso."),

        h ("Como praticar celulas e acentos"),
        p (
            "O treino combina metrônomo, contagem em voz alta e repetição. Escolha uma célula, conte-a, toque-a em ciclo até ficar firme e só então acrescente o acento. Varie as células sem parar o pulso. Este módulo usa BPM meta 68: um andamento calmo, ideal para consolidar o desenho antes de acelerar."),
        b ("Uma célula por vez, em ciclo, com metrônomo."),
        b ("Conte em voz alta enquanto repete."),
        b ("Acrescente o acento só quando o desenho estiver firme."),
        b ("Varie as células mantendo o pulso."),
        part ("m3_partitura_celula", { "C4", "E4", "G4", "E4" },
              "Partitura: célula de acompanhamento em Dó maior. Repita o desenho na grade."),

        h ("Resumo do topico"),
        b ("Célula rítmica é um desenho curto de ataques que se repete."),
        b ("Combinando células, você monta qualquer levada."),
        b ("Acentuar é dar relevo: tempo forte, fraco ou contratempo."),
        b ("Pausas e abafamentos dão respiração e percussão à célula."),
        b ("O groove nasce da célula + acento + pulso firme."),
        c (
            "Nos exercícios, você tocará células na grade do metrônomo. O app mede o alinhamento e confere se o desenho se manteve estável."),

        h ("Vocabulario de celulas por estilo"),
        p (
            "Cada estilo tem um repertório de células que o define. Conhecer essas células é reconhecer o estilo de ouvido e saber reproduzi-lo. Ao estudar um estilo novo, comece pelas suas células mais típicas: elas dão o sotaque imediatamente. A partir delas, você acrescenta variações sem perder a identidade."),
        tbl ({ "Estilo", "Celula tipica", "Acento" }, {
            { "Rock", "tempo + duas colcheias", "tempos 1 e 3" },
            { "Pop", "colcheias constantes", "tempos 2 e 4 (backbeat)" },
            { "Reggae", "colcheias no contratempo", "contratempo" },
            { "Samba", "sincope com abafamento", "contratempo" },
            { "Baião", "baixo alternado + acorde", "padrao de baião" },
            { "Blues", "tercinas e shuffle", "grupos de 3" },
        }),
        b ("Comece pela célula mais típica de cada estilo."),
        b ("Acrescente variações sem perder o sotaque."),
        b ("O acento é o que identifica o estilo de imediato."),
        c (
            "Uma boa forma de treinar estilos é tocar a mesma progressão (C – G – Am – F) em células de estilos diferentes. A harmonia não muda; o sotaque, sim."),

        h ("Criando suas proprias celulas"),
        p (
            "Depois de dominar as células tradicionais, você pode criar as suas. O caminho é combinar figuras e pausas em um desenho que caiba no compasso e repeti-lo. Boas células têm um equilíbrio entre som e silêncio, e um acento claro. Criar células é o primeiro passo da composição rítmica: muitas músicas nascem de um riff de acompanhamento."),
        b ("Escolha a subdivisão base (colcheias, semicolcheias)."),
        b ("Distribua ataques e pausas em um ciclo de um ou dois compassos."),
        b ("Defina onde caem os acentos."),
        b ("Teste com o metrônomo e ajuste o que 'corre' demais."),
        c (
            "Riffs famosos do rock nada mais são do que células rítmicas repetidas. Compor um riff é, muitas vezes, achar uma célula que gruda no ouvido."),

        h ("Dinamica dentro da celula"),
        p (
            "Além do acento, a dinâmica geral da célula importa. Uma levada pode começar mais baixa e crescer, ou alternar forte e fraco para criar tensão e relaxamento. Trabalhar a dinâmica é o que separa um acompanhamento plano de um acompanhamento expressivo. O volume não é enfeite: é parte da música."),
        b ("Crescer e diminuir dentro da repetição cria movimento."),
        b ("Alternar forte e fraco dá relevo às frases."),
        b ("A dinâmica deve acompanhar a forma da música, não competir com ela."),
        aud ({ "C4", "E4", "G4", "E4", "C4", "E4", "G4", "C5" }, "Célula em Dó maior: repita e varie a intensidade para sentir o groove."),

        h ("Aplicando a celula a um acorde real"),
        p (
            "Na guitarra, a célula rítmica é aplicada a um acorde. Você escolhe a forma do acorde, mantém o pulso na mão direita e executa o desenho de ataques. A mão esquerda só precisa segurar o acorde; a direita faz o ritmo. Separar as duas funções é o que permite tocar células complexas sem perder o tempo."),
        b ("Escolha uma forma de acorde que você domine."),
        b ("Mantenha o pulso na mão direita e execute a célula."),
        b ("A mão esquerda segura; a direita faz o ritmo."),
        part ("m3_partitura_celula", { "C4", "E4", "G4", "E4" },
              "Partitura: célula de acompanhamento. Toque o desenho na grade, sem perder o pulso."),

        h ("Do tempo ao contratempo"),
        p (
            "A maioria dos iniciantes toca somente nos tempos. O salto de qualidade acontece quando o músico aprende a tocar no contratempo — a subdivisão entre dois tempos. As células com contratempo são as que soam 'modernas' e sincopadas, porque deslocam o ataque do lugar óbvio. É o contratempo que dá ao samba, ao funk e ao reggae o seu balanço característico."),
        tbl ({ "Ataque em...", "Como contar", "Carater" }, {
            { "tempo", "1, 2, 3, 4", "previsivel, marcado" },
            { "contratempo simples", "1 e 2 e 3 e 4 e", "sincopado" },
            { "contratempo de semicolcheia", "1 e a e 2 e a e", "funk, denso" },
            { "contratempo com pausa", "( ) e ( ) e", "reggae, ska" },
        }),
        b ("Contratempo: o ataque entre dois tempos."),
        b ("Células com contratempo soam sincopadas."),
        b ("O reggae toca quase tudo no contratempo."),
        c (
            "Estudar o contratempo é estudar a síncope. Sem ele, o acompanhamento fica 'quadrado' — correto, mas sem groove."),

        h ("Celula, pulso e respiracao"),
        p (
            "Repetir uma célula por muito tempo exige controle do pulso e da respiração. O corpo tende a tensionar durante a repetição, e a tensão rouba o tempo. Relaxar os ombros, respirar no tempo e manter a mão leve são cuidados que permitem repetir a célula por minutos sem perder o alinhamento. Groove é, também, resistência relaxada."),
        b ("Relaxe os ombros e a mão durante a repetição."),
        b ("Respire no tempo; não prenda a respiração."),
        b ("Repita em ciclos longos para treinar a resistência."),
        c (
            "Uma levada que se sustenta por dois minutos sem perder o pulso é uma levada dominada. Treinar a repetição longa é o que constrói isso."),
    };
}

} // namespace cursomusica::content
