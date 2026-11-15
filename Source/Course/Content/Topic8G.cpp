#include "Course/Content/Topics.h"

// Topic 8G — Dilatação do campo harmônico maior (Módulo 8, Etapa 8).
// Fonte de verdade do texto: docs/MUSIC.md §8 (bloco G).
namespace cursomusica::content
{

std::vector<ContentItem> topic8G()
{
    return {

        p (
            "O campo harmônico maior, sozinho, tem apenas sete acordes. Mas a música real usa muito mais. A esse processo de ampliar o campo harmônico chamamos dilatação: o campo deixa de ser um conjunto fechado de sete acordes e passa a ser um sistema aberto, no qual dominantes secundários, SubV7, SubIIm e empréstimos modais se somam ao material original. Este tópico reúne tudo o que você estudou até aqui num mapa único."),
        p (
            "Entender a dilatação é entender por que a música popular e o jazz soam tão ricos. Não se trata de decorar centenas de acordes, mas de compreender como cada acorde novo se relaciona com os sete originais. Todo acorde do sistema dilatado tem uma função: ou é um dominante apontando para algum grau, ou é um empréstimo de outro modo, ou é uma substituição de um acorde do campo."),
        c (
            "Objetivo do tópico: compreender como o campo harmônico maior se dilata, quais acordes se acrescentam e como eles se organizam em funções."),

        h ("O campo original e as três funções"),
        p (
            "O campo harmônico maior de Dó tem sete acordes: CM7, Dm7, Em7, FM7, G7, Am7 e Bm7b5. Cada um exerce uma das três funções básicas: tônica (I, III, VI), subdominante (II, IV) e dominante (V, VII). A dilatação acontece quando acrescentamos acordes que exercem essas mesmas funções, mas com cores novas."),
        b ("Tônica: CM7, Em7, Am7 (repouso)."),
        b ("Subdominante: Dm7, FM7 (preparação)."),
        b ("Dominante: G7, Bm7b5 (tensão)."),
        img ("m8_dilatacao_maior", "O campo maior dilatado: em volta do I gravitam dominantes, substituições e empréstimos."),

        h ("A dilatação pelos dominantes secundários"),
        p (
            "O primeiro grupo de acordes que se acrescenta vem dos dominantes secundários. Cada grau recebe o seu próprio V7, e assim o campo ganha cinco acordes novos (A7, B7, C7, D7, E7). Esses dominantes apontam para os graus do campo, criando pequenos movimentos internos. Eles não mudam o tom, mas enriquecem enormemente a harmonia."),
        b ("A7 (V7/ii): aponta para Dm."),
        b ("D7 (V7/V): aponta para G."),
        b ("E7 (V7/vi): aponta para Am."),
        b ("B7 (V7/iii) e C7 (V7/IV): apontam para Em e F."),
        tbl ({ "Função original", "Acordes do campo", "Dilatação" }, {
            { "Tônica", "CM7, Em7, Am7", "Am7 com dominante E7" },
            { "Subdominante", "Dm7, FM7", "Dm7 com dominante A7; FM7 com dominante C7" },
            { "Dominante", "G7, Bm7b5", "G7 com dominante D7" },
        }),

        h ("A dilatação pelas substituições"),
        p (
            "O segundo grupo vem das substituições. Cada dominante pode ser trocado pelo seu SubV7, e cada ii pode ser trocado pelo SubIIm. Assim, o campo ganha mais acordes: em vez de apenas G7 como dominante de Dó, temos também Db7 (SubV7). Em vez de apenas Dm7 como ii, temos também Dm7b5 (SubIIm). As substituições multiplicam as possibilidades."),
        b ("G7 pode virar Db7 (SubV7)."),
        b ("Dm7 pode virar Dm7b5 (SubIIm)."),
        b ("Cada dominante tem o seu SubV7 a um trítono de distância."),
        aud ({ "C#3", "F3", "G#3", "B3", "C4", "E4", "G4" },
             "Db7 → C: a dilatação pelo SubV7, com o baixo descendo meio-tom."),

        h ("A dilatação pelos empréstimos modais"),
        p (
            "O terceiro grupo vem do modo paralelo. Do campo de Dó menor, o campo de Dó maior empresta o Cm, o Fm7, o Ab7M, o Bb7 e o Eb7M. Esses acordes acrescentam cores que o campo maior não tem, com notas bemóis que criam tensão e dramaticidade. Eles completam a dilatação, ligando o maior ao menor paralelo."),
        b ("Cm, Fm7, Ab7M, Bb7, Eb7M: empréstimos do menor paralelo."),
        b ("Cada um introduz uma ou duas notas bemóis."),
        b ("São usados para cor e drama, não para mudar o tom."),

        h ("O mapa completo das funções"),
        p (
            "Reunindo tudo, o campo harmônico maior dilatado de Dó tem as seguintes funções. Na tônica: CM7, Em7, Am7, e também os empréstimos Cm, Eb7M. Na subdominante: Dm7, FM7, Dm7b5 (SubIIm), Fm7 (iv menor), e os dominantes A7 (V7/ii) e C7 (V7/IV). No dominante: G7, Bm7b5, Db7 (SubV7), D7 (V7/V), Ab7M e Bb7 (empréstimos de cor). Esse é o vocabulário completo do campo maior."),
        tbl ({ "Função", "Acordes", "Origem" }, {
            { "Tônica", "CM7, Em7, Am7", "campo maior" },
            { "Tônica", "Cm, Eb7M", "empréstimo modal" },
            { "Subdominante", "Dm7, FM7", "campo maior" },
            { "Subdominante", "Dm7b5, Fm7", "SubIIm / iv menor" },
            { "Subdominante", "A7, C7", "dominantes secundários" },
            { "Dominante", "G7, Bm7b5", "campo maior" },
            { "Dominante", "Db7, D7", "SubV7 / V7/V" },
            { "Dominante", "Ab7M, Bb7", "empréstimos de cor" },
        }),

        h ("Como usar o mapa"),
        p (
            "O mapa não serve para decorar, mas para escolher. Diante de um acorde do campo, você pode perguntar: qual outra opção exerce a mesma função? Se o acorde é G7 (dominante), você pode trocá-lo por Db7 (SubV7) ou prepará-lo com D7 (V7/V). Se é Dm7 (subdominante), você pode trocá-lo por Dm7b5 (SubIIm) ou por Fm7 (iv menor). A dilatação é, na prática, um repertório de escolhas."),
        b ("Pergunte qual é a função do acorde."),
        b ("Procure no mapa outros acordes com a mesma função."),
        b ("Escolha a cor que combina com o trecho."),
        c (
            "Regra prática: comece trocando um acorde por vez. Substituir tudo de uma vez descaracteriza a música."),

        h ("Dilatação e reharmonização"),
        p (
            "A dilatação do campo é a base da reharmonização, que você verá em módulos avançados. Reharmonizar é trocar os acordes de uma música mantendo a melodia, usando o mapa dilatado como fonte de opções. Quanto melhor você conhece o mapa, mais liberdade tem para reharmonizar sem perder o sentido da música."),
        b ("Reharmonizar é trocar acordes mantendo a melodia."),
        b ("As opções vêm do campo dilatado."),
        b ("O bom gosto está em preservar a função e a melodia."),

        h ("Erros comuns"),
        p (
            "O erro mais comum é usar todos os acordes do mapa de uma vez, o que torna a música confusa. A dilatação é um recurso, não uma obrigação. Outro erro é perder a função de vista: se um acorde deixa de exercer a sua função, a música perde o sentido. A dilatação deve sempre respeitar a lógica funcional."),
        b ("Não use todas as substituições ao mesmo tempo."),
        b ("Mantenha a função de cada acorde."),
        b ("A melodia precisa continuar fazendo sentido."),
        c (
            "Dica: escreva a função acima de cada acorde antes de substituir. Ver a função ajuda a escolher a substituição certa."),

        h ("Aplicação prática"),
        p (
            "Pegue uma progressão simples, como C → Am → Dm → G7 → C, e reharmonize-a usando o mapa. Troque o G7 por Db7, o Dm7 por Dm7b5, acrescente um D7 antes do G7. Depois toque e escute o resultado. No instrumento, cada escolha exige uma digitação; use o app para conferir se os acordes que você toca estão corretos."),
        b ("Escreva a progressão original e as funções."),
        b ("Substitua um acorde por vez usando o mapa."),
        b ("Toque e compare as versões."),
        part ("m8_partitura_ii_v_i", { "D3", "F3", "A3", "C4", "G3", "B3", "D4", "F4", "C4", "E4", "G4" },
              "Partitura do II-V-I maior, a célula que a dilatação amplia. Ouça o que está escrito."),

        h ("A dilatação em outras tonalidades"),
        p (
            "A dilatação do campo maior vale para qualquer tonalidade. Em Sol maior, os dominantes secundários são E7 (V7/ii), F#7 (V7/iii), G7 (V7/IV), A7 (V7/V) e B7 (V7/vi); o SubV7 é Ab7; o SubIIm é Am7b5. O mapa se desloca com a tonalidade, mantendo as mesmas relações. Aprender a dilatação em várias tonalidades torna o vocabulário transportável."),
        b ("Em Dó maior: A7, B7, C7, D7, E7; SubV7 = Db7; SubIIm = Dm7b5."),
        b ("Em Sol maior: E7, F#7, G7, A7, B7; SubV7 = Ab7; SubIIm = Am7b5."),
        b ("As relações são as mesmas; só mudam as notas."),
        tbl ({ "Tonalidade", "V7/V", "SubV7", "SubIIm" }, {
            { "Dó maior", "D7", "Db7", "Dm7b5" },
            { "Sol maior", "A7", "Ab7", "Am7b5" },
            { "Fá maior", "G7", "Gb7", "Gm7b5" },
        }),

        h ("Dilatação na guitarra"),
        p (
            "No instrumento, a dilatação significa ter várias opções para cada acorde. Diante de um G7, você pode tocar Db7 (SubV7), prepará-lo com D7 (V7/V), ou simplesmente acrescentar uma tensão (G7b9). Cada opção tem a sua digitação, e conhecer várias delas dá liberdade para acompanhar. Praticar as substituições em várias tonalidades é o caminho."),
        b ("Pratique o II-V-I e troque o V7 pelo SubV7."),
        b ("Acrescente dominantes secundários antes dos graus."),
        b ("Experimente empréstimos para variar a cor."),
        aud ({ "D3", "F3", "A3", "C4", "D3", "F#3", "A3", "C4", "G3", "B3", "D4", "F4", "C4", "E4", "G4" },
             "Dm7 → D7 → G7 → C: o V7/V dilatando a cadência antes da resolução."),

        h ("Dilatação e o ouvido"),
        p (
            "A dilatação do campo é, acima de tudo, uma forma de organizar o ouvido. Cada acorde novo tem uma função clara, e o ouvido aprende a esperar o que vem depois. Quanto mais você pratica, mais natural fica reconhecer as funções e prever as resoluções. É isso que permite tocar de ouvido com segurança, mesmo em músicas que você nunca viu."),
        b ("Cada acorde dilatado tem uma função."),
        b ("O ouvido aprende a prever a resolução."),
        b ("Prever a resolução é a base do acompanhamento de ouvido."),

        h ("Dilatação e o blues"),
        p (
            "O blues é um exemplo extremo de dilatação: no blues de Dó, todos os acordes são dominantes (C7, F7, G7), mesmo o I. Isso significa que o campo do blues é feito inteiramente de dominantes, e as resoluções não seguem a lógica funcional tradicional. O blues mostra que a dilatação pode ir além do campo maior e criar um sistema próprio, com regras próprias."),
        b ("Blues de Dó: C7, F7, G7 — todos dominantes."),
        b ("A dilatação do blues cria um campo próprio."),
        b ("O blues é o laboratório do dominante."),
        aud ({ "C3", "E3", "G3", "A#3", "F3", "A3", "C4", "D#4", "G3", "B3", "D4", "F4" },
             "C7 → F7 → G7: o campo dilatado do blues, todo em dominantes."),

        h ("Dilatação e o jazz"),
        p (
            "No jazz, a dilatação é levada ao extremo: quase todo acorde pode ser precedido por um dominante e substituído pelo seu SubV7. Um standard típico tem dominantes secundários em quase todos os graus, substituições por trítono e empréstimos modais. Entender a dilatação é a chave para tocar jazz, porque é ela que explica a densidade harmônica do gênero."),
        b ("Jazz: dominantes em quase todos os graus."),
        b ("Substituições por trítono são a norma."),
        b ("A dilatação explica a densidade harmônica."),

        h ("Resumo do tópico"),
        b ("Dilatar o campo é acrescentar acordes às três funções básicas."),
        b ("Os dominantes secundários apontam para os graus do campo."),
        b ("As substituições (SubV7, SubIIm) trocam acordes do campo."),
        b ("Os empréstimos modais acrescentam cores do modo paralelo."),
        b ("O mapa dilatado é a base da reharmonização."),
        c (
            "Nos exercícios deste tópico, toque os acordes do campo dilatado e confira com o app. Ele reconhece as notas e verifica se o acorde montado corresponde ao pedido."),
    };
}

} // namespace cursomusica::content
