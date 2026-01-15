#pragma once
#include <array>
#include <string>

using DamageDone = std::array<float, 3>;

class Multiplier {
protected:
    const std::string name;
    const float multiplier;
public:
    Multiplier(std::string name, float multiplier);

    [[nodiscard]] std::string get_name() const;
    [[nodiscard]] float get_multiplier() const;
};