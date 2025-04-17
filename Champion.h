// Champion.h
#pragma once
#include "Entity.h"

class Champion : public Entity {
protected:
    ChampionStats champion_stats;

public:
    Champion(const Stats& stats, const ChampionStats& champion_stats);

    [[nodiscard]] float getHealthRegen() const;
    [[nodiscard]] float getResourceRegen() const;
    [[nodiscard]] float getHealShieldPower() const;
    [[nodiscard]] float getLethality() const;
    [[nodiscard]] float getArmorPen() const;
    [[nodiscard]] float getMagicPenFlat() const;
    [[nodiscard]] float getMagicPen() const;
    [[nodiscard]] float getLifeSteal() const;
    [[nodiscard]] float getOmnivamp() const;
    [[nodiscard]] float getAttackRange() const;
    [[nodiscard]] float getTenacity() const;
    [[nodiscard]] float getSpellVamp() const;
    [[nodiscard]] float getCritDamage() const;
    [[nodiscard]] float getBasicSpellsHaste() const;
    [[nodiscard]] float getUltimateHaste() const;
    [[nodiscard]] float getCritDamageReduction() const;

    [[nodiscard]] const ChampionStats& getChampionStats() const;
};
