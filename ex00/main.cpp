#include "BitcoinExchange.hpp"

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    try
    {
        BitcoinExchange exchange("data.csv");
        exchange.handleInputFile(argv[1]);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
