#include "Course/Content/Topics.h"

// Topic 4B — Tríades aumentadas e diminutas (Módulo 4, Etapa 4).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 4 — construção de acordes).
namespace cursomusica::content
{

std::vector<ContentItem> topic4B()
{
    return {

        p (
            "No tópico anterior você viu as tríades maior e menor, que têm a quinta justa (7 semitons acima da tônica). Existem mais duas tríades: a aumentada e a diminuta. Elas nascem de alterar a quinta — subir ou descer um semitom — e produzem sons de tensão, de passagem e de instabilidade. São menos comuns no acompanhamento, mas essenciais para entender harmonia e para dar cor a um arranjo."),
        p (
            "A ideia é simples: a tônica continua sendo a tônica; o que muda é a quinta. Na tríade aumentada, a quinta sobe um semitom (fica aumentada). Na tríade diminuta, a quinta desce um semitom (fica diminuta). Comparando as quatro tríades, você percebe que todas compartilham a mesma tônica e diferem só na terça e na quinta."),
        c (
            "As quatro tríades: maior (0–4–7), menor (0–3–7), aumentada (0–4–8) e diminuta (0–3–6). Duas alterações (terça e quinta) geram as quatro qualidades."),

        h ("A tríade aumentada"),
        p (
            "A tríade aumentada tem a terça maior (4 semitons) e a quinta aumentada (8 semitons). Em semitons, escreve-se 0–4–8. Em Dó, isso dá Dó–Mi–Sol♯. O som é suspenso, 'flutuante', como se o acorde não quisesse repousar. Ele aparece em passagens, em dominantes alterados e em harmonias de jazz e de música impressionista."),
        tbl ({ "Nota (Caug)", "Grau", "Semitons da tônica", "Intervalo" }, {
            { "Dó", "1 (tônica)", "0", "uníssono" },
            { "Mi", "3", "4", "terça maior" },
            { "Sol♯", "5", "8", "quinta aumentada" },
        }),
        c (
            "Tríade aumentada = 0–4–8. A quinta justa sobe um semitom e vira quinta aumentada."),
        img ("m4_triades_aum_dim", "Tríade aumentada (Dó–Mi–Sol♯) e diminuta (Dó–Mi♭–Sol♭)."),

        h ("A tríade diminuta"),
        p (
            "A tríade diminuta tem a terça menor (3 semitons) e a quinta diminuta (6 semitons). Em semitons, escreve-se 0–3–6. Em Dó, isso dá Dó–Mi♭–Sol♭. O som é tenso e instável, quase 'desafinado' de propósito. Ela aparece como o sétimo grau do campo harmônico maior (em Dó, o Si diminuto) e em passagens cromáticas."),
        tbl ({ "Nota (Cdim)", "Grau", "Semitons da tônica", "Intervalo" }, {
            { "Dó", "1 (tônica)", "0", "uníssono" },
            { "Mi♭", "3", "3", "terça menor" },
            { "Sol♭", "5", "6", "quinta diminuta" },
        }),
        c (
            "Tríade diminuta = 0–3–6. A quinta justa desce um semitom e vira quinta diminuta."),

        h ("As quatro tríades lado a lado"),
        p (
            "Comparar as quatro tríades é a melhor forma de entender o sistema. Todas partem da mesma tônica; o que muda é a terça (maior ou menor) e a quinta (justa, aumentada ou diminuta). Note que a diminuta tem a terça menor (como a menor) e a quinta diminuta; a aumentada tem a terça maior (como a maior) e a quinta aumentada."),
        tbl ({ "Tríade", "Semitons", "Notas em Dó", "Sensação" }, {
            { "Maior", "0–4–7", "Dó–Mi–Sol", "aberta, estável" },
            { "Menor", "0–3–7", "Dó–Mi♭–Sol", "fechada, séria" },
            { "Aumentada", "0–4–8", "Dó–Mi–Sol♯", "suspensa, flutuante" },
            { "Diminuta", "0–3–6", "Dó–Mi♭–Sol♭", "tensa, instável" },
        }),
        aud ({ "C4", "E4", "G#4" }, "Tríade aumentada (Dó–Mi–Sol♯): som suspenso, que parece não resolver."),
        aud ({ "C4", "D#4", "F#4" }, "Tríade diminuta (Dó–Mi♭–Sol♭): som tenso e instável."),

        h ("Onde a aumentada aparece"),
        p (
            "A tríade aumentada tem uma propriedade curiosa: ela é simétrica. Cada nota pode ser vista como a tônica de uma nova tríade aumentada, porque os intervalos entre as notas são todos iguais (4 semitons). Por isso, um acorde aumentado 'não tem direção': ele pode resolver para vários lugares diferentes. É um som de passagem e de tensão, muito usado em finais e em modulações."),
        b ("Som de passagem: entre dois acordes estáveis."),
        b ("Dominante alterado: uma tensão antes da resolução."),
        b ("É simétrico: 4 semitons entre cada par de notas."),

        h ("Onde a diminuta aparece"),
        p (
            "A tríade diminuta aparece naturalmente no sétimo grau da escala maior. Em Dó maior, o acorde sobre o Si é um Si diminuto (Si–Ré–Fá), porque o Si é a sensível que puxa para o Dó. Ela também é comum em passagens cromáticas, ligando dois acordes por meio de um acorde tenso. Ouvir a diminuta é ouvir a sensação de 'quase lá' — a música pede uma resolução."),
        b ("Sétimo grau do campo harmônico maior: Si diminuto em Dó maior."),
        b ("Passagem cromática entre acordes."),
        b ("Som que pede resolução: tenso e instável."),

        h ("Como ouvir as duas"),
        p (
            "Ouça primeiro a tríade maior e a menor (estáveis) e depois a aumentada e a diminuta (instáveis). A aumentada soa como um 'ponto de interrogação' suspenso; a diminuta, como um 'aperto' que quer se soltar. Ao tocar as quatro seguidas, o contraste fica claro. Esse reconhecimento é o que permite usar as tríades alteradas no momento certo."),
        b ("Maior e menor: repousam, soam resolvidas."),
        b ("Aumentada: flutua, não repousa."),
        b ("Diminuta: tensiona, pede para resolver."),
        aud ({ "C4", "E4", "G4", "C4", "E4", "G#4", "C4", "D#4", "F#4" },
             "Dó maior, aumentado e diminuto em sequência: sinta o contraste de estabilidade."),

        h ("Tocar as tríades alteradas no instrumento"),
        p (
            "No braço, as tríades alteradas são mais difíceis de encaixar do que as maiores e menores, porque a quinta alterada fica em posições menos óbvias. Uma boa estratégia é começar tocando a tríade em arpejo — tônica, terça e quinta alterada, uma após a outra — para ouvir a nota que muda. Depois, tente achar as três notas juntas em uma posição confortável."),
        b ("Arpeje primeiro: tônica, terça, quinta alterada."),
        b ("Depois procure as três notas juntas."),
        b ("Diga o nome de cada nota em voz alta enquanto toca."),

        h ("Tensão e resolução: por que elas existem"),
        p (
            "Toda música é um jogo de tensão e repouso. As tríades maior e menor são o repouso; a aumentada e a diminuta são a tensão. A tensão não é um erro: é o que faz a música andar. Quando você ouve um acorde diminuto, o ouvido espera o próximo acorde — geralmente um acorde estável que resolve a tensão. Entender isso transforma a harmonia em algo previsível e expressivo."),
        b ("Repouso: acordes maior e menor (estáveis)."),
        b ("Tensão: acordes aumentado e diminuto (instáveis)."),
        b ("A música alterna os dois: tensão cria expectativa, repouso a resolve."),
        c (
            "Regra prática: quanto mais notas alteradas (quinta aumentada, quinta diminuta), maior a tensão. Use-as para conduzir a música, não para repousar nela."),

        h ("Tríades alteradas e cifra"),
        p (
            "Na cifra, a tríade aumentada aparece com o símbolo '+' ou 'aug' (por exemplo, C+ ou Caug) e a diminuta com 'dim' ou '°' (Cdim ou C°). Saber ler esses símbolos é essencial para tocar a música escrita. Muitas vezes a cifra traz um acorde diminuto no meio de uma progressão simples, ligando dois acordes por meio da tensão."),
        tbl ({ "Cifra", "Significado", "Semitons", "Notas em Dó" }, {
            { "C", "tríade maior", "0–4–7", "Dó–Mi–Sol" },
            { "Cm", "tríade menor", "0–3–7", "Dó–Mi♭–Sol" },
            { "C+ / Caug", "tríade aumentada", "0–4–8", "Dó–Mi–Sol♯" },
            { "Cdim / C°", "tríade diminuta", "0–3–6", "Dó–Mi♭–Sol♭" },
        }),

        h ("Exercício de escuta: identificando as quatro"),
        p (
            "Peça a um colega (ou ao próprio app) para tocar as quatro tríades de Dó em ordem aleatória. Tente identificar cada uma apenas pelo ouvido. Comece distinguindo as estáveis (maior e menor) das instáveis (aumentada e diminuta); depois refine a distinção entre maior e menor (a terça) e entre aumentada e diminuta. Com prática, o ouvido reconhece a qualidade em poucos segundos."),
        b ("Primeiro passo: estável ou instável?"),
        b ("Segundo passo: se estável, maior ou menor?"),
        b ("Terceiro passo: se instável, aumentada ou diminuta?"),

        h ("As tríades alteradas no braço"),
        p (
            "No braço, uma forma prática é tomar uma tríade maior e mover apenas a nota da quinta: subir um semitom produz a aumentada, descer um semitom produz a diminuta. Como as três notas estão distribuídas em cordas diferentes, você quase sempre pode alterar a quinta sem mudar a tônica e a terça. Isso torna as tríades alteradas acessíveis mesmo para quem está começando."),
        b ("Pegue uma tríade maior (por exemplo, Dó)."),
        b ("Suba a quinta um semitom: vira aumentada."),
        b ("Desça a quinta um semitom: vira diminuta."),

        h ("Simetria da tríade aumentada"),
        p (
            "A tríade aumentada é dividida em três partes iguais: 4 semitons da tônica para a terça, 4 da terça para a quinta aumentada e 4 da quinta aumentada para a oitava da tônica. Essa simetria faz com que as três notas sejam intercambiáveis: qualquer uma pode soar como baixo sem que o acorde mude de caráter. Por isso dizemos que a aumentada 'não tem direção' — ela é igual vista de qualquer um dos três pontos."),
        b ("Intervalos iguais: 4 + 4 + 4 semitons fecham a oitava."),
        b ("As três notas podem servir de baixo sem mudar o som."),
        b ("É por isso que ela serve tão bem como acorde de passagem."),

        h ("Simetria da tríade diminuta"),
        p (
            "A tríade diminuta também é simétrica, mas de outra forma: os intervalos são de 3 semitons (terça menor) entre as notas. Isso dá 3 + 3 + 3 + 3 = 12 semitons, fechando a oitava com quatro acordes diminutos que compartilham as mesmas notas em rotações. Ou seja, Dó diminuto, Mi♭ diminuto, Sol♭ diminuto e Lá diminuto usam exatamente as mesmas quatro notas (com uma oitava de diferença). Essa propriedade é muito usada em substituições harmônicas."),
        b ("Intervalos de 3 semitons entre as notas."),
        b ("Quatro acordes diminutos compartilham as mesmas notas."),
        b ("Base das substituições e das passagens cromáticas."),

        h ("Aplicação: enriquecendo um acompanhamento"),
        p (
            "Você pode usar as tríades alteradas para dar cor a um acompanhamento simples. Em uma progressão Dó – Sol, por exemplo, um Dó aumentado antes do Sol cria uma condução suave: a quinta aumentada (Sol♯) sobe para a nota do acorde seguinte. Esses detalhes são o que separam um acompanhamento básico de um acompanhamento musical. Mas use com parcimônia: a tensão só funciona quando contrasta com o repouso."),
        b ("Use a aumentada como acorde de passagem antes de um acorde estável."),
        b ("Use a diminuta para ligar dois acordes por cromatismo."),
        b ("A tensão precisa de contraste: não toque tudo alterado."),
        part ("m4_partitura_familia", { "C4", "E4", "G4", "D#4", "F#4" },
              "Partitura da família de Dó: da tríade maior (Dó–Mi–Sol) para a diminuta (Dó–Mi♭–Sol♭)."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é confundir a quinta aumentada com a sexta menor, ou a quinta diminuta com a quarta aumentada: são enarmônicos (mesmo som), mas o nome depende do papel que a nota tem no acorde. Em Dó, a quinta aumentada é Sol♯ (não Lá♭) e a quinta diminuta é Sol♭ (não Fá♯). Outro erro é usar a tríade alterada onde a música pede estabilidade — ela é som de tensão, não de repouso."),
        b ("Sol♯ na tríade aumentada é a quinta (escrita como Sol♯, não Lá♭)."),
        b ("Sol♭ na tríade diminuta é a quinta (escrita como Sol♭, não Fá♯)."),
        b ("Tríades alteradas são tensão: use com intenção."),

        h ("Resumo do tópico"),
        b ("Tríade aumentada = 0–4–8 (terça maior, quinta aumentada)."),
        b ("Tríade diminuta = 0–3–6 (terça menor, quinta diminuta)."),
        b ("As quatro tríades compartilham a tônica e diferem na terça e na quinta."),
        b ("Aumentada é suspensa e simétrica; diminuta é tensa e pede resolução."),
        b ("Na cifra: '+' ou 'aug' para aumentada, 'dim' ou '°' para diminuta."),
        c (
            "Nos exercícios deste tópico, toque as tríades alteradas pedidas. O app reconhece as notas e confere as classes de altura, aceitando qualquer posição do braço."),
    };
}

} // namespace cursomusica::content
