# ZiaKhanCalculator

## Simple Build Instructions (as of 2019-10-17):

Build Cpp Files in this order:
```
Expressions/Expression.cpp
Functions/FunctionModule.cpp
Context/CalculatorContext.cpp
Expressions/ExpressionModule.cpp
Tokens/Token.cpp
Parsing/ParseInputToTokens.cpp
Parsing/InfixToPostfix.cpp
Parsing/ExpressionBuilder.cpp
main.cpp
```

## Sample main.cpp Code to test it out
```cpp
#include "Expressions/ExpressionModule.hpp"
#include "Parsing/TokenParser.hpp"
#include "Parsing/ExpressionBuilder.hpp"
#include <iostream>

using namespace std;

double getAnswer(string & input, CalculatorContext & context)
{
    Expression expression = buildExpressionFromPostfix(infixToPostfix(parse(input)));
    double answer = evaluate(expression, context);
    context.setValue("ans", answer);
    return answer;
}

int main(int, char**)
{
    CalculatorContext context = CalculatorContext();
    while (true)
    {
        string input;
        cout << "Enter an expression to evaluate:" << endl;
        getline(cin, input);
        if (input == "clear")
        {
            std::cout << "\x1B[2J\x1B[H";
            continue;
        }
        else if (input == "quit")
        {
            break;
        }
        std::cout << getAnswer(input, context) << endl;
    }
}
```

## How to add Functions
1. Add the function name to the enum in [Function.hpp](Functions/Function.hpp)

2. Add the string corresponding to the function enum in the map at the top of [FunctionModule.cpp](Functions/FunctionModule.cpp), along with the enum & corresponding values of whatever non-default attributes the function has (ex: 2 args instead of 1, etc.) in the corresponding function
 - ex: ``{"cos", Function::Cosine}``

 3. Modify [ExpressionModule.cpp](Expressions/ExpressionModule.cpp) with what the function does
  - ex: (in buildEvaluator function):
  ```cpp
    case Function::Cosine:
        return [](Expression & toEvaluate)
        {
            return std::cos(evaluate(*toEvaluate.arguments[0]));
        };
  ```
 
*Note: This aspect of the project was written in cooperation with classmates.*