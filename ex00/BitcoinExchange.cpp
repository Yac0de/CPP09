#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::BitcoinExchange(const std::string &filename) : _data(fileToMap(filename)) {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &src) : _data(src._data) {}
BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
    if (this != &rhs)
        _data = rhs._data;
    return *this;
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
    if(date.size() != 10)
        return false;
    for(int i = 0; i < 10; ++i)
    {
        if (i == 4 || i == 7)
        {
            if (date[i] != '-')
                return false;
        }
        else if (!std::isdigit(date[i]))
            return false;
    }

    int year, month, day;
    std::istringstream(date.substr(0, 4)) >> year;
    std::istringstream(date.substr(5, 2)) >> month;
    std::istringstream(date.substr(8, 2)) >> day;

    if (year < 1000 || year > 9999 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;

    if (month == 2)
    {
        /*Check if the year is a leap year.
        A year is a leap year if it meets the following conditions:
        1. The year is divisible by 4.
        2. However, if the year is divisible by 100, it is not a leap year,
           except if it is also divisible by 400.*/
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > 29 || (day == 29 && !isLeap))
            return false;
    }
    return true;
}

std::map<std::string, float> BitcoinExchange::fileToMap(const std::string &filename) const
{
    std::map<std::string, float> data;
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        throw std::runtime_error("Error: could not open file.");
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
    {
        size_t sep = line.find(",");
        if (sep == std::string::npos)
            throw std::runtime_error("Error: invalid format in data file => " + line);
        std::string date = line.substr(0, sep);
        std::string value_str = line.substr(sep + 1);
        if (!isValidDate(date))
            throw std::runtime_error("Error: invalid date format => " + date);
        std::istringstream iss(value_str);
        float value;
        iss >> value;
        if (iss.fail())
            throw std::runtime_error("Error: invalid value in data file => " + value_str);
        data[date] = value;
    }
    return data;
}

void BitcoinExchange::handleInputFile(const std::string &filename) const
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        throw std::runtime_error("Error: could not open file.");
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
    {
        size_t sep = line.find(" | ");
        if (sep == std::string::npos)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        std::string date = line.substr(0, sep);
        std::string value_str = line.substr(sep + 3);
        if (!isValidDate(date))
        {
            std::cerr << "Error: invalid date format => " << date << std::endl;
            continue;
        }
        std::istringstream iss(value_str);
        float value;
        iss >> value;
        if (iss.fail() || value > 1000 || value < 0)
        {
            if (value > 1000)
                std::cerr << "Error: too large a number." << std::endl;
            else if (value < 0)
                std::cerr << "Error: not a positive number." << std::endl;
            else
                std::cerr << "Error: invalid value." << std::endl;
            continue;
        }

        std::map<std::string, float>::const_iterator it = _data.lower_bound(date);
        if (it == _data.end() || it->first != date)
        {
            if (it == _data.begin())
            {
                std::cerr << "Error: no valid date found for " << date << std::endl;
                continue;
            }
            --it;
        }

        float exchangeRate = it->second;
        float result = value * exchangeRate;
        std::cout << date << " => " << value << " = " << result << std::endl;
    }
}