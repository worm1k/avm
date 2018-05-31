//
// Created by Artem Bykov on 5/31/18.
//

#include "LexerException.hpp"
#include <iostream>

LexerException::LexerException(const char* what_message)
    : what_message_(what_message)
{}

const char* LexerException::what() const
{
    return what_message_.c_str();
}