#pragma once
#include <string>
#include <vector>

#include "../entities/Stats.h"
#include "../damage/Effect.h"

class Item {
protected:
    const std::string name;
    const std::vector<Ratio> stats;
    const std::vector<Effect> effects;
public:
    Item(std::string name, std::vector<Ratio> terms, std::vector<Effect> effects);

    [[nodiscard]] const std::vector<Ratio>& getStats() const;
    [[nodiscard]] const std::vector<Effect>& getEffects() const;
};
