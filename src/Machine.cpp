#include "Machine.hpp"

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
          {"push", &Machine::push},
          {"pop", &Machine::pop},
          {"dump", &Machine::dump},
          {"assert", &Machine::assert},
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
//    for (auto& elem : types_map_)
//    {
//        std::cout << elem.first << " " << elem.second << std::endl;
//    }

}


void Machine::push()
{
    std::cout << "push\n";
}

void Machine::pop()
{
    std::cout << "pop\n";}

void Machine::dump()
{
    std::cout << "dump\n";
}

void Machine::assert()
{
    std::cout << "assert\n";
}

void Machine::add()
{
    std::cout << "add\n";
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

