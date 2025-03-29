#include "../include/parser.h"
#include<iostream>
Parser::Parser() {

};

Command Parser::parse(std::string &inputLine)
{
    std::cout<<"Got something to parse "<<inputLine<<std::endl;
    if(inputLine.empty()){
        return CommandType::BLANK;
    }
    std::transform(inputLine.begin(),inputLine.end(),inputLine.begin(),::tolower);
    std::cout<<"Transformed into: "<<inputLine<<std::endl;
    std::vector<std::string> tokens=tokenize(inputLine);
    CommandType comType=CommandType::ERROR;
    if(tokens[0]=="create"){
        std::cout<<"Entered create mode"<<std::endl;
        if(tokens.size()<3){
            return Command::createError("Invalid 'CREATE' syntax. Expected Create Subject/<Object Type> <Subject/Object Name>\n");
        }
        if(tokens[1]=="subject"){
            return Command(CommandType::CREATE_SUB,tokens[2],"",ObjectType::UNKNOWN,{});
        }else{
            ObjectType obType=stringToObjectType(tokens[1]);
            std::cout<<"Found the object type"<<std::endl;
            if(obType==ObjectType::UNKNOWN){
                return Command::createError("Invalid Object type '"+tokens[1]+"'. Use Help to find valid types");
            }else{
                return Command(CommandType::CREATE_OBJ,"",tokens[2],obType,{});
            }
        }
    }else if(tokens[0]=="grant"){
        std::cout << "Entered grant" << std::endl;
        if(tokens.size()<4){
            return Command::createError("Invalid GRANT syntax. Expected: Grant <Subject Name> <Object Name> [List of Rights]");
        }
        std::cout << "Passed check" << std::endl;
        std::set<Right> rightsSet;
        for(int i=3;i<tokens.size();i++){
            Right currentRight=stringToRight(tokens[i]);
            if(currentRight==Right::INVALID){
                return Command::createError("Invalid RIGHT '"+tokens[i]+"' encountered. Cancelling Operation.");
            }else{
                rightsSet.insert(currentRight);
            }
        }
        return Command(CommandType::GRANT,tokens[1],tokens[2],ObjectType::UNKNOWN,rightsSet);
    }else if(tokens[0]=="revoke"){
        comType=CommandType::REVOKE;
    }else if(tokens[0]=="check"){
        comType=CommandType::CHECK;
    }else if(tokens[0]=="policy"){
        comType=CommandType::POLICY;
    }else if(tokens[0]=="done"){
        comType=CommandType::DONE;
    }

    return CommandType::ERROR;
};
std::vector<std::string> Parser::tokenize(const std::string &inputLine)
{
    std::vector<std::string> tokens;
    std::istringstream tokenStream(inputLine);
    std::string token;
    while (tokenStream >> token)
    {
        tokens.push_back(token);
    }
    return tokens;
}
