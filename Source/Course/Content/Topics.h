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

// MIDI notes from pitch names ("C4", "E4"), for the playable examples below.
std::vector<int> midiNotes (std::initializer_list<const char*> names);

// A playable audio example (REQ-004): the app plays the notes when the student
// presses the button under `caption`. Used to demonstrate an interval by ear.
ContentItem aud (std::initializer_list<const char*> names, const char* caption);

// A score with its audio (REQ-004): `imageName` is the embedded score image, the
// notes are what the app plays for it. Every score in the course carries audio.
ContentItem part (const char* imageName, std::initializer_list<const char*> names, const char* caption);

std::vector<ContentItem> topicA();  // Partes da guitarra e do violão
std::vector<ContentItem> topicB();  // Notas musicais
std::vector<ContentItem> topicC();  // Sustenidos e bemóis
std::vector<ContentItem> topicD();  // Localização das notas no braço
std::vector<ContentItem> topicE();  // Pestanas
std::vector<ContentItem> topicF();  // Sistema 5 (CAGED)
std::vector<ContentItem> topicG();  // Organização das tonalidades
std::vector<ContentItem> topicH();  // Introdução ao cifrado
std::vector<ContentItem> topicI();  // Rítmica: pulsação e figuras

// Module 2 (Etapa 2 — teoria dos intervalos e percepção musical).
std::vector<ContentItem> topic2A();  // Intervalos musicais
std::vector<ContentItem> topic2B();  // Quadro móvel de intervalos
std::vector<ContentItem> topic2C();  // Maiores, menores, justos, aumentados e diminutos
std::vector<ContentItem> topic2D();  // Percepção de intervalos
std::vector<ContentItem> topic2E();  // Terças, quartas, quintas, sextas, sétimas e nonas
std::vector<ContentItem> topic2F();  // Relação entre intervalos e construção de acordes
std::vector<ContentItem> topic2G();  // Cantar e tocar os intervalos
std::vector<ContentItem> topic2H();  // Identificar intervalos no instrumento e de ouvido

// Module 3 (Etapa 3 — ritmo, leitura e levadas).
std::vector<ContentItem> topic3A();  // Leitura rítmica e convenções de escrita
std::vector<ContentItem> topic3B();  // Pulsação e subdivisão
std::vector<ContentItem> topic3C();  // Cifrado com divisão
std::vector<ContentItem> topic3D();  // Células rítmicas e acentuações
std::vector<ContentItem> topic3E();  // Levadas com palheta
std::vector<ContentItem> topic3F();  // Levadas com os dedos e mapa da mão direita
std::vector<ContentItem> topic3G();  // Compassos simples, compostos e fórmulas incomuns
std::vector<ContentItem> topic3H();  // Sílabas rítmicas (Konokol), percussões e efeito sanfona
// Module 4 (Etapa 4 — construção de acordes: tríades e tétrades).
std::vector<ContentItem> topic4A();  // Tríades maiores e menores
std::vector<ContentItem> topic4B();  // Tríades aumentadas e diminutas
std::vector<ContentItem> topic4C();  // Tríades abertas e fechadas
std::vector<ContentItem> topic4D();  // Inversões
std::vector<ContentItem> topic4E();  // Tétrades
std::vector<ContentItem> topic4F();  // Formação de acordes
std::vector<ContentItem> topic4G();  // Sistema 5 (CAGED) e famílias de acordes
std::vector<ContentItem> topic4H();  // As cinco fases das famílias
std::vector<ContentItem> topic4I();  // Acordes clean e distribuição pelo braço
// Module 5 (Etapa 5 — campo harmônico maior e funções harmônicas).
std::vector<ContentItem> topic5A();  // Escala maior
std::vector<ContentItem> topic5B();  // Campo harmônico maior e graus da escala
std::vector<ContentItem> topic5C();  // Função tônica
std::vector<ContentItem> topic5D();  // Função subdominante
std::vector<ContentItem> topic5E();  // Função dominante
std::vector<ContentItem> topic5F();  // Acordes relativos
std::vector<ContentItem> topic5G();  // Armaduras de clave e tonalidades
std::vector<ContentItem> topic5H();  // Cadências e progressões harmônicas
std::vector<ContentItem> topic5I();  // Modos gerados pela escala maior
std::vector<ContentItem> topic5J();  // Harmonização da escala maior
// Module 6 (Etapa 6 — escalas menores e campos harmônicos).
std::vector<ContentItem> topic6A();  // Escala menor natural
std::vector<ContentItem> topic6B();  // Escala menor harmônica
std::vector<ContentItem> topic6C();  // Modos da menor harmônica
std::vector<ContentItem> topic6D();  // Escala menor melódica
std::vector<ContentItem> topic6E();  // Modos da menor melódica
std::vector<ContentItem> topic6F();  // Campos harmônicos menores e funções
std::vector<ContentItem> topic6G();  // Subdominantes menores
std::vector<ContentItem> topic6H();  // Relações entre os campos maior e menor
std::vector<ContentItem> topic6I();  // Modos dórico, frígio, lídio, mixolídio e lócrio
// Module 7 (Etapa 7 — empilhamentos, estruturas modais e sonoridades).
std::vector<ContentItem> topic7A();  // Empilhamentos de terças
std::vector<ContentItem> topic7B();  // Empilhamentos quartais
std::vector<ContentItem> topic7C();  // Outros empilhamentos
std::vector<ContentItem> topic7D();  // Estruturas modais e tríades do meio
std::vector<ContentItem> topic7E();  // Acordes e famílias modais
std::vector<ContentItem> topic7F();  // Modos estruturais pelo CAGED
std::vector<ContentItem> topic7G();  // Dórico, Lídio e Mixolídio
std::vector<ContentItem> topic7H();  // Mixolídio sus e Mixolídio #4
std::vector<ContentItem> topic7I();  // Lócrio 9 e Alterado (Alt.7)
std::vector<ContentItem> topic7J();  // Aplicações modais no rock e pop-rock
// Module 8 (Etapa 8 — dominantes, cadências e substituições harmônicas).
std::vector<ContentItem> topic8A();  // Dominante V7
std::vector<ContentItem> topic8B();  // Dominantes secundários
std::vector<ContentItem> topic8C();  // Dominantes alterados e resoluções
std::vector<ContentItem> topic8D();  // SubV7
std::vector<ContentItem> topic8E();  // SubIIm
std::vector<ContentItem> topic8F();  // Empréstimos modais
std::vector<ContentItem> topic8G();  // Dilatação do campo harmônico maior
std::vector<ContentItem> topic8H();  // Dilatação do campo harmônico menor
std::vector<ContentItem> topic8I();  // Progressão II-V-I maior e menor
std::vector<ContentItem> topic8J();  // Identificação de situações que não são II-V-I

} // namespace cursomusica::content
