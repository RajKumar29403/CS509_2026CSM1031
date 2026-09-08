#include "../include/csr_graph.h"

#include <vector>

using namespace std;

CSRGraph convertToCSR(const vector<vector<int>>& adj,
                      int V,
                      int E)
{
    CSRGraph csr;

    csr.V = V;
    csr.E = E;

    csr.row_ptr.clear();
    csr.col_idx.clear();

    csr.row_ptr.push_back(0);

    for(int i = 0; i < V; i++)
    {
        for(int neighbour : adj[i])
        {
            csr.col_idx.push_back(neighbour);
        }

        csr.row_ptr.push_back(csr.col_idx.size());
    }

    return csr;
}