#pragma once
#include <string>
#include <vector>
#include <limits>
#include <algorithm>

#include "../entities/Stats.h"
#include "../entities/Entity.h"
#include "../entities/Champion.h"
#include "PreMitigationDamage.h"

class Effect {
protected:
    const std::string name;
    const float base_dmg;
    const std::vector<Term> terms;
    const float min_damage;
    float max_damage = std::numeric_limits<float>::infinity();
    float max_monster_damage = std::numeric_limits<float>::infinity();
    float max_epic_monster_damage = std::numeric_limits<float>::infinity();
    const float physical_ratio;
    const float magical_ratio;
    const float true_ratio;
public:
    Effect(std::string name, float base_dmg, std::vector<Term> terms, float min_damage, float max_damage,
    float max_monster_damage, float max_epic_monster_damage, float physical_ratio, float magical_ratio, float true_ratio);

    [[nodiscard]] DamageDone ComputePremitigationDamage(const Entity& source, const Entity& target) const;
};
