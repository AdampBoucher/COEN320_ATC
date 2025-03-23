
#ifndef SRC_AIRCRAFT_H_
#define SRC_AIRCRAFT_H_

#define AIRCRAFT_CALLBACK_RATE 1

#include <time.h>
#include <pthread.h>
#include <sys/siginfo.h>
#include <unistd.h>


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

	int id;
		int arrivalTime;
		position_t arrivalPosition;
		speed_t arrivalSpeed;

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
