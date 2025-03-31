#include "SharedData.h"
#include "SharedMemory.h"

#include <unistd.h>
#include <cmath>
#include <iostream>

bool isViolation(const AircraftData& a, const AircraftData& b, int lookahead) {
    int aX = a.posX + a.spdX * lookahead;
    int aY = a.posY + a.spdY * lookahead;
    int aZ = a.posZ + a.spdZ * lookahead;

    int bX = b.posX + b.spdX * lookahead;
    int bY = b.posY + b.spdY * lookahead;
    int bZ = b.posZ + b.spdZ * lookahead;

    int dz = std::abs(aZ - bZ);
    int dx = aX - bX;
    int dy = aY - bY;
    double dXY = std::sqrt(dx * dx + dy * dy);

    return (dz < 1000 && dXY < 3000);
}

int main() {
    SharedAirspace* shm = createSharedMemory(false);

    while (true) {
        sleep(5);

        sem_wait(&shm->mutex);
        int n = shm->n_seconds;
        for (int i = 0; i < MAX_AIRCRAFT; ++i) {
            if (!shm->aircraftList[i].active) continue;

            for (int j = i + 1; j < MAX_AIRCRAFT; ++j) {
                if (!shm->aircraftList[j].active) continue;

                bool current = isViolation(shm->aircraftList[i], shm->aircraftList[j], 0);
                bool future = isViolation(shm->aircraftList[i], shm->aircraftList[j], n);

                if (current) {
                    std::cout << "[ALERT] Immediate violation between "
                              << shm->aircraftList[i].id << " and " << shm->aircraftList[j].id << "\n";
                } else if (future) {
                    std::cout << "[WARNING] Violation expected in " << n
                              << "s between " << shm->aircraftList[i].id
                              << " and " << shm->aircraftList[j].id << "\n";
                }
            }
        }
        sem_post(&shm->mutex);
    }

    return 0;
}
