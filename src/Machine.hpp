#ifndef MACHINE_HPP
#define MACHINE_HPP

#include <deque>
#include <map>

#include "Lexer.hpp"
#include "IOperand.hpp"

class Machine
{
public:
    Machine(const tTokens& tokens);
    void run();

    Machine()                                = delete;
    Machine(const Machine&)                  = delete;
    const Machine& operator=(const Machine&) = delete;

private:
    void push();
    void pop();
    void dump();
    /* ... */

    const tTokens& tokens_;
    std::deque<const IOperand*> deque_;
    std::map<std::string, eOperandType> types_map_;

};

#endif // MACHINE_HPP
