//
// Created by Artem Bykov on 5/31/18.
//

#ifndef AVM_LEXEREXCEPTION_HPP
#define AVM_LEXEREXCEPTION_HPP

#include <string>

class LexerException
{

public:

    LexerException(const char* what_message);
    const char* what() const;

private:

    std::string what_message_;

};

#endif //AVM_LEXEREXCEPTION_HPP
