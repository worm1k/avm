#include "Machine.hpp"
#include "MachineException.hpp"
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
          {"pop", &Machine::pop},
          {"dump", &Machine::dump},
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
            // do nothing()
        }
        else {
            (this->*op_map_[line[0]])();
        }
    }
}

Machine::~Machine()
{
//    std::cout << "~Machine():" << std::endl;
    for (auto& ptr : deque_) {
        delete ptr;
    }
}

void Machine::push(const std::string& type, const std::string& value)
{
//    std::cout << "push " << type << " " << value << "\n";
    eOperandType etype = types_map_[type];
    deque_.push_back(OperandFactory::getInstance().makeOperand(etype, value));
}

void Machine::pop()
{
//    std::cout << "pop\n";
    if (deque_.size() == 0) {
        throw (MachineException("MachineException: pop on empty stack"));
    }
    auto a = *(deque_.end() - 1);
    deque_.pop_back();
    delete a;
}

void Machine::dump()
{
//    std::cout << "dump\n";
    for (auto it = deque_.rbegin(); it != deque_.rend(); ++it) {
        std::cout << (*it)->toString() << "\n";
    }
}

void Machine::assert(const std::string& type, const std::string& value)
{
//    std::cout << "assert " << type << " " << value << "\n";
    if (deque_.size() == 0) {
        throw (MachineException("MachineException: assert on empty stack"));
    }
    auto a = *(deque_.end() - 1);
    auto b = OperandFactory::getInstance().makeOperand(types_map_[type], value);
    if (a->getType() != b->getType() || a->toString() != b->toString()) {
        delete b;
        throw (MachineException("MachineException: assert failed"));
    }
    delete b;
}

void Machine::add()
{
//    std::cout << "add\n";
    if (deque_.size() < 2) {
        throw (MachineException("MachineException: add on less than 2 operands"));
    }
    auto b = *(deque_.end() - 1);
    auto a = *(deque_.end() - 2);
    auto res = *a + *b;
    deque_.pop_back();
    deque_.pop_back();
    delete a;
    delete b;
    deque_.push_back(res);
}

void Machine::sub()
{
//    std::cout << "sub\n";
    if (deque_.size() < 2) {
        throw (MachineException("MachineException: sub on less than 2 operands"));
    }
    auto b = *(deque_.end() - 1);
    auto a = *(deque_.end() - 2);
    auto res = *a - *b;
    deque_.pop_back();
    deque_.pop_back();
    delete a;
    delete b;
    deque_.push_back(res);
}

void Machine::mul()
{
//    std::cout << "mul\n";
    if (deque_.size() < 2) {
        throw (MachineException("MachineException: mul on less than 2 operands"));
    }
    auto b = *(deque_.end() - 1);
    auto a = *(deque_.end() - 2);
    auto res = *a * *b;
    deque_.pop_back();
    deque_.pop_back();
    delete a;
    delete b;
    deque_.push_back(res);
}

void Machine::div()
{
//    std::cout << "div\n";
    if (deque_.size() < 2) {
        throw (MachineException("MachineException: div on less than 2 operands"));
    }
    auto b = *(deque_.end() - 1);
    auto a = *(deque_.end() - 2);
    auto res = *a / *b;
    deque_.pop_back();
    deque_.pop_back();
    delete a;
    delete b;
    deque_.push_back(res);
}

void Machine::mod()
{
//    std::cout << "mod\n";
    if (deque_.size() < 2) {
        throw (MachineException("MachineException: mod on less than 2 operands"));
    }
    auto b = *(deque_.end() - 1);
    auto a = *(deque_.end() - 2);
    auto res = *a % *b;
    deque_.pop_back();
    deque_.pop_back();
    delete a;
    delete b;
    deque_.push_back(res);
}

void Machine::print()
{
//    std::cout << "print\n";
    if (deque_.size() == 0) {
        throw (MachineException("MachineException: print on empty stack"));
    }
    auto a = *(deque_.end() - 1);
    if (a->getPrecision() != INT8) {
        throw (MachineException("MachineException: print on non Int8 value"));
    }
    char c = static_cast<char>(std::stoi(a->toString().c_str()));
    if (32 <= c && c <= 126) {
        std::cout << c << std::endl;
    }
//    std::cout << "print:" << c << std::endl;
}

