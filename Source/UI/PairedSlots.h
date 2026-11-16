#pragma once

#include <cstddef>
#include <vector>

namespace cursomusica::ui
{

// Keeps two parallel arrays the same length.
//
// The central pane remembers, for each "Ouvir exemplo" button, both its
// rectangle and the notes that button plays. Both are rebuilt on every paint and
// indexed by the button's position, so they must always have the same length.
// Growing only the rectangle list left the notes list short and the next write
// landed one past its end, corrupting the heap and closing the app as soon as a
// topic with audio or a score was opened (every topic of modules 2..10).
template <typename Slot, typename Payload>
inline void ensurePairedSlots (std::vector<Slot>& slots, std::vector<Payload>& payloads,
                               std::size_t index)
{
    while (slots.size() <= index)
        slots.emplace_back();

    while (payloads.size() <= index)
        payloads.emplace_back();
}

} // namespace cursomusica::ui
