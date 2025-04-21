//AutoAttack.h
#pragma once
#include "PreMitigationDamage.h"


class AutoAttack final : public PreMitigationDamage {
public:
    AutoAttack(const Entity& source, const Entity& target);

    [[nodiscard]] DamageDone computePremitigationDamage() const override;
};
