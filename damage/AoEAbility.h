//AoEAbility.h
#pragma once
#include "PreMitigationDamage.h"
#include "../entities/Stats.h"

class AoEAbility final : public PreMitigationDamage {
    /*
     * Class representing an area of effect ability in the game.
     * Inherits from PreMitigationDamage.
     * All area of effect abilities have a source and target entity, and damage properties.
     */
protected:
    AoEAbilityStats aoe_ability_stats;
    // FOR NOW, SUPPORTS ONLY ONE DAMAGE TYPE PER ABILITY
    DamageType damage_type_enum;
public:
    /*
     * Constructor for AoEAbility.
     * Initializes the source and target entities, and damage properties.
     */
    AoEAbility(const Entity& source, const Entity& target,
                    const AoEAbilityStats &aoe_ability_stats, DamageType damage_type_enum);

    // Computes the damage done by the AoE ability to the target by the source before mitigation.
    [[nodiscard]] DamageDone computePremitigationDamage() const override;
};
