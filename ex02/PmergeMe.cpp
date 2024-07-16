#include "PmergeMe.hpp"

PmergeMe::PmergeMe(const std::vector<int> &numbers)
    : _vector(numbers), _deque(numbers.begin(), numbers.end()), _vectorTime(0), _dequeTime(0) {}

PmergeMe::~PmergeMe() {}

const std::vector<int> & PmergeMe::getVector() const { return this->_vector; }
const std::deque<int> & PmergeMe::getDeque() const { return this->_deque; }

template <typename Container>
void PmergeMe::sort(Container &cont, double &time)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    fordJohnsonSort(cont);
    gettimeofday(&end, NULL);

    // Calculate the time in microseconds
    time = (end.tv_sec - start.tv_sec) * 1000000.0; // Convert seconds to microseconds
    time += (end.tv_usec - start.tv_usec); // Add the microseconds difference
}

void PmergeMe::sortVector() { sort(_vector, _vectorTime); }

void PmergeMe::sortDeque() { sort(_deque, _dequeTime); }

void PmergeMe::displayTimes() const
{
    std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector: "
              << _vectorTime << " us" << std::endl;
    std::cout << "Time to process a range of " << _deque.size() << " elements with std::deque: "
              << _dequeTime << " us" << std::endl;
}

template <typename Container>
void PmergeMe::fordJohnsonSort(Container &cont)
{
    int n = cont.size();
    if (n <= 1) return; // Base case for recursion

    std::vector<std::pair<typename Container::value_type, typename Container::value_type> > pairs;
    typename Container::value_type unpairedElement;

    // Step 1: Pairing the elements
#ifdef DEBUG
    std::cout << BLUE << "Pairs formed:" << RESET << " ";
#endif
    for (int i = 0; i < n - 1; i += 2)
    {
        pairs.push_back(std::make_pair(cont[i], cont[i + 1]));
#ifdef DEBUG
        std::cout << "(" << std::setw(2) << cont[i] << ", " << std::setw(2) << cont[i + 1] << ")";
        if (i + 2 < n - 1) std::cout << ", ";  // Add a comma except after the last pair
#endif
    }

    // Handle the unpaired element if n is odd
    if (n % 2 != 0)
    {
        unpairedElement = cont.back();
#ifdef DEBUG
        std::cout << " | Unpaired element: " << unpairedElement;
#endif
    }
#ifdef DEBUG
    std::cout << std::endl;
#endif

    // Step 2: Compare elements in each pair and separate max/min
    Container maxElements;
    Container minElements;

#ifdef DEBUG
    std::cout << GREEN << "Max elements:" << RESET << " ";
#endif
    for (size_t i = 0; i < pairs.size(); ++i)
    {
        if (pairs[i].first > pairs[i].second)
        {
            maxElements.push_back(pairs[i].first);
            minElements.push_back(pairs[i].second);
        }
        else
        {
            maxElements.push_back(pairs[i].second);
            minElements.push_back(pairs[i].first);
        }
#ifdef DEBUG
    std::cout << " " << std::left << std::setw(7) << maxElements.back();
    if (i != pairs.size() - 1) std::cout << ", ";
#endif
    }
#ifdef DEBUG
    std::cout << std::endl;
#endif

#ifdef DEBUG
    std::cout << YELLOW << "Min elements:" << RESET << " ";
    for (size_t i = 0; i < minElements.size(); ++i)
    {
        std::cout << " " << std::left << std::setw(7) << minElements[i];
        if (i != minElements.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
#endif

    // Step 3: Sort the max elements recursively to create the sequence S
    if (maxElements.size() > 1)
    {
        Container leftHalf(maxElements.begin(), maxElements.begin() + maxElements.size() / 2);
        fordJohnsonSort(leftHalf);

        Container rightHalf(maxElements.begin() + maxElements.size() / 2, maxElements.end());
        fordJohnsonSort(rightHalf);

#ifdef DEBUG
        std::cout << CYAN << "Merging leftHalf: " << RESET;
        for (size_t i = 0; i < leftHalf.size(); ++i)
        {
            std::cout << leftHalf[i];
            if (i != leftHalf.size() - 1) std::cout << ", ";
        }
        std::cout  << CYAN << " with rightHalf: "<< RESET;
        for (size_t i = 0; i < rightHalf.size(); ++i)
        {
            std::cout << rightHalf[i];
            if (i != rightHalf.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
#endif

        // Merge sorted halves in maxElements
        std::merge(leftHalf.begin(), leftHalf.end(), rightHalf.begin(), rightHalf.end(), maxElements.begin());

        // Delete duplicates after merging
        maxElements.erase(std::unique(maxElements.begin(), maxElements.end()), maxElements.end());
    }

    // Step 4: Insert the element paired with the smallest element at the correct position in S
    typename Container::value_type smallestElement = maxElements.front();  
    typename Container::value_type pairedElement = typename Container::value_type();

    for (size_t i = 0; i < pairs.size(); ++i)
    {
        if (pairs[i].first == smallestElement)
        {
            pairedElement = pairs[i].second;
            break;
        }
        if (pairs[i].second == smallestElement)
        {
            pairedElement = pairs[i].first;
            break;
        }
    }

#ifdef DEBUG
     std::cout << MAGENTA << "Inserting element paired with the smallest element (" 
              << RESET << smallestElement << MAGENTA << ") at the correct position in S: " << pairedElement << RESET << std::endl;
#endif

    // Find the correct position to insert to maintain sorted order
    typename Container::iterator pos = std::lower_bound(maxElements.begin(), maxElements.end(), pairedElement);
    if (pos == maxElements.end() || *pos != pairedElement)
        maxElements.insert(pos, pairedElement);

#ifdef DEBUG
    std::cout << GREEN << "Updated max elements (S): " << RESET;
    for (size_t i = 0; i < maxElements.size(); ++i)
    {
        std::cout << maxElements[i];
        if (i != maxElements.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
#endif

    // Step 5: Process the remaining elements that were not part of the initial max sequence
    Container remainingElements = minElements;
    if (n % 2 != 0)
        remainingElements.push_back(unpairedElement);

    // Remove elements already inserted into S
    for (typename Container::iterator it = remainingElements.begin(); it != remainingElements.end(); )
    {
        if (std::find(maxElements.begin(), maxElements.end(), *it) != maxElements.end())
            it = remainingElements.erase(it);
        else
            ++it;
    }

    // Step 5.1: Partition remaining elements into groups of powers of two
    std::vector<Container> groupedElements;

    size_t currentIndex = 0;
    int groupSize = 1;
    while (currentIndex < remainingElements.size())
    {
        Container group;
        for (int j = 0; j < groupSize && currentIndex < remainingElements.size(); ++j)
            group.push_back(remainingElements[currentIndex++]);
        groupedElements.push_back(group);
        groupSize *= 2; // Increase the group size to the next power of two
    }

#ifdef DEBUG
    // Display the grouped elements
    std::cout << BLUE << "Partitioned elements into groups: " << RESET << std::endl;
    for (size_t i = 0; i < groupedElements.size(); ++i) {
        std::cout << "Group " << i + 1 << " (size " << groupedElements[i].size() << "): ";
        for (size_t j = 0; j < groupedElements[i].size(); ++j) {
            std::cout << groupedElements[i][j];
            if (j != groupedElements[i].size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
#endif

    // Step 5.2: Sort the elements within each group in decreasing order by index
    for (size_t i = 0; i < groupedElements.size(); ++i)
    {
        std::sort(groupedElements[i].rbegin(), groupedElements[i].rend());

#ifdef DEBUG
        // Display the sorted group elements
        std::cout << YELLOW << "Sorted Group " << i + 1 << " in decreasing order: " << RESET;
        for (size_t j = 0; j < groupedElements[i].size(); ++j)
        {
            std::cout << groupedElements[i][j];
            if (j != groupedElements[i].size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
#endif
    }

    // Step 5.3: Insert each element into S using binary search
    for (size_t i = 0; i < groupedElements.size(); ++i)
    {
        for (size_t j = 0; j < groupedElements[i].size(); ++j)
        {
            typename Container::value_type elementToInsert = groupedElements[i][j];

            // Perform binary search to find the correct position
            typename Container::iterator pos = std::lower_bound(maxElements.begin(), maxElements.end(), elementToInsert);

            // Insert the element at the correct position if not already present
            if (pos == maxElements.end() || *pos != elementToInsert)
                maxElements.insert(pos, elementToInsert);

#ifdef DEBUG
            // Log the insertion
            std::cout << MAGENTA << "Inserted " << RESET << CYAN << elementToInsert << RESET << MAGENTA << " into S." << RESET << GREEN << std::endl << "Updated max elements (S): " << RESET;
            for (size_t k = 0; k < maxElements.size(); ++k)
            {
                if (maxElements[k] == elementToInsert)
                    std::cout << CYAN << maxElements[k] << RESET;
                else
                    std::cout << maxElements[k];
                if (k != maxElements.size() - 1)
                    std::cout << ", ";
            }
            std::cout << std::endl;
#endif
        }
    }

    // Update the original container with the sorted elements
    cont.assign(maxElements.begin(), maxElements.end());
}