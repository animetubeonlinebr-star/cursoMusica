#pragma once

#include <juce_core/juce_core.h>

#include <utility>

namespace cursomusica::course
{

// Human-readable label for a curated apostila, given the file stem the catalogue
// stores (CourseModule::sources). The stem stays the identifier — the app cites
// the file by it (REQ-006) — but a stem is not something to show a student: one
// of them carries a layout artifact from the site it came from
// ("p-classtruncatedtext-module-lineclamped-…"). The label is what the UI prints.
inline juce::String apostilaLabel (const juce::String& stem)
{
    static const std::pair<const char*, const char*> known[] = {
        { "pdf-mozart-mello-livroestudosdeguitarra4em1",
          "Mozart Mello — Livro de estudos de guitarra (4 em 1)" },
        { "pdf-fraseado-melodico",
          "Fraseado melódico" },
        { "pdf-desvendando-os-segredos-da-guitarra-fusion",
          "Desvendando os segredos da guitarra fusion — José Ricardo Santana" },
        { "pdf-caged-e-derivaoes-de-acordes-marcelo-mello-apostila-de-violao-e-guitarra-vol1",
          "CAGED e derivações de acordes — Marcelo Mello (vol. 1)" },
        { "pdf-teoria-elementar-da-musica-ricordi-osvaldo-lacerda",
          "Compêndio de Teoria Elementar da Música — Osvaldo Lacerda" },
        { "pdf-p-classtruncatedtext-module-lineclamped-85ulhh-style-max-lines5bohumil-med-teoria-da-musica-5-edicao-p",
          "Teoria da Música — Bohumil Med (5ª edição)" },
        { "pdf-manual-de-regulagem-e-manutenao-em-guitarra-contrabaixos-e-violoes-mozart-carvalho",
          "Manual de regulagem e manutenção — Mozart Carvalho" },
        { "pdf-mozart-mello-improvisacion-pop",
          "Mozart Mello — Improvisação pop" },
    };

    for (const auto& [key, label] : known)
        if (stem == key)
            return juce::String::fromUTF8 (label);

    // Unknown stem: never show the raw artifact. Drop the file prefix and the
    // site layout noise, then read the rest as words.
    auto readable = stem.replace ("pdf-", "");
    if (readable.contains ("classtruncatedtext"))
    {
        const int at = readable.indexOf ("max-lines");
        if (at >= 0)
            readable = readable.substring (at + 10);
        while (readable.startsWithChar ('-') || readable.startsWithChar ('5'))
            readable = readable.substring (1);
    }
    return readable.replaceCharacter ('-', ' ').trim();
}

} // namespace cursomusica::course
