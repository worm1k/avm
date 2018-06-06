//
// Created by Artem Bykov on 22.05.2018.
//

#ifndef AVM_PARSER_HPP
#define AVM_PARSER_HPP

#include "Lexer.hpp"
#include <iostream>
#include <limits>

class Parser
{
public:
    Parser(const tTokens& tokens);
    ~Parser();

    void run();
    void printTokens();

    Parser()                         = delete;
    Parser(const Parser&)            = delete;
    Parser& operator=(const Parser&) = delete;

private:
    void validateLine(const std::vector<std::string>& line);
    template<class T> void validateIntegral(const std::string& value);
    template<class T> void validateFloat(const std::string& value);
    void addError(const std::string& error);
    void checkExit(const std::string& operation, bool& has_exit);

    const tTokens& tokens_;
    std::string errors_;
};

#endif //AVM_PARSER_HPP
