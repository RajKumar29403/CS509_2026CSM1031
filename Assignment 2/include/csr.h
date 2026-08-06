#ifndef CSR_H
#define CSR_H

#include <vector>
#include "graph.h"

using namespace std;

struct CSR
{
    vector<int> row_ptr;
    vector<int> col_idx;
    vector<int> values;
};

void convertToCSR(Graph &graph, CSR &csr);

void printCSR(CSR &csr);

#endif