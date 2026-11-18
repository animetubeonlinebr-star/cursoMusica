#include "Course/Content/Topics.h"

// Topic 11H — Escala menor harmônica (Módulo 11, Etapa 11).
namespace cursomusica::content
{

std::vector<ContentItem> topic11H()
{
    return {

        p (
            "A escala menor harmônica é a escala menor que você já conhece com uma única mudança decisiva: o sétimo grau sobe. Essa nota elevada cria uma segunda aumentada — um intervalo de som exótico — e, ao mesmo tempo, dá à escala uma dominante de verdade. Por isso ela é a escala menor do fraseado clássico, do rock neoclássico e do metal."),
        p (
            "Você já viu a menor harmônica no Módulo 6, dentro dos campos harmônicos menores. Aqui ela volta como ferramenta de fraseado: uma escala que dá à frase menor um caráter dramático e uma resolução forte. Aprender o seu desenho e a sua nota característica é o que permite usá-la para improvisar."),
        c (
            "Menor harmônica = menor natural com o 7º grau elevado. Em Lá: A-B-C-D-E-F-G#-A. A nota nova (G#) cria a segunda aumentada (F-G#) e transforma a escala numa dominante pronta para resolver."),

        h ("A nota que muda tudo"),
        p (
            "A menor natural tem a sétima menor (em Lá, o Sol). A menor harmônica eleva essa sétima para a sétima maior (Sol#). Essa única mudança faz duas coisas ao mesmo tempo: cria o intervalo de segunda aumentada entre o sexto grau (Fá) e o sétimo elevado (Sol#), e constrói, no quinto grau, um acorde de dominante. A escala deixa de ser apenas menor e passa a ter uma força de resolução que a menor natural não tem."),
        p (
            "A segunda aumentada é a marca sonora da menor harmônica. É o intervalo de três semitons entre o Fá e o Sol# — um salto que soa oriental e dramático. No fraseado, ele é usado como gesto: você toca a segunda aumentada quando quer tensão e resolve logo em seguida na tônica."),
        b ("A menor harmônica eleva o 7º grau (em Lá: Sol vira Sol#)."),
        b ("A elevação cria a segunda aumentada entre o 6º e o 7º graus."),
        b ("O 5º grau vira um acorde de dominante com força de resolução."),
        b ("A segunda aumentada é o gesto de tensão característico da escala."),
        img ("m11_menor_harmonica", "Escala menor harmônica: a menor natural com o 7º grau elevado. A segunda aumentada (F-G#) é a sua marca sonora."),

        h ("Onde a menor harmônica fraseia"),
        p (
            "A menor harmônica aparece em três grandes territórios. No clássico e no neoclássico, como base das cadências menores e das escalas de velocidade — é a escala dos grandes violinistas adaptada à guitarra. No metal, como a cor dramática de riffs e solos. E no jazz, sobre o acorde menor com sétima maior (m7M) e sobre o dominante alterado que resolve no menor."),
        p (
            "Cada território explora uma parte da escala. O neoclássico explora a velocidade e a segunda aumentada como gesto; o metal explora o peso da dominante; o jazz explora os modos derivados dela. Aprender o desenho base dá acesso a todos eles."),
        tbl ({ "Grau", "Nota em Lá", "Função na frase" }, {
            { "1", "A", "tônica — repouso" },
            { "b3", "C", "terça menor — cor" },
            { "4", "D", "subdominante" },
            { "5", "E", "dominante" },
            { "b6", "F", "sexta menor — tensão" },
            { "7", "G#", "sétima elevada — puxa para a tônica" },
        }),
        c (
            "Repouso × tensão: em Lá menor harmônica, A-C-E são repouso; o G# é tensão que resolve na tônica; o Fá (b6) é tensão de cor. O exercício deste tópico reconhece essas notas e cobra que a tensão seja resolvida."),

        h ("O lick deste tópico"),
        p (
            "O lick abaixo sobe a menor harmônica de Lá e destaca a segunda aumentada (Fá–Sol#) antes de resolver na tônica. É um gesto de neoclássico, na linha de Yngwie Malmsteen — a escala menor harmônica usada como sequência de velocidade com a segunda aumentada como ponto de tensão. Ouça o caráter dramático da nota elevada."),
        aud ({ "A4", "B4", "C5", "D5", "E5", "F5", "G#5", "A5", "G#5", "F5", "E5", "D5", "C5", "B4", "A4" },
             "Lick do tópico H: menor harmônica de Lá. A segunda aumentada (F–G#) marca a tensão; a frase resolve na tônica."),
        part ("m11_partitura_h", { "A4", "B4", "C5", "D5", "E5", "F5", "G#5", "A5", "G#5", "F5", "E5", "D5", "C5", "B4", "A4" },
              "Partitura do lick H: escala menor harmônica ascendente e descendente. A sétima elevada (Sol#) é a nota característica."),

        h ("Estudar a menor harmônica"),
        p (
            "Toque a escala devagar, isolando a segunda aumentada: toque Fá e Sol# como um par, repetidas vezes, até o intervalo soar familiar. Depois toque a escala inteira nos dois sentidos, sempre destacando a sétima elevada. No fim, improvise sobre um acorde menor resolvendo sempre com a segunda aumentada na tônica."),

        h ("A segunda aumentada como gesto"),
        p (
            "A segunda aumentada da menor harmônica não é um defeito a corrigir: é um recurso expressivo. O salto de três semitons entre o sexto e o sétimo graus tem um som dramático e reconhecível, usado há séculos na música clássica e, mais tarde, no rock neoclássico. Saber tocar e resolver esse intervalo é o que dá à frase menor o seu caráter."),
        p (
            "No fraseado, a segunda aumentada funciona como um gesto de tensão. Você toca o sexto grau, salta para o sétimo elevado e resolve na tônica. O salto é o momento de drama; a resolução é o alívio. Usada com moderação, a segunda aumentada dá personalidade à frase; usada em excesso, ela soa exótica demais. O equilíbrio é a chave."),
        b ("A segunda aumentada (F–G# em Lá) é a marca sonora da escala."),
        b ("Ela funciona como gesto de tensão que resolve na tônica."),
        b ("Usada com moderação, dá caráter; em excesso, soa exótica."),
        tbl ({ "Uso", "Onde aparece", "Efeito" }, {
            { "Clássico / neoclássico", "cadências menores, escalas de velocidade", "drama e virtuosismo" },
            { "Metal", "riffs e solos", "peso e tensão" },
            { "Jazz", "sobre m7M e dominante alterado", "cor e resolução" },
        }),

        h ("O dominante da menor harmônica"),
        p (
            "Elevar o sétimo grau tem uma consequência harmônica importante: o quinto grau da escala vira um acorde de dominante de verdade. Em Lá menor harmônica, o Mi (5º grau) forma o E7, com a sensível (Sol#) que puxa para a tônica. É esse dominante que dá à cadência menor a sua força de resolução — a mesma força que a menor natural não tem, porque nela falta a sensível."),
        p (
            "É por isso que a menor harmônica é a escala da música menor tonal. Sem a sétima elevada, não há dominante, e sem dominante, não há a cadência que resolve. A menor harmônica dá ao modo menor a tensão necessária para que a tônica seja um repouso de verdade. No fraseado, isso significa que a sétima elevada é a nota que prepara a chegada."),
        c (
            "Comparação útil: toque a menor natural e a menor harmônica seguidas. Ouça como a harmônica soa \"mais tensa\" — é o Sol# pedindo o Lá. Essa tensão é o motor da frase menor tonal."),

        h ("Aplicando a menor harmônica"),
        p (
            "No rock neoclássico, a menor harmônica é tocada em sequências rápidas, com destaque para a segunda aumentada. No metal, ela aparece em riffs e solos de caráter sombrio. No jazz, ela é usada sobre o acorde menor com sétima maior e sobre o dominante alterado que resolve no menor. Cada estilo explora uma faceta diferente da mesma escala."),
        p (
            "Para o aluno deste módulo, o objetivo é ter a menor harmônica como uma referência a mais: uma escala que dá à frase menor um caráter dramático e uma resolução forte. Ela entra no vocabulário ao lado da pentatônica e dos modos, e é escolhida quando a frase pede tensão e drama."),


        h ("A menor harmônica no braço"),
        p (
            "A menor harmônica aparece em todas as regiões do braço, como qualquer escala de sete notas. O que muda é o desenho: por causa da segunda aumentada, há um salto que nenhuma escala de sete notas \"normal\" tem. Esse salto é o que dá à escala o seu caráter, mas também o que exige atenção na digitação. Muitas vezes, o salto é tocado com um deslize ou uma corda solta, para não quebrar a fluência."),
        p (
            "Um bom exercício é tocar a menor harmônica em todas as posições, destacando a segunda aumentada e resolvendo na tônica. Você percebe que o salto cai sempre entre os mesmos dois graus (o sexto menor e o sétimo elevado), apenas transportado para outra região. Quando o gesto fica automático, a escala deixa de ser \"difícil\" e passa a ser um recurso que a mão encontra sem pensar."),
        p (
            "É importante tocar a escala devagar antes de acelerar. A segunda aumentada é um intervalo grande, e a tendência é atropelá-lo na correria. Tocando devagar, você ouve o salto e o resolve com clareza; acelerando depois, o salto continua claro, porque a mão já sabe onde ele está. O drama da escala depende de o salto ser ouvido como intenção, não como erro."),
        b ("A menor harmônica cabe em todas as regiões; o desenho é que muda."),
        b ("A segunda aumentada exige cuidado na digitação; às vezes, um deslize resolve."),
        b ("Toque devagar para ouvir o salto, e só depois acelere."),
        tbl ({ "Região", "Onde cai a 2ª aumentada", "Dica" }, {
            { "Grave", "entre 6º e 7º graus", "deslize para manter a fluência" },
            { "Média", "entre 6º e 7º graus", "destaque o salto e resolva" },
            { "Aguda", "entre 6º e 7º graus", "cuidado com a tensão da mão" },
        }),


        h ("Drama e resolução"),
        p (
            "A menor harmônica é uma escala de drama. Ela existe para criar tensão e resolvê-la com força. A sétima elevada é a sensível, que puxa para a tônica; a sexta menor, logo abaixo, é a cor sombria que a antecede. Juntas, elas formam a segunda aumentada, o gesto que dá à escala o seu caráter. Usar a menor harmônica é usar esse drama a favor da música."),
        p (
            "O drama precisa de contraste para funcionar. Se toda a frase é dramática, o drama se banaliza. Por isso, a menor harmônica costuma aparecer em momentos específicos: a cadência final, o clímax do solo, a resolução de uma passagem tensa. Nos outros momentos, a menor natural ou a pentatônica dão o contraste que faz o drama da harmônica sobressair."),
        p (
            "Um bom exercício é tocar uma frase que começa na menor natural e termina na menor harmônica, resolvendo na tônica. Você sente o momento em que o drama entra e a força da resolução. Esse tipo de frase, que muda de cor no meio, é muito usado no rock e no metal, onde o contraste entre o sombrio e o dramático é parte da linguagem."),
        b ("A menor harmônica existe para criar tensão e resolvê-la com força."),
        b ("Use-a nos momentos de clímax, com contraste nos outros."),
        b ("Uma frase pode começar na menor natural e resolver na harmônica."),
        tbl ({ "Momento", "Escala", "Efeito" }, {
            { "Exposição", "menor natural", "som melancólico" },
            { "Clímax", "menor harmônica", "drama e tensão" },
            { "Resolução", "menor harmônica na tônica", "força e conclusão" },
        }),

        c (
            "Meta do módulo: 100 BPM. A prova da menor harmônica é a resolução: a frase toca a segunda aumentada e cai na tônica no tempo forte, com convicção."),
    };
}

} // namespace cursomusica::content
