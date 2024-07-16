#include "PmergeMe.hpp"

std::vector<int> parseArgs(int argc, const char* argv[]);

int main(int argc, const char* argv[])
{
    try
    {
        if (argc < 2)
        {
            std::cerr << "Usage: " << argv[0] << " <number1> <number2> ... <numberN>" << std::endl;
            return 1;
        }

        std::vector<int> numbers = parseArgs(argc, argv);

        PmergeMe sorter(numbers);

        std::cout << "Before: ";
        sorter.display(sorter.getVector());
        sorter.sortVector();
        sorter.sortDeque();
        std::cout << "After: ";
        sorter.display(sorter.getVector());
        sorter.displayTimes();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

std::vector<int> parseArgs(int argc, const char* argv[])
{
    std::vector<int> numbers;
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        char* end;
        long num = std::strtol(arg.c_str(), &end, 10);

        if (*end != '\0' || num < 0 || num > std::numeric_limits<int>::max())
            throw std::invalid_argument("Invalid number: " + arg);
        numbers.push_back(static_cast<int>(num));
    }
    return numbers;
}

