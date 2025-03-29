#include "../include/utils.h"
#include "../include/command.h"

const std::map<ObjectType, std::set<Right>> validRights = {
    { ObjectType::FILE, { Right::READ, Right::WRITE, Right::OWN, Right::OPEN, Right::SEARCH, Right::ACCESS } },
    { ObjectType::PROCESS, { Right::OWN, Right::EXECUTE, Right::STOP, Right::SEARCH } },
    { ObjectType::DIRECTORY, { Right::READ, Right::WRITE, Right::OWN, Right::OPEN, Right::SEARCH, Right::SEARCH, Right::ACCESS } },
    { ObjectType::DATABASE, { Right::READ, Right::WRITE, Right::OWN, Right::OPEN, Right::STOP, Right::ACCESS } },
    { ObjectType::DEVICE, { Right::OWN, Right::RUN, Right::STOP, Right::ACCESS } },
    { ObjectType::UNKNOWN, {} }
};

ObjectType stringToObjectType(const std::string str)
{
    if (str == "file") {
        return ObjectType::FILE;
    } else if (str == "process") {
        return ObjectType::PROCESS;
    } else if (str == "directory") {
        return ObjectType::DIRECTORY;
    } else if (str == "database") {
        return ObjectType::DATABASE;
    } else if (str == "device") {
        return ObjectType::DEVICE;
    } else {
        return ObjectType::UNKNOWN;
    }
}
bool isRightValidForObject(Right right, ObjectType objectType)
{
    if (objectType == ObjectType::UNKNOWN || right == Right::INVALID) {
        return false;
    }
    auto mapIterator = validRights.find(objectType);

    if(mapIterator==validRights.end()){
        std::cerr << "Warning: Illeagal objectType encountered in isRightValidForObject"
                  << std::endl;
        return false;
    }
    const std::set<Right>& allowedRights = mapIterator->second;

    return allowedRights.count(right) > 0;
}
std::string objectTypeToString(ObjectType objType)
{
    if (objType == ObjectType::FILE) {
        return "File";
    } else if (objType == ObjectType::DATABASE) {
        return "Database";
    } else if (objType == ObjectType::DEVICE) {
        return "Device";
    } else if (objType == ObjectType::DIRECTORY) {
        return "Directory";
    } else if (objType == ObjectType::PROCESS) {
        return "Process";
    } else if (objType == ObjectType::UNKNOWN) {
        return "Unknown";
    } else {
        return "Error in objectTypeToString()";
    }
}

Right stringToRight(const std::string str)
{
    if (str == "read" || str == "r") {
        return Right::READ;
    } else if (str == "write" || str == "w") {
        return Right::WRITE;
    } else if (str == "own" || str == "o") {
        return Right::OWN;
    } else if (str == "execute" || str == "x") {
        return Right::EXECUTE;
    } else if (str == "run" || str == "r") {
        return Right::RUN;
    } else if (str == "open") {
        return Right::OPEN;
    } else if (str == "stop") {
        return Right::STOP;
    } else if (str == "search") {
        return Right::SEARCH;
    } else if (str == "access") {
        return Right::ACCESS;
    }
    return Right::INVALID;
}
std::string rightToString(Right right) {
    switch (right) {
        case Right::READ:
            return "Read";
        case Right::WRITE:
            return "Write";
        case Right::OWN:
            return "Own";
        case Right::EXECUTE:
            return "Execute";
        case Right::RUN:
            return "Run";
        case Right::OPEN:
            return "Open";
        case Right::STOP:
            return "Stop";
        case Right::SEARCH:
            return "Search";
        case Right::ACCESS:
            return "Access";
        case Right::INVALID:
            return "INVALID"; 
        default:
            return "UnknownRight";
    }
}
