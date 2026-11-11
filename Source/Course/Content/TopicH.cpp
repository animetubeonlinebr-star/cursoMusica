#include "Course/Content/Topics.h"

// Topic H — Introdução ao cifrado.
// Sources: pdf-mozart-mello-livroestudosdeguitarra4em1 and the chord-quality
// vocabulary of pdf-desvendando-os-segredos-da-guitarra-fusion (tríades,
// tétrades).
namespace cursomusica::content
{

std::vector<ContentItem> topicH()
{
    return {
        p ("Cifra é a forma escrita de dizer qual acorde tocar, de maneira "
           "compacta. Em vez de desenhar o acorde na pauta, escrevemos um símbolo "
           "como C, Am ou G7. Praticamente toda música popular — de MPB a rock, "
           "de samba a gospel — circula em cifras. Saber ler cifras é o que "
           "permite acompanhar uma música que você nunca viu, e é a ponte entre a "
           "teoria (tópicos B a G) e a prática no braço."),

        h ("Por que a cifra existe"),
        p ("A partitura é precisa, mas lenta de ler e escrever para quem só quer "
           "acompanhar. A cifra resolve isso: com poucos caracteres, ela diz o "
           "acorde, sua qualidade e até as notas que o compõem. É um sistema "
           "prático, criado para músicos populares que precisam aprender e "
           "transmitir músicas rapidamente."),
        b ("Praticidade: uma música inteira cabe em uma folha, com os acordes "
           "acima da letra."),
        b ("Flexibilidade: a cifra não fixa a posição no braço; você escolhe onde "
           "tocar (e é aí que o CAGED ajuda)."),
        b ("Universalidade: o mesmo sistema vale para guitarra, violão, teclado, "
           "baixo e voz."),
        c ("A cifra não substitui o ouvido nem o ritmo. Ela diz quais acordes "
           "tocar, mas o \"como\" (ritmo, intensidade, região do braço) é decisão "
           "sua."),

        h ("A letra da nota: de onde vem o nome do acorde"),
        p ("O nome de um acorde vem da sua nota fundamental — a nota que dá nome "
           "ao acorde. Na cifra, usamos as letras anglo-saxônicas: A = Lá, B = Si, "
           "C = Dó, D = Ré, E = Mi, F = Fá, G = Sol. Se você já fixou o tópico B, "
           "já conhece essa correspondência."),
        tbl ({ "Cifra", "Nome em português", "Observação" },
             { { "C", "Dó maior", "acorde maior" },
               { "D", "Ré maior", "acorde maior" },
               { "E", "Mi maior", "acorde maior" },
               { "F", "Fá maior", "acorde maior" },
               { "G", "Sol maior", "acorde maior" },
               { "A", "Lá maior", "acorde maior" },
               { "B", "Si maior", "acorde maior" } }),
        p ("Quando não há nenhum símbolo depois da letra, o acorde é maior. "
           "Assim, C significa Dó maior e G significa Sol maior. Os acidentes "
           "aparecem normalmente: F♯ é Fá sustenido maior, B♭ é Si bemol maior."),
        c ("Em português, algumas cifras aparecem com H para Si bemol (herança "
           "alemã), mas o padrão internacional usa B♭. No Brasil, usamos B para Si "
           "e B♭ para Si bemol, seguindo o padrão anglo-saxônico."),

        h ("Qualidades do acorde: maior, menor e as sétimas"),
        p ("Depois da letra, os símbolos indicam a qualidade do acorde. A "
           "qualidade diz quais notas, além da fundamental, formam o acorde. "
           "Vamos das mais simples às mais complexas."),
        tbl ({ "Símbolo", "Significado", "Exemplo", "Em português" },
             { { "C", "acorde maior", "C", "Dó maior" },
               { "Cm", "acorde menor", "Cm", "Dó menor" },
               { "C7", "sétima dominante", "C7", "Dó com sétima menor" },
               { "C7M / Cmaj7", "sétima maior", "C7M", "Dó com sétima maior" },
               { "Cm7", "menor com sétima", "Cm7", "Dó menor com sétima" },
               { "Cdim / C°", "diminuto", "Cdim", "Dó diminuto" },
               { "Caug / C+", "aumentado", "Caug", "Dó aumentado" },
               { "Csus4 / Csus", "suspenso (quarta no lugar da terça)", "Csus4",
                 "Dó com quarta" } }),
        p ("A diferença entre maior e menor está na terça: o acorde maior tem a "
           "terça maior (quatro semitons acima da fundamental); o menor tem a "
           "terça menor (três semitons). É esse semitom de diferença que muda "
           "completamente o caráter do acorde — de alegre/estável para "
           "melancólico/tenso."),
        p ("A sétima acrescenta uma quarta nota ao acorde. A sétima dominante "
           "(7) é a mais comum no blues e no rock; a sétima maior (7M) aparece "
           "muito na bossa nova e no jazz; a menor com sétima (m7) é comum em "
           "baladas e soul."),
        c ("Regra de leitura: leia a letra (fundamental), depois a qualidade "
           "(maior/menor/diminuto), depois os números (7, 9, 11, 13). Cada parte "
           "acrescenta informação."),

        h ("Tensões e notas adicionadas"),
        p ("Além das sétimas, a cifra pode indicar tensões: notas acrescentadas "
           "que dão cor ao acorde. As tensões mais comuns são a nona (9), a "
           "décima primeira (11) e a décima terceira (13), além de alterações "
           "como ♯ (aumentada) e ♭ (diminuída)."),
        tbl ({ "Símbolo", "Significado", "Efeito sonoro" },
             { { "C(9) / Cadd9", "nona acrescentada", "som mais aberto e moderno" },
               { "C7(9)", "sétima com nona", "típico do funk e do soul" },
               { "C(#11)", "quarta aumentada", "tensão jazzy" },
               { "C6", "sexta no lugar da sétima", "som suave e estável" },
               { "Cm7(9)", "menor com sétima e nona", "balada, soul" },
               { "C7(♭9)", "sétima com nona menor", "tensão forte, som espanhol" } }),
        p ("Para o iniciante, não é preciso dominar todas as tensões agora. O "
           "importante é reconhecer que os números e alterações informam notas "
           "extra — e que esses acordes são variações coloridas do acorde básico."),
        c ("Curiosidade: quando você vê C7(9), está diante de um acorde de "
           "funk/soul por excelência. É o famoso \"acorde de guitarra do "
           "Earth, Wind & Fire\". Só de ler a cifra, você já sabe o caráter."),

        h ("Baixo invertido: a barra (/)"),
        p ("Quando a cifra tem uma barra, o que vem depois indica a nota que deve "
           "estar no baixo. Isso se chama inversão. C/E significa: acorde de Dó "
           "maior, mas com o Mi (E) no baixo, em vez do Dó."),
        tbl ({ "Cifra", "Leitura", "Uso típico" },
             { { "C/E", "Dó maior com Mi no baixo", "criar movimento descendente" },
               { "G/B", "Sol maior com Si no baixo", "conectar acordes suavemente" },
               { "Am7/G", "Lá menor com Sol no baixo", "baixo melódico" },
               { "F/A", "Fá maior com Lá no baixo", "transição" } }),
        p ("As inversões servem para criar linhas de baixo mais interessantes. Em "
           "vez de pular de C para G com o baixo saltando, você passa por C/E e "
           "G/B, criando uma linha suave de baixo (Dó–Mi, Sol–Si). Isso é "
           "onipresente na MPB e no pop."),
        c ("No braço, a nota após a barra costuma ser a nota mais grave do "
           "acorde. Ao ver C/E, procure uma forma de Dó em que a corda mais grave "
           "soando seja o Mi."),

        h ("Lendo uma cifra no contexto"),
        p ("Uma folha de cifra traz os acordes escritos acima da letra da música. "
           "Sua tarefa é tocar o acorde no tempo certo, seguindo o ritmo da "
           "música. Alguns símbolos adicionais aparecem nesse contexto."),
        b ("Barra de compasso (|): separa os compassos. Você troca de acorde "
           "geralmente a cada barra."),
        b ("Repetição (x2, x4): indica quantas vezes repetir uma passagem."),
        b ("Símbolos de ritmo (às vezes desenhados): indicam a levada a tocar."),
        b ("Indicações de seção (Intro, Refrão, Ponte): organizam a forma da "
           "música."),
        c ("Dica: comece lendo cifras de músicas lentas e simples, com poucos "
           "acordes. A fluência de leitura vem com a prática, como ler um idioma."),

        h ("Como encontrar o acorde no braço a partir da cifra"),
        p ("Saber ler a cifra é metade do trabalho; a outra metade é achar o "
           "acorde no instrumento. Aqui entra tudo o que você aprendeu: as notas "
           "no braço (tópico D), a pestana (tópico E) e o CAGED (tópico F)."),
        b ("Passo 1: identifique a fundamental (a letra) e sua qualidade (maior, "
           "menor, etc.)."),
        b ("Passo 2: escolha uma forma do CAGED para essa fundamental."),
        b ("Passo 3: ajuste a forma para a qualidade (menor, sétima)."),
        b ("Passo 4: se houver barra (inversão), ajuste o baixo para a nota "
           "indicada."),
        p ("Exemplo com Dm7: fundamental Ré (D), qualidade menor (m), com sétima "
           "(7). Você procura a forma de Ré menor com sétima — pode ser na "
           "primeira posição (forma de D) ou em qualquer região com pestana "
           "(forma de A, E, etc.)."),
        c ("Esse fluxo — ler a cifra, identificar fundamental e qualidade, achar "
           "a forma no braço — é a habilidade prática central do módulo. Com ele, "
           "você toca qualquer música escrita em cifra."),

        h ("Erros comuns ao ler cifras"),
        p ("Alguns enganos são frequentes no início. Conhecê-los evita confusão."),
        b ("Confundir B com Si bemol. No padrão que usamos, B é Si natural; Si "
           "bemol é B♭."),
        b ("Achar que \"m\" é minúsculo mas \"M\" é maior: em muitas cifras, m = "
           "menor e M (ou maj) = maior. Cuidado com a diferença: Cm7 (menor com "
           "sétima) e C7M (sétima maior) são acordes bem diferentes."),
        b ("Ignorar a barra (inversão). C/E não é a mesma coisa que C."),
        b ("Tocar sempre na primeira posição. Muitas cifras ficam mais fáceis em "
           "outra região do braço."),
        c ("Regra de ouro: leia a cifra em partes — fundamental, qualidade, "
           "extensões, baixo. Lendo devagar e por partes, você não erra."),

        h ("Cifra x partitura: quando usar cada uma"),
        p ("Cifra e partitura não competem: são ferramentas para finalidades "
           "diferentes. Saber quando usar cada uma faz parte de ser um músico "
           "completo."),
        tbl ({ "Aspecto", "Cifra", "Partitura" },
             { { "O que informa", "qual acorde tocar", "exatamente cada nota" },
               { "Leitura", "rápida, por símbolos", "detalhada, nota a nota" },
               { "Uso típico", "acompanhamento, música popular",
                 "melodia, arranjo, música escrita" },
               { "Liberdade", "alta (você escolhe a posição)", "baixa (nota fixa)" },
               { "Ritmo", "indicado à parte", "escrito com precisão" } }),
        p ("Na prática, muitos músicos usam as duas: a cifra para os acordes e a "
           "partitura (ou tablatura) para a melodia. Entender a cifra é essencial "
           "para quem quer tocar música popular; a partitura é essencial para "
           "quem quer ler arranjos e estudar formalmente."),
        c ("Neste módulo, o foco é a cifra, porque é a linguagem da música "
           "popular e a que você mais vai usar para acompanhar e tocar. A leitura "
           "de partitura é aprofundada em módulos posteriores."),

        h ("Tablatura: a terceira forma de escrever"),
        p ("Além da cifra e da partitura, existe a tablatura (tab), muito usada "
           "para guitarra. Ela mostra exatamente onde colocar os dedos: cada linha "
           "representa uma corda, e os números indicam as casas."),
        tbl ({ "Linha da tab", "Corda representada" },
             { { "linha de cima", "1ª corda (mais aguda)" },
               { "linha 2", "2ª corda" },
               { "linha 3", "3ª corda" },
               { "linha 4", "4ª corda" },
               { "linha 5", "5ª corda" },
               { "linha de baixo", "6ª corda (mais grave)" } }),
        p ("A tablatura resolve a dúvida de \"onde tocar\", mas não diz a duração "
           "das notas nem o ritmo — por isso costuma vir acompanhada de cifra ou "
           "de indicação de ritmo. Muitos materiais de guitarra usam as três "
           "formas juntas: cifra para os acordes, tab para os dedos e partitura "
           "para o ritmo."),
        c ("Comparação rápida: cifra diz \"qual acorde\"; tablatura diz \"onde "
           "colocar os dedos\"; partitura diz \"exatamente o que soa e por quanto "
           "tempo\". Cada uma responde a uma pergunta diferente."),

        h ("Resumo do tópico H"),
        tbl ({ "Ideia", "O que fixar" },
             { { "Fundamental", "letra = nota que dá nome (C = Dó)" },
               { "Maior", "letra sem símbolo (C = Dó maior)" },
               { "Menor", "símbolo m (Cm = Dó menor)" },
               { "Sétimas", "7 (dominante), 7M (maior), m7 (menor com sétima)" },
               { "Tensões", "9, 11, 13, ♯, ♭ acrescentam notas" },
               { "Inversão", "C/E = Dó com Mi no baixo" },
               { "Prática", "ler a cifra e achar a forma no braço (CAGED)" } }),

        h ("Como estudar o tópico H na prática"),
        p ("Cifra se aprende lendo cifras reais. Escolha músicas simples e vá "
           "aumentando a dificuldade."),
        b ("Pegue uma música de três ou quatro acordes e toque acompanhando a "
           "letra."),
        b ("Para cada acorde, diga em voz alta: fundamental, qualidade, extensão."),
        b ("Pratique acordes com inversão (C/E, G/B) e ouça a diferença do baixo."),
        b ("Leia a cifra de uma música desconhecida e tente tocá-la de primeira, "
           "sem estudar antes."),
        b ("Transcreva para cifra uma música que você saiba tocar de ouvido."),
        c ("Meta do tópico: ler qualquer cifra de acorde simples (maior, menor, "
           "sétima, inversão) e encontrar a forma no braço sem hesitar. Isso "
           "fecha a ligação entre teoria e prática no módulo 1."),
    };
}

} // namespace cursomusica::content
