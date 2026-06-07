//
// Created by Daniel Castillo on 31/05/2026.
//

#include "domain/Potion.h"

Potion::Potion(string n, string desc, double w, string r, int val, string type):Item(n,desc,w,r),effectValue(val),effectType(type){}

void Potion:: use(Hero& target)  {
    cout << "Using " << name << ". Applied " << effectType << " with intensity: " << effectValue << "\n";
}
void Potion:: getInfo() const {
    Item::getInfo();
    cout << " -> Effect: " << effectType << " (" << effectValue << " pts)\n";
}


