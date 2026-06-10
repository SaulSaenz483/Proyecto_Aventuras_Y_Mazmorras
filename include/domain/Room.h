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



// Each type maps to exactly one ASCII character — always 1 byte wide
enum class CellType {
    FLOOR,      // '.'
    WALL,       // '#'
    PLAYER,     // '@'
    ENEMY,      // 'E'
    BOSS,       // 'B'  <- Final boss; defeat him = victory
    NPC,        // 'N'
    TREASURE    // '$'
};

class Room {
private:
    CellType       type;
    std::string         description;
    bool           visited;

// Non-owner pointers — DungeonLoader is the owner
    std::vector<Enemy*> enemies;
    std::vector<NPC*>   npcs;
    std::vector<Item*>  items;

public:
    explicit Room(CellType t = CellType::FLOOR, const std::string& desc = "");

    // --- Type y render ---
    CellType      getType()         const { return type; }
    void          setType(CellType t)     { type = t; }
    char          getSymbol()       const;
    bool          isWalkable()      const { return type != CellType::WALL; }

    // --- Description ---
    const std::string& getDescription()  const { return description; }
    void          setDescription(const std::string& d) { description = d; }

    // --- Visited (for the final report) ---
    bool isVisited()  const { return visited; }
    void markVisited()      { visited = true; }

    // --- Entities ---
    void addEnemy(Enemy* e) { enemies.push_back(e); }
    void addNPC(NPC* n)     { npcs.push_back(n); }
    void addItem(Item* i)   { items.push_back(i); }

    const std::vector<Enemy*>& getEnemies() const { return enemies; }
    const std::vector<NPC*>&   getNPCs()    const { return npcs; }
    const std::vector<Item*>&  getItems()   const { return items; }

    bool hasLiveEnemies() const;
    bool hasBoss()        const;
    bool hasNPCs()        const { return !npcs.empty(); }
    bool hasItems()       const { return !items.empty(); }

    void removeDeadEnemies();
    void removeItem(Item* item);
};


#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_ROOM_H
