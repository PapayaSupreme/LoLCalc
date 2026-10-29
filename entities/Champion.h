// Champion.h
#pragma once

#include <vector>

#include "Entity.h"


using DamageDone = std::array<float, 3>;

class Multiplier;
class Effect;
class Damage;
class Stack;
class Item;
class Champion : public Entity {
    /*
     * Class representing a champion in the game.
     * Inherits from Entity.
     * All champions have basic stats and champion stats.
     */
protected:
    ChampionStats champion_stats;
    std::vector<const Damage*> on_hit_damage_effects;
    std::vector<const Damage*> on_ability_damage_effects; // TODO: some abilities dont proc effects when they dont damage except hextech alternator, eg anivia wall. fix that
    std::vector<const Damage*> on_attack_damage_effects;
    std::vector<const Multiplier*> post_attack_multiplier;
    std::vector<Stack*> on_attack_stacks;
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
    [[nodiscard]] float getLethality() const noexcept override;
    // Champion stat armor penetration getter
    [[nodiscard]] float getArmorPen() const noexcept override;
    // Champion stat magic penetration flat getter
    [[nodiscard]] float getMagicPenFlat() const noexcept override;
    // Champion stat magic penetration getter
    [[nodiscard]] float getMagicPen() const noexcept override;
    // Champion stat life steal getter
    [[nodiscard]] float getLifesteal() const noexcept;
    // Champion stat omnivamp getter
    [[nodiscard]] float getOmnivamp() const noexcept;
    // Champion stat tenacity getter
    [[nodiscard]] float getTenacity() const noexcept;
    // Champion stat spell vampirism getter
    [[nodiscard]] float getSpellVamp() const noexcept;
    // Champion stat critical damage multiplier getter
    [[nodiscard]] float getCritDamage() const noexcept;
    // Champion stat basic ability haste getter
    [[nodiscard]] float getBasicAH() const noexcept;
    // Champion stat ultimate ability haste getter
    [[nodiscard]] float getUltimateAH() const noexcept;
    // Champion stat critical damage reduction getter
    [[nodiscard]] float getCritDamageReduction() const noexcept;
    // Champion stat list getter
    [[nodiscard]] const ChampionStats& getChampionStats() const;
    [[nodiscard]] std::string toString() const override;
    [[nodiscard]] const std::vector<const Damage *>& getOnHitEffects() const;
    [[nodiscard]] const std::vector<const Damage *>& getOnAbilityHitEffects() const;
    [[nodiscard]] const std::vector<const Damage *>& getOnAttackEffects() const;
    [[nodiscard]] std::vector<Stack *> getOnAttackStacks() const;
    [[nodiscard]] const std::vector<const Multiplier *>& getPostAttackMultipliers() const;

    void addOmnivamp(float omnivamp) noexcept; // TODO: fucking do a function that takes the thing as input and updates it
                                                //instead of having 1000 functions
    void addLifesteal(float lifesteal) noexcept;
    void add_spell_vamp(float spell_vamp) noexcept;
    void add_lethality(float lethality) noexcept;
    void add_armor_pen(float armor_pen) noexcept;
    void add_magic_pen(float magic_pen) noexcept;
    void add_magic_pen_flat(float magic_pen_flat) noexcept;

    void add_on_hit_effect(const Damage& effect);
    void add_on_ability_hit_effect(const Damage& effect);
    void add_on_attack_effect(const Damage& effect);
    void add_on_attack_stack(Stack& stack);
    void add_post_attack_multiplier(const Multiplier& multiplier);

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
    [[nodiscard]] DamageDone postAttack(const Entity& source, DamageDone& dmg_pre) override;

    [[nodiscard]] DamageDone attack(Entity& target, const Damage& effect) const;

    /*
     * Adds an item, its stats and its  effects to a champion
     */
    void buyItem(const Item& item);
};
