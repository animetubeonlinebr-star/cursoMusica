#pragma once

#include <initializer_list>
#include <vector>

#include "Course/Module.h"

// The detailed explanation of each module-1 topic (A..I), one function per
// topic. Content lives in the Topic*.cpp files next to this header; the source
// of truth for the wording is docs/MUSIC.md (owner: musician).
//
// A topic must carry at least `content::minPages` "pages" of explanation (see
// minTopicChars) so the central panel really teaches the subject instead of
// showing a one-line summary. tests/TestMain.cpp enforces it.
namespace cursomusica::content
{

// One rendered page of the central panel, in characters of body text. Used to
// turn the client's "at least five pages per topic" into a checkable rule.
inline constexpr int charsPerPage = 1800;
inline constexpr int minPages = 5;
inline constexpr int minTopicChars = charsPerPage * minPages;

juce::String U (const char* text);

// Shorthands so the content files read like the text they carry.
inline ContentItem h (const char* t) { return ContentItem::heading (U (t)); }
inline ContentItem p (const char* t) { return ContentItem::paragraph (U (t)); }
inline ContentItem b (const char* t) { return ContentItem::bullet (U (t)); }
inline ContentItem c (const char* t) { return ContentItem::callout (U (t)); }

// A JPG diagram embedded in the binary, by its file stem (see Diagrams.h and
// tools/make_diagrams.py). `caption` is optional and shown under the image.
inline ContentItem img (const char* name, const char* caption = "")
{
    return ContentItem::image (U (name), U (caption));
}

ContentItem tbl (std::initializer_list<const char*> header,
                 std::initializer_list<std::initializer_list<const char*>> rows);

std::vector<ContentItem> topicA();  // Partes da guitarra e do violão
std::vector<ContentItem> topicB();  // Notas musicais
std::vector<ContentItem> topicC();  // Sustenidos e bemóis
std::vector<ContentItem> topicD();  // Localização das notas no braço
std::vector<ContentItem> topicE();  // Pestanas
std::vector<ContentItem> topicF();  // Sistema 5 (CAGED)
std::vector<ContentItem> topicG();  // Organização das tonalidades
std::vector<ContentItem> topicH();  // Introdução ao cifrado
std::vector<ContentItem> topicI();  // Rítmica: pulsação e figuras

} // namespace cursomusica::content
