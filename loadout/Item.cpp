//
// Created by pablo on 12/01/2026.
//

#include "Item.h"

Item::Item(std::string name, std::vector<Ratio> terms, std::vector<Effect> effects)
    : name(std::move(name)), stats(std::move(terms)), effects(std::move(effects)) {}

const std::vector<Ratio>& Item::getStats() const { return stats; }
const std::vector<Effect>& Item::getEffects() const { return effects; }
