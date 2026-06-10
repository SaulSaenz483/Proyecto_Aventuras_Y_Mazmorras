//
// Created by sauls on 07/06/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_COMBATSYSTEM_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_COMBATSYSTEM_H

#include "domain/Hero.h"
#include "domain/Enemy.h"
#include "output/Logger.h"



// Possible outcome upon exiting combat
enum class CombatResult {
    HERO_WON,   // the enemy died
    HERO_DIED,  // the hero died
    HERO_FLED,   // the hero fled (enemy is still alive)
    CONTINUE    // turn ended, combat continues
};

class CombatSystem {
private:
    Hero&   hero;
    Enemy&  enemy;
    Logger& logger;

    // Render the combat screen
    void drawCombatScreen() const;

    // Individual actions — return true if the battle has ended
    CombatResult attack();
    CombatResult useItem();
    CombatResult flee();

    // Enemy's turn — always counterattacks after the hero's action
    // returns true if the hero died
    bool enemyTurn();

    // HP bar: [||||||||  ] 80/100
    static std::string hpBar(int current, int max, int width = 10);
    static std::string padRight(const std::string& s, int width);

public:
    CombatSystem(Hero& h, Enemy& e, Logger& l);

    // Starts the full combat loop and returns the result
    CombatResult start();
};


#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_COMBATSYSTEM_H
