#include "../include/parser.h"
#include<iostream>
Parser::Parser() {

};

Command Parser::parse(std::string &inputLine)
{
    if(inputLine.empty()){
        return CommandType::BLANK;
    }
    std::transform(inputLine.begin(),inputLine.end(),inputLine.begin(),::tolower);
    std::vector<std::string> tokens=tokenize(inputLine);
    if(tokens[0]=="create"){
        if(tokens.size()<3){
            return Command::createError("Invalid 'CREATE' syntax. Expected Create Subject/<Object Type> <Subject/Object Name>\n");
        }
        if(tokens[1]=="subject"){
            return Command(CommandType::CREATE_SUB,tokens[2],"",ObjectType::UNKNOWN,{});
        }else{
            ObjectType obType=stringToObjectType(tokens[1]);
            if(obType==ObjectType::UNKNOWN){
                return Command::createError("Invalid Object type '"+tokens[1]+"'. Use Help to find valid types");
            }else{
                return Command(CommandType::CREATE_OBJ,"",tokens[2],obType,{});
            }
        }
    }else if(tokens[0]=="grant"){
        if(tokens.size()<4){
            return Command::createError("Invalid GRANT syntax. Expected: Grant <Subject Name> <Object Name> [List of Rights]");
        }
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
        if(tokens.size()<4){
            return Command::createError("Invalid REVOKE syntax. Expected: Revoke <Subject Name> <Object Name> [List of Rights]");
        }
        std::set<Right> rightsSet;
        for(int i=3;i<tokens.size();i++){
            Right currentRight=stringToRight(tokens[i]);
            if(currentRight==Right::INVALID){
                return Command::createError("Invalid RIGHT '"+tokens[i]+"' encountered. Cancelling Operation.");
            }else{
                rightsSet.insert(currentRight);
            }
        }
        return Command(CommandType::REVOKE,tokens[1],tokens[2],ObjectType::UNKNOWN,rightsSet);
    }else if(tokens[0]=="check"){
        if(tokens.size()<4){
            return Command::createError("Invalid CHECK syntax. Expected: Check <Subject Name> <Object Name> [List of Rights]");
        }
        std::set<Right> rightsSet;
        if(tokens[3]=="all"){
            rightsSet.insert(Right::ALL);
        }else{
            Right requestedRight = stringToRight(tokens[3]);
            if(requestedRight==Right::INVALID){
                return Command::createError("Invalid permission '" + tokens[3] + "' encountered. Cancelling check.");
            }
            rightsSet.insert(requestedRight);
        }
        return Command(CommandType::CHECK,tokens[1],tokens[2],ObjectType::UNKNOWN,rightsSet);
    }else if(tokens[0]=="done"){
        return CommandType::DONE;
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
