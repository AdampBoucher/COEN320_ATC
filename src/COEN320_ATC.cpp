#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // for sleep()
#include <time.h>
#include <iostream>     
#include <string>

#include "Aircraft.h"
#include "Airspace.h"
#include "Logger.h"
#include "OperatorCommand.h"

int main(void) {
	puts("Hello World!!!");

	int arrivalTime = 2;
	position_t position = {0, 0, 0};
	speed_t speed = {1, 1, 1};

	Aircraft aircraft[10];
	Airspace airspace;

	for (int i = 0; i < 10; i++) {
		aircraft[i].id = i;
		aircraft[i].arrivalTime = arrivalTime;
		aircraft[i].arrivalPosition = position;
		aircraft[i].arrivalSpeed = speed;

		airspace.addAircraft(&aircraft[i]);  // store pointer for logger 
	}

	for (int i = 0; i < 10; i++)
		aircraft[i].start();

	int simulationTime = 0;

	while (simulationTime <= 60) {
		simulationTime++;

		// Log aircraft state every 20 seconds
		if (simulationTime % 20 == 0) {
			Logger::logAirspace(airspace, simulationTime);
		}

		// Prompt for operator input every 5 seconds
		if (simulationTime % 5 == 0) {
			std::string input;
			std::cout << "\n[SIM TIME " << simulationTime << "s] Enter operator command: ";
			std::getline(std::cin, input);

			auto parsed = OperatorCommandParser::parse(input);
			if (parsed) {
				Logger::logCommand(input, simulationTime);
				std::cout << "Command logged for aircraft: " << parsed->aircraftId << "\n";
			} else {
				std::cout << "Invalid command format.\n";
			}
		}

		sleep(1);
	}

	for (int i = 0; i < 10; i++)
		aircraft[i].join();

	printf("ended\n");
	return EXIT_SUCCESS;
}
