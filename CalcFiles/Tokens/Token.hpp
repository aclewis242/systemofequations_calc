#pragma once

#include "TokenType.hpp"
#include "../Functions/Function.hpp"
#include <string>

class Token
{
    public:
        std::string value;
        TokenType tokenType;
        Function function;

        Token(std::string value, TokenType tokenType, Function function);
};