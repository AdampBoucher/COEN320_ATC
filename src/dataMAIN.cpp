#include "DataDisplay.h"
#include <iostream>

DataDisplay::DataDisplay() {}

DataDisplay::~DataDisplay() {}

bool DataDisplay::initialize() {
    std::cout << "Data Display system initialized." << std::endl;
    return true; // Initialization successful
}

void DataDisplay::addAircraftData(const AircraftData& aircraftData) {
    aircraftList.push_back(aircraftData);
}

void DataDisplay::displayAllAircraft() const {
    std::cout << "---- Aircraft Data ----" << std::endl;
    for (const auto& aircraft : aircraftList) {
        if (aircraft.active) {
            std::cout << "Aircraft ID: " << aircraft.id << " Position: "
                      << aircraft.posX << ", " << aircraft.posY << ", " << aircraft.posZ
                      << " Speed: " << aircraft.spdX << ", " << aircraft.spdY << ", " << aircraft.spdZ
                      << std::endl;
        }
    }
}

void DataDisplay::updateDisplay() {
    std::cout << "Updating aircraft display data..." << std::endl;
    // You can modify this method to handle updates based on time or external events
    displayAllAircraft();
}
