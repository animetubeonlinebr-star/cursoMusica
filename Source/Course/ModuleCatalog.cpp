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


    // Module 3 — Etapa 3: ritmo, leitura e levadas. The most rhythmic module of
    // the level: the playable exercises are graded on the metronome grid
    // (usesGrid = true) and the rhythmic cell of the topic appears in m.rhythm
    // (REQ-015). Level 2, target BPM 68, on-grid target 0.77 (MUSIC.md).
    CourseModule makeModule3()
    {
        CourseModule m;
        m.number = 3;
        m.title = juce::String::fromUTF8 ("Ritmo, leitura e levadas");
        m.objective = juce::String::fromUTF8 (
            "Desenvolver a compreensão rítmica e a capacidade de acompanhar "
            "diferentes estilos — lendo o ritmo e tocando levadas na grade.");
        m.level = 2;          // MUSIC.md: módulos 3–4 = nível 2 (vamps de 2 acordes)
        m.targetBpm = 68;     // MUSIC.md, módulo 3
        m.onGridTarget = 0.77f;
        m.implemented = true;

        m.lessons = {
            detail (block ("A", juce::String::fromUTF8 ("Leitura rítmica e convenções de escrita"), {
                "Ritmo é a organização do som no tempo: pulso, tempo e compasso.",
                "Figuras: semibreve (4), mínima (2), semínima (1), colcheia (1/2), semicolcheia (1/4).",
                "Pausas, ponto de aumento e ligadura completam a escrita do ritmo."
            }), content::topic3A()),
            detail (block ("B", juce::String::fromUTF8 ("Pulsação e subdivisão"), {
                "Pulso é a batida constante; subdivisão é reparti-lo em partes iguais.",
                "Binária divide em 2 ou 4; ternária divide em 3.",
                "Cada nível de subdivisão dobra as notas sem mudar o pulso."
            }), content::topic3B()),
            detail (block ("C", juce::String::fromUTF8 ("Cifrado com divisão"), {
                "A cifra diz o acorde; a divisão diz como ele se distribui no tempo.",
                "Acorde sustentado, marcado ou sincopado: escolha por estilo.",
                "O baixo em movimento (C/E, C/G) enriquece a levada sem trocar o acorde."
            }), content::topic3C()),
            detail (block ("D", juce::String::fromUTF8 ("Células rítmicas e acentuações"), {
                "Célula rítmica é um desenho curto de ataques que se repete.",
                "Combinando células, você monta qualquer levada.",
                "Acentuar (tempo forte, fraco ou contratempo) dá o groove."
            }), content::topic3D()),
            detail (block ("E", juce::String::fromUTF8 ("Levadas com palheta"), {
                "A mão direita, com a palheta, faz o ritmo.",
                "Palhetada alternada (para baixo e para cima) economiza movimento.",
                "Palm mute e dinâmica dão relevo à levada de rock."
            }), content::topic3E()),
            detail (block ("F", juce::String::fromUTF8 ("Levadas com os dedos e mapa da mão direita"), {
                "Cada dedo cuida de um grupo de cordas: p nos graves, i/m/a nos agudos.",
                "A levada básica separa o baixo (polegar) do acorde (dedos).",
                "A bossa nova usa polegar nos tempos e dedos nas síncopes."
            }), content::topic3F()),
            detail (block ("G", juce::String::fromUTF8 ("Compassos simples, compostos e fórmulas incomuns"), {
                "A fórmula de compasso diz quantos tempos e qual figura vale um tempo.",
                "Simples divide o tempo em 2; compostos dividem em 3.",
                "5/4 e 7/8 agrupam os tempos em blocos de 2 e 3."
            }), content::topic3G()),
            detail (block ("H", juce::String::fromUTF8 ("Sílabas rítmicas (Konokol), percussões e efeito sanfona"), {
                "Falar o ritmo com sílabas (TÁ, TÁ-KI) antes de tocar.",
                "O Konokol é a solfa rítmica indiana, ótima para ritmos irregulares.",
                "Percussão no violão e efeito sanfona dão groove ao acompanhamento."
            }), content::topic3H()),
        };

        // Exercises: at least three per topic, mixing verifiable quizzes (reading
        // and counting) and playable exercises graded on the metronome grid (the
        // app recognises the notes and checks the alignment, REQ-008/REQ-015).
        // Ids follow EX-3.<topico>.<n>, numbered per topic.
        auto add = [&m] (Exercise e, const char* topic)
        {
            e.lessonId = topic;
            m.exercises.push_back (std::move (e));
            return (int) m.exercises.size() - 1;
        };

        // --- Topic A — leitura rítmica ---------------------------------------
        add (exercise ("EX-3.A.1", juce::String::fromUTF8 ("Questionário: figuras e valores"),
                       juce::String::fromUTF8 ("Responder ao questionário das figuras rítmicas e seus valores."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de leitura rítmica.")), "A");
        m.exercises.back().quiz = {
            question ("Quantos tempos vale uma semibreve em 4/4?",
                      { "1", "2", "4", "8" }, 2),
            question ("Quantos tempos vale uma semínima?",
                      { "1", "2", "1/2", "4" }, 0),
            question ("Quanto vale uma colcheia?",
                      { "1 tempo", "meio tempo", "1/4 de tempo", "dois tempos" }, 1),
            question ("O que o ponto de aumento faz?",
                      { "Acrescenta metade do valor da figura",
                        "Dobra o valor da figura",
                        "Nada",
                        "Divide a figura por dois" }, 0),
            question ("Para que serve a ligadura de valor?",
                      { "Somar a duração de duas notas de mesma altura",
                        "Separar duas notas",
                        "Aumentar o volume",
                        "Mudar a altura" }, 0),
        };
        add (exercise ("EX-3.A.2", juce::String::fromUTF8 ("Tocar semínimas na grade"),
                       juce::String::fromUTF8 ("Tocar quatro semínimas (Dó) na grade do metrônomo, a 68 BPM."),
                       juce::String::fromUTF8 ("Notas reconhecidas e alinhadas à grade (on_grid_ratio ≥ 0,77).")), "A");
        m.exercises.back().targets = notes ({ "C4", "C4", "C4", "C4" });
        m.exercises.back().subdivision = course::TempoGrid::Subdivision::quarter;
        add (exercise ("EX-3.A.3", juce::String::fromUTF8 ("Questionário: pulso, tempo e compasso"),
                       juce::String::fromUTF8 ("Responder ao questionário de pulso, tempo e compasso."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de compasso.")), "A");
        m.exercises.back().quiz = {
            question ("O que é o pulso?",
                      { "A batida regular e constante da música",
                        "O volume da nota",
                        "A altura da nota",
                        "O número de cordas" }, 0),
            question ("Em 4/4, quantos tempos há por compasso?",
                      { "2", "3", "4", "6" }, 2),
            question ("O que a barra de compasso faz?",
                      { "Separa um compasso do seguinte",
                        "Indica o volume",
                        "Muda a tonalidade",
                        "Aumenta o tempo" }, 0),
            question ("O andamento mede o quê?",
                      { "A velocidade do pulso (BPM)",
                        "O volume",
                        "A altura",
                        "O número de notas" }, 0),
        };

        // --- Topic B — pulsação e subdivisão --------------------------------
        add (exercise ("EX-3.B.1", juce::String::fromUTF8 ("Questionário: pulso e subdivisão"),
                       juce::String::fromUTF8 ("Responder ao questionário de pulso e subdivisão."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de subdivisão.")), "B");
        m.exercises.back().quiz = {
            question ("Subdividir é:",
                      { "Repartir o pulso em partes iguais",
                        "Tocar mais rápido",
                        "Aumentar o volume",
                        "Mudar a tonalidade" }, 0),
            question ("A subdivisão binária divide o pulso em:",
                      { "2 partes iguais", "3 partes iguais", "5 partes", "nenhuma" }, 0),
            question ("A subdivisão ternária divide o pulso em:",
                      { "2 partes iguais", "3 partes iguais", "4 partes iguais", "6 partes" }, 1),
            question ("Contar '1 e 2 e 3 e 4 e' corresponde a qual subdivisão?",
                      { "Colcheias", "Tercinas", "Semínimas", "Semibreves" }, 0),
            question ("Qual estilo usa subdivisão ternária?",
                      { "Blues / shuffle", "Rock", "Pop", "Funk" }, 0),
        };
        add (exercise ("EX-3.B.2", juce::String::fromUTF8 ("Tocar colcheias na grade"),
                       juce::String::fromUTF8 ("Tocar oito colcheias (Dó) na grade, dois ataques por tempo."),
                       juce::String::fromUTF8 ("Notas reconhecidas e alinhadas à grade (on_grid_ratio ≥ 0,77).")), "B");
        m.exercises.back().targets = notes ({ "C4", "C4", "C4", "C4", "C4", "C4", "C4", "C4" });
        m.exercises.back().subdivision = course::TempoGrid::Subdivision::eighth;
        add (exercise ("EX-3.B.3", juce::String::fromUTF8 ("Tocar semicolcheias na grade"),
                       juce::String::fromUTF8 ("Tocar dezesseis semicolcheias (Dó) na grade, quatro ataques por tempo."),
                       juce::String::fromUTF8 ("Notas reconhecidas e alinhadas à grade (on_grid_ratio ≥ 0,77).")), "B");
        m.exercises.back().targets = notes ({ "C4", "C4", "C4", "C4", "C4", "C4", "C4", "C4",
                                              "C4", "C4", "C4", "C4", "C4", "C4", "C4", "C4" });
        m.exercises.back().subdivision = course::TempoGrid::Subdivision::sixteenth;
        add (exercise ("EX-3.B.4", juce::String::fromUTF8 ("Tempo forte e fraco"),
                       juce::String::fromUTF8 ("Dizer o peso de cada tempo e o papel do contratempo."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário de acentos.")), "B");
        m.exercises.back().quiz = {
            question ("Em 4/4, qual tempo é o mais forte?",
                      { "1", "2", "3", "4" }, 0),
            question ("O contratempo é:",
                      { "A subdivisão entre dois tempos",
                        "O tempo mais forte",
                        "Uma pausa",
                        "Um acorde" }, 0),
            question ("Acentuar o contratempo é a marca de qual estilo?",
                      { "Samba, funk e bossa", "Marcha", "Valsa", "Hino" }, 0),
            question ("Perder o pulso significa:",
                      { "Não manter a batida constante",
                        "Tocar baixo",
                        "Mudar de acorde",
                        "Parar de tocar" }, 0),
        };

        // --- Topic C — cifrado com divisão ----------------------------------
        add (exercise ("EX-3.C.1", juce::String::fromUTF8 ("Questionário: cifra e divisão"),
                       juce::String::fromUTF8 ("Responder ao questionário de cifra com divisão."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de cifra.")), "C");
        m.exercises.back().quiz = {
            question ("O que a cifra descreve?",
                      { "O acorde", "O ritmo exato", "O volume", "O andamento" }, 0),
            question ("O que a divisão do compasso acrescenta à cifra?",
                      { "Quando e como o acorde é tocado",
                        "A tonalidade",
                        "O volume",
                        "O número de cordas" }, 0),
            question ("Em C/E, o que significa a barra?",
                      { "A nota do baixo é Mi",
                        "O acorde é menor",
                        "Toca duas vezes",
                        "O acorde é suspenso" }, 0),
            question ("Tocar o mesmo acorde em colcheias em vez de semínimas muda:",
                      { "A levada (o ritmo)", "A harmonia", "A tonalidade", "Nada" }, 0),
        };
        add (exercise ("EX-3.C.2", juce::String::fromUTF8 ("Progressão C–G–Am–F na grade"),
                       juce::String::fromUTF8 ("Tocar C – G – Am – F, um acorde por tempo, na grade a 68 BPM."),
                       juce::String::fromUTF8 ("Acordes reconhecidos e alinhados à grade (on_grid_ratio ≥ 0,77).")), "C");
        m.exercises.back().chordProgression = {
            { 0, 4, 7 },    // C
            { 7, 11, 2 },   // G
            { 9, 0, 4 },    // Am
            { 5, 9, 0 },    // F
        };
        add (exercise ("EX-3.C.3", juce::String::fromUTF8 ("Arpejo de Dó na grade"),
                       juce::String::fromUTF8 ("Tocar o arpejo de Dó maior em colcheias, dividindo o compasso."),
                       juce::String::fromUTF8 ("Notas reconhecidas e alinhadas à grade (on_grid_ratio ≥ 0,77).")), "C");
        m.exercises.back().targets = notes ({ "C4", "E4", "G4", "C5", "G4", "E4", "C4", "G3" });
        m.exercises.back().subdivision = course::TempoGrid::Subdivision::eighth;

        // --- Topic D — células rítmicas e acentuações -----------------------
        add (exercise ("EX-3.D.1", juce::String::fromUTF8 ("Questionário: células e acentos"),
                       juce::String::fromUTF8 ("Responder ao questionário de células rítmicas e acentuações."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de células.")), "D");
        m.exercises.back().quiz = {
            question ("O que é uma célula rítmica?",
                      { "Um desenho curto de ataques que se repete",
                        "Um acorde de três notas",
                        "Uma escala",
                        "Um tipo de palheta" }, 0),
            question ("Para que serve uma célula?",
                      { "Montar levadas a partir de um padrão",
                        "Afinar o instrumento",
                        "Aumentar o volume",
                        "Mudar a tonalidade" }, 0),
            question ("Acentuar é:",
                      { "Dar relevo a um tempo ou contratempo",
                        "Tocar mais rápido",
                        "Tocar mais grave",
                        "Parar" }, 0),
            question ("No samba e no funk, o acento cai:",
                      { "No contratempo (o 'e')", "No tempo 1", "Na pausa", "Nunca" }, 0),
        };
        add (exercise ("EX-3.D.2", juce::String::fromUTF8 ("Tocar uma célula de rock na grade"),
                       juce::String::fromUTF8 ("Tocar a célula TA (TA-KI) TA (TA-KI) em Dó, na grade."),
                       juce::String::fromUTF8 ("Notas reconhecidas e alinhadas à grade (on_grid_ratio ≥ 0,77).")), "D");
        m.exercises.back().targets = notes ({ "C4", "C4", "C4", "C4", "C4", "C4" });
        m.exercises.back().subdivision = course::TempoGrid::Subdivision::eighth;
        add (exercise ("EX-3.D.3", juce::String::fromUTF8 ("Células e pausas"),
                       juce::String::fromUTF8 ("Reconhecer o papel das pausas e do abafamento na célula."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de pausas.")), "D");
        m.exercises.back().quiz = {
            question ("Na célula, a pausa serve para:",
                      { "Dar respiração e groove à levada",
                        "Aumentar o volume",
                        "Mudar o acorde",
                        "Afundar o tempo" }, 0),
            question ("Uma 'dead note' (nota abafada) produz:",
                      { "Um som percussivo, sem altura definida",
                        "Uma nota longa",
                        "Um acorde maior",
                        "Silêncio total" }, 0),
            question ("O groove nasce de:",
                      { "Célula + acento + pulso firme",
                        "Volume alto",
                        "Muitas notas",
                        "Tocar rápido" }, 0),
        };

        // --- Topic E — levadas com palheta ----------------------------------
        add (exercise ("EX-3.E.1", juce::String::fromUTF8 ("Questionário: levadas com palheta"),
                       juce::String::fromUTF8 ("Responder ao questionário de levadas com palheta."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de palhetada.")), "E");
        m.exercises.back().quiz = {
            question ("A palhetada alternada é:",
                      { "Alternar ataques para baixo e para cima",
                        "Tocar só para baixo",
                        "Tocar só para cima",
                        "Tocar com os dedos" }, 0),
            question ("O que é palm mute?",
                      { "Abafar as cordas com a base da mão, perto da ponte",
                        "Tocar mais forte",
                        "Usar os dedos",
                        "Afinar a corda" }, 0),
            question ("No rock, a levada típica com palheta:",
                      { "Marca acordes nos tempos fortes, muitas vezes com palm mute",
                        "Usa só notas abafadas",
                        "Toca apenas no contratempo",
                        "Não usa acordes" }, 0),
            question ("A vantagem da palhetada alternada é:",
                      { "Economizar movimento e manter o tempo",
                        "Aumentar o volume",
                        "Mudar a tonalidade",
                        "Tocar mais grave" }, 0),
        };
        add (exercise ("EX-3.E.2", juce::String::fromUTF8 ("Palhetada alternada na corda 6"),
                       juce::String::fromUTF8 ("Tocar oito colcheias na 6ª corda solta (Mi) na grade, a 68 BPM."),
                       juce::String::fromUTF8 ("Notas reconhecidas e alinhadas à grade (on_grid_ratio ≥ 0,77).")), "E");
        m.exercises.back().targets = notes ({ "E2", "E2", "E2", "E2", "E2", "E2", "E2", "E2" });
        m.exercises.back().subdivision = course::TempoGrid::Subdivision::eighth;
        add (exercise ("EX-3.E.3", juce::String::fromUTF8 ("Power chord na grade"),
                       juce::String::fromUTF8 ("Tocar um power chord de Mi (E5: tônica e quinta) na grade."),
                       juce::String::fromUTF8 ("Notas reconhecidas e alinhadas à grade (on_grid_ratio ≥ 0,77).")), "E");
        m.exercises.back().chordPitchClasses = { 4, 11 };   // E5: E + B
        add (exercise ("EX-3.E.4", juce::String::fromUTF8 ("Varredura de acorde"),
                       juce::String::fromUTF8 ("Reconhecer os tipos de varredura (cheia, parcial, alternada)."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de varredura.")), "E");
        m.exercises.back().quiz = {
            question ("A varredura (strumming) é:",
                      { "Passar a palheta por várias cordas em um movimento",
                        "Tocar uma corda só",
                        "Usar os dedos",
                        "Afinar" }, 0),
            question ("Varredura parcial atinge:",
                      { "Apenas algumas cordas (ex.: as agudas)",
                        "Todas as cordas",
                        "Nenhuma corda",
                        "Só a 6ª corda" }, 0),
            question ("Alternar para baixo e para cima na varredura dá:",
                      { "Fluidez à levada",
                        "Mais volume",
                        "Menos groove",
                        "Nada" }, 0),
        };

        // --- Topic F — levadas com os dedos ---------------------------------
        add (exercise ("EX-3.F.1", juce::String::fromUTF8 ("Questionário: mapa da mão direita"),
                       juce::String::fromUTF8 ("Responder ao questionário do fingerstyle e do mapa da mão direita."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de dedos.")), "F");
        m.exercises.back().quiz = {
            question ("No fingerstyle, o polegar (p) cuida de quais cordas?",
                      { "As graves (6ª, 5ª, 4ª)", "As agudas (1ª, 2ª, 3ª)",
                        "Só a 1ª", "Todas" }, 0),
            question ("Na nomenclatura clássica, 'i', 'm' e 'a' são:",
                      { "Indicador, médio e anelar",
                        "Polegar, indicador e médio",
                        "Três cordas",
                        "Três acordes" }, 0),
            question ("Na levada básica de dedos:",
                      { "O polegar marca o baixo e os dedos o acorde",
                        "Os dedos marcam o baixo",
                        "Só o polegar toca",
                        "Nenhum dedo toca" }, 0),
            question ("A bossa nova usa:",
                      { "Polegar nos tempos e dedos nas síncopes",
                        "Só palheta",
                        "Só polegar",
                        "Só o dedo mindinho" }, 0),
        };
        add (exercise ("EX-3.F.2", juce::String::fromUTF8 ("Arpejo com os dedos na grade"),
                       juce::String::fromUTF8 ("Tocar o arpejo de Dó maior com os dedos, em colcheias, na grade."),
                       juce::String::fromUTF8 ("Notas reconhecidas e alinhadas à grade (on_grid_ratio ≥ 0,77).")), "F");
        m.exercises.back().targets = notes ({ "C4", "E4", "G4", "C5", "G4", "E4", "C4", "G3" });
        m.exercises.back().subdivision = course::TempoGrid::Subdivision::eighth;
        add (exercise ("EX-3.F.3", juce::String::fromUTF8 ("Baixo alternado"),
                       juce::String::fromUTF8 ("Tocar o baixo alternado (tônica e quinta de Dó) com o polegar."),
                       juce::String::fromUTF8 ("Notas reconhecidas e alinhadas à grade (on_grid_ratio ≥ 0,77).")), "F");
        m.exercises.back().targets = notes ({ "C4", "G4", "C4", "G4" });
        m.exercises.back().subdivision = course::TempoGrid::Subdivision::quarter;
        add (exercise ("EX-3.F.4", juce::String::fromUTF8 ("Polifonia: duas vozes"),
                       juce::String::fromUTF8 ("Reconhecer as duas vozes do fingerstyle (baixo e agudo)."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de polifonia.")), "F");
        m.exercises.back().quiz = {
            question ("A grande vantagem dos dedos é:",
                      { "Tocar duas vozes (baixo e agudo) ao mesmo tempo",
                        "Tocar mais alto",
                        "Tocar mais rápido",
                        "Afinar melhor" }, 0),
            question ("O arpejo ascendente básico é:",
                      { "p, i, m, a", "a, m, i, p", "p, p, p", "i, i, i" }, 0),
            question ("Hybrid picking combina:",
                      { "Palheta (graves) e dedos (agudos)",
                        "Só dedos",
                        "Só palheta",
                        "Duas palhetas" }, 0),
        };

        // --- Topic G — compassos --------------------------------------------
        add (exercise ("EX-3.G.1", juce::String::fromUTF8 ("Questionário: fórmulas de compasso"),
                       juce::String::fromUTF8 ("Responder ao questionário de compassos simples, compostos e incomuns."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de compasso.")), "G");
        m.exercises.back().quiz = {
            question ("Em uma fórmula de compasso, o número de cima indica:",
                      { "Quantos tempos há no compasso",
                        "Qual figura vale um tempo",
                        "O volume",
                        "O andamento" }, 0),
            question ("Um compasso composto divide o tempo em:",
                      { "3 partes iguais", "2 partes iguais", "4 partes iguais", "5 partes" }, 0),
            question ("O compasso 6/8 é sentido como:",
                      { "Dois grupos de três colcheias", "Três tempos de dois",
                        "Quatro tempos", "Um tempo só" }, 0),
            question ("Um 7/8 pode ser agrupado como:",
                      { "2 + 2 + 3", "5 + 5", "3 + 3 + 3", "sempre 4 + 3" }, 0),
        };
        // 6/8 is compound: the eighth notes group 3 + 3 around the dotted-minim
        // pulse. TempoGrid does not model 6/8 directly, so the exercise is graded
        // on a triplet grid (3 ticks per beat) where six notes over two beats
        // land exactly as two groups of three.
        add (exercise ("EX-3.G.2", juce::String::fromUTF8 ("Seis colcheias em 6/8 na grade ternária"),
                       juce::String::fromUTF8 ("Tocar seis colcheias (Dó, Ré, Mi) agrupando 3 + 3, o balanço do 6/8, na grade ternária a 68 BPM."),
                       juce::String::fromUTF8 ("Notas reconhecidas e alinhadas à grade ternária (on_grid_ratio ≥ 0,77).")), "G");
        m.exercises.back().targets = notes ({ "C4", "C4", "C4", "D4", "D4", "D4" });
        m.exercises.back().subdivision = course::TempoGrid::Subdivision::triplet;
        add (exercise ("EX-3.G.3", juce::String::fromUTF8 ("Formula incomum 5/4"),
                       juce::String::fromUTF8 ("Reconhecer os agrupamentos de um 5/4 e de um 7/8."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de fórmulas incomuns.")), "G");
        m.exercises.back().quiz = {
            question ("Um 5/4 agrupado como 3 + 2 conta-se:",
                      { "1 2 3 / 1 2", "1 2 / 1 2 3 / 1 2", "1 2 3 4 5", "1 / 2 / 3 / 4 / 5" }, 0),
            question ("Qual estilo costuma usar 5/4 e 7/8?",
                      { "Jazz moderno e prog rock", "Valsa", "Marcha", "Hino" }, 0),
            question ("Contar o agrupamento de um compasso incomum serve para:",
                      { "Não se perder no meio do compasso",
                        "Aumentar o volume",
                        "Mudar a tonalidade",
                        "Afinar" }, 0),
        };

        // --- Topic H — Konokol, percussão e efeito sanfona ------------------
        add (exercise ("EX-3.H.1", juce::String::fromUTF8 ("Questionário: sílabas, percussão e sanfona"),
                       juce::String::fromUTF8 ("Responder ao questionário de sílabas rítmicas, percussão e efeito sanfona."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de sílabas e percussão.")), "H");
        m.exercises.back().quiz = {
            question ("A sílaba 'TÁ-KI' representa:",
                      { "Duas colcheias", "Uma semínima", "Quatro semicolcheias", "Uma pausa" }, 0),
            question ("O Konokol é:",
                      { "Um sistema de solfa rítmica indiana",
                        "Um tipo de acorde",
                        "Uma afinação",
                        "Um estilo de rock" }, 0),
            question ("O efeito sanfona consiste em:",
                      { "Alternar o acorde aberto e abafado",
                        "Tocar mais rápido",
                        "Afinar a corda",
                        "Usar só os dedos" }, 0),
            question ("Bater na madeira do violão serve para:",
                      { "Marcar o tempo com percussão",
                        "Aumentar o volume",
                        "Mudar a tonalidade",
                        "Afinar" }, 0),
        };
        add (exercise ("EX-3.H.2", juce::String::fromUTF8 ("Célula rítmica falada e tocada"),
                       juce::String::fromUTF8 ("Falar as sílabas e tocar a célula em Dó na grade, a 68 BPM."),
                       juce::String::fromUTF8 ("Notas reconhecidas e alinhadas à grade (on_grid_ratio ≥ 0,77).")), "H");
        m.exercises.back().targets = notes ({ "C4", "E4", "D4", "F4", "E4", "G4", "C5", "G4" });
        m.exercises.back().subdivision = course::TempoGrid::Subdivision::eighth;
        add (exercise ("EX-3.H.3", juce::String::fromUTF8 ("Efeito sanfona na grade"),
                       juce::String::fromUTF8 ("Tocar o acorde de Dó maior alternando aberto e abafado, na grade."),
                       juce::String::fromUTF8 ("Acorde reconhecido e alinhado à grade (on_grid_ratio ≥ 0,77).")), "H");
        m.exercises.back().chordPitchClasses = { 0, 4, 7 };   // C major

        // The gate closes the module: a two-chord vamp (C–G) on the grid, built
        // from the material of the module (REQ-009, REQ-015). Level 2 = vamps of
        // two chords (MUSIC.md).
        auto& gate = m.exercises.emplace_back (exercise (
            "GATE-3", juce::String::fromUTF8 ("Desafio de gate — vamp C–G a 68 BPM"),
            juce::String::fromUTF8 ("Tocar C – G – C – G (vamp de 2 acordes) a 68 BPM, na grade do metrônomo."),
            juce::String::fromUTF8 ("Acordes reconhecidos e alinhados à grade (≥ 0,77).")));
        gate.isGate = true;
        gate.lessonId = "H";
        gate.chordProgression = {
            { 0, 4, 7 },    // C
            { 7, 11, 2 },   // G
            { 0, 4, 7 },    // C
            { 7, 11, 2 },   // G
        };

        m.gateChallenge = juce::String::fromUTF8 (
            "Tocar C – G (vamp de 2 acordes, nível 2) a 68 BPM com ≥90% de acerto "
            "de acordes e on_grid_ratio ≥ 0,77. Os acordes são tocados na levada "
            "estudada no módulo, mantendo o pulso firme.");

        // Pattern and link the module must cite (REQ-007, REQ-010).
        m.practice.patternId = "PTN-R-PALM";
        m.practice.patternUse = juce::String::fromUTF8 (
            "Pedal point abafado + power chords: a base rítmica do módulo, com "
            "palm mute e palhetada alternada. Complemento: PTN-R-BOSSA (polegar "
            "nos tempos, dedos nas síncopes) para a levada de dedos.");
        m.practice.guitarists = { "Kiko Loureiro", "Juninho Afram", "John Petrucci" };

        // Counting cells for the metronome (REQ-015); syllables from the
        // rhythmic reading chapter of the curated apostila (MUSIC.md, block I).
        m.rhythm = {
            { juce::String::fromUTF8 ("Semínima"), juce::String::fromUTF8 ("1 tempo (1/4)"),
              juce::String::fromUTF8 ("TÁ") },
            { juce::String::fromUTF8 ("Colcheias"), juce::String::fromUTF8 ("2 por tempo (2/8)"),
              juce::String::fromUTF8 ("TÁ-KI") },
            { juce::String::fromUTF8 ("Semicolcheias"), juce::String::fromUTF8 ("4 por tempo (4/16)"),
              juce::String::fromUTF8 ("TA-KI-TA-KI") },
            { juce::String::fromUTF8 ("Tercinas"), juce::String::fromUTF8 ("3 por tempo (ternário)"),
              juce::String::fromUTF8 ("TÁ-KI-TA") },
        };

        // Curated apostilas (REQ-006, CM-012); see docs/MUSIC.md. The rhythm
        // chapter of fraseado-melodico, the metric chapter of Bohumil Med and
        // the studies of Mozart Mello back the module.
        m.sources = {
            "pdf-fraseado-melodico",
            "pdf-p-classtruncatedtext-module-lineclamped-85ulhh-style-max-lines5bohumil-med-teoria-da-musica-5-edicao-p",
            "pdf-mozart-mello-livroestudosdeguitarra4em1",
            "pdf-teoria-elementar-da-musica-ricordi-osvaldo-lacerda",
        };

        return m;
    }


    // Module 4 — Etapa 4: construção de acordes (tríades e tétrades). Following
    // module 2's pattern: part of the exercises is played on the instrument and
    // the app recognises the notes (Exercise::chordPitchClasses / Exercise::interval),
    // so any position on the neck is accepted. Every topic carries images,
    // tables, audio examples and scores with their audio, and >=5 pages
    // (content::minTopicChars).
    CourseModule makeModule4()
    {
        CourseModule m;
        m.number = 4;
        m.title = juce::String::fromUTF8 ("Construção de acordes: tríades e tétrades");
        m.objective = juce::String::fromUTF8 (
            "Compreender a formação dos acordes e suas diferentes possibilidades de "
            "execução — construindo tríades e tétrades, identificando as notas e "
            "executando inversões e posições.");
        m.level = 2;          // MUSIC.md: módulos 3–4 = nível 2 (vamps de 2 acordes)
        m.targetBpm = 72;     // MUSIC.md, módulo 4
        m.onGridTarget = 0.78f;
        m.implemented = true;

        m.lessons = {
            detail (block ("A", juce::String::fromUTF8 ("Tríades maiores e menores"), {
                "Tríade é um acorde de três notas: tônica, terça e quinta.",
                "Maior = 0–4–7; menor = 0–3–7; a diferença está na terça.",
                "A receita vale em qualquer tônica e posição do braço."
            }), content::topic4A()),
            detail (block ("B", juce::String::fromUTF8 ("Tríades aumentadas e diminutas"), {
                "Aumentada = 0–4–8 (quinta aumentada); diminuta = 0–3–6 (quinta diminuta).",
                "São sons de tensão: a aumentada flutua, a diminuta pede resolução.",
                "Na cifra: '+' ou 'aug' para aumentada, 'dim' ou '°' para diminuta."
            }), content::topic4B()),
            detail (block ("C", juce::String::fromUTF8 ("Tríades abertas e fechadas"), {
                "Disposição é a ordem e o espaçamento das notas do acorde.",
                "Fechada: notas próximas, som compacto; aberta: espalhadas, som amplo.",
                "As notas não mudam; só a distribuição muda."
            }), content::topic4C()),
            detail (block ("D", juce::String::fromUTF8 ("Inversões"), {
                "Inverter é mudar a nota do baixo, mantendo as mesmas notas.",
                "Fundamental: tônica no baixo; 1ª inversão: terça; 2ª inversão: quinta.",
                "Na cifra, a inversão vem depois da barra (C/E, C/G)."
            }), content::topic4D()),
            detail (block ("E", juce::String::fromUTF8 ("Tétrades"), {
                "Tétrade = tríade + sétima: 7M, 7, m7 e m7♭5.",
                "A sétima maior (11 semitons) repousa; a menor (10) pede resolução.",
                "Tétrades dão a cor do jazz, da bossa e da MPB."
            }), content::topic4E()),
            detail (block ("F", juce::String::fromUTF8 ("Formação de acordes"), {
                "Formar acorde = empilhar terças sobre a tônica.",
                "As notas essenciais são a tônica, a terça e a sétima.",
                "A cifra dá a tônica e a qualidade; a receita de semitons monta o acorde."
            }), content::topic4F()),
            detail (block ("G", juce::String::fromUTF8 ("Sistema 5 (CAGED) e famílias de acordes"), {
                "O CAGED é um mapa de cinco formas que cobrem o braço.",
                "Cada forma é um molde: serve para maior, menor, sétima e outras.",
                "As formas se conectam em ciclo: C → A → G → E → D → C."
            }), content::topic4G()),
            detail (block ("H", juce::String::fromUTF8 ("As cinco fases das famílias"), {
                "Cinco fases: forma → transposição → troca → progressão → criação.",
                "Cada fase dá a base para a seguinte; respeite a ordem.",
                "As fases valem para qualquer família (maior, menor, dominante…)."
            }), content::topic4H()),
            detail (block ("I", juce::String::fromUTF8 ("Acordes clean e distribuição pelo braço"), {
                "Clean: sem corda abafada, sem zumbido e sem nota errada.",
                "Dedo junto ao traste, pressão mínima, cordas certas abafadas.",
                "Distribuir é escolher a região do braço e a nota do baixo."
            }), content::topic4I()),
        };

        // Exercises: at least three per topic, mixing verifiable quizzes and
        // playable exercises. The app recognises the notes of a chord
        // (chordPitchClasses) or the distance the instrument produced
        // (intervalExercise), so any position on the neck is accepted. Ids
        // follow EX-4.<topico>.<n>, numbered per topic.
        auto add = [&m] (Exercise e, const char* topic)
        {
            e.lessonId = topic;
            m.exercises.push_back (std::move (e));
            return (int) m.exercises.size() - 1;
        };

        // --- Topic A — tríades maiores e menores -----------------------------
        add (exercise ("EX-4.A.1", juce::String::fromUTF8 ("Questionário: tríades"),
                       juce::String::fromUTF8 ("Responder ao questionário de formação das tríades."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de tríades.")), "A");
        m.exercises.back().quiz = {
            question ("Quantas notas tem uma tríade?",
                      { "duas", "três", "quatro", "cinco" }, 1),
            question ("Uma tríade maior é formada por quais semitons?",
                      { "0, 4, 7", "0, 3, 7", "0, 3, 6", "0, 4, 8" }, 0),
            question ("A diferença entre a tríade maior e a menor está:",
                      { "na tônica", "na terça", "na quinta", "na oitava" }, 1),
            question ("Qual é a única nota que muda de Dó maior para Dó menor?",
                      { "Mi vira Mi♭", "Sol vira Sol♭", "Dó vira Si", "Sol vira Lá" }, 0),
            question ("Tocar o mesmo acorde em outra posição do braço:",
                      { "muda o acorde", "muda as notas", "mantém o acorde", "muda a tonalidade" }, 2),
        };
        add (exercise ("EX-4.A.2", juce::String::fromUTF8 ("Tocar a tríade maior"),
                       juce::String::fromUTF8 ("Tocar uma tríade maior (tônica, terça maior e quinta justa)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere a tríade maior (0–4–7), em qualquer posição do braço.")), "A");
        m.exercises.back().chordPitchClasses = { 0, 4, 7 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-4.A.3", juce::String::fromUTF8 ("Tocar a tríade menor"),
                       juce::String::fromUTF8 ("Tocar uma tríade menor (tônica, terça menor e quinta justa)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere a tríade menor (0–3–7), em qualquer posição do braço.")), "A");
        m.exercises.back().chordPitchClasses = { 0, 3, 7 };
        m.exercises.back().usesGrid = false;
        add (intervalExercise ("EX-4.A.4", "A terça da tríade",
                               "Tocar uma terça maior (4 semitons) a partir de qualquer nota, três vezes.", 4, 3), "A");
        add (exercise ("EX-4.A.5", juce::String::fromUTF8 ("Nomear as notas da tríade"),
                       juce::String::fromUTF8 ("Dizer as três notas de tríades básicas."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário de notas.")), "A");
        m.exercises.back().quiz = {
            question ("Quais são as notas de Dó maior?",
                      { "Dó–Mi–Sol", "Dó–Mi♭–Sol", "Dó–Fá–Sol", "Dó–Mi–Lá" }, 0),
            question ("Quais são as notas de Lá menor?",
                      { "Lá–Dó–Mi", "Lá–Dó♯–Mi", "Lá–Ré–Fá", "Lá–Si–Mi" }, 0),
            question ("Em Sol maior, qual é a terça?",
                      { "Si", "Lá", "Dó", "Ré" }, 0),
            question ("Em Ré menor, qual é a terça?",
                      { "Fá", "Fá♯", "Sol", "Lá" }, 0),
        };

        // --- Topic B — tríades aumentadas e diminutas ------------------------
        add (exercise ("EX-4.B.1", juce::String::fromUTF8 ("Questionário: aumentadas e diminutas"),
                       juce::String::fromUTF8 ("Responder ao questionário das tríades alteradas."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "B");
        m.exercises.back().quiz = {
            question ("A tríade aumentada usa quais semitons?",
                      { "0, 4, 7", "0, 3, 7", "0, 4, 8", "0, 3, 6" }, 2),
            question ("A tríade diminuta usa quais semitons?",
                      { "0, 4, 7", "0, 3, 7", "0, 4, 8", "0, 3, 6" }, 3),
            question ("Quais são as notas de Dó aumentado?",
                      { "Dó–Mi–Sol♯", "Dó–Mi♭–Sol♭", "Dó–Mi–Sol", "Dó–Mi♭–Sol" }, 0),
            question ("Quais são as notas de Dó diminuto?",
                      { "Dó–Mi–Sol♯", "Dó–Mi♭–Sol♭", "Dó–Mi–Sol", "Dó–Mi♭–Sol" }, 1),
            question ("A tríade diminuta aparece naturalmente no grau:",
                      { "I", "IV", "V", "vii" }, 3),
        };
        add (exercise ("EX-4.B.2", juce::String::fromUTF8 ("Tocar a tríade aumentada"),
                       juce::String::fromUTF8 ("Tocar uma tríade aumentada (tônica, terça maior e quinta aumentada)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere a tríade aumentada (0–4–8), em qualquer posição do braço.")), "B");
        m.exercises.back().chordPitchClasses = { 0, 4, 8 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-4.B.3", juce::String::fromUTF8 ("Tocar a tríade diminuta"),
                       juce::String::fromUTF8 ("Tocar uma tríade diminuta (tônica, terça menor e quinta diminuta)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere a tríade diminuta (0–3–6), em qualquer posição do braço.")), "B");
        m.exercises.back().chordPitchClasses = { 0, 3, 6 };
        m.exercises.back().usesGrid = false;
        add (intervalExercise ("EX-4.B.4", "A quinta alterada",
                               "Tocar um trítono (6 semitons) a partir de qualquer nota, duas vezes.", 6, 2), "B");

        // --- Topic C — tríades abertas e fechadas ----------------------------
        add (exercise ("EX-4.C.1", juce::String::fromUTF8 ("Questionário: abertas e fechadas"),
                       juce::String::fromUTF8 ("Responder ao questionário das disposições."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de disposição.")), "C");
        m.exercises.back().quiz = {
            question ("Na disposição fechada, as notas ficam:",
                      { "próximas umas das outras", "espalhadas pelo braço",
                        "sempre na 1ª corda", "sempre em oitavas" }, 0),
            question ("Na disposição aberta, o som é:",
                      { "compacto e direto", "amplo e cheio",
                        "sempre menor", "sempre igual" }, 1),
            question ("Mudar a disposição de um acorde:",
                      { "muda as notas", "muda o acorde",
                        "mantém as notas", "muda a tonalidade" }, 2),
            question ("Uma disposição ideal para acompanhamento rítmico é:",
                      { "fechada", "aberta", "aleatória", "sem notas" }, 0),
        };
        add (exercise ("EX-4.C.2", juce::String::fromUTF8 ("Dó maior em disposição fechada"),
                       juce::String::fromUTF8 ("Tocar Dó maior com as notas próximas (disposição fechada)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere o acorde (0–4–7), em qualquer posição do braço.")), "C");
        m.exercises.back().chordPitchClasses = { 0, 4, 7 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-4.C.3", juce::String::fromUTF8 ("Sol maior em disposição aberta"),
                       juce::String::fromUTF8 ("Tocar Sol maior com as notas espalhadas (disposição aberta)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere o acorde (7–11–2), em qualquer posição do braço.")), "C");
        m.exercises.back().chordPitchClasses = { 7, 11, 2 };
        m.exercises.back().usesGrid = false;
        add (intervalExercise ("EX-4.C.4", "A quinta do acorde",
                               "Tocar uma quinta justa (7 semitons) a partir de qualquer nota, três vezes.", 7, 3), "C");

        // --- Topic D — inversões ---------------------------------------------
        add (exercise ("EX-4.D.1", juce::String::fromUTF8 ("Questionário: inversões"),
                       juce::String::fromUTF8 ("Responder ao questionário das inversões."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de inversão.")), "D");
        m.exercises.back().quiz = {
            question ("Inverter um acorde é:",
                      { "mudar a nota do baixo", "mudar as notas do acorde",
                        "mudar a tonalidade", "tirar uma nota" }, 0),
            question ("Na 1ª inversão, qual nota fica no baixo?",
                      { "a tônica", "a terça", "a quinta", "a sétima" }, 1),
            question ("Na 2ª inversão, qual nota fica no baixo?",
                      { "a tônica", "a terça", "a quinta", "a sétima" }, 2),
            question ("A cifra C/E significa:",
                      { "Dó com Mi no baixo", "Mi com Dó no baixo",
                        "Dó com Sol no baixo", "Dó menor" }, 0),
            question ("O acorde invertido, em relação ao original:",
                      { "é outro acorde", "tem as mesmas notas",
                        "tem menos notas", "muda a tonalidade" }, 1),
        };
        add (exercise ("EX-4.D.2", juce::String::fromUTF8 ("Dó maior com Mi no baixo"),
                       juce::String::fromUTF8 ("Tocar Dó maior na 1ª inversão (Mi no baixo)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere o acorde (0–4–7), em qualquer posição do braço.")), "D");
        m.exercises.back().chordPitchClasses = { 0, 4, 7 };
        m.exercises.back().usesGrid = false;
        add (intervalExercise ("EX-4.D.3", "A terça menor da inversão",
                               "Tocar uma terça menor (3 semitons) a partir de qualquer nota, três vezes.", 3, 3), "D");
        add (exercise ("EX-4.D.4", juce::String::fromUTF8 ("Inversões e a linha do baixo"),
                       juce::String::fromUTF8 ("Relacionar inversões à condução do baixo."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário de aplicação.")), "D");
        m.exercises.back().quiz = {
            question ("A principal aplicação das inversões é:",
                      { "suavizar a linha do baixo", "aumentar o volume",
                        "mudar a tonalidade", "tocar mais rápido" }, 0),
            question ("Numa progressão que desce por graus, a inversão serve para:",
                      { "manter o baixo caminhando", "abafar as cordas",
                        "tirar a terça", "tocar mais alto" }, 0),
            question ("A 2ª inversão soa:",
                      { "estável e conclusiva", "instável, de passagem",
                        "igual à fundamental", "sempre menor" }, 1),
        };

        // --- Topic E — tétrades ----------------------------------------------
        add (exercise ("EX-4.E.1", juce::String::fromUTF8 ("Questionário: tétrades"),
                       juce::String::fromUTF8 ("Responder ao questionário das tétrades."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de tétrades.")), "E");
        m.exercises.back().quiz = {
            question ("Uma tétrade é formada por:",
                      { "três notas", "quatro notas", "cinco notas", "duas notas" }, 1),
            question ("C7M (sétima maior) usa qual sétima?",
                      { "11 semitons (maior)", "10 semitons (menor)",
                        "9 semitons", "12 semitons" }, 0),
            question ("C7 (dominante) usa qual sétima?",
                      { "11 semitons", "10 semitons", "6 semitons", "7 semitons" }, 1),
            question ("Cm7 tem os semitons:",
                      { "0, 3, 7, 10", "0, 4, 7, 11", "0, 4, 7, 10", "0, 3, 6, 10" }, 0),
            question ("O acorde meio-diminuto (m7♭5) tem os semitons:",
                      { "0, 3, 6, 10", "0, 4, 7, 11", "0, 3, 7, 10", "0, 4, 8, 11" }, 0),
        };
        add (exercise ("EX-4.E.2", juce::String::fromUTF8 ("Tocar a sétima maior"),
                       juce::String::fromUTF8 ("Tocar uma tétrade de sétima maior (tônica, terça, quinta e sétima maior)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere a tétrade 7M (0–4–7–11), em qualquer posição do braço.")), "E");
        m.exercises.back().chordPitchClasses = { 0, 4, 7, 11 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-4.E.3", juce::String::fromUTF8 ("Tocar o dominante"),
                       juce::String::fromUTF8 ("Tocar uma tétrade de sétima dominante (tônica, terça, quinta e sétima menor)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere a tétrade 7 (0–4–7–10), em qualquer posição do braço.")), "E");
        m.exercises.back().chordPitchClasses = { 0, 4, 7, 10 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-4.E.4", juce::String::fromUTF8 ("Tocar a menor com sétima"),
                       juce::String::fromUTF8 ("Tocar uma tétrade menor com sétima (tônica, terça menor, quinta e sétima menor)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere a tétrade m7 (0–3–7–10), em qualquer posição do braço.")), "E");
        m.exercises.back().chordPitchClasses = { 0, 3, 7, 10 };
        m.exercises.back().usesGrid = false;
        add (intervalExercise ("EX-4.E.5", "A sétima maior",
                               "Tocar uma sétima maior (11 semitons) a partir de qualquer nota, duas vezes.", 11, 2), "E");

        // --- Topic F — formação de acordes -----------------------------------
        add (exercise ("EX-4.F.1", juce::String::fromUTF8 ("Questionário: formação de acordes"),
                       juce::String::fromUTF8 ("Responder ao questionário da formação de acordes."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de formação.")), "F");
        m.exercises.back().quiz = {
            question ("Formar um acorde é:",
                      { "empilhar terças sobre a tônica", "somar volumes",
                        "repetir a tônica", "tocar só a quinta" }, 0),
            question ("As notas essenciais de um acorde são:",
                      { "tônica, terça e sétima", "tônica e quinta",
                        "só a terça", "todas as notas" }, 0),
            question ("Acrescentar a sétima menor (10 semitons) a uma tríade maior forma:",
                      { "acorde de sétima maior", "acorde de sétima dominante",
                        "acorde diminuto", "acorde suspenso" }, 1),
            question ("As notas de F7M são:",
                      { "Fá–Lá–Dó–Mi", "Fá–Lá♭–Dó–Mi♭", "Fá–Lá–Dó–Mi♭", "Fá–Sol–Dó–Mi" }, 0),
            question ("O acorde suspenso (sus4) substitui a terça por:",
                      { "a quarta", "a quinta", "a sétima", "a nona" }, 0),
        };
        add (exercise ("EX-4.F.2", juce::String::fromUTF8 ("Montar Fá maior"),
                       juce::String::fromUTF8 ("Tocar Fá maior (Fá–Lá–Dó), formada por empilhamento de terças."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere o acorde (5–9–0), em qualquer posição do braço.")), "F");
        m.exercises.back().chordPitchClasses = { 5, 9, 0 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-4.F.3", juce::String::fromUTF8 ("Montar Sol maior"),
                       juce::String::fromUTF8 ("Tocar Sol maior (Sol–Si–Ré), formada por empilhamento de terças."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere o acorde (7–11–2), em qualquer posição do braço.")), "F");
        m.exercises.back().chordPitchClasses = { 7, 11, 2 };
        m.exercises.back().usesGrid = false;
        add (intervalExercise ("EX-4.F.4", "A quinta da formação",
                               "Tocar uma quinta justa (7 semitons) a partir de qualquer nota, três vezes.", 7, 3), "F");
        add (exercise ("EX-4.F.5", juce::String::fromUTF8 ("Ler a cifra e formar o acorde"),
                       juce::String::fromUTF8 ("Relacionar cifra, tônica e qualidade."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário de cifra.")), "F");
        m.exercises.back().quiz = {
            question ("Na cifra, 'm' significa:",
                      { "maior", "menor", "aumentado", "meio-diminuto" }, 1),
            question ("Na cifra, '7M' significa:",
                      { "sétima maior", "sétima menor", "sétima dominante", "menor com sétima" }, 0),
            question ("A cifra 'Am7' pede:",
                      { "Lá menor com sétima", "Lá maior com sétima",
                        "Lá diminuto", "Lá suspenso" }, 0),
            question ("A tônica de 'Dm' é:",
                      { "Ré", "Fá", "Lá", "Dó" }, 0),
        };

        // --- Topic G — CAGED e famílias --------------------------------------
        add (exercise ("EX-4.G.1", juce::String::fromUTF8 ("Questionário: CAGED e famílias"),
                       juce::String::fromUTF8 ("Responder ao questionário do sistema CAGED."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões do CAGED.")), "G");
        m.exercises.back().quiz = {
            question ("As cinco formas do CAGED são:",
                      { "C, A, G, E, D", "A, B, C, D, E", "I, IV, V, vi, vii", "Dó, Ré, Mi, Fá, Sol" }, 0),
            question ("Cada forma do CAGED é:",
                      { "um molde para várias qualidades", "um acorde único",
                        "uma escala apenas", "uma corda" }, 0),
            question ("Para transformar uma forma maior em menor:",
                      { "desça a terça um semitom", "suba a quinta um semitom",
                        "tire a tônica", "dobre a tônica" }, 0),
            question ("A ordem do ciclo das formas é:",
                      { "C → A → G → E → D", "A → C → E → G → D",
                        "E → A → D → G → C", "G → E → D → A → C" }, 0),
            question ("Dentro de Dó maior, o grau V pertence à família:",
                      { "maior", "menor", "dominante", "diminuta" }, 2),
        };
        add (exercise ("EX-4.G.2", juce::String::fromUTF8 ("Lá menor pela família"),
                       juce::String::fromUTF8 ("Tocar Lá menor (Lá–Dó–Mi) usando uma forma do CAGED."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere o acorde (9–0–4), em qualquer posição do braço.")), "G");
        m.exercises.back().chordPitchClasses = { 9, 0, 4 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-4.G.3", juce::String::fromUTF8 ("Ré menor pela família"),
                       juce::String::fromUTF8 ("Tocar Ré menor (Ré–Fá–Lá) usando uma forma do CAGED."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere o acorde (2–5–9), em qualquer posição do braço.")), "G");
        m.exercises.back().chordPitchClasses = { 2, 5, 9 };
        m.exercises.back().usesGrid = false;
        add (intervalExercise ("EX-4.G.4", "A terça da família",
                               "Tocar uma terça maior (4 semitons) a partir de qualquer nota, três vezes.", 4, 3), "G");

        // --- Topic H — as cinco fases ----------------------------------------
        add (exercise ("EX-4.H.1", juce::String::fromUTF8 ("Questionário: as cinco fases"),
                       juce::String::fromUTF8 ("Responder ao questionário das cinco fases."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões das fases.")), "H");
        m.exercises.back().quiz = {
            question ("A ordem das cinco fases é:",
                      { "forma → transposição → troca → progressão → criação",
                        "criação → forma → troca → transposição → progressão",
                        "transposição → forma → criação → troca → progressão",
                        "progressão → troca → forma → criação → transposição" }, 0),
            question ("Na fase 1, o objetivo é:",
                      { "montar a forma sem olhar", "criar vozes próprias",
                        "improvisar", "tocar rápido" }, 0),
            question ("Na fase 2, você treina:",
                      { "transpor a forma pelo braço", "abafar cordas",
                        "afinar", "cantar" }, 0),
            question ("A partir de qual fase o metrônomo é essencial?",
                      { "1", "2", "3", "5" }, 2),
            question ("A fase 5 é a fase de:",
                      { "criar e inverter livremente", "decorar formas",
                        "tocar devagar", "ler cifra" }, 0),
        };
        add (exercise ("EX-4.H.2", juce::String::fromUTF8 ("Dó maior pelas fases"),
                       juce::String::fromUTF8 ("Tocar Dó maior (Dó–Mi–Sol) montando a forma com precisão."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere o acorde (0–4–7), em qualquer posição do braço.")), "H");
        m.exercises.back().chordPitchClasses = { 0, 4, 7 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-4.H.3", juce::String::fromUTF8 ("Menor com sétima pelas fases"),
                       juce::String::fromUTF8 ("Tocar Lá menor com sétima (Lá–Dó–Mi–Sol)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere a tétrade m7 (9–0–4–7), em qualquer posição do braço.")), "H");
        m.exercises.back().chordPitchClasses = { 9, 0, 4, 7 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-4.H.4", juce::String::fromUTF8 ("Das fases para a música"),
                       juce::String::fromUTF8 ("Relacionar as fases ao acompanhamento real."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário de aplicação.")), "H");
        m.exercises.back().quiz = {
            question ("Pular etapas no estudo das famílias:",
                      { "acelera sem prejuízo", "gera vícios difíceis de corrigir",
                        "é indiferente", "é obrigatório" }, 1),
            question ("A fase 4 consiste em:",
                      { "aplicar a família em uma progressão", "decorar formas",
                        "afinar o instrumento", "só ler cifra" }, 0),
            question ("A velocidade deve ser buscada:",
                      { "antes da precisão", "depois da precisão",
                        "nunca", "só no palco" }, 1),
        };

        // --- Topic I — acordes clean e distribuição --------------------------
        add (exercise ("EX-4.I.1", juce::String::fromUTF8 ("Questionário: clean e distribuição"),
                       juce::String::fromUTF8 ("Responder ao questionário de acordes clean."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de limpeza.")), "I");
        m.exercises.back().quiz = {
            question ("Um acorde clean é aquele que:",
                      { "não tem corda abafada nem zumbido", "é tocado bem rápido",
                        "usa todas as cordas", "tem sempre sétima" }, 0),
            question ("Para o som sair limpo, o dedo deve pressionar:",
                      { "junto ao traste", "no meio da casa",
                        "em cima do traste", "na corda vizinha" }, 0),
            question ("As cordas que não pertencem ao acorde devem ser:",
                      { "abafadas de propósito", "tocadas normalmente",
                        "sempre soltas", "sempre a 12ª casa" }, 0),
            question ("Na pestana, o polegar deve:",
                      { "apoiar no meio do braço", "ficar solto",
                        "apertar a corda", "apoiar no captador" }, 0),
            question ("Distribuir acordes pelo braço é:",
                      { "escolher a região e a nota do baixo", "tocar mais alto",
                        "abafar todas as cordas", "usar só a 1ª posição" }, 0),
        };
        add (exercise ("EX-4.I.2", juce::String::fromUTF8 ("Dó maior clean"),
                       juce::String::fromUTF8 ("Tocar Dó maior sem nenhuma corda abafada."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere o acorde (0–4–7), em qualquer posição do braço.")), "I");
        m.exercises.back().chordPitchClasses = { 0, 4, 7 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-4.I.3", juce::String::fromUTF8 ("Sol maior em outra região"),
                       juce::String::fromUTF8 ("Tocar Sol maior distribuído em uma região diferente do braço."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere o acorde (7–11–2), em qualquer posição do braço.")), "I");
        m.exercises.back().chordPitchClasses = { 7, 11, 2 };
        m.exercises.back().usesGrid = false;
        add (intervalExercise ("EX-4.I.4", "A quinta limpa",
                               "Tocar uma quinta justa (7 semitons) a partir de qualquer nota, três vezes.", 7, 3), "I");

        // The gate closes the module: a I–vi–IV–V vamp of triads on the grid,
        // built from the chord construction studied here (REQ-009, REQ-015).
        auto& gate = m.exercises.emplace_back (exercise (
            "GATE-4", juce::String::fromUTF8 ("Desafio de gate — vamp C–Am–F–G"),
            juce::String::fromUTF8 ("Tocar C – Am – F – G a 72 BPM, na grade do metrônomo."),
            juce::String::fromUTF8 ("Acordes reconhecidos e alinhados à grade (≥ 0,78).")));
        gate.isGate = true;
        gate.lessonId = "I";
        gate.chordProgression = {
            { 0, 4, 7 },    // C
            { 9, 0, 4 },    // Am
            { 5, 9, 0 },    // F
            { 7, 11, 2 },   // G
        };

        m.gateChallenge = juce::String::fromUTF8 (
            "Tocar C – Am – F – G (quatro acordes; o modelo de improvisação do "
            "nível 2 é o 'vamp de 2 acordes') a 72 BPM com ≥90% de acerto de "
            "acordes e on_grid_ratio ≥ 0,78. Os acordes são tríades construídas "
            "pelos intervalos estudados no módulo.");

        // Pattern and link the module must cite (REQ-007, REQ-010).
        m.practice.patternId = "PTN-A-TRIAD";
        m.practice.patternUse = juce::String::fromUTF8 (
            "Arpejos de tríades em três cordas (varredura e retorno): o aluno ouve "
            "as três notas do acorde em sequência, ligando a forma à construção. "
            "Complemento: PTN-A-DROP2 (arpejos de sétima em Drop 2) para as tétrades.");
        m.practice.guitarists = { "Eric Johnson", "John Petrucci", "Andy Timmons" };

        // Curated apostilas (REQ-006, CM-012); see docs/MUSIC.md §1.1.
        m.sources = {
            "pdf-caged-e-derivaoes-de-acordes-marcelo-mello-apostila-de-violao-e-guitarra-vol1",
            "pdf-desvendando-os-segredos-da-guitarra-fusion",
            "pdf-teoria-elementar-da-musica-ricordi-osvaldo-lacerda",
            "pdf-p-classtruncatedtext-module-lineclamped-85ulhh-style-max-lines5bohumil-med-teoria-da-musica-5-edicao-p",
            "pdf-mozart-mello-livroestudosdeguitarra4em1",
        };

        return m;
    }


    // Module 5 — Etapa 5: campo harmônico maior e funções harmônicas. The student
    // builds the harmonic field of a key and identifies the function of each
    // chord (tonic, subdominant, dominant). Part of the exercises is played on
    // the instrument: the app recognises the notes and checks the chord, the
    // scale or the progression (Exercise::targets / chordPitchClasses /
    // chordProgression). Every topic has >=5 pages (content::minTopicChars),
    // images, tables, audio examples and scores with their audio.
    CourseModule makeModule5()
    {
        CourseModule m;
        m.number = 5;
        m.title = juce::String::fromUTF8 ("Campo harmônico maior e funções harmônicas");
        m.objective = juce::String::fromUTF8 (
            "Entender como os acordes se relacionam dentro de uma tonalidade: "
            "construir o campo harmônico maior e identificar a função de cada acorde.");
        m.level = 3;          // MUSIC.md: módulos 5–7 = nível 3 (II–V–I)
        m.targetBpm = 76;     // MUSIC.md, módulo 5
        m.onGridTarget = 0.79f;
        m.implemented = true;

        m.lessons = {
            detail (block ("A", juce::String::fromUTF8 ("Escala maior"), {
                "A escala maior segue o padrão T – T – S – T – T – T – S.",
                "Os semitons ficam entre os graus 3–4 e 7–8.",
                "Cada grau tem um número romano; é a matéria-prima da harmonia."
            }), content::topic5A()),
            detail (block ("B", juce::String::fromUTF8 ("Campo harmônico maior e graus da escala"), {
                "Campo harmônico = sete acordes que nascem da escala maior.",
                "A qualidade segue o padrão I – ii – iii – IV – V – vi – vii°.",
                "Em Dó maior: C – Dm – Em – F – G – Am – Bdim."
            }), content::topic5B()),
            detail (block ("C", juce::String::fromUTF8 ("Função tônica"), {
                "Função tônica é o repouso da tonalidade.",
                "Exercida pelo grau I e pelos substitutos iii e vi.",
                "Soa estável e conclusiva; é o ponto de chegada da frase."
            }), content::topic5C()),
            detail (block ("D", juce::String::fromUTF8 ("Função subdominante"), {
                "Função subdominante é o afastamento da tônica.",
                "Exercida pelo grau IV e pelo substituto ii.",
                "Prepara o dominante, sem a tensão forte dele."
            }), content::topic5D()),
            detail (block ("E", juce::String::fromUTF8 ("Função dominante"), {
                "Função dominante é a tensão da tonalidade.",
                "Exercida pelo grau V (e V7) e pelo substituto vii°.",
                "Pede resolução na tônica; V → I é a cadência mais forte."
            }), content::topic5E()),
            detail (block ("F", juce::String::fromUTF8 ("Acordes relativos"), {
                "Relativos: par maior/menor com a mesma armadura de clave.",
                "O relativo menor está três semitons abaixo do maior.",
                "No campo: I–vi, IV–ii e V–iii; trocar a cor sem mudar a função."
            }), content::topic5F()),
            detail (block ("G", juce::String::fromUTF8 ("Armaduras de clave e tonalidades"), {
                "Armadura de clave é o conjunto de acidentes que define a tonalidade.",
                "Sustenidos: Fá–Dó–Sol–Ré–Lá–Mi–Si; bemóis, a ordem inversa.",
                "O ciclo das quintas organiza todas as tonalidades."
            }), content::topic5G()),
            detail (block ("H", juce::String::fromUTF8 ("Cadências e progressões harmônicas"), {
                "Cadência é a pontuação da frase musical.",
                "Autêntica (V → I), plagal (IV → I), meia cadência (I → V), de engano (V → vi).",
                "As progressões comuns combinam as três funções."
            }), content::topic5H()),
            detail (block ("I", juce::String::fromUTF8 ("Modos gerados pela escala maior"), {
                "Modo é a escala maior começando em um grau diferente.",
                "Jônio, dórico, frígio, lídio, mixolídio, eólio e lócrio.",
                "As notas são as mesmas; muda o centro e o intervalo característico."
            }), content::topic5I()),
            detail (block ("J", juce::String::fromUTF8 ("Harmonização da escala maior"), {
                "Harmonizar é construir um acorde sobre cada grau da escala.",
                "O empilhamento 1–3–5 produz as tríades do campo.",
                "A harmonização é a base do acompanhamento e da transposição."
            }), content::topic5J()),
        };

        // Exercises: three per topic, mixing verifiable quizzes with playable
        // exercises the app checks by recognising the notes. Ids follow
        // EX-5.<topico>.<n>, numbered per topic, as modules 1 and 2.
        auto add = [&m] (Exercise e, const char* topic)
        {
            e.lessonId = topic;
            m.exercises.push_back (std::move (e));
            return (int) m.exercises.size() - 1;
        };

        // Plays a chord whose pitch classes the evaluator checks (the student may
        // use any shape/position on the neck). Identification, not tempo: no grid.
        auto chordExercise = [&add] (const char* id, const char* title, const char* goal,
                                     const char* chordName, std::vector<int> pitchClasses,
                                     const char* topic)
        {
            auto e = exercise (id, juce::String::fromUTF8 (title), juce::String::fromUTF8 (goal),
                               juce::String::fromUTF8 ("O app reconhece as notas tocadas e confere se formam ")
                                   + juce::String::fromUTF8 (chordName)
                                   + juce::String::fromUTF8 (", em qualquer posição do braço."));
            e.chordPitchClasses = std::move (pitchClasses);
            e.usesGrid = false;
            add (std::move (e), topic);
        };

        // Plays an ordered set of notes (a scale or a mode); any position works.
        auto noteExercise = [&add] (const char* id, const char* title, const char* goal,
                                    std::initializer_list<const char*> pitchNames, const char* topic)
        {
            auto e = exercise (id, juce::String::fromUTF8 (title), juce::String::fromUTF8 (goal),
                               juce::String::fromUTF8 (
                                   "O app reconhece as notas tocadas e confere se a sequência está correta."));
            e.targets = notes (pitchNames);
            e.usesGrid = false;
            add (std::move (e), topic);
        };

        // --- Topic A — escala maior ------------------------------------------
        add (exercise ("EX-5.A.1", juce::String::fromUTF8 ("Questionário: a escala maior"),
                       juce::String::fromUTF8 ("Responder ao questionário sobre a escala maior."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "A");
        m.exercises.back().quiz = {
            question ("Qual é o padrão de tons e semitons da escala maior?",
                      { "T – T – S – T – T – T – S",
                        "T – S – T – T – S – T – T",
                        "S – T – T – T – S – T – T",
                        "T – T – T – S – T – T – S" }, 0),
            question ("Em Dó maior, os semitons ficam entre os graus:",
                      { "4–5 e 8–9", "3–4 e 7–8", "1–2 e 5–6", "2–3 e 6–7" }, 1),
            question ("Quantas notas tem a escala maior (dentro da oitava)?",
                      { "oito", "doze", "sete", "cinco" }, 2),
            question ("A tônica da escala é o grau:",
                      { "3", "5", "7", "1" }, 3),
            question ("Mudar a tonalidade de uma escala maior:",
                      { "mantém o padrão e troca a nota de partida",
                        "muda o padrão de tons e semitons",
                        "elimina os semitons",
                        "acrescenta uma oitava" }, 0),
        };
        noteExercise ("EX-5.A.2", "Tocar a escala de Dó maior",
                      "Tocar a escala de Dó maior (Dó a Dó) subindo, em qualquer posição.",
                      { "C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5" }, "A");
        add (exercise ("EX-5.A.3", juce::String::fromUTF8 ("Questionário: graus da escala"),
                       juce::String::fromUTF8 ("Responder ao questionário sobre os graus."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "A");
        m.exercises.back().quiz = {
            question ("O grau 3 da escala de Dó maior é:",
                      { "Lá", "Mi", "Fá", "Sol" }, 1),
            question ("O grau 5 da escala de Dó maior é:",
                      { "Lá", "Si", "Sol", "Fá" }, 2),
            question ("Em algarismo romano, um acorde menor se escreve:",
                      { "com letra maiúscula (II)", "com um círculo (ii°)",
                        "com um sustenido", "com letra minúscula (ii)" }, 3),
        };

        // --- Topic B — campo harmônico maior ---------------------------------
        add (exercise ("EX-5.B.1", juce::String::fromUTF8 ("Questionário: campo harmônico"),
                       juce::String::fromUTF8 ("Responder ao questionário do campo harmônico."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "B");
        m.exercises.back().quiz = {
            question ("Qual é o padrão de qualidades do campo harmônico maior?",
                      { "I – ii – iii – IV – V – vi – vii°",
                        "I – ii – iii – IV – V – VI – vii°",
                        "i – II – III – iv – V – vi – VII",
                        "I – III – V – vii" }, 0),
            question ("O campo harmônico de Dó maior é:",
                      { "C – Dm – Em – F – G – Am – B",
                        "C – Dm – Em – F – G – Am – Bdim",
                        "C – Dm – Em – F – Gm – Am – Bdim",
                        "C – D – E – F – G – A – B" }, 1),
            question ("Os acordes maiores do campo maior estão nos graus:",
                      { "I, ii e iii", "V, vi e vii", "I, IV e V", "ii, iii e vi" }, 2),
            question ("O acorde do grau vii do campo maior é:",
                      { "maior", "menor", "aumentado", "diminuto" }, 3),
            question ("O campo harmônico é construído:",
                      { "empilhando as notas da própria escala sobre cada grau",
                        "usando notas de fora da escala",
                        "somando acordes aleatórios",
                        "tomando só os acordes maiores" }, 0),
        };
        chordExercise ("EX-5.B.2", "Tocar o acorde de tônica (I)",
                       "Tocar a tríade de C (grau I de Dó maior) em qualquer posição.",
                       "a tríade de Dó maior (I)", { 0, 4, 7 }, "B");
        chordExercise ("EX-5.B.3", "Tocar o acorde de subdominante (IV)",
                       "Tocar a tríade de F (grau IV de Dó maior) em qualquer posição.",
                       "a tríade de Fá maior (IV)", { 5, 9, 0 }, "B");

        // --- Topic C — função tônica -----------------------------------------
        add (exercise ("EX-5.C.1", juce::String::fromUTF8 ("Questionário: função tônica"),
                       juce::String::fromUTF8 ("Responder ao questionário da função tônica."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "C");
        m.exercises.back().quiz = {
            question ("A função tônica é a função de:",
                      { "modulação", "repouso", "tensão", "afastamento" }, 1),
            question ("A tônica de Dó maior é exercida pelo acorde de:",
                      { "F (grau IV)", "Am (grau vi)", "C (grau I)", "G (grau V)" }, 2),
            question ("Além do grau I, também exercem função tônica:",
                      { "ii e IV", "V e vii°", "apenas o I", "iii e vi" }, 3),
            question ("A função tônica soa:",
                      { "estável e conclusiva", "tensa e instável",
                        "suspensa e pedindo continuação", "sempre menor" }, 0),
        };
        chordExercise ("EX-5.C.2", "Tocar a tônica e ouvir o repouso",
                       "Tocar a tríade de C (tônica) e perceber a sensação de repouso.",
                       "a tríade de Dó maior (tônica)", { 0, 4, 7 }, "C");
        add (exercise ("EX-5.C.3", juce::String::fromUTF8 ("Questionário: substitutos da tônica"),
                       juce::String::fromUTF8 ("Responder ao questionário dos substitutos."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "C");
        m.exercises.back().quiz = {
            question ("O relativo menor do acorde de C é:",
                      { "G", "Am", "Em", "Dm" }, 1),
            question ("Trocar C por Am numa progressão:",
                      { "cria tensão de dominante",
                        "sai do campo harmônico",
                        "mantém a função de repouso com outra cor",
                        "muda a tonalidade" }, 2),
            question ("Os substitutos da tônica compartilham com o I:",
                      { "nenhuma nota", "todas as notas", "só a fundamental", "duas notas" }, 3),
        };

        // --- Topic D — função subdominante -----------------------------------
        add (exercise ("EX-5.D.1", juce::String::fromUTF8 ("Questionário: função subdominante"),
                       juce::String::fromUTF8 ("Responder ao questionário da subdominante."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "D");
        m.exercises.back().quiz = {
            question ("A função subdominante é a função de:",
                      { "afastamento", "repouso", "tensão máxima", "modulação" }, 0),
            question ("A subdominante de Dó maior é exercida pelo acorde de:",
                      { "Em (grau iii)", "F (grau IV)", "C (grau I)", "G (grau V)" }, 1),
            question ("O principal substituto da subdominante é o acorde de:",
                      { "vii°", "iii", "ii", "vi" }, 2),
            question ("A tarefa principal da subdominante é:",
                      { "concluir a música",
                        "substituir a tônica",
                        "criar a tensão máxima",
                        "preparar o dominante" }, 3),
        };
        chordExercise ("EX-5.D.2", "Tocar a subdominante (IV)",
                       "Tocar a tríade de F (grau IV de Dó maior) em qualquer posição.",
                       "a tríade de Fá maior (IV)", { 5, 9, 0 }, "D");
        chordExercise ("EX-5.D.3", "Tocar o substituto da subdominante (ii)",
                       "Tocar a tríade de Dm (grau ii de Dó maior) em qualquer posição.",
                       "a tríade de Ré menor (ii)", { 2, 5, 9 }, "D");

        // --- Topic E — função dominante --------------------------------------
        add (exercise ("EX-5.E.1", juce::String::fromUTF8 ("Questionário: função dominante"),
                       juce::String::fromUTF8 ("Responder ao questionário da dominante."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "E");
        m.exercises.back().quiz = {
            question ("A função dominante é a função de:",
                      { "tensão", "repouso", "afastamento suave", "modulação" }, 0),
            question ("A dominante de Dó maior é exercida pelo acorde de:",
                      { "Am (grau vi)", "G (grau V)", "C (grau I)", "F (grau IV)" }, 1),
            question ("A força do dominante vem principalmente do:",
                      { "intervalo de oitava", "baixo pedal", "trítono", "uníssono" }, 2),
            question ("O dominante resolve, naturalmente, na:",
                      { "subdominante", "relativa menor", "mediante", "tônica" }, 3),
            question ("O substituto do dominante no campo é o acorde de:",
                      { "vii°", "ii", "vi", "IV" }, 0),
        };
        chordExercise ("EX-5.E.2", "Tocar a dominante (V)",
                       "Tocar a tríade de G (grau V de Dó maior) em qualquer posição.",
                       "a tríade de Sol maior (V)", { 7, 11, 2 }, "E");
        chordExercise ("EX-5.E.3", "Tocar o substituto do dominante (vii°)",
                       "Tocar a tríade de Bdim (grau vii° de Dó maior) em qualquer posição.",
                       "a tríade de Si diminuto (vii°)", { 11, 2, 5 }, "E");

        // --- Topic F — acordes relativos -------------------------------------
        add (exercise ("EX-5.F.1", juce::String::fromUTF8 ("Questionário: acordes relativos"),
                       juce::String::fromUTF8 ("Responder ao questionário dos relativos."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "F");
        m.exercises.back().quiz = {
            question ("O relativo menor de um acorde maior está:",
                      { "sete semitons acima", "três semitons abaixo",
                        "três semitons acima", "cinco semitons abaixo" }, 1),
            question ("O relativo menor de C é:",
                      { "Em", "Gm", "Am", "Dm" }, 2),
            question ("Dois acordes relativos compartilham:",
                      { "a mesma fundamental", "o mesmo baixo",
                        "a mesma terça", "a mesma armadura de clave" }, 3),
            question ("Os pares de relativos no campo de Dó são:",
                      { "I–vi, IV–ii e V–iii", "I–ii, IV–V e vi–vii",
                        "I–IV, V–vi e ii–iii", "I–iii, IV–vi e V–vii" }, 0),
        };
        chordExercise ("EX-5.F.2", "Tocar o relativo menor (vi)",
                       "Tocar a tríade de Am (grau vi de Dó maior), relativo menor de C.",
                       "a tríade de Lá menor (vi)", { 9, 0, 4 }, "F");
        add (exercise ("EX-5.F.3", juce::String::fromUTF8 ("Questionário: usar os relativos"),
                       juce::String::fromUTF8 ("Responder ao questionário do uso dos relativos."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "F");
        m.exercises.back().quiz = {
            question ("Trocar um acorde pelo seu relativo serve para:",
                      { "sair da música",
                        "mudar a cor sem mudar a função",
                        "mudar a tonalidade",
                        "criar um dominante secundário" }, 1),
            question ("Substituir o I pelo vi deixa a progressão:",
                      { "mais rápida", "sem tônica", "mais melancólica", "mais tensa" }, 2),
            question ("Uma música com armadura de Dó maior pode estar em:",
                      { "Dó maior ou Sol maior", "Lá menor ou Mi menor",
                        "Fá maior ou Ré menor", "Dó maior ou Lá menor" }, 3),
        };

        // --- Topic G — armaduras de clave ------------------------------------
        add (exercise ("EX-5.G.1", juce::String::fromUTF8 ("Questionário: armaduras de clave"),
                       juce::String::fromUTF8 ("Responder ao questionário das armaduras."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "G");
        m.exercises.back().quiz = {
            question ("A ordem dos sustenidos na armadura é:",
                      { "Fá–Dó–Sol–Ré–Lá–Mi–Si", "Si–Mi–Lá–Ré–Sol–Dó–Fá",
                        "Dó–Ré–Mi–Fá–Sol–Lá–Si", "Lá–Si–Dó–Ré–Mi–Fá–Sol" }, 0),
            question ("Uma armadura com um sustenido indica a tonalidade de:",
                      { "Lá maior", "Sol maior", "Fá maior", "Ré maior" }, 1),
            question ("Uma armadura com um bemol indica a tonalidade de:",
                      { "Dó maior", "Sib maior", "Fá maior", "Sol maior" }, 2),
            question ("O ciclo das quintas subindo acrescenta:",
                      { "um bemol por passo", "nenhum acidente",
                        "dois acidentes por passo", "um sustenido por passo" }, 3),
            question ("Tonalidades vizinhas no ciclo das quintas diferem por:",
                      { "um acidente", "três acidentes", "nenhum acidente", "meio tom" }, 0),
        };
        chordExercise ("EX-5.G.2", "Tocar a tônica de Sol maior",
                       "Tocar a tríade de G (tônica de Sol maior, armadura de 1 sustenido).",
                       "a tríade de Sol maior (I de Sol)", { 7, 11, 2 }, "G");
        chordExercise ("EX-5.G.3", "Tocar a tônica de Fá maior",
                       "Tocar a tríade de F (tônica de Fá maior, armadura de 1 bemol).",
                       "a tríade de Fá maior (I de Fá)", { 5, 9, 0 }, "G");

        // --- Topic H — cadências e progressões -------------------------------
        add (exercise ("EX-5.H.1", juce::String::fromUTF8 ("Questionário: cadências"),
                       juce::String::fromUTF8 ("Responder ao questionário das cadências."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "H");
        m.exercises.back().quiz = {
            question ("A cadência autêntica é:",
                      { "V → vi", "V → I", "IV → I", "I → V" }, 1),
            question ("A cadência plagal é:",
                      { "I → V", "ii → V", "IV → I", "V → I" }, 2),
            question ("A meia cadência termina:",
                      { "na tônica", "no relativo menor",
                        "na subdominante", "no dominante, sem resolver" }, 3),
            question ("A cadência de engano é:",
                      { "V → vi", "V → I", "IV → I", "I → V" }, 0),
            question ("A cadência mais conclusiva é a:",
                      { "de engano", "autêntica", "plagal", "meia cadência" }, 1),
        };
        {
            auto e = exercise ("EX-5.H.2", juce::String::fromUTF8 ("Tocar a cadência IV – V – I"),
                               juce::String::fromUTF8 ("Tocar a progressão IV – V – I (F – G – C) em qualquer posição."),
                               juce::String::fromUTF8 (
                                   "O app reconhece os acordes, na ordem, e confere a progressão."));
            e.chordProgression = {
                { 5, 9, 0 },    // F (IV)
                { 7, 11, 2 },   // G (V)
                { 0, 4, 7 },    // C (I)
            };
            e.usesGrid = false;
            add (std::move (e), "H");
        }
        add (exercise ("EX-5.H.3", juce::String::fromUTF8 ("Questionário: progressões"),
                       juce::String::fromUTF8 ("Responder ao questionário das progressões."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "H");
        m.exercises.back().quiz = {
            question ("A progressão ii – V – I é chamada de:",
                      { "meia cadência", "cadência de engano",
                        "cadência preparada (jazz)", "cadência plagal" }, 2),
            question ("A progressão pop mais usada é:",
                      { "ii – V – I", "I – IV – V – I", "V – vi – IV – I", "I – V – vi – IV" }, 3),
            question ("Reconhecer as cadências permite:",
                      { "prever o próximo acorde e acompanhar de ouvido",
                        "afinar o instrumento",
                        "aumentar o volume",
                        "mudar a afinação das cordas" }, 0),
        };

        // --- Topic I — modos --------------------------------------------------
        add (exercise ("EX-5.I.1", juce::String::fromUTF8 ("Questionário: modos"),
                       juce::String::fromUTF8 ("Responder ao questionário dos modos."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "I");
        m.exercises.back().quiz = {
            question ("Um modo é obtido:",
                      { "tocando só os acordes maiores",
                        "começando a escala maior em um grau diferente",
                        "trocando as notas da escala",
                        "subindo meio tom a escala" }, 1),
            question ("Os modos da escala maior usam:",
                      { "apenas cinco notas",
                        "só as notas do acorde",
                        "as mesmas notas da escala maior",
                        "notas de várias tonalidades" }, 2),
            question ("O modo que começa no grau II é o:",
                      { "frígio", "lídio", "mixolídio", "dórico" }, 3),
            question ("O modo que começa no grau V é o:",
                      { "mixolídio", "jônio", "eólio", "lócrio" }, 0),
            question ("O intervalo característico do lídio é a:",
                      { "segunda menor", "quarta aumentada", "sexta menor", "sétima menor" }, 1),
        };
        noteExercise ("EX-5.I.2", "Tocar o modo dórico",
                      "Tocar o modo dórico (notas de Dó maior a partir de Ré), subindo.",
                      { "D4", "E4", "F4", "G4", "A4", "B4", "C5", "D5" }, "I");
        add (exercise ("EX-5.I.3", juce::String::fromUTF8 ("Questionário: modo por acorde"),
                       juce::String::fromUTF8 ("Responder ao questionário da aplicação dos modos."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "I");
        m.exercises.back().quiz = {
            question ("Sobre o acorde de ii (Dm) em Dó maior, o modo natural é o:",
                      { "lídio", "lócrio", "dórico", "frígio" }, 2),
            question ("Sobre o acorde de V (G) em Dó maior, o modo natural é o:",
                      { "jônio", "eólio", "dórico", "mixolídio" }, 3),
            question ("O jônio é o mesmo que:",
                      { "a escala maior", "a escala menor natural",
                        "a pentatônica", "o blues" }, 0),
        };

        // --- Topic J — harmonização da escala maior --------------------------
        add (exercise ("EX-5.J.1", juce::String::fromUTF8 ("Questionário: harmonização"),
                       juce::String::fromUTF8 ("Responder ao questionário da harmonização."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "J");
        m.exercises.back().quiz = {
            question ("Harmonizar a escala maior é:",
                      { "trocar a tonalidade",
                        "construir um acorde sobre cada grau",
                        "tocar a escala mais rápido",
                        "somar duas escalas" }, 1),
            question ("O empilhamento que forma uma tríade é:",
                      { "1 – 4 – 5", "1 – 2 – 5", "1 – 3 – 5", "1 – 2 – 3" }, 2),
            question ("Os acordes de I, IV e V do campo maior são:",
                      { "menores", "diminutos", "meio-diminutos", "maiores" }, 3),
            question ("Os acordes de ii, iii e vi do campo maior são:",
                      { "menores", "maiores", "aumentados", "diminutos" }, 0),
        };
        {
            auto e = exercise ("EX-5.J.2", juce::String::fromUTF8 ("Tocar o campo harmônico de Dó"),
                               juce::String::fromUTF8 ("Tocar I – IV – V – I (C – F – G – C) em qualquer posição."),
                               juce::String::fromUTF8 (
                                   "O app reconhece os acordes, na ordem, e confere a progressão do campo."));
            e.chordProgression = {
                { 0, 4, 7 },    // C (I)
                { 5, 9, 0 },    // F (IV)
                { 7, 11, 2 },   // G (V)
                { 0, 4, 7 },    // C (I)
            };
            e.usesGrid = false;
            add (std::move (e), "J");
        }
        add (exercise ("EX-5.J.3", juce::String::fromUTF8 ("Questionário: tríades e tétrades"),
                       juce::String::fromUTF8 ("Responder ao questionário das tríades e tétrades."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "J");
        m.exercises.back().quiz = {
            question ("As tétrades do campo de Dó maior são:",
                      { "Cm – Dm – Em – Fm – Gm – Am – Bdim",
                        "C7M – Dm7 – Em7 – F7M – G7 – Am7 – Bm7(b5)",
                        "C7 – Dm7 – Em7 – F7 – G7 – Am7 – Bdim",
                        "C7M – D7 – E7 – F7M – G7 – A7 – B7" }, 1),
            question ("A harmonização serve de base para:",
                      { "regular o metrônomo",
                        "escolher o captador",
                        "acompanhar, compor e transpor",
                        "afinar o instrumento" }, 2),
            question ("Transpor uma progressão mantém:",
                      { "os nomes dos acordes",
                        "a mesma tônica",
                        "a mesma armadura",
                        "as distâncias entre os graus" }, 3),
        };

        // The gate closes the module: play the I–IV–V–I progression of the field
        // on the metronome grid (REQ-009, REQ-015), built from the material of
        // the module (the harmonic field of the key).
        auto& gate = m.exercises.emplace_back (exercise (
            "GATE-5", juce::String::fromUTF8 ("Desafio de gate — campo harmônico C–F–G–C"),
            juce::String::fromUTF8 ("Tocar C – F – G – C a 76 BPM, na grade do metrônomo."),
            juce::String::fromUTF8 ("Acordes reconhecidos e alinhados à grade (≥ 0,79).")));
        gate.isGate = true;
        gate.lessonId = "J";
        gate.chordProgression = {
            { 0, 4, 7 },    // C (I)
            { 5, 9, 0 },    // F (IV)
            { 7, 11, 2 },   // G (V)
            { 0, 4, 7 },    // C (I)
        };

        m.gateChallenge = juce::String::fromUTF8 (
            "Tocar a progressão do campo harmônico maior C – F – G – C (I – IV – V – I) "
            "a 76 BPM com ≥90% de acerto de acordes e on_grid_ratio ≥ 0,79. A "
            "progressão percorre as três funções estudadas no módulo: tônica, "
            "subdominante e dominante.");

        // Pattern and link the module must cite (REQ-007, REQ-010).
        m.practice.patternId = "PTN-A-TRIAD";
        m.practice.patternUse = juce::String::fromUTF8 (
            "Arpejos de tríade: o padrão PTN-A-TRIAD varre as três notas do acorde "
            "(1–3–5) e faz o aluno ouvir, na mão, as notas que formam cada grau do "
            "campo harmônico. Complemento: PTN-M-3rds (terças) mostra como os "
            "acordes nascem do empilhamento de terças sobre a escala.");
        m.practice.guitarists = { "Wes Montgomery", "Joe Pass", "Kiko Loureiro" };

        // Curated apostilas (REQ-006, CM-012); see docs/MUSIC.md §2.1.
        m.sources = {
            "pdf-desvendando-os-segredos-da-guitarra-fusion",
            "pdf-teoria-elementar-da-musica-ricordi-osvaldo-lacerda",
            "pdf-p-classtruncatedtext-module-lineclamped-85ulhh-style-max-lines5bohumil-med-teoria-da-musica-5-edicao-p",
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
        m.exercises.back().targets = notes ({ "C4", "D4", "D#4", "F4", "G4", "A4", "A#4", "C5" });
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


    // A chord-montage exercise (module 8): the student plays a chord and the app
    // verifies the pitch classes it heard. Not grid-gated: the goal is the
    // harmony, not the tempo.
    Exercise chordExercise (const char* id, const char* title, const char* goal,
                            std::initializer_list<int> pitchClasses)
    {
        auto e = exercise (id, juce::String::fromUTF8 (title), juce::String::fromUTF8 (goal),
                           juce::String::fromUTF8 (
                               "O app reconhece as notas tocadas e confere se o acorde tem as notas certas."));
        e.chordPitchClasses.assign (pitchClasses.begin(), pitchClasses.end());
        e.usesGrid = false;
        return e;
    }

    // A chord-progression exercise (module 8): the student plays the progression
    // chord by chord; the app matches each chord in order. Grid-gated when the
    // caller keeps `usesGrid` (the gate closes the module on the metronome).
    Exercise progressionExercise (const char* id, const char* title, const char* goal,
                                  std::initializer_list<std::initializer_list<int>> chords)
    {
        auto e = exercise (id, juce::String::fromUTF8 (title), juce::String::fromUTF8 (goal),
                           juce::String::fromUTF8 (
                               "O app reconhece os acordes na ordem e confere se a progressão está correta."));
        for (const auto& chord : chords)
            e.chordProgression.push_back (std::vector<int> (chord.begin(), chord.end()));
        e.usesGrid = false;
        return e;
    }

    // Module 8 (Etapa 8 — dominantes, cadências e substituições harmônicas).
    // Ten topics (A..J); 3..5 exercises per topic, ids EX-8.<topico>.<n>; the gate
    // closes the module on the grid with a II-V-I maior (REQ-009).
    CourseModule makeModule8()
    {
        CourseModule m;
        m.number = 8;
        m.title = juce::String::fromUTF8 ("Dominantes, cadências e substituições harmônicas");
        m.objective = juce::String::fromUTF8 (
            "Compreender como criar tensão, resolução e movimentação harmônica: o "
            "dominante V7, os dominantes secundários e alterados, o SubV7, o SubIIm, "
            "os empréstimos modais e a progressão II-V-I maior e menor.");
        m.level = 4;          // MUSIC.md: módulos 8–10 = nível 4 (turnarounds)
        m.targetBpm = 88;     // MUSIC.md, módulo 8
        m.onGridTarget = 0.81f;
        m.implemented = true;

        m.lessons = {
            detail (block ("A", juce::String::fromUTF8 ("Dominante V7"), {
                "O quinto grau com sétima menor (0, 4, 7, 10); o trítono entre a terça e a sétima cria a tensão.",
                "A resolução V7 → I acontece por meio-tom (voice leading).",
                "No campo maior, o V7 é o único acorde de sétima dominante natural."
            }), content::topic8A()),
            detail (block ("B", juce::String::fromUTF8 ("Dominantes secundários"), {
                "Qualquer grau pode virar tônica temporária com o seu próprio V7 (V7/x).",
                "Constrói-se subindo uma quinta justa a partir do alvo.",
                "A nota estranha ao campo aponta o alvo; podem se encadear em quintas."
            }), content::topic8B()),
            detail (block ("C", juce::String::fromUTF8 ("Dominantes alterados e resoluções"), {
                "Alteram-se quinta e extensões (b5, #5, b9, #9, #11), nunca a terça nem a sétima.",
                "Cada alteração tem uma direção natural de resolução por meio-tom.",
                "O acorde alterado (alt) é o dominante de tensão máxima."
            }), content::topic8C()),
            detail (block ("D", juce::String::fromUTF8 ("SubV7"), {
                "O dominante substituto fica meio-tom acima do alvo e resolve no mesmo lugar.",
                "Compartilha o trítono com o V7; o baixo desce um semitom.",
                "No II-V-I: Dm7 → Db7 → CM7; pode se encadear cromaticamente."
            }), content::topic8D()),
            detail (block ("E", juce::String::fromUTF8 ("SubIIm"), {
                "O ii vira menor com quinta diminuta (Dm7b5): a cor do campo menor dentro do maior.",
                "Prepara o dominante com nona menor (b9).",
                "No II-V-I menor é o acorde natural; com o SubV7 dá a resolução mais suave."
            }), content::topic8E()),
            detail (block ("F", juce::String::fromUTF8 ("Empréstimos modais"), {
                "Pegar acordes do modo paralelo (Dó menor dentro do Dó maior).",
                "Principais: i, iv, bIII, bVI, bVII; o iv menor e o bVII são os mais usados.",
                "Empréstimo é passageiro; modulação é permanente."
            }), content::topic8F()),
            detail (block ("G", juce::String::fromUTF8 ("Dilatação do campo harmônico maior"), {
                "O campo de sete acordes se amplia com dominantes secundários, substituições e empréstimos.",
                "Cada acorde novo exerce uma das três funções básicas.",
                "O mapa dilatado é a base da reharmonização."
            }), content::topic8G()),
            detail (block ("H", juce::String::fromUTF8 ("Dilatação do campo harmônico menor"), {
                "O campo menor é a união das escalas natural, harmônica e melódica.",
                "A harmônica cria o V7 (dominante); a melódica acrescenta acordes de cor.",
                "A cadência fundamental é o II-V-I menor: Dm7b5 → G7 → Cm7."
            }), content::topic8H()),
            detail (block ("I", juce::String::fromUTF8 ("Progressão II-V-I maior e menor"), {
                "Reúne as três funções: subdominante (II), dominante (V) e tônica (I).",
                "Maior: Dm7 → G7 → CM7; menor: Dm7b5 → G7 → Cm7.",
                "O voice leading conduz as vozes por meio-tom; as notas-guia guiam a cadência."
            }), content::topic8I()),
            detail (block ("J", juce::String::fromUTF8 ("Identificação de situações que não são II-V-I"), {
                "Cadência deceptiva resolve no vi; backdoor usa ivm e bVII, sem o V.",
                "Vamp modal nunca resolve; meia cadência para no V.",
                "Pergunte sempre: qual é o alvo e como ele é alcançado?"
            }), content::topic8J()),
        };

        auto add = [&m] (Exercise e, const char* topic)
        {
            e.lessonId = topic;
            m.exercises.push_back (std::move (e));
            return (int) m.exercises.size() - 1;
        };

        // --- Topic A — dominante V7 ------------------------------------------
        add (exercise ("EX-8.A.1", juce::String::fromUTF8 ("Questionário: o dominante V7"),
                       juce::String::fromUTF8 ("Responder ao questionário de introdução ao dominante."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões do dominante.")), "A");
        m.exercises.back().quiz = {
            question ("Quais intervalos formam o acorde de sétima dominante (em semitons)?",
                      { "0, 4, 7, 11", "0, 3, 7, 10", "0, 4, 7, 10", "0, 4, 8, 11" }, 2),
            question ("Qual é o V7 de Dó maior?",
                      { "G7", "D7", "C7", "F7" }, 0),
            question ("O que cria a tensão do dominante?",
                      { "A quinta justa", "O trítono entre a terça e a sétima",
                        "A fundamental", "A repetição da tônica" }, 1),
            question ("Na resolução G7 → C, para onde vai o Fá (sétima)?",
                      { "Sobe para Sol", "Desce para Mi", "Permanece em Fá", "Vai para Lá" }, 1),
            question ("No campo maior, quantos acordes de sétima dominante existem naturalmente?",
                      { "Um (o V7)", "Dois", "Três", "Sete" }, 0),
        };
        add (chordExercise ("EX-8.A.2", "Montar o dominante G7",
                            "Tocar um acorde de sétima dominante (fundamental, terça maior, quinta justa e sétima menor).",
                            { 7, 11, 2, 5 }), "A");
        add (exercise ("EX-8.A.3", juce::String::fromUTF8 ("Tocar o arpejo do dominante"),
                       juce::String::fromUTF8 ("Tocar o arpejo Sol–Si–Ré–Fá do G7."),
                       juce::String::fromUTF8 ("O app reconhece as notas na ordem e confere o arpejo do dominante.")), "A");
        m.exercises.back().targets = notes ({ "G3", "B3", "D4", "F4" });
        m.exercises.back().usesGrid = false;
        add (intervalExercise ("EX-8.A.4", "Tocar o trítono do dominante",
                               "Tocar o trítono (6 semitons) que dá a tensão ao dominante, três vezes.", 6, 3), "A");

        // --- Topic B — dominantes secundários --------------------------------
        add (exercise ("EX-8.B.1", juce::String::fromUTF8 ("Questionário: dominantes secundários"),
                       juce::String::fromUTF8 ("Responder ao questionário dos dominantes secundários."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "B");
        m.exercises.back().quiz = {
            question ("O que significa V7/ii?",
                      { "O dominante do segundo grau", "O segundo grau do dominante",
                        "Um dominante com nona", "O dominante da tônica" }, 0),
            question ("Como se constrói o dominante de um alvo?",
                      { "Subindo uma quinta justa a partir do alvo",
                        "Descendo uma quarta a partir do alvo",
                        "Subindo meio-tom a partir do alvo",
                        "Usando as notas do campo" }, 0),
            question ("Em Dó maior, qual é o V7/vi (dominante de Lá menor)?",
                      { "A7", "E7", "D7", "B7" }, 1),
            question ("O que aponta o alvo de um dominante secundário?",
                      { "A nota estranha ao campo harmônico",
                        "A fundamental do I",
                        "O volume do acorde",
                        "A corda usada" }, 0),
            question ("Uma cadeia de dominantes desce em:",
                      { "quartas", "quintas", "semitons", "tons" }, 1),
        };
        add (chordExercise ("EX-8.B.2", "Montar o V7/ii (A7)",
                            "Tocar o dominante de Dm em Dó maior.",
                            { 9, 1, 4, 7 }), "B");
        add (chordExercise ("EX-8.B.3", "Montar o V7/V (D7)",
                            "Tocar o dominante de Sol em Dó maior.",
                            { 2, 6, 9, 0 }), "B");
        add (exercise ("EX-8.B.4", juce::String::fromUTF8 ("Dominantes em outras tonalidades"),
                       juce::String::fromUTF8 ("Dizer o V7/ii e o V7/V em outras tonalidades."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário de transposição.")), "B");
        m.exercises.back().quiz = {
            question ("Em Sol maior, qual é o V7/V?",
                      { "A7", "E7", "B7", "D7" }, 0),
            question ("Em Fá maior, qual é o V7/ii?",
                      { "G7", "D7", "C7", "A7" }, 1),
            question ("O V7/IV de Dó maior é:",
                      { "C7", "F7", "G7", "D7" }, 0),
        };

        // --- Topic C — dominantes alterados ----------------------------------
        add (exercise ("EX-8.C.1", juce::String::fromUTF8 ("Questionário: dominantes alterados"),
                       juce::String::fromUTF8 ("Responder ao questionário dos dominantes alterados."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "C");
        m.exercises.back().quiz = {
            question ("Quais notas de um dominante NUNCA se alteram?",
                      { "A quinta e a nona", "A fundamental, a terça e a sétima",
                        "A nona e a décima primeira", "Apenas a fundamental" }, 1),
            question ("G7b9 tem qual nota acrescentada?",
                      { "Lá bemol", "Lá natural", "Sol sustenido", "Fá sustenido" }, 0),
            question ("O acorde G7#9 é conhecido como:",
                      { "acorde hendrix", "acorde meio-diminuto",
                        "acorde suspenso", "power chord" }, 0),
            question ("Na resolução, a nona menor (b9) do dominante:",
                      { "desce meio-tom", "sobe meio-tom",
                        "permanece", "salta uma quinta" }, 0),
            question ("O que o acorde alterado (alt) representa?",
                      { "A tensão máxima antes da resolução",
                        "Um acorde de repouso",
                        "Um acorde menor",
                        "Um acorde sem terça" }, 0),
        };
        add (chordExercise ("EX-8.C.2", "Montar o dominante G7b9",
                            "Tocar um dominante com nona menor.",
                            { 7, 11, 2, 5, 8 }), "C");
        add (chordExercise ("EX-8.C.3", "Montar o dominante G7#9",
                            "Tocar o 'acorde hendrix' (terça maior e nona aumentada).",
                            { 7, 11, 2, 5, 10 }), "C");
        add (exercise ("EX-8.C.4", juce::String::fromUTF8 ("Direção da resolução"),
                       juce::String::fromUTF8 ("Dizer para onde cada alteração resolve."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário de resolução.")), "C");
        m.exercises.back().quiz = {
            question ("A quinta aumentada (#5) do dominante resolve:",
                      { "subindo meio-tom", "descendo meio-tom",
                        "permanecendo", "salta uma quarta" }, 0),
            question ("A décima primeira aumentada (#11) resolve:",
                      { "descendo meio-tom", "subindo meio-tom",
                        "permanecendo", "salta uma oitava" }, 0),
            question ("A resolução deceptiva leva o dominante a:",
                      { "outro grau, não a tônica", "sempre à tônica",
                        "um acorde diminuto", "um silêncio" }, 0),
        };

        // --- Topic D — SubV7 -------------------------------------------------
        add (exercise ("EX-8.D.1", juce::String::fromUTF8 ("Questionário: SubV7"),
                       juce::String::fromUTF8 ("Responder ao questionário do dominante substituto."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões do SubV7.")), "D");
        m.exercises.back().quiz = {
            question ("O SubV7 de Dó é:",
                      { "Db7", "D7", "C7", "Gb7" }, 0),
            question ("Por que o SubV7 resolve no mesmo lugar que o V7?",
                      { "Porque compartilha o mesmo trítono",
                        "Porque tem a mesma fundamental",
                        "Porque é o mesmo acorde",
                        "Porque tem a mesma quinta" }, 0),
            question ("O baixo do SubV7, ao resolver, faz:",
                      { "um salto de quarta", "um movimento de semitom descendente",
                        "um salto de oitava", "um movimento de tom" }, 1),
            question ("No II-V-I, o SubV7 substitui:",
                      { "o ii", "o I", "o V7", "a melodia" }, 2),
            question ("O SubV7 fica, em relação ao alvo:",
                      { "meio-tom acima", "uma quinta acima",
                        "uma terça acima", "uma oitava acima" }, 0),
        };
        add (chordExercise ("EX-8.D.2", "Montar o SubV7 (Db7)",
                            "Tocar o dominante substituto de Dó.",
                            { 1, 5, 8, 11 }), "D");
        add (progressionExercise ("EX-8.D.3", "II-SubV7-I",
                                  "Tocar Dm7 → Db7 → CM7, a cadência com o SubV7.",
                                  { { 2, 5, 9, 0 }, { 1, 5, 8, 11 }, { 0, 4, 7, 11 } }), "D");
        add (exercise ("EX-8.D.4", juce::String::fromUTF8 ("SubV7 em outras tonalidades"),
                       juce::String::fromUTF8 ("Dizer o SubV7 de outros alvos."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário de transposição.")), "D");
        m.exercises.back().quiz = {
            question ("O SubV7 de Sol é:",
                      { "Ab7", "A7", "Gb7", "G7" }, 0),
            question ("O SubV7 de Fá é:",
                      { "Gb7", "G7", "F7", "C7" }, 0),
            question ("Uma cadeia de SubV7 desce em:",
                      { "quintas", "semitons", "tons", "oitavas" }, 1),
        };

        // --- Topic E — SubIIm ------------------------------------------------
        add (exercise ("EX-8.E.1", juce::String::fromUTF8 ("Questionário: SubIIm"),
                       juce::String::fromUTF8 ("Responder ao questionário do segundo grau menor."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões do SubIIm.")), "E");
        m.exercises.back().quiz = {
            question ("O SubIIm em Dó maior é:",
                      { "Dm7b5", "Dm7", "D7", "Dm6" }, 0),
            question ("O que distingue o SubIIm do ii do campo maior?",
                      { "A quinta diminuta", "A terça", "A sétima", "A fundamental" }, 0),
            question ("O SubIIm costuma preparar qual dominante?",
                      { "Com nona menor (b9)", "Com quinta aumentada",
                        "Sem sétima", "Com nona maior" }, 0),
            question ("No II-V-I menor, o SubIIm é:",
                      { "o acorde natural", "uma substituição rara",
                        "um erro", "o próprio I" }, 0),
            question ("Qual nota do Dm7b5 reaparece como b9 do G7?",
                      { "Lá bemol", "Lá natural", "Fá", "Dó" }, 0),
        };
        add (chordExercise ("EX-8.E.2", "Montar o SubIIm (Dm7b5)",
                            "Tocar o ii menor com quinta diminuta de Dó maior.",
                            { 2, 5, 8, 0 }), "E");
        add (chordExercise ("EX-8.E.3", "Montar o iv menor (Fm7)",
                            "Tocar a subdominante menor de Dó maior.",
                            { 5, 8, 0, 3 }), "E");
        add (exercise ("EX-8.E.4", juce::String::fromUTF8 ("SubIIm em outras tonalidades"),
                       juce::String::fromUTF8 ("Dizer o SubIIm de outros tons."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário de transposição.")), "E");
        m.exercises.back().quiz = {
            question ("O SubIIm de Sol maior é:",
                      { "Am7b5", "Am7", "A7", "Ab7" }, 0),
            question ("O SubIIm de Fá maior é:",
                      { "Gm7b5", "Gm7", "G7", "Gm7M" }, 0),
            question ("SubIIm + SubV7 em Dó maior dá:",
                      { "Dm7b5 → Db7 → CM7", "Dm7 → G7 → CM7",
                        "Dm7b5 → G7 → CM7", "Dm7 → Db7 → CM7" }, 0),
        };

        // --- Topic F — empréstimos modais ------------------------------------
        add (exercise ("EX-8.F.1", juce::String::fromUTF8 ("Questionário: empréstimos modais"),
                       juce::String::fromUTF8 ("Responder ao questionário dos empréstimos modais."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "F");
        m.exercises.back().quiz = {
            question ("O que é empréstimo modal?",
                      { "Usar um acorde do modo paralelo",
                        "Mudar definitivamente de tom",
                        "Tocar mais rápido",
                        "Usar só os acordes do campo" }, 0),
            question ("Modos paralelos compartilham:",
                      { "a mesma tônica", "as mesmas notas",
                        "o mesmo acorde", "o mesmo baixo" }, 0),
            question ("O iv menor de Dó maior é:",
                      { "Fm7", "FM7", "Gm7", "F7" }, 0),
            question ("O bVII de Dó maior cria qual cadência?",
                      { "mixolídia", "frígia", "deceptiva", "plagal" }, 0),
            question ("Empréstimo modal é passageiro; modulação é:",
                      { "permanente", "também passageira",
                        "igual ao empréstimo", "uma substituição" }, 0),
        };
        add (chordExercise ("EX-8.F.2", "Montar o bVI (Ab7M)",
                            "Tocar o bVI emprestado do Dó menor.",
                            { 8, 0, 3, 7 }), "F");
        add (chordExercise ("EX-8.F.3", "Montar o bVII (Bb7)",
                            "Tocar o bVII que cria a cadência mixolídia.",
                            { 10, 2, 5, 8 }), "F");
        add (exercise ("EX-8.F.4", juce::String::fromUTF8 ("Empréstimos e escalas"),
                       juce::String::fromUTF8 ("Relacionar cada acorde emprestado à sua escala."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário de escalas.")), "F");
        m.exercises.back().quiz = {
            question ("Sobre o iv menor (Fm7), qual escala usar?",
                      { "dórica de Fá", "lídia de Fá", "mixolídia de Fá", "lócria de Fá" }, 0),
            question ("Sobre o bVI (Ab7M), qual escala usar?",
                      { "lídia de Lá bemol", "dórica de Lá bemol",
                        "mixolídia de Lá bemol", "eólio de Lá bemol" }, 0),
            question ("O bVII de Dó maior é:",
                      { "Bb7", "B7", "Bb7M", "Bdim7" }, 0),
        };

        // --- Topic G — dilatação do campo maior ------------------------------
        add (exercise ("EX-8.G.1", juce::String::fromUTF8 ("Questionário: dilatação do campo maior"),
                       juce::String::fromUTF8 ("Responder ao questionário da dilatação do campo maior."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "G");
        m.exercises.back().quiz = {
            question ("Dilatar o campo harmônico é:",
                      { "acrescentar acordes às funções básicas",
                        "trocar a tonalidade",
                        "tocar mais rápido",
                        "remover acordes do campo" }, 0),
            question ("Quantos acordes de sétima dominante naturais tem o campo maior?",
                      { "um", "dois", "três", "cinco" }, 0),
            question ("O SubV7 de Dó é:",
                      { "Db7", "D7", "G7", "C7" }, 0),
            question ("O SubIIm de Dó é:",
                      { "Dm7b5", "Dm7", "D7", "Fm7" }, 0),
            question ("No campo dilatado, o D7 (V7/V) aponta para:",
                      { "Sol", "Dó", "Lá", "Fá" }, 0),
        };
        add (chordExercise ("EX-8.G.2", "Montar o V7/V (D7)",
                            "Tocar o dominante que aponta para o Sol no campo dilatado.",
                            { 2, 6, 9, 0 }), "G");
        add (progressionExercise ("EX-8.G.3", "Dilatar a cadência com o V7/V",
                                  "Tocar Dm7 → D7 → G7 → CM7.",
                                  { { 2, 5, 9, 0 }, { 2, 6, 9, 0 },
                                    { 7, 11, 2, 5 }, { 0, 4, 7, 11 } }), "G");
        add (exercise ("EX-8.G.4", juce::String::fromUTF8 ("Funções do campo dilatado"),
                       juce::String::fromUTF8 ("Classificar os acordes do campo dilatado por função."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário de funções.")), "G");
        m.exercises.back().quiz = {
            question ("A7 (V7/ii) exerce qual função?",
                      { "subdominante", "tônica", "dominante de Dm", "empréstimo" }, 2),
            question ("Ab7M (bVI) exerce qual função?",
                      { "tônica", "subdominante", "empréstimo de cor", "dominante" }, 2),
            question ("No campo dilatado, o que o G7 pode virar?",
                      { "Db7 (SubV7)", "Dm7b5", "FM7", "Am7" }, 0),
        };

        // --- Topic H — dilatação do campo menor ------------------------------
        add (exercise ("EX-8.H.1", juce::String::fromUTF8 ("Questionário: dilatação do campo menor"),
                       juce::String::fromUTF8 ("Responder ao questionário da dilatação do campo menor."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "H");
        m.exercises.back().quiz = {
            question ("O campo menor é a união de quantas escalas?",
                      { "uma", "duas", "três", "sete" }, 2),
            question ("Qual escala menor cria o dominante (V7)?",
                      { "natural", "harmônica", "melódica", "dórica" }, 1),
            question ("No campo menor natural, o quinto grau é:",
                      { "G7", "Gm7", "Gm7b5", "Gdim7" }, 1),
            question ("A cadência fundamental do menor é:",
                      { "Dm7b5 → G7 → Cm7", "Dm7 → G7 → CM7",
                        "Fm7 → Bb7 → Cm7", "Cm7 → Fm7 → G7" }, 0),
            question ("O que a escala melódica acrescenta ao campo menor?",
                      { "acordes de cor (Dm7, F7)", "o dominante",
                        "a tônica menor", "nada" }, 0),
        };
        add (chordExercise ("EX-8.H.2", "Montar a tônica menor (Cm7)",
                            "Tocar o i do campo menor de Dó.",
                            { 0, 3, 7, 10 }), "H");
        add (chordExercise ("EX-8.H.3", "Montar o dominante do menor (G7)",
                            "Tocar o V7 que vem da escala menor harmônica.",
                            { 7, 11, 2, 5 }), "H");
        add (exercise ("EX-8.H.4", juce::String::fromUTF8 ("Escalas do campo menor"),
                       juce::String::fromUTF8 ("Relacionar cada acorde do menor à sua escala."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário de escalas.")), "H");
        m.exercises.back().quiz = {
            question ("Sobre o Cm7, qual escala usar?",
                      { "dórica de Dó", "lócria de Dó", "lídia de Dó", "mixolídia de Dó" }, 0),
            question ("Sobre o Dm7b5, qual escala usar?",
                      { "lócria de Ré", "dórica de Ré", "frígia de Ré", "lídia de Ré" }, 0),
            question ("Sobre o G7 do menor, qual escala usar?",
                      { "mixolídia (ou alterada)", "dórica", "lócria", "lídia" }, 0),
        };

        // --- Topic I — II-V-I maior e menor ----------------------------------
        add (exercise ("EX-8.I.1", juce::String::fromUTF8 ("Questionário: II-V-I"),
                       juce::String::fromUTF8 ("Responder ao questionário do II-V-I."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões do II-V-I.")), "I");
        m.exercises.back().quiz = {
            question ("Quais funções o II-V-I reúne?",
                      { "subdominante, dominante e tônica",
                        "tônica, tônica e dominante",
                        "dominante e empréstimo",
                        "apenas dominante" }, 0),
            question ("O II-V-I maior em Dó é:",
                      { "Dm7 → G7 → CM7", "Dm7b5 → G7 → Cm7",
                        "Dm7 → Db7 → CM7", "Fm7 → Bb7 → CM7" }, 0),
            question ("O II-V-I menor em Dó é:",
                      { "Dm7b5 → G7 → Cm7", "Dm7 → G7 → CM7",
                        "Dm7 → Db7 → Cm7", "Fm7 → G7 → Cm7" }, 0),
            question ("O que conduz as vozes no II-V-I?",
                      { "o voice leading por meio-tom", "o volume",
                        "a corda usada", "a velocidade" }, 0),
            question ("As notas-guia de um acorde são:",
                      { "a terça e a sétima", "a tônica e a quinta",
                        "a nona e a décima primeira", "a fundamental e a oitava" }, 0),
        };
        add (progressionExercise ("EX-8.I.2", "II-V-I maior",
                                  "Tocar Dm7 → G7 → CM7.",
                                  { { 2, 5, 9, 0 }, { 7, 11, 2, 5 }, { 0, 4, 7, 11 } }), "I");
        add (progressionExercise ("EX-8.I.3", "II-V-I menor",
                                  "Tocar Dm7b5 → G7 → Cm7.",
                                  { { 2, 5, 8, 0 }, { 7, 11, 2, 5 }, { 0, 3, 7, 10 } }), "I");
        add (exercise ("EX-8.I.4", juce::String::fromUTF8 ("II-V-I em outras tonalidades"),
                       juce::String::fromUTF8 ("Dizer o II-V-I em outras tonalidades."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário de transposição.")), "I");
        m.exercises.back().quiz = {
            question ("O II-V-I maior em Sol é:",
                      { "Am7 → D7 → GM7", "Am7b5 → D7 → Gm7",
                        "Am7 → Db7 → GM7", "Cm7 → F7 → GM7" }, 0),
            question ("O II-V-I menor em Lá menor é:",
                      { "Bm7b5 → E7 → Am7", "Bm7 → E7 → Am7",
                        "Bm7b5 → Bb7 → Am7", "Dm7 → G7 → Am7" }, 0),
            question ("No II-V-I menor, o dominante costuma receber:",
                      { "b9", "#11 apenas", "nona maior", "nenhuma tensão" }, 0),
        };

        // --- Topic J — situações que não são II-V-I --------------------------
        add (exercise ("EX-8.J.1", juce::String::fromUTF8 ("Questionário: o que não é II-V-I"),
                       juce::String::fromUTF8 ("Responder ao questionário das falsas cadências."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "J");
        m.exercises.back().quiz = {
            question ("A cadência deceptiva resolve em:",
                      { "no vi", "no I", "no IV", "no V" }, 0),
            question ("A cadência de backdoor usa:",
                      { "iv menor e bVII", "ii e V", "só o V", "só o IV" }, 0),
            question ("Um vamp modal:",
                      { "nunca resolve", "sempre resolve no I",
                        "tem dois dominantes", "é um II-V-I" }, 0),
            question ("A meia cadência para:",
                      { "no V", "no I", "no vi", "no bVII" }, 0),
            question ("A pergunta-chave para identificar uma progressão é:",
                      { "qual é o alvo e como ele é alcançado",
                        "quantos acordes tem",
                        "quem compôs",
                        "qual o andamento" }, 0),
        };
        add (progressionExercise ("EX-8.J.2", "Cadência deceptiva",
                                  "Tocar Dm7 → G7 → Am7 (o dominante resolve no vi).",
                                  { { 2, 5, 9, 0 }, { 7, 11, 2, 5 }, { 9, 0, 4, 7 } }), "J");
        add (progressionExercise ("EX-8.J.3", "Cadência de backdoor",
                                  "Tocar Fm7 → Bb7 → CM7 (sem passar pelo V).",
                                  { { 5, 8, 0, 3 }, { 10, 2, 5, 8 }, { 0, 4, 7, 11 } }), "J");
        add (exercise ("EX-8.J.4", juce::String::fromUTF8 ("Identificar a progressão"),
                       juce::String::fromUTF8 ("Nomear as progressões pelo alvo."),
                       juce::String::fromUTF8 ("Acerto ≥90% na identificação.")), "J");
        m.exercises.back().quiz = {
            question ("G7 → Am7 é:",
                      { "cadência deceptiva", "II-V-I", "backdoor", "plagal" }, 0),
            question ("Fm7 → Bb7 → CM7 é:",
                      { "cadência de backdoor", "II-V-I maior", "vamp modal", "deceptiva" }, 0),
            question ("Dm7 → G7 (repetindo) é:",
                      { "um vamp modal", "um II-V-I", "uma deceptiva", "um backdoor" }, 0),
        };

        // The gate closes the module: play a II-V-I maior on the grid, built
        // from the material of the module (REQ-009, REQ-015).
        auto& gate = m.exercises.emplace_back (exercise (
            "GATE-8", juce::String::fromUTF8 ("Desafio de gate — II-V-I maior (Dm7–G7–CM7)"),
            juce::String::fromUTF8 ("Tocar Dm7 – G7 – CM7 a 88 BPM, na grade do metrônomo."),
            juce::String::fromUTF8 ("Acordes reconhecidos e alinhados à grade (≥ 0,81).")));
        gate.isGate = true;
        gate.lessonId = "I";
        gate.chordProgression = {
            { 2, 5, 9, 0 },   // Dm7
            { 7, 11, 2, 5 },  // G7
            { 0, 4, 7, 11 },  // CM7
        };

        m.gateChallenge = juce::String::fromUTF8 (
            "Tocar Dm7 – G7 – CM7 (II-V-I maior, nível 4) a 88 BPM com ≥90% de "
            "acerto de acordes e on_grid_ratio ≥ 0,81. A cadência usa o dominante "
            "estudado no módulo.");

        // Pattern and links the module must cite (REQ-007, REQ-010).
        m.practice.patternId = "PTN-A-DROP2";
        m.practice.patternUse = juce::String::fromUTF8 (
            "Arpejos de sétima em Drop 2: a digitação fixa 1-3-5-7 aplica-se a "
            "qualquer acorde do módulo (Dm7, G7, CM7, Db7), de modo que o aluno "
            "ouve cada nota do dominante e da sua substituição. Complemento: "
            "PTN-M-4ths (quartas) para ouvir o movimento das quintas.");
        m.practice.guitarists = { "Joe Pass", "Wes Montgomery", "Pat Metheny" };

        // Curated apostilas (REQ-006, CM-012); see docs/MUSIC.md §8.
        m.sources = {
            "pdf-p-classtruncatedtext-module-lineclamped-85ulhh-style-max-lines5bohumil-med-teoria-da-musica-5-edicao-p",
            "pdf-desvendando-os-segredos-da-guitarra-fusion",
            "pdf-teoria-elementar-da-musica-ricordi-osvaldo-lacerda",
            "pdf-mozart-mello-livroestudosdeguitarra4em1",
            "pdf-caged-e-derivaoes-de-acordes-marcelo-mello-apostila-de-violao-e-guitarra-vol1",
        };

        return m;
    }


    // Module 9 — Etapa 9: harmonia avançada e estruturas especiais. Same shape
    // as module 2: nine topics (A..I), each with >=5 pages of explanation,
    // images and tables; the module demonstrates the structures with audio and
    // scores (every score carries its audio); 3..5 exercises per topic mixing
    // quizzes and playable exercises (the app recognises the notes). Level, BPM
    // and alignment come from MUSIC.md (the placeholder values are reused).
    CourseModule makeModule9()
    {
        CourseModule m;
        m.number = 9;
        m.title = juce::String::fromUTF8 ("Harmonia avançada e estruturas especiais");
        m.objective = juce::String::fromUTF8 (
            "Explorar possibilidades harmônicas mais elaboradas — acordes diminutos, "
            "dominantes diminutos, campos e estruturas simétricas — e desenvolver uma "
            "visão ampla das relações entre acordes.");
        m.level = 4;          // MUSIC.md: módulo 9 = nível 4
        m.targetBpm = 92;     // MUSIC.md, módulo 9
        m.onGridTarget = 0.81f;
        m.implemented = true;

        m.lessons = {
            detail (block ("A", juce::String::fromUTF8 ("Acordes diminutos e suas funções"), {
                "O diminuto é um empilhamento de terças menores (0-3-6; dim7 = 0-3-6-9).",
                "É simétrico: só existem três dim7 diferentes.",
                "Funções: sensível, ii grau menor, passagem e substituto de dominante."
            }), content::topic9A()),
            detail (block ("B", juce::String::fromUTF8 ("Dominantes diminutos (DomDim)"), {
                "O DomDim é o dominante com nona bemol (e outras tensões).",
                "Nasce da escala diminuta meio-tom / tom.",
                "Sem a fundamental, o dominante com nona bemol vira um dim7."
            }), content::topic9B()),
            detail (block ("C", juce::String::fromUTF8 ("Ciclos diminutos"), {
                "O ciclo das terças menores percorre quatro notas e volta ao início.",
                "Existem apenas três dim7 diferentes no total.",
                "O ciclo é um mapa de modulação e um recurso de improvisação."
            }), content::topic9C()),
            detail (block ("D", juce::String::fromUTF8 ("Campos harmônicos diminutos"), {
                "As escalas diminutas geram dois campos: tom-meio-tom e meio-tom-tom.",
                "O campo do DomDim é o da escala meio-tom / tom.",
                "O campo diminuto se cruza com o campo maior pelo vii grau."
            }), content::topic9D()),
            detail (block ("E", juce::String::fromUTF8 ("Acorde m7(#5)"), {
                "m7(#5) = tônica, terça menor, quinta aumentada e sétima menor.",
                "Difere do m7 apenas na quinta, mas a cor muda por completo.",
                "Tem leitura enarmônica: é uma inversão de acorde maior com nona."
            }), content::topic9E()),
            detail (block ("F", juce::String::fromUTF8 ("Policordes"), {
                "Policorde = dois acordes empilhados; o baixo define a harmonia.",
                "Diferente do slash chord, o baixo é um acorde completo.",
                "Na guitarra, as camadas se separam por registro."
            }), content::topic9F()),
            detail (block ("G", juce::String::fromUTF8 ("Simetria e escalas simétricas"), {
                "Escala simétrica divide a oitava em partes iguais.",
                "Tons inteiros: seis notas, duas formas; diminuta: oito notas, três formas.",
                "Na guitarra, a mesma digitação se desloca pelo braço."
            }), content::topic9G()),
            detail (block ("H", juce::String::fromUTF8 ("Relações entre campos harmônicos"), {
                "Campos vizinhos compartilham seis das sete notas.",
                "O acorde pivô pertence aos dois campos e prepara a passagem.",
                "O dominante secundário e o diminuto ligam campos distantes."
            }), content::topic9H()),
            detail (block ("I", juce::String::fromUTF8 ("Sonoridades especiais"), {
                "Quartal, cluster, add9/6-9, inversões e estruturas superiores.",
                "Cada sonoridade tem um uso: cor, tensão, movimento ou repouso.",
                "Todas funcionam melhor em contraste com momentos simples."
            }), content::topic9I()),
        };

        auto add = [&m] (Exercise e, const char* topic)
        {
            e.lessonId = topic;
            m.exercises.push_back (std::move (e));
            return (int) m.exercises.size() - 1;
        };

        // --- Topic A — acordes diminutos e suas funções -----------------------
        add (exercise ("EX-9.A.1", juce::String::fromUTF8 ("Questionário: acordes diminutos"),
                       juce::String::fromUTF8 ("Responder ao questionário sobre o acorde diminuto."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões do diminuto.")), "A");
        m.exercises.back().quiz = {
            question ("O acorde diminuto é formado por:",
                      { "terças menores empilhadas", "terças maiores empilhadas",
                        "quartas empilhadas", "quintas empilhadas" }, 0),
            question ("Quais intervalos formam o dim7 sobre a tônica?",
                      { "0-3-6-9", "0-4-7-11", "0-3-7-10", "0-4-7-10" }, 0),
            question ("Quantos acordes dim7 diferentes existem na música ocidental?",
                      { "Três", "Quatro", "Seis", "Doze" }, 0),
            question ("No campo harmônico maior, o acorde diminuto aparece no:",
                      { "sétimo grau (sensível)", "primeiro grau",
                        "quarto grau", "quinto grau" }, 0),
            question ("O acorde meio-diminuto se distingue do dim7 pela:",
                      { "sétima menor (10 semitons) em vez da diminuta (9)",
                        "terça maior", "quinta justa", "nona" }, 0),
        };
        add (exercise ("EX-9.A.2", juce::String::fromUTF8 ("Tocar a tríade diminuta"),
                       juce::String::fromUTF8 ("Tocar uma tríade diminuta (0-3-6) em qualquer posição."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere as classes de altura da tríade diminuta.")), "A");
        m.exercises.back().chordPitchClasses = { 0, 3, 6 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-9.A.3", juce::String::fromUTF8 ("Tocar o diminuto de sétima"),
                       juce::String::fromUTF8 ("Tocar um dim7 (0-3-6-9) em qualquer posição do braço."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere as classes de altura do dim7.")), "A");
        m.exercises.back().chordPitchClasses = { 0, 3, 6, 9 };
        m.exercises.back().usesGrid = false;
        add (intervalExercise ("EX-9.A.4", "Identificar o trítono",
                               "Tocar um trítono (6 semitons), que é a quinta diminuta do acorde, duas vezes.",
                               6, 2), "A");

        // --- Topic B — dominantes diminutos -----------------------------------
        add (exercise ("EX-9.B.1", juce::String::fromUTF8 ("Questionário: dominantes diminutos"),
                       juce::String::fromUTF8 ("Responder ao questionário do DomDim."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões do DomDim.")), "B");
        m.exercises.back().quiz = {
            question ("O acorde dominante diminuto (DomDim) é:",
                      { "o dominante com nona bemol", "o dominante com quarta justa",
                        "um acorde menor com sétima", "uma tríade aumentada" }, 0),
            question ("O DomDim nasce de qual escala?",
                      { "diminuta meio-tom / tom", "maior natural",
                        "menor natural", "pentatônica" }, 0),
            question ("Sem a fundamental, o dominante com nona bemol vira:",
                      { "um acorde diminuto de sétima", "uma tríade maior",
                        "um acorde menor com sétima", "uma quinta aumentada" }, 0),
            question ("O dim7 substituto fica, em relação à resolução, a:",
                      { "um semitom acima", "uma quarta acima",
                        "uma quinta abaixo", "uma oitava abaixo" }, 0),
            question ("Quantos dominantes usam a mesma escala diminuta?",
                      { "Quatro, a uma terça menor de distância", "Dois",
                        "Três", "Doze" }, 0),
        };
        add (exercise ("EX-9.B.2", juce::String::fromUTF8 ("Tocar o dominante com nona bemol"),
                       juce::String::fromUTF8 ("Tocar C7(b9) (0-4-7-10-1) em qualquer posição."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere as classes de altura do dominante com nona bemol.")), "B");
        m.exercises.back().chordPitchClasses = { 0, 4, 7, 10, 1 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-9.B.3", juce::String::fromUTF8 ("Tocar o diminuto substituto"),
                       juce::String::fromUTF8 ("Tocar o dim7 substituto um semitom acima da resolução."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere as classes de altura do dim7 substituto.")), "B");
        m.exercises.back().chordPitchClasses = { 1, 4, 7, 10 };
        m.exercises.back().usesGrid = false;
        add (intervalExercise ("EX-9.B.4", "A terça menor do substituto",
                               "Tocar uma terça menor (3 semitons), o passo que separa o dominante do substituto, duas vezes.",
                               3, 2), "B");

        // --- Topic C — ciclos diminutos ---------------------------------------
        add (exercise ("EX-9.C.1", juce::String::fromUTF8 ("Questionário: ciclos diminutos"),
                       juce::String::fromUTF8 ("Responder ao questionário do ciclo diminuto."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões do ciclo.")), "C");
        m.exercises.back().quiz = {
            question ("O ciclo diminuto percorre a oitava de quantos em quantos semitons?",
                      { "de 3 em 3 (terças menores)", "de 2 em 2 (tons)",
                        "de 4 em 4 (terças maiores)", "de 7 em 7 (quintas)" }, 0),
            question ("Quantas notas o ciclo das terças menores percorre?",
                      { "Quatro", "Três", "Seis", "Doze" }, 0),
            question ("Cdim7, Ebdim7, Gbdim7 e Adim7 são:",
                      { "o mesmo som, com nomes diferentes", "quatro acordes distintos",
                        "tríades maiores", "dominantes" }, 0),
            question ("O ciclo diminuto serve, na prática, para:",
                      { "modular e deslocar frases pelo braço", "afinar o instrumento",
                        "medir o tempo", "aumentar o volume" }, 0),
        };
        add (exercise ("EX-9.C.2", juce::String::fromUTF8 ("O mesmo dim7 em quatro posições"),
                       juce::String::fromUTF8 ("Tocar um dim7 (0-3-6-9) e deslocá-lo de terça menor em terça menor."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere que as classes de altura continuam as do dim7.")), "C");
        m.exercises.back().chordPitchClasses = { 0, 3, 6, 9 };
        m.exercises.back().usesGrid = false;
        add (intervalExercise ("EX-9.C.3", "O passo do ciclo",
                               "Tocar uma terça menor (3 semitons), o passo do ciclo diminuto, duas vezes.",
                               3, 2), "C");

        // --- Topic D — campos harmônicos diminutos ----------------------------
        add (exercise ("EX-9.D.1", juce::String::fromUTF8 ("Questionário: campos diminutos"),
                       juce::String::fromUTF8 ("Responder ao questionário dos campos diminutos."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões do campo diminuto.")), "D");
        m.exercises.back().quiz = {
            question ("As escalas diminutas geram quantos campos?",
                      { "Dois: tom-meio-tom e meio-tom-tom", "Um só",
                        "Três", "Doze" }, 0),
            question ("O campo do DomDim é o da escala:",
                      { "meio-tom / tom", "maior natural", "menor harmônica", "pentatônica" }, 0),
            question ("O vii grau do campo maior pertence também ao:",
                      { "campo diminuto", "campo de blues", "campo pentatônico", "campo de tons inteiros" }, 0),
            question ("O campo diminuto organiza a harmonia sobretudo por:",
                      { "cor e tensão", "função de tônica e dominante",
                        "compasso", "andamento" }, 0),
        };
        add (exercise ("EX-9.D.2", juce::String::fromUTF8 ("Tocar o meio-diminuto"),
                       juce::String::fromUTF8 ("Tocar um m7(b5) (0-3-6-10), o ii grau do campo menor."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere as classes de altura do meio-diminuto.")), "D");
        m.exercises.back().chordPitchClasses = { 0, 3, 6, 10 };
        m.exercises.back().usesGrid = false;
        add (intervalExercise ("EX-9.D.3", "O passo de tom do campo",
                               "Tocar um tom (2 semitons), o passo da escala tom-meio-tom, duas vezes.",
                               2, 2), "D");

        // --- Topic E — acorde m7(#5) ------------------------------------------
        add (exercise ("EX-9.E.1", juce::String::fromUTF8 ("Questionário: o acorde m7(#5)"),
                       juce::String::fromUTF8 ("Responder ao questionário do m7(#5)."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões do m7(#5).")), "E");
        m.exercises.back().quiz = {
            question ("O m7(#5) tem os intervalos:",
                      { "0-3-8-10", "0-3-7-10", "0-4-7-10", "0-3-6-10" }, 0),
            question ("Em relação ao m7, o m7(#5) muda:",
                      { "a quinta (de justa para aumentada)", "a terça", "a sétima", "a fundamental" }, 0),
            question ("O m7(#5) tem uma leitura enarmônica como:",
                      { "uma inversão de acorde maior com nona", "um dominante",
                        "uma tríade aumentada", "um acorde meio-diminuto" }, 0),
            question ("O som do m7(#5) é:",
                      { "suspenso, sem repouso claro", "estável e cantável",
                        "igual ao m7", "igual a uma tríade maior" }, 0),
        };
        add (exercise ("EX-9.E.2", juce::String::fromUTF8 ("Tocar o m7(#5)"),
                       juce::String::fromUTF8 ("Tocar um m7(#5) (0-3-8-10) em qualquer posição."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere as classes de altura do m7(#5).")), "E");
        m.exercises.back().chordPitchClasses = { 0, 3, 8, 10 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-9.E.3", juce::String::fromUTF8 ("Comparar m7 e m7(#5)"),
                       juce::String::fromUTF8 ("Tocar um m7 (0-3-7-10) para comparar com o m7(#5)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere as classes de altura do m7.")), "E");
        m.exercises.back().chordPitchClasses = { 0, 3, 7, 10 };
        m.exercises.back().usesGrid = false;
        add (intervalExercise ("EX-9.E.4", "Identificar a quinta aumentada",
                               "Tocar uma quinta aumentada (8 semitons), a marca do m7(#5), duas vezes.",
                               8, 2), "E");

        // --- Topic F — policordes ---------------------------------------------
        add (exercise ("EX-9.F.1", juce::String::fromUTF8 ("Questionário: policordes"),
                       juce::String::fromUTF8 ("Responder ao questionário dos policordes."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões dos policordes.")), "F");
        m.exercises.back().quiz = {
            question ("Um policorde é:",
                      { "dois acordes empilhados", "um acorde com uma nota repetida",
                        "uma escala", "um intervalo" }, 0),
            question ("Diferente do slash chord, no policorde o baixo é:",
                      { "um acorde completo", "uma nota do acorde de cima",
                        "sempre a tônica", "uma nota estranha" }, 0),
            question ("A camada inferior de um policorde:",
                      { "define a harmonia de base", "só acrescenta tensão",
                        "é sempre maior", "não importa" }, 0),
            question ("Na guitarra, as camadas do policorde se separam por:",
                      { "registro (graves e agudos)", "andamento", "volume", "afinação" }, 0),
        };
        add (exercise ("EX-9.F.2", juce::String::fromUTF8 ("Tocar o policorde D/C"),
                       juce::String::fromUTF8 ("Tocar as notas de D/C (tríade de Ré sobre a de Dó)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere as classes de altura das duas camadas.")), "F");
        m.exercises.back().chordPitchClasses = { 0, 2, 4, 6, 7, 9 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-9.F.3", juce::String::fromUTF8 ("Tocar a camada inferior"),
                       juce::String::fromUTF8 ("Tocar a tríade de Dó (0-4-7), o baixo do policorde."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere a tríade de baixo.")), "F");
        m.exercises.back().chordPitchClasses = { 0, 4, 7 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-9.F.4", juce::String::fromUTF8 ("Notação do policorde"),
                       juce::String::fromUTF8 ("Interpretar a cifra de um policorde."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário de notação.")), "F");
        m.exercises.back().quiz = {
            question ("Na cifra D/C, o que significa a barra?",
                      { "que o acorde de Ré soa sobre o baixo de Dó",
                        "que o acorde é menor", "que o acorde é dominante",
                        "que o baixo é a nota Ré" }, 0),
            question ("F/G, na prática, é:",
                      { "a tríade de Fá sobre a de Sol", "um acorde menor",
                        "um dim7", "uma escala" }, 0),
            question ("Um policorde bem construído soa:",
                      { "rico e coerente", "confuso", "igual a um acorde simples", "desafinado" }, 0),
        };

        // --- Topic G — simetria e escalas simétricas --------------------------
        add (exercise ("EX-9.G.1", juce::String::fromUTF8 ("Questionário: escalas simétricas"),
                       juce::String::fromUTF8 ("Responder ao questionário das escalas simétricas."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões da simetria.")), "G");
        m.exercises.back().quiz = {
            question ("Uma escala é simétrica quando:",
                      { "divide a oitava em partes iguais", "tem sete notas",
                        "é sempre maior", "não tem tônica" }, 0),
            question ("Quantas escalas de tons inteiros existem?",
                      { "Duas", "Três", "Quatro", "Doze" }, 0),
            question ("Quantas escalas diminutas existem?",
                      { "Três", "Duas", "Quatro", "Doze" }, 0),
            question ("Na guitarra, a simetria permite:",
                      { "deslocar a mesma digitação pelo braço", "afinar mais rápido",
                        "tocar mais alto", "mudar o timbre" }, 0),
        };
        add (intervalExercise ("EX-9.G.2", "O passo da escala de tons inteiros",
                               "Tocar um tom (2 semitons), o passo da escala de tons inteiros, duas vezes.",
                               2, 2), "G");
        add (intervalExercise ("EX-9.G.3", "O passo da escala diminuta",
                               "Tocar uma terça menor (3 semitons), o passo do ciclo diminuto, duas vezes.",
                               3, 2), "G");
        add (intervalExercise ("EX-9.G.4", "O passo da escala aumentada",
                               "Tocar uma terça maior (4 semitons), o passo da escala aumentada, duas vezes.",
                               4, 2), "G");

        // --- Topic H — relações entre campos harmônicos -----------------------
        add (exercise ("EX-9.H.1", juce::String::fromUTF8 ("Questionário: relações entre campos"),
                       juce::String::fromUTF8 ("Responder ao questionário das relações entre campos."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões das relações.")), "H");
        m.exercises.back().quiz = {
            question ("Duas tonalidades vizinhas no círculo das quintas compartilham:",
                      { "seis das sete notas", "apenas a tônica",
                        "todas as notas", "nenhuma nota" }, 0),
            question ("Um acorde pivô é um acorde que:",
                      { "pertence aos dois campos", "só existe no campo maior",
                        "é sempre diminuto", "não tem função" }, 0),
            question ("O dominante secundário é:",
                      { "o V7 da nova tônica", "o I grau do campo",
                        "um acorde diminuto", "o IV grau" }, 0),
            question ("Campos relativos (Do maior e Lá menor) compartilham:",
                      { "as mesmas notas", "apenas a tônica", "nenhuma nota", "só o dominante" }, 0),
        };
        add (exercise ("EX-9.H.2", juce::String::fromUTF8 ("Modular por acorde pivô"),
                       juce::String::fromUTF8 ("Tocar uma progressão que passa por um pivô até a nova tônica."),
                       juce::String::fromUTF8 ("O app reconhece a progressão de acordes e confere as classes de altura.")), "H");
        m.exercises.back().chordProgression = {
            { 0, 4, 7 },      // C  (campo de origem)
            { 7, 11, 2 },     // G  (pivô)
            { 2, 6, 9, 0 },   // D7 (dominante secundário, com a sétima menor)
            { 7, 11, 2 },     // G  (nova tônica)
        };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-9.H.3", juce::String::fromUTF8 ("Tocar o dominante secundário"),
                       juce::String::fromUTF8 ("Tocar D7 (2-6-9-0), o V7 da nova tonalidade."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere as classes de altura do dominante secundário.")), "H");
        m.exercises.back().chordPitchClasses = { 2, 6, 9, 0 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-9.H.4", juce::String::fromUTF8 ("Homônimos e relativos"),
                       juce::String::fromUTF8 ("Distinguir campos relativos de homônimos."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário de campos.")), "H");
        m.exercises.back().quiz = {
            question ("Do maior e Lá menor são campos:",
                      { "relativos", "homônimos", "distantes", "idênticos" }, 0),
            question ("Do maior e Do menor são campos:",
                      { "homônimos", "relativos", "distantes", "iguais" }, 0),
            question ("Quanto mais notas dois campos compartilham, a passagem entre eles é:",
                      { "mais suave", "mais abrupta", "impossível", "sempre igual" }, 0),
        };

        // --- Topic I — sonoridades especiais ----------------------------------
        add (exercise ("EX-9.I.1", juce::String::fromUTF8 ("Questionário: sonoridades especiais"),
                       juce::String::fromUTF8 ("Responder ao questionário das sonoridades especiais."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões das sonoridades.")), "I");
        m.exercises.back().quiz = {
            question ("O acorde quartal é construído empilhando:",
                      { "quartas", "terças", "quintas", "sextas" }, 0),
            question ("O cluster é:",
                      { "um conjunto de notas vizinhas", "uma tríade maior",
                        "um acorde diminuto", "uma escala" }, 0),
            question ("Uma estrutura superior é:",
                      { "uma tríade tocada sobre um dominante", "um acorde menor",
                        "um cluster", "um baixo invertido" }, 0),
            question ("O acorde add9 acrescenta à tríade:",
                      { "a nona", "a sétima", "a quarta", "a sexta" }, 0),
            question ("As sonoridades especiais funcionam melhor:",
                      { "em contraste com momentos simples", "em excesso",
                        "isoladas da música", "sem função" }, 0),
        };
        add (exercise ("EX-9.I.2", juce::String::fromUTF8 ("Tocar o acorde quartal"),
                       juce::String::fromUTF8 ("Tocar um acorde quartal sobre Dó (quartas empilhadas)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere as classes de altura do acorde quartal.")), "I");
        m.exercises.back().chordPitchClasses = { 0, 5, 10 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-9.I.3", juce::String::fromUTF8 ("Tocar o acorde 6/9"),
                       juce::String::fromUTF8 ("Tocar um C6/9 (tônica, terça, quinta, sexta e nona)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere as classes de altura do 6/9.")), "I");
        m.exercises.back().chordPitchClasses = { 0, 2, 4, 7, 9 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-9.I.4", juce::String::fromUTF8 ("Da sonoridade à música"),
                       juce::String::fromUTF8 ("Escolher a sonoridade certa para cada momento."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário de aplicação.")), "I");
        m.exercises.back().quiz = {
            question ("Para um clímax de máxima tensão, a sonoridade indicada é:",
                      { "o cluster", "o add9", "a tríade maior", "a oitava" }, 0),
            question ("Para abrir uma introdução com som moderno e sem direção, use:",
                      { "o acorde quartal", "uma tríade maior", "um dominante", "uma escala maior" }, 0),
            question ("A sonoridade doce típica da bossa nova vem do:",
                      { "6/9", "cluster", "quartal", "dim7" }, 0),
        };

        // The gate closes the module on the grid: a I–#Idim7–ii–V turnaround
        // that returns to the tonic, built from the material of the module
        // (REQ-009, REQ-015). The student plays the chords in time.
        auto& gate = m.exercises.emplace_back (exercise (
            "GATE-9", juce::String::fromUTF8 ("Desafio de gate — turnaround C–C#dim7–Dm7–G7"),
            juce::String::fromUTF8 ("Tocar C – C#dim7 – Dm7 – G7 a 92 BPM, na grade do metrônomo."),
            juce::String::fromUTF8 ("Acordes reconhecidos e alinhados à grade (≥ 0,81).")));
        gate.isGate = true;
        gate.lessonId = "A";
        gate.chordProgression = {
            { 0, 4, 7 },      // C
            { 1, 4, 7, 10 },  // C#dim7 (diminuto de passagem)
            { 2, 5, 9, 0 },   // Dm7
            { 7, 11, 2, 5 },  // G7
        };

        m.gateChallenge = juce::String::fromUTF8 (
            "Tocar C – C#dim7 – Dm7 – G7 (turnaround com diminuto de passagem) a 92 BPM "
            "com ≥90% de acerto de acordes e on_grid_ratio ≥ 0,81. O diminuto de "
            "passagem conduz ao ii–V e prepara o retorno à tônica.");

        // Pattern and links the module must cite (REQ-007, REQ-010).
        m.practice.patternId = "PTN-A-DROP2";
        m.practice.patternUse = juce::String::fromUTF8 (
            "Arpejos de sétima em Drop 2: a digitação 1-3-5-7 cobre as tétrades "
            "estudadas (dim7, m7(b5), m7(#5), dominante com nona bemol) e permite "
            "tocar as sonoridades do módulo em qualquer posição. Complemento: "
            "PTN-M-4ths (quartas) para os acordes quartais.");
        m.practice.guitarists = { "Greg Howe", "Guthrie Govan", "Joe Satriani" };

        // Curated apostilas (REQ-006, CM-012); see docs/MUSIC.md.
        m.sources = {
            "pdf-teoria-elementar-da-musica-ricordi-osvaldo-lacerda",
            "pdf-p-classtruncatedtext-module-lineclamped-85ulhh-style-max-lines5bohumil-med-teoria-da-musica-5-edicao-p",
            "pdf-mozart-mello-livroestudosdeguitarra4em1",
            "pdf-desvendando-os-segredos-da-guitarra-fusion",
        };

        return m;
    }


    // Module 10 — Etapa 10: análise harmônica, verticalização e reharmonização.
    // The student learns to analyse a song (degree, function, scale) and then to
    // find new ways to harmonise it (substitution, modal borrowing, target
    // harmony). The explanation carries images, tables, audio examples and
    // scores with their audio; every topic has >=5 pages (content::minTopicChars)
    // and part of the exercises is played on the instrument and verified by the
    // app (chord pitch classes / interval recognition).
    CourseModule makeModule10()
    {
        CourseModule m;
        m.number = 10;
        m.title = juce::String::fromUTF8 ("Análise harmônica, verticalização e reharmonização");
        m.objective = juce::String::fromUTF8 (
            "Aprender a analisar músicas e descobrir diferentes caminhos para "
            "modificar suas harmonias — do grau e da função de cada acorde até a "
            "verticalização e a reharmonização, sempre respeitando a melodia.");
        m.level = 4;          // MUSIC.md: módulos 8–10 = nível 4
        m.targetBpm = 96;     // MUSIC.md, módulo 10
        m.onGridTarget = 0.82f;
        m.implemented = true;

        m.lessons = {
            detail (block ("A", juce::String::fromUTF8 ("Análise harmônica"), {
                "Analisar é responder grau, função e escala para cada acorde.",
                "O grau vem da escala; a função é tônica, subdominante ou dominante.",
                "A análise é o mapa que sustenta toda a reharmonização."
            }), content::topic10A()),
            detail (block ("B", juce::String::fromUTF8 ("Análise melódica"), {
                "Cada nota da melodia é repouso (nota do acorde) ou tensão.",
                "A tensão precisa resolver; no tempo forte, prefira o repouso.",
                "Converter a melodia em graus revela o desenho da frase."
            }), content::topic10B()),
            detail (block ("C", juce::String::fromUTF8 ("Escolha modal"), {
                "O modo vem do acorde, não da escala da música.",
                "Cada modo se distingue pela nota característica.",
                "Escolher o modo é escolher a cor e as tensões."
            }), content::topic10C()),
            detail (block ("D", juce::String::fromUTF8 ("Verticalização"), {
                "Verticalizar é construir acordes a partir das notas da melodia.",
                "Empilhar terças a partir da nota é o caminho mais direto.",
                "A melodia deve ser a voz de cima do acorde verticalizado."
            }), content::topic10D()),
            detail (block ("E", juce::String::fromUTF8 ("Conexão entre campos harmônicos"), {
                "Conectar campos é passar de uma tonalidade a outra sem ruptura.",
                "O acorde-pivo é a dobradiça entre os dois campos.",
                "A modulação se prepara com o dominante ou o ii–V do novo tom."
            }), content::topic10E()),
            detail (block ("F", juce::String::fromUTF8 ("Estudo das vozes internas"), {
                "Cada nota do acorde é uma voz; conduza cada linha pelo menor movimento.",
                "Notas comuns ficam paradas; sem nota comum, move-se um grau.",
                "Na guitarra, acordes de poucas notas facilitam a condução."
            }), content::topic10F()),
            detail (block ("G", juce::String::fromUTF8 ("Reharmonização"), {
                "Reharmonizar é trocar a harmonia mantendo a melodia.",
                "A melodia manda: as notas fortes precisam caber nos novos acordes.",
                "Substituição, empréstimo modal e acordes de passagem são as técnicas básicas."
            }), content::topic10G()),
            detail (block ("H", juce::String::fromUTF8 ("Harmonia-alvo"), {
                "Defina o alvo (a chegada) e construa a harmonia de trás para frente.",
                "O alvo é o acorde de repouso, revelado muitas vezes pela melodia.",
                "As aproximações (ii–V, subV, cromática) dão cores diferentes à chegada."
            }), content::topic10H()),
            detail (block ("I", juce::String::fromUTF8 ("Ferramentas de reharmonização"), {
                "Reharmonizar é aplicar um conjunto pequeno de ferramentas conhecidas.",
                "SubV, dominante secundário, empréstimo modal, passagem e verticalização.",
                "Escolha a ferramenta pelo efeito que você quer."
            }), content::topic10I()),
            detail (block ("J", juce::String::fromUTF8 ("Relação entre estilos e sonoridades"), {
                "A análise é a mesma em todos os estilos; a sonoridade é que muda.",
                "Bossa: densidade. Jazz: substituições. Blues: dominantes. Rock: tríades.",
                "Cada estilo tem convenções próprias de reharmonização."
            }), content::topic10J()),
        };

        // Exercises: 3..5 per topic, mixing verifiable quizzes and playable
        // exercises (the app recognises the notes). Ids follow EX-10.<topico>.<n>.
        auto add = [&m] (Exercise e, const char* topic)
        {
            e.lessonId = topic;
            m.exercises.push_back (std::move (e));
            return (int) m.exercises.size() - 1;
        };

        // --- Topic A — análise harmônica -------------------------------------
        add (exercise ("EX-10.A.1", juce::String::fromUTF8 ("Questionário: analisar a harmonia"),
                       juce::String::fromUTF8 ("Responder ao questionário de análise harmônica."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de análise.")), "A");
        m.exercises.back().quiz = {
            question ("Analisar uma harmonia é responder, por acorde:",
                      { "grau, função e escala",
                        "volume, timbre e andamento",
                        "apenas o nome do acorde",
                        "a duração de cada nota" }, 0),
            question ("Em Dó maior, o acorde Dm7 é qual grau?",
                      { "I", "ii", "IV", "V" }, 1),
            question ("Qual é a função do acorde de dominante (V)?",
                      { "repouso", "afastamento", "tensão que pede resolução", "nenhuma" }, 2),
            question ("Um A7 dentro do campo de Dó maior é:",
                      { "o I", "um dominante secundário (V/ii)", "o vii", "um erro" }, 1),
            question ("Sobre um acorde de sétima maior (7M) cabe qual escala?",
                      { "jônio / lídio", "lócrio", "alterada", "dórico" }, 0),
        };
        add (exercise ("EX-10.A.2", juce::String::fromUTF8 ("Tocar o ii–V–I em Dó"),
                       juce::String::fromUTF8 ("Tocar Dm7 – G7 – C7M e confirmar a análise (subdominante, dominante, tônica)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere a progressão ii–V–I.")), "A");
        m.exercises.back().chordProgression = {
            { 2, 5, 9, 0 },    // Dm7
            { 7, 11, 2, 5 },   // G7
            { 0, 4, 7, 11 },   // C7M
        };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-10.A.3", juce::String::fromUTF8 ("Tocar o turnaround analisado"),
                       juce::String::fromUTF8 ("Tocar C7M – A7 – Dm7 – G7, identificando o dominante secundário (A7)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere os quatro acordes do turnaround.")), "A");
        m.exercises.back().chordProgression = {
            { 0, 4, 7, 11 },   // C7M
            { 9, 1, 4, 7 },    // A7
            { 2, 5, 9, 0 },    // Dm7
            { 7, 11, 2, 5 },   // G7
        };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-10.A.4", juce::String::fromUTF8 ("Questionário: graus e funções"),
                       juce::String::fromUTF8 ("Identificar grau e função de acordes do campo harmônico."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário de graus.")), "A");
        m.exercises.back().quiz = {
            question ("Em Dó maior, o acorde F7M é qual grau e função?",
                      { "IV, subdominante", "V, dominante", "I, tônica", "vi, tônica relativa" }, 0),
            question ("Em Dó maior, o acorde Am7 é qual grau e função?",
                      { "vi, tônica relativa", "ii, subdominante", "IV, subdominante", "vii, dominante" }, 0),
            question ("O ciclo ii–V–I representa:",
                      { "subdominante, dominante, tônica",
                        "tônica, dominante, subdominante",
                        "dominante, tônica, subdominante",
                        "três tônicas" }, 0),
            question ("Um acorde que não está no campo harmônico pode ser:",
                      { "dominante secundário, empréstimo modal ou passagem",
                        "sempre um erro",
                        "sempre uma modulação",
                        "sempre o I" }, 0),
        };

        // --- Topic B — análise melódica --------------------------------------
        add (exercise ("EX-10.B.1", juce::String::fromUTF8 ("Questionário: notas de repouso e tensão"),
                       juce::String::fromUTF8 ("Responder ao questionário de análise melódica."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de análise melódica.")), "B");
        m.exercises.back().quiz = {
            question ("Sobre um acorde, as notas do acorde são:",
                      { "notas de repouso", "notas de tensão", "notas erradas", "sempre a melodia" }, 0),
            question ("Uma nota de tensão bem colocada:",
                      { "resolve numa nota do acorde",
                        "fica parada no tempo forte",
                        "é sempre um erro",
                        "substitui o acorde" }, 0),
            question ("As notas fortes da melodia devem cair, de preferência, em:",
                      { "notas do acorde", "notas estranhas", "qualquer nota", "silêncios" }, 0),
            question ("A nona (E) sobre Dm7, resolvendo para a fundamental (D), é:",
                      { "tensão resolvida (intenção)", "erro grave", "nota do acorde", "modulação" }, 0),
            question ("Analisar a melodia sem considerar o acorde é:",
                      { "errado: a nota só faz sentido contra o acorde",
                        "o método correto",
                        "a única forma",
                        "indiferente" }, 0),
        };
        add (exercise ("EX-10.B.2", juce::String::fromUTF8 ("Tocar o repouso do acorde"),
                       juce::String::fromUTF8 ("Tocar as notas do acorde Dm7 (D–F–A–C) como repouso."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere a cobertura do acorde.")), "B");
        m.exercises.back().chordPitchClasses = { 2, 5, 9, 0 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-10.B.3", juce::String::fromUTF8 ("Tensão que resolve"),
                       juce::String::fromUTF8 ("Tocar a nona (E) resolvendo na terça (F) sobre Dm7, como tensão resolvida."),
                       juce::String::fromUTF8 ("O app reconhece as notas tocadas e confere o movimento de tensão e resolução.")), "B");
        m.exercises.back().targets = notes ({ "E4", "F4", "E4", "F4" });
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-10.B.4", juce::String::fromUTF8 ("Questionário: a melodia revela a harmonia"),
                       juce::String::fromUTF8 ("Deduzir acordes a partir das notas fortes da melodia."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário de dedução.")), "B");
        m.exercises.back().quiz = {
            question ("A melodia insiste nas notas F e A. Qual acorde as contém?",
                      { "F7M (ou Dm7)", "C7", "G7", "Bm7b5" }, 0),
            question ("Na verticalização, a melodia serve para:",
                      { "escolher os acordes que a contêm",
                        "definir o andamento",
                        "aumentar o volume",
                        "substituir o baixo" }, 0),
            question ("A tensão que não resolve soa como:",
                      { "nota errada", "resolução", "tônica", "oitava" }, 0),
            question ("Antes de analisar uma nota, é preciso saber:",
                      { "o acorde que está soando", "o volume", "a corda usada", "o timbre" }, 0),
        };

        // --- Topic C — escolha modal -----------------------------------------
        add (exercise ("EX-10.C.1", juce::String::fromUTF8 ("Questionário: escolha modal"),
                       juce::String::fromUTF8 ("Responder ao questionário de modos."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões de escolha modal.")), "C");
        m.exercises.back().quiz = {
            question ("O modo a tocar sobre um acorde vem:",
                      { "do acorde que está soando", "da escala da música", "do andamento", "da tonalidade fixa" }, 0),
            question ("A nota característica que distingue o dórico do eólio é:",
                      { "a sexta (maior x menor)", "a terça", "a quinta", "a sétima" }, 0),
            question ("Sobre um acorde dominante que resolve (G7) cabe:",
                      { "mixolídio / alterada", "jônio", "lócrio", "eólio" }, 0),
            question ("A quarta aumentada (#11) é a nota característica do:",
                      { "lídio", "dórico", "frígio", "eólio" }, 0),
            question ("Escolher o modo é escolher:",
                      { "a cor e as tensões do improviso", "o andamento", "a afinação", "o volume" }, 0),
        };
        add (exercise ("EX-10.C.2", juce::String::fromUTF8 ("Tocar o modo dórico"),
                       juce::String::fromUTF8 ("Tocar as notas do modo dórico sobre Dm7, destacando a sexta maior."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere se o modo dórico foi tocado.")), "C");
        m.exercises.back().targets = notes ({ "D4", "E4", "F4", "G4", "A4", "B4", "C5" });
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-10.C.3", juce::String::fromUTF8 ("Tocar o modo mixolídio"),
                       juce::String::fromUTF8 ("Tocar as notas do modo mixolídio sobre G7, destacando a sétima menor."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere o modo mixolídio sobre o dominante.")), "C");
        m.exercises.back().targets = notes ({ "G3", "A3", "B3", "C4", "D4", "E4", "F4" });
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-10.C.4", juce::String::fromUTF8 ("Tocar o modo lídio"),
                       juce::String::fromUTF8 ("Tocar as notas do modo lídio sobre C7M, destacando a quarta aumentada."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere o modo lídio sobre a tônica.")), "C");
        m.exercises.back().targets = notes ({ "C4", "D4", "E4", "F#4", "G4", "A4", "B4" });
        m.exercises.back().usesGrid = false;

        // --- Topic D — verticalização ----------------------------------------
        add (exercise ("EX-10.D.1", juce::String::fromUTF8 ("Questionário: verticalização"),
                       juce::String::fromUTF8 ("Responder ao questionário de verticalização."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "D");
        m.exercises.back().quiz = {
            question ("Verticalizar é:",
                      { "construir acordes a partir das notas da melodia",
                        "tocar a melodia mais rápido",
                        "subir a melodia uma oitava",
                        "afinar o instrumento" }, 0),
            question ("Empilhando terças a partir da nota A, obtém-se:",
                      { "Am7 (A, C, E, G)", "C7M", "G7", "Dm7" }, 0),
            question ("Na verticalização, a melodia deve ficar:",
                      { "na voz mais aguda do acorde", "no baixo", "no meio do acorde", "escondida" }, 0),
            question ("Se a melodia toca D sobre C7M, o acorde verticalizado pode ser:",
                      { "C7M9", "C7M (#11)", "Cdim", "Cm7b5" }, 0),
            question ("A verticalização garante que:",
                      { "a harmonia contenha as notas da melodia",
                        "a música fique mais rápida",
                        "a melodia mude de tom",
                        "o acorde fique maior" }, 0),
        };
        add (exercise ("EX-10.D.2", juce::String::fromUTF8 ("Verticalizar a melodia A–G–F–E"),
                       juce::String::fromUTF8 ("Tocar os acordes Am7 – G7 – F7M – Em7 que verticalizam a melodia A–G–F–E."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere os quatro acordes verticalizados.")), "D");
        m.exercises.back().chordProgression = {
            { 9, 0, 4, 7 },    // Am7
            { 7, 11, 2, 5 },   // G7
            { 5, 9, 0, 4 },    // F7M
            { 4, 7, 11, 2 },   // Em7
        };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-10.D.3", juce::String::fromUTF8 ("Verticalizar com tensão"),
                       juce::String::fromUTF8 ("Tocar C7M9 (C–E–G–B–D), verticalizando a nona (D) sobre a tônica."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere a cobertura do acorde com a tensão.")), "D");
        m.exercises.back().chordPitchClasses = { 0, 4, 7, 11, 2 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-10.D.4", juce::String::fromUTF8 ("Questionário: empilhamento de terças"),
                       juce::String::fromUTF8 ("Identificar o acorde resultante do empilhamento."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário.")), "D");
        m.exercises.back().quiz = {
            question ("Empilhando terças a partir de G (G, B, D, F), obtém-se:",
                      { "G7", "G7M", "Gm7", "Gm7b5" }, 0),
            question ("Empilhando terças a partir de F (F, A, C, E), obtém-se:",
                      { "F7M", "F7", "Fm7", "Fdim" }, 0),
            question ("Empilhando terças a partir de E (E, G, B, D), obtém-se:",
                      { "Em7", "E7", "E7M", "Em7b5" }, 0),
            question ("Verticalizar uma tensão (ex.: nona) significa:",
                      { "escolher um acorde que contenha essa tensão",
                        "evitar a nota",
                        "tocar a nota mais grave",
                        "mudar de tom" }, 0),
        };

        // --- Topic E — conexão entre campos ----------------------------------
        add (exercise ("EX-10.E.1", juce::String::fromUTF8 ("Questionário: conectar campos"),
                       juce::String::fromUTF8 ("Responder ao questionário de conexão entre campos harmônicos."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "E");
        m.exercises.back().quiz = {
            question ("Um acorde-pivo é:",
                      { "um acorde que pertence (ou serve) aos dois campos",
                        "um acorde fora de qualquer campo",
                        "o acorde mais agudo",
                        "um acorde de passagem sem função" }, 0),
            question ("Para modular de Dó para Fá, o dominante do novo tom é:",
                      { "C7", "G7", "D7", "A7" }, 0),
            question ("Empréstimo modal é:",
                      { "usar acordes do menor paralelo sem mudar de centro",
                        "modular para outro tom",
                        "tocar mais rápido",
                        "mudar a afinação" }, 0),
            question ("A técnica mais poderosa para modular é:",
                      { "o ii–V do novo tom", "tocar a escala da tonalidade", "um acorde de passagem", "um silêncio" }, 0),
            question ("Um dominante que resolve num acorde que não era a tônica indica:",
                      { "modulação", "erro", "empréstimo", "fim da música" }, 0),
        };
        add (exercise ("EX-10.E.2", juce::String::fromUTF8 ("Tocar a modulação de Dó para Fá"),
                       juce::String::fromUTF8 ("Tocar C7M – Gm7 – C7 – F7M: um ii–V do novo tom (Fá)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere a progressão de modulação.")), "E");
        m.exercises.back().chordProgression = {
            { 0, 4, 7, 11 },   // C7M
            { 7, 10, 2, 5 },   // Gm7
            { 0, 4, 7, 10 },   // C7
            { 5, 9, 0, 4 },    // F7M
        };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-10.E.3", juce::String::fromUTF8 ("Tocar o empréstimo modal"),
                       juce::String::fromUTF8 ("Tocar C7M – Fm7 – C7M: o Fm7 é o iv emprestado do menor paralelo."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere o empréstimo modal.")), "E");
        m.exercises.back().chordProgression = {
            { 0, 4, 7, 11 },   // C7M
            { 5, 8, 0, 3 },    // Fm7
            { 0, 4, 7, 11 },   // C7M
        };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-10.E.4", juce::String::fromUTF8 ("Questionário: empréstimo e modulação"),
                       juce::String::fromUTF8 ("Distinguir empréstimo modal de modulação."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário.")), "E");
        m.exercises.back().quiz = {
            question ("Em Dó maior, o acorde Fm7 é:",
                      { "empréstimo modal (iv do menor)", "modulação para Fá", "o V", "o ii" }, 0),
            question ("A diferença entre empréstimo modal e modulação é:",
                      { "o empréstimo não muda o centro; a modulação sim",
                        "o empréstimo é mais rápido",
                        "a modulação não tem acordes",
                        "são a mesma coisa" }, 0),
            question ("Um acorde-pivo funcional em Dó e Fá é:",
                      { "Dm7 (ii de Dó, vi de Fá)", "G7", "C#7", "Bdim" }, 0),
            question ("Modular para um tom vizinho (uma quinta) é:",
                      { "mais fácil: os campos se sobrepõem muito",
                        "impossível",
                        "igual a modular para longe",
                        "sempre um erro" }, 0),
        };

        // --- Topic F — vozes internas ----------------------------------------
        add (exercise ("EX-10.F.1", juce::String::fromUTF8 ("Questionário: vozes internas"),
                       juce::String::fromUTF8 ("Responder ao questionário de condução de vozes."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "F");
        m.exercises.back().quiz = {
            question ("Conduzir vozes é:",
                      { "mover cada voz pelo caminho mais curto",
                        "tocar todas as vozes juntas",
                        "aumentar o volume",
                        "tocar mais rápido" }, 0),
            question ("As quatro vozes são:",
                      { "soprano, contralto, tenor e baixo",
                        "primeira, segunda, terceira e quarta",
                        "aguda, média, grave e mais grave",
                        "melodia, harmonia, baixo e ritmo" }, 0),
            question ("Quando dois acordes têm uma nota comum, ela deve:",
                      { "ficar parada na mesma voz", "subir uma oitava", "ser omitida", "ser duplicada" }, 0),
            question ("Inverter um acorde muda:",
                      { "a nota do baixo", "as notas do acorde", "a tonalidade", "o número de notas" }, 0),
            question ("Na guitarra, a condução de vozes é mais fácil com:",
                      { "acordes de poucas notas (shell voicings)", "acordes de seis cordas", "power chords", "só o baixo" }, 0),
        };
        add (exercise ("EX-10.F.2", juce::String::fromUTF8 ("Conduzir as vozes num ii–V–I"),
                       juce::String::fromUTF8 ("Tocar Dm7 – G7 – C7M mantendo a nota F comum entre Dm7 e G7."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere a progressão com a nota comum.")), "F");
        m.exercises.back().chordProgression = {
            { 2, 5, 9, 0 },    // Dm7 (com F)
            { 7, 11, 2, 5 },   // G7 (com F)
            { 0, 4, 7, 11 },   // C7M
        };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-10.F.3", juce::String::fromUTF8 ("Tocar um shell voicing"),
                       juce::String::fromUTF8 ("Tocar C7M com três notas (C, E, B), deixando a quinta de fora para conduzir as vozes."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere o shell voicing (tônica, terça, sétima).")), "F");
        m.exercises.back().chordPitchClasses = { 0, 4, 11 };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-10.F.4", juce::String::fromUTF8 ("Questionário: inversões e baixo"),
                       juce::String::fromUTF8 ("Identificar a nota do baixo nas inversões."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário.")), "F");
        m.exercises.back().quiz = {
            question ("Na primeira inversão (C/E), a nota do baixo é:",
                      { "E (terça)", "C (tônica)", "G (quinta)", "B (sétima)" }, 0),
            question ("Na segunda inversão (C/G), a nota do baixo é:",
                      { "G (quinta)", "C (tônica)", "E (terça)", "B (sétima)" }, 0),
            question ("Conduzir o baixo por graus próximos serve para:",
                      { "dar fluidez à harmonia", "aumentar o volume", "mudar o tom", "tocar mais rápido" }, 0),
            question ("Movimento oblíquo entre vozes significa:",
                      { "uma voz fica parada enquanto as outras se movem",
                        "todas as vozes sobem",
                        "todas as vozes descem",
                        "as vozes se cruzam" }, 0),
        };

        // --- Topic G — reharmonização ----------------------------------------
        add (exercise ("EX-10.G.1", juce::String::fromUTF8 ("Questionário: reharmonização"),
                       juce::String::fromUTF8 ("Responder ao questionário de reharmonização."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "G");
        m.exercises.back().quiz = {
            question ("Reharmonizar é:",
                      { "trocar a harmonia mantendo a melodia",
                        "trocar a melodia",
                        "mudar o andamento",
                        "afinar o instrumento" }, 0),
            question ("A substituição de trítono de G7 é:",
                      { "Db7", "D7", "C7", "A7" }, 0),
            question ("Reharmonizar sem olhar a melodia pode causar:",
                      { "atrito entre a melodia e os novos acordes",
                        "melhora automática",
                        "mudança de tom",
                        "aumento do volume" }, 0),
            question ("O substituto relativo de C7M é:",
                      { "Am7", "G7", "Dm7", "Fm7" }, 0),
            question ("Reharmonizar com parcimônia serve para:",
                      { "manter a identidade da música", "tocar mais rápido", "mudar de tom", "simplificar tudo" }, 0),
        };
        add (exercise ("EX-10.G.2", juce::String::fromUTF8 ("Reharmonizar com o subV"),
                       juce::String::fromUTF8 ("Tocar Dm7 – Db7 – C7M: o Db7 substitui o G7 (substituição de trítono)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere a progressão com o subV.")), "G");
        m.exercises.back().chordProgression = {
            { 2, 5, 9, 0 },    // Dm7
            { 1, 5, 8, 11 },   // Db7
            { 0, 4, 7, 11 },   // C7M
        };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-10.G.3", juce::String::fromUTF8 ("Reharmonizar com dominante secundário"),
                       juce::String::fromUTF8 ("Tocar C7M – A7 – Dm7 – G7 – C7M: o A7 prepara o ii (Dm7)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere a progressão com o dominante secundário.")), "G");
        m.exercises.back().chordProgression = {
            { 0, 4, 7, 11 },   // C7M
            { 9, 1, 4, 7 },    // A7
            { 2, 5, 9, 0 },    // Dm7
            { 7, 11, 2, 5 },   // G7
            { 0, 4, 7, 11 },   // C7M
        };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-10.G.4", juce::String::fromUTF8 ("Reharmonizar com empréstimo modal"),
                       juce::String::fromUTF8 ("Tocar C7M – Fm7 – C7M, escurecendo a tônica com o iv emprestado."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere a reharmonização por empréstimo.")), "G");
        m.exercises.back().chordProgression = {
            { 0, 4, 7, 11 },   // C7M
            { 5, 8, 0, 3 },    // Fm7
            { 0, 4, 7, 11 },   // C7M
        };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-10.G.5", juce::String::fromUTF8 ("Questionário: técnicas de reharmonização"),
                       juce::String::fromUTF8 ("Identificar a técnica usada em cada reharmonização."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário.")), "G");
        m.exercises.back().quiz = {
            question ("Trocar G7 por Db7 é:",
                      { "substituição de trítono", "empréstimo modal", "relativo", "modulação" }, 0),
            question ("Trocar C7M por Cm7 é:",
                      { "empréstimo modal (paralelo)", "substituição de trítono", "dominante secundário", "inversão" }, 0),
            question ("Inserir um Bm7b5 entre C7M e Dm7 é:",
                      { "acorde de passagem", "modulação", "substituição de trítono", "relativo" }, 0),
            question ("A melodia é, na reharmonização:",
                      { "a restrição que não pode ser quebrada", "opcional", "sempre substituída", "irrelevante" }, 0),
        };

        // --- Topic H — harmonia-alvo -----------------------------------------
        add (exercise ("EX-10.H.1", juce::String::fromUTF8 ("Questionário: harmonia-alvo"),
                       juce::String::fromUTF8 ("Responder ao questionário de harmonia-alvo."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "H");
        m.exercises.back().quiz = {
            question ("O alvo de uma frase é:",
                      { "o acorde de chegada (o repouso)", "o primeiro acorde", "o acorde mais agudo", "o mais rápido" }, 0),
            question ("Construir a harmonia-alvo é trabalhar:",
                      { "de trás para frente, do alvo para as aproximações",
                        "do começo para o fim",
                        "sem ordem",
                        "só pelo baixo" }, 0),
            question ("Antes de um alvo C7M, um subV seria:",
                      { "Db7", "G7", "D7", "B7" }, 0),
            question ("O alvo é revelado, muitas vezes, por:",
                      { "onde a melodia repousa", "o volume", "o andamento", "o timbre" }, 0),
            question ("Aproximações diferentes do mesmo alvo produzem:",
                      { "cores diferentes na chegada", "o mesmo som", "erros", "modulações" }, 0),
        };
        add (exercise ("EX-10.H.2", juce::String::fromUTF8 ("Construir a aproximação do alvo"),
                       juce::String::fromUTF8 ("Tocar Em7b5 – A7 – Dm7 – G7 – C7M: uma cadência construída de trás para frente até o alvo."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere a progressão que chega ao alvo C7M.")), "H");
        m.exercises.back().chordProgression = {
            { 4, 7, 10, 2 },   // Em7b5
            { 9, 1, 4, 7 },    // A7
            { 2, 5, 9, 0 },    // Dm7
            { 7, 11, 2, 5 },   // G7
            { 0, 4, 7, 11 },   // C7M
        };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-10.H.3", juce::String::fromUTF8 ("Chegar ao alvo por subV"),
                       juce::String::fromUTF8 ("Tocar Dm7 – Db7 – C7M, chegando ao alvo com baixo cromático."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere a chegada ao alvo por subV.")), "H");
        m.exercises.back().chordProgression = {
            { 2, 5, 9, 0 },    // Dm7
            { 1, 5, 8, 11 },   // Db7
            { 0, 4, 7, 11 },   // C7M
        };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-10.H.4", juce::String::fromUTF8 ("Questionário: alvos na forma"),
                       juce::String::fromUTF8 ("Identificar os alvos de uma forma AABA."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário.")), "H");
        m.exercises.back().quiz = {
            question ("Numa forma AABA, cada seção tem:",
                      { "um alvo (ponto de chegada)", "um único acorde", "a mesma melodia", "nenhum acorde" }, 0),
            question ("O turnaround serve para:",
                      { "levar a música de volta ao alvo do início", "encerrar a música", "modular", "mudar o andamento" }, 0),
            question ("Improvisar pensando no alvo faz a frase:",
                      { "ter direção e contar uma história", "ficar mais rápida", "perder a tonalidade", "repetir notas" }, 0),
            question ("O alvo deve conter:",
                      { "a nota de repouso da melodia", "a nota mais aguda", "só a fundamental", "qualquer nota" }, 0),
        };

        // --- Topic I — ferramentas de reharmonização -------------------------
        add (exercise ("EX-10.I.1", juce::String::fromUTF8 ("Questionário: ferramentas de reharmonização"),
                       juce::String::fromUTF8 ("Responder ao questionário das ferramentas."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "I");
        m.exercises.back().quiz = {
            question ("Qual ferramenta cria um baixo cromático?",
                      { "substituição de trítono", "empréstimo modal", "relativo", "inversão" }, 0),
            question ("Para criar movimento antes de cada acorde, use:",
                      { "dominantes secundários", "relativos", "power chords", "oitavas" }, 0),
            question ("Para escurecer a harmonia sem modular, use:",
                      { "empréstimo modal", "substituição de trítono", "inversão", "power chords" }, 0),
            question ("Para garantir que a melodia caiba na harmonia, use:",
                      { "verticalização", "empréstimo modal", "modulação", "baixo pedal" }, 0),
            question ("Usar todas as ferramentas ao mesmo tempo:",
                      { "faz a harmonia perder a identidade", "melhora a música", "é obrigatório", "não tem efeito" }, 0),
        };
        add (exercise ("EX-10.I.2", juce::String::fromUTF8 ("Combinar ferramentas"),
                       juce::String::fromUTF8 ("Tocar C7M – A7 – Dm7 – Db7 – C7M: dominante secundário e subV combinados."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere a progressão reharmonizada.")), "I");
        m.exercises.back().chordProgression = {
            { 0, 4, 7, 11 },   // C7M
            { 9, 1, 4, 7 },    // A7
            { 2, 5, 9, 0 },    // Dm7
            { 1, 5, 8, 11 },   // Db7
            { 0, 4, 7, 11 },   // C7M
        };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-10.I.3", juce::String::fromUTF8 ("Ferramenta com baixo pedal"),
                       juce::String::fromUTF8 ("Tocar C7M – Fm7 – C7M mantendo a intenção de baixo pedal (suspensão)."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere a progressão com o empréstimo.")), "I");
        m.exercises.back().chordProgression = {
            { 0, 4, 7, 11 },   // C7M
            { 5, 8, 0, 3 },    // Fm7
            { 0, 4, 7, 11 },   // C7M
        };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-10.I.4", juce::String::fromUTF8 ("Questionário: escolher a ferramenta"),
                       juce::String::fromUTF8 ("Associar cada efeito desejado à ferramenta certa."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário.")), "I");
        m.exercises.back().quiz = {
            question ("Efeito desejado: suavidade e fluidez. Ferramenta:",
                      { "relativos, inversões e condução de vozes", "substituição de trítono", "dominante secundário", "baixo pedal" }, 0),
            question ("Efeito desejado: tensão suspensa. Ferramenta:",
                      { "baixo pedal", "relativo", "inversão", "oitavas" }, 0),
            question ("Efeito desejado: mais movimento. Ferramenta:",
                      { "dominantes secundários e acordes de passagem", "relativo", "inversão", "empréstimo modal" }, 0),
            question ("A restrição final de toda reharmonização é:",
                      { "a melodia", "o andamento", "o timbre", "o volume" }, 0),
        };

        // --- Topic J — estilos e sonoridades ---------------------------------
        add (exercise ("EX-10.J.1", juce::String::fromUTF8 ("Questionário: estilos e sonoridades"),
                       juce::String::fromUTF8 ("Responder ao questionário de estilos."),
                       juce::String::fromUTF8 ("Acerto ≥90% nas questões.")), "J");
        m.exercises.back().quiz = {
            question ("A análise harmônica, entre estilos, é:",
                      { "a mesma; o que muda é a sonoridade", "sempre diferente", "irrelevante", "impossível" }, 0),
            question ("Qual estilo usa mais densidade harmônica (9, 13)?",
                      { "bossa nova", "rock", "blues", "punk" }, 0),
            question ("Qual estilo usa tríades e power chords?",
                      { "rock / pop", "jazz", "bossa nova", "bebop" }, 0),
            question ("As blue notes são típicas do:",
                      { "blues", "rock progressivo", "bossa nova", "clássico" }, 0),
            question ("Cada estilo tem:",
                      { "convenções próprias de reharmonização", "a mesma reharmonização", "nenhuma harmonia", "só tríades" }, 0),
        };
        add (exercise ("EX-10.J.2", juce::String::fromUTF8 ("Tocar o ii–V–I em estilo de bossa"),
                       juce::String::fromUTF8 ("Tocar Dm7 – G7 – C7M com nonas (Dm9 – G9 – C7M9), sonoridade de bossa."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere os acordes com tensão de bossa.")), "J");
        m.exercises.back().chordProgression = {
            { 2, 5, 9, 0, 4 },    // Dm9
            { 7, 11, 2, 5, 9 },   // G9
            { 0, 4, 7, 11, 2 },   // C7M9
        };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-10.J.3", juce::String::fromUTF8 ("Tocar o ii–V–I em estilo de rock"),
                       juce::String::fromUTF8 ("Tocar Dm – G – C com tríades (sem sétimas), sonoridade de rock."),
                       juce::String::fromUTF8 ("O app reconhece as notas e confere as tríades do ii–V–I.")), "J");
        m.exercises.back().chordProgression = {
            { 2, 5, 9 },    // Dm
            { 7, 11, 2 },   // G
            { 0, 4, 7 },    // C
        };
        m.exercises.back().usesGrid = false;
        add (exercise ("EX-10.J.4", juce::String::fromUTF8 ("Questionário: vestir a mesma estrutura"),
                       juce::String::fromUTF8 ("Identificar como cada estilo veste o mesmo ii–V–I."),
                       juce::String::fromUTF8 ("Acerto ≥90% no questionário.")), "J");
        m.exercises.back().quiz = {
            question ("O mesmo ii–V–I em blues tende a virar:",
                      { "dominantes com sétima e blue notes", "tríades limpas", "acordes sus", "só o baixo" }, 0),
            question ("O ii–V–I em jazz costuma trazer:",
                      { "substituições e tensões alteradas", "power chords", "só a fundamental", "nenhuma tensão" }, 0),
            question ("A sonoridade também depende de:",
                      { "instrumentação, timbre e ataque", "apenas dos acordes", "só do andamento", "só da tonalidade" }, 0),
            question ("Reharmonizar fora do estilo da música pode:",
                      { "soar deslocado", "sempre melhorar", "não ter efeito", "mudar o tom" }, 0),
        };

        // The gate closes the module: reharmonise a ii–V–I with a secondary
        // dominant and a tritone substitution, ending on the target (REQ-009,
        // REQ-015). Built from the module's material.
        auto& gate = m.exercises.emplace_back (exercise (
            "GATE-10", juce::String::fromUTF8 ("Desafio de gate — ii–V–I reharmonizado"),
            juce::String::fromUTF8 ("Tocar Dm7 – A7 – Dm7 – Db7 – C7M a 96 BPM, na grade do metrônomo: um ii–V–I com dominante secundário e subV."),
            juce::String::fromUTF8 ("Acordes reconhecidos e alinhados à grade (≥ 0,82).")));
        gate.isGate = true;
        gate.lessonId = "J";
        gate.chordProgression = {
            { 2, 5, 9, 0 },    // Dm7
            { 9, 1, 4, 7 },    // A7 (dominante secundário)
            { 2, 5, 9, 0 },    // Dm7
            { 1, 5, 8, 11 },   // Db7 (subV)
            { 0, 4, 7, 11 },   // C7M (alvo)
        };

        m.gateChallenge = juce::String::fromUTF8 (
            "Reharmonizar e tocar Dm7 – A7 – Dm7 – Db7 – C7M (um ii–V–I com "
            "dominante secundário e substituição de trítono) a 96 BPM, com ≥90% "
            "de acerto de acordes e on_grid_ratio ≥ 0,82. A progressão usa as "
            "ferramentas de reharmonização estudadas no módulo.");

        // Pattern and link the module must cite (REQ-007, REQ-010).
        m.practice.patternId = "PTN-A-DROP2";
        m.practice.patternUse = juce::String::fromUTF8 (
            "Arpejos de sétima em Drop 2: a digitação fixa 1-3-5-7 permite ouvir "
            "cada voz do acorde separadamente, o que é a base da condução de vozes "
            "e da verticalização. Complemento: PTN-M-3rds para ouvir os intervalos "
            "do acorde em movimento.");
        m.practice.guitarists = { "Joe Pass", "Wes Montgomery", "Chick Corea" };

        // Curated apostilas (REQ-006, CM-012); see docs/MUSIC.md.
        m.sources = {
            "pdf-teoria-elementar-da-musica-ricordi-osvaldo-lacerda",
            "pdf-p-classtruncatedtext-module-lineclamped-85ulhh-style-max-lines5bohumil-med-teoria-da-musica-5-edicao-p",
            "pdf-desvendando-os-segredos-da-guitarra-fusion",
            "pdf-caged-e-derivaoes-de-acordes-marcelo-mello-apostila-de-violao-e-guitarra-vol1",
        };

        return m;
    }

    // Module 11 (Etapa 11 — referências de escalas e domínio do braço). The
    // module turns scale knowledge into phrase references: every topic teaches a
    // lick, and the topic's exercises oblige the student to play it. It is the
    // first module with improvisation evaluation (REQ-011/REQ-012): the rest
    // notes are the chord/scale tones of the vamp, and a tension outside the
    // centre is an error. Module 11 has no quizzes — every exercise is played.
    std::vector<int> midiOf (std::initializer_list<const char*> names)
    {
        std::vector<int> out;
        for (auto* name : names)
            out.push_back (music::noteNameToMidi (juce::String (name)));
        return out;
    }

    CourseModule makeModule11()
    {
        CourseModule m;
        m.number = 11;
        m.title = juce::String::fromUTF8 ("Referências de escalas e domínio do braço");
        m.objective = juce::String::fromUTF8 (
            "Transformar o conhecimento das escalas em referências para a construção "
            "de frases: desenhos, trilhas, pentatônicas, Sistema 5, menores harmônica "
            "e melódica, e a relação entre escalas e acordes que sustenta o improviso.");
        m.level = 5;          // MUSIC.md: módulos 11–14 = nível 5 (blues)
        m.targetBpm = 100;    // MUSIC.md, módulo 11
        m.onGridTarget = 0.82f;
        m.implemented = true;

        m.lessons = {
            detail (block ("A", juce::String::fromUTF8 ("Desenhos de escalas por regiões"), {
                "Uma região é um trecho de 4–5 casas onde a escala cabe sob os quatro dedos.",
                "O desenho é a escala com uma forma fixa; a forma é o vocabulário motor da frase.",
                "Frases nascem numa região, viajam pela nota comum e voltam para resolver."
            }), content::topic11A()),
            detail (block ("B", juce::String::fromUTF8 ("Escalas ascendentes e descendentes"), {
                "A escala nos dois sentidos é o alicerce da fluência; a descida é onde o aluno trava.",
                "Subir e descer pedem digitações diferentes, escolhidas pelo conforto da mão.",
                "A escala parelha no metrônomo é o termômetro da mão antes da frase."
            }), content::topic11B()),
            detail (block ("C", juce::String::fromUTF8 ("Pentatônica menor 7"), {
                "A pentatônica menor 7 é a pentatônica menor de sempre: 1-b3-4-5-b7 (cinco notas).",
                "O 7 do nome é a sétima menor (b7), que já pertence à escala e dá o som do acorde m7.",
                "Sobre m7, as cinco notas são de repouso: a apostila é a fonte primária."
            }), content::topic11C()),
            detail (block ("D", juce::String::fromUTF8 ("Pentatônica menor 6"), {
                "A pentatônica menor 6 troca a sétima menor pela sexta maior: 1-b3-4-5-6 (cinco notas).",
                "O 6 do nome é a sexta maior, que dá o som do acorde m6 (cor dórica).",
                "Sobre m6, use a menor 6; sobre m7, use a menor 7 — o acorde decide a pentatônica."
            }), content::topic11D()),
            detail (block ("E", juce::String::fromUTF8 ("Cinco desenhos da pentatônica"), {
                "São cinco posições porque a pentatônica tem cinco notas por oitava.",
                "Posições vizinhas compartilham notas nas cordas de fronteira.",
                "A posição 5 (casa 12) é a posição 1 uma oitava acima; juntas cobrem o braço."
            }), content::topic11E()),
            detail (block ("F", juce::String::fromUTF8 ("Trilhas abertas e fechadas"), {
                "Trilha fechada: a escala dentro da posição, mão parada, sem cordas soltas.",
                "Trilha aberta: a escala ao longo de uma ou duas cordas, mão viajando pelo braço.",
                "O fraseado maduro alterna as duas: controle na caixa, movimento na corda."
            }), content::topic11F()),
            detail (block ("G", juce::String::fromUTF8 ("Sistema 5 (CAGED)"), {
                "Cinco formas de acorde (C-A-G-E-D), cada uma com um desenho de escala ao redor.",
                "Cada forma é uma região; a tônica da forma é o alvo da frase.",
                "Trocar de acorde é trocar de forma: o solo segue a harmonia pelo braço."
            }), content::topic11G()),
            detail (block ("H", juce::String::fromUTF8 ("Escala menor harmônica"), {
                "Menor harmônica: a menor natural com o 7º grau elevado (1-2-b3-4-5-b6-7).",
                "A elevação do 7º cria a segunda aumentada, a marca sonora da escala.",
                "O 5º grau vira dominante: a escala dá à frase menor uma resolução forte."
            }), content::topic11H()),
            detail (block ("I", juce::String::fromUTF8 ("Escala menor melódica"), {
                "Menor melódica: a menor natural com o 6º e o 7º graus elevados (1-2-b3-4-5-6-7).",
                "Elevar o 6º grau elimina a segunda aumentada: a escala sobe por graus conjuntos.",
                "É a escala menor cantável; serve à melodia, como a harmônica serve à harmonia."
            }), content::topic11I()),
            detail (block ("J", juce::String::fromUTF8 ("Relação entre escalas e acordes"), {
                "A escala vem do acorde: 7M pede maior/lídia; m7 pede menor/dórica; 7 pede mixolídia.",
                "A escala escolhida define as notas de repouso (acorde e escala) da frase.",
                "Fora do centro, a nota é tensão não pedida — erro (REQ-012)."
            }), content::topic11J()),
        };

        // One lick per topic (client: "cada tópico deve ter um lick"). The topic's
        // exercise obliges the student to play it. Notes match the audio and the
        // score drawn in tools/make_diagrams.py.
        auto lick = [&m] (const char* id, const char* title, const char* guitarist,
                          const char* patternId, const char* tab, const char* source,
                          std::initializer_list<const char*> noteNames)
        {
            Lick l;
            l.id = id;
            l.title = juce::String::fromUTF8 (title);
            l.guitarist = guitarist;
            l.patternId = patternId;
            l.tab = juce::String::fromUTF8 (tab);
            l.source = source;
            l.notes = midiOf (noteNames);
            l.referenceExcerptPending = true; // excerpt (time range) pending, AGENTS.md §10
            m.licks.push_back (std::move (l));
            return l.id;
        };

        // Representative listening (client request, 2026-11-18, Decision A): a
        // real song where the cited player uses the same scale/gesture — similar
        // vocabulary, never the same phrase, since the lick is an original
        // phrase of the course. Song, album and year are verified; the exact
        // excerpt (time range) is still pending (docs/MUSIC.md §11.5).
        auto listen = [&m] (const char* lickId, const char* song, const char* note)
        {
            for (auto& l : m.licks)
                if (l.id == lickId)
                {
                    l.referenceSong = juce::String::fromUTF8 (song);
                    l.referenceNote = juce::String::fromUTF8 (note);
                }
        };

        lick ("LK-11.A", "Grupos de três subindo na região", "John Petrucci", "PTN-M-3",
              "e|--5-7-8-7-8-10-8-10-12-10-12-13-12-13-15-13-15-17--|", "pdf-fraseado-melodico",
              { "A4", "B4", "C5", "B4", "C5", "D5", "C5", "D5", "E5", "D5", "E5", "F5", "E5", "F5", "G5", "F5", "G5", "A5" });
        lick ("LK-11.B", "Escala ascendente e descendente", "Guthrie Govan", "PTN-M-SCALE",
              "e|--5-7-8-10-12-13-15-17-15-13-12-10-8-7-5--|", "pdf-fraseado-melodico",
              { "A4", "B4", "C5", "D5", "E5", "F5", "G5", "A5", "G5", "F5", "E5", "D5", "C5", "B4", "A4" });
        lick ("LK-11.C", "Pentatônica menor 7 (a sétima menor)", "Richie Kotzen", "PTN-M-SCALE",
              "e|--5-8-10-12-15-17-15-12-10-8-5--|", "pdf-desvendando-os-segredos-da-guitarra-fusion",
              { "A4", "C5", "D5", "E5", "G5", "A5", "G5", "E5", "D5", "C5", "A4" });
        lick ("LK-11.D", "Pentatônica menor 6 (a sexta como cor)", "Greg Howe", "PTN-M-SCALE",
              "e|--5-8-10-12-14-12-10-8-5--|", "pdf-mozart-mello-improvisacion-pop",
              { "A4", "C5", "D5", "E5", "F#5", "E5", "D5", "C5", "A4" });
        lick ("LK-11.E", "Pentatônica ligando duas posições", "Edu Ardanuy", "PTN-M-SCALE",
              "e|--5-8-10-12-15-17-15-12-10-8-5--|", "pdf-mozart-mello-livroestudosdeguitarra4em1",
              { "A4", "C5", "D5", "E5", "G5", "A5", "G5", "E5", "D5", "C5", "A4" });
        lick ("LK-11.F", "Trilha aberta na 3ª corda", "Joe Satriani", "PTN-M-SCALE",
              "G|--0-2-4-5-7-9-10-12-14--|", "pdf-fraseado-melodico",
              { "G3", "A3", "B3", "C4", "D4", "E4", "F4", "G4", "A4" });
        lick ("LK-11.G", "Escala dentro da forma (Sistema 5)", "Kiko Loureiro", "PTN-M-SCALE",
              "e|--5-8-10-12-13-15-17-15-12-8-5--|", "pdf-caged-e-derivaoes-de-acordes-marcelo-mello-apostila-de-violao-e-guitarra-vol1",
              { "A4", "C5", "D5", "E5", "F5", "G5", "A5", "G5", "E5", "C5", "A4" });
        lick ("LK-11.H", "Menor harmônica (segunda aumentada)", "Yngwie Malmsteen", "PTN-M-SCALE",
              "e|--5-7-8-10-12-13-16-17-16-13-12-10-8-7-5--|", "pdf-fraseado-melodico",
              { "A4", "B4", "C5", "D5", "E5", "F5", "G#5", "A5", "G#5", "F5", "E5", "D5", "C5", "B4", "A4" });
        lick ("LK-11.I", "Menor melódica (6ª e 7ª elevadas)", "Steve Vai", "PTN-M-SCALE",
              "e|--5-7-8-10-12-14-16-17-16-14-12-10-8-7-5--|", "pdf-fraseado-melodico",
              { "A4", "B4", "C5", "D5", "E5", "F#5", "G#5", "A5", "G#5", "F#5", "E5", "D5", "C5", "B4", "A4" });
        lick ("LK-11.J", "Frase de repouso e tensão sobre o vamp", "Santana", "PTN-M-REST",
              "e|--5-8-10-13-10-8-5-12-10-8-5--|", "pdf-mozart-mello-improvisacion-pop",
              { "A4", "C5", "D5", "F5", "D5", "C5", "A4", "E5", "D5", "C5", "A4" });

        // Listening references (client request, 2026-11-18). Each song is a real
        // recording, verified track/album/year, where the cited player uses the
        // same vocabulary as the topic's lick — never the lick itself, which is
        // original. The UI labels each as "mesmo vocabulário, não a mesma frase"
        // while the exact excerpt is unmapped (AGENTS.md §10, MUSIC.md §11.5).
        listen ("LK-11.A", "Dream Theater — \"Under a Glass Moon\" (Images and Words, 1992)",
                "Sequências de grupos de três subindo a escala; mesmo desenho, frase diferente.");
        listen ("LK-11.B", "Guthrie Govan — \"Waves\" (Erotic Cakes, 2006)",
                "Corridas ascendentes e descendentes na mesma posição; mesmo vocabulário, frase diferente.");
        listen ("LK-11.C", "Richie Kotzen — \"Mother Head's Family Reunion\" (1994)",
                "Pentatônica menor usada como base melódica sobre acorde m7; mesmo vocabulário, frase diferente.");
        listen ("LK-11.D", "Greg Howe — \"Jump Start\" (Introspection, 1993)",
                "Pentatônica com a sexta maior como cor sobre acorde menor; mesmo vocabulário, frase diferente.");
        listen ("LK-11.E", "Edu Ardanuy (Dr. Sin) — \"Dr. Sin\" (Dr. Sin, 1993)",
                "Pentatônica ligando posições vizinhas pela nota comum; mesmo vocabulário, frase diferente.");
        listen ("LK-11.F", "Joe Satriani — \"Flying in a Blue Dream\" (1989)",
                "Linhas longas ao longo de uma corda, com a mão viajando pelo braço; mesmo vocabulário, frase diferente.");
        listen ("LK-11.G", "Kiko Loureiro — \"No Gravity\" (No Gravity, 2005)",
                "Escala desenhada dentro da forma do acorde (Sistema 5); mesmo vocabulário, frase diferente.");
        listen ("LK-11.H", "Yngwie Malmsteen — \"Far Beyond the Sun\" (Rising Force, 1984)",
                "Corridas ascendentes na menor harmônica, com a segunda aumentada; mesmo vocabulário, frase diferente.");
        listen ("LK-11.I", "Steve Vai — \"For the Love of God\" (Passion and Warfare, 1990)",
                "Linhas cantáveis com a sexta e a sétima elevadas (menor melódica); mesmo vocabulário, frase diferente.");
        listen ("LK-11.J", "Santana — \"Black Magic Woman / Gypsy Queen\" (Abraxas, 1970)",
                "Frases que alternam repouso no acorde e tensão de cor; mesmo vocabulário, frase diferente.");

        auto add = [&m] (Exercise e) { m.exercises.push_back (std::move (e)); return (int) m.exercises.size() - 1; };

        // --- Harmonic programme of the improvisation track -------------------
        // docs/MUSIC.md, "Programa de estudo de improvisação" (Etapa 11).
        //
        // Central rule of the programme: no exercise runs on a bare scale. Every
        // exercise declares the bed it plays over (`bedModelId`), the cadence the
        // topic teaches (`cadenceId`) and its harmonic level (`harmonicLevel`).
        // The three exercises of a topic walk P1 -> P2 -> P3: control over a
        // static centre, connection across two chords, integration over a form.
        auto bedOf = [] (const char* code) -> const course::harmony::BackingModelDef&
        {
            if (auto* found = course::harmony::findModel (juce::String (code)))
                return *found;

            static const course::harmony::BackingModelDef none { "H0", "sem base", {}, {}, false };
            return none;
        };

        auto declareBed = [bedOf] (Exercise e, const char* modelCode, const char* cadenceCode, int level)
        {
            e.bedModelId = modelCode;
            e.cadenceId = cadenceCode;
            e.harmonicLevel = level;
            e.harmony = course::harmony::timelineFor (bedOf (modelCode));
            return e;
        };

        auto lickNotes = [&m] (const char* lickId)
        {
            for (const auto& l : m.licks)
                if (l.id == juce::String (lickId))
                    return l.notes;
            return std::vector<int> {};
        };

        // Exercise A — recognition and control (P1): the topic's lick, which the
        // exercise obliges, played over a static centre.
        // The scale the topic teaches, when it is not the one the chord
        // would suggest (the module's centre is A minor, so its licks use the
        // natural minor over the m7 vamp). The declaration wins over the
        // chord-scale default: the app must expect what the lesson teaches.
        auto control = [lickNotes, declareBed] (const char* id, const char* title, const char* goal,
                                                const char* lickId, const char* topic,
                                                const char* modelCode, const char* cadenceCode,
                                                std::initializer_list<int> scale = {})
        {
            auto e = exercise (id, juce::String::fromUTF8 (title), juce::String::fromUTF8 (goal),
                               juce::String::fromUTF8 ("O app reconhece as notas do lick sobre a base "
                                                       "declarada, nota a nota."));
            for (auto midi : lickNotes (lickId))
                e.targets.push_back ({ midi, music::midiToNoteName (midi) });
            e.lessonId = topic;
            e.lickId = lickId;
            auto declared = declareBed (std::move (e), modelCode, cadenceCode, 1);

            if (scale.size() > 0)
                for (auto& segment : declared.harmony)
                    segment.context.scalePitchClasses = std::vector<int> (scale);

            return declared;
        };

        // Exercise B — application and connection (P2): the arpeggios of the bed,
        // chord by chord. The expected notes *are* the harmony, so the student
        // has to move the target when the chord changes.
        auto connection = [declareBed, bedOf] (const char* id, const char* title, const char* goal,
                                        const char* topic, const char* modelCode, const char* cadenceCode)
        {
            auto e = exercise (id, juce::String::fromUTF8 (title), juce::String::fromUTF8 (goal),
                               juce::String::fromUTF8 ("O app confere as notas do arpejo de cada acorde "
                                                       "da base, na ordem em que a harmonia muda."));
            e.lessonId = topic;

            for (const auto& chord : bedOf (modelCode).chords)
            {
                auto tones = chord.pitchClasses;
                std::sort (tones.begin(), tones.end(), [&chord] (int a, int b)
                {
                    return ((a - chord.rootPitchClass + 12) % 12)
                             < ((b - chord.rootPitchClass + 12) % 12);
                });

                for (int pc : tones)
                {
                    const int midi = 60 + chord.rootPitchClass
                                       + ((pc - chord.rootPitchClass + 12) % 12);
                    e.targets.push_back ({ midi, music::midiToNoteName (midi) });
                }
            }

            return declareBed (std::move (e), modelCode, cadenceCode, 2);
        };

        // Exercise C — integration and autonomy (P3): free improvisation over the
        // declared form. Each note is judged against the chord in force when it
        // sounded, so following the changes passes and ignoring them does not.
        auto integration = [declareBed] (const char* id, const char* title, const char* goal,
                                         const char* topic, const char* modelCode, const char* cadenceCode)
        {
            auto e = exercise (id, juce::String::fromUTF8 (title), juce::String::fromUTF8 (goal),
                               juce::String::fromUTF8 ("O app classifica cada nota tocada contra o "
                                                       "acorde em vigor: repouso (acorde ou escala), "
                                                       "tensão pedida, passagem cromática ou erro."));
            e.lessonId = topic;
            e.usesGrid = false;   // graded by note role against the form, not by the grid
            auto declared = declareBed (std::move (e), modelCode, cadenceCode, 3);

            // The opening context is also the single-chord fallback; the form
            // itself (declared above) is what the attempt is graded against.
            if (! declared.harmony.empty())
                declared.restNotes = declared.harmony.front().context;

            return declared;
        };

        // --- Topic A — desenhos por regiões (11.1) ---------------------------
        add (control ("EX-11.A.1", "Tocar o lick A sobre o vamp (controle)",
                      "Tocar o lick do tópico — grupos de três subindo dentro de uma região — sobre o vamp de Am7 (H1). "
                      "O centro é estático: o trabalho é de reconhecimento e controle, sem mudança de acorde.",
                      "LK-11.A", "A", "H1", "C02", { 9, 11, 0, 2, 4, 5, 7 }));
        add (connection ("EX-11.A.2", "Arpejos de Am7 e D7 (conexão)",
                         "Tocar o arpejo de cada acorde da base H5 (Am7 – D7), na ordem em que a harmonia muda: "
                         "a nota-alvo tem de acompanhar o acorde, não ficar na posição.",
                         "A", "H5", "C16"));
        add (integration ("EX-11.A.3", "Improvisar sobre a célula Am7 – Fmaj7 (integração)",
                          "Improvisar sobre a célula H7 (Am7 – Fmaj7) usando os desenhos do tópico e ligando as "
                          "regiões pela nota comum; as notas de repouso mudam quando o acorde muda.",
                          "A", "H7", "C18"));

        // --- Topic B — escalas ascendentes e descendentes (11.2) -------------
        add (control ("EX-11.B.1", "Tocar o lick B sobre o vamp (controle)",
                      "Tocar o lick do tópico — a escala sobe até o topo e desce resolvendo na tônica — sobre o vamp de Am7 (H1).",
                      "LK-11.B", "B", "H1", "C02", { 9, 11, 0, 2, 4, 5, 7 }));
        add (connection ("EX-11.B.2", "Arpejos de Dm7 e G7 (conexão)",
                         "Tocar o arpejo de cada acorde da base H4 (Dm7 – G7) na ordem da harmonia: "
                         "subir e descer a escala passa a servir a duas notas-alvo diferentes.",
                         "B", "H4", "C15"));
        add (integration ("EX-11.B.3", "Improvisar sobre Cmaj7 – Fmaj7 (integração)",
                          "Improvisar sobre a célula H6 (Cmaj7 – Fmaj7) alternando movimento ascendente e "
                          "descendente, com a escala do acorde em vigor.",
                          "B", "H6", "C13"));

        // --- Topic C — pentatônica menor 7 (11.3) ----------------------------
        add (control ("EX-11.C.1", "Tocar o lick C sobre Am7 (controle)",
                      "Tocar o lick do tópico — a pentatônica menor 7 de Lá, com a sétima menor como chegada — "
                      "sobre o vamp de Am7 (H1), onde as cinco notas são de repouso.",
                      "LK-11.C", "C", "H1", "C02", { 9, 0, 2, 4, 7 }));
        add (connection ("EX-11.C.2", "Arpejos de Am7 e D7 (conexão)",
                         "Tocar o arpejo de Am7 e de D7 (base H5): a pentatônica de Lá cobre o Am7, e o D7 pede "
                         "a terça maior (F#) — a nota-alvo muda com o acorde.",
                         "C", "H5", "C16"));
        add (integration ("EX-11.C.3", "Improvisar sobre o blues menor (integração)",
                          "Improvisar sobre o blues menor de 12 compassos em Lá (H13), mantendo a pentatônica "
                          "como espinha e resolvendo em cada mudança de acorde.",
                          "C", "H13", "C10"));

        // --- Topic D — pentatônica menor 6 (11.4) ----------------------------
        add (control ("EX-11.D.1", "Tocar o lick D sobre Am7 (controle)",
                      "Tocar o lick do tópico — a pentatônica menor 6 de Lá, com a sexta maior como cor — "
                      "sobre o vamp de Am7 (H1).",
                      "LK-11.D", "D", "H1", "C02", { 9, 0, 2, 4, 6 }));
        add (connection ("EX-11.D.2", "Arpejos de Am7 e D7 (conexão)",
                         "Tocar o arpejo de Am7 e de D7 (base H5): a sexta maior (F#) é cor sobre o Am7 e "
                         "terça do D7 — a mesma nota muda de função quando o acorde muda.",
                         "D", "H5", "C16"));
        add (integration ("EX-11.D.3", "Improvisar sobre o blues maior (integração)",
                          "Improvisar sobre o blues de 12 compassos em Lá (H12): a pentatônica menor 6 funciona "
                          "sobre os dominantes e a blue note resolve na terça.",
                          "D", "H12", "C10"));

        // --- Topic E — cinco desenhos da pentatônica (11.5) ------------------
        add (control ("EX-11.E.1", "Tocar o lick E sobre o vamp (controle)",
                      "Tocar o lick do tópico — a frase atravessa a nota comum entre duas posições — sobre o vamp de Am7 (H1).",
                      "LK-11.E", "E", "H1", "C02", { 9, 0, 2, 4, 7 }));
        add (connection ("EX-11.E.2", "Arpejos de Dm7 e G7 (conexão)",
                         "Tocar o arpejo de Dm7 e de G7 (base H4) passando de uma posição da pentatônica para a "
                         "vizinha: a mão viaja enquanto a harmonia muda.",
                         "E", "H4", "C15"));
        add (integration ("EX-11.E.3", "Improvisar sobre a progressão fusion (integração)",
                          "Improvisar sobre H17 (Am9 – D13 – Gmaj9 – Cmaj9): quatro centros de cor, cada um "
                          "com a sua escala, atravessando as cinco posições.",
                          "E", "H17", "C21"));

        // --- Topic F — trilhas abertas e fechadas (11.6) ---------------------
        add (control ("EX-11.F.1", "Tocar o lick F sobre Cmaj7 (controle)",
                      "Tocar o lick do tópico — a escala sobe linearmente pela 3ª corda, trilha aberta — "
                      "sobre o vamp de Cmaj7 (H2).",
                      "LK-11.F", "F", "H2", "C02"));
        add (connection ("EX-11.F.2", "Arpejos de Dm7 e G7 (conexão)",
                         "Tocar o arpejo de Dm7 e de G7 (base H4) em trilha aberta: a mão percorre o braço "
                         "acompanhando cada acorde.",
                         "F", "H4", "C15"));
        add (integration ("EX-11.F.3", "Improvisar alternando caixa e linha (integração)",
                          "Improvisar sobre H6 (Cmaj7 – Fmaj7) alternando trilha fechada e trilha aberta, "
                          "mantendo a nota-alvo do acorde em vigor.",
                          "F", "H6", "C18"));

        // --- Topic G — Sistema 5 / CAGED (11.7) -----------------------------
        add (control ("EX-11.G.1", "Tocar o lick G dentro da forma (controle)",
                      "Tocar o lick do tópico — o desenho da escala dentro da forma do acorde, resolvendo na tônica — "
                      "sobre o vamp de Cmaj7 (H2).",
                      "LK-11.G", "G", "H2", "C01"));
        add (connection ("EX-11.G.2", "Arpejos de Cmaj7 e Fmaj7 (conexão)",
                         "Tocar o arpejo de Cmaj7 e de Fmaj7 (base H6): trocar de acorde é trocar de forma, "
                         "e a tônica da forma é a nota-alvo.",
                         "G", "H6", "C05"));
        add (integration ("EX-11.G.3", "Improvisar sobre o turnaround (integração)",
                          "Improvisar sobre o turnaround H10 (Cmaj7 – Am7 – Dm7 – G7), resolvendo cada frase "
                          "numa nota do acorde em vigor e seguindo a harmonia pelo braço.",
                          "G", "H10", "C24"));

        // --- Topic H — escala menor harmônica (11.8) ------------------------
        add (control ("EX-11.H.1", "Tocar o lick H sobre o vamp (controle)",
                      "Tocar o lick do tópico — a segunda aumentada marca a tensão e a frase resolve na tônica — "
                      "sobre o vamp de Am7 (H1).",
                      "LK-11.H", "H", "H1", "C17", { 9, 11, 0, 2, 4, 5, 8 }));
        add (connection ("EX-11.H.2", "Arpejos de Bm7(b5), E7 e Am7 (conexão)",
                         "Tocar o arpejo de cada acorde de H9 (Bm7(b5) – E7 – Am7): o ii–V–i menor é onde a "
                         "menor harmônica nasce, e a sétima elevada é a terça do dominante.",
                         "H", "H9", "C23"));
        add (integration ("EX-11.H.3", "Improvisar sobre Am – Bb – E7 (integração)",
                          "Improvisar sobre H19 (Am – Bb – E7), adaptando a escala a cada acorde e resolvendo "
                          "a segunda aumentada na tônica quando o E7 chega.",
                          "H", "H19", "C27"));

        // --- Topic I — escala menor melódica (11.9) -------------------------
        add (control ("EX-11.I.1", "Tocar o lick I sobre o vamp (controle)",
                      "Tocar o lick do tópico — a sexta e a sétima elevadas dão fluência e a frase resolve na tônica — "
                      "sobre o vamp de Am7 (H1).",
                      "LK-11.I", "I", "H1", "C06", { 9, 11, 0, 2, 4, 6, 8 }));
        add (connection ("EX-11.I.2", "Arpejos de Bm7(b5), E7 e Am7 (conexão)",
                         "Tocar o arpejo de cada acorde de H9: sobre o ii–V–i menor a menor melódica é a escala "
                         "do centro, e a nota-alvo muda a cada acorde.",
                         "I", "H9", "C23"));
        add (integration ("EX-11.I.3", "Improvisar sobre II–V–I em dois tons (integração)",
                          "Improvisar sobre H16 (Dm7 – G7 – Cmaj7 – Em7 – A7 – Dmaj7): o centro tonal muda no "
                          "meio da forma, e as notas-alvo têm de mudar com ele.",
                          "I", "H16", "C27"));

        // --- Topic J — relação entre escalas e acordes (11.10) --------------
        add (control ("EX-11.J.1", "Tocar o lick J sobre Cmaj7 (controle)",
                      "Tocar o lick do tópico — repouso no acorde e tensão de cor — sobre o vamp de Cmaj7 (H2).",
                      "LK-11.J", "J", "H2", "C01"));
        add (connection ("EX-11.J.2", "Arpejos de Am7 e D7 (conexão)",
                         "Tocar o arpejo de Am7 e de D7 (base H5): a escala vem do acorde, então a mesma nota "
                         "é repouso num acorde e tensão no outro.",
                         "J", "H5", "C16"));
        add (integration ("EX-11.J.3", "Improvisar sobre o II–V–I maior (integração)",
                          "Improvisar sobre H8 (Dm7 – G7 – Cmaj7) escolhendo a escala de cada acorde e "
                          "resolvendo as tensões no acorde em vigor.",
                          "J", "H8", "C22"));

        // The gate closes the module: the lick J played on the grid at the target
        // BPM (REQ-009 accuracy + REQ-015 grid), so the student proves the phrase
        // and the tempo together over the module's own vamp.
        auto& gate = m.exercises.emplace_back (control (
            "GATE-11", "Desafio de gate — lick sobre a grade",
            "Tocar o lick do tópico J (repouso e tensão) sobre o vamp de Am7 (H1) a 100 BPM, na grade do metrônomo.",
            "LK-11.J", "J", "H1", "C02", { 9, 11, 0, 2, 4, 5, 7 }));
        gate.isGate = true;
        gate.targetBpm = 100;
        gate.usesGrid = true;

        m.gateChallenge = juce::String::fromUTF8 (
            "Tocar o lick do tópico J (uma frase de repouso e tensão sobre o vamp "
            "de Lá menor) a 100 BPM, na grade do metrônomo, com ≥90% de acerto e "
            "on_grid_ratio ≥ 0,82. O gate prova a frase e o tempo juntos.");

        // Pattern and links the module must cite (REQ-007, REQ-010).
        m.practice.patternId = "PTN-M-3";
        m.practice.patternUse = juce::String::fromUTF8 (
            "O padrão de grupos de três (PTN-M-3) constrói a frase do tópico A: "
            "cada grupo sobe um grau, criando movimento contínuo dentro da região. "
            "As demais frases correm a escala por graus conjuntos (PTN-M-SCALE), que "
            "é o material de onde as sequências nascem, e a frase do tópico J alterna "
            "repouso e tensão (PTN-M-REST).");
        m.practice.guitarists = { "John Petrucci", "Guthrie Govan", "Kiko Loureiro" };

        // Curated apostilas (REQ-006); see docs/MUSIC.md.
        m.sources = {
            "pdf-fraseado-melodico",
            "pdf-mozart-mello-improvisacion-pop",
            "pdf-mozart-mello-livroestudosdeguitarra4em1",
            "pdf-caged-e-derivaoes-de-acordes-marcelo-mello-apostila-de-violao-e-guitarra-vol1",
            "pdf-desvendando-os-segredos-da-guitarra-fusion",
        };

        return m;
    }

    // Modules 11..20 exist as placeholders so the list is honest about what is
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
        makeModule3(),
        makeModule4(),
        makeModule5(),
        makeModule6(),
        makeModule7(),
        makeModule8(),
        makeModule9(),
        makeModule10(),
        makeModule11(),
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
