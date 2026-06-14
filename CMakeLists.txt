cmake_minimum_required(VERSION 4.2)
project(Proyecto_Aventuras_Y_Mazmorras)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

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
        src/domain/NPC.cpp
        include/output/Logger.h
        src/output/Logger.cpp
        include/simulation/CombatSystem.h
        src/simulation/CombatSystem.cpp
        include/simulation/SimulationEngine.h
        src/simulation/SimulationEngine.cpp
        include/output/ReportGenerator.h
        src/output/ReportGenerator.cpp)




file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
