# CPP Module 09 – Advanced STL, Parsing & Higher-Order Programming

## Table of Contents

1. [Project Overview](#project-overview)
2. [Key Concepts Introduced](#key-concepts-introduced)
   - [File Parsing & Data Mapping](#file-parsing--data-mapping)
   - [Stack-Based Expression Evaluation](#stack-based-expression-evaluation)
   - [Hybrid Sorting Algorithms](#hybrid-sorting-algorithms)
   - [Container-Specific Constraints](#container-specific-constraints)
3. [Exercise Breakdown](#exercise-breakdown)
   - [Ex00: Bitcoin Exchange](#ex00-bitcoin-exchange)
   - [Ex01: Reverse Polish Notation](#ex01-reverse-polish-notation)
   - [Ex02: PmergeMe](#ex02-pmergeme)
4. [Compiling and Running](#compiling-and-running)
5. [Conclusion](#conclusion)

---

## Project Overview

The final module of the C++ Piscine, CPP09 pushes your skills with **real-world STL use cases**:

- Efficient file parsing
- Runtime-safe data validation
- Expression evaluation with stack logic
- Performance measurement with custom sorting algorithms

You'll work with multiple STL containers under **strict reuse constraints**, making container choice a design decision.

---

## Key Concepts Introduced

### File Parsing & Data Mapping

- Use `std::map` or `std::unordered_map` to store and access data with timestamps.
- Validate CSV data structure and format.
- Retrieve closest lower-bound dates using map iterators.

### Stack-Based Expression Evaluation

- Use `std::stack` to evaluate postfix (Reverse Polish Notation) expressions.
- Handle operations `+ - * /` and error-checking for invalid tokens.
- Learn to parse and process command-line string expressions.

### Hybrid Sorting Algorithms

- Implement the **Ford-Johnson algorithm** (merge-insert sort): a fast sorting algorithm for large sets.
- Use **two different containers** (e.g., `std::deque` and `std::vector`) to compare performance.
- Time your implementation precisely and format readable output.

### Container-Specific Constraints

Each exercise restricts reuse of previously used containers:

- Carefully choose containers based on access, insertion, and iteration performance.
- Avoid accidental reuse: design your classes around allowed types.

---

## Exercise Breakdown

### Ex00: Bitcoin Exchange

**Goal:** Compute Bitcoin value for given dates using a CSV database.

**We learn:**

- Parsing external files (CSV and user input)
- Using `std::map` to store and retrieve time-series data
- Error handling and closest-date logic with `lower_bound()`

### Ex01: Reverse Polish Notation

**Goal:** Build a calculator that evaluates RPN expressions from a string.

**We learn:**

- Use of `std::stack` to store operands and apply operators
- Managing integer-only logic with custom error messages
- Safe parsing and edge case checks (underflow, malformed expression)

### Ex02: PmergeMe

**Goal:** Sort a sequence of positive integers using the Ford-Johnson algorithm.

**We learn:**

- Implementing a hybrid sort (merge + insert sort)
- Managing both `std::vector` and `std::deque`
- Measuring performance using `clock()` or `gettimeofday()`
- Displaying readable output for before/after sort and timing

**🔍 Understanding Ford-Johnson Sort:**
Also known as the **Merge-Insertion Sort**, this algorithm is particularly efficient for small to medium-sized sequences. It reduces the number of comparisons compared to traditional merge sort, especially in the worst case.

📖 Learn more: [Wikipedia - Merge-Insertion Sort](https://en.wikipedia.org/wiki/Merge-insertion_sort)

**🛠 DEBUG Mode Example:**
Running the program with `make DEBUG=1` enables a detailed trace of the sorting steps. Example output:

```
╰─ ./PmergeMe 9 5 3 7
Before: 9 5 3 7
Pairs formed: ( 9,  5), ( 3,  7)
Max elements:  9      ,  7
Min elements:  5      ,  3
Merging leftHalf: 9 with rightHalf: 7
Inserting element paired with the smallest element (7) at the correct position in S: 3
Updated max elements (S): 3, 7, 9
Partitioned elements into groups:
Group 1 (size 1): 5
Sorted Group 1 in decreasing order: 5
Inserted 5 into S.
Updated max elements (S): 3, 5, 7, 9
After: 3 5 7 9
Time to process a range of 4 elements with std::vector: 66 us
Time to process a range of 4 elements with std::deque: 160 us
```

These logs show:

- How elements are paired
- Which elements are sorted as the main chain (max values)
- How the remaining elements are grouped and reinserted using a binary search

**🔬 Step-by-Step Breakdown:**
Based on the [Wikipedia description](https://en.wikipedia.org/wiki/Merge-insertion_sort), the algorithm follows these steps:

1. Group elements into ⌊n/2⌋ pairs. If `n` is odd, one element remains unpaired.
2. Compare each pair and keep the larger value. This forms the candidate list for the main sorted sequence.
3. Recursively sort the larger values using the same algorithm.
4. Take the smaller value from the pair that includes the smallest sorted element and insert it at the beginning of the sorted list.
5. Group the remaining smaller values based on a Jacobsthal-like pattern: group sizes 2, 2, 6, 10, 22, etc.
6. Within each group, elements are inserted in **reverse** order.
7. Each element is inserted using **binary search** up to (but not including) its associated pair value in the sorted chain.

## Compiling and Running

### Debug Mode

Both `ex01` and `ex02` support a `DEBUG` flag in the Makefile. To enable debug output during execution (e.g., intermediate stack state or merge steps), compile with:

```sh
make DEBUG=1
```

This will define a `DEBUG` macro during compilation, enabling additional logging inside your code. It's a great way to trace execution while developing or troubleshooting.

1. Navigate to the desired directory:

```sh
cd ex02
```

2. Compile:

```sh
make
```

3. Run:

```sh
./PmergeMe 3 5 9 7 4
```

4. Clean:

```sh
make clean
make fclean
make re
```

---

## Conclusion

CPP09 puts everything you've learned to the test:

- Parsing, processing, and transforming real-world data
- Careful selection and use of STL containers
- Algorithmic reasoning for expression evaluation and sorting

This marks the end of the C++ Piscine. It helped us build solid foundations — a good starting point to keep improving in C++ development for those who wish to go further

