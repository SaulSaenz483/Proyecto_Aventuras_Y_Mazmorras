//
// Created by sauls on 07/06/2026.
//

#include "output/ReportGenerator.h"
#include <fstream>
#include <stdexcept>

using namespace std;

void ReportGenerator::generate(const Hero&          hero,
                                const DungeonLoader& dungeon,
                                GameResult           result,
                                int                  totalTurns,
                                const string&        outputPath) {
    ofstream file(outputPath);
    if (!file.is_open())
        throw runtime_error("ReportGenerator: Cannot be created: " + outputPath);

    // ── encabezado ────────────────────────────────────────────────────────
    file << "============================================================\n";
    file << "        ADVENTURES & DUNGEONS — FINAL REPORT\n";
    file << "============================================================\n\n";

    file << "  RESULT : "
         << (result == GameResult::VICTORY ? "VICTORY" : "DEFEAT") << "\n";
    file << "  TURNS    : " << totalTurns << "\n\n";

    // ── estado del heroe ──────────────────────────────────────────────────
    file << "------------------------------------------------------------\n";
    file << "  HEROE\n";
    file << "------------------------------------------------------------\n";
    file << "  Name     : " << hero.getName()       << "\n";
    file << "  HP final   : " << hero.getHp()
         << " / "             << hero.getMaxHp()      << "\n";
    file << "  ATK base   : " << hero.getBaseAttack() << "\n";

    const auto& inv = hero.getInventory();
    file << "  Inventory : " << inv.size() << " item(s)\n";
    for (size_t i = 0; i < inv.size(); i++)
        file << "    [" << (i + 1) << "] " << inv[i]->getName() << "\n";

    // ── estado del mundo ──────────────────────────────────────────────────
    file << "\n------------------------------------------------------------\n";
    file << "  DUNGEON\n";
    file << "------------------------------------------------------------\n";
    file << "  Size     : " << dungeon.getWidth()
         << " x "             << dungeon.getHeight() << "\n";

    // Contar celdas exploradas
    int explored = 0;
    int total    = 0;
    for (int y = 0; y < dungeon.getHeight(); y++) {
        for (int x = 0; x < dungeon.getWidth(); x++) {
            const Room& r = dungeon.getRoom(x, y);
            if (r.getType() != CellType::WALL) {
                total++;
                if (r.isVisited()) explored++;
            }
        }
    }
    file << "  Exploring  : " << explored << " / " << total << " cells\n";

    // Estado del Boss
    Enemy* boss = dungeon.getBoss();
    if (boss != nullptr) {
        file << "  Boss       : " << boss->getName()
             << " — " << (boss->isAlive() ? "ALIVE" : "DEFEAT") << "\n";
    }

    // ── pie ───────────────────────────────────────────────────────────────
    file << "\n============================================================\n";
    file << "  See adventure log.txt for the full log.\n";
    file << "============================================================\n";

    file.close();
}
