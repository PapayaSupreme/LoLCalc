#pragma once
#include <string>
#include <vector>

#include "../damage/Effect.h"
#include "../entities/Stats.h"

class Item {
protected:
    const std::string name;
    const std::vector<Term> stats;
    const std::vector<Effect> effects;
public:
    Item(std::string name, std::vector<Term> terms, std::vector<Effect> effects);

    [[nodiscard]] std::vector<Term> getStats() const;
    [[nodiscard]] std::vector<Effect> getEffects() const;
};
