#include <stdio.h>
#include <stdlib.h>

#include "Aircraft.h"

int main(void) {
	puts("Hello World!!!"); /* prints Hello World!!! */

	int id = 0;
	int arrivalTime = 2;
	position_t position; position.x = 0; position.y = 0; position.z = 0;
	speed_t speed; speed.x = 1; speed.y = 1; speed.z = 1;

	Aircraft aircraft[10];
	for(int i = 0; i < 10; i++) {
		aircraft[i].id = i;
		aircraft[i].arrivalTime = arrivalTime;
		aircraft[i].arrivalPosition = position;
		aircraft[i].arrivalSpeed = speed;
	}
	for(int i = 0; i < 10; i++)
		aircraft[i].start();
	for(int i = 0; i < 10; i++)
		aircraft[i].join();
	printf("ended");

	return EXIT_SUCCESS;
}
