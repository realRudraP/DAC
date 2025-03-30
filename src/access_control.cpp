#include "../include/dac_types.h"
#include "../include/manager.h"
#include "../include/utils.h"
#include "../include/colors.h"

AccessManager::AccessManager() { AccessManager::objectHead = nullptr; }
inline bool AccessManager::subjectExists(const std::string name)
{
    return AccessManager::subjects.find(name) != AccessManager::subjects.end();
}
bool AccessManager::addSubject(const std::string name)
{
    if (!AccessManager::subjectExists(
            name)) { // Check if there is existing subject with the same name
        AccessManager::subjects.insert(name);
        return true;
    } else {
        std::cerr << "Error: There already exists a subject with name: '" + name + "'. Please try another name\n";
        return false;
    }
}
bool AccessManager::addObject(const std::string name, ObjectType obType)
{
    if (AccessManager::findObjectWithName(name) != nullptr) {
        std::cout << "Object with name '" + name + "' already exists. Please choose another name"
                  << std::endl;
        return false;
    }
    ObjectNode* newObject = new ObjectNode(name, obType);
    if (AccessManager::objectHead == nullptr) {
        AccessManager::objectHead = newObject;
        return true;
    }
    ObjectNode* currentNode = AccessManager::objectHead;
    while (currentNode->next != nullptr) {
        currentNode = currentNode->next;
    }
    currentNode->next = newObject;
    return true;
}
ObjectNode* AccessManager::findObjectWithName(const std::string name)
{
    ObjectNode* currentNode = AccessManager::objectHead;
    while (currentNode != nullptr && currentNode->objectId != name) {
        currentNode = currentNode->next;
    }
    return currentNode;
}
ObjectType AccessManager::findObjectTypeOfName(const std::string name)
{
    ObjectNode* requiredNode = AccessManager::findObjectWithName(name);
    if (requiredNode != nullptr) {
        return requiredNode->objectType;
    } else {
        return ObjectType::UNKNOWN;
    }
}
ACLEntry* AccessManager::findACLEntryWithinObject(ObjectNode* obj,
    const std::string subjectName,
    bool createIfDoesntExist)
{
    if (obj->aclHead == nullptr) {
        if (createIfDoesntExist) {
            obj->aclHead = new ACLEntry(subjectName);
            return obj->aclHead;
        }
        return nullptr;
    }
    ACLEntry* entry = obj->aclHead;
    ACLEntry* previous = nullptr;
    while (entry != nullptr && entry->subjectId != subjectName) {
        previous = entry;
        entry = entry->next;
    }

    if (entry == nullptr && createIfDoesntExist) {
        ACLEntry* newEntry = new ACLEntry(subjectName);
        previous->next = newEntry; // This is safe now since previous can't be nullptr
        entry = newEntry;
    }

    return entry;
}

bool AccessManager::grantPermissions(const std::string objName,
    const std::string subName,
    std::set<Right> rights)
{
    ObjectNode* requiredObject = AccessManager::findObjectWithName(objName);
    if (!AccessManager::subjectExists(subName)) {
        std::cerr << "Error in GRANT operation. No subject with name '" + subName + "' was found. Cancelling operation"
                  << std::endl;
        return false;
    }

    if (requiredObject == nullptr) {
        std::cerr << "Error in GRANT operation. No object with name '" + objName + "' was found."
                  << std::endl;
        return false;
    }
    ACLEntry* acl = AccessManager::findACLEntryWithinObject(requiredObject, subName, true);
    bool permissionChanged = false;
    for (Right right : rights) {
        if (isRightValidForObject(right, requiredObject->objectType)) {
            acl->rights.insert(right);
            permissionChanged = true;
        } else {
            std::cout << "\tInfo: The right '" + rightToString(right) + "' is not valid for the object type '" + objectTypeToString(requiredObject->objectType) + "'. Permission is not added" << std::endl;
        }
    }

    return permissionChanged;
}
bool AccessManager::removePermissions(const std::string objName, const std::string subName, std::set<Right> rights)
{
    ObjectNode* requiredObject = AccessManager::findObjectWithName(objName);
    if (!AccessManager::subjectExists(subName)) {
        std::cerr << "Error in REVOKE operation. No subject with name '" + subName + "' was found. Cancelling operation"
                  << std::endl;
        return false;
    }

    if (requiredObject == nullptr) {
        std::cerr << "Error in REVOKE operation. No object with name '" + objName + "' was found."
                  << std::endl;
        return false;
    }
    if (!this->subjectExists(subName)) {
        std::cerr << "Warning in REVOKE operation: Subject '" << subName << "' is not globally known (though permissions might not exist anyway)." << std::endl;
        return false;
    }
    ACLEntry* entryToModify = nullptr;
    ACLEntry* previousEntry = nullptr;
    ACLEntry* currentEntry = requiredObject->aclHead;

    while (currentEntry != nullptr) {
        if (currentEntry->subjectId == subName) {
            entryToModify = currentEntry;
            break;
        }
        previousEntry = currentEntry;
        currentEntry = currentEntry->next;
    }

    if (entryToModify == nullptr) {
        std::cout << "Info: Subject '" << subName << "' has no permissions on object '" << objName << "'. Nothing to revoke." << std::endl;
        return true;
    }

    bool rightsWereRemoved = false;
    for (Right right : rights) {
        if (entryToModify->rights.erase(right) > 0) {
            rightsWereRemoved = true;
        } else {
            std::cout << "\tInfo: Given subject didnt't have '" + rightToString(right) + "' permission on the given object. Continuing with other rights revocation" << std::endl;
        }
    }
    if (!rightsWereRemoved) {
        std::cout << "Info: None of the specified rights were present for subject '" << subName << "' on object '" << objName << "'." << std::endl;
    }
    if (entryToModify->rights.empty()) {
        std::cout << "Info: All rights removed for subject '" << subName << "' on object '" << objName << "'. Removing ACL entry." << std::endl;

        if (previousEntry == nullptr) {
            requiredObject->aclHead = entryToModify->next;
        } else {
            previousEntry->next = entryToModify->next;
        }
        delete entryToModify;
        entryToModify = nullptr;
    }
    return true;
}

const bool AccessManager::hasPermission(const std::string objName, const std::string subName, std::set<Right> right)
{
    ObjectNode* targetObject = findObjectWithName(objName);
    if (targetObject == nullptr) {
        std::cerr << "Warning: checkAccesss failed- Object " + objName + " not found" << std::endl;
        return false;
    }
    if (!subjectExists(subName)) {
        std::cerr << "Warning: checkAccess failed- Subject " + subName + " not found" << std::endl;
        return false;
    }
    ACLEntry* acl = findACLEntryWithinObject(targetObject, subName, false);
    if (acl == nullptr) {
        std::cout << Color::RED<<"The subject " + subName + " has no rights on the object " + objName <<Color::RESET<< std::endl;
        return false;
    }
    for (Right r : right) {
        bool hasRight = acl->rights.count(r) > 0;
        if (!hasRight) {
            std::cout<<Color::RED<<"Access DENIED:"<<Color::RESET <<"Subject '" + subName + "' does NOT have " + rightToString(*(right).begin()) + " access on object '" + objName + "'" << std::endl;
        }
        return hasRight;
    }
    return false;
}