// BasicStats.h
#pragma once

struct Stats {
    /*
     * Basic stats for entities.
     * All floats except level.
     */
    float max_HP = 0.0f;
    float current_HP = 0.0f;
    float base_AD = 0.0f;
    float bonus_AD = 0.0f;
    float AP = 0.0f;
    float base_armor = 0.0f;
    float bonus_armor = 0.0f;
    float base_MR = 0.0f;
    float bonus_MR = 0.0f;
    float base_resource = 0.0f;
    float bonus_resource = 0.0f;
    float current_resource = 0.0f;
    float attack_speed = 0.0f;
    float ability_haste = 0.0f;
    float crit_chance = 0.0f;
    float MS = 0.0f;
    int level = 1;
};

enum class DamageType : int {
    Physical = 0,
    Magical  = 1,
    True     = 2
};

struct ChampionStats {
    /*
     * Champion stats for entities.
     * All floats.
     */
    float health_regen = 0.0f;
    float resource_regen = 0.0f;
    float heal_shield_power = 0.0f;
    float lethality = 0.0f;
    float armor_pen = 0.0f;
    float magic_pen_flat = 0.0f;
    float magic_pen = 0.0f;
    float lifesteal = 0.0f;
    float omnivamp = 0.0f;
    float tenacity = 0.0f;
    //hidden stats
    float spell_vamp = 0.0f;
    float AD_vamp = 0.0f;
    float crit_damage = 0.0f;
    float basic_spells_haste = 0.0f;
    float ultimate_haste = 0.0f;
    float crit_damage_reduction = 0.0f;
};
// TODO: add ultimate bool ?
struct RatiosStats {
    /*
     * ability stats for entities.
     */
    float AD_ratio = 0.0f;
    float base_AD_ratio = 0.0f;
    float AP_ratio = 0.0f;
    float health_ratio = 0.0f;
    float armor_ratio = 0.0f;
    float MR_ratio = 0.0f;
    float target_max_health_ratio = 0.0f;
    float target_current_health_ratio = 0.0f;
    float mana_ratio = 0.0f;
    float lethality_ratio = 0.0f;
};

struct DoTAbilityStats {
    /*
     * DoT ability stats for entities.
     */
    float duration = 0.0f;
    float tick_rate = 0;// between 0.125, 0.25, 0.5, 1.0 seconds
};

