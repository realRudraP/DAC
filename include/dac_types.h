#ifndef DAC_TYPES_H
#define DAC_TYPES_H

#include <string>
#include <set>
enum class Right
{
    READ,
    WRITE,
    OWN,
    EXECUTE,
    RUN,
    OPEN,
    STOP,
    SEARCH,
    ACCESS,
    INVALID
};

enum class ObjectType{
    FILE,  // Read, Write, Own, Open, Search and Access Operations can be performed 
    PROCESS, // Own, Execute, Stop and Search Operations can be performed
    DIRECTORY, // Read, Write, Own, Open, Search and Access Operations can be performed
    DATABASE, // Read, Write, Own, Run, Open, Stop and Access Operations can be performed
    DEVICE, // Own, Run, Stop and Access Operations can be performed
    UNKNOWN // To be used for error 
};


ObjectType stringToObjectType(const std::string str){
    if(str=="file"){
        return ObjectType::FILE;
    }else if(str=="process"){
        return ObjectType::PROCESS;
    }else if(str=="directory"){
        return ObjectType::DIRECTORY;
    }else if(str=="database"){
        return ObjectType::DATABASE;
    }else if(str=="device"){
        return ObjectType::DEVICE;
    }else{
        return ObjectType::UNKNOWN;
    }
}
class ACLEntry
{
public:
    std::string subjectId;
    std::set<Right> rights;
    ACLEntry *next = nullptr;

    ACLEntry(const std::string &subId)
    {
        subjectId = subId;
    }
};

class ObjectNode
{
public:
    std::string objectId;
    ACLEntry *aclHead = nullptr;
    ObjectNode *next = nullptr;
    ObjectType objectType;

    ObjectNode(const std::string &objectId, ObjectType objType)
    {
        this->objectId = objectId;
        this->objectType=objType;
        aclHead=nullptr;
        next=nullptr;
    }
    ~ObjectNode();
};

#endif