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
        readFromConsole();
    }
    else if (argc == 2) {
        readFromFile(argv);
    }
    else {
        throw LexerException("LexerException: Invalid number of arguments");
    }
}

Lexer::~Lexer()
{}

void Lexer::readFromConsole()
{
    std::string line;
    int line_number = 1;

    while (std::getline(std::cin, line))
    {
        if (line == ";;")
            break ;
        validateLine(line, line_number);
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

void Lexer::readFromFile(char** argv)
{
    std::ifstream infile(argv[1]);
    std::string line;
    int line_number = 1;

    while (std::getline(infile, line))
    {
        validateLine(line, line_number);
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

void Lexer::validateLine(const std::string& line, int line_number)
{
    std::regex operation_no_args("^\\s*(pop|dump|add|sub|mul|div|mod|print|exit)\\s*(?:;.*)?$");
    std::regex operation_with_int("^\\s*(push|assert)\\s+(int8|int16|int32)\\(([-]?\\d+)\\)\\s*(?:;.*)?$");
    std::regex operation_with_float("^\\s*(push|assert)\\s+(float|double)\\(([-]?\\d+\\.\\d+)\\)\\s*(?:;.*)?$");
    std::regex comment("^\\s*(?:;.*){1}$");
    std::regex empty_line("^\\s*$");

    std::smatch line_match;
    if (regex_search(line, line_match, operation_no_args)) {
        tokens_.push_back({line_match[1].str()});
    }
    else if (regex_search(line, line_match, operation_with_int) || regex_search(line, line_match, operation_with_float)) {
        tokens_.push_back({line_match[1].str(), line_match[2].str(), line_match[3].str()});
    }
    else if (!regex_search(line, line_match, comment) && !regex_search(line, line_match, empty_line)) {
        addError(std::string("LexerException: Invalid line:") + std::to_string(line_number) + " " + line);
    }
    // else { do nothing }
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
    std::cout << "==============" << std::endl;
    std::cout << "Tokens output:" << std::endl;
    for (auto& line: tokens_)
    {
        for (auto& token: line) {
            std::cout << token << " ";
        }
        std::cout << std::endl;
    }
}