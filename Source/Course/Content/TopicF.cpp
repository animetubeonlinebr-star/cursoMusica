#include "Course/Content/Topics.h"

// Topic F — Sistema 5 (CAGED).
// Sources: pdf-caged-e-derivaoes-de-acordes-marcelo-mello (five movable shapes,
// their connection and the scale over each shape) and pdf-fraseado-melodico
// (section "Sistema 5 - Acordes x Escalas").
namespace cursomusica::content
{

std::vector<ContentItem> topicF()
{
    return {
        p ("O sistema CAGED (ou Sistema 5) é o método mais usado no mundo para "
           "organizar o braço da guitarra. A ideia é simples e poderosa: cinco "
           "formas básicas de acorde maior — Dó, Lá, Sol, Mi e Ré — cobrem todo o "
           "braço e se conectam entre si. Aprender essas cinco formas é aprender a "
           "tocar qualquer acorde em qualquer região, e é a ponte entre acordes e "
           "escalas. O nome do sistema vem justamente das iniciais dessas formas "
           "em inglês: C, A, G, E, D."),

        h ("A origem das cinco formas"),
        img ("f_caged_cinco_formas", "As cinco formas de Dó maior: C, A, G, E, D."),
        p ("As cinco formas do CAGED nascem dos acordes abertos que todo iniciante "
           "aprende na primeira posição: Dó, Lá, Sol, Mi e Ré. Cada uma dessas "
           "formas pode ser transformada em uma forma móvel com o uso da pestana "
           "(tópico E). Assim, elas deixam de valer só na primeira posição e "
           "passam a poder ser levadas para qualquer casa do braço."),
        p ("A genialidade do sistema é perceber que essas cinco formas, quando "
           "deslocadas e conectadas, cobrem a extensão inteira do braço sem deixar "
           "buracos. O braço inteiro é dividido em cinco regiões, uma para cada "
           "forma."),
        tbl ({ "Forma", "Acorde aberto de origem", "Corda da fundamental" },
             { { "C", "Dó maior", "5ª corda" },
               { "A", "Lá maior", "5ª corda" },
               { "G", "Sol maior", "6ª corda" },
               { "E", "Mi maior", "6ª corda" },
               { "D", "Ré maior", "4ª corda" } }),
        c ("A ordem das letras — C, A, G, E, D — não é arbitrária: é a ordem em "
           "que as formas aparecem subindo pelo braço. Por isso o sistema se "
           "chama CAGED e não, digamos, DGEAC."),

        h ("Todas as cinco formas para um mesmo acorde"),
        p ("O primeiro passo é entender que as cinco formas podem representar o "
           "mesmo acorde, em regiões diferentes do braço. Tomemos o acorde de Dó "
           "maior. Ele pode ser tocado com a forma de C na primeira posição, com a "
           "forma de A na 3ª casa, com a forma de G na 5ª casa, com a forma de E "
           "na 8ª casa e com a forma de D na 10ª casa."),
        tbl ({ "Forma", "Posição (casa)", "Região do braço" },
             { { "C", "0–3", "primeira posição" },
               { "A", "3–5", "região da 3ª casa" },
               { "G", "5–8", "região da 5ª casa" },
               { "E", "8–12", "região da 8ª casa" },
               { "D", "10–12", "região da 10ª casa" } }),
        p ("Todas essas posições produzem o mesmo acorde de Dó maior, apenas em "
           "oitavas e timbres diferentes. Isso dá ao guitarrista enorme liberdade: "
           "pode escolher a região que melhor encaixa na música e na melodia que "
           "está tocando."),
        c ("Exercício mental: pegue a forma de Mi maior (a mais fácil de mover) e "
           "deslize-a pela 6ª corda. A fundamental segue a 6ª corda: casa 1 dá Fá, "
           "casa 3 dá Sol, casa 5 dá Lá, casa 8 dá Dó. Você acabou de gerar quatro "
           "acordes com uma única forma."),

        h ("As formas se conectam"),
        img ("f_caged_conexao", "As formas cobrem o braço em regiões que se conectam."),
        p ("O segundo conceito do CAGED é a conexão. As formas não são ilhas: cada "
           "uma termina onde a próxima começa. A última nota de uma forma é a "
           "primeira nota da forma seguinte. Isso permite deslizar de uma região "
           "para outra sem interromper a música."),
        p ("A sequência de conexão é sempre C → A → G → E → D → C, subindo pelo "
           "braço, e depois repete uma oitava acima. Cada forma \"encosta\" na "
           "seguinte, formando uma corrente contínua que cobre as doze casas."),
        b ("A forma de C conecta-se à forma de A."),
        b ("A forma de A conecta-se à forma de G."),
        b ("A forma de G conecta-se à forma de E."),
        b ("A forma de E conecta-se à forma de D."),
        b ("A forma de D conecta-se novamente à forma de C, uma oitava acima."),
        c ("Por que isso importa? Porque a melodia de uma música raramente fica "
           "parada numa só região. Saber conectar as formas permite acompanhar "
           "qualquer melodia sem perder a mão."),

        h ("CAGED e escalas: cada forma contém uma escala"),
        img ("f_caged_escala", "A escala de Dó maior sobre o braço."),
        p ("O terceiro conceito — e o mais poderoso para quem quer improvisar — é "
           "que cada forma de acorde contém a escala daquela tonalidade. Sobre a "
           "forma de Dó, você encontra a escala de Dó maior (e a pentatônica de "
           "Dó). Isso significa que, onde há um acorde, há também as notas "
           "disponíveis para solar."),
        b ("Forma de C: contém a escala de Dó maior na região da primeira posição."),
        b ("Forma de A: contém a mesma escala de Dó maior, na região da 3ª casa."),
        b ("Forma de G: contém a escala de Dó maior na região da 5ª casa."),
        b ("Forma de E: contém a escala de Dó maior na região da 8ª casa."),
        b ("Forma de D: contém a escala de Dó maior na região da 10ª casa."),
        p ("A apostila de Marcelo Mello descreve isso como \"escala local\" (home "
           "scale): a digitação da escala que corresponde à forma do acorde "
           "naquela região. As duas notas mais importantes da escala local são a "
           "fundamental (tônica) e a quinta, porque elas definem a resolução da "
           "frase."),
        c ("É por isso que o CAGED é considerado a ponte entre acompanhamento e "
           "improviso: o mesmo mapa que serve para tocar acordes serve para solar "
           "sobre eles."),

        h ("As formas servem para acordes menores e de sétima"),
        p ("As cinco formas não servem só para acordes maiores. Mudando a "
           "qualidade — ou seja, alterando algumas notas —, cada forma passa a "
           "representar acordes menores, com sétima, com nona, e assim por diante."),
        tbl ({ "Qualidade", "O que muda na forma", "Exemplo" },
             { { "Maior", "forma original", "C" },
               { "Menor", "abaixa a terça em um semitom", "Cm" },
               { "Sétima dominante", "acrescenta a sétima menor", "C7" },
               { "Sétima maior", "acrescenta a sétima maior", "C7M" },
               { "Menor com sétima", "terça menor + sétima menor", "Cm7" } }),
        p ("A vantagem é que a posição da fundamental (a nota que dá nome ao "
           "acorde) permanece a mesma. Se você sabe que a forma de Mi tem a "
           "fundamental na 6ª corda, sabe que uma forma de Mi menor com sétima "
           "também terá a fundamental ali."),
        c ("Cuidado: a qualidade do acorde (maior, menor, sétima) muda a digitação "
           "das notas internas, mas não a lógica do sistema. Continue pensando em "
           "regiões e formas; só ajuste as notas."),

        h ("Como praticar o CAGED passo a passo"),
        p ("O CAGED se aprende por camadas. Não tente memorizar as cinco formas de "
           "uma vez."),
        b ("Etapa 1 — uma forma móvel: domine a forma de Mi maior com pestana, "
           "moviendo-a pela 6ª corda e nomeando o acorde em cada casa."),
        b ("Etapa 2 — duas formas: acrescente a forma de Lá, movendo-a pela 5ª "
           "corda."),
        b ("Etapa 3 — o ciclo completo: para uma única tonalidade (por exemplo, "
           "Dó), toque as cinco formas em sequência, subindo pelo braço."),
        b ("Etapa 4 — conexão: toque as cinco formas sem pausa, ligando uma à "
           "outra, sentindo como a mão desliza pelo braço."),
        b ("Etapa 5 — escalas: sobre cada forma, toque a escala da tonalidade e "
           "identifique a fundamental e a quinta."),
        c ("Progressão do app: o exercício EX-1.F.1 pede para montar C, G, D, Am e "
           "Em e identificar a forma CAGED de cada um; o EX-1.F.2 pede para mover a "
           "forma de Mi e nomear o acorde resultante."),

        h ("O que é a \"posição local\" (home position)"),
        p ("A apostila de Marcelo Mello destaca dois conceitos úteis: a posição "
           "local e a escala local. A posição local é uma região do braço onde "
           "você se sente em casa — um ponto de referência a partir do qual você "
           "pode improvisar sem se perder."),
        p ("A escala local é a digitação da escala que corresponde àquela forma. "
           "Quando você improvisa, pode ficar dentro de uma região (usando uma "
           "forma) ou transitar entre regiões (conectando as formas). Os dois "
           "caminhos são válidos; a escolha depende do efeito que você quer."),
        c ("Para o iniciante, o mais importante é ter pelo menos uma posição local "
           "bem dominada. A partir dela, a confiança cresce e as outras formas "
           "vão sendo incorporadas."),

        h ("Erros comuns no estudo do CAGED"),
        p ("O CAGED é simples em conceito, mas alguns erros atrasam o aprendizado."),
        b ("Decorar as formas como desenhos soltos, sem entender que são regiões "
           "conectadas. Sempre pense na conexão C→A→G→E→D."),
        b ("Esquecer a fundamental. Em cada forma, saiba qual nota dá o nome ao "
           "acorde e em qual corda ela está."),
        b ("Estudar só os acordes maiores. Lembre que as formas valem para "
           "menores e sétimas com pequenos ajustes."),
        b ("Tentar tocar as cinco formas rápido demais, sem clareza de som. "
           "Devagar e limpo vence."),
        c ("Regra de ouro: o CAGED não é um conjunto de desenhos para decorar; é "
           "um mapa para entender o braço. Se você entende o mapa, as formas se "
           "organizam sozinhas."),

        h ("Comparando as cinco formas: onde está a fundamental"),
        p ("Para usar o CAGED com fluência, você precisa saber, de memória, em "
           "qual corda está a fundamental de cada forma. Essa é a informação que "
           "diz o nome do acorde em qualquer posição."),
        tbl ({ "Forma", "Corda da fundamental", "Como achar o nome do acorde" },
             { { "C", "5ª corda (Lá)", "nota da 5ª corda na pestana" },
               { "A", "5ª corda (Lá)", "nota da 5ª corda na pestana" },
               { "G", "6ª corda (Mi)", "nota da 6ª corda na pestana" },
               { "E", "6ª corda (Mi)", "nota da 6ª corda na pestana" },
               { "D", "4ª corda (Ré)", "nota da 4ª corda na pestana" } }),
        p ("Exemplo: se você toca a forma de Mi com pestana na 3ª casa, a "
           "fundamental é a nota da 6ª corda na 3ª casa, que é Sol. Logo, o acorde "
           "é Sol maior. Se toca a forma de Lá com pestana na 3ª casa, a "
           "fundamental é a nota da 5ª corda na 3ª casa, que é Dó. Logo, é Dó "
           "maior."),
        c ("Esse é o segredo para nunca mais se perder: a forma diz o desenho, a "
           "corda da fundamental diz o nome. Com essas duas informações, você "
           "nomeia qualquer acorde em qualquer casa."),

        h ("CAGED no dia a dia: por que ele ajuda tanto"),
        p ("Talvez você se pergunte por que investir tempo no CAGED quando já sabe "
           "tocar alguns acordes. A resposta está na liberdade que ele dá em "
           "situações reais de música."),
        b ("Trocar de tom: com as formas móveis, você transpõe uma música inteira "
           "sem aprender acordes novos."),
        b ("Escolher a região certa: se a melodia está aguda, você toca o acorde "
           "numa região mais grave para não competir; se está grave, faz o "
           "contrário."),
        b ("Seguir a melodia: acompanhar um cantor ou um solo fica muito mais "
           "fácil quando você enxerga o braço como um mapa de formas."),
        b ("Improvisar: cada forma traz a escala correspondente, então o CAGED "
           "abre caminho para o solo."),
        c ("Resumo do tópico F: cinco formas (C, A, G, E, D), móveis com pestana, "
           "conectadas na ordem C→A→G→E→D, cada uma contendo a escala da "
           "tonalidade e com a fundamental numa corda específica. Isso é o mapa "
           "completo do braço."),

        h ("Resumo do tópico F"),
        tbl ({ "Ideia", "O que fixar" },
             { { "Cinco formas", "C, A, G, E, D (acordes abertos)" },
               { "Mobilidade", "com pestana, valem em qualquer casa" },
               { "Cobertura", "as cinco formas cobrem todo o braço" },
               { "Conexão", "C → A → G → E → D, e recomeça uma oitava acima" },
               { "Escalas", "cada forma contém a escala da tonalidade" },
               { "Qualidades", "valem para menores e sétimas com ajustes" },
               { "Fundamental", "corda da fundamental depende da forma" } }),

        h ("Como estudar o tópico F na prática"),
        p ("O CAGED entra na mão com repetição lenta e consciente. Faça este "
           "roteiro algumas vezes por semana."),
        b ("Toque as cinco formas de Dó maior, subindo pelo braço, uma após a "
           "outra, sem pausa."),
        b ("Desça pelo braço na ordem inversa (D→E→G→A→C)."),
        b ("Escolha uma tonalidade por dia e faça as cinco formas dela."),
        b ("Sobre cada forma, toque a escala correspondente e cante a fundamental."),
        b ("Toque uma música usando duas ou três regiões diferentes, conectando "
           "as formas."),
        c ("Meta do tópico: tocar as cinco formas de uma tonalidade, conectadas e "
           "limpas, e identificar a fundamental de cada uma. Com isso, você "
           "domina o mapa do braço."),
    };
}

} // namespace cursomusica::content
