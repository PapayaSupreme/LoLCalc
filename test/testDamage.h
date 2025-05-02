#pragma once

#include "../damage/PreMitigationDamage.h"  // for DamageDone and DamageType
#include "../entities/Entity.h"  // for Entity

// === Auto Attack Test ===
void testAutoAttackDamage(const Entity& source, Entity& target);

// === Targeted Ability Test ===
void testTargetedAbilityDamage(const Entity& source, Entity& target, const TargetedAbilityStats &targeted_ability_stats,  DamageType type);

// === AoE Damage Test ===
void testAOEDamage(const Entity& source, Entity& target,
                   const AoEAbilityStats &aoe_ability_stats, DamageType type);

// === DoT Damage Test ===
void testDoTDamage(const Entity& source, Entity& target,
                   const DoTAbilityStats &dot_ability_stats, DamageType type);
