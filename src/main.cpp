#include<iostream>
#include<string>
#include "../include/dac_types.h"
#include "../include/command.h"
#include "../include/parser.h"
#include "../include/manager.h"
int main(){
    Parser parser;
    AccessManager manager;
    std::cout<<"Discretionary Access Control: Linked List\n";
    std::cout<<"(Create Access Policy Mode)\n";
    std::cout<<"Commands:\n";
    std::cout<<"\tCreate Subject <Subject name>\n\tCreates <Object Type> <Object Name>\n";
    std::cout<<"\tGrant <Subject Name> <Object Name> [List of Rights]\n";
    std::cout<<"\tRevoke <Subject Name> <Object Name> [List of Rights]\n";
    std::cout<<"\tCheck <Subject Name> <Object Name> <Right>\n";
    std::cout<<"\tPolicy\n";
    std::cout<<"\tDone (Finish creating policies)\n";

    std::string inputLine;
    while (true)
    {
        std::cout<<"Create ACL> ";
        if(!std::getline(std::cin,inputLine)){
            std::cerr<<"Error in input from console"<<std::endl;
        }
        Command currentCommand=parser.parse(inputLine);
        if(currentCommand.type==CommandType::CREATE_OBJ){
            if(manager.addSubject(currentCommand.subject)){
                std::cout<<"Subject "+currentCommand.subject+" added successfully"<<std::endl;
            }
        }
    }
    
    return 0;
}