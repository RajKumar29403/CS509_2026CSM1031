# CS509 Programming Assignment 4

## Graph Analytics using CSR Representation


# 1. Overview

This assignment implements two graph analytics algorithms using the Compressed Sparse Row (CSR) graph representation.

Algorithms implemented:

1. Greedy Vertex Coloring (Welsh-Powell Ordering)
2. PageRank

The CSR representation is used to efficiently store sparse graphs and support scalable graph processing.

---

# 2. Objectives

The objectives of this assignment are:

- Understand CSR graph representation.
- Implement graph traversal using CSR.
- Implement Greedy Vertex Coloring.
- Implement PageRank with convergence checking.
- Measure execution time on graphs of different sizes.
- Verify correctness of generated results.

---

# 3. Folder Structure

```text
Assignment4/
│
├── include/
│   ├── csr_graph.h
│   ├── csr_converter.h
│   ├── vertex_coloring.h
│   ├── pagerank.h
│   └── driver.h
│
├── src/
│   ├── driver.cpp
│   ├── csr_converter.cpp
│   ├── vertex_coloring.cpp
│   └── pagerank.cpp
│
├── generator/
│   ├── generate_coloring_graph.cpp
│   └── generate_pagerank_graph.cpp
│
├── input/
│   ├── color_10.txt
│   ├── color_100.txt
│   ├── color_10000.txt
│   ├── color_50000.txt
│   ├── color_100000.txt
│   ├── pagerank_10.txt
│   ├── pagerank_100.txt
│   ├── pagerank_1000.txt
│   ├── pagerank_10000.txt
│   └── pagerank_50000.txt
│
└── README.md
```

---

# 4. CSR Graph Representation

The graph is stored using the Compressed Sparse Row (CSR) format.

## Components

### row_ptr

Stores the starting index of each vertex adjacency list.

### col_idx

Stores neighboring vertices sequentially.

Example:

```text
0 -> {1,2}
1 -> {2}
2 -> {0}
```

CSR:

```text
row_ptr = [0,2,3,4]
col_idx = [1,2,2,0]
```

Advantages:

- Reduced memory usage.
- Efficient traversal.
- Suitable for sparse graphs.

---

# 5. Algorithm 1: Vertex Coloring

## Description

A greedy Welsh-Powell based coloring algorithm is used.

Steps:

1. Compute degree of each vertex.
2. Sort vertices by decreasing degree.
3. Assign the smallest available color.
4. Continue until all vertices are colored.

## Output

- Color of each vertex.
- Total colors used.
- Coloring validity.
- Execution time.

## Complexity

```text
Degree Computation : O(V)
Sorting            : O(V log V)
Coloring           : O(V + E)

Overall            : O(V log V + E)
```

---

# 6. Algorithm 2: PageRank

## Description

PageRank estimates vertex importance using iterative rank propagation.

Features:

- Damping factor.
- Dangling node handling.
- Convergence checking.
- Maximum iteration limit.

## Parameters

```text
Damping Factor : 0.85
Tolerance      : 0.000001
Max Iterations : 100
```

## Output

- Rank of each vertex.
- Rank sum.
- Iterations performed.
- Convergence status.
- Execution time.

## Complexity

Per iteration:

```text
O(V + E)
```

For K iterations:

```text
O(K(V + E))
```

---

# 7. Input Format

## Vertex Coloring

```text
V E
vertex degree neighbor1 neighbor2 ...
vertex degree neighbor1 neighbor2 ...
...
```

Example:

```text
5 6
0 2 1 2
1 2 0 3
2 3 0 3 4
3 2 1 2
4 1 2
```

---

## PageRank

```text
V E
vertex degree neighbor1 neighbor2 ...
vertex degree neighbor1 neighbor2 ...
...

0.85
0.000001
100
```

---

# 8. Compilation

Using Makefile:

```bash
make clean
make
```

Direct Compilation:

```bash
g++ -std=c++17 -Wall -I"Assignment 1" -I"Assignment 2/include" -I"Assignment 3/include" -I"Assignment4/include" main.cpp "Assignment 1/driver.cpp" "Assignment 1/simple_gemm.cpp" "Assignment 1/blocked_gemm.cpp" "Assignment 2/src/driver.cpp" "Assignment 2/src/graph.cpp" "Assignment 2/src/csr.cpp" "Assignment 2/src/bellman_ford.cpp" "Assignment 2/src/floyd_warshall.cpp" "Assignment 3/src/driver.cpp" "Assignment 3/src/mst.cpp" "Assignment4/src/driver.cpp" "Assignment4/src/csr_converter.cpp" "Assignment4/src/vertex_coloring.cpp" "Assignment4/src/pagerank.cpp" -o cs509.exe
```

---

# 9. Program Execution

Run:

```bash
./cs509
```

Main Menu:

```text
1. Assignment 1
2. Assignment 2
3. Assignment 3
4. Assignment 4
5. Exit
```

Assignment 4 Menu:

```text
1. Vertex Coloring
2. PageRank
0. Back
```

---

# 10. Execution Time Measurement

Execution time is measured using:

```cpp
std::chrono::high_resolution_clock
```

Timing Method:

```cpp
auto start = high_resolution_clock::now();

/* Algorithm Execution */

auto stop = high_resolution_clock::now();

auto duration =
duration_cast<microseconds>(stop - start);
```

Execution time is reported in:

```text
Microseconds (µs)
```

Only the algorithm execution phase is measured.

---

# 11. Experimental Results

## Vertex Coloring

| Graph Size (Vertices) | Colors Used | Execution Time (µs) |
|----------------------|-------------|---------------------|
| 10 | 5 | 0 |
| 100 | 5 | 996 |
| 10,000 | 6 | 11059 |
| 50,000 | 6 | 54161 |
| 100,000 | 6 | 112000 |

---

## PageRank

| Graph Size (Vertices) | Iterations | Execution Time (µs) |
|----------------------|------------|---------------------|
| 10 | 16 | 0 |
| 100 | 18 | 0 |
| 1,000 | 19 | 998 |
| 10,000 | 19 | 9002 |
| 50,000 | 19 | 45245 |

---

# 12. Correctness Verification

## Vertex Coloring

The implementation verifies:

- Every vertex receives a valid color.
- Adjacent vertices do not share the same color.
- Total colors used are reported.

## PageRank

The implementation verifies:

- Rank values are non-negative.
- Rank sum is approximately 1.
- Convergence criteria are satisfied.
- Number of iterations is reported.

---

# 13. Source Files

## Header Files

```text
csr_graph.h
csr_converter.h
vertex_coloring.h
pagerank.h
driver.h
```

## Source Files

```text
driver.cpp
csr_converter.cpp
vertex_coloring.cpp
pagerank.cpp
```

---

# 14. Summary

This assignment demonstrates graph analytics using CSR representation.

The CSR format provides memory-efficient storage and enables efficient implementation of graph algorithms on large sparse graphs.

Both Vertex Coloring and PageRank were successfully implemented and evaluated using graphs of varying sizes while measuring execution time and validating correctness.
