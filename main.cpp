#include <iostream>
#include <stdexcept>
 
#include "domain/DungeonLoader.h"
#include "domain/Hero.h"
#include "output/Logger.h"
#include "output/ReportGenerator.h"
#include "simulation/SimulationEngine.h"
 
using namespace std;
 
int main() {
    // ── Title screen ──────────────────────────────────────────────────────
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    cout << "\n";
    cout << "  ==========================================\n";
    cout << "       ADVENTURES & DUNGEONS  v1.0\n";
    cout << "  ==========================================\n";
    cout << "    Explore the dungeon. Defeat the Boss.\n\n";
    cout << "  Press ENTER to begin...\n";
    cout << "  ==========================================\n\n";
    cin.get();
 
    // ── Load dungeon ──────────────────────────────────────────────────────
    DungeonLoader dungeon;
    try {
        dungeon.loadMap    ("data/map.txt");
        dungeon.loadEnemies("data/enemies.txt");
        dungeon.loadItems  ("data/items.txt");
    } catch (const exception& e) {
        cerr << "[ERROR] Failed to load dungeon: " << e.what() << "\n";
        return 1;
    }


    // ── Create hero ───────────────────────────────────────────────────────
    Hero hero("Aldric", 100, 18);
 
    // ── Start logger ──────────────────────────────────────────────────────
    Logger* logger = nullptr;
    try {
        logger = new Logger("data/adventure_log.txt");
    } catch (const exception& e) {
        cerr << "[ERROR] Failed to create log file: " << e.what() << "\n";
        return 1;
    }
 
    // ── Run simulation ────────────────────────────────────────────────────
    GameResult result = GameResult::DEFEAT;
    try {
        SimulationEngine engine(hero, dungeon, *logger);
        result = engine.run();
    } catch (const exception& e) {
        cerr << "[ERROR] Simulation crashed: " << e.what() << "\n";
        delete logger;
        return 1;
    }
 
    // ── Generate final report ─────────────────────────────────────────────
    try {
        ReportGenerator::generate(hero, dungeon, result,
                                  logger->getTurn(),
                                  "data/final_report.txt");
        cout << "\n  Report saved to data/final_report.txt\n";
        cout << "  Adventure log saved to data/adventure_log.txt\n\n";
    } catch (const exception& e) {
        cerr << "[ERROR] Could not generate report: " << e.what() << "\n";
    }
 
    delete logger;
    return 0;
}


