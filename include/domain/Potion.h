//
// Created by Daniel Castillo on 31/05/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_POTION_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_POTION_H

#include "domain/Item.h"
#include <string>

using namespace std;

class Potion:public Item {

private:

    int effectValue; //Cuanto cura o cuanta fuerza da
    string effectType; // Heal , buff

public:
    Potion(string n, string desc, double w, string r, int val, string type);
    ~Potion() override = default;

    void use(Hero& target) override;
    void getInfo() const override;

    //Getters
    int getEffectValue() const{return effectValue;}
    string getEffectType() const{return effectType;}




};




#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_POTION_H
