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
        commandOut = { CommandType::SET_SPEED, id, v1, v2, v3 };
        return true;
    }
    else if (commandTypeStr == "SET_ALT") {
        if (!(iss >> v1)) return false;
        commandOut = { CommandType::SET_ALT, id, 0, 0, v1 };
        return true;
    }
    else if (commandTypeStr == "CHANGE_POS") {
        if (!(iss >> v1 >> v2 >> v3)) return false;
        commandOut = { CommandType::CHANGE_POS, id, v1, v2, v3 };
        return true;
    }

    return false;
}
