#pragma once
#include <iostream>
#include <cstdlib>
#include "Expressions/ExpressionModule.hpp"
#include "Parsing/TokenParser.hpp"
#include "Parsing/ExpressionBuilder.hpp"

using namespace std;

class mainCalc{
public:
	double getAnswer(string&, CalculatorContext&);
	double returnAns(string);
};
