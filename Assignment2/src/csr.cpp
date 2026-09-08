#include "../include/csr.h"

#include <iostream>

using namespace std;

void convertToCSR(Graph &graph, CSR &csr)
{
    csr.row_ptr.clear();
    csr.col_idx.clear();
    csr.values.clear();

    csr.row_ptr.push_back(0);

    for (int i = 0; i < graph.V; i++)
    {
        for (size_t j = 0; j < graph.adjList[i].size(); j++)
        {
            csr.col_idx.push_back(graph.adjList[i][j].dest);
            csr.values.push_back(graph.adjList[i][j].weight);
        }

        csr.row_ptr.push_back(csr.col_idx.size());
    }
}

void printCSR(CSR &csr)
{
    cout << "\nRow Pointer : ";

    for (int x : csr.row_ptr)
        cout << x << " ";

    cout << "\nColumn Index : ";

    for (int x : csr.col_idx)
        cout << x << " ";

    cout << "\nValues : ";

    for (int x : csr.values)
        cout << x << " ";

    cout << endl;
}