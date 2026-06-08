//
// Created by Daniel Castillo on 31/05/2026.
//
#include"domain/NPC.h"
#include "iostream"
using namespace std;


NPC::NPC(string n, string dial):Entity(n),dialogue(dial) {}

void NPC::interact() {
    cout << "  | " << name << "\n";
    cout << "  " << dialogue << "\n";
}