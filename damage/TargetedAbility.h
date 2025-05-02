//TargetedAbility.h
#pragma once
#include "PreMitigationDamage.h"
#include "../entities/Stats.h"


class TargetedAbility final : public PreMitigationDamage {
    /*
     * Class representing a targeted ability in the game.
     * Inherits from PreMitigationDamage.
     * All targeted abilities have a source and target entity, and damage properties.
     */
protected:

    TargetedAbilityStats targeted_ability_stats;
    // FOR NOW, SUPPORTS ONLY ONE DAMAGE TYPE PER ABILITY
    DamageType damage_type_enum;
public:
    /*
     * Constructor for TargetedAbility.
     * Initializes the source and target entities, and damage properties.
     */
    TargetedAbility(const Entity& source, const Entity& target,
                    const TargetedAbilityStats& targeted_ability_stats, DamageType damage_type_enum);

    // Computes the damage done by the targeted ability to the target by the source before mitigation.
    [[nodiscard]] DamageDone computePremitigationDamage() const override;
};
