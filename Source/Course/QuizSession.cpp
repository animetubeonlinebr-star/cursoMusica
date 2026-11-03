#include "Course/QuizSession.h"

#include "Course/ExerciseEvaluator.h"

namespace cursomusica::course
{

void QuizSession::start (const Exercise& exercise)
{
    questions = exercise.quiz;
    restart();
}

void QuizSession::restart()
{
    questionIndex = 0;
    answered = 0;
    correct = 0;
    lastCorrect = false;
    running = ! questions.empty();
    finished = questions.empty();
    recompute();
}

void QuizSession::stop()
{
    running = false;
    recompute();
}

void QuizSession::answer (int optionIndex)
{
    if (! running || questionIndex >= (int) questions.size())
        return;

    const auto& question = questions[(size_t) questionIndex];

    if (optionIndex >= 0 && optionIndex < question.options.size())
    {
        ++answered;
        lastCorrect = optionIndex == question.correctIndex;
        if (lastCorrect)
            ++correct;
    }

    ++questionIndex;

    if (questionIndex >= (int) questions.size())
    {
        running = false;
        finished = true;
    }

    recompute();
}

void QuizSession::finish()
{
    running = false;
    finished = true;
    recompute();
}

void QuizSession::recompute()
{
    state.running = running;
    state.finished = finished;
    state.currentQuestion = questionIndex;
    state.answered = answered;
    state.correct = correct;
    state.lastAnswerCorrect = lastCorrect;
    state.accuracy = evaluator::accuracyOf (correct, answered);
    state.passed = answered > 0 && evaluator::gatePassed (state.accuracy);

    if (! finished)
        state.message = {};
    else if (answered == 0)
        state.message = juce::String::fromUTF8 ("Nenhuma questão respondida.");
    else
        state.message = juce::String::fromUTF8 ("Acertos: ") + juce::String (correct)
                          + "/" + juce::String (answered) + " ("
                          + juce::String (juce::roundToInt (state.accuracy * 100.0)) + "%).";
}

const QuizQuestion* QuizSession::currentQuestion() const
{
    if (questionIndex < 0 || questionIndex >= (int) questions.size())
        return nullptr;

    return &questions[(size_t) questionIndex];
}

} // namespace cursomusica::course
