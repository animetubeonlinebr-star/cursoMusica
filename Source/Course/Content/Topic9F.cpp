#include "Course/Content/Topics.h"

// Topic 9F — Policordes (Modulo 9, Etapa 9).
// Fonte de verdade do texto: docs/MUSIC.md (bloco F da Etapa 9).
namespace cursomusica::content
{

std::vector<ContentItem> topic9F()
{
    return {

        p (
            "Policorde é a sobreposição de dois acordes. Em vez de empilhar notas uma a uma, o músico toca um acorde inteiro sobre outro, e a soma das duas camadas cria uma sonoridade nova. É um recurso central da música moderna, da bossa ao jazz e a fusão. Neste tópico você aprende como os policordes se formam e como usá-los."),
        p (
            "Você já sabe montar tríades e tétrades. O policorde leva essa ideia um passo adiante: cada camada é um acorde completo, e a relação entre as camadas é o que define a sonoridade final. Entender essa relação é o que separa o uso consciente do acaso."),

        h ("O que é um policorde"),
        p (
            "Um policorde é formado por dois ou mais acordes soando ao mesmo tempo. Normalmente, um acorde fica na região grave (o baixo) e o outro na região aguda. O acorde grave fixa a harmonia, e o agudo acrescenta tensão e cor. A notação mais comum mostra o acorde de cima sobre uma barra e o de baixo embaixo dela, como D/C."),
        b ("Duas camadas: um acorde inferior (baixo) e um superior."),
        b ("A camada inferior define a harmonia de base."),
        b ("A camada superior acrescenta tensão e cor."),
        img ("m9_policordes", "Policorde: uma tríade superior sobre uma tríade inferior. D sobre C."),
        aud ({ "C4", "E4", "G4", "D5", "F#5", "A5" },
             "Policorde D/C: tríade de Do grave com tríade de Re aguda. A tensão vem do Re sobre Do."),

        h ("A diferença entre policorde e slash chord"),
        p (
            "É comum confundir policorde com acorde com baixo invertido, o slash chord. A diferença está no conteúdo. No slash chord, como C/E, o baixo é apenas uma nota do próprio acorde (o Mi). No policorde, como D/C, o baixo é um acorde completo, e o acorde de cima traz notas que não pertencem ao de baixo. Essa sobreposição de dois conjuntos é o que faz o policorde soar mais rico."),
        tbl ({ "Estrutura", "O que é", "Exemplo", "Efeito" }, {
            { "Acorde simples", "três ou quatro notas de uma vez", "C", "cor básica" },
            { "Slash chord", "acorde com nota do próprio acorde no baixo", "C/E", "inversão, baixo mais suave" },
            { "Policorde", "dois acordes empilhados", "D/C", "tensão e cor novas" },
        }),
        c (
            "Regra prática: se o baixo é uma nota do acorde de cima, e uma inversão; se o baixo é um acorde inteiro, e um policorde."),

        h ("Como os policordes se formam"),
        p (
            "A forma mais comum de construir um policorde é escolher uma tríade maior para a camada superior e sobrepor a uma tríade maior ou menor embaixo. A combinação gera tensões previsíveis. Por exemplo, uma tríade maior sobreposta a outra tríade maior a um tom de distância produz nona, quarta aumentada e sexta — as tensões típicas do som moderno."),
        b ("Tríade maior sobre maior a um tom: tensões 9, #11 e 13."),
        b ("Tríade maior sobre dominante: tensões 9, #11 e 13 sobre o dominante."),
        b ("Tríade menor sobre maior: cor menor com tensões."),
        aud ({ "C4", "E4", "G4", "D5", "F#5", "A5" },
             "Re maior sobre Do maior: as tensões 9, #11 e 13 aparecem na camada aguda."),

        h ("Policordes na guitarra"),
        p (
            "Na guitarra, o policorde tem uma vantagem natural: como o instrumento tem seis cordas, é fácil dividir as cordas graves e agudas em duas camadas. Uma forma comum toca a tríade inferior nas cordas 5 e 4 e a superior nas cordas 3, 2 e 1. Assim, cada camada fica clara e o ouvido separa as duas sonoridades."),
        b ("Camada inferior nas cordas graves, superior nas agudas."),
        b ("Use dedilhado ou palhetada para separar as camadas."),
        b ("A forma se desloca pelo braço como qualquer acorde."),
        part ("m9_partitura_policorde", { "C4", "E4", "G4", "D5", "F#5", "A5" },
              "Partitura do policorde D/C: tríade de Ré sobre a tríade de Dó (com o seu áudio)."),
        c (
            "Se as duas camadas se misturarem, o policorde perde a identidade e soa apenas como um acorde cheio. Toque as camadas em registros bem separados."),

        h ("Onde os policordes aparecem"),
        p (
            "Os policordes são muito usados em estilos que valorizam harmonia rica. Na bossa nova e no jazz, aparecem como acordes de passagem e como tensões sobre dominantes. Na fusão e no rock progressivo, dão a cor densa que caracteriza o gênero. Na música instrumental, servem para criar clímaxes antes de resoluções."),
        b ("Bossa e jazz: tensões sobre dominantes e acordes de passagem."),
        b ("Fusão e rock progressivo: densidade e cor."),
        b ("Música instrumental: clímaxes antes da resolução."),

        h ("Construindo o seu policorde"),
        p (
            "Para construir um policorde, comece pelo baixo. Escolha o acorde que define a harmonia e toque-o nas cordas graves. Depois, escolha uma tríade para cima que traga as tensões que você quer. Teste diferentes distâncias entre as camadas e ouça como a cor muda. O ouvido é o melhor guia."),
        b ("Defina primeiro a harmonia de base."),
        b ("Escolha a tríade superior pela tensão que ela traz."),
        b ("Teste a distância entre as camadas até a cor agradar."),
        aud ({ "C4", "E4", "G4", "A4", "C#5", "E5" },
             "Uma tríade maior sobre Do: cada distância muda a cor do policorde."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é tocar o policorde sem separar as camadas, o que produz um som embaralhado. Outro erro é sobrepor acordes sem relação, criando um cluster involuntário. O policorde precisa de lógica: a relação entre as camadas é o que faz sentido musical."),
        b ("Misturar as camadas no mesmo registro: o policorde perde a identidade."),
        b ("Sobrepor acordes sem relação harmônica."),
        b ("Esquecer a função do baixo: ele define a harmonia."),
        c (
            "Se o acorde soar confuso, separe mais as camadas no registro. O ouvido precisa distinguir as duas sonoridades."),

        h ("Aplicando na prática"),
        p (
            "Tome uma progressão simples e substitua um dos acordes por um policorde. Comece com D/C sobre Do maior e ouça como a tensão muda. Depois, experimente outras sobreposições e escolha as que melhor se encaixam na música. Registre as que você gostou, para reusar."),
        b ("Substitua um acorde da progressão por um policorde."),
        b ("Experimente diferentes tríades superiores sobre o mesmo baixo."),
        b ("Registre as sobreposições que funcionaram."),
        aud ({ "C4", "E4", "G4", "D5", "F#5", "A5", "G4", "C5" },
             "Policorde resolvendo: a tensão da camada aguda cede para a tônica."),

        h ("Policordes e improvisação"),
        p (
            "Os policordes também influenciam a improvisação. Quando a harmonia tem uma estrutura superior, o improvisador pode tocar as notas dessa estrutura como parte do seu vocabulário. Assim, o solo acompanha a cor do arranjo em vez de tocar apenas a escala do acorde de baixo. Isso cria uma integração entre a harmonia e a melodia que caracteriza a música instrumental madura."),
        b ("Improvise usando as notas da camada superior."),
        b ("A melodia acompanha a cor do arranjo."),
        b ("A integração entre harmonia e melodia é a marca da música madura."),

        h ("Policordes no arranjo"),
        p (
            "Em um arranjo, o policorde pode ser distribuido entre instrumentos. O baixo toca a camada inferior, o teclado toca a superior, e a guitarra faz uma mistura das duas. Essa divisão faz com que o policorde soe amplo, sem que nenhum instrumento fique sobrecarregado. É uma técnica comum em arranjos de jazz e de música instrumental."),
        b ("Distribua as camadas entre os instrumentos."),
        b ("O baixo toca a camada inferior."),
        b ("O teclado e a guitarra dividem a superior."),

        h ("Policordes e a percepção do ouvinte"),
        p (
            "O ouvinte percebe o policorde como uma sonoridade única, mas o ouvido treinado consegue distinguir as duas camadas. Isso significa que um policorde bem construído soa rico e coerente ao mesmo tempo. O segredo está na distância entre as camadas: se elas estiverem bem separadas, o ouvido separa; se estiverem juntas, soa como um acorde cheio."),
        b ("O ouvinte percebe uma sonoridade única."),
        b ("O ouvido treinado distingue as camadas."),
        b ("A distância entre as camadas define a clareza."),

        h ("Policordes e a notação"),
        p (
            "Na cifra, o policorde aparece com o acorde de cima separado por uma barra do acorde de baixo, como D/C ou F/G. Às vezes, escreve-se apenas o acorde de cima, quando a convenção do estilo já deixa claro o baixo. Saber ler essa notação é o que permite tirar uma música de ouvido e tocar a harmonia exata que o compositor escreveu."),
        b ("A barra separa o acorde de cima do de baixo."),
        b ("D/C significa tríade de Ré sobre a tríade de Dó."),
        b ("Alguns estilos omitem o baixo por convenção."),

        h ("Policordes e a tensão controlada"),
        p (
            "A grande vantagem do policorde é controlar a tensão. Em vez de acrescentar notas uma a uma, o músico escolhe uma tríade inteira para a camada de cima, e a tensão vem pronta. Isso torna a harmonia mais rica sem exigir que o aluno pense em cada intervalo separadamente. É por isso que o policorde é tão usado na música instrumental."),
        b ("O policorde controla a tensão de uma vez."),
        b ("A tríade superior traz o conjunto de tensões pronto."),
        b ("É mais simples de pensar do que empilhar nota a nota."),

        h ("Policordes e a condução de vozes"),
        p (
            "Um policorde bem usado também conduz as vozes. Ao mudar de um policorde para outro, as notas da camada superior podem se mover por graus conjuntos, criando uma linha melódica dentro da harmonia. Esse é um dos segredos do arranjo de jazz: a camada de cima vira uma segunda melodia, e o ouvinte acompanha esse movimento mesmo sem perceber."),
        b ("A camada superior pode formar uma linha melódica."),
        b ("As notas se movem por graus conjuntos."),
        b ("Recurso típico do arranjo de jazz."),

        h ("Policordes no repertório"),
        p (
            "Você encontra policordes em muitos estilos. Na bossa nova, aparecem como acordes de passagem e como tensões sobre dominantes. No jazz, são parte do vocabulário harmônico desde os anos sessenta. Na fusão e no rock progressivo, dão a densidade que caracteriza o gênero. Reconhecer o policorde de ouvido ajuda a tirar músicas complexas de ouvido."),
        b ("Bossa nova: acordes de passagem e tensões."),
        b ("Jazz: vocabulário harmônico desde os anos sessenta."),
        b ("Fusão e rock progressivo: densidade e cor."),

        h ("Policordes e o baixo"),
        p (
            "O baixo é a parte mais importante de um policorde, porque é ele que define a harmonia. Se o baixo mudar, o policorde inteiro muda de função, mesmo que a camada de cima permaneça. Por isso, ao tocar um policorde, comece sempre pelo baixo: ele é a fundação sobre a qual a camada de cima constrói a tensão."),
        b ("O baixo define a harmonia do policorde."),
        b ("Mudar o baixo muda a função, mesmo com a camada de cima igual."),
        b ("Toque o baixo primeiro: ele é a fundação."),

        h ("Erros comuns com policordes"),
        p (
            "Além de misturar as camadas no mesmo registro, o aluno costuma esquecer a função do baixo ou sobrepor acordes sem relação. O policorde precisa de lógica: as duas camadas devem ter uma relação harmônica clara. Sem essa lógica, o acorde soa apenas como um aglomerado de notas, e não como uma sonoridade intencional."),
        b ("Misturar as camadas no mesmo registro."),
        b ("Esquecer a função do baixo."),
        b ("Sobrepor acordes sem relação harmônica."),
        c (
            "Um policorde bem construído soa rico e coerente. Se soar confuso, verifique se as duas camadas têm uma relação clara."),

        h ("Resumo do tópico"),
        b ("Policorde = dois acordes empilhados."),
        b ("O baixo define a harmonia; a camada aguda traz tensão."),
        b ("Diferente do slash chord, o baixo é um acorde completo."),
        b ("Na guitarra, as camadas se separam por registro."),
        b ("Usado em bossa, jazz, fusão e música instrumental."),
        c (
            "Nos exercícios, toque os policordes e as suas resoluções. O app reconhece as notas e confere as classes de altura das duas camadas."),
    };
}

} // namespace cursomusica::content
