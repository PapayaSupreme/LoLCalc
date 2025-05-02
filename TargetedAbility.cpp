//TargetedAbility.cpp
#include "TargetedAbility.h"

#include "Entity.h"
TargetedAbility::TargetedAbility(const Entity& source, const Entity& target,
                                 const float AD_ratio, const float AP_ratio,
                                 const float base_damage, const bool ultimate, const int cost,
                                 const float cooldown, const int range, const int channel, const int damage_type)
    : PreMitigationDamage(source, target),
      AD_ratio(AD_ratio), AP_ratio(AP_ratio), base_damage(base_damage), ultimate(ultimate),
      cost(cost), range(range), channel(channel), damage_type(damage_type), cooldown(cooldown) {}

DamageDone TargetedAbility::computePremitigationDamage() const{
    DamageDone dmg = {0.0f, 0.0f, 0.0f};
    float damage_dealt = base_damage + source.getAD() * AD_ratio + source.getAP() * AP_ratio;
    if (damage_type == 0) { // AD
        dmg[static_cast<int>(DamageType::Physical)] = damage_dealt;
    } else if (damage_type == 1) { // AP
        dmg[static_cast<int>(DamageType::Magical)] = damage_dealt;
    } else if (damage_type == 2) { // True
        dmg[static_cast<int>(DamageType::True)] = damage_dealt;
    }
    return dmg;
}
