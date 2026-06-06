//
// Created by sauls on 04/06/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_ROOM_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_ROOM_H

#include <vector>
#include <string>

class Enemy;
class NPC;
class Item;

using namespace std;

// Cada tipo mapea a exactamente 1 caracter ASCII — ancho siempre 1
enum class CellType {
    FLOOR,      // '.'
    WALL,       // '#'
    PLAYER,     // '@'  (solo para render)
    ENEMY,      // 'E'
    BOSS,       // 'B'  <- jefe final, derrotarlo = victoria
    NPC,        // 'N'
    TREASURE    // '$'
};

class Room {
private:
    CellType       type;
    string         description;
    bool           visited;

    // Punteros no propietarios — DungeonLoader es dueno
    vector<Enemy*> enemies;
    vector<NPC*>   npcs;
    vector<Item*>  items;

public:
    explicit Room(CellType t = CellType::FLOOR, const string& desc = "");

    // --- Tipo y render ---
    CellType      getType()         const { return type; }
    void          setType(CellType t)     { type = t; }
    char          getSymbol()       const;
    bool          isWalkable()      const { return type != CellType::WALL; }

    // --- Descripcion ---
    const string& getDescription()  const { return description; }
    void          setDescription(const string& d) { description = d; }

    // --- Visitado (para el reporte final) ---
    bool isVisited()  const { return visited; }
    void markVisited()      { visited = true; }

    // --- Entidades ---
    void addEnemy(Enemy* e) { enemies.push_back(e); }
    void addNPC(NPC* n)     { npcs.push_back(n); }
    void addItem(Item* i)   { items.push_back(i); }

    const vector<Enemy*>& getEnemies() const { return enemies; }
    const vector<NPC*>&   getNPCs()    const { return npcs; }
    const vector<Item*>&  getItems()   const { return items; }

    bool hasLiveEnemies() const;
    bool hasBoss()        const;
    bool hasNPCs()        const { return !npcs.empty(); }
    bool hasItems()       const { return !items.empty(); }

    void removeDeadEnemies();
    void removeItem(Item* item);
};


#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_ROOM_H
