//
// Created by Daniel Castillo on 31/05/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_NPC_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_NPC_H


#include"domain/Entity.h"
#include<string>

class Hero;

class NPC: public Entity {
private:
    std::string dialogue;
    std::string actionType;  // "heal", "give_potion", "none"
    int    actionValue; // HP amount or effect value
    bool   actionUsed;  // Each NPC can only help once

public:
    NPC(std::string n, std::string dial, std::string action = "none", int value = 0);
    ~NPC() override = default;

    void interact() override;
    void applyEffect(Hero& hero);   // Apply the effect to the hero

    std::string getDialogue()   const { return dialogue; }
    std::string getActionType() const { return actionType; }
    bool   isActionUsed()  const { return actionUsed; }
};

#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_NPC_H
