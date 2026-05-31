//
// Created by Daniel Castillo on 31/05/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_ITEM_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_ITEM_H

#include <string>
#include <iostream>
using namespace std;

//Forward declaration para evitar dependencias circulares

class Hero;

class Item {

protected:
    string name;
   string description;
    double weight;
    string rarity;

public:
    Item(string n,string d, double w, string r):name(n), description(d), weight(w), rarity(r) {}

    virtual ~Item() = default; //Destructor virtual esencial para herencia polimorfica

    //El metodo virtual puro que definimos para que la clase sea abstracta

    virtual void use(Hero& target) = 0;
    virtual void getInfo()const {
        std::cout << "[" << rarity << "] " << name << ": " << description << " (" << weight << "kg)\n";
    }
    //Getters y setters irian aca, de momento no los he implementado
    string getName() const{return name;}


};





#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_ITEM_H
