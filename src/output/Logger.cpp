//
// Created by sauls on 07/06/2026.
//

#include "output/Logger.h"
#include <stdexcept>

using namespace std;

Logger::Logger(const string& outputPath) : turn(1) {
    file.open(outputPath);
    if (!file.is_open())
        throw runtime_error("Logger: the file cannot be created: " + outputPath);

    file << "=== ADVENTURE LOG ===\n\n";
    file.flush();
}

Logger::~Logger() {
    if (file.is_open()) {
        file << "\n=== END OF LOG ===\n";
        file.close();
    }
}

void Logger::log(const string& message) {
    string entry = "[T" + to_string(turn) + "] " + message;

    // Escribe al archivo inmediatamente
    file << entry << "\n";
    file.flush();

    // Guarda en memoria para el panel visual
    recent.push_back(entry);
    if ((int)recent.size() > MAX_RECENT)
        recent.pop_front();
}
