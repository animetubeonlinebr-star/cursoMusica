#include "Course/Content/Topics.h"

// Topic 2F — Relação entre intervalos e construção de acordes.
// Fonte de verdade do texto: docs/MUSIC.md §2.2 (bloco F).
namespace cursomusica::content
{

std::vector<ContentItem> topic2F()
{
    return {

        p (
            "Um acorde não é um desenho decorado no braço: é um conjunto de intervalos empilhados sobre uma nota de base. Quando você entende isso, deixa de decorar formas e passa a construir qualquer acorde em qualquer lugar. Este tópico liga a teoria dos intervalos à prática dos acordes."),
        p (
            "A ideia central é simples: escolha a tônica, escolha os intervalos, toque as notas. O nome do acorde é apenas a descrição dos intervalos escolhidos."),

        h ("Tríades: três intervalos empilhados"),
        p (
            "A tríade é o acorde de três notas: tônica, terça e quinta. A terça define a qualidade (maior ou menor) e a quinta dá a estabilidade. Todas as combinações de tríade vêm de variar a terça e a quinta."),
        tbl ({ "Tríade", "Intervalos (semitons)", "Exemplo em Dó", "Som" }, {
            { "maior", "0, 4, 7", "Dó, Mi, Sol", "alegre, estável" },
            { "menor", "0, 3, 7", "Dó, Mib, Sol", "triste, estável" },
            { "diminuta", "0, 3, 6", "Dó, Mib, Solb", "tensa, instável" },
            { "aumentada", "0, 4, 8", "Dó, Mi, Sol#", "suspensa, etérea" },
        }),
        aud ({ "C4", "E4", "G4" }, "Tríade maior: Dó–Mi–Sol (0, 4, 7)."),
        aud ({ "C4", "D#4", "G4" }, "Tríade menor: Dó–Mib–Sol (0, 3, 7)."),
        c (
            "A única diferença entre o acorde maior e o menor é a terça: 4 semitons contra 3. Ouça as duas tríades e confirme que o resto é idêntico."),

        h ("Tétrades: acrescentando a sétima"),
        p (
            "Ao acrescentar a sétima sobre a tríade, formam-se as tétrades. O intervalo da sétima define o caráter do acorde: sétima maior dá brilho; sétima menor dá o som do dominante. As tétrades são a base da harmonia de jazz, bossa e MPB."),
        tbl ({ "Tétrade", "Intervalos (semitons)", "Exemplo em Dó", "Cifra" }, {
            { "sétima maior", "0, 4, 7, 11", "Dó, Mi, Sol, Si", "C7M" },
            { "sétima dominante", "0, 4, 7, 10", "Dó, Mi, Sol, Sib", "C7" },
            { "menor com sétima", "0, 3, 7, 10", "Dó, Mib, Sol, Sib", "Cm7" },
            { "meio-diminuto", "0, 3, 6, 10", "Dó, Mib, Solb, Sib", "Cm7(b5)" },
        }),
        aud ({ "C4", "E4", "G4", "B4" }, "Sétima maior: Dó–Mi–Sol–Si (0, 4, 7, 11)."),
        aud ({ "C4", "E4", "G4", "A#4" }, "Sétima dominante: Dó–Mi–Sol–Sib (0, 4, 7, 10)."),

        h ("Da tríade ao acorde completo"),
        p (
            "A passagem da tríade para a tétrade é apenas acrescentar um intervalo. Do mesmo modo, acrescentando a nona, a décima primeira ou a décima terceira, o acorde ganha cor sem mudar de função. Tudo continua sendo intervalo sobre a tônica."),
        b ("Tríade maior + sétima maior = acorde de sétima maior."),
        b ("Tétrade + nona = acorde de nona."),
        b ("As tensões (9, 11, 13) são intervalos de extensão: mesmo número, uma oitava acima."),
        img ("m2_triades_empilhadas", "Tríades e tétrades: cada nota é um intervalo empilhado sobre a tônica."),

        h ("Inversões de acorde"),
        p (
            "Inverter um acorde é trocar qual nota fica no baixo. As mesmas notas, em outra ordem, mudam a cor sem mudar o acorde. A inversão é uma consequência direta dos intervalos: você apenas escolhe qual deles soa mais grave."),
        b ("Estado fundamental: a tônica no baixo (Dó–Mi–Sol)."),
        b ("Primeira inversão: a terça no baixo (Mi–Sol–Dó)."),
        b ("Segunda inversão: a quinta no baixo (Sol–Dó–Mi)."),
        aud ({ "E4", "G4", "C5" }, "Primeira inversão: a terça no baixo — mesmo acorde, outra cor."),

        h ("Construindo acordes por intervalo"),
        p (
            "Com o quadro móvel na cabeça, construir um acorde é localizar as notas do intervalo a partir da tônica. Você não precisa de formas prontas: escolhe a tônica, encontra a terça e a quinta, e o acorde aparece."),
        b ("Ache a tônica na corda que quiser."),
        b ("Localize a terça (3 ou 4 semitons) e a quinta (7 semitons)."),
        b ("Toque as três notas e confirme o som com o app."),
        c (
            "Nos exercícios deste tópico, o app reconhece as notas que você toca e verifica se os intervalos formam a tríade pedida — em qualquer posição do braço."),


        h ("A tônica como referência"),
        p (
            "Todo acorde parte de uma nota de referência: a tônica. Escolhida a tônica, todos os outros intervalos são medidos a partir dela. É por isso que o mesmo desenho de acorde funciona em qualquer região do braço: o que muda é a tônica, não as distâncias. Entender isso é o que permite construir acordes em vez de decorar formas."),
        b ("Escolha a tônica (a nota que dá nome ao acorde)."),
        b ("Meça os intervalos a partir dela (terça, quinta, sétima…)."),
        b ("Toque as notas e o acorde aparece, em qualquer posição."),
        aud ({ "C4", "E4", "G4" }, "Tônica, terça e quinta a partir de Dó: o acorde maior."),

        h ("Acordes de três e de quatro notas"),
        p (
            "Os acordes mais usados têm três ou quatro notas. As tríades (três notas) são a base; as tétrades (quatro notas) acrescentam a sétima e definem o tipo do acorde. A diferença entre elas é apenas um intervalo a mais empilhado sobre a tríade."),
        b ("Tríade: tônica, terça e quinta."),
        b ("Tétrade: tríade mais a sétima."),
        b ("Quanto mais intervalos, mais rico e mais específico o som."),
        aud ({ "C4", "E4", "G4", "B4" }, "Sétima maior: a tríade de Dó com a sétima maior por cima."),

        h ("Acordes suspensos, aumentados e diminutos"),
        p (
            "Alterando um ou dois intervalos, formam-se outros acordes. Substituir a terça pela quarta cria o acorde suspenso (sus). Alargar a quinta cria o acorde aumentado. Estreitar a quinta e a terça cria o acorde diminuto. Todos são variações de intervalos sobre a mesma tônica."),
        tbl ({ "Acorde", "Intervalos (semitons)", "Exemplo em Dó" }, {
            { "maior", "0, 4, 7", "Dó, Mi, Sol" },
            { "menor", "0, 3, 7", "Dó, Mib, Sol" },
            { "suspenso (sus4)", "0, 5, 7", "Dó, Fá, Sol" },
            { "aumentado", "0, 4, 8", "Dó, Mi, Sol#" },
            { "diminuto", "0, 3, 6", "Dó, Mib, Solb" },
        }),
        aud ({ "C4", "F4", "G4" }, "Acorde suspenso: a quarta substitui a terça e pede resolução."),
        aud ({ "C4", "D#4", "F#4" }, "Acorde diminuto: terça menor e quinta diminuta, som instável."),

        h ("Inversões e baixo"),
        p (
            "Inverter um acorde é tocar as mesmas notas com outra no baixo. Isso não muda o acorde, mas muda a cor e ajuda a manter o baixo numa linha suave. As inversões são, na prática, uma escolha de qual intervalo soa mais grave."),
        b ("Estado fundamental: tônica no baixo."),
        b ("Primeira inversão: terça no baixo."),
        b ("Segunda inversão: quinta no baixo."),
        aud ({ "E4", "G4", "C5" }, "Primeira inversão: a terça no baixo, mesmo acorde com outra cor."),

        h ("Distribuição dos acordes pelo braço"),
        p (
            "Como o braço é uma régua de semitons, o mesmo acorde pode ser montado em várias regiões, com vozes diferentes. Escolher onde tocar depende do som que se quer e do movimento que se busca. O CAGED, do módulo 1, é justamente o mapa que organiza essas posições."),
        b ("A mesma tríade pode ser tocada em regiões graves ou agudas."),
        b ("A posição escolhida afeta o timbre e a condução das vozes."),
        b ("O CAGED conecta as formas por toda a extensão do braço."),
        c (
            "Nos exercícios deste tópico, o app reconhece as notas que você toca e verifica se os intervalos formam a tríade pedida, em qualquer posição."),


        h ("Acordes de sétima e suas funções"),
        p (
            "Os acordes de sétima são a base da harmonia funcional. A sétima maior dá um som brilhante e suspenso; a sétima menor cria o som do dominante, que pede resolução. Reconhecer a sétima de um acorde é o primeiro passo para entender sua função na música."),
        tbl ({ "Acorde", "Intervalos (semitons)", "Som" }, {
            { "sétima maior", "0, 4, 7, 11", "brilhante, suspenso" },
            { "sétima dominante", "0, 4, 7, 10", "tenso, pede resolução" },
            { "menor com sétima", "0, 3, 7, 10", "suave, jazzy" },
            { "meio-diminuto", "0, 3, 6, 10", "instável" },
        }),
        aud ({ "C4", "E4", "G4", "B4" }, "Sétima maior: brilho e suspensão."),
        aud ({ "C4", "E4", "G4", "A#4" }, "Sétima dominante: tensão que pede resolução."),

        h ("Como as inversões mudam a condução"),
        p (
            "As inversões são essenciais para a condução das vozes. Mantendo as notas mais graves próximas entre um acorde e o seguinte, o acompanhamento soa mais suave e profissional. Isso só é possível porque as inversões permitem escolher qual intervalo fica no baixo."),
        b ("Escolha a inversão que deixa o baixo mais próximo do acorde anterior."),
        b ("Mantenha as vozes comuns entre acordes sempre que possível."),
        b ("A condução suave é uma consequência direta do domínio dos intervalos."),
        aud ({ "G3", "C4", "E4" }, "Inversão com a quinta no baixo: baixo próximo, condução suave."),

        h ("Construindo acordes em qualquer posição"),
        p (
            "Com os intervalos na cabeça, você constrói o mesmo acorde em várias regiões do braço. Escolha a tônica, aplique os intervalos e pronto: o acorde aparece. Essa habilidade é o que permite acompanhar músicas em qualquer tom e encontrar a posição mais confortável para cada situação."),
        b ("Ache a tônica na corda desejada."),
        b ("Localize a terça e a quinta a partir dela."),
        b ("Toque as notas e confirme o som."),
        c (
            "Nos exercícios, o app reconhece as notas e verifica os intervalos da tríade pedida, em qualquer posição do braço."),


        h ("Reconhecendo acordes pelos intervalos"),
        p (
            "Identificar um acorde de ouvido é, na prática, identificar os intervalos que ele contém. Um acorde maior tem uma terça maior; um menor, uma terça menor; um de sétima acrescenta a sétima correspondente. Treinar o ouvido para os intervalos é o caminho mais direto para reconhecer acordes."),
        b ("Ouça o acorde e identifique a terça (maior ou menor)."),
        b ("Verifique se há sétima e qual é (maior ou menor)."),
        b ("Confirme tocando os intervalos no instrumento."),
        aud ({ "C4", "E4", "G4" }, "Acorde maior: ouça a terça maior dentro da harmonia."),
        aud ({ "C4", "D#4", "G4" }, "Acorde menor: a mesma estrutura com a terça menor."),

        h ("Acordes e condução harmônica"),
        p (
            "Numa progressão, os acordes se conectam pela proximidade das vozes. Entender os intervalos permite escolher inversões que mantêm o baixo e as vozes internas próximas, o que dá fluidez ao acompanhamento. Essa técnica, chamada condução de vozes, depende inteiramente do domínio dos intervalos."),
        b ("Mantenha as notas comuns entre acordes consecutivos."),
        b ("Escolha inversões que aproximem o baixo."),
        b ("A condução suave é uma consequência do domínio dos intervalos."),
        c (
            "Nos exercícios, o app reconhece as notas da tríade que você toca e confirma os intervalos, em qualquer inversão ou posição."),

        h ("Erros comuns ao montar acordes"),
        p (
            "Quem começa a montar acordes por intervalo costuma errar a contagem da terça ou esquecer a inversão. Conferir cada intervalo com calma e ouvir o resultado resolve a maior parte dos erros. O app ajuda porque mede a distância real das notas tocadas e confirma se a tríade está correta."),
        b ("Conte a terça com cuidado: 3 ou 4 semitons."),
        b ("Não esqueça que a inversão não muda o acorde."),
        b ("Confirme o som com o app antes de seguir adiante."),

        h ("Resumo do tópico"),
        b ("Um acorde é um conjunto de intervalos empilhados sobre a tônica."),
        b ("Tríade = tônica, terça e quinta; a terça define maior ou menor."),
        b ("Tétrade acrescenta a sétima, que define o tipo do acorde."),
        b ("Extensões (9, 11, 13) são intervalos uma oitava acima."),
        b ("Inversões mudam o baixo, não o acorde."),
        part ("m2_partitura_triade", { "C4", "E4", "G4", "C5" },
              "Partitura da tríade de Dó maior com a oitava no topo. Ouça as notas empilhadas."),
    };
}

} // namespace cursomusica::content
