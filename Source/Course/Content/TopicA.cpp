#include "Course/Content/Topics.h"

// Topic A — Partes da guitarra e do violão.
// Sources: pdf-manual-de-regulagem-e-manutenao-...-mozart-carvalho (partes do
// instrumento) and pdf-mozart-mello-livroestudosdeguitarra4em1.
namespace cursomusica::content
{

std::vector<ContentItem> topicA()
{
    return {

                p (
                    "A guitarra e o violão são instrumentos de cordas. Compartilham a construção geral, mas diferem na forma de produzir e amplificar o som: o violão usa a caixa de ressonância; a guitarra elétrica depende de captação e amplificação."),
                h ("O corpo"),
                p (
                    "Parte principal e mais volumosa. É nele que ficam os componentes que produzem e controlam o som."),
                b (
                    "No violão: a caixa de ressonância amplifica naturalmente a vibração das cordas. A vibração é transmitida ao cavalete e ao tampo, movimentando o ar dentro da caixa."),
                b (
                    "Na guitarra elétrica: corpo geralmente maciço; sustenta ponte, captadores e controles, e depende do sistema de captação para soar."),
                c (
                    "Para memorizar: o corpo é a estrutura principal; no violão acústico, também é a caixa de ressonância."),
                h ("O braço"),
                p (
                    "Parte alongada que liga o corpo às tarraxas. Sobre ele ficam a escala, os trastes e as casas. É onde a mão de execução posiciona os dedos."),
                b (
                    "Pressionar a corda numa casa muda o comprimento vibrante e, portanto, a altura da nota."),
                b (
                    "Corda solta = nota mais grave; avançar pelas casas deixa a nota progressivamente mais aguda."),
                c (
                    "Para memorizar: o braço permite posicionar os dedos e modificar as notas."),
                h ("O cavalete ou ponte"),
                p (
                    "Sustenta as cordas sobre o corpo e transmite as vibrações ao tampo."),
                h ("O rastilho"),
                p (
                    "Encaixado no cavalete, serve de apoio às cordas no lado do corpo."),
                b ("Determina a altura das cordas em relação ao corpo."),
                b ("Ajuda a transmitir vibrações e participa da entonação."),
                c (
                    "Altura inadequada deixa o instrumento desconfortável de tocar."),
                h ("A pestana"),
                p (
                    "Pequena peça na extremidade superior do braço, junto à cabeça, com sulcos que mantêm as cordas separadas e posicionadas."),
                b ("Mantém o espaçamento entre as cordas."),
                b ("Determina a altura das cordas no início do braço."),
                b ("Apoia as cordas quando tocadas soltas."),
                c (
                    "Pestana fica no início da escala (junto às tarraxas); rastilho fica no cavalete, sobre o corpo. Funções parecidas, posições diferentes."),
                h ("As tarraxas"),
                p (
                    "Ficam na cabeça do instrumento e afinam as cordas; cada corda tem a sua."),
                b ("Aumentar a tensão deixa a nota mais aguda."),
                b ("Diminuir a tensão deixa a nota mais grave."),
                c (
                    "Para memorizar: as tarraxas controlam a tensão e a afinação das cordas."),
                h ("Os trastes e as casas"),
                p (
                    "Trastes são as barras metálicas transversais sobre a escala; casas são os espaços entre dois trastes. Não confunda: traste é a barra, casa é o espaço."),
                b (
                    "Cada casa corresponde a um semitom na afinação convencional."),
                tbl ({ "Posição", "Nota (corda Mi)" },
                    { { "Corda solta", "Mi" },
                      { "1ª casa", "Fá" },
                      { "2ª casa", "Fá sustenido" },
                      { "3ª casa", "Sol" },
                      { "4ª casa", "Sol sustenido" },
                      { "5ª casa", "Lá" } }),
                c (
                    "Para memorizar: as casas são os espaços onde posicionamos os dedos."),
                h ("As cordas: nylon e aço"),
                p (
                    "A corda vibra e produz uma frequência que depende do comprimento vibrante, da tensão e da massa por unidade de comprimento. O par guitarra/violão costuma ter seis cordas."),
                b (
                    "Nylon (violão clássico): toque mais macio, menor tensão, timbre mais suave — associado a clássico, MPB e bossa nova."),
                b (
                    "Aço (guitarra e violões de aço): timbre mais brilhante, mais agudos, toque mais rígido e maior tensão; essencial para os captadores magnéticos."),
                tbl ({ "Característica", "Nylon", "Aço" },
                    { { "Timbre", "Mais suave", "Mais brilhante" },
                      { "Toque", "Geralmente mais macio", "Geralmente mais firme" },
                      { "Uso tradicional", "Violão clássico", "Guitarra e violão de aço" },
                      { "Material", "Polímeros sintéticos", "Metal" },
                      { "Captação magnética", "Não adequada", "Adequada" } }),
                c (
                    "Nunca coloque cordas de aço num violão feito para nylon: a tensão pode danificar o instrumento."),
                h ("Os captadores"),
                p (
                    "Componentes eletrônicos das guitarras: transformam a vibração das cordas metálicas em sinal elétrico, que segue para o amplificador."),
                b (
                    "Single coil: uma bobina; som mais brilhante e definido, sujeito a ruído."),
                b (
                    "Humbucker: duas bobinas; som mais encorpado, boa resposta com distorção e menos ruído."),
                h ("Controle de volume e de tom"),
                b (
                    "Volume: regula a intensidade do sinal enviado pelo instrumento."),
                b (
                    "Tom (tone): na maioria das guitarras passivas, reduz os agudos — tom aberto soa brilhante, tom fechado soa mais escuro e suave."),
                h ("Resumo dos componentes"),
                tbl ({ "Componente", "Função principal" },
                    { { "Corpo", "Estrutura principal do instrumento" },
                      { "Braço", "Sustenta a escala e permite posicionar os dedos" },
                      { "Cavalete/ponte", "Sustenta as cordas e transmite vibrações" },
                      { "Rastilho", "Apoia as cordas no cavalete" },
                      { "Pestana", "Organiza e apoia as cordas no início do braço" },
                      { "Tarraxas", "Regulam a tensão e a afinação" },
                      { "Trastes", "Determinam os pontos de apoio das cordas" },
                      { "Casas", "Espaços onde posicionamos os dedos" },
                      { "Cordas", "Produzem as vibrações sonoras" },
                      { "Captadores", "Transformam vibrações em sinais elétricos" },
                      { "Volume", "Regula a intensidade do sinal" },
                      { "Tom", "Modifica a característica tonal do sinal" } }),
                h ("Como tudo funciona em conjunto"),
                b (
                    "Guitarra: toque na corda → vibração → captador gera sinal elétrico → circuito e controles → amplificador → alto-falante."),
                b (
                    "Violão: toque na corda → vibração → cavalete transmite ao corpo → tampo e caixa de ressonância movimentam o ar → som projetado naturalmente."),

                h ("Nomenclatura completa (Manual de regulagem e manutenção)"),
                img ("a_partes_do_instrumento", "Peças da guitarra e do violão, da cabeça ao cavalete."),
                p ("O manual de regulagem e manutenção de Mozart Carvalho, uma das "
                   "fontes deste módulo, usa uma nomenclatura precisa para cada peça. "
                   "Conhecer esses nomes ajuda a conversar com luthier, a entender "
                   "manuais e a cuidar do instrumento. Muitos desses termos aparecem "
                   "em catálogos e fóruns."),
                tbl ({ "Região", "Peças (guitarra)", "Peças (violão)" },
                     { { "Corpo", "Escudo, chave seletora, knobs, potenciômetros, "
                                  "roldana da correia, chanfrado de apoio",
                         "Tampo, fundo, faixa, filetes, boca, cavalete, rastilho" },
                       { "Braço", "Escala, trastes, pestana, placa de fixação do braço",
                         "Braço, escala, trastes, pestana (capelinha)" },
                       { "Cabeça", "Cabeçote, tarraxas, trava-cordas", "Tarrachas" },
                       { "Elétrica", "Captadores, potenciômetros, jack, chave seletora",
                         "—" },
                       { "Molas/ponte", "Placa das molas, trava-molas, alavanca (tremolo)",
                         "Cavalete fixo, rastilho" },
                       { "Tirante", "Tirante (truss rod) dentro do braço",
                         "Tirante, acesso pelo tampo ou pela boca" } }),
                p ("O tirante (truss rod) é uma haste metálica dentro do braço que "
                   "compensa a tensão das cordas. Ajustá-lo corrige o empenamento do "
                   "braço e a altura das cordas. É um ajuste delicado: pequenas voltas "
                   "por vez, e, se houver dúvida, procure um profissional."),
                c ("Nunca force o tirante. Um quarto de volta já altera bastante o "
                   "relevo do braço. Regulagem inadequada pode empenhar o braço de "
                   "forma permanente."),

                h ("Regulagem e manutenção básica"),
                p ("Um instrumento bem regulado é mais fácil de tocar e afina melhor. "
                   "A regulagem envolve três ajustes principais: a altura das cordas "
                   "na pestana, o relevo do braço (tirante) e a altura das cordas no "
                   "rastilho, além da oitava (entonação)."),
                b ("Ação (altura das cordas): cordas muito altas cansam a mão; muito "
                   "baixas geram trastejamento (zumbido)."),
                b ("Entonação: ajuste no cavalete que faz a nota da casa 12 soar "
                   "exatamente uma oitava acima da corda solta. Se a nota da casa 12 "
                   "estiver desafinada, o instrumento está desregulado."),
                b ("Conservação: mantenha as cordas limpas, evite variações bruscas de "
                   "temperatura e umidade, e guarde o instrumento em estojo quando não "
                   "estiver em uso."),
                c ("Para memorizar: regulagem = conforto + afinação correta. Manutenção "
                   "= limpeza + proteção contra clima."),

                h ("Troca de cordas e primeiros cuidados"),
                p ("Trocar as cordas é a manutenção que você fará com mais frequência. "
                   "Cordas velhas perdem brilho, desafinam e machucam os dedos. Aprenda "
                   "a trocar uma corda de cada vez: assim o braço mantém a tensão e o "
                   "instrumento não sai de afinação por completo."),
                b ("Solte a corda velha girando a tarraxa, remova-a e passe a corda "
                   "nova pelo orifício da tarraxa e pelo rastilho."),
                b ("Deixe algumas voltas organizadas na tarraxa e vá esticando a corda "
                   "enquanto afina, para assentar a tensão."),
                b ("Corte o excesso com um alicate, sempre deixando uma sobra pequena "
                   "para não escapar."),
                c ("Cuidado com a tensão: cordas de aço em instrumento feito para nylon "
                   "podem danificar o instrumento. Sempre use o tipo de corda para o "
                   "qual o instrumento foi projetado."),

                h ("Como o som nasce: vibração, tensão e comprimento"),
                p ("Todo som do instrumento começa na corda. Ao tocar, você a "
                   "desloca e ela vibra. Três fatores decidem a altura da nota: o "
                   "comprimento vibrante (quanto da corda está livre entre o dedo e "
                   "o rastilho), a tensão (quão esticada está) e a massa por unidade "
                   "de comprimento (o quão grossa e densa é a corda)."),
                b ("Comprimento menor → som mais agudo. É o que acontece ao "
                   "pressionar uma casa: você encurta a parte que vibra."),
                b ("Mais tensão → som mais agudo. É o que a tarraxa faz ao esticar a "
                   "corda."),
                b ("Corda mais grossa → som mais grave, com a mesma tensão e "
                   "comprimento."),
                p ("Essa relação explica por que as cordas mais grossas ficam nas "
                   "notas graves e as mais finas nas agudas, e por que, ao afinar, "
                   "pequenos giros na tarraxa já mudam bastante a nota: a tensão é "
                   "sensível."),
                c ("Ondas estacionárias: a corda vibra formando nós e ventres. A "
                   "frequência fundamental dá o nome da nota; os harmônicos "
                   "(múltiplos inteiros dessa frequência) dão o timbre. É por isso "
                   "que a mesma nota soa diferente na guitarra e no violão."),

                h ("A madeira e a construção importam"),
                p ("No violão acústico, a madeira do tampo é o principal "
                   "amplificador natural: ela vibra junto com a corda e movimenta o "
                   "ar da caixa de ressonância. Madeiras de tampo macias e leves, "
                   "como o abeto e o cedro, respondem rápido e projetam bem o som."),
                p ("Na guitarra elétrica, o corpo maciço contribui para o timbre e "
                   "para o sustain, mas quem capta a vibração são os captadores "
                   "magnéticos. Por isso, uma guitarra desligada quase não soa: sem "
                   "captação e amplificação, o corpo maciço não projeta som como a "
                   "caixa do violão."),
                tbl ({ "Elemento", "Violão acústico", "Guitarra elétrica" },
                     { { "Amplificação", "Caixa de ressonância (natural)",
                         "Captadores + amplificador (elétrica)" },
                       { "Tampo", "Peça central do som", "Não se aplica (corpo maciço)" },
                       { "Cordas", "Nylon ou aço", "Aço" },
                       { "Som desligado", "Projeta naturalmente", "Quase inaudível" } }),
                c ("Resumindo a cadeia sonora: a corda vibra; no violão a vibração "
                   "passa pelo rastilho e pelo cavalete até o tampo, que move o ar "
                   "da caixa; na guitarra, o captador transforma a vibração das "
                   "cordas de aço em sinal elétrico, que o amplificador converte em "
                   "som."),

                h ("Como estudar o tópico A na prática"),
                p ("Antes de avançar, faça o reconhecimento do seu próprio instrumento. "
                   "Pegue-o, aponte e nomeie cada peça em voz alta. Esse contato físico "
                   "fixa o vocabulário muito mais rápido que a leitura."),
                b ("Nomeie as seis cordas contando da mais grave (6ª, Mi) até a mais "
                   "aguda (1ª, Mi)."),
                b ("Localize a pestana, os trastes, as casas, o cavalete e o rastilho, "
                   "e diga a diferença de posição entre pestana e rastilho."),
                b ("Gire uma tarraxa devagar e perceba o som subindo ou descendo; depois "
                   "volte a afinar."),
                c ("Resumo do tópico A: o corpo produz e amplifica; o braço permite "
                   "mudar as notas; a pestana organiza as cordas no início; o rastilho "
                   "as apoia no cavalete; as tarraxas afinam; os trastes dividem as "
                   "casas; os captadores transformam vibração em sinal elétrico."),
    };
}

} // namespace cursomusica::content
