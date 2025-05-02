//AutoAttack.h
#pragma once
#include "PreMitigationDamage.h"


class AutoAttack final : public PreMitigationDamage {
    /*
     * Class representing an auto attack in the game.
     * Inherits from PreMitigationDamage.
     * All auto attacks have a source and target entity.
     */
public:
    /*
     * Constructor for AutoAttack.
     * Initializes the source and target entities.
     */
    AutoAttack(const Entity& source, const Entity& target);

    // Computes the damage done by the auto-attack to the target by the source before mitigation.
    [[nodiscard]] DamageDone computePremitigationDamage() const override;
};
