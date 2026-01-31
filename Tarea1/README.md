# Array Sum with OpenMP

This C++ project demonstrates parallel array summation using OpenMP. It sums two integer arrays (A and B) element-wise to create a new array (C), dividing the work between two threads.

## Project Description

- **Array Size**: 10 elements
- **Arrays**: A, B (input), C (output where C[i] = A[i] + B[i])
- **Threading**: OpenMP with 2 threads
  - Thread 0: Processes indices 0-4 (first half)
  - Thread 1: Processes indices 5-9 (second half)

## Requirements

- C++ compiler with OpenMP support (GCC, Clang, or MSVC)
- OpenMP library (usually included with modern compilers)

## Compilation

### Using Makefile (Recommended)

```bash
make
```

### Manual Compilation

```bash
g++ -Wall -Wextra -std=c++11 -fopenmp -o array_sum main.cpp
```

**Note for macOS users**: If you encounter issues with OpenMP, you may need to install libomp:
```bash
brew install libomp
```
Then compile with:
```bash
g++ -Wall -Wextra -std=c++11 -Xpreprocessor -fopenmp -lomp -o array_sum main.cpp
```

## Running the Program

### Using Makefile

```bash
make run
```

### Direct Execution

```bash
./array_sum
```

## Output

The program will display:
- The contents of arrays A and B
- Which thread processes which indices
- The computation details for each element
- The final result array C

## Clean Build Artifacts

```bash
make clean
```

## Example Output

```
Array A: 1 2 3 4 5 6 7 8 9 10
Array B: 10 9 8 7 6 5 4 3 2 1
Thread 0 processing indices 0 to 4
Thread 1 processing indices 5 to 9
Thread 0: C[0] = 1 + 10 = 11
Thread 0: C[1] = 2 + 9 = 11
...
Result Array C: 11 11 11 11 11 11 11 11 11 11
```
