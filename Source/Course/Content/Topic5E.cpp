#include "Course/Content/Topics.h"

// Topic 5E — Função dominante (Módulo 5, Etapa 5).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 5, bloco E).
namespace cursomusica::content
{

std::vector<ContentItem> topic5E()
{
    return {

        p (
            "A função dominante é a mais dramática das três. Se a tônica é o repouso e a subdominante é o afastamento, o dominante é a tensão: o acorde que faz a música pedir, com força, para voltar para casa. É a função que cria a expectativa da resolução, e é por isso que ela aparece no fim de quase toda progressão, logo antes do acorde de tônica."),
        p (
            "Entender o dominante é entender por que a música 'puxa' para a tônica. A força dessa atração vem de um intervalo específico dentro do acorde — o trítono — e de uma nota que 'quer' subir meio tom para chegar à tônica. Neste tópico você aprende a reconhecer essa tensão, a localizá-la no campo harmônico e a usá-la para criar resolução."),

        h ("O que é a função dominante"),
        p (
            "Função dominante é a função de tensão da tonalidade. Ela é exercida pelo acorde de grau V — em Dó maior, o acorde de G. Quando a música chega ao dominante, o ouvido sente que algo precisa acontecer: há uma instabilidade que só se resolve quando o acorde volta para a tônica. Essa instabilidade é o motor da harmonia funcional."),
        p (
            "O nome 'dominante' já diz muito: é o acorde que domina a expectativa. Depois de ouvi-lo, o ouvido praticamente exige a volta ao repouso. Essa é a razão pela qual o dominante é o penúltimo acorde da maioria das cadências — ele prepara a chegada da tônica de forma quase inevitável."),
        b ("Função dominante = tensão, instabilidade, pedido de resolução."),
        b ("Exercida pelo acorde de grau V (G, em Dó maior)."),
        b ("Cria a expectativa que a tônica vem resolver."),
        img ("m5_funcoes_tres", "As três funções: a dominante é o polo de tensão que empurra a música de volta para a tônica."),

        h ("Por que o dominante pede resolução"),
        p (
            "A força do dominante vem de duas notas do acorde que apontam para a tônica. A terça do acorde de G é o Si, que está a meio tom abaixo do Dó (a tônica); e a sétima, quando presente, é o Fá, que está a meio tom acima do Mi (a terça da tônica). Essas duas notas criam a tendência de movimento que o ouvido percebe como 'precisa resolver'."),
        p (
            "Quando o acorde de G resolve em C, o Si sobe para o Dó e o Fá desce para o Mi — movimentos de meio tom, os menores possíveis, e por isso os mais convincentes. Essa condução de vozes é o que faz a cadência dominante–tônica soar tão natural, e é o que você vai aprender a ouvir e a executar."),
        b ("A terça do dominante (Si) está meio tom abaixo da tônica (Dó)."),
        b ("A sétima do dominante (Fá) está meio tom acima da terça da tônica (Mi)."),
        b ("Esses meio tons criam a tendência de movimento que resolve na tônica."),
        aud ({ "G4", "B4", "D5", "C5", "E5", "G5" },
             "Dominante (G) resolvendo na tônica (C): o Si sobe para o Dó e o Fá desce para o Mi."),

        h ("A dominante no campo harmônico"),
        p (
            "No campo harmônico maior, a função dominante é exercida pelo grau V e, com mais força, pelo grau V com sétima (V7). O acorde de G7 contém o trítono Si–Fá, que é a fonte da tensão máxima, e por isso é o acorde dominante por excelência. Ele é tão direcional que praticamente obriga a resolução na tônica."),
        p (
            "Além do V e do V7, o grau vii° também exerce função dominante, porque compartilha notas com o V7 e contém o mesmo trítono. É um substituto do dominante, muito usado para criar tensão com um acorde diminuto. Em Dó maior, o Bdim tem a mesma força direcional do G7, só que com outra cor."),
        tbl ({ "Grau", "Acorde (Dó maior)", "Relação com a dominante", "Tensão" }, {
            { "V", "G", "dominante principal", "alta" },
            { "V7", "G7", "dominante com sétima (trítono)", "máxima" },
            { "vii°", "Bdim", "substituto (compartilha o trítono)", "alta" },
        }),
        c (
            "O V7 é o dominante mais forte porque contém o trítono Si–Fá. Esse intervalo é a própria 'mola' que empurra a música de volta para a tônica."),
        aud ({ "G4", "B4", "D5", "F5", "C5", "E5", "G5" },
             "Dominante com sétima (G7) resolvendo em C: a tensão do trítono se desfaz na tônica."),

        h ("Como a dominante soa"),
        p (
            "O ouvido reconhece o dominante pela sensação de instabilidade. Diferente da subdominante, que soa como movimento tranquilo, o dominante soa como um ponto de interrogação: a música não pode terminar ali. É uma tensão que pede, ativamente, uma resposta na tônica."),
        p (
            "Uma forma de treinar isso é tocar I → V e parar. O ouvido vai ficar esperando o I. Depois toque I → V → I e repare no alívio. Essa diferença entre 'parar no V' e 'resolver no I' é a experiência mais direta da função dominante, e é o que os exercícios deste tópico vão pedir que você reconheça e execute."),
        b ("O dominante soa instável e inconclusivo."),
        b ("Parar no dominante deixa o ouvido esperando a tônica."),
        b ("Resolver dominante → tônica produz a sensação de chegada."),
        aud ({ "C4", "E4", "G4", "G4", "B4", "D5" },
             "Tônica (C) indo para dominante (G): o ouvido percebe que a música saiu do repouso e pede a volta."),

        h ("A cadência dominante–tônica"),
        p (
            "A sequência dominante → tônica é a cadência mais forte da música tonal, e a base de toda a harmonia funcional. Ela aparece em todos os estilos, do clássico ao pop, do jazz ao rock. Reconhecer essa cadência de ouvido é reconhecer o fim de uma frase musical, mesmo sem saber a tonalidade."),
        p (
            "A cadência pode ser preparada pela subdominante (IV → V → I) ou pelo ii (ii → V → I), mas o núcleo é sempre V → I. É esse par de acordes que cria a sensação de 'aqui termina a frase'. Os exercícios e o gate deste módulo vão cobrar essa cadência tocada no instrumento, com o app conferindo as notas."),
        b ("V → I é a cadência mais forte (autêntica)."),
        b ("Pode ser preparada por IV → V → I ou ii → V → I."),
        b ("É o fim de frase mais comum da música tonal."),
        part ("m5_partitura_iv_v_i", { "F4", "A4", "C5", "G4", "B4", "D5", "C5", "E5", "G5" },
              "Partitura de IV – V – I: a subdominante prepara o dominante, que resolve na tônica."),

        h ("A dominante na guitarra"),
        p (
            "No braço, o dominante está a uma quinta acima da tônica — a mesma relação que a subdominante tem, mas no sentido oposto. Em Dó maior, o G está na 6ª corda, casa 3, ou na 5ª corda, casa 10. Toque o acorde de dominante com a sétima (G7) para sentir a tensão máxima, e resolva na tônica logo em seguida."),
        p (
            "Os exercícios deste tópico pedem que você toque o acorde de dominante e o resolva na tônica, e o app confere as notas reconhecidas. É a forma mais direta de internalizar a função: tocar a tensão e sentir a resolução acontecer na ponta dos dedos."),
        b ("O dominante fica a uma quinta acima da tônica."),
        b ("Use o V7 (com sétima) para sentir a tensão máxima."),
        b ("Resolva logo na tônica e confirme com o app."),
        img ("m5_campo_harmonico_braco", "O dominante no braço: o acorde de V, pronto para ser tocado e resolvido na tônica."),

        h ("O trítono: a mola da harmonia"),
        p (
            "O trítono é o intervalo de três tons inteiros (seis semitons), o mais instável da música ocidental. No acorde de dominante com sétima, o trítono aparece entre a terça e a sétima — em G7, entre o Si e o Fá. É esse intervalo que cria a tensão característica do dominante e que pede, com força, a resolução na tônica."),
        p (
            "A resolução do trítono é o que faz a cadência funcionar: o Si sobe meio tom para o Dó e o Fá desce meio tom para o Mi. As duas notas se afastam em direções opostas, cada uma movendo o mínimo possível. Essa condução de vozes, com movimentos de meio tom, é a razão pela qual a resolução do dominante soa tão convincente ao ouvido."),
        b ("Trítono = três tons = seis semitons, o intervalo mais instável."),
        b ("No V7, ele aparece entre a terça e a sétima do acorde."),
        b ("Na resolução, a terça sobe e a sétima desce, cada uma meio tom."),
        img ("m5_funcoes_tres", "O dominante e a sua tensão: o trítono é a mola que empurra a música para a tônica."),

        h ("Dominante e condução de vozes"),
        p (
            "A condução de vozes é a arte de mover cada nota do acorde para a nota mais próxima do acorde seguinte. No dominante → tônica, essa condução é quase automática, porque as notas do acorde de V estão a meio tom das notas do acorde de I. Por isso a resolução soa suave, mesmo sendo a passagem de maior tensão para maior repouso."),
        p (
            "Na guitarra, a condução de vozes é uma ferramenta muito útil para acompanhar sem ficar pulando de uma região a outra do braço. Se você conduz as vozes, o acorde de tônica aparece quase no mesmo lugar do acorde de dominante, com um ou dois dedos se movendo. Isso deixa o acompanhamento mais fluido e mais musical."),
        b ("Condução de vozes: mover cada nota para a mais próxima."),
        b ("No V → I, as notas se movem por meio tom."),
        b ("Na guitarra, a condução mantém o acompanhamento na mesma região."),
        aud ({ "G4", "B4", "D5", "F5", "C5", "E5", "G5" },
             "G7 resolvendo em C: o Si sobe para o Dó e o Fá desce para o Mi."),

        h ("Exercícios para ouvir o dominante"),
        p (
            "Para treinar o ouvido, toque I → V e pare. O ouvido vai ficar esperando a resolução. Depois toque I → V → I e repare no alívio. Repita o exercício várias vezes, alternando entre parar e resolver, até que a sensação de tensão do dominante fique clara. Esse é o treino mais direto para reconhecer a função dominante."),
        p (
            "Um segundo exercício é tocar apenas o acorde de dominante e tentar cantar a nota para onde ele quer ir (a tônica). Se você acertar, é sinal de que o seu ouvido já reconhece a direção da resolução. Esse reconhecimento é a base para acompanhar músicas de ouvido e para improvisar sobre a harmonia com intenção."),
        b ("Toque I → V e pare; note a expectativa do ouvido."),
        b ("Depois resolva em I e note o alívio."),
        b ("Cante a nota de resolução para treinar a direção."),
        c (
            "A função dominante é a que mais 'puxa' o ouvido. Quando você a reconhece, passa a prever a resolução antes de ela acontecer — e é essa previsão que permite acompanhar e improvisar com segurança."),

        h ("Resumo do tópico"),
        b ("Função dominante é a função de tensão da tonalidade."),
        b ("É exercida pelo grau V (e V7) e pelo substituto vii°."),
        b ("Soa instável e pede resolução na tônica."),
        b ("A força vem do trítono e dos meio tons que conduzem à tônica."),
        b ("V → I é a cadência mais forte da música tonal."),
        c (
            "Nos exercícios deste tópico, toque o dominante e o resolva na tônica. O app reconhece as notas e confere se a função de tensão está sendo executada e resolvida corretamente."),
    };
}

} // namespace cursomusica::content
