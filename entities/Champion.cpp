// Champion.cpp
#include "Champion.h"
#include "../loadout/Item.h"

Champion::Champion(std::string name, const Stats& stats, const ChampionStats& champion_stats)
    : Entity(std::move(name), stats), champion_stats(champion_stats) {}

float Champion::getHealthRegen() const {return champion_stats.health_regen;}
float Champion::getResourceRegen() const {return champion_stats.resource_regen;}
float Champion::getHealShieldPower() const {return champion_stats.heal_shield_power;}
float Champion::getLethality() const {return champion_stats.lethality;}
float Champion::getArmorPen() const {return champion_stats.armor_pen;}
float Champion::getMagicPenFlat() const {return champion_stats.magic_pen_flat;}
float Champion::getMagicPen() const {return champion_stats.magic_pen;}
float Champion::getLifesteal() const {return champion_stats.lifesteal;}
float Champion::getOmnivamp() const {return champion_stats.omnivamp;}
float Champion::getTenacity() const {return champion_stats.tenacity;}

float Champion::getSpellVamp() const {return champion_stats.spell_vamp;}
float Champion::getCritDamage() const {return champion_stats.crit_damage;}
float Champion::getBasicAbilityHaste() const {return champion_stats.basic_spells_haste;}
float Champion::getUltimateHaste() const {return champion_stats.ultimate_haste;}
float Champion::getCritDamageReduction() const {return champion_stats.crit_damage_reduction;}

const ChampionStats& Champion::getChampionStats() const {return champion_stats;}

void Champion::addLethality(const float lethality){ champion_stats.lethality += lethality; }
void Champion::addArmorPen(const float armor_pen){ champion_stats.armor_pen += armor_pen; }
void Champion::addLifesteal(const float lifesteal){ champion_stats.lifesteal += lifesteal; }

void Champion::addOnHitEffect(const Effect &effect) { on_hit_effects.push_back(&effect); }

void Champion::removeLifeSteal(float lifesteal) { champion_stats.lifesteal -= lifesteal; }


DamageDone Champion::PostAttack(const Entity& Source, DamageDone& dmg_pre) {
    DamageDone dmg_post = dmg_pre;
    if (dmg_post[static_cast<int>(DamageType::Physical)] > 0.0f) {
        dmg_post[static_cast<int>(DamageType::Physical)] *= computeArmorReduction(Source);
    }
    if (dmg_post[static_cast<int>(DamageType::Magical)] > 0.0f) {
        dmg_post[static_cast<int>(DamageType::Magical)] *= computeMagicReduction(Source);
    }
    return dmg_post;
}

void Champion::BuyItem(const Item& item) {
    for (const auto&[stat, k] : item.getStats()) {
        switch (stat) {
            case TermStat::bonus_AD: addBonusAD(k); break;
            case TermStat::AP: addAP(k); break;
            case TermStat::bonus_health: addBonusHealth(k); break;
            case TermStat::bonus_armor: addBonusArmor(k); break;
            case TermStat::bonus_MR: addBonusMR(k); break;
            case TermStat::bonus_mana: addBonusMana(k); break;
            case TermStat::lethality: addLethality(k); break;
            case TermStat::armor_pen: addArmorPen(k); break;
            default: break;
        }
    }
    for (const Effect& effect : item.getEffects()) {
        switch (effect.getEffectTrigger()) {
            case EffectTrigger::OnHit: addOnHitEffect(effect); break;
            case EffectTrigger::OnCrit:
            case EffectTrigger::OnAbilityHit:
                break;
        }
    }
}
