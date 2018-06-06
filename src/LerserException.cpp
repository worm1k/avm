//
// Created by Artem Bykov on 5/31/18.
//

#include "LerserException.hpp"

LerserException::LerserException()
{}

LerserException::LerserException(const std::string& what_message)
    : what_message_(what_message)
{}

LerserException::LerserException(const LerserException& obj)
{
    *this = obj;
}

LerserException& LerserException::operator=(const LerserException& obj)
{
    if (this != &obj) {
        what_message_= obj.what_message_;
    }
    return *this;
}

const char* LerserException::what() const noexcept
{
    return what_message_.c_str();
}
