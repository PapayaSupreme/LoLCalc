//AoEAbility.cpp
#include "AoEAbility.h"

#include "../entities/Entity.h"
AoEAbility::AoEAbility(const Entity& source, const Entity& target,
                                 const AoEAbilityStats &aoe_ability_stats,
                                 const DamageType damage_type_enum)
    : PreMitigationDamage(source, target), aoe_ability_stats(aoe_ability_stats),
            damage_type_enum(damage_type_enum) {}

DamageDone AoEAbility::computePremitigationDamage() const{
    DamageDone dmg = {0.0f, 0.0f, 0.0f};
    float damage_dealt = this->aoe_ability_stats.base_damage + source.getAD() * this->aoe_ability_stats.AD_ratio
                        + source.getAP() * this->aoe_ability_stats.AP_ratio;
    dmg[static_cast<int>(damage_type_enum)] = damage_dealt;
    return dmg;
}
