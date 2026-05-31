//
// Created by Daniel Castillo on 31/05/2026.
//

//Conectamos con su archivo de cabecera

#include "domain/Weapon.h"

#include<iostream>

using namespace std;

Weapon::Weapon(string n, string d, double w, string r, int atk, string dmgType): Item(n, d, w, r),attackBonus(atk), damageType(dmgType){}

//Implementacion del metodo using

void Weapon:: use(Hero &target) {
    cout << name << "has been equipped. Damage type: "<< damageType << "\n";
}

void Weapon::getInfo() const {
    Item::getInfo(); //LLama a la funcion del padre
    cout <<" -> Attack Bonus: +"<<attackBonus<<" | Damage Type: "<<damageType<<"\n";
}
