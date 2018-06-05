#include "Operand.hpp"
#include "OperandFactory.hpp"

#include <algorithm>
#include <iostream>

template <class T>
Operand<T>::Operand(const std::string value, eOperandType type)
    : str_value_(value)
    , precision_(type)
    , type_(type)
{
}

template <class T>
Operand<T>::~Operand()
{}

template <class T>
const IOperand* Operand<T>::operator+(IOperand const& obj) const
{
    eOperandType type = std::max(getType(), obj.getType());
    long double a = std::strtold(toString().c_str(), nullptr);
    long double b = std::strtold(obj.toString().c_str(), nullptr);
    std::string value = std::to_string(a + b);
    std::cout << "type :" << type << std::endl;
    std::cout << "value:" << value << std::endl;
    // add limits check
    return OperandFactory::getInstance().makeOperand(type, value);
}

template <class T>
const IOperand* Operand<T>::operator-(IOperand const& obj) const
{
    (void)obj;
    return nullptr;
}

template <class T>
const IOperand* Operand<T>::operator*(IOperand const& obj) const
{
    (void)obj;
    return nullptr;
}

template <class T>
const IOperand* Operand<T>::operator/(IOperand const& obj) const
{
    (void)obj;
    return nullptr;
}

template <class T>
const IOperand* Operand<T>::operator%(IOperand const& obj) const
{
    (void)obj;
    return nullptr;
}

template <class T>
const std::string& Operand<T>::toString() const
{
    return str_value_;
}

template <class T>
int Operand<T>::getPrecision() const
{
    return precision_;
}

template <class T>
eOperandType Operand<T>::getType() const
{
    return type_;
}
