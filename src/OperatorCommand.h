#ifndef OPERATORCOMMAND_H
#define OPERATORCOMMAND_H

#include <string>
#include <optional>

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
    // Parses a raw command string
    static std::optional<OperatorCommand> parse(const std::string& input);
};

#endif 
