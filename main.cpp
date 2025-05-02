#include <iostream>
#include "entities/Champion.h"
#include "damage/AutoAttack.h"
#include "damage/TargetedAbility.h"

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

    Stats garenStats = kennenStats;
    garenStats.armor = 80;
    garenStats.magicResist = 60;

    Champion garen(garenStats, kennenExtras);  // simulate garen as target

    // === Test AutoAttack ===
    AutoAttack aa(kennen, garen);
    DamageDone aa_pre = aa.computePremitigationDamage();
    DamageDone aa_post = garen.PostAutoAttack(kennen, aa_pre);

    std::cout << "=== Auto Attack Test ===\n";
    std::cout << "Raw physical damage: " << aa_pre[0] << "\n";
    std::cout << "Post-armor damage:   " << aa_post[0] << "\n";

    // === Test TargetedAbility (magic damage) ===
    TargetedAbility kennenQ(
        kennen, garen,
        /* AD ratio = */ 0.3f,
        /* AP ratio = */ 0.6f,
        /* base damage = */ 100.0f,
        /* ultimate = */ false,
        /* cost = */ 50,
        /* cooldown = */ 8.0f,
        /* range = */ 600,
        /* channel = */ 0,
        /* damage type = */ DamageType::Magical
    );

    DamageDone q_pre = kennenQ.computePremitigationDamage();
    DamageDone q_post = garen.PostTargetedAbility(kennen, q_pre);

    std::cout << "\n=== Targeted Ability Test ===\n";
    std::cout << "Raw physical damage: " << q_pre[0] << "\n";  // index 0 = physical
    std::cout << "Raw Magic Damage:        " << q_pre[1] << "\n";  // index 1 = magical
    std::cout << "Raw True Damage:         " << q_pre[2] << "\n";  // index 2 = true
    std::cout << "Post-armor damage:       " << q_post[0] << "\n";
    std::cout << "Post-magic damage:       " << q_post[1] << "\n";
    std::cout << "Post-true damage:        " << q_post[2] << "\n";

    return 0;
}
