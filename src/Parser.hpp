//
// Created by Artem Bykov on 22.05.2018.
//

#ifndef AVM_PARSER_HPP
#define AVM_PARSER_HPP

#include "Lexer.hpp"
#include <iostream>

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
    template<class T> void validateIntegral(const std::string& line);
    void addError(const std::string& error);

    const tTokens& tokens_;
    std::string errors_;
};


template<class T>
void Parser::validateIntegral(const std::string& line)
{
    std::cout << "inside validateIntegral: ";
    std::cout << typeid(T).name() << std::endl;
}


#endif //AVM_PARSER_HPP
