#include "ExpressionBuilder.hpp"
#include "../Functions/FunctionModule.hpp"
#include <tuple>

double parseValue(Token & token)
{
    return std::strtod(token.value.c_str(), nullptr);
}

Expression * tokenToExpression(Token & token)
{
    switch (token.tokenType)
    {
        case TokenType::Literal:
            return new Expression(token.value);
        default:
            return new Expression(token.function);
    }
}

std::tuple<Expression *, int> buildExpressionRec(std::deque<Token> & postfix, int startIndex)
{
    Token currentToken = postfix[startIndex];
    Expression * currentExpression = tokenToExpression(currentToken);

    switch (currentExpression->function)
    {
        case Function::Identity:
            return std::make_tuple(currentExpression, startIndex - 1);
        default:
            int numOfArgs = numberOfArguments(currentExpression->function);
            currentExpression->arguments = std::vector<Expression *>(numOfArgs);
            int nextDequeIndex = startIndex - 1;
            for (int i = numOfArgs - 1; i >= 0; i--)
            {
                auto result = buildExpressionRec(postfix, nextDequeIndex);
                currentExpression->arguments[i] = std::get<0>(result);
                nextDequeIndex = std::get<1>(result);
            }
            return std::make_tuple(currentExpression, nextDequeIndex);
    }
}

Expression buildExpressionFromPostfix(std::deque<Token> postfix)
{
    return *(std::get<0>(buildExpressionRec(postfix, postfix.size() - 1)));
}