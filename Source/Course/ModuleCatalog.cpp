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

    CourseModule makeModule7()
    {
        CourseModule m;
        m.number = 7;
        m.title = juce::String::fromUTF8 ("Empilhamentos, estruturas modais e sonoridades");
        m.objective = juce::String::fromUTF8 (
            "Conhecer estruturas harmônicas além das tríades e tétrades "
            "convencionais: empilhamentos de terças, quartas e outros, estruturas "
            "modais, tríades do meio, modos estruturais pelo CAGED e as "
            "sonoridades modais do dórico ao alterado.");
        m.level = 3;          // MUSIC.md: módulos 5–7 = nível 3 (II–V–I)
        m.targetBpm = 84;     // MUSIC.md, módulo 7
        m.onGridTarget = 0.80f;
        m.implemented = true;

        m.lessons = {
            detail (block ("A", juce::String::fromUTF8 ("Empilhamentos de terças"), {
                "Empilhar terças é somar intervalos de terça, um sobre o outro.",
                "A mistura de terças maiores e menores define a qualidade do acorde.",
                "As tensões 9, 11 e 13 são os graus 2, 4 e 6 uma oitava acima."
            }), content::topic7A()),
            detail (block ("B", juce::String::fromUTF8 ("Empilhamentos quartais"), {
                "Empilhar quartas justas (5 semitons) produz um som suspenso e modal.",
                "O acorde de So What empilha quartas com uma terça no topo.",
                "Sem terça, o acorde não é maior nem menor."
            }), content::topic7B()),
            detail (block ("C", juce::String::fromUTF8 ("Outros empilhamentos"), {
                "Quintas dão força e abertura (power chords).",
                "Segundas dão tensão (clusters); mistos dão cor sob medida.",
                "O empilhamento escolhido define a sonoridade do acorde."
            }), content::topic7C()),
            detail (block ("D", juce::String::fromUTF8 ("Estruturas modais e tríades do meio"), {
                "Estruturas modais reforçam um modo sem criar resolução.",
                "Tríades do meio são tríades sobre graus internos da escala.",
                "Cada tríade do meio acrescenta tensões ao acorde de base."
            }), content::topic7D()),
            detail (block ("E", juce::String::fromUTF8 ("Acordes e famílias modais"), {
                "Cada acorde carrega uma família de modos possíveis.",
                "Maiores: jônio e lídio. Menores: dórico, eólio, frígio.",
                "Dominantes: mixolídio, lídio dominante, alterado, sus."
            }), content::topic7E()),
            detail (block ("F", juce::String::fromUTF8 ("Modos estruturais pelo CAGED"), {
                "O CAGED é um mapa do braço, não só um conjunto de acordes.",
                "Cada forma contém a escala do tom e os seus modos.",
                "Os modos são a mesma escala vista de graus diferentes."
            }), content::topic7F()),
            detail (block ("G", juce::String::fromUTF8 ("Dórico, Lídio e Mixolídio"), {
                "Dórico: menor com sexta maior (1 2 b3 4 5 6 b7).",
                "Lídio: maior com quarta aumentada (1 2 3 #4 5 6 7).",
                "Mixolídio: maior com sétima menor (1 2 3 4 5 6 b7)."
            }), content::topic7G()),
            detail (block ("H", juce::String::fromUTF8 ("Mixolídio sus e Mixolídio #4"), {
                "Mixolídio sus: 1 2 4 5 6 b7 (sem a terça), combina com X7sus4.",
                "Mixolídio #4: 1 2 3 #4 5 6 b7, combina com X7#11.",
                "As duas são variações do dominante, com cores diferentes."
            }), content::topic7H()),
            detail (block ("I", juce::String::fromUTF8 ("Lócrio 9 e Alterado (Alt.7)"), {
                "Lócrio 9: 1 2 b3 4 b5 b6 b7 (meio-diminuto com nona natural).",
                "Alterado: 1 b9 #9 3 b5 #5 b7 (tensão máxima do dominante).",
                "As duas aparecem juntas no II–V–I menor."
            }), content::topic7I()),
            detail (block ("J", juce::String::fromUTF8 ("Aplicações modais no rock e pop-rock"), {
                "Vamps de um ou dois acordes são o terreno da harmonia modal.",
                "Cada modo tem um tipo de vamp e uma cor.",
                "Do modal se chega à harmonia funcional dos próximos módulos."
            }), content::topic7J()),
        };

        // Exercises: 3..5 per topic, ids EX-7.<topico>.<n>, mixing verifiable
        // quizzes with exercises played on the instrument (the app recognises
        // the notes). Playable exercises are not grid-gated.
        auto add = [&m] (Exercise e, const char* topic)
        {
            e.lessonId = topic;
            m.exercises.push_back (std::move (e));
            return (int) m.exercises.size() - 1;
        };

        // --- Topic A — empilhamentos de terças -------------------------------
        add (exercise ("EX-7.A.1", juce::String::fromUTF8 ("Questionário: empilhamento de terças"),
                       juce::String::fromUTF8 ("Responder ao questionário do empilhamento de terças."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de empilhamento.")), "A");
        m.exercises.back().quiz = {
            question ("Empilhar terças é somar:",
                      { "intervalos de terça, um sobre o outro",
                        "intervalos de quinta", "notas fora da escala", "apenas duas notas" }, 0),
            question ("O que define a qualidade de um acorde no empilhamento de terças?",
                      { "a mistura de terças maiores e menores",
                        "o volume", "a corda usada", "a posição do braço" }, 0),
            question ("A nona (9) é qual grau uma oitava acima?",
                      { "a segunda", "a terça", "a quarta", "a sexta" }, 0),
            question ("Quantas notas tem uma tétrade?",
                      { "três", "quatro", "cinco", "sete" }, 1),
            question ("Qual grau nunca deve sair ao simplificar um acorde?",
                      { "a quinta", "a terça", "a nona", "a décima terceira" }, 1),
        };
        add (exercise ("EX-7.A.2", juce::String::fromUTF8 ("Tocar a tríade maior"),
                       juce::String::fromUTF8 ("Tocar uma tríade maior (tônica, terça maior e quinta justa)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere os intervalos 0-4-7.")), "A");
        m.exercises.back().chordPitchClasses = { 0, 4, 7 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-7.A.3", juce::String::fromUTF8 ("Tocar a tríade menor"),
                       juce::String::fromUTF8 ("Tocar uma tríade menor (tônica, terça menor e quinta justa)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere os intervalos 0-3-7.")), "A");
        m.exercises.back().chordPitchClasses = { 0, 3, 7 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-7.A.4", juce::String::fromUTF8 ("Questionário: da tríade à tétrade"),
                       juce::String::fromUTF8 ("Identificar a sétima que transforma a tríade em cada tétrade."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário de tétrades.")), "A");
        m.exercises.back().quiz = {
            question ("C7M usa qual sétima?",
                      { "11 semitons (sétima maior)", "10 semitons (sétima menor)",
                        "9 semitons", "12 semitons" }, 0),
            question ("C7 (dominante) usa qual sétima?",
                      { "11 semitons", "10 semitons", "6 semitons", "7 semitons" }, 1),
            question ("Cm7b5 (meio-diminuto) tem os intervalos:",
                      { "0, 3, 6, 10", "0, 4, 7, 11", "0, 3, 7, 10", "0, 4, 8, 11" }, 0),
            question ("Empilhar terças acima da sétima gera:",
                      { "as tensões 9, 11 e 13", "as tríades", "as quintas", "nada" }, 0),
        };

        // --- Topic B — empilhamentos quartais --------------------------------
        add (exercise ("EX-7.B.1", juce::String::fromUTF8 ("Questionário: empilhamento quartal"),
                       juce::String::fromUTF8 ("Responder ao questionário do empilhamento quartal."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "B");
        m.exercises.back().quiz = {
            question ("A quarta justa tem quantos semitons?",
                      { "4", "5", "6", "7" }, 1),
            question ("Um acorde quartal é:",
                      { "suspenso, nem maior nem menor",
                        "sempre maior", "sempre menor", "sempre diminuto" }, 0),
            question ("O acorde de So What empilha:",
                      { "quartas com uma terça no topo",
                        "apenas terças", "apenas quintas", "segundas" }, 0),
            question ("Por que o acorde quartal não resolve?",
                      { "porque não tem função dominante",
                        "porque não tem notas", "porque é muito grave", "porque é rápido" }, 0),
        };
        add (exercise ("EX-7.B.2", juce::String::fromUTF8 ("Tocar o acorde quartal"),
                       juce::String::fromUTF8 ("Tocar um empilhamento quartal (tônica, quarta e sétima menor)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere os intervalos 0-5-10.")), "B");
        m.exercises.back().chordPitchClasses = { 0, 5, 10 };
        m.exercises.back().usesGrid = false;
        add (intervalExercise ("EX-7.B.3", "Tocar a quarta justa",
                               "Tocar uma quarta justa (5 semitons) em qualquer posição, três vezes.",
                               5, 3), "B");
        add (exercise ("EX-7.B.4", juce::String::fromUTF8 ("Questionário: quartal na prática"),
                       juce::String::fromUTF8 ("Relacionar o empilhamento quartal aos seus usos."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "B");
        m.exercises.back().quiz = {
            question ("A quarta aumentada tem quantos semitons?",
                      { "5", "6", "7", "8" }, 1),
            question ("O empilhamento quartal é típico de:",
                      { "jazz modal e vamps", "marchas", "valsas clássicas", "nada" }, 0),
            question ("Dó-Fá-Sib pode ser lido como:",
                      { "Sib com quarta e nona", "Dó maior", "Dó menor", "Dó diminuto" }, 0),
        };

        // --- Topic C — outros empilhamentos ----------------------------------
        add (exercise ("EX-7.C.1", juce::String::fromUTF8 ("Questionário: outros empilhamentos"),
                       juce::String::fromUTF8 ("Responder ao questionário dos outros empilhamentos."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "C");
        m.exercises.back().quiz = {
            question ("O empilhamento de quintas é a base de:",
                      { "power chords", "acordes diminutos", "clusters", "nada" }, 0),
            question ("O empilhamento de segundas produz:",
                      { "um som denso e tenso", "um som estável", "um som vazio", "um som igual à quinta" }, 0),
            question ("Empilhamentos mistos:",
                      { "combinam intervalos diferentes", "usam só terças",
                        "usam só quintas", "não existem" }, 0),
            question ("Clusters de segundas funcionam melhor:",
                      { "nas regiões médias e agudas", "no grave profundo",
                        "apenas no piano", "apenas com distorção" }, 0),
        };
        add (exercise ("EX-7.C.2", juce::String::fromUTF8 ("Tocar o power chord"),
                       juce::String::fromUTF8 ("Tocar um empilhamento de quintas (tônica, quinta e oitava)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere o conjunto tônica-quinta.")), "C");
        m.exercises.back().chordPitchClasses = { 0, 7 };
        m.exercises.back().usesGrid = false;
        add (intervalExercise ("EX-7.C.3", "Tocar a quinta justa",
                               "Tocar uma quinta justa (7 semitons) em qualquer posição, três vezes.",
                               7, 3), "C");
        add (exercise ("EX-7.C.4", juce::String::fromUTF8 ("Questionário: empilhamentos e estilo"),
                       juce::String::fromUTF8 ("Relacionar cada empilhamento ao seu estilo."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "C");
        m.exercises.back().quiz = {
            question ("Qual empilhamento dá força e abertura?",
                      { "quintas", "segundas", "sétimas", "quartas" }, 0),
            question ("Qual empilhamento dá tensão?",
                      { "segundas", "quintas", "quartas", "terças" }, 0),
            question ("No jazz, predominam:",
                      { "terças e quartas", "apenas quintas", "apenas segundas", "apenas oitavas" }, 0),
        };

        // --- Topic D — estruturas modais e tríades do meio --------------------
        add (exercise ("EX-7.D.1", juce::String::fromUTF8 ("Questionário: estruturas modais"),
                       juce::String::fromUTF8 ("Responder ao questionário das estruturas modais."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "D");
        m.exercises.back().quiz = {
            question ("Uma estrutura modal:",
                      { "reforça um modo sem criar resolução",
                        "resolve sempre para a tônica", "usa só duas notas", "não tem função" }, 0),
            question ("Tríades do meio são tríades construídas:",
                      { "sobre graus internos da escala", "só sobre a tônica",
                        "fora da escala", "com quatro notas" }, 0),
            question ("A tríade de Sol sobre Dó produz:",
                      { "Dó com nona (Cmaj9)", "Dó menor", "Dó diminuto", "Dó sus" }, 0),
            question ("Na harmonia modal, os acordes:",
                      { "permanecem; não conduzem", "sempre resolvem",
                        "não têm centro", "são sempre menores" }, 0),
        };
        add (exercise ("EX-7.D.2", juce::String::fromUTF8 ("Tocar uma estrutura com nona"),
                       juce::String::fromUTF8 ("Tocar um acorde maior com a nona (tríade do meio sobre a tônica)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere o conjunto 0-4-7-11-2.")), "D");
        m.exercises.back().chordPitchClasses = { 0, 4, 7, 11, 2 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-7.D.3", juce::String::fromUTF8 ("Tocar uma estrutura menor com nona"),
                       juce::String::fromUTF8 ("Tocar um acorde menor com a nona (cor dórica)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere o conjunto 0-3-7-10-2.")), "D");
        m.exercises.back().chordPitchClasses = { 0, 3, 7, 10, 2 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-7.D.4", juce::String::fromUTF8 ("Questionário: tríades do meio"),
                       juce::String::fromUTF8 ("Identificar a cor que cada tríade do meio acrescenta."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "D");
        m.exercises.back().quiz = {
            question ("Sobre Cmaj7, a tríade de Ré maior dá:",
                      { "a #11 (cor lídia)", "a nona apenas", "a sétima menor", "nada" }, 0),
            question ("Sobre Cm7, a tríade de Sol menor dá:",
                      { "a cor dórica (9)", "a cor lídia", "a cor frígia", "nada" }, 0),
            question ("Para a cor do modo aparecer, é preciso:",
                      { "afirmar o centro no baixo", "tocar rápido",
                        "tocar todas as notas", "usar distorção" }, 0),
        };

        // --- Topic E — acordes e famílias modais ------------------------------
        add (exercise ("EX-7.E.1", juce::String::fromUTF8 ("Questionário: famílias modais"),
                       juce::String::fromUTF8 ("Responder ao questionário das famílias modais."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "E");
        m.exercises.back().quiz = {
            question ("Cmaj7 combina principalmente com:",
                      { "jônio e lídio", "dórico e eólio", "lócrio", "alterado" }, 0),
            question ("Cm7 combina principalmente com:",
                      { "dórico e eólio", "jônio e lídio", "mixolídio", "alterado" }, 0),
            question ("C7 (dominante) combina com:",
                      { "mixolídio, lídio dominante e alterado", "jônio e lídio",
                        "dórico e eólio", "lócrio" }, 0),
            question ("Cm7b5 (meio-diminuto) combina com:",
                      { "lócrio", "jônio", "lídio", "mixolídio" }, 0),
            question ("A sétima do acorde serve para:",
                      { "restringir as opções de modo", "definir o volume",
                        "definir a corda", "nada" }, 0),
        };
        add (exercise ("EX-7.E.2", juce::String::fromUTF8 ("Tocar um acorde dominante"),
                       juce::String::fromUTF8 ("Tocar um acorde dominante (tônica, terça maior, quinta e sétima menor)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere o conjunto 0-4-7-10.")), "E");
        m.exercises.back().chordPitchClasses = { 0, 4, 7, 10 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-7.E.3", juce::String::fromUTF8 ("Tocar um acorde meio-diminuto"),
                       juce::String::fromUTF8 ("Tocar um acorde meio-diminuto (tônica, terça menor, quinta diminuta e sétima menor)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere o conjunto 0-3-6-10.")), "E");
        m.exercises.back().chordPitchClasses = { 0, 3, 6, 10 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-7.E.4", juce::String::fromUTF8 ("Questionário: nota de evitação"),
                       juce::String::fromUTF8 ("Reconhecer as notas de evitação de cada família."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "E");
        m.exercises.back().quiz = {
            question ("Sobre um acorde maior, a décima primeira natural (11) é:",
                      { "nota de evitação; use a #11", "a nota principal",
                        "igual à terça", "a tônica" }, 0),
            question ("Sobre Cm7 (dórico), a sexta maior:",
                      { "é aceita e dá a cor do modo", "é proibida",
                        "é a tônica", "é a quinta" }, 0),
            question ("Escolher a escala pelo acorde é a base de:",
                      { "improvisar com intenção", "afinar", "tocar rápido", "nada" }, 0),
        };

        // --- Topic F — modos estruturais pelo CAGED ---------------------------
        add (exercise ("EX-7.F.1", juce::String::fromUTF8 ("Questionário: modos pelo CAGED"),
                       juce::String::fromUTF8 ("Responder ao questionário dos modos pelo CAGED."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "F");
        m.exercises.back().quiz = {
            question ("O CAGED, como mapa, serve para:",
                      { "enxergar a escala e os modos no braço", "afinar",
                        "medir o volume", "trocar cordas" }, 0),
            question ("Os modos são:",
                      { "a mesma escala vista de graus diferentes", "sete escalas sem relação",
                        "acordes de três notas", "figuras rítmicas" }, 0),
            question ("Para o ouvido perceber o modo, é preciso:",
                      { "afirmar o centro no baixo", "tocar mais rápido",
                        "usar só notas agudas", "nada" }, 0),
            question ("As cinco formas do CAGED:",
                      { "cobrem o braço inteiro e se conectam", "são isoladas",
                        "servem só para Dó", "não têm escala" }, 0),
        };
        add (exercise ("EX-7.F.2", juce::String::fromUTF8 ("Tocar a escala do tom"),
                       juce::String::fromUTF8 ("Tocar a escala de Dó maior (a base de todos os modos)."),
                       juce::String::fromUTF8 ("O app reconhece a sequência de notas da escala de Dó maior.")), "F");
        m.exercises.back().targets = notes ({ "C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5" });
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-7.F.3", juce::String::fromUTF8 ("Tocar a escala a partir da segunda"),
                       juce::String::fromUTF8 ("Tocar a mesma escala começando em Ré (o dórico dentro do tom)."),
                       juce::String::fromUTF8 ("O app reconhece a sequência a partir de Ré.")), "F");
        m.exercises.back().targets = notes ({ "D4", "E4", "F4", "G4", "A4", "B4", "C5", "D5" });
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-7.F.4", juce::String::fromUTF8 ("Questionário: âncora da frase"),
                       juce::String::fromUTF8 ("Identificar o modo pela âncora da frase."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "F");
        m.exercises.back().quiz = {
            question ("Se a frase começa e termina na segunda do tom, o modo é:",
                      { "dórico", "jônio", "mixolídio", "lócrio" }, 0),
            question ("Se a frase ancora na quinta do tom, o modo é:",
                      { "mixolídio", "dórico", "lídio", "frígio" }, 0),
            question ("A conexão entre as formas do CAGED permite:",
                      { "percorrer o braço sem perder a escala", "afinar de ouvido",
                        "medir o volume", "trocar a afinação" }, 0),
        };

        // --- Topic G — dórico, lídio e mixolídio ------------------------------
        add (exercise ("EX-7.G.1", juce::String::fromUTF8 ("Questionário: os três modos"),
                       juce::String::fromUTF8 ("Responder ao questionário do dórico, lídio e mixolídio."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "G");
        m.exercises.back().quiz = {
            question ("O dórico é o menor com:",
                      { "sexta maior", "sexta menor", "sétima maior", "quarta aumentada" }, 0),
            question ("O lídio é o maior com:",
                      { "quarta aumentada (#11)", "sétima menor", "sexta menor", "segunda menor" }, 0),
            question ("O mixolídio é o maior com:",
                      { "sétima menor", "sétima maior", "#11", "b2" }, 0),
            question ("A nota característica do dórico é:",
                      { "a sexta maior", "a sétima maior", "a quarta justa", "a segunda menor" }, 0),
            question ("A nota característica do mixolídio é:",
                      { "a sétima menor (b7)", "a sexta maior", "a #11", "a b2" }, 0),
        };
        add (exercise ("EX-7.G.2", juce::String::fromUTF8 ("Tocar a escala dórica"),
                       juce::String::fromUTF8 ("Tocar a escala dórica em Dó (menor com a sexta maior)."),
                       juce::String::fromUTF8 ("O app reconhece a sequência da escala dórica em Dó.")), "G");
        m.exercises.back().targets = notes ({ "C4", "D4", "D#4", "F4", "G4", "A4", "A#3", "C5" });
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-7.G.3", juce::String::fromUTF8 ("Tocar a escala lídia"),
                       juce::String::fromUTF8 ("Tocar a escala lídia em Dó (maior com a quarta aumentada)."),
                       juce::String::fromUTF8 ("O app reconhece a sequência da escala lídia em Dó.")), "G");
        m.exercises.back().targets = notes ({ "C4", "D4", "E4", "F#4", "G4", "A4", "B4", "C5" });
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-7.G.4", juce::String::fromUTF8 ("Questionário: notas de repouso"),
                       juce::String::fromUTF8 ("Identificar as notas de repouso de cada modo."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "G");
        m.exercises.back().quiz = {
            question ("As notas de repouso do dórico são:",
                      { "1, b3, 5, 6", "1, 3, 5, 7", "1, 3, #4, 7", "1, 3, 5, b7" }, 0),
            question ("As notas de repouso do lídio são:",
                      { "1, 3, #4, 7", "1, b3, 5, 6", "1, 3, 5, b7", "1, b2, b3, b5" }, 0),
            question ("As notas de repouso do mixolídio são:",
                      { "1, 3, 5, b7", "1, 3, 5, 7", "1, b3, 5, 6", "1, b2, b3, b5" }, 0),
        };

        // --- Topic H — mixolídio sus e mixolídio #4 ---------------------------
        add (exercise ("EX-7.H.1", juce::String::fromUTF8 ("Questionário: mixolídio sus e #4"),
                       juce::String::fromUTF8 ("Responder ao questionário das variações do mixolídio."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "H");
        m.exercises.back().quiz = {
            question ("O mixolídio sus tem a fórmula:",
                      { "1 2 4 5 6 b7 (sem a terça)", "1 2 3 4 5 6 b7",
                        "1 2 3 #4 5 6 b7", "1 b2 b3 4 b5 b6 b7" }, 0),
            question ("O mixolídio #4 tem a fórmula:",
                      { "1 2 3 #4 5 6 b7", "1 2 4 5 6 b7", "1 2 3 4 5 6 b7", "1 2 3 4 5 6 7" }, 0),
            question ("O acorde sus combina com:",
                      { "mixolídio sus", "jônio", "lócrio", "eólio" }, 0),
            question ("O acorde com #11 combina com:",
                      { "mixolídio #4 (lídio dominante)", "dórico", "eólio", "lócrio" }, 0),
            question ("Sobre um acorde sus4, você NÃO deve tocar:",
                      { "a terça", "a quarta", "a quinta", "a sétima menor" }, 0),
        };
        add (exercise ("EX-7.H.2", juce::String::fromUTF8 ("Tocar o acorde sus"),
                       juce::String::fromUTF8 ("Tocar um acorde dominante suspenso (tônica, quarta, quinta e sétima menor)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere o conjunto 0-5-7-10.")), "H");
        m.exercises.back().chordPitchClasses = { 0, 5, 7, 10 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-7.H.3", juce::String::fromUTF8 ("Tocar o acorde com #11"),
                       juce::String::fromUTF8 ("Tocar um acorde dominante com a quarta aumentada (#11)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere o conjunto 0-4-6-10.")), "H");
        m.exercises.back().chordPitchClasses = { 0, 4, 6, 10 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-7.H.4", juce::String::fromUTF8 ("Questionário: escolha da cor"),
                       juce::String::fromUTF8 ("Escolher a variação do mixolídio pela tensão do acorde."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "H");
        m.exercises.back().quiz = {
            question ("Se o acorde tem quarta sem terça (sus4), use:",
                      { "mixolídio sus", "mixolídio natural", "mixolídio #4", "jônio" }, 0),
            question ("Se o acorde tem terça e #11, use:",
                      { "mixolídio #4", "mixolídio sus", "dórico", "eólio" }, 0),
            question ("O acorde sus cria:",
                      { "expectativa, sem definir maior ou menor", "resolução imediata",
                        "uma cadência", "nada" }, 0),
        };

        // --- Topic I — lócrio 9 e alterado ------------------------------------
        add (exercise ("EX-7.I.1", juce::String::fromUTF8 ("Questionário: lócrio 9 e alterado"),
                       juce::String::fromUTF8 ("Responder ao questionário das escalas de tensão."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "I");
        m.exercises.back().quiz = {
            question ("O lócrio 9 é o meio-diminuto com:",
                      { "a nona natural (a segunda maior)", "a b2",
                        "a sétima maior", "a quarta aumentada" }, 0),
            question ("O alterado tem quantas quintas e quantas nonas alteradas?",
                      { "duas quintas e duas nonas", "uma quinta e uma nona",
                        "três quintas", "nenhuma" }, 0),
            question ("O alterado resolve:",
                      { "meio-tom abaixo (ou uma quinta abaixo)", "uma oitava acima",
                        "na mesma nota", "nunca resolve" }, 0),
            question ("O lócrio 9 combina com:",
                      { "Xm7b5 (II grau de II–V–I menor)", "Xmaj7", "X7sus4", "nada" }, 0),
            question ("O alterado combina com:",
                      { "X7alt (V grau)", "Xmaj7", "Xm7", "Xm7b5" }, 0),
        };
        add (exercise ("EX-7.I.2", juce::String::fromUTF8 ("Tocar o acorde meio-diminuto"),
                       juce::String::fromUTF8 ("Tocar um acorde meio-diminuto (tônica, terça menor, quinta diminuta e sétima menor)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere o conjunto 0-3-6-10.")), "I");
        m.exercises.back().chordPitchClasses = { 0, 3, 6, 10 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-7.I.3", juce::String::fromUTF8 ("Tocar o acorde alterado"),
                       juce::String::fromUTF8 ("Tocar um acorde dominante com a quinta aumentada (uma das tensões do alterado)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere o conjunto 0-4-8-10.")), "I");
        m.exercises.back().chordPitchClasses = { 0, 4, 8, 10 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-7.I.4", juce::String::fromUTF8 ("Questionário: II–V–I menor"),
                       juce::String::fromUTF8 ("Identificar as escalas do II–V–I menor."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "I");
        m.exercises.back().quiz = {
            question ("No II–V–I menor, o II grau (Xm7b5) usa:",
                      { "lócrio 9", "alterado", "jônio", "lídio" }, 0),
            question ("No II–V–I menor, o V grau (X7alt) usa:",
                      { "alterado", "lócrio 9", "dórico", "eólio" }, 0),
            question ("O alterado resolve meio-tom abaixo para:",
                      { "um acorde maior", "um acorde sus", "a mesma nota", "nada" }, 0),
        };

        // --- Topic J — aplicações modais no rock e pop-rock -------------------
        add (exercise ("EX-7.J.1", juce::String::fromUTF8 ("Questionário: aplicações modais"),
                       juce::String::fromUTF8 ("Responder ao questionário das aplicações modais no rock."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "J");
        m.exercises.back().quiz = {
            question ("O modo mais usado no rock, sobre acordes dominantes, é:",
                      { "mixolídio", "jônio", "lócrio", "lídio" }, 0),
            question ("O dórico dá ao rock um som:",
                      { "menor aberto, com energia", "menor triste e fechado",
                        "maior brilhante", "suspenso" }, 0),
            question ("O lídio aparece principalmente em:",
                      { "rock progressivo e música instrumental", "marchas",
                        "valsas", "blues de 12" }, 0),
            question ("Uma progressão de dois acordes é típica de:",
                      { "harmonia modal", "harmonia clássica", "atonalismo", "nada" }, 0),
            question ("Sobre um vamp modal, a improvisação:",
                      { "habita a cor, sem resolver", "resolve sempre",
                        "usa só a tônica", "não existe" }, 0),
        };
        add (exercise ("EX-7.J.2", juce::String::fromUTF8 ("Tocar um vamp dórico"),
                       juce::String::fromUTF8 ("Tocar um acorde menor com sétima (a cor do dórico)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere o conjunto 0-3-7-10.")), "J");
        m.exercises.back().chordPitchClasses = { 0, 3, 7, 10 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-7.J.3", juce::String::fromUTF8 ("Tocar um vamp mixolídio"),
                       juce::String::fromUTF8 ("Tocar um acorde dominante (a cor do mixolídio)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere o conjunto 0-4-7-10.")), "J");
        m.exercises.back().chordPitchClasses = { 0, 4, 7, 10 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-7.J.4", juce::String::fromUTF8 ("Questionário: do modal ao funcional"),
                       juce::String::fromUTF8 ("Distinguir harmonia modal de harmonia funcional."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "J");
        m.exercises.back().quiz = {
            question ("A harmonia modal:",
                      { "permanece (um centro, uma cor)", "conduz e resolve",
                        "não tem centro", "usa só tríades" }, 0),
            question ("A harmonia funcional:",
                      { "conduz e resolve (funções)", "só permanece",
                        "não tem função", "usa só clusters" }, 0),
            question ("O riff menor com sexta maior está usando:",
                      { "dórico", "eólio", "lócrio", "jônio" }, 0),
        };

        // The gate closes the module: a II–V–I on the grid, built from the
        // module's material (the structures and chords studied). REQ-009/REQ-015.
        auto& gate = m.exercises.emplace_back (exercise (
            "GATE-7", juce::String::fromUTF8 ("Desafio de gate — II–V–I (Dm7–G7–C7M–C7M)"),
            juce::String::fromUTF8 ("Tocar Dm7 – G7 – C7M – C7M a 84 BPM, na grade do metrônomo."),
            juce::String::fromUTF8 ("Acordes reconhecidos e alinhados à grade (≥ 0,80).")));
        gate.isGate = true;
        gate.lessonId = "J";
        gate.chordProgression = {
            { 2, 5, 9, 0 },   // Dm7
            { 7, 11, 2, 5 },  // G7
            { 0, 4, 7, 11 },  // C7M
            { 0, 4, 7, 11 },  // C7M
        };

        m.gateChallenge = juce::String::fromUTF8 (
            "Tocar o II–V–I Dm7 – G7 – C7M – C7M a 84 BPM com ≥90% de acerto de "
            "acordes e on_grid_ratio ≥ 0,80. Os acordes são construídos pelos "
            "empilhamentos e estruturas estudados no módulo.");

        // Pattern and links the module must cite (REQ-007, REQ-010).
        m.practice.patternId = "PTN-A-DROP2";
        m.practice.patternUse = juce::String::fromUTF8 (
            "Drop 2: as tétrades em estruturas de quatro cordas mostram na prática "
            "os empilhamentos de terça e as tríades do meio. Complemento: "
            "PTN-M-4ths (quartas) para tocar as estruturas modais.");
        m.practice.guitarists = { "Joe Satriani", "Steve Vai", "Guthrie Govan" };

        // Curated apostilas (REQ-006, CM-012); see docs/MUSIC.md §7.
        m.sources = {
            "pdf-teoria-elementar-da-musica-ricordi-osvaldo-lacerda",
            "pdf-p-classtruncatedtext-module-lineclamped-85ulhh-style-max-lines5bohumil-med-teoria-da-musica-5-edicao-p",
            "pdf-mozart-mello-livroestudosdeguitarra4em1",
            "pdf-caged-e-derivaoes-de-acordes-marcelo-mello-apostila-de-violao-e-guitarra-vol1",
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
        makePlaceholder (6,  "II–V–I (menor)",                      3,  80,  0.80f),
        makeModule7(),
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
