//
// Created by Daniel Castillo on 31/05/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_HERO_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_HERO_H

//Incluiremos <vector> para un mejor manejo de Item que ya posee polimorfismo

#include "domain/Entity.h"
#include "domain/Item.h"
#include<vector>
#include <string>

using namespace std;

class Hero: public Entity {
private:
    int hp;
    int baseAttack;
    vector<Item*> inventory; //Un arreglo dinamico de punteros a la clase Item

public:
    Hero(string n, int health, int attack);
    ~Hero()override;

    //Sobreescribimos el metodo virtual puro de Entity
    void interact() override;

    //Acciones propias del heroe
    void takeDamage(int amount);
    void addItem(Item* item);
    void showInventory() const;

    //Getters
    int getHp() const{return hp;}
    int getBaseAttack() const{return baseAttack;}




};

#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_HERO_H
