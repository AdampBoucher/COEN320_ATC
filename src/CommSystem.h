#ifndef COMMSYSTEM_H_
#define COMMSYSTEM_H_

#include <string>
#include <vector>

// Define message structure
struct CommMessage {
    std::string command;
    std::string data;
    int aircraftId;
    int timestamp;
};

// Communication system class for sending and receiving messages
class CommSystem {
public:
    CommSystem();
    ~CommSystem();

    // Initializes communication system (shared memory, message queues, etc.)
    bool initialize();

    // Send message to another system
    bool sendMessage(const CommMessage& message);

    // Receive message from another system
    bool receiveMessage(CommMessage& message);

    // Process the message (interpreting and executing commands)
    void processMessage(const CommMessage& message);

private:
    // Internal storage for messages (could be message queue, buffer, etc.)
    std::vector<CommMessage> messageQueue;
};

#endif // COMMSYSTEM_H_
