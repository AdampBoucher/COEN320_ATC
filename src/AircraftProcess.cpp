#include "SharedData.h"
#include "SharedMemory.h"

#include <iostream>
#include <unistd.h>
#include <cstring>

int main(int argc, char* argv[]) {
    if (argc != 8) {
        std::cerr << "Usage: ./AircraftProcess <ID> <X> <Y> <Z> <SpdX> <SpdY> <SpdZ>\n";
        return 1;
    }

    SharedAirspace* shm = createSharedMemory(false);

    const char* id = argv[1];
    int posX = atoi(argv[2]);
    int posY = atoi(argv[3]);
    int posZ = atoi(argv[4]);
    int spdX = atoi(argv[5]);
    int spdY = atoi(argv[6]);
    int spdZ = atoi(argv[7]);

    int index = -1;

    sem_wait(&shm->mutex);
    for (int i = 0; i < MAX_AIRCRAFT; ++i) {
        if (!shm->aircraftList[i].active) {
            index = i;
            shm->aircraftList[i].active = true;
            strncpy(shm->aircraftList[i].id, id, sizeof(shm->aircraftList[i].id));
            shm->aircraftList[i].posX = posX;
            shm->aircraftList[i].posY = posY;
            shm->aircraftList[i].posZ = posZ;
            shm->aircraftList[i].spdX = spdX;
            shm->aircraftList[i].spdY = spdY;
            shm->aircraftList[i].spdZ = spdZ;
            break;
        }
    }
    sem_post(&shm->mutex);

    if (index == -1) {
        std::cerr << "No available slot for aircraft.\n";
        return 1;
    }

    while (true) {
        sleep(1);
        sem_wait(&shm->mutex);
        shm->aircraftList[index].posX += shm->aircraftList[index].spdX;
        shm->aircraftList[index].posY += shm->aircraftList[index].spdY;
        shm->aircraftList[index].posZ += shm->aircraftList[index].spdZ;
        sem_post(&shm->mutex);
    }

    return 0;
}
