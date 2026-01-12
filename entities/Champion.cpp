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
float Champion::get_lifesteal() const noexcept {return champion_stats.lifesteal;}
float Champion::get_omnivamp() const noexcept {return champion_stats.omnivamp;}
float Champion::get_tenacity() const noexcept {return champion_stats.tenacity;}

float Champion::get_spell_vamp() const noexcept {return champion_stats.spell_vamp;}
float Champion::get_crit_damage() const noexcept {return champion_stats.crit_damage;}
float Champion::get_basic_AH() const noexcept {return champion_stats.basic_spells_haste;}
float Champion::get_ultimate_AH() const noexcept {return champion_stats.ultimate_haste;}
float Champion::get_crit_damage_reduction() const noexcept {return champion_stats.crit_damage_reduction;}

const ChampionStats& Champion::getChampionStats() const {return champion_stats;}
const std::vector<const Effect*>& Champion::get_on_hit_effects() const { return on_hit_effects; }
const std::vector<const Effect*>& Champion::get_on_ability_hit_effects() const { return on_ability_hit_effects; }

void Champion::add_omnivamp(const float omnivamp) noexcept { champion_stats.omnivamp += omnivamp; }
void Champion::add_lifesteal(const float lifesteal) noexcept { champion_stats.lifesteal += lifesteal; }
void Champion::add_spell_vamp(const float spell_vamp) noexcept { champion_stats.spell_vamp += spell_vamp; }
void Champion::add_lethality(const float lethality) noexcept { champion_stats.lethality += lethality; }
void Champion::add_armor_pen(const float armor_pen) noexcept { champion_stats.armor_pen += armor_pen; }
void Champion::add_magic_pen(const float magic_pen) noexcept { champion_stats.magic_pen += magic_pen; }
void Champion::add_magic_pen_flat(const float magic_pen_flat) noexcept { champion_stats.magic_pen_flat += magic_pen_flat; }

void Champion::add_on_hit_effect(const Effect &effect) { on_hit_effects.push_back(&effect); }
void Champion::add_on_ability_hit_effect(const Effect &effect) { on_ability_hit_effects.push_back(&effect); }

void Champion::remove_omnivamp(const float omnivamp) noexcept { champion_stats.omnivamp -= omnivamp; }
void Champion::remove_lifesteal(const float lifesteal) noexcept { champion_stats.lifesteal -= lifesteal; }
void Champion::remove_spell_vamp(const float spell_vamp) noexcept { champion_stats.spell_vamp -= spell_vamp; }
void Champion::remove_armor_pen(const float armor_pen) noexcept { champion_stats.armor_pen -= armor_pen; }
void Champion::remove_lethality(const float lethality) noexcept { champion_stats.lethality -= lethality; }
void Champion::remove_magic_pen(const float magic_pen) noexcept { champion_stats.magic_pen -= magic_pen; }
void Champion::remove_magic_pen_flat(const float magic_pen_flat) noexcept { champion_stats.magic_pen_flat -= magic_pen_flat; }


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

            for (const Effect* e: on_hit_effects) {
                temp = e->computePremitigationDamage(*this, target);
                std::cout << e->getName() << " dmg: " << temp[0] << " " << temp[1] << " " << temp[2] << "\n\n";
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
            case TermStat::bonus_AD: add_bonus_AD(k); break;
            case TermStat::AP: add_AP(k); break;
            case TermStat::bonus_health: add_bonus_health(k); break;
            case TermStat::bonus_armor: add_bonus_armor(k); break;
            case TermStat::bonus_MR: add_bonus_MR(k); break;
            case TermStat::bonus_mana: add_bonus_mana(k); break;
            case TermStat::lethality: add_lethality(k); break;
            case TermStat::armor_pen: add_armor_pen(k); break;
            default: break;
        }
    }
    for (const Effect& effect : item.getEffects()) {
        switch (effect.getEffectTrigger()) {
            case EffectTrigger::OnHit: add_on_hit_effect(effect); break;
            case EffectTrigger::OnCrit:
            case EffectTrigger::OnAbilityHit:
                break;
        }
    }
}
