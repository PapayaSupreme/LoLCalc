//TargetedAbility.h
#pragma once
#include "PreMitigationDamage.h"


class TargetedAbility final : public PreMitigationDamage {
    /*
     * Class representing a targeted ability in the game.
     * Inherits from PreMitigationDamage.
     * All targeted abilities have a source and target entity, and damage properties.
     */
protected:
    const float AD_ratio, AP_ratio, base_damage;
    const bool ultimate;
    const int cost, range, channel;
    const float cooldown;
    // FOR NOW, SUPPORTS ONLY ONE DAMAGE TYPE PER ABILITY
    DamageType damage_type_enum;
public:
    /*
     * Constructor for TargetedAbility.
     * Initializes the source and target entities, and damage properties.
     */
    TargetedAbility(const Entity& source, const Entity& target,
                    float AD_ratio, float AP_ratio, float base_damage,
                    bool ultimate, int cost, float cooldown, int range,
                    int channel, DamageType damage_type_enum);

    // Computes the damage done by the targeted ability to the target by the source before mitigation.
    [[nodiscard]] DamageDone computePremitigationDamage() const override;
};
