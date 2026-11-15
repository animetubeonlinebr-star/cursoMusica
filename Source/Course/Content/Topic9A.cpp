#include "Course/Content/Topics.h"

// Topic 9A — Acordes diminutos e suas funcoes (Modulo 9, Etapa 9).
// Fonte de verdade do texto: docs/MUSIC.md (bloco A da Etapa 9).
namespace cursomusica::content
{

std::vector<ContentItem> topic9A()
{
    return {

        p (
            "O acorde diminuto é uma das sonoridades mais reconhecíveis da harmonia. Ele soa instável, tenso e sempre pede para resolver em outro acorde. Neste tópico você aprende como ele é construído, como se escreve na cifra e — o mais importante — quais funções ele cumpre na música."),
        p (
            "Você já sabe montar tríades e tétrades empilhando terças. O diminuto segue a mesma lógica: é um empilhamento de terças menores. É justamente por empilhar sempre a mesma terça que ele se torna simétrico, e essa simetria explica quase tudo o que ele faz na harmonia."),
        c (
            "Objetivo do tópico: reconhecer o acorde diminuto de ouvido e pela cifra, entender as suas funções e saber tocá-lo no instrumento. Parte dos exercícios será tocada e o app vai reconhecer as notas."),

        h ("Como o acorde diminuto é construído"),
        p (
            "A tríade diminuta nasce de duas terças menores empilhadas sobre a tônica. Tomando Do como tônica: Do, Mib (terça menor) e Solb (outra terça menor sobre Mib). Os intervalos em semitons são 0, 3 e 6. Repare que a quinta do acorde — a distância de Do a Solb — é de 6 semitons, ou seja, uma quinta diminuta. É daí vem o nome."),
        p (
            "Quando acrescentamos mais uma terça menor sobre a quinta diminuta, chegamos ao acorde de sétima diminuta, o dim7. Sobre Do: Do, Mib, Solb e Lab. Em semitons: 0, 3, 6 e 9. Esse acorde de quatro notas é o que você mais vai encontrar na prática, porque ele é o motor de quase todas as resoluções com diminutos."),
        tbl ({ "Acorde", "Notas sobre Do", "Intervalos (semitons)", "Cifra" }, {
            { "Tríade diminuta", "Do - Mib - Solb", "0 - 3 - 6", "Cdim (ou Co)" },
            { "Sétima diminuta", "Do - Mib - Solb - Lab", "0 - 3 - 6 - 9", "Cdim7 (ou Co7)" },
            { "Meio-diminuto", "Do - Mib - Solb - Sib", "0 - 3 - 6 - 10", "Cm7(b5)" },
        }),
        c (
            "Atenção a diferença: o dim7 tem a sétima diminuta (9 semitons, igual a uma sexta maior); o meio-diminuto tem a sétima menor (10 semitons). São acordes diferentes, com funções diferentes."),
        img ("m9_diminuto_formacao", "Formação do diminuto: duas terças menores (tríade) e três terças menores (dim7)."),
        aud ({ "C4", "D#4", "F#4" }, "Tríade diminuta: Do - Mib - Solb. Som instável, que pede resolução."),
        aud ({ "C4", "D#4", "F#4", "A4" }, "Diminuto de sétima: Do - Mib - Solb - Lá. A sétima deixa a tensão ainda mais clara."),
        part ("m9_partitura_dim7", { "C4", "D#4", "F#4", "A4", "C5" },
              "Partitura do arpejo de Cdim7 subindo até a oitava. Ouça exatamente o que está escrito."),

        h ("A simetria: a propriedade que explica tudo"),
        p (
            "O dim7 tem uma propriedade rara: ele se repete a cada três semitons. Partindo de Do, contamos 3 semitons e chegamos a Mib; mais 3, a Solb; mais 3, a Lá; mais 3 e voltamos a Do. Como as terças menores se repetem em ciclo, o acorde não tem uma nota que se destaque como tônica. Qualquer uma das quatro notas pode ser lida como a fundamental."),
        p (
            "Essa simetria tem duas consequências práticas enormes. A primeira: só existem três dim7 diferentes em toda a música ocidental (os que começam em Do, em Do# e em Re). A segunda: o mesmo acorde pode servir a quatro tonalidades diferentes, porque as suas notas coincidem com a sétima de quatro dominantes distintos."),
        b ("Cdim7 = Ebdim7 = Gbdim7 = Adim7: mesmo som, quatro grafias."),
        b ("C#dim7 = Edim7 = Gdim7 = Bbdim7."),
        b ("Ddim7 = Fdim7 = Abdim7 = Bdim7."),
        c (
            "Por isso, ao ler um dim7 numa cifra, não se preocupe em decorar todas as grafias: pense nas quatro notas e no acorde a que ele vai resolver."),

        h ("As funções do acorde diminuto"),
        p (
            "O diminuto aparece em quatro situações principais na música popular, do jazz a MPB. Reconhecer cada uma delas é o que permite usar o acorde de forma consciente, em vez de apenas copiar formas do braço."),
        h ("1. Sensível (vii grau)"),
        p (
            "No campo harmônico maior, o sétimo grau gera um acorde diminuto. Em Do maior, esse acorde é Si diminuto (Si - Re - Fa). Ele conduz a tônica porque contém a sensível (Si) e a subdominante (Fa), as duas notas que puxam para Do. Tocar Si diminuto antes de Do cria uma resolução forte."),
        h ("2. Segundo grau no modo menor"),
        p (
            "No campo harmônico menor, o segundo grau é um acorde meio-diminuto. Em Lá menor, é Si meio-diminuto (Si - Re - Fa - Lá). Ele prepara o dominante (Mi7) e faz parte do ii-V-i menor, uma das progressões mais usadas do jazz."),
        h ("3. Diminuto de passagem"),
        p (
            "O diminuto também serve para ligar dois acordes por graus conjuntos. Colocado entre dois acordes, ele cria um cromatismo que movimenta a harmonia sem mudar o centro tonal. É um recurso comum em arranjos de bossa e de samba."),
        h ("4. Diminuto como substituto de dominante"),
        p (
            "Como o dim7 tem as mesmas notas da parte superior de um acorde dominante com nona bemol, ele pode substituir esse dominante. Um Dim7 colocado um semitom acima da tônica funciona como um dominante que resolve para ela. Voltaremos a essa ideia no tópico dos dominantes diminutos."),
        img ("m9_diminuto_funcoes", "As funções do diminuto: sensível, segundo grau menor, passagem e substituição de dominante."),

        h ("O diminuto no braço da guitarra"),
        p (
            "Na guitarra, o diminuto tem formas muito ágeis, justamente por causa da simetria. Como as terças menores se repetem a cada três casas, você pode mover a mesma digitação de três em três casas e continuar no mesmo acorde. Isso faz do dim7 um acorde fácil de deslocar pelo braço."),
        b ("Forma móvel: uma digitação que se repete de três em três casas."),
        b ("Nas cordas graves, o diminuto soa bem como acorde de passagem."),
        b ("No registro agudo, use três notas (tríade) para não pesar o som."),
        c (
            "Ao praticar, toque o mesmo dim7 em três posições diferentes do braço. O app reconhece as notas e confere se as classes de altura formam o acorde pedido."),

        h ("Como identificar o diminuto de ouvido"),
        p (
            "O diminuto tem um som tenso, mas simétrico. Diferente do dominante, que tem uma direção clara, o diminuto parece suspenso e instável em todas as direções. Ouvir essa instabilidade é o primeiro passo para reconhecê-lo. Associe-o a ideia de algo que não está resolvido."),
        b ("Som instável, que pede continuação."),
        b ("Sem nota de repouso clara: qualquer nota soa como tensão."),
        b ("Aparece em passagens cromáticas e em momentos de suspense."),
        aud ({ "C4", "D#4", "F#4", "A4", "C5", "A4", "F#4", "D#4" },
             "Arpejo do dim7 subindo e descendo: repare na simetria do som."),

        h ("Erros comuns ao estudar o diminuto"),
        p (
            "Alguns enganos aparecem sempre que o aluno encontra o diminuto pela primeira vez. Conhecê-los ajuda a evitá-los."),
        b ("Confundir dim7 com meio-diminuto: a sétima é diferente (9 contra 10 semitons)."),
        b ("Decorar só uma grafia do acorde: são quatro nomes para as mesmas notas."),
        b ("Tentar dar função de tônica ao diminuto: ele nunca é um repouso."),
        c (
            "Se o diminuto soar resolvido, algo está errado na execução — provavelmente faltou uma nota ou a sétima foi tocada errada."),

        h ("Aplicando na prática"),
        p (
            "Comece tocando o diminuto como acorde de passagem entre dois acordes do seu repertório. Depois experimente usa-lo como sensível, antes da tônica. Por fim, explore a substituição de dominante, trocando um acorde dominante pelo diminuto correspondente. Em cada caso, o objetivo é ouvir a resolução."),
        b ("Passagem: toque o diminuto entre dois acordes por graus conjuntos."),
        b ("Sensível: toque o diminuto um semitom abaixo da tônica."),
        b ("Substituição: toque o diminuto no lugar do dominante."),
        aud ({ "B3", "D4", "F4", "G4" }, "Si diminuto resolvendo em Do: a sensível puxa para a tônica."),

        h ("A diferença entre o diminuto e os outros acordes"),
        p (
            "Para reconhecer o diminuto, ajude comparando-o com os acordes que você já conhece. Uma tríade maior (Do, Mi, Sol) tem uma terça maior e uma quinta justa. Uma tríade menor (Do, Mib, Sol) tem uma terça menor e uma quinta justa. Uma tríade diminuta (Do, Mib, Solb) tem uma terça menor e uma quinta diminuta. Basta alterar a quinta para que o acorde mude de caráter: de estável para instável."),
        p (
            "O acorde aumentado segue a lógica inversa: Do, Mi, Sol#. Ele tem a terça maior e a quinta aumentada. Diminuto e aumentado são os dois extremos: um estreita a quinta, o outro alarga. Os dois são simétricos e os dois soam instáveis, mas de maneiras diferentes — o diminuto pede resolução, o aumentado flutua."),
        tbl ({ "Tríade", "Notas sobre Do", "Intervalos (semitons)", "Sensação" }, {
            { "Maior", "Do - Mi - Sol", "0 - 4 - 7", "estável, alegre" },
            { "Menor", "Do - Mib - Sol", "0 - 3 - 7", "estável, triste" },
            { "Diminuta", "Do - Mib - Solb", "0 - 3 - 6", "instável, pede resolução" },
            { "Aumentada", "Do - Mi - Sol#", "0 - 4 - 8", "flutuante, suspensa" },
        }),
        c (
            "Guardar esse quadro ajuda muito: as quatro tríades nascem da mesma tônica, mudando apenas a terça e a quinta. O diminuto e o aumentado são as duas versões instáveis."),

        h ("O diminuto na escrita musical"),
        p (
            "Na partitura, o diminuto aparece com a quinta e a sétima abaixadas em relação ao acorde maior. A cifra usa o símbolo de grau (o) ou a abreviação dim. Quando você lê uma cifra como Cdim7, já sabe que as notas são Do, Mib, Solb e Lab — quatro notas, todas a uma terça menor de distância. Reconhecer isso pela cifra acelera muito a leitura."),
        b ("Cdim ou Co: tríade diminuta."),
        b ("Cdim7 ou Co7: sétima diminuta (quatro notas)."),
        b ("Cm7(b5): meio-diminuto (sétima menor)."),
        b ("Na partitura, a quinta e a sétima aparecem rebaixadas."),

        h ("O diminuto é a condução de vozes"),
        p (
            "Uma das razões pelas quais o diminuto é tão usado é a sua capacidade de conduzir as vozes por semitons. Como as suas notas estão muito proximas das notas do acorde seguinte, a passagem de um para o outro quase não tem saltos. Esse movimento suave é o que faz a resolução soar natural, mesmo quando a harmonia muda de direção."),
        b ("As notas do diminuto ficam a um semitom do acorde seguinte."),
        b ("Por isso a resolução soa suave e natural."),
        b ("O baixo pode descer ou subir cromaticamente até a tônica."),
        aud ({ "C#4", "E4", "G4", "A#4", "C4", "E4", "G4", "C5" },
             "Dim7 de Reb resolvendo em Do: as vozes se movem por semitons."),

        h ("O diminuto no repertório"),
        p (
            "Você encontra o diminuto em quase todos os estilos. No choro e no samba, ele aparece como acorde de passagem, ligando dois acordes por graus conjuntos. No jazz, é onipresente: como substituto de dominante, como sensível e como cor sobre acordes menores. Na MPB, ele colore as passagens mais elaboradas. Reconhecer o diminuto de ouvido ajuda a tirar músicas de ouvido com mais facilidade."),
        b ("Choro e samba: acorde de passagem."),
        b ("Jazz: substituto de dominante e sensível."),
        b ("MPB: coloração em passagens elaboradas."),

        h ("Resumo do tópico"),
        b ("Diminuto = terças menores empilhadas (0-3-6; dim7 = 0-3-6-9)."),
        b ("E simétrico: só existem três dim7 diferentes."),
        b ("Funções: sensível, ii grau menor, passagem e substituto de dominante."),
        b ("No braço, a mesma forma se repete de três em três casas."),
        b ("Soa instável e sempre pede resolução."),
        c (
            "Nos exercícios deste tópico, toque o acorde diminuto no instrumento. O app reconhece as notas e confere as classes de altura, então qualquer posição do braço vale."),
    };
}

} // namespace cursomusica::content
