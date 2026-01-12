// Champion.h
#pragma once

#include "Entity.h"
#include "../damage/PreMitigationDamage.h"
#include "../loadout/Item.h"
#include "../damage/Effect.h"

class Champion : public Entity {
    /*
     * Class representing a champion in the game.
     * Inherits from Entity.
     * All champions have basic stats and champion stats.
     */
protected:
    ChampionStats champion_stats;
    std::vector<Effect> on_hit_effects;
    std::vector<Effect> on_ability_hit_effects;
public:
    /*
     * Constructor for Champion.
     * Initializes the champion with the given basic stats and champion stats.
     */
    Champion(std::string name, const Stats& stats, const ChampionStats& champion_stats);

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
    [[nodiscard]] float getLifesteal() const;
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


    void addLethality(float lethality);
    void addArmorPen(float armor_pen);
    void addLifesteal(float lifesteal);

    void addOnHitEffect(const Effect& effect);

    void removeLifeSteal(float lifesteal);


    /*
     * Computes the damage done to the champion by an unmitigated attack.
     */
    [[nodiscard]] DamageDone PostAttack(const Entity& Source, DamageDone& dmg_pre) override;

    /*
     * Adds an item, its stats and its  effects to a champion
     */
    void BuyItem(const Item& item);
};
