//
// Created by Artem Bykov on 22.05.2018.
//

#include "Parser.hpp"
#include <iostream>

Parser::Parser(const tTokens& tokens)
    : tokens_(tokens)
{
}

Parser::~Parser()
{}

void Parser::printTokens()
{
    std::cout << "output number of lines with tokens: " << this->tokens_.size() << std::endl;
    for (auto& line : this->tokens_) {
        for (auto& token : line) {
            std::cout << token << " ";
        }
    }
    std::cout << std::endl;
}

void Parser::run()
{
    std::cout << "Parsing ========" << std::endl;
    std::cout << tokens_.size() << std::endl;
    printTokens();
    bool has_exit = false;

    for (auto& line : this->tokens_) {
        if (line[0] == "assert" || line[0] == "push") {
            validateLine(line);
        }
        else {
//            checkExit(line[0]);
        }
    }
}

void Parser::validateLine(const std::vector<std::string>& line)
{
    if (line[1] == "int8") {
        this->template validateIntegral<int8_t>(line);
    }
    else if (line[1] == "int16") {

    }
    else if (line[1] == "int32") {

    }
    else if (line[1] == "float") {

    }
    else if (line[1] == "int8") {

    }
    else {
        // thorw sth
    }
}


void Parser::addError(const std::string& error)
{
    if (errors_.empty()) {
        errors_ = error;
    }
    else {
        errors_ += "\n";
        errors_ += error;
    }
}
