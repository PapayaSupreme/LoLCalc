//TargetedAbility.cpp
#include "TargetedAbility.h"

#include "../entities/Entity.h"
TargetedAbility::TargetedAbility(const Entity& source, const Entity& target,
                                 const TargetedAbilityStats& targeted_ability_stats, const DamageType damage_type_enum)
    : PreMitigationDamage(source, target), targeted_ability_stats(targeted_ability_stats), damage_type_enum(damage_type_enum) {}

DamageDone TargetedAbility::computePremitigationDamage() const{
    DamageDone dmg = {0.0f, 0.0f, 0.0f};
    float damage_dealt = this->targeted_ability_stats.base_damage + source.getAD() * this->targeted_ability_stats.AD_ratio
                        + source.getAP() * this->targeted_ability_stats.AP_ratio;
    dmg[static_cast<int>(damage_type_enum)] = damage_dealt;
    return dmg;
}
