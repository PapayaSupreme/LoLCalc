//TargetedAbility.h
#pragma once
#include "PreMitigationDamage.h"


class TargetedAbility final : public PreMitigationDamage {
protected:
    const float AD_ratio, AP_ratio, base_damage;
    const bool ultimate;
    const int cost, range, channel, damage_type; //0 for ad, 1 for ap, 2 for true
    const float cooldown;
public:
    TargetedAbility(const Entity& source, const Entity& target,
                    float AD_ratio, float AP_ratio, float base_damage, bool ultimate,
                    int cost, float cooldown, int range, int channel, int damage_type);

    [[nodiscard]] DamageDone computePremitigationDamage() const override;
};
