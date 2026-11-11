#include "Course/Content/Topics.h"

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

} // namespace cursomusica::content
