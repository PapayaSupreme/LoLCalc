// Entity.h
#pragma once
#include <string>

#include "../damage/PreMitigationDamage.h"
#include "Stats.h"

class Entity {
    /*
     * Base class for all entities in the game.
     * Includes champions, minions, turrets, wards, boxes.
     * All entities have basic stats.
     */
protected:
    std::string name;
    Stats entity_stats;
public:
    /*
     * Constructor for Entity.
     * Initializes the entity with the given basic stats.
     */
    Entity(std::string name, const Stats &stats);

    //Basic stat HP getter
    [[nodiscard]] float getHP() const;
    //Basic stat current HP getter
    [[nodiscard]] float getCurrHP() const;
    //Basic stat base attack damage getter
    [[nodiscard]] float getBaseAD() const;
    //Basic stat bonus attack damage getter
    [[nodiscard]] float getBonusAD() const;
    //Basic stat ability power getter
    [[nodiscard]] float getAP() const;
    //Basic stat armor getter
    [[nodiscard]] float getArmor() const;
    //Basic stat magic resistance getter
    [[nodiscard]] float getMR() const;
    //Basic stat attack speed getter
    [[nodiscard]] float getAS() const;
    //Basic stat ability haste getter
    [[nodiscard]] float getAH() const;
    //Basic stat critical strike chance getter
    [[nodiscard]] float getCrit() const;
    //Basic stat move speed getter
    [[nodiscard]] float getMS() const;
    //Basic stat level getter
    [[nodiscard]] int getLevel() const;
    //Basic stat list getter
    [[nodiscard]] const Stats& getStats() const;

    void addBonusAD(float bonus_AD);
    void addBonusArmor(float bonus_armor);
    void addBonusMR(float bonus_MR);
    void addBonusAS(float bonus_AS);
    void addAP(float AP);
    void addBonusHealth(float bonus_health);
    void addBonusMana(float bonus_mana);

    /*
     * Computes the damage done to the entity after applying armor from an amount.
     */
    [[nodiscard]] virtual float computeArmorReduction(const Entity& Source) const;

    /*
     * Computes the damage done to the entity after applying magic resistance from an amount.
     */
    [[nodiscard]] virtual float computeMagicReduction(const Entity& Source) const;

    /*
     * Computes the damage done to the entity by an unmitigated attack.
     */
    [[nodiscard]] virtual DamageDone PostAttack(const Entity& source, DamageDone& dmg_pre) = 0;

    virtual ~Entity() = default;  // polymorphic destruction
};

