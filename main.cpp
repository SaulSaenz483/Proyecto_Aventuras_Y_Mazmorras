//
// main_test.cpp
// Prueba que DungeonLoader carga el mapa correctamente
// y que Room, Enemy e Item funcionan bien juntos.
//

#include <iostream>
#include "domain/DungeonLoader.h"
#include "domain/Item.h"

using namespace std;

int main() {
    cout << "=== PRUEBA DE CARGA ===\n\n";

    DungeonLoader loader;

    try {
        loader.loadMap    ("data/map.txt");
        loader.loadEnemies("data/enemies.txt");
        loader.loadItems  ("data/items.txt");
    } catch (const exception& e) {
        cerr << "[ERROR] " << e.what() << "\n";
        return 1;
    }

    cout << "\n--- Dimensiones del mapa ---\n";
    cout << "Width : " << loader.getWidth()  << "\n";
    cout << "Height: " << loader.getHeight() << "\n";
    cout << "Start : (" << loader.getStartX() << "," << loader.getStartY() << ")\n";

    cout << "\n--- Boss ---\n";
    if (loader.getBoss()) {
        Enemy* b = loader.getBoss();
        cout << "Nombre: " << b->getName()      << "\n";
        cout << "Tipo  : " << b->getEnemyType() << "\n";
        cout << "HP    : " << b->getHp()        << "\n";
        cout << "Daño  : " << b->getDamage()    << "\n";
    }

    cout << "\n--- Render del mapa (@ = posicion inicio) ---\n";
    for (int row = 0; row < loader.getHeight(); row++) {
        for (int col = 0; col < loader.getWidth(); col++) {
            // Mostrar @ en la posicion de inicio
            if (col == loader.getStartX() && row == loader.getStartY())
                cout << '@';
            else
                cout << loader.getRoom(col, row).getSymbol();
        }
        cout << "\n";
    }

    cout << "\n--- Celdas con contenido ---\n";
    for (int row = 0; row < loader.getHeight(); row++) {
        for (int col = 0; col < loader.getWidth(); col++) {
            const Room& r = loader.getRoom(col, row);

            if (!r.getEnemies().empty()) {
                for (const Enemy* e : r.getEnemies())
                    cout << "(" << col << "," << row << ") Enemigo: "
                         << e->getName() << " [" << e->getEnemyType() << "]"
                         << " HP:" << e->getHp() << "\n";
            }
            if (!r.getItems().empty()) {
                for (const Item* i : r.getItems())
                    cout << "(" << col << "," << row << ") Item: "
                         << i->getName() << "\n";
            }
        }
    }

    cout << "\n=== PRUEBA EXITOSA ===\n";
    return 0;
}