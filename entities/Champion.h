// Champion.h
#pragma once
#include "Entity.h"
#include "../damage/PreMitigationDamage.h"

class Champion : public Entity {
    /*
     * Class representing a champion in the game.
     * Inherits from Entity.
     * All champions have basic stats and champion stats.
     */
protected:
    ChampionStats champion_stats;

public:
    /*
     * Constructor for Champion.
     * Initializes the champion with the given basic stats and champion stats.
     */
    Champion(const Stats& stats, const ChampionStats& champion_stats);

    // Champion stat health regeneration getter
    [[nodiscard]] float getHealthRegen() const;
    // Champion stat resource regeneration getter
    [[nodiscard]] float getResourceRegen() const;
    // Champion stat heal and shield power getter
    [[nodiscard]] float getHealShieldPower() const;
    // Champion stat lethality getter
    [[nodiscard]] float getLethality() const;
    // Champion stat armor penetration getter
    [[nodiscard]] float getArmorPen() const;
    // Champion stat magic penetration flat getter
    [[nodiscard]] float getMagicPenFlat() const;
    // Champion stat magic penetration getter
    [[nodiscard]] float getMagicPen() const;
    // Champion stat life steal getter
    [[nodiscard]] float getLifeSteal() const;
    // Champion stat omnivamp getter
    [[nodiscard]] float getOmnivamp() const;
    // Champion stat tenacity getter
    [[nodiscard]] float getTenacity() const;
    // Champion stat spell vampirism getter
    [[nodiscard]] float getSpellVamp() const;
    // Champion stat critical damage multiplier getter
    [[nodiscard]] float getCritDamage() const;
    // Champion stat basic ability haste getter
    [[nodiscard]] float getBasicAbilityHaste() const;
    // Champion stat ultimate ability haste getter
    [[nodiscard]] float getUltimateHaste() const;
    // Champion stat critical damage reduction getter
    [[nodiscard]] float getCritDamageReduction() const;
    // Champion stat list getter
    [[nodiscard]] const ChampionStats& getChampionStats() const;


    /*
     * Computes the damage done to the champion by an unmitigated auto attack.
     */
    [[nodiscard]] DamageDone PostAutoAttack(const Entity& Source, DamageDone& dmg_pre) override;

    /*
     * Computes the damage done to the champion by an unmitigated targeted ability.
     */
    [[nodiscard]] DamageDone PostTargetedAbility(const Entity& Source, DamageDone& dmg_pre) override;
};
