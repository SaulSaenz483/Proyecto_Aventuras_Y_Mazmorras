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
    std::deque<std::string> recent;          // final lines for the visual panel
    static const int MAX_RECENT = 4;

public:
    explicit Logger(const std::string& outputPath);
    ~Logger();

    // No copies — handles an open file
    Logger(const Logger&)            = delete;
    Logger& operator=(const Logger&) = delete;

    // Logs an event to the file and in memory
    void log(const std::string& message);

    // Increment the turn counter
    void nextTurn() { turn++; }
    int  getTurn()  const { return turn; }

  // For the visual panel — returns the last MAX_RECENT lines
    const std::deque<std::string>& getRecent() const { return recent; }
};


#endif //PROYECTO_AVENTURAS_Y_MAZMORRAS_LOGGER_H
