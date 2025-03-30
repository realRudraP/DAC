#ifndef DAC_UTILS_H
#define DAC_UTILS_H

#include<map>
#include<iostream>
#include "dac_types.h"
#include<iomanip>

const std::map<ObjectType,std::set<Right>> getValidRights();
std::string objectTypeToString(ObjectType objType); // Returns the object type name in a string with first letter capitalized.
ObjectType stringToObjectType(const std::string str);
Right stringToRight(const std::string str);
std::string rightToString(Right right);
bool isRightValidForObject(Right right, ObjectType objectType);
void displayHelp();
#endif