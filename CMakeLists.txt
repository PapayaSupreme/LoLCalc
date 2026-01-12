cmake_minimum_required(VERSION 3.31)
project(LoLCalc)

set(CMAKE_CXX_STANDARD 20)

add_executable(LoLCalc main.cpp
        entities/Entity.cpp
        entities/Entity.h
        entities/Stats.h
        entities/Champion.cpp
        entities/Champion.h
        damage/PreMitigationDamage.cpp
        damage/PreMitigationDamage.h
        damage/AutoAttack.cpp
        damage/AutoAttack.h
        damage/Ability.cpp
        damage/Ability.h
        test/testDamage.cpp
        test/testDamage.h
        damage/DoTAbility.cpp
        damage/DoTAbility.h
        damage/Effect.cpp
        damage/Effect.h
        loadout/Item.cpp
        loadout/Item.h)
