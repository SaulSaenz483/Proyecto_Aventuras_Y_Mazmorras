//
// Created by Daniel Castillo on 31/05/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_ITEM_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_ITEM_H

#include <string>
#include <iostream>


//Forward declaration to avoid circular dependencies

class Hero;

class Item {

protected:
    std::string name;
   std::string description;
    double weight;
    std::string rarity;

public:
    Item(std::string n,std::string d, double w, std::string r):name(n), description(d), weight(w), rarity(r) {}

    virtual ~Item() = default; //Essential virtual destructor for polymorphic inheritance

    //The pure virtual method to make the class abstract

    virtual void use(Hero& target) = 0;
    virtual void getInfo()const {
        std::cout << "[" << rarity << "] " << name << ": " << description << " (" << weight << "kg)\n";
    }

    std::string getName() const{return name;}


};





#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_ITEM_H
