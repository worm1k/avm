#include "MachineException.hpp"

MachineException::MachineException()
{}

MachineException::MachineException(const std::string& what_message)
    : what_message_(what_message)
{}

MachineException::MachineException(const MachineException& obj)
{
    *this = obj;
}

MachineException& MachineException::operator=(const MachineException& obj)
{
    if (this != &obj) {
        what_message_= obj.what_message_;
    }
    return *this;
}

const char* MachineException::what() const noexcept
{
    return what_message_.c_str();
}

