//
// Created by Daniel Castillo on 31/05/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_NPC_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_NPC_H


#include"domain/Entity.h"
#include <iostream>
#include<string>

class Hero;

class NPC: public Entity {
private:
    std::string dialogue;
    std::string actionType;  // "heal", "give_potion", "none"
    int    actionValue; // cantidad de HP o valor del efecto
    bool   actionUsed;  // cada NPC ayuda solo una vez

public:
    NPC(std::string n, std::string dial, std::string action = "none", int value = 0);
    ~NPC() override = default;

    void interact() override;
    void applyEffect(Hero& hero);   // aplica el efecto al heroe

    std::string getDialogue()   const { return dialogue; }
    std::string getActionType() const { return actionType; }
    bool   isActionUsed()  const { return actionUsed; }
};

#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_NPC_H
