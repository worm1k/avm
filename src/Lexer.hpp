//
// Created by Artem Bykov on 22.05.2018.
//

#ifndef AVM_LEXER_HPP
#define AVM_LEXER_HPP

#include <vector>
#include <string>
#include <functional>

typedef std::vector<std::vector<std::string>> tTokens;

class Lexer
{

public:
    Lexer(int argc, char** argv);
    ~Lexer();
    void run();
    const tTokens& getTokens();

private:
    Lexer() = delete;
    Lexer(const Lexer& obj) = delete;
    Lexer& operator=(const Lexer& obj) = delete;

    void readFromConsole();
    void readFromFile(char* argv);
    void validateLineAndPush(const std::string& line, int line_number);
    void addError(const std::string& error);


    tTokens tokens_;
    std::string errors_;
    std::function<void()> readInputFunction_;


};

#endif //AVM_LEXER_HPP
