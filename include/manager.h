#ifndef DAC_MANAGER_H
#define DAC_MANAGER_H
#include<vector>
#include<string>
#include<iostream>
#include "../include/dac_types.h"
class AccessManager{
    ObjectNode* objectHead;
    std::set<std::string> subjects;
    inline bool subjectExists(const std::string name);
    public:
    AccessManager();
    bool addSubject(const std::string name);
    bool addObject(const std::string name,ObjectType obType);
    
    ObjectNode* findObjectWithName(const std::string name);
    ObjectType findObjectTypeOfName(const std::string name);
    ACLEntry* findACLEntryWithinObject(ObjectNode* obj,const std::string subjectName,bool createIfDoesntExist);
    bool grantPermissions(const std::string subName,const std::string objName,std::set<Right>rights);
    bool removePermissions(const std::string subName, const std::string objName, std::set<Right> rights);
};

#endif