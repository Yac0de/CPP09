#include "RPN.hpp"

RPN::RPN() {}
RPN::RPN(const std::string &expression) : _expression(expression), _result(0) {}
RPN::RPN(const RPN &src) : _expression(src._expression), _result(src._result) {}
RPN::~RPN() {}

RPN& RPN::operator=(const RPN &rhs)
{
    if (this != &rhs)
        _result = rhs._result;
    return *this;
}

int RPN::getResult() const { return _result; }
void RPN::setResult(int result) { this->_result = result; }

void RPN::handleExpression()
{
    checkValidExpression();
    std::stack<int> stack;

    std::string remainingExpression = this->_expression;

    for (size_t i = 0; i < this->_expression.length(); ++i)
    {
        char token = this->_expression[i];
        if (std::isspace(token))
            continue;

        if (std::isdigit(token))
        {
            stack.push(token - '0');
            DEBUG_LOG(GREEN << "Pushed " << token << " to stack." << RESET);
        }
        else if (token == '+' || token == '-' || token == '*' || token == '/')
        {
            int operand2 = stack.top(); stack.pop();
            int operand1 = stack.top(); stack.pop();
            DEBUG_LOG(CYAN << "Popped operands: " << operand1 << " and " << operand2 << RESET);

            int result;
            switch (token)
            {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0)
                        throw std::invalid_argument("Error: Invalid expression: division by zero");
                    result = operand1 / operand2;
                    break;
            }

            stack.push(result);
#ifdef DEBUG
            DEBUG_LOG(MAGENTA << "Applied " << token << ": " << operand1 << " " << token << " " << operand2 << " = " << result << RESET);

            std::stringstream ss;
            ss << operand1 << " " << operand2 << " " << token;

            size_t pos = remainingExpression.find(ss.str());
            if (pos != std::string::npos)
            {
                std::stringstream resultStr;
                resultStr << result;
                remainingExpression.replace(pos, ss.str().length(), resultStr.str());
            }
            DEBUG_LOG(YELLOW << "Remaining expression: " << remainingExpression << RESET);
#endif
        }
    }
    setResult(stack.top());
    DEBUG_LOG(RED << "Final result: " << getResult() << RESET);
}

void RPN::checkValidExpression() const
{
    int operandCount = 0;

    for (size_t i = 0; i < this->_expression.length(); ++i)
    {
        char token = this->_expression[i];

        if (std::isspace(token))
            continue;

        if (std::isdigit(token))
        {
            if (i + 1 < this->_expression.length() && std::isdigit(this->_expression[i + 1]))
                throw std::invalid_argument("Error: Invalid number: " + std::string(1, token) + std::string(1, this->_expression[i + 1]) + " is greater than 9");
            operandCount++;
        }
        else if (token == '+' || token == '-' || token == '*' || token == '/')
        {
            if (operandCount < 2)
                throw std::invalid_argument("Error: Invalid expression: not enough operands for the operator " + std::string(1, token));
            operandCount--; 
        }
        else
            throw std::invalid_argument("Error: Invalid expression: unknown character " + std::string(1, token));
    }
    if (operandCount != 1)
        throw std::invalid_argument("Error: Invalid expression: the number of operands and operators does not match");
}
