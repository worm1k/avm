#include "Machine.hpp"
#include "OperandFactory.hpp"
#include "Operand.hpp"

#include <iostream>

Machine::Machine(const tTokens& tokens)
    : tokens_(tokens)
    , types_map_ {
          {"int8", INT8},
          {"int16", INT16},
          {"int32", INT32},
          {"float", FLOAT},
          {"double", DOUBLE}
      }
    , op_map_ {
          //{"push", &Machine::push},
          {"pop", &Machine::pop},
          {"dump", &Machine::dump},
          //{"assert", &Machine::assert},
          {"add", &Machine::add},
          {"sub", &Machine::sub},
          {"mul", &Machine::mul},
          {"div", &Machine::div},
          {"mod", &Machine::mod},
          {"print", &Machine::print}
      }
{}

void Machine::run()
{
    for (auto& line : tokens_) {
        if (line[0] == "push") {
            push(line[1], line[2]);
        }
        else if (line[0] == "assert") {
            assert(line[1], line[2]);
        }
        else if (line[0] == "exit"){
            // do nothing
        }
        else {
            (this->*op_map_[line[0]])();
        }
    }
}


void Machine::push(const std::string& type, const std::string& value)
{
    std::cout << "push " << type << " " << value << "\n";
    eOperandType etype = types_map_[type];
    deque_.push_back(OperandFactory::getInstance().makeOperand(etype, value));
}

void Machine::pop()
{
    std::cout << "pop\n";
}

void Machine::dump()
{
    std::cout << "dump\n";
    for (auto it = deque_.rbegin(); it != deque_.rend(); ++it) {
        std::cout << (*it)->toString() << "\n";
    }
}

void Machine::assert(const std::string& type, const std::string& value)
{
    std::cout << "assert " << type << " " << value << "\n";
}

void Machine::add()
{
    std::cout << "add\n";
    if (deque_.size() < 2) {
        //throw sth
    }
    auto a = *(deque_.end() - 1);
    auto b = *(deque_.end() - 2);
    deque_.pop_back();
    deque_.pop_back();
    deque_.push_back(*a + *b);
    delete a;
    delete b;
}

void Machine::sub()
{
    std::cout << "sub\n";
}

void Machine::mul()
{
    std::cout << "mul\n";
}

void Machine::div()
{
    std::cout << "div\n";
}

void Machine::mod()
{
    std::cout << "mod\n";
}

void Machine::print()
{
    std::cout << "print\n";
}

