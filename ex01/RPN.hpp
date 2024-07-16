#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <stdexcept>

#ifdef DEBUG
    #include <sstream>
    #define DEBUG_LOG(x) do { std::cout << x << std::endl; } while (0)
#else
    #define DEBUG_LOG(x) do {} while (0)
#endif

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

class RPN
{
private:
    RPN();

    const std::string _expression;
    int _result;
public:
    RPN(const std::string &expression);
    RPN(const RPN &src);
    ~RPN();

    RPN& operator=(const RPN &rhs);

    int getResult() const;
    void setResult(int result);

    void handleExpression();
    void checkValidExpression() const;
};

#endif