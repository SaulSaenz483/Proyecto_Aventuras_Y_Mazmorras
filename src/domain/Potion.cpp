//
// Created by Daniel Castillo on 31/05/2026.
//

#include "domain/Potion.h"
#include "domain/Hero.h"
#include <iostream>

Potion::Potion(string n, string desc, double w, string r, int val, string type):Item(n,desc,w,r),effectValue(val),effectType(type){}

void Potion::use(Hero& target) {
    if (effectType == "Heal" || effectType == "heal") {
        target.heal(effectValue);
        cout << "Used " << name << ". Restored " << effectValue << " HP.\n";
    } else {
        cout << "Used " << name << ". Applied " << effectType
             << " with intensity: " << effectValue << "\n";
    }
}

void Potion:: getInfo() const {
    Item::getInfo();
    cout << " -> Effect: " << effectType << " (" << effectValue << " pts)\n";
}


