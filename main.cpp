#include <iostream>
#include "entities/Champion.h"
#include "damage/Ability.h"
#include "damage/Effect.h"
#include "test/testDamage.h"

int main() {
    // === Champion Setup ===
    Stats sionStats = {
        .max_HP = 1000,
        .current_HP = 1000,
        .base_AD = 68,
        .bonus_AD = 51,
        .AP = 0,
        .base_armor = 80,
        .bonus_armor = 0,
        .base_MR = 50,
        .bonus_MR = 0,
        .base_resource = 0,
        .bonus_resource = 0,
        .current_resource = 0,
        .attack_speed = 0.7f,
        .ability_haste = 0,
        .crit_chance = 0,
        .MS = 350,
        .level = 18
    };
    ChampionStats sionExtras = {
        .health_regen = 10,
        .resource_regen = 0,
        .heal_shield_power = 0,
        .lethality = 0.0f,
        .armor_pen = 0.0f,
        .magic_pen_flat = 0,
        .magic_pen = 0,
        .lifesteal = 0,
        .omnivamp = 0,
        .tenacity = 0,
        .spell_vamp = 0,
        .AD_vamp = 0,
        .crit_damage = 0,
        .basic_spells_haste = 0,
        .ultimate_haste = 0,
        .crit_damage_reduction = 0
    };
    Champion sion("Sion", sionStats, sionExtras);


    Effect AutoAttackEffect("Auto Attack", 0.0f,
                                  {{TermStat::AD_ratio, 1}},
                                  0.0f, std::numeric_limits<float>::infinity(),
                                  std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(),
                                  1.0f, 0.0f, 0.0f);

    Effect BORKEffect("Mist's Edge", 0.0f,
                                  {{TermStat::target_current_health_ratio, 0.09}},
                                  0.0f, std::numeric_limits<float>::infinity(),
                                  std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(),
                                  1.0f, 0.0f, 0.0f);

    Stats brandStats = sionStats;
    brandStats.base_armor = 50;
    brandStats.base_MR = 50;
    ChampionStats brandExtras = {};
    Champion brand("Brand", brandStats, brandExtras);  // simulate brand as target

    //testAutoAttackDamage(sion, brand);
    testEffectDamage(sion, brand, AutoAttackEffect);
    testEffectDamage(sion, brand, BORKEffect);
    /*testAbilityDamage(kennen, brand, kennenQstats, damageTypekennenq);
    testDoTDamage(brand, kennen, brandqstats, damageTypekennenq);*/
    return 0;
}
