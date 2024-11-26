#pragma once

#include "../Expressions/Expression.hpp"

int precedence(Function func);

int numberOfArguments(Function func);

bool leftAssociative(Function func);

/* Check if String is in the known list of functions. If not, return the Identity function */
Function stringToFunction(std::string input);