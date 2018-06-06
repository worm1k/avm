﻿
#include "MachineException.hpp"
#include "Operand.hpp"
#include "OperandFactory.hpp"

#include <algorithm>
#include <iostream>
#include <limits>

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
template <class Lambda>
const IOperand* Operand<T>::operation(IOperand const& x, IOperand const& y, Lambda func) const
{
    eOperandType type = std::max(x.getType(), y.getType());
    long double a = std::stold(x.toString().c_str(), nullptr);
    long double b = std::stold(y.toString().c_str(), nullptr);
    auto ldvalue = func(a, b);
    T min = std::numeric_limits<T>::min();
    T max = std::numeric_limits<T>::max();
    if (ldvalue < min || max < ldvalue) {
        throw MachineException("MachineException: operation result value if out of limits");
    }
    T tvalue = static_cast<T>(ldvalue);
    std::string svalue = std::to_string(tvalue);
    std::cout << "type :" << type << std::endl;
    std::cout << "value:" << svalue << std::endl;
    return OperandFactory::getInstance().makeOperand(type, svalue);
}

template <class T>
const IOperand* Operand<T>::operator+(IOperand const& obj) const
{
    return operation(*this, obj, [](long double a, long double b)
                                 -> long double {return a + b;});
}

template <class T>
const IOperand* Operand<T>::operator-(IOperand const& obj) const
{
    return operation(*this, obj, [](long double a, long double b)
                                 -> long double {return a - b;});
}

template <class T>
const IOperand* Operand<T>::operator*(IOperand const& obj) const
{
    return operation(*this, obj, [](long double a, long double b)
                                 -> long double {return a * b;});
}

template <class T>
const IOperand* Operand<T>::operator/(IOperand const& obj) const
{
    return operation(*this, obj, [](long double a, long double b)
                                 -> long double
        {
            if (b == 0) {
                throw MachineException("MachineException: division by zero");
            }
            return a / b;
        }
    );
}

template <class T>
const IOperand* Operand<T>::operator%(IOperand const& obj) const
{
    eOperandType type = std::max(getType(), obj.getType());
    if (type >= FLOAT) {
        throw MachineException("MachineException: modulo with float numbers is forbidden");
    }
    return operation(*this, obj, [](long double a, long double b)
                                 -> long long
        {
            if (b == 0) {
                throw MachineException("MachineException: modulo by zero");
            }
            return static_cast<long long>(a) % static_cast<long long>(b);
        }
    );
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
