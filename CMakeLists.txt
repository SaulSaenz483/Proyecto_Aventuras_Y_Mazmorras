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

# Copia automatica de data/ al directorio de build en cada compilacion.
# Funciona en cualquier equipo sin configuracion manual.
add_custom_command(
        TARGET Proyecto_Aventuras_Y_Mazmorras POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:Proyecto_Aventuras_Y_Mazmorras>/data
        COMMENT "Copiando archivos de datos al directorio de build..."
)