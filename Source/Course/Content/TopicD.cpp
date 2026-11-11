#include "Course/Content/Topics.h"

// Topic D — Localização das notas no braço.
// Sources: pdf-mozart-mello-livroestudosdeguitarra4em1 (introdução) and
// pdf-teoria-elementar-da-musica-ricordi-osvaldo-lacerda.
namespace cursomusica::content
{

std::vector<ContentItem> topicD()
{
    return {
        p ("Agora que você conhece os nomes das notas e os acidentes, chegou a "
           "hora de encontrar cada uma delas no braço. Este tópico é o mapa do "
           "instrumento: você vai aprender a afinação padrão das seis cordas, "
           "como cada casa corresponde a um semitom e como deduzir qualquer nota "
           "sem decorar o braço inteiro. É a habilidade que destrava tudo o que "
           "vem depois."),

        h ("A afinação padrão: por que as cordas são Mi Lá Ré Sol Si Mi"),
        p ("A guitarra e o violão usam, por padrão, a afinação em que as cordas "
           "soltas são Mi, Lá, Ré, Sol, Si e Mi — da mais grave (6ª corda) para a "
           "mais aguda (1ª corda). Em notação de frequência, isso é E2, A2, D3, "
           "G3, B3 e E4. As duas cordas das pontas dão o mesmo nome, Mi, separadas "
           "por duas oitavas."),
        tbl ({ "Corda", "Nome", "Nota (anglo)", "Frequência" },
             { { "6ª (mais grave)", "Mi", "E2", "82,41 Hz" },
               { "5ª", "Lá", "A2", "110,00 Hz" },
               { "4ª", "Ré", "D3", "146,83 Hz" },
               { "3ª", "Sol", "G3", "196,00 Hz" },
               { "2ª", "Si", "B3", "246,94 Hz" },
               { "1ª (mais aguda)", "Mi", "E4", "329,63 Hz" } }),
        p ("Essa afinação é o resultado de compromissos práticos: permite tocar "
           "acordes com formas confortáveis e cobrir uma grande extensão de "
           "alturas sem mudar de posição com frequência. Existem afinações "
           "alternativas (drop D, aberta em Sol, etc.), mas começamos pela "
           "padrão."),
        c ("Truque para lembrar a ordem das cordas: \"Minha Lá Ré Sol Si Mi\" — ou, "
           "em inglês, \"Eddie Ate Dynamite, Good Bye Eddie\" (E A D G B E)."),
        p ("Observe um padrão útil: da 6ª à 5ª corda há uma quarta justa (cinco "
           "semitons); da 5ª à 4ª também; da 4ª à 3ª também. Mas da 3ª para a 2ª "
           "há apenas uma terça maior (quatro semitons). Esse \"degrau\" entre a "
           "3ª e a 2ª corda é a razão pela qual as formas de acorde mudam de "
           "desenho quando passam por ali."),
        tbl ({ "Salto entre cordas", "Intervalo", "Semitons (casas)" },
             { { "6ª → 5ª", "quarta justa", "5" },
               { "5ª → 4ª", "quarta justa", "5" },
               { "4ª → 3ª", "quarta justa", "5" },
               { "3ª → 2ª", "terça maior", "4" },
               { "2ª → 1ª", "quarta justa", "5" } }),

        h ("Cada casa é um semitom"),
        p ("Esta é a regra que faz tudo funcionar: no braço, avançar uma casa "
           "equivale a subir um semitom. Duas casas são um tom. Se você sabe a "
           "nota da corda solta, pode chegar a qualquer nota contando casas — ou "
           "melhor, aplicando as distâncias de tom e semitom que você aprendeu no "
           "tópico B."),
        p ("Como entre Mi e Fá há um semitom, a nota da 1ª casa da 6ª corda (que "
           "é Mi) é Fá. Como entre Fá e Sol há um tom, a nota da 3ª casa é Sol, e "
           "a 2ª casa (entre as duas) é Fá♯. Esse raciocínio, aplicado a cada "
           "corda, constrói o mapa completo do braço."),
        c ("Não decore o braço como uma tabela. Aprenda a regra (uma casa = um "
           "semitom) e use os pontos de referência. Com o tempo, o mapa se "
           "memoriza sozinho pelo uso."),

        h ("Mapa da 6ª corda (Mi grave)"),
        p ("A 6ª corda é a mais importante para se orientar: muitas formas de "
           "acorde e escalas têm a fundamental nela. Vamos mapear as primeiras "
           "casas e os pontos de referência."),
        tbl ({ "Casa", "Nota", "Como deduzir" },
             { { "0 (solta)", "Mi", "ponto de partida" },
               { "1", "Fá", "Mi–Fá = semitom" },
               { "2", "Fá♯", "um tom acima do Mi" },
               { "3", "Sol", "tom acima do Fá" },
               { "5", "Lá", "mesma nota da 5ª corda solta" },
               { "7", "Si", "tom acima do Lá" },
               { "8", "Dó", "Si–Dó = semitom" },
               { "10", "Ré", "tom acima do Dó" },
               { "12", "Mi", "uma oitava acima da corda solta" } }),
        p ("O ponto de referência mais valioso é a casa 5 da 6ª corda: é a nota "
           "Lá, a mesma da 5ª corda solta. Isso permite \"descer\" mentalmente da "
           "6ª para a 5ª corda. Do mesmo modo, a casa 5 da 5ª corda é o Ré da 4ª "
           "corda solta, e assim por diante, exceto no salto entre a 3ª e a 2ª "
           "corda."),

        h ("Mapa completo do braço (6ª à 1ª corda)"),
        p ("A tabela a seguir reúne as notas das seis cordas nas casas principais. "
           "Use-a como consulta, não como decoreba. Confirme sempre pela regra do "
           "semitom."),
        tbl ({ "Corda", "Solta", "Casa 1", "Casa 2", "Casa 3", "Casa 5", "Casa 7", "Casa 12" },
             { { "6ª", "E2", "F2", "F♯2", "G2", "A2", "B2", "E3" },
               { "5ª", "A2", "A♯2", "B2", "C3", "D3", "E3", "A3" },
               { "4ª", "D3", "D♯3", "E3", "F3", "G3", "A3", "D4" },
               { "3ª", "G3", "G♯3", "A3", "A♯3", "C4", "D4", "G4" },
               { "2ª", "B3", "C4", "C♯4", "D4", "E4", "F♯4", "B4" },
               { "1ª", "E4", "F4", "F♯4", "G4", "A4", "B4", "E5" } }),
        p ("Note que a 2ª corda segue o mesmo padrão da 6ª, apenas duas oitavas "
           "acima — é o mesmo Mi. As cordas 4ª, 3ª e 1ª seguem um padrão "
           "semelhante entre si. Perceber essas repetições reduz muito o esforço "
           "de memorização."),

        h ("A regra do oitavo grau (casa 12)"),
        p ("A casa 12 é especial: ela repete exatamente a corda solta, uma oitava "
           "acima. Isso vale para todas as seis cordas e é consequência direta de "
           "doze semitons formarem uma oitava."),
        b ("6ª solta = E2; casa 12 da 6ª = E3."),
        b ("1ª solta = E4; casa 12 da 1ª = E5."),
        p ("Muitos instrumentos marcam a casa 12 com dois pontos em vez de um, "
           "justamente para sinalizar essa oitava. Use-a como âncora: se você se "
           "perde no meio do braço, volte para a casa 12 e recomece a contagem."),
        c ("Consequência prática: tocar na casa 12 é como tocar na corda solta, "
           "mas uma oitava acima. Acordes de forma \"aberta\" podem ser tocados na "
           "casa 12 com pestana, soando mais agudos."),

        h ("Notas iguais em cordas diferentes"),
        p ("Um dos fatos mais libertadores do instrumento é que a mesma nota pode "
           "ser tocada em vários lugares. O Lá, por exemplo, existe na 5ª corda "
           "solta, na casa 5 da 6ª corda, na casa 10 da 2ª corda e assim por "
           "diante."),
        tbl ({ "Nota", "Onde encontrar (alguns exemplos)" },
             { { "Lá (A)", "5ª solta; 6ª casa 5; 4ª casa 7; 3ª casa 2; 2ª casa 10" },
               { "Dó (C)", "5ª casa 3; 4ª casa 10; 3ª casa 5; 2ª casa 1; 6ª casa 8" },
               { "Mi (E)", "6ª solta; 1ª solta; 4ª casa 2; 3ª casa 9; 2ª casa 5" },
               { "Sol (G)", "3ª solta; 6ª casa 3; 4ª casa 5; 2ª casa 8; 5ª casa 10" } }),
        p ("Por que isso importa? Porque tocar a mesma nota em cordas diferentes "
           "muda o timbre (corda mais grossa soa mais cheia; mais fina soa mais "
           "brilhante) e muda a facilidade de encadear a próxima nota. Escolher "
           "onde tocar é uma decisão de música, não só de mecânica."),
        c ("Exercício de oitavas: toque uma nota na 6ª corda e encontre a mesma "
           "nota duas cordas acima e duas casas à frente. Esse é o padrão de "
           "oitava, usado o tempo todo em solos e arranjos."),

        h ("Estratégia para decorar o braço sem sofrimento"),
        p ("Decorar o braço inteiro de uma vez é desnecessário e desmotivador. "
           "Use uma abordagem em camadas, começando pelos pontos de referência."),
        b ("Primeiro, domine as cordas soltas e as casas 5, 7 e 12 — os pontos "
           "naturais do instrumento."),
        b ("Depois, domine a 6ª e a 5ª cordas nas primeiras cinco casas: são as "
           "fundamentais mais usadas em acordes com pestana."),
        b ("Em seguida, aprenda a nota de cada corda na casa 3, 5 e 7, que formam "
           "uma grade de referência."),
        b ("Por fim, preencha os espaços com a regra do semitom. Em poucas "
           "semanas de uso, você consulta cada vez menos."),
        c ("Dica de treino: escolha uma nota por dia (por exemplo, Sol) e "
           "encontre-a em todas as cordas e casas possíveis. Em uma semana você "
           "cobriu as sete naturais."),

        h ("Como usar o mapa na prática: escalas e acordes"),
        p ("Encontrar notas isoladas é o começo. O objetivo é usar o mapa para "
           "tocar música: escalas, melodias e acordes. Veja como o mapa do braço "
           "se aplica."),
        p ("A escala de Dó maior na primeira posição usa três notas em cada uma "
           "das três primeiras cordas. Partindo da 5ª corda, casa 3 (Dó), você "
           "sobe a escala sem sair da região: Dó, Ré, Mi, Fá, Sol, Lá, Si, Dó. "
           "Cada nota cai numa casa específica, e o mapa diz onde."),
        tbl ({ "Nota da escala de Dó", "Corda e casa" },
             { { "Dó", "5ª corda, casa 3" },
               { "Ré", "4ª corda, solta" },
               { "Mi", "4ª corda, casa 2" },
               { "Fá", "4ª corda, casa 3" },
               { "Sol", "3ª corda, solta" },
               { "Lá", "3ª corda, casa 2" },
               { "Si", "2ª corda, solta" },
               { "Dó (agudo)", "2ª corda, casa 1" } }),
        p ("Perceba como a escala \"cai\" naturalmente no braço: não é preciso "
           "decorar posições, basta seguir as notas na ordem e escolher, para cada "
           "uma, uma corda/casa conveniente. O mapa do braço é o que permite essa "
           "escolha."),
        c ("Mesma ideia para acordes: um Dó maior é formado pelas notas Dó, Mi e "
           "Sol. Se você sabe onde cada uma está, pode montar o acorde em várias "
           "regiões do braço — é exatamente o que o sistema CAGED (tópico F) "
           "organiza."),

        h ("Pontos de referência visuais do braço"),
        p ("O braço tem marcas físicas (bolinhas) nas casas 3, 5, 7, 9, 12 (dupla), "
           "15, 17 e 19. Elas existem para você se orientar rapidamente. Aprender "
           "as notas dessas casas dá uma grade mental poderosa."),
        tbl ({ "Casa marcada", "Notas (6ª → 1ª corda)" },
             { { "3", "Sol, Dó, Fá, Lá♯, Ré, Sol" },
               { "5", "Lá, Ré, Sol, Dó, Mi, Lá" },
               { "7", "Si, Mi, Lá, Ré, Fá♯, Si" },
               { "9", "Dó♯, Fá♯, Si, Mi, Sol♯, Dó♯" },
               { "12", "Mi, Lá, Ré, Sol, Si, Mi (uma oitava acima)" } }),
        p ("Repare que a casa 12 repete as cordas soltas. As casas 5 e 7 têm "
           "relações úteis: a casa 5 da 6ª corda é o Lá da 5ª solta, e a casa 7 da "
           "6ª é o Si da 2ª solta uma oitava abaixo. Essas coincidências são "
           "atalhos de memorização."),
        c ("Faça o teste: toque a 6ª corda na casa 5 e a 5ª corda solta. Devem "
           "soar exatamente iguais (mesma nota Lá). Se soar diferente, o "
           "instrumento está desafinado."),

        h ("Erro comum: a guitarra soa uma oitava abaixo do escrito"),
        p ("Há uma convenção importante: a guitarra é um instrumento transpositor "
           "de uma oitava. Uma nota escrita na partitura soa uma oitava mais grave "
           "do que está grafado. Assim, o Mi escrito (E4) soa como E3."),
        p ("Isso não muda o nome da nota nem a posição no braço; muda apenas a "
           "oitava real do som. O app leva essa transposição em conta ao converter "
           "partitura em áudio, para que o som que sai seja o correto."),
        c ("Para o iniciante, a consequência prática é simples: não se assuste se "
           "o som que você produz parecer \"mais grave\" que a partitura sugere. "
           "É o esperado para a guitarra."),

        h ("Resumo do tópico D"),
        tbl ({ "Ideia", "O que fixar" },
             { { "Afinação padrão", "E2 A2 D3 G3 B3 E4 (Mi Lá Ré Sol Si Mi)" },
               { "Uma casa", "um semitom" },
               { "Casa 12", "repete a corda solta, uma oitava acima" },
               { "Referências", "casas 3, 5, 7 e 12" },
               { "Salto 3ª→2ª", "quarta justa vira terça maior (uma casa menos)" },
               { "Mesma nota", "pode ser tocada em cordas diferentes" },
               { "Transposição", "a guitarra soa uma oitava abaixo do escrito" } }),

        h ("Como estudar o tópico D na prática"),
        p ("Localização de notas é hábito, não talento. Quinze minutos por dia, "
           "durante duas semanas, valem mais que uma tarde de decoreba."),
        b ("Diga em voz alta as seis cordas soltas, da 6ª à 1ª, todos os dias."),
        b ("Toque a casa 5 de cada corda e diga a nota; depois a casa 7 e a 12."),
        b ("Escolha uma nota por dia e localize-a em todas as cordas."),
        b ("Toque a escala de Dó maior na 1ª posição lendo o mapa, sem olhar a "
           "tabela, conferindo depois."),
        b ("Toque uma nota na 6ª corda e a mesma nota na 1ª corda (duas oitavas "
           "acima) para treinar a relação entre as pontas."),
        c ("Meta do tópico: dado o nome de uma nota, apontar pelo menos duas "
           "posições no braço em menos de três segundos. Quando conseguir isso, "
           "você está pronto para os acordes e o CAGED."),
    };
}

} // namespace cursomusica::content
