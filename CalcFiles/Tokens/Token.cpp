#include "Token.hpp"

Token::Token(std::string value, TokenType tokenType, Function function)
{
    this->value = value;
    this->tokenType = tokenType;
    this->function = function;
}