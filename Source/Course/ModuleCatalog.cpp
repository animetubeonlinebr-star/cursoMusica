#include "Course/ModuleCatalog.h"

#include "Course/NoteMath.h"

namespace cursomusica
{

namespace
{
    LessonBlock block (juce::String id, juce::String title, std::initializer_list<const char*> paragraphs)
    {
        LessonBlock b;
        b.id = std::move (id);
        b.title = std::move (title);
        for (auto* p : paragraphs)
            b.paragraphs.add (juce::String::fromUTF8 (p));
        return b;
    }

    // Attaches the rich explanation unfolded in the central panel.
    LessonBlock detail (LessonBlock b, std::vector<ContentItem> items)
    {
        b.detail = std::move (items);
        return b;
    }

    QuizQuestion question (const char* prompt, std::initializer_list<const char*> options, int correctIndex)
    {
        QuizQuestion q;
        q.prompt = juce::String::fromUTF8 (prompt);
        for (auto* o : options)
            q.options.add (juce::String::fromUTF8 (o));
        q.correctIndex = correctIndex;
        return q;
    }

    Exercise exercise (juce::String id, juce::String title, juce::String goal, juce::String check)
    {
        Exercise e;
        e.id = std::move (id);
        e.title = std::move (title);
        e.goal = std::move (goal);
        e.check = std::move (check);
        return e;
    }

    // Builds an ordered list of target notes from pitch names ("E2", "C4").
    std::vector<course::TargetNote> notes (std::initializer_list<const char*> names)
    {
        std::vector<course::TargetNote> out;
        for (auto* name : names)
        {
            const auto text = juce::String (name);
            out.push_back ({ music::noteNameToMidi (text), text });
        }
        return out;
    }

    CourseModule makeModule1()
    {
        CourseModule m;
        m.number = 1;
        m.title = juce::String::fromUTF8 ("Ambientação, instrumento e organização musical");
        m.objective = juce::String::fromUTF8 (
            "Preparar o aluno para acompanhar os estudos e compreender a organização "
            "do instrumento.");
        m.level = 1;
        m.targetBpm = 60;      // MUSIC.md, módulo 1
        m.onGridTarget = 0.75f;
        m.implemented = true;
        m.usesTempo = false;   // the client: module 1 does not use the BPM target

        m.lessons = {
            detail (block ("A", juce::String::fromUTF8 ("Partes da guitarra e do violão"), {
                "Corpo, braço, cavalete (ponte), rastilho, pestana (nut), tarraxas, "
                "trastes, casas, cordas (6ª a 1ª), captadores, volume e tom.",
                "No violão: a boca, o tampo e as cordas de nylon — som mais doce e "
                "menor tensão que as cordas de aço da guitarra."
            }), {
                ContentItem::paragraph (juce::String::fromUTF8 (
                    "A guitarra e o violão são instrumentos de cordas. Compartilham a "
                    "construção geral, mas diferem na forma de produzir e amplificar o som: "
                    "o violão usa a caixa de ressonância; a guitarra elétrica depende de "
                    "captação e amplificação.")),
                ContentItem::heading (juce::String::fromUTF8 ("O corpo")),
                ContentItem::paragraph (juce::String::fromUTF8 (
                    "Parte principal e mais volumosa. É nele que ficam os componentes que "
                    "produzem e controlam o som.")),
                ContentItem::bullet (juce::String::fromUTF8 (
                    "No violão: a caixa de ressonância amplifica naturalmente a vibração das "
                    "cordas. A vibração é transmitida ao cavalete e ao tampo, movimentando o "
                    "ar dentro da caixa.")),
                ContentItem::bullet (juce::String::fromUTF8 (
                    "Na guitarra elétrica: corpo geralmente maciço; sustenta ponte, "
                    "captadores e controles, e depende do sistema de captação para soar.")),
                ContentItem::callout (juce::String::fromUTF8 (
                    "Para memorizar: o corpo é a estrutura principal; no violão acústico, "
                    "também é a caixa de ressonância.")),
                ContentItem::heading (juce::String::fromUTF8 ("O braço")),
                ContentItem::paragraph (juce::String::fromUTF8 (
                    "Parte alongada que liga o corpo às tarraxas. Sobre ele ficam a escala, "
                    "os trastes e as casas. É onde a mão de execução posiciona os dedos.")),
                ContentItem::bullet (juce::String::fromUTF8 (
                    "Pressionar a corda numa casa muda o comprimento vibrante e, portanto, a "
                    "altura da nota.")),
                ContentItem::bullet (juce::String::fromUTF8 (
                    "Corda solta = nota mais grave; avançar pelas casas deixa a nota "
                    "progressivamente mais aguda.")),
                ContentItem::callout (juce::String::fromUTF8 (
                    "Para memorizar: o braço permite posicionar os dedos e modificar as notas.")),
                ContentItem::heading (juce::String::fromUTF8 ("O cavalete ou ponte")),
                ContentItem::paragraph (juce::String::fromUTF8 (
                    "Sustenta as cordas sobre o corpo e transmite as vibrações ao tampo.")),
                ContentItem::heading (juce::String::fromUTF8 ("O rastilho")),
                ContentItem::paragraph (juce::String::fromUTF8 (
                    "Encaixado no cavalete, serve de apoio às cordas no lado do corpo.")),
                ContentItem::bullet (juce::String::fromUTF8 ("Determina a altura das cordas em relação ao corpo.")),
                ContentItem::bullet (juce::String::fromUTF8 ("Ajuda a transmitir vibrações e participa da entonação.")),
                ContentItem::callout (juce::String::fromUTF8 (
                    "Altura inadequada deixa o instrumento desconfortável de tocar.")),
                ContentItem::heading (juce::String::fromUTF8 ("A pestana")),
                ContentItem::paragraph (juce::String::fromUTF8 (
                    "Pequena peça na extremidade superior do braço, junto à cabeça, com sulcos "
                    "que mantêm as cordas separadas e posicionadas.")),
                ContentItem::bullet (juce::String::fromUTF8 ("Mantém o espaçamento entre as cordas.")),
                ContentItem::bullet (juce::String::fromUTF8 ("Determina a altura das cordas no início do braço.")),
                ContentItem::bullet (juce::String::fromUTF8 ("Apoia as cordas quando tocadas soltas.")),
                ContentItem::callout (juce::String::fromUTF8 (
                    "Pestana fica no início da escala (junto às tarraxas); rastilho fica no "
                    "cavalete, sobre o corpo. Funções parecidas, posições diferentes.")),
                ContentItem::heading (juce::String::fromUTF8 ("As tarraxas")),
                ContentItem::paragraph (juce::String::fromUTF8 (
                    "Ficam na cabeça do instrumento e afinam as cordas; cada corda tem a sua.")),
                ContentItem::bullet (juce::String::fromUTF8 ("Aumentar a tensão deixa a nota mais aguda.")),
                ContentItem::bullet (juce::String::fromUTF8 ("Diminuir a tensão deixa a nota mais grave.")),
                ContentItem::callout (juce::String::fromUTF8 (
                    "Para memorizar: as tarraxas controlam a tensão e a afinação das cordas.")),
                ContentItem::heading (juce::String::fromUTF8 ("Os trastes e as casas")),
                ContentItem::paragraph (juce::String::fromUTF8 (
                    "Trastes são as barras metálicas transversais sobre a escala; casas são os "
                    "espaços entre dois trastes. Não confunda: traste é a barra, casa é o espaço.")),
                ContentItem::bullet (juce::String::fromUTF8 (
                    "Cada casa corresponde a um semitom na afinação convencional.")),
                ContentItem::table (juce::StringArray { "Posição", "Nota (corda Mi)" },
                    { juce::StringArray { "Corda solta", "Mi" },
                      juce::StringArray { "1ª casa", "Fá" },
                      juce::StringArray { "2ª casa", "Fá sustenido" },
                      juce::StringArray { "3ª casa", "Sol" },
                      juce::StringArray { "4ª casa", "Sol sustenido" },
                      juce::StringArray { "5ª casa", "Lá" } }),
                ContentItem::callout (juce::String::fromUTF8 (
                    "Para memorizar: as casas são os espaços onde posicionamos os dedos.")),
                ContentItem::heading (juce::String::fromUTF8 ("As cordas: nylon e aço")),
                ContentItem::paragraph (juce::String::fromUTF8 (
                    "A corda vibra e produz uma frequência que depende do comprimento vibrante, "
                    "da tensão e da massa por unidade de comprimento. O par guitarra/violão "
                    "costuma ter seis cordas.")),
                ContentItem::bullet (juce::String::fromUTF8 (
                    "Nylon (violão clássico): toque mais macio, menor tensão, timbre mais "
                    "suave — associado a clássico, MPB e bossa nova.")),
                ContentItem::bullet (juce::String::fromUTF8 (
                    "Aço (guitarra e violões de aço): timbre mais brilhante, mais agudos, "
                    "toque mais rígido e maior tensão; essencial para os captadores magnéticos.")),
                ContentItem::table (juce::StringArray { "Característica", "Nylon", "Aço" },
                    { juce::StringArray { "Timbre", "Mais suave", "Mais brilhante" },
                      juce::StringArray { "Toque", "Geralmente mais macio", "Geralmente mais firme" },
                      juce::StringArray { "Uso tradicional", "Violão clássico", "Guitarra e violão de aço" },
                      juce::StringArray { "Material", "Polímeros sintéticos", "Metal" },
                      juce::StringArray { "Captação magnética", "Não adequada", "Adequada" } }),
                ContentItem::callout (juce::String::fromUTF8 (
                    "Nunca coloque cordas de aço num violão feito para nylon: a tensão pode "
                    "danificar o instrumento.")),
                ContentItem::heading (juce::String::fromUTF8 ("Os captadores")),
                ContentItem::paragraph (juce::String::fromUTF8 (
                    "Componentes eletrônicos das guitarras: transformam a vibração das cordas "
                    "metálicas em sinal elétrico, que segue para o amplificador.")),
                ContentItem::bullet (juce::String::fromUTF8 (
                    "Single coil: uma bobina; som mais brilhante e definido, sujeito a ruído.")),
                ContentItem::bullet (juce::String::fromUTF8 (
                    "Humbucker: duas bobinas; som mais encorpado, boa resposta com distorção e "
                    "menos ruído.")),
                ContentItem::heading (juce::String::fromUTF8 ("Controle de volume e de tom")),
                ContentItem::bullet (juce::String::fromUTF8 (
                    "Volume: regula a intensidade do sinal enviado pelo instrumento.")),
                ContentItem::bullet (juce::String::fromUTF8 (
                    "Tom (tone): na maioria das guitarras passivas, reduz os agudos — tom aberto "
                    "soa brilhante, tom fechado soa mais escuro e suave.")),
                ContentItem::heading (juce::String::fromUTF8 ("Resumo dos componentes")),
                ContentItem::table (juce::StringArray { "Componente", "Função principal" },
                    { juce::StringArray { "Corpo", "Estrutura principal do instrumento" },
                      juce::StringArray { "Braço", "Sustenta a escala e permite posicionar os dedos" },
                      juce::StringArray { "Cavalete/ponte", "Sustenta as cordas e transmite vibrações" },
                      juce::StringArray { "Rastilho", "Apoia as cordas no cavalete" },
                      juce::StringArray { "Pestana", "Organiza e apoia as cordas no início do braço" },
                      juce::StringArray { "Tarraxas", "Regulam a tensão e a afinação" },
                      juce::StringArray { "Trastes", "Determinam os pontos de apoio das cordas" },
                      juce::StringArray { "Casas", "Espaços onde posicionamos os dedos" },
                      juce::StringArray { "Cordas", "Produzem as vibrações sonoras" },
                      juce::StringArray { "Captadores", "Transformam vibrações em sinais elétricos" },
                      juce::StringArray { "Volume", "Regula a intensidade do sinal" },
                      juce::StringArray { "Tom", "Modifica a característica tonal do sinal" } }),
                ContentItem::heading (juce::String::fromUTF8 ("Como tudo funciona em conjunto")),
                ContentItem::bullet (juce::String::fromUTF8 (
                    "Guitarra: toque na corda → vibração → captador gera sinal elétrico → "
                    "circuito e controles → amplificador → alto-falante.")),
                ContentItem::bullet (juce::String::fromUTF8 (
                    "Violão: toque na corda → vibração → cavalete transmite ao corpo → tampo e "
                    "caixa de ressonância movimentam o ar → som projetado naturalmente.")),
            }),
            block ("B", juce::String::fromUTF8 ("Notas musicais"), {
                "Sete nomes naturais: Dó Ré Mi Fá Sol Lá Si (C D E F G A B).",
                "Entre Mi–Fá e Si–Dó não há nota intermediária (semitons naturais). "
                "As demais notas naturais estão a um tom e admitem nota intermediária."
            }),
            block ("C", juce::String::fromUTF8 ("Sustenidos e bemóis"), {
                "Sustenido (#) sobe meio-tom: Fá# está meio-tom acima de Fá. "
                "Bemol (b) desce meio-tom: Sib está meio-tom abaixo de Si.",
                "Enarmonia: Fá# = Solb, Dó# = Réb — mesmo som, nomes diferentes.",
                "Regra prática: não existe Mi# nem Si# na escala natural."
            }),
            block ("D", juce::String::fromUTF8 ("Localização das notas no braço"), {
                "Afinação padrão, da 6ª (mais grave) à 1ª (mais aguda): E2 A2 D3 G3 B3 E4.",
                "Regra do oitavo grau: a casa 12 repete a corda solta uma oitava acima.",
                "Convenção de partitura: a guitarra soa uma oitava abaixo do escrito. "
                "A conversão partitura→áudio aplica essa transposição."
            }),
            block ("E", juce::String::fromUTF8 ("Pestanas"), {
                "Pestana completa (barré): um dedo pressiona todas as cordas na mesma "
                "casa; os demais dedos montam o acorde à frente.",
                "Meio barré: o indicador cobre apenas 2 a 4 cordas.",
                "Permite usar a mesma forma de acorde em qualquer região do braço — "
                "é o alicerce do CAGED.",
                "Erro comum: corda abafada no meio da pestana soa morta. Ajuste o dedo "
                "para trás do traste e aproxime o polegar do centro do braço."
            }),
            block ("F", juce::String::fromUTF8 ("Sistema 5 (CAGED)"), {
                "Cinco formas de acorde maior (C, A, G, E, D) cobrem todo o braço e se "
                "repetem a cada 12 casas, na ordem C → A → G → E → D.",
                "As formas conectam-se: a última nota de uma é a primeira da seguinte.",
                "A mesma forma vale para acordes menores e de 7ª (muda a qualidade).",
                "O CAGED é a ponte entre acorde e escala: cada forma contém a "
                "pentatônica/modo daquele centro."
            }),
            block ("G", juce::String::fromUTF8 ("Organização das tonalidades"), {
                "Campo harmônico maior: I – ii – iii – IV – V – vi – vii°. "
                "Em Dó: C – Dm – Em – F – G – Am – Bdim.",
                "Círculo das quintas: C → G → D → A → E → B → F# → C#…; cada passo "
                "acrescenta um sustenido. No sentido inverso, um bemol.",
                "Cada maior tem uma relativa menor com a mesma armadura (C ↔ Am)."
            }),
            block ("H", juce::String::fromUTF8 ("Introdução ao cifrado"), {
                "Cifrar é descrever o acorde de forma compacta: C (maior), Cm (menor), "
                "C7 (sétima dominante), C7M (sétima maior), Cm7 (menor com sétima).",
                "C/E indica baixo na nota após a barra; C(9) e C(#11) indicam tensões.",
                "Ler a cifra e achar a forma no braço (via CAGED) é a habilidade "
                "prática do módulo."
            }),
            block ("I", juce::String::fromUTF8 ("Rítmica: pulsação e figuras"), {
                "Pulsação (tempo) é a batida constante do metrônomo; o compasso agrupa "
                "os tempos (4/4, 3/4, 6/8).",
                "Figuras: semibreve (4 tempos), mínima (2), semínima (1), colcheia "
                "(1/2) e semicolcheia (1/4). Ponto aumenta metade do valor; ligadura "
                "soma a duração de duas notas.",
                "Sílaba rítmica (solfa rítmica): TÁ = semínima, TÁ-KI = colcheias, "
                "TA-KI-TA-KI = quatro semicolcheias. Contar em voz alta antes de tocar "
                "é o que permite alinhar ao metrônomo.",
                "O gate cobra tocar na grade: contar a subdivisão é a base do "
                "on_grid_ratio ≥ 0,75."
            }),
        };

        m.exercises = {
            exercise ("EX-1.1", juce::String::fromUTF8 ("Questionário: conhecendo o instrumento"),
                      juce::String::fromUTF8 ("Responder ao teste de aprendizagem do Módulo 1, uma questão por vez."),
                      juce::String::fromUTF8 ("Acerto ≥90% nas questões do questionário.")),
            exercise ("EX-1.2", juce::String::fromUTF8 ("Corda 6ª e casa 5"),
                      juce::String::fromUTF8 ("Tocar a 6ª solta (Mi) e a casa 5 (Lá)."),
                      juce::String::fromUTF8 ("Detector: E2 solto e A2 na 5ª casa.")),
            exercise ("EX-1.3", juce::String::fromUTF8 ("Escala de Dó na 1ª posição"),
                      juce::String::fromUTF8 ("Tocar a escala de Dó em 2 oitavas."),
                      juce::String::fromUTF8 ("Sequência de notas esperada, 90% de acerto.")),
            exercise ("EX-1.4", juce::String::fromUTF8 ("Acordes simples"),
                      juce::String::fromUTF8 ("Montar C, G, D, Am, Em e identificar a forma CAGED."),
                      juce::String::fromUTF8 ("Detecção de acorde (soma de notas).")),
            exercise ("EX-1.5", juce::String::fromUTF8 ("Pestana de Fá"),
                      juce::String::fromUTF8 ("Pestana de F na 1ª casa; todas as cordas soam."),
                      juce::String::fromUTF8 ("Nível/ataque presente em todas as cordas.")),
            exercise ("EX-1.6", juce::String::fromUTF8 ("Mover a forma de E"),
                      juce::String::fromUTF8 ("Deslizar a forma de E e nomear o acorde."),
                      juce::String::fromUTF8 ("Identificar acorde pela região do braço.")),
            exercise ("EX-1.7", juce::String::fromUTF8 ("Cifrado e tonalidade"),
                      juce::String::fromUTF8 ("Dado Dm7, G7, C7M, dizer o campo harmônico e tocar as tríades."),
                      juce::String::fromUTF8 ("Detecção de acorde e resposta.")),
            exercise ("EX-1.8", juce::String::fromUTF8 ("Contar e tocar na grade"),
                      juce::String::fromUTF8 ("Contar em voz alta (TÁ / TÁ-KI) e tocar a 6ª solta em semínimas na grade do metrônomo a 60 BPM."),
                      juce::String::fromUTF8 ("on_grid_ratio ≥ 0,75 nas batidas (REQ-015).")),
            exercise ("EX-1.9", juce::String::fromUTF8 ("Sustenidos, bemóis e enarmonia"),
                      juce::String::fromUTF8 ("Nomear a nota que falta e dizer quais nomes são o mesmo som (enarmonia)."),
                      juce::String::fromUTF8 ("Acerto ≥90% nas questões de sustenidos, bemóis e enarmonia.")),
            exercise ("EX-1.10", juce::String::fromUTF8 ("Tonalidade e campo harmônico"),
                      juce::String::fromUTF8 ("Montar o campo harmônico maior de Dó e achar a relativa menor."),
                      juce::String::fromUTF8 ("Acerto ≥90% nas questões de campo harmônico e círculo das quintas.")),
        };

        // Topic each exercise belongs to, so the right panel follows the topic
        // selected on the left (empty -> module-wide).
        m.exercises[0].lessonId = "A";   // quiz on the instrument parts
        m.exercises[1].lessonId = "D";   // notes on the fretboard
        m.exercises[2].lessonId = "B";   // natural notes / scale
        m.exercises[3].lessonId = "F";   // chords / CAGED
        m.exercises[4].lessonId = "E";   // barre chords
        m.exercises[5].lessonId = "F";   // CAGED shapes
        m.exercises[6].lessonId = "H";   // chord symbols
        m.exercises[7].lessonId = "I";   // rhythm on the grid
        m.exercises[8].lessonId = "C";   // sharps / flats / enharmony
        m.exercises[9].lessonId = "G";   // key organisation / harmonic field

        // EX-1.1 is the learning quiz of the module (Questionario_m1). Questions
        // are answered one at a time; the gate is the same 90% (REQ-009).
        m.exercises[0].quiz = {
            question ("Qual é a principal função das tarraxas?",
                      { "Modificar o volume",
                        "Regular a tensão e a afinação das cordas",
                        "Amplificar o som",
                        "Sustentar os trastes" }, 1),
            question ("Qual é a diferença entre trastes e casas?",
                      { "São exatamente a mesma coisa",
                        "Trastes são espaços e casas são barras",
                        "Trastes são barras metálicas e casas são os espaços entre elas",
                        "Trastes controlam o volume" }, 2),
            question ("Qual componente transforma a vibração das cordas metálicas em sinal elétrico?",
                      { "Pestana", "Rastilho", "Captador", "Cavalete" }, 2),
            question ("Qual é a função da pestana?",
                      { "Regular o tom",
                        "Apoiar e organizar as cordas no início do braço",
                        "Amplificar o som",
                        "Controlar o volume" }, 1),
            question ("Qual característica é geralmente associada às cordas de nylon?",
                      { "Timbre mais suave e toque geralmente mais macio",
                        "Produção obrigatória de sinal magnético",
                        "Maior brilho em todas as situações",
                        "Uso exclusivo em guitarras elétricas" }, 0),
            question ("Qual é a função do controle de tom?",
                      { "Afinar as cordas",
                        "Modificar a característica tonal do sinal",
                        "Alterar o comprimento do braço",
                        "Prender as cordas" }, 1),
            question ("Como o violão acústico amplifica naturalmente o som?",
                      { "Por meio dos captadores magnéticos",
                        "Por meio das tarraxas",
                        "Por meio da caixa de ressonância",
                        "Por meio do controle de volume" }, 2),
        };

        // Playable specs for the exercises the app can verify with the detector.
        m.exercises[1].targets = notes ({ "E2", "A2" });                    // EX-1.2
        m.exercises[2].targets = notes ({ "C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5" }); // EX-1.3
        m.exercises[3].chordPitchClasses = { 0, 4, 7 };                     // EX-1.4, first C
        m.exercises[4].chordPitchClasses = { 5, 9, 0 };                     // EX-1.5, F barre
        m.exercises[7].targets = notes ({ "E2" });                          // EX-1.8, on the grid

        // EX-1.7 (topic H, cifrado) is playable: the student plays the ii–V–I of C
        // as the app recognises each chord (REQ-022 — every topic has an
        // executable exercise, not only a questionnaire).
        m.exercises[6].chordProgression = {
            { 2, 5, 9, 0 },    // Dm7
            { 7, 11, 2, 5 },   // G7
            { 0, 4, 7, 11 },   // C7M
        };

        // EX-1.9 and EX-1.10 are quizzes on topics C and G, so every topic A..I
        // has at least one exercise (REQ-022). Answered one at a time, like the
        // module quiz, with the same 90% mark (REQ-009).
        m.exercises[8].quiz = {
            question ("Quantos semitons um sustenido (#) sobe a nota?",
                      { "Meio-tom (um semitom)",
                        "Um tom (dois semitons)",
                        "Dois tons",
                        "Uma oitava" }, 0),
            question ("Sib está a que distância de Si?",
                      { "Meio-tom acima",
                        "Meio-tom abaixo",
                        "Um tom abaixo",
                        "Nenhuma: são a mesma nota" }, 1),
            question ("Quais pares são enarmônicos (mesmo som, nomes diferentes)?",
                      { "Fá# e Solb",
                        "Dó e Dó#",
                        "Mi e Fá",
                        "Sol e Sol#" }, 0),
            question ("Por que não existe Mi# nem Si# na escala natural?",
                      { "Porque o intervalo Mi–Fá e Si–Dó já é de meio-tom",
                        "Porque essas notas são graves demais",
                        "Porque a guitarra não alcança essas notas",
                        "Porque só existem bemóis" }, 0),
            question ("Dó# é enarmônico de qual nota?",
                      { "Ré", "Réb", "Si", "Dób" }, 1),
            question ("Um bemol (b) faz o quê com a altura da nota?",
                      { "Sobe meio-tom", "Desce meio-tom", "Não muda nada", "Dobra a duração" }, 1),
        };

        m.exercises[9].quiz = {
            question ("Qual é o campo harmônico maior de Dó?",
                      { "C – Dm – Em – F – G – Am – Bdim",
                        "C – D – E – F – G – A – B",
                        "Cm – Dm – Em – Fm – Gm – Am – Bdim",
                        "C – Em – F – G – Am – Bdim – Dm" }, 0),
            question ("No círculo das quintas, qual tonalidade vem logo depois de Dó?",
                      { "Fá", "Sol", "Ré", "Si" }, 1),
            question ("Qual é a relativa menor de Dó maior?",
                      { "Lá menor (Am)", "Mi menor (Em)", "Ré menor (Dm)", "Si menor (Bm)" }, 0),
            question ("A armadura de clave indica o quê?",
                      { "O tempo do compasso",
                        "Quantos sustenidos ou bemóis a tonalidade tem",
                        "A digitação da mão direita",
                        "O volume do metrônomo" }, 1),
            question ("No campo harmônico maior, qual grau é o acorde dominante?",
                      { "I", "IV", "V", "vi" }, 2),
            question ("Ir de Dó para Fá no círculo das quintas acrescenta o quê?",
                      { "Um sustenido", "Um bemol", "Nada", "Duas oitavas" }, 1),
        };

        // The gate is a chord progression played on the grid (REQ-009, REQ-015).
        auto& gate = m.exercises.emplace_back (exercise (
            "GATE-1", juce::String::fromUTF8 ("Desafio de gate — vamp C–G–Am–F"),
            juce::String::fromUTF8 ("Tocar C – G – Am – F a 60 BPM, na grade do metrônomo."),
            juce::String::fromUTF8 ("Acordes reconhecidos e alinhados à grade (≥ 0,75).")));
        gate.isGate = true;
        gate.lessonId = "I";   // the gate is played on the metronome grid
        gate.chordProgression = {
            { 0, 4, 7 },   // C
            { 7, 11, 2 },  // G
            { 9, 0, 4 },   // Am
            { 5, 9, 0 },   // F
        };

        m.gateChallenge = juce::String::fromUTF8 (
            "Tocar C – G – Am – F (vamp de 1 acorde, nível 1) a 60 BPM com ≥90% de "
            "acerto de acordes e on_grid_ratio ≥ 0,75.");

        m.practice.patternId = "PTN-R-PALM";
        m.practice.patternUse = juce::String::fromUTF8 (
            "Pedal point abafado + power chords: primeiro contato com o ritmo e o "
            "abafamento. Alternativa PTN-R-BOSSA para quem já tem base de violão.");
        m.practice.guitarists = { "Juninho Afram", "Kiko Loureiro", "John Petrucci" };

        m.caged = {
            { "C", juce::String::fromUTF8 ("5ª"), juce::String::fromUTF8 ("casas 0–3") },
            { "A", juce::String::fromUTF8 ("5ª"), juce::String::fromUTF8 ("casas 3–5") },
            { "G", juce::String::fromUTF8 ("6ª"), juce::String::fromUTF8 ("casas 5–8") },
            { "E", juce::String::fromUTF8 ("6ª"), juce::String::fromUTF8 ("casas 8–12") },
            { "D", juce::String::fromUTF8 ("4ª"), juce::String::fromUTF8 ("casas 10–12") },
        };

        // Counting cells for the metronome (REQ-015); syllables from the
        // rhythmic reading chapter of the curated apostila (MUSIC.md §1.2, block I).
        m.rhythm = {
            { juce::String::fromUTF8 ("Semínima"), juce::String::fromUTF8 ("1 tempo (1/4)"),
              juce::String::fromUTF8 ("TÁ") },
            { juce::String::fromUTF8 ("Colcheias"), juce::String::fromUTF8 ("2 por tempo (2/8)"),
              juce::String::fromUTF8 ("TÁ-KI") },
            { juce::String::fromUTF8 ("Semicolcheias"), juce::String::fromUTF8 ("4 por tempo (4/16)"),
              juce::String::fromUTF8 ("TA-KI-TA-KI") },
        };

        // Curated apostilas (REQ-006, CM-012); see docs/MUSIC.md §1.1. The
        // 2026-11-04 review of branch `adequacao` added four apostilas: CAGED
        // (block F), elementary theory (blocks B/C/D), music theory (blocks
        // G/I) and guitar setup/maintenance (block A).
        m.sources = {
            "pdf-mozart-mello-livroestudosdeguitarra4em1",
            "pdf-fraseado-melodico",
            "pdf-desvendando-os-segredos-da-guitarra-fusion",
            "pdf-caged-e-derivaoes-de-acordes-marcelo-mello-apostila-de-violao-e-guitarra-vol1",
            "pdf-teoria-elementar-da-musica-ricordi-osvaldo-lacerda",
            "pdf-p-classtruncatedtext-module-lineclamped-85ulhh-style-max-lines5bohumil-med-teoria-da-musica-5-edicao-p",
            "pdf-manual-de-regulagem-e-manutenao-em-guitarra-contrabaixos-e-violoes-mozart-carvalho",
        };

        return m;
    }

    // Modules 2..20 exist as placeholders so the list is honest about what is
    // coming (ADR 0005): level, target BPM and alignment come from MUSIC.md.
    CourseModule makePlaceholder (int number, const char* title, int level,
                                  int targetBpm, float onGridTarget)
    {
        CourseModule m;
        m.number = number;
        m.title = juce::String::fromUTF8 (title);
        m.objective = juce::String::fromUTF8 (
            "Conteúdo em preparação. A especificação musical já existe em "
            "docs/MUSIC.md; a aula entra em uma entrega seguinte.");
        m.level = level;
        m.targetBpm = targetBpm;
        m.onGridTarget = onGridTarget;
        m.implemented = false;
        return m;
    }
}

const std::vector<CourseModule>& ModuleCatalog::getModules()
{
    static const std::vector<CourseModule> modules {
        makeModule1(),
        makePlaceholder (2,  "Vamps de 1 acorde (continuação)",     1,  64,  0.76f),
        makePlaceholder (3,  "Vamps de 2 acordes",                  2,  68,  0.77f),
        makePlaceholder (4,  "Vamps de 2 acordes (aplicação)",      2,  72,  0.78f),
        makePlaceholder (5,  "II–V–I",                              3,  76,  0.79f),
        makePlaceholder (6,  "II–V–I (menor)",                      3,  80,  0.80f),
        makePlaceholder (7,  "II–V–I (aplicação)",                  3,  84,  0.80f),
        makePlaceholder (8,  "Turnarounds",                         4,  88,  0.81f),
        makePlaceholder (9,  "Turnarounds (variações)",             4,  92,  0.81f),
        makePlaceholder (10, "Turnarounds (aplicação)",             4,  96,  0.82f),
        makePlaceholder (11, "Blues de 12 compassos",               5, 100,  0.82f),
        makePlaceholder (12, "Blues menor",                         5, 104,  0.82f),
        makePlaceholder (13, "Blues (variações)",                   5, 108,  0.82f),
        makePlaceholder (14, "Blues (aplicação)",                   5, 112,  0.82f),
        makePlaceholder (15, "Standards com modulação",             6, 120,  0.82f),
        makePlaceholder (16, "Standards com modulação (aplicação)", 6, 124,  0.84f),
        makePlaceholder (17, "Standards com modulação (repertório)",6, 128,  0.85f),
        makePlaceholder (18, "Repertório (MPB/Bossa)",              7, 132,  0.87f),
        makePlaceholder (19, "Repertório (jazz)",                   7, 136,  0.88f),
        makePlaceholder (20, "Repertório (performance)",            7, 140,  0.90f),
    };
    return modules;
}

const CourseModule* ModuleCatalog::findModule (int number)
{
    for (const auto& m : getModules())
        if (m.number == number)
            return &m;

    return nullptr;
}

} // namespace cursomusica
