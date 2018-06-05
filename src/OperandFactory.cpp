#include "OperandFactory.hpp"
#include "Operand.hpp"

OperandFactory::OperandFactory()
    : create_ {
          &OperandFactory::createInt8,
          &OperandFactory::createInt16,
          &OperandFactory::createInt32,
          &OperandFactory::createFloat,
          &OperandFactory::createDouble
      }
{}

OperandFactory::~OperandFactory()
{}

OperandFactory& OperandFactory::getInstance()
{
    static OperandFactory instance;
    return instance;
}

const IOperand* OperandFactory::makeOperand(eOperandType type, const std::string& value) const
{
    return (this->*create_[type])(value);
}

const IOperand* OperandFactory::createInt8(const std::string& value) const
{
    return new Operand<int8_t>(value, INT8);
}

const IOperand* OperandFactory::createInt16(const std::string& value) const
{
    return new Operand<int16_t>(value, INT16);
}

const IOperand* OperandFactory::createInt32(const std::string& value) const
{
    return new Operand<int32_t>(value, INT32);
}

const IOperand* OperandFactory::createFloat(const std::string& value) const
{
    return new Operand<float>(value, FLOAT);
}

const IOperand* OperandFactory::createDouble(const std::string& value) const
{
    return new Operand<double>(value, DOUBLE);
}

