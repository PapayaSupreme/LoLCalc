#pragma once
class Entity;
#include <array>
enum class DamageType : int {
    Physical = 0,
    Magical  = 1,
    True     = 2
};

using DamageDone = std::array<float, 3>;

class PreMitigationDamage {
protected:
    const Entity& source;
    const Entity& target;
public:
    PreMitigationDamage(const Entity& source, const Entity& target);
    virtual ~PreMitigationDamage() = default;

    [[nodiscard]] const Entity& getSource() const;
    [[nodiscard]] const Entity& getTarget() const;

    [[nodiscard]] virtual DamageDone computePremitigationDamage() const = 0;
};
