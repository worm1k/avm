//
// Created by Artem Bykov on 22.05.2018.
//

#ifndef AVM_LEXER_HPP
#define AVM_LEXER_HPP

#include <vector>
#include <string>

enum TokenType
{
};

class Lexer
{

public:
    Lexer(int argc, char** argv);
    ~Lexer();
    void run();

private:
    Lexer() = delete;
    Lexer(const Lexer& obj) = delete;
    Lexer& operator=(const Lexer& obj) = delete;

    void readFromConsole();
    void readFromFile(char** argv);
    void validateLine(const std::string& line, int line_number);
    void addError(const std::string& error);

    std::vector<std::vector<std::string>> tokens_;
    std::string errors_;

};

#endif //AVM_LEXER_HPP
