#include "CommSystem.h"
#include <iostream>
#include <string>

int main() {
    // Initialize the communication system
    CommSystem commSystem;
    if (!commSystem.initialize()) {
        std::cerr << "Error: Failed to initialize communication system." << std::endl;
        return -1;
    }

    // Create example messages to send
    CommMessage msg1 = {"SET_SPEED", "250", 1, 1000};  // Set speed for aircraft 1
    CommMessage msg2 = {"SET_ALT", "15000", 2, 1000};  // Set altitude for aircraft 2
    CommMessage msg3 = {"CHANGE_POS", "3000,4000,5000", 3, 1000}; // Change position for aircraft 3

    // Send messages using the communication system
    commSystem.sendMessage(msg1);
    commSystem.sendMessage(msg2);
    commSystem.sendMessage(msg3);

    // Simulate receiving and processing messages
    CommMessage receivedMsg;
    while (commSystem.receiveMessage(receivedMsg)) {
        std::cout << "Processing received message..." << std::endl;
        commSystem.processMessage(receivedMsg);
    }

    // Send another command (for demonstration purposes)
    CommMessage msg4 = {"SET_SPEED", "300", 1, 1005};  // Set speed for aircraft 1 again
    commSystem.sendMessage(msg4);

    // Display final status of all sent and received messages
    std::cout << "Final radar report (messages sent and processed):" << std::endl;
    std::cout << "Aircraft 1 speed set to 250, Aircraft 2 altitude set to 15000, Aircraft 3 position changed." << std::endl;

    return 0;
}
