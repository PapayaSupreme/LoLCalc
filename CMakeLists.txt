cmake_minimum_required(VERSION 3.31)
project(LoLCalc)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(LoLCalc main.cpp
        entities/Entity.cpp
        entities/Entity.h
        entities/Stats.h
        entities/Champion.cpp
        entities/Champion.h
        test/testDamage.cpp
        test/testDamage.h
        damage/Damage.cpp
        damage/Damage.h
        loadout/Item.cpp
        loadout/Item.h
        damage/Stack.cpp
        damage/Stack.h
        structs/EffectTrigger.h
        structs/TermStat.h
        structs/Ratio.h
        damage/Multiplier.cpp
        damage/Multiplier.h
        damage/Effect.cpp
        damage/Effect.h
        structs/EffectType.h
)

# GCC's MinGW implementation of <print> keeps terminal support in the
# experimental standard library extension.
if (MINGW)
    target_link_libraries(LoLCalc PRIVATE stdc++exp)
endif()
