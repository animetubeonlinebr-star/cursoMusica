#include "Course/Content/Topics.h"

// Topic 5B — Campo harmônico maior e graus da escala (Módulo 5, Etapa 5).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 5, bloco B).
namespace cursomusica::content
{

std::vector<ContentItem> topic5B()
{
    return {

        p (
            "O campo harmônico maior é o conjunto dos sete acordes que nascem de uma escala maior. Se a escala maior é a régua das notas, o campo harmônico é a régua dos acordes: para cada grau da escala existe um acorde, e todos eles pertencem à mesma tonalidade. Saber o campo harmônico de uma tonalidade é saber, de antemão, quais acordes 'cabem' numa música naquele tom."),
        p (
            "Este tópico responde a uma pergunta muito prática: se estou em Dó maior, quais acordes posso usar? A resposta é sempre a mesma sequência: C – Dm – Em – F – G – Am – Bdim. Com ela você acompanha, compõe e analisa músicas inteiras sem sair da tonalidade."),

        h ("Como se constrói o campo harmônico"),
        p (
            "O campo harmônico é construído empilhando as notas da própria escala. Para cada grau, toma-se aquela nota como fundamental, pula-se um grau, pega-se o seguinte, pula-se mais um e pega-se o terceiro. Esse empilhamento de terças sobre cada grau da escala produz um acorde de três notas — uma tríade — e o conjunto dos sete acordes forma o campo harmônico."),
        p (
            "O que decide se cada acorde é maior, menor ou diminuto é a distância entre as notas empilhadas. Como a escala maior tem semitons em posições fixas, cada grau acaba gerando sempre o mesmo tipo de acorde. Não é coincidência: é consequência direta do padrão T – T – S – T – T – T – S que você viu no tópico A."),
        b ("Empilhe de dois em dois graus: 1–3–5, 2–4–6, 3–5–7…"),
        b ("Cada tríade é formada pela fundamental, a terça e a quinta daquele grau."),
        b ("A qualidade (maior, menor, diminuto) depende dos intervalos dentro da escala."),
        img ("m5_campo_harmonico_maior", "O campo harmônico maior: para cada grau da escala nasce um acorde, com a sua qualidade."),

        h ("A sequência fixa dos sete acordes"),
        p (
            "A grande descoberta do campo harmônico é que a qualidade dos acordes segue um padrão que nunca muda. Os graus I e IV e V geram acordes maiores; os graus ii, iii e vi geram acordes menores; e o grau vii gera um acorde diminuto. Isso vale para qualquer tonalidade maior — só mudam as notas, nunca as qualidades."),
        p (
            "Em Dó maior, esse padrão dá exatamente: C (I, maior), Dm (ii, menor), Em (iii, menor), F (IV, maior), G (V, maior), Am (vi, menor) e Bdim (vii°, diminuto). Toque essa sequência em ordem e você ouve a escala 'harmonizada' — cada acorde é um degrau da escala transformado em harmonia."),
        tbl ({ "Grau", "Qualidade", "Em Dó maior", "Em Sol maior", "Em Fá maior" }, {
            { "I", "maior", "C", "G", "F" },
            { "ii", "menor", "Dm", "Am", "Gm" },
            { "iii", "menor", "Em", "Bm", "Am" },
            { "IV", "maior", "F", "C", "Bb" },
            { "V", "maior", "G", "D", "C" },
            { "vi", "menor", "Am", "Em", "Dm" },
            { "vii°", "diminuto", "Bdim", "F#dim", "Edim" },
        }),
        c (
            "Padrão universal: I – ii – iii – IV – V – vi – vii°. Decore a sequência de qualidades e você monta o campo harmônico de qualquer tonalidade maior."),
        aud ({ "C4", "E4", "G4", "D4", "F4", "A4", "E4", "G4", "B4", "F4", "A4", "C5", "G4", "B4", "D5" },
             "Os cinco primeiros acordes do campo de Dó (C, Dm, Em, F, G) arpejados em sequência."),
        part ("m5_partitura_campo", { "C4", "E4", "G4", "D4", "F4", "A4", "E4", "G4", "B4" },
              "Partitura dos três primeiros acordes do campo de Dó (C – Dm – Em), arpejados."),

        h ("Por que as qualidades caem sempre nos mesmos graus"),
        p (
            "A razão das qualidades fixas está na posição dos semitons. Quando você empilha terças a partir do grau I, encontra as distâncias de terça maior e quinta justa, e o resultado é um acorde maior. Quando empilha a partir do grau ii, a terça que aparece é menor, e o acorde vira menor. No grau vii, as duas terças empilhadas ficam pequenas, e o acorde vira diminuto."),
        p (
            "Esse encadeamento não é arbitrário: é a própria escala 'decidindo' o tipo de cada acorde. Entender isso é o que permite deduzir o campo harmônico de qualquer tom sem decorar tabelas. Basta aplicar o padrão de qualidades à sequência de notas da tonalidade e você tem os sete acordes na hora."),
        b ("Graus com terça maior sobre a fundamental → acorde maior (I, IV, V)."),
        b ("Graus com terça menor → acorde menor (ii, iii, vi)."),
        b ("Grau com terças menores empilhadas → acorde diminuto (vii°)."),

        h ("Tonalidade, grau e nome do acorde"),
        p (
            "Uma mesma ideia harmônica pode ser escrita de duas formas: pelo grau ou pelo nome do acorde. Dizer 'I – IV – V' descreve uma progressão que vale em qualquer tom; dizer 'C – F – G' descreve a mesma progressão já fixada em Dó maior. A análise por graus é o que permite reconhecer que duas músicas em tons diferentes usam a mesma progressão."),
        p (
            "Por isso o músico experiente pensa em graus. Quando alguém diz 'essa música é um I–vi–ii–V', ele imediatamente sabe a função de cada acorde e pode tocar em qualquer tom. O nome do acorde é apenas a tradução dessa ideia para uma tonalidade específica — útil para tocar, mas secundário para entender."),
        tbl ({ "Progressão em graus", "Em Dó maior", "Função" }, {
            { "I – IV – V", "C – F – G", "repouso, afastamento, tensão" },
            { "I – vi – ii – V", "C – Am – Dm – G", "ciclo clássico de retorno" },
            { "ii – V – I", "Dm – G – C", "cadência mais usada do jazz" },
            { "I – V – vi – IV", "C – G – Am – F", "progressão pop universal" },
        }),

        h ("Acordes relativos dentro do campo"),
        p (
            "Dentro do campo harmônico, alguns acordes compartilham notas e por isso soam próximos. O acorde de vi (Am, em Dó maior) compartilha duas notas com o I (C) e é chamado de relativo menor. Da mesma forma, cada acorde maior tem um relativo menor a três semitons abaixo, e esse par aparece naturalmente no campo harmônico."),
        p (
            "Essa proximidade explica por que certas trocas de acorde soam suaves e outras soam dramáticas. Trocar C por Am é quase imperceptível — eles têm duas notas em comum. Trocar C por G é um salto maior de tensão. Aprender a ouvir essas relações é o que permite escolher acordes de forma consciente, e não por tentativa e erro."),
        b ("Relativo menor de um acorde maior fica a 3 semitons abaixo (C → Am)."),
        b ("Acordes que compartilham notas soam próximos e permitem trocas suaves."),
        b ("O campo harmônico já contém os relativos naturais de cada acorde."),
        aud ({ "C4", "E4", "G4", "A3", "C4", "E4" },
             "C (I) e Am (vi): duas notas em comum, uma troca suave dentro do campo."),

        h ("Usando o campo harmônico na prática"),
        p (
            "Na prática, o campo harmônico é a lista de acordes de que você dispõe numa tonalidade. Quando você quer acompanhar uma música em Dó maior, procura os acordes dela dentro de C, Dm, Em, F, G, Am e Bdim. Quando quer compor algo que soe coerente, escolhe acordes do mesmo campo. É o vocabulário harmônico básico."),
        p (
            "Os exercícios deste tópico pedem que você toque os acordes do campo harmônico e deixe o app reconhecer as notas. Assim você confirma, na prática, que as tríades que montou no braço correspondem exatamente às notas da escala — a teoria e a execução se encontram no mesmo gesto."),
        b ("Escolha a tonalidade e monte os sete acordes do campo."),
        b ("Toque cada acorde e ouça a qualidade (maior, menor, diminuto)."),
        b ("Confirme no app se as notas que você tocou formam a tríade correta."),
        img ("m5_campo_harmonico_braco", "O campo harmônico de Dó no braço: as tríades do campo em uma região, para tocar e conferir."),

        h ("Erros comuns ao montar o campo harmônico"),
        p (
            "O erro mais comum é trocar a qualidade de um grau — fazer o grau IV menor ou o grau ii maior. Isso acontece quando se decora o nome dos acordes sem entender o padrão de qualidades. Outro erro é esquecer que o grau vii é diminuto e tratá-lo como menor. E há quem misture acordes de tonalidades diferentes sem perceber que saiu do campo."),
        b ("Errar a qualidade do grau (IV maior, não menor; ii menor, não maior)."),
        b ("Esquecer o acorde diminuto do grau vii."),
        b ("Misturar acordes de outra tonalidade sem intenção."),
        c (
            "Dica: antes de tocar, escreva a sequência de qualidades (M m m M M m d) acima dos graus. Depois aplique as notas da tonalidade. Assim você nunca troca maior por menor."),

        h ("O campo harmônico como vocabulário"),
        p (
            "Há uma comparação útil para entender o campo harmônico: ele é o vocabulário harmônico de uma tonalidade. Assim como uma língua tem um conjunto de palavras que combinam entre si, uma tonalidade tem um conjunto de acordes que combinam entre si. Usar acordes de fora do campo é como usar uma palavra estrangeira: pode funcionar, mas chama atenção e precisa de intenção."),
        p (
            "Quando você compõe ou acompanha dentro do campo harmônico, tudo soa coerente automaticamente. É por isso que tantas músicas usam os mesmos acordes: não por falta de criatividade, mas porque esses acordes são o vocabulário natural da tonalidade. A criatividade vem de como você organiza esse vocabulário — a ordem, o ritmo, a melodia — e não de inventar acordes novos."),
        b ("O campo harmônico é o vocabulário de acordes da tonalidade."),
        b ("Acordes do campo combinam entre si automaticamente."),
        b ("Acordes de fora são possíveis, mas exigem intenção."),

        h ("Identificando o campo harmônico de uma música"),
        p (
            "Para identificar o campo harmônico de uma música, o caminho é descobrir a sua tonalidade. Ouça qual acorde soa como repouso: normalmente é o acorde em que a música termina e para o qual ela sempre volta. Esse acorde é a tônica, e a partir dele você monta o campo harmônico completo aplicando o padrão I – ii – iii – IV – V – vi – vii°."),
        p (
            "Depois de identificar a tônica, confira se os acordes da música pertencem ao campo que você montou. Se todos pertencerem, a análise está correta. Se aparecer um acorde de fora, pode ser um empréstimo de outra tonalidade ou um acorde de passagem — assunto dos módulos mais avançados, mas que você já vai começar a reconhecer."),
        b ("Descubra a tônica: o acorde de repouso e de conclusão."),
        b ("Monte o campo harmônico a partir dela com o padrão de qualidades."),
        b ("Confira se os acordes da música pertencem ao campo."),
        aud ({ "C4", "E4", "G4", "A3", "C4", "E4", "D4", "F4", "A4", "G4", "B4", "D5", "C5", "E5", "G5" },
             "I – vi – ii – V – I: uma progressão inteira dentro do campo de Dó maior."),

        h ("Campo harmônico e improvisação"),
        p (
            "Saber o campo harmônico também ajuda a improvisar. Como todos os acordes do campo usam notas da mesma escala, você pode improvisar com a escala da tonalidade sobre toda a progressão, sem trocar de escala a cada acorde. As notas da escala 'cabem' em todos os acordes do campo, o que simplifica muito a improvisação para quem está começando."),
        p (
            "Mais adiante, você vai aprender a realçar as notas de cada acorde dentro dessa escala — o que dá mais cor ao solo. Mas o ponto de partida é este: uma tonalidade, uma escala, um campo harmônico. Improvisar sobre o campo é escolher, dentro da escala, as notas que combinam com o acorde que está soando naquele momento."),
        b ("A escala da tonalidade cabe sobre todos os acordes do campo."),
        b ("Improvisar sobre o campo é escolher notas da escala em cada acorde."),
        b ("Mais adiante, as notas do acorde dão cor ao solo."),
        c (
            "O campo harmônico é, ao mesmo tempo, uma ferramenta de análise (para entender músicas), de composição (para escolher acordes) e de improvisação (para saber que notas usar). É por isso que ele é um dos conceitos centrais de todo o curso."),

        h ("Resumo do tópico"),
        b ("Campo harmônico maior = sete acordes que nascem da escala maior."),
        b ("A qualidade segue o padrão I – ii – iii – IV – V – vi – vii°."),
        b ("Em Dó maior: C – Dm – Em – F – G – Am – Bdim."),
        b ("Cada acorde pode ser nomeado pelo grau ou pelo nome, conforme a tonalidade."),
        b ("Acordes que compartilham notas soam próximos (relativos)."),
        c (
            "Nos exercícios deste tópico, toque as tríades do campo harmônico. O app reconhece as notas e confere se a qualidade do acorde corresponde ao grau que você escolheu."),
    };
}

} // namespace cursomusica::content
