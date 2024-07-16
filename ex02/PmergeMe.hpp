#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <iomanip>
#include <vector>
#include <deque>
#include <algorithm>
#include <ctime>
#include <limits>
#include <sys/time.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

class PmergeMe
{
private:
    std::vector<int> _vector;
    std::deque<int> _deque;
    double _vectorTime;
    double _dequeTime;

    template <typename Container>
    void sort(Container & cont, double & time);

    template <typename Container>
    void fordJohnsonSort(Container & cont);
public:
    PmergeMe(const std::vector<int> & numbers);
    ~PmergeMe();

    const std::vector<int> & getVector() const;
    const std::deque<int> & getDeque() const;

    void sortVector();
    void sortDeque();

    template <typename Container>
    void display(const Container & cont) const;
    void displayTimes() const;
};

template <typename Container>
void PmergeMe::display(const Container& cont) const
{
    for (size_t i = 0; i < cont.size(); ++i)
    {
        std::cout << cont[i];
        if (i != cont.size() - 1)
            std::cout << " ";
    }
    std::cout << std::endl;
}

#endif
