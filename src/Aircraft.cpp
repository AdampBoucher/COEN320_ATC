#include "Aircraft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Aircraft::Aircraft() {}

Aircraft::Aircraft(int id, int arrivalTime, position_t arrivalPosition, speed_t arrivalSpeed) :
	id(id),
	arrivalTime(arrivalTime),
	arrivalPosition(arrivalPosition),
	arrivalSpeed(arrivalSpeed),
	thread(0),
	planeArrived(false),
	planeLeft(false) {

}

void Aircraft::start() {
	int threadId = pthread_create(&thread, NULL, startThread, this);
	if(threadId < 0) {
		//handle error
		printf(":(\n");
	}
}

void Aircraft::update() {
	if(!planeArrived)
		planeArrived = true;
	arrivalPosition.x++;
	printf("%d ID: %d thread: %lu \n",arrivalPosition.x, id, (unsigned long)pthread_self());
	if(arrivalPosition.x>4) {
		planeLeft = true;
	}
}

void* Aircraft::startThread(void* arg) {
	Aircraft* aircraft = reinterpret_cast<Aircraft*>(arg);

	timer_t timer;
	struct sigevent sev;
	struct itimerspec its;

	sev.sigev_notify = SIGEV_THREAD;
	sev.sigev_notify_function = Aircraft::timerCallback;
	sev.sigev_value.sival_ptr = arg;

	if (timer_create(CLOCK_REALTIME, &sev, &timer) == -1) {
		printf("timer create failed\n");
	    //handle error
	}

	its.it_value.tv_sec = aircraft->arrivalTime;  // Initial expiration after 2 seconds
	its.it_value.tv_nsec = 0;
	its.it_interval.tv_sec = AIRCRAFT_CALLBACK_RATE; // Repeat every 1 second
	its.it_interval.tv_nsec = 0;

	if(timer_settime(timer, 0, &its, NULL) == -1) {
		printf("set time failed\n");
		//handle error
	}

	while(!aircraft->planeLeft) {
		sleep(1);
	}

	return NULL;
}

void Aircraft::timerCallback(union sigval arg) {
	Aircraft* aircraft = reinterpret_cast<Aircraft*>(arg.sival_ptr);
	aircraft->update();
}

void Aircraft::join() {
	if(pthread_join(thread, NULL) != 0) {
		//handle error
		printf("join bad\n");
	}
}

