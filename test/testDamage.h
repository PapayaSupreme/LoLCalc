#pragma once

#include "../entities/Stats.h"

struct RatiosStats;
using DamageDone = std::array<float, 3>;

class Entity;
class Effect;

// === Auto Attack Test ===
//void testAutoAttackDamage(const Entity& source, Entity& target);

void testEffectDamage(const Entity& source, Entity& target, const Effect& effect);

// === Targeted Ability Test ===
//void testTargetedAbilityDamage(const Entity& source, Entity& target, const RatiosStats &targeted_ability_stats,  DamageType type);
