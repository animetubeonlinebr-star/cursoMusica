#include "Course/Content/Topics.h"

// Topic 2G — Cantar e tocar os intervalos (Módulo 2, Etapa 2).
// Fonte de verdade do texto: docs/MUSIC.md §2.2 (bloco G).
namespace cursomusica::content
{

std::vector<ContentItem> topic2G()
{
    return {

        p (
            "Cantar e tocar os intervalos é o treino que une ouvido, voz e mão. Quando você canta uma nota antes de tocá-la, o cérebro precisa ter uma imagem sonora clara dela. Quando essa imagem está firme, tocar de ouvido e improvisar deixam de ser sorte e passam a ser controle."),
        p (
            "A ordem deste tópico é: ouvir, cantar, tocar, conferir. O app participa de cada passo — demonstra o exemplo, e depois reconhece o que você toca para dizer se o intervalo saiu correto."),

        h ("Por que cantar ajuda a tocar"),
        p (
            "A voz é o único instrumento que não depende de mecânica: ela reproduz o que o ouvido imagina. Por isso, quando você canta um intervalo corretamente, é sinal de que o ouviu corretamente. O dedo no braço passa a executar uma ideia clara, em vez de procurar às cegas."),
        b ("Cantar desenvolve a memória auditiva."),
        b ("Cantar liga a altura ouvida à altura produzida."),
        b ("Quem canta a nota erra menos ao tocar de ouvido."),

        h ("Cantar a partir de uma nota de referência"),
        p (
            "O método é simples: toque uma nota fixa (por exemplo, a 5ª corda solta) e cante cada intervalo a partir dela. Use o app para conferir a altura cantada, se quiser. Comece pelos intervalos pequenos (segunda e terça) e vá aumentando."),
        b ("Toque a tônica e segure-a na memória."),
        b ("Cante o intervalo pedido acima dela."),
        b ("Toque a nota no braço e confira se coincide com o que cantou."),
        aud ({ "A2", "B2", "C#3", "D3", "E3" }, "Sequência para cantar: segunda, terça menor, terça maior, quarta — subindo a partir de Lá."),

        h ("Cantar o intervalo antes de tocar"),
        p (
            "O exercício mais valioso é cantar a nota antes de tocar. Você toca a tônica, canta a terça, e só depois toca a terça no braço. Se as duas alturas coincidem, sua percepção está alinhada com o instrumento."),
        b ("Toca a tônica."),
        b ("Canta o intervalo-alvo sem tocar."),
        b ("Toca a nota e compara mentalmente."),
        c (
            "No começo pode parecer lento, mas é este passo que constrói o ouvido. Com a prática, o intervalo cantado sai certo de primeira."),

        h ("Tocar o intervalo no instrumento"),
        p (
            "Depois de cantar, você toca o intervalo no braço. Aqui entra o reconhecimento do app: ele escuta as notas que você toca e confere se a distância em semitons corresponde ao intervalo pedido. Não importa a posição — só o intervalo."),
        b ("Escolha uma nota de partida qualquer."),
        b ("Toque a segunda nota do intervalo pedido."),
        b ("O app confere a distância e mostra o resultado."),
        img ("m2_cantar_tocar", "O ciclo do treino: ouvir, cantar, tocar e conferir com o app."),

        h ("Intervalos melódicos e harmônicos na prática"),
        p (
            "Você pode cantar e tocar tanto intervalos melódicos (notas em sequência) quanto harmônicos (notas juntas). Cantar um intervalo harmônico é mais difícil, porque as duas notas soam ao mesmo tempo; uma boa estratégia é cantar cada nota separadamente e depois ouvi-las juntas."),
        b ("Melódico: toque as duas notas uma após a outra e cante junto."),
        b ("Harmônico: cante cada nota separada, depois toque as duas juntas."),
        aud ({ "C4", "G4" }, "Quinta harmônica: cante Dó e Sol separadamente antes de ouvir as duas juntas."),

        h ("Do exercício para a música"),
        p (
            "Quando cantar e tocar intervalos vira hábito, você consegue aprender melodias de ouvido: ouve uma frase, identifica os intervalos e reproduz no braço. É esse o objetivo final do módulo — não decorar intervalos, mas usá-los para fazer música."),
        b ("Ouça uma melodia simples e identifique os primeiros intervalos."),
        b ("Cante-os e depois toque-os no braço."),
        b ("Repita até a frase sair sem hesitação."),
        c (
            "A percepção treinada aqui é a mesma usada nos módulos de improvisação: reconhecer a distância entre as notas é a base para escolher as próximas notas com intenção."),


        h ("Do ouvido para a voz, da voz para o dedo"),
        p (
            "Existe uma cadeia que liga o ouvido, a voz e a mão. Quando você ouve um intervalo e o canta corretamente, confirma que o ouviu bem. Quando canta e depois toca a mesma nota, confirma que o dedo executa o que o ouvido imaginou. Quebrar essa cadeia em etapas torna o treino mais eficiente do que tentar tocar de ouvido diretamente."),
        b ("Ouça o intervalo."),
        b ("Cante-o."),
        b ("Toque-o e compare com o que cantou."),
        aud ({ "C4", "E4" }, "Ouça, cante e depois toque esta terça maior a partir de Dó."),

        h ("Escolhendo a nota de referência"),
        p (
            "Uma nota de referência fixa é o alicerce do treino de canto. Escolha uma nota que você consiga cantar confortavelmente — a 5ª corda solta (Lá) ou a 6ª solta (Mi) funcionam bem — e use-a como base para todos os intervalos. Com o tempo, você internaliza essa referência e consegue partir dela sem tocar."),
        tbl ({ "Referência", "Nota", "Uso" }, {
            { "6ª corda solta", "Mi (E2)", "base grave, fácil de cantar" },
            { "5ª corda solta", "Lá (A2)", "base intermediária" },
            { "3ª corda solta", "Sol (G3)", "base aguda, para vozes mais altas" },
        }),

        h ("Cantar intervalos harmônicos"),
        p (
            "Cantar um intervalo harmônico é mais difícil, porque as duas notas soam juntas. A estratégia é cantar cada nota separadamente, ouvi-las na memória e só então ouvir as duas ao mesmo tempo. Esse exercício desenvolve a capacidade de ouvir notas dentro de um acorde, habilidade essencial para harmonizar melodias."),
        b ("Cante a nota grave, depois a aguda."),
        b ("Ouça as duas juntas e perceba como se combinam."),
        b ("Repita até conseguir manter cada nota na memória."),
        aud ({ "C4", "G4" }, "Quinta harmônica: cante Dó e Sol separadamente antes de ouvir juntos."),

        h ("Repetição e consistência"),
        p (
            "O ouvido se desenvolve com repetição consistente, não com esforço concentrado esporádico. Cantar e tocar alguns intervalos todos os dias produz mais resultado do que uma sessão longa de vez em quando. O app ajuda porque permite repetir os exemplos quantas vezes forem necessárias, sempre com a mesma afinação."),
        b ("Pratique todos os dias, mesmo que por pouco tempo."),
        b ("Repita o mesmo intervalo até ele sair sem esforço."),
        b ("Acrescente novos intervalos só quando os anteriores estiverem firmes."),
        part ("m2_partitura_intervalos", { "C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5" },
              "Escala maior: cante subindo junto com o áudio, um passo por vez."),

        h ("Aplicando o treino à música"),
        p (
            "Quando cantar e tocar intervalos vira hábito, aprender música de ouvido se torna possível. Você ouve uma frase, identifica os intervalos e reproduz no braço. Esse é o objetivo final do módulo: não decorar intervalos, mas usá-los para fazer música de forma consciente e controlada."),
        c (
            "O mesmo treino é a base dos módulos de improvisação: escolher notas com intenção exige ouvir a distância entre elas antes de tocar."),


        h ("Exercícios de canto para o dia a dia"),
        p (
            "Alguns exercícios simples, feitos todos os dias, desenvolvem o ouvido rapidamente. Cantar a escala maior subindo e descendo, cantar terças e quintas a partir de uma nota fixa, e cantar a nota antes de tocá-la são os mais eficazes. O importante é a constância, não a duração."),
        b ("Cante a escala maior subindo e descendo, junto com o instrumento."),
        b ("Cante terças e quintas a partir de uma nota de referência."),
        b ("Cante a nota antes de tocá-la e confira a altura."),
        aud ({ "C4", "E4", "G4", "C5" }, "Cante junto: tônica, terça, quinta e oitava."),

        h ("O papel do app no treino"),
        p (
            "O app toca os exemplos com afinação exata e reconhece as notas que você toca. Isso permite um ciclo de treino completo: ouvir o exemplo, cantar, tocar e receber o retorno imediato. Esse retorno é o que acelera o aprendizado, porque corrige o erro no momento em que ele acontece."),
        b ("Ouça o exemplo demonstrado pelo app."),
        b ("Cante o intervalo junto."),
        b ("Toque-o no instrumento e veja se o app confirma."),

        h ("Da percepção à performance"),
        p (
            "Quando o ouvido está treinado, tocar deixa de ser um ato mecânico e passa a ser uma escolha consciente. Você ouve a distância entre as notas antes de tocá-las, e a mão executa o que a cabeça imaginou. Essa ligação entre percepção e execução é o que distingue um músico que apenas repete de um que realmente entende o que toca."),
        c (
            "A habilidade treinada aqui é a mesma usada nos módulos de improvisação: ouvir antes de tocar, escolhendo as notas com intenção."),


        h ("Cantar e a memória de longo prazo"),
        p (
            "Cantar intervalos consolida a memória de longo prazo porque envolve o corpo, não apenas o ouvido. Quando você canta uma terça maior repetidamente, ela se torna uma referência interna que você acessa sem pensar. Essa memória corporal é o que permite tocar de ouvido com segurança."),
        b ("Cantar envolve a voz, o ouvido e a memória ao mesmo tempo."),
        b ("A repetição transforma o intervalo em referência interna."),
        b ("A referência interna permite tocar sem contar semitons."),

        h ("Erros comuns no treino de canto"),
        p (
            "Quem começa a cantar intervalos costuma cometer alguns erros: cantar alto demais, forçar a voz ou tentar acertar de primeira um intervalo difícil. O canto deve ser confortável e relaxado; o objetivo não é a qualidade vocal, mas a precisão da altura. Cantar baixo e com calma produz melhores resultados."),
        b ("Cante em uma altura confortável, sem forçar."),
        b ("Comece pelos intervalos pequenos e vá aumentando."),
        b ("O objetivo é a precisão, não o volume."),
        c (
            "Com o tempo, o ciclo ouvir-cantar-tocar-conferir se torna automático, e o ouvido passa a guiar a mão no instrumento."),


        h ("Cantar e improvisar"),
        p (
            "Cantar intervalos também prepara para improvisar. Quem consegue cantar o que pretende tocar improvisa com intenção, escolhendo as notas pela distância que quer ouvir. Sem essa ligação, a improvisação vira tentativa e erro. O treino de canto, por isso, aparece antes dos módulos de improvisação."),
        b ("Cante a nota que pretende tocar antes de tocá-la."),
        b ("Toque e confirme se a nota coincide com o que cantou."),
        b ("A improvisação consciente depende dessa ligação."),

        h ("Resumo do tópico"),
        b ("Cantar desenvolve a memória auditiva e liga ouvido e mão."),
        b ("Cante a partir de uma nota de referência, subindo aos poucos."),
        b ("Cante antes de tocar: é o passo que constrói o ouvido."),
        b ("Toque o intervalo e deixe o app conferir a distância."),
        b ("Intervalos melódicos e harmônicos treinam habilidades complementares."),
        part ("m2_partitura_intervalos", { "C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5" },
              "Partitura de uma escala maior: cada passo é um intervalo. Cante subindo junto com o áudio."),
    };
}

} // namespace cursomusica::content
