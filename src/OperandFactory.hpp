#ifndef OPERANDFACTORY_HPP
#define OPERANDFACTORY_HPP

#include "IOperand.hpp"
#include <string>

class OperandFactory
{
public:
    ~OperandFactory();
    static OperandFactory& getInstance();
    const IOperand* makeOperand(eOperandType type, const std::string& value) const;

    OperandFactory(const OperandFactory&)            = delete;
    OperandFactory& operator=(const OperandFactory&) = delete;

private:
    OperandFactory();

    const IOperand* (OperandFactory::*create_[5])(const std::string&) const;

    const IOperand* createInt8(const std::string& value) const;
    const IOperand* createInt16(const std::string& value) const;
    const IOperand* createInt32(const std::string& value) const;
    const IOperand* createFloat(const std::string& value) const;
    const IOperand* createDouble(const std::string& value) const;

};

#endif // OPERANDFACTORY_HPP
