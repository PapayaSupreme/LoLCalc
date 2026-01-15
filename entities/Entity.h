#pragma once
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

    [[nodiscard]] virtual float get_armor_pen() const noexcept { return 0.f; }
    [[nodiscard]] virtual float get_lethality() const noexcept { return 0.f; }
    [[nodiscard]] virtual float get_magic_pen() const noexcept { return 0.f; }
    [[nodiscard]] virtual float get_magic_pen_flat() const noexcept { return 0.f; }

    //name getter
    [[nodiscard]] std::string get_name() const noexcept;
    //Basic stat HP getter
    [[nodiscard]] float get_HP() const noexcept;
    //Basic stat current HP getter
    [[nodiscard]] float get_current_HP() const noexcept;
    //Basic stat base attack damage getter
    [[nodiscard]] float get_base_AD() const noexcept;
    //Basic stat bonus attack damage getter
    [[nodiscard]] float get_bonus_AD() const noexcept;
    //Basic stat ability power getter
    [[nodiscard]] float get_AP() const noexcept;
    //Basic stat armor getter
    [[nodiscard]] float get_armor() const noexcept;
    //Basic stat magic resistance getter
    [[nodiscard]] float get_MR() const noexcept;
    //Basic stat attack speed getter
    [[nodiscard]] float get_AS() const;
    //Basic stat ability haste getter
    [[nodiscard]] float get_AH() const noexcept;
    //Basic stat critical strike chance getter
    [[nodiscard]] float get_crit_chance() const noexcept;
    //Basic stat move speed getter
    [[nodiscard]] float get_MS() const noexcept;
    //Basic stat level getter
    [[nodiscard]] int get_level() const noexcept;
    //Basic stat list getter
    [[nodiscard]] const Stats& getStats() const;

    void add_bonus_AD(float bonus_AD) noexcept;
    void add_bonus_armor(float bonus_armor) noexcept;
    void add_bonus_MR(float bonus_MR) noexcept;
    void add_AS(float AS) noexcept;
    void add_AP(float AP) noexcept;
    void add_bonus_health(float bonus_health) noexcept;
    void add_bonus_mana(float bonus_mana) noexcept;

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
    [[nodiscard]] virtual DamageDone post_attack(const Entity& source, DamageDone& dmg_pre) = 0;

    //[[nodiscard]] virtual DamageDone attack(const Champion *target, const Damage &effect) const = 0;

    virtual ~Entity() = default;  // polymorphic destruction
};

