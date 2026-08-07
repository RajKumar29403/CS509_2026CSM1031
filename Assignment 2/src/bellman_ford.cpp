#include "../include/bellman_ford.h"

#include <iostream>

using namespace std;

bool bellmanFord(Graph &graph,
                 CSR &csr,
                 int source,
                 vector<int> &distance)
{
    const int INF = 1000000000;

    distance.assign(graph.V, INF);
    distance[source] = 0;

    // Relax all edges V-1 times
    for (int i = 0; i < graph.V - 1; i++)
    {
        bool updated = false;

        for (int u = 0; u < graph.V; u++)
        {
            for (int j = csr.row_ptr[u]; j < csr.row_ptr[u + 1]; j++)
            {
                int v = csr.col_idx[j];
                int wt = csr.values[j];

                if (distance[u] != INF &&
                    distance[u] + wt < distance[v])
                {
                    distance[v] = distance[u] + wt;
                    updated = true;
                }
            }
        }

        // Stop early if no relaxation happened
        if (!updated)
            break;
    }

    // Check for negative weight cycle
    for (int u = 0; u < graph.V; u++)
    {
        for (int j = csr.row_ptr[u]; j < csr.row_ptr[u + 1]; j++)
        {
            int v = csr.col_idx[j];
            int wt = csr.values[j];

            if (distance[u] != INF &&
                distance[u] + wt < distance[v])
            {
                return false;
            }
        }
    }

    return true;
}