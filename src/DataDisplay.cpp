#include "SharedData.h"
#include "SharedMemory.h"

#include <iostream>
#include <unistd.h>
#include <iomanip>

int main() {
    SharedAirspace* shm = createSharedMemory(false);

    while (true) {
        sleep(5);

        sem_wait(&shm->mutex);

        std::cout << "\n====== Airspace Snapshot ======\n";
        std::cout << std::left << std::setw(8) << "ID"
                  << std::setw(12) << "Position"
                  << std::setw(12) << "Speed"
                  << std::setw(8) << "Z" << "\n";

        for (int i = 0; i < MAX_AIRCRAFT; ++i) {
            if (!shm->aircraftList[i].active) continue;

            const AircraftData& a = shm->aircraftList[i];
            std::cout << std::left << std::setw(8) << a.id
                      << std::setw(12) << "(" + std::to_string(a.posX) + "," + std::to_string(a.posY) + ")"
                      << std::setw(12) << "(" + std::to_string(a.spdX) + "," + std::to_string(a.spdY) + ")"
                      << std::setw(8)  << a.posZ
                      << "\n";
        }

        std::cout << "===============================\n";

        sem_post(&shm->mutex);
    }

    return 0;
}
