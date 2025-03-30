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
void displayHelp() {
    std::cout << "\n==================================================\n";
    std::cout << "            DISCRETIONARY ACCESS CONTROL HELP            \n";
    std::cout << "==================================================\n\n";
    
    // Basic Commands Section
    std::cout << "BASIC COMMANDS:\n";
    std::cout << "---------------\n";
    std::cout << std::setw(40) << std::left << "Create Subject <Subject name>" << "Create a new subject in the system\n";
    std::cout << std::setw(40) << std::left << "Create <Object Type> <Object Name>" << "Create a new object of specified type\n";
    std::cout << std::setw(40) << std::left << "Grant <Subject Name> <Object Name> [Rights]" << "Grant permissions to a subject\n";
    std::cout << std::setw(40) << std::left << "Revoke <Subject Name> <Object Name> [Rights]" << "Remove permissions from a subject\n";
    std::cout << std::setw(40) << std::left << "Check <Subject Name> <Object Name> <Right>" << "Check if subject has specific permission\n";
    std::cout << std::setw(40) << std::left << "Done" << "Finish creating policies and move to access stage\n";
    std::cout << std::setw(40) << std::left << "Help" << "Display this help message\n\n";
    
    // Object Types Section
    std::cout << "AVAILABLE OBJECT TYPES:\n";
    std::cout << "----------------------\n";
    std::cout << "file, process, directory, database, device\n\n";
    
    // Rights Section
    std::cout << "AVAILABLE RIGHTS:\n";
    std::cout << "----------------\n";
    std::cout << "read (r), write (w), own (o), execute (x), run, open, stop, search, access\n\n";
    
    // Valid Rights per Object Type Section
    std::cout << "VALID RIGHTS PER OBJECT TYPE:\n";
    std::cout << "----------------------------\n";
    
    for (const auto& entry : validRights) {
        if (entry.first == ObjectType::UNKNOWN) continue;
        
        std::cout << objectTypeToString(entry.first) << ": ";
        bool first = true;
        for (const auto& right : entry.second) {
            if (!first) std::cout << ", ";
            std::cout << rightToString(right);
            first = false;
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    
    // Examples Section
    std::cout << "EXAMPLES:\n";
    std::cout << "---------\n";
    std::cout << "Create Subject alice\n";
    std::cout << "Create file document.txt\n";
    std::cout << "Create directory home\n";
    std::cout << "Grant alice document.txt read write\n";
    std::cout << "Check alice document.txt read\n";
    std::cout << "Revoke alice document.txt write\n";
    std::cout << "Done\n\n";
    
    // Notes Section
    std::cout << "NOTES:\n";
    std::cout << "------\n";
    std::cout << "- Rights can be specified using full names (read, write) or shortcuts (r, w, o, x) where applicable\n";
    std::cout << "- Object names and Subject names are case-insensitive\n";
    std::cout << "- Multiple rights can be specified in Grant and Revoke commands\n";
    std::cout << "- The 'Check' command requires specifying a particular right to check\n";
    std::cout << "==================================================\n\n";
}

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
    } else if (str == "run") {
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
