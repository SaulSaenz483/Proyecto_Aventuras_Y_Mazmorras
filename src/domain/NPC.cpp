//
// Created by Daniel Castillo on 31/05/2026.
//

#include "domain/Potion.h"
#include "domain/NPC.h"
#include "domain/Hero.h"
#include <iostream>

using namespace std;

NPC::NPC(string n, string dial, string action, int value)
    : Entity(n), dialogue(dial), actionType(action), actionValue(value), actionUsed(false) {}

void NPC::interact() {
    cout << "  | " << name << "\n";
    cout << "  " << dialogue << "\n";
}

void NPC::applyEffect(Hero& hero) {
    if (actionUsed) {
        cout << "  " << name << ": I have nothing more to offer, traveler.\n";
        return;
    }

    if (actionType == "heal") {
        hero.heal(actionValue);
        cout << "  " << name << " channels ancient magic and restores "
             << actionValue << " HP!\n";
        actionUsed = true;
    } else if (actionType == "give_potion") {
        Potion* p = new Potion("Knight's Potion", "Given by a wounded knight",
                               0.3, "Uncommon", actionValue, "Heal");
        hero.addItem(p);
        cout << "  " << name << " hands you a potion. Use it wisely!\n";
        actionUsed = true;
    } else {
        cout << "  " << name << " has nothing to offer.\n";
    }
}