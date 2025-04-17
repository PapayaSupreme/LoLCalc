cmake_minimum_required(VERSION 3.31)
project(LoLCalc)

set(CMAKE_CXX_STANDARD 20)

add_executable(LoLCalc main.cpp
        Entity.cpp
        Entity.h
        Stats.h
        Champion.cpp
        Champion.h)
