//
// Created by Daniel Castillo on 31/05/2026.
//

#include "domain/Weapon.h"
#include "domain/Hero.h"
#include<iostream>
using std::cout;
using std::string;

Weapon::Weapon(string n, string d, double w, string r, int atk, string dmgType): Item(n, d, w, r),attackBonus(atk), damageType(dmgType){}

void Weapon::use(Hero& target) {
    target.equipWeapon(attackBonus);
    cout << name << " equipped! +" << attackBonus << " ATK (" << damageType << ")\n";
}

void Weapon::getInfo() const {
    Item::getInfo();
    cout <<" -> Attack Bonus: +"<<attackBonus<<" | Damage Type: "<<damageType<<"\n";
}
