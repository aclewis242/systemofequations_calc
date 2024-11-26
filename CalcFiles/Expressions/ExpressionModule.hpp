#pragma once

#include "Expression.hpp"
#include "../Context/CalculatorContext.hpp"

typedef double (* Evaluator) (Expression & toEvaluate, CalculatorContext & context);

double evaluate(Expression & expression, CalculatorContext & context);