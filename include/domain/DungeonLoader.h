//
// Created by Daniel Castillo on 04/06/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_DUNGEONLOADER_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_DUNGEONLOADER_H

#include <string>
#include<map> //Manejo de diccionario
#include "domain/Room.h"

using namespace std;

class DungeonLoader {
private:

    //Un diccionario que guarda: [ID del cuarto]-> [Puntero al cuarto real]

    map<int, Room*> dungeonMap;

public:
    DungeonLoader();
    ~DungeonLoader()=default;

    //Metodos para cargar cada archivo

    void loadRooms(string filepath);
    void loadItems(string filepath);
    void loadEnemies(string filepath);

    //Metodo para conectar las habitaciones

    void connectRooms(string filepath);

    //Getter para devolver el mapa del juego

    map<int, Room*> getDungeonMap()const{return dungeonMap;}


};

#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_DUNGEONLOADER_H
