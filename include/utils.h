#ifndef DAC_UTILS_H
#define DAC_UTILS_H

#include<map>
#include "dac_types.h"

const std::map<ObjectType,std::set<Right>>& getValidRights();
std::string objectTypeToString(ObjectType objType);
#endif