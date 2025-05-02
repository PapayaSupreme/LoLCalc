// Champion.cpp
#include "Champion.h"

Champion::Champion(const Stats& stats, const ChampionStats& champion_stats)
    : Entity(stats), champion_stats(champion_stats) {}

float Champion::getHealthRegen() const {return champion_stats.healthRegen;}
float Champion::getResourceRegen() const {return champion_stats.resourceRegen;}
float Champion::getHealShieldPower() const {return champion_stats.healShieldPower;}
float Champion::getLethality() const {return champion_stats.lethality;}
float Champion::getArmorPen() const {return champion_stats.armorPen;}
float Champion::getMagicPenFlat() const {return champion_stats.magicPenFlat;}
float Champion::getMagicPen() const {return champion_stats.magicPen;}
float Champion::getLifeSteal() const {return champion_stats.lifeSteal;}
float Champion::getOmnivamp() const {return champion_stats.omnivamp;}
float Champion::getAttackRange() const {return champion_stats.attackRange;}
float Champion::getTenacity() const {return champion_stats.tenacity;}

float Champion::getSpellVamp() const {return champion_stats.spellVamp;}
float Champion::getCritDamage() const {return champion_stats.critDamage;}
float Champion::getBasicSpellsHaste() const {return champion_stats.basicSpellsHaste;}
float Champion::getUltimateHaste() const {return champion_stats.ultimateHaste;}
float Champion::getCritDamageReduction() const {return champion_stats.critDamageReduction;}

const ChampionStats& Champion::getChampionStats() const {return champion_stats;}


//dynamic cast way to check if its champion : const Champion* champSource = dynamic_cast<const Champion*>(&Source)
DamageDone Champion::AutoAttackPost(const Entity& Source, DamageDone& dmg_pre) {
    DamageDone dmg_post = dmg_pre;
    dmg_post[static_cast<int>(DamageType::Physical)] *= computeArmorReduction(Source);
    return dmg_post;
}

DamageDone Champion::TargetedAbilityPost(const Entity& Source, DamageDone& dmg_pre) {
    DamageDone dmg_post = dmg_pre;
    if (dmg_post[static_cast<int>(DamageType::Physical)] > 0.0f) {
        dmg_post[static_cast<int>(DamageType::Physical)] *= computeArmorReduction(Source);
    }
    if (dmg_post[static_cast<int>(DamageType::Magical)] > 0.0f) {
        dmg_post[static_cast<int>(DamageType::Magical)] *= computeMagicReduction(Source);
    }
    if (dmg_post[static_cast<int>(DamageType::True)] > 0.0f) {
        dmg_post[static_cast<int>(DamageType::True)] *= computeMagicReduction(Source);
    }
    return dmg_post;
}
