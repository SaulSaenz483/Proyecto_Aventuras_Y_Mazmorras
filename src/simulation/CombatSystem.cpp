//
// Created by sauls on 07/06/2026.
//

#include "simulation/CombatSystem.h"
#include "domain/Potion.h"
#include <iostream>
#include <limits>
#include <cstdlib>

using namespace std;

// ── helpers ────────────────────────────────────────────────────────────────

string CombatSystem::hpBar(int current, int max, int width) {
    if (max <= 0) return string(width, ' ');
    int filled = current * width / max;
    if (filled < 0)     filled = 0;
    if (filled > width) filled = width;
    return string(filled, '|') + string(width - filled, ' ');
}

string CombatSystem::padRight(const string& s, int width) {
    if ((int)s.size() >= width) return s.substr(0, width);
    return s + string(width - (int)s.size(), ' ');
}

// ── constructor ────────────────────────────────────────────────────────────

CombatSystem::CombatSystem(Hero& h, Enemy& e, Logger& l)
    : hero(h), enemy(e), logger(l) {}

// ── drawCombatScreen ───────────────────────────────────────────────────────

void CombatSystem::drawCombatScreen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    const int TW = 44; // ancho interior

    // Lineas de borde
    string top    = "+" + string(TW, '=') + "+";
    string mid    = "+" + string(TW, '-') + "+";
    string bottom = "+" + string(TW, '=') + "+";

    auto fullRow = [&](const string& text) {
        cout << "| " << padRight(text, TW - 1) << "|\n";
    };
    auto splitRow = [&](const string& left, const string& right) {
        int half = TW / 2;
        cout << "| " << padRight(left,  half - 2)
             << "| " << padRight(right, TW - half - 2) << "|\n";
    };

    // Header
    cout << top << "\n";
    string title = "*** COMBAT ***";
    int pad = (TW - (int)title.size()) / 2;
    cout << "|" << string(pad, ' ') << title
         << string(TW - pad - (int)title.size(), ' ') << "|\n";

    // Nombres
    cout << mid << "\n";
    splitRow(hero.getName(),
             enemy.getName() + " [" + enemy.getEnemyType() + "]");

    // Barras de HP
    string heroBar  = "HP [" + hpBar(hero.getHp(),  hero.getMaxHp()) + "] " +
                      to_string(hero.getHp()) + "/" + to_string(hero.getMaxHp());
    string enemyBar = "HP [" + hpBar(enemy.getHp(), enemy.getMaxHp()) + "] " +
                          to_string(enemy.getHp()) + "/" + to_string(enemy.getMaxHp());
    splitRow(heroBar, enemyBar);

    // Stats
    splitRow("ATK: " + to_string(hero.getBaseAttack()),
             "DMG: " + to_string(enemy.getDamage()));

    // Log panel
    cout << mid << "\n";
    fullRow("--- log ---");
    const auto& recent = logger.getRecent();
    int printed = 0;
    for (auto it = recent.begin(); it != recent.end() && printed < 3; ++it, ++printed)
        fullRow(*it);
    for (int i = printed; i < 3; i++) fullRow("");

    // Opciones
    cout << mid << "\n";
    fullRow("[1] Attack   [2] Use item   [3] Run");
    cout << bottom << "\n";
}

// ── enemyTurn ──────────────────────────────────────────────────────────────

bool CombatSystem::enemyTurn() {
    int dmg = enemy.getDamage();
    hero.takeDamage(dmg);
    logger.log(enemy.getName() + " attack by " + to_string(dmg) + " dmg. " +
               "HP heroe: " + to_string(hero.getHp()));
    return !hero.isAlive();
}

// ── attack ─────────────────────────────────────────────────────────────────

CombatResult CombatSystem::attack() {
    int dmg = hero.getBaseAttack();
    enemy.takeDamage(dmg);
    logger.log(hero.getName() + " attack to " + enemy.getName() +
               " por " + to_string(dmg) + " dmg. enemy HP: " + to_string(enemy.getHp()));

    if (!enemy.isAlive()) {
        logger.log(enemy.getName() + " has been defeated!");
        return CombatResult::HERO_WON;
    }

    if (enemyTurn()) return CombatResult::HERO_DIED;
    return CombatResult::CONTINUE;
}

// ── useItem ────────────────────────────────────────────────────────────────

CombatResult CombatSystem::useItem() {
    const auto& inv = hero.getInventory();

    // Buscar la primera pocion disponible
    for (Item* item : inv) {
        Potion* p = dynamic_cast<Potion*>(item);
        if (p) {
            p->use(hero);
            hero.removeItem(p); //Incluimos esta linea porque sino Hero y DungeonLoader intentan hacer delete sobre el mismo puntero
            delete p;
            logger.log("Use " + p->getName() + ". heroe HP: " + to_string(hero.getHp()));

            // El enemigo igual contraataca este turno
            if (enemyTurn()) return CombatResult::HERO_DIED;
            return CombatResult::CONTINUE; // combate sigue
        }
    }

    // No habia pocion
    cout << "  You have no potions available.\n";
    logger.log("Tried to use an item but no potions were available.");

    if (enemyTurn()) return CombatResult::HERO_DIED;
    return CombatResult::CONTINUE; // combate sigue
}

// ── flee ───────────────────────────────────────────────────────────────────

CombatResult CombatSystem::flee() {
    // Huir tiene costo: el enemigo da un golpe de salida
    logger.log(hero.getName() + " tries to run away...");
    if (enemyTurn()) return CombatResult::HERO_DIED;

    logger.log(hero.getName() + " fled the battle.");
    return CombatResult::HERO_FLED;
}

// ── start ──────────────────────────────────────────────────────────────────

CombatResult CombatSystem::start() {
    logger.log("Combat has begun: " + hero.getName() +
               " vs " + enemy.getName() + " [" + enemy.getEnemyType() + "]");

    // Vaciar buffer interno de cin
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (hero.isAlive() && enemy.isAlive()) {
        drawCombatScreen();

        string line;
        cout << "\n> ";
        cout.flush();
        if (!getline(cin, line)) break;

        int choice = 0;
        try {
            if (!line.empty()) choice = stoi(line);
        } catch (...) {
            choice = 0;
        }

        CombatResult result;

        switch (choice) {
            case 1: result = attack();  break;
            case 2: result = useItem(); break;
            case 3: result = flee();    break;
            default:
                logger.log("Invalid option in combat.");
                continue;
        }

        logger.nextTurn();

        // Si el enemigo murio o huimos o morimos, salimos del bucle
        if (!enemy.isAlive())                  return CombatResult::HERO_WON;
        if (!hero.isAlive())                   return CombatResult::HERO_DIED;
        if (result == CombatResult::HERO_FLED) return CombatResult::HERO_FLED;
    }

    return hero.isAlive() ? CombatResult::HERO_WON : CombatResult::HERO_DIED;
}
