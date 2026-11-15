#include "Course/ModuleCatalog.h"

#include "Course/Content/Topics.h"
#include "Course/Intervals.h"
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

    // An interval-recognition exercise (module 2): the app listens to the root
    // and the second note and checks the distance the instrument produced, so
    // any position on the neck is accepted (client: "o sistema precisa
    // reconhecer as notas tocadas"). Not graded against the grid.
    Exercise intervalExercise (const char* id, const char* title, const char* goal,
                               int semitones, int repeats)
    {
        auto e = exercise (id, juce::String::fromUTF8 (title), juce::String::fromUTF8 (goal),
                           juce::String::fromUTF8 ("O app reconhece as notas tocadas e confere a distância de ")
                               + juce::String (semitones) + juce::String::fromUTF8 (" semitons (")
                               + course::intervalName (semitones)
                               + juce::String::fromUTF8 ("), em qualquer posição do braço."));
        e.interval.semitones = semitones;
        e.interval.repeats = repeats;
        e.interval.ascending = true;
        e.interval.descending = false;
        e.usesGrid = false;
        return e;
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
            }), content::topicA()),
            detail (block ("B", juce::String::fromUTF8 ("Notas musicais"), {

                "Sete nomes naturais: Dó Ré Mi Fá Sol Lá Si (C D E F G A B).",
                "Entre Mi–Fá e Si–Dó não há nota intermediária (semitons naturais). "
                "As demais notas naturais estão a um tom e admitem nota intermediária."
            }), content::topicB()),
            detail (block ("C", juce::String::fromUTF8 ("Sustenidos e bemóis"), {

                "Sustenido (#) sobe meio-tom: Fá# está meio-tom acima de Fá. "
                "Bemol (b) desce meio-tom: Sib está meio-tom abaixo de Si.",
                "Enarmonia: Fá# = Solb, Dó# = Réb — mesmo som, nomes diferentes.",
                "Regra prática: não existe Mi# nem Si# na escala natural."
            }), content::topicC()),
            detail (block ("D", juce::String::fromUTF8 ("Localização das notas no braço"), {

                "Afinação padrão, da 6ª (mais grave) à 1ª (mais aguda): E2 A2 D3 G3 B3 E4.",
                "Regra do oitavo grau: a casa 12 repete a corda solta uma oitava acima.",
                "Convenção de partitura: a guitarra soa uma oitava abaixo do escrito. "
                "A conversão partitura→áudio aplica essa transposição."
            }), content::topicD()),
            detail (block ("E", juce::String::fromUTF8 ("Pestanas"), {

                "Pestana completa (barré): um dedo pressiona todas as cordas na mesma "
                "casa; os demais dedos montam o acorde à frente.",
                "Meio barré: o indicador cobre apenas 2 a 4 cordas.",
                "Permite usar a mesma forma de acorde em qualquer região do braço — "
                "é o alicerce do CAGED.",
                "Erro comum: corda abafada no meio da pestana soa morta. Ajuste o dedo "
                "para trás do traste e aproxime o polegar do centro do braço."
            }), content::topicE()),
            detail (block ("F", juce::String::fromUTF8 ("Sistema 5 (CAGED)"), {

                "Cinco formas de acorde maior (C, A, G, E, D) cobrem todo o braço e se "
                "repetem a cada 12 casas, na ordem C → A → G → E → D.",
                "As formas conectam-se: a última nota de uma é a primeira da seguinte.",
                "A mesma forma vale para acordes menores e de 7ª (muda a qualidade).",
                "O CAGED é a ponte entre acorde e escala: cada forma contém a "
                "pentatônica/modo daquele centro."
            }), content::topicF()),
            detail (block ("G", juce::String::fromUTF8 ("Organização das tonalidades"), {

                "Campo harmônico maior: I – ii – iii – IV – V – vi – vii°. "
                "Em Dó: C – Dm – Em – F – G – Am – Bdim.",
                "Círculo das quintas: C → G → D → A → E → B → F# → C#…; cada passo "
                "acrescenta um sustenido. No sentido inverso, um bemol.",
                "Cada maior tem uma relativa menor com a mesma armadura (C ↔ Am)."
            }), content::topicG()),
            detail (block ("H", juce::String::fromUTF8 ("Introdução ao cifrado"), {

                "Cifrar é descrever o acorde de forma compacta: C (maior), Cm (menor), "
                "C7 (sétima dominante), C7M (sétima maior), Cm7 (menor com sétima).",
                "C/E indica baixo na nota após a barra; C(9) e C(#11) indicam tensões.",
                "Ler a cifra e achar a forma no braço (via CAGED) é a habilidade "
                "prática do módulo."
            }), content::topicH()),
            detail (block ("I", juce::String::fromUTF8 ("Rítmica: pulsação e figuras"), {

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
            }), content::topicI()),
        };

        m.exercises = {
            exercise ("EX-1.A.1", juce::String::fromUTF8 ("Questionário: conhecendo o instrumento"),
                      juce::String::fromUTF8 ("Responder ao teste de aprendizagem do Módulo 1, uma questão por vez."),
                      juce::String::fromUTF8 ("Acerto ≥90% nas questões do questionário.")),
            exercise ("EX-1.D.1", juce::String::fromUTF8 ("Corda 6ª e casa 5"),
                      juce::String::fromUTF8 ("Tocar a 6ª solta (Mi) e a casa 5 (Lá)."),
                      juce::String::fromUTF8 ("Detector: E2 solto e A2 na 5ª casa.")),
            exercise ("EX-1.B.1", juce::String::fromUTF8 ("Escala de Dó na 1ª posição"),
                      juce::String::fromUTF8 ("Tocar a escala de Dó em 2 oitavas."),
                      juce::String::fromUTF8 ("Sequência de notas esperada, 90% de acerto.")),
            exercise ("EX-1.F.1", juce::String::fromUTF8 ("Acordes simples"),
                      juce::String::fromUTF8 ("Montar C, G, D, Am, Em e identificar a forma CAGED."),
                      juce::String::fromUTF8 ("Detecção de acorde (soma de notas).")),
            exercise ("EX-1.E.1", juce::String::fromUTF8 ("Pestana de Fá"),
                      juce::String::fromUTF8 ("Pestana de F na 1ª casa; todas as cordas soam."),
                      juce::String::fromUTF8 ("Nível/ataque presente em todas as cordas.")),
            exercise ("EX-1.F.2", juce::String::fromUTF8 ("Mover a forma de E"),
                      juce::String::fromUTF8 ("Deslizar a forma de E e nomear o acorde."),
                      juce::String::fromUTF8 ("Identificar acorde pela região do braço.")),
            exercise ("EX-1.H.1", juce::String::fromUTF8 ("Cifrado e tonalidade"),
                      juce::String::fromUTF8 ("Dado Dm7, G7, C7M, dizer o campo harmônico e tocar as tríades."),
                      juce::String::fromUTF8 ("Detecção de acorde e resposta.")),
            exercise ("EX-1.I.1", juce::String::fromUTF8 ("Contar e tocar na grade"),
                      juce::String::fromUTF8 ("Contar em voz alta (TÁ / TÁ-KI) e tocar a 6ª solta em semínimas na grade do metrônomo a 60 BPM."),
                      juce::String::fromUTF8 ("on_grid_ratio ≥ 0,75 nas batidas (REQ-015).")),
            exercise ("EX-1.C.1", juce::String::fromUTF8 ("Sustenidos, bemóis e enarmonia"),
                      juce::String::fromUTF8 ("Nomear a nota que falta e dizer quais nomes são o mesmo som (enarmonia)."),
                      juce::String::fromUTF8 ("Acerto ≥90% nas questões de sustenidos, bemóis e enarmonia.")),
            exercise ("EX-1.G.1", juce::String::fromUTF8 ("Tonalidade e campo harmônico"),
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

        // EX-1.A.1 is the learning quiz of the module (Questionario_m1). Questions
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
        m.exercises[1].targets = notes ({ "E2", "A2" });                    // EX-1.D.1
        m.exercises[2].targets = notes ({ "C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5" }); // EX-1.B.1
        m.exercises[3].chordPitchClasses = { 0, 4, 7 };                     // EX-1.F.1, first C
        m.exercises[4].chordPitchClasses = { 5, 9, 0 };                     // EX-1.E.1, F barre
        m.exercises[7].targets = notes ({ "E2" });                          // EX-1.I.1, on the grid

        // EX-1.H.1 (topic H, cifrado) is playable: the student plays the ii–V–I of C
        // as the app recognises each chord (REQ-022 — every topic has an
        // executable exercise, not only a questionnaire).
        m.exercises[6].chordProgression = {
            { 2, 5, 9, 0 },    // Dm7
            { 7, 11, 2, 5 },   // G7
            { 0, 4, 7, 11 },   // C7M
        };

        // EX-1.C.1 and EX-1.G.1 are quizzes on topics C and G, so every topic A..I
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

        // --- Extra exercises: at least three per topic (client request). ------
        // The client asked for >= 3 exercises on every topic A..I. EX-1.A.1..EX-1.G.3
        // and the gate give each topic at least one; the exercises below complete
        // the set, mixing quizzes (verifiable) and playable specs (detector).
        m.exercises.emplace_back (exercise (
            "EX-1.A.2", juce::String::fromUTF8 ("Partes do instrumento: nomear"),
            juce::String::fromUTF8 ("Apontar e nomear as partes da guitarra e do violão."),
            juce::String::fromUTF8 ("Acerto ≥90% no questionário de partes do instrumento.")));
        m.exercises.back().lessonId = "A";
        m.exercises.back().quiz = {
            question ("O que é a pestana (nut)?",
                      { "A barra metálica onde os dedos pressionam",
                        "A peça que organiza as cordas no início do braço",
                        "O controle de volume",
                        "O captador" }, 1),
            question ("Qual peça transmite a vibração da corda ao corpo do violão?",
                      { "A tarraxa", "O cavalete (ponte)", "O traste", "A pestana" }, 1),
            question ("Na guitarra elétrica, o que transforma a vibração em sinal elétrico?",
                      { "O captador", "O rastilho", "A caixa de ressonância", "A escala" }, 0),
            question ("Qual é a função das tarraxas?",
                      { "Regular a tensão e a afinação das cordas",
                        "Amplificar o som",
                        "Sustentar os trastes",
                        "Abafar as cordas" }, 0),
            question ("Onde fica o tirante (truss rod)?",
                      { "Dentro do braço", "Dentro da caixa de ressonância",
                        "Na cabeça", "No captador" }, 0),
            question ("O que diferencia as cordas de nylon das de aço?",
                      { "O nylon produz som mais suave e menor tensão",
                        "O nylon produz som mais brilhante e metálico",
                        "São idênticas",
                        "O nylon só existe em guitarras" }, 0),
        };

        m.exercises.emplace_back (exercise (
            "EX-1.A.3", juce::String::fromUTF8 ("Identificar partes por região"),
            juce::String::fromUTF8 ("Dizer a que região do instrumento pertence cada peça."),
            juce::String::fromUTF8 ("Acerto ≥90% no questionário de regiões.")));
        m.exercises.back().lessonId = "A";
        m.exercises.back().quiz = {
            question ("Em que região fica o captador?",
                      { "Corpo", "Braço", "Cabeça", "Pestana" }, 0),
            question ("Em que região fica a escala (com os trastes)?",
                      { "Corpo", "Braço", "Cabeça", "Cavalete" }, 1),
            question ("Em que região ficam as tarraxas?",
                      { "Corpo", "Braço", "Cabeça", "Boca" }, 2),
            question ("O rastilho fica em qual peça?",
                      { "No cavalete", "Na pestana", "No cabeçote", "No tampo" }, 0),
        };

        // Topic B — notes.
        m.exercises.emplace_back (exercise (
            "EX-1.B.2", juce::String::fromUTF8 ("Nomear as notas naturais"),
            juce::String::fromUTF8 ("Dizer as sete notas naturais e suas cifras."),
            juce::String::fromUTF8 ("Acerto ≥90% no questionário de notas.")));
        m.exercises.back().lessonId = "B";
        m.exercises.back().quiz = {
            question ("Quais são as sete notas naturais?",
                      { "Dó Ré Mi Fá Sol Lá Si",
                        "Dó Ré Mi Fá Sol Lá Si Dó",
                        "Lá Si Dó Ré Mi Fá Sol",
                        "Dó Ré Mi Fá Sol Lá" }, 0),
            question ("Qual cifra corresponde ao Lá?",
                      { "A", "B", "G", "L" }, 0),
            question ("Qual cifra corresponde ao Ré?",
                      { "R", "D", "E", "C" }, 1),
            question ("Entre quais notas naturais há apenas um semitom?",
                      { "Dó–Ré e Fá–Sol", "Mi–Fá e Si–Dó",
                        "Ré–Mi e Sol–Lá", "Fá–Sol e Lá–Si" }, 1),
            question ("Depois do Si, qual nota vem subindo?",
                      { "Lá", "Dó", "Ré", "Mi" }, 1),
        };

        m.exercises.emplace_back (exercise (
            "EX-1.B.3", juce::String::fromUTF8 ("Tons e semitons"),
            juce::String::fromUTF8 ("Dizer a distância (tom ou semitom) entre notas naturais."),
            juce::String::fromUTF8 ("Acerto ≥90% no questionário de intervalos.")));
        m.exercises.back().lessonId = "B";
        m.exercises.back().quiz = {
            question ("Um tom equivale a quantos semitons?",
                      { "Meio semitom", "Um semitom", "Dois semitons", "Doze semitons" }, 2),
            question ("Qual é a distância entre Dó e Ré?",
                      { "Um semitom", "Um tom", "Dois tons", "Uma oitava" }, 1),
            question ("Qual é a distância entre Mi e Fá?",
                      { "Um semitom", "Um tom", "Dois tons", "Três semitons" }, 0),
            question ("Quantos semitons há de Dó a Dó (uma oitava)?",
                      { "7", "10", "12", "14" }, 2),
            question ("Qual é a distância entre Sol e Lá?",
                      { "Um semitom", "Um tom", "Dois tons", "Nenhuma" }, 1),
        };

        m.exercises.emplace_back (exercise (
            "EX-1.B.4", juce::String::fromUTF8 ("Cantar a nota junto com a corda"),
            juce::String::fromUTF8 ("Tocar a 6ª corda solta (Mi) e cantar a mesma nota."),
            juce::String::fromUTF8 ("Detector: E2 solto, sustentado por 2 segundos.")));
        m.exercises.back().lessonId = "B";
        m.exercises.back().targets = notes ({ "E2" });

        // Topic C — sharps, flats and enharmony (EX-1.C.1 already covers the topic).
        m.exercises.emplace_back (exercise (
            "EX-1.C.2", juce::String::fromUTF8 ("Sustenido e bemol no braço"),
            juce::String::fromUTF8 ("Tocar Fá e Fá♯ na 6ª corda; depois Si e Si♭."),
            juce::String::fromUTF8 ("Detector: F2, F♯2, B3, A♯3.")));
        m.exercises.back().lessonId = "C";
        m.exercises.back().targets = notes ({ "F2", "F#2", "B3", "A#3" });

        m.exercises.emplace_back (exercise (
            "EX-1.C.3", juce::String::fromUTF8 ("Escala cromática na 6ª corda"),
            juce::String::fromUTF8 ("Tocar a 6ª corda da casa 0 à casa 12, casa a casa."),
            juce::String::fromUTF8 ("Detector: 13 notas cromáticas de E2 a E3.")));
        m.exercises.back().lessonId = "C";
        m.exercises.back().targets = notes ({
            "E2", "F2", "F#2", "G2", "G#2", "A2", "A#2", "B2",
            "C3", "C#3", "D3", "D#3", "E3" });

        // Topic D — fretboard location (EX-1.D.1 and EX-1.B.1 already cover it).
        m.exercises.emplace_back (exercise (
            "EX-1.D.2", juce::String::fromUTF8 ("Oitavas: mesma nota, duas cordas"),
            juce::String::fromUTF8 ("Tocar E2 na 6ª solta e E3 na casa 12 da 6ª."),
            juce::String::fromUTF8 ("Detector: E2 e E3, uma oitava de diferença.")));
        m.exercises.back().lessonId = "D";
        m.exercises.back().targets = notes ({ "E2", "E3" });

        m.exercises.emplace_back (exercise (
            "EX-1.D.3", juce::String::fromUTF8 ("Casa 5 = corda de baixo solta"),
            juce::String::fromUTF8 ("Tocar a casa 5 da 6ª (Lá) e a 5ª corda solta (Lá)."),
            juce::String::fromUTF8 ("Detector: A2 tocado duas vezes (mesma nota).")));
        m.exercises.back().lessonId = "D";
        m.exercises.back().targets = notes ({ "A2", "A2" });

        // Topic E — barre (EX-1.E.1 already covers it).
        m.exercises.emplace_back (exercise (
            "EX-1.E.2", juce::String::fromUTF8 ("Meio barré de Si menor"),
            juce::String::fromUTF8 ("Fazer o meio barré de Bm na 2ª casa; cordas limpas."),
            juce::String::fromUTF8 ("Detector: acorde Bm (Si Ré Fá♯).")));
        m.exercises.back().lessonId = "E";
        m.exercises.back().chordPitchClasses = { 11, 2, 6 };

        m.exercises.emplace_back (exercise (
            "EX-1.E.3", juce::String::fromUTF8 ("Pestana: teoria e posição"),
            juce::String::fromUTF8 ("Responder sobre pestana completa, meio barré e posição."),
            juce::String::fromUTF8 ("Acerto ≥90% no questionário de pestana.")));
        m.exercises.back().lessonId = "E";
        m.exercises.back().quiz = {
            question ("O que é uma pestana completa (barré)?",
                      { "Um dedo pressionando todas as cordas numa casa",
                        "Dois dedos pressionando uma corda",
                        "Um acorde sem pestana",
                        "Uma corda solta" }, 0),
            question ("Quantas cordas um meio barré costuma cobrir?",
                      { "Todas as seis", "Apenas uma", "De 2 a 4", "Nenhuma" }, 2),
            question ("Onde o dedo deve ficar para a pestana soar limpa?",
                      { "No meio da casa", "Logo atrás do traste",
                        "Em cima do traste", "Fora do braço" }, 1),
            question ("Onde o polegar deve ficar para dar alavanca?",
                      { "Aproximado do centro do braço", "Muito acima do braço",
                        "Solto, sem tocar", "Cruzado na frente" }, 0),
            question ("Por que uma corda abafa no meio da pestana?",
                      { "Por falta de força sempre",
                        "Por causa dos vales entre as falanges do dedo",
                        "Porque a corda está solta",
                        "Porque o traste está gasto" }, 1),
        };

        // Topic F — CAGED (EX-1.F.1 and EX-1.F.2 already cover it).
        m.exercises.emplace_back (exercise (
            "EX-1.F.3", juce::String::fromUTF8 ("As cinco formas do CAGED"),
            juce::String::fromUTF8 ("Tocar as formas C, A, G, E, D de Dó maior."),
            juce::String::fromUTF8 ("Detector: C maior em cinco regiões do braço.")));
        m.exercises.back().lessonId = "F";
        m.exercises.back().chordProgression = {
            { 0, 4, 7 },   // C  (forma C)
            { 0, 4, 7 },   // C  (forma A)
            { 0, 4, 7 },   // C  (forma G)
            { 0, 4, 7 },   // C  (forma E)
            { 0, 4, 7 },   // C  (forma D)
        };

        m.exercises.emplace_back (exercise (
            "EX-1.F.4", juce::String::fromUTF8 ("Nomear o acorde pela forma"),
            juce::String::fromUTF8 ("Mover a forma de A e dizer o acorde em cada casa."),
            juce::String::fromUTF8 ("Acerto ≥90% no questionário de formas móveis.")));
        m.exercises.back().lessonId = "F";
        m.exercises.back().quiz = {
            question ("Quais letras formam o sistema CAGED?",
                      { "C A G E D", "D G B E A", "A B C D E", "C D E F G" }, 0),
            question ("Em que ordem as formas aparecem subindo pelo braço?",
                      { "C → A → G → E → D", "D → E → G → A → C",
                        "A → B → C → D → E", "G → C → D → A → E" }, 0),
            question ("A forma de E tem a fundamental em qual corda?",
                      { "4ª corda", "5ª corda", "6ª corda", "1ª corda" }, 2),
            question ("A forma de D tem a fundamental em qual corda?",
                      { "4ª corda", "5ª corda", "6ª corda", "2ª corda" }, 0),
            question ("O CAGED serve também para acordes menores?",
                      { "Sim, mudando a qualidade da forma",
                        "Não, só para maiores",
                        "Só na primeira posição",
                        "Não, apenas para escalas" }, 0),
        };

        // Topic G — key organisation (EX-1.G.1 already covers it).
        m.exercises.emplace_back (exercise (
            "EX-1.G.2", juce::String::fromUTF8 ("Campo harmônico de Dó"),
            juce::String::fromUTF8 ("Tocar I–vi–IV–V em Dó: C – Am – F – G."),
            juce::String::fromUTF8 ("Detector: sequência C, Am, F, G.")));
        m.exercises.back().lessonId = "G";
        m.exercises.back().chordProgression = {
            { 0, 4, 7 },   // C
            { 9, 0, 4 },   // Am
            { 5, 9, 0 },   // F
            { 7, 11, 2 },  // G
        };

        m.exercises.emplace_back (exercise (
            "EX-1.G.3", juce::String::fromUTF8 ("Escala maior: padrão de tons"),
            juce::String::fromUTF8 ("Tocar a escala de Dó maior e confirmar o padrão T–T–S–T–T–T–S."),
            juce::String::fromUTF8 ("Detector: C4 a C5 (oito notas da escala).")));
        m.exercises.back().lessonId = "G";
        m.exercises.back().targets = notes ({ "C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5" });

        // Topic H — chord symbols (EX-1.H.1 already covers it).
        m.exercises.emplace_back (exercise (
            "EX-1.H.2", juce::String::fromUTF8 ("Ler cifras de acorde"),
            juce::String::fromUTF8 ("Dizer o significado de C, Cm, C7, C7M, Cm7 e C/E."),
            juce::String::fromUTF8 ("Acerto ≥90% no questionário de cifras.")));
        m.exercises.back().lessonId = "H";
        m.exercises.back().quiz = {
            question ("O que significa Cm7?",
                      { "Dó maior com sétima", "Dó menor com sétima",
                        "Dó menor sem sétima", "Dó aumentado" }, 1),
            question ("O que significa C/E?",
                      { "Dó maior com Mi no baixo", "Dó dividido por Mi",
                        "Mi maior com Dó no baixo", "Dois acordes ao mesmo tempo" }, 0),
            question ("Qual cifra indica sétima maior?",
                      { "C7", "C7M", "Cm7", "Cdim" }, 1),
            question ("Uma letra sem símbolo (por exemplo, G) indica qual acorde?",
                      { "Sol menor", "Sol maior", "Sol diminuto", "Sol com sétima" }, 1),
            question ("O que C(#11) acrescenta?",
                      { "Uma nona", "Uma quarta aumentada", "Uma sexta", "Um baixo em Mi" }, 1),
        };

        m.exercises.emplace_back (exercise (
            "EX-1.H.3", juce::String::fromUTF8 ("Tocar uma cifra com inversão"),
            juce::String::fromUTF8 ("Tocar C/E (Dó maior com Mi no baixo)."),
            juce::String::fromUTF8 ("Detector: acorde C maior com baixo em E.")));
        m.exercises.back().lessonId = "H";
        m.exercises.back().chordProgression = {
            { 0, 4, 7 },   // C with E in the bass
        };

        // Topic I — rhythm (EX-1.I.1 already covers it).
        m.exercises.emplace_back (exercise (
            "EX-1.I.2", juce::String::fromUTF8 ("Colcheias na grade"),
            juce::String::fromUTF8 ("Tocar a 6ª solta em colcheias (TÁ-KI) a 60 BPM."),
            juce::String::fromUTF8 ("on_grid_ratio ≥ 0,75 em subdivisão de colcheia.")));
        m.exercises.back().lessonId = "I";
        m.exercises.back().targets = notes ({ "E2" });
        m.exercises.back().subdivision = course::TempoGrid::Subdivision::eighth;
        m.exercises.back().onGridTarget = 0.75f;

        m.exercises.emplace_back (exercise (
            "EX-1.I.3", juce::String::fromUTF8 ("Figuras rítmicas e valores"),
            juce::String::fromUTF8 ("Dizer o valor das figuras e as sílabas rítmicas."),
            juce::String::fromUTF8 ("Acerto ≥90% no questionário de rítmica.")));
        m.exercises.back().lessonId = "I";
        m.exercises.back().quiz = {
            question ("Quantos tempos vale uma semínima?",
                      { "4 tempos", "2 tempos", "1 tempo", "Meio tempo" }, 2),
            question ("Quantas colcheias cabem em um tempo?",
                      { "1", "2", "3", "4" }, 1),
            question ("Qual sílaba rítmica corresponde a duas colcheias?",
                      { "TÁ", "TÁ-KI", "TA-KI-TA-KI", "TÁ-A" }, 1),
            question ("O que o ponto de aumento faz com a figura?",
                      { "Dobra o valor", "Soma metade do valor",
                        "Nada", "Divide o valor por dois" }, 1),
            question ("Em 4/4, quantos tempos há por compasso?",
                      { "2", "3", "4", "6" }, 2),
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

    // Module 2 — Etapa 2: teoria dos intervalos e percepção musical. The client
    // asked the student to start identifying what is played: part of the
    // exercises is played on the instrument and the app recognises the notes to
    // check the interval (Exercise::interval). The explanation carries images,
    // audio examples (ContentKind::audio) and scores with their audio
    // (ContentKind::score), and every topic has >=5 pages (content::minTopicChars).
    CourseModule makeModule2()
    {
        CourseModule m;
        m.number = 2;
        m.title = juce::String::fromUTF8 ("Teoria dos intervalos e percepção musical");
        m.objective = juce::String::fromUTF8 (
            "Compreender a distância entre as notas e desenvolver a capacidade de "
            "identificar sonoridades — pelo instrumento e de ouvido.");
        m.level = 1;          // MUSIC.md: módulos 1–2 = nível 1
        m.targetBpm = 64;     // MUSIC.md, módulo 2
        m.onGridTarget = 0.76f;
        m.implemented = true;

        m.lessons = {
            detail (block ("A", juce::String::fromUTF8 ("Intervalos musicais"), {
                "Intervalo é a distância entre duas notas, medida em semitons.",
                "Melódico (notas em sequência) e harmônico (notas juntas).",
                "O número vem da contagem das letras; a qualidade, dos semitons."
            }), content::topic2A()),
            detail (block ("B", juce::String::fromUTF8 ("Quadro móvel de intervalos"), {
                "Tabela dos doze semitons com o nome de cada intervalo.",
                "É móvel: vale a partir de qualquer nota de partida.",
                "No braço, cada corda é uma linha do quadro."
            }), content::topic2B()),
            detail (block ("C", juce::String::fromUTF8 ("Maiores, menores, justos, aumentados e diminutos"), {
                "Justos: uníssono, quarta, quinta e oitava.",
                "Maiores e menores: segunda, terça, sexta e sétima.",
                "Aumentado alarga o padrão; diminuto estreita."
            }), content::topic2C()),
            detail (block ("D", juce::String::fromUTF8 ("Percepção de intervalos"), {
                "Reconhecer a distância pelo ouvido, sem olhar o braço.",
                "Consonantes soam estáveis; dissonantes soam tensos.",
                "Reconheça em três passos: direção, tamanho, qualidade."
            }), content::topic2D()),
            detail (block ("E", juce::String::fromUTF8 ("Terças, quartas, quintas, sextas, sétimas e nonas"), {
                "A terça define maior ou menor; é o coração do acorde.",
                "Quarta e quinta dão movimento e estabilidade.",
                "Sexta, sétima e nona dão cor, tensão e identidade."
            }), content::topic2E()),
            detail (block ("F", juce::String::fromUTF8 ("Relação entre intervalos e construção de acordes"), {
                "Um acorde é um conjunto de intervalos empilhados sobre a tônica.",
                "Tríade = tônica, terça e quinta; tétrade acrescenta a sétima.",
                "Inversões mudam o baixo, não o acorde."
            }), content::topic2F()),
            detail (block ("G", juce::String::fromUTF8 ("Cantar e tocar os intervalos"), {
                "Cantar desenvolve a memória auditiva e liga ouvido e mão.",
                "Cante a partir de uma nota de referência, subindo aos poucos.",
                "Cante antes de tocar; depois toque e deixe o app conferir."
            }), content::topic2G()),
            detail (block ("H", juce::String::fromUTF8 ("Identificar intervalos no instrumento e de ouvido"), {
                "Identificar é dizer número, qualidade e sensação.",
                "Pelo instrumento, o app mede os semitons e valida.",
                "De ouvido, reconheça direção, tamanho e qualidade."
            }), content::topic2H()),
        };

        // Exercises: at least three per topic, mixing verifiable quizzes (ear
        // training) and playable interval exercises (the app recognises the
        // notes). Ids follow EX-2.<topico>.<n>, numbered per topic, as module 1.
        auto add = [&m] (Exercise e, const char* topic)
        {
            e.lessonId = topic;
            m.exercises.push_back (std::move (e));
            return (int) m.exercises.size() - 1;
        };

        // --- Topic A — intervalos musicais -----------------------------------
        add (exercise ("EX-2.A.1", juce::String::fromUTF8 ("Questionário: o que é intervalo"),
                       juce::String::fromUTF8 ("Responder ao questionário de introdução aos intervalos."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de intervalo.")), "A");
        m.exercises.back().quiz = {
            question ("O que é um intervalo musical?",
                      { "A distância entre duas notas",
                        "O volume de uma nota",
                        "A duração de um acorde",
                        "O número de cordas" }, 0),
            question ("Quantos semitons há em um tom?",
                      { "1", "2", "3", "12" }, 1),
            question ("Na guitarra, um semitom corresponde a quantas casas?",
                      { "Uma casa", "Duas casas", "Cinco casas", "Doze casas" }, 0),
            question ("Quando as duas notas soam juntas, o intervalo é:",
                      { "melódico", "harmônico", "enarmônico", "cromático" }, 1),
            question ("Quantos semitons tem uma oitava?",
                      { "7", "10", "12", "14" }, 2),
        };
        add (intervalExercise ("EX-2.A.2", "Tocar uma terça maior",
                               "Tocar uma terça maior (4 semitons) a partir de qualquer nota, três vezes.",
                               4, 3), "A");
        add (intervalExercise ("EX-2.A.3", "Tocar uma segunda maior",
                               "Tocar uma segunda maior (2 semitons), duas vezes.",
                               2, 2), "A");
        add (exercise ("EX-2.A.4", juce::String::fromUTF8 ("Nomear intervalos do quadro"),
                       juce::String::fromUTF8 ("Dizer o número e a qualidade de intervalos básicos."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário de nomes.")), "A");
        m.exercises.back().quiz = {
            question ("Qual intervalo tem 4 semitons?",
                      { "terça menor", "terça maior", "quarta justa", "segunda maior" }, 1),
            question ("Qual intervalo tem 7 semitons?",
                      { "quarta justa", "quinta justa", "sexta maior", "sétima menor" }, 1),
            question ("Qual intervalo tem 5 semitons?",
                      { "quarta justa", "quarta aumentada", "terça maior", "quinta justa" }, 0),
            question ("Qual intervalo é o trítono?",
                      { "4 semitons", "5 semitons", "6 semitons", "7 semitons" }, 2),
        };

        // --- Topic B — quadro móvel ------------------------------------------
        add (exercise ("EX-2.B.1", juce::String::fromUTF8 ("Questionário: quadro móvel"),
                       juce::String::fromUTF8 ("Responder ao questionário do quadro móvel."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões do quadro móvel.")), "B");
        m.exercises.back().quiz = {
            question ("O que significa dizer que o quadro de intervalos é móvel?",
                      { "Que ele vale a partir de qualquer nota de partida",
                        "Que ele muda de nome a cada compasso",
                        "Que ele só serve para Dó",
                        "Que ele só existe no papel" }, 0),
            question ("No quadro, qual intervalo está a 4 semitons da tônica?",
                      { "terça menor", "terça maior", "quarta justa", "quinta justa" }, 1),
            question ("Qual intervalo fica no centro do quadro (6 semitons)?",
                      { "quinta justa", "trítono", "sexta maior", "oitava" }, 1),
            question ("A 9 semitons da tônica está qual intervalo?",
                      { "sexta menor", "sexta maior", "sétima menor", "sétima maior" }, 1),
        };
        add (intervalExercise ("EX-2.B.2", "Quarta justa no quadro",
                               "Tocar uma quarta justa (5 semitons), três vezes.", 5, 3), "B");
        add (intervalExercise ("EX-2.B.3", "Quinta justa no quadro",
                               "Tocar uma quinta justa (7 semitons), três vezes.", 7, 3), "B");
        add (exercise ("EX-2.B.4", juce::String::fromUTF8 ("Ler o quadro em outras tônicas"),
                       juce::String::fromUTF8 ("Aplicar o quadro a partir de Sol e de Lá."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário de transposição.")), "B");
        m.exercises.back().quiz = {
            question ("4 semitons acima de Sol caem em qual nota?",
                      { "Lá", "Si", "Dó", "Ré" }, 1),
            question ("7 semitons acima de Lá caem em qual nota?",
                      { "Mi", "Ré", "Dó", "Fá" }, 0),
            question ("O nome do intervalo depende de quê?",
                      { "Da nota de partida",
                        "Da distância em semitons",
                        "Do volume",
                        "Da corda usada" }, 1),
            question ("A 12 semitons de qualquer nota, qual intervalo ocorre?",
                      { "quinta justa", "sétima maior", "oitava justa", "sexta maior" }, 2),
        };

        // --- Topic C — qualidades --------------------------------------------
        add (exercise ("EX-2.C.1", juce::String::fromUTF8 ("Questionário: qualidades dos intervalos"),
                       juce::String::fromUTF8 ("Responder ao questionário de qualidades."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de qualidade.")), "C");
        m.exercises.back().quiz = {
            question ("Quais intervalos são justos?",
                      { "1ª, 4ª, 5ª e 8ª", "2ª, 3ª, 6ª e 7ª", "só a 5ª", "todos os intervalos" }, 0),
            question ("A diferença entre terça maior e terça menor é de:",
                      { "um tom", "um semitom", "meio semitom", "uma oitava" }, 1),
            question ("Um intervalo aumentado é:",
                      { "o padrão alargado em um semitom",
                        "o padrão estreitado em um semitom",
                        "o dobro da oitava",
                        "sempre o trítono" }, 0),
            question ("Quarta aumentada e quinta diminuta têm quantos semitons cada?",
                      { "5", "6", "7", "8" }, 1),
            question ("Qual qualidade a terça maior tem?",
                      { "justa", "maior", "menor", "diminuta" }, 1),
        };
        add (intervalExercise ("EX-2.C.2", "Terça maior",
                               "Tocar uma terça maior (4 semitons), três vezes.", 4, 3), "C");
        add (intervalExercise ("EX-2.C.3", "Terça menor",
                               "Tocar uma terça menor (3 semitons), três vezes.", 3, 3), "C");
        add (intervalExercise ("EX-2.C.4", "Trítono",
                               "Tocar um trítono (6 semitons), duas vezes.", 6, 2), "C");
        add (exercise ("EX-2.C.5", juce::String::fromUTF8 ("Enarmonia de intervalos"),
                       juce::String::fromUTF8 ("Reconhecer intervalos enarmônicos."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de enarmonia.")), "C");
        m.exercises.back().quiz = {
            question ("Dois intervalos enarmônicos:",
                      { "têm o mesmo som e nomes diferentes",
                        "têm nomes iguais e sons diferentes",
                        "são sempre iguais",
                        "nunca ocorrem" }, 0),
            question ("Dó–Fá# e Dó–Solb são, respectivamente:",
                      { "quarta aumentada e quinta diminuta",
                        "quarta justa e quinta justa",
                        "terça maior e terça menor",
                        "quinta e sexta" }, 0),
            question ("Estreitar um intervalo justo em um semitom o torna:",
                      { "maior", "aumentado", "diminuto", "enarmônico" }, 2),
        };

        // --- Topic D — percepção ---------------------------------------------
        add (exercise ("EX-2.D.1", juce::String::fromUTF8 ("Questionário: percepção"),
                       juce::String::fromUTF8 ("Responder ao questionário de percepção de intervalos."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de percepção.")), "D");
        m.exercises.back().quiz = {
            question ("Quais intervalos soam consonantes (estáveis)?",
                      { "segundas e sétimas",
                        "oitava, quinta, quarta, terças e sextas",
                        "só o trítono",
                        "nenhum" }, 1),
            question ("O trítono costuma soar:",
                      { "estável e repousado", "tenso e instável",
                        "igual à oitava", "idêntico à quinta" }, 1),
            question ("Ao reconhecer um intervalo de ouvido, o primeiro passo é:",
                      { "decidir a direção (sobe ou desce)",
                        "olhar o braço",
                        "contar as cordas",
                        "ver o volume" }, 0),
            question ("Uma referência para a quinta justa é:",
                      { "som vazio e grandioso", "som tenso", "melodia triste", "mesma nota" }, 0),
        };
        add (exercise ("EX-2.D.2", juce::String::fromUTF8 ("Classificar consonância"),
                       juce::String::fromUTF8 ("Dizer se o intervalo é consonante ou dissonante."),
                       juce::String::fromUTF8 ("Acerto ≥90% na classificação.")), "D");
        m.exercises.back().quiz = {
            question ("A terça maior é consonante ou dissonante?",
                      { "consonante", "dissonante", "nem um nem outro", "depende do volume" }, 0),
            question ("A segunda maior é:",
                      { "consonante", "dissonante", "justa", "aumentada" }, 1),
            question ("A quinta justa é:",
                      { "consonante", "dissonante", "diminuta", "aumentada" }, 0),
            question ("A sétima maior é:",
                      { "consonante", "dissonante", "justa", "igual à oitava" }, 1),
        };
        add (intervalExercise ("EX-2.D.3", "Sexta maior",
                               "Tocar uma sexta maior (9 semitons), duas vezes.", 9, 2), "D");
        add (exercise ("EX-2.D.4", juce::String::fromUTF8 ("Identificar de ouvido"),
                       juce::String::fromUTF8 ("Ouvir os exemplos e nomear os intervalos."),
                       juce::String::fromUTF8 ("Acerto ≥90% na identificação.")), "D");
        m.exercises.back().quiz = {
            question ("Um som que parece a mesma nota, mais aguda, é:",
                      { "a oitava", "a quinta", "a terça", "o trítono" }, 0),
            question ("Um som firme, de chamada, lembra:",
                      { "a quarta justa", "a sétima maior", "a segunda menor", "a oitava" }, 0),
            question ("Um som alegre e aberto sugere:",
                      { "terça maior", "terça menor", "trítono", "sétima menor" }, 0),
        };

        // --- Topic E — terças a nonas ----------------------------------------
        add (exercise ("EX-2.E.1", juce::String::fromUTF8 ("Questionário: intervalos práticos"),
                       juce::String::fromUTF8 ("Responder ao questionário dos intervalos práticos."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "E");
        m.exercises.back().quiz = {
            question ("Qual intervalo define se um acorde é maior ou menor?",
                      { "a quinta", "a terça", "a sétima", "a nona" }, 1),
            question ("O power chord usa quais intervalos?",
                      { "tônica e terça", "tônica e quinta", "tônica e sétima", "tônica e nona" }, 1),
            question ("A nona é o mesmo intervalo que:",
                      { "a segunda, uma oitava acima", "a terça", "a quarta", "a sétima" }, 0),
            question ("Qual intervalo dá o som do blues e do dominante?",
                      { "sétima maior", "sétima menor", "sexta maior", "quarta justa" }, 1),
            question ("A sexta maior tem quantos semitons?",
                      { "8", "9", "10", "11" }, 1),
        };
        add (intervalExercise ("EX-2.E.2", "Terça (coração do acorde)",
                               "Tocar uma terça maior (4 semitons), três vezes.", 4, 3), "E");
        add (intervalExercise ("EX-2.E.3", "Quinta (estabilidade)",
                               "Tocar uma quinta justa (7 semitons), três vezes.", 7, 3), "E");
        add (intervalExercise ("EX-2.E.4", "Sétima maior",
                               "Tocar uma sétima maior (11 semitons), duas vezes.", 11, 2), "E");
        add (exercise ("EX-2.E.5", juce::String::fromUTF8 ("Papel de cada intervalo"),
                       juce::String::fromUTF8 ("Relacionar cada intervalo ao seu papel musical."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário de papéis.")), "E");
        m.exercises.back().quiz = {
            question ("Qual intervalo dá movimento e suspensão?",
                      { "quarta justa", "quinta justa", "oitava", "terça maior" }, 0),
            question ("A sétima maior produz um som:",
                      { "brilhante e suspenso", "tenso e de blues",
                        "igual à oitava", "fechado e triste" }, 0),
            question ("Acordes com nona têm:",
                      { "som mais rico, sem perder a identidade",
                        "som sempre menor",
                        "apenas duas notas",
                        "nenhuma terça" }, 0),
        };

        // --- Topic F — acordes -----------------------------------------------
        add (exercise ("EX-2.F.1", juce::String::fromUTF8 ("Questionário: intervalos e acordes"),
                       juce::String::fromUTF8 ("Responder ao questionário de construção de acordes."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de acordes.")), "F");
        m.exercises.back().quiz = {
            question ("Uma tríade maior é formada por quais intervalos (em semitons)?",
                      { "0, 4, 7", "0, 3, 7", "0, 3, 6", "0, 4, 8" }, 0),
            question ("Uma tríade menor usa quais intervalos?",
                      { "0, 4, 7", "0, 3, 7", "0, 3, 6", "0, 4, 8" }, 1),
            question ("Acrescentar a sétima menor (10 semitons) a uma tríade maior forma:",
                      { "acorde de sétima maior", "acorde de sétima dominante",
                        "acorde diminuto", "acorde suspenso" }, 1),
            question ("Uma inversão de acorde muda:",
                      { "a nota do baixo", "as notas do acorde",
                        "a tonalidade", "o número de notas" }, 0),
            question ("As tensões 9, 11 e 13 são:",
                      { "intervalos uma oitava acima dos graus 2, 4 e 6",
                        "notas fora da escala",
                        "acordes inteiros",
                        "sinônimos de 1, 3 e 5" }, 0),
        };
        add (exercise ("EX-2.F.2", juce::String::fromUTF8 ("Montar a tríade maior"),
                       juce::String::fromUTF8 ("Tocar uma tríade maior (tônica, terça maior e quinta justa)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere os intervalos da tríade maior.")), "F");
        m.exercises.back().chordPitchClasses = { 0, 4, 7 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-2.F.3", juce::String::fromUTF8 ("Montar a tríade menor"),
                       juce::String::fromUTF8 ("Tocar uma tríade menor (tônica, terça menor e quinta justa)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere os intervalos da tríade menor.")), "F");
        m.exercises.back().chordPitchClasses = { 0, 3, 7 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-2.F.4", juce::String::fromUTF8 ("Da tríade à tétrade"),
                       juce::String::fromUTF8 ("Dizer qual sétima transforma a tríade em cada tétrade."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário de tétrades.")), "F");
        m.exercises.back().quiz = {
            question ("C7M (sétima maior) usa qual sétima?",
                      { "11 semitons (sétima maior)", "10 semitons (sétima menor)",
                        "9 semitons", "12 semitons" }, 0),
            question ("Cm7 usa qual sétima?",
                      { "11 semitons", "10 semitons", "6 semitons", "7 semitons" }, 1),
            question ("A diferença entre C7M e C7 está:",
                      { "na terça", "na quinta", "na sétima", "na tônica" }, 2),
            question ("Um acorde meio-diminuto tem os intervalos:",
                      { "0, 3, 6, 10", "0, 4, 7, 11", "0, 3, 7, 10", "0, 4, 8, 11" }, 0),
        };

        // --- Topic G — cantar e tocar ----------------------------------------
        add (exercise ("EX-2.G.1", juce::String::fromUTF8 ("Questionário: cantar e tocar"),
                       juce::String::fromUTF8 ("Responder ao questionário do treino de canto."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "G");
        m.exercises.back().quiz = {
            question ("Por que cantar ajuda a tocar de ouvido?",
                      { "Porque desenvolve a memória auditiva e liga ouvido e mão",
                        "Porque aumenta a força dos dedos",
                        "Porque afina o instrumento",
                        "Porque substitui a prática" }, 0),
            question ("O melhor momento para cantar o intervalo é:",
                      { "antes de tocar", "depois de errar", "só no fim", "nunca" }, 0),
            question ("Cantar a partir de uma nota de referência serve para:",
                      { "comparar alturas com uma base fixa",
                        "mudar a tonalidade da música",
                        "aumentar o volume",
                        "afinar as cordas" }, 0),
            question ("Cantar um intervalo harmônico é mais difícil porque:",
                      { "as duas notas soam ao mesmo tempo",
                        "é sempre mais grave",
                        "não tem som",
                        "é sempre menor" }, 0),
        };
        add (intervalExercise ("EX-2.G.2", "Cantar e tocar a terça",
                               "Cantar e tocar uma terça maior (4 semitons), três vezes.", 4, 3), "G");
        add (intervalExercise ("EX-2.G.3", "Cantar e tocar a quinta",
                               "Cantar e tocar uma quinta justa (7 semitons), três vezes.", 7, 3), "G");
        add (exercise ("EX-2.G.4", juce::String::fromUTF8 ("Do exercício para a música"),
                       juce::String::fromUTF8 ("Identificar intervalos de uma melodia simples."),
                       juce::String::fromUTF8 ("Acerto ≥90% na identificação.")), "G");
        m.exercises.back().quiz = {
            question ("Identificar intervalos de ouvido permite:",
                      { "tirar melodias de ouvido e tocar de memória",
                        "afinar sem afinador",
                        "aumentar o volume",
                        "mudar a afinação das cordas" }, 0),
            question ("O ciclo do treino de intervalos é:",
                      { "ouvir, cantar, tocar e conferir",
                        "tocar, errar, parar",
                        "ler, escrever, apagar",
                        "afinar, tocar, guardar" }, 0),
            question ("Cantar a nota antes de tocar ajuda porque:",
                      { "o dedo executa uma ideia clara em vez de procurar às cegas",
                        "o som fica mais alto",
                        "a corda vibra mais",
                        "o metrônomo acelera" }, 0),
        };

        // --- Topic H — identificar -------------------------------------------
        add (exercise ("EX-2.H.1", juce::String::fromUTF8 ("Questionário: identificar intervalos"),
                       juce::String::fromUTF8 ("Responder ao questionário de identificação."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "H");
        m.exercises.back().quiz = {
            question ("Identificar um intervalo é dizer:",
                      { "número, qualidade e sensação",
                        "apenas o número",
                        "apenas a nota de partida",
                        "o volume" }, 0),
            question ("No instrumento, o app identifica o intervalo medindo:",
                      { "a distância em semitons entre as notas tocadas",
                        "o volume das notas",
                        "a duração das notas",
                        "a corda usada" }, 0),
            question ("Ao confundir terça maior e quarta justa, conte:",
                      { "4 contra 5 semitons", "2 contra 3 semitons",
                        "7 contra 8 semitons", "11 contra 12 semitons" }, 0),
            question ("Sétima maior e oitava têm, respectivamente:",
                      { "11 e 12 semitons", "10 e 11 semitons",
                        "9 e 10 semitons", "12 e 13 semitons" }, 0),
            question ("Uma boa dica antes de responder é:",
                      { "cantar a nota de referência",
                        "olhar o braço",
                        "aumentar o volume",
                        "tocar mais rápido" }, 0),
        };
        add (intervalExercise ("EX-2.H.2", "Identificar a terça maior",
                               "Tocar uma terça maior (4 semitons) em qualquer posição, três vezes.", 4, 3), "H");
        add (intervalExercise ("EX-2.H.3", "Identificar a quinta justa",
                               "Tocar uma quinta justa (7 semitons) em qualquer posição, três vezes.", 7, 3), "H");
        add (exercise ("EX-2.H.4", juce::String::fromUTF8 ("Identificar de ouvido"),
                       juce::String::fromUTF8 ("Ouvir os exemplos e nomear os intervalos."),
                       juce::String::fromUTF8 ("Acerto ≥90% na identificação de ouvido.")), "H");
        m.exercises.back().quiz = {
            question ("Um som tenso, quase desafinado, sugere:",
                      { "o trítono", "a oitava", "a quinta justa", "a terça maior" }, 0),
            question ("Um som que pede resolução, de blues, sugere:",
                      { "sétima menor", "sétima maior", "quarta justa", "oitava" }, 0),
            question ("A terça maior tem quantos semitons?",
                      { "3", "4", "5", "7" }, 1),
            question ("A quinta justa tem quantos semitons?",
                      { "5", "6", "7", "8" }, 2),
        };

        // The gate closes the module: play a I–IV–V–I vamp on the grid, built
        // from the intervals of the tonic (REQ-009, REQ-015).
        auto& gate = m.exercises.emplace_back (exercise (
            "GATE-2", juce::String::fromUTF8 ("Desafio de gate — vamp C–F–G–C"),
            juce::String::fromUTF8 ("Tocar C – F – G – C a 64 BPM, na grade do metrônomo."),
            juce::String::fromUTF8 ("Acordes reconhecidos e alinhados à grade (≥ 0,76).")));
        gate.isGate = true;
        gate.lessonId = "H";
        gate.chordProgression = {
            { 0, 4, 7 },    // C
            { 5, 9, 0 },    // F
            { 7, 11, 2 },   // G
            { 0, 4, 7 },    // C
        };

        m.gateChallenge = juce::String::fromUTF8 (
            "Tocar C – F – G – C (vamp de 1 acorde, nível 1) a 64 BPM com ≥90% de "
            "acerto de acordes e on_grid_ratio ≥ 0,76. Os acordes são construídos "
            "pelos intervalos estudados no módulo.");

        // Pattern and link the module must cite (REQ-007, REQ-010).
        m.practice.patternId = "PTN-M-3rds";
        m.practice.patternUse = juce::String::fromUTF8 (
            "Terças: o padrão 1-3, 2-4, 3-5… percorre a escala saltando um grau, o "
            "que faz o aluno ouvir o intervalo de terça em movimento. Complemento: "
            "PTN-M-4ths (quartas) para contrastar com as terças.");
        m.practice.guitarists = { "John Petrucci", "Guthrie Govan", "Steve Vai" };

        // Curated apostilas (REQ-006, CM-012); see docs/MUSIC.md §2.1.
        m.sources = {
            "pdf-teoria-elementar-da-musica-ricordi-osvaldo-lacerda",
            "pdf-p-classtruncatedtext-module-lineclamped-85ulhh-style-max-lines5bohumil-med-teoria-da-musica-5-edicao-p",
            "pdf-mozart-mello-livroestudosdeguitarra4em1",
            "pdf-caged-e-derivaoes-de-acordes-marcelo-mello-apostila-de-violao-e-guitarra-vol1",
        };

        return m;
    }

    // Module 6 — Etapa 6: escalas menores e campos harmônicos. It follows the
    // module-2 pattern: >=5 pages per topic with images, tables, audio and
    // scores (each score with its own audio), 3..5 exercises per topic mixing
    // verifiable quizzes and playable exercises the app recognises, and a gate
    // that closes the module on the grid (REQ-009, REQ-015).
    CourseModule makeModule6()
    {
        CourseModule m;
        m.number = 6;
        m.title = juce::String::fromUTF8 ("Escalas menores e campos harmônicos");
        m.objective = juce::String::fromUTF8 (
            "Ampliar a compreensão harmônica e melódica para as tonalidades menores: "
            "as três escalas menores, os seus modos e os campos harmônicos menores.");
        m.level = 3;          // MUSIC.md: módulos 5–7 = nível 3
        m.targetBpm = 80;     // MUSIC.md, módulo 6
        m.onGridTarget = 0.80f;
        m.implemented = true;

        m.lessons = {
            detail (block ("A", juce::String::fromUTF8 ("Escala menor natural"), {
                "Escala menor natural (eólio): 1 2 b3 4 5 b6 b7.",
                "É a relativa menor de uma escala maior: mesmas notas, outro repouso.",
                "A terça menor define o caráter melancólico da escala."
            }), content::topic6A()),
            detail (block ("B", juce::String::fromUTF8 ("Escala menor harmônica"), {
                "Escala menor harmônica: 1 2 b3 4 5 b6 7 — a menor natural com o 7º elevado.",
                "A sensível (7) cria a cadência V7 → i.",
                "O intervalo de segunda aumentada (b6 → 7) dá o caráter exótico."
            }), content::topic6B()),
            detail (block ("C", juce::String::fromUTF8 ("Modos da menor harmônica"), {
                "A menor harmônica gera sete modos, um por grau.",
                "O quinto (frígio dominante) é o mais usado; o primeiro e o quarto vêm em seguida.",
                "Cada modo combina com um tipo de acorde."
            }), content::topic6C()),
            detail (block ("D", juce::String::fromUTF8 ("Escala menor melódica"), {
                "Escala menor melódica: 1 2 b3 4 5 6 7 — o 6º e o 7º elevados.",
                "Sobe suave a partir do 5º grau; padrão T-S-T-T-T-T-S.",
                "É a base das sonoridades modernas do jazz e da bossa."
            }), content::topic6D()),
            detail (block ("E", juce::String::fromUTF8 ("Modos da menor melódica"), {
                "A menor melódica gera sete modos, um por grau.",
                "O quarto (lídio dominante) e o sétimo (escala alterada) são os mais usados no jazz.",
                "Cada modo combina com um tipo de acorde."
            }), content::topic6E()),
            detail (block ("F", juce::String::fromUTF8 ("Campos harmônicos menores e funções dos acordes"), {
                "Campo harmônico é o conjunto de acordes que nasce da escala.",
                "Campo menor natural: i, ii, III, iv, v, VI, VII; harmônico troca o v pelo V7.",
                "Funções: tônica (i, III), subdominante (ii, iv, VI), dominante (v/V, VII)."
            }), content::topic6F()),
            detail (block ("G", juce::String::fromUTF8 ("Subdominantes menores"), {
                "Subdominante menor: acordes do campo menor paralelo usados no campo maior.",
                "O iv menor é o mais comum: I → IV → iv → I.",
                "bVI, bVII e bII (napolitano) são empréstimos modais e cromáticos."
            }), content::topic6G()),
            detail (block ("H", juce::String::fromUTF8 ("Relações entre os campos maior e menor"), {
                "Relativa: mesma armadura, outra tônica (Dó maior ↔ Lá menor).",
                "Paralela: mesma tônica, outra armadura (Dó maior ↔ Dó menor).",
                "Tonalidades próximas facilitam a modulação."
            }), content::topic6H()),
            detail (block ("I", juce::String::fromUTF8 ("Modos dórico, frígio, lídio, mixolídio e lócrio"), {
                "Os sete modos gregos são a escala maior vista de sete pontos de partida.",
                "Jônio (maior), dórico, frígio, lídio, mixolídio, eólio (menor) e lócrio.",
                "Cada acorde do campo tem um modo que combina com ele."
            }), content::topic6I()),
        };

        // Exercises: 3..5 per topic, mixing verifiable quizzes and playable
        // exercises the app recognises (interval or chord). Ids follow
        // EX-6.<topico>.<n>, numbered per topic, as modules 1 and 2.
        auto add = [&m] (Exercise e, const char* topic)
        {
            e.lessonId = topic;
            m.exercises.push_back (std::move (e));
            return (int) m.exercises.size() - 1;
        };

        // --- Topic A — escala menor natural ----------------------------------
        add (exercise ("EX-6.A.1", juce::String::fromUTF8 ("Questionário: escala menor natural"),
                       juce::String::fromUTF8 ("Responder ao questionário da escala menor natural."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões da menor natural.")), "A");
        m.exercises.back().quiz = {
            question ("Quantas notas tem a escala menor natural?",
                      { "7", "5", "8", "12" }, 0),
            question ("Quais graus são abaixados na menor natural em relação à maior?",
                      { "a terça, a sexta e a sétima",
                        "apenas a terça",
                        "a quarta e a quinta",
                        "nenhum" }, 0),
            question ("Qual é a relativa menor de Dó maior?",
                      { "Lá menor", "Si menor", "Ré menor", "Mi menor" }, 0),
            question ("Em Lá menor natural, as notas são:",
                      { "A B C D E F G", "A B C# D E F# G#",
                        "A B C D E F# G#", "A Bb C D Eb F G" }, 0),
            question ("O modo grego que é a escala menor natural chama-se:",
                      { "eólio", "jônio", "dórico", "lócrio" }, 0),
        };
        add (intervalExercise ("EX-6.A.2", "Tocar a terça menor",
                               "Tocar uma terça menor (3 semitons), três vezes.", 3, 3), "A");
        add (intervalExercise ("EX-6.A.3", "Tocar a sétima menor",
                               "Tocar uma sétima menor (10 semitons), duas vezes.", 10, 2), "A");
        add (exercise ("EX-6.A.4", juce::String::fromUTF8 ("Graus da menor natural"),
                       juce::String::fromUTF8 ("Nomear os graus e a relativa da escala menor."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário dos graus.")), "A");
        m.exercises.back().quiz = {
            question ("Em Lá menor, qual é o sexto grau?",
                      { "Fá", "Fá#", "Sol", "Sol#" }, 0),
            question ("Em Lá menor, qual é o sétimo grau?",
                      { "Sol", "Sol#", "Fá#", "Lá" }, 0),
            question ("O padrão de intervalos da menor natural é:",
                      { "T S T T S T T", "T S T T T T S", "T T S T T T S", "S T T S T T T" }, 0),
        };

        // --- Topic B — escala menor harmônica --------------------------------
        add (exercise ("EX-6.B.1", juce::String::fromUTF8 ("Questionário: escala menor harmônica"),
                       juce::String::fromUTF8 ("Responder ao questionário da menor harmônica."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões da menor harmônica.")), "B");
        m.exercises.back().quiz = {
            question ("A escala menor harmônica eleva qual grau?",
                      { "o sétimo", "o sexto", "o terceiro", "o quarto" }, 0),
            question ("O intervalo entre o b6 e o 7 na menor harmônica é:",
                      { "segunda aumentada", "terça menor",
                        "segunda maior", "quarta justa" }, 0),
            question ("Em Lá menor harmônica, o sétimo grau é:",
                      { "Sol#", "Sol", "Fá#", "Lá" }, 0),
            question ("Para que serve a menor harmônica?",
                      { "dar força à cadência V7 → i", "suavizar a melodia",
                        "formar acordes suspensos", "substituir a escala maior" }, 0),
            question ("A sensível da escala de Lá menor é:",
                      { "Sol#", "Sol", "Lá", "Fá" }, 0),
        };
        add (intervalExercise ("EX-6.B.2", "Tocar a sétima maior (sensível)",
                               "Tocar uma sétima maior (11 semitons), três vezes.", 11, 3), "B");
        add (intervalExercise ("EX-6.B.3", "Tocar a sexta menor",
                               "Tocar uma sexta menor (8 semitons), duas vezes.", 8, 2), "B");
        add (exercise ("EX-6.B.4", juce::String::fromUTF8 ("Menor natural x harmônica"),
                       juce::String::fromUTF8 ("Comparar as duas escalas menores."),
                       juce::String::fromUTF8 ("Acerto ≥90% na comparação.")), "B");
        m.exercises.back().quiz = {
            question ("A diferença entre a menor natural e a menor harmônica está:",
                      { "no sétimo grau", "na terça", "na quinta", "no ritmo" }, 0),
            question ("A segunda aumentada da menor harmônica soa:",
                      { "exótica e dramática", "suave e igual à maior",
                        "idêntica à oitava", "sem tensão" }, 0),
            question ("A sensível da menor harmônica serve para:",
                      { "puxar para a tônica", "aumentar o volume",
                        "mudar a tonalidade", "formar quintas" }, 0),
        };

        // --- Topic C — modos da menor harmônica ------------------------------
        add (exercise ("EX-6.C.1", juce::String::fromUTF8 ("Questionário: modos da menor harmônica"),
                       juce::String::fromUTF8 ("Responder ao questionário dos modos da harmônica."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões dos modos.")), "C");
        m.exercises.back().quiz = {
            question ("Quantos modos gera a escala menor harmônica?",
                      { "sete", "cinco", "doze", "três" }, 0),
            question ("O modo mais usado da menor harmônica é:",
                      { "o quinto (frígio dominante)", "o primeiro",
                        "o sétimo", "o quarto" }, 0),
            question ("O frígio dominante tem qual terça?",
                      { "maior", "menor", "justa", "diminuta" }, 0),
            question ("Os modos da menor harmônica servem para:",
                      { "improvisar sobre cada acorde do campo", "afinar o instrumento",
                        "substituir o metrônomo", "formar escalas maiores" }, 0),
        };
        add (intervalExercise ("EX-6.C.2", "Tocar a segunda menor (frígio dominante)",
                               "Tocar uma segunda menor (1 semitom), três vezes.", 1, 3), "C");
        add (exercise ("EX-6.C.3", juce::String::fromUTF8 ("Aplicar os modos"),
                       juce::String::fromUTF8 ("Relacionar cada modo da harmônica ao seu acorde."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário de aplicação.")), "C");
        m.exercises.back().quiz = {
            question ("O frígio dominante é usado sobre:",
                      { "acordes de dominante (V7)", "acordes maiores com sétima",
                        "acordes diminutos", "acordes suspensos" }, 0),
            question ("O primeiro modo da menor harmônica é:",
                      { "a própria escala menor harmônica", "o jônio",
                        "o lócrio", "o mixolídio" }, 0),
            question ("Cada modo da menor harmônica combina com:",
                      { "um tipo de acorde", "um andamento fixo",
                        "uma corda do instrumento", "uma tonalidade só" }, 0),
        };

        // --- Topic D — escala menor melódica ---------------------------------
        add (exercise ("EX-6.D.1", juce::String::fromUTF8 ("Questionário: escala menor melódica"),
                       juce::String::fromUTF8 ("Responder ao questionário da menor melódica."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões da menor melódica.")), "D");
        m.exercises.back().quiz = {
            question ("A escala menor melódica eleva quais graus?",
                      { "o sexto e o sétimo", "o sétimo", "o terceiro", "o sexto" }, 0),
            question ("O padrão de intervalos da menor melódica é:",
                      { "T S T T T T S", "T S T T S T T", "T T S T T T S", "S T T T T S T" }, 0),
            question ("Em Lá menor melódica, as notas são:",
                      { "A B C D E F# G#", "A B C D E F G#",
                        "A B C D E F G", "A B C# D E F# G#" }, 0),
            question ("A menor melódica é muito usada em:",
                      { "jazz e bossa", "rock pesado apenas",
                        "música medieval", "nenhum estilo" }, 0),
            question ("A terça da menor melódica é:",
                      { "menor", "maior", "aumentada", "diminuta" }, 0),
        };
        add (intervalExercise ("EX-6.D.2", "Tocar a sétima maior",
                               "Tocar uma sétima maior (11 semitons), três vezes.", 11, 3), "D");
        add (intervalExercise ("EX-6.D.3", "Tocar a sexta maior",
                               "Tocar uma sexta maior (9 semitons), duas vezes.", 9, 2), "D");
        add (exercise ("EX-6.D.4", juce::String::fromUTF8 ("As três menores"),
                       juce::String::fromUTF8 ("Distinguir as três escalas menores pelo 6º e 7º graus."),
                       juce::String::fromUTF8 ("Acerto ≥90% na distinção das três menores.")), "D");
        m.exercises.back().quiz = {
            question ("Qual escala menor tem o 6º e o 7º graus elevados?",
                      { "a menor melódica", "a menor natural",
                        "a menor harmônica", "a pentatônica" }, 0),
            question ("Qual escala menor tem apenas o 7º grau elevado?",
                      { "a menor harmônica", "a menor melódica",
                        "a menor natural", "a pentatônica" }, 0),
            question ("A menor melódica soa:",
                      { "suave e moderna", "exótica e angular",
                        "idêntica à maior", "sem terça" }, 0),
        };

        // --- Topic E — modos da menor melódica -------------------------------
        add (exercise ("EX-6.E.1", juce::String::fromUTF8 ("Questionário: modos da menor melódica"),
                       juce::String::fromUTF8 ("Responder ao questionário dos modos da melódica."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões dos modos da melódica.")), "E");
        m.exercises.back().quiz = {
            question ("O quarto modo da menor melódica é:",
                      { "lídio dominante", "frígio", "dórico", "eólio" }, 0),
            question ("O sétimo modo da menor melódica é:",
                      { "a escala alterada", "o lócrio", "o jônio", "o mixolídio" }, 0),
            question ("O lídio dominante é usado sobre:",
                      { "acordes de dominante (V7)", "acordes menores",
                        "acordes diminutos", "acordes suspensos" }, 0),
            question ("A escala alterada serve para:",
                      { "criar máxima tensão sobre o V7", "repousar na tônica",
                        "formar acordes maiores", "afinar a guitarra" }, 0),
        };
        add (intervalExercise ("EX-6.E.2", "Tocar o trítono (lídio dominante)",
                               "Tocar um trítono (6 semitons), três vezes.", 6, 3), "E");
        add (intervalExercise ("EX-6.E.3", "Tocar a segunda menor (alterada)",
                               "Tocar uma segunda menor (1 semitono), duas vezes.", 1, 2), "E");
        add (exercise ("EX-6.E.4", juce::String::fromUTF8 ("Modos e acordes da melódica"),
                       juce::String::fromUTF8 ("Relacionar cada modo da melódica ao seu acorde."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário de aplicação.")), "E");
        m.exercises.back().quiz = {
            question ("O modo 1 da menor melódica combina com qual acorde?",
                      { "m7M", "maj7", "dim7", "sus4" }, 0),
            question ("O modo 6 da menor melódica (lócrio 2 natural) é usado sobre:",
                      { "acordes meio-diminutos", "acordes maiores",
                        "acordes suspensos", "acordes diminutos de sétima" }, 0),
            question ("O lídio dominante é brilhante porque contém:",
                      { "a quarta aumentada (#4)", "a sexta menor",
                        "a terça menor", "a segunda menor" }, 0),
        };

        // --- Topic F — campos harmônicos menores -----------------------------
        add (exercise ("EX-6.F.1", juce::String::fromUTF8 ("Questionário: campos harmônicos menores"),
                       juce::String::fromUTF8 ("Responder ao questionário dos campos menores."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões dos campos menores.")), "F");
        m.exercises.back().quiz = {
            question ("O campo harmônico menor natural tem qual dominante?",
                      { "v menor (sem sensível)", "V7 maior",
                        "V7 diminuto", "não tem dominante" }, 0),
            question ("Qual acorde do campo menor harmônico dá força à cadência?",
                      { "V7", "i", "iv", "VI" }, 0),
            question ("No campo menor, o segundo grau é:",
                      { "meio-diminuto", "maior",
                        "menor com sétima maior", "aumentado" }, 0),
            question ("A cadência menor por excelência é:",
                      { "i → iv → V7 → i", "I → IV → V → I",
                        "i → ii → iii → i", "I → vi → ii → V" }, 0),
            question ("O i do campo menor melódico é:",
                      { "m7M", "m7", "maj7", "dim7" }, 0),
        };
        add (exercise ("EX-6.F.2", juce::String::fromUTF8 ("Montar a tríade menor"),
                       juce::String::fromUTF8 ("Tocar uma tríade menor (tônica, terça menor e quinta justa)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere os intervalos da tríade menor.")), "F");
        m.exercises.back().chordPitchClasses = { 0, 3, 7 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-6.F.3", juce::String::fromUTF8 ("Montar a tríade diminuta"),
                       juce::String::fromUTF8 ("Tocar uma tríade diminuta (tônica, terça menor e quinta diminuta)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere os intervalos da tríade diminuta.")), "F");
        m.exercises.back().chordPitchClasses = { 0, 3, 6 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-6.F.4", juce::String::fromUTF8 ("Funções no campo menor"),
                       juce::String::fromUTF8 ("Identificar as funções dos acordes do campo menor."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário das funções.")), "F");
        m.exercises.back().quiz = {
            question ("Qual é a função do iv no campo menor?",
                      { "subdominante", "tônica", "dominante", "nenhuma" }, 0),
            question ("Qual é a função do V7 no campo menor harmônico?",
                      { "dominante", "tônica", "subdominante", "nenhuma" }, 0),
            question ("Os graus de tônica no campo menor são:",
                      { "i e III", "ii e iv", "v e VII", "apenas o i" }, 0),
        };

        // --- Topic G — subdominantes menores ---------------------------------
        add (exercise ("EX-6.G.1", juce::String::fromUTF8 ("Questionário: subdominantes menores"),
                       juce::String::fromUTF8 ("Responder ao questionário dos subdominantes menores."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões dos empréstimos.")), "G");
        m.exercises.back().quiz = {
            question ("O subdominante menor (iv) vem de onde?",
                      { "do campo menor paralelo", "do campo maior",
                        "da escala pentatônica", "do blues" }, 0),
            question ("Em Dó maior, o iv emprestado é:",
                      { "Fm7", "F7M", "Gm7", "Am7" }, 0),
            question ("Qual nota o iv acrescenta ao campo de Dó maior?",
                      { "Ab (b6)", "A natural", "F#", "B" }, 0),
            question ("Os empréstimos modais servem para:",
                      { "dar cor à harmonia", "mudar a afinação",
                        "acelerar o tempo", "substituir o metrônomo" }, 0),
        };
        add (exercise ("EX-6.G.2", juce::String::fromUTF8 ("Montar o iv menor"),
                       juce::String::fromUTF8 ("Tocar uma tríade menor (o iv emprestado, tônica, terça menor e quinta justa)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere os intervalos do iv menor.")), "G");
        m.exercises.back().chordPitchClasses = { 0, 3, 7 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-6.G.3", juce::String::fromUTF8 ("Tocar a progressão I–iv–I"),
                       juce::String::fromUTF8 ("Tocar C7M – Fm7 – C7M (I–iv–I em Dó maior)."),
                       juce::String::fromUTF8 ("O app reconhece os acordes e confere a progressão do empréstimo.")), "G");
        m.exercises.back().chordProgression = {
            { 0, 4, 7 },    // C
            { 5, 8, 0 },    // Fm
            { 0, 4, 7 },    // C
        };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-6.G.4", juce::String::fromUTF8 ("Empréstimos do campo menor"),
                       juce::String::fromUTF8 ("Reconhecer os acordes emprestados do campo menor paralelo."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário dos empréstimos.")), "G");
        m.exercises.back().quiz = {
            question ("Em Dó maior, o bVII emprestado é:",
                      { "Bb7", "Bm7", "C7", "Db7" }, 0),
            question ("O acorde napolitano (bII) em Dó maior é:",
                      { "Db maior", "D menor", "Cb maior", "Eb maior" }, 0),
            question ("O ii meio-diminuto emprestado em Dó maior é:",
                      { "Dm7(b5)", "Dm7", "D7", "Dbm7" }, 0),
        };

        // --- Topic H — relações entre os campos ------------------------------
        add (exercise ("EX-6.H.1", juce::String::fromUTF8 ("Questionário: relações entre os campos"),
                       juce::String::fromUTF8 ("Responder ao questionário das relações maior/menor."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões das relações.")), "H");
        m.exercises.back().quiz = {
            question ("Dó maior e Lá menor são tonalidades:",
                      { "relativas", "paralelas", "vizinhas", "distantes" }, 0),
            question ("Dó maior e Dó menor são tonalidades:",
                      { "paralelas", "relativas", "iguais", "enarmônicas" }, 0),
            question ("A relativa menor de uma tonalidade maior começa no:",
                      { "sexto grau", "quinto grau", "terceiro grau", "segundo grau" }, 0),
            question ("Duas tonalidades vizinhas no ciclo das quintas compartilham:",
                      { "seis notas", "nenhuma nota",
                        "todas as sete notas", "apenas a tônica" }, 0),
        };
        add (intervalExercise ("EX-6.H.2", "Tocar a sexta maior (relativa)",
                               "Tocar uma sexta maior (9 semitons), duas vezes.", 9, 2), "H");
        add (exercise ("EX-6.H.3", juce::String::fromUTF8 ("Maior, relativa e paralela"),
                       juce::String::fromUTF8 ("Distinguir as relações entre as tonalidades."),
                       juce::String::fromUTF8 ("Acerto ≥90% na distinção das relações.")), "H");
        m.exercises.back().quiz = {
            question ("Relativa e paralela diferem em que?",
                      { "a relativa compartilha as notas; a paralela, a tônica",
                        "são a mesma coisa",
                        "a paralela compartilha as notas",
                        "nenhuma relação existe" }, 0),
            question ("A relativa maior de Lá menor é:",
                      { "Dó maior", "Mi maior", "Sol maior", "Ré maior" }, 0),
            question ("Qual tonalidade é mais próxima de Dó maior?",
                      { "Sol maior", "Fá# maior", "Dó# maior", "Lá maior" }, 0),
        };

        // --- Topic I — modos gregos ------------------------------------------
        add (exercise ("EX-6.I.1", juce::String::fromUTF8 ("Questionário: modos gregos"),
                       juce::String::fromUTF8 ("Responder ao questionário dos modos gregos."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões dos modos gregos.")), "I");
        m.exercises.back().quiz = {
            question ("Qual modo grego é a própria escala maior?",
                      { "jônio", "dórico", "lídio", "mixolídio" }, 0),
            question ("O modo dórico tem qual nota característica?",
                      { "sexta maior", "segunda menor",
                        "quarta aumentada", "sétima menor" }, 0),
            question ("O modo frígio tem:",
                      { "segunda menor (b2)", "sexta maior",
                        "quarta aumentada", "sétima maior" }, 0),
            question ("O modo mixolídio é usado sobre:",
                      { "acordes de dominante (7)", "acordes menores",
                        "acordes diminutos", "acordes suspensos" }, 0),
            question ("O modo lócrio tem:",
                      { "quinta diminuta (b5)", "quinta justa",
                        "quarta aumentada", "sexta maior" }, 0),
        };
        add (intervalExercise ("EX-6.I.2", "Tocar a quarta aumentada (lídio)",
                               "Tocar uma quarta aumentada (6 semitons), três vezes.", 6, 3), "I");
        add (intervalExercise ("EX-6.I.3", "Tocar a sétima menor (mixolídio)",
                               "Tocar uma sétima menor (10 semitons), duas vezes.", 10, 2), "I");
        add (exercise ("EX-6.I.4", juce::String::fromUTF8 ("Modos e acordes"),
                       juce::String::fromUTF8 ("Relacionar cada modo grego ao acorde do campo."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário de aplicação.")), "I");
        m.exercises.back().quiz = {
            question ("O dórico combina com qual acorde?",
                      { "m7", "maj7", "7", "dim7" }, 0),
            question ("O lídio combina com qual acorde?",
                      { "maj7", "m7", "7", "m7(b5)" }, 0),
            question ("O mixolídio combina com qual acorde?",
                      { "7", "maj7", "m7", "dim7" }, 0),
        };

        // The gate closes the module: a ii–V–i minor cadence on the grid, built
        // from the chords of the minor field (REQ-009, REQ-015).
        auto& gate = m.exercises.emplace_back (exercise (
            "GATE-6", juce::String::fromUTF8 ("Desafio de gate — cadência menor ii–V–i"),
            juce::String::fromUTF8 ("Tocar Bm7(b5) – E7 – Am7 – Am7 a 80 BPM, na grade do metrônomo."),
            juce::String::fromUTF8 ("Acordes reconhecidos e alinhados à grade (≥ 0,80).")));
        gate.isGate = true;
        gate.lessonId = "H";
        gate.chordProgression = {
            { 11, 2, 5, 9 },   // Bm7(b5)
            { 4, 8, 11, 2 },   // E7
            { 9, 0, 4, 7 },    // Am7
            { 9, 0, 4, 7 },    // Am7
        };

        m.gateChallenge = juce::String::fromUTF8 (
            "Tocar a cadência menor ii–V–i (Bm7(b5) – E7 – Am7 – Am7) a 80 BPM "
            "com ≥90% de acerto de acordes e on_grid_ratio ≥ 0,80. Os acordes vêm "
            "do campo harmônico menor estudado no módulo.");

        // Pattern and link the module must cite (REQ-007, REQ-010).
        m.practice.patternId = "PTN-M-3rds";
        m.practice.patternUse = juce::String::fromUTF8 (
            "Terças: o padrão 1-3, 2-4, 3-5… percorre a escala menor saltando um "
            "grau, o que faz o aluno ouvir a terça (que define o caráter menor) "
            "em movimento. Complemento: PTN-A-TRIAD (arpejos de tríade) para "
            "tocar os acordes do campo menor.");
        m.practice.guitarists = { "Wes Montgomery", "Pat Metheny", "Santana" };

        // Curated apostilas (REQ-006, CM-012); see docs/MUSIC.md §2.1.
        m.sources = {
            "pdf-teoria-elementar-da-musica-ricordi-osvaldo-lacerda",
            "pdf-p-classtruncatedtext-module-lineclamped-85ulhh-style-max-lines5bohumil-med-teoria-da-musica-5-edicao-p",
            "pdf-caged-e-derivaoes-de-acordes-marcelo-mello-apostila-de-violao-e-guitarra-vol1",
            "pdf-mozart-mello-livroestudosdeguitarra4em1",
            "pdf-desvendando-os-segredos-da-guitarra-fusion",
        };

        return m;
    }

    // Modules 3..20 exist as placeholders so the list is honest about what is
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
        makeModule2(),
        makePlaceholder (3,  "Vamps de 2 acordes",                  2,  68,  0.77f),
        makePlaceholder (4,  "Vamps de 2 acordes (aplicação)",      2,  72,  0.78f),
        makePlaceholder (5,  "II–V–I",                              3,  76,  0.79f),
        makeModule6(),
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
