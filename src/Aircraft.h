#ifndef SRC_AIRCRAFT_H_
#define SRC_AIRCRAFT_H_

#define AIRCRAFT_CALLBACK_RATE 1

#include <time.h>
#include <pthread.h>
#include <sys/siginfo.h>
#include <unistd.h>
#include <stdio.h>

typedef struct {
	int x; int y; int z;
} position_t;

typedef struct {
	int x; int y; int z;
} speed_t;

class Aircraft {
public:
	Aircraft();
	Aircraft(int id, int arrivalTime, position_t arrivalPosition, speed_t arrivalSpeed);

	void start();
	void join();

	// Public data members (used during init)
	int id;
	int arrivalTime;
	position_t arrivalPosition;
	speed_t arrivalSpeed;

	// === Getters needed for logger ===
	int getId() const { return id; }

	int getX() const { return arrivalPosition.x; }
	int getY() const { return arrivalPosition.y; }
	int getZ() const { return arrivalPosition.z; }

	int getVx() const { return arrivalSpeed.x; }
	int getVy() const { return arrivalSpeed.y; }
	int getVz() const { return arrivalSpeed.z; }

	// === Optional: For console debugging ===
	void printStatus() const {
		printf("Aircraft %d → Pos(%d, %d, %d) Vel(%d, %d, %d)\n",
			id,
			arrivalPosition.x, arrivalPosition.y, arrivalPosition.z,
			arrivalSpeed.x, arrivalSpeed.y, arrivalSpeed.z);
	}

private:
	position_t currentPosition;
	speed_t currentSpeed;
	bool planeArrived;
	bool planeLeft;

	pthread_t thread;

	static void* startThread(void*);
	static void timerCallback(union sigval);

	void update(void);
};

#endif /* SRC_AIRCRAFT_H_ */
