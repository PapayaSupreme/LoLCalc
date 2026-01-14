#pragma once
#include <map>
#include <string>
#include <unordered_map>

#include "../structs/EffectTrigger.h"


class Entity;
class Champion;
class Effect;

class Stack {
protected:
    const std::string name;
    const EffectTrigger effect_trigger;
    std::unordered_map<const Entity*, uint16_t> entities_stack_count;
    std::map<uint16_t, const Effect*> effects;
    const bool stop_at_max_count;
public:
    Stack(std::string name, EffectTrigger effect_trigger,
        std::map<uint16_t, const Effect *> effects, bool stop_at_max_count);

    [[nodiscard]] std::string get_name() const noexcept;
    [[nodiscard]] EffectTrigger get_effect_trigger() const noexcept;
    [[nodiscard]] std::map<uint16_t, const Effect *> get_effects() const noexcept;
    [[nodiscard]] std::unordered_map<const Entity *, uint16_t> get_entities_stack_count() const noexcept;
    [[nodiscard]] bool get_stop_at_max_count() const noexcept;

    /*
     *Adds one to the counter of the specified champion, and returns either a pointer of either null or the effect to apply.
     */
    const Effect* add_entity_stack_count(const Entity *entity) noexcept;

    void reset_entity_stack_count(const Entity *entity, bool is_resilient) noexcept;
};


