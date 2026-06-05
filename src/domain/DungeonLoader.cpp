//
// Created by Daniel Castillo on 04/06/2026.
//

#include "domain/DungeonLoader.h"
#include "domain/Weapon.h"
#include"domain/Potion.h"
#include "domain/Item.h"
#include <fstream>
#include <sstream> //Para leer linea por linea
#include<iostream>

#include "domain/Enemy.h"

using namespace std;

DungeonLoader::DungeonLoader() {}

void DungeonLoader::loadRooms(string filepath) {
    ifstream file(filepath); //Para leer datos desde el archivo de texto
    if (!file.is_open()) {
        cout << "Error opening file" << filepath << "\n";
        return;
    }
    string line;
    while (getline(file, line)) {
        if (line.empty())continue;

        stringstream ss;
        string id_str, name, desc;

        //Cortamos usando el '|'

        getline(ss, id_str, '|');
        getline(ss, name, '|');
        getline(ss, desc, '|');

        //Ya que tenemos un id debemos convertirlo de entero a texto

        int id = stoi(id_str); //Aqui logramos esa conversion necesaria

        //Creamos el cuarto y lo guardamos en nuestro diccionario

        dungeonMap[id] = new Room(name, desc);

    }
    file.close();
    cout <<"-> Base rooms loaded.\n";

}

// Conectar las habitaciones

void DungeonLoader::connectRooms(string filepath) {
    ifstream file(filepath);
    string line;
    while (getline(file, line)) {
        if (line.empty())continue;
        stringstream ss(line);
        string id_str, name, desc,n_str,s_str,e_str,w_str;

        getline(ss, id_str, '|');
        getline(ss, name, '|');
        getline(ss, desc, '|');
        getline(ss, n_str, '|');
        getline(ss, s_str, '|');
        getline(ss, e_str, '|');
        getline(ss, w_str, '|');

        int id = stoi(id_str);
        int n = stoi(n_str);
        int s = stoi(s_str);
        int e = stoi(e_str);
        int w = stoi(w_str);

        Room* currentRoom = dungeonMap[id];

        //Buscamos a los vecinos. SI es -1, significa que hay pared (nullptr)
        Room* north = (n!=-1)?dungeonMap[n]:nullptr;
        Room* east = (e!=-1)?dungeonMap[e]:nullptr;
        Room* west = (w!=-1)?dungeonMap[w]:nullptr;
        Room* south = (s!=-1)?dungeonMap[s]:nullptr;

        currentRoom->setExits(north, south, east, west);

    }
    file.close();
    cout <<"-> Rooms connected.\n";
}
void DungeonLoader:: loadItems(string filepath) {
    ifstream file(filepath);
    string line;
    while (getline(file, line)) {
        if (line.empty())continue;
        stringstream ss(line);
        string type, roomId_str, name, desc, weight_str, rarity, stat_str, effect_str;

        getline(ss, type, '|');
        getline(ss, roomId_str, '|');
        getline(ss, name, '|');
        getline(ss, desc, '|');
        getline(ss, weight_str, '|');
        getline(ss, rarity, '|');
        getline(ss, stat_str, '|');
        getline(ss, effect_str, '|');

        int roomId = stoi(roomId_str);
        double weight = stod(weight_str);
        int stat = stoi(stat_str);

        Item* newItem = nullptr;
        if (type=="W") { //Es un arma
            newItem = new Weapon(name, desc, weight, rarity, stat,effect_str);
        } else if (type=="P") {
            newItem = new Potion(name, desc, weight, rarity, stat,effect_str);
        }
        //Si el item se creo bien lo incluimos en el cuarto correspondiente

        if (newItem!=nullptr && dungeonMap.count(roomId)) {
            dungeonMap[roomId]->addItem(newItem);
        }
    }
    file.close();
    cout <<"-> Items over the dungeon.\n";
}

//Cargar los enemigos y ponerlos en sus cuartos

void DungeonLoader:: loadEnemies(string filepath) {
    ifstream file(filepath);
    string line;
    while (getline(file, line)) {
        if (line.empty())continue;
        stringstream ss(line);
        string roomId_str, name, type, hp_str, dmg_str;

        getline(ss, roomId_str, '|');
        getline(ss, name, '|');
        getline(ss, type, '|');
        getline(ss, hp_str, '|');
        getline(ss, dmg_str, '|');

        int roomId = stoi(roomId_str);
        int hp = stoi(hp_str);
        int dmg = stoi(dmg_str);

        Enemy* newEnemy = new Enemy(name, type, hp, dmg);

        if (dungeonMap.count(roomId)) {
            dungeonMap[roomId]->addEntity(newEnemy);
        }
    }
    file.close();
    cout << "-> Enemies located.\n";
}

