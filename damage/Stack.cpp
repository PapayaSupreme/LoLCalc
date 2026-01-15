#include "Stack.h"

Stack::Stack(std::string name, const EffectTrigger effect_trigger,
             std::multimap<uint16_t, const Effect *> effects, const bool stop_at_max_count)
: name(std::move(name)), effect_trigger(effect_trigger),
effects(std::move(effects)), stop_at_max_count(stop_at_max_count) {
}

std::string Stack::get_name() const noexcept { return name; }
EffectTrigger Stack::get_effect_trigger() const noexcept { return effect_trigger; }
std::multimap<uint16_t, const Effect *> Stack::get_effects() const noexcept { return effects; }
std::unordered_map<const Entity *, uint16_t> Stack::get_entities_stack_count() const noexcept { return entities_stack_count; }
bool Stack::get_stop_at_max_count() const noexcept { return stop_at_max_count; }

std::vector<const Effect *> Stack::add_entity_stack_count(const Entity *entity) {
    uint16_t& count = entities_stack_count[entity];
    if (stop_at_max_count  && count >= effects.rbegin()->first) {
        return {};
    }

    ++count;

    std::vector<const Effect*> result;
    auto [fst, snd] = effects.equal_range(count);
    for (auto it = fst; it != snd; ++it) {
        result.push_back(it->second);
    }
    return result;
}

void Stack::reset_entity_stack_count(const Entity *entity, const bool is_resilient) noexcept {
    if (is_resilient) {
        entities_stack_count[entity] = 0;
    } else {
        entities_stack_count.erase(entity);
    }
}