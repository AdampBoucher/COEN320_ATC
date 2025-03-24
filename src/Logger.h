#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include "Airspace.h"

class Logger {
public:
    // Logs all aircraft in the airspace every 20 seconds
    static void logAirspace(const Airspace& airspace, int simulationTime);

    // Logs each operator command immediately
    static void logCommand(const std::string& command, int simulationTime);
};

#endif 
