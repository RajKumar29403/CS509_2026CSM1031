# Matrix Multiplication using Simple GEMM and Blocked GEMM

## Overview

This project implements matrix multiplication using two different approaches in C++:

- **Simple GEMM** – Standard triple nested loop matrix multiplication.
- **Blocked GEMM** – Matrix multiplication using the blocking (tiling) technique to improve cache performance.

Both implementations generate the same output, while the blocked version is expected to perform better for larger matrices.

---

## Project Structure

| File | Description |
|------|-------------|
| `driver.cpp` | Reads input, executes both algorithms and measures execution time |
| `gemm.h` | Function declarations |
| `simple_gemm.cpp` | Standard matrix multiplication |
| `blocked_gemm.cpp` | Blocked (tiled) matrix multiplication |
| `Makefile` | Automates compilation and cleaning |
| `gemm_test_01.txt` | Small sample test case |
| `gemm_test_50x50.txt` | 50 × 50 matrix input |
| `gemm_test_256x256.txt` | 256 × 256 matrix input |
| `gemm_test_1000x1000.txt` | 1000 × 1000 matrix input |

---

## Compilation

### Using Makefile (Recommended)

Compile the project:

```bash
make
```

Clean generated files:

```bash
make clean
```

Rebuild the project:

```bash
make rebuild
```

---

### Manual Compilation

```bash
g++ -std=c++17 driver.cpp simple_gemm.cpp blocked_gemm.cpp -o gemm
```

---

## Running the Program

Execute:

```bash
./gemm
```

When prompted, enter the input file name.

Example:

```
Enter input file name:
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
- **K** = Number of columns in Matrix A (also rows in Matrix B)
- **N** = Number of columns in Matrix B

After that,

- Next **M** lines → Matrix **A**
- Next **K** lines → Matrix **B**

---

## Output

The program prints:

- Result matrix using Simple GEMM
- Execution time of Simple GEMM
- Result matrix using Blocked GEMM
- Execution time of Blocked GEMM

---

## Algorithm

### Simple GEMM

Uses the traditional three nested loops.

Time Complexity:

```
O(M × K × N)
```

---

### Blocked GEMM

The matrix is divided into smaller blocks (tiles). Each block is multiplied independently, which improves cache locality and reduces cache misses.

Advantages:

- Better cache utilization
- Reduced cache misses
- Improved performance for large matrices

Block Size Used:

```
32
```

---

## Test Cases

| Input File | Matrix Size |
|------------|------------:|
| `gemm_test_01.txt` | 2 × 3 × 2 |
| `gemm_test_50x50.txt` | 50 × 50 × 50 |
| `gemm_test_256x256.txt` | 256 × 256 × 256 |
| `gemm_test_1000x1000.txt` | 1000 × 1000 × 1000 |

---

## Performance Results

| Test Case | Matrix Size | Simple GEMM (µs) | Blocked GEMM (µs) |
|-----------|------------:|-----------------:|------------------:|
| Test 1 | 50 × 50 | 151 | 227 |
| Test 2 | 256 × 256 | 23023 | 21719 |
| Test 3 | 1000 × 1000 | 2072760  |  1258391 |

> Replace the above values with the execution times obtained on your system.

---

## Conclusion

Both implementations produce identical matrix multiplication results. The blocked implementation improves memory access patterns by processing smaller matrix blocks, resulting in better cache utilization and improved execution time for larger matrices. As the matrix size increases, the performance advantage of the blocked algorithm becomes more noticeable.