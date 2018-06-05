#ifndef IOPERAND_HPP
#define IOPERAND_HPP

#include <string>

enum eOperandType {
    INT8,
    INT16,
    INT32,
    FLOAT,
    DOUBLE
};

class IOperand
{
public:
    virtual ~IOperand() {}

    virtual const IOperand* operator+(IOperand const& rhs) const = 0;
    virtual const IOperand* operator-(IOperand const& rhs) const = 0;
    virtual const IOperand* operator*(IOperand const& rhs) const = 0;
    virtual const IOperand* operator/(IOperand const& rhs) const = 0;
    virtual const IOperand* operator%(IOperand const& rhs) const = 0;

    virtual const std::string& toString() const = 0;
    virtual int getPrecision() const = 0;
    virtual eOperandType getType() const = 0;
};

#endif // IOPERAND_HPP
