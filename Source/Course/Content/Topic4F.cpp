#include "Course/Content/Topics.h"

// Topic 4F — Formação de acordes (Módulo 4, Etapa 4).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 4 — construção de acordes).
namespace cursomusica::content
{

std::vector<ContentItem> topic4F()
{
    return {

        p (
            "Formar um acorde é escolher notas e empilhá-las de forma que o ouvido reconheça uma sonoridade. Até agora você viu tríades e tétrades; neste tópico, o objetivo é entender o sistema por trás de todos eles. Quando você compreende como os acordes se formam, deixa de depender de formas decoradas e passa a construir qualquer acorde em qualquer lugar do braço, apenas contando intervalos."),
        p (
            "A regra geral é simples: um acorde se forma empilhando terças a partir de uma nota de partida, a tônica. A primeira terça dá a terceira nota; a segunda, a quinta; a terceira, a sétima. Se você parar na quinta, tem uma tríade; se acrescentar a sétima, tem uma tétrade; e assim por diante. Cada nota acrescentada muda o nome e a cor do acorde."),
        c (
            "Formar acorde = empilhar terças. O número de notas empilhadas dá o tamanho do acorde (tríade, tétrade, nona…)."),

        h ("O empilhamento de terças"),
        p (
            "Empilhar terças significa pegar a tônica, subir uma terça, subir outra terça sobre essa, e assim por diante. Cada terça pode ser maior (4 semitons) ou menor (3 semitons), e é essa alternância que cria as diferentes qualidades. Em Dó maior, as terças são: Dó→Mi (maior), Mi→Sol (menor), Sol→Si (maior). O resultado é a tétrade Dó7M."),
        b ("1ª terça: tônica → terça (maior ou menor)."),
        b ("2ª terça: terça → quinta."),
        b ("3ª terça: quinta → sétima."),
        img ("m4_formacao_acordes", "Formação de acordes: tríades e tétrades como empilhamento de terças sobre a tônica."),

        h ("Tamanho do acorde e nome"),
        p (
            "O número de notas empilhadas define o tamanho do acorde e, com ele, o nome. Duas notas formam um intervalo (não é acorde); três formam uma tríade; quatro formam uma tétrade. Quando você continua empilhando, chega às extensões: a nona (cinco notas), a décima primeira (seis) e a décima terceira (sete). Mas não se preocupe em tocar todas: na prática, você escolhe as notas essenciais."),
        tbl ({ "Notas", "Acorde", "Exemplo em Dó", "Semitons" }, {
            { "3", "tríade", "Dó–Mi–Sol", "0–4–7" },
            { "4", "tétrade", "Dó–Mi–Sol–Si", "0–4–7–11" },
            { "5", "nona", "Dó–Mi–Sol–Si–Ré", "0–4–7–11–14" },
            { "6", "décima primeira", "Dó–Mi–Sol–Si–Ré–Fá", "0–4–7–11–14–17" },
        }),

        h ("As notas essenciais"),
        p (
            "Nem todas as notas de um acorde têm o mesmo peso. A terça diz se o acorde é maior ou menor; a sétima diz a família; a tônica dá o nome; a quinta dá corpo, mas pode ser omitida. Por isso, em um acorde de quatro ou mais notas, muitas vezes você toca apenas três ou quatro: a tônica, a terça, a sétima e, às vezes, a tensão. Saber quais notas são essenciais é o que permite simplificar sem perder a identidade."),
        b ("Essenciais: tônica, terça e sétima."),
        b ("Quinta: dispensável na maioria dos casos."),
        b ("Tensões (9, 11, 13): cor, mas opcionais."),
        aud ({ "C4", "E4", "Bb4" }, "Acorde reduzido ao essencial (Dó–Mi–Si♭): ainda se reconhece o dominante."),

        h ("Formação das tríades e das tétrades"),
        p (
            "Com as regras em mãos, você forma qualquer acorde. Para a tríade maior, empilhe terça maior e terça menor (0–4–7). Para a menor, empilhe terça menor e terça maior (0–3–7). Para a tétrade de sétima maior, acrescente uma terça maior (0–4–7–11). Para a dominante, acrescente uma terça menor (0–4–7–10). Cada escolha muda uma nota e, com ela, toda a sonoridade."),
        tbl ({ "Acorde", "Empilhamento", "Semitons", "Exemplo em Dó" }, {
            { "Maior", "3M + 3m", "0–4–7", "Dó–Mi–Sol" },
            { "Menor", "3m + 3M", "0–3–7", "Dó–Mi♭–Sol" },
            { "7M", "3M + 3m + 3M", "0–4–7–11", "Dó–Mi–Sol–Si" },
            { "7", "3M + 3m + 3m", "0–4–7–10", "Dó–Mi–Sol–Si♭" },
            { "m7", "3m + 3M + 3m", "0–3–7–10", "Dó–Mi♭–Sol–Si♭" },
            { "m7♭5", "3m + 3m + 3M", "0–3–6–10", "Dó–Mi♭–Sol♭–Si♭" },
        }),

        h ("Formar acordes a partir da cifra"),
        p (
            "Ler uma cifra e formar o acorde é uma habilidade prática. A letra diz a tônica (C = Dó, G = Sol, Am = Lá menor); os símbolos dizem a qualidade (m = menor, 7 = dominante, 7M = sétima maior). Com a receita de semitons, você monta o acorde em qualquer tônica. Por exemplo, para F7M: Fá é a tônica, 7M pede 0–4–7–11, então Fá–Lá–Dó–Mi."),
        tbl ({ "Cifra", "Tônica", "Qualidade", "Notas (exemplo)" }, {
            { "C", "Dó", "maior", "Dó–Mi–Sol" },
            { "Dm", "Ré", "menor", "Ré–Fá–Lá" },
            { "G7", "Sol", "dominante", "Sol–Si–Ré–Fá" },
            { "F7M", "Fá", "sétima maior", "Fá–Lá–Dó–Mi" },
            { "Am7", "Lá", "menor com sétima", "Lá–Dó–Mi–Sol" },
        }),
        p (
            "Esse processo é o mesmo que você usará para ler qualquer música. Com prática, você reconhece a cifra e já 'vê' as notas no braço. O segredo é sempre partir da tônica e contar os intervalos: não existe acorde que fuja dessa regra. Mesmo as cifras mais complexas, com muitas extensões, obedecem ao mesmo princípio de empilhamento."),

        h ("Por que a formação importa mais que a forma"),
        p (
            "Muitos guitarristas passam anos decorando formas e travam quando precisam tocar em uma tonalidade nova ou quando aparece uma cifra diferente. Quem entende a formação não tem esse problema: basta contar os intervalos e montar o acorde onde a mão estiver. É a diferença entre saber um desenho e saber música. A forma é uma consequência; a formação é a causa."),
        b ("Forma decorada: só funciona onde você decorou."),
        b ("Formação entendida: funciona em qualquer tônica e posição."),
        b ("A forma nasce da formação, não o contrário."),

        h ("O que muda cada nota"),
        p (
            "Uma das melhores formas de entender a formação é alterar uma nota de cada vez e ouvir o que acontece. Pegue Dó maior (Dó–Mi–Sol) e desça a terça: vira Dó menor (Dó–Mi♭–Sol). Suba a quinta: vira Dó aumentado (Dó–Mi–Sol♯). Desça a quinta: vira Dó diminuto (Dó–Mi♭–Sol♭). Acrescente a sétima maior: Dó7M. Cada alteração tem um efeito sonoro específico."),
        b ("Terça: define maior ou menor."),
        b ("Quinta: define justa, aumentada ou diminuta."),
        b ("Sétima: define a família (7M, 7, m7…)."),
        aud ({ "C4", "E4", "G4", "C4", "Eb4", "G4", "C4", "E4", "G#4", "C4", "Eb4", "Gb4" },
             "Alterando uma nota de cada vez: maior, menor, aumentado, diminuto."),

        h ("Acordes suspensos"),
        p (
            "Existem acordes que substituem a terça por outro grau. O acorde suspenso (sus4) troca a terça pela quarta: em Dó, Dó–Fá–Sol (0–5–7). O sus2 troca a terça pela segunda: Dó–Ré–Sol (0–2–7). Esses acordes não são maiores nem menores — eles 'suspendem' a definição, criando uma sensação de abertura. São muito usados no pop e no rock como acordes de passagem."),
        tbl ({ "Acorde", "Substitui", "Semitons", "Notas em Dó" }, {
            { "sus4", "terça → quarta", "0–5–7", "Dó–Fá–Sol" },
            { "sus2", "terça → segunda", "0–2–7", "Dó–Ré–Sol" },
        }),

        h ("Formação e contexto"),
        p (
            "Um acorde isolado não diz muito; o que importa é o contexto. O mesmo Dó7M pode ser a tônica de uma música em Dó, o quarto grau de uma música em Sol, ou um acorde de passagem em outra tonalidade. Por isso, aprender a formar acordes caminha junto com aprender o campo harmônico. Nos módulos seguintes você vai ver como os acordes se relacionam dentro de uma tonalidade."),
        b ("O mesmo acorde pode ter funções diferentes conforme a tonalidade."),
        b ("Formar o acorde é o primeiro passo; entender sua função é o segundo."),
        b ("O campo harmônico organiza os acordes de uma tonalidade."),

        h ("Formação no instrumento"),
        p (
            "No braço, formar acordes é escolher quais cordas e casas usar. Como a guitarra tem seis cordas, você quase sempre tem mais de uma forma para o mesmo acorde. O importante é saber quais notas está tocando, para não incluir uma nota errada. Ao montar um acorde, comece pela tônica, conte a terça e a quinta, e só depois distribua as notas pelas cordas."),
        b ("Comece pela tônica: identifique-a no braço."),
        b ("Conte a terça e a quinta a partir dela."),
        b ("Distribua as notas pelas cordas sem abafar nenhuma."),
        part ("m4_partitura_triade", { "C4", "E4", "G4", "C5" },
              "Partitura da tríade de Dó maior formada por empilhamento (Dó–Mi–Sol–Dó)."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é decorar formas sem saber as notas, o que trava a transposição e a criatividade. Outro erro é incluir uma nota que não pertence ao acorde sem perceber — muitas vezes a corda errada soa. E há o erro de tentar tocar todas as notas de um acorde extenso quando bastam as essenciais. Formar acordes é escolher com intenção, não acumular notas."),
        b ("Não decore só a forma: saiba as notas."),
        b ("Confira se nenhuma corda indesejada está soando."),
        b ("Nem todo acorde precisa de todas as notas."),

        h ("Do acorde à harmonia"),
        p (
            "Formar acordes é a base, mas a música acontece quando os acordes se conectam. A passagem de um acorde para o outro envolve escolher as vozes, manter as notas comuns e respeitar a função de cada acorde dentro da tonalidade. É por isso que este módulo, depois de ensinar a formação, trata das famílias de acordes e da distribuição pelo braço. Formar bem é o começo; conduzir bem é o objetivo."),
        b ("Formar: montar o acorde certo."),
        b ("Conduzir: ligar os acordes com suavidade."),
        b ("A harmonia nasce da relação entre os acordes."),
        p (
            "Um exercício útil é montar o campo harmônico completo de uma tonalidade e tocar os sete acordes em sequência. Você vai ouvir como cada acorde tem uma função: alguns repousam, outros tensionam, outros preparam. Esse é o alicerce da harmonia funcional, que você aprofundará nos próximos módulos."),

        h ("Formação e criatividade"),
        p (
            "Quando você domina a formação, começa a criar suas próprias vozes. Em vez de tocar sempre a mesma forma, você escolhe as notas que soam melhor no contexto: uma terça mais aguda, uma sétima no baixo, uma quinta omitida. Esse é o caminho para um acompanhamento pessoal. A teoria não limita a criatividade — ela dá as ferramentas para exercê-la com precisão."),
        b ("Escolha as notas que servem à música."),
        b ("Omita o que não é essencial."),
        b ("Crie vozes próprias com base na formação."),

        h ("Aplicação musical"),
        p (
            "Pegue uma cifra simples de uma música que você gosta e, para cada acorde, escreva as notas que o formam. Depois toque a música, verificando se cada acorde soa com as notas certas. Esse exercício liga a leitura, a teoria e a execução. Com o tempo, você forma qualquer acorde em qualquer tônica sem pensar — e passa a criar suas próprias vozes."),
        b ("Escreva as notas de cada acorde da cifra."),
        b ("Toque e confira com o ouvido."),
        b ("O app reconhece as notas e confere a formação."),
        aud ({ "C4", "E4", "G4", "G3", "B3", "D4", "F4", "C4", "E4", "G4" },
             "Formação em ação: C – G7 – C, acordes montados por empilhamento."),

        h ("Resumo do tópico"),
        b ("Formar acorde = empilhar terças sobre a tônica."),
        b ("O número de notas define o tamanho (tríade, tétrade, nona…)."),
        b ("As notas essenciais são a tônica, a terça e a sétima."),
        b ("A cifra informa a tônica e a qualidade; a receita de semitons monta o acorde."),
        b ("Alterar uma nota muda a qualidade (maior, menor, aumentado, diminuto)."),
        c (
            "Nos exercícios deste tópico, forme e toque os acordes pedidos. O app reconhece as notas e confere o conjunto, aceitando qualquer posição do braço."),
    };
}

} // namespace cursomusica::content
