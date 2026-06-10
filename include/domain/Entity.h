//
// Created by Daniel Castillo on 31/05/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_ENTITY_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_ENTITY_H

#include<string>


class Entity {
protected:
    std::string name;

public:
    Entity(std::string n): name(n) {}
    virtual ~Entity()=default;

//Pure virtual method for polymorphism
    virtual void interact()=0;
    std::string getName()const {return name;}
    
};

#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_ENTITY_H
