//
// Created by Artem Bykov on 22.05.2018.
//

#ifndef AVM_PARSER_HPP
#define AVM_PARSER_HPP

#include "Lexer.hpp"
#include <iostream>
#include <limits>

class Parser {

public:
    Parser(const tTokens& tokens);
    ~Parser();
    void run();
    void printTokens();

private:
    Parser() = delete;
    Parser(const Parser& obj) = delete;
    Parser& operator=(const Parser& obj) = delete;

    void validateLine(const std::vector<std::string>& line);
    template<class T> void validateIntegral(const std::string& value);
    void addError(const std::string& error);
    void checkExit(const std::string& operation);

    const tTokens& tokens_;
    std::string errors_;
};



#endif //AVM_PARSER_HPP
