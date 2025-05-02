// Entity.h
#pragma once
#include "../damage/PreMitigationDamage.h"
#include "Stats.h"

class Entity {
    /*
     * Base class for all entities in the game.
     * Includes champions, minions, turrets, wards, boxes.
     * All entities have basic stats.
     */
protected:
    Stats entity_stats;

public:
    /*
     * Constructor for Entity.
     * Initializes the entity with the given basic stats.
     */
    explicit Entity(const Stats& stats);

    //Basic stat HP getter
    [[nodiscard]] float getHP() const;
    //Basic stat current HP getter
    [[nodiscard]] float getCurrHP() const;
    //Basic stat attack damage getter
    [[nodiscard]] float getAD() const;
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
    //Basic stat attack range getter
    [[nodiscard]] float getAttackRange() const;
    //Basic stat list getter
    [[nodiscard]] const Stats& getStats() const;

    /*
     * Computes the damage done to the entity after applying armor from an amount.
     */
    [[nodiscard]] virtual float computeArmorReduction(const Entity& Source) const;

    /*
     * Computes the damage done to the entity after applying magic resistance from an amount.
     */
    [[nodiscard]] virtual float computeMagicReduction(const Entity& Source) const;

    /*
     * Computes the damage done to the entity by an unmitigated auto attack.
     */
    [[nodiscard]] virtual DamageDone PostAutoAttack(const Entity& source, DamageDone& dmg_pre) = 0;

    /*
     * Computes the damage done to the entity by an unmitigated targeted ability.
     */
    [[nodiscard]] virtual DamageDone PostTargetedAbility(const Entity& source, DamageDone& dmg_pre) = 0;

    [[nodiscard]] virtual DamageDone PostAoEAbility(const Entity& Source, DamageDone& dmg_pre) = 0;


    virtual ~Entity() = default;  // polymorphic destruction
};

