#include "Course/Content/Topics.h"

// Topic 8D — SubV7 (Módulo 8, Etapa 8).
// Fonte de verdade do texto: docs/MUSIC.md §8 (bloco D).
namespace cursomusica::content
{

std::vector<ContentItem> topic8D()
{
    return {

        p (
            "O SubV7 é uma das substituições mais elegantes da harmonia. Ele troca o dominante tradicional por outro acorde de sétima dominante, meio-tom acima do alvo, e o resultado é uma resolução cromática — com o baixo descendo em vez de subir. É a substituição que dá o som característico da bossa nova e do jazz moderno."),
        p (
            "O nome vem de \"substituto do V7\". Em vez de resolver com o V7 do alvo, resolvemos com um acorde dominante localizado meio-tom acima. Em Dó, o V7 é G7; o SubV7 é Db7. Os dois resolvem em Dó, mas por caminhos diferentes. Entender por que os dois funcionam exige entender o trítono."),
        c (
            "Objetivo do tópico: compreender o SubV7, por que ele substitui o V7 e como usá-lo para criar resoluções cromáticas."),

        h ("A origem do SubV7"),
        p (
            "O que faz um dominante resolver é o trítono entre a sua terça e a sua sétima. Em G7, esse trítono é Si–Fá. Acontece que o acorde Db7 também contém um trítono: entre a sua terça (Fá) e a sua sétima (Dó bemol, enarmônico de Si). Os dois trítonos são formados pelas mesmas duas notas, apenas invertidas. Por isso os dois acordes resolvem no mesmo lugar."),
        b ("G7: trítono Si–Fá."),
        b ("Db7: trítono Fá–Dó bemol (que é o mesmo Si–Fá invertido)."),
        b ("Dois dominantes com o mesmo trítono são substitutos um do outro."),
        img ("m8_subv7", "G7 e Db7 compartilham o mesmo trítono; por isso os dois resolvem em Dó."),
        c (
            "Regra de ouro: todo dominante tem um SubV7 a um trítono de distância (seis semitons), e os dois são intercambiáveis."),

        h ("Por que o SubV7 soa diferente"),
        p (
            "Apesar de resolverem no mesmo acorde, os dois dominantes produzem sensações diferentes por causa do baixo. Em G7 → C, o baixo sobe uma quarta (Sol → Dó). Em Db7 → C, o baixo desce um semitom (Ré bemol → Dó). O movimento cromático descendente é muito mais suave e cria uma sensação de deslizamento, que é a marca do SubV7."),
        b ("G7 → C: baixo sobe uma quarta (Sol → Dó)."),
        b ("Db7 → C: baixo desce um semitom (Réb → Dó)."),
        b ("O semitom descendente é o que dá o som de bossa."),
        tbl ({ "Dominante", "Notas", "Baixo → alvo", "Sensação" }, {
            { "G7 (V7)", "G, B, D, F", "sobe 4ª (G → C)", "resolução forte" },
            { "Db7 (SubV7)", "Db, F, Ab, Cb", "desce 1/2 tom (Db → C)", "resolução suave" },
        }),
        aud ({ "C#3", "F3", "G#3", "B3", "C4", "E4", "G4" }, "Db7 (SubV7) resolvendo em C: o baixo desce meio-tom e o som desliza."),

        h ("Como construir um SubV7"),
        p (
            "Para construir o SubV7 de um alvo, suba meio-tom a partir da fundamental do alvo e forme um acorde de sétima dominante sobre essa nota. Em C, o SubV7 é Db7. Em G, o SubV7 é Ab7. Em F, o SubV7 é Gb7. Em Am, o SubV7 é Bb7. O processo é sempre o mesmo: meio-tom acima, dominante."),
        b ("SubV7 de C: Db7."),
        b ("SubV7 de G: Ab7."),
        b ("SubV7 de F: Gb7."),
        b ("SubV7 de Am: Bb7."),
        c (
            "Compare com o V7: o V7 fica uma quinta acima do alvo; o SubV7 fica meio-tom acima. São dois lados do mesmo caminho."),

        h ("SubV7 e a escala"),
        p (
            "O SubV7 costuma ser tocado com a escala lídia dominante, que é a escala mixolídia com a quarta aumentada. Isso significa que, além das notas do acorde, você pode usar a quarta aumentada como cor. Em Db7, a quarta aumentada é o Sol, que é justamente a fundamental do G7 que ele substitui. Há uma ligação íntima entre os dois acordes."),
        b ("Escala do SubV7: lídia dominante (mixolídia com 4ª aumentada)."),
        b ("A 4ª aumentada do SubV7 é a fundamental do V7 substituído."),
        b ("Usar a escala certa dá a cor certa à resolução."),

        h ("SubV7 no II-V-I"),
        p (
            "No contexto do II-V-I, o SubV7 aparece com frequência no lugar do V7. Em vez de Dm7 → G7 → CM7, temos Dm7 → Db7 → CM7. O ii permanece; o que muda é o dominante. O resultado é um II-V-I mais suave, com o baixo descendo Ré → Réb → Dó. Essa é uma das progressões mais comuns do jazz."),
        b ("II-V-I tradicional: Dm7 → G7 → CM7."),
        b ("II-SubV7-I: Dm7 → Db7 → CM7."),
        b ("O baixo desce cromaticamente: Ré → Réb → Dó."),
        tbl ({ "Progressão", "Acordes", "Baixo" }, {
            { "II-V-I maior", "Dm7 – G7 – CM7", "Ré – Sol – Dó" },
            { "II-SubV7-I", "Dm7 – Db7 – CM7", "Ré – Réb – Dó" },
            { "SubV7 isolado", "G7 – Db7 – CM7", "Sol – Réb – Dó" },
        }),

        h ("SubV7 encadeados"),
        p (
            "Os SubV7 podem se encadear como os dominantes secundários, mas sempre descendo cromaticamente. Uma sequência de SubV7 cria uma linha de baixo que desce meio-tom por meio-tom, um efeito muito usado em finais e em passagens modulantes. É o oposto da cadeia de dominantes, que desce em quintas."),
        b ("Cadeia de dominantes: desce em quintas (E7 → A7 → D7 → G7 → C)."),
        b ("Cadeia de SubV7: desce em semitons (… → Eb7 → Db7 → C)."),
        b ("A cadeia cromática cria um efeito de deslizamento."),
        aud ({ "D#3", "G3", "A#3", "C#4", "C#3", "F3", "G#3", "B3", "C4", "E4", "G4" },
             "Eb7 → Db7 → C: dois SubV7 encadeados descendo cromaticamente até a tônica."),

        h ("Como identificar de ouvido"),
        p (
            "O SubV7 tem um som reconhecível: parece que o baixo desliza para baixo até a tônica. Se você ouvir um dominante cujo baixo desce meio-tom para resolver, é um SubV7. Compare com o V7 tradicional, cujo baixo sobe uma quarta. O ouvido aprende a diferença rapidamente com o treino."),
        b ("O baixo desce meio-tom: provável SubV7."),
        b ("O baixo sobe uma quarta: provável V7."),
        b ("O SubV7 soa mais suave e mais \"escorregadio\"."),
        aud ({ "G2", "B2", "D3", "F3", "C3", "E3", "G3", "C#3", "F3", "G#3", "B3", "C4", "E4", "G4" },
             "G7 → C e depois Db7 → C: compare as duas resoluções."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é confundir o SubV7 com um dominante secundário. O SubV7 resolve na tônica (meio-tom abaixo), enquanto o dominante secundário resolve em outro grau. Outro erro é esquecer o bemol da fundamental: o SubV7 de C é Db7, não D7."),
        b ("SubV7 resolve no alvo, meio-tom abaixo."),
        b ("Não esqueça o bemol: Db7, não D7."),
        b ("O trítono é o mesmo do V7: use isso para conferir."),
        c (
            "Dica: para achar o SubV7, pense no V7 e desça um trítono. G7 → Db7. É o caminho mais rápido."),

        h ("Aplicação prática"),
        p (
            "Pratique substituir o V7 pelo SubV7 em progressões que você já conhece. Toque Dm7 → G7 → CM7 e depois Dm7 → Db7 → CM7, e compare as duas sensações. No instrumento, o SubV7 exige uma digitação diferente; use o app para conferir se as notas que você toca formam o acorde certo."),
        b ("Toque um II-V-I e depois troque o V7 pelo SubV7."),
        b ("Toque o SubV7 como arpejo antes de tocar como acorde."),
        b ("Compare as duas resoluções e escolha a que preferir."),
        part ("m8_partitura_subv7", { "Db3", "F3", "Ab3", "B3" },
              "Partitura do arpejo de Db7 (SubV7 de Dó). Ouça o baixo descendo meio-tom para resolver."),

        h ("SubV7 em outras tonalidades"),
        p (
            "O SubV7 existe para qualquer alvo. Basta subir meio-tom a partir da fundamental do alvo e formar um dominante. Em Sol, o SubV7 é Ab7; em Fá, é Gb7; em Ré, é Eb7; em Lá, é Bb7. Como o SubV7 está sempre a meio-tom do alvo, ele cria um movimento cromático em qualquer tom. Aprender a construí-lo em várias tonalidades torna a substituição automática."),
        b ("SubV7 de C: Db7."),
        b ("SubV7 de G: Ab7."),
        b ("SubV7 de F: Gb7."),
        b ("SubV7 de D: Eb7."),
        tbl ({ "Alvo", "V7", "SubV7", "Baixo → alvo" }, {
            { "C", "G7", "Db7", "Db → C" },
            { "G", "D7", "Ab7", "Ab → G" },
            { "F", "C7", "Gb7", "Gb → F" },
            { "D", "A7", "Eb7", "Eb → D" },
            { "Am", "E7", "Bb7", "Bb → A" },
        }),

        h ("SubV7 na guitarra"),
        p (
            "No instrumento, o SubV7 costuma ser tocado com a fundamental na quarta ou na terceira corda, o que facilita o movimento cromático do baixo. Uma forma útil é tocar o SubV7 como acorde de sétima dominante na região média do braço, deixando o baixo descer meio-tom até o alvo. Tocar as duas versões (V7 e SubV7) alternadamente treina o ouvido para a diferença entre as duas resoluções."),
        b ("Toque Db7 na região média e desça o baixo para C."),
        b ("Compare com G7 subindo o baixo para C."),
        b ("Ouça a diferença: subida em quarta contra descida em semitom."),
        aud ({ "G3", "B3", "D4", "F4", "C4", "E4", "G4", "Db4", "F4", "Ab4", "Cb5", "C4", "E4", "G4" },
             "G7 → C e depois Db7 → C: compare as duas resoluções em sequência."),

        h ("SubV7 e a relação com o V7"),
        p (
            "É útil pensar no SubV7 como uma inversão do V7. Se você tocar um V7 e, em seguida, mover cada nota meio-tom para baixo, obtém o SubV7. Essa relação visual e auditiva ajuda a lembrar a substituição: o SubV7 é o V7 \"de cabeça para baixo\". Do ponto de vista do trítono, os dois acordes são idênticos, apenas com as notas rearranjadas."),
        b ("V7 → SubV7: cada nota desce meio-tom."),
        b ("G7 (G, B, D, F) → Db7 (Db, F, Ab, Cb)."),
        b ("O trítono permanece: B–F vira F–Cb (mesmo som)."),
        c (
            "Pense no SubV7 como o espelho do V7. Essa imagem mental torna a substituição fácil de lembrar e de aplicar."),

        h ("Onde o SubV7 aparece"),
        p (
            "O SubV7 é onipresente no jazz e na bossa nova, e aparece também em baladas e em música pop sofisticada. Ele pode substituir o V7 em qualquer cadência, preparar uma modulação, ou simplesmente criar um movimento cromático numa progressão. Reconhecê-lo é essencial para tocar standards, porque muitas músicas usam o SubV7 no lugar do dominante tradicional."),
        b ("Jazz: substitui o V7 em cadências."),
        b ("Bossa nova: cria o movimento cromático característico."),
        b ("Baladas: suaviza a resolução."),
        c (
            "Sempre que uma resolução soar \"escorregadia\", com o baixo descendo, suspeite de um SubV7."),

        h ("SubV7 e modulação"),
        p (
            "O SubV7 é uma ferramenta poderosa para modulação. Para mudar de tom, você pode usar o SubV7 do novo tom, criando uma resolução cromática que aponta para a nova tônica. Em vez de uma modulação abrupta, a música desliza para o novo centro. Essa técnica é muito usada em transições suaves, especialmente na bossa nova."),
        b ("Para modular a C, use Db7 antes do C."),
        b ("O baixo desce meio-tom para a nova tônica."),
        b ("A modulação soa suave, sem corte."),
        tbl ({ "De", "Para", "SubV7 da modulação" }, {
            { "G maior", "C maior", "Db7" },
            { "C maior", "F maior", "Gb7" },
            { "F maior", "Bb maior", "B7" },
        }),

        h ("SubV7 e o II-V-I"),
        p (
            "Dentro do II-V-I, o SubV7 substitui o V7 e cria uma das cadências mais elegantes do jazz. Em Dó maior, a progressão Dm7 → Db7 → CM7 tem um baixo que desce cromaticamente (Ré, Ré bemol, Dó), o que soa suave e sofisticado. Essa cadência aparece em incontáveis standards e é uma das primeiras substituições que o estudante deve dominar."),
        b ("II-SubV7-I: Dm7 → Db7 → CM7."),
        b ("O baixo desce Ré → Ré bemol → Dó."),
        b ("A resolução soa suave e sofisticada."),
        c (
            "Pratique o II-SubV7-I ao lado do II-V-I tradicional. Alternar os dois treina o ouvido para reconhecer cada tipo de resolução."),

        h ("Resumo do tópico"),
        b ("SubV7 é um dominante meio-tom acima do alvo."),
        b ("Ele compartilha o trítono com o V7 e por isso resolve no mesmo lugar."),
        b ("O baixo desce um semitom, criando uma resolução suave."),
        b ("No II-V-I, substitui o V7: Dm7 → Db7 → CM7."),
        b ("Os SubV7 podem se encadear descendo cromaticamente."),
        c (
            "Nos exercícios deste tópico, toque o SubV7 e confira com o app. Ele reconhece as notas e verifica se o acorde montado corresponde ao pedido."),
    };
}

} // namespace cursomusica::content
