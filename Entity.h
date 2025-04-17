// Entity.h
#pragma once
#include "Stats.h"

class Entity {
protected:
    Stats entity_stats;

public:
    explicit Entity(const Stats& stats);

    [[nodiscard]] float getHP() const;
    [[nodiscard]] float getCurrHP() const;
    [[nodiscard]] float getAD() const;
    [[nodiscard]] float getAP() const;
    [[nodiscard]] float getArmor() const;
    [[nodiscard]] float getMR() const;
    [[nodiscard]] float getAS() const;
    [[nodiscard]] float getAH() const;
    [[nodiscard]] float getCrit() const;
    [[nodiscard]] float getMS() const;

    [[nodiscard]] const Stats& getStats() const;

    virtual ~Entity() = default;  // polymorphic destruction
};

