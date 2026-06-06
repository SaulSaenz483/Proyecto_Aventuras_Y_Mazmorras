//
// Created by sauls on 04/06/2026.
//

#include "domain/Room.h"
#include "domain/Enemy.h"
#include "domain/Item.h"
#include <algorithm>

Room::Room(CellType t, const string& desc)
    : type(t), description(desc), visited(false) {}

char Room::getSymbol() const {
    switch (type) {
        case CellType::FLOOR:    return '.';
        case CellType::WALL:     return '#';
        case CellType::PLAYER:   return '@';
        case CellType::ENEMY:    return 'E';
        case CellType::BOSS:     return 'B';
        case CellType::NPC:      return 'N';
        case CellType::TREASURE: return '$';
        default:                 return '?';
    }
}

bool Room::hasLiveEnemies() const {
    for (const Enemy* e : enemies)
        if (e->isAlive()) return true;
    return false;
}

bool Room::hasBoss() const {
    for (const Enemy* e : enemies)
        if (e->getEnemyType() == "Boss" && e->isAlive()) return true;
    return false;
}

void Room::removeDeadEnemies() {
    enemies.erase(
        remove_if(enemies.begin(), enemies.end(),
                  [](const Enemy* e){ return !e->isAlive(); }),
        enemies.end()
    );
}

void Room::removeItem(Item* item) {
    auto it = find(items.begin(), items.end(), item);
    if (it != items.end())
        items.erase(it);
}

