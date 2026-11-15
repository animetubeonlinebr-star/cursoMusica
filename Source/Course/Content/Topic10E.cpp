#include "Course/Content/Topics.h"

// Topic 10E — Conexão entre campos harmônicos (Módulo 10, Etapa 10).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 10) e o laboratório de
// standards (500 Miles High, Spain: modulação e áreas tonais).
namespace cursomusica::content
{

std::vector<ContentItem> topic10E()
{
    return {

        p (
            "Conexão entre campos harmônicos é a arte de passar de uma tonalidade para outra sem que a música pareça 'pular'. Toda música que modula precisa de uma ponte entre os dois campos — e essa ponte é feita, quase sempre, por acordes que existem nos dois campos (os acordes-pivo) ou por dominantes que preparam o novo centro. Entender essa conexão é o que permite tocar uma música modulante sem se perder e, mais adiante, reharmonizar criando ou desfazendo modulações."),
        p (
            "O repertório curado do curso é cheio de exemplos: 500 Miles High liga duas áreas tonais distantes (Em/Am e Fm/Cm) por movimento cromático, e Spain atravessa modulações ao longo da forma. Este tópico ensina a identificar os pontos de ligação e a escolher o caminho entre dois centros."),
        c (
            "Ideia central: uma modulação não é uma ruptura — é uma passagem. A música caminha de um centro para o outro usando acordes que pertencem aos dois mundos."),

        h ("O que é um campo harmônico"),
        p (
            "O campo harmônico é o conjunto dos sete acordes que nascem de uma escala. Em Dó maior, o campo é C7M, Dm7, Em7, F7M, G7, Am7, Bm7b5. Em Fá maior, o campo é F7M, Gm7, Am7, Bb7M, C7, Dm7, Em7b5. Quando dois campos compartilham acordes, a música pode transitar entre eles por esses acordes comuns — e é isso que faz a modulação soar natural."),
        tbl ({ "Grau", "Campo de Dó", "Campo de Fá", "Comum?" }, {
            { "I", "C7M", "F7M", "não" },
            { "ii", "Dm7", "Gm7", "não" },
            { "iii", "Em7", "Am7", "não" },
            { "IV", "F7M", "Bb7M", "não" },
            { "V", "G7", "C7", "não" },
            { "vi", "Am7", "Dm7", "não (mas é pivo funcional)" },
            { "vii", "Bm7b5", "Em7b5", "não" },
        }),
        c (
            "Apesar de os campos de Dó e Fá não compartilharem acordes literais, eles se conectam por acordes-pivo funcionais: o Dm7 é o ii de Dó e o vi de Fá; o Am7 é o vi de Dó e o iii de Fá. A mesma nota serve a duas funções — é aí que a modulação acontece."),

        h ("Acordes-pivo: os acordes que pertencem aos dois campos"),
        p (
            "O acorde-pivo é o acorde que existe (ou exerce função) nos dois campos. Ele é a dobradiça da modulação. Quando a música chega a um acorde-pivo, você está 'em cima do muro': a partir dele pode seguir para o campo antigo ou para o novo. Reconhecer o pivo é reconhecer o momento exato em que a tonalidade muda — e é o que permite acompanhar uma música modulante sem se perder."),
        b ("Pivo literal: o acorde pertence aos dois campos (ex.: Am7 é vi de Dó e iii de Fá)."),
        b ("Pivo funcional: o acorde muda de função ao mudar de campo (Dm7 é ii de Dó e vi de Fá)."),
        b ("O pivo é a dobradiça: a música pode seguir para qualquer um dos dois lados."),
        img ("m10_conexao_campos", "Dois campos harmônicos ligados por acordes-pivo. O Dm7 é o pivo: ii de Dó, vi de Fá."),
        aud ({ "C4", "E4", "G4", "B4", "A3", "C4", "E4", "G4", "D4", "F4", "A4", "C5" },
             "C7M → Am7 → Dm7: o Am7 é o pivo. Ouça como a música pode seguir para dois lados."),

        h ("Como se faz uma modulação"),
        p (
            "Modular é mudar de centro. Existem várias técnicas, e a mais comum é preparar o novo centro com o dominante dele. Para ir de Dó a Fá, você toca o dominante de Fá (C7) antes do F7M. Esse C7 é uma ponte: ele não pertence ao campo de Dó como dominante (ali o dominante é G7), mas prepara perfeitamente o Fá. Outra técnica é a modulação relativa: Dó maior e Lá menor compartilham o mesmo campo, então passar de um para o outro é quase imperceptível."),
        tbl ({ "Técnica", "Como funciona", "Exemplo" }, {
            { "Dominante do novo tom", "tocar o V do novo campo antes dele", "C7 → F7M (Dó para Fá)" },
            { "Relativa", "compartilhar o mesmo campo", "C7M ↔ Am7" },
            { "Pivo", "chegar por um acorde comum aos dois campos", "Am7 → Dm7 (pivo)" },
            { "Cromática", "subir ou descer de semitom", "F7M → F#7M" },
            { "ii–V do novo tom", "preparar com o ii e o V do novo campo", "Gm7–C7 → F7M" },
        }),
        c (
            "O ii–V–I é a ferramenta de modulação mais poderosa: para ir a qualquer tom, toque o ii e o V daquele tom antes de chegar nele. É assim que os standards modulam por toda parte."),
        part ("m10_partitura_turnaround", { "C4", "E4", "G4", "A4", "D5", "F5", "G5", "B4" },
              "Partitura de um turnaround que conecta áreas: ouça como a harmonia prepara a volta ao centro."),

        h ("Modulação no repertório curado"),
        p (
            "No repertório do curso, a modulação aparece em várias formas. 500 Miles High liga duas áreas (Em/Am e Fm/Cm) por movimento de graus conjuntos, sem cadências óbvias — a ligação é cromática, e é o ouvido que a percebe. Spain tem uma introdução em Si menor, uma seção principal que passa por Sol maior e Ré maior e uma seção C que modula e retorna. Incompatibilidade de Gênios usa empréstimo modal e baixos pedalizados para escurecer a harmonia sem sair do centro. Cada caso é uma lição diferente de conexão entre campos."),
        b ("500 Miles High: duas áreas ligadas por cromatismo (movimento por graus conjuntos)."),
        b ("Spain: modulação explícita, com seção C que muda de centro e retorna."),
        b ("Incompatibilidade de Gênios: empréstimo modal e baixos pedalizados, sem modular de fato."),
        aud ({ "E4", "G4", "B4", "D5", "F4", "A4", "C5", "E5" },
             "Duas áreas tonais ligadas: de Em para Fm. Ouça o movimento cromático que conecta os centros."),

        h ("Empréstimo modal: a modulação sem sair de casa"),
        p (
            "Existe uma conexão entre campos que não muda a tonalidade: o empréstimo modal. Você pega um acorde do campo menor paralelo (o campo de Dó menor) e usa dentro do campo maior (Dó maior). O Fm, o Ab7M, o Bb7 e o Cm são empréstimos comuns. Eles não modulam, mas dão à música uma cor emprestada do menor — e são a ferramenta favorita de quem reharmoniza. Em Incompatibilidade de Gênios, os acordes de passagem fazem exatamente isso."),
        tbl ({ "Acorde emprestado", "De onde vem", "Efeito no campo de Dó" }, {
            { "Fm7", "iv do menor paralelo", "escurece o subdominante" },
            { "Ab7M", "VI do menor paralelo", "abre uma cor nova" },
            { "Bb7", "VII do menor paralelo", "som de rock/blues" },
            { "Cm7", "i do menor paralelo", "tônica menor (paralela)" },
        }),
        b ("Empréstimo modal não modula: a tonalidade continua a mesma."),
        b ("Ele pega a cor do campo menor paralelo sem mudar o centro."),
        b ("É uma das ferramentas mais usadas na reharmonização."),
        aud ({ "F3", "A#3", "C4", "D#4" }, "Fm7 emprestado do campo menor paralelo: ouça o escurecimento dentro de Dó maior."),

        h ("Como praticar a conexão entre campos"),
        p (
            "Pratique modular entre dois tons próximos usando o ii–V do novo tom. Comece em Dó, vá para Fá com Gm7–C7–F7M, e volte para Dó com Dm7–G7–C7M. Depois tente tons mais distantes, usando dominantes secundários e substituições. O app ajuda: ele reconhece os acordes que você toca e confere a progressão, então você pode treinar modulações com verificação. A conexão entre campos é, no fim, um exercício de ouvir o momento exato da virada."),
        b ("Modulação próxima: ii–V do novo tom (Gm7–C7 para Fá)."),
        b ("Modulação distante: dominante secundário e substituições de trítono."),
        b ("Empréstimo modal: cor do menor paralelo sem mudar de centro."),
        c (
            "Erro comum: modular sem preparar. Se você simplesmente 'aparece' no novo acorde, a modulação soa abrupta. A preparação (o ii–V do novo tom) é o que faz a virada soar natural."),

        h ("Erros comuns na conexão entre campos"),
        p (
            "O erro mais comum é achar que todo acorde fora do campo é uma modulação. Muitas vezes é só um dominante secundário ou um empréstimo modal, e a música continua no mesmo centro. O segundo erro é preparar mal a modulação, criando um salto brusco. O terceiro é perder o centro de vista: numa música modulante, você precisa saber em qual campo está a cada momento, senão a análise desmorona. Saber onde está o centro é a metade do trabalho."),
        b ("Distinga modulação (muda o centro) de dominante secundário e empréstimo (não muda)."),
        b ("Prepare sempre a modulação com o ii–V do novo tom, quando possível."),
        b ("Mantenha o centro na cabeça: a cada momento, saiba em que campo está."),
        img ("m10_conexao_campos", "Saber qual campo está ativo é o que permite escolher o próximo acorde sem se perder."),

        h ("Modulação por tons vizinhos"),
        p (
            "As modulações mais fáceis são entre tons vizinhos no ciclo das quintas: Dó maior e Sol maior, ou Dó maior e Fá maior. Esses tons compartilham seis das sete notas da escala, então a transição é quase imperceptível. A técnica é simples: você prepara o novo tom com o seu dominante. Para ir de Dó a Sol, toca o D7 (o V de Sol) antes do G7M. Para ir de Dó a Fá, toca o C7 (o V de Fá) antes do F7M. Esse dominante é o 'aviso' que prepara o ouvido para o novo centro."),
        b ("Tons vizinhos: uma diferença de uma quinta (Dó ↔ Sol, Dó ↔ Fá)."),
        b ("Prepare com o dominante do novo tom (D7 para Sol, C7 para Fá)."),
        b ("A transição é quase imperceptível porque os campos se sobrepõem muito."),
        aud ({ "D4", "F4", "A4", "C5", "A3", "C#4", "E4", "G4", "G3", "B3", "D4", "F#4", "C4", "E4", "G4", "B4" },
             "De Dó para Sol e de volta: o D7 prepara o novo centro. Ouça a virada."),

        h ("Modulação para tons distantes"),
        p (
            "Quando os dois tons são distantes (Dó maior e Lá bemol maior, por exemplo), não há notas comuns suficientes para uma transição suave. Nesse caso, você usa duas técnicas. A primeira é a modulação cromática: você desloca o centro meio tom ou um tom de cada vez, por acordes de passagem. A segunda é a modulação por acorde comum — você procura um acorde que exista nos dois campos e o usa como ponte. Os standards modulam para tons distantes o tempo todo, e é por isso que eles soam ricos: a música viaja por vários centros."),
        tbl ({ "Distância", "Técnica", "Exemplo" }, {
            { "vizinha (uma quinta)", "dominante do novo tom", "C7 → F7M" },
            { "duas quintas", "ii–V do novo tom", "Gm7–C7 → F7M" },
            { "distante (trítono)", "acorde comum ou cromática", "C7M → F#7M (cromática)" },
            { "relativa", "mesmo campo", "C7M ↔ Am7" },
        }),
        b ("Tons distantes exigem ponte cromática ou acorde comum."),
        b ("A modulação por acorde comum usa um acorde que existe nos dois campos."),
        b ("Músicas que modulam para longe soam mais ricas."),
        aud ({ "C4", "E4", "G4", "B4", "C#4", "F4", "G#4", "C5", "D4", "F#4", "A4", "C#5" },
             "Modulação cromática: o centro sobe de semitom em semitom. Ouça a viagem."),

        h ("Empréstimo modal: a cor sem a viagem"),
        p (
            "O empréstimo modal é a técnica de pegar acordes do campo menor paralelo sem mudar o centro. Ele não é uma modulação — a tonalidade continua a mesma —, mas dá à música a cor do modo menor. Em Dó maior, você empresta Fm7 (o iv do menor), Ab7M (o VI), Bb7 (o VII) e Cm7 (o i). Esses acordes aparecem o tempo todo na MPB, no samba e no jazz, e são a ferramenta favorita de quem quer escurecer a harmonia sem sair de casa. Incompatibilidade de Gênios usa empréstimo modal em vários pontos."),
        b ("Empréstimo modal não modula: a tonalidade continua."),
        b ("Empresta o iv, o VI, o VII e o i do menor paralelo."),
        b ("Dá a cor do menor sem mudar o centro."),
        aud ({ "C4", "D#4", "G4", "A#4" }, "Cm7 (i do menor paralelo) dentro de Dó maior: a cor escurece, o centro fica."),

        h ("Como identificar o campo ativo"),
        p (
            "Numa música modulante, a habilidade essencial é saber em qual campo você está a cada momento. Os indícios são: o acorde que soa como repouso (a tônica), a presença de um dominante que prepara um novo centro, e o aparecimento de acordes fora do campo anterior. Quando você ouve um V que resolve num acorde que não era a tônica, provavelmente a música modulou. Treinar essa escuta é o que permite tocar uma música modulante sem se perder — e é o que prepara o terreno para reharmonizar criando modulações de propósito."),
        b ("Procure o acorde de repouso: ele indica a tônica do momento."),
        b ("Um dominante que resolve num acorde novo indica modulação."),
        b ("Acordes fora do campo anterior indicam mudança de centro."),
        c (
            "Nos exercícios, o app reconhece os acordes que você toca e confere a progressão. Toque modulações e verifique se o app reconhece a virada de centro."),

        h ("Resumo do tópico"),
        b ("Conectar campos é passar de uma tonalidade a outra sem ruptura."),
        b ("O acorde-pivo é a dobradiça: pertence (ou serve) aos dois campos."),
        b ("A modulação se prepara com o dominante ou o ii–V do novo tom."),
        b ("O empréstimo modal pega a cor do menor paralelo sem mudar de centro."),
        b ("Saber o campo ativo a cada momento é a base da reharmonização modulante."),
        c (
            "Objetivo do tópico: aprender a reconhecer e a construir as pontes entre tonalidades, preparando as viradas para que a música caminhe de um centro a outro com naturalidade."),
    };
}

} // namespace cursomusica::content
