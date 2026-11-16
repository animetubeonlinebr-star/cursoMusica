#include "Course/Content/Topics.h"

// Topic 4G — Sistema 5 (CAGED) e famílias de acordes (Módulo 4, Etapa 4).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 4 — construção de acordes).
namespace cursomusica::content
{

std::vector<ContentItem> topic4G()
{
    return {

        p (
            "No módulo 1 você conheceu o Sistema 5 (CAGED) como um mapa de cinco formas que cobrem o braço. Agora ele volta como ferramenta de construção: cada forma não é só uma posição de acorde, mas uma família inteira. Da mesma forma que você monta um acorde maior, monta o menor, o de sétima e o diminuto usando a mesma forma. Entender isso é o que transforma o CAGED de desenho decorado em sistema de trabalho."),
        p (
            "A ideia central é simples: as cinco formas básicas (C, A, G, E, D) se repetem pelo braço e servem de molde para qualquer qualidade. Se você sabe a forma de Mi maior, sabe também a forma de Mi menor, Mi7 e Mim7 — basta alterar as notas certas. Neste tópico você aprende a usar o CAGED como gerador de famílias de acordes."),
        c (
            "CAGED é um mapa de cinco formas que cobrem o braço. Cada forma é um molde: serve para maior, menor, sétima e outras qualidades."),

        h ("Relembrando as cinco formas"),
        p (
            "As cinco formas do CAGED nascem dos cinco acordes básicos da primeira posição: Dó, Lá, Sol, Mi e Ré. Deslocadas pelo braço, elas cobrem todo o instrumento. Na ordem C → A → G → E → D, cada forma conecta-se à seguinte: a última nota de uma é a primeira da próxima. Depois da forma de Ré, o ciclo recomeça com a forma de Dó, uma oitava acima."),
        b ("C: forma do acorde de Dó na 1ª posição."),
        b ("A: forma do acorde de Lá, deslocada."),
        b ("G: forma do acorde de Sol, deslocada."),
        b ("E: forma do acorde de Mi, deslocada (a mais usada)."),
        b ("D: forma do acorde de Ré, deslocada."),
        img ("m4_caged_familias", "As cinco formas do CAGED (C, A, G, E, D) cobrindo o braço."),

        h ("Cada forma é um molde"),
        p (
            "A grande sacada do CAGED é que cada forma é um molde: as posições dos dedos marcam as notas do acorde (tônica, terça e quinta) e, quando você quer outra qualidade, altera apenas as notas que mudam. A forma de Mi, por exemplo, tem a tônica na 6ª corda, a quinta na 5ª, a tônica na 4ª, a terça na 3ª, a quinta na 2ª e a tônica na 1ª. Sabendo isso, você altera a terça para fazer o menor e acrescenta a sétima para fazer o de sétima."),
        tbl ({ "Corda (forma de E)", "Nota", "Função" }, {
            { "6ª", "tônica", "1" },
            { "5ª", "quinta", "5" },
            { "4ª", "tônica", "1 (oitava)" },
            { "3ª", "terça", "3" },
            { "2ª", "quinta", "5 (oitava)" },
            { "1ª", "tônica", "1 (duas oitavas)" },
        }),

        h ("Da forma maior para a menor"),
        p (
            "Para transformar a forma maior em menor, basta descer a terça um semitom. Em qualquer forma do CAGED, a terça está em uma corda específica; desça essa nota um semitom e você tem o acorde menor. É a mesma lógica que você viu nas tríades, aplicada a cada forma do sistema. Assim, uma única forma gera dois acordes: maior e menor."),
        b ("Localize a terça na forma."),
        b ("Desça-a um semitom: vira menor."),
        b ("Toda forma do CAGED funciona assim."),
        aud ({ "E2", "B2", "E3", "G#3", "B3", "E4" }, "Mi maior na forma de E (6ª corda na tônica)."),
        aud ({ "E2", "B2", "E3", "G3", "B3", "E4" }, "Mi menor na mesma forma: só a terça (Sol♯→Sol) desceu."),

        h ("Da tríade para a tétrade"),
        p (
            "Para acrescentar a sétima a uma forma do CAGED, você insere a nota que está uma terça acima da quinta. Em algumas formas a sétima cai em uma corda já usada; em outras, exige um pequeno ajuste. O resultado é uma família completa: cada forma gera a tríade maior, a menor, a de sétima maior, a dominante e a menor com sétima. Cinco formas × várias qualidades = dezenas de acordes."),
        b ("Tríade maior: a forma básica."),
        b ("Tríade menor: terça abaixada."),
        b ("Sétima maior: acrescente a sétima maior."),
        b ("Dominante: acrescente a sétima menor."),
        b ("Menor com sétima: terça menor + sétima menor."),

        h ("As cinco famílias"),
        p (
            "Podemos agrupar os acordes em famílias por qualidade. A família maior reúne os acordes maiores (0–4–7) e suas versões de sétima maior (0–4–7–11). A família menor reúne os menores (0–3–7) e os menores com sétima (0–3–7–10). A família dominante reúne os acordes de sétima (0–4–7–10) e suas alterações. A família diminuta reúne os diminutos e meio-diminutos. E a família aumentada reúne os aumentados. Cada família tem um som e um uso próprios."),
        tbl ({ "Família", "Semitons", "Som", "Uso típico" }, {
            { "Maior", "0–4–7 (7M: 0–4–7–11)", "aberto, estável", "tônica, subdominante" },
            { "Menor", "0–3–7 (m7: 0–3–7–10)", "fechado, suave", "relativa, ii do menor" },
            { "Dominante", "0–4–7–10", "tenso", "V, resolução" },
            { "Diminuta", "0–3–6 (m7♭5: 0–3–6–10)", "instável", "vii, ii do menor" },
            { "Aumentada", "0–4–8", "suspenso", "passagem, dominante alterado" },
        }),

        h ("Famílias no braço"),
        p (
            "Quando você aprende uma família inteira em uma forma, ganha liberdade no braço. Em vez de pensar 'aqui é o Dó maior, ali é o Dó menor', você pensa 'esta é a forma de Mi, e eu posso fazer maior, menor, sétima…'. Isso reduz drasticamente a quantidade de informação a memorizar e aumenta a capacidade de resposta a qualquer cifra. É o poder do CAGED como sistema."),
        b ("Aprenda uma forma e todas as suas qualidades."),
        b ("Pense em formas, não em acordes isolados."),
        b ("O mesmo molde serve em qualquer tônica."),

        h ("Famílias e tonalidade"),
        p (
            "Dentro de uma tonalidade, as famílias se distribuem pelos graus. Em Dó maior, o I e o IV são da família maior; o ii, o iii e o vi são da família menor; o V é da família dominante; o vii é da família diminuta. Reconhecer a família de cada grau ajuda a prever o som da progressão e a escolher a forma certa no braço. É a ponte entre a teoria e a prática."),
        tbl ({ "Grau em Dó", "Acorde", "Família" }, {
            { "I", "C / C7M", "maior" },
            { "ii", "Dm / Dm7", "menor" },
            { "iii", "Em / Em7", "menor" },
            { "IV", "F / F7M", "maior" },
            { "V", "G / G7", "dominante" },
            { "vi", "Am / Am7", "menor" },
            { "vii", "Bdim / Bm7♭5", "diminuta" },
        }),

        h ("O ciclo das formas"),
        p (
            "As cinco formas se conectam em ciclo: depois da forma de Dó vem a de Lá, depois a de Sol, a de Mi, a de Ré e, novamente, a de Dó uma oitava acima. Esse ciclo é o mapa do braço. Ao subir uma progressão pelo braço, você percorre as formas na ordem. Ao descer, percorre na ordem inversa. Decorar o ciclo é decorar o braço inteiro de uma só vez."),
        b ("Ordem: C → A → G → E → D → C (oitava acima)."),
        b ("Subir pelo braço: percorrer o ciclo."),
        b ("Descer: percorrer o ciclo inverso."),

        h ("Tônica, terça e quinta dentro da forma"),
        p (
            "Para usar o CAGED com segurança, você precisa saber onde estão a tônica, a terça e a quinta em cada forma. A tônica é a nota que dá o nome ao acorde e é a referência para transpor; a terça é a nota que muda quando você faz maior ou menor; a quinta pode ser alterada para fazer aumentado ou diminuto. Localizar essas três notas na forma é o que permite criar qualquer acorde a partir dela."),
        b ("Tônica: referência para transpor a forma."),
        b ("Terça: abaixe para o menor, confirme para o maior."),
        b ("Quinta: altere para aumentado (sobe 1) ou diminuto (desce 1)."),

        h ("Transpor uma forma pelo braço"),
        p (
            "Transpor uma forma é deslocá-la pelo braço até que a tônica caia na nota desejada. Se a forma de Mi maior tem a tônica na 6ª corda solta (Mi), para tocar Fá você move a forma uma casa acima; para Sol, três casas. Como cada casa é um semitom, você calcula o deslocamento pela distância entre a tônica original e a nova tônica. Esse é o mecanismo que faz uma única forma gerar doze acordes."),
        b ("Identifique a tônica da forma."),
        b ("Conte os semitons até a nova tônica."),
        b ("Desloque a forma pelo número de casas correspondente."),

        h ("CAGED e as escalas"),
        p (
            "O CAGED não serve apenas para acordes: cada forma contém também a escala daquele centro. A forma de Mi maior, por exemplo, contém a escala de Mi maior nas primeiras casas. Isso significa que, quando você aprende uma forma, aprende ao mesmo tempo o acorde e o território da escala. Essa ligação entre acorde e escala é o que permite improvisar sobre uma progressão sem sair da região."),
        b ("Cada forma contém a escala do seu centro."),
        b ("Acorde e escala compartilham o mesmo território."),
        b ("Improvisar fica mais fácil quando você vê o acorde e a escala juntos."),

        h ("CAGED e a harmonia"),
        p (
            "Com as cinco formas, você pode acompanhar uma progressão inteira em uma única região do braço, mudando apenas a forma e a qualidade de cada acorde. Isso é muito útil quando a música tem um ritmo que exige a mão parada em uma região. Em vez de saltar pelo braço, você mantém a mão no lugar e troca o molde. O acompanhamento fica mais fluido e mais controlado."),
        b ("Uma região, várias formas: a mão não salta."),
        b ("Troque a forma e a qualidade conforme a cifra."),
        b ("Ideal para ritmos que exigem a mão parada."),

        h ("Como praticar as famílias"),
        p (
            "Uma prática eficaz é escolher uma tônica e tocar todas as qualidades na mesma forma, uma após a outra: maior, menor, dominante, sétima maior, menor com sétima. Depois faça o mesmo na forma seguinte do ciclo. Em pouco tempo, você associa cada forma a um conjunto de acordes e consegue tocar qualquer cifra em qualquer região do braço."),
        b ("Uma tônica, uma forma, todas as qualidades."),
        b ("Depois passe para a forma seguinte do ciclo."),
        b ("Objetivo: responder a qualquer cifra em qualquer região."),
        part ("m4_partitura_progressao", { "C4", "A4", "D4", "G4" },
              "Partitura das fundamentais da progressão Dó – Lá menor – Ré menor – Sol, que percorre o ciclo."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é tratar o CAGED como cinco acordes e não como cinco moldes. Assim, você decora o Dó de cada forma, mas trava quando aparece um Cm7. Outro erro é ignorar a ordem do ciclo e tentar achar as formas 'a esmo', o que deixa buracos no braço. E há o erro de não saber qual nota é a tônica em cada forma, o que impede transpor."),
        b ("CAGED são moldes, não cinco acordes."),
        b ("Respeite a ordem do ciclo."),
        b ("Saiba onde está a tônica em cada forma."),

        h ("Aplicação musical"),
        p (
            "Escolha uma progressão simples — por exemplo, Dó – Lá menor – Ré menor – Sol — e toque-a usando uma única forma do CAGED, transpondo para cada acorde. Depois toque usando todas as formas, subindo pelo braço. Você vai perceber que o CAGED permite acompanhar a mesma música em qualquer região, com qualquer cor. O app reconhece as notas e confere cada acorde, aceitando qualquer forma do sistema."),
        b ("Toque a progressão com uma forma só, transpondo."),
        b ("Depois percorra o ciclo pelo braço."),
        b ("O app confere as notas, não a forma usada."),
        aud ({ "C4", "E4", "G4", "A3", "C4", "E4", "D4", "F4", "A4", "G3", "B3", "D4" },
             "Dó – Lá menor – Ré menor – Sol, todos reconhecidos pelo app."),

        h ("Resumo do tópico"),
        b ("O CAGED é um mapa de cinco formas que cobrem o braço."),
        b ("Cada forma é um molde: serve para maior, menor, sétima e outras."),
        b ("As famílias agrupam acordes por qualidade (maior, menor, dominante…)."),
        b ("As formas se conectam em ciclo: C → A → G → E → D → C."),
        b ("Dominar o CAGED é acompanhar qualquer cifra em qualquer região."),
        c (
            "Nos exercícios deste tópico, toque os acordes pedidos usando as formas do CAGED. O app reconhece as notas e confere a qualidade, aceitando qualquer posição do braço."),
    };
}

} // namespace cursomusica::content
