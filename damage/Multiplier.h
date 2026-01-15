#pragma once
#include <array>
#include <string>

#include "Effect.h"

using DamageDone = std::array<float, 3>;

class Multiplier : public Effect {
protected:
    const float multiplier;
public:
    Multiplier(std::string name, float multiplier);

    [[nodiscard]] float get_multiplier() const noexcept;
    [[nodiscard]] EffectTrigger get_effect_trigger() const noexcept override;
    [[nodiscard]] DamageDone compute_premitigation_damage(const Entity& source, const Entity& target) const override;
};