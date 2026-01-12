#include "Effect.h"

#include <array>
#include <iostream>
#include <utility>

#include "../entities/Champion.h"

Effect::Effect(std::string name, const EffectTrigger effect_trigger, const float base_dmg, std::vector<Term> terms, const float min_damage,
    const float max_damage, const float max_monster_damage, const float max_epic_monster_damage,
    const float physical_ratio, const float magical_ratio, const float true_ratio)
    : name(std::move(name)), effect_trigger(effect_trigger), base_dmg(base_dmg), terms(std::move(terms)), min_damage(min_damage), max_damage(max_damage),
      max_monster_damage(max_monster_damage), max_epic_monster_damage(max_epic_monster_damage), //TODO: add max dmg to monters logic
      physical_ratio(physical_ratio), magical_ratio(magical_ratio), true_ratio(true_ratio) {}

EffectTrigger Effect::getEffectTrigger() const { return effect_trigger; }

DamageDone Effect::computePremitigationDamage(const Entity& source, const Entity& target) const {
    const Stats& srcStats = source.getStats();
    const Stats& tgtStats = target.getStats();
    const auto* srcChamp = dynamic_cast<const Champion*>(&source);

    float raw = 0.0f;
    for (const auto&[stat, k] : terms) {
        float value = 0.0f;
        switch (stat) {
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
            case TermStat::lethality: value = srcChamp ? srcChamp->getLethality() : 0.0f; break;
            case TermStat::armor_pen: value = srcChamp ? srcChamp->getArmorPen() : 0.0f; break;
            case TermStat::level: value = static_cast<float>(srcStats.level); break;
            default: value = 0.0f; break;
        }
        raw += k * value;
    }

    raw = std::clamp(raw, this->min_damage, this->max_damage);

    DamageDone damage_done {};
    damage_done[static_cast<int>(DamageType::Physical)] = raw * physical_ratio;
    damage_done[static_cast<int>(DamageType::Magical)] = raw * magical_ratio;
    damage_done[static_cast<int>(DamageType::True)] = raw * true_ratio;
    return damage_done;
}
