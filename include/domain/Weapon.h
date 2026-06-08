//
// Created by Daniel Castillo on 31/05/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_WEAPON_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_WEAPON_H

#include "domain/Item.h"
#include <string>



//Weapon hereda de Item

    class Weapon: public Item {
    private:
        int attackBonus;
        std::string damageType; // Slash, piercing, magic, throw, etc. // Seria correcto eliminar el damageType para simplificar el sistema,
                                                                  //  dejarlo como un unico tipo  de daño simplifica la tare
    public:
        Weapon(std::string n, std::string d, double w, std::string r, int atk, std::string dmgType);

        //Destructor (usamos override porque el de su padre es virtual)

        ~Weapon() override = default;

        //Aplicamos polimorfismo sobreescribiendo el metodo virtual puro

        void use(Hero &target) override;

        void getInfo() const override; //Para incluir la informacion adicional de Weapon

        int getAttackBonus()const{return attackBonus;}
        std::string getDamageType()const{return damageType;}


    };




#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_WEAPON_H
