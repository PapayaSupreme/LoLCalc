#pragma once
#include <string>
#include <vector>

#include "../entities/Stats.h"
#include "../damage/Damage.h"

class Item {
protected:
    const std::string name;
    const std::vector<Ratio> stats;
    const std::vector<Damage> effects;
public:
    Item(std::string name, std::vector<Ratio> terms, std::vector<Damage> effects);

    [[nodiscard]] const std::vector<Ratio>& getStats() const;
    [[nodiscard]] const std::vector<Damage>& getEffects() const;
};
