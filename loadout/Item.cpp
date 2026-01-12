//
// Created by pablo on 12/01/2026.
//

#include "Item.h"

Item::Item(std::string name, std::vector<Term> terms, std::vector<Effect> effects)
    : name(std::move(name)), stats(std::move(terms)), effects(std::move(effects)) {}

std::vector<Term> Item::getStats() const { return stats; }
std::vector<Effect> Item::getEffects() const { return effects; }
