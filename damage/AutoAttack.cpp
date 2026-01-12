//AutoAttck.cpp
#include "AutoAttack.h"

#include "../entities/Entity.h"
AutoAttack::AutoAttack(const Entity& source, const Entity& target)
    : PreMitigationDamage(source, target) {}

DamageDone AutoAttack::computePremitigationDamage() const{
    DamageDone dmg = {0.0f, 0.0f, 0.0f};
    dmg[static_cast<int>(DamageType::Physical)] = source.getBaseAD();
    return dmg;
}
