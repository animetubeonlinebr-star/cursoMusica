#include "Course/Content/Topics.h"

// Topic 10G — Reharmonização (Módulo 10, Etapa 10).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 10). Reharmonizar = trocar a
// harmonia mantendo a melodia.
namespace cursomusica::content
{

std::vector<ContentItem> topic10G()
{
    return {

        p (
            "Reharmonizar é trocar os acordes de uma música sem trocar a melodia. Você mantém a linha que o ouvinte reconhece e muda a harmonia que a sustenta — e a mesma melodia passa a soar diferente. É o recurso mais criativo da harmonia: com ele, você não é mais escravo da cifra original; você escolhe o caminho que a música vai seguir. Reharmonizar é, no fundo, analisar uma música e depois reescrevê-la com a sua assinatura."),
        p (
            "Este tópico é a aplicação de tudo o que veio antes. A análise harmônica diz a função de cada acorde; a análise melódica diz quais notas são fortes; a escolha modal dá a cor; a verticalização constrói acordes a partir da melodia; a conexão entre campos mostra como trocar de centro; e a condução de vozes faz tudo soar bem. Reharmonizar é juntar todas essas ferramentas e mudar a harmonia com critério."),
        c (
            "Regra de ouro: reharmonize sempre em função da melodia. As notas fortes da melodia precisam continuar sendo notas do novo acorde. Se a melodia insiste numa nota, a nova harmonia tem de contê-la."),

        h ("O que pode e o que não pode mudar"),
        p (
            "Reharmonizar tem limites, e os limites são dados pela melodia. As notas fortes (as que caem no tempo forte e as que são sustentadas) precisam pertencer ao novo acorde; as notas de passagem são mais livres. Um acorde novo que 'abriga' todas as notas fortes da melodia é sempre uma opção válida; um acorde que entra em choque com uma nota forte não é. Antes de reharmonizar, marque na partitura quais notas são fortes — elas são as restrições do seu trabalho."),
        b ("Notas fortes da melodia: o novo acorde precisa contê-las."),
        b ("Notas de passagem: maior liberdade para a nova harmonia."),
        b ("Nunca deixe uma nota forte da melodia em choque com o novo acorde."),
        img ("m10_reharmonizacao", "Reharmonizar: para cada acorde original existem caminhos — substituto, empréstimo modal, dominante extra."),

        h ("Substituição: trocar um acorde por outro equivalente"),
        p (
            "A forma mais simples de reharmonizar é a substituição: trocar um acorde por outro que exerça a mesma função. Um G7 pode virar um Db7 (substituição de trítono), porque os dois têm o mesmo trítono e resolvem para o mesmo acorde. Um Dm7 pode virar um F7M (relativo), porque compartilham quase todas as notas. Substituir mantém a função e muda a cor — a música continua no caminho, mas soa nova."),
        tbl ({ "Original", "Substituto", "Por que funciona" }, {
            { "G7", "Db7", "mesmo trítono (B e F), resolve para C" },
            { "Dm7", "F7M", "notas em comum (F, A, C)" },
            { "C7M", "Am7", "relativo menor, mesma família" },
            { "G7", "Bb7", "subV por outro caminho (trítono)" },
        }),
        c (
            "A substituição de trítono é a mais famosa: o dominante que está a um trítono de distância do V tem o mesmo trítono interno e pode tomar o seu lugar. G7 e Db7 resolvem ambos para C."),
        aud ({ "G3", "B3", "D4", "F4", "C#4", "F4", "G#4", "B4" },
             "G7 e Db7 em sequência: os dois resolvem para C. Ouça como o baixo desce de cromatismo."),
        aud ({ "D4", "F4", "A4", "C5", "F3", "A3", "C4", "E4" },
             "Dm7 e F7M: o substituto mantém F, A e C. Ouça a cor mudar sem mudar o caminho."),

        h ("Empréstimo modal e acordes de passagem"),
        p (
            "Outra forma de reharmonizar é emprestar acordes do campo menor paralelo. Onde havia um C7M, você pode tocar um Cm7 ou um Fm7 — a tonalidade continua a mesma, mas a cor escurece. Também vale inserir acordes de passagem: onde havia um salto de C7M direto para Dm7, você coloca um Bm7b5 entre os dois, criando movimento por graus. Essas técnicas não mudam o centro; elas enriquecem a harmonia mantendo a melodia intacta."),
        tbl ({ "Onde havia", "Você pode tocar", "Técnica" }, {
            { "C7M", "Cm7 / Cm6", "empréstimo modal (i do menor paralelo)" },
            { "F7M", "Fm7", "empréstimo modal (iv do menor paralelo)" },
            { "C7M → Dm7", "C7M → Bm7b5 → Dm7", "acorde de passagem" },
            { "Dm7 → G7", "Dm7 → Ab7 → G7", "dominante de aproximação" },
        }),
        b ("Empréstimo modal escurece a harmonia sem mudar o centro."),
        b ("Acordes de passagem preenchem os saltos com movimento por graus."),
        b ("Dominantes de aproximação preparam o acorde seguinte de perto."),
        aud ({ "C4", "D#4", "G4", "A#4" }, "Cm7 no lugar do C7M: a cor escurece, a tonalidade continua a mesma."),

        h ("Reharmonização por reescala"),
        p (
            "Uma técnica mais avançada é a reharmonização por reescala: você mantém a melodia e troca a escala que a sustenta, o que muda todos os acordes de uma vez. Se a melodia se adapta a uma nova escala, toda a harmonia pode ser reconstruída a partir dela. É o que Chick Corea faz em trechos de Spain e de 500 Miles High: a mesma melodia reaparece sobre áreas tonais diferentes. Essa técnica exige que você conheça bem a melodia e as escalas — é a reharmonização levada ao limite."),
        b ("Mantenha a melodia e troque a escala que a sustenta."),
        b ("Reconstrua todos os acordes a partir da nova escala."),
        b ("Confira se todas as notas fortes da melodia cabem na nova escala."),
        part ("m10_partitura_reharmonizado", { "C4", "E4", "G4", "A4", "D5", "F5", "G5", "C5" },
              "Partitura de uma melodia reharmonizada: a linha continua reconhecível, a harmonia chegou a um novo lugar."),

        h ("Aplicando ao repertório curado"),
        p (
            "Pegue uma música do repertório do curso e reharmonize um trecho. Em Só Danço Samba, o II7 (D7) que já existe é um exemplo de reharmonização que o próprio compositor fez: onde se esperava um Dm7, ele colocou um D7, e essa é a 'luz' da bossa. Em Incompatibilidade de Gênios, os acordes de passagem com baixo pedalizado são reharmonizações que o compositor usou para dar o 'molho' do samba. Reharmonizar é fazer, com critério, o que os grandes compositores fizeram por intuição."),
        b ("Só Danço Samba: o D7 no lugar do Dm7 é uma reharmonização (dominante secundário)."),
        b ("Incompatibilidade de Gênios: acordes de passagem com baixo pedalizado."),
        b ("Estude reharmonizações existentes para construir seu vocabulário."),
        aud ({ "D4", "F4", "A4", "C5", "D4", "F#4", "A4", "C5" },
             "Dm7 e D7: a reharmonização que o Jobim usou em Só Danço Samba. Ouça a diferença."),

        h ("Como praticar a reharmonização"),
        p (
            "Pratique em progressões curtas. Pegue um ii–V–I e reharmonize-o de várias formas: substitua o dominante por um subV, insira um dominante secundário, empreste um acorde do menor paralelo, adicione um acorde de passagem. Tocar a melodia por cima de cada versão e ouvir qual funciona é o treino. O app ajuda: ele reconhece os acordes que você toca e confere a progressão reharmonizada, então você pode testar suas versões com verificação. Reharmonizar é um exercício de ouvido tanto quanto de teoria."),
        b ("Reharmonize o mesmo ii–V–I de várias maneiras."),
        b ("Toque a melodia por cima de cada versão e escute."),
        b ("Confira com o app e escolha a versão que soa melhor."),
        c (
            "Erro comum: reharmonizar sem olhar a melodia. Uma troca de acorde 'teoricamente correta' que entra em choque com uma nota forte da melodia soa errada. A melodia é a lei."),

        h ("Erros comuns na reharmonização"),
        p (
            "O erro mais comum é mudar o acorde sem verificar a melodia, criando atritos. O segundo é reharmonizar demais: uma música em que todo acorde foi trocado perde a identidade. O terceiro é ignorar a função — trocar um dominante por um acorde que não resolve para o lugar certo quebra a música. Reharmonizar bem é trocar com parcimônia, respeitando a função e a melodia. Às vezes, uma única troca bem colocada vale mais do que dez trocas aleatórias."),
        b ("Verifique sempre a melodia antes de trocar o acorde."),
        b ("Reharmonize com parcimônia: mantenha a identidade da música."),
        b ("Respeite a função: o novo acorde precisa levar a música ao mesmo lugar."),
        img ("m10_harmonia_alvo", "Reharmonizar bem é trabalhar em direção ao alvo da frase. O tópico H mostra como definir esse alvo."),

        h ("Reharmonização e tensão: as cores da troca"),
        p (
            "Uma reharmonização muda não só os acordes, mas as tensões disponíveis. Trocar um C7M por um Cm7 muda a terça (de maior para menor) e escurece; trocar um G7 por um G7alt aumenta as tensões disponíveis. É por isso que a reharmonização está ligada à escolha modal (tópico C): cada acorde novo traz um conjunto novo de notas de cor. Reharmonizar com consciência é escolher a cor, não apenas o acorde — a melodia e o improviso vão se ajustar ao novo campo de tensões."),
        tbl ({ "Troca", "Muda", "Cor resultante" }, {
            { "C7M → C7", "a sétima (maior → menor)", "dominante, tenso" },
            { "C7M → Cm7", "a terça (maior → menor)", "menor, escuro" },
            { "G7 → G7alt", "as tensões disponíveis", "dominante moderno" },
            { "Dm7 → Dm7(9)", "acrescenta a nona", "menor rico" },
        }),
        b ("Cada acorde novo traz um novo conjunto de tensões."),
        b ("Reharmonizar é escolher a cor, não só o acorde."),
        b ("A escolha modal (tópico C) define as tensões da nova harmonia."),
        aud ({ "C4", "E4", "G4", "A#4" }, "C7 no lugar do C7M: a sétima menor muda a cor para dominante."),

        h ("Reharmonização e ritmo harmônico"),
        p (
            "Reharmonizar também pode mudar o ritmo harmônico — a frequência com que os acordes mudam. Uma música que muda de acorde a cada compasso pode ser reharmonizada para mudar a cada dois compassos (menos movimento) ou a cada meio compasso (mais movimento). Às vezes, a reharmonização mais eficaz não é trocar os acordes, mas mudar a velocidade com que eles passam. Esse recurso é muito usado em arranjos de bossa e de jazz: manter a harmonia e desacelerar ou acelerar a troca de acordes muda completamente a sensação."),
        b ("Ritmo harmônico: a frequência das trocas de acorde."),
        b ("Menos movimento (acorde por mais tempo) = mais calma."),
        b ("Mais movimento (trocas rápidas) = mais tensão e densidade."),
        aud ({ "C4", "E4", "G4", "B4", "D4", "F4", "A4", "C5" },
             "Ritmo harmônico lento: dois acordes em tempos largos. Ouça a calma."),

        h ("Reharmonização no repertório: exemplos práticos"),
        p (
            "Vamos ver como as ferramentas aparecem em músicas reais do repertório curado. Em Só Danço Samba, o D7 onde se esperava um Dm7 é um dominante secundário — a 'luz' da bossa. Em Incompatibilidade de Gênios, os acordes de passagem com baixo pedalizado (C7M(#11), Bm7b5/A) são reharmonizações que dão o 'molho' do samba. Em Equinox, o Ab9 do nono compasso é um substituto do IV que coloca o D da melodia como trítono. Cada um desses casos é uma ferramenta do catálogo aplicada com maestria — e estudá-los é aprender a reharmonizar com ouvido."),
        b ("Só Danço Samba: D7 no lugar de Dm7 (dominante secundário)."),
        b ("Incompatibilidade de Gênios: acordes de passagem com baixo pedalizado."),
        b ("Equinox: Ab9 como substituto do IV (coloca o D como trítono)."),
        aud ({ "A3", "C4", "D#4", "F#4" }, "Um acorde substituto: ouça a cor que ele traz à progressão."),

        h ("Erros comuns na reharmonização: revisão"),
        p (
            "Vale reforçar os erros mais frequentes, porque eles são a causa da maioria das reharmonizações que não funcionam. Reharmonizar sem analisar (trocar acordes sem saber a função), reharmonizar sem olhar a melodia (criar atritos), reharmonizar demais (perder a identidade) e reharmonizar sem conduzir as vozes (a progressão soa dura). Cada um desses erros tem uma correção: analise primeiro, verifique a melodia, use poucas trocas e cuide da condução. A reharmonização é uma habilidade que se aprende corrigindo esses erros um a um."),
        b ("Analise antes de reharmonizar: saiba a função de cada acorde."),
        b ("Verifique a melodia: as notas fortes precisam caber."),
        b ("Use poucas trocas: mantenha a identidade."),
        b ("Cuide da condução de vozes: a progressão precisa fluir."),

        h ("Resumo do tópico"),
        b ("Reharmonizar é trocar a harmonia mantendo a melodia."),
        b ("A melodia manda: as notas fortes precisam caber nos novos acordes."),
        b ("Substituição (trítono, relativo), empréstimo modal e acordes de passagem são as técnicas básicas."),
        b ("Reescalar troca a escala e reconstrói a harmonia inteira."),
        b ("Reharmonize com parcimônia, respeitando a função e a melodia."),
        c (
            "Objetivo do tópico: ganhar liberdade sobre a harmonia sem perder a música. Reharmonizar é escolher um caminho novo para a mesma melodia — com critério, não por acaso."),
    };
}

} // namespace cursomusica::content
