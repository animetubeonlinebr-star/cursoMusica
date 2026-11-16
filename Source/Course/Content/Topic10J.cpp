#include "Course/Content/Topics.h"

// Topic 10J — Relação entre estilos e sonoridades (Módulo 10, Etapa 10).
// Fonte de verdade do texto: docs/MUSIC.md (Etapa 10) e o repertório curado.
namespace cursomusica::content
{

std::vector<ContentItem> topic10J()
{
    return {

        p (
            "A mesma progressão de acordes pode soar completamente diferente conforme o estilo. Um ii–V–I tocado com levada de bossa, com swing de jazz, com shuffle de blues ou com power chords de rock usa os mesmos acordes, mas produz quatro sonoridades distintas. A relação entre estilo e sonoridade é o último assunto da Etapa 10 porque fecha o ciclo: depois de analisar, escolher modos, verticalizar e reharmonizar, você aprende que a sonoridade também vem do estilo — do ritmo, da densidade, das tensões e da forma de tocar."),
        p (
            "Este tópico mostra como o mesmo material harmônico se transforma em linguagens diferentes. Ele ensina a escolher a 'roupa' da harmonia: quais tensões combinar, qual densidade usar, qual ritmo aplicar. É o tópico que liga a harmonia abstrata ao som real, e é a ponte para o repertório — onde todos os conceitos do módulo aparecem em contexto."),
        c (
            "Ideia central: a análise harmônica é a mesma em todos os estilos; o que muda é a sonoridade — o ritmo, a densidade das vozes e as tensões escolhidas."),

        h ("A harmonia não muda; a sonoridade sim"),
        p (
            "Quando você analisa um ii–V–I, a estrutura é a mesma em qualquer estilo: subdominante, dominante, tônica. O que muda é como você o veste. Na bossa nova, você acrescenta nonas e décimas terceiras e toca com levada sincopada; no jazz, você usa substituições e tensões alteradas; no blues, você mantém as sétimas menores e as blue notes; no rock, você reduz tudo a tríades e power chords. A análise identifica a estrutura; o estilo escolhe a roupa."),
        b ("A estrutura (ii–V–I) é a mesma em todos os estilos."),
        b ("O estilo decide as tensões, a densidade e o ritmo."),
        b ("Analisar é identificar a estrutura; tocar é escolher a roupa."),
        img ("m10_estilos", "A mesma progressão em quatro estilos: muda o ritmo, a densidade e as tensões; a análise continua a mesma."),

        h ("Bossa nova: densidade e síncope"),
        p (
            "A bossa nova é o estilo brasileiro que mais explora a densidade harmônica. Ela usa acordes de sétima maior, nona e décima terceira, com baixos que caminham e uma levada sincopada de violão. A sonoridade é suave e conversada, com tensões que não pedem resolução imediata. Só Danço Samba é o exemplo perfeito: o II7 prolongado, as nonas e a síncope criam a 'luz' da bossa. É o estilo em que a reharmonização é mais natural, porque a própria harmonia já é rica."),
        b ("Acordes ricos: sétimas maiores, nonas, décimas terceiras."),
        b ("Levada sincopada: o polegar marca os tempos, os dedos preenchem os contratempos."),
        b ("Tensões suaves, sem resolução imediata."),
        aud ({ "D4", "F#4", "A4", "C5", "E5" }, "Acorde de bossa (com nona): som suave e denso. Ouça a riqueza harmônica."),
        aud ({ "D4", "F4", "A4", "C5", "G4", "B4", "D5", "F5", "C4", "E4", "G4", "B4" },
             "Um ii–V–I com levada de bossa: ouça a síncope e a suavidade."),

        h ("Jazz: substituições e tensões alteradas"),
        p (
            "O jazz usa o mesmo ii–V–I, mas com muito mais recursos: substituições de trítono, dominantes secundários, tensões alteradas (b9, #9, #11, b13) e condução de vozes elaborada. A sonoridade é densa e resolvida, com a tensão sempre resolvendo na hora certa. É o estilo em que as ferramentas do tópico I são mais usadas. Ouvir jazz é ouvir reharmonização em tempo real — a cada ii–V, o músico escolhe entre várias opções."),
        b ("Substituições e dominantes secundários por toda parte."),
        b ("Tensões alteradas: b9, #9, #11, b13."),
        b ("Condução de vozes elaborada, com inversões."),
        aud ({ "D4", "F4", "A4", "C5", "D4", "F4", "G#4", "B4", "C4", "E4", "G4", "B4" },
             "Um ii–V–I de jazz com o V alterado: ouça a tensão e a resolução."),

        h ("Blues: sétimas menores e blue notes"),
        p (
            "O blues é o estilo da tensão não resolvida. Ele usa dominantes com sétima menor em todos os graus, blue notes (a terça menor sobre o acorde maior) e uma levada com swing ou shuffle. A sonoridade é crua e tensa, e a reharmonização no blues costuma ser sutil: acrescentar um #9, trocar um acorde por outro dominante, inserir um turnaround. Equinox e Incompatibilidade de Gênios mostram como o blues se mistura com a música modal e com o samba."),
        b ("Dominantes com sétima menor em todos os graus."),
        b ("Blue notes: a terça menor sobre o acorde maior."),
        b ("Levada com swing ou shuffle."),
        aud ({ "C4", "D#4", "F4", "F#4", "G4", "A#4", "C5" }, "A escala de blues: ouça a blue note (Mi bemol) sobre o acorde de Dó."),

        h ("Rock e pop: tríades e power chords"),
        p (
            "O rock e o pop, em geral, usam menos notas: tríades, power chords (fundamental e quinta) e progressões diretas (I–IV–V, vi–IV–I). A sonoridade é aberta e direta, e a reharmonização acontece mais por empréstimo modal e por acordes de passagem do que por substituições. Ainda assim, o mesmo raciocínio de análise se aplica: um vi–IV–I é o mesmo campo harmônico, vestido com menos notas e mais peso."),
        b ("Menos notas: tríades e power chords (fundamental + quinta)."),
        b ("Progressões diretas: I–IV–V, vi–IV–I."),
        b ("Reharmonização por empréstimo modal e acordes de passagem."),
        aud ({ "C3", "G3", "C4", "G4" }, "Um power chord: só fundamental e quinta. Ouça o som aberto do rock."),

        h ("A mesma progressão em quatro roupas"),
        p (
            "Vamos vestir um ii–V–I (Dm7–G7–C7M) com quatro estilos. Na bossa: acrescente nonas (Dm9, G9, C7M9) e toque com síncope. No jazz: use o V alterado (G7alt) e um subV. No blues: transforme tudo em dominantes (D7–G7–C7) com blue notes. No rock: reduza a tríades (Dm–G–C) ou power chords. A estrutura é a mesma; a sonoridade, quatro vezes diferente. Esse exercício é a síntese do módulo: analisar a estrutura e escolher a roupa."),
        tbl ({ "Estilo", "ii–V–I vestido", "Sensação" }, {
            { "bossa nova", "Dm9–G9–C7M9, síncope", "suave, conversado" },
            { "jazz", "Dm7–Db7–C7M (subV)", "denso, resolvido" },
            { "blues", "D7–G7–C7, blue notes", "cru, tenso" },
            { "rock", "Dm–G–C (tríades)", "direto, aberto" },
        }),
        b ("Mesma estrutura, quatro sonoridades."),
        b ("A roupa vem das tensões, da densidade e do ritmo."),
        b ("Reconhecer a estrutura é o que permite vesti-la de várias formas."),
        aud ({ "D4", "F4", "A4", "C5", "E5" }, "O ii com nona (bossa): ouça a suavidade."),
        aud ({ "D3", "A3", "D4", "A4" }, "O ii como power chord (rock): só fundamental e quinta (D–A). Ouça a diferença de peso."),
        img ("m10_estilos", "Do mesmo ii–V–I nascem quatro sonoridades. O estilo é a roupa; a análise é o corpo."),

        h ("Estilo e reharmonização"),
        p (
            "Cada estilo tem suas convenções de reharmonização. Na bossa, você acrescenta tensões e caminha os baixos; no jazz, substitui e altera; no blues, você insiste nos dominantes e no turnaround; no rock, você empresta do menor paralelo. Conhecer as convenções do estilo evita reharmonizações 'fora de lugar': um subV numa música de rock soa estranho, assim como um power chord numa bossa soa pobre. A ferramenta certa depende do estilo — e o estilo faz parte da análise."),
        b ("Cada estilo tem convenções próprias de reharmonização."),
        b ("Use a ferramenta que combina com o estilo da música."),
        b ("Reharmonizar fora do estilo pode soar deslocado."),
        c (
            "Nos exercícios, o app reconhece os acordes que você toca. Escolha as tensões e a densidade conforme o estilo pedido e verifique se a harmonia está correta — é o treino de vestir a mesma estrutura de várias formas."),

        h ("O repertório como síntese"),
        p (
            "O repertório curado do curso reúne tudo o que o módulo ensinou. Maiden Voyage e Cantaloupe Island são laboratórios de escolha modal; Só Danço Samba e Equinox, de ii–V–I e blues; Incompatibilidade de Gênios, de empréstimo modal e síncope; 500 Miles High e Spain, de modulação e reharmonização. Estudar essas músicas é ver a análise, a verticalização, a reharmonização e a sonoridade trabalhando juntas. É a conclusão natural da Etapa 10: da teoria para a música real."),
        b ("Maiden Voyage / Cantaloupe Island: escolha modal e vamps."),
        b ("Só Danço Samba / Equinox: ii–V–I, dominantes secundários e blues."),
        b ("Incompatibilidade de Gênios: empréstimo modal, síncope e acordes de passagem."),
        b ("500 Miles High / Spain: modulação, áreas distantes e reharmonização."),
        part ("m10_partitura_turnaround", { "C4", "E4", "G4", "B4", "C#4", "E4", "G4", "A4", "D4", "F4", "A4", "C5", "G3", "B3", "D4", "F4" },
              "Partitura de um turnaround de repertório: a harmonia em contexto, pronta para ser vestida em qualquer estilo."),

        h ("Erros comuns na relação entre estilo e sonoridade"),
        p (
            "O erro mais comum é tocar todos os estilos do mesmo jeito, ignorando as convenções. O segundo é exagerar nas tensões num estilo que pede simplicidade (rock) ou simplificar demais num estilo que pede riqueza (bossa). O terceiro é reharmonizar sem considerar o estilo, criando um resultado deslocado. Ouvir muito, de cada estilo, é o que constrói a referência de sonoridade — e é o que permite escolher a roupa certa para cada música."),
        b ("Respeite as convenções de cada estilo."),
        b ("Ajuste a densidade e as tensões ao estilo."),
        b ("Ouvir cada estilo é o que constrói a referência de sonoridade."),
        img ("m10_estilos", "Cada estilo tem sua sonoridade. Ouvir muito é o que permite escolher a roupa certa para cada música."),

        h ("Sonoridade e instrumentação"),
        p (
            "A sonoridade de um estilo também depende da instrumentação e da forma de tocar. O mesmo acorde soa diferente numa guitarra limpa, distorcida, com captador da ponte ou do braço, tocado com palheta ou com os dedos. Na bossa, os dedos e o som limpo definem a leveza; no rock, a distorção e a palheta definem o peso; no jazz, o som encorpado do captador do braço define a calidez. Escolher a sonoridade é escolher como o acorde é produzido — e isso faz parte da 'roupa' da harmonia."),
        tbl ({ "Parâmetro", "Bossa", "Jazz", "Rock" }, {
            { "ataque", "dedos", "palheta/dedos", "palheta" },
            { "timbre", "limpo, suave", "encorpado, quente", "distorcido, brilhante" },
            { "captador", "ponte/misto", "braço", "ponte" },
            { "dinâmica", "suave", "variada", "forte" },
        }),
        b ("A forma de tocar faz parte da sonoridade."),
        b ("Ataque, timbre, captador e dinâmica mudam a mesma harmonia."),
        b ("Escolha a sonoridade conforme o estilo."),
        aud ({ "D4", "F4", "A4", "C5" }, "O mesmo acorde: imagine-o limpo (bossa) e distorcido (rock). A harmonia é a mesma; a sonoridade, não."),

        h ("Aprendendo os estilos pelo ouvido"),
        p (
            "A única forma de dominar as sonoridades é ouvir muito. Escute bossa nova e repare nas tensões e na síncope; escute jazz e repare nas substituições e nas resoluções; escute blues e repare nas blue notes e no swing; escute rock e repare na simplicidade e no peso. Cada estilo tem um vocabulário sonoro que você absorve pela escuta repetida. Depois de ouvir muito, você começa a 'sentir' qual roupa veste cada música — e a escolha deixa de ser teórica e passa a ser instintiva."),
        b ("Ouvir é o único caminho para dominar as sonoridades."),
        b ("Cada estilo tem um vocabulário sonoro próprio."),
        b ("A escuta repetida transforma a escolha em instinto."),
        c (
            "Sugestão de estudo: ouça, de cada estilo, uma música do repertório curado e anote o que você percebe (tensões, ritmo, densidade). Compare as anotações e veja como a mesma estrutura se veste diferente."),

        h ("Reharmonização e estilo"),
        p (
            "Cada estilo aceita certas reharmonizações e rejeita outras. A bossa aceita tensões ricas e baixos caminhantes; o jazz aceita substituições ousadas; o blues aceita alterações sutis nos dominantes; o rock aceita empréstimo modal e acordes de passagem, mas estranha substituições de trítono. Reharmonizar dentro do estilo é o que faz o resultado soar natural; reharmonizar contra o estilo é o que faz soar deslocado. Conhecer as convenções de cada estilo é, portanto, uma ferramenta de reharmonização."),
        b ("Cada estilo aceita um conjunto de reharmonizações."),
        b ("Reharmonizar dentro do estilo soa natural; contra ele, deslocado."),
        b ("Conhecer as convenções é uma ferramenta a mais."),
        img ("m10_estilos", "Cada estilo aceita certas reharmonizações. Escolher a que combina é o que faz o resultado soar natural."),

        h ("Resumo do tópico"),
        b ("A análise harmônica é a mesma em todos os estilos; a sonoridade é que muda."),
        b ("Bossa: densidade e síncope. Jazz: substituições e alterações. Blues: dominantes e blue notes. Rock: tríades e power chords."),
        b ("A mesma progressão pode ser vestida de quatro formas diferentes."),
        b ("Cada estilo tem convenções próprias de reharmonização."),
        b ("O repertório curado reúne todos os conceitos do módulo em contexto real."),
        c (
            "Objetivo do tópico: fechar a Etapa 10 ligando a harmonia abstrata ao som real. Analisar, escolher, verticalizar e reharmonizar — tudo isso ganha sentido quando vestido com a sonoridade do estilo."),
    };
}

} // namespace cursomusica::content
