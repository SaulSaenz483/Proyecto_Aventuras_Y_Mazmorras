//
// Created by Daniel Castillo on 31/05/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_ENTITY_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_ENTITY_H

#include<string>
using namespace std;

class Entity {
protected:
    string name;

public:
    Entity(string n): name(n) {}
    virtual ~Entity()=default;

    //Metodo virtual puro para el polimorfismo
    virtual void interact()=0;
    string getName()const {return name;}
    
};

#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_ENTITY_H
