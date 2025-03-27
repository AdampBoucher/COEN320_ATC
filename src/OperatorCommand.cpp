#include "OperatorCommand.h"
#include <sstream>

bool OperatorCommandParser::parse(const std::string& input, OperatorCommand& commandOut) {
    std::istringstream iss(input);
    std::string commandTypeStr;
    std::string id;
    int v1 = 0, v2 = 0, v3 = 0;

    iss >> commandTypeStr >> id;

    if (commandTypeStr == "SET_SPEED") {
        if (!(iss >> v1 >> v2 >> v3)) return false;
        commandOut.type = CommandType::SET_SPEED;
        commandOut.aircraftId = id;
        commandOut.val1 = v1;
        commandOut.val2 = v2;
        commandOut.val3 = v3;
        return true;
    }
    else if (commandTypeStr == "SET_ALT") {
        if (!(iss >> v1)) return false;
        commandOut.type = CommandType::SET_ALT;
        commandOut.aircraftId = id;
        commandOut.val1 = 0;
        commandOut.val2 = 0;
        commandOut.val3 = v1;
        return true;
    }
    else if (commandTypeStr == "CHANGE_POS") {
        if (!(iss >> v1 >> v2 >> v3)) return false;
        commandOut.type = CommandType::CHANGE_POS;
        commandOut.aircraftId = id;
        commandOut.val1 = v1;
        commandOut.val2 = v2;
        commandOut.val3 = v3;
        return true;
    }

    return false;
}
