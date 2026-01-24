#include <array>
#include <iostream>

#include "entities/Champion.h"
#include "damage/Damage.h"
#include "damage/Multiplier.h"
#include "damage/Stack.h"
#include "loadout/Item.h"

int main() {
    // === Source Setup ===
    Stats sionStats = {
        .max_HP = 1400,
        .current_HP = 1400,
        .base_AD = 68,
        .bonus_AD = 5 // from stat runes
    };
    ChampionStats sionExtras = {
        .lethality = 0.0f,
        .armor_pen = 0.0f
    };
    Champion sion("Sion", sionStats, sionExtras);

    // === Target Setup ===
    Stats vayneStats = sionStats;
    vayneStats.base_armor = 10;
    vayneStats.base_MR = 10;
    ChampionStats vayneExtras = {};
    Champion vayne("Vayne", vayneStats, vayneExtras);

    // === Effects Setup ===
    Damage AutoAttackEffect("Auto attack", EffectTrigger::OnHit, 0.0f,
                                  {{TermStat::total_AD, 1}},
                                  1.0f, 0.0f, 0.0f);

    Damage MistsEdge("Mist's Edge", EffectTrigger::OnHit, 0.0f,
                                  {{TermStat::target_current_health, 0.09}},
                                  0.0f, std::numeric_limits<float>::infinity(),
                                  std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(),
                                  1.0f, 0.0f, 0.0f); //TODO: add real max monster dmg

    Damage PTAProc("Press The Attack Proc", EffectTrigger::OnActivate, 40.0f,
                                  {{TermStat::level, 7.06}});

    Multiplier PTA("Press The Attack", 1.08);

    // === Stacks Setup ===

    Stack PTAStack("Press The Attack Stack", EffectTrigger::OnAttack, std::multimap<uint16_t, const Effect*> {{3, &PTAProc}, {3, &PTA}}, true);
    // === Items Setup ===
    Item LongSword("Long Sword", {{TermStat::bonus_AD, 10}}, {{}});
    Item BORK("Blade of the Ruined King",
        {{TermStat::bonus_AD, 40}, {TermStat::bonus_AS, 25}, {TermStat::lifesteal, 10}},
        {MistsEdge});
    Item Serylda("Serylda's Grudge",
        {{TermStat::bonus_AD, 45}, {TermStat::armor_pen, 35}, {TermStat::ability_haste, 15}},
        {});

    //buy
    sion.buy_item(BORK);
    sion.buy_item(Serylda);
    sion.add_on_attack_stack(PTAStack);
    std::cout << sion.get_base_AD() << " + " << sion.get_bonus_AD();

    DamageDone post = {};
    DamageDone total = {};
    //testEffectDamage(sion, vayne, AutoAttackEffect);
    //testEffectDamage(sion, vayne, MistsEdge);
    for (int i = 0;i<4;i++) {
        std::cout << "\n======  "<< i << "  ======\n\n";
        post = sion.attack(vayne, AutoAttackEffect);
        for (int j = 0;j<3;j++) {
            total[j] += post[j];
        }
    }

    std::cout << "\n TOTAL (POST): " << total[0] << " " << total[1] << " " << total[2] << "\n";

    /*
    constexpr int WARMUP = 10'000;
    constexpr int ITERS  = 1'000'000;

    // --- WARMUP ---
    for (int i = 0; i < WARMUP; ++i) {
        auto dmg = sion.attack(vayne, AutoAttackEffect);
        sink += dmg[0] + dmg[1] + dmg[2];
    }

    // --- TIMED SECTION ---
    const auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < ITERS; ++i) {
        auto dmg = sion.attack(vayne, AutoAttackEffect);
        sink += dmg[0] + dmg[1] + dmg[2];
    }

    const auto end = std::chrono::steady_clock::now();

    const auto total_ns =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    std::cout << "Total: " << total_ns << " ns\n";
    std::cout << "Avg per attack: "
              << static_cast<double>(total_ns) / ITERS
              << " ns\n";
    std::cout << "sink: " << sink << "\n";
    */
    return 0;
}
