#pragma once
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <cstdint>

#include "../entities/Stats.h"
#include "../entities/Entity.h"

enum class EffectTrigger : uint8_t {
    OnHit, OnCrit, OnAbilityHit
};

using DamageDone = std::array<float, 3>;

class Effect {
protected:
    const std::string name;
    const EffectTrigger effect_trigger;
    const float base_dmg;
    const std::vector<Ratio> ratios;
    const float min_damage;
    float max_damage = std::numeric_limits<float>::infinity();
    float max_monster_damage = std::numeric_limits<float>::infinity();
    float max_epic_monster_damage = std::numeric_limits<float>::infinity();
    const float physical_ratio;
    const float magical_ratio;
    const float true_ratio;
public:
    Effect(std::string name, EffectTrigger effect_trigger, float base_dmg, std::vector<Ratio> terms, float min_damage, float max_damage,
    float max_monster_damage, float max_epic_monster_damage, float physical_ratio, float magical_ratio, float true_ratio);

    [[nodiscard]] std::string getName() const;
    [[nodiscard]] EffectTrigger getEffectTrigger() const;
    [[nodiscard]] DamageDone computePremitigationDamage(const Entity& source, const Entity& target) const;
};
