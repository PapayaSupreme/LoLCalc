#include <iostream>
#include "entities/Champion.h"
#include "damage/Effect.h"
#include "loadout/Item.h"
#include "test/testDamage.h"

int main() {
    // === Champion Setup ===
    Stats sionStats = {
        .max_HP = 1000,
        .current_HP = 1000,
        .base_AD = 68,
        .bonus_AD = 51
    };
    ChampionStats sionExtras = {
        .lethality = 0.0f,
        .armor_pen = 0.0f
    };


    Champion sion("Sion", sionStats, sionExtras);


    Effect AutoAttackEffect("Auto Attack", EffectTrigger::OnHit, 0.0f,
                                  {{TermStat::total_AD, 1}},
                                  0.0f, std::numeric_limits<float>::infinity(),
                                  std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(),
                                  1.0f, 0.0f, 0.0f);

    Effect MistsEdge("Mist's Edge", EffectTrigger::OnHit, 0.0f,
                                  {{TermStat::target_current_health, 0.09}},
                                  0.0f, std::numeric_limits<float>::infinity(),
                                  std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(),
                                  1.0f, 0.0f, 0.0f);

    Stats brandStats = sionStats;
    brandStats.base_armor = 50;
    brandStats.base_MR = 50;
    ChampionStats brandExtras = {};
    Champion brand("Brand", brandStats, brandExtras);  // simulate brand as target

    Item LongSword("Long Sword", {{TermStat::bonus_AD, 10}}, {{}});
    Item BORK("Blade of the Ruined King",
        {{TermStat::bonus_AD, 40}, {TermStat::bonus_AS, 25}, {TermStat::lifesteal, 10}},
        {MistsEdge});
    //testAutoAttackDamage(sion, brand);
    testEffectDamage(sion, brand, AutoAttackEffect);
    testEffectDamage(sion, brand, MistsEdge);
    /*testAbilityDamage(kennen, brand, kennenQstats, damageTypekennenq);
    testDoTDamage(brand, kennen, brandqstats, damageTypekennenq);*/
    return 0;
}
