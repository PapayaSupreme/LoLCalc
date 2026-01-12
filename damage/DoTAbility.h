//DoTAbility.h
#pragma once
#include "PreMitigationDamage.h"
#include "../entities/Stats.h"

class DoTAbility final : public PreMitigationDamage {
    /*
     * Class representing a damage over time ability in the game.
     * Inherits from PreMitigationDamage.
     * All damage over time abilities have a source and target entity, and damage properties.
     */
protected:
    DoTAbilityStats dot_ability_stats;
    // FOR NOW, SUPPORTS ONLY ONE DAMAGE TYPE PER ABILITY
    DamageType damage_type_enum;

public:
    /*
     * Constructor for DoTAbility.
     * Initializes the source and target entities, and damage properties.
     */
    DoTAbility(const Entity &source, const Entity &target,
               const DoTAbilityStats &dot_ability_stats, DamageType damage_type_enum);

    // Computes the damage done by the AoE ability to the target by the source before mitigation.
    [[nodiscard]] DamageDone computePremitigationDamage() const override;
};