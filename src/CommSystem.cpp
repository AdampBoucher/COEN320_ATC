#include "CommSystem.h"
#include <iostream>
#include <cstring>

// Constructor
CommSystem::CommSystem() {
    // Initialize message queue or other internal structures
}

// Destructor
CommSystem::~CommSystem() {
    // Cleanup if needed (e.g., closing shared memory or message queues)
}

// Initialize communication system (e.g., shared memory setup)
bool CommSystem::initialize() {
    // Setup shared memory, message queue, etc.
    std::cout << "Communication System Initialized!" << std::endl;
    return true;
}

// Send message
bool CommSystem::sendMessage(const CommMessage& message) {
    // Send the message to the desired recipient (e.g., using shared memory, message queue)
    std::cout << "Sending message: " << message.command << " to aircraft " << message.aircraftId << std::endl;
    // Example: Add message to internal queue
    messageQueue.push_back(message);
    return true;
}

// Receive message
bool CommSystem::receiveMessage(CommMessage& message) {
    if (!messageQueue.empty()) {
        message = messageQueue.front(); // Retrieve the first message from the queue
        messageQueue.erase(messageQueue.begin()); // Remove the message after processing
        std::cout << "Received message: " << message.command << " from aircraft " << message.aircraftId << std::endl;
        return true;
    }
    return false; // Return false if no messages are available
}

// Process received message
void CommSystem::processMessage(const CommMessage& message) {
    // Process the message based on command (e.g., setting aircraft speed, changing altitude)
    if (message.command == "SET_SPEED") {
        // Implement logic to set speed for the aircraft
        std::cout << "Setting speed for aircraft " << message.aircraftId << " to " << message.data << std::endl;
    } else if (message.command == "SET_ALT") {
        // Implement logic to set altitude
        std::cout << "Setting altitude for aircraft " << message.aircraftId << " to " << message.data << std::endl;
    }
    // Add more commands as necessary...
}
