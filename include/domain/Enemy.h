//
// Created by Daniel Castillo on 31/05/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_ENEMY_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_ENEMY_H

#include "domain/Entity.h"
#include <string>



class Enemy: public Entity {
private:
    std::string enemyType;
    int hp;
    int maxHp;
    int damage;

public:
    Enemy(std::string n, std::string type, int health, int dam);
    ~Enemy() override = default;


    void interact() override; //Override the interact method for polymorphism

    void takeDamage(int amount);

    //Getters
    int getHp() const { return hp; }
    int getMaxHp() const { return maxHp; }
    int getDamage() const { return damage; }
    std::string getEnemyType() const { return enemyType; }

    bool isAlive() const { return hp > 0; }




};

#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_ENEMY_H
