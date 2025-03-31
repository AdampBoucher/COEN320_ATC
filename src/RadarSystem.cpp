#include "SharedData.h"
#include <unistd.h>
#include <iostream>
#include <ctime>

extern SharedAirspace* createSharedMemory(bool isCreator);

int main() {
    SharedAirspace* shm = createSharedMemory(false);

    while (true) {
        sem_wait(&shm->mutex);
        std::cout << "---- RADAR REPORT (" << time(NULL) << ") ----" << std::endl;
        for (int i = 0; i < MAX_AIRCRAFT; ++i) {
            if (shm->aircraftList[i].active) {
                AircraftData& a = shm->aircraftList[i];
                std::cout << a.id << ": POS(" << a.posX << "," << a.posY << "," << a.posZ
                          << ") SPD(" << a.spdX << "," << a.spdY << "," << a.spdZ << ")" << std::endl;
            }
        }
        sem_post(&shm->mutex);
        sleep(5);
    }

    return 0;
}
