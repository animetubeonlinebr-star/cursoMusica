#include "Course/Content/Topics.h"

// Topic 4A — Tríades maiores e menores (Módulo 4, Etapa 4).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 4 — construção de acordes).
namespace cursomusica::content
{

std::vector<ContentItem> topic4A()
{
    return {

        p (
            "Acorde é um conjunto de notas que soam juntas. A forma mais simples de acorde tem três notas e se chama tríade. Praticamente tudo o que você toca — acompanhamento, base de música, arranjo — nasce de uma tríade ou de uma tríade com uma nota a mais. Por isso este módulo começa por ela: entender a tríade é entender de onde vem o som de cada acorde."),
        p (
            "Uma tríade é construída empilhando intervalos de terça a partir de uma nota de partida, a tônica. A primeira terça dá a terceira nota do acorde; a segunda terça, sobre ela, dá a quinta. Você já estudou intervalos no módulo anterior; agora vai usá-los para montar acordes e reconhecê-los no braço e de ouvido."),
        c (
            "Objetivo do módulo: compreender a formação dos acordes e suas diferentes possibilidades de execução. Neste tópico, a tríade maior e a tríade menor — as duas que sustentam quase toda a música popular."),

        h ("O que é uma tríade"),
        p (
            "Tríade é um acorde de três notas: a tônica (1), a terça (3) e a quinta (5). A tônica dá o nome ao acorde (em Dó, a tônica é Dó); a terça define se o acorde é maior ou menor; a quinta dá corpo e estabilidade. Quando você toca um Dó maior, está tocando Dó, Mi e Sol — uma tríade de Dó."),
        b ("Tônica (1): a nota que dá nome ao acorde."),
        b ("Terça (3): decide a qualidade — maior ou menor."),
        b ("Quinta (5): reforça e estabiliza o som."),
        img ("m4_triades_maior_menor", "Tríade maior (Dó–Mi–Sol) e tríade menor (Dó–Mi♭–Sol): a terça muda tudo."),

        h ("A tríade maior"),
        p (
            "A tríade maior tem a tônica, a terça maior (4 semitons acima da tônica) e a quinta justa (7 semitons acima da tônica). Em semitons, escreve-se 0–4–7. Em Dó, isso dá Dó–Mi–Sol. O som é aberto, estável e alegre: é o acorde mais comum da música."),
        tbl ({ "Nota", "Grau", "Semitons da tônica", "Intervalo" }, {
            { "Dó", "1 (tônica)", "0", "uníssono" },
            { "Mi", "3", "4", "terça maior" },
            { "Sol", "5", "7", "quinta justa" },
        }),
        c (
            "Grave na memória: tríade maior = 0–4–7. É a receita do acorde maior, em qualquer tônica."),

        h ("A tríade menor"),
        p (
            "A tríade menor tem a mesma tônica e a mesma quinta, mas a terça é menor (3 semitons acima da tônica). Em semitons, escreve-se 0–3–7. Em Dó, isso dá Dó–Mi♭–Sol. O som é fechado, introspectivo e melancólico. Comparando as duas, percebe-se que a única diferença está na terça: um semitom para baixo transforma o maior em menor."),
        tbl ({ "Nota (Cm)", "Grau", "Semitons da tônica", "Intervalo" }, {
            { "Dó", "1 (tônica)", "0", "uníssono" },
            { "Mi♭", "3", "3", "terça menor" },
            { "Sol", "5", "7", "quinta justa" },
        }),
        c (
            "Tríade menor = 0–3–7. A tônica e a quinta são as mesmas do maior; só a terça desce um semitom."),

        h ("Maior e menor: a mesma forma, uma nota diferente"),
        p (
            "No braço, o acorde maior e o menor da mesma tônica ficam muito próximos. Muitas vezes basta levantar ou baixar um dedo na corda onde está a terça. Essa proximidade é a chave para trocar entre maior e menor sem mudar de posição — e é a base da harmonia que você vai usar em todas as músicas."),
        b ("Dó maior: Dó–Mi–Sol (a terça, Mi, é a 1ª corda solta; a 6ª também é Mi, duas oitavas abaixo)."),
        b ("Dó menor: Dó–Mi♭–Sol (a mesma forma, com a terça abaixada um semitom)."),
        b ("Ouvir a terça é ouvir a diferença entre os dois acordes."),
        aud ({ "C4", "E4", "G4" }, "Tríade maior (Dó–Mi–Sol): som aberto e estável."),
        aud ({ "C4", "Eb4", "G4" }, "Tríade menor (Dó–Mi♭–Sol): só a terça mudou, o som ficou fechado."),

        h ("Como ouvir a diferença"),
        p (
            "Toque uma tríade maior e depois a mesma tríade com a terça menor. A tônica e a quinta não mudam; só a terça se move. O ouvido percebe imediatamente a mudança de humor: o maior soa resolvido, o menor soa como uma pergunta. Treinar esse reconhecimento é o primeiro passo da percepção harmônica."),
        b ("Maior: parece 'para cima', aberto, otimista."),
        b ("Menor: parece 'para baixo', fechado, sério."),
        b ("Dica: cante a terça de cada um — Mi (maior) e Mi♭ (menor)."),

        h ("Tríades em qualquer tônica"),
        p (
            "A receita 0–4–7 e 0–3–7 vale para qualquer nota de partida. Basta achar a tônica e contar os semitons. Em Sol maior: Sol–Si–Ré (0–4–7). Em Lá menor: Lá–Dó–Mi (0–3–7). Como a guitarra é uma régua de semitons, você constrói a tríade em qualquer região do braço contando as casas."),
        tbl ({ "Acorde", "Notas", "Semitons", "Qualidade" }, {
            { "Dó maior (C)", "Dó–Mi–Sol", "0–4–7", "maior" },
            { "Sol maior (G)", "Sol–Si–Ré", "0–4–7", "maior" },
            { "Fá maior (F)", "Fá–Lá–Dó", "0–4–7", "maior" },
            { "Lá menor (Am)", "Lá–Dó–Mi", "0–3–7", "menor" },
            { "Ré menor (Dm)", "Ré–Fá–Lá", "0–3–7", "menor" },
            { "Mi menor (Em)", "Mi–Sol–Si", "0–3–7", "menor" },
        }),

        h ("A tríade e o campo harmônico"),
        p (
            "As tríades que nascem de uma escala formam o campo harmônico. Em Dó maior, as sete tríades sobre os graus da escala são Dó, Ré menor, Mi menor, Fá, Sol, Lá menor e Si diminuto. Repare: os graus I, IV e V são maiores; os graus ii, iii e vi são menores; e o vii é diminuto. Essa distribuição não é acidental — ela vem dos intervalos da própria escala."),
        b ("I, IV e V: maiores (têm terça maior)."),
        b ("ii, iii e vi: menores (têm terça menor)."),
        b ("vii: diminuto (terça menor e quinta diminuta) — assunto do próximo tópico."),
        img ("m4_formacao_acordes", "Tríades maior e menor formadas pelo empilhamento de terças sobre a tônica."),

        h ("Primeiros passos no instrumento"),
        p (
            "Para tocar uma tríade, você não precisa de todas as notas ao mesmo tempo. O acorde pode ser tocado nota por nota (arpejo) ou com as três notas juntas. No começo, toque a tríade em arpejo, dizendo o nome de cada nota em voz alta. Depois, toque as três juntas. O app reconhece as notas e confere se a terça é a certa."),
        b ("Arpejo: toque tônica, terça e quinta, uma após a outra."),
        b ("Acorde: toque as três notas juntas e deixe soar."),
        b ("Confira: a terça maior tem 4 semitons; a menor, 3."),
        part ("m4_partitura_triade", { "C4", "E4", "G4", "C5" },
              "Partitura da tríade de Dó maior (Dó–Mi–Sol–Dó). Ouça exatamente o que está escrito."),

        h ("A terça: o coração do acorde"),
        p (
            "Se você tivesse que escolher a nota mais importante de um acorde, seria a terça. Ela é a nota que diz ao ouvido se o acorde é maior ou menor; a tônica apenas dá o nome e a quinta apenas dá corpo. Em muitos arranjos, a quinta é omitida e a terça permanece, porque sem ela o acorde perde a identidade. Quando você acompanha uma música, ouvir a terça é ouvir a cor de cada acorde."),
        b ("Tônica: dá o nome (Dó, Sol, Lá…)."),
        b ("Terça: dá a qualidade (maior ou menor) — a mais importante."),
        b ("Quinta: dá corpo e estabilidade; pode ser omitida sem prejuízo."),
        tbl ({ "Acorde", "Tônica", "Terça", "Quinta", "Qualidade" }, {
            { "Dó (C)", "Dó", "Mi", "Sol", "maior" },
            { "Dó menor (Cm)", "Dó", "Mi♭", "Sol", "menor" },
            { "Sol (G)", "Sol", "Si", "Ré", "maior" },
            { "Sol menor (Gm)", "Sol", "Si♭", "Ré", "menor" },
            { "Lá (A)", "Lá", "Dó♯", "Mi", "maior" },
            { "Lá menor (Am)", "Lá", "Dó", "Mi", "menor" },
        }),

        h ("Tríades na prática: acompanhar uma música"),
        p (
            "Quando você acompanha uma música, quase nunca toca a tríade na posição mais óbvia o tempo todo. Você escolhe a posição que mantém a mão perto da próxima e que deixa o baixo na nota certa. Esse cuidado se chama condução de vozes: buscar as notas comuns entre acordes vizinhos para que a mão se mova o mínimo possível. A tríade é o material dessa escolha."),
        p (
            "Experimente a progressão Dó – Lá menor – Ré menor – Sol. Se você tocar cada acorde na primeira posição, a mão salta o tempo todo. Se procurar as formas próximas — por exemplo, mantendo o Dó e o Mi como notas comuns —, o acompanhamento fica mais fluido e mais musical. O ouvido agradece: menos saltos, mais continuidade."),
        b ("Procure as notas comuns entre um acorde e o seguinte."),
        b ("Prefira posições vizinhas em vez de saltos grandes."),
        b ("Escolha o baixo pensando na linha grave, não só no acorde."),
        aud ({ "C4", "E4", "G4", "A3", "C4", "E4" }, "Dó maior seguido de Lá menor: duas notas comuns mantêm a mão no lugar."),

        h ("Tríade fechada e tríade com cordas soltas"),
        p (
            "Há muitas maneiras de distribuir as três notas pelo braço. Uma tríade fechada usa as notas na ordem mais compacta; uma tríade com cordas soltas usa cordas vazias para dar brilho e volume, muito comum no violão. Não existe uma versão 'certa': existe a versão que serve à música que você está tocando. O importante é saber sempre quais notas estão soando."),
        b ("Tríade fechada: notas empilhadas, som compacto."),
        b ("Tríade com cordas soltas: som aberto e cheio, típico do violão."),
        b ("Trocar a posição não muda o acorde, só a cor."),

        h ("Erros comuns"),
        p (
            "O erro mais frequente é abafar uma corda ou tocar uma nota errada sem perceber, porque o acorde ainda soa 'parecido'. Outro erro é decorar a forma sem saber quais notas está tocando, o que trava a transposição. Estude sempre sabendo o nome das notas: assim, a forma deixa de ser um desenho e passa a ser um acorde que você entende."),
        b ("Corda abafada: soa morta; aproxime o dedo do traste."),
        b ("Nota errada: confira se a terça é a certa (maior ou menor)."),
        b ("Forma decorada sem nome de nota: impede tocar em outras tônicas."),

        h ("Como o app confere este tópico"),
        p (
            "Os exercícios tocados deste tópico pedem que você toque uma tríade maior ou menor. O app ouve as notas, calcula as classes de altura (Dó, Mi, Sol, por exemplo) e verifica se o conjunto corresponde ao acorde pedido. Isso significa que qualquer posição do braço vale: o que o app cobra é a qualidade do acorde, não uma forma específica. Assim você aprende o acorde, e não uma receita decorada."),
        b ("O app reconhece as notas tocadas e confere a terça."),
        b ("Qualquer posição do braço é aceita, desde que as notas certas soem."),
        b ("Confira sempre com o ouvido: maior soa aberto, menor soa fechado."),

        h ("Aplicação musical: onde as tríades aparecem"),
        p (
            "Tríades estão em todo lugar: na base de um violão que acompanha um samba, na harmonia de um rock, no arranjo de uma balada. Mesmo quando um acorde tem sétima ou nona, a tríade continua sendo o esqueleto — as outras notas apenas acrescentam cor. Aprender a tríade com clareza é o que permite, mais tarde, acrescentar tensões sem se perder."),
        b ("Acompanhamento: toque a tríade de cada acorde da música."),
        b ("Arranjo: distribua as três notas em regiões diferentes do braço."),
        b ("Improviso: os arpejos de tríade dão a base do solo."),
        p (
            "Um bom caminho de estudo é pegar uma música simples, escrever o nome dos acordes e, para cada um, dizer as três notas. Depois toque a tríade em três regiões diferentes do braço. Isso constrói a ligação entre o que você lê (a cifra), o que você pensa (as notas) e o que você toca (a posição)."),

        h ("Resumo do tópico"),
        b ("Tríade é um acorde de três notas: tônica, terça e quinta."),
        b ("Tríade maior = 0–4–7; tríade menor = 0–3–7."),
        b ("A única diferença entre maior e menor está na terça (4 ou 3 semitons)."),
        b ("A receita vale em qualquer tônica e em qualquer posição do braço."),
        c (
            "Nos exercícios deste tópico, toque as tríades pedidas no instrumento. O app reconhece as notas e confere a qualidade (maior ou menor), então qualquer posição do braço vale — o que importa é a terça."),
    };
}

} // namespace cursomusica::content
