
#include "Lexer.hpp"
#include "LerserException.hpp"
#include "Machine.hpp"
#include "MachineException.hpp"
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
        Machine machine(lexer.getTokens());
        machine.run();
    } catch (const LerserException& e) {
        std::cout << e.what() << std::endl;
    } catch (const MachineException& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
