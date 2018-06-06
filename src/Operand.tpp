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
/*
try {
    long long time_ago = std::stoll(value);
    T min = std::numeric_limits<T>::min();
    T max = std::numeric_limits<T>::max();

    if (time_ago < min || max < time_ago) {
        errors_ += "ParserException: \"" + value + "\" is out of int8 boundaries.\n";
    }
} catch (std::invalid_argument& e) {
    this->errors_ += "std::invalid_argument Exception on value \"" + value +  "\": " + e.what();
} catch (std::out_of_range& e) {
    this->errors_ += "std::out_of_range: Exception on value \"" + value + "\": " + e.what();
}
*/
template <class T>
const IOperand* Operand<T>::operator+(IOperand const& obj) const
{
    eOperandType type = std::max(getType(), obj.getType());
    long double a = std::stold(toString().c_str(), nullptr);
    long double b = std::stold(obj.toString().c_str(), nullptr);
    long double ldvalue = a + b;
    T min = std::numeric_limits<T>::min();
    T max = std::numeric_limits<T>::max();
    if (ldvalue < min || max < ldvalue) {
        // throw "ParserException: \"" + value + "\" is out of int8 boundaries.\n";
    }
    T tvalue = static_cast<T>(ldvalue);
    std::string svalue = std::to_string(tvalue);
    std::cout << "type :" << type << std::endl;
    std::cout << "value:" << svalue << std::endl;
    return OperandFactory::getInstance().makeOperand(type, svalue);
}

template <class T>
const IOperand* Operand<T>::operator-(IOperand const& obj) const
{
    eOperandType type = std::max(getType(), obj.getType());
    long double a = std::stold(toString().c_str(), nullptr);
    long double b = std::stold(obj.toString().c_str(), nullptr);
    long double ldvalue = a - b;
    T min = std::numeric_limits<T>::min();
    T max = std::numeric_limits<T>::max();
    if (ldvalue < min || max < ldvalue) {
        // throw "ParserException: \"" + value + "\" is out of int8 boundaries.\n";
    }
    T tvalue = static_cast<T>(ldvalue);
    std::string svalue = std::to_string(tvalue);
    std::cout << "type :" << type << std::endl;
    std::cout << "value:" << svalue << std::endl;
    return OperandFactory::getInstance().makeOperand(type, svalue);
}

template <class T>
const IOperand* Operand<T>::operator*(IOperand const& obj) const
{
    eOperandType type = std::max(getType(), obj.getType());
    long double a = std::stold(toString().c_str(), nullptr);
    long double b = std::stold(obj.toString().c_str(), nullptr);
    long double ldvalue = a * b;
    T min = std::numeric_limits<T>::min();
    T max = std::numeric_limits<T>::max();
    if (ldvalue < min || max < ldvalue) {
        // throw "ParserException: \"" + value + "\" is out of int8 boundaries.\n";
    }
    T tvalue = static_cast<T>(ldvalue);
    std::string svalue = std::to_string(tvalue);
    std::cout << "type :" << type << std::endl;
    std::cout << "value:" << svalue << std::endl;
    return OperandFactory::getInstance().makeOperand(type, svalue);
}

template <class T>
const IOperand* Operand<T>::operator/(IOperand const& obj) const
{
    eOperandType type = std::max(getType(), obj.getType());
    long double a = std::stold(toString().c_str(), nullptr);
    long double b = std::stold(obj.toString().c_str(), nullptr);
    long double ldvalue = a / b;
    T min = std::numeric_limits<T>::min();
    T max = std::numeric_limits<T>::max();
    if (ldvalue < min || max < ldvalue) {
        // throw "ParserException: \"" + value + "\" is out of int8 boundaries.\n";
    }
    T tvalue = static_cast<T>(ldvalue);
    std::string svalue = std::to_string(tvalue);
    std::cout << "type :" << type << std::endl;
    std::cout << "value:" << svalue << std::endl;
    return OperandFactory::getInstance().makeOperand(type, svalue);
}

template <class T>
const IOperand* Operand<T>::operator%(IOperand const& obj) const
{
    eOperandType type = std::max(getType(), obj.getType());
    if (type >= FLOAT) {
        // throw
    }
    long long a = std::stoll(toString().c_str(), nullptr);
    long long b = std::stoll(obj.toString().c_str(), nullptr);
    long long ldvalue = a % b;
    T min = std::numeric_limits<T>::min();
    T max = std::numeric_limits<T>::max();
    if (ldvalue < min || max < ldvalue) {
        // throw "ParserException: \"" + value + "\" is out of int8 boundaries.\n";
    }
    T tvalue = static_cast<T>(ldvalue);
    std::string svalue = std::to_string(tvalue);
    std::cout << "type :" << type << std::endl;
    std::cout << "value:" << svalue << std::endl;
    return OperandFactory::getInstance().makeOperand(type, svalue);
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
