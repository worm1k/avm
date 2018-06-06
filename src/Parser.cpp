//
// Created by Artem Bykov on 22.05.2018.
//

#include "Parser.hpp"
#include "LerserException.hpp"

#include <iostream>

template<> void Parser::validateIntegral<double>(const std::string& value);
template<> void Parser::validateIntegral<float>(const std::string& value);

Parser::Parser(const tTokens& tokens)
    : tokens_(tokens)
{}

Parser::~Parser()
{}

//void Parser::printTokens()
//{
//    std::cout << "number of lines: " << this->tokens_.size() << std::endl;
//    for (auto& line : this->tokens_) {
//        for (auto& token : line) {
//            std::cout << token << " ";
//        }
//        std::cout << std::endl;
//    }
//}

void Parser::run()
{
    std::cout << "======== Parsing ========" << std::endl;

    bool has_exit = false;

    for (auto& line : this->tokens_) {
        if (line[0] == "assert" || line[0] == "push") {
            validateLine(line);
        }
        else {
            checkExit(line[0], has_exit);
        }
    }
    if (!has_exit) {
        addError(std::string("ParserException: exit command is missing"));
    }
    if (!errors_.empty()) {
        throw LerserException(errors_);
    }
    std::cout << "======== Parsed =========" << std::endl;
}

void Parser::validateLine(const std::vector<std::string>& line)
{
    if (line[1] == "int8") {
        validateIntegral<int8_t>(line[2]);
    }
    else if (line[1] == "int16") {
        validateIntegral<int16_t>(line[2]);
    }
    else if (line[1] == "int32") {
        validateIntegral<int32_t>(line[2]);
    }
    else if (line[1] == "float") {
        validateFloat<float>(line[2]);
    }
    else if (line[1] == "double") {
        validateFloat<double>(line[2]);
    }
    else {
        addError(std::string("ParserException: unknown type: ") + line[1]);
    }
}

template<class T> // int8 || int16 || int32
void Parser::validateIntegral(const std::string& value)
{
    std::cout << "inside validateIntegral: ";
    std::cout << typeid(T).name() << std::endl;
    try {
        long long time_ago = std::stoll(value);
        T min = std::numeric_limits<T>::lowest();
        T max = std::numeric_limits<T>::max();

        if (time_ago < min || max < time_ago) {
            addError(std::string("ParserException: \"") + value + "\" is out of boundaries.\n");
        }
    } catch (std::invalid_argument& e) {
        addError(std::string("std::invalid_argument Exception on value \"") + value +  "\": " + e.what());
    } catch (std::out_of_range& e) {
        addError(std::string("std::out_of_range: Exception on value \"") + value + "\": " + e.what());
    }
}

template<class T> // float || double
void Parser::validateFloat(const std::string& value)
{
    std::cout << "inside validateFloat: ";
    std::cout << typeid(T).name() << std::endl;
    try {
        long double time_ago = std::stold(value);
        T min = std::numeric_limits<T>::lowest();
        T max = std::numeric_limits<T>::max();

        if (time_ago < min || max < time_ago) {
            addError(std::string("ParserException: \"") + value + "\" is out of boundaries.\n");
        }
    } catch (std::invalid_argument& e) {
        addError(std::string("std::invalid_argument Exception on value \"") + value +  "\": " + e.what());
    } catch (std::out_of_range& e) {
        addError(std::string("std::out_of_range: Exception on value \"") + value + "\": " + e.what());
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

void Parser::checkExit(const std::string &operation, bool& has_exit)
{
    if (operation == "exit") {
        if (!has_exit) {
            has_exit = true;
        }
        else {
            addError(std::string("ParserException: more than one exit"));
        }
    }
}
