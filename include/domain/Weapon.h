//
// Created by Daniel Castillo on 31/05/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_WEAPON_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_WEAPON_H

#include "domain/Item.h"
#include <string>



//Weapon inherits from Item

    class Weapon: public Item {
    private:
        int attackBonus;
        std::string damageType; // Slash, piercing, magic, throw, etc.
    public:
        Weapon(std::string n, std::string d, double w, std::string r, int atk, std::string dmgType);

        //Destructor

        ~Weapon() override = default;

        //Implement polymorphism by overriding the pure virtual method

        void use(Hero &target) override;

        void getInfo() const override; //To include additional information about Weapon

        int getAttackBonus()const{return attackBonus;}
        std::string getDamageType()const{return damageType;}


    };




#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_WEAPON_H
