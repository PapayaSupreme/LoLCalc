#include "Stack.h"

#include <map>

Stack::Stack(std::string name, const EffectTrigger effect_trigger,
             std::map<uint16_t, const Effect *> effects, const bool stop_at_max_count)
: name(std::move(name)), effect_trigger(effect_trigger),
effects(std::move(effects)), stop_at_max_count(stop_at_max_count) {
}

std::string Stack::get_name() const noexcept { return name; }
EffectTrigger Stack::get_effect_trigger() const noexcept { return effect_trigger; }
std::map<uint16_t, const Effect *> Stack::get_effects() const noexcept { return effects; }
std::unordered_map<const Entity *, uint16_t> Stack::get_entities_stack_count() const noexcept { return entities_stack_count; }
bool Stack::get_stop_at_max_count() const noexcept { return stop_at_max_count; }

const Effect *Stack::add_entity_stack_count(const Entity *entity) noexcept {
    if (const uint16_t count = entities_stack_count[entity]; !(stop_at_max_count && count == get_effects().rbegin()->first)) {
        ++entities_stack_count[entity];
        if (effects.contains(count+1)) {
            return effects[count+1];
        }
    }
    return nullptr;
}

void Stack::reset_entity_stack_count(const Entity *entity, bool is_resilient) noexcept {
    if (is_resilient) {
        entities_stack_count[entity] = 0;
    } else {
        entities_stack_count.erase(entity);
    }
}