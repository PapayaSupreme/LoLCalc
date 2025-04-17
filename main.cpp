#include <iostream>
#include "Champion.h"

int main() {
    // Create a base stat block
    Stats kennenBaseStats = {
        .maxHP = 600.0f,
        .currentHP = 600.0f,
        .AD = 50.0f,
        .AP = 80.0f,
        .armor = 30.0f,
        .magicResist = 30.0f,
        .attackSpeed = 0.7f,
        .abilityHaste = 15.0f,
        .critChance = 0.0f,
        .movementSpeed = 335.0f
    };

    // Create champion-specific stats
    ChampionStats kennenChampStats = {
        .healthRegen = 5.0f,
        .resourceRegen = 0.0f,
        .healShieldPower = 0.1f,
        .lethality = 0.0f,
        .armorPen = 0.0f,
        .magicPenFlat = 12.0f,
        .magicPen = 0.2f,
        .lifeSteal = 0.0f,
        .omnivamp = 0.1f,
        .attackRange = 550.0f,
        .tenacity = 0.0f,
        .spellVamp = 0.0f,
        .critDamage = 0.0f,
        .basicSpellsHaste = 0.0f,
        .ultimateHaste = 0.0f,
        .critDamageReduction = 0.0f
    };

    Champion kennen(kennenBaseStats, kennenChampStats);

    std::cout << "=== Champion Stat Test ===\n";
    std::cout << "HP: " << kennen.getHP() << "\n";
    std::cout << "Current HP: " << kennen.getCurrHP() << "\n";
    std::cout << "AD: " << kennen.getAD() << "\n";
    std::cout << "AP: " << kennen.getAP() << "\n";
    std::cout << "Armor: " << kennen.getArmor() << "\n";
    std::cout << "MR: " << kennen.getMR() << "\n";
    std::cout << "Attack Speed: " << kennen.getAS() << "\n";
    std::cout << "Ability Haste: " << kennen.getAH() << "\n";
    std::cout << "Crit Chance: " << kennen.getCrit() << "\n";
    std::cout << "Movement Speed: " << kennen.getMS() << "\n";
    std::cout << "Omnivamp: " << kennen.getOmnivamp() << "\n";
    std::cout << "Magic Pen Flat: " << kennen.getMagicPenFlat() << "\n";
    std::cout << "Magic Pen %: " << kennen.getMagicPen() << "\n";
    std::cout << "Attack Range: " << kennen.getAttackRange() << "\n";
    std::cout << "Health Regen: " << kennen.getHealthRegen() << "\n";

    return 0;
}
