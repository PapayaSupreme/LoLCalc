#include "Multiplier.h"

Multiplier::Multiplier(std::string name, const float multiplier)
    : Effect(std::move(name), EffectType::Multiplier), multiplier(multiplier) {}

float Multiplier::get_multiplier() const noexcept { return multiplier; }
EffectTrigger Multiplier::get_effect_trigger() const noexcept { return EffectTrigger::AfterAttack; }
DamageDone Multiplier::compute_premitigation_damage(const Entity& source, const Entity& target) const { return DamageDone {}; }
