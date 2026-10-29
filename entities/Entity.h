#pragma once
#include <cstdint>
#include <string>

#include "Stats.h"

class Damage;
using DamageDone = std::array<float, 3>;

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

    [[nodiscard]] virtual float getArmorPen() const noexcept { return 0.f; }
    [[nodiscard]] virtual float getLethality() const noexcept { return 0.f; }
    [[nodiscard]] virtual float getMagicPen() const noexcept { return 0.f; }
    [[nodiscard]] virtual float getMagicPenFlat() const noexcept { return 0.f; }

    //name getter
    [[nodiscard]] std::string getName() const noexcept;
    [[nodiscard]] virtual std::string toString() const;
    //Basic stat HP getter
    [[nodiscard]] float getMaxHP() const noexcept;
    //Basic stat current HP getter
    [[nodiscard]] float getCurrentHP() const noexcept;
    //Basic stat base attack damage getter
    [[nodiscard]] float getBaseAD() const noexcept;
    //Basic stat bonus attack damage getter
    [[nodiscard]] float getBonusAD() const noexcept;
    [[nodiscard]] float getAD() const noexcept;
    //Basic stat ability power getter
    [[nodiscard]] float getAP() const noexcept;
    //Basic stat armor getter
    [[nodiscard]] float getArmor() const noexcept;
    //Basic stat magic resistance getter
    [[nodiscard]] float getMR() const noexcept;
    //Basic stat attack speed getter
    [[nodiscard]] float getAS() const;
    //Basic stat ability haste getter
    [[nodiscard]] float getAH() const noexcept;
    //Basic stat critical strike chance getter
    [[nodiscard]] float getCritChance() const noexcept;
    //Basic stat move speed getter
    [[nodiscard]] float getMS() const noexcept;
    //Basic stat level getter
    [[nodiscard]] int getLevel() const noexcept;
    //Basic stat list getter
    [[nodiscard]] const Stats& getStats() const;

    /*
     *1 for physical, 2 for magical
     **/
    [[nodiscard]] uint8_t getAdaptiveType() const;

    void addCurrentHP(float HP) noexcept;

    /*
     *removes HP, returns True if entity is dead (entity_stats.current_HP <= 0)
     */
    bool removeCurrentHP(float HP) noexcept;
    void addBonusAD(float bonus_AD) noexcept;
    void addBonusArmor(float bonus_armor) noexcept;
    void addBonusMR(float bonus_MR) noexcept;
    void addAS(float AS) noexcept;
    void addAP(float AP) noexcept;
    void addBonusHealth(float bonus_health) noexcept;
    void addBonusMana(float bonus_mana) noexcept;
    void addAH(float ability_haste) noexcept;

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
    [[nodiscard]] virtual DamageDone postAttack(const Entity& source, DamageDone& dmg_pre) = 0;

    //[[nodiscard]] virtual DamageDone attack(const Champion *target, const Damage &effect) const = 0;

    virtual ~Entity() = default;  // polymorphic destruction
};
