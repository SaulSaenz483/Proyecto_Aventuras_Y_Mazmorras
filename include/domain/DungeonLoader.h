//
// Created by Daniel Castillo on 04/06/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_DUNGEONLOADER_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_DUNGEONLOADER_H

#include "domain/Room.h"
#include "domain/Enemy.h"
#include <vector>
#include <string>



class DungeonLoader {
private:

    std::vector<std::vector<Room>> grid;  // grid[row][col]
    int width;
    int height;
    int startX;
    int startY;

    Enemy* boss;               // victory condition

    // DungeonLoader owns these objects
    std::vector<Enemy*> allEnemies;
    std::vector<NPC*>   allNPCs;
    std::vector<Item*>  allItems;

    static std::string    trim(const std::string& s);
    static CellType  charToCell(char c);

public:
    DungeonLoader();
    ~DungeonLoader();

    DungeonLoader(const DungeonLoader&)            = delete;
    DungeonLoader& operator=(const DungeonLoader&) = delete;

    // Load in this order:
    void loadMap     (const std::string& filepath);
    void loadEnemies (const std::string& filepath);
    void loadItems   (const std::string& filepath);
    void loadNPCs    (const std::string& filepath);

    // Access to the grid
    Room&       getRoom(int x, int y);
    const Room& getRoom(int x, int y) const;
    bool        isValid(int x, int y) const;

    int getWidth()  const { return width;  }
    int getHeight() const { return height; }
    int getStartX() const { return startX; }
    int getStartY() const { return startY; }

    Enemy* getBoss() const { return boss; }
};


#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_DUNGEONLOADER_H
