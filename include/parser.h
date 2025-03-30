#ifndef DAC_PARSER_H
#define DAC_PARSER_H

#include<string>
#include<vector>
#include "command.h"
#include "utils.h"
#include<sstream>
#include<algorithm>

class Parser{
    public:
    Parser();
    Command parse(std::string& inputLine);
    Command parseAccessRequest(std::string inputLine);

private:
    std::vector<std::string> tokenize(const std::string& inputLine);
};
#endif