#include "Audio/PluginChain.h"

namespace cursomusica
{

PluginChain::PluginChain() = default;

PluginChain::~PluginChain()
{
    clear();
}

void PluginChain::publish (const SlotArray& next)
{
    const int current = activeIndex.load();
    const int target = 1 - current;

    slots[(size_t) target] = next;
    activeIndex.store (target, std::memory_order_release);

    waitForAudioThread (target);

    pendingDelete.clear();
}

void PluginChain::waitForAudioThread (int publishedIndex)
{
    // When the device is stopped no callback will arrive, and nothing is
    // reading the retired array, so deletion is safe immediately.
    if (! deviceRunning.load())
        return;

    const auto deadline = juce::Time::getMillisecondCounter() + 500;

    while (lastProcessedIndex.load (std::memory_order_acquire) != publishedIndex
           && juce::Time::getMillisecondCounter() < deadline)
    {
        juce::Thread::sleep (1);
    }
}

void PluginChain::addPlugin (std::unique_ptr<juce::AudioPluginInstance> instance)
{
    if (instance == nullptr || (int) owned.size() >= maxPlugins)
        return;

    instance->prepareToPlay (currentSampleRate, currentBlockSize);
    owned.push_back (std::move (instance));

    SlotArray next;
    next.count = (int) owned.size();
    for (int i = 0; i < next.count; ++i)
        next.plugins[(size_t) i] = owned[(size_t) i].get();

    publish (next);
}

void PluginChain::removePlugin (int index)
{
    if (index < 0 || index >= (int) owned.size())
        return;

    pendingDelete.push_back (std::move (owned[(size_t) index]));
    owned.erase (owned.begin() + index);

    SlotArray next;
    next.count = (int) owned.size();
    for (int i = 0; i < next.count; ++i)
        next.plugins[(size_t) i] = owned[(size_t) i].get();

    publish (next);
}

void PluginChain::clear()
{
    for (auto& instance : owned)
        pendingDelete.push_back (std::move (instance));
    owned.clear();

    publish (SlotArray {});
}

void PluginChain::prepare (double sampleRate, int maximumBlockSize)
{
    currentSampleRate = sampleRate > 0.0 ? sampleRate : 44100.0;
    currentBlockSize = maximumBlockSize > 0 ? maximumBlockSize : 512;

    for (auto& instance : owned)
        if (instance != nullptr)
            instance->prepareToPlay (currentSampleRate, currentBlockSize);
}

void PluginChain::process (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi) noexcept
{
    const int index = activeIndex.load (std::memory_order_acquire);
    const auto& active = slots[(size_t) index];

    for (int i = 0; i < active.count; ++i)
    {
        auto* plugin = active.plugins[(size_t) i];
        if (plugin == nullptr)
            continue;

        // A plugin with no inputs (e.g. an instrument) would silence the chain,
        // so skip it rather than feed it the signal.
        if (plugin->getTotalNumInputChannels() == 0)
            continue;

        plugin->processBlock (buffer, midi);
    }

    // Publish only after processing, so the message thread can never free an
    // instance that a callback is still using.
    lastProcessedIndex.store (index, std::memory_order_release);
}

int PluginChain::getNumPlugins() const
{
    return (int) owned.size();
}

juce::AudioPluginInstance* PluginChain::getPlugin (int index) const
{
    if (index < 0 || index >= (int) owned.size())
        return nullptr;

    return owned[(size_t) index].get();
}

} // namespace cursomusica
