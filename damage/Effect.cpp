#include "Effect.h"

#include <iostream>
#include <utility>

Effect::Effect(std::string name, const float base_dmg, std::vector<Term> terms, const float min_damage,
    const float max_damage, const float max_monster_damage, const float max_epic_monster_damage,
    const float physical_ratio, const float magical_ratio, const float true_ratio)
    : name(std::move(name)), base_dmg(base_dmg), terms(std::move(terms)), min_damage(min_damage), max_damage(max_damage),
      max_monster_damage(max_monster_damage), max_epic_monster_damage(max_epic_monster_damage), //TODO: add max dmg to monters logic
      physical_ratio(physical_ratio), magical_ratio(magical_ratio), true_ratio(true_ratio) {}

DamageDone Effect::ComputePremitigationDamage(const Entity& source, const Entity& target) const {
    const Stats& srcStats = source.getStats();
    const Stats& tgtStats = target.getStats();
    const auto* srcChamp = dynamic_cast<const Champion*>(&source);

    float raw = 0.0f;
    for (const auto&[stat, k] : terms) {
        float value = 0.0f;
        switch (stat) {
            case TermStat::AD_ratio: value = srcStats.base_AD + srcStats.bonus_AD; break;
            case TermStat::base_AD_ratio: value = srcStats.base_AD; break;
            case TermStat::bonus_AD_ratio: value = srcStats.bonus_AD; break;
            case TermStat::AP_ratio: value = srcStats.AP; break;
            case TermStat::health_ratio:
            case TermStat::base_health_ratio: value = srcStats.max_HP; break;
            case TermStat::bonus_health_ratio: value = 0.0f; break;
            case TermStat::armor_ratio: value = tgtStats.base_armor + tgtStats.bonus_armor; break;
            case TermStat::base_armor_ratio: value = tgtStats.base_armor; break;
            case TermStat::bonus_armor_ratio: value = tgtStats.bonus_armor; break;
            case TermStat::MR_ratio: value = tgtStats.base_MR + tgtStats.bonus_MR; break;
            case TermStat::base_MR_ratio: value = tgtStats.base_MR; break;
            case TermStat::bonus_MR_ratio: value = tgtStats.bonus_MR; break;
            case TermStat::target_max_health_ratio: value = tgtStats.max_HP; break;
            case TermStat::target_current_health_ratio: value = tgtStats.current_HP; break;
            case TermStat::target_missing_health_ratio: value = std::max(0.0f, tgtStats.max_HP - tgtStats.current_HP); break;
            case TermStat::mana_ratio: value = srcStats.base_resource + srcStats.bonus_resource; break;
            case TermStat::base_mana_ratio: value = srcStats.base_resource; break;
            case TermStat::bonus_mana_ratio: value = srcStats.bonus_resource; break;
            case TermStat::current_mana_ratio: value = srcStats.current_resource; break;
            case TermStat::lethality_ratio: value = srcChamp ? srcChamp->getLethality() : 0.0f; break;
            case TermStat::armor_pen_ratio: value = srcChamp ? srcChamp->getArmorPen() : 0.0f; break;
            case TermStat::level_ratio: value = static_cast<float>(srcStats.level); break;
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
