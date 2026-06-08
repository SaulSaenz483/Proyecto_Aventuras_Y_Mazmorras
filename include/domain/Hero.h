//
// Created by Daniel Castillo on 31/05/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_HERO_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_HERO_H

#include "domain/Entity.h"
#include "domain/Item.h"
#include <vector>
#include <string>

using namespace std;

class Hero: public Entity {
private:
    int hp;
    int maxHp;        // necesario para la barra de HP en la interfaz
    int baseAttack;
    vector<Item*> inventory;

public:
    Hero(string n, int health, int attack);
    ~Hero() override;

    void interact() override;

    // Acciones
    void takeDamage(int amount);
    void heal(int amount);        // usado por Potion en combate
    void addItem(Item* item);
    void showInventory() const;

    // Getters
    int  getHp()           const { return hp; }
    int  getMaxHp()        const { return maxHp; }
    int  getBaseAttack()   const { return baseAttack; }
    bool isAlive()         const { return hp > 0; }

    const vector<Item*>& getInventory() const { return inventory; }
};

#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_HERO_H
