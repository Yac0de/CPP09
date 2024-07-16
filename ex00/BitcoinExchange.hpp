#ifndef BITCOIN_EXCHANGE_CPP
#define BITCOIN_EXCHANGE_CPP

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <limits>
#include <stdexcept>

class BitcoinExchange
{
private:
    BitcoinExchange();

    bool isValidDate(const std::string &date) const;
    std::map<std::string, float> fileToMap(const std::string &filename) const;
    std::map<std::string, float> _data;
public:
    BitcoinExchange(const std::string &filename);
    BitcoinExchange(const BitcoinExchange &src);
    ~BitcoinExchange();

    BitcoinExchange& operator=(const BitcoinExchange &rhs);

    void handleInputFile(const std::string &filename) const;
};

#endif
