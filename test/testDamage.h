#pragma once

#include "../entities/Stats.h"
#include "../damage/Damage.h"
#include "../entities/Champion.h"
using DamageDone = std::array<float, 3>;

class Entity;
class Damage;

// === Auto attack Test ===
void testAutoAttackDamage(const Entity& source, Entity& target);

void testEffectDamage(const Entity& source, Entity& target, const Damage& effect);

// === Ability Test ===
void testAbilityDamage(const Entity& source, Entity& target,
                       const Damage& ability);
