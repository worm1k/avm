//
// Created by Artem Bykov on 22.05.2018.
//

#include "Lexer.hpp"
#include "LerserException.hpp"

#include <sys/stat.h>
#include <iostream>
#include <regex>
#include <sstream>
#include <fstream>
#include <string>

Lexer::Lexer(int argc, char** argv)
{
    if (argc == 1) {
        readInputFunction_ = std::bind(&Lexer::readFromConsole, this);
    }
    else if (argc == 2) {
        if (std::string("--help") == argv[1]) {
            printUsageMessage();
            std::exit(1);
        }
        checkBullShit(argv[1]);
        readInputFunction_ = std::bind(&Lexer::readFromFile, this, argv[1]);
    }
    else {
        printUsageMessage();
        std::exit(1);
    }
}

Lexer::~Lexer()
{}

void Lexer::checkBullShit(const char* devzero)
{
    struct stat sb;

    if (stat(devzero, &sb) == 0 && S_ISREG(sb.st_mode)) {
        return ;
    }
    if (strstr(devzero, "/dev/")) {
        throw LerserException(std::string("EricException: Can not read from ") + devzero + ". Please, try to input it up your ass");
    } else {
        throw LerserException("LexerException: Please provide regular file as an input");
    }
}

void Lexer::printUsageMessage() {
    std::cout << "\033[0;32mThe program works either with no arguments (standard input with '\033[1;94m;;\033[0;32m' as the ending input) or with one argument (the file's name).\033[0m" << std::endl << std::endl;
    std::cout << "\033[1;95mcomments\033[0m: \033[0;32mComments start with a '\033[1;94m;\033[0;32m' symbol and end with a newline. A comment can be either at the start of a line or after an instruction.\033[0m" << std::endl << std::endl;
    std::cout << "\033[1;95mpush v\033[0m: \033[0;32mPushes the value \033[1;94mv\033[0m \033[0;32mat the top of the stack. The value \033[1;94mv\033[0m \033[0;32mmust have one of the following forms:\033[0m" << std::endl;
    std::cout << "\t\033[1;94mint8(n) : \033[0;32mCreates a 8-bit integer with the value \033[1;94mn\033[0m." << std::endl;
    std::cout << "\t\033[1;94mint16(n) : \033[0;32mCreates a 16-bit integer with the value \033[1;94mn\033[0m." << std::endl;
    std::cout << "\t\033[1;94mint32(n) : \033[0;32mCreates a 32-bit integer with the value \033[1;94mn\033[0m." << std::endl;
    std::cout << "\t\033[1;94mfloat(z) : \033[0;32mCreates a float with the value \033[1;94mz\033[0m." << std::endl;
    std::cout << "\t\033[1;94mdouble(z) : \033[0;32mCreates a double with the value \033[1;94mz\033[0m." << std::endl << std::endl;
    std::cout << "\033[1;95mpop\033[0m: \033[0;32mUnstacks the value from the top of the stack. \033[1;91m" << std::endl << "     If the stack is empty, the program execution stops with an error.\033[0m" << std::endl << std::endl;
    std::cout << "\033[1;95mdump\033[0m: \033[0;32mDisplays each value of the stack from the most recent one to the oldest one without changing the stack.\033[0m" << std::endl << std::endl;
    std::cout << "\033[1;95massert v\033[0m: \033[0;32mAsserts that the value at the top of the stack is equal to the one passed as the parameter for this instruction. \033[1;91m" << std::endl << "          If it is not - the program execution stops with an error.\033[0m" << std::endl << "          \033[0;32mThe value \033[1;94mv\033[0m \033[0;32mhas the same form that those passed as parameters to the command push.\033[0m" << std::endl << std::endl;
    std::cout << "\033[1;95madd\033[0m: \033[0;32mUnstacks the first two values in the stack, adds them together, and pushes the result on the stack. \033[1;91m" << std::endl << "     If there are less than 2 operands in the stack, the program execution stops with an error.\033[0m" << std::endl << std::endl;
    std::cout << "\033[1;95msub\033[0m: \033[0;32mUnstacks the first two values in the stack, subtracts them, and pushes the result on the stack. \033[1;91m" << std::endl << "     If there are less than 2 operands in the stack, the program execution stops with an error.\033[0m" << std::endl << std::endl;
    std::cout << "\033[1;95mmul\033[0m: \033[0;32mUnstacks the first two values in the stack, multiplies them, and pushes the result on the stack. \033[1;91m" << std::endl << "     If there are less than 2 operands in the stack, the program execution stops with an error.\033[0m" << std::endl << std::endl;
    std::cout << "\033[1;95mdiv\033[0m: \033[0;32mUnstacks the first two values in the stack, divides them, and pushes the result on the stack. \033[1;91m" << std::endl << "     If there are less than 2 operands in the stack or the divisor is equal to 0, the program execution stops with an error.\033[0m" << std::endl << std::endl;
    std::cout << "\033[1;95mmod\033[0m: \033[0;32mUnstacks the first two values in the stack, calculates the modulus, and pushes the result on the stack. \033[1;91m" << std::endl << "     If there are less than 2 operands in the stack or the divisor is equal to 0, the program execution stops with an error.\033[0m" << std::endl << std::endl;
    std::cout << "\033[1;95mprint\033[0m: \033[0;32mAsserts that the value at the top of the stack is a 8-bit integer (\033[1;91mif not, check the instructions for assert\033[0m\033[0;32m);" << std::endl << "       After that, it interprets it as an ASCII value and displays the corresponding character on the standard output.\033[0m" << std::endl << std::endl;
    std::cout << "\033[1;95mexit\033[0m: \033[0;32mTerminates the execution of the current program. \033[1;91m" << std::endl << "      There must be only one exit command and it must be located at the end of the input.\033[0m" << std::endl;
}

void Lexer::readFromConsole()
{
//    std::cout << "reading from console" << std::endl;
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
        throw LerserException("LexerException: No input provided");
    }
}

void Lexer::readFromFile(char* argv)
{
//    std::cout << "reading from file" << std::endl;
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
        throw LerserException("LexerException: No input provided");
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
        errors_ += "\n*** ";
        errors_ += error;
    }
}

void Lexer::run()
{
    readInputFunction_();
    if (!errors_.empty()) {
        throw LerserException(errors_);
    }
}

const tTokens& Lexer::getTokens()
{
    return tokens_;
}
