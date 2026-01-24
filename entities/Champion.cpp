#include "Champion.h"

#include <array>
#include <iostream>

#include "../damage/Multiplier.h"
#include "../damage/Stack.h"
#include "../loadout/Item.h"
#include "../structs/TermStat.h"

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
const std::vector<const Damage *> &Champion::get_on_hit_effects() const { return on_hit_damage_effects; }
const std::vector<const Damage *> &Champion::get_on_ability_hit_effects() const { return on_ability_hit_damage_effects; }
const std::vector<const Damage *> &Champion::get_on_attack_effects() const { return on_attack_damage_effects; }
std::vector<Stack *> Champion::get_on_attack_stacks() const { return on_attack_stacks; }
const std::vector<const Multiplier *> &Champion::get_post_attack_multipliers() const { return post_attack_multiplier; }

void Champion::add_omnivamp(const float omnivamp) noexcept { champion_stats.omnivamp += omnivamp; }
void Champion::add_lifesteal(const float lifesteal) noexcept { champion_stats.lifesteal += lifesteal; }
void Champion::add_spell_vamp(const float spell_vamp) noexcept { champion_stats.spell_vamp += spell_vamp; }
void Champion::add_lethality(const float lethality) noexcept { champion_stats.lethality += lethality; }
void Champion::add_armor_pen(const float armor_pen) noexcept { champion_stats.armor_pen += armor_pen; }
void Champion::add_magic_pen(const float magic_pen) noexcept { champion_stats.magic_pen += magic_pen; }
void Champion::add_magic_pen_flat(const float magic_pen_flat) noexcept { champion_stats.magic_pen_flat += magic_pen_flat; }

void Champion::add_on_hit_effect(const Damage &effect) { on_hit_damage_effects.push_back(&effect); }
void Champion::add_on_ability_hit_effect(const Damage &effect) { on_ability_hit_damage_effects.push_back(&effect); }
void Champion::add_on_attack_effect(const Damage &effect) { on_attack_damage_effects.push_back(&effect); }
void Champion::add_on_attack_stack(Stack &stack) { on_attack_stacks.push_back(&stack); }
void Champion::add_post_attack_multiplier(const Multiplier &multiplier) { post_attack_multiplier.push_back(&multiplier); }

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

DamageDone Champion::attack(Entity& target, const Damage &effect) const {
    DamageDone pre = effect.compute_premitigation_damage(*this, target);
    float multiplier = 1.0f;
    DamageDone post = {};
    std::vector<const Damage *> damages = on_attack_damage_effects;
    const std::vector<Stack *> stacks = on_attack_stacks;
    const std::vector<const Multiplier *> multipliers = post_attack_multiplier;
    std::cout << "Primary effect dmg (PRE): " << pre[0] << " " << pre[1] << " " << pre[2] << "\n\n";

    switch (effect.get_effect_trigger()) {
        case EffectTrigger::OnHit: damages.insert(damages.end(), on_hit_damage_effects.begin(), on_hit_damage_effects.end()); break;
        case EffectTrigger::OnAbilityHit: damages = on_ability_hit_damage_effects; break;
        case EffectTrigger::OnCrit:
        case EffectTrigger::OnToggle:
        case EffectTrigger::OnAttack:
        case EffectTrigger::OnActivate:
        case EffectTrigger::AfterAttack:
            break;
    }

    for (const Damage* d: damages) {
        DamageDone temp = d->compute_premitigation_damage(*this, target);
        std::cout << d->get_name() << " damage: " << temp[0] << " " << temp[1] << " " << temp[2] << "\n\n";
        for (int i = 0; i < 3; ++i) {
            pre[i] += temp[i];
        }
    }
    std::cout << "All effects dmg (PRE): " << pre[0] << " " << pre[1] << " " << pre[2] << "\n\n";
                                                                                // if one get procced after theres a +1 lag like PTA

    for (Stack* s : stacks) {
        if (std::vector<const Effect *>effects_maybe = s->add_entity_stack_count(&target); !effects_maybe.empty()) {
            for (const Effect* e : effects_maybe) {
                if (e->get_effect_trigger() == EffectTrigger::OnActivate) {
                    DamageDone temp = e->compute_premitigation_damage(*this, target);
                    std::cout << e->get_name() << " details: " << temp[0] << " " << temp[1] << " " << temp[2] << "\n\n";
                    for (int i = 0; i < 3; ++i) {
                        pre[i] += temp[i];
                    }
                    std::cout << s->get_name() << " has proc onActivate " << e->get_name() << " while having "
                    << s->get_entities_stack_count().find(&target)->second << " stacks\n\n";
                } else if (e->get_effect_trigger() == EffectTrigger::OnToggle && std::ranges::find(damages, e) == damages.end()) {
                    std::cout << s->get_name() << " has proc onToggle " << e->get_name() << " while having "
                    << s->get_entities_stack_count().find(&target)->second << " stacks\n\n";
                    damages.push_back(static_cast<const Damage *>(e)); //DO NOT CLICK CLANG TIDY I just won't do the comparison for one less if hehe
                } else if (e->get_effect_trigger() == EffectTrigger::AfterAttack) { // here and only here its mult type
                    const_cast<Champion&>(*this).add_post_attack_multiplier(*static_cast<const Multiplier *>(e));
                    std::cout << s->get_name() << " has proc afterAttack " << e->get_name() << " while having "
                    << s->get_entities_stack_count().find(&target)->second << " stacks\n\n";
                } else {
                    std::cout << "switch case of stack proc" << e->get_name() <<" not done\n\n";
                }
            }
        }
        std::cout << s->get_name() << " has " << s->get_entities_stack_count().find(&target)->second << " stacks on "
        << target.get_name() << "\n";
    }

    for (const Multiplier* m : multipliers) {
        std::cout <<"mult in  loops: " << m->get_multiplier();
        multiplier *= m->get_multiplier();
    } //we compute this attack mult here so that
    for (int i = 0; i < 3; ++i) {
        pre[i] *= multiplier;
    }
    std::cout << "All effects + mults dmg (PRE): " << pre[0] << " " << pre[1] << " " << pre[2] << "\n\n";
    post = target.post_attack(*this, pre);
    std::cout << "All effects dmg (POST): " << post[0] << " " << post[1] << " " << post[2] << "\n\n";
    //now deal the dmg
    const bool dead = target.remove_HP(post[0] + post[1] + post[2]);
    std::cout << "Target is dead : " << dead << "\n";
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
    for (const Damage& effect : item.getEffects()) {
        switch (effect.get_effect_trigger()) {
            case EffectTrigger::OnHit: add_on_hit_effect(effect); break;
            case EffectTrigger::OnCrit:
            case EffectTrigger::OnAbilityHit:
            case EffectTrigger::OnAttack:
            case EffectTrigger::OnToggle:
            case EffectTrigger::OnActivate:
            case EffectTrigger::AfterAttack:
                break;
        }
    }
}
