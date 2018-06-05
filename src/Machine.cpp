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
{}

void Machine::run()
{
//    for (auto& elem : types_map_)
//    {
//        std::cout << elem.first << " " << elem.second << std::endl;
//    }
    for

}
