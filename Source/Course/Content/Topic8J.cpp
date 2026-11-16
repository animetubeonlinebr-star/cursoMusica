#include "Course/Content/Topics.h"

// Topic 8J — Identificação de situações que não são II-V-I (Módulo 8, Etapa 8).
// Fonte de verdade do texto: .agents/agents/mc-modulo-8.md (Etapa 8, tópico J).
namespace cursomusica::content
{

std::vector<ContentItem> topic8J()
{
    return {

        p (
            "Depois de aprender a identificar e usar o II-V-I, é preciso aprender o contrário: reconhecer quando uma progressão não é um II-V-I. Muitas sequências parecem cadências, mas resolvem em lugares inesperados ou não resolvem. Saber distinguir esses casos é o que separa o aluno que decora do músico que entende."),
        p (
            "A pergunta fundamental é sempre a mesma: qual é o alvo e como ele é alcançado? No II-V-I, o alvo é o I, e ele é alcançado por ii → V → I. Quando o alvo é outro, ou quando o caminho é diferente, não é um II-V-I — é outra coisa, com outro nome e outra função. Este tópico ensina a fazer essa distinção."),
        c (
            "Objetivo do tópico: identificar as situações que se parecem com um II-V-I, mas não são, e saber nomeá-las."),

        h ("Por que distinguir"),
        p (
            "Se você trata toda tensão como II-V-I, vai tocar errado: improvisará as notas do tom errado, fará as resoluções erradas e se perderá na forma. Identificar corretamente a progressão permite escolher as notas certas e antecipar o que vem. É a diferença entre acompanhar de ouvido e se perder no meio da música."),
        b ("Cada progressão tem um alvo específico."),
        b ("Reconhecer o alvo define as notas que servem."),
        b ("Confundir a progressão leva a tocar fora do tom."),

        h ("Cadência deceptiva"),
        p (
            "A cadência deceptiva é a mais comum das falsas cadências. O dominante aparece e cria expectativa de resolver no I, mas resolve em outro grau — normalmente o vi (em Dó, o Am). O ouvido sente a surpresa, mas não a ruptura: a música continua no mesmo tom. Em Dó, é G7 → Am em vez de G7 → C."),
        b ("Esperado: G7 → C."),
        b ("Deceptivo: G7 → Am (resolve no vi)."),
        b ("A tensão existe, mas o alvo é outro."),
        img ("m8_nao_ii_v_i", "Situações que não são II-V-I: a deceptiva, o backdoor, o vamp modal e a meia cadência."),
        aud ({ "D3", "F3", "A3", "C4", "G3", "B3", "D4", "F4", "A3", "C4", "E4", "G4" },
             "Dm7 → G7 → Am: o dominante resolve no vi, não no I (cadência deceptiva)."),

        h ("Cadência de backdoor"),
        p (
            "A cadência de backdoor (\"porta dos fundos\") usa o iv menor e o bVII para chegar ao I, sem passar pelo V. Em Dó, é Fm7 → Bb7 → CM7. A resolução soa modal e suave, sem a tensão do dominante tradicional. É um empréstimo modal transformado em cadência, muito usado no jazz e na MPB."),
        b ("Backdoor: Fm7 → Bb7 → CM7."),
        b ("O iv menor e o bVII vêm do menor paralelo."),
        b ("A resolução é modal, não funcional."),
        aud ({ "F3", "G#3", "C4", "D#4", "A#3", "D4", "F4", "G#4", "C3", "E3", "G3" },
             "Fm7 → Bb7 → C: a cadência de backdoor, suave e modal."),

        h ("Dominante sem resolução"),
        p (
            "Há casos em que o dominante aparece, mas não resolve na tônica esperada. Ele pode resolver em outro dominante (encadeamento), em um acorde de empréstimo, ou simplesmente não resolver. Quando o dominante não resolve, ele deixa de cumprir a função de fechar e passa a cumprir a função de mover. É o caso dos dominantes secundários e das cadeias."),
        b ("G7 → D7: o dominante resolve em outro dominante."),
        b ("G7 → F: o dominante não vai para o I."),
        b ("Sem resolução no I, não há cadência."),

        h ("Vamp modal"),
        p (
            "Um vamp é uma repetição de dois acordes que não fecham. O vamp modal mais famoso é Dm7 → G7, repetido indefinidamente sem nunca chegar ao C. Ele não é um II-V-I porque o I nunca aparece. A música fica suspensa, em movimento perpétuo, o que é uma característica do modal (o jazz modal usa vamps extensivamente)."),
        b ("Vamp: Dm7 → G7 → Dm7 → G7 (e repete)."),
        b ("Falta o I: a cadência nunca fecha."),
        b ("O movimento é modal, não funcional."),
        aud ({ "D3", "F3", "A3", "C4", "G3", "B3", "D4", "F4", "D3", "F3", "A3", "C4" },
             "Dm7 → G7 → Dm7: um vamp modal que nunca resolve. Ouça a suspensão."),

        h ("Meia cadência e cadência suspensa"),
        p (
            "A meia cadência para no dominante: ii → V, sem o I. Ela cria uma expectativa que não se fecha, e é usada para preparar uma nova seção. A cadência suspensa é semelhante: para no V ou no IV, deixando a frase em aberto. Reconhecer essas paradas é tão importante quanto reconhecer as chegadas."),
        b ("Meia cadência: ii → V (para no dominante)."),
        b ("Cadência suspensa: para no IV ou no V."),
        b ("A frase fica em aberto, esperando continuação."),

        h ("O II-V-I de verdade"),
        p (
            "Para contrastar, o II-V-I de verdade tem três características: o ii é um acorde subdominante, o V é um dominante, e o I é o alvo claro e estável. A resolução é forte e fecha a frase. Se qualquer uma dessas três condições falha, provavelmente não é um II-V-I. Use essa lista de verificação para distinguir os casos."),
        b ("ii: acorde subdominante (Dm7 ou Dm7b5)."),
        b ("V: acorde dominante (G7, G7b9, G7alt, Db7)."),
        b ("I: alvo estável (CM7 ou Cm7)."),
        b ("Se falta uma condição, é outra progressão."),
        tbl ({ "Progressão", "Alvo", "É II-V-I?" }, {
            { "Dm7 – G7 – CM7", "I (Dó maior)", "sim" },
            { "Dm7b5 – G7 – Cm7", "i (Dó menor)", "sim (menor)" },
            { "Dm7 – G7 – Am", "vi (Lá menor)", "não (deceptiva)" },
            { "Fm7 – Bb7 – CM7", "I (Dó maior)", "não (backdoor)" },
            { "Dm7 – G7 (repete)", "nenhum", "não (vamp)" },
            { "Dm7 – G7", "nenhum", "não (meia cadência)" },
        }),

        h ("Como identificar de ouvido"),
        p (
            "Treine ouvindo progressões e perguntando: onde a música chegou? Se ela chegou num repouso claro e esse repouso foi preparado por um ii e um V, é um II-V-I. Se ela resolveu em outro lugar, parou no meio ou nunca resolveu, é outra coisa. O ouvido aprende a distinguir pela sensação de fechamento ou de suspensão."),
        b ("Ouça e localize o repouso."),
        b ("Verifique se o repouso foi preparado por ii → V."),
        b ("Se não, nomeie a progressão pelo seu alvo."),
        aud ({ "D3", "F3", "A3", "C4", "G3", "B3", "D4", "F4", "C4", "E4", "G4", "D3", "F3", "A3", "C4" },
             "II-V-I e depois vamp: compare a sensação de fechamento e de suspensão."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é chamar de II-V-I tudo o que tem dois acordes em movimento. Um vamp Dm7 → G7 não é II-V-I, porque não resolve. Outro erro é não perceber a deceptiva: o aluno espera o I, ouve o vi e não entende o que aconteceu. Ouvir com atenção ao alvo resolve os dois casos."),
        b ("Nem toda sequência com ii e V é II-V-I."),
        b ("Sem resolução no I, não há cadência."),
        b ("Perceba quando o alvo não é o esperado."),
        c (
            "Dica: sempre pergunte \"onde a música chegou?\". A resposta define a progressão."),

        h ("Aplicação prática"),
        p (
            "Pratique identificar progressões em músicas que você conhece. Toque o II-V-I e depois toque as variações (deceptiva, backdoor, vamp) e compare as sensações. No instrumento, use o app para conferir se os acordes que você toca formam a progressão pedida — o app reconhece as notas e verifica cada acorde."),
        b ("Toque o II-V-I e depois a versão deceptiva (→ Am)."),
        b ("Toque a cadência de backdoor (Fm7 → Bb7 → C)."),
        b ("Toque um vamp (Dm7 → G7) e note a suspensão."),
        part ("m8_partitura_ii_v_i", { "D3", "F3", "A3", "C4", "G3", "B3", "D4", "F4", "C4", "E4", "G4" },
              "Partitura do II-V-I verdadeiro (Dm7 – G7 – CM7), para comparar com as falsas cadências. Ouça o que está escrito."),

        h ("Outras progressões que parecem cadências"),
        p (
            "Além da deceptiva, do backdoor e do vamp, há outras situações que enganam. A cadência plagal (IV → I) não tem dominante: é uma resolução suave, sem tensão. A cadência frígia (bVII → i, no menor) tem um som modal. A progressão IV → V → IV (sem resolver no I) mantém o movimento suspenso. Reconhecer todas essas formas é o que completa o vocabulário."),
        b ("Cadência plagal: IV → I (sem dominante)."),
        b ("Cadência frígia: bVII → i (no menor)."),
        b ("IV → V → IV: sem resolução, movimento suspenso."),
        tbl ({ "Progressão", "Alvo", "Observação" }, {
            { "IV → I", "I", "plagal, sem dominante" },
            { "bVII → i", "i", "frígia, modal" },
            { "IV → V → IV", "nenhum", "suspensa" },
        }),

        h ("Reconhecer o alvo pelo ouvido"),
        p (
            "A habilidade de reconhecer o alvo pelo ouvido é o que permite identificar corretamente qualquer progressão. Toque uma sequência e cante a nota que você sente como \"casa\". Essa nota é o alvo. Depois, verifique se ela foi preparada por um ii e um V. Se não foi, a progressão é outra — e você a nomeia pelo alvo e pelo caminho."),
        b ("Ouça a progressão até o fim."),
        b ("Cante a nota que soa como repouso: é o alvo."),
        b ("Verifique o caminho: ii → V → I ou outra coisa?"),
        aud ({ "D3", "F3", "A3", "C4", "G3", "B3", "D4", "F4", "A3", "C4", "E4", "G4" },
             "Dm7 → G7 → Am7: ouça como o alvo é o Lá menor, não o Dó (deceptiva)."),

        h ("Por que o II-V-I é tão comum"),
        p (
            "O II-V-I é comum porque combina três coisas essenciais: preparação, tensão e resolução. Nenhuma outra progressão reúne as três funções de forma tão clara. Por isso ela aparece em quase toda música tonal. Quando você a encontra, sabe que uma frase está fechando; quando não a encontra, sabe que a música está fazendo outra coisa — e aí está o interesse."),
        b ("Reúne as três funções: ii, V e I."),
        b ("É a cadência mais forte da música tonal."),
        b ("A ausência dela é tão informativa quanto a presença."),

        h ("Nomenclatura das progressões"),
        p (
            "Nomear corretamente uma progressão é parte do estudo. O II-V-I tem nome próprio; as outras têm os seus. Chamar um vamp de II-V-I é um erro de nomenclatura que leva a erros de improvisação. Use a tabela abaixo como referência rápida para nomear o que você ouve, e pratique nomear progressões de músicas que você conhece."),
        b ("II-V-I: ii → V → I (fecha)."),
        b ("Cadência deceptiva: V → vi (surpreende)."),
        b ("Cadência de backdoor: ivm → bVII → I."),
        b ("Vamp modal: dois acordes em repetição, sem resolver."),
        b ("Meia cadência: ii → V (para no dominante)."),
        c (
            "Nomear é entender. Quando você dá nome ao que ouve, deixa de tocar no escuro."),

        h ("Erros de identificação mais frequentes"),
        p (
            "Os erros de identificação têm um padrão. O mais comum é confundir a cadência deceptiva com um II-V-I que resolveu errado: o aluno ouve o dominante, espera o I e se perde quando chega o vi. O segundo é confundir um vamp com uma cadência: o aluno acha que a música vai resolver e ela continua repetindo. Saber que esses casos existem evita a confusão."),
        b ("Deceptiva: o alvo é outro, mas a tensão é a mesma."),
        b ("Vamp: não há resolução, só repetição."),
        b ("Backdoor: resolve sem passar pelo V."),
        c (
            "Treine identificar esses três casos separadamente. Depois, misture-os e teste o ouvido. A prática leva à segurança."),

        h ("Resumo do tópico"),
        b ("Nem toda progressão com ii e V é um II-V-I."),
        b ("Cadência deceptiva resolve no vi, não no I."),
        b ("Cadência de backdoor usa iv menor e bVII, sem o V."),
        b ("Vamp modal nunca resolve; meia cadência para no V."),
        b ("A pergunta-chave é: qual é o alvo e como ele é alcançado?"),
        c (
            "Nos exercícios deste tópico, identifique as progressões e toque os acordes no instrumento. O app reconhece as notas e confere cada acorde, inclusive nas cadências que não são II-V-I."),
    };
}

} // namespace cursomusica::content
