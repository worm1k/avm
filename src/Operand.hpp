#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "IOperand.hpp"

template <class T>
class Operand : public IOperand
{
public:

    Operand(const std::string value, eOperandType type);
    ~Operand();

    const IOperand* operator+(IOperand const& rhs) const;
    const IOperand* operator-(IOperand const& rhs) const;
    const IOperand* operator*(IOperand const& rhs) const;
    const IOperand* operator/(IOperand const& rhs) const;
    const IOperand* operator%(IOperand const& rhs) const;

    const std::string& toString() const;
    int getPrecision() const;
    eOperandType getType() const;

    Operand()                          = delete;
    Operand(const Operand&)            = delete;
    Operand& operator=(const Operand&) = delete;

private:
    const std::string str_value_;
    T num_value_;
    const int precision_;
    const eOperandType type_;
};

#include "Operand.tpp"

#endif // OPERAND_HPP
