#include <array>

#include "entities/Champion.h"
#include "damage/Effect.h"
#include "damage/Stack.h"
#include "loadout/Item.h"

int main() {
    // === Source Setup ===
    Stats sionStats = {
        .max_HP = 1000,
        .current_HP = 1000,
        .base_AD = 68,
        .bonus_AD = 11
    };
    ChampionStats sionExtras = {
        .lethality = 0.0f,
        .armor_pen = 0.0f
    };
    Champion sion("Sion", sionStats, sionExtras);

    // === Target Setup ===
    Stats vayneStats = sionStats;
    vayneStats.base_armor = 50;
    vayneStats.base_MR = 50;
    ChampionStats vayneExtras = {};
    Champion vayne("Vayne", vayneStats, vayneExtras);

    // === Effects Setup ===
    Effect AutoAttackEffect("Auto attack", EffectTrigger::OnHit, 0.0f,
                                  {{TermStat::total_AD, 1}},
                                  0.0f, std::numeric_limits<float>::infinity(),
                                  std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(),
                                  1.0f, 0.0f, 0.0f);

    Effect MistsEdge("Mist's Edge", EffectTrigger::OnHit, 0.0f,
                                  {{TermStat::target_current_health, 0.09}},
                                  0.0f, std::numeric_limits<float>::infinity(),
                                  std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(),
                                  1.0f, 0.0f, 0.0f);

    Effect PTAProc("Press The Attack Proc", EffectTrigger::OnToggle, 40.0f,
                                  {{TermStat::level, 7.06}},
                                  0.0f, std::numeric_limits<float>::infinity(),
                                  0.0f, 0.0f,
                                  1.0f, 0.0f, 0.0f); // TODO: turn into adaptive dmg

    // === Stacks Setup ===

    Stack PTAStack("Press The Attack Stack", EffectTrigger::OnAttack, std::map<uint16_t, const Effect*> {{3, &PTAProc}}, true);
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

    DamageDone post = {};
    //testEffectDamage(sion, vayne, AutoAttackEffect);
    //testEffectDamage(sion, vayne, MistsEdge);
    post = sion.attack(vayne, AutoAttackEffect);
    post = sion.attack(vayne, AutoAttackEffect);
    post = sion.attack(vayne, AutoAttackEffect);

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
