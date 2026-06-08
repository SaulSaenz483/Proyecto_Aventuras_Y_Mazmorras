//
// Created by sauls on 07/06/2026.
//
// Bucle principal del juego. Maneja:
//   - Render del mapa con panel lateral y log
//   - Movimiento del heroe con WASD
//   - Activacion de CombatSystem al tocar un enemigo
//   - Interaccion con NPCs
//   - Recogida de items
//   - Condiciones de victoria (Boss derrotado) y derrota (HP = 0)


#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_SIMULATIONENGINE_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_SIMULATIONENGINE_H

#include "domain/Hero.h"
#include "domain/DungeonLoader.h"
#include "domain/Enemy.h"
#include "output/Logger.h"



enum class GameResult {
    VICTORY,
    DEFEAT
};

class SimulationEngine {
private:
    Hero&          hero;
    DungeonLoader& dungeon;
    Logger&        logger;

    int  heroX;
    int  heroY;
    int  lastDx;   // ultimo delta — usado para retroceder al huir
    int  lastDy;
    bool running;

    // Render
    void drawMap()     const;
    void drawVictory() const;
    void drawDefeat()  const;

    // Helpers
    static std::string hpBar   (int current, int max, int width = 10);
    static std::string padRight(const std::string& s, int width);
    static void   clearScreen();

    // Logica
    bool moveHero    (int dx, int dy);
    void handleEnemies(Room& room);
    void handleNPCs   (Room& room);
    void handleItems  (Room& room);

public:
    SimulationEngine(Hero& h, DungeonLoader& d, Logger& l);
    GameResult run();
};

#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_SIMULATIONENGINE_H
