//
// Created by sauls on 07/06/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_COMBATSYSTEM_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_COMBATSYSTEM_H

#include "domain/Hero.h"
#include "domain/Enemy.h"
#include "output/Logger.h"



// Resultado posible al salir del combate
enum class CombatResult {
    HERO_WON,   // el enemigo murio
    HERO_DIED,  // el heroe murio
    HERO_FLED,   // el heroe huyo (enemigo sigue vivo)
    CONTINUE    // turno terminó, combate sigue
};

class CombatSystem {
private:
    Hero&   hero;
    Enemy&  enemy;
    Logger& logger;

    // Render de la pantalla de combate
    void drawCombatScreen() const;

    // Acciones individuales — devuelven true si el combate termino
    CombatResult attack();
    CombatResult useItem();
    CombatResult flee();

    // Turno del enemigo — contraataca siempre despues de la accion del heroe
    // devuelve true si el heroe murio
    bool enemyTurn();

    // Barra de HP visual: [||||||||  ] 80/100
    static std::string hpBar(int current, int max, int width = 10);
    static std::string padRight(const std::string& s, int width);

public:
    CombatSystem(Hero& h, Enemy& e, Logger& l);

    // Inicia el bucle completo de combate y devuelve el resultado
    CombatResult start();
};


#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_COMBATSYSTEM_H
