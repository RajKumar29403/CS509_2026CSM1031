# CS509_2026CSM1031
i did a change
i have added gemm.h file
i have added simple_gemm.cpp file
i have added blocked_gemm.cpp file

# Matrix Multiplication using Simple GEMM and Blocked GEMM

## Overview

This assignment implements two different approaches for matrix multiplication in C++:

1. **Simple GEMM** – Performs the standard matrix multiplication using three nested loops.
2. **Blocked GEMM** – Uses the blocking (tiling) technique to improve cache utilization and reduce execution time for larger matrices.

The program executes both implementations, prints the resulting matrices, and compares their execution times.

---

## Files Included

| File | Description |
|------|-------------|
| `driver.cpp` | Main program that reads input, calls both GEMM implementations, and measures execution time. |
| `gemm.h` | Header file containing function declarations. |
| `simple_gemm.cpp` | Standard matrix multiplication implementation. |
| `blocked_gemm.cpp` | Blocked (tiled) matrix multiplication implementation. |
| `gemm_test_01.txt` | Small sample input for testing correctness. |
| `gemm_test_50x50.txt` | 50 × 50 matrix input. |
| `gemm_test_256x256.txt` | 256 × 256 matrix input. |
| `gemm_test_1000x1000.txt` | 1000 × 1000 matrix input. |

---

## Compilation

Compile the program using g++:

```bash
g++ driver.cpp simple_gemm.cpp blocked_gemm.cpp -o gemm
```

---

## Running the Program

Run the executable:

```bash
./gemm
```

or on Windows:

```bash
gemm.exe
```

When prompted, enter the input file name.

Example:

```
Enter input file name :
gemm_test_50x50.txt
```

---

## Input Format

The first line contains:

```
M K N
```

where

- **M** = Number of rows in Matrix A
- **K** = Number of columns in Matrix A (and rows in Matrix B)
- **N** = Number of columns in Matrix B

The next **M** lines contain Matrix **A**, followed by **K** lines containing Matrix **B**.

---

## Output

The program displays:

- Result of Simple GEMM
- Execution time of Simple GEMM
- Result of Blocked GEMM
- Execution time of Blocked GEMM

This allows easy comparison of both implementations.

---

## Algorithm

### Simple GEMM

The simple implementation uses the traditional three nested loops.

```
for i
    for j
        for k
            C[i][j] += A[i][k] * B[k][j]
```

Time Complexity:

```
O(M × K × N)
```

---

### Blocked GEMM

The blocked implementation divides matrices into smaller blocks (tiles). Instead of processing the whole matrix at once, multiplication is performed block by block.

Advantages:

- Better cache utilization
- Reduced cache misses
- Faster execution for large matrices

The block size used in this assignment is **32**.

---

## Sample Test Files

The repository contains multiple test cases:

- Small matrix
- 50 × 50 matrix
- 256 × 256 matrix
- 1000 × 1000 matrix

These inputs can be used to observe the performance difference between the two implementations.

---

## Conclusion

This assignment demonstrates that while both algorithms produce the same output, the blocked GEMM implementation is generally more efficient for large matrices because it makes better use of the CPU cache. The performance improvement becomes more noticeable as the matrix size increases.