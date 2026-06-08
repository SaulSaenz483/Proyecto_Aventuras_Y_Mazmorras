//
// Created by Daniel Castillo on 31/05/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_POTION_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_POTION_H

#include "domain/Item.h"
#include <string>



class Potion:public Item {

private:

    int effectValue; //Cuanto cura o cuanta fuerza da
    std::string effectType; // Heal , buff

public:
    Potion(std::string n, std::string desc, double w, std::string r, int val, std::string type);
    ~Potion() override = default;

    void use(Hero& target) override;
    void getInfo() const override;

    //Getters
    int getEffectValue() const{return effectValue;}
    std::string getEffectType() const{return effectType;}




};




#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_POTION_H
