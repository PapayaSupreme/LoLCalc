#include <iostream>
#include "testDamage.h"

#include <array>

#include "../damage/Damage.h"

/*void testDamage(const Entity&source, const Entity& target, const DamageDone pre, const DamageDone post) {
    std::cout << "Raw Physical Damage: " << pre[0] << "\n";
    if (const auto* champSource = dynamic_cast<const Champion*>(&source)) {
        std::cout << "Source AD: " << champSource->getBaseAD() << "\n";
        std::cout << "Source Lethality / Armor Pen: " << champSource->getLethality() << " / " << champSource->getArmorPen() << "\n";
    }
    std::cout << "DMG CALCULATION - 1 : Target Armor = " << target.getArmor() << "\n";
    std::cout << "DMG CALCULATION - 2 : Target Damage taken multiplier after Armor Pen then lethality deduction = " << target.computeArmorReduction(source) << "\n";
    std::cout << "DMG CALCULATION - 3 : AD Damage on target: " << post[0] << "\n\n\n";

    std::cout << "Raw Magic Damage: " << pre[1] << "\n";
    if (const auto* champSource = dynamic_cast<const Champion*>(&source)) {
        std::cout << "Source AP: " << champSource->getBaseAD() << "\n";
        std::cout << "Source Magic Pen (%) / Magic Pen (Flat): " << champSource->getMagicPen() << " / " << champSource->getMagicPenFlat() << "\n";
    }
    std::cout << "DMG CALCULATION - 1 : Target MR = " << target.getMR() << "\n";
    std::cout << "DMG CALCULATION - 2 : Target MR after Magic Pen (%) then Magic Pen (Flat) deduction = " << target.computeMagicReduction(source) << "\n";
    std::cout << "DMG CALCULATION - 3 : AP Damage on target: " << post[1] << "\n\n\n";

    std::cout << "Raw True Damage: " << pre[2] << "\n";
    std::cout << "DMG CALCULATION - 1 : True Damage on target: " << post[2] << "\n\n\n";
}
// === Auto Attack Test ===
void testAutoAttackDamage(const Entity& source, Entity& target) {
    const AutoAttack auto_attack = AutoAttack(source, target);
    DamageDone pre = auto_attack.compute_premitigation_damage();
    const DamageDone post = target.post_attack(source, pre);

    std::cout << "Ratios of this Attack: 100% AD \n";
    testDamage(source, target, pre, post);
}


// === Damage Test ===
void testEffectDamage(const Entity& source, Entity& target, const Damage& effect) {
    DamageDone pre = effect.compute_premitigation_damage(source, target);
    const DamageDone post = target.post_attack(source, pre);
    std::cout << "DMG CALCULATION - Damage pre on target: " << pre[0] << " " << pre[1] << " " << pre[2] << "\n";
    std::cout << "DMG CALCULATION - Damage post on target: " << post[0] << " " << post[1] << " " << post[2] << "\n\n\n";
}

// === Targeted Ability Test ===
void testAbilityDamage(const Entity& source, Entity& target, const RatioStats &ability_stats, const DamageType type) {
    const Ability ability = Ability(source, target, ability_stats, type);
    DamageDone pre = ability.compute_premitigation_damage();
    const DamageDone post = target.PostTargetedAbility(source, pre);

    std::cout << "\n[Targeted Ability]\n";

    std::cout << "Ratios of this Attack:  ";
    for (int i = 0; i < static_cast<int>(const RatioStats&ability_stats::Count)-1; ++i) {
        float ratio = static_cast<ability_stats>(i);
        std::cout << ratio << "  ";
    }
    testDamage(source, target, pre, post);
}

// === DoT Damage Test (Stub) === WIP TODO: do that
void testDoTDamage(const Entity& source, Entity& target,
                   const DoTAbilityStats &dot_ability_stats, DamageType type) {
    DoTAbility dot = DoTAbility(source, target, dot_ability_stats, type);
    DamageDone pre = dot.compute_premitigation_damage();
    DamageDone post = target.PostTargetedAbility(source, pre);

    std::cout << "\n[DoT Ability]\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << "Raw " << i << ":  " << pre[i] << "\n";
        std::cout << "Post-Mitigation: "<< i << ":  " << post[i] << "\n";
    }
    // Print source stats if it's a champion
    if (const auto* champSource = dynamic_cast<const Champion*>(&source)) {
        std::cout << "Source AD: " << champSource->getAD() << "\n";
        std::cout << "Source AP: " << champSource->getAP() << "\n";
        std::cout << "Base Damage: 100.0\n";
        std::cout << "AD Ratio: 0.3\n";
        std::cout << "AP Ratio: 0.6\n";
    }
    std::cout << "Target MR: " << target.getMR() << "\n";
    std::cout<< "ticks every "<<dot_ability_stats.tick_rate<<" seconds over "<<dot_ability_stats.duration<<" seconds for a total of "
            <<dot_ability_stats.duration/dot_ability_stats.tick_rate<<" ticks\n";
}*/
