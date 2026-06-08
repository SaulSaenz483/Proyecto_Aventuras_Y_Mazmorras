//
// Created by Daniel Castillo on 31/05/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_NPC_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_NPC_H


#include"domain/Entity.h"
#include <iostream>
#include<string>


class NPC:public Entity {
private:
    std::string dialogue;
public:
    NPC(std::string n, std::string dial);
    ~NPC() override = default;

    void interact() override;
    std::string getDialogue()const{return dialogue;}
};

#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_NPC_H
