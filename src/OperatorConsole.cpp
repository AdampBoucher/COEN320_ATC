#include "SharedData.h"
#include "SharedMemory.h"

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>

void toUpper(std::string& s) {
    for (size_t i = 0; i < s.size(); ++i) s[i] = toupper(s[i]);
}

int main() {
    SharedAirspace* shm = createSharedMemory(false);

    std::string line;
    while (true) {
        std::cout << "\n[OperatorConsole] Enter command: ";
        std::getline(std::cin, line);

        std::istringstream iss(line);
        std::string cmd, id;
        int v1 = 0, v2 = 0, v3 = 0;

        if (!(iss >> cmd >> id)) {
            std::cout << "Invalid format.\n";
            continue;
        }

        toUpper(cmd);
        bool matched = false;

        sem_wait(&shm->mutex);
        for (int i = 0; i < MAX_AIRCRAFT; ++i) {
            if (shm->aircraftList[i].active && id == shm->aircraftList[i].id) {
                if (cmd == "SET_SPEED") {
                    if (!(iss >> v1 >> v2 >> v3)) break;
                    shm->aircraftList[i].spdX = v1;
                    shm->aircraftList[i].spdY = v2;
                    shm->aircraftList[i].spdZ = v3;
                    std::cout << "Updated speed for " << id << "\n";
                    matched = true;
                } else if (cmd == "SET_ALT") {
                    if (!(iss >> v3)) break;
                    shm->aircraftList[i].posZ = v3;
                    std::cout << "Updated altitude for " << id << "\n";
                    matched = true;
                } else if (cmd == "CHANGE_POS") {
                    if (!(iss >> v1 >> v2 >> v3)) break;
                    shm->aircraftList[i].posX = v1;
                    shm->aircraftList[i].posY = v2;
                    shm->aircraftList[i].posZ = v3;
                    std::cout << "Changed position for " << id << "\n";
                    matched = true;
                }
                break;
            }
        }
        sem_post(&shm->mutex);

        if (!matched)
            std::cout << "Aircraft not found or bad parameters.\n";
    }

    return 0;
}
