//
// Created by pablo on 12/01/2026.
//

#include "Item.h"

Item::Item(std::string name, std::vector<Ratio> terms, std::vector<Damage> effects)
    : name(std::move(name)), stats(std::move(terms)), effects(std::move(effects)) {}

const std::vector<Ratio>& Item::getStats() const { return stats; }
const std::vector<Damage>& Item::getEffects() const { return effects; }
