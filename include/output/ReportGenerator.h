//
// Created by sauls on 07/06/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_REPORTGENERATOR_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_REPORTGENERATOR_H

#include "domain/Hero.h"
#include "domain/DungeonLoader.h"
#include "simulation/SimulationEngine.h"
#include <string>



class ReportGenerator {
public:
    // Genera el reporte en outputPath.
    // Throws std::runtime_error si no puede crear el archivo.
    static void generate(const Hero&      hero,
                         const DungeonLoader& dungeon,
                         GameResult       result,
                         int              totalTurns,
                         const std::string&    outputPath);
};

#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_REPORTGENERATOR_H
