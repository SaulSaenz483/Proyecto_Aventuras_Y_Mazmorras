//
// Created by Daniel Castillo on 31/05/2026.
//

#include "domain/Enemy.h"
#include <iostream>

using namespace std;

Enemy::Enemy(string n, string type, int health, int dam):Entity(n),enemyType(type),hp(health),maxHp(health),damage(dam){}

void Enemy:: interact() {
    if (hp > 0) {
        cout << "A wild " << enemyType << " named " << name << " appears! (HP: " << hp << ", DMG: " << damage << ")\n";
    } else {
        cout << name << " the " << enemyType << " is lying dead on the floor.\n";
    }

}

void Enemy:: takeDamage(int amount) {
    hp -= amount;
    if (hp < 0) hp=0;
    cout << name << "took "<< amount << " damage!\n";
    if (hp==0) {
        cout <<"It has been defeated!\n";
    } else {
        cout <<"HP remaining: " <<hp << "\n";
    }
}

