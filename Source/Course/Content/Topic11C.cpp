#include "Course/Content/Topics.h"

// Topic 11C — Pentatônica menor 7 (Módulo 11, Etapa 11).
// Fonte primária: "Desvendando os Segredos da Guitarra Fusion" (José Ricardo
// Santana), cap. 2 — "PENTATÔNICA MENOR 7": "a escala pentatônica menor 7 é
// formada por 5 notas" (tônica, terça menor, quarta justa, quinta justa, sétima
// menor). O "7" nomeia a qualidade do acorde (m7) para o qual a escala serve, e
// não uma sexta nota acrescentada: é a pentatônica menor de sempre, 1-b3-4-5-b7.
namespace cursomusica::content
{

std::vector<ContentItem> topic11C()
{
    return {

        p (
            "A pentatônica menor você já toca — e é justamente ela que a apostila chama de pentatônica menor 7. O nome assusta, mas não há nota nova para decorar: a escala pentatônica menor 7 tem cinco notas, as mesmas cinco da pentatônica menor que você conhece. O que o nome diz é outra coisa: a sétima menor (b7) já está dentro dela, e é essa sétima que faz a escala servir tão bem aos acordes de sétima menor, o famoso som de blues."),
        p (
            "Entender o nome é o primeiro passo para não se perder. A pentatônica menor é 1, b3, 4, 5 e b7. Como ela já contém a sétima menor, ela encaixa como uma luva sobre os acordes menores com sétima (m7) — daí o nome pentatônica menor 7. A apostila de fusion, que é a nossa referência aqui, é explícita: a escala pentatônica menor 7 é formada por cinco notas, e não por seis."),
        c (
            "Pentatônica menor 7 = pentatônica menor = 1, b3, 4, 5 e b7. Em Lá: A-C-D-E-G. Cinco notas. O sete do nome é a sétima menor (o Sol em Lá), que já pertence à escala e dá a ela o som do acorde m7."),

        h ("O que o nome 7 quer dizer"),
        p (
            "Muita gente acha que a pentatônica menor 7 é a pentatônica menor com uma nota extra acrescentada. Não é. A escala continua tendo cinco notas por oitava; o que muda é o nome, que descreve para que a escala serve. Como ela contém a sétima menor, ela é a pentatônica própria dos acordes de sétima menor. Por isso a apostila a chama de pentatônica menor 7 e não apenas de pentatônica menor."),
        p (
            "A prova está nas notas. Em Lá, a pentatônica menor é A-C-D-E-G. O Sol é a sétima menor de Lá, e é essa nota que dá à escala o seu caráter de blues. Quando você improvisa com essas cinco notas sobre um Am7, cada nota cai bem: o Lá, o Dó e o Mi são as notas do acorde; o Ré é a quarta, que soa estável; e o Sol é a sétima menor, que dá o tempero. Nenhuma nota briga com o acorde."),
        b ("A pentatônica menor 7 tem cinco notas: 1, b3, 4, 5 e b7."),
        b ("O nome 7 descreve a sétima menor que já está dentro da escala."),
        b ("Em Lá, a escala é A-C-D-E-G: as mesmas notas da pentatônica menor."),
        img ("m11_pent_menor7", "Pentatônica menor 7 de Lá: cinco notas (A C D E G). A sétima menor (Sol) já pertence à escala e dá o som do acorde m7."),

        h ("Onde a pentatônica menor 7 vive"),
        p (
            "A pentatônica menor 7 é a escala mais usada do blues e do rock. Ela aparece sobre os acordes menores com sétima — os graus i e iv do blues —, onde fornece tanto as notas do acorde quanto uma cor adicional. No jazz, ela é o ponto de partida do fraseado menor: antes de estudar os modos, o guitarrista já improvisa com a pentatônica sobre o m7."),
        p (
            "A apostila de fusion mostra exatamente isso na sua tabela de aplicação: sobre um Cm7, a pentatônica menor 7 de C é a escolha direta; sobre os acordes vizinhos do campo, ela é aplicada por deslocamento, gerando as tensões de cada acorde. Aprender a pentatônica menor 7 numa posição é aprender o centro a partir do qual as outras aplicações se organizam."),
        tbl ({ "Contexto", "Acorde", "Por que a pentatônica menor 7 serve" }, {
            { "Blues", "i7 e iv7", "contém as notas do acorde e a sétima menor (cor)" },
            { "Rock / metal", "menor com sétima", "som menor direto, sem notas estranhas" },
            { "Jazz", "m7", "base do fraseado antes dos modos" },
        }),
        c (
            "Nota de repouso × tensão (REQ-011/REQ-012): sobre um Am7, as cinco notas da pentatônica menor 7 (A-C-D-E-G) são todas de repouso — as do acorde mais a quarta e a sétima menor, que soam estáveis. Este é o tópico do repouso; a tensão aparece quando você sai dessas notas sem ser pedido."),

        h ("O lick deste tópico"),
        p (
            "O lick abaixo sobe e desce a pentatônica menor 7 de Lá, destacando o Sol — a sétima menor que dá o nome à escala. É um gesto de blues, no estilo dos guitarristas citados pela apostila: você sobe pela escala, toca o Sol no ponto mais alto da frase e recolhe. Ouça como a sétima menor é uma nota de chegada, não de tensão."),
        aud ({ "A4", "C5", "D5", "E5", "G5", "A5", "G5", "E5", "D5", "C5", "A4" },
             "Lick do tópico C: a pentatônica menor 7 de Lá. O Sol (b7) é a nota que dá o nome e o caráter de blues à escala."),
        part ("m11_partitura_c", { "A4", "C5", "D5", "E5", "G5", "A5", "G5", "E5", "D5", "C5", "A4" },
              "Partitura do lick C: a pentatônica menor 7 de Lá (A C D E G). Cinco notas, com a sétima menor (Sol) no topo da frase."),

        h ("Estudar a pentatônica menor 7"),
        p (
            "Estude a escala como você estudaria qualquer pentatônica: suba e desça as cinco notas, devagar, ouvindo cada grau. Depois, toque a escala parando na sétima menor (o Sol) e resolvendo na tônica. O objetivo é reconhecer o som do m7 — a sétima menor é o que faz a escala soar como acorde, e não apenas como uma sequência de notas. Toque o mesmo lick sobre um Am7 e sinta o encaixe."),

        h ("A sétima menor no blues e no rock"),
        p (
            "No blues, a sétima menor é a nota de repouso do acorde i7. Você sobe pela pentatônica menor 7 e usa o Sol como nota de chegada, sem pressa de resolver. É o oposto da tensão: a sétima menor conforta. É por isso que a pentatônica menor 7 é a escala padrão do blues — ela já contém, entre as suas cinco notas, a sétima que o acorde pede."),
        p (
            "No rock e no metal, a pentatônica menor 7 é a base dos solos menores. A sétima menor dá o peso do acorde, e as outras notas (a terça menor, a quarta e a quinta) completam o vocabulário. Quando o guitarrista quer uma tensão, ele sai da pentatônica e acrescenta uma nota de fora; enquanto fica dentro dela, tudo é repouso."),
        tbl ({ "Uso", "Papel da sétima menor", "Efeito" }, {
            { "Blues (i7)", "nota de chegada", "sabor de acorde, repouso" },
            { "Rock (menor)", "peso do acorde", "som menor direto" },
            { "Jazz (m7)", "base do fraseado", "ponto de partida dos modos" },
        }),
        b ("A sétima menor é nota de repouso da escala, não de tensão."),
        b ("É ela que dá à pentatônica o nome de menor 7 e o som do acorde m7."),
        b ("No blues, ela aparece como nota de chegada; no rock, como peso."),

        h ("Comparando com a pentatônica menor 6"),
        p (
            "A pentatônica menor 7 e a pentatônica menor 6 são irmãs: as duas são pentatônicas menores, com cinco notas, e diferem em um único grau. Na menor 7, o quinto grau da escala é a sétima menor (b7); na menor 6, é a sexta maior (6). Em Lá, a menor 7 termina em Sol; a menor 6 termina em Fá sustenido. Trocar uma pela outra troca o som do acorde de m7 para m6."),
        p (
            "As duas nunca aparecem juntas na mesma pentatônica, porque a b7 e a 6 são graus diferentes do mesmo lugar. Você escolhe uma ou outra conforme o acorde que está tocando: sobre Am7, use a pentatônica menor 7 (com o Sol); sobre Am6, use a pentatônica menor 6 (com o Fá sustenido). É o acorde que decide qual das duas pentatônicas encaixa."),
        c (
            "A diferença entre a pentatônica menor 7 e a menor 6 é uma só nota: a sétima menor (b7) no lugar da sexta maior (6). Sobre m7, use a menor 7; sobre m6, use a menor 6. Este tópico é a menor 7; o próximo é a menor 6."),

        h ("A sétima menor e o ouvido"),
        p (
            "Toda escala tem um grau que a define. Na pentatônica menor 7, esse grau é a sétima menor: é ela que faz o ouvido reconhecer o som do acorde de sétima menor. Quando você toca a pentatônica sem pensar, o ouvido espera o Sol; quando ele chega, a frase parece completa. É esse reconhecimento que a apostila chama de sonoridade do m7."),
        p (
            "Treine o ouvido tocando a escala e parando na sétima menor, sem resolver. O ouvido vai sentir que a frase está estável — porque a sétima menor é repouso, não tensão. Compare com a sensação de parar numa tensão verdadeira, como a sétima maior. A diferença entre repouso e tensão é a base de todo o fraseado, e a pentatônica menor 7 é onde ela começa."),

        h ("A sétima menor e as posições do braço"),
        p (
            "A pentatônica menor 7 tem cinco posições, uma por nota da escala, e a sétima menor aparece em todas elas. Isso significa que, quando você aprende a escala numa posição, aprende também onde a sétima está nas outras. É esse mapeamento que permite usar o som do m7 em qualquer região do braço, sem depender de uma posição específica."),
        p (
            "Um bom exercício é tocar a sétima menor em cada posição da pentatônica e resolvê-la na tônica mais próxima. Você percebe que a sétima é sempre o mesmo gesto (a nota que fica logo abaixo da tônica, no caminho de descida), apenas transportado para outra região. Quando o gesto fica automático, a sonoridade do m7 deixa de ser uma posição e passa a ser um som que a mão encontra sozinha."),
        p (
            "Não confunda a sétima menor com a sétima maior. A sétima menor (b7) é nota de repouso da pentatônica menor 7 — em Lá, o Sol. A sétima maior (7) é outra nota, um semitom acima (o Sol sustenido), e não pertence a esta escala. O nome pentatônica menor 7 refere-se à sétima menor; se você tocar o Sol sustenido, já saiu da escala e entrou na tensão."),
        b ("A sétima menor está em todas as posições da pentatônica menor 7."),
        b ("Tocar a sétima e resolver na tônica mais próxima fixa o gesto."),
        b ("Não confunda a sétima menor (b7, repouso) com a sétima maior (7, tensão)."),
        tbl ({ "Nota", "Grau", "Função" }, {
            { "b7 (Sol em Lá)", "sétima menor", "repouso; dá o nome à escala" },
            { "7 (Sol# em Lá)", "sétima maior", "não pertence a esta escala" },
            { "1 (Lá)", "tônica", "nota de chegada da frase" },
        }),

        h ("A sétima menor como repouso"),
        p (
            "Na pentatônica menor 7, todas as cinco notas são de repouso. Isso é uma vantagem e um risco. A vantagem é que você pode tocar qualquer nota da escala sem medo de errar: sobre o m7, todas encaixam. O risco é que uma frase feita só de repouso pode soar sem direção, porque nada puxa para lugar nenhum. A apostila resolve isso pelo ritmo e pelo desenho, não por notas de fora."),
        p (
            "Quando você quiser criar movimento dentro da pentatônica menor 7 sem sair dela, use o ritmo: comece no tempo forte, acelere, freie. A escala dá as notas estáveis; o ritmo dá o movimento. É por isso que a pentatônica é tão usada no blues: ela é toda repouso, e o blues constrói a tensão pelo tempo, não pela nota."),
        p (
            "Guarde a distinção para o resto do módulo. Nos tópicos das escalas menor harmônica e menor melódica, você vai encontrar notas de tensão de verdade, que precisam ser resolvidas. Aqui, na pentatônica menor 7, você está no terreno do repouso: o objetivo é dominar as cinco notas e o som do m7, não criar tensão. A tensão fica para quando o exercício pedir."),
        b ("Todas as notas da pentatônica menor 7 são de repouso sobre o acorde m7."),
        b ("O movimento dentro da escala vem do ritmo e do desenho, não de notas de fora."),
        b ("Tensão de verdade fica para as escalas dos próximos tópicos."),
        tbl ({ "Tipo de nota", "Exemplo em Lá", "Função" }, {
            { "Acorde (m7)", "A C E G", "repouso: notas do acorde" },
            { "Quarta", "D", "repouso: som estável sobre o m7" },
            { "Tensão (fora)", "F, G#", "só quando o exercício pedir" },
        }),

        c (
            "Meta do módulo: 100 BPM. Toque o lick com a sétima menor (Sol) como nota de chegada, no metrônomo, até a frase ficar parelha. A escala é toda repouso; a precisão do tempo é o que dá a ela direção."),
    };
}

} // namespace cursomusica::content
