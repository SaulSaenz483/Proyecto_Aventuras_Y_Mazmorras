//
// Created by Daniel Castillo on 31/05/2026.
//

#include "domain/Hero.h"
#include <iostream>

using namespace std;

Hero::Hero(string n, int health, int attack)
    : Entity(n), hp(health), maxHp(health), baseAttack(attack) {}

Hero::~Hero() {
    for (Item* item : inventory)
        delete item;
    inventory.clear();
}

void Hero::interact() {
    cout << name << " is ready for battle! HP: " << hp << "/" << maxHp << "\n";
}

void Hero::takeDamage(int amount) {
    hp -= amount;
    if (hp < 0) hp = 0;
    cout << name << " took " << amount << " damage. Remaining HP: " << hp << "\n";
}

void Hero::heal(int amount) {
    hp += amount;
    if (hp > maxHp) hp = maxHp;
    cout << name << " recovered " << amount << " HP. Current HP: " << hp << "\n";
}

void Hero::addItem(Item* item) {
    inventory.push_back(item);
    cout << "Added [" << item->getName() << "] to inventory.\n";
}

void Hero::showInventory() const {
    cout << "\n=== " << name << "'s Inventory ===\n";
    if (inventory.empty()) {
        cout << "Inventory is empty.\n";
        return;
    }
    for (size_t i = 0; i < inventory.size(); i++) {
        cout << i + 1 << ". ";
        inventory[i]->getInfo();
    }
    cout << "========================\n\n";
}

