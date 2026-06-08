//
// Created by sauls on 07/06/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_LOGGER_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_LOGGER_H

#include <string>
#include <fstream>
#include<iostream>
#include <deque>



class Logger {
private:
    std::ofstream      file;
    int           turn;
    std::deque<std::string> recent;          // ultimas lineas para el panel visual
    static const int MAX_RECENT = 4;

public:
    explicit Logger(const std::string& outputPath);
    ~Logger();

    // Sin copias — maneja un archivo abierto
    Logger(const Logger&)            = delete;
    Logger& operator=(const Logger&) = delete;

    // Registra un evento en el archivo y en memoria
    void log(const std::string& message);

    // Avanza el contador de turno
    void nextTurn() { turn++; }
    int  getTurn()  const { return turn; }

    // Para el panel visual — devuelve las ultimas MAX_RECENT lineas
    const std::deque<std::string>& getRecent() const { return recent; }
};


#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_LOGGER_H
