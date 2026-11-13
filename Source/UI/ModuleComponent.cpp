#include "UI/ModuleComponent.h"

#include "Course/ModuleCatalog.h"
#include "Course/QuizSession.h"
#include "Course/Content/Diagrams.h"
#include "UI/Design/Theme.h"
#include "UI/PracticePanel.h"

#include <functional>
#include <unordered_map>

namespace cursomusica
{

namespace th = cursomusica::theme;

namespace
{
    // Concrete root of the subject tree; the modules hang from it. The root
    // itself is not shown (TreeView::setRootItemVisible(false)).
    class SubjectRootItem final : public juce::TreeViewItem
    {
    public:
        bool mightContainSubItems() override { return true; }
    };

    // Lays out a wrapped run of text and returns the height it needs.
    int textHeight (const juce::Font& font, const juce::String& text, int width)
    {
        juce::AttributedString s;
        s.setFont (font);
        s.setText (text);

        juce::TextLayout layout;
        layout.createLayout (s, (float) juce::jmax (40, width));
        return juce::jmax (18, juce::roundToInt (layout.getHeight()));
    }

    // The teaching diagrams ship inside the binary (juce_add_binary_data). They
    // are decoded once and kept, so scrolling and relayout do not hit the JPEG
    // decoder repeatedly.
    const juce::Image& diagramImage (const juce::String& name)
    {
        static std::unordered_map<std::string, juce::Image> cache;

        const std::string key = name.toStdString();
        auto it = cache.find (key);
        if (it != cache.end())
            return it->second;

        int size = 0;
        const auto* data = content::diagramData (name, size);
        juce::Image image;
        if (data != nullptr && size > 0)
            image = juce::ImageFileFormat::loadFrom (data, (size_t) size);

        return cache.emplace (std::move (key), std::move (image)).first->second;
    }

    int diagramHeightForWidth (const juce::String& name, int width)
    {
        const auto& image = diagramImage (name);
        if (! image.isValid() || image.getWidth() <= 0)
            return 120; // placeholder box for a missing resource
        return juce::roundToInt ((float) width * (float) image.getHeight()
                                     / (float) image.getWidth());
    }
}

// Central pane: explains the current selection. With no topic selected it shows
// the module overview (objective, CAGED, rhythm, practice track, gate); with a
// topic selected it shows that topic's detailed explanation; with an exercise
// demonstrated it shows the exercise card (REQ-003).
class ModuleComponent::ContentView final : public juce::Component
{
public:
    void setSelection (const CourseModule* module, const LessonBlock* topic, const Exercise* exercise)
    {
        current = module;
        currentTopic = topic;
        currentExercise = exercise;
        hoveredOption = -1;
        repaint();
    }

    // Mirrors the quiz state held by the practice pane, so the centre can render
    // the question and the clickable options (the exercise runs in the centre,
    // the right pane keeps only the controls — REQ-021).
    void setQuiz (const Exercise* exercise, const course::QuizState& state)
    {
        quizExercise = exercise;
        quizState = state;
        hoveredOption = -1;
        repaint();
    }

    // The centre answers the quiz by proxy: the pane owns the session.
    std::function<void (int)> onAnswerOption;

    void setLockedMessage (const juce::String& message)
    {
        lockedMessage = message;
        repaint();
    }

    // The module overview lists its topics only after the student has read one
    // there (REQ-020): a module never read opens blank of lesson content
    // (REQ-019), a module already read keeps its topic data loaded.
    void setOverviewLessonsVisible (bool visible)
    {
        showOverviewLessons = visible;
        repaint();
    }

    int getRequiredHeight() const
    {
        if (current == nullptr)
            return 400;

        const int width = juce::jmax (320, getWidth() - 2 * th::spacing::lg);
        int height = 150; // header, meta line and objective

        if (currentExercise != nullptr)
            return height + exerciseDetailHeight (width) + 40;

        if (currentTopic != nullptr)
            return height + topicDetailHeight (width) + 40;

        // A module never read opens blank: only the header, the meta line and the
        // objective are measured (REQ-019). A module already read lists its topics
        // again and keeps its module-level context on return (REQ-020).
        if (! showOverviewLessons)
            return juce::jmax (height, 200);

        height += th::spacing::sm;

        for (const auto& lesson : current->lessons)
            height += lessonSummaryHeight (lesson, width);

        if (! current->caged.empty())
            height += 24 + 40 * (int) current->caged.size() + th::spacing::sm;

        if (! current->rhythm.empty())
            height += 24 + 20 * (int) current->rhythm.size() + th::spacing::sm;

        if (current->practice.patternId.isNotEmpty())
            height += 24 + 20 + 20 + 20 * (int) current->practice.guitarists.size() + th::spacing::sm;

        height += 22 + 40;

        if (! current->sources.isEmpty())
            height += th::spacing::sm + 24 + 18 * (int) current->sources.size();

        return juce::jmax (height, 400);
    }

    void paint (juce::Graphics& g) override
    {
        auto bounds = getLocalBounds().reduced (th::spacing::lg);

        if (current == nullptr)
        {
            g.setColour (th::colour::textSecondary);
            g.setFont (th::type::makeFont (th::type::body));
            g.drawFittedText (lockedMessage.isNotEmpty()
                                  ? lockedMessage
                                  : juce::String::fromUTF8 ("Selecione um módulo à esquerda."),
                              bounds, juce::Justification::centred, 3);
            return;
        }

        const auto& m = *current;

        g.setColour (th::colour::textPrimary);
        g.setFont (th::type::makeFont (th::type::title, true));
        g.drawFittedText (juce::String::fromUTF8 ("Módulo ") + juce::String (m.number) + " — " + m.title,
                          bounds.removeFromTop (34), juce::Justification::centredLeft, 2);

        paintMetaLine (g, bounds.removeFromTop (20), m);
        bounds.removeFromTop (th::spacing::xs);

        g.setColour (th::colour::textSecondary);
        g.setFont (th::type::makeFont (th::type::body));
        g.drawFittedText (m.objective, bounds.removeFromTop (44), juce::Justification::topLeft, 3);

        bounds.removeFromTop (th::spacing::md);

        if (currentExercise != nullptr)
            paintExercise (g, bounds, *currentExercise);
        else if (currentTopic != nullptr)
            paintTopic (g, bounds, *currentTopic);
        else
            paintOverview (g, bounds, m);
    }

private:
    int lessonSummaryHeight (const LessonBlock& lesson, int width) const
    {
        int height = 22;
        for (const auto& paragraph : lesson.paragraphs)
            height += textHeight (th::type::makeFont (th::type::body), paragraph, width);
        return height + th::spacing::sm;
    }

    int topicDetailHeight (int width) const
    {
        int height = 28 + th::spacing::sm; // topic title
        for (const auto& item : currentTopic->detail)
            height += itemHeight (item, width);
        return height;
    }

    int exerciseDetailHeight (int width) const
    {
        int height = 0; // the id/title sits on the meta line, not in the card

        if (currentExercise->isQuiz())
        {
            // The quiz runs in the centre (REQ-021): instruction, current
            // question and its clickable options — no goal/check card, which
            // would only repeat what the module header already states.
            height += 20 + th::spacing::sm;                 // "Responda uma questão por vez."
            height += 20;                                    // "Questão X de Y" (or its gap)
            if (const auto* q = currentQuestion())
                height += textHeight (th::type::makeFont (th::type::body, true), q->prompt, width);
            height += th::spacing::sm;
            height += quizOptionCount() * (32 + th::spacing::xs);
            height += th::spacing::sm;
            height += 36;                                    // verdict line
            return height;
        }

        height += 20 + textHeight (th::type::makeFont (th::type::body), currentExercise->goal, width) + 8;
        height += 20 + textHeight (th::type::makeFont (th::type::body), currentExercise->check, width) + 8;

        // The exercise card only explains what was proposed (REQ-021); the
        // playable one runs in the right pane.
        height += 36 + th::spacing::sm;
        return height;
    }

    int itemHeight (const ContentItem& item, int width) const
    {
        switch (item.kind)
        {
            case ContentKind::heading:   return 24 + th::spacing::xs;
            case ContentKind::paragraph: return textHeight (th::type::makeFont (th::type::body), item.text, width) + 6;
            case ContentKind::bullet:    return textHeight (th::type::makeFont (th::type::body), item.text, width - 18) + 4;
            case ContentKind::callout:   return textHeight (th::type::makeFont (th::type::body), item.text, width - 20) + 16;
            case ContentKind::table:     return 22 + 20 * (int) item.rows.size() + th::spacing::sm;
            case ContentKind::image:
            {
                int height = diagramHeightForWidth (item.imageName, width) + th::spacing::sm;
                if (item.text.isNotEmpty())
                    height += 20 + textHeight (th::type::makeFont (th::type::caption), item.text, width);
                return height;
            }
        }
        return 20;
    }

    void paintMetaLine (juce::Graphics& g, juce::Rectangle<int> area, const CourseModule& m)
    {
        const bool quiz = currentExercise != nullptr && currentExercise->isQuiz();

        juce::String text;
        if (currentExercise != nullptr && ! quiz)
            text = currentExercise->id + " — " + currentExercise->title;
        else if (quiz || currentTopic == nullptr)
        {
            // The quiz keeps the module header (NÍVEL/BPM/GATE) of the mock-up,
            // not the topic line: the question is what identifies the exercise.
            // A module that does not use a BPM target prints a dash (client).
            const juce::String bpm = m.usesTempo ? juce::String (m.targetBpm)
                                                 : juce::String::fromUTF8 ("—");
            text = juce::String::fromUTF8 ("NÍVEL ") + juce::String (m.level)
                     + juce::String::fromUTF8 ("   ·   BPM META ") + bpm
                     + juce::String::fromUTF8 ("   ·   GATE 90%");
        }
        else
            text = juce::String::fromUTF8 ("Tópico ") + currentTopic->id + " — " + currentTopic->title;

        g.setColour (th::colour::accentAlt);
        g.setFont (th::type::makeFont (th::type::caption, true));
        g.drawText (text, area, juce::Justification::centredLeft, false);
    }

    void paintOverview (juce::Graphics& g, juce::Rectangle<int> bounds, const CourseModule& m)
    {
        // A module never read opens blank: only the module context drawn by
        // paint() (header, meta line, objective) shows, so no lesson content is
        // loaded by itself (REQ-019). Once the student reads a topic there,
        // returning to the module lists its topics and keeps that content
        // (REQ-020); opening another module clears the centre again.
        if (! showOverviewLessons)
        {
            g.setColour (th::colour::textDisabled);
            g.setFont (th::type::makeFont (th::type::body));
            g.drawFittedText (juce::String::fromUTF8 (
                                  "Selecione um tópico à esquerda para ler a explicação. "
                                  "Os exercícios de cada tópico ficam no painel de prática, à direita."),
                              bounds.removeFromTop (44), juce::Justification::topLeft, 3);
            return;
        }

        for (const auto& lesson : m.lessons)
        {
            g.setColour (th::colour::accent);
            g.setFont (th::type::makeFont (th::type::body, true));
            g.drawText (lesson.id + ". " + lesson.title, bounds.removeFromTop (22),
                        juce::Justification::centredLeft, false);

            g.setColour (th::colour::textSecondary);
            g.setFont (th::type::makeFont (th::type::body));
            for (const auto& paragraph : lesson.paragraphs)
            {
                const int height = textHeight (th::type::makeFont (th::type::body), paragraph, bounds.getWidth());
                g.drawFittedText (paragraph, bounds.removeFromTop (height),
                                  juce::Justification::topLeft, 4);
            }
            bounds.removeFromTop (th::spacing::sm);
        }

        if (! m.caged.empty())
        {
            g.setColour (th::colour::textPrimary);
            g.setFont (th::type::makeFont (th::type::body, true));
            g.drawText (juce::String::fromUTF8 ("Sistema CAGED"), bounds.removeFromTop (24),
                        juce::Justification::centredLeft, false);

            g.setFont (th::type::makeFont (th::type::body));
            for (const auto& shape : m.caged)
            {
                g.setColour (th::colour::accent);
                g.drawText (juce::String::fromUTF8 ("Forma ") + shape.shape,
                            bounds.removeFromTop (20).removeFromLeft (110),
                            juce::Justification::centredLeft, false);
                g.setColour (th::colour::textSecondary);
                g.drawText (juce::String::fromUTF8 ("baixo na ") + shape.bassString
                                + "   ·   " + shape.region,
                            bounds.removeFromTop (20), juce::Justification::centredLeft, false);
            }
            bounds.removeFromTop (th::spacing::sm);
        }

        if (! m.rhythm.empty())
        {
            g.setColour (th::colour::textPrimary);
            g.setFont (th::type::makeFont (th::type::body, true));
            g.drawText (juce::String::fromUTF8 ("Rítmica e contagem"), bounds.removeFromTop (24),
                        juce::Justification::centredLeft, false);

            g.setFont (th::type::makeFont (th::type::body));
            for (const auto& cell : m.rhythm)
            {
                g.setColour (th::colour::accent);
                g.drawText (cell.figure, bounds.removeFromTop (20).removeFromLeft (150),
                            juce::Justification::centredLeft, false);
                g.setColour (th::colour::textSecondary);
                g.drawText (cell.value + juce::String::fromUTF8 ("   ·   ") + cell.syllable,
                            bounds.removeFromTop (20), juce::Justification::centredLeft, false);
            }
            bounds.removeFromTop (th::spacing::sm);
        }

        if (m.practice.patternId.isNotEmpty())
        {
            g.setColour (th::colour::textPrimary);
            g.setFont (th::type::makeFont (th::type::body, true));
            g.drawText (juce::String::fromUTF8 ("Trilha de prática"), bounds.removeFromTop (24),
                        juce::Justification::centredLeft, false);

            g.setColour (th::colour::accent);
            g.setFont (th::type::makeFont (th::type::body, true));
            g.drawText (m.practice.patternId, bounds.removeFromTop (20),
                        juce::Justification::centredLeft, false);

            g.setColour (th::colour::textSecondary);
            g.setFont (th::type::makeFont (th::type::body));
            g.drawFittedText (m.practice.patternUse, bounds.removeFromTop (20),
                              juce::Justification::topLeft, 1);

            for (const auto& guitarist : m.practice.guitarists)
            {
                g.setColour (th::colour::textSecondary);
                g.drawText (juce::String::fromUTF8 ("Referência: ") + guitarist,
                            bounds.removeFromTop (20), juce::Justification::centredLeft, false);
            }
            bounds.removeFromTop (th::spacing::sm);
        }

        if (m.gateChallenge.isNotEmpty())
        {
            g.setColour (th::colour::textPrimary);
            g.setFont (th::type::makeFont (th::type::body, true));
            g.drawText (juce::String::fromUTF8 ("Desafio de gate"), bounds.removeFromTop (22),
                        juce::Justification::centredLeft, false);

            g.setColour (th::colour::success);
            g.setFont (th::type::makeFont (th::type::body));
            g.drawFittedText (m.gateChallenge, bounds.removeFromTop (40),
                              juce::Justification::topLeft, 2);
        }

        if (! m.sources.isEmpty())
        {
            bounds.removeFromTop (th::spacing::sm);
            g.setColour (th::colour::textPrimary);
            g.setFont (th::type::makeFont (th::type::body, true));
            g.drawText (juce::String::fromUTF8 ("Apostilas (curadoria — REQ-006)"),
                        bounds.removeFromTop (24), juce::Justification::centredLeft, false);

            g.setColour (th::colour::textSecondary);
            g.setFont (th::type::makeFont (th::type::caption));
            for (const auto& source : m.sources)
                g.drawText (source, bounds.removeFromTop (18), juce::Justification::centredLeft, false);
        }
    }

    void paintTopic (juce::Graphics& g, juce::Rectangle<int> bounds, const LessonBlock& topic)
    {
        g.setColour (th::colour::accent);
        g.setFont (th::type::makeFont (th::type::title, true));
        g.drawFittedText (topic.id + ". " + topic.title, bounds.removeFromTop (28),
                          juce::Justification::centredLeft, 1);
        bounds.removeFromTop (th::spacing::sm);

        for (const auto& item : topic.detail)
            paintItem (g, bounds, item);
    }

    void paintItem (juce::Graphics& g, juce::Rectangle<int>& bounds, const ContentItem& item)
    {
        const int width = bounds.getWidth();

        switch (item.kind)
        {
            case ContentKind::heading:
            {
                bounds.removeFromTop (th::spacing::xs);
                g.setColour (th::colour::accentAlt);
                g.setFont (th::type::makeFont (th::type::body, true));
                g.drawFittedText (item.text, bounds.removeFromTop (22), juce::Justification::centredLeft, 1);
                break;
            }
            case ContentKind::paragraph:
            {
                g.setColour (th::colour::textSecondary);
                g.setFont (th::type::makeFont (th::type::body));
                const int height = textHeight (th::type::makeFont (th::type::body), item.text, width);
                g.drawFittedText (item.text, bounds.removeFromTop (height), juce::Justification::topLeft, 6);
                bounds.removeFromTop (6);
                break;
            }
            case ContentKind::bullet:
            {
                const int height = textHeight (th::type::makeFont (th::type::body), item.text, width - 18);
                auto row = bounds.removeFromTop (height);
                g.setColour (th::colour::accent);
                g.setFont (th::type::makeFont (th::type::body, true));
                g.drawText (juce::String::fromUTF8 ("•"), row.removeFromLeft (16),
                            juce::Justification::topLeft, false);
                g.setColour (th::colour::textSecondary);
                g.setFont (th::type::makeFont (th::type::body));
                g.drawFittedText (item.text, row, juce::Justification::topLeft, 6);
                bounds.removeFromTop (4);
                break;
            }
            case ContentKind::callout:
            {
                const int height = textHeight (th::type::makeFont (th::type::body), item.text, width - 20) + 12;
                auto box = bounds.removeFromTop (height);
                g.setColour (th::colour::accentMuted.withAlpha (0.35f));
                g.fillRoundedRectangle (box.toFloat(), th::radius::sm);
                g.setColour (th::colour::textPrimary);
                g.setFont (th::type::makeFont (th::type::body));
                g.drawFittedText (item.text, box.reduced (10, 6), juce::Justification::centredLeft, 4);
                bounds.removeFromTop (th::spacing::xs);
                break;
            }
            case ContentKind::table:
            {
                auto area = bounds.removeFromTop (22 + 20 * (int) item.rows.size());
                const int columns = juce::jmax (1, item.columns.size());
                const int columnWidth = area.getWidth() / columns;

                auto header = area.removeFromTop (22);
                g.setColour (th::colour::surfaceRaised);
                g.fillRoundedRectangle (header.toFloat(), th::radius::sm);
                g.setFont (th::type::makeFont (th::type::caption, true));
                for (int c = 0; c < columns; ++c)
                {
                    g.setColour (th::colour::accentAlt);
                    g.drawText (c < item.columns.size() ? item.columns[c] : juce::String(),
                                header.removeFromLeft (columnWidth).reduced (8, 0),
                                juce::Justification::centredLeft, false);
                }

                g.setFont (th::type::makeFont (th::type::caption));
                for (const auto& row : item.rows)
                {
                    auto line = area.removeFromTop (20);
                    for (int c = 0; c < columns; ++c)
                    {
                        g.setColour (th::colour::textSecondary);
                        g.drawText (c < row.size() ? row[c] : juce::String(),
                                    line.removeFromLeft (columnWidth).reduced (8, 0),
                                    juce::Justification::centredLeft, false);
                    }
                }
                bounds.removeFromTop (th::spacing::sm);
                break;
            }
            case ContentKind::image:
            {
                const int height = diagramHeightForWidth (item.imageName, width);
                auto area = bounds.removeFromTop (height);
                const auto& image = diagramImage (item.imageName);

                if (image.isValid())
                    g.drawImage (image, area.toFloat(),
                                 juce::RectanglePlacement::stretchToFit);
                else
                {
                    // Missing resource: draw a labelled box instead of failing
                    // silently, so the gap is obvious while authoring content.
                    g.setColour (th::colour::surfaceRaised);
                    g.fillRoundedRectangle (area.toFloat(), th::radius::sm);
                    g.setColour (th::colour::textDisabled);
                    g.setFont (th::type::makeFont (th::type::caption));
                    g.drawText (juce::String::fromUTF8 ("Diagrama indisponível: ") + item.imageName,
                                area, juce::Justification::centred, false);
                }

                if (item.text.isNotEmpty())
                {
                    g.setColour (th::colour::textDisabled);
                    g.setFont (th::type::makeFont (th::type::caption));
                    g.drawFittedText (item.text, bounds.removeFromTop (20),
                                      juce::Justification::centredLeft, 1);
                }
                bounds.removeFromTop (th::spacing::sm);
                break;
            }
        }
    }

    void paintExercise (juce::Graphics& g, juce::Rectangle<int> bounds, const Exercise& exercise)
    {
        // A quiz goes straight to the question: the module header above already
        // states the context, so no goal/check card is repeated here (REQ-021).
        if (exercise.isQuiz())
        {
            paintQuiz (g, bounds);
            return;
        }

        // The exercise id/title already sits on the meta line above (context);
        // the card explains what was proposed (REQ-021).
        g.setColour (th::colour::textPrimary);
        g.setFont (th::type::makeFont (th::type::body, true));
        g.drawText (juce::String::fromUTF8 ("Objetivo"), bounds.removeFromTop (20),
                    juce::Justification::centredLeft, false);
        g.setColour (th::colour::textSecondary);
        g.setFont (th::type::makeFont (th::type::body));
        g.drawFittedText (exercise.goal,
                          bounds.removeFromTop (textHeight (th::type::makeFont (th::type::body), exercise.goal, bounds.getWidth())),
                          juce::Justification::topLeft, 3);
        bounds.removeFromTop (th::spacing::sm);

        g.setColour (th::colour::textPrimary);
        g.setFont (th::type::makeFont (th::type::body, true));
        g.drawText (juce::String::fromUTF8 ("Como o app verifica"), bounds.removeFromTop (20),
                    juce::Justification::centredLeft, false);
        g.setColour (th::colour::textSecondary);
        g.setFont (th::type::makeFont (th::type::body));
        g.drawFittedText (exercise.check,
                          bounds.removeFromTop (textHeight (th::type::makeFont (th::type::body), exercise.check, bounds.getWidth())),
                          juce::Justification::topLeft, 3);
        bounds.removeFromTop (th::spacing::md);

        // A playable exercise explains only what was proposed (REQ-021); the
        // play controls and the live measurement live in the right pane.
        g.setColour (th::colour::textDisabled);
        g.setFont (th::type::makeFont (th::type::body));
        g.drawFittedText (juce::String::fromUTF8 (
                              "Execute no painel de prática, à direita. "
                              "Aqui fica só a explicação do que foi proposto."),
                          bounds.removeFromTop (36), juce::Justification::topLeft, 2);
    }

    // The quiz (question + options) runs in the centre: the student answers here
    // and the right pane keeps only the controls and the scoreboard (REQ-021).
    void paintQuiz (juce::Graphics& g, juce::Rectangle<int> bounds)
    {
        g.setColour (th::colour::accentAlt);
        g.setFont (th::type::makeFont (th::type::body, true));
        g.drawFittedText (quizInstruction(), bounds.removeFromTop (20), juce::Justification::centredLeft, 2);
        bounds.removeFromTop (th::spacing::sm);

        const auto* question = currentQuestion();
        const int total = quizExercise != nullptr ? (int) quizExercise->quiz.size() : 0;

        if (question != nullptr)
        {
            g.setColour (th::colour::textPrimary);
            g.setFont (th::type::makeFont (th::type::body, true));
            g.drawText (juce::String::fromUTF8 ("Questão ") + juce::String (quizState.currentQuestion + 1)
                            + juce::String::fromUTF8 (" de ") + juce::String (total),
                        bounds.removeFromTop (20), juce::Justification::centredLeft, false);

            g.setColour (th::colour::textPrimary);
            g.setFont (th::type::makeFont (th::type::body, true));
            g.drawFittedText (question->prompt,
                              bounds.removeFromTop (textHeight (th::type::makeFont (th::type::body, true),
                                                                question->prompt, bounds.getWidth())),
                              juce::Justification::topLeft, 2);
        }
        else
        {
            bounds.removeFromTop (20);
        }

        bounds.removeFromTop (th::spacing::sm);
        layoutQuizButtons (bounds);

        if (question != nullptr)
            for (size_t i = 0; i < optionBounds.size() && i < (size_t) question->options.size(); ++i)
            {
                const bool hovered = (int) i == hoveredOption;
                g.setColour (hovered ? th::colour::accentMuted : th::colour::surfaceRaised);
                g.fillRoundedRectangle (optionBounds[i].toFloat(), th::radius::sm);

                g.setColour (th::colour::textPrimary);
                g.setFont (th::type::makeFont (th::type::body, hovered));
                g.drawFittedText (juce::String::charToString ((juce::juce_wchar) ("ABCD"[i % 4]))
                                      + ") " + question->options[(int) i],
                                  optionBounds[i].reduced (10, 0), juce::Justification::centredLeft, 1);
            }

        if (! optionBounds.empty())
            bounds.removeFromTop ((int) optionBounds.size() * (32 + th::spacing::xs));
        bounds.removeFromTop (th::spacing::sm);

        // The verdict replaces the instruction once the quiz is over.
        if (quizState.finished)
        {
            g.setColour (quizState.passed ? th::colour::success : th::colour::danger);
            g.setFont (th::type::makeFont (th::type::body, true));
            g.drawFittedText (quizState.message, bounds.removeFromTop (36),
                              juce::Justification::topLeft, 2);
        }
    }

    juce::String quizInstruction() const
    {
        return juce::String::fromUTF8 ("Responda uma questão por vez.");
    }

    const QuizQuestion* currentQuestion() const
    {
        if (quizExercise == nullptr)
            return nullptr;

        const int i = quizState.currentQuestion;
        if (i < 0 || i >= (int) quizExercise->quiz.size())
            return nullptr;

        return &quizExercise->quiz[(size_t) i];
    }

    // Lays out the clickable option rows; they are painted (not child buttons)
    // so the layout follows the painted flow. `optionBounds` is filled here and
    // read back by the mouse handlers.
    void layoutQuizButtons (juce::Rectangle<int> area)
    {
        optionBounds.clear();
        for (int i = 0; i < quizOptionCount(); ++i)
        {
            optionBounds.push_back (area.removeFromTop (32));
            area.removeFromTop (th::spacing::xs);
        }
    }

    int quizOptionCount() const
    {
        const auto* question = currentQuestion();
        return question != nullptr ? question->options.size() : 0;
    }

    void mouseDown (const juce::MouseEvent& e) override
    {
        for (size_t i = 0; i < optionBounds.size(); ++i)
        {
            if (optionBounds[i].contains (e.getPosition()))
            {
                if (onAnswerOption != nullptr)
                    onAnswerOption ((int) i);
                return;
            }
        }
    }

    void mouseMove (const juce::MouseEvent& e) override
    {
        int hovered = -1;
        for (size_t i = 0; i < optionBounds.size(); ++i)
            if (optionBounds[i].contains (e.getPosition()))
                hovered = (int) i;

        if (hovered != hoveredOption)
        {
            hoveredOption = hovered;
            repaint();
        }
    }

    void mouseExit (const juce::MouseEvent&) override
    {
        if (hoveredOption != -1)
        {
            hoveredOption = -1;
            repaint();
        }
    }

    const CourseModule* current = nullptr;
    const LessonBlock* currentTopic = nullptr;
    const Exercise* currentExercise = nullptr;
    const Exercise* quizExercise = nullptr;
    course::QuizState quizState;
    std::vector<juce::Rectangle<int>> optionBounds;
    int hoveredOption = -1;
    bool showOverviewLessons = false;
    juce::String lockedMessage;
};

// A topic (explanation block) under a module. Selecting it loads its detail.
class ModuleComponent::TopicTreeItem final : public juce::TreeViewItem
{
public:
    TopicTreeItem (ModuleComponent& owner, int moduleNumber, int topicIndex,
                   juce::String topicId, juce::String topicTitle)
        : ownerRef (owner), module (moduleNumber), index (topicIndex),
          id (std::move (topicId)), title (std::move (topicTitle))
    {}

    bool mightContainSubItems() override { return false; }
    int getItemHeight() const override { return 24; }

    void itemSelectionChanged (bool isNowSelected) override
    {
        if (isNowSelected && ! ownerRef.suppressTreeCallbacks)
            ownerRef.selectTopic (module, index);
    }

    // A click always loads the topic, even when the item was already selected
    // (the module view pre-highlights the last topic read, REQ-020).
    void itemClicked (const juce::MouseEvent&) override
    {
        if (! ownerRef.suppressTreeCallbacks)
            ownerRef.selectTopic (module, index);
    }

    void paintItem (juce::Graphics& g, int width, int height) override
    {
        g.setColour (isSelected() ? th::colour::textPrimary : th::colour::textSecondary);
        g.setFont (th::type::makeFont (th::type::body, isSelected()));
        g.drawFittedText (id + ". " + title, 4, 0, width - 8, height,
                          juce::Justification::centredLeft, 1);
    }

private:
    ModuleComponent& ownerRef;
    int module = 0;
    int index = 0;
    juce::String id;
    juce::String title;
};

// A module node in the left menu. Expanding it reveals its topics.
class ModuleComponent::SubjectTreeItem final : public juce::TreeViewItem
{
public:
    SubjectTreeItem (ModuleComponent& owner, const CourseModule& module)
        : ownerRef (owner), number (module.number), title (module.title),
          implemented (module.implemented)
    {
        setOpen (false);

        if (implemented)
            for (int i = 0; i < (int) module.lessons.size(); ++i)
                addSubItem (new TopicTreeItem (owner, number, i, module.lessons[(size_t) i].id,
                                               module.lessons[(size_t) i].title));
    }

    int getModuleNumber() const noexcept { return number; }
    bool isImplemented() const noexcept { return implemented; }

    bool mightContainSubItems() override { return implemented; }

    int getItemHeight() const override { return 46; }

    void itemOpennessChanged (bool isNowOpen) override
    {
        // Opening a module reveals its topics but must not load one by itself
        // (REQ-019): the centre stays on the module context until a topic is
        // clicked. Re-opening a module restores the topic last read in it
        // (REQ-020); the memory is per module, so it survives collapsing.
        if (isNowOpen && ! ownerRef.suppressTreeCallbacks)
            ownerRef.showModule (number);
    }

    void itemClicked (const juce::MouseEvent&) override
    {
        if (! implemented)
            return;

        // The first click expands the module (topics appear, centre still empty);
        // the second collapses it and returns to the module view. Selecting a
        // topic is what loads the content.
        if (isOpen())
        {
            setOpen (false);

            if (! ownerRef.suppressTreeCallbacks)
                ownerRef.showModule (number);
        }
        else
        {
            setOpen (true);
        }
    }

    void itemSelectionChanged (bool isNowSelected) override
    {
        if (isNowSelected && ! ownerRef.suppressTreeCallbacks)
            ownerRef.showModule (number);
    }

    void paintItem (juce::Graphics& g, int width, int height) override
    {
        const bool unlocked = ownerRef.progressStore.isModuleUnlocked (number);
        const bool isSel = isSelected();

        if (isSel)
        {
            g.setColour (th::colour::accentMuted);
            g.fillRoundedRectangle (juce::Rectangle<float> (0.0f, 0.0f, (float) width, (float) height).reduced (2.0f),
                                    th::radius::sm);
        }

        g.setColour (isSel ? th::colour::textPrimary
                            : (unlocked ? th::colour::textSecondary : th::colour::textDisabled));
        g.setFont (th::type::makeFont (th::type::body, true));
        g.drawText (juce::String::fromUTF8 ("Módulo ") + juce::String (number)
                        + (implemented ? juce::String() : juce::String::fromUTF8 ("  ·  em preparação")),
                    8, 4, width - 16, 20, juce::Justification::centredLeft, false);

        g.setColour (implemented ? th::colour::textSecondary : th::colour::accentMuted);
        g.setFont (th::type::makeFont (th::type::caption));
        g.drawFittedText (title, 8, 24, width - 16, 20, juce::Justification::centredLeft, 1);

        if (! unlocked)
        {
            g.setColour (th::colour::textDisabled);
            g.setFont (th::type::makeFont (th::type::caption, true));
            g.drawText (juce::String::fromUTF8 ("bloqueado"), width - 90, 4, 78, 20,
                        juce::Justification::centredRight, false);
        }
    }

private:
    ModuleComponent& ownerRef;
    int number = 0;
    juce::String title;
    bool implemented = false;
};

ModuleComponent::ModuleComponent (AudioEngine& engine)
    : audioEngine (engine)
{
    titleLabel.setText (juce::String::fromUTF8 ("Módulos do curso"), juce::dontSendNotification);
    titleLabel.setFont (th::type::makeFont (th::type::title, true));
    titleLabel.setColour (juce::Label::textColourId, th::colour::textPrimary);
    addAndMakeVisible (titleLabel);

    subtitleLabel.setText (juce::String::fromUTF8 ("Assunto à esquerda, explicação no centro, prática à direita"),
                           juce::dontSendNotification);
    subtitleLabel.setFont (th::type::makeFont (th::type::body));
    subtitleLabel.setColour (juce::Label::textColourId, th::colour::textSecondary);
    addAndMakeVisible (subtitleLabel);

    closeButton.onClick = [this] { if (onCloseRequested != nullptr) onCloseRequested(); };
    addAndMakeVisible (closeButton);

    listToggle.setClickingTogglesState (true);
    listToggle.setToggleState (true, juce::dontSendNotification);
    listToggle.onClick = [this] { setListVisible (listToggle.getToggleState()); };
    addAndMakeVisible (listToggle);

    practiceToggle.setClickingTogglesState (true);
    practiceToggle.setToggleState (true, juce::dontSendNotification);
    practiceToggle.onClick = [this] { setPracticeVisible (practiceToggle.getToggleState()); };
    addAndMakeVisible (practiceToggle);

    subjectTree.setRootItemVisible (false);
    subjectTree.setDefaultOpenness (false);
    subjectTree.setMultiSelectEnabled (false);
    subjectTree.setIndentSize (14);
    subjectTree.setColour (juce::TreeView::backgroundColourId, th::colour::surface);
    addAndMakeVisible (subjectTree);

    contentView = std::make_unique<ContentView>();
    contentViewport.setViewedComponent (contentView.get(), false);
    contentViewport.setScrollBarsShown (true, false);
    addAndMakeVisible (contentViewport);

    practicePanel = std::make_unique<PracticePanel> (audioEngine);
    practicePanel->onGateResult = [this] (int moduleNumber, bool passed)
    {
        progressStore.recordGateResult (moduleNumber, passed);
        refreshSubjectTree();
    };
    practicePanel->onExerciseSelected = [this] (const Exercise* exercise) { showExercise (exercise); };

    // The quiz runs in the centre: mirror its state whenever it advances, and
    // route the answer chosen there back to the session owned by the pane.
    practicePanel->onQuizChanged = [this] { syncQuizToCentre(); };
    contentView->onAnswerOption = [this] (int optionIndex)
    {
        if (practicePanel != nullptr)
            practicePanel->answerQuizOption (optionIndex);
    };
    addAndMakeVisible (*practicePanel);

    hintLabel.setFont (th::type::makeFont (th::type::caption));
    hintLabel.setColour (juce::Label::textColourId, th::colour::textDisabled);
    hintLabel.setJustificationType (juce::Justification::centredLeft);
    hintLabel.setText (juce::String::fromUTF8 (
        "Progressão linear: conclua o gate (≥90%) do módulo atual para abrir o próximo."),
        juce::dontSendNotification);
    addAndMakeVisible (hintLabel);

    buildTree();

    // Select and expand the first module so its topics are visible, but do not
    // load one: the centre starts on the module context only (REQ-019).
    if (subjectRoot != nullptr && subjectRoot->getNumSubItems() > 0)
        if (auto* first = subjectRoot->getSubItem (0))
        {
            first->setOpen (true);
            first->setSelected (true, true);
        }

    startTimerHz (20); // drains detected notes while an exercise runs
}

ModuleComponent::~ModuleComponent()
{
    stopTimer();
    subjectTree.setRootItem (nullptr);
}

void ModuleComponent::buildTree()
{
    subjectRoot = std::make_unique<SubjectRootItem>();

    for (const auto& module : ModuleCatalog::getModules())
        subjectRoot->addSubItem (new SubjectTreeItem (*this, module));

    subjectTree.setRootItem (subjectRoot.get());
}

void ModuleComponent::timerCallback()
{
    if (practicePanel != nullptr)
        practicePanel->poll();
}

void ModuleComponent::refreshSubjectTree()
{
    subjectTree.repaint();
}

void ModuleComponent::setListVisible (bool shouldBeVisible)
{
    listVisible = shouldBeVisible;
    listToggle.setToggleState (shouldBeVisible, juce::dontSendNotification);
    subjectTree.setVisible (shouldBeVisible);
    listToggle.setButtonText (shouldBeVisible ? juce::String::fromUTF8 ("Módulos")
                                              : juce::String::fromUTF8 ("> Módulos"));
    resized();
}

void ModuleComponent::setPracticeVisible (bool shouldBeVisible)
{
    practiceVisible = shouldBeVisible;
    practiceToggle.setToggleState (shouldBeVisible, juce::dontSendNotification);
    practicePanel->setVisible (shouldBeVisible);
    practiceToggle.setButtonText (shouldBeVisible ? juce::String::fromUTF8 ("Prática")
                                                  : juce::String::fromUTF8 ("Prática <"));
    resized();
}

void ModuleComponent::showModule (int number)
{
    const auto* module = ModuleCatalog::findModule (number);
    const bool unlocked = module != nullptr && progressStore.isModuleUnlocked (module->number);

    contentView->setLockedMessage (juce::String::fromUTF8 ("Módulo ") + juce::String (number)
                                     + juce::String::fromUTF8 (" bloqueado.\nConclua o gate do módulo ")
                                     + juce::String (juce::jmax (1, number - 1))
                                     + juce::String::fromUTF8 (" com ≥90% para abrir."));

    selection = {};
    selection.module = unlocked ? module : nullptr;

    const int remembered = (unlocked && module != nullptr) ? recalledTopic (number) : -1;
    const bool hasMemory = module != nullptr && remembered >= 0
                             && remembered < (int) module->lessons.size();

    // Opening a module never auto-loads a topic: the centre stays on the module
    // context (REQ-019). A module already read lists its topics again, and the
    // right pane keeps that topic's exercises (REQ-020); a module never read has
    // no memory and stays blank of lesson content.
    contentView->setOverviewLessonsVisible (hasMemory);

    if (practicePanel != nullptr)
    {
        practicePanel->setModule (unlocked ? module : nullptr);

        // The right pane depends on the left one (client): it only knows what to
        // show after a topic is selected. Opening a module without a topic keeps
        // it blank; only a module already read restores that topic's exercises.
        if (hasMemory)
            practicePanel->setTopicFilter (module->lessons[(size_t) remembered].id);
    }

    // Highlight the remembered topic in the tree without loading it, so the
    // student sees where they stopped while the centre stays on the overview.
    if (hasMemory)
        restoreTopicInTree (number, remembered);

    updateContent();

    if (! unlocked && module != nullptr)
    {
        hintLabel.setColour (juce::Label::textColourId, th::colour::danger);
        hintLabel.setText (juce::String::fromUTF8 ("Módulo ") + juce::String (module->number)
                             + juce::String::fromUTF8 (" bloqueado: conclua o gate do módulo ")
                             + juce::String (module->number - 1)
                             + juce::String::fromUTF8 (" (≥90%) para abrir."),
                           juce::dontSendNotification);
    }
    else
    {
        hintLabel.setColour (juce::Label::textColourId, th::colour::textDisabled);
        hintLabel.setText (juce::String::fromUTF8 (
            "Progressão linear: conclua o gate (≥90%) do módulo atual para abrir o próximo."),
            juce::dontSendNotification);
    }
}

void ModuleComponent::selectTopic (int moduleNumber, int topicIndex)
{
    const auto* module = ModuleCatalog::findModule (moduleNumber);
    if (module == nullptr || ! progressStore.isModuleUnlocked (moduleNumber))
        return;

    if (topicIndex < 0 || topicIndex >= (int) module->lessons.size())
        return;

    selection.module = module;
    selection.topic = &module->lessons[(size_t) topicIndex];
    selection.exercise = nullptr;

    // The student read this topic, so the module now remembers it (REQ-020).
    rememberTopic (moduleNumber, topicIndex);

    if (practicePanel != nullptr)
        practicePanel->setTopicFilter (module->lessons[(size_t) topicIndex].id);

    updateContent();
}

void ModuleComponent::rememberTopic (int moduleNumber, int topicIndex)
{
    lastTopicPerModule[moduleNumber] = topicIndex;
}

int ModuleComponent::recalledTopic (int moduleNumber) const
{
    const auto it = lastTopicPerModule.find (moduleNumber);
    return it == lastTopicPerModule.end() ? -1 : it->second;
}

void ModuleComponent::restoreTopicInTree (int moduleNumber, int topicIndex)
{
    if (subjectRoot == nullptr)
        return;

    const juce::ScopedValueSetter<bool> guard (suppressTreeCallbacks, true);

    for (int i = 0; i < subjectRoot->getNumSubItems(); ++i)
    {
        if (auto* moduleItem = dynamic_cast<SubjectTreeItem*> (subjectRoot->getSubItem (i)))
        {
            if (moduleItem->getModuleNumber() != moduleNumber)
                continue;

            if (auto* topicItem = moduleItem->getSubItem (topicIndex))
                topicItem->setSelected (true, true);

            return;
        }
    }
}

void ModuleComponent::showExercise (const Exercise* exercise)
{
    selection.exercise = exercise;
    updateContent();
}

void ModuleComponent::updateContent()
{
    contentView->setSelection (selection.module, selection.topic, selection.exercise);
    syncQuizToCentre();
    contentView->setSize (contentViewport.getMaximumVisibleWidth(), contentView->getRequiredHeight());
}

void ModuleComponent::syncQuizToCentre()
{
    if (practicePanel == nullptr)
        return;

    // The quiz is demonstrated in the centre only when the armed exercise is a
    // questionnaire; any other exercise (or none) clears the quiz state.
    if (selection.exercise != nullptr && selection.exercise->isQuiz())
    {
        contentView->setQuiz (selection.exercise, practicePanel->getQuizState());
        contentView->setSize (contentViewport.getMaximumVisibleWidth(), contentView->getRequiredHeight());
    }
    else
    {
        contentView->setQuiz (nullptr, {});
        contentView->setSize (contentViewport.getMaximumVisibleWidth(), contentView->getRequiredHeight());
    }
}

void ModuleComponent::paint (juce::Graphics& g)
{
    g.fillAll (th::colour::background);
}

void ModuleComponent::resized()
{
    auto bounds = getLocalBounds().reduced (th::spacing::lg);

    hintLabel.setBounds (bounds.removeFromBottom (20));
    bounds.removeFromBottom (th::spacing::sm);

    auto header = bounds.removeFromTop (64);
    closeButton.setBounds (header.removeFromRight (110).withSizeKeepingCentre (110, 34));
    header.removeFromRight (th::spacing::md);
    practiceToggle.setBounds (header.removeFromRight (110).withSizeKeepingCentre (110, 34));
    header.removeFromRight (th::spacing::sm);
    listToggle.setBounds (header.removeFromRight (110).withSizeKeepingCentre (110, 34));
    header.removeFromRight (th::spacing::md);
    titleLabel.setBounds (header.removeFromTop (32));
    subtitleLabel.setBounds (header.removeFromTop (22));

    bounds.removeFromTop (th::spacing::md);

    // Either side pane can be collapsed to give the centre the width.
    if (listVisible)
    {
        subjectTree.setBounds (bounds.removeFromLeft (260));
        bounds.removeFromLeft (th::spacing::md);
    }

    if (practiceVisible)
    {
        practicePanel->setBounds (bounds.removeFromRight (340));
        bounds.removeFromRight (th::spacing::md);
    }

    contentViewport.setBounds (bounds);
    contentView->setSize (contentViewport.getMaximumVisibleWidth(), contentView->getRequiredHeight());
}

} // namespace cursomusica
