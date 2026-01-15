#pragma once
#include <string>


#include "../structs/EffectType.h"
#include "../structs/EffectTrigger.h"

using DamageDone = std::array<float, 3>;

class Entity;
class Effect {
protected:
    const std::string name;
    const EffectType effect_type;
public:
    virtual ~Effect() = default;

    Effect(std::string name, EffectType effect_type);

    [[nodiscard]] std::string get_name() const noexcept;
    [[nodiscard]] EffectType get_effect_type() const noexcept;
    [[nodiscard]] virtual EffectTrigger get_effect_trigger() const noexcept = 0;
    [[nodiscard]] virtual DamageDone compute_premitigation_damage(const Entity& source, const Entity& target) const = 0;
};
