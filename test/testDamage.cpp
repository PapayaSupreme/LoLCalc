#include "testDamage.h"

#include <array>
#include <iostream>

namespace {
void printDamage(const char* label, const Entity& source, const Entity& target,
                 const DamageDone& pre, const DamageDone& post) {
    std::cout << "\n[" << label << "]\n"
              << "Pre-mitigation  (physical, magic, true): "
              << pre[0] << ", " << pre[1] << ", " << pre[2] << '\n'
              << "Post-mitigation (physical, magic, true): "
              << post[0] << ", " << post[1] << ", " << post[2] << '\n'
              << "Target armor/MR: " << target.get_armor() << " / "
              << target.get_MR() << '\n'
              << "Armor/MR multipliers: "
              << target.computeArmorReduction(source) << " / "
              << target.computeMagicReduction(source) << "\n";
}

void testDamage(const char* label, const Entity& source, Entity& target,
                const Damage& damage) {
    const DamageDone pre = damage.compute_premitigation_damage(source, target);
    DamageDone postInput = pre;
    const DamageDone post = target.post_attack(source, postInput);
    printDamage(label, source, target, pre, post);
}
} // namespace

// An auto attack is represented by a physical Damage effect with a 100% total
// AD ratio.
void testAutoAttackDamage(const Entity& source, Entity& target) {
    const Damage autoAttack(
        "Auto attack", EffectTrigger::OnHit, 0.0f,
        {{TermStat::total_AD, 1.0f}}, 1.0f, 0.0f, 0.0f);
    testDamage("Auto attack", source, target, autoAttack);
}

// An ability is also a Damage effect; its base damage and ratios define the
// ability's scaling and its damage type.
void testAbilityDamage(const Entity& source, Entity& target,
                       const Damage& ability) {
    testDamage("Ability", source, target, ability);
}

void testEffectDamage(const Entity& source, Entity& target,
                      const Damage& effect) {
    testDamage("Effect", source, target, effect);
}
