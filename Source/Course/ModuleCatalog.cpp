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
        makePlaceholder (7,  "II–V–I (aplicação)",                  3,  84,  0.80f),
        makeModule8(),
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
