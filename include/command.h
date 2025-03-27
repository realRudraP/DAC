#ifndef DAC_COMMAND_H
#define DAC_COMMAND_H

#include <string>
#include <vector>
#include <set>
#include <optional>
#include "dac_types.h"

enum class CommandType
{
    CREATE_OBJ,
    CREATE_SUB,
    GRANT,
    REVOKE,
    CHECK,
    POLICY,
    BLANK,
    ERROR,
    DONE
};

class Command
{
public:
    CommandType type;

    std::string subject;
    std::string object;
    ObjectType objType = ObjectType::UNKNOWN;
    std::set<Right> rights;

    std::string errorMessage;

    // Constructor for blank commands
    Command(CommandType t = CommandType::BLANK) : type(t) {};

    // Constructor for normal commands
    Command(CommandType t, std::string subject, std::string object, ObjectType objType, std::set<Right> right) : type(t), subject(std::move(subject)), object(std::move(object)), objType(objType), rights(std::move(right)) {};

    static Command createError(std::string message){
        Command cmd(CommandType::ERROR);
        cmd.errorMessage=std::move(message);
        return cmd;
    }
};


#endif
