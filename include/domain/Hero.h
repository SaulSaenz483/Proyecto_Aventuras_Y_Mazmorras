//
// Created by Daniel Castillo on 31/05/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_HERO_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_HERO_H

#include "domain/Entity.h"
#include "domain/Item.h"
#include <vector>
#include <string>



class Hero: public Entity {
private:
    int hp;
    int maxHp;
    int baseAttack;
    int weaponBonus;
    std::vector<Item*> inventory;

public:
    Hero(std::string n, int health, int attack);
    ~Hero() override;

    void interact() override;

    // Acciones
    void takeDamage(int amount);
    void heal(int amount);
    void equipWeapon(int bonus);
    void addItem(Item* item);
    void showInventory() const;
    void removeItem(Item* item);

    // Getters
    int  getHp()           const { return hp; }
    int  getMaxHp()        const { return maxHp; }
    int  getBaseAttack()   const { return baseAttack + weaponBonus; }
    int  getRawAttack()    const {return baseAttack; }
    int  getWeaponBonus()  const {return weaponBonus; }
    bool isAlive()         const { return hp > 0; }

    const std::vector<Item*>& getInventory() const { return inventory; }
};

#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_HERO_H
