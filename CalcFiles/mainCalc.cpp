#include "Expressions/ExpressionModule.hpp"
#include "Parsing/TokenParser.hpp"
#include "Parsing/ExpressionBuilder.hpp"
#include "mainCalc.hpp"
#include <iostream>

using namespace std;

double mainCalc::getAnswer(string & input, CalculatorContext & context)
{
    Expression expression = buildExpressionFromPostfix(infixToPostfix(parse(input)));
    double answer = evaluate(expression, context);
    context.setValue("ans", answer);
    return answer;
}

double mainCalc::returnAns(string input){
    CalculatorContext whyisthissocomplicated = CalculatorContext();
    return getAnswer(input, whyisthissocomplicated);
}