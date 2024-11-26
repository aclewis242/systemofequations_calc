#include "TokenParser.hpp"
#include "../Functions/FunctionModule.hpp"

void handleFunction(deque<Token> & postfix, deque<Token> & operatorStack, Token token)
{
    if (!operatorStack.empty())
    {
        while (
            (precedence(operatorStack.front().function) > precedence(token.function)
            || (precedence(operatorStack.front().function) == precedence(token.function) 
                && leftAssociative(operatorStack.front().function))
            )
            && operatorStack.front().tokenType != TokenType::LeftParenthesis)
        {
            Token popped = operatorStack.front();
            operatorStack.pop_front();
            postfix.push_back(popped);

            if (operatorStack.empty())
            {
                break;
            }
        }
    }
    operatorStack.push_front(token);
}

void handleRightParenthesis(deque<Token> & postfix, deque<Token> & operatorStack, Token token)
{
    while (operatorStack.front().tokenType != TokenType::LeftParenthesis)
    {
        Token popped = operatorStack.front();
        operatorStack.pop_front();
        postfix.push_back(popped);
    }
    if (operatorStack.front().tokenType == TokenType::LeftParenthesis)
    {
        operatorStack.pop_front();
    }
}

deque<Token> infixToPostfix(deque<Token> infix)
{
    deque<Token> postfix;
    deque<Token> operatorStack;
    for (auto token : infix)
    {
        switch (token.tokenType)
        {
            case TokenType::Literal:
                postfix.push_back(token);
                break;
            case TokenType::Function:
                handleFunction(postfix, operatorStack, token);
                break;
            case TokenType::LeftParenthesis:
                operatorStack.push_front(token);
                break;
            case TokenType::RightParenthesis:
                handleRightParenthesis(postfix, operatorStack, token);
                break;
            default:
                break;
        }
    }
    while (!operatorStack.empty())
    {
        Token popped = operatorStack.front();
        operatorStack.pop_front();
        postfix.push_back(popped);
    }
    return postfix;
}