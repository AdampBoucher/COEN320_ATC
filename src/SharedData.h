#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include <semaphore.h>

#define MAX_AIRCRAFT 20
#define SHM_NAME "/airspace_shm"

typedef struct {
    char id[8];
    int posX, posY, posZ;
    int spdX, spdY, spdZ;
    bool active;
} AircraftData;

typedef struct {
    AircraftData aircraftList[MAX_AIRCRAFT];
    int n_seconds; // lookahead time for prediction
    sem_t mutex;   // semaphore for data access
} SharedAirspace;

#endif
