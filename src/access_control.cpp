#include "../include/dac_types.h"
#include "../include/manager.h"

AccessManager::AccessManager(){
    AccessManager::objectHead=nullptr;
}

bool AccessManager::addSubject(const std::string name){
    if(AccessManager::subjects.find(name)!=AccessManager::subjects.end()){ // Check if there is existing subject with the same name
        AccessManager::subjects.insert(name);
        return true;
    }else{
        std::cerr<<"Error: There already exists a subject with name: '"+name+"'. Please try another name\n";
        return false;
    }
}