#include "Course/Content/Topics.h"

// Topic 2D — Percepção de intervalos (Módulo 2, Etapa 2).
// Fonte de verdade do texto: docs/MUSIC.md §2.2 (bloco D).
namespace cursomusica::content
{

std::vector<ContentItem> topic2D()
{
    return {

        p (
            "Saber contar semitons é o lado racional do intervalo. Perceber o intervalo pelo ouvido é o lado musical. Este tópico treina a escuta: reconhecer a distância entre duas notas sem olhar o braço. É a habilidade que permite tocar de memória, tirar música de ouvido e improvisar com intenção."),
        p (
            "A percepção se constrói por referência. Você aprende a ouvir um intervalo associando-o a algo que já conhece — uma música, um som familiar. Com repetição, a associação deixa de ser consciente e o ouvido reconhece direto."),

        h ("Intervalos estáveis e instáveis"),
        p (
            "O ouvido classifica os intervalos em dois grandes grupos. Os consonantes soam estáveis, repousados; os dissonantes soam tensos, pedindo resolução. Essa classificação não é uma regra arbitrária: vem da própria física das ondas sonoras."),
        b ("Consonantes: uníssono, oitava, quinta, quarta, terças e sextas."),
        b ("Dissonantes: segundas, sétimas e o trítono."),
        b ("Tensão e repouso alternam para criar movimento musical."),
        aud ({ "C4", "G4" }, "Consonante: quinta justa, som estável e repousado."),
        aud ({ "C4", "D4" }, "Dissonante: segunda maior, som tenso, pede continuação."),

        h ("Referências para reconhecer cada intervalo"),
        p (
            "A forma mais rápida de treinar o ouvido é associar cada intervalo a um trecho conhecido. Não é preciso decorar tabelas: basta ter uma música que começa com aquele salto. Abaixo, exemplos clássicos de cada intervalo — ouça e memorize a sensação inicial."),
        tbl ({ "Intervalo", "Semitons", "Referência (exemplo)", "Sensação" }, {
            { "segunda maior", "2", "primeiros passos de uma escala maior", "passo, movimento" },
            { "terça maior", "4", "início de uma melodia alegre", "aberto, claro" },
            { "terça menor", "3", "início de uma melodia triste", "fechado, melancólico" },
            { "quarta justa", "5", "toque de chamada (fanfarra)", "firme, anunciador" },
            { "quinta justa", "7", "tema de abertura de filme épico", "vazio, grandioso" },
            { "sexta maior", "9", "frase lírica ascendente", "doce, expansivo" },
            { "sétima maior", "11", "acorde de sétima maior", "brilhante, suspenso" },
            { "oitava", "12", "mesma nota mais aguda", "idêntico, mais alto" },
        }),
        c (
            "O app demonstra cada linha da tabela com o botão de ouvir. Aprender o intervalo é ouvir a referência até a sensação ficar automática."),

        h ("Reconhecendo pelo nome"),
        p (
            "Depois de memorizar a referência, o próximo passo é nomear o intervalo que se ouve. Um bom método é sempre cantar a partir da mesma nota de referência e comparar com o intervalo que está soando. Com o tempo, a comparação se torna instantânea."),
        b ("Toque uma nota fixa (por exemplo, a 5ª corda solta) e cante cada intervalo acima dela."),
        b ("Ouça um intervalo e diga primeiro se sobe ou desce, depois se é grande ou pequeno."),
        b ("Classifique por grupo: estável ou instável, estreito ou largo."),
        img ("m2_percepcao_referencias", "Cada intervalo tem uma referência sonora; associar é memorizar."),

        h ("Direção e tamanho"),
        p (
            "Antes de nomear, o ouvido percebe duas coisas: a direção (sobe ou desce) e o tamanho (perto ou longe). Treinar essas duas percepções separadamente torna o reconhecimento mais fácil, porque reduz o número de hipóteses a cada passo."),
        b ("Direção: a segunda nota está acima ou abaixo da primeira?"),
        b ("Tamanho: a distância é pequena (2ª, 3ª) ou grande (6ª, 7ª, oitava)?"),
        b ("Qualidade: depois de decidir direção e tamanho, resta pouca dúvida."),
        aud ({ "C4", "G4", "C4", "F4" }, "Compare uma quinta (sobe) e uma quarta (sobe): distâncias diferentes, mesma direção."),

        h ("Do ouvido para o instrumento"),
        p (
            "Perceber o intervalo é metade do caminho; a outra metade é reproduzi-lo no braço. Quando você ouve uma terça maior e sabe tocá-la a partir de qualquer nota, você consegue acompanhar uma música de ouvido. Este tópico fecha o ciclo: ouvir, nomear, tocar."),
        b ("Ouça o intervalo demonstrado pelo app."),
        b ("Nomeie-o antes de olhar o braço."),
        b ("Toque-o no instrumento e confira com a nota de partida."),
        c (
            "Nos exercícios deste tópico, parte é respondida de ouvido (o app toca e você nomeia) e parte é tocada (você toca e o app confere). As duas formas treinam o mesmo conhecimento por caminhos diferentes."),


        h ("Treinando o ouvido por comparação"),
        p (
            "O ouvido aprende por comparação, não por memorização isolada. Em vez de tentar decorar cada intervalo do zero, compare pares: terça maior contra terça menor, quarta justa contra quinta justa, sexta maior contra sétima maior. Ao ouvir os dois lado a lado, a diferença fica evidente e você passa a reconhecer cada um pela oposição ao outro."),
        b ("Ouça terça maior, depois terça menor: a segunda soa mais fechada."),
        b ("Ouça quarta justa, depois quinta justa: a segunda soa mais 'vazia'."),
        b ("Ouça sexta maior, depois sétima maior: a segunda soa mais tensa."),
        aud ({ "C4", "E4", "C4", "D#4" }, "Terça maior e terça menor, uma após a outra, para comparar."),

        h ("Intervalos ascendentes e descendentes"),
        p (
            "Um mesmo intervalo pode ser ouvido subindo ou descendo. O ouvido tende a reconhecer mais facilmente os intervalos ascendentes, porque as referências musicais que memorizamos costumam subir. Treinar também os descendentes é essencial para tirar melodias de ouvido, que raramente sobem sempre."),
        b ("Ascendente: da nota grave para a aguda."),
        b ("Descendente: da aguda para a grave."),
        b ("O nome do intervalo é o mesmo; muda a direção da execução."),
        aud ({ "G4", "C4" }, "Quinta descendente (Sol até Dó): mesmo intervalo, direção oposta."),

        h ("Percepção e contexto harmônico"),
        p (
            "O mesmo intervalo pode soar diferente conforme o contexto. Uma terça maior isolada soa aberta; dentro de um acorde, ela pode soar repousada ou tensa conforme a função do acorde. O ouvido treinado percebe não só a distância, mas também a relação com o centro tonal. Isso é o que permite reconhecer uma música inteira de ouvido."),
        b ("O contexto (o acorde, a tonalidade) muda a sensação do intervalo."),
        b ("Reconhecer o intervalo isolado é o primeiro passo; reconhecê-lo no contexto é o segundo."),
        aud ({ "C4", "E4", "G4" }, "A terça maior dentro do acorde de Dó maior: soa estável porque pertence à harmonia."),

        h ("O método dos três passos"),
        p (
            "Para reconhecer um intervalo de ouvido, siga sempre a mesma ordem: primeiro a direção (sobe ou desce), depois o tamanho (pequeno, médio ou grande) e por fim a qualidade (maior, menor ou justa). Reduzir o problema em etapas evita o erro comum de tentar adivinhar o nome de uma vez."),
        tbl ({ "Passo", "Pergunta", "Resultado" }, {
            { "1", "Sobe ou desce?", "direção" },
            { "2", "Perto ou longe?", "tamanho aproximado" },
            { "3", "Maior, menor ou justa?", "qualidade" },
        }),
        c (
            "Com prática, os três passos se tornam um só. No começo, porém, separá-los é o que garante acerto consistente."),

        h ("Percepção é treinável"),
        p (
            "Ninguém nasce reconhecendo intervalos: é uma habilidade que se constrói com repetição. Cinco minutos por dia, comparando dois intervalos, produzem mais resultado do que uma hora esporádica. O app ajuda porque toca os exemplos com precisão e permite repetir quantas vezes quiser."),
        b ("Treine pouco e sempre, em vez de muito e raramente."),
        b ("Comece com poucos intervalos e só acrescente quando acertar com segurança."),
        b ("Use as referências musicais para fixar a sensação de cada intervalo."),


        h ("Intervalos e emoção"),
        p (
            "Os intervalos têm uma carga emocional que a música explora de forma sistemática. A terça maior é associada a alegria; a terça menor, à tristeza; a quinta justa, a algo grandioso; o trítono, ao suspense. Conhecer essas associações ajuda a compor, a improvisar e a entender por que certas músicas nos tocam."),
        b ("Terça maior: alegria, clareza."),
        b ("Terça menor: tristeza, introspecção."),
        b ("Quinta justa: grandeza, estabilidade."),
        b ("Trítono: suspense, instabilidade."),
        aud ({ "C4", "E4" }, "Terça maior: sensação de alegria."),
        aud ({ "C4", "D#4" }, "Terça menor: sensação de tristeza."),

        h ("Memorizando por músicas conhecidas"),
        p (
            "A forma mais eficiente de memorizar intervalos é associá-los a músicas que começam com aquele salto. Como a memória musical é forte, a referência fica disponível imediatamente. Escolha uma música para cada intervalo e use-a como atalho mental durante o treino."),
        tbl ({ "Intervalo", "Tipo de referência", "Sensação" }, {
            { "segunda maior", "primeiros passos de uma escala", "movimento" },
            { "terça maior", "início de melodia alegre", "aberto" },
            { "terça menor", "início de melodia triste", "fechado" },
            { "quarta justa", "toque de chamada", "firme" },
            { "quinta justa", "tema grandioso", "vazio" },
            { "sexta maior", "frase lírica", "doce" },
            { "sétima maior", "acorde de sétima maior", "brilhante" },
            { "oitava", "mesma nota mais aguda", "idêntico" },
        }),

        h ("Praticando com o app"),
        p (
            "O app oferece os exemplos sonoros de cada intervalo, o que torna o treino prático e repetível. Ouça o exemplo, tente nomear o intervalo antes de olhar a resposta e repita até acertar com consistência. Combine esse treino com o exercício de tocar o intervalo no instrumento: assim, ouvido e mão se desenvolvem juntos."),
        b ("Ouça o exemplo e nomeie o intervalo."),
        b ("Confira a resposta e repita se errar."),
        b ("Toque o mesmo intervalo no instrumento para fixar."),
        c (
            "Percepção e execução se reforçam: ouvir bem ajuda a tocar bem, e tocar bem confirma o que o ouvido percebeu."),


        h ("Construindo um treino consistente"),
        p (
            "Um treino de percepção eficaz tem uma estrutura simples: escolha poucos intervalos, ouça cada um várias vezes, compare com os outros e só acrescente novos quando os atuais estiverem firmes. O app permite repetir os exemplos quantas vezes quiser, o que torna esse treino fácil de fazer todos os dias."),
        b ("Escolha dois intervalos contrastantes para começar."),
        b ("Compare-os até reconhecer cada um sem hesitar."),
        b ("Acrescente um terceiro intervalo só depois de dominar os dois primeiros."),
        aud ({ "C4", "G4", "C4", "E4" }, "Compare a quinta e a terça: distâncias diferentes, sensações diferentes."),

        h ("Percepção e leitura"),
        p (
            "A percepção dos intervalos também ajuda na leitura. Ao ler uma partitura, reconhecer o intervalo escrito permite antecipar o som antes de tocar. Ler e ouvir se reforçam: quanto melhor você ouve, mais fácil ler; quanto mais lê, mais reconhece os intervalos de ouvido."),
        b ("Leia o intervalo na partitura e cante-o antes de tocar."),
        b ("Compare o que cantou com o som do instrumento."),
        b ("Repita até a leitura virar audição automática."),

        h ("Resumo do tópico"),
        b ("Percepção é reconhecer a distância pelo ouvido, sem olhar o braço."),
        b ("Consonantes soam estáveis; dissonantes soam tensos."),
        b ("Cada intervalo tem uma referência sonora que ajuda a memorizar."),
        b ("Reconheça em três passos: direção, tamanho, qualidade."),
        b ("Ouvir, nomear e tocar fecham o aprendizado do intervalo."),
        aud ({ "C4", "A4" }, "Sexta maior: associe a uma frase lírica que sobe. Estável e expansiva."),
    };
}

} // namespace cursomusica::content
