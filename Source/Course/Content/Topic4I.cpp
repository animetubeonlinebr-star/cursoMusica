#include "Course/Content/Topics.h"

// Topic 4I — Acordes clean e distribuição pelo braço (Módulo 4, Etapa 4).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 4 — construção de acordes).
namespace cursomusica::content
{

std::vector<ContentItem> topic4I()
{
    return {

        p (
            "Você já sabe formar acordes e usar as formas do CAGED. Falta o acabamento: fazer o acorde soar limpo e saber distribuí-lo pelo braço. Um acorde bem montado, mas com uma corda abafada ou um zumbido, soa amador; um acorde limpo, mesmo simples, soa profissional. Neste tópico você aprende a tocar acordes clean — sem ruído — e a escolher onde tocar cada acorde no braço."),
        p (
            "Tocar 'clean' (limpo) depende de três coisas: a posição dos dedos, a pressão certa e a escolha das cordas que devem soar. Distribuir os acordes pelo braço significa escolher a região que melhor serve à música — mantendo a mão confortável e a condução de vozes suave. Esses dois cuidados, juntos, transformam o acompanhamento."),
        c (
            "Clean = sem corda abafada, sem zumbido e sem nota errada. Distribuição = escolher onde tocar o acorde no braço."),

        h ("O que é um acorde clean"),
        p (
            "Um acorde clean é aquele em que todas as notas soam claras e no volume certo, sem nenhum ruído parasita. Na guitarra, isso exige atenção a detalhes: o dedo deve pressionar logo atrás do traste (não em cima, não no meio da casa); a pressão deve ser suficiente para a corda soar, mas não excessiva; e as cordas que não pertencem ao acorde devem ser abafadas de propósito. Um acorde clean é o resultado de vários cuidados simultâneos."),
        b ("Dedo logo atrás do traste, nunca em cima dele."),
        b ("Pressão suficiente: nem abafado, nem apertado demais."),
        b ("Cordas que não pertencem ao acorde devem ser abafadas."),
        img ("m4_acordes_clean", "Acordes clean: pestana de Fá e meio barré de Si menor, com todas as cordas limpas."),

        h ("A posição dos dedos"),
        p (
            "A causa número um de acorde sujo é a posição dos dedos. Se o dedo está no meio da casa, a corda vibra mal e o som sai abafado; se está em cima do traste, o som chia. A regra é: pressione o mais próximo possível do traste, sem encostar nele. Além disso, cada dedo deve pressionar apenas a corda que lhe cabe, sem encostar nas vizinhas. Um leve ajuste de ângulo resolve muitos problemas."),
        b ("Pressione junto ao traste (sem encostar)."),
        b ("Cada dedo toca só a sua corda."),
        b ("Ajuste o ângulo para não abafar as vizinhas."),

        h ("A pestana e o meio barré"),
        p (
            "A pestana (barré) é o teste definitivo do acorde clean: um dedo cobre várias cordas e todas precisam soar. Para isso, o dedo deve estar reto, pressionando com a parte óssea lateral, e o polegar deve apoiar no meio do braço, dando alavanca. O meio barré cobre de duas a quatro cordas e é mais fácil, porque exige menos extensão. Em ambos, a limpeza vem do ajuste fino, não da força bruta."),
        b ("Pestana: dedo reto, apoiado no osso lateral."),
        b ("Polegar no meio do braço para dar alavanca."),
        b ("Meio barré: 2 a 4 cordas, mais fácil que a pestana completa."),
        aud ({ "F2", "C3", "F3", "A3", "C4", "F4" }, "Fá maior com pestana: todas as cordas soam limpas."),

        h ("Abafar as cordas certas"),
        p (
            "Muitos acordes não usam todas as seis cordas. No acorde de Ré maior, por exemplo, a 5ª e a 6ª cordas não soam. Abafá-las é parte de tocar clean: você usa o polegar, a lateral da mão ou um dedo para silenciá-las de propósito. Um acorde com uma corda grave indevida soando soa 'embolado', mesmo que as notas estejam certas."),
        b ("Identifique quais cordas o acorde usa."),
        b ("Abafe as demais com o polegar ou a lateral da mão."),
        b ("Corda grave indevida embola o acorde."),
        tbl ({ "Acorde", "Cordas que soam", "Abafadas" }, {
            { "Dó maior (C)", "5ª a 1ª", "6ª" },
            { "Ré maior (D)", "4ª a 1ª", "6ª e 5ª" },
            { "Lá maior (A)", "5ª a 1ª", "6ª" },
            { "Sol maior (G)", "6ª a 1ª", "nenhuma" },
        }),

        h ("A pressão certa"),
        p (
            "A pressão é um equilíbrio: se for pouca, a corda abafa; se for muita, a mão cansa e a afinação sobe. O ideal é a pressão mínima que faz a corda soar limpa. Isso vem com a prática e com a posição correta do dedo: quando o dedo está junto ao traste, é preciso muito menos força. Tocar clean é, em grande parte, tocar com eficiência."),
        b ("Pressão mínima que faz a corda soar."),
        b ("Dedo junto ao traste reduz a força necessária."),
        b ("Pressão excessiva sobe a afinação."),

        h ("Distribuir os acordes pelo braço"),
        p (
            "Distribuir acordes pelo braço é escolher a região em que você toca cada acorde. O mesmo acorde existe em várias regiões, com cores diferentes. A escolha depende da música: se a melodia está aguda, toque o acorde mais grave; se você quer brilho, toque mais agudo. A distribuição também serve para manter a mão próxima do próximo acorde, evitando saltos."),
        b ("O mesmo acorde existe em várias regiões do braço."),
        b ("Escolha a região pela cor e pela conveniência."),
        b ("Evite saltos desnecessários entre acordes."),
        img ("m4_distribuicao_braco", "A tríade de Dó distribuída pelo braço: tônica (roxo), terça e quinta (ciano)."),

        h ("Distribuição e a tônica"),
        p (
            "Para distribuir um acorde pelo braço, comece pela tônica: encontre-a na corda que você quer usar e, a partir dela, conte a terça e a quinta. Como a guitarra é uma régua de semitons, a terça está sempre a 3 ou 4 semitons, e a quinta a 7. Achar a tônica primeiro é a chave para montar o acorde em qualquer região — e para saber se você está tocando a nota certa no baixo."),
        b ("Ache a tônica na corda desejada."),
        b ("Conte a terça (3 ou 4 semitons) e a quinta (7)."),
        b ("Confira se o baixo é a nota que você quer."),

        h ("Distribuição e o baixo"),
        p (
            "A distribuição define também qual nota fica no baixo. Se você toca a forma com a tônica na 6ª corda, o baixo é a tônica; se usa uma inversão, o baixo pode ser a terça ou a quinta. Escolher a distribuição é, muitas vezes, escolher o baixo. E o baixo é o que dá o alicerce do acorde — por isso essa escolha é tão importante."),
        b ("A forma escolhida define a nota do baixo."),
        b ("Baixo na tônica: mais estável."),
        b ("Baixo na terça ou quinta: mais leve, de passagem."),

        h ("Distribuição em uma progressão"),
        p (
            "Em uma progressão, a distribuição ideal mantém a mão em uma região e as vozes em movimento suave. Se um acorde está na 1ª posição e o seguinte exige um salto de cinco casas, talvez exista uma distribuição melhor que fique mais perto. Pensar na progressão inteira, e não em cada acorde isolado, é o que dá fluidez ao acompanhamento."),
        b ("Pense na progressão, não no acorde isolado."),
        b ("Mantenha a mão em uma região quando possível."),
        b ("Busque a distribuição que suaviza o movimento."),
        part ("m4_partitura_progressao", { "C4", "A4", "D4", "G4" },
              "Partitura das fundamentais da progressão Dó – Lá menor – Ré menor – Sol, distribuída pelo braço."),

        h ("Distribuição e as três regiões do braço"),
        p (
            "O braço costuma ser dividido em três regiões práticas: a primeira posição (casas 1 a 4), a região média (casas 5 a 8) e a região aguda (casas 9 a 12). Cada região tem uma cor e uma função. A primeira posição é a mais familiar e cheia; a média é equilibrada; a aguda é brilhante. Saber tocar o mesmo acorde nas três regiões dá ao guitarrista um vocabulário enorme de acompanhamento."),
        tbl ({ "Região", "Casas", "Cor", "Uso" }, {
            { "1ª posição", "1–4", "cheia, familiar", "acompanhamento básico" },
            { "média", "5–8", "equilibrada", "condução, solos" },
            { "aguda", "9–12", "brilhante", "arranjos, contrastes" },
        }),
        aud ({ "C3", "E3", "G3", "C4", "E4", "G4", "C5", "E5", "G5" },
             "Dó maior em três regiões: grave, média e aguda."),

        h ("Clean, distribuição e o estilo"),
        p (
            "A limpeza e a distribuição mudam conforme o estilo. No violão de bossa nova, o acorde clean e a distribuição suave são essenciais, porque a música é delicada. No rock, às vezes se busca um som mais cru e menos 'limpo'. Mas mesmo no rock, um acorde com corda abafada indesejada atrapalha. Saber tocar clean é uma base que serve a todos os estilos."),
        b ("Bossa nova: clean e distribuição suave são essenciais."),
        b ("Rock: pode ser mais cru, mas sem abafamento indesejado."),
        b ("A base clean serve a qualquer estilo."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é achar que força resolve: apertar demais cansa a mão e desafina. Outro erro é não abafar as cordas que não pertencem ao acorde, deixando notas estranhas soando. E há o erro de tocar sempre na mesma região do braço, o que limita as possibilidades e deixa o acompanhamento monótono. Clean e distribuição são hábitos que se constroem com atenção."),
        b ("Força bruta não resolve; ajuste fino sim."),
        b ("Abafe as cordas que não pertencem ao acorde."),
        b ("Explore regiões diferentes do braço."),

        h ("Rotina para um acorde clean"),
        p (
            "Uma rotina simples ajuda a limpar qualquer acorde. Primeiro, monte o acorde devagar e toque corda por corda, ouvindo cada nota isoladamente. Identifique qual corda está abafada ou chiando. Depois, ajuste a posição do dedo correspondente e repita. Só quando todas as cordas soarem limpas individualmente é que você toca o acorde inteiro. Esse método resolve quase todos os problemas de limpeza."),
        b ("Toque corda por corda, ouvindo cada nota."),
        b ("Identifique a corda problemática e ajuste o dedo."),
        b ("Só então toque o acorde inteiro."),
        p (
            "Depois de limpar o acorde isolado, faça o mesmo dentro de uma progressão: toque a sequência devagar, conferindo a limpeza a cada troca. Muitas vezes o problema aparece só na mudança, quando um dedo chega atrasado ou encosta em outra corda. Praticar a troca devagar, cuidando da limpeza, é o que consolida o acorde clean no contexto real."),

        h ("Distribuição e criatividade"),
        p (
            "Saber distribuir acordes pelo braço abre espaço para a criatividade. Você deixa de tocar sempre a mesma forma e passa a escolher a região que combina com a música. Uma mesma progressão pode soar íntima na região grave, brilhante na aguda ou equilibrada na média. Essa escolha é uma decisão musical, e tomá-la com consciência é o que dá personalidade ao acompanhamento."),
        b ("Escolha a região pela intenção musical."),
        b ("A mesma progressão muda de caráter conforme a região."),
        b ("Distribuir é uma decisão musical, não um acidente."),

        h ("Aplicação musical"),
        p (
            "Escolha uma música simples e toque-a duas vezes: primeiro cuidando só da limpeza (cada acorde clean), depois cuidando da distribuição (a mão se movendo o mínimo). Em seguida, junte as duas coisas. Você vai notar uma diferença enorme na qualidade do acompanhamento. O app reconhece as notas e confere cada acorde, então você pode verificar se está tocando as notas certas em qualquer distribuição."),
        b ("Primeiro: limpeza. Depois: distribuição."),
        b ("Junte as duas e ouça o resultado."),
        b ("O app confere as notas, não a região do braço."),
        aud ({ "C4", "E4", "G4", "A3", "C4", "E4", "D4", "F4", "A4", "G3", "B3", "D4", "C4", "E4", "G4" },
             "Progressão clean: C – Am – Dm – G com cada acorde soando limpo."),

        h ("Resumo do tópico"),
        b ("Acorde clean: sem corda abafada, sem zumbido, sem nota errada."),
        b ("Dedo junto ao traste, pressão mínima, cordas certas abafadas."),
        b ("Pestana e meio barré exigem ajuste fino, não força."),
        b ("Distribuir é escolher a região do braço e a nota do baixo."),
        b ("Pense na progressão inteira ao distribuir os acordes."),
        c (
            "Nos exercícios deste tópico, toque os acordes pedidos cuidando da limpeza e da distribuição. O app reconhece as notas e confere o conjunto, aceitando qualquer região do braço."),
    };
}

} // namespace cursomusica::content
