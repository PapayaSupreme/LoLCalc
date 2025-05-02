//testDamage.cpp

#include <iostream>
#include "testDamage.h"
#include "../damage/AutoAttack.h"
#include "../damage/TargetedAbility.h"
#include "../entities/Champion.h"
#include "../damage/AoEAbility.h"
#include "../damage/DoTAbility.h"

// === Auto Attack Test ===
void testAutoAttackDamage(const Entity& source, Entity& target) {
    const auto aa = AutoAttack(source, target);
    DamageDone pre = aa.computePremitigationDamage();
    const DamageDone post = target.PostAutoAttack(source, pre);

    std::cout << "\n[AutoAttack]\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << "Raw " << i << ":  " << pre[i] << "\n";
        std::cout << "Post-Mitigation: "<< i << ":  " << post[i] << "\n";
    }
    //print the source lethality and armor pen then the target armor if the source is a chmapion
    if (const auto* champSource = dynamic_cast<const Champion*>(&source)) {
        std::cout << "Source Lethality: " << champSource->getLethality() << "\n";
        std::cout << "Source Armor Pen: " << champSource->getArmorPen() << "\n";
    }
    std::cout << "Target Armor: " << target.getArmor() << "\n";
}

// === Targeted Ability Test ===
void testTargetedAbilityDamage(const Entity& source, Entity& target, const TargetedAbilityStats &targeted_ability_stats, DamageType type) {
    TargetedAbility q = TargetedAbility(source, target, targeted_ability_stats, type);
    DamageDone pre = q.computePremitigationDamage();
    DamageDone post = target.PostTargetedAbility(source, pre);

    std::cout << "\n[Targeted Ability]\n";
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
}


// === AoE Damage Test (Stub) ===
void testAOEDamage(const Entity& source, Entity& target,
                   const AoEAbilityStats &aoe_ability_stats, DamageType type) {
    AoEAbility r = AoEAbility(source, target, aoe_ability_stats, type);
    DamageDone pre = r.computePremitigationDamage();
    DamageDone post = target.PostTargetedAbility(source, pre);

    std::cout << "\n[AoE Ability]\n";
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
}

// === DoT Damage Test (Stub) ===
void testDoTDamage(const Entity& source, Entity& target,
                   const DoTAbilityStats &dot_ability_stats, DamageType type) {
    DoTAbility dot = DoTAbility(source, target, dot_ability_stats, type);
    DamageDone pre = dot.computePremitigationDamage();
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
}
