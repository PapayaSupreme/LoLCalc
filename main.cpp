#include <array>
#include <chrono>
#include <iostream>
#include <limits>
#include <print>
#include "entities/Champion.h"
#include "damage/Damage.h"
#include "damage/Multiplier.h"
#include "damage/Stack.h"
#include "loadout/Item.h"
#include "test/testDamage.h"

int main() {
    std::println("Initializing...");
    // === Source Setup ===
    Stats sionStats = {
        .max_HP = 1400,
        .current_HP = 1400,
        .base_AD = 68,
        .bonus_AD = 0 // from stat runes
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

    Damage AbilityEffect("Sion ability", EffectTrigger::OnAbilityHit, 100.0f,
                                  {{TermStat::total_AD, 0.6f}},
                                  1.0f, 0.0f, 0.0f);

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

    bool quit = false;
    bool loadoutApplied = false;

    while (!quit) {
        std::println("\n=== MAIN MENU ===");
        std::println("1. See champion stats");
        std::println("2. Buy items and gain Press The Attack");
        std::println("3. Test the three damage types");
        std::println("4. Record the time of 1,000,000 attacks");
        std::println("0. EXIT");
        std::print("Choose an option: ");

        int option = -1;
        if (!(std::cin >> option)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::println("Invalid input.");
            continue;
        }

        switch (option) {
            case 1:
                std::println("\n{}", sion.toString());
                std::println("\n{}", vayne.toString());
                break;

            case 2:
                if (loadoutApplied) {
                    std::println("Sion already has BORK, Serylda's Grudge, and PTA.");
                    break;
                }
                sion.buy_item(BORK);
                sion.buy_item(Serylda);
                sion.add_on_attack_stack(PTAStack);
                loadoutApplied = true;
                std::println("Sion bought BORK and Serylda's Grudge and gained PTA.");
                break;

            case 3:
                testAutoAttackDamage(sion, vayne);
                testAbilityDamage(sion, vayne, AbilityEffect);
                testEffectDamage(sion, vayne, MistsEdge);
                break;

            case 4: {
                constexpr int WARMUP = 10'000;
                constexpr int ITERS = 1'000'000;

                for (int i = 0; i < WARMUP; ++i) {
                    static_cast<void>(sion.attack(vayne, AutoAttackEffect));
                }

                const auto start = std::chrono::steady_clock::now();
                for (int i = 0; i < ITERS; ++i) {
                    static_cast<void>(sion.attack(vayne, AutoAttackEffect));
                }
                const auto end = std::chrono::steady_clock::now();

                const auto total_ns =
                    std::chrono::duration_cast<std::chrono::nanoseconds>(
                        end - start).count();
                std::println("Total: {} ns", total_ns);
                std::println("Average per attack: {} ns",
                             static_cast<double>(total_ns) / ITERS);
                break;
            }

            case 0:
                quit = true;
                break;

            default:
                std::println("Unknown option.");
                break;
        }
    }

    return 0;
}
