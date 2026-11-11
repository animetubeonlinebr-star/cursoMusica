#include "Course/Content/Topics.h"

// Topic G — Organização das tonalidades.
// Sources: pdf-desvendando-os-segredos-da-guitarra-fusion (escalas, tríades,
// tétrades, harmonia) and pdf-p-...-bohumil-med-teoria-da-musica (escala, grau,
// intervalos).
namespace cursomusica::content
{

std::vector<ContentItem> topicG()
{
    return {
        p ("Até aqui você aprendeu notas, acidentes, o braço e as formas de "
           "acorde. Este tópico dá o passo que une tudo: como as notas e os "
           "acordes de uma música se organizam em torno de uma tonalidade. Você "
           "vai conhecer a escala maior, o campo harmônico, o círculo das quintas "
           "e a ideia de relativa menor. É a harmonia funcional em versão "
           "iniciante — o que explica por que certos acordes combinam e outros "
           "não."),

        h ("Tonalidade: o centro da música"),
        p ("Toda música popular tem um centro tonal: uma nota que soa como "
           "\"casa\", para onde a música tende a voltar. Essa nota é a tônica, e a "
           "tonalidade leva o nome dela. Quando dizemos que uma música está em Dó "
           "maior, queremos dizer que o Dó é a tônica e que as notas e acordes "
           "giram em torno dele."),
        p ("A tonalidade não é uma regra rígida: é uma tendência. A música "
           "ocidental usa a tensão e a resolução em relação à tônica para criar "
           "movimento. Entender a tonalidade é entender para onde a música "
           "\"quer\" ir."),
        b ("Tônica: a nota central, de repouso (1º grau)."),
        b ("Dominante: a nota que cria tensão e pede resolução (5º grau)."),
        b ("Subdominante: a nota que prepara a dominante (4º grau)."),
        c ("Ouça uma música simples e tente cantar a nota em que ela \"termina\" "
           "e parece resolver. Muitas vezes essa nota é a tônica. Esse exercício "
           "de ouvido vale mais que muitas tabelas."),

        h ("A escala maior: a fábrica de tudo"),
        p ("A escala maior é a sequência de sete notas construída a partir de uma "
           "tônica, seguindo um padrão fixo de tons e semitons. Esse padrão é o "
           "mesmo em todas as tonalidades — só muda a nota inicial. Decorar o "
           "padrão permite construir qualquer escala maior."),
        p ("O padrão da escala maior é: tom, tom, semitom, tom, tom, tom, semitom. "
           "Em números: T–T–S–T–T–T–S. Aplicando esse padrão a partir do Dó, "
           "obtemos exatamente as notas naturais, sem nenhum acidente."),
        tbl ({ "Grau", "Nota (escala de Dó)", "Distância do grau anterior" },
             { { "1º (tônica)", "Dó", "—" },
               { "2º", "Ré", "tom" },
               { "3º", "Mi", "tom" },
               { "4º", "Fá", "semitom" },
               { "5º", "Sol", "tom" },
               { "6º", "Lá", "tom" },
               { "7º", "Si", "tom" },
               { "8º (oitava)", "Dó", "semitom" } }),
        p ("Aplicando o mesmo padrão a partir do Sol, surge o Fá♯ (por isso a "
           "tonalidade de Sol maior tem um sustenido). Aplicando a partir do Fá, "
           "surge o Si♭ (por isso Fá maior tem um bemol). É assim que as "
           "tonalidades vão ganhando acidentes, um a um."),
        c ("Verificação rápida: conte os semitons do padrão. T–T–S–T–T–T–S soma "
           "2+2+1+2+2+2+1 = 12 semitons, exatamente uma oitava. O padrão fecha o "
           "ciclo perfeitamente."),

        h ("Graus da escala e intervalos"),
        p ("Cada nota da escala recebe um número, chamado grau. Os graus são a "
           "maneira de falar de música sem depender do nome das notas: dizer "
           "\"quinta\" funciona em qualquer tonalidade. Aprender os graus é "
           "aprender a linguagem da harmonia."),
        tbl ({ "Grau", "Nome", "Intervalo a partir da tônica" },
             { { "1", "tônica", "uníssono" },
               { "2", "supertônica", "segunda maior" },
               { "3", "mediante", "terça maior" },
               { "4", "subdominante", "quarta justa" },
               { "5", "dominante", "quinta justa" },
               { "6", "superdominante", "sexta maior" },
               { "7", "sensível", "sétima maior" } }),
        p ("A terça (3º grau) define se um acorde é maior ou menor: terça maior "
           "dá acorde maior, terça menor dá acorde menor. A quinta (5º grau) e a "
           "sétima definem outras qualidades. Esses três graus — fundamental, "
           "terça e quinta — formam a tríade, a base de quase todo acorde."),
        c ("Você já viu os intervalos no tópico B. Agora eles ganham função: a "
           "terça e a quinta de cada grau determinam os acordes que formam a "
           "tonalidade."),

        h ("O campo harmônico maior"),
        p ("O campo harmônico é o conjunto de acordes que nasce naturalmente de "
           "uma escala maior. Se construirmos uma tríade (fundamental, terça e "
           "quinta) sobre cada grau da escala de Dó maior, obtemos sete acordes, "
           "cada um com uma qualidade (maior, menor ou diminuto)."),
        tbl ({ "Grau", "Acorde em Dó maior", "Qualidade" },
             { { "I", "C (Dó maior)", "maior" },
               { "ii", "Dm (Ré menor)", "menor" },
               { "iii", "Em (Mi menor)", "menor" },
               { "IV", "F (Fá maior)", "maior" },
               { "V", "G (Sol maior)", "maior" },
               { "vi", "Am (Lá menor)", "menor" },
               { "vii°", "Bdim (Si diminuto)", "diminuto" } }),
        p ("O padrão de qualidades é sempre o mesmo em qualquer tonalidade maior: "
           "maior, menor, menor, maior, maior, menor, diminuto. Em notação "
           "romana, escreve-se I–ii–iii–IV–V–vi–vii°. Maiúsculas indicam acordes "
           "maiores; minúsculas, menores; o símbolo ° indica diminuto."),
        p ("Esses sete acordes são a paleta do compositor naquela tonalidade. "
           "Praticamente toda música em Dó maior usa combinações desses acordes, "
           "porque eles compartilham as mesmas notas da escala."),
        c ("Exercício: toque a sequência I–vi–IV–V em Dó (C–Am–F–G). É a "
           "progressão mais famosa da música popular, usada em milhares de "
           "canções. Sinta como o V (Sol) puxa de volta para o I (Dó)."),

        h ("Funções harmônicas: tensão e repouso"),
        p ("Os sete acordes do campo harmônico se agrupam em três funções: "
           "repouso (tônica), preparação (subdominante) e tensão (dominante). "
           "Entender essas funções explica por que certas sequências soam "
           "\"certas\"."),
        tbl ({ "Função", "Graus", "Papel na música" },
             { { "Tônica", "I, vi (às vezes iii)", "repouso, chegada" },
               { "Subdominante", "IV, ii", "preparação, afastamento" },
               { "Dominante", "V, vii°", "tensão, pedido de resolução" } }),
        p ("O movimento harmônico mais comum é: tônica → subdominante → dominante "
           "→ tônica. Em Dó, isso dá C → F → G → C. É o esqueleto de inúmeras "
           "músicas. O dominante (V) cria a tensão que faz o retorno à tônica "
           "soar como uma conclusão."),
        c ("Cadência: é o nome desse movimento de conclusão. A cadência V–I "
           "(dominante para tônica) é a mais forte e a mais usada para encerrar "
           "frases musicais."),

        h ("O círculo das quintas"),
        p ("O círculo das quintas é um diagrama que organiza todas as tonalidades "
           "por distância de quinta. Cada passo no sentido horário sobe uma quinta "
           "justa (sete semitons) e acrescenta um sustenido à armadura; cada passo "
           "no sentido anti-horário desce uma quinta (sobe uma quarta) e "
           "acrescenta um bemol."),
        b ("Sentido dos sustenidos: Dó → Sol → Ré → Lá → Mi → Si → Fá♯ → Dó♯."),
        b ("Sentido dos bemóis: Dó → Fá → Si♭ → Mi♭ → Lá♭ → Ré♭ → Sol♭ → Dó♭."),
        p ("O círculo mostra por que as tonalidades vizinhas são parecidas: elas "
           "compartilham quase todas as notas e diferem em apenas uma. Dó e Sol "
           "diferem só no Fá/Fá♯; Sol e Ré diferem só no Dó/Dó♯. Isso explica por "
           "que é fácil modular (mudar de tom) entre tonalidades vizinhas."),
        c ("O círculo também serve para achar acidentes rapidamente: a tonalidade "
           "de Lá maior está a três passos de Dó no sentido dos sustenidos, então "
           "tem três sustenidos (Fá♯, Dó♯, Sol♯)."),

        h ("Relativa menor"),
        p ("Cada tonalidade maior tem uma tonalidade menor que usa exatamente as "
           "mesmas notas e a mesma armadura de clave. Ela é chamada relativa "
           "menor e está sempre uma terça menor abaixo da tônica maior (ou seja, "
           "no 6º grau da escala maior)."),
        tbl ({ "Tonalidade maior", "Relativa menor", "Notas iguais?" },
             { { "Dó maior", "Lá menor", "sim" },
               { "Sol maior", "Mi menor", "sim" },
               { "Ré maior", "Si menor", "sim" },
               { "Fá maior", "Ré menor", "sim" },
               { "Lá maior", "Fá♯ menor", "sim" } }),
        p ("Dó maior e Lá menor usam as mesmas sete notas (nenhum acidente). A "
           "diferença está no centro: em Dó maior, o repouso é o Dó; em Lá menor, "
           "o repouso é o Lá. Por isso o campo harmônico de Lá menor natural tem "
           "os mesmos acordes de Dó maior, apenas começando pelo Lá: Am, Bdim, C, "
           "Dm, Em, F, G."),
        c ("Isso explica por que muitas músicas \"tristes\" em Dó usam os acordes "
           "de Lá menor: elas compartilham as notas, mas mudam o centro de "
           "gravidade para o Lá, dando o caráter menor."),

        h ("Campo harmônico menor (introdução)"),
        p ("O campo harmônico menor é um pouco mais rico que o maior, porque "
           "existem três formas de escala menor: natural, harmônica e melódica. "
           "Para o iniciante, basta conhecer a menor natural e saber que a "
           "harmônica altera o 7º grau."),
        tbl ({ "Grau (Lá menor natural)", "Acorde", "Qualidade" },
             { { "i", "Am", "menor" },
               { "ii°", "Bdim", "diminuto" },
               { "III", "C", "maior" },
               { "iv", "Dm", "menor" },
               { "v", "Em", "menor" },
               { "VI", "F", "maior" },
               { "VII", "G", "maior" } }),
        p ("Na escala menor harmônica, o 7º grau sobe um semitom, e o acorde do "
           "5º grau vira maior (E, no caso de Lá menor). Esse E maior cria uma "
           "tensão mais forte e é muito usado para dar mais \"puxão\" de volta ao "
           "Am. É o mesmo princípio da dominante do campo maior."),
        c ("A apostila \"Desvendando os segredos da guitarra fusion\" explora "
           "exatamente esse tipo de raciocínio: como os acordes nascem da escala "
           "e como usar isso para compor e improvisar. Para o iniciante, basta "
           "fixar o campo maior e a ideia de relativa menor."),

        h ("Como usar tudo isso na prática"),
        p ("A teoria das tonalidades só serve se virar decisão musical. Veja como "
           "ela ajuda no dia a dia."),
        b ("Achar os acordes de uma música: identifique a tonalidade e use o campo "
           "harmônico dela."),
        b ("Transpor: mude a tonalidade e aplique os mesmos graus em outro centro."),
        b ("Compor: escolha as funções (repouso, preparação, tensão) para dar "
           "forma à música."),
        b ("Improvisar: sabendo a tonalidade, você sabe quais notas da escala "
           "funcionam sobre cada acorde."),
        c ("Resumo do tópico G: a escala maior é um padrão fixo de tons e "
           "semitons; dela nascem sete acordes (campo harmônico I–ii–iii–IV–V–vi–"
           "vii°); esses acordes têm funções de repouso, preparação e tensão; o "
           "círculo das quintas organiza as tonalidades; e cada maior tem uma "
           "relativa menor."),

        h ("Como estudar o tópico G na prática"),
        p ("Harmonia se aprende ouvindo e tocando, não decorando tabelas. Faça "
           "estes exercícios para transformar a teoria em som."),
        b ("Toque a escala de Dó maior e cante os graus (um, dois, três...) "
           "enquanto toca."),
        b ("Toque o campo harmônico de Dó em sequência (C–Dm–Em–F–G–Am–Bdim) e "
           "ouça a qualidade de cada acorde."),
        b ("Toque a progressão I–vi–IV–V (C–Am–F–G) várias vezes e sinta a "
           "resolução de volta ao C."),
        b ("Escolha uma música que você conhece e descubra a tonalidade pelo "
           "acorde final e pelos acidentes."),
        b ("Transponha uma progressão simples para outra tonalidade usando os "
           "graus, não os nomes."),
        c ("Meta do tópico: dado o nome de uma tonalidade maior, escrever os sete "
           "acordes do campo harmônico dela e dizer a função de cada um. Isso "
           "abre a porta para compor e improvisar."),

        h ("Resumo do tópico G"),
        tbl ({ "Ideia", "O que fixar" },
             { { "Tonalidade", "centro em torno de uma tônica" },
               { "Escala maior", "padrão T–T–S–T–T–T–S" },
               { "Campo harmônico", "I–ii–iii–IV–V–vi–vii°" },
               { "Funções", "tônica (repouso), subdominante (preparação), "
                            "dominante (tensão)" },
               { "Círculo das quintas", "organiza tonalidades por 5ªs" },
               { "Relativa menor", "mesma armadura, centro no 6º grau" } }),
    };
}

} // namespace cursomusica::content
