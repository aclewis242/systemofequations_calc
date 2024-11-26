#include "Expression.hpp"

Expression::Expression()
{

}

Expression::Expression(Function function)
{
    this->function = function;
}

Expression::Expression(std::string value)
{
    this->function = Function::Identity;
    this->value = value;
}