#pragma once
#include <cstdint>

enum class EffectTrigger : uint8_t {
    OnHit, OnCrit, OnAbilityHit, OnAttack, OnToggle
};
