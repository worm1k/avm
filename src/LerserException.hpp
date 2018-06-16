//
// Created by Artem Bykov on 5/31/18.
//

#ifndef AVM_LERSEREXCEPTION_HPP
#define AVM_LERSEREXCEPTION_HPP

#include <string>

class LerserException : public std::exception
{
public:
    LerserException(const std::string& what_message);
    const char* what() const noexcept;

    ~LerserException();
    LerserException();
    LerserException(const LerserException& obj);
    LerserException& operator=(const LerserException&);

private:
    std::string what_message_;

};

#endif //AVM_LERSEREXCEPTION_HPP
