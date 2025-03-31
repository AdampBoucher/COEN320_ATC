#include "SharedData.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

SharedAirspace* createSharedMemory(bool isCreator) {
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open failed");
        exit(1);
    }

    ftruncate(shm_fd, sizeof(SharedAirspace));

    void* ptr = mmap(0, sizeof(SharedAirspace), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    SharedAirspace* shared = (SharedAirspace*)ptr;

    if (isCreator) {
        memset(shared, 0, sizeof(SharedAirspace));
        sem_init(&shared->mutex, 1, 1);
        shared->n_seconds = 10;
    }

    return shared;
}
