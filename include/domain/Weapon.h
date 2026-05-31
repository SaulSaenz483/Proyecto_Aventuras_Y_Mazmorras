//
// Created by Daniel Castillo on 31/05/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_WEAPON_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_WEAPON_H

#include "domain/Item.h"
#include <string>

using namespace std;

//Weapon hereda de Item

    class Weapon: public Item {
    private:
        int attackBonus;
        string damageType; // Slash, piercing, magic, throw, etc

    public:
        Weapon(string n, string d, double w, string r, int atk, string dmgType);

        //Destructor (usamos override porque el de su padre es virtual)

        ~Weapon() override = default;

        //Aplicamos polimorfismo sobreescribiendo el metodo virtual puro

        void use(Hero &target) override;

        void getInfo() const override; //Para incluir la informacion adicional de Weapon

        int getAttackBonus()const{return attackBonus;}
        string getDamageType()const{return damageType;}


    };




#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_WEAPON_H
