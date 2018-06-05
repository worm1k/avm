#include "Operand.hpp"

template <class T>
Operand<T>::Operand(const std::string value, eOperandType type)
    : str_value_(value)
    , precision_(type)
    , type_(type)
{}

template <class T>
Operand<T>::~Operand()
{}

template <class T>
const IOperand* Operand<T>::operator+(IOperand const& obj) const
{
    (void)obj;
    return nullptr;
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
