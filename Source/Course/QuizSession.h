#pragma once

#include <juce_core/juce_core.h>

#include <vector>

#include "Course/Module.h"

namespace cursomusica::course
{

// Live state of a quiz attempt: questions are answered one at a time and the
// verdict follows the same gate as the playable exercises (REQ-009).
struct QuizState
{
    bool running = false;
    bool finished = false;
    int currentQuestion = 0;   // index into the exercise's questions
    int answered = 0;
    int correct = 0;
    bool lastAnswerCorrect = false;
    double accuracy = 0.0;
    bool passed = false;
    juce::String message;
};

// Drives a multiple-choice quiz: pure logic, no audio and no UI, so it is
// deterministic and covered by the headless test suite.
class QuizSession
{
public:
    void start (const Exercise& exercise);

    void stop();
    bool isRunning() const noexcept { return state.running; }

    // Records the chosen option for the current question and advances.
    void answer (int optionIndex);

    void finish();

    // Restarts from the first question, keeping the same exercise.
    void restart();

    const QuizState& getState() const noexcept { return state; }

    int getNumQuestions() const noexcept { return (int) questions.size(); }

    // The question currently on screen, or nullptr when the quiz is over.
    const QuizQuestion* currentQuestion() const;

private:
    void recompute();

    std::vector<QuizQuestion> questions;
    int questionIndex = 0;
    int answered = 0;
    int correct = 0;
    bool lastCorrect = false;
    bool running = false;
    bool finished = false;

    QuizState state;
};

} // namespace cursomusica::course
