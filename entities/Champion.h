// Champion.h
#pragma once

#include <vector>

#include "Entity.h"

using DamageDone = std::array<float, 3>;

class Effect;
class Item;
class Champion : public Entity {
    /*
     * Class representing a champion in the game.
     * Inherits from Entity.
     * All champions have basic stats and champion stats.
     */
protected:
    ChampionStats champion_stats;
    std::vector<const Effect*> on_hit_effects;
    std::vector<const Effect*> on_ability_hit_effects;
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
    [[nodiscard]] float get_lethality() const noexcept override;
    // Champion stat armor penetration getter
    [[nodiscard]] float get_armor_pen() const noexcept override;
    // Champion stat magic penetration flat getter
    [[nodiscard]] float get_magic_pen_flat() const noexcept override;
    // Champion stat magic penetration getter
    [[nodiscard]] float get_magic_pen() const noexcept override;
    // Champion stat life steal getter
    [[nodiscard]] float get_lifesteal() const noexcept;
    // Champion stat omnivamp getter
    [[nodiscard]] float get_omnivamp() const noexcept;
    // Champion stat tenacity getter
    [[nodiscard]] float get_tenacity() const noexcept;
    // Champion stat spell vampirism getter
    [[nodiscard]] float get_spell_vamp() const noexcept;
    // Champion stat critical damage multiplier getter
    [[nodiscard]] float get_crit_damage() const noexcept;
    // Champion stat basic ability haste getter
    [[nodiscard]] float get_basic_AH() const noexcept;
    // Champion stat ultimate ability haste getter
    [[nodiscard]] float get_ultimate_AH() const noexcept;
    // Champion stat critical damage reduction getter
    [[nodiscard]] float get_crit_damage_reduction() const noexcept;
    // Champion stat list getter
    [[nodiscard]] const ChampionStats& getChampionStats() const;
    [[nodiscard]] const std::vector<const Effect*>& get_on_hit_effects() const;
    [[nodiscard]] const std::vector<const Effect*>& get_on_ability_hit_effects() const;

    void add_omnivamp(float omnivamp) noexcept;
    void add_lifesteal(float lifesteal) noexcept;
    void add_spell_vamp(float spell_vamp) noexcept;
    void add_lethality(float lethality) noexcept;
    void add_armor_pen(float armor_pen) noexcept;
    void add_magic_pen(float magic_pen) noexcept;
    void add_magic_pen_flat(float magic_pen_flat) noexcept;

    void add_on_hit_effect(const Effect& effect);
    void add_on_ability_hit_effect(const Effect& effect);

    void remove_omnivamp(float omnivamp) noexcept;
    void remove_lifesteal(float lifesteal) noexcept;
    void remove_spell_vamp(float spell_vamp) noexcept;
    void remove_armor_pen(float armor_pen) noexcept;
    void remove_lethality(float lethality) noexcept;
    void remove_magic_pen(float magic_pen) noexcept;
    void remove_magic_pen_flat(float magic_pen_flat) noexcept;


    /*
     * Computes the damage done to the champion by an unmitigated attack.
     */
    [[nodiscard]] DamageDone post_attack(const Entity& source, DamageDone& dmg_pre) override;

    [[nodiscard]] DamageDone attack(Entity& target, const Effect& effect) const;

    /*
     * Adds an item, its stats and its  effects to a champion
     */
    void buy_item(const Item& item);
};
