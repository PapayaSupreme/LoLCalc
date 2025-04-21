#include <iostream>
#include "Champion.h"
#include "AutoAttack.h"

int main() {
    Stats kennenStats = {
        .maxHP = 600, .currentHP = 600,
        .AD = 80, .AP = 0,
        .armor = 30, .magicResist = 32,
        .attackSpeed = 0.7f, .abilityHaste = 0.0f,
        .critChance = 0.0f, .movementSpeed = 335,
        .level = 11
    };

    ChampionStats kennenExtras = {
        .lethality = 12.0f,
        .armorPen = 0.2f,
        // rest = default 0
    };

    Champion kennen(kennenStats, kennenExtras);

    Stats garenStats = kennenStats;
    garenStats.armor = 80;
    Champion garen(garenStats, kennenExtras);  // simulate garen

    AutoAttack aa(kennen, garen);

    DamageDone pre = aa.computePremitigationDamage();
    DamageDone final = garen.AutoAttackPost(kennen, pre);

    std::cout << "=== Auto Attack Test ===\n";
    std::cout << "Raw physical damage: " << pre[0] << "\n";
    std::cout << "Post-armor damage: " << final[0] << "\n";

    return 0;
}
