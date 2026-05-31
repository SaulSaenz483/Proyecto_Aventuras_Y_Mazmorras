//
// Created by Daniel Castillo on 31/05/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_ENEMY_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_ENEMY_H

#include "domain/Entity.h"
#include <string>

using namespace std;

class Enemy: public Entity {
private:
    string enemyType;
    int hp;
    int damage;

public:
    Enemy(string n, string type, int health, int dam);
    ~Enemy() override = default;


    void interact() override; //Sobreescribimos el interact para polimorfismo

    void takeDamage(int amount);

    //Getters
    int getHp() const { return hp; }
    int getDamage() const { return damage; }
    string getEnemyType() const { return enemyType; }

    bool isAlive() const { return hp > 0; }




};

#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_ENEMY_H
