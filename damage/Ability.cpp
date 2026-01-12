//Ability.cpp
#include "Ability.h"

#include "../entities/Entity.h"
/*Ability::Ability(const Entity& source, const Entity& target,
                                 const RatiosStats& ability_stats, const DamageType damage_type_enum)
    : PreMitigationDamage(source, target), ability_stats(ability_stats), damage_type_enum(damage_type_enum) {}

DamageDone Ability::computePremitigationDamage() const{
    DamageDone dmg = {0.0f, 0.0f, 0.0f};
    float damage_dealt = this->ability_stats.base_damage + source.getAD() * this->ability_stats.AD_ratio
                        + source.getAP() * this->ability_stats.AP_ratio;
    dmg[static_cast<int>(damage_type_enum)] = damage_dealt;
    return dmg;
}*/
