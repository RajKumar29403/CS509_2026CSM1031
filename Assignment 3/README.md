## CS509 Assignment 3 — Minimum Spanning Tree (MST)

## Overview

Assignment 3 implements two Minimum Spanning Tree algorithms for an undirected weighted graph:

1. **Kruskal's Algorithm**
2. **Prim's Algorithm**

The program can run either algorithm individually or run both algorithms and compare their MST results.

The Assignment 3 implementation reuses the graph and CSR representations from Assignment 2.

---

## Objectives

The main objectives of Assignment 3 are:

- Implement Kruskal's MST algorithm.
- Implement Prim's MST algorithm.
- Use the existing graph representation from Assignment 2.
- Use CSR (Compressed Sparse Row) representation for efficient graph traversal.
- Compare the total MST weight produced by both algorithms.
- Measure and report algorithm execution time.
- Test the implementation on graphs of different sizes.

---

## Folder Structure

```text
CS509_2026CSM1031/
└── Assignment 3/
    ├── generator_mst.cpp
    │
    ├── include/
    │   └── mst.h
    │
    ├── input/
    │   └── mst/
    │       ├── mst_10.txt
    │       ├── mst_100.txt
    │       ├── mst_10000.txt
    │       ├── mst_50000.txt
    │       └── mst_100000.txt
    │
    └── src/
        ├── driver.cpp
        └── mst.cpp
```

Assignment 3 uses the following files from Assignment 2:

```text
Assignment 2/include/graph.h
Assignment 2/include/csr.h
Assignment 2/src/graph.cpp
Assignment 2/src/csr.cpp
```

---

## Algorithms

### 1. Kruskal's Algorithm

Kruskal's algorithm sorts all graph edges according to their weights and then adds the smallest edge that does not create a cycle.

A **Disjoint Set Union (DSU)** data structure is used for cycle detection.

### Main steps

1. Collect all undirected edges.
2. Sort the edges by increasing weight.
3. Initialize a DSU structure.
4. Process edges in sorted order.
5. Add an edge if its endpoints belong to different sets.
6. Stop when `V - 1` edges have been selected.

### Complexity

```text
Time Complexity:  O(E log E)
Space Complexity: O(V + E)
```

---

### 2. Prim's Algorithm

Prim's algorithm starts from vertex `0` and repeatedly selects the minimum-weight edge that connects a vertex already in the MST to a vertex outside the MST.

A priority queue is used to select the minimum-weight edge efficiently.

### Main steps

1. Start from vertex `0`.
2. Assign its minimum connection weight as `0`.
3. Insert it into the priority queue.
4. Select the minimum-weight available vertex.
5. Add its connecting edge to the MST.
6. Update the neighbouring vertices.
7. Continue until all reachable vertices are included.

### Complexity

With a priority queue and adjacency/CSR representation:

```text
Time Complexity:  O(E log V)
Space Complexity: O(V + E)
```

---

## Graph Representation

The input graph is first stored using an adjacency list.

Each edge stores:

```text
destination
weight
```

For Assignment 3, the adjacency list is converted into CSR format before running the MST algorithms.

CSR contains:

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

This provides compact storage and efficient sequential traversal.

---

## Input Files

The input files are generated using:

```text
Assignment 3/generator_mst.cpp
```

The generator creates graphs with:

| Input File | Vertices (V) | Edges (E) |
|---|---:|---:|
| `mst_10.txt` | 10 | 20 |
| `mst_100.txt` | 100 | 200 |
| `mst_10000.txt` | 10,000 | 20,000 |
| `mst_50000.txt` | 50,000 | 100,000 |
| `mst_100000.txt` | 100,000 | 200,000 |

The generator uses a fixed random seed, so the generated test data is reproducible.

The generated graphs are undirected and connected. Edge weights are positive integers in the range:

```text
1 to 100
```

---

## Input File Format

Each MST input file follows this format:

```text
V E
vertex degree neighbour weight neighbour weight ...
...
```

For example:

```text
4 4
0 2 1 5 3 2
1 2 0 5 2 4
2 2 1 4 3 3
3 2 0 2 2 3
```

Where:

- `V` = number of vertices.
- `E` = number of undirected edges.
- `vertex` = vertex number.
- `degree` = number of neighbours.
- Each neighbour is followed by its edge weight.

---

## Generating Input Files

From the project root:

```powershell
g++ -std=c++17 "Assignment 3/generator_mst.cpp" -o "generator_mst.exe"
```

Run:

```powershell
.\generator_mst.exe
```

The generated files are placed in:

```text
Assignment 3/input/mst/
```

---

## Program Menu

When Assignment 3 is selected, the following menu is displayed:

```text
=====================================
          Assignment 3 - MST
=====================================
1. Kruskal's Algorithm
2. Prim's Algorithm
3. Run Both Algorithms
=====================================
Enter your choice:
```

### Input File Menu

After selecting an algorithm:

```text
=====================================
           Select Input File
=====================================
1. MST - 10 vertices
2. MST - 100 vertices
3. MST - 10000 vertices
4. MST - 50000 vertices
5. MST - 100000 vertices
6. Back to Main Menu
=====================================
Enter your choice:
```

The input file path is selected automatically using a switch statement. Therefore, the user does not need to manually type the input-file path.

For example, selecting:

```text
4
```

automatically loads:

```text
Assignment 3/input/mst/mst_50000.txt
```

Selecting:

```text
6
```

returns from Assignment 3 to the main program menu.

---

## Running Both Algorithms

When option `3` is selected, both Kruskal's and Prim's algorithms are executed.

The program displays:

- MST edges
- Total MST weight
- Execution time for Kruskal
- Execution time for Prim
- Comparison of the total MST weights
- PASS/FAIL status

The two algorithms should produce the same total MST weight for the same connected graph.

Example comparison:

```text
=====================================
           MST Comparison
=====================================
Kruskal total weight: ...
Prim total weight:    ...

Total weights equal: Yes
Status: PASS

Kruskal execution time: ... ms
Prim execution time:    ... ms
```

---

## Execution Time Measurement

Execution time is measured using C++:

```cpp
high_resolution_clock
```

The timer starts immediately before the MST algorithm is called and stops immediately after it returns.

Graph input and CSR conversion are performed before the timer starts.

The reported execution time therefore measures the MST algorithm itself rather than file reading and graph conversion.

The program reports execution time in:

```text
milliseconds (ms)
```

---

## Execution Time Table

Record the execution times obtained on your system after running each test case.

### Kruskal and Prim

| Test Case | Input File | Vertices (V) | Edges (E) | Kruskal Time (ms) | Prim Time (ms) |
|---|---|---:|---:|---:|---:|
| 1 | `mst_10.txt` | 10 | 20 | 0 | 0 |
| 2 | `mst_100.txt` | 100 | 200 | 1.067 | 0 |
| 3 | `mst_10000.txt` | 10,000 | 20,000 | 8.995 | 15 |
| 4 | `mst_50000.txt` | 50,000 | 100,000 | 32.588 | 86.877 |
| 5 | `mst_100000.txt` | 100,000 | 200,000 | 62.814 | 184.273 |

### Optional Run-Both Record

If option `3` (Run Both Algorithms) is used, the same execution times can be recorded here:

| Test Case | Input File | Kruskal Time (ms) | Prim Time (ms) | MST Weight Equal? | Status |
|---|---|---:|---:|---|---|
| 1 | `mst_10.txt` | 0 | 0 | Yes | PASS |
| 2 | `mst_100.txt` | 1.067 | 0 | Yes | PASS |
| 3 | `mst_10000.txt` | 8.995 | 15 | Yes | PASS |
| 4 | `mst_50000.txt` | 32.588 | 86.877 | Yes | PASS |
| 5 | `mst_100000.txt` | 62.814 | 184.273 | Yes | PASS |

---

## Compilation

### Compile Assignment 3 with the complete project

From the `CS509_2026CSM1031` project root:

```powershell
g++ -std=c++17 -Wall main.cpp `
"Assignment 1/driver.cpp" `
"Assignment 1/simple_gemm.cpp" `
"Assignment 1/blocked_gemm.cpp" `
"Assignment 2/src/driver.cpp" `
"Assignment 2/src/graph.cpp" `
"Assignment 2/src/csr.cpp" `
"Assignment 2/src/bellman_ford.cpp" `
"Assignment 2/src/floyd_warshall.cpp" `
"Assignment 3/src/driver.cpp" `
"Assignment 3/src/mst.cpp" `
-I"Assignment 1" `
-I"Assignment 2/include" `
-I"Assignment 3/include" `
-o cs509.exe
```

Run:

```powershell
.\cs509.exe
```

### Important

Run the executable from the:

```text
CS509_2026CSM1031
```

directory because the Assignment 3 input files use the relative path:

```text
Assignment 3/input/mst/
```

---

## Main Program Menu

The complete program provides:

```text
=====================================
      CS509 Programming Assignment
=====================================
1. Assignment 1
2. Assignment 2
3. Assignment 3
4. Exit
```

Select:

```text
3
```

to run Assignment 3.

---

## Source Files

### `Assignment 3/src/mst.cpp`

Contains:

- Kruskal's algorithm
- DSU implementation
- Prim's algorithm
- Priority queue based minimum-edge selection

### `Assignment 3/src/driver.cpp`

Contains:

- MST input-file reading
- Assignment 3 menu
- Input-file switch cases
- MST result printing
- Execution-time measurement
- Comparison of Kruskal and Prim results

### `Assignment 3/include/mst.h`

Contains:

- `MSTEdge`
- `MSTResult`
- Function declarations for Kruskal and Prim

### `Assignment 3/generator_mst.cpp`

Generates the five MST test cases.

---

## Correctness Verification

For every connected graph with `V` vertices, an MST must contain exactly:

```text
V - 1 edges
```

The program checks this condition after each algorithm.

When both algorithms are executed, their total MST weights are compared.

Expected result:

```text
Total weights equal: Yes
Status: PASS
```

This verifies that both implementations produced an MST with the same minimum total weight.

---

## Summary

Assignment 3 implements two classical MST algorithms using efficient graph representations:

| Algorithm | Main Technique | Time Complexity |
|---|---|---|
| Kruskal | Sorting + DSU | `O(E log E)` |
| Prim | Priority Queue + CSR | `O(E log V)` |

The implementation is tested on graphs ranging from:

```text
10 vertices
```

to:

```text
100,000 vertices
```

and provides execution-time measurements for performance comparison.
