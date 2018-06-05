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
    void assert();
    void add();
    void sub();
    void mul();
    void div();
    void mod();
    void print();
    // void exit();

    const tTokens& tokens_;
    std::deque<const IOperand*> deque_;
    std::map<std::string, eOperandType> types_map_;
    std::map<std::string, void (Machine::*)()> op_map_;
    int i;

};

#endif // MACHINE_HPP
