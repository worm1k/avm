
#include "Lexer.hpp"
#include "LexerException.hpp"
#include "Parser.hpp"

#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    try {
        Lexer lexer(argc, argv);
        lexer.run();
        Parser parser(lexer.getTokens());
        parser.run();
    } catch (const LexerException& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}