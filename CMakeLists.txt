cmake_minimum_required(VERSION 4.2)
project(Proyecto_Aventuras_Y_Mazmorras)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(Proyecto_Aventuras_Y_Mazmorras main.cpp ${SOURCES}
        include/domain/Potion.h
        src/domain/Potion.cpp
        include/domain/Hero.h
        src/domain/Hero.cpp
        include/domain/Enemy.h
        src/domain/Enemy.cpp
        include/domain/NPC.h
        src/domain/NPC.cpp)