#include "Damage.h"

#include <array>
#include <iostream>
#include <utility>

#include "../entities/Champion.h"

Damage::Damage(std::string name, const EffectTrigger effect_trigger, const float base_damage, std::vector<Ratio> terms,
    const float min_damage, const float max_damage, const float max_monster_damage, const float max_epic_monster_damage,
    const float physical_ratio, const float magical_ratio, const float true_ratio)
    : Effect(std::move(name), EffectType::Damage), effect_trigger(effect_trigger), base_damage(base_damage), ratios(std::move(terms)), min_damage(min_damage), max_damage(max_damage),
      max_monster_damage(max_monster_damage), max_epic_monster_damage(max_epic_monster_damage), //TODO: add max dmg to monters logic
      is_adaptive_damage(false), physical_ratio(physical_ratio), magical_ratio(magical_ratio), true_ratio(true_ratio) {}

Damage::Damage(std::string name, const EffectTrigger effect_trigger, const float base_damage, std::vector<Ratio> terms,
    const float min_damage, const float max_damage, const float max_monster_damage, const float max_epic_monster_damage)
    : Effect(std::move(name), EffectType::Damage), effect_trigger(effect_trigger), base_damage(base_damage),
      ratios(std::move(terms)), min_damage(min_damage), max_damage(max_damage),
      max_monster_damage(max_monster_damage), max_epic_monster_damage(max_epic_monster_damage),
      is_adaptive_damage(true), physical_ratio(0.0f), magical_ratio(0.0f), true_ratio(0.0f) {}

Damage::Damage(std::string name, const EffectTrigger effect_trigger, const float base_damage, std::vector<Ratio> terms,
    const float physical_ratio, const float magical_ratio, const float true_ratio)
    : Effect(std::move(name), EffectType::Damage), effect_trigger(effect_trigger), base_damage(base_damage),
      ratios(std::move(terms)),is_adaptive_damage(false),
      physical_ratio(physical_ratio), magical_ratio(magical_ratio), true_ratio(true_ratio) {}

Damage::Damage(std::string name, const EffectTrigger effect_trigger, const float base_damage, std::vector<Ratio> terms)
    : Effect(std::move(name), EffectType::Damage), effect_trigger(effect_trigger), base_damage(base_damage),
      ratios(std::move(terms)), is_adaptive_damage(true),
      physical_ratio(0.0f), magical_ratio(0.0f),  true_ratio(0) {
}


EffectTrigger Damage::get_effect_trigger() const noexcept { return effect_trigger; }

float Damage::get_base_damage() const noexcept { return base_damage; }

DamageDone Damage::compute_premitigation_damage(const Entity& source, const Entity& target) const {
    const Stats& srcStats = source.getStats();
    const Stats& tgtStats = target.getStats();
    float multiplier = 1.0f;
    float raw = get_base_damage();
    for (const auto&[stat, k] : ratios) {
        multiplier = 1.0f;
        float value = 0.0f;
        switch (stat) {
            case TermStat::damage_amplifier: multiplier = k;
            case TermStat::total_AD: value = srcStats.base_AD + srcStats.bonus_AD; break;
            case TermStat::base_AD: value = srcStats.base_AD; break;
            case TermStat::bonus_AD: value = srcStats.bonus_AD; break;
            case TermStat::AP: value = srcStats.AP; break;
            case TermStat::total_health:
            case TermStat::base_health: value = srcStats.max_HP; break;
            case TermStat::bonus_health: value = 0.0f; break;
            case TermStat::total_armor: value = tgtStats.base_armor + tgtStats.bonus_armor; break;
            case TermStat::base_armor: value = tgtStats.base_armor; break;
            case TermStat::bonus_armor: value = tgtStats.bonus_armor; break;
            case TermStat::total_MR: value = tgtStats.base_MR + tgtStats.bonus_MR; break;
            case TermStat::base_MR: value = tgtStats.base_MR; break;
            case TermStat::bonus_MR: value = tgtStats.bonus_MR; break;
            case TermStat::target_max_health: value = tgtStats.max_HP; break;
            case TermStat::target_current_health: value = tgtStats.current_HP; break;
            case TermStat::target_missing_health: value = std::max(0.0f, tgtStats.max_HP - tgtStats.current_HP); break;
            case TermStat::total_mana: value = srcStats.base_resource + srcStats.bonus_resource; break;
            case TermStat::base_mana: value = srcStats.base_resource; break;
            case TermStat::bonus_mana: value = srcStats.bonus_resource; break;
            case TermStat::current_mana: value = srcStats.current_resource; break;
            case TermStat::lethality: value = source.get_lethality(); break;
            case TermStat::armor_pen: value = source.get_armor_pen(); break;
            case TermStat::level: value = static_cast<float>(srcStats.level-1); break;
            default: value = 0.0f; break;
        }
        raw += k * value;
    }

    raw = std::clamp(raw, this->min_damage, this->max_damage);
    //std::cout << "HERE  RAW OF " << this->getName() << raw;

    DamageDone damage_done {};
    if (is_adaptive_damage) {
        damage_done[source.get_adaptive_type()] = raw * multiplier;
    }
    else {
        damage_done[0] = raw * physical_ratio * multiplier;
        damage_done[1] = raw * magical_ratio * multiplier;
        damage_done[2] = raw * true_ratio * multiplier;
    }

    return damage_done;
}
