#include "include/parser.h"

Parser::Parser() {

};

Command Parser::parse(std::string &inputLine)
{
    if(inputLine.empty()){
        return CommandType::BLANK;
    }
    std::transform(inputLine.begin(),inputLine.end(),inputLine.begin(),::tolower);
    std::vector<std::string> tokens=tokenize(inputLine);
    CommandType comType=CommandType::ERROR;
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
        comType=CommandType::GRANT;
    }else if(tokens[0]=="revoke"){
        comType=CommandType::REVOKE;
    }else if(tokens[0]=="check"){
        comType=CommandType::CHECK;
    }else if(tokens[0]=="policy"){
        comType=CommandType::POLICY;
    }else if(tokens[0]=="done"){
        comType=CommandType::DONE;
    }

}


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
