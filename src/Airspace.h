#pragma once

#include <vector>
#include "Aircraft.h"

class Airspace {
private:
    std::vector<Aircraft*> aircraftList;
    const int volume[3] = {100000, 100000, 25000};
    const int minimumHeight = 15000;

public:
    // Add aircraft by raw pointer
    void addAircraft(Aircraft* aircraft) {
        aircraftList.push_back(aircraft);
    }

    // Return aircraft list for logging
    const std::vector<Aircraft*>& getAllAircraft() const {
        return aircraftList;
    }

    // Display aircraft states
    void printAirspace() const {
        for (const auto* aircraft : aircraftList) {
            aircraft->printStatus();
        }
    }
};
