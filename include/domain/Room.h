//
// Created by Daniel Castillo on 04/06/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_ROOM_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_ROOM_H

#include <string>
#include <vector>
#include "domain\Item.h"
#include "domain/Entity.h"

using namespace std;

class Room {
private:
    string name;
    string description;


    //Punteros a otras habitaciones (nullptr significa que hay pared)

    Room* north;
    Room* south;
    Room* east;
    Room* west;

    //Contenido de la habitacion, tendran que existir Items y Entities

    vector<Item*> itemsInRoom;
    vector<Entity*> entitiesInRoom;

public:
    Room(string n, string des);
    ~Room(); //Para limpiar memoria si la habitacion se destruye

    //Conectar habitaciones

    void setExits(Room* n, Room* s, Room* e, Room* w );

    //Agregar contenido
    void addItem(Item* item);
    void addEntity(Entity* entity);

    //Ver que hay alrededor
    void lookAround()const;

    //Getters de salidas para movilizarnos

    Room* getNorth()const{return north;}
    Room* getSouth()const{return south;}
    Room* getEast()const{return east;}
    Room* getWest()const{return west;}
    string getName()const{return name;}





};


#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_ROOM_H
