#ifndef OPERATORCOMMAND_H
#define OPERATORCOMMAND_H

#include <string>

enum class CommandType {
    SET_SPEED,
    SET_ALT,
    CHANGE_POS,
    INVALID
};

struct OperatorCommand {
    CommandType type;
    std::string aircraftId;
    int val1 = 0;
    int val2 = 0;
    int val3 = 0;
};

class OperatorCommandParser {
public:
    // Returns true if parse successful
    static bool parse(const std::string& input, OperatorCommand& commandOut);
};

#endif 
