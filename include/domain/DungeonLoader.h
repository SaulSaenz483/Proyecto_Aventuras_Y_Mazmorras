//
// Created by Daniel Castillo on 04/06/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_DUNGEONLOADER_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_DUNGEONLOADER_H

#include "domain/Room.h"
#include "domain/Enemy.h"
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

class DungeonLoader {
private:
    vector<vector<Room>> grid;  // grid[row][col]
    int width;
    int height;
    int startX;
    int startY;

    Enemy* boss;               // condicion de victoria

    // DungeonLoader es dueno de estos objetos
    vector<Enemy*> allEnemies;
    vector<NPC*>   allNPCs;
    vector<Item*>  allItems;

    static string    trim(const string& s);
    static CellType  charToCell(char c);

public:
    DungeonLoader();
    ~DungeonLoader();

    DungeonLoader(const DungeonLoader&)            = delete;
    DungeonLoader& operator=(const DungeonLoader&) = delete;

    // Cargar en este orden:
    void loadMap     (const string& filepath);
    void loadEnemies (const string& filepath);
    void loadItems   (const string& filepath);
    void loadNPCs    (const string& filepath);

    // Acceso a la cuadricula
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
