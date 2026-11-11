#include "Course/Content/Topics.h"

// Topic B — Notas musicais.
// Sources: pdf-teoria-elementar-da-musica-ricordi-osvaldo-lacerda (notas, pauta,
// claves, tom e semitom) and pdf-fraseado-melodico (fundamentos).
namespace cursomusica::content
{

std::vector<ContentItem> topicB()
{
    return {
        p ("Antes de tocar qualquer coisa, você precisa saber o nome dos sons. "
           "Neste tópico você aprende as sete notas naturais, como elas se "
           "organizam em tom e semitom e por que essa organização é a base de "
           "tudo o que vem depois: escalas, acordes e a localização das notas "
           "no braço. Vá com calma: aqui não se toca ainda, se entende."),

        h ("O que é uma nota musical"),
        p ("Nota musical é um som de altura definida, ou seja, um som com uma "
           "frequência estável que o ouvido percebe como uma altura específica. "
           "Quando você canta uma nota, a voz vibra numa frequência constante; "
           "quando toca uma corda, ela vibra e produz uma frequência que "
           "depende do comprimento, da tensão e da massa da corda. A cada "
           "frequência corresponde um nome."),
        p ("Frequência é medida em hertz (Hz): quantas vibrações por segundo. O "
           "ouvido humano escuta, em média, de 20 Hz a 20.000 Hz. O instrumento "
           "com que trabalhamos produz alturas na região de 80 Hz a 1.300 Hz, "
           "que é onde o ouvido é mais sensível e onde as notas são mais fáceis "
           "de distinguir."),
        b ("Altura (pitch) é a posição do som na escala grave–agudo. Não "
           "confunda com volume (intensidade) nem com timbre (a cor do som)."),
        b ("Grave é a região dos sons baixos e profundos; agudo é a região dos "
           "sons altos e finos."),
        b ("O mesmo nome de nota pode existir em várias alturas; para "
           "diferenciá-las usamos números de oitava (por exemplo, E2 é mais "
           "grave que E4)."),
        c ("Curiosidade: quando a frequência dobra, o ouvido percebe a mesma "
           "nota mais aguda. A distância entre uma nota e essa nota dobrada "
           "chama-se oitava. É por isso que voltaremos ao nome E várias vezes "
           "ao longo do braço."),

        h ("As sete notas naturais"),
        p ("A música ocidental usa sete nomes básicos, as chamadas notas "
           "naturais. Na leitura em português e na leitura latina, elas são Dó, "
           "Ré, Mi, Fá, Sol, Lá e Si. Na notação anglo-saxônica, muito usada em "
           "cifras e no meio da guitarra, as mesmas notas aparecem como C, D, "
           "E, F, G, A e B. Você vai conviver com as duas formas, então decore "
           "a correspondência."),
        tbl ({ "Ordem", "Nome latino (PT)", "Nota anglo-saxônica (cifra)" },
             { { "1", "Dó", "C" },
               { "2", "Ré", "D" },
               { "3", "Mi", "E" },
               { "4", "Fá", "F" },
               { "5", "Sol", "G" },
               { "6", "Lá", "A" },
               { "7", "Si", "B" } }),
        p ("Depois do Si, a série recomeça no Dó. Mas atenção: esse novo Dó "
           "está mais agudo que o anterior, exatamente uma oitava acima. A "
           "sequência é cíclica, e cada volta completa sobe uma oitava."),
        b ("Memorize a sequência na ordem e também de trás para a frente: "
           "Dó–Ré–Mi–Fá–Sol–Lá–Si e Si–Lá–Sol–Fá–Mi–Ré–Dó."),
        b ("Associe cada nome à sua cifra até responder sem pensar: Dó = C, "
           "Ré = D, Mi = E, Fá = F, Sol = G, Lá = A, Si = B."),
        c ("Por que a ordem começa no Dó e não no Lá? Por convenção da notação "
           "ocidental. O Dó é o centro de referência da teoria clássica, e "
           "vamos usá-lo como ponto de partida para montar escalas adiante."),

        h ("Tom e semitom: a menor distância entre duas notas"),
        p ("Entre duas notas vizinhas existem duas distâncias possíveis: o "
           "semitom, que é o menor intervalo usado na nossa música, e o tom, "
           "que equivale a dois semitons. Entender onde há tom e onde há "
           "semitom entre as notas naturais é o que permite localizar tudo no "
           "braço e construir escalas corretas."),
        p ("A regra é simples e vale a pena decorar: entre a maioria das notas "
           "naturais há um tom, mas entre Mi–Fá e entre Si–Dó há apenas um "
           "semitom. Esses dois pares são as exceções que você precisa "
           "memorizar."),
        tbl ({ "Par de notas", "Distância" },
             { { "Dó → Ré", "1 tom" },
               { "Ré → Mi", "1 tom" },
               { "Mi → Fá", "1 semitom (meio-tom)" },
               { "Fá → Sol", "1 tom" },
               { "Sol → Lá", "1 tom" },
               { "Lá → Si", "1 tom" },
               { "Si → Dó", "1 semitom (meio-tom)" } }),
        p ("Some as distâncias do Dó até o Dó seguinte: 1 + 1 + 0,5 + 1 + 1 + 1 "
           "+ 0,5 = 6 tons, ou seja, 12 semitons. Esse é o número de casas que "
           "separa uma nota da sua oitava no braço — e a razão pela qual a casa "
           "12 repete a corda solta uma oitava acima."),
        c ("Truque de memória: as duas notas naturais que têm meio-tom entre si "
           "são as que terminam em i quando vizinhas de uma começada por F ou "
           "por C: Mi–Fá e Si–Dó. Repita em voz alta até virar automático."),

        h ("As notas na pauta: leitura básica"),
        p ("Na partitura, as notas se escrevem em cinco linhas paralelas "
           "chamadas pauta ou pentagrama. A posição na pauta indica a altura: "
           "quanto mais para cima, mais agudo. Como cinco linhas não bastam "
           "para todas as notas, usamos pequenas linhas extras e, sobretudo, "
           "uma clave que fixa o nome das notas."),
        p ("A clave mais comum para guitarra e violão é a clave de Sol, escrita "
           "na segunda linha: ela diz que a nota naquela linha é o Sol. A "
           "partir dela, cada linha e cada espaço ganham um nome fixo."),
        tbl ({ "Posição na pauta", "Nota (clave de Sol)" },
             { { "1ª linha (de baixo)", "Mi" },
               { "1º espaço", "Fá" },
               { "2ª linha", "Sol" },
               { "2º espaço", "Lá" },
               { "3ª linha", "Si" },
               { "3º espaço", "Dó" },
               { "4ª linha", "Ré" },
               { "4º espaço", "Mi" },
               { "5ª linha", "Fá" } }),
        c ("Detalhe importante da guitarra: ela é um instrumento transpositor. "
           "Uma nota escrita na partitura soa uma oitava abaixo do que está "
           "escrito. Ou seja, o Mi escrito na 1ª linha soa como o Mi uma "
           "oitava mais grave. Guarde essa ideia; ela reaparece no tópico D."),

        h ("Sustenido, bemol e a ideia de cromatismo"),
        p ("Se o semitom é a menor distância, o que existe entre duas notas "
           "naturais separadas por um tom? Existe uma nota intermediária, "
           "escrita com um sinal chamado acidente. O sustenido (♯) sobe meio-tom "
           "e o bemol (♭) desce meio-tom. Entre Dó e Ré há uma nota que pode "
           "ser chamada de Dó♯ (lida subindo a partir do Dó) ou de Ré♭ (lida "
           "descendo a partir do Ré)."),
        p ("O nome genérico para essas doze alturas — sete naturais mais cinco "
           "intermediárias — é escala cromática. Ela contém todos os semitons "
           "possíveis dentro de uma oitava. O tópico C aprofunda esse assunto; "
           "aqui basta saber que as notas intermediárias existem e recebem nome."),
        b ("Subindo de semitom em semitom a partir do Dó: Dó, Dó♯, Ré, Ré♯, "
           "Mi, Fá, Fá♯, Sol, Sol♯, Lá, Lá♯, Si, e de volta ao Dó."),
        b ("Nem toda nota intermediária existe entre todos os pares: entre "
           "Mi–Fá e Si–Dó não há nota intermediária, porque a distância já é "
           "de um semitom."),

        h ("Intervalos: a distância ganha nome"),
        p ("Quando medimos a distância entre duas notas, estamos lidando com "
           "intervalos. O intervalo mais básico é o semitom; o tom é o "
           "intervalo de dois semitons. Contando semitons, chegamos a nomes que "
           "você vai reencontrar em escalas e acordes: terça, quinta, sétima e "
           "assim por diante."),
        tbl ({ "Semitons", "Nome do intervalo", "Exemplo a partir do Dó" },
             { { "0", "uníssono", "Dó → Dó" },
               { "1", "segunda menor", "Dó → Ré♭" },
               { "2", "segunda maior", "Dó → Ré" },
               { "3", "terça menor", "Dó → Mi♭" },
               { "4", "terça maior", "Dó → Mi" },
               { "5", "quarta justa", "Dó → Fá" },
               { "6", "quarta aumentada / quinta diminuta", "Dó → Fá♯ / Sol♭" },
               { "7", "quinta justa", "Dó → Sol" },
               { "9", "sexta maior", "Dó → Lá" },
               { "11", "sétima maior", "Dó → Si" },
               { "12", "oitava", "Dó → Dó (agudo)" } }),
        p ("Não é preciso decorar a tabela inteira agora. O objetivo é você "
           "perceber que os intervalos são apenas contagens de semitons, e que "
           "essas contagens valem igualmente no braço: uma casa é um semitom, "
           "duas casas são um tom."),
        c ("A terça define se um acorde é maior ou menor, e a sétima define o "
           "caráter (doce, tenso, jazzy). Guarde os nomes: eles voltam nos "
           "tópicos F, G e H."),

        h ("Por que isso importa para o guitarrista"),
        p ("Toda a organização do braço nasce das notas e dos intervalos. "
           "Quando você sabe que a corda 6ª solta é Mi, que a 5ª casa é Lá e que "
           "a casa 12 repete a corda solta, você consegue deduzir qualquer nota "
           "do braço. Quando você sabe que há um semitom entre Mi e Fá, você "
           "entende por que certas casas caem onde caem."),
        b ("Localizar notas: cada casa é um semitom; conte de semitom em "
           "semitom a partir da corda solta."),
        b ("Montar escalas: a escala maior é uma sequência fixa de tons e "
           "semitons que começa numa nota escolhida."),
        b ("Formar acordes: acorde é um conjunto de notas escolhidas por "
           "intervalo (por exemplo, fundamental, terça e quinta)."),
        c ("Resumo do tópico: sete nomes naturais (Dó Ré Mi Fá Sol Lá Si = C D E "
           "F G A B); tom = dois semitons; semitom entre Mi–Fá e Si–Dó; notas "
           "intermediárias levam sustenido ou bemol; intervalos são contagens "
           "de semitons. Com isso você já consegue ler o braço."),

        h ("Para ir além: a nota como frequência"),
        p ("Para quem quer chegar ao nível avançado, vale entender a nota por "
           "dentro. Cada nota corresponde a uma frequência exata em hertz. A "
           "referência de afinação usada hoje é o Lá acima do Dó central a 440 "
           "Hz, chamado Lá 440. A partir dele, todas as outras notas podem ser "
           "calculadas."),
        p ("O sistema de afinação mais usado, o temperamento igual, divide a "
           "oitava em doze partes iguais. Isso significa que a razão de "
           "frequência entre duas notas vizinhas (um semitom) é sempre a mesma: "
           "a raiz doze de dois, aproximadamente 1,0595. Dobrando a frequência, "
           "você sobe exatamente uma oitava."),
        b ("Lá 440 × 1,0595 ≈ Lá♯ 466,16 Hz; subindo doze vezes, chega-se ao "
           "próximo Lá a 880 Hz."),
        b ("Afinadores e detectores de altura trabalham comparando a frequência "
           "medida com essa tabela. É assim que o app reconhece a nota que você "
           "toca."),
        c ("No temperamento igual, todas as tonalidades soam igualmente "
           "afinadas, ao custo de pequenos ajustes em relação às frequências "
           "puramente matemáticas. É o preço da liberdade de tocar em qualquer "
           "tom — e é o padrão desde Bach."),

        h ("Como estudar este tópico na prática"),
        p ("Teoria só vira música quando entra nos dedos e nos ouvidos. Antes "
           "de passar para o tópico C, faça três coisas simples todos os dias "
           "durante alguns minutos."),
        b ("Recite a sequência das sete notas naturais em voz alta, na ordem "
           "direta e na inversa, associando cada uma à sua cifra."),
        b ("Cante a sequência de tons e semitons, marcando com a mão onde está "
           "o meio-tom: Dó (tom) Ré (tom) Mi (semitom) Fá (tom) Sol (tom) Lá "
           "(tom) Si (semitom) Dó."),
        b ("Toque uma única corda solta e cante junto com ela. Depois procure "
           "cantar, sem tocar, o mesmo som. Esse exercício de afinação entre "
           "ouvido e voz é a base da percepção melódica."),
        c ("Erro comum de iniciante: confundir o nome da nota com a posição no "
           "braço. Nome é som; posição é casa. O tópico D junta os dois; aqui "
           "você só precisa dominar os nomes e as distâncias."),

        h ("Resumo final do tópico B"),
        tbl ({ "Ideia", "O que fixar" },
             { { "Notas naturais", "Dó Ré Mi Fá Sol Lá Si = C D E F G A B" },
               { "Ciclo", "depois do Si recomeça o Dó, uma oitava acima" },
               { "Tom", "equivale a 2 semitons" },
               { "Semitom", "menor distância; entre Mi–Fá e Si–Dó" },
               { "Acidentes", "♯ sobe meio-tom; ♭ desce meio-tom" },
               { "Cromática", "12 semitons cobrem a oitava inteira" },
               { "Intervalo", "distância entre notas, contada em semitons" },
               { "Oitava", "dobrar a frequência" } }),
    };
}

} // namespace cursomusica::content
