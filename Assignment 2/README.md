# CS509 Programming Assignment 2

## Overview

This repository contains the implementation of **Assignment 2** for CS509.

The assignment focuses on two shortest-path algorithms:

1. **Bellman-Ford Algorithm**
2. **Floyd-Warshall Algorithm**

The implementation also includes:

- Graph representation using an adjacency list
- Conversion of an adjacency list to **Compressed Sparse Row (CSR)** format
- Input file handling
- Random test-data generators
- Execution-time measurement
- Negative-cycle detection

> **Note:** Assignment 1 is intentionally not documented or included in the scope of this README.

---

## Project Structure

```text
Assignment 2/
│
├── include/
│   ├── graph.h
│   ├── csr.h
│   ├── bellman_ford.h
│   └── floyd_warshall.h
│
├── src/
│   ├── driver.cpp
│   ├── graph.cpp
│   ├── csr.cpp
│   ├── bellman_ford.cpp
│   └── floyd_warshall.cpp
│
├── generator/
│   ├── generate_bellman_ford.cpp
│   └── generate_floyd_warshall.cpp
│
├── input/
│   ├── bellman_ford/
│   │   ├── bf_10.txt
│   │   ├── bf_100.txt
│   │   ├── bf_10000.txt
│   │   ├── bf_50000.txt
│   │   └── bf_100000.txt
│   │
│   └── floyd_warshall/
│       ├── fw_10.txt
│       ├── fw_100.txt
│       ├── fw_500.txt
│       ├── fw_1000.txt
│       └── fw_2000.txt
│
├── Makefile
└── README.md
```

---

## Algorithms Implemented

### 1. Bellman-Ford

The Bellman-Ford algorithm is used to find the shortest distance from a given source vertex to all other vertices in a weighted directed graph.

It can handle **negative edge weights** and can also detect a reachable **negative-weight cycle**.

#### Main steps

1. Initialize the distance of the source vertex to `0`.
2. Initialize all other distances to `INF`.
3. Relax every edge `V-1` times.
4. If no update occurs during an iteration, the algorithm stops early.
5. Perform one additional pass over all edges.
6. If any distance can still be reduced, a negative-weight cycle exists.

#### Time Complexity

```text
O(VE)
```

where:

- `V` = number of vertices
- `E` = number of edges

The implementation uses CSR representation for efficient edge traversal.

---

### 2. Floyd-Warshall

The Floyd-Warshall algorithm calculates the shortest paths between **every pair of vertices**.

It uses dynamic programming and gradually allows each vertex to become an intermediate vertex.

The main update is:

```text
dist[i][j] = min(dist[i][j],
                 dist[i][k] + dist[k][j])
```

After the algorithm finishes, a negative value on the diagonal indicates a negative cycle:

```text
dist[i][i] < 0
```

#### Time Complexity

```text
O(V^3)
```

#### Space Complexity

```text
O(V^2)
```

---

## Graph Representation

### Adjacency List

Bellman-Ford input graphs are initially stored using an adjacency list.

Each edge contains:

```text
destination
weight
```

The graph structure stores:

- Number of vertices
- Number of edges
- Adjacency list

---

### CSR Representation

For Bellman-Ford, the adjacency list is converted into **Compressed Sparse Row (CSR)** format.

CSR contains three arrays:

```text
row_ptr
col_idx
values
```

For a vertex `u`, its outgoing edges are stored between:

```text
row_ptr[u]
```

and

```text
row_ptr[u + 1]
```

This provides compact storage and efficient sequential traversal of graph edges.

---

## Input File Formats

### Bellman-Ford Input

The Bellman-Ford input file follows this format:

```text
V E
vertex degree neighbour weight neighbour weight ...
...
SOURCE source_vertex
```

Example:

```text
4 5
0 2 1 5 2 3
1 1 3 2
2 1 3 4
3 1 0 1
SOURCE 0
```

Here:

- `V` is the number of vertices.
- `E` is the number of edges.
- Each vertex line contains its vertex number, degree, and destination-weight pairs.
- The final line specifies the source vertex.

---

### Floyd-Warshall Input

The Floyd-Warshall input file contains a square adjacency matrix.

Example:

```text
4
0 5 3 INF
INF 0 2 6
INF INF 0 4
INF INF INF 0
```

`INF` represents that there is no direct edge between the corresponding vertices.

---

## Test Cases

### Bellman-Ford

The following test files are provided:

| File | Vertices | Target Edges |
|---|---:|---:|
| `bf_10.txt` | 10 | 20 |
| `bf_100.txt` | 100 | 300 |
| `bf_10000.txt` | 10,000 | 25,000 |
| `bf_50000.txt` | 50,000 | 120,000 |
| `bf_100000.txt` | 100,000 | 250,000 |

The test graphs contain positive and some negative edge weights.

The source vertex generated for these files is:

```text
0
```

---

### Floyd-Warshall

The following matrix sizes are provided:

| File | Vertices |
|---|---:|
| `fw_10.txt` | 10 |
| `fw_100.txt` | 100 |
| `fw_500.txt` | 500 |
| `fw_1000.txt` | 1,000 |
| `fw_2000.txt` | 2,000 |

The generated matrices contain:

- `0` on the diagonal
- `INF` where no direct edge exists
- Positive edge weights
- Some negative edge weights

The generated graphs use forward edges, so the generated test graphs do not intentionally create negative cycles.

---

## Input Generation

Two generator programs are included.

### Bellman-Ford Generator

File:

```text
generator/generate_bellman_ford.cpp
```

This program creates sparse directed graphs with different numbers of vertices and edges.

Compile and run it from the `Assignment 2` directory:

```bash
g++ -std=c++17 generator/generate_bellman_ford.cpp -o genBF
./genBF
```

The generated files are placed in:

```text
input/bellman_ford/
```

---

### Floyd-Warshall Generator

File:

```text
generator/generate_floyd_warshall.cpp
```

Compile and run:

```bash
g++ -std=c++17 generator/generate_floyd_warshall.cpp -o genFW
./genFW
```

The generated files are placed in:

```text
input/floyd_warshall/
```

---

## Compilation

The project uses a `Makefile`.

From the project root, run:

```bash
make
```

This compiles the Assignment 2 source files and creates the executable:

```text
cs509
```

To remove the executable:

```bash
make clean
```

To clean and compile again:

```bash
make rebuild
```

### Windows

If `make` is available through MinGW/MSYS, the same commands can be used.

Alternatively, the Assignment 2 source files can be compiled manually using:

```bash
g++ -std=c++17 -Wall main.cpp ^
"Assignment 2/src/driver.cpp" ^
"Assignment 2/src/graph.cpp" ^
"Assignment 2/src/csr.cpp" ^
"Assignment 2/src/bellman_ford.cpp" ^
"Assignment 2/src/floyd_warshall.cpp" ^
-I"Assignment 2/include" -o cs509
```

---

## Running the Program

Run the executable:

```bash
./cs509
```

On Windows:

```text
cs509.exe
```

The Assignment 2 menu is:

```text
==============================
1. Bellman-Ford
2. Floyd-Warshall
==============================
Enter your choice :
```

Select:

```text
1
```

for Bellman-Ford, or:

```text
2
```

for Floyd-Warshall.

The program then asks for the input file.

### Bellman-Ford example

Enter:

```text
1
```

Then enter:

```text
input/bellman_ford/bf_10.txt
```

The program displays:

- Source vertex
- Shortest distance to every vertex
- Negative-cycle status
- Execution time

### Floyd-Warshall example

Enter:

```text
2
```

Then enter:

```text
input/floyd_warshall/fw_10.txt
```

The program displays:

- Final all-pairs distance matrix
- Negative-cycle status
- Execution time

---

## Negative Cycle Detection

### Bellman-Ford

After the normal `V-1` relaxation rounds, all edges are checked one more time.

If a distance can still be reduced:

```text
Negative cycle : true
```

Otherwise:

```text
Negative cycle : none
```

### Floyd-Warshall

After all intermediate vertices have been processed, the diagonal elements are checked.

If:

```text
dist[i][i] < 0
```

for any vertex `i`, the graph contains a negative cycle.

---

## Execution Time

The program measures only the execution of the main shortest-path algorithm using C++'s:

```cpp
high_resolution_clock
```

The time is reported in:

```text
microseconds
```

For Bellman-Ford, graph reading and CSR conversion are performed before the timer starts.

For Floyd-Warshall, the input matrix is read before the timer starts.

This allows the reported time to focus on the algorithm execution.

---

## Execution Time Results

Record the execution time obtained after running each test case.

### Bellman-Ford Execution Time

| Input File | Vertices (V) | Edges (E) | Execution Time (µs) |
|---|---:|---:|---:|
| `bf_10.txt` | 10 | 20 | 6 |
| `bf_100.txt` | 100 | 300 | 1945 |
| `bf_10000.txt` | 10,000 | 25,000 | 24621 |
| `bf_50000.txt` | 50,000 | 120,000 | 445958153 |
| `bf_100000.txt` | 100,000 | 250,000 | 1609746215 |

### Floyd-Warshall Execution Time

| Input File | Vertices (V) | Execution Time (µs) |
|---|---:|---:|
| `fw_10.txt` | 10 | 16 |
| `fw_100.txt` | 100 | 10681 |
| `fw_500.txt` | 500 | 1365343 |
| `fw_1000.txt` | 1,000 | 10946355 |
| `fw_2000.txt` | 2,000 | 86377382 |

> **Note:** Fill in the execution-time values after running the program. The reported values should be taken directly from the program output and should be recorded in microseconds (µs).

---

## Source Files

### `driver.cpp`

Provides the Assignment 2 user interface and connects the input, graph representation, algorithms, and timing functionality.

### `graph.cpp`

Handles reading:

- Bellman-Ford adjacency-list input
- Floyd-Warshall adjacency-matrix input

### `csr.cpp`

Converts the adjacency-list representation into CSR format.

### `bellman_ford.cpp`

Contains the Bellman-Ford shortest-path implementation and negative-cycle detection.

### `floyd_warshall.cpp`

Contains the Floyd-Warshall all-pairs shortest-path implementation and negative-cycle detection.

---

## Complexity Comparison

| Algorithm | Problem | Time Complexity | Space Complexity |
|---|---|---|---|
| Bellman-Ford | Single-source shortest path | `O(VE)` | `O(V + E)` |
| Floyd-Warshall | All-pairs shortest path | `O(V^3)` | `O(V^2)` |

Bellman-Ford is more suitable for sparse graphs when shortest paths from a single source are required.

Floyd-Warshall is useful when shortest paths between all pairs of vertices are required, especially for smaller or moderate graph sizes.

---

## Notes

- Vertex numbering starts from `0`.
- `INF` is internally represented by `1000000000`.
- Negative edge weights are supported.
- Negative cycles are detected by both algorithms.
- Bellman-Ford uses CSR for edge traversal.
- Execution time is reported in microseconds.
- Assignment 1 is outside the scope of this README.
