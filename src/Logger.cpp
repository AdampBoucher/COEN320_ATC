#include "Logger.h"
#include <fstream>
#include <iomanip>

void Logger::logAirspace(const Airspace& airspace, int simulationTime) {
    std::ofstream file("airspace_log.csv", std::ios::app);

    if (file.is_open()) {
        
        file.seekp(0, std::ios::end);
        if (file.tellp() == 0) {
            file << "Time,ID,PosX,PosY,PosZ,SpdX,SpdY,SpdZ\n";
        }

        for (const auto* aircraft : airspace.getAllAircraft()) {
            file << simulationTime << ","
                 << aircraft->getId() << ","
                 << aircraft->getX() << "," << aircraft->getY() << "," << aircraft->getZ() << ","
                 << aircraft->getVx() << "," << aircraft->getVy() << "," << aircraft->getVz() << "\n";
        }

        file.close();
    }
}

void Logger::logCommand(const std::string& command, int simulationTime) {
    std::ofstream file("operator_log.txt", std::ios::app);

    if (file.is_open()) {
        file << "[Time = " << simulationTime << "s] " << command << "\n";
        file.close();
    }
}
