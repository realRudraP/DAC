#ifndef DAC_MANAGER_H
#define DAC_MANAGER_H
#include<vector>
#include<string>
#include<iostream>
#include "../include/dac_types.h"
class AccessManager{
    ObjectNode* objectHead;
    std::set<std::string> subjects;
    public:
    AccessManager();
    bool addSubject(const std::string name);
    bool addObject(const std::string name,ObjectType obType);
};

#endif