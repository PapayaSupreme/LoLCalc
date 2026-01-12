//Ability.h
#pragma once
#include "PreMitigationDamage.h"
#include "../entities/Stats.h"


class Ability final : public PreMitigationDamage {
    /*
     * Class representing a targeted ability in the game.
     * Inherits from PreMitigationDamage.
     * All targeted abilities have a source and target entity, and damage properties.
     */
protected:

    RatiosStats ability_stats;
    // FOR NOW, SUPPORTS ONLY ONE DAMAGE TYPE PER ABILITY
    DamageType damage_type_enum;
public:
    /*
     * Constructor for Ability.
     * Initializes the source and target entities, and damage properties.
     */
    Ability(const Entity& source, const Entity& target,
                    const RatiosStats& ability_stats, DamageType damage_type_enum);

    // Computes the damage done by the targeted ability to the target by the source before mitigation.
    [[nodiscard]] DamageDone computePremitigationDamage() const override;
};
