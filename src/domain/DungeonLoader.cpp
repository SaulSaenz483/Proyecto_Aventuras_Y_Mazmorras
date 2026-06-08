//
// Created by Daniel Castillo on 04/06/2026.
//

#include "domain/DungeonLoader.h"
#include "domain/NPC.h"
#include "domain/Weapon.h"
#include "domain/Potion.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// ── helpers ────────────────────────────────────────────────────────────────

string DungeonLoader::trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end   = s.find_last_not_of(" \t\r\n");
    if (start == string::npos) return "";
    return s.substr(start, end - start + 1);
}

CellType DungeonLoader::charToCell(char c) {
    switch (c) {
        case '#': return CellType::WALL;
        case '.': return CellType::FLOOR;
        case '@': return CellType::PLAYER;
        case 'E': return CellType::ENEMY;
        case 'B': return CellType::BOSS;
        case 'N': return CellType::NPC;
        case '$': return CellType::TREASURE;
        default:  return CellType::FLOOR;
    }
}

// ── constructor / destructor ───────────────────────────────────────────────

DungeonLoader::DungeonLoader()
    : width(0), height(0), startX(1), startY(1), boss(nullptr) {}

DungeonLoader::~DungeonLoader() {
    for (Enemy* e : allEnemies) delete e;
    for (NPC*   n : allNPCs)    delete n;
    for (Item*  i : allItems)   delete i;
}

// ── acceso a la cuadricula ─────────────────────────────────────────────────

bool DungeonLoader::isValid(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

Room& DungeonLoader::getRoom(int x, int y) {
    if (!isValid(x, y))
        throw out_of_range("DungeonLoader::getRoom out of range (" +
                           to_string(x) + "," + to_string(y) + ")");
    return grid[y][x];
}

const Room& DungeonLoader::getRoom(int x, int y) const {
    if (!isValid(x, y))
        throw out_of_range("DungeonLoader::getRoom out of range (" +
                           to_string(x) + "," + to_string(y) + ")");
    return grid[y][x];
}

// ── loadMap ────────────────────────────────────────────────────────────────

void DungeonLoader::loadMap(const string& filepath) {
    ifstream file(filepath);
    if (!file.is_open())
        throw runtime_error("DungeonLoader: cannot be open: " + filepath);

    string line;

    // Linea 1: WIDTH|HEIGHT
    if (!getline(file, line))
        throw runtime_error("DungeonLoader: map.txt is empty");

    {
        stringstream ss(trim(line));
        string w_str, h_str;
        getline(ss, w_str, '|');
        getline(ss, h_str, '|');
        if (w_str.empty() || h_str.empty())
            throw runtime_error("DungeonLoader: line 1 will be WIDTH|HEIGHT");
        width  = stoi(trim(w_str));
        height = stoi(trim(h_str));
        if (width <= 0 || height <= 0)
            throw runtime_error("DungeonLoader: invalid dimensions in map.txt");
    }

    // Inicializar grid con celdas FLOOR
    grid.assign(height, vector<Room>(width));

    // Leer filas del mapa
    for (int row = 0; row < height; row++) {
        if (!getline(file, line))
            throw runtime_error("DungeonLoader: missing rows in map.txt (row " +
                                to_string(row) + ")");

        // Rellenar con '.' si la linea es mas corta que width
        while ((int)line.size() < width) line += '.';

        for (int col = 0; col < width; col++) {
            CellType ct = charToCell(line[col]);
            grid[row][col].setType(ct);

            // '@' marca la posicion de inicio del heroe
            if (ct == CellType::PLAYER) {
                startX = col;
                startY = row;
                grid[row][col].setType(CellType::FLOOR);
            }
        }
    }

    file.close();
    cout << "-> Loading map (" << width << "x" << height << ").\n";
}

// ── loadEnemies ────────────────────────────────────────────────────────────

void DungeonLoader::loadEnemies(const string& filepath) {
    ifstream file(filepath);
    if (!file.is_open())
        throw runtime_error("DungeonLoader: Cannot be open: " + filepath);

    string line;
    int lineNum = 0;

    while (getline(file, line)) {
        lineNum++;
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;

        stringstream ss(line);
        string col_str, row_str, name, type, hp_str, dmg_str;

        getline(ss, col_str, '|');
        getline(ss, row_str, '|');
        getline(ss, name,    '|');
        getline(ss, type,    '|');
        getline(ss, hp_str,  '|');
        getline(ss, dmg_str, '|');

        if (col_str.empty() || row_str.empty() || name.empty())
            throw runtime_error("DungeonLoader: invalid line " +
                                to_string(lineNum) + " en: " + filepath);

        int col = stoi(trim(col_str));
        int row = stoi(trim(row_str));
        int hp  = stoi(trim(hp_str));
        int dmg = stoi(trim(dmg_str));
        type    = trim(type);

        if (!isValid(col, row))
            throw runtime_error("DungeonLoader: position (" + to_string(col) +
                                "," + to_string(row) + ") out of row " +
                                to_string(lineNum));

        Enemy* e = new Enemy(trim(name), type, hp, dmg);
        allEnemies.push_back(e);
        grid[row][col].addEnemy(e);

        if (type == "Boss") {
            if (boss != nullptr)
                throw runtime_error("DungeonLoader: There can only be one boss.");
            boss = e;
            grid[row][col].setType(CellType::BOSS);
        } else {
            grid[row][col].setType(CellType::ENEMY);
        }
    }

    file.close();

    if (boss == nullptr)
        throw runtime_error("DungeonLoader: enemies.txt does not contain any Bosses.\n"
                            "    Add a line with the ‘Boss’ type.");

    cout << "-> " << allEnemies.size() << " loaded enemies (Boss: "
         << boss->getName() << ").\n";
}

// ── loadItems ──────────────────────────────────────────────────────────────

void DungeonLoader::loadItems(const string& filepath) {
    ifstream file(filepath);
    if (!file.is_open())
        throw runtime_error("DungeonLoader: Cannot be open: " + filepath);

    string line;
    int lineNum = 0;

    while (getline(file, line)) {
        lineNum++;
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;

        stringstream ss(line);
        string type, col_str, row_str, name, desc, weight_str, rarity, stat_str, effect_str;

        getline(ss, type,       '|');
        getline(ss, col_str,    '|');
        getline(ss, row_str,    '|');
        getline(ss, name,       '|');
        getline(ss, desc,       '|');
        getline(ss, weight_str, '|');
        getline(ss, rarity,     '|');
        getline(ss, stat_str,   '|');
        getline(ss, effect_str, '|');

        if (type.empty() || col_str.empty() || name.empty())
            throw runtime_error("DungeonLoader: invalid line " +
                                to_string(lineNum) + " en: " + filepath);

        int    col    = stoi(trim(col_str));
        int    row    = stoi(trim(row_str));
        double weight = stod(trim(weight_str));
        int    stat   = stoi(trim(stat_str));
        type          = trim(type);

        if (!isValid(col, row))
            throw runtime_error("DungeonLoader: position (" + to_string(col) +
                                "," + to_string(row) + ") out of row " +
                                to_string(lineNum));

        Item* newItem = nullptr;

        if (type == "W") {
            newItem = new Weapon(trim(name), trim(desc), weight,
                                 trim(rarity), stat, trim(effect_str));
        } else if (type == "P") {
            newItem = new Potion(trim(name), trim(desc), weight,
                                 trim(rarity), stat, trim(effect_str));
        } else {
            cerr << "DungeonLoader: unknown type '" << type
                 << "' in line " << lineNum << " — ignore.\n";
            continue;
        }

        allItems.push_back(newItem);
        grid[row][col].addItem(newItem);
        grid[row][col].setType(CellType::TREASURE);
    }

    file.close();
    cout << "-> " << allItems.size() << " loaded items.\n";
}

