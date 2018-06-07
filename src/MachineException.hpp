#ifndef MACHINEEXCEPTION_HPP
#define MACHINEEXCEPTION_HPP

#include <string>

class MachineException : public std::exception
{
public:
    MachineException(const std::string& what_message);
    const char* what() const noexcept;

    ~MachineException() noexcept;
    MachineException();
    MachineException(const MachineException& obj);
    MachineException& operator=(const MachineException&);

private:
    std::string what_message_;

};

#endif // MACHINEEXCEPTION_HPP
