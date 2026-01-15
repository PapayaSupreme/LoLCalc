#include "Multiplier.h"

Multiplier::Multiplier(std::string name, const float multiplier)
    : name(std::move(name)), multiplier(multiplier) {}

std::string Multiplier::get_name() const { return name; }
float Multiplier::get_multiplier() const { return multiplier; }
