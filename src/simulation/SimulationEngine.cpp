//
// Created by sauls on 07/06/2026.
//

#include "simulation/SimulationEngine.h"
#include "simulation/CombatSystem.h"
#include "domain/NPC.h"
#include "domain/Weapon.h"
#include <iostream>
#include <limits>
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::vector;
using std::size_t;
using std::numeric_limits;
using std::streamsize;
using std::cin;

// ---------------------- helpers ----------------------

void SimulationEngine::clearScreen() {
    // Terminal clearing not used — compatible with all environments
}

string SimulationEngine::hpBar(int current, int max, int width) {
    if (max <= 0) return string(width, ' ');
    int filled = current * width / max;
    if (filled < 0)     filled = 0;
    if (filled > width) filled = width;
    return string(filled, '|') + string(width - filled, ' ');
}

string SimulationEngine::padRight(const string& s, int width) {
    if ((int)s.size() >= width) return s.substr(0, width);
    return s + string(width - (int)s.size(), ' ');
}

// ---------------------- constructor ----------------------

SimulationEngine::SimulationEngine(Hero& h, DungeonLoader& d, Logger& l)
    : hero(h), dungeon(d), logger(l),
      heroX(d.getStartX()), heroY(d.getStartY()),
      lastDx(0), lastDy(0),
      running(true) {}

// ---------------------- drawMap ----------------------

void SimulationEngine::drawMap() const {
    clearScreen();
    cout.flush();

    const int MW = dungeon.getWidth();
    const int SP = 26;              // wide enough for "HP [||||||||||] 100/100"
    const int TW = MW + SP + 1;    // total inner width

    // borders
    auto hline = [](char c, int n) { return string(n, c); };

    string borderTop = "+" + hline('=', MW) + "+" + hline('=', SP) + "+";
    string borderMid = "+" + hline('-', MW) + "+" + hline('-', SP) + "+";
    string borderLog = "+" + hline('-', TW) + "+";
    string borderBot = "+" + hline('=', TW) + "+";

    // header: room description | hero name
    const Room& heroRoom = dungeon.getRoom(heroX, heroY);
    string roomName = heroRoom.getDescription().empty()
                      ? "Dungeon" : heroRoom.getDescription();

    cout << borderTop << "\n";
    cout << "| " << padRight(roomName,      MW - 2)
         << " | " << padRight(hero.getName(), SP - 2) << " |\n";

    // HP row
    string hpLine = "HP [" + hpBar(hero.getHp(), hero.getMaxHp()) + "] " +
                    to_string(hero.getHp()) + "/" + to_string(hero.getMaxHp());

    cout << borderMid << "\n";
    cout << "| " << padRight("", MW - 2)
         << " | " << padRight(hpLine, SP - 2) << " |\n";

    // map rows + side panel
    const auto& inv = hero.getInventory();

    for (int row = 0; row < dungeon.getHeight(); row++) {
        cout << "|";
        for (int col = 0; col < MW; col++) {
            if (col == heroX && row == heroY) cout << '@';
            else cout << dungeon.getRoom(col, row).getSymbol();
        }
        cout << "|";

        string side;
        if (row == 0) {
            string atkStr = "ATK " + to_string(hero.getBaseAttack());
            if (hero.getWeaponBonus() > 0)
                atkStr += " (+" + to_string(hero.getWeaponBonus()) + " weapon)";
            side = atkStr;
        } else if (row == 1) {
            side = "--- Inventory ---";
        } else if (row == 2) {
            int idx = 0;
            if (idx < (int)inv.size()) side = "> " + inv[idx]->getName();
        } else if (row == 3) {
            int idx = 1;
            if (idx < (int)inv.size()) side = "> " + inv[idx]->getName();
        } else if (row == 4) {
            side = "--- Legend ---";
        } else if (row == 5) {
            side = "@ Hero  E Enemy";
        } else if (row == 6) {
            side = "B Boss  N NPC";
        } else if (row == 7) {
            side = "$ Item  # Wall";
        }
        cout << " " << padRight(side, SP - 1) << "|\n";
    }

    // log panel (4 lines)
    cout << borderLog << "\n";
    const auto& recent = logger.getRecent();
    int printed = 0;
    for (auto it = recent.begin(); it != recent.end() && printed < 4; ++it, ++printed)
        cout << "| " << padRight(*it, TW - 1) << "|\n";
    for (int i = printed; i < 4; i++)
        cout << "| " << string(TW - 1, ' ') << "|\n";

    // controls
    cout << borderLog << "\n";
    cout << "| " << padRight("WASD move   I inventory   Q quit", TW - 1) << "|\n";
    cout << borderBot << "\n";
}

// ---------------------- drawVictory / drawDefeat ----------------------

void SimulationEngine::drawVictory() const {
    clearScreen();
    cout << "\n  ==========================================\n";
    cout << "            *** VICTORY ***\n";
    cout << "  ==========================================\n";
    cout << "  " << hero.getName() << " has conquered the dungeon!\n";
    cout << "  HP remaining: " << hero.getHp() << "/" << hero.getMaxHp() << "\n";
    cout << "  ==========================================\n\n";
}

void SimulationEngine::drawDefeat() const {
    clearScreen();
    cout << "\n  ==========================================\n";
    cout << "             *** DEFEAT ***\n";
    cout << "  ==========================================\n";
    cout << "  " << hero.getName() << " has fallen in the dungeon.\n";
    cout << "  ==========================================\n\n";
}

// ---------------------- handleEnemies ----------------------

void SimulationEngine::handleEnemies(Room& room) {
    vector<Enemy*> enemies = room.getEnemies();
    for (Enemy* e : enemies) {
        if (!e->isAlive()) continue;

        CombatSystem combat(hero, *e, logger);
        CombatResult result = combat.start();

        if (result == CombatResult::HERO_DIED) {
            running = false;
            return;
        }
        if (result == CombatResult::HERO_FLED) {
            heroX -= lastDx;
            heroY -= lastDy;
            logger.log(hero.getName() + " fled and stepped back.");
            return;
        }
    }

    room.removeDeadEnemies();
    if (!room.hasLiveEnemies()) {
        cout << "\n  Enemy defeated! Press ENTER to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (!room.hasItems() && !room.hasNPCs())
            room.setType(CellType::FLOOR);
    }
}

// ---------------------- handleNPCs ----------------------

void SimulationEngine::handleNPCs(Room& room) {
    for (NPC* n : room.getNPCs()) {
        cout << "\n  +---------------------------------+\n";
        n->interact();
        cout << "  +---------------------------------+\n";
        n->applyEffect(hero);
        cout << "\n  Press ENTER to continue...";
        cin.get();
        logger.log("NPC encountered: " + n->getName() +
                   " | Action: " + n->getActionType());
    }
}

// ---------------------- handleItems ----------------------

void SimulationEngine::handleItems(Room& room) {
    vector<Item*> items = room.getItems();
    for (Item* item : items) {
        hero.addItem(item);
        room.removeItem(item);

        // Weapons are automatically equipped when picked up
        if (dynamic_cast<Weapon*>(item)) {
            item->use(hero);
            logger.log("Weapon equipped: " + item->getName() +
                       " (ATK now " + to_string(hero.getBaseAttack()) + ")");
        } else {
            logger.log("Item picked up: " + item->getName());
        }
    }
    if (!room.hasItems() && !room.hasLiveEnemies() && !room.hasNPCs())
        room.setType(CellType::FLOOR);
}

// ---------------------- moveHero ----------------------

bool SimulationEngine::moveHero(int dx, int dy) {
    int nx = heroX + dx;
    int ny = heroY + dy;

    if (!dungeon.isValid(nx, ny)) {
        logger.log("Movement out of bounds.");
        return false;
    }

    Room& target = dungeon.getRoom(nx, ny);
    if (!target.isWalkable()) {
        logger.log("Blocked by a wall.");
        return false;
    }

    Room& prev = dungeon.getRoom(heroX, heroY);
    if (!prev.hasLiveEnemies() && !prev.hasItems() && !prev.hasNPCs())
        prev.setType(CellType::FLOOR);

    lastDx = dx;
    lastDy = dy;
    heroX  = nx;
    heroY  = ny;
    target.markVisited();
    logger.log("Moved to (" + to_string(heroX) + "," + to_string(heroY) + ")");

    if (target.hasNPCs())        handleNPCs(target);
    if (target.hasItems())       handleItems(target);
    if (target.hasLiveEnemies()) handleEnemies(target);

    return true;
}

// ---------------------- readInput — reads exactly one char, ignores the rest of the line ----------------------

static char readInput() {
    string line;
    if (!getline(cin, line)) return 'q';
    if (line.empty()) return '\0';
    return (char)tolower(line[0]);
}

// ---------------------- run ----------------------

GameResult SimulationEngine::run() {
    dungeon.getRoom(heroX, heroY).markVisited();
    logger.log("Adventure started. Hero: " + hero.getName());

    while (running) {
        // Check conditions before drawing
        if (dungeon.getBoss() != nullptr && !dungeon.getBoss()->isAlive()) {
            drawVictory();
            logger.log("*** VICTORY: Boss defeated ***");
            return GameResult::VICTORY;
        }
        if (!hero.isAlive()) {
            drawDefeat();
            logger.log("*** DEFEAT: Hero died ***");
            return GameResult::DEFEAT;
        }

        drawMap();
        cout << "> ";
        cout.flush();

        char input = readInput();

    switch (input) {
            case 'w': moveHero( 0, -1); break;
            case 's': moveHero( 0,  1); break;
            case 'a': moveHero(-1,  0); break;
            case 'd': moveHero( 1,  0); break;
            case 'i':
                clearScreen();
                hero.showInventory();
                cout << "  Press ENTER to continue...";
                cin.get();
                break;
            case 'q':
                logger.log("Player quit.");
                running = false;
                break;
            default:
                logger.log("Unknown command: " + string(1, input));
                break;
        }

        logger.nextTurn();
    }

    return hero.isAlive() ? GameResult::VICTORY : GameResult::DEFEAT;
}