
#include "MachineException.hpp"
#include "OperandFactory.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <map>

namespace {
std::map<eOperandType, long double> lowest {
    {INT8, std::numeric_limits<int8_t>::lowest()},
    {INT16, std::numeric_limits<int16_t>::lowest()},
    {INT32, std::numeric_limits<int32_t>::lowest()},
    {FLOAT, std::numeric_limits<float>::lowest()},
    {DOUBLE, std::numeric_limits<double>::lowest()},
};

std::map<eOperandType, long double> maxest {
    {INT8, std::numeric_limits<int8_t>::max()},
    {INT16, std::numeric_limits<int16_t>::max()},
    {INT32, std::numeric_limits<int32_t>::max()},
    {FLOAT, std::numeric_limits<float>::max()},
    {DOUBLE, std::numeric_limits<double>::max()},
};
}

template <class T>
Operand<T>::Operand(const std::string value, eOperandType type)
    : str_value_(value)
    , precision_(type)
    , type_(type)
{}

template <class T>
Operand<T>::~Operand()
{}

// fix T.
template <class T>
template <class Lambda>
const IOperand* Operand<T>::operation(IOperand const& x, IOperand const& y, Lambda func) const
{
    eOperandType type = std::max(x.getType(), y.getType());

    long double a = std::stold(x.toString());
    long double b = std::stold(y.toString());
    auto value = func(a, b);
    auto min = lowest[type];
    auto max = maxest[type];;
    if (value < min || max < value) {
        throw MachineException("MachineException: operation result value out of limits");
    }
//    T value = static_cast<T>(ldvalue);
//    std::string svalue = std::to_string(tvalue);
//    std::cout << "type :" << type << std::endl;
//    std::cout << "value:" << svalue << std::endl;
    return OperandFactory::getInstance().makeOperand(type, toString(type, value));
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
    return operation(*this, obj, [](long double a, long double b)
                                 -> long double
        {
            if (b == 0) {
                throw MachineException("MachineException: modulo by zero");
            }
            return std::fmod(a, b);
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

template<class T>
const std::string Operand<T>::toString(eOperandType type, long double value) const
{
    std::string res;

    switch (type) {
    case INT8:
    case INT16:
    case INT32:
        res = std::to_string(static_cast<int32_t>(value));
        break;
    case FLOAT:
        res = std::to_string(static_cast<float>(value));
        break;
    case DOUBLE:
    default:
        res = std::to_string(static_cast<double>(value));
    }
    // delete trailing zeros
    res.erase(res.find_last_not_of('0') + 1, std::string::npos);
    return res;
}
