#include "Course/Content/Topics.h"

#include "Course/NoteMath.h"

namespace cursomusica::content
{

juce::String U (const char* text)
{
    return juce::String::fromUTF8 (text);
}

ContentItem tbl (std::initializer_list<const char*> header,
                 std::initializer_list<std::initializer_list<const char*>> rows)
{
    juce::StringArray columns;
    for (auto* cell : header)
        columns.add (U (cell));

    std::vector<juce::StringArray> body;
    for (const auto& row : rows)
    {
        juce::StringArray line;
        for (auto* cell : row)
            line.add (U (cell));
        body.push_back (std::move (line));
    }

    return ContentItem::table (std::move (columns), std::move (body));
}

std::vector<int> midiNotes (std::initializer_list<const char*> names)
{
    std::vector<int> out;
    out.reserve (names.size());
    for (auto* name : names)
        out.push_back (music::noteNameToMidi (juce::String (name)));
    return out;
}

ContentItem aud (std::initializer_list<const char*> names, const char* caption)
{
    return ContentItem::audio (midiNotes (names), U (caption));
}

ContentItem part (const char* imageName, std::initializer_list<const char*> names, const char* caption)
{
    return ContentItem::score (U (imageName), midiNotes (names), U (caption));
}

} // namespace cursomusica::content
