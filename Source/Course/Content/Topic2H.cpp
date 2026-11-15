#include "Course/Content/Topics.h"

// Topic 2H — Identificar intervalos no instrumento e de ouvido.
// Fonte de verdade do texto: docs/MUSIC.md §2.2 (bloco H).
namespace cursomusica::content
{

std::vector<ContentItem> topic2H()
{
    return {

        p (
            "Este é o tópico de fechamento do módulo: identificar intervalos pelos dois caminhos — pelo instrumento e pelo ouvido. Aqui você junta tudo o que aprendeu: o quadro móvel, as qualidades, a percepção e a construção de acordes. O objetivo é reconhecer um intervalo e saber, na hora, onde ele está no braço e como ele soa."),
        p (
            "Identificar um intervalo significa responder três perguntas ao mesmo tempo: qual é o número, qual é a qualidade e como ele soa. O app verifica a primeira e a segunda quando você toca; a terceira é o treino de ouvido, feito com os exemplos sonoros."),

        h ("Identificar pelo instrumento"),
        p (
            "No braço, identificar um intervalo é medir a distância em semitons entre duas notas. Como o app reconhece as notas que você toca, ele confere se a distância corresponde ao intervalo pedido, sem se importar com a posição. Você pode tocar o intervalo em qualquer região."),
        b ("Escolha uma nota de partida."),
        b ("Toque a segunda nota na distância correta."),
        b ("O app mede os semitons e valida o intervalo."),
        c (
            "É por isso que o módulo insiste em tocar os intervalos: o reconhecimento pelo instrumento transforma a teoria em prática verificável."),

        h ("Identificar de ouvido"),
        p (
            "O treino de ouvido segue a mesma lógica, mas sem o instrumento. O app toca um intervalo e você o nomeia. Comece com poucos intervalos por vez e só acrescente novos quando os primeiros ficarem automáticos. Reconhecer cinco intervalos com segurança vale mais do que reconhecer doze com dúvida."),
        b ("Ouça o intervalo demonstrado."),
        b ("Decida direção, tamanho e qualidade, nessa ordem."),
        b ("Confira a resposta e repita até acertar com consistência."),
        aud ({ "C4", "E4" }, "Que intervalo é este? Ouça antes de olhar a resposta: terça maior."),
        aud ({ "C4", "G4" }, "E este? Ouça e nomeie: quinta justa."),

        h ("O quadro de identificação rápida"),
        p (
            "Com o tempo, você cria atalhos mentais. Alguns intervalos se reconhecem pela sensação: a oitava parece a mesma nota; a quinta parece vazia; a terça maior parece alegre. Use a tabela abaixo como consulta rápida até os atalhos se fixarem."),
        tbl ({ "Se o som...", "Provavelmente é...", "Semitons" }, {
            { "parece a mesma nota, mais aguda", "oitava", "12" },
            { "soa vazio e grandioso", "quinta justa", "7" },
            { "soa firme, de chamada", "quarta justa", "5" },
            { "soa alegre e aberto", "terça maior", "4" },
            { "soa triste e fechado", "terça menor", "3" },
            { "soa tenso, quase desafinado", "trítono", "6" },
            { "soa brilhante e suspenso", "sétima maior", "11" },
            { "pede resolução, som de blues", "sétima menor", "10" },
        }),

        h ("Erros comuns e como evitá-los"),
        p (
            "Quem está começando confunde alguns pares de intervalos. Saber onde estão as armadilhas acelera o aprendizado. A maioria dos erros vem de não distinguir direção e tamanho antes de tentar a qualidade."),
        b ("Confundir terça maior com quarta justa: 4 contra 5 semitons. Conte sempre."),
        b ("Confundir quinta com quarta: uma sobe cinco letras, a outra quatro."),
        b ("Confundir sétima maior com oitava: 11 contra 12 semitons."),
        b ("Esquecer a direção: a mesma distância sobe ou desce, e isso muda o nome do intervalo em relação à tônica."),
        c (
            "Dica prática: cante a nota de referência antes de responder. Ter a tônica na memória reduz muito a confusão."),

        h ("Fechando o módulo"),
        p (
            "Ao dominar este tópico, você conclui a Etapa 2. Você entende a distância entre as notas, sabe nomear os intervalos, reconhece-os pelo ouvido e os toca no instrumento. Esse conjunto é a base para tudo o que vem depois: escalas, campos harmônicos e improvisação usam intervalos o tempo todo."),
        b ("Identifique intervalos no instrumento e o app confere a distância."),
        b ("Identifique intervalos de ouvido com os exemplos sonoros."),
        b ("Use os atalhos de sensação para reconhecer mais rápido."),
        img ("m2_mapa_intervalos", "Mapa final: os intervalos no braço, prontos para reconhecer e tocar."),


        h ("Um roteiro para identificar qualquer intervalo"),
        p (
            "Identificar intervalos com segurança depende de um método, não de sorte. O roteiro é sempre o mesmo: determine a direção, estime o tamanho, conte os semitons e confirme a qualidade. Seguindo os passos na ordem, você reduz o número de hipóteses a cada etapa e acerta com consistência."),
        tbl ({ "Etapa", "O que fazer", "Como confirmar" }, {
            { "1. Direção", "Veja se a segunda nota sobe ou desce", "escala ascendente/descendente" },
            { "2. Tamanho", "Estime se é perto (2ª, 3ª) ou longe (6ª, 7ª, 8ª)", "comparação com referências" },
            { "3. Semitons", "Conte as casas na mesma corda", "régua de semitons" },
            { "4. Qualidade", "Decida maior, menor ou justa", "tabela do quadro móvel" },
        }),

        h ("Identificar no instrumento: o papel do reconhecimento"),
        p (
            "Quando você toca, o app reconhece as notas e mede a distância entre elas. Isso significa que a verificação é objetiva: não importa a região do braço nem a corda usada, apenas o intervalo produzido. Esse retorno imediato é o que permite corrigir e consolidar a habilidade."),
        b ("Toque a nota de partida e a segunda nota."),
        b ("O app mede os semitons entre as notas reconhecidas."),
        b ("Se a distância corresponde ao intervalo pedido, o exercício conta como acerto."),
        aud ({ "C4", "E4" }, "O app ouve Dó e Mi e reconhece uma terça maior (4 semitons)."),

        h ("Identificar de ouvido: treino progressivo"),
        p (
            "O treino de ouvido deve ser progressivo. Comece com dois intervalos contrastantes (terça maior e quinta justa), acrescente um terceiro quando acertar com segurança, e assim por diante. Tentar reconhecer doze intervalos de uma vez é o caminho mais rápido para a frustração."),
        b ("Semana 1: terça maior contra quinta justa."),
        b ("Semana 2: acrescente a oitava e o trítono."),
        b ("Semana 3: acrescente as terças menor, sextas e sétimas."),
        c (
            "Reconhecer cinco intervalos com segurança vale mais do que reconhecer doze com dúvida. A base sólida permite avançar rápido depois."),

        h ("Integrando instrumento e ouvido"),
        p (
            "O objetivo final é unir as duas habilidades: ouvir um intervalo e saber imediatamente onde ele está no braço. Esse é o ponto em que a teoria, a percepção e a técnica se encontram, e é o que permite tocar de ouvido, acompanhar músicas e improvisar com intenção."),
        b ("Ouça o intervalo e nomeie-o."),
        b ("Localize-o no braço a partir de qualquer nota."),
        b ("Toque-o e confirme com o app."),
        img ("m2_mapa_intervalos", "O mapa final: os intervalos no braço, prontos para reconhecer e tocar."),

        h ("Fechando a Etapa 2"),
        p (
            "Com este tópico, você conclui o módulo de intervalos e percepção musical. Você entende a distância entre as notas, nomeia os intervalos, reconhece-os pelo ouvido e os toca no instrumento. Esse conjunto é a base para os próximos módulos, que tratam de ritmo, acordes e harmonia."),
        b ("Identifique intervalos no instrumento; o app confere a distância."),
        b ("Identifique intervalos de ouvido com os exemplos sonoros."),
        b ("Use os atalhos de sensação para reconhecer mais rápido."),
        b ("Una as duas habilidades: ouvir, nomear e tocar."),
        part ("m2_partitura_arpejo", { "C4", "E4", "G4", "C5", "G4", "E4", "C4" },
              "Arpejo de Dó maior: os intervalos da tríade em sequência. Ouça e identifique cada salto."),


        h ("Atalhos de sensação por intervalo"),
        p (
            "Com a prática, você cria atalhos mentais que dispensam a contagem. A oitava parece a mesma nota, mais aguda; a quinta parece vazia; a terça maior parece alegre; o trítono parece tenso. Esses atalhos são pessoais: cada um associa o intervalo a algo que reconhece. Quanto mais você treina, mais rápidos ficam."),
        tbl ({ "Sensação", "Intervalo provável", "Semitons" }, {
            { "mesma nota, mais aguda", "oitava", "12" },
            { "vazio e grandioso", "quinta justa", "7" },
            { "firme, de chamada", "quarta justa", "5" },
            { "alegre e aberto", "terça maior", "4" },
            { "triste e fechado", "terça menor", "3" },
            { "tenso, quase desafinado", "trítono", "6" },
            { "brilhante e suspenso", "sétima maior", "11" },
            { "pede resolução", "sétima menor", "10" },
        }),

        h ("Do intervalo à música"),
        p (
            "Depois de dominar a identificação dos intervalos, você começa a usá-los para fazer música: tirar melodias de ouvido, acompanhar canções, improvisar com intenção. O intervalo deixa de ser um conceito teórico e passa a ser uma ferramenta prática do dia a dia musical."),
        b ("Tire uma melodia simples de ouvido, identificando os intervalos."),
        b ("Acompanhe uma música encontrando os intervalos dos acordes."),
        b ("Improvise escolhendo as notas pela distância que você quer ouvir."),

        h ("Preparando os próximos módulos"),
        p (
            "Os intervalos são a base de tudo o que vem a seguir. As escalas são padrões de intervalos; os acordes são empilhamentos de intervalos; a harmonia funcional é o jogo de tensão e resolução entre intervalos. Dominar este módulo é o que torna os próximos temas compreensíveis em vez de decorados."),
        c (
            "Nos exercícios finais, o app toca intervalos para você nomear e reconhece os que você toca. Os dois caminhos, juntos, fecham o módulo: identificar intervalos no instrumento e pelo ouvido."),


        h ("Consolidando o módulo"),
        p (
            "Para consolidar tudo o que foi estudado, faça uma revisão ativa: toque cada intervalo do quadro a partir de três tônicas diferentes, nomeie cada um de ouvido e confira os resultados com o app. Essa revisão reúne a medição, a percepção e a execução em um único exercício, que é exatamente o objetivo da Etapa 2."),
        b ("Toque cada intervalo a partir de três tônicas."),
        b ("Nomeie cada intervalo de ouvido antes de olhar a resposta."),
        b ("Confirme com o app e revise os erros."),

        h ("Resumo do método"),
        p (
            "Reunindo tudo: para identificar um intervalo pelo instrumento, toque as duas notas e deixe o app medir a distância; para identificá-lo de ouvido, siga o roteiro de direção, tamanho e qualidade; para consolidar, revise os intervalos do quadro a partir de várias tônicas. Esses três caminhos, praticados juntos, fecham o módulo e preparam os próximos temas do curso."),
        b ("Pelo instrumento: toque e confira a distância com o app."),
        b ("De ouvido: direção, tamanho e qualidade."),
        b ("Consolidação: revise o quadro em várias tônicas."),
        aud ({ "C4", "E4", "G4" }, "Exemplo final: a tríade maior, com terça (4) e quinta (7), para reconhecer e tocar."),

        h ("Resumo do tópico"),
        b ("Identificar um intervalo é dizer número, qualidade e sensação."),
        b ("Pelo instrumento, o app mede os semitons e valida."),
        b ("De ouvido, reconheça em três passos: direção, tamanho, qualidade."),
        b ("Cuidado com os pares que se confundem; conte os semitons."),
        b ("Dominar intervalos é a base para escalas, harmonia e improvisação."),
        part ("m2_partitura_arpejo", { "C4", "E4", "G4", "C5", "G4", "E4", "C4" },
              "Partitura de um arpejo: os intervalos da tríade tocados em sequência. Ouça e identifique cada salto."),
    };
}

} // namespace cursomusica::content
