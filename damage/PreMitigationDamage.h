//pragma once

#pragma once
class Entity;
#include <array>

// DamageType enum class
enum class DamageType : int {
    Physical = 0,
    Magical  = 1,
    True     = 2
};

using DamageDone = std::array<float, 3>;

class PreMitigationDamage {
    /*
     * Base class for all pre-mitigation damage calculations.
     * All premitigation damages have a source and target entity.
     */
protected:
    //source entity of the damage
    const Entity& source;
    //target entity of the damage
    const Entity& target;
public:
    /*
     * Constructor for PreMitigationDamage.
     * Initializes the source and target entities.
     */
    PreMitigationDamage(const Entity& source, const Entity& target);

    // Source entity getter
    [[nodiscard]] const Entity& getSource() const;
    // Target entity getter
    [[nodiscard]] const Entity& getTarget() const;

    // Computes the damage done to the target by the source before mitigation.
    [[nodiscard]] virtual DamageDone computePremitigationDamage() const = 0;

    virtual ~PreMitigationDamage() = default;
};
