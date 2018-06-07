
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
    } catch (std::exception& e) {
        std::cout << std::endl << "*** " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Uncaught exception" << std::endl;
    }
    return 0;
}
