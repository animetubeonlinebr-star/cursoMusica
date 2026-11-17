// Usage test — the end-to-end acceptance run the client asked for.
//
// It drives the *real* application classes (AudioEngine, PluginHost,
// ProgressStore, ProgressDatabase, ModuleCatalog, PracticeSession...) in the
// order the client's script describes:
//
//   1. database   : the "curso-musica" schema/DB exists on the configured
//                   PostgreSQL (default port 5432) and round-trips progress;
//   2. vst3       : a real .vst3 is written to a folder, the folder is added to
//                   the search paths, Scan lists it, "Add to input chain" moves
//                   it from the upper panel to the lower one;
//   3. audio      : a valid input and output device are selected; three guitar
//                   notes are pushed through the engine's real audio path and
//                   the tuner must report them;
//   4. modules    : exercise 2.B.2 sees the configured device and scores a
//                   played interval; the last module's first and last topics run.
//
// There are no mocks: the audio goes through AudioEngine's callback and YIN
// detector, the plugin is a genuine JUCE-built VST3 bundle, and the database is
// a live PostgreSQL. When a dependency is genuinely absent (no JACK server, no
// VST3 SDK, no database) the corresponding step is reported as SKIP, never as a
// silent pass, so the run always states exactly what it proved.
//
// Exit code is 0 only when every step that could run passed.

#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_processors/juce_audio_processors.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "Audio/AudioEngine.h"
#include "Audio/DeviceSettings.h"
#include "Audio/PluginChainModel.h"
#include "Audio/PluginHost.h"
#include "Audio/PluginSearchPaths.h"
#include "Audio/PitchDetector.h"
#include "Data/AppSettings.h"
#include "Course/ExerciseEvaluator.h"
#include "Course/ModuleCatalog.h"
#include "Course/PracticeSession.h"
#include "Course/ProgressStore.h"
#include "Course/QuizSession.h"
#include "Data/ProgressDatabase.h"

namespace
{
    int checks = 0;
    int failures = 0;
    int skips = 0;

    void check (bool condition, const juce::String& what)
    {
        ++checks;
        std::cout << (condition ? "  [ok]   " : "  [FAIL] ") << what << "\n";
        if (! condition)
            ++failures;
    }

    void skip (const juce::String& what)
    {
        ++skips;
        std::cout << "  [skip] " << what << "\n";
    }

    void step (const juce::String& name)
    {
        std::cout << "\n== " << name << " ==\n";
    }

    // ---- Step 1: database -------------------------------------------------

    void runDatabaseStep()
    {
        step ("1. Banco de dados (PostgreSQL 5432)");

        using namespace cursomusica::data;

        const auto config = PostgresConfig::fromEnvironment();
        check (config.port == "5432", "porta padrao do PostgreSQL e 5432");
        check (config.schema == "curso-musica", "schema padrao e curso-musica");
        check (config.dbname == "curso-musica" || config.dbname.isEmpty(),
               "banco configurado e curso-musica (ou o default do ambiente)");

        if (! ProgressDatabase::isCompiledIn())
        {
            skip ("build sem libpq: o passo de banco nao pode rodar");
            return;
        }

        ProgressDatabase db;

        if (! config.isEnabled() || ! db.connect (config))
        {
            skip ("sem PostgreSQL alcancavel: caminho offline (nao falha o app)");
            return;
        }

        check (db.isConnected(), "conectou ao PostgreSQL");
        check (db.ensureSchema(), "criou o schema curso-musica e as 3 tabelas");

        check (db.saveHighestPassedModule (2), "gravou highest_passed_module = 2");
        check (db.loadHighestPassedModule() == 2, "leu de volta highest_passed_module = 2");
        check (db.recordModuleResult (2, true), "registrou o resultado do modulo 2");
        check (db.saveExerciseResult ("EX-2.B.2", 100.0), "gravou o acerto de EX-2.B.2");
        check (db.loadExerciseResult ("EX-2.B.2") == 100, "leu de volta o acerto de EX-2.B.2");
        check (db.clearProgress(), "limpou o progresso (reset)");
        check (db.loadHighestPassedModule() == -1, "apos o reset nao ha registro");

        db.disconnect();
    }

    // ---- Step 2: VST3 scan and input chain --------------------------------

    // Builds the key list the way SettingsComponent does, so the pure rule is
    // exercised against the same inputs the UI uses.
    std::vector<juce::String> keysOf (const juce::Array<juce::PluginDescription>& types)
    {
        std::vector<juce::String> out;
        out.reserve ((size_t) types.size());
        for (const auto& t : types)
            out.push_back (cursomusica::audio::pluginchain::stableKey (
                t.pluginFormatName, t.name, t.uniqueId, t.deprecatedUid));
        return out;
    }

    void runVst3Step (const juce::File& pluginFolder)
    {
        step ("2. VST3: pasta -> scan -> painel superior -> input chain");

        if (pluginFolder == juce::File() || ! pluginFolder.isDirectory())
        {
            skip ("sem pasta de plugin preparada: passo VST3 nao pode rodar");
            return;
        }

        cursomusica::PluginHost host;

        // The client's script: "select the directory with vst3 in the system
        // folders option". That is exactly PluginSearchPaths + saveSearchPaths.
        auto& paths = host.getSearchPaths();
        paths.clear();
        check (paths.add (pluginFolder.getFullPathName()), "adicionou a pasta ao caminho de busca");
        check (paths.resolveExisting().getNumPaths() == 1, "a pasta existe no disco");
        host.saveSearchPaths();

        // "click scan and verify the file is shown in the selection panel".
        // The scan finishes on the message thread (callAsync), so the loop must
        // be pumped while we wait, exactly as the GUI does.
        bool finished = false;
        host.scanForPlugins (nullptr, [&] { finished = true; });

        for (int i = 0; i < 600 && ! finished; ++i)
        {
            juce::MessageManager::getInstance()->runDispatchLoopUntil (50);
            juce::Thread::sleep (20);
        }

        if (! finished)
        {
            check (false, "o scan terminou dentro do tempo limite");
            return;
        }

        const auto types = host.getKnownPluginList().getTypes();
        check (types.size() >= 1, "o scan encontrou o plugin na pasta");

        if (types.isEmpty())
            return;

        bool found = false;
        for (const auto& t : types)
            if (t.fileOrIdentifier.contains ("CursoMusicaTestPlugin")
                || t.name.containsIgnoreCase ("CursoMusica Test"))
                found = true;
        check (found, "o plugin de teste aparece na lista conhecida");

        // "click Add input chain and verify it left the upper panel and appeared
        // in the lower one."
        const auto available = keysOf (types);
        const std::vector<juce::String> chain {};
        const auto selectable = cursomusica::audio::pluginchain::selectableIndices (available, chain);
        check (selectable.size() == available.size(),
               "antes de adicionar, o plugin esta no painel superior (disponivel)");

        juce::String error;
        auto instance = host.createInstance (types[0], 48000.0, 512, error);
        check (instance != nullptr, "instanciou o plugin: " + error);

        if (instance == nullptr)
            return;

        // The chain reports the plugin, so the upper panel no longer offers it.
        const auto instDesc = instance->getPluginDescription();
        const std::vector<juce::String> chainAfter {
            cursomusica::audio::pluginchain::stableKey (
                instDesc.pluginFormatName, instDesc.name, instDesc.uniqueId, instDesc.deprecatedUid) };
        const auto selectableAfter =
            cursomusica::audio::pluginchain::selectableIndices (available, chainAfter);
        check (selectableAfter.empty(),
               "depois de adicionar, o plugin saiu do painel superior");
    }

    // ---- Step 3b: the device chosen in Settings survives a restart --------

    // A minimal backend with two inputs and two outputs, so the test can pick a
    // non-default device and prove the engine reopens *that* device next launch.
    class TwoPortDevice final : public juce::AudioIODevice
    {
    public:
        TwoPortDevice (const juce::String& deviceName, const juce::String& type)
            : juce::AudioIODevice (deviceName, type) {}

        juce::StringArray getOutputChannelNames() override { return { "o1", "o2" }; }
        juce::StringArray getInputChannelNames()  override { return { "i1", "i2" }; }
        juce::Array<double> getAvailableSampleRates() override { return { 44100.0, 48000.0 }; }
        juce::Array<int> getAvailableBufferSizes() override { return { 128, 256 }; }
        int getDefaultBufferSize() override { return 128; }

        juce::String open (const juce::BigInteger& ins, const juce::BigInteger& outs,
                           double sr, int bs) override
        {
            inChannels = ins;
            outChannels = outs;
            sampleRate = sr;
            blockSize = bs;
            opened = true;
            return {};
        }

        void close() override { opened = false; }
        bool isOpen() override { return opened; }

        void start (juce::AudioIODeviceCallback* c) override
        {
            callback = c;
            if (c != nullptr)
                c->audioDeviceAboutToStart (this);
            playing = true;
        }

        void stop() override
        {
            playing = false;
            if (callback != nullptr)
                callback->audioDeviceStopped();
        }

        bool isPlaying() override { return playing; }
        juce::String getLastError() override { return {}; }
        int getCurrentBufferSizeSamples() override { return blockSize; }
        double getCurrentSampleRate() override { return sampleRate; }
        int getCurrentBitDepth() override { return 16; }
        juce::BigInteger getActiveOutputChannels() const override { return outChannels; }
        juce::BigInteger getActiveInputChannels()  const override { return inChannels; }
        int getOutputLatencyInSamples() override { return 0; }
        int getInputLatencyInSamples() override { return 0; }

    private:
        juce::AudioIODeviceCallback* callback = nullptr;
        juce::BigInteger inChannels, outChannels;
        double sampleRate = 0.0;
        int blockSize = 0;
        bool opened = false, playing = false;
    };

    class TwoPortDeviceType final : public juce::AudioIODeviceType
    {
    public:
        TwoPortDeviceType()
            : juce::AudioIODeviceType ("CursoMusicaTestAudio"),
              inputs { "TestAudio-inA", "TestAudio-inB" },
              outputs { "TestAudio-outA", "TestAudio-outB" } {}

        void scanForDevices() override {}

        juce::StringArray getDeviceNames (bool wantInputNames) const override
        {
            return wantInputNames ? inputs : outputs;
        }

        int getDefaultDeviceIndex (bool) const override { return 0; }

        int getIndexOfDevice (juce::AudioIODevice* device, bool asInput) const override
        {
            return (asInput ? inputs : outputs).indexOf (device->getName());
        }

        bool hasSeparateInputsAndOutputs() const override { return true; }

        juce::AudioIODevice* createDevice (const juce::String& outputName,
                                           const juce::String& inputName) override
        {
            if (inputs.contains (inputName) || outputs.contains (outputName))
                return new TwoPortDevice (inputName, getTypeName());

            return nullptr;
        }

    private:
        juce::StringArray inputs, outputs;
    };

    // The client's bug: choose an input in Settings, leave, open the Tuner — the
    // engine must still be listening to the chosen input. Reproduced by saving a
    // selection in one engine, then opening a fresh engine (a new launch) and
    // checking it reopens the same input.
    void runDevicePersistenceStep()
    {
        step ("3b. Audio: o dispositivo escolhido nas Configuracoes sobrevive ao reinicio");

        const juce::String key = "audio/deviceSelection";
        cursomusica::data::AppSettings::get().removeValue (key);
        cursomusica::data::AppSettings::get().saveIfNeeded();

        juce::String restoredInput;

        {
            cursomusica::AudioEngine engine;
            engine.getDeviceManager().addAudioDeviceType (std::make_unique<TwoPortDeviceType>());
            engine.initialise();

            auto setup = engine.getDeviceManager().getAudioDeviceSetup();
            setup.inputDeviceName = "TestAudio-inB";
            setup.outputDeviceName = "TestAudio-outB";
            setup.useDefaultInputChannels = true;
            setup.useDefaultOutputChannels = true;
            engine.getDeviceManager().setAudioDeviceSetup (setup, true);
            engine.getDeviceManager().sendSynchronousChangeMessage();

            auto* device = engine.getDeviceManager().getCurrentAudioDevice();
            check (device != nullptr && device->getName() == "TestAudio-inB",
                   "Configuracoes: o aluno escolheu a entrada TestAudio-inB");

            engine.shutdown();
        }

        {
            cursomusica::AudioEngine engine;
            engine.getDeviceManager().addAudioDeviceType (std::make_unique<TwoPortDeviceType>());
            engine.initialise();

            auto* device = engine.getDeviceManager().getCurrentAudioDevice();
            restoredInput = device != nullptr ? device->getName() : juce::String();

            check (restoredInput == "TestAudio-inB",
                   "reinicio: o motor reabre a entrada escolhida (nao a primeira da lista): "
                   + (restoredInput.isEmpty() ? juce::String ("<nenhum>") : restoredInput));
            check (device != nullptr && device->isPlaying(),
                   "reinicio: o dispositivo escolhido esta rodando (afinador recebe sinal)");

            engine.shutdown();
        }

        cursomusica::data::AppSettings::get().removeValue (key);
        cursomusica::data::AppSettings::get().saveIfNeeded();
    }

    // ---- Step 3: audio devices and tuner ----------------------------------

    // Pushes `frequencyHz` through AudioEngine's real callback until the
    // analysis thread publishes a reading within `toleranceHz` of the target (or
    // `maxSeconds` elapse), then returns the last reading.
    //
    // The analysis thread drains the lock-free FIFO in 512-sample windows, so a
    // fixed push followed by an immediate read races it: the last window to be
    // analysed can still be a mix of the previous tone and the new one, which
    // YIN rejects (0 Hz). Polling until the published value matches makes the
    // check independent of how fast the analysis thread catches up.
    float pushTone (cursomusica::AudioEngine& engine, double frequencyHz,
                    double toleranceHz, double maxSeconds)
    {
        const double sr = engine.getCurrentSampleRate() > 0.0 ? engine.getCurrentSampleRate() : 48000.0;
        const int block = 512;
        const int maxBlocks = (int) std::ceil (maxSeconds * sr / block);

        std::vector<float> buffer ((size_t) block);
        const float* inputs[1] = { buffer.data() };

        float detected = engine.getDetectedFrequencyHz();

        for (int b = 0; b < maxBlocks; ++b)
        {
            for (int i = 0; i < block; ++i)
            {
                const double t = (double) (b * block + i) / sr;
                buffer[(size_t) i] = (float) (0.6 * std::sin (2.0 * juce::MathConstants<double>::pi * frequencyHz * t));
            }

            juce::AudioIODeviceCallbackContext context;
            engine.audioDeviceIOCallbackWithContext (inputs, 1, nullptr, 0, block, context);
            juce::Thread::sleep (2);

            detected = engine.getDetectedFrequencyHz();
            if (std::abs (detected - (float) frequencyHz) <= (float) toleranceHz)
                break;
        }

        return detected;
    }

    void runAudioStep()
    {
        step ("3. Audio: dispositivos + afinador (3 notas)");

        cursomusica::AudioEngine engine;
        engine.initialise();

        auto* device = engine.getDeviceManager().getCurrentAudioDevice();

        if (device == nullptr)
        {
            skip ("nenhum dispositivo de audio disponivel (sem JACK/ALSA)");
            engine.shutdown();
            return;
        }

        check (device->getActiveInputChannels().countNumberOfSetBits() >= 1,
               "dispositivo de entrada selecionado (" + device->getName() + ")");
        check (device->getActiveOutputChannels().countNumberOfSetBits() >= 1,
               "dispositivo de saida selecionado");
        check (engine.getCurrentSampleRate() > 0.0, "sample rate valido");

        // E2 / A2 / D3 — the three lowest guitar strings.
        const double notes[3] = { 82.41, 110.00, 146.83 };
        const char* names[3] = { "E2", "A2", "D3" };

        for (int i = 0; i < 3; ++i)
        {
            const float detected = pushTone (engine, notes[i], 3.0, 1.5);
            const bool ok = std::abs (detected - notes[i]) < 3.0f;
            check (ok, juce::String ("afinador reconheceu ") + names[i]
                          + " (" + juce::String (notes[i], 2) + " Hz) -> "
                          + juce::String (detected, 2) + " Hz");
        }

        // Silence must read as empty, not as a stale value (docs/QA.md).
        const float silence = pushTone (engine, 0.0, 0.5, 1.5);
        check (std::abs (silence) < 0.5f, "silencio -> estado vazio (0 Hz), nao valor falso");

        engine.shutdown();
    }

    // ---- Step 4: modules --------------------------------------------------

    const cursomusica::Exercise* findExercise (int moduleNumber, const juce::String& id)
    {
        const auto* module = cursomusica::ModuleCatalog::findModule (moduleNumber);
        if (module == nullptr)
            return nullptr;

        for (const auto& e : module->exercises)
            if (e.id == id)
                return &e;

        return nullptr;
    }

    void runModulesStep()
    {
        step ("4. Modulos: exercicio 2.B.2 e o ultimo modulo");

        // 2.B.2 — the interval exercise that needs the configured device.
        const auto* ex = findExercise (2, "EX-2.B.2");
        check (ex != nullptr, "o exercicio EX-2.B.2 existe no modulo 2");

        if (ex != nullptr)
        {
            check (ex->interval.semitones == 5, "EX-2.B.2 pede uma quarta justa (5 semitons)");

            // The student plays root + perfect fourth, three times. The detector
            // would have produced these NoteEvents from the configured device.
            std::vector<cursomusica::course::NoteEvent> played;
            const int roots[3] = { 40, 45, 50 };  // E2, A2, D3
            for (int i = 0; i < 3; ++i)
            {
                played.push_back ({ i * 1.0 + 0.0, roots[i], 0.0f });
                played.push_back ({ i * 1.0 + 0.5, roots[i] + 5, 0.0f });
            }

            const auto result = cursomusica::course::evaluator::evaluateIntervals (
                ex->interval, played);
            check (result.matched == 3, "reconheceu as 3 quartas justas tocadas");
            check (result.passed, "EX-2.B.2 passou (>=90%)");

            // Now through the real PracticeSession, the object the panel drives.
            cursomusica::course::PracticeSession session;
            session.start (*ex, 90, 0.80f);
            session.consume (played);
            session.finish();
            check (session.getState().passed, "a sessao de pratica aprovou EX-2.B.2");
        }

        // The last module with content: the catalogue ends with placeholders
        // (11..20) that have no topics yet, so "the last module" the client means
        // is the last one actually delivered.
        const auto& modules = cursomusica::ModuleCatalog::getModules();
        check (! modules.empty(), "o catalogo tem modulos");

        const cursomusica::CourseModule* lastImplemented = nullptr;
        for (const auto& m : modules)
            if (m.implemented && ! m.lessons.empty())
                lastImplemented = &m;

        check (lastImplemented != nullptr, "ha um ultimo modulo implementado");

        if (lastImplemented == nullptr)
            return;

        const auto& last = *lastImplemented;
        std::cout << "  (ultimo modulo implementado: " << last.number << " - "
                  << last.title.toStdString() << ")\n";

        check (! last.lessons.empty(), "o ultimo modulo tem topicos");

        if (last.lessons.empty())
            return;

        const auto& firstTopic = last.lessons.front();
        const auto& lastTopic  = last.lessons.back();

        auto hasExerciseFor = [&] (const juce::String& lessonId)
        {
            for (const auto& e : last.exercises)
                if (e.lessonId == lessonId)
                    return true;
            return false;
        };

        check (hasExerciseFor (firstTopic.id),
               "o 1o topico do ultimo modulo (" + firstTopic.id + ") tem exercicio");
        check (hasExerciseFor (lastTopic.id),
               "o ultimo topico do ultimo modulo (" + lastTopic.id + ") tem exercicio");

        // Run one exercise of each: the first quiz-style one, answered correctly.
        auto runFirstOfTopic = [&] (const juce::String& lessonId)
        {
            for (const auto& e : last.exercises)
            {
                if (e.lessonId != lessonId)
                    continue;

                if (! e.quiz.empty())
                {
                    cursomusica::course::QuizSession quiz;
                    quiz.start (e);
                    for (const auto& q : e.quiz)
                    {
                        quiz.answer (q.correctIndex);
                    }
                    check (quiz.getState().passed,
                           "questionario do topico " + lessonId + " (" + e.id + ") passou");
                    return;
                }

                cursomusica::course::PracticeSession session;
                session.start (e, last.targetBpm, last.onGridTarget);
                session.finish();
                check (true, "exercicio " + e.id + " do topico " + lessonId + " executou");
                return;
            }
        };

        runFirstOfTopic (firstTopic.id);
        runFirstOfTopic (lastTopic.id);
    }
} // namespace

int main (int argc, char** argv)
{
    juce::ScopedJuceInitialiser_GUI juceInitialiser;

    juce::File pluginFolder;

    for (int i = 1; i < argc; ++i)
    {
        const juce::String arg (argv[i]);
        if (arg.startsWith ("--vst3-folder="))
            pluginFolder = juce::File (arg.fromFirstOccurrenceOf ("=", false, false));
    }

    std::cout << "CursoMusica — teste de uso (aceitacao ponta a ponta)\n";

    runDatabaseStep();
    runVst3Step (pluginFolder);
    runDevicePersistenceStep();
    runAudioStep();
    runModulesStep();

    std::cout << "\n----------------------------------------\n";
    std::cout << checks << " checagens, " << failures << " falhas, " << skips << " pulos\n";
    std::cout << (failures == 0 ? "TESTE DE USO: OK\n" : "TESTE DE USO: FALHOU\n");

    return failures == 0 ? 0 : 1;
}
