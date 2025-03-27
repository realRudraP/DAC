#include "../include/utils.h"
#include "include/command.h"

const std::map<ObjectType, std::set<Right>> validRights = {
    {ObjectType::FILE, {Right::READ, Right::WRITE, Right::OWN, Right::OPEN, Right::SEARCH, Right::ACCESS}},
    {ObjectType::PROCESS, {Right::OWN, Right::EXECUTE, Right::STOP, Right::SEARCH}},
    {ObjectType::DIRECTORY, {Right::READ, Right::WRITE, Right::OWN, Right::OPEN, Right::SEARCH, Right::SEARCH, Right::ACCESS}},
    {ObjectType::DATABASE, {Right::READ, Right::WRITE, Right::OWN, Right::OPEN, Right::STOP, Right::ACCESS}},
    {ObjectType::DEVICE, {Right::OWN, Right::RUN, Right::STOP, Right::ACCESS}},
{ObjectType::UNKNOWN,{}}};




