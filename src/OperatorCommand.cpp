#include "OperatorCommand.h"
#include <sstream>

std::optional<OperatorCommand> OperatorCommandParser::parse(const std::string& input) {
    std::istringstream iss(input);
    std::string commandTypeStr;
    std::string id;
    int v1 = 0, v2 = 0, v3 = 0;

    iss >> commandTypeStr >> id;

    if (commandTypeStr == "SET_SPEED") {
        if (!(iss >> v1 >> v2 >> v3)) return std::nullopt;
        return OperatorCommand{ CommandType::SET_SPEED, id, v1, v2, v3 };
    }
    else if (commandTypeStr == "SET_ALT") {
        if (!(iss >> v1)) return std::nullopt;
        return OperatorCommand{ CommandType::SET_ALT, id, 0, 0, v1 }; // Altitude stored in val3
    }
    else if (commandTypeStr == "CHANGE_POS") {
        if (!(iss >> v1 >> v2 >> v3)) return std::nullopt;
        return OperatorCommand{ CommandType::CHANGE_POS, id, v1, v2, v3 };
    }

    return std::nullopt;
}
