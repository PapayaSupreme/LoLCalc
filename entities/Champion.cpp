// Champion.cpp
#include "Champion.h"

Champion::Champion(std::string name, const Stats& stats, const ChampionStats& champion_stats)
    : Entity(std::move(name), stats), champion_stats(champion_stats) {}

float Champion::getHealthRegen() const {return champion_stats.health_regen;}
float Champion::getResourceRegen() const {return champion_stats.resource_regen;}
float Champion::getHealShieldPower() const {return champion_stats.heal_shield_power;}
float Champion::getLethality() const {return champion_stats.lethality;}
float Champion::getArmorPen() const {return champion_stats.armor_pen;}
float Champion::getMagicPenFlat() const {return champion_stats.magic_pen_flat;}
float Champion::getMagicPen() const {return champion_stats.magic_pen;}
float Champion::getLifeSteal() const {return champion_stats.lifesteal;}
float Champion::getOmnivamp() const {return champion_stats.omnivamp;}
float Champion::getTenacity() const {return champion_stats.tenacity;}

float Champion::getSpellVamp() const {return champion_stats.spell_vamp;}
float Champion::getCritDamage() const {return champion_stats.crit_damage;}
float Champion::getBasicAbilityHaste() const {return champion_stats.basic_spells_haste;}
float Champion::getUltimateHaste() const {return champion_stats.ultimate_haste;}
float Champion::getCritDamageReduction() const {return champion_stats.crit_damage_reduction;}

const ChampionStats& Champion::getChampionStats() const {return champion_stats;}


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
