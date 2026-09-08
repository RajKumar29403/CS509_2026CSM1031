#ifndef CSR_GRAPH_H
#define CSR_GRAPH_H

#include <vector>

using namespace std;

struct CSRGraph
{
    int V;
    int E;

    vector<int> row_ptr;
    vector<int> col_idx;
};

#endif