//
// Created by sauls on 07/06/2026.
//

#ifndef PROYECTO_AVENTURAS_Y_MAZMORRAS_LOGGER_H
#define PROYECTO_AVENTURAS_Y_MAZMORRAS_LOGGER_H

#include <string>
#include <fstream>
#include <deque>

using namespace std;

class Logger {
private:
    ofstream      file;
    int           turn;
    deque<string> recent;          // ultimas lineas para el panel visual
    static const int MAX_RECENT = 4;

public:
    explicit Logger(const string& outputPath);
    ~Logger();

    // Sin copias — maneja un archivo abierto
    Logger(const Logger&)            = delete;
    Logger& operator=(const Logger&) = delete;

    // Registra un evento en el archivo y en memoria
    void log(const string& message);

    // Avanza el contador de turno
    void nextTurn() { turn++; }
    int  getTurn()  const { return turn; }

    // Para el panel visual — devuelve las ultimas MAX_RECENT lineas
    const deque<string>& getRecent() const { return recent; }
};


#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_LOGGER_H
