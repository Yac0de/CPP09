#include "RPN.hpp"

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <expression>" << std::endl;
        return 1;
    }

    try
    {
        RPN rpn(argv[1]);
        rpn.handleExpression();
        std::cout << rpn.getResult() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
