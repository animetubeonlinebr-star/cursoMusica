#include "Course/Content/Topics.h"

// Topic C — Sustenidos e bemóis (acidentes, cromatismo e enarmonia).
// Sources: pdf-teoria-elementar-da-musica-ricordi-osvaldo-lacerda (semitom,
// tom, acidentes) and pdf-fraseado-melodico (cromatismo).
namespace cursomusica::content
{

std::vector<ContentItem> topicC()
{
    return {
        p ("No tópico B você viu que existem sete notas naturais e que, entre "
           "algumas delas, sobra espaço para uma nota intermediária. Este tópico "
           "trata exatamente dessas notas: como nomeá-las com os sinais de "
           "sustenido e bemol, por que dois nomes podem representar o mesmo som e "
           "como isso se organiza na escala cromática. É a base do cromatismo, "
           "muito usado em solos, blues e jazz."),

        h ("O semitom como unidade de medida"),
        p ("Toda a lógica dos acidentes nasce do semitom. Lembre-se: o semitom é a "
           "menor distância entre duas notas na música ocidental, e o tom equivale "
           "a dois semitons. Se você subir de semitom em semitom a partir de uma "
           "nota, passa por todas as alturas possíveis até voltar à nota inicial "
           "uma oitava acima."),
        p ("Entre duas notas naturais vizinhas separadas por um tom (como Dó–Ré) "
           "existe uma altura intermediária. Precisamos de um nome para ela. Se a "
           "nomeamos a partir da nota de baixo, usamos o sustenido; se a nomeamos "
           "a partir da nota de cima, usamos o bemol."),
        tbl ({ "Distância", "Símbolo", "Efeito sobre a nota" },
             { { "Semitom", "♯ (sustenido)", "sobe meio-tom" },
               { "Semitom", "♭ (bemol)", "desce meio-tom" },
               { "Dois semitons", "♯♯ (duplo sustenido)", "sobe um tom inteiro" },
               { "Dois semitons", "♭♭ (duplo bemol)", "desce um tom inteiro" },
               { "Semitom", "♮ (bequadro)", "cancela um acidente anterior" } }),
        c ("O bequadro (♮) não sobe nem desce: ele cancela. Serve para voltar à "
           "nota natural depois de um acidente. É o \"desfazer\" da notação."),

        h ("O sustenido (♯)"),
        p ("O sustenido eleva a nota em um semitom. Ele é escrito à esquerda da "
           "nota, um pouco acima. Quando você lê Fá♯, deve pensar: \"a nota que "
           "está meio-tom acima do Fá\". No braço, isso equivale a avançar uma "
           "casa a partir do Fá."),
        b ("Dó♯ está meio-tom acima do Dó."),
        b ("Ré♯ está meio-tom acima do Ré."),
        b ("Fá♯ está meio-tom acima do Fá."),
        b ("Sol♯ está meio-tom acima do Sol."),
        b ("Lá♯ está meio-tom acima do Lá."),
        p ("Note que não existe Mi♯ nem Si♯ na escala natural. Como Mi–Fá e Si–Dó "
           "já estão separados por apenas um semitom, subir meio-tom a partir do "
           "Mi leva direto ao Fá, e a partir do Si leva direto ao Dó. Se alguém "
           "escrever Mi♯, isso é enarmonicamente igual a Fá; é uma grafia "
           "possível, mas incomum."),

        h ("O bemol (♭)"),
        p ("O bemol abaixa a nota em um semitom. Escrito à esquerda e um pouco "
           "abaixo, ele indica que você deve descer meio-tom. Quando lê Si♭, "
           "pense: \"a nota que está meio-tom abaixo do Si\". No braço, é uma casa "
           "abaixo do Si."),
        b ("Ré♭ está meio-tom abaixo do Ré."),
        b ("Mi♭ está meio-tom abaixo do Mi."),
        b ("Sol♭ está meio-tom abaixo do Sol."),
        b ("Lá♭ está meio-tom abaixo do Lá."),
        b ("Si♭ está meio-tom abaixo do Si."),
        p ("Assim como não havia Mi♯ e Si♯, também não há Fá♭ nem Dó♭ na escala "
           "natural: descer meio-tom do Fá chega direto ao Mi, e do Dó chega "
           "direto ao Si. Novamente, são grafias possíveis porém incomuns."),
        c ("Regra de ouro dos acidentes naturais: os pares Mi–Fá e Si–Dó são "
           "\"colados\" (um semitom). Por isso o sustenido de Mi é Fá, o bemol de "
           "Fá é Mi, o sustenido de Si é Dó e o bemol de Dó é Si."),

        h ("Enarmonia: dois nomes, um som"),
        img ("c_enarmonia_teclado", "Cada tecla preta tem dois nomes (sustenido e bemol)."),
        p ("Enarmonia é o fenômeno de duas notas com nomes diferentes soarem "
           "exatamente igual. Dó♯ e Ré♭ são a mesma altura; Fá♯ e Sol♭ são a mesma "
           "altura; Sol♯ e Lá♭ são a mesma altura. No instrumento, você toca a "
           "mesma casa."),
        tbl ({ "Nome subindo (♯)", "Nome descendo (♭)", "Mesma altura" },
             { { "Dó♯", "Ré♭", "sim" },
               { "Ré♯", "Mi♭", "sim" },
               { "Fá♯", "Sol♭", "sim" },
               { "Sol♯", "Lá♭", "sim" },
               { "Lá♯", "Si♭", "sim" },
               { "Mi♯", "Fá", "sim (grafia incomum)" },
               { "Si♯", "Dó", "sim (grafia incomum)" } }),
        p ("Por que, então, usar dois nomes? Porque o nome certo depende do "
           "contexto harmônico. Numa tonalidade com sustenidos, escrevemos Fá♯; "
           "numa tonalidade com bemóis, escrevemos Sol♭. A escolha deixa a "
           "partitura mais lógica e revela a função da nota dentro do acorde."),
        c ("Exemplo prático: a escala de Ré maior tem Fá♯ e Dó♯ (sustenidos). A "
           "escala de Sol♭ maior tem seis bemóis (Sol♭, Lá♭, Si♭, Dó♭, Ré♭ e Mi♭), "
           "com o Fá natural. As duas soam nas mesmas doze alturas, mas cada uma é "
           "escrita de um jeito para respeitar a lógica da tonalidade."),

        h ("A escala cromática"),
        img ("c_escala_cromatica_corda6", "Da 6ª solta (Mi) à casa 12 (Mi): doze semitons."),
        p ("A escala cromática é a sequência de todas as doze alturas dentro da "
           "oitava, subindo de semitom em semitom. É a escala mais completa do "
           "sistema temperado e serve de mapa para o braço: cada casa é um passo "
           "cromático."),
        b ("Subindo: Dó, Dó♯, Ré, Ré♯, Mi, Fá, Fá♯, Sol, Sol♯, Lá, Lá♯, Si, Dó."),
        b ("Descendo (escrita com bemóis): Dó, Si, Si♭, Lá, Lá♭, Sol, Sol♭, Fá, "
           "Mi, Mi♭, Ré, Ré♭, Dó."),
        p ("Repare que subindo usamos sustenidos e descendo usamos bemóis — uma "
           "convenção para deixar a leitura natural. Mas as doze alturas são as "
           "mesmas nos dois sentidos. Doze semitons formam uma oitava; é por isso "
           "que a casa 12 do braço repete a corda solta."),
        c ("No braço, a escala cromática é simplesmente \"andar de casa em casa\". "
           "Se você memorizar as notas naturais (tópico D) e souber que uma casa "
           "é um semitom, você alcança qualquer nota cromática por dedução."),

        h ("Onde os acidentes aparecem na prática"),
        p ("Os acidentes não são um detalhe teórico: eles estão em toda parte na "
           "música que você vai tocar. Reconhecê-los é o que permite ler cifras, "
           "entender escalas e acompanhar solos."),
        b ("Armadura de clave: no início da partitura, os sustenidos ou bemóis da "
           "tonalidade são escritos de uma vez, valendo para toda a peça."),
        b ("Acidentes ocorrentes: um ♯ ou ♭ escrito no meio da peça vale até o fim "
           "do compasso, salvo indicação contrária."),
        b ("Cifras: acordes com acidentes aparecem como F♯m, B♭, C♯7 e assim por "
           "diante."),
        c ("Cuidado com nomes como \"Si♯\" e \"Dó♭\": existem, mas quase sempre "
           "são grafias de passagem. Na prática, você toca Fá e Si, "
           "respectivamente."),

        h ("Cromatismo: acidentes em movimento"),
        p ("Quando acidentes são usados para ligar notas próximas, criando "
           "movimento por semitons, chamamos isso de cromatismo. É um recurso "
           "expressivo fundamental no blues, no jazz e na música popular."),
        b ("Aproximação cromática: chegar a uma nota-alvo subindo ou descendo por "
           "semitons a partir de uma nota vizinha."),
        b ("Nota de passagem cromática: um semitom entre duas notas da escala, "
           "para ligar uma à outra."),
        b ("Bend e slide cromático: na guitarra, alcançar o semitom curvando a "
           "corda (bend) ou deslizando o dedo (slide), muito comum no blues."),
        c ("Ouvido antes da teoria: cante um semitom subindo e descendo. O "
           "cromatismo só faz sentido quando você ouve a tensão que ele cria e "
           "resolve."),

        h ("Acidentes no braço: contando semitons"),
        p ("A melhor forma de dominar os acidentes é ligá-los ao braço. Cada casa "
           "é um semitom. Se você sabe onde está uma nota natural, o sustenido "
           "está uma casa à frente e o bemol uma casa atrás. Isso vale para "
           "qualquer corda e qualquer região."),
        tbl ({ "A partir de", "♯ (uma casa à frente)", "♭ (uma casa atrás)" },
             { { "Dó", "Dó♯", "Dó♭ ( = Si )" },
               { "Ré", "Ré♯", "Ré♭" },
               { "Mi", "Mi♯ ( = Fá )", "Mi♭" },
               { "Fá", "Fá♯", "Fá♭ ( = Mi )" },
               { "Sol", "Sol♯", "Sol♭" },
               { "Lá", "Lá♯", "Lá♭" },
               { "Si", "Si♯ ( = Dó )", "Si♭" } }),
        p ("Perceba de novo as quatro posições \"coladas\": o sustenido do Mi é o "
           "Fá; o bemol do Fá é o Mi; o sustenido do Si é o Dó; o bemol do Dó é o "
           "Si. Em todas as outras, o acidente gera uma casa intermediária real."),
        c ("Exercício de ouvido: toque uma nota natural, depois a casa à frente e "
           "a casa atrás. Cante as três. Esse reconhecimento auditivo dos "
           "semitons é o que sustenta a afinação e o fraseado cromático."),

        h ("Armadura de clave: por que a tonalidade escolhe o acidente"),
        p ("Quando uma música está numa tonalidade com sustenidos ou bemóis, "
           "escrevemos esses acidentes de uma vez no início da pauta: é a "
           "armadura de clave. Ela economiza acidentes soltos e revela a "
           "tonalidade de imediato."),
        b ("Tonalidades com sustenidos: Sol (1 ♯), Ré (2 ♯), Lá (3 ♯), Mi (4 ♯), "
           "Si (5 ♯), Fá♯ (6 ♯), Dó♯ (7 ♯)."),
        b ("Tonalidades com bemóis: Fá (1 ♭), Si♭ (2 ♭), Mi♭ (3 ♭), Lá♭ (4 ♭), "
           "Ré♭ (5 ♭), Sol♭ (6 ♭), Dó♭ (7 ♭)."),
        p ("Note que a ordem em que os acidentes aparecem na armadura é sempre a "
           "mesma: os sustenidos entram Fá, Dó, Sol, Ré, Lá, Mi, Si; os bemóis "
           "entram Si, Mi, Lá, Ré, Sol, Dó, Fá. Essa ordem é o que o círculo das "
           "quintas organiza (tópico G)."),
        c ("Curiosidade enarmônica: Fá♯ maior e Sol♭ maior têm o mesmo som, mas "
           "uma usa seis sustenidos e a outra seis bemóis. Compositores escolhem "
           "a grafia que dá menos trabalho para ler."),

        h ("Erros comuns e como evitá-los"),
        p ("Quase todo iniciante tropeça nos mesmos pontos ao estudar acidentes. "
           "Antecipe-se a eles."),
        b ("Achar que Fá♯ e Sol♭ são notas diferentes no braço. São a mesma casa; "
           "o nome muda conforme a tonalidade."),
        b ("Escrever Mi♯ ou Si♯ como se fossem notas distintas de Fá e Dó. São "
           "enarmônicos; a grafia existe, mas o som é o mesmo."),
        b ("Contar um tom onde há semitom (entre Mi–Fá e Si–Dó). Isso desalinha "
           "toda escala montada a seguir."),
        b ("Esquecer que o acidente vale para o compasso inteiro: um Fá♯ escrito "
           "no começo do compasso continua valendo para todos os Fás até a "
           "barra de compasso seguinte."),
        c ("Método de conferência: quando estiver em dúvida sobre uma nota, "
           "pergunte \"quantos semitons a partir da natural?\" e conte no braço. "
           "A contagem física resolve a dúvida na hora."),

        h ("Como estudar o tópico C na prática"),
        p ("Acidentes se aprendem no braço e no ouvido, não só no papel. Faça "
           "estes exercícios curtos antes de seguir para o tópico D."),
        b ("Escolha uma corda e uma casa, nomeie a nota natural, depois diga o "
           "sustenido e o bemol correspondentes."),
        b ("Percorra uma corda de casa em casa dizendo os nomes cromáticos em voz "
           "alta, subindo com sustenidos e descendo com bemóis."),
        b ("Toque a mesma nota em duas cordas diferentes e confirme que o som é "
           "idêntico, mesmo que a posição mude."),
        b ("Escreva, no papel, a escala cromática de Dó subindo e descendo, "
           "alternando ♯ e ♭."),
        c ("Resumo prático: sustenido sobe, bemol desce, bequadro cancela; "
           "enarmonia é mesmo som com nomes diferentes; a tonalidade decide a "
           "grafia; no braço, cada acidente é uma casa de diferença."),

        h ("Resumo do tópico C"),
        tbl ({ "Ideia", "O que fixar" },
             { { "Sustenido (♯)", "sobe meio-tom" },
               { "Bemol (♭)", "desce meio-tom" },
               { "Bequadro (♮)", "cancela o acidente anterior" },
               { "Enarmonia", "nomes diferentes, mesmo som (Fá♯ = Sol♭)" },
               { "Exceções", "não há Mi♯ nem Si♯ na escala natural" },
               { "Cromática", "12 semitons por oitava" },
               { "Cromatismo", "movimento por semitons (aproximações, bends)" },
               { "Contexto", "a tonalidade decide se usamos ♯ ou ♭" } }),
    };
}

} // namespace cursomusica::content
