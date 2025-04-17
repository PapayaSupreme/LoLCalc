// BasicStats.h
#pragma once

struct Stats {
    /*
     * Basic stats for entities.
     * All floats
     */
    float maxHP = 0.0f;
    float currentHP = 0.0f;
    float AD = 0.0f;
    float AP = 0.0f;
    float armor = 0.0f;
    float magicResist = 0.0f;
    float attackSpeed = 0.0f;
    float abilityHaste = 0.0f;
    float critChance = 0.0f;
    float movementSpeed = 0.0f;
};

struct ChampionStats {
    float healthRegen = 0.0f;
    float resourceRegen = 0.0f;
    float healShieldPower = 0.0f;
    float lethality = 0.0f;
    float armorPen = 0.0f;
    float magicPenFlat = 0.0f;
    float magicPen = 0.0f;
    float lifeSteal = 0.0f;
    float omnivamp = 0.0f;
    float attackRange = 0.0f;
    float tenacity = 0.0f;
    //hidden stats
    float spellVamp = 0.0f;
    float critDamage = 0.0f;
    float basicSpellsHaste = 0.0f;
    float ultimateHaste = 0.0f;
    float critDamageReduction = 0.0f;
};
