#include <iostream>
#include "entities/Champion.h"
#include "damage/TargetedAbility.h"
#include "damage/AoEAbility.h"
#include "test/testDamage.h"

int main() {
    // === Champion Setup ===
    Stats kennenStats = {
        .maxHP = 600, .currentHP = 600,
        .AD = 80, .AP = 100,
        .armor = 30, .magicResist = 32,
        .attackSpeed = 0.7f, .abilityHaste = 0.0f,
        .critChance = 0.0f, .movementSpeed = 335,
        .level = 11
    };
    ChampionStats kennenExtras = {
        .lethality = 12.0f,
        .armorPen = 0.2f,
        // other stats = 0
    };
    Champion kennen(kennenStats, kennenExtras);


    TargetedAbilityStats kennenQstats = {
        .AD_ratio = 0.3f,
        .AP_ratio = 0.6f,
        .base_damage = 100.0f,
        .ultimate = false,
        .cost = 50,
        .cooldown = 8.0f,
        .range = 600,
        .channel = 0
    };
    AoEAbilityStats kennenRstats = {
        .AD_ratio = 0.3f,
        .AP_ratio = 0.6f,
        .base_damage = 100.0f,
        .ultimate = true,
        .cost = 100,
        .cooldown = 120.0f,
        .range = 600,
        .channel = 0
    };
    DamageType damageTypekennenq = DamageType::Magical;
    DamageType damageTypekennenr = DamageType::Physical;


    Stats garenStats = kennenStats;
    garenStats.armor = 80;
    garenStats.magicResist = 60;
    ChampionStats garenExtras = {};
    Champion garen(garenStats, garenExtras);  // simulate garen as target

    testAutoAttackDamage(kennen, garen);
    testTargetedAbilityDamage(kennen, garen, kennenQstats, damageTypekennenq);
    testAOEDamage(kennen, garen, kennenRstats, damageTypekennenr);
    return 0;
}
