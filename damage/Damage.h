#pragma once
#include <string>
#include <vector>
#include <limits>
#include <algorithm>

#include "Effect.h"
#include "../structs/EffectTrigger.h"
#include "../structs/Ratio.h"

class Entity;

class Damage final : public Effect {
protected:
    const EffectTrigger effect_trigger;
    const float base_damage;
    const std::vector<Ratio> ratios;
    const float min_damage;
    float max_damage = std::numeric_limits<float>::infinity();
    float max_monster_damage = std::numeric_limits<float>::infinity();
    float max_epic_monster_damage = std::numeric_limits<float>::infinity();
    const float physical_ratio;
    const float magical_ratio;
    const float true_ratio;

public:
    Damage(std::string name, EffectTrigger effect_trigger, float base_damage, std::vector<Ratio> terms, float min_damage, float max_damage,
    float max_monster_damage, float max_epic_monster_damage, float physical_ratio, float magical_ratio, float true_ratio);

    [[nodiscard]] EffectTrigger get_effect_trigger() const noexcept override;
    [[nodiscard]] float get_base_damage() const noexcept;
    [[nodiscard]] DamageDone compute_premitigation_damage(const Entity& source, const Entity& target) const override;
};
