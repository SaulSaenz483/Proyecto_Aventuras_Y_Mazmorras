//
// Created by Daniel Castillo on 04/06/2026.
//

#include "domain/Room.h"

Room::Room(string n, string des):name(n), description(des),north(nullptr),south(nullptr),east(nullptr),west(nullptr) {}

Room::~Room() {

    //Liberamos la memoria de las items y entidades

    for (Item* item: itemsInRoom) {

        delete item;

    }

    for (Entity* entity: entitiesInRoom) {
        delete entity;
    }
    itemsInRoom.clear(); //La libreria los limpia de esta manera con clear
    entitiesInRoom.clear();
}

//Conectar habitaciones

void Room:: setExits(Room* n, Room* s, Room* e, Room* w ) {
    north = n;
    south = s;
    east = e;
    west = w;
}

//Agregar contenido, utilizamos el comando de la libreria
void Room:: addItem(Item* item) {
    itemsInRoom.push_back(item);
}
void Room:: addEntity(Entity* entity) {
    entitiesInRoom.push_back(entity);
}

//Ver que hay alrededor
void Room:: lookAround()const {
    cout << "\n--- [" << name << "] ---\n";
    cout << description << "\n";

    cout <<"\nExits: ";
    if (north) cout << "[North] ";
    if (south) cout << "[South] ";
    if (east) cout << "[East] ";
    if (west) cout << "[West] ";
    cout << "\n";

    //Preguntamos y recorremos si hay entidades y Items en las habitaciones

    if (!entitiesInRoom.empty()) {
        cout << "\nYou see someone/something here:\n";
        for (Entity* e: entitiesInRoom) {
            cout << "- "<< e->getName() << "\n";
        }
    }

    if (!itemsInRoom.empty()) {
        cout << "\nItems on the floor:\n";
        for (Item* item: itemsInRoom) {
            cout << "- "<< item->getName() << "\n";
        }
    }
    cout << "----------------------\n\n";
}
