// Champion.cpp
#include "Champion.h"

#include <array>
#include <iostream>

#include "../loadout/Item.h"

Champion::Champion(std::string name, const Stats& stats, const ChampionStats& champion_stats)
    : Entity(std::move(name), stats), champion_stats(champion_stats) {}

float Champion::getHealthRegen() const {return champion_stats.health_regen;}
float Champion::getResourceRegen() const {return champion_stats.resource_regen;}
float Champion::getHealShieldPower() const {return champion_stats.heal_shield_power;}
float Champion::get_lethality() const noexcept {return champion_stats.lethality;}
float Champion::get_armor_pen() const noexcept {return champion_stats.armor_pen;}
float Champion::get_magic_pen_flat() const noexcept {return champion_stats.magic_pen_flat;}
float Champion::get_magic_pen() const noexcept {return champion_stats.magic_pen;}
float Champion::getLifesteal() const {return champion_stats.lifesteal;}
float Champion::getOmnivamp() const {return champion_stats.omnivamp;}
float Champion::getTenacity() const {return champion_stats.tenacity;}

float Champion::getSpellVamp() const {return champion_stats.spell_vamp;}
float Champion::getCritDamage() const {return champion_stats.crit_damage;}
float Champion::getBasicAbilityHaste() const {return champion_stats.basic_spells_haste;}
float Champion::getUltimateHaste() const {return champion_stats.ultimate_haste;}
float Champion::getCritDamageReduction() const {return champion_stats.crit_damage_reduction;}

const ChampionStats& Champion::getChampionStats() const {return champion_stats;}
std::vector<const Effect*> Champion::getOnHitEffects() const {
    std::vector<const Effect*> ptrs;
    for (const auto& e : on_hit_effects) {
        ptrs.push_back(&e);
    }
    return ptrs;
}

void Champion::addLethality(const float lethality){ champion_stats.lethality += lethality; }
void Champion::addArmorPen(const float armor_pen){ champion_stats.armor_pen += armor_pen; }
void Champion::addLifesteal(const float lifesteal){ champion_stats.lifesteal += lifesteal; }

void Champion::addOnHitEffect(const Effect &effect) { on_hit_effects.push_back(effect); }

void Champion::remove_lifesteal(float lifesteal) { champion_stats.lifesteal -= lifesteal; }


DamageDone Champion::post_attack(const Entity& source, DamageDone& dmg_pre) {
    DamageDone dmg_post = dmg_pre;
    if (dmg_post[static_cast<int>(DamageType::Physical)] > 0.0f) {
        dmg_post[static_cast<int>(DamageType::Physical)] *= computeArmorReduction(source);
    }
    if (dmg_post[static_cast<int>(DamageType::Magical)] > 0.0f) {
        dmg_post[static_cast<int>(DamageType::Magical)] *= computeMagicReduction(source);
    }
    return dmg_post;
}

DamageDone Champion::attack(Entity& target, const Effect& effect) const {
    DamageDone pre = effect.computePremitigationDamage(*this, target);
    DamageDone post = {};
    std::cout << "Primary effect dmg: " << pre[0] << " " << pre[1] << " " << pre[2] << "\n\n";
    switch (effect.getEffectTrigger()) {
        case EffectTrigger::OnHit: {
            DamageDone temp {};
            for (const Effect& e: on_hit_effects) {
                temp = e.computePremitigationDamage(*this, target);
                std::cout << e.getName() << " dmg: " << temp[0] << " " << temp[1] << " " << temp[2] << "\n\n";
                for (int i = 0; i < 3; ++i) {
                    pre[i] += temp[i];
                }
            }
            std::cout << "attack dmg pre: " << pre[0] << " " << pre[1] << " " << pre[2] << "\n\n";
            post = target.post_attack(*this, pre);
            std::cout << "attack dmg post: " << post[0] << " " << post[1] << " " << post[2] << "\n\n";
            break;
        }
        case EffectTrigger::OnCrit:
        case EffectTrigger::OnAbilityHit:
            break;
    }

    return post;
}

void Champion::buy_item(const Item& item) {
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
