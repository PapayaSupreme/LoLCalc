#include "Effect.h"

Effect::Effect(std::string name, const EffectType effect_type)
    : name(std::move(name)), effect_type(effect_type) {}

std::string Effect::get_name() const noexcept { return name; }
EffectType Effect::get_effect_type() const noexcept { return effect_type; }
