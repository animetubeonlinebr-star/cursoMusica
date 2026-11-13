#include "Course/Content/Topics.h"

// Topic E — Pestanas (barré e meio barré).
// Source: pdf-mozart-mello-livroestudosdeguitarra4em1 (técnica) and
// pdf-caged-e-derivaoes-de-acordes (a pestana torna as formas móveis).
namespace cursomusica::content
{

std::vector<ContentItem> topicE()
{
    return {
        p ("A pestana é a técnica que mais assusta o iniciante — e também a que "
           "mais abre portas. Com um único dedo pressionando várias cordas de uma "
           "vez, você transforma qualquer forma de acorde em uma forma móvel, que "
           "pode ser levada para qualquer região do braço. É o alicerce do sistema "
           "CAGED e o que permite tocar em tonalidades distantes sem decorar "
           "dezenas de acordes novos."),

        h ("O que é uma pestana"),
        p ("Pestana é pressionar, com um único dedo — quase sempre o indicador — "
           "duas ou mais cordas na mesma casa. O dedo funciona como o rastilho do "
           "instrumento: cria um \"novo ponto zero\" a partir do qual o braço "
           "passa a soar mais agudo. Os demais dedos montam as notas do acorde à "
           "frente do dedo que faz a pestana."),
        p ("Quando o indicador cobre todas as seis cordas, chamamos de pestana "
           "completa ou barré. Quando cobre apenas parte das cordas (em geral de "
           "duas a quatro), chamamos de meio barré ou meia pestana. As duas "
           "técnicas aparecem o tempo todo na música popular."),
        tbl ({ "Tipo", "Cobertura", "Uso típico" },
             { { "Pestana completa (barré)", "todas as 6 cordas",
                 "acordes com fundamental na 6ª corda; acordes móveis" },
               { "Meio barré (meia pestana)", "2 a 4 cordas",
                 "acordes com fundamental na 5ª ou na 4ª corda" },
               { "Pestana parcial (3 cordas)", "3 cordas graves",
                 "formas de Fá, Si♭, Si maiores" } }),
        c ("A palavra \"barré\" vem do francês barrer, \"barrar\". É o mesmo "
           "recurso que o violão clássico usa há séculos e que a guitarra popular "
           "incorporou como base dos acordes móveis."),

        h ("Por que a pestana existe: formas móveis"),
        p ("Se você aprende um acorde de Fá maior com pestana na 1ª casa, pode "
           "deslizar essa mesma forma duas casas à frente e obter um Sol maior; "
           "mais duas casas e obtém um Lá maior. A forma permanece idêntica — muda "
           "apenas a posição, e portanto o nome do acorde."),
        tbl ({ "Forma de Fá deslocada para...", "Acorde resultante" },
             { { "1ª casa", "Fá (F)" },
               { "3ª casa", "Sol (G)" },
               { "5ª casa", "Lá (A)" },
               { "7ª casa", "Si (B)" },
               { "8ª casa", "Dó (C)" },
               { "10ª casa", "Ré (D)" },
               { "13ª casa", "Fá (F), uma oitava acima" } }),
        p ("Essa mobilidade é a razão pela qual a pestana é tão valorizada: com "
           "poucas formas na mão, você toca em qualquer tom. É exatamente a ideia "
           "que o sistema CAGED organiza em cinco formas (tópico F)."),
        c ("A regra que sustenta tudo: cada casa é um semitom. Ao mover a forma "
           "uma casa, o acorde sobe meio-tom. Ao mover doze casas, sobe uma "
           "oitava e volta ao mesmo nome."),

        h ("Como fazer uma pestana completa (barré)"),
        img ("e_pestana_fa", "Fá maior com pestana na 1ª casa."),
        p ("A execução correta da pestana depende mais de posição e pressão "
           "distribuída do que de força bruta. Vamos por partes."),
        b ("Posicione o indicador deitado, levemente de lado (a parte óssea, não "
           "a polpa mole), encostando as cordas logo atrás do traste — não em "
           "cima dele, nem no meio da casa."),
        b ("Alinhe o dedo paralelo ao traste. Se ele ficar torto, algumas cordas "
           "escapam."),
        b ("Aproxime o polegar do centro do braço, atrás. Isso dá alavanca e "
           "permite que os dedos pressionem com menos esforço."),
        b ("Pressione o mínimo necessário. Se você precisa apertar muito, a "
           "posição está errada; ajuste o dedo mais perto do traste."),
        b ("Relaxe o ombro e o pulso. A tensão excessiva é o principal inimigo da "
           "pestana; ela cansa a mão e abafa o som."),
        c ("Teste rápido: faça a pestana e toque corda por corda. Todas devem "
           "soar limpas. As cordas que falham ficam exatamente onde o dedo está "
           "mal posicionado ou longe do traste."),

        h ("Como fazer um meio barré"),
        img ("e_meio_barre_bm", "Si menor com meio barré na 2ª casa."),
        p ("O meio barré é mais fácil que a pestana completa e é o primeiro passo "
           "para quem está começando. Em vez de cobrir as seis cordas, o indicador "
           "cobre apenas as cordas necessárias — por exemplo, as duas ou três "
           "primeiras (mais graves)."),
        b ("Acordes com fundamental na 5ª corda, como Si♭ ou Fá#m, costumam usar "
           "meio barré cobrindo da 5ª à 1ª corda."),
        b ("Acordes com fundamental na 4ª corda, como Ré com pestana, cobrem da "
           "4ª à 1ª corda."),
        b ("A ponta do dedo pode se apoiar levemente na borda do braço, o que "
           "ajuda a firmar o meio barré."),
        c ("A ordem natural de aprendizado é: primeiro o meio barré de duas ou "
           "três cordas; depois a pestana completa. Não pule etapas."),

        h ("Por que algumas cordas \"morrem\" na pestana"),
        p ("O problema clássico é a corda abafada no meio da pestana: ela soa "
           "fraca ou nem soa. Isso quase nunca é falta de força; é posição. As "
           "articulações do dedo criam pequenos vales por onde a corda escapa."),
        tbl ({ "Sintoma", "Causa provável", "Correção" },
             { { "Corda do meio abafada", "vale entre as falanges do dedo",
                 "gire o dedo levemente de lado e aproxime do traste" },
               { "Corda aguda abafada", "ponta do indicador muito longe do traste",
                 "levante a ponta e aproxime-a do traste" },
               { "Zumbido geral", "dedo em cima do traste ou longe dele",
                 "posicione logo atrás do traste" },
               { "Mão cansada rápido", "polegar longe do centro / pressão excessiva",
                 "traga o polegar para o centro e relaxe" } }),
        p ("Outro recurso é ajustar a altura da ação do instrumento (tópico A). "
           "Um instrumento com cordas muito altas torna a pestana quase "
           "impossível; um bem regulado facilita enormemente."),
        c ("Paciência: a pestana limpa costuma levar semanas de prática diária. "
           "Faça séries curtas e pare antes de sentir dor. A calosidade e a "
           "resistência vêm com o tempo, não com a força de um dia."),

        h ("Exercícios graduais para dominar a pestana"),
        p ("Treine em etapas, aumentando a dificuldade. Cada etapa prepara a "
           "seguinte."),
        b ("Etapa 1 — meio barré: faça a pestana apenas nas duas primeiras cordas "
           "e toque-as juntas. Ouça se as duas soam limpas."),
        b ("Etapa 2 — três cordas: amplie para três cordas graves e repita o "
           "teste de som."),
        b ("Etapa 3 — pestana completa: cubra as seis cordas, sem ainda montar "
           "acorde, e toque cada corda isoladamente."),
        b ("Etapa 4 — forma de Fá: monte o acorde de Fá maior completo (pestana na "
           "1ª casa) e verifique todas as cordas."),
        b ("Etapa 5 — mobilidade: deslize a forma de Fá pelas casas 3, 5, 7 e 8, "
           "nomeando o acorde resultante em cada posição."),
        c ("Progressão do app: o exercício EX-1.E.1 cobra exatamente a pestana de "
           "Fá na 1ª casa, com todas as cordas soando. Use-o como teste depois de "
           "praticar as etapas acima."),

        h ("Pestana e CAGED: a ponte para o tópico seguinte"),
        p ("Sem pestana, você só toca acordes na primeira posição. Com ela, as "
           "cinco formas do CAGED cobrem o braço inteiro. É por isso que o estudo "
           "da pestana é a preparação direta para o sistema CAGED."),
        b ("Cada forma do CAGED (C, A, G, E, D) pode ser tocada com pestana, "
           "tornando-se móvel."),
        b ("A forma de Mi (E) com pestana é a mais usada para acordes maiores "
           "móveis: sua fundamental está na 6ª corda."),
        b ("A forma de Lá (A) com pestana é usada para acordes com fundamental na "
           "5ª corda."),
        c ("Resumo do tópico E: a pestana é um dedo que vira rastilho; permite "
           "formas móveis; exige posição, não força; e é o alicerce do CAGED. "
           "Domine primeiro o meio barré, depois a pestana completa."),

        h ("A pestana no repertório: onde ela aparece"),
        p ("A pestana não é um exercício isolado: ela está em praticamente toda a "
           "música popular. Reconhecê-la no repertório ajuda a praticá-la com "
           "propósito."),
        b ("Fá maior (F) e Si♭ (B♭) na 1ª posição usam pestana completa ou meio "
           "barré."),
        b ("Si menor (Bm) e Fá♯ menor (F♯m) usam meio barré na 2ª casa."),
        b ("Acordes com fundamental na 6ª corda (formas móveis de Mi) usam pestana "
           "completa."),
        b ("Riffs e melodias com notas pedal usam pestana parcial para manter as "
           "cordas agudas soando."),
        c ("Dica de repertório: escolha uma música que você goste e que tenha um "
           "acorde com pestana. Praticar a técnica dentro da música motiva muito "
           "mais que exercícios isolados."),

        h ("Cuidados com a saúde da mão"),
        p ("A pestana exige força, e força em excesso machuca. Alguns cuidados "
           "evitam tendinite e dor desnecessária."),
        b ("Aqueca antes de praticar: movimente os dedos, faça alongamentos leves "
           "e toque alguns minutos em posições fáceis antes de atacar a pestana."),
        b ("Faça pausas curtas. Séries de trinta segundos a um minuto, com "
           "descanso, são mais produtivas que insistir por dez minutos seguidos."),
        b ("Pare ao primeiro sinal de dor aguda. Dor de cansaço passa; dor de "
           "lesão avisa."),
        b ("Verifique a regulagem do instrumento. Cordas muito altas exigem força "
           "desnecessária; uma ação bem ajustada (tópico A) facilita tudo."),
        c ("Se a mão doer com frequência, reveja a posição do polegar e a altura "
           "do braço. Muitas vezes o problema é postura, não força."),

        h ("Como estudar o tópico E na prática"),
        p ("A pestana é técnica pura: melhora com repetição inteligente, não com "
           "tentativas aleatórias. Faça este roteiro diário."),
        b ("Comece pelo meio barré de duas cordas; toque-as juntas e confirme que "
           "ambas soam."),
        b ("Avance para três cordas e depois para a pestana completa, sempre "
           "tocando corda por corda para conferir."),
        b ("Monte a forma de Fá na 1ª casa e deslize-a pelas casas 3, 5, 7 e 8, "
           "nomeando o acorde em cada posição."),
        b ("Toque uma música simples que use pestana e observe a diferença entre "
           "aplicar a técnica e apenas apertar."),
        b ("Encerre com alongamento leve e descanso. Não treine com dor."),
        c ("Meta do tópico: fazer uma pestana completa soando todas as seis cordas "
           "e deslocá-la por várias casas sem perder a clareza. Quando conseguir "
           "isso, o tópico F (CAGED) vai fluir naturalmente."),

        h ("Pestana ou capotraste? Entenda a diferença"),
        p ("Muita gente confunde a pestana com o capotraste (capo, ou \"braçadeira\"). "
           "São coisas diferentes que, às vezes, produzem efeitos parecidos."),
        tbl ({ "Recurso", "O que é", "Quando usar" },
             { { "Pestana", "dedo pressionando várias cordas numa casa",
                 "tocar acordes móveis; parte da técnica da mão esquerda" },
               { "Capotraste", "acessório preso ao braço, apertando todas as cordas",
                 "mudar a tonalidade mantendo as formas abertas" },
               { "Pestana parcial", "dedo cobrindo só as cordas necessárias",
                 "acordes com fundamental na 5ª ou 4ª corda" } }),
        p ("Com o capotraste, você sobe a tonalidade sem mudar as formas dos "
           "acordes: as mesmas posições que davam Dó passam a dar Ré, por exemplo. "
           "Com a pestana, você toca formas móveis com o próprio dedo. Os dois "
           "recursos convivem e servem a propósitos diferentes."),
        c ("Curiosidade: se você prender o capotraste na 1ª casa, as formas "
           "abertas de Mi, Lá, Ré, etc. sobem meio-tom. É o mesmo efeito de mover "
           "uma forma com pestana, mas sem esforço da mão esquerda."),

        h ("Resumo do tópico E"),
        tbl ({ "Ideia", "O que fixar" },
             { { "Pestana completa", "indicador cobre as 6 cordas" },
               { "Meio barré", "indicador cobre 2 a 4 cordas" },
               { "Função", "tornar as formas de acorde móveis" },
               { "Posição", "dedo logo atrás do traste, polegar no centro" },
               { "Pressão", "mínima necessária; posição vence força" },
               { "Corda abafada", "ajuste o dedo, não aperte mais" },
               { "Ligação", "alicerce do sistema CAGED (tópico F)" } }),
    };
}

} // namespace cursomusica::content
