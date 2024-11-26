#pragma once

#include "../Functions/Function.hpp"
#include <vector>
#include <string>

class Expression
{
    public:
        Function function;
        std::string value;
        std::vector<Expression *> arguments;

        Expression();
        Expression(Function function);
        Expression(std::string value);
};