// PremitigationDamage.cpp
#include "PreMitigationDamage.h"

PreMitigationDamage::PreMitigationDamage(const Entity& source, const Entity& target)
    : source(source), target(target) {}

const Entity& PreMitigationDamage::getSource() const {return source;}
const Entity& PreMitigationDamage::getTarget() const {return target;}