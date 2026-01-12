#pragma once
#include <string>
#include <vector>

#include "../entities/Stats.h"
#include "../damage/Effect.h"

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
