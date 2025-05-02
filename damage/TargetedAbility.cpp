//TargetedAbility.cpp
#include "TargetedAbility.h"

#include "../entities/Entity.h"
TargetedAbility::TargetedAbility(const Entity& source, const Entity& target,
                                 const float AD_ratio, const float AP_ratio,
                                 const float base_damage, const bool ultimate, const int cost,
                                 const float cooldown, const int range, const int channel,
                                 const DamageType damage_type_enum)
    : PreMitigationDamage(source, target),
      AD_ratio(AD_ratio), AP_ratio(AP_ratio), base_damage(base_damage), ultimate(ultimate),
      cost(cost), range(range), channel(channel), cooldown(cooldown), damage_type_enum(damage_type_enum) {}

DamageDone TargetedAbility::computePremitigationDamage() const{
    DamageDone dmg = {0.0f, 0.0f, 0.0f};
    float damage_dealt = base_damage + source.getAD() * AD_ratio
                        + source.getAP() * AP_ratio;
    dmg[static_cast<int>(damage_type_enum)] = damage_dealt;
    return dmg;
}
