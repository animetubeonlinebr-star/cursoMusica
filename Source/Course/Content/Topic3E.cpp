#include "Course/Content/Topics.h"

// Topic 3E — Levadas com palheta (Modulo 3, Etapa 3).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 3, bloco E).
namespace cursomusica::content
{

std::vector<ContentItem> topic3E()
{
    return {

        p (
            "A palheta é a ferramenta que dá o ataque ao som da guitarra. A mão direita, com a palheta, é quem faz o ritmo: ela decide quando cada acorde soa e com que intensidade. Este tópico ensina as levadas com palheta — os desenhos de ataque mais usados no rock, no pop e no reggae — e a técnica que mantém o tempo firme: a palhetada alternada."),
        p (
            "Dominar a mão direita é o que separa o guitarrista que 'sabe os acordes' do guitarrista que faz música. Um acorde simples, tocado com uma boa levada, soa profissional. O contrário também é verdade: um acorde difícil, tocado com a mão direita insegura, soa amador. O ritmo está na mão que ataca."),
        c (
            "Objetivo: tocar levadas de acompanhamento com palheta, mantendo o pulso firme e a mão relaxada. A levada é o que dá o caráter ao acompanhamento."),

        h ("A pegada da palheta"),
        p (
            "A forma de segurar a palheta define o som e a resistência. Segure-a entre o polegar e o indicador, deixando apenas uma pequena ponta para fora — cerca de um terço. Muita palheta para fora dá som duro e cansa a mão; pouca palheta abafa o som. A mão deve ficar relaxada, com o movimento vindo do pulso e não do braço."),
        b ("Segure entre polegar e indicador, com a ponta para fora."),
        b ("Deixe apenas um terço da palheta aparecendo."),
        b ("O movimento vem do pulso; o braço fica relaxado."),
        c (
            "Mão tensa não toca no tempo. Se a mão cansa rápido, a pegada está apertada demais ou a palheta está muito para fora."),

        h ("Palhetada para baixo e para cima"),
        p (
            "Existem dois ataques: para baixo (downstroke) e para cima (upstroke). O ataque para baixo é mais forte e costuma cair nos tempos; o para cima é mais leve e cai nos contratempos. Alternar os dois é o que permite tocar subdivisões rápidas sem esforço — cada ataque tem o seu espaço natural no tempo."),
        b ("Downstroke (v): ataque para baixo, mais forte, nos tempos."),
        b ("Upstroke (^): ataque para cima, mais leve, nos contratempos."),
        b ("Alternar os dois é a base da palhetada alternada."),
        img ("m3_direcoes_palheta", "As duas direções da palhetada: para baixo (v) e para cima (^)."),

        h ("Palhetada alternada"),
        p (
            "A palhetada alternada é a técnica mais importante da mão direita. Em vez de tocar tudo para baixo, você alterna: baixo, cima, baixo, cima. Isso economiza movimento, mantém a mão relaxada e permite tocar rápido sem perder o tempo. A regra é simples: o movimento da palheta é contínuo, mesmo quando não há nota — o silêncio 'toca' no ar."),
        tbl ({ "Situacao", "Palhetada", "Vantagem" }, {
            { "Seminimas", "tudo para baixo", "som forte, estavel" },
            { "Colcheias", "alternada (v ^ v ^)", "movimento economico" },
            { "Semicolcheias", "alternada estrita", "velocidade" },
            { "Acordes", "para baixo ou varredura", "som cheio" },
        }),
        b ("Alternada: baixo, cima, baixo, cima, sem parar."),
        b ("O movimento é contínuo mesmo nos silêncios."),
        b ("Isso mantém o tempo e evita travamentos."),
        img ("m3_levadas_palheta", "Levadas com palheta: direções e padrões de ataque por estilo."),
        c (
            "O segredo da alternada é o movimento contínuo. Quem 'para' a palheta no silêncio perde o tempo quando a nota volta."),

        h ("Levadas tipicas de acompanhamento"),
        p (
            "Cada estilo tem levadas típicas com palheta. O rock usa acordes marcados nos tempos fortes, muitas vezes com palm mute. O pop usa colcheias constantes, com acento no tempo 2 e 4. O reggae toca quase tudo no contratempo. O punk usa semicolcheias rápidas e agressivas. Reconhecer e reproduzir essas levadas é o que faz o acompanhamento soar no estilo certo."),
        tbl ({ "Estilo", "Levada com palheta", "Caracteristica" }, {
            { "Rock", "acordes nos tempos fortes", "palm mute, som cheio" },
            { "Pop", "colcheias constantes", "acento no backbeat" },
            { "Reggae", "contratempo (skank)", "ataque curto e leve" },
            { "Punk", "semicolcheias rapidas", "energia, sem abafar" },
            { "Metal", "palhetada alternada veloz", "precisao, palm mute" },
        }),
        b ("Rock: acorde cheio nos tempos 1 e 3, com abafamento."),
        b ("Pop: colcheias constantes, acento nos tempos 2 e 4."),
        b ("Reggae: acordes curtos no contratempo."),
        aud ({ "E2", "E2", "E2", "E2", "E2", "E2", "E2", "E2" }, "Colcheias na corda 6: o movimento base da palhetada alternada."),

        h ("Palm mute: o abafamento da ponte"),
        p (
            "O palm mute é uma técnica em que a base da mão direita abafa as cordas perto da ponte, produzindo um som curto e percussivo. É a marca do rock e do metal: o famoso 'chug' dos power chords. O segredo é apoiar a mão de leve sobre as cordas, sem abafar demais, e tocar a palheta com firmeza. Achar o ponto certo de abafamento é uma questão de prática."),
        b ("Apoie a base da mão sobre as cordas, perto da ponte."),
        b ("Toque com firmeza para o som sair curto e definido."),
        b ("Movimente a mão até achar o ponto de abafamento ideal."),
        c (
            "Palm mute demais abafa o som; de menos, não soa o efeito. É uma questão de equilíbrio: a mão abafa, mas não mata a nota."),

        h ("Ritmo e dinâmica na palhetada"),
        p (
            "A palhetada controla não só o tempo, mas a intensidade. O mesmo acorde pode soar suave ou agressivo dependendo da força do ataque. Trabalhar a dinâmica — tocar mais forte nos tempos fortes, mais leve nos fracos — dá relevo à levada. É isso que faz o acompanhamento respirar, em vez de soar plano e mecânico."),
        b ("Ataque mais forte nos tempos fortes, mais leve nos fracos."),
        b ("Variação de intensidade cria relevo e movimento."),
        b ("Dinâmica é parte do groove, não um enfeite."),

        h ("Erros comuns com a palheta"),
        p (
            "Os erros mais frequentes são travar a palheta nos silêncios (perdendo o tempo), segurar a palheta com força excessiva (cansando a mão) e tocar tudo para baixo em passagens rápidas (limitando a velocidade). Outro erro comum é mover o braço inteiro em vez do pulso, o que rouba precisão e velocidade."),
        b ("Travar a palheta no silêncio e perder o tempo."),
        b ("Apertar demais a palheta e cansar a mão."),
        b ("Tocar tudo para baixo em passagens rápidas."),
        b ("Mover o braço em vez do pulso."),
        c (
            "Dica: pratique a alternada em uma corda solta, devagar, olhando a mão. Quando o movimento ficar automático, leve-o para os acordes e as levadas."),

        h ("Como praticar levadas com palheta"),
        p (
            "Comece com uma corda solta e palhetada alternada, em andamento lento. Depois passe para um acorde único e toque a levada escolhida. Em seguida, acrescente a troca de acordes, mantendo a levada da mão direita. Este módulo usa BPM meta 68: um andamento calmo, ideal para consolidar o movimento antes de acelerar."),
        b ("Corda solta: treine o movimento da palheta."),
        b ("Um acorde: aplique a levada."),
        b ("Troca de acordes: mantenha a levada e deixe a mão esquerda acompanhar."),
        part ("m3_partitura_palheta", { "E3", "E3", "E3", "E3", "E3", "E3", "E3", "E3" },
              "Partitura: palhetada alternada na corda 6 (Mi). Cada nota é um ataque na grade."),

        h ("Resumo do topico"),
        b ("A mão direita, com a palheta, faz o ritmo: é ela que define o caráter."),
        b ("Pegada relaxada, movimento do pulso, ponta da palheta para fora."),
        b ("Palhetada alternada economiza movimento e mantém o tempo."),
        b ("Cada estilo tem levadas típicas: rock, pop, reggae, punk, metal."),
        b ("Palm mute e dinâmica dão relevo e percussão à levada."),
        c (
            "Nos exercícios, você tocará levadas com palheta na grade do metrônomo. O app mede o alinhamento e confere a estabilidade do pulso."),

        h ("Varredura de acorde (strumming)"),
        p (
            "Tocar um acorde inteiro com a palheta é uma varredura (strumming). Em vez de atacar cada corda isoladamente, a palheta passa por várias cordas em um único movimento, e o acorde soa cheio. A varredura pode ser para baixo, para cima ou alternada. Controlar a velocidade da varredura e a quantidade de cordas atingidas dá diferentes texturas ao acompanhamento."),
        tbl ({ "Varredura", "Cordas", "Efeito" }, {
            { "para baixo (cheia)", "todas as cordas", "som amplo" },
            { "para cima (cheia)", "todas as cordas", "resposta leve" },
            { "parcial (3 cordas)", "apenas as agudas", "som discreto" },
            { "alternada", "cheia ou parcial", "movimento continuo" },
        }),
        b ("Varredura cheia: todas as cordas, som amplo."),
        b ("Varredura parcial: só as cordas agudas, som discreto."),
        b ("Alternar para baixo e para cima dá fluidez à levada."),
        c (
            "A varredura é o gesto mais comum do acompanhamento com palheta. Suavizar a passagem pelas cordas é o que faz o acorde soar cheio em vez de 'picado'."),

        h ("Power chords e levadas de rock"),
        p (
            "Os power chords (acordes de quinta, como E5) são a base do rock e do metal. Formados por tônica e quinta, soam neutros e fortes, e são perfeitos para levadas com palm mute. A levada de rock clássica alterna o power chord abafado (palm mute) com o acorde aberto, criando o contraste entre o som curto e o som cheio que define o gênero."),
        b ("Power chord: tônica + quinta, sem terça."),
        b ("Alternar abafado e aberto cria o contraste do rock."),
        b ("A mão esquerda segura a forma; a direita faz o ritmo."),
        aud ({ "E2", "E2", "E2", "E2", "B2", "B2", "B2", "B2" }, "Power chords de Mi e Si: alternância de baixo, base de levada de rock."),

        h ("Do movimento mecanico ao groove"),
        p (
            "A palhetada mecânica mantém o tempo, mas o groove nasce do controle da intensidade e do silêncio. O mesmo desenho de ataques soa 'robótico' se todos os golpes tiverem a mesma força. Acentuar certos golpes, deixar outros mais leves e respeitar as pausas é o que transforma a mecânica em música. O groove mora no detalhe da mão direita."),
        b ("O movimento é mecânico; a expressão é intencional."),
        b ("Acento e silêncio criam o groove."),
        b ("Estude devagar exagerando a intenção; depois naturalize."),
        c (
            "Gravar a própria levada e ouvir é a forma mais rápida de perceber se falta groove. A gravação revela o que o ouvido 'completa' durante a execução."),

        h ("Planejando o estudo da mao direita"),
        p (
            "A mão direita merece estudo separado da esquerda. Dedique alguns minutos de cada sessão apenas ao movimento da palheta: alternada em corda solta, varredura em acorde único, palm mute em power chords. Esse trabalho isolado constrói uma mão direita independente e confiável — a base de todo acompanhamento sólido."),
        b ("Aquecimento: alternada em corda solta, lento e depois rápido."),
        b ("Varredura: acorde único, para baixo e para cima."),
        b ("Palm mute: power chords com abafamento na ponte."),
        b ("Levada completa: junte tudo com o metrônomo."),
        part ("m3_partitura_palheta", { "E3", "E3", "E3", "E3", "E3", "E3", "E3", "E3" },
              "Repita a partitura em andamento crescente, sem perder o alinhamento à grade."),
    };
}

} // namespace cursomusica::content
