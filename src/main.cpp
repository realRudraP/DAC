#include "../include/command.h"
#include "../include/dac_types.h"
#include "../include/manager.h"
#include "../include/parser.h"
#include "../include/colors.h"
#include <iostream>
#include <string>
int main()
{
    Parser parser;
    AccessManager manager;
    std::cout << "Discretionary Access Control: Linked List\n";
    std::cout << "(Create Access Policy Mode)\n";
    std::cout << "Commands:\n";
    std::cout << "\tCreate Subject <Subject name>\n\tCreate <Object Type> <Object Name>\n";
    std::cout << "\tGrant <Subject Name> <Object Name> [List of Rights]\n";
    std::cout << "\tRevoke <Subject Name> <Object Name> [List of Rights]\n";
    std::cout << "\tCheck <Subject Name> <Object Name> <Right to check>\n";
    std::cout << "\tDone (Finish creating policies)\n";

    std::string inputLine;
    while (true) {
        std::cout << "Create ACL> ";
        if (!std::getline(std::cin, inputLine)) {
            std::cerr << "Error in input from console" << std::endl;
        }
        Command currentCommand = parser.parse(inputLine);
        if (currentCommand.type == CommandType::CREATE_SUB) {
            if (manager.addSubject(currentCommand.subject)) {
                std::cout << "Subject " + currentCommand.subject + " added successfully" << std::endl;
            }
        } else if (currentCommand.type == CommandType::CREATE_OBJ) {
            if (manager.addObject(currentCommand.object, currentCommand.objType)) {
                std::cout << "Object " + currentCommand.object + " added successfully" << std::endl;
            }
        } else if (currentCommand.type == CommandType::GRANT) {
            if (manager.grantPermissions(currentCommand.object, currentCommand.subject, currentCommand.rights)) {
                std::cout << "Subject '" + currentCommand.subject + "' now has updated permissions for object '" + currentCommand.object + "'" << std::endl;
            }
        } else if (currentCommand.type == CommandType::REVOKE) {
            if (manager.removePermissions(currentCommand.object, currentCommand.subject, currentCommand.rights)) {
                std::cout << "Subject '" + currentCommand.subject + "' now has updated permissions for object '" + currentCommand.object + "'" << std::endl;
            }
        } else if (currentCommand.type == CommandType::CHECK) {
            if (manager.hasPermission(currentCommand.object, currentCommand.subject, currentCommand.rights)) {
                std::cout << "Subject " + currentCommand.subject + " has " + rightToString(*(currentCommand.rights).begin()) + " access on the object " + currentCommand.object << std::endl;
            }
        } else if (currentCommand.type == CommandType::DONE) {
            break;
        } else if (currentCommand.type == CommandType::HELP) {
            displayHelp();
        } else if (currentCommand.type == CommandType::ERROR) {
            std::cerr << "Error: " + currentCommand.errorMessage << std::endl;
        }
    }

    std::cout << "Entering Access Check Mode\n";
    std::cout << "Format: <Subject Name> <Object Name> <Right to access>\n";
    std::cout << "Type 'Exit' to end program\n";
    std::string accessLine;
    while (true) {
        std::cout << "Check Access> ";
        if (!std::getline(std::cin, accessLine)) {
            std::cerr << "Error in input from console" << std::endl;
            break;
        }

        if (accessLine == "Exit" || accessLine == "exit") {
            std::cout << "Exiting program" << std::endl;
            break;
        }

        Command accessRequest = parser.parseAccessRequest(accessLine);
        if (accessRequest.type == CommandType::ERROR) {
            std::cerr << "Error: " + accessRequest.errorMessage << std::endl;
            continue;
        }

        if (manager.hasPermission(accessRequest.object, accessRequest.subject, accessRequest.rights)) {
            std::cout << Color::GREEN<<"Access GRANTED: "<<Color::RESET<<"Subject '" + accessRequest.subject + "' has " + rightToString(*(accessRequest.rights).begin()) + " access on object '" + accessRequest.object + "'" << std::endl;
        } 
    }
}