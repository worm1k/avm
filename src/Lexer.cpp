//
// Created by Artem Bykov on 22.05.2018.
//

#include "Lexer.hpp"
#include "LexerException.hpp"
#include <iostream>
#include <regex>
#include <sstream>
#include <fstream>

Lexer::Lexer(int argc, char** argv)
{
    if (argc == 1) {
        readInputFunction_ = std::bind(&Lexer::readFromConsole, this);
    }
    else if (argc == 2) {
        if (std::string("/dev/zero") == argv[1]) {
            throw LexerException("EricException: the best place to put /dev/zero is up your ass");
        }
        readInputFunction_ = std::bind(&Lexer::readFromFile, this, argv[1]);
    }
    else {
        throw LexerException("LexerException: Invalid number of arguments");
    }
}

Lexer::~Lexer()
{}

void Lexer::readFromConsole()
{
    std::cout << "reading from console" << std::endl;
    std::string line;
    int line_number = 1;

    while (std::getline(std::cin, line))
    {
        if (line == ";;")
            break ;
        validateLineAndPush(line, line_number);
        ++line_number;
    }

    if (line_number == 1)
    {
        throw LexerException("LexerException: No input provided");
    }
    if (!errors_.empty()) {
        throw LexerException(errors_.c_str());
    }
}

void Lexer::readFromFile(char* argv)
{
    std::cout << "reading from file" << std::endl;
    std::ifstream infile(argv);
    std::string line;
    int line_number = 1;

    while (std::getline(infile, line))
    {
        validateLineAndPush(line, line_number);
        ++line_number;
    }

    if (line_number == 1)
    {
        throw LexerException("LexerException: No input provided");
    }
}

void Lexer::validateLineAndPush(const std::string& line, int line_number)
{
    std::regex operation_no_args("^\\s*(pop|dump|add|sub|mul|div|mod|print|exit)\\s*(?:;.*)?$");
    std::regex operation_with_int("^\\s*(push|assert)\\s+(int8|int16|int32)\\(([-]?\\d+)\\)\\s*(?:;.*)?$");
    std::regex operation_with_float("^\\s*(push|assert)\\s+(float|double)\\(([-]?\\d+\\.\\d+)\\)\\s*(?:;.*)?$");
    std::regex comment("^\\s*(?:;.*){1}$");
    std::regex empty_line("^\\s*$");

    std::smatch line_match;
    if (regex_search(line, line_match, operation_no_args)) {
//        std::cout << "no_args" << std::endl;
        tokens_.push_back({line_match[1].str()});
    }
    else if (regex_search(line, line_match, operation_with_int) || regex_search(line, line_match, operation_with_float)) {
//        std::cout << "with_args" << std::endl;
        tokens_.push_back({line_match[1].str(), line_match[2].str(), line_match[3].str()});
    }
    else if (!regex_search(line, line_match, comment) && !regex_search(line, line_match, empty_line)) {
        addError(std::string("LexerException: Invalid line:") + std::to_string(line_number) + " " + line);
    }
    else {
        // do nothing
    }
}

void Lexer::addError(const std::string& error)
{
    if (errors_.empty()) {
        errors_ = error;
    }
    else {
        errors_ += "\n";
        errors_ += error;
    }
}

void Lexer::run()
{
    readInputFunction_();
    if (!errors_.empty()) {
        throw LexerException(errors_.c_str());
    }
}

const tTokens& Lexer::getTokens()
{
    return tokens_;
}
